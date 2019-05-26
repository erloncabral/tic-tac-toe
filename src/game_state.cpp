#include "game_state.hpp"

#include <iostream>
#include <string>
#include <utility>

#include "game_over.hpp"
#include "pause_state.hpp"

namespace ttc {

inline static const std::string GRID = "game_grid";
inline static const std::string PAUSE_BUTTON = "game_pause_button";
inline static const std::string X_PIECE = "game_x_piece";
inline static const std::string O_PIECE = "game_0_piece";
inline static const std::string X_WIN_PIECE = "game_x_win_piece";
inline static const std::string O_WIN_PIECE = "game_0_win_piece";

GameState::GameState(GameDataRef data)
    : _data(std::move(data))
    , _ia(IA())
{
    _data->assets.load_texture(GRID, Constants::Game::GRID_PATH);
    _data->assets.load_texture(PAUSE_BUTTON, Constants::Game::PAUSE_BUTTON_PATH);
    _data->assets.load_texture(X_PIECE, Constants::Game::X_PATH);
    _data->assets.load_texture(O_PIECE, Constants::Game::O_PATH);
    _data->assets.load_texture(X_WIN_PIECE, Constants::Game::X_WIN_PATH);
    _data->assets.load_texture(O_WIN_PIECE, Constants::Game::O_WIN_PATH);
}

void GameState::init()
{
    _grid.setTexture(_data->assets.get_texture(GRID));
    _pause_button.setTexture(_data->assets.get_texture(PAUSE_BUTTON));

    auto grid_x = (Constants::SCREEN_WIDTH / 2.f) - (_grid.getLocalBounds().width / 2.f);
    auto grid_y = (Constants::SCREEN_HEIGHT / 2.f) - (_grid.getLocalBounds().height / 2.f);
    _grid.setPosition(grid_x, grid_y);

    auto pause_x = Constants::SCREEN_WIDTH - _pause_button.getLocalBounds().width;
    auto pause_y = _pause_button.getPosition().y;
    _pause_button.setPosition(pause_x, pause_y);

    init_grid_pieces();
}

void GameState::handle_input()
{
    sf::Event event{};
    while (_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data->window.close();
        }

        if (_data->input.is_sprite_clicked(event, _pause_button, sf::Mouse::Left, _data->window)) {
            if (_status == Status::playing) {
                _status = Status::paused;
                _data->machine.add_state(StateRef(std::make_unique<PauseState>(_data, _status)),
                                         false);
            }
        }

        if (_status == Status::playing) {
            if (_data->input.is_sprite_clicked(event, _grid, sf::Mouse::Left, _data->window)) {
                for (int x = 0; x < 3; ++x) {
                    for (int y = 0; y < 3; ++y) {
                        if (_data->input.is_sprite_clicked(event,
                                                           _pieces[x][y],
                                                           sf::Mouse::Left,
                                                           _data->window)) {
                            if (Turn turn = _game_grid.get_turn(); play_if_empty(turn, {x, y})) {
                                if (_game_grid.is_turn_win(turn)) {
                                    _status = turn == Turn::ia ? Status::lose : Status::won;
                                }
                                break;
                            } else {
                                return;
                            }
                        }
                    }
                }

                if (_moves <= 0) {
                    _status = Status::draw;
                }

                if (Turn turn = _game_grid.get_turn(); _status == Status::playing) {
                    _ia.play(_game_grid, _pieces);
                    _moves--;
                    if (_game_grid.is_turn_win(turn)) {
                        _status = Status::lose;
                    }
                }
            }
        }

        if (_status == Status::won || _status == Status::lose || _status == Status::draw) {
            _clock.restart();
        }
    }
}

void GameState::update([[maybe_unused]] float dt)
{
    if (_status == Status::won || _status == Status::lose) {
        std::string texture = _status == Status::won ? X_WIN_PIECE : O_WIN_PIECE;
        for (auto &piece : _game_grid.get_wining_grid()) {
            _pieces[piece.x][piece.y].setTexture(_data->assets.get_texture(texture));
        }
    }

    if (_status == Status::won || _status == Status::lose || _status == Status::draw) {
        if (_clock.getElapsedTime().asSeconds() > Constants::GameOver::DELAY_SHOW_TIME) {
            _data->machine.add_state(StateRef(std::make_unique<GameOver>(_data)), true);
        }
    }
}

void GameState::draw([[maybe_unused]] float interpolation)
{
    _data->window.clear(Constants::BACKGROUND_COLOR);
    _data->window.draw(_grid);

    for (auto &row : _pieces) {
        for (auto &col : row) {
            _data->window.draw(col);
        }
    }

    _data->window.draw(_pause_button);
    _data->window.display();
}

void GameState::init_grid_pieces()
{
    sf::Vector2f piece_size = static_cast<sf::Vector2f>(
        _data->assets.get_texture(X_PIECE).getSize());

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            sf::Vector2f pos(_grid.getPosition().x + (piece_size.x * x) - 7.f,
                             _grid.getPosition().y + (piece_size.y * y) - 7.f);
            _pieces[x][y].setTexture(_data->assets.get_texture(O_PIECE));
            _pieces[x][y].setColor(sf::Color::Transparent);
            _pieces[x][y].setPosition(pos);
        }
    }
}

bool GameState::play_if_empty(Turn const &turn, sf::Vector2i const &place)
{
    if (_game_grid.get_piece_status(place) == PieceStatus::empty) {
        if (_game_grid.get_turn() == turn) {
            auto texture = turn == Turn::ia ? O_PIECE : X_PIECE;
            auto piece_status = turn == Turn::ia ? PieceStatus::ia : PieceStatus::player;
            _game_grid.set_piece_status(piece_status, place);
            _pieces[place.x][place.y].setTexture(_data->assets.get_texture(texture));
            _pieces[place.x][place.y].setColor(sf::Color::White);
            _moves--;
            return true;
        }
    }
    return false;
}

} // namespace ttc

#include "game_over.hpp"

#include <string>
#include <utility>

#include "game_state.hpp"
#include "menu_state.hpp"

namespace ttc {

inline static const std::string RETRY_BUTTON = "game_over_retry_button";
inline static const std::string HOME_BUTTON = "game_over_home_button";

GameOver::GameOver(GameDataRef data) : _data(std::move(data))
{
    _data->assets.load_texture(RETRY_BUTTON, Constants::GameOver::RETRY_BUTTON_PATH);
    _data->assets.load_texture(HOME_BUTTON, Constants::Pause::HOME_BUTTON_PATH);
}

void GameOver::init()
{
    _retry_button.setTexture(_data->assets.get_texture(RETRY_BUTTON));
    _home_button.setTexture(_data->assets.get_texture(HOME_BUTTON));

    auto resume_x = (Constants::SCREEN_WIDTH / 2.f) - (_retry_button.getLocalBounds().width / 2.f);
    auto resume_y = (Constants::SCREEN_HEIGHT / 3.f)
                    - (_retry_button.getLocalBounds().height / 2.f);
    _retry_button.setPosition(resume_x, resume_y);

    auto home_x = (Constants::SCREEN_WIDTH / 2.f) - (_home_button.getLocalBounds().width / 2.f);
    auto home_y = (Constants::SCREEN_HEIGHT / 3.f * 2.f)
                  - (_home_button.getLocalBounds().height / 2.f);
    _home_button.setPosition(home_x, home_y);
}

void GameOver::handle_input()
{
    sf::Event event{};
    while (_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data->window.close();
        }

        if (_data->input.is_sprite_clicked(event, _retry_button, sf::Mouse::Left, _data->window)) {
            _data->machine.add_state(StateRef(std::make_unique<GameState>(_data)), true);
        }

        if (_data->input.is_sprite_clicked(event, _home_button, sf::Mouse::Left, _data->window)) {
            _data->machine.add_state(StateRef(std::make_unique<MenuState>(_data)), true);
        }
    }
}

void GameOver::update([[maybe_unused]] float dt) {}

void GameOver::draw([[maybe_unused]] float interpolation)
{
    _data->window.clear(sf::Color::Red);
    _data->window.draw(_retry_button);
    _data->window.draw(_home_button);
    _data->window.display();
}

} // namespace ttc

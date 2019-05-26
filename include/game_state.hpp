#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "game_grid.hpp"
#include "ia.hpp"
#include "state.hpp"

namespace ttc {

inline static const int MAX_PIECES_MOVES = COLUMNS * COLUMNS;

class GameState : public State
{
private:
    GameDataRef _data;
    GameGrid _game_grid;
    Status _status{Status::playing};
    IA _ia;

    int _moves = MAX_PIECES_MOVES;

    sf::Sprite _grid;
    sf::Sprite _pause_button;
    sf::Sprite _pieces[COLUMNS][COLUMNS]{{}, {}};
    sf::Clock _clock;

    void init_grid_pieces();
    bool play_if_empty(Turn const &turn, sf::Vector2i const &place);

public:
    explicit GameState(GameDataRef data);

    void init() override;
    void handle_input() override;
    void update(float dt) override;
    void draw(float interpolation) override;
};

} // namespace ttc

#endif // GAME_STATE_HPP

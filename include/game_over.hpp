#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "state.hpp"

namespace ttc {

class GameOver : public State
{
private:
    GameDataRef _data;

    sf::Sprite _home_button;
    sf::Sprite _retry_button;

public:
    explicit GameOver(GameDataRef data);

    void init() override;
    void handle_input() override;
    void update(float dt) override;
    void draw(float interpolation) override;
};

} // namespace ttc

#endif // GAME_OVER_HPP

#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "game_state.hpp"
#include "state.hpp"

namespace ttc {

class PauseState : public State
{
private:
    GameDataRef _data;
    Status &_status;

    sf::Sprite _background;
    sf::Sprite _home_button;
    sf::Sprite _resume_button;

public:
    PauseState(GameDataRef data, Status &status);

    void init() override;
    void handle_input() override;
    void update(float dt) override;
    void draw(float interpolation) override;
};

} // namespace ttc

#endif // PAUSE_STATE_HPP

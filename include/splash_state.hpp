#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "state.hpp"

namespace ttc {

class SplashState : public State
{
private:
    GameDataRef _data;

    sf::Clock _clock;
    sf::Sprite _background;

public:
    explicit SplashState(GameDataRef data);

    void init() override;
    void handle_input() override;
    void update(float dt) override;
    void draw(float interpolation) override;
};

} // namespace ttc

#endif // SPLASH_STATE_HPP

#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "state.hpp"

namespace ttc {

class MenuState : public State
{
private:
    GameDataRef _data;

    sf::Sprite _title;
    sf::Sprite _button;
    sf::Sprite _outer;

public:
    explicit MenuState(GameDataRef data);

    void init() override;
    void handle_input() override;
    void update(float dt) override;
    void draw(float interpolation) override;
};

} // namespace ttc

#endif // MENU_STATE_HPP

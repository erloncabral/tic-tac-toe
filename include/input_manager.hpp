#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SFML/Graphics.hpp>

namespace ttc {

class InputManager
{
public:
    bool is_sprite_clicked(sf::Event const &event,
                           sf::Sprite const &sprite,
                           sf::Mouse::Button const &button,
                           sf::RenderWindow const &window);
    static sf::Vector2i const get_mouse_position(sf::RenderWindow const &window);
};

} // namespace ttc

#endif // INPUT_MANAGER_HPP

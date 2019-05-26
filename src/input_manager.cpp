#include "input_manager.hpp"

namespace ttc {

bool InputManager::is_sprite_clicked(sf::Event const &event,
                                     sf::Sprite const &sprite,
                                     sf::Mouse::Button const &button,
                                     sf::RenderWindow const &window)
{
    if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(button)) {
        auto mouse_pos = static_cast<sf::Vector2f>(get_mouse_position(window));
        return sprite.getGlobalBounds().contains(mouse_pos);
    }
    return false;
}

sf::Vector2i const InputManager::get_mouse_position(sf::RenderWindow const &window)
{
    return sf::Mouse::getPosition(window);
}

} // namespace ttc

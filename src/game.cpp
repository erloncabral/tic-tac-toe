#include "game.hpp"
#include "splash_state.hpp"

namespace ttc {

Game::Game(unsigned int const &width, unsigned int const &height,
           std::string const &title)
    : _data(std::make_shared<GameData>())
{
    _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close);
    if (sf::Image icon; icon.loadFromFile(Constants::ICON_PATH)) {
        _data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    _data->window.setFramerateLimit(Constants::FRAMERATE_LIMIT);
    _data->machine.add_state(StateRef(std::make_unique<SplashState>(_data)));
    run();
}

void Game::run()
{
    while (_data->window.isOpen()) {
        sf::Time elapsed = _clock.restart();
        float dt = elapsed.asSeconds();
        _data->machine.process_state_changes();
        _data->machine.get_active_state()->handle_input();
        _data->machine.get_active_state()->update(dt);
        _data->machine.get_active_state()->draw(dt);
    }
}

} // namespace ttc

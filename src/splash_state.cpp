#include "splash_state.hpp"

#include <string>
#include <utility>

#include "menu_state.hpp"

namespace ttc {

const std::string BACKGROUND = "splash_background";

SplashState::SplashState(GameDataRef data)
    : _data(std::move(data))
{
    _data->assets.load_texture(BACKGROUND, Constants::Splash::BACKGROUND_PATH);
}

void SplashState::init()
{
    _background.setTexture(_data->assets.get_texture(BACKGROUND));
}

void SplashState::handle_input()
{
    sf::Event event{};
    while (_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data->window.close();
        }
    }
}

void SplashState::update([[maybe_unused]] float dt)
{
    if (_clock.getElapsedTime().asSeconds() > Constants::Splash::SHOW_TIME) {
        _data->machine.add_state(StateRef(std::make_unique<MenuState>(_data)), true);
    }
}

void SplashState::draw([[maybe_unused]] float interpolation)
{
    _data->window.clear();
    _data->window.draw(_background);
    _data->window.display();
}

} // namespace ttc

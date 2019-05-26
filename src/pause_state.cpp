#include "pause_state.hpp"

#include <string>
#include <utility>

#include "menu_state.hpp"

namespace ttc {

inline static const std::string BACKGROUND = "pause_background";
inline static const std::string RESUME_BUTTON = "pause_resume_button";
inline static const std::string HOME_BUTTON = "pause_home_button";

PauseState::PauseState(GameDataRef data, Status &status)
    : _data(std::move(data))
    , _status(status)
{
    _data->assets.load_texture(BACKGROUND, Constants::Pause::BACKGROUND_PATH);
    _data->assets.load_texture(RESUME_BUTTON, Constants::Pause::RESUME_BUTTON_PATH);
    _data->assets.load_texture(HOME_BUTTON, Constants::Pause::HOME_BUTTON_PATH);
}

void PauseState::init()
{
    _background.setTexture(_data->assets.get_texture(BACKGROUND));
    _resume_button.setTexture(_data->assets.get_texture(RESUME_BUTTON));
    _home_button.setTexture(_data->assets.get_texture(HOME_BUTTON));

    auto resume_x = (Constants::SCREEN_WIDTH / 2.f) - (_resume_button.getLocalBounds().width / 2.f);
    auto resume_y = (Constants::SCREEN_HEIGHT / 3.f)
                    - (_resume_button.getLocalBounds().height / 2.f);
    _resume_button.setPosition(resume_x, resume_y);

    auto home_x = (Constants::SCREEN_WIDTH / 2.f) - (_home_button.getLocalBounds().width / 2.f);
    auto home_y = (Constants::SCREEN_HEIGHT / 3.f * 2.f)
                  - (_home_button.getLocalBounds().height / 2.f);
    _home_button.setPosition(home_x, home_y);
}

void PauseState::handle_input()
{
    sf::Event event{};
    while (_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data->window.close();
        }

        if (_data->input.is_sprite_clicked(event, _resume_button, sf::Mouse::Left, _data->window)) {
            _status = Status::playing;
            _data->machine.remove_state();
        }

        if (_data->input.is_sprite_clicked(event, _home_button, sf::Mouse::Left, _data->window)) {
            _data->machine.remove_state();
            _data->machine.add_state(StateRef(std::make_unique<MenuState>(_data)), true);
        }
    }
}

void PauseState::update([[maybe_unused]] float dt) {}

void PauseState::draw([[maybe_unused]] float interpolation)
{
    _data->window.draw(_background);
    _data->window.draw(_resume_button);
    _data->window.draw(_home_button);
    _data->window.display();
}

} // namespace ttc

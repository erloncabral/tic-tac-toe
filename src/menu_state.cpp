#include "menu_state.hpp"

#include <string>
#include <utility>

#include "game_state.hpp"

namespace ttc {

inline static const std::string BACKGROUND = "menu_background";
inline static const std::string BUTTON = "menu_button";
inline static const std::string BUTTON_OUTER = "menu_button_outer";
inline static const std::string TITLE = "menu_title";

MenuState::MenuState(GameDataRef data)
    : _data(std::move(data))
{
    _data->assets.load_texture(BUTTON, Constants::Menu::PLAY_BUTTON_PATH);
    _data->assets.load_texture(BUTTON_OUTER, Constants::Menu::PLAY_BUTTON_OUTER_PATH);
    _data->assets.load_texture(TITLE, Constants::Menu::TITLE_PATH);
}

void MenuState::init()
{
    _title.setTexture(_data->assets.get_texture(TITLE));
    _button.setTexture(_data->assets.get_texture(BUTTON));
    _outer.setTexture(_data->assets.get_texture(BUTTON_OUTER));

    auto title_x = (Constants::SCREEN_WIDTH / 2.f) - (_title.getLocalBounds().width / 2.f);
    auto title_y = static_cast<int>(_button.getLocalBounds().height * .1f);
    _title.setPosition(title_x, title_y);

    auto button_x = (Constants::SCREEN_WIDTH / 2.f) - (_button.getLocalBounds().width / 2.f);
    auto button_y = (Constants::SCREEN_HEIGHT / 2.f) - (_button.getLocalBounds().height / 2.f);
    _button.setPosition(button_x, button_y);

    auto outer_x = (Constants::SCREEN_WIDTH / 2.f) - (_outer.getLocalBounds().width / 2.f);
    auto outer_y = (Constants::SCREEN_HEIGHT / 2.f) - (_outer.getLocalBounds().height / 2.f);
    _outer.setPosition(outer_x, outer_y);
}

void MenuState::handle_input()
{
    sf::Event event{};
    while (_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            _data->window.close();
        }

        if (_data->input.is_sprite_clicked(event, _button, sf::Mouse::Left, _data->window)) {
            _data->machine.add_state(StateRef(std::make_unique<GameState>(_data)), true);
        }
    }
}

void MenuState::update([[maybe_unused]] float dt) {}

void MenuState::draw([[maybe_unused]] float interpolation)
{
    _data->window.clear(Constants::BACKGROUND_COLOR);
    _data->window.draw(_title);
    _data->window.draw(_outer);
    _data->window.draw(_button);
    _data->window.display();
}

} // namespace ttc

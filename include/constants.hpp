#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace ttc {

struct Constants
{
    struct Splash
    {
        inline static const float SHOW_TIME = 1.25f;

        inline static const std::string BACKGROUND_PATH = "resources/sprites/splash_background.png";
    };

    struct Menu
    {
        inline static const std::string TITLE_PATH = "resources/sprites/game_title.png";
        inline static const std::string PLAY_BUTTON_PATH = "resources/sprites/play_button.png";
        inline static const std::string PLAY_BUTTON_OUTER_PATH
            = "resources/sprites/play_button_outer.png";
    };

    struct Game
    {
        inline static const std::string GRID_PATH = "resources/sprites/grid.png";
        inline static const std::string PAUSE_BUTTON_PATH = "resources/sprites/pause_button.png";
        inline static const std::string X_PATH = "resources/sprites/x.png";
        inline static const std::string O_PATH = "resources/sprites/o.png";
        inline static const std::string X_WIN_PATH = "resources/sprites/x_win.png";
        inline static const std::string O_WIN_PATH = "resources/sprites/o_win.png";
    };

    struct Pause
    {
        inline static const std::string BACKGROUND_PATH = "resources/sprites/pause_background.png";
        inline static const std::string RESUME_BUTTON_PATH = "resources/sprites/resume_button.png";
        inline static const std::string HOME_BUTTON_PATH = "resources/sprites/home_button.png";
    };

    struct GameOver
    {
        inline static const float DELAY_SHOW_TIME = 0.4f;
        inline static const std::string RETRY_BUTTON_PATH = "resources/sprites/retry_button.png";
    };

    inline static const std::string ICON_PATH = "resources/sprites/icon.png";
    inline static const sf::Color BACKGROUND_COLOR = sf::Color(241, 213, 94);

    inline static const int FRAMERATE_LIMIT = 60;
    inline static const unsigned int SCREEN_WIDTH = 768;
    inline static const unsigned int SCREEN_HEIGHT = 1136;
};

} // namespace ttc

#endif // DEFINITIONS_HPP

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "asset_manager.hpp"
#include "input_manager.hpp"
#include "state_machine.hpp"

#include "constants.hpp"

namespace ttc {

struct GameData
{
    AssetManager assets;
    InputManager input;
    StateMachine machine;
    sf::RenderWindow window;
};

using GameDataRef = std::shared_ptr<GameData>;

class Game
{
private:
    sf::Clock _clock;
    GameDataRef _data;

    void run();

public:
    Game(unsigned int const &width, unsigned int const &height, std::string const &title);
};

} // namespace ttc

#endif // GAME_HPP

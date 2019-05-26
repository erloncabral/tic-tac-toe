#ifndef IA_HPP
#define IA_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>

#include "game.hpp"
#include "game_grid.hpp"

namespace ttc {

inline static const int WINNING_COLUMNS = 6;

class IA
{
private:
    std::vector<std::array<int, WINNING_COLUMNS>> _winning_matches;

    bool play_next_empty_piece(sf::Vector2i const &place,
                               GameGrid &game_grid,
                               sf::Sprite pieces[COLUMNS][COLUMNS]);
    bool defensive_play(sf::Vector2i const &place1,
                        sf::Vector2i const &place2,
                        sf::Vector2i const &player_place,
                        PieceStatus const &check_piece,
                        GameGrid &game_grid,
                        sf::Sprite pieces[COLUMNS][COLUMNS]);

public:
    IA();

    void play(GameGrid &game_grid, sf::Sprite pieces[COLUMNS][COLUMNS]);
};

} // namespace ttc

#endif // IA_HPP

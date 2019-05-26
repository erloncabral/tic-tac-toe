#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include <SFML/Graphics.hpp>
#include <array>

namespace ttc {

enum class Turn { player, ia };
enum class PieceStatus : int { empty = 0, player = 1, ia = 2 };
enum class Status { playing, paused, won, lose, draw };

inline static const int COLUMNS = 3;

class GameGrid
{
private:
    Turn _turn{Turn::player};
    std::array<sf::Vector2i, COLUMNS> _wining_grid;
    int _grid[COLUMNS][COLUMNS]{{0, 0, 0}, {0, 0, 0}};

public:
    GameGrid();

    Turn get_turn() const;
    PieceStatus get_piece_status(sf::Vector2i const &piece) const;
    bool is_turn_win(Turn const &turn);
    std::array<sf::Vector2i, COLUMNS> get_wining_grid() const;
    bool check_match_three(Turn const &turn,
                           sf::Vector2i const &p1,
                           sf::Vector2i const &p2,
                           sf::Vector2i const &p3);
    void set_piece_status(PieceStatus const status, sf::Vector2i const &piece);
};

} // namespace ttc

#endif // GAME_GRID_HPP

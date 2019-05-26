#include "game_grid.hpp"

namespace ttc {

GameGrid::GameGrid()
{
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            set_piece_status(PieceStatus::empty, {x, y});
        }
    }
}

Turn GameGrid::get_turn() const { return _turn; }

PieceStatus GameGrid::get_piece_status(sf::Vector2i const &piece) const
{
    return static_cast<PieceStatus>(_grid[piece.x][piece.y]);
}

bool GameGrid::is_turn_win(Turn const &turn)
{
    // Loop through the rows
    for (int i = 0; i < 3; i++) {
        if (check_match_three(turn, {i, 0}, {i, 1}, {i, 2})) {
            return true;
        }
    }

    // Loop through the columns
    for (int i = 0; i < 3; i++) {
        if (check_match_three(turn, {0, i}, {1, i}, {2, i})) {
            return true;
        }
    }

    // Check diagonals
    return check_match_three(turn, {0, 0}, {1, 1}, {2, 2}) ||
            check_match_three(turn, {0, 2}, {1, 1}, {2, 0});
}

bool GameGrid::check_match_three(Turn const &turn,
                                 sf::Vector2i const &p1,
                                 sf::Vector2i const &p2,
                                 sf::Vector2i const &p3)
{
    auto player = static_cast<int>(turn == Turn::player ? PieceStatus::player : PieceStatus::ia);
    if (_grid[p1.x][p1.y] == player && _grid[p2.x][p2.y] == player && _grid[p3.x][p3.y] == player) {
        _wining_grid.at(0) = p1;
        _wining_grid.at(1) = p2;
        _wining_grid.at(2) = p3;
        return true;
    }
    return false;
}

std::array<sf::Vector2i, COLUMNS> GameGrid::get_wining_grid() const
{
    return _wining_grid;
}

void GameGrid::set_piece_status(PieceStatus const status, sf::Vector2i const &piece)
{
    _grid[piece.x][piece.y] = static_cast<int>(status);

    if (status == PieceStatus::player) {
        _turn = Turn::ia;
    }

    if (status == PieceStatus::ia) {
        _turn = Turn::player;
    }
}

} // namespace ttc

#include "ia.hpp"

namespace ttc {

IA::IA()
{
    _winning_matches.push_back({0, 2, 1, 2, 2, 2});
    _winning_matches.push_back({0, 2, 0, 1, 0, 0});
    _winning_matches.push_back({0, 2, 1, 1, 2, 0});
    _winning_matches.push_back({2, 2, 1, 2, 0, 2});
    _winning_matches.push_back({2, 2, 2, 1, 2, 0});
    _winning_matches.push_back({2, 2, 1, 1, 0, 0});
    _winning_matches.push_back({0, 0, 0, 1, 0, 2});
    _winning_matches.push_back({0, 0, 1, 0, 2, 0});
    _winning_matches.push_back({0, 0, 1, 1, 2, 2});
    _winning_matches.push_back({2, 0, 2, 1, 2, 2});
    _winning_matches.push_back({2, 0, 1, 0, 0, 0});
    _winning_matches.push_back({2, 0, 1, 1, 0, 2});
    _winning_matches.push_back({0, 1, 1, 1, 2, 1});
    _winning_matches.push_back({1, 2, 1, 1, 1, 0});
    _winning_matches.push_back({2, 1, 1, 1, 0, 1});
    _winning_matches.push_back({1, 0, 1, 1, 1, 2});
    _winning_matches.push_back({0, 1, 2, 1, 1, 1});
    _winning_matches.push_back({1, 2, 1, 0, 1, 1});
    _winning_matches.push_back({0, 2, 2, 0, 1, 1});
    _winning_matches.push_back({2, 2, 0, 0, 1, 1});
    _winning_matches.push_back({0, 2, 2, 2, 1, 2});
    _winning_matches.push_back({0, 0, 2, 0, 1, 0});
    _winning_matches.push_back({0, 2, 0, 0, 0, 1});
    _winning_matches.push_back({2, 2, 2, 0, 2, 1});
}

void IA::play(GameGrid &game_grid, sf::Sprite pieces[COLUMNS][COLUMNS])
{
    // check if IA can win
    for (auto &match : _winning_matches) {
        if (defensive_play({match.at(0), match.at(1)},
                           {match.at(2), match.at(3)},
                           {match.at(4), match.at(5)},
                           PieceStatus::ia,
                           game_grid,
                           pieces)) {
            return;
        }
    }

    // check if player can win
    for (auto &match : _winning_matches) {
        if (defensive_play({match.at(0), match.at(1)},
                           {match.at(2), match.at(3)},
                           {match.at(4), match.at(5)},
                           PieceStatus::player,
                           game_grid,
                           pieces)) {
            return;
        }
    }

    // check if center is empty
    if (play_next_empty_piece({1, 1}, game_grid, pieces)) {
        return;
    }

    // check if a corner is empty
    if (play_next_empty_piece({0, 2}, game_grid, pieces)
        || play_next_empty_piece({2, 2}, game_grid, pieces)
        || play_next_empty_piece({0, 0}, game_grid, pieces)
        || play_next_empty_piece({2, 0}, game_grid, pieces)) {
        return;
    }

    // check for any other empty piece
    if (play_next_empty_piece({1, 2}, game_grid, pieces)
        || play_next_empty_piece({0, 1}, game_grid, pieces)
        || play_next_empty_piece({2, 1}, game_grid, pieces)
        || play_next_empty_piece({1, 0}, game_grid, pieces)) {
        return;
    }
}

bool IA::play_next_empty_piece(sf::Vector2i const &place,
                               GameGrid &game_grid,
                               sf::Sprite pieces[COLUMNS][COLUMNS])
{
    if (PieceStatus::empty == game_grid.get_piece_status(place)) {
        game_grid.set_piece_status(PieceStatus::ia, place);
        pieces[place.x][place.y].setColor(sf::Color::White);
        return true;
    }
    return false;
}

bool IA::defensive_play(sf::Vector2i const &place1,
                        sf::Vector2i const &place2,
                        sf::Vector2i const &player_place,
                        PieceStatus const &check_piece,
                        GameGrid &game_grid,
                        sf::Sprite pieces[COLUMNS][COLUMNS])
{
    if (game_grid.get_piece_status(place1) == check_piece
        && game_grid.get_piece_status(place2) == check_piece) {
        if (PieceStatus::empty == game_grid.get_piece_status(player_place)) {
            game_grid.set_piece_status(PieceStatus::ia, player_place);
            pieces[player_place.x][player_place.y].setColor(sf::Color::White);
            return true;
        }
    }
    return false;
}

} // namespace ttc

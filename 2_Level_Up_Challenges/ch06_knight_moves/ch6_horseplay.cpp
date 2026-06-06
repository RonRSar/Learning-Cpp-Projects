// C++ Code Challenges, LinkedIn Learning

// Challenge #6: Horseplay
// Write a function that takes in the location of a knight in a chessboard and returns a vector of strings with the possible locations it might move to.
// The locations are expressed as strings in algebraic notation.
// Print the list on the terminal.
// Don't worry about other pieces on the chessboard.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// knight_moves()
// Summary: This function receives a string with the location of a knight in a chessboard and returns a vector of strings with the possible locations it might move to.
// Arguments:
//           knight: The knight's location.
// Returns: An STL vector of strings with the possible locations to move.

// This was very inefficient! I think my mistake was not abstracting the problem down
// working with the string notation of the chessboard directly
std::vector<std::string> knight_moves(std::string knight)
{
    std::vector<std::string> moves;

    std::vector<std::string> alpha_grid{"a", "b", "c", "d", "e", "f", "g", "h"};
    std::vector<std::string> num_grid{"1", "2", "3", "4", "5", "6", "7", "8"};

    std::string k_alpha(1, knight[0]);
    std::string k_num(1, knight[1]);

    // find where target is by std::find
    auto alpha_it = std::find(alpha_grid.begin(), alpha_grid.end(), k_alpha);
    auto num_it = std::find(num_grid.begin(), num_grid.end(), k_num);

    // add 2 to alpha, then 1 to num, and vice versa
    std::vector<std::string> possible_moves{};

    // Check every valid position before adding to moves. Inefficient (O(8)?) but works c:
    // Potential improvement would be to abstract this to a loop.
    if (std::find(alpha_grid.begin(), alpha_grid.end(), *(alpha_it + 2)) != alpha_grid.end())
    {
        if (std::find(num_grid.begin(), num_grid.end(), *(num_it + 1)) != num_grid.end())
            possible_moves.push_back(*(alpha_it + 2) + *(num_it + 1));
        if (std::find(num_grid.begin(), num_grid.end(), *(num_it - 1)) != num_grid.end())
            possible_moves.push_back(*(alpha_it + 2) + *(num_it - 1));
    }
    if (std::find(alpha_grid.begin(), alpha_grid.end(), *(alpha_it - 2)) != alpha_grid.end())
    {
        if (std::find(num_grid.begin(), num_grid.end(), *(num_it + 1)) != num_grid.end())
            possible_moves.push_back(*(alpha_it - 2) + *(num_it + 1));
        if (std::find(num_grid.begin(), num_grid.end(), *(num_it - 1)) != num_grid.end())
            possible_moves.push_back(*(alpha_it - 2) + *(num_it - 1));
    }

    if (std::find(num_grid.begin(), num_grid.end(), *(num_it + 2)) != num_grid.end())
    {
        if (std::find(alpha_grid.begin(), alpha_grid.end(), *(alpha_it + 1)) != alpha_grid.end())
            possible_moves.push_back(*(alpha_it + 1) + *(num_it + 2));
        if (std::find(alpha_grid.begin(), alpha_grid.end(), *(alpha_it - 1)) != alpha_grid.end())
            possible_moves.push_back(*(alpha_it - 1) + *(num_it + 2));
    }
    if (std::find(num_grid.begin(), num_grid.end(), *(num_it - 2)) != num_grid.end())
    {
        if (std::find(alpha_grid.begin(), alpha_grid.end(), *(alpha_it + 1)) != alpha_grid.end())
            possible_moves.push_back(*(alpha_it + 1) + *(num_it - 2));
        if (std::find(alpha_grid.begin(), alpha_grid.end(), *(alpha_it - 1)) != alpha_grid.end())
            possible_moves.push_back(*(alpha_it - 1) + *(num_it - 2));
    }

    // add all existing places to moves
    moves = std::move(possible_moves);
    return moves;
}

// This function was my attempt to optimise it so its more readable and less verbose
// no need for a vector for the individual grids. also no need for possible_moves vector.
// im sure there is perhaps room for even smaller code (like by writing out the move matrix)
// but im satisfied with this solution and think its an improvement over the last one.  
std::vector<std::string> optimal_imp_knight_moves(std::string knight)
{
    std::vector<std::string> moves{};
    char k_alpha{knight[0]};
    char k_num{knight[1]};

    const char delta_i[2] = {-2, 2};
    const char delta_j[2] = {-1, 1};

    auto find_knight_moves = [&moves, &delta_i, &delta_j](char grid_alpha, char grid_num, bool flip)
    {
        char new_k_alpha{}, new_k_num{};
        for (auto i : delta_i)
        {
            for (auto j : delta_j)
            {
                if (flip)
                {
                    new_k_alpha = grid_alpha + i;
                    new_k_num = grid_num + j;
                }
                else
                {
                    new_k_alpha = grid_alpha + j;
                    new_k_num = grid_num + i;
                }

                if  (new_k_alpha >= 'a' && new_k_alpha <= 'h' && new_k_num >= '1' && new_k_num <= '8')
                {
                    moves.push_back(std::string(1, new_k_alpha) + std::string(1, new_k_num));
                }
            }
        }
    };

    find_knight_moves(k_alpha, k_num, true); //true means add 2 to alpha first then 1 to num 
    find_knight_moves(k_alpha, k_num, false); //false means opposite

    return moves;
}

bool check_moves(const std::string &knight, const std::vector<std::string> &expected)
{
    std::vector<std::string> result = optimal_imp_knight_moves(knight);
    if (result.size() != expected.size())
        return false;
    std::vector<std::string> r = result;
    std::vector<std::string> e = expected;
    std::sort(r.begin(), r.end());
    std::sort(e.begin(), e.end());
    return r == e;
}

// Main function
int main()
{
    int passed = 0, failed = 0;

    struct
    {
        std::string pos;
        std::vector<std::string> expected;
    } tests[] = {
        {"d4", {"b3", "b5", "c2", "c6", "e2", "e6", "f3", "f5"}},
        {"a1", {"b3", "c2"}},
        {"h1", {"f2", "g3"}},
        {"a8", {"b6", "c7"}},
        {"h8", {"f7", "g6"}},
        {"a4", {"b2", "b6", "c3", "c5"}},
        {"h5", {"f4", "f6", "g3", "g7"}},
        {"d1", {"b2", "c3", "e3", "f2"}},
        {"e5", {"c4", "c6", "d3", "d7", "f3", "f7", "g4", "g6"}},
        {"c3", {"a2", "a4", "b1", "b5", "d1", "d5", "e2", "e4"}}};

    for (auto &t : tests)
    {
        if (check_moves(t.pos, t.expected))
        {
            std::cout << "Pass\n";
            passed++;
        }
        else
        {
            std::cout << "Fail\n";
            failed++;
        }
    }
    std::cout << "\n"
              << passed << " passed, " << failed << " failed\n";
    return failed > 0 ? 1 : 0;
}
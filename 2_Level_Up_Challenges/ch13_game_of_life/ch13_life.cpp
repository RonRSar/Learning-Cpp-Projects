// C++ Code Challenges, LinkedIn Learning

// Challenge #13: Conway's Game of Life
// Write an application that runs Conway's Game of Life, the best-known cellular automaton.
// Do this for a 10x10 grid.
// The grid wraps around in all directions, like the Pac-Man world.

// Rules:
// Any live cell with fewer than two live neighbors dies, as if by underpopulation.
// Any live cell with two or three live neighbors lives on to the next generation.
// Any live cell with more than three live neighbors dies, as if by overpopulation.
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>

#define N 10
#define M 10

// Conway's Game of Life, main()
// Summary: This application is a simulation of Conway's game of life.
int main()
{
    // The game, initialized with a glider and a blinker.
    char game[N][M];
    std::memset(game, '-', N * M); // Initialize game with dashes.

    // A glider     // - - - - - - - - - -
    game[1][1] = 'X'; // - X - - - - - - - -
    game[2][2] = 'X'; // - - X - - - - - - -
    game[3][0] = 'X'; // X X X - - - - - - -
    game[3][1] = 'X';
    game[3][2] = 'X';

    // A blinker    // - - - - - - - - - -
    game[3][6] = 'X'; // - - - - - - - - - -
    game[3][7] = 'X'; // - - - - - - - - - -
    game[3][8] = 'X'; // - - - - - - X X X -

    int generation = 0;
    std::string go_on;
    // Matrix of all neighbours relative to cell
    const int displacement[8][2] = {
        { 0,  1},
        { 0, -1},
        { 1,  0},
        { 1,  1},
        { 1, -1},
        {-1,  0},
        {-1,  1},
        {-1, -1}};
    int num_neighbours{};

    // lambda func to find number of live neighbours
    auto find_num_neighbours = [&displacement, &game, &num_neighbours](int i, int j)
    {
        int index_1{}, index_2{};
        for (auto d : displacement)
        {
            // using modulo here to get values that are always within 0 - bounds;
            index_1 = (i + N + d[0]) % N;
            index_2 = (j + M + d[1]) % M;
            // an alternate way to do this by manually using if statements for wrap around
            // if (i + d[0] > N - 1)
            //     index_1 = 0;
            // if (i + d[0] < 0)
            //     index_1 = N - 1;
            // if (j + d[1] > M - 1)
            //     index_2 = 0;
            // if (j + d[1] < 0)
            //     index_2 = M - 1;
            if (game[index_1][index_2] == 'X')
                num_neighbours += 1;
        }
    };

    do
    {
        std::cout << "Generation #" << generation++ << "\n";
        for (auto &str : game)
        {
            for (auto &ch : str)
                std::cout << " " << ch;
            std::cout << "\n";
        }
        std::cout << "\n";

        std::vector<std::pair<int, int>> update_lives{}, update_deads{};
        // it would be more memory efficient to use a char new_game[N][M]
        // but this was my original solution so I'm keeping it as it is
        // a double buffer approach would mean no heap allocations
        // and a std::memcpy could be used between game and new_game

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                num_neighbours = 0;
                if (game[i][j] == 'X')
                { // Live cell
                    find_num_neighbours(i, j);
                    switch (num_neighbours)
                    {
                    // 2 or 3 neighbours live
                    case 2:
                    case 3:
                        update_lives.push_back({i, j});
                        break;

                    default: // anything else dies
                        update_deads.push_back({i, j});
                        break;
                    }
                }
                else
                { // Dead cell
                    find_num_neighbours(i, j);
                    if (num_neighbours == 3)
                        update_lives.push_back({i, j}); // if 3 alive neighbours, cell is alive
                }
            }
        }

        // Only update after passing through whole grid, to prevent incorrect decisions based on wrong state
        for (const auto& ul : update_lives)
        {
            game[ul.first][ul.second] = 'X';
        }
        for (const auto& ud : update_deads)
        {
            game[ud.first][ud.second] = '-';
        }

        std::cout << "Press Enter for the next generation, or type \"Exit\": " << std::flush;
        std::getline(std::cin, go_on);
        std::transform(go_on.begin(), go_on.end(), go_on.begin(), toupper);
        std::cout << "\n"
                  << std::flush;
    } while (go_on.compare("EXIT") != 0);

    return 0;
}

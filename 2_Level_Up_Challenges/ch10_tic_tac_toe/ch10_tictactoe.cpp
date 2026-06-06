// C++ Code Challenges, LinkedIn Learning

// Challenge #10: Playing Tic-Tac-Toe
// Write an application that plays Tic-Tac-Toe against the user.

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

// ask_for_move()
// Summary: This function asks the user to make a move.
// Arguments:
//           game[3][3]: The state of the game.
//           mark: The user's mark: 'X' or 'O'.
// Returns: Nothing.
void ask_for_move(char game[][3], char mark)
{
    std::string str;
    int row, col;
    while (true)
    {
        std::cout << "Place your mark (" << mark << ") in row: " << std::flush;
        std::cin >> str;
        try //added some nicer try-catch blocks to stop hard fails. 
        {
            size_t len = 0;
            row = stoi(str, &len);
            if (len != str.length() || row < 1 || row > 3) //added bounds checking so that theres no segmentation faults
                throw std::invalid_argument("");
        }
        catch (...) // catch all errors
        {
            std::cout << "Invalid row!\n";
            continue;
        }

        std::cout << "Place your mark (" << mark << ") in column: " << std::flush;
        std::cin >> str;
        try
        {
            size_t len = 0;
            col = stoi(str, &len);
            if (len != str.length() || col < 1 || col > 3)
                throw std::invalid_argument("");
        }
        catch (...)
        {
            std::cout << "Invalid column!\n";
            continue;
        }

        if (game[row - 1][col - 1] != ' ')
            std::cout << "That cell is taken!\n";
        else
            break;
    }
    game[row - 1][col - 1] = mark;
}

// game_state()
// Summary: This function returns the state of a game.
// Arguments:
//           game[3][3]: The state of the game.
// Returns: A character encoded as:
//                                  'a': An active game.
//                                  'X': X won.
//                                  'O': O won.
//                                  't': A tie.
char game_state(char game[][3])
{
    int filled_square{0};
    for (int i = 0; i < 3; i++)
    {
        if (game[i][0] != ' ' && game[i][0] == game[i][1] && game[i][1] == game[i][2])
            return game[i][0];

        if (game[0][i] != ' ' && game[0][i] == game[1][i] && game[1][i] == game[2][i])
            return game[0][i];

        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] != ' ')
                filled_square++;
        }
    }

    // diagonals
    if (game[0][0] != ' ' && game[0][0] == game[1][1] && game[1][1] == game[2][2])
        return game[0][0];
    if (game[0][2] != ' ' && game[0][2] == game[1][1] && game[1][1] == game[2][0])
        return game[0][2];

    if (filled_square == 9)
        return 't';

    return 'a';
}

// recursively find best move with minimax 
//(i looked up the specifics on how to implement this but I knew that manually trying 
// to find the best possible places seemed incorrect/inefficient to me so i begun by assinging each
// square a value until I realised that there is probably an existing optimisation algo for this)
int minimax(char game[][3], char mark, bool maximise_score)
{
    char state = game_state(game);
    if (state != 'a')
    {
        if (state == 't')
            return 0; // we tie...
        if (state == mark)
            return 10; // we win!
        if (state != mark)
            return -10; // we lose :( (i dont think it is possible to reach this since optimal TTT moves always end in a draw)
    }

    char opponent{};
    if (mark == 'X')
        opponent = 'O';
    else
        opponent = 'X';

    if (maximise_score)
    {
        int best = -100; // we want our starting best score to be very low to max it
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (game[i][j] == ' ')
                {
                    game[i][j] = mark;
                    best = std::max(best, minimax(game, mark, false));
                    //must reset after finding because we are passing char array in by pointer so it directly modifies
                    game[i][j] = ' ';
                }
        return best;
    }
    else
    {
        int best = 100; // we want to minimise our opponents score
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (game[i][j] == ' ')
                {
                    game[i][j] = opponent;
                    best = std::min(best, minimax(game, mark, true));
                    game[i][j] = ' ';
                }
        return best;
    }
}

// make_move()
// Summary: This AI function makes a move on behalf of the computer in an ongoing tic-tac-toe game.
// Arguments:
//           game[3][3]: The state of the game.
//           mark: The AI's mark: 'X' or 'O'.
// Returns: Nothing.

// #define TWO_PLAYERS
void make_move(char game[][3], char mark)
{
#ifdef TWO_PLAYERS
    ask_for_move(game, mark);
#else
    int best_i{-1}, best_j{-1}, best_score{-100};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (game[i][j] == ' ')
            {
                game[i][j] = mark;
                int score = minimax(game, mark, false);
                game[i][j] = ' ';
                if (score > best_score)
                {
                    best_score = score;
                    best_i = i;
                    best_j = j;
                }
            }
    game[best_i][best_j] = mark;
#endif
    return;
}

// print_game()
// Summary: This function prints an ongoing tic-tac-toe game.
// Arguments:
//           game[3][3]: The state of the game.
// Returns: Nothing.
void print_game(char game[][3])
{
    std::cout << std::endl
              << std::endl;
    std::cout << "    1   2   3\n\n";
    std::cout << "1   " << game[0][0] << " | " << game[0][1] << " | " << game[0][2] << "\n";
    std::cout << "   " << "---+---+---\n";
    std::cout << "2   " << game[1][0] << " | " << game[1][1] << " | " << game[1][2] << "\n";
    std::cout << "   " << "---+---+---\n";
    std::cout << "3   " << game[2][0] << " | " << game[2][1] << " | " << game[2][2] << "\n";

    std::cout << std::endl
              << std::endl;
    return;
}

// Main function
int main()
{
    char game[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char user_mark = 'X', ai_mark = 'O', turn = 'X';
    std::string str;

    std::cout << "Pick your mark (X goes first): " << std::flush;
    std::cin >> str;
    if (str[0] == 'O' || str[0] == 'o')
    {
        user_mark = 'O';
        ai_mark = 'X';
    }
    std::cout << "      User: " << user_mark << "     AI: " << ai_mark << "\n";

    print_game(game);

    while (game_state(game) == 'a')
    {
        std::cout << turn << "'s turn...\n";
        if (turn == user_mark)
            ask_for_move(game, user_mark);
        else
            make_move(game, ai_mark);
        print_game(game);
        turn = turn == 'X' ? 'O' : 'X';
    }
    if (game_state(game) == 't')
        std::cout << "It's a tie.\n\n";
    else
        std::cout << game_state(game) << " is the winner.\n\n";
    std::cout << std::flush;
    return 0;
}

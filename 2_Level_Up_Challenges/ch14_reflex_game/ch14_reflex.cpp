// C++ Code Challenges, LinkedIn Learning

// Challenge #14: The Reflex Game
// Write an application that waits a random delay between 4 and 10 seconds, and then asks the user to type in a random word.
// This random word comes from a list of 10 3-letter words.
// If the user enters the correct word in less than 2 seconds, print a success message on the screen.
// Otherwise, print a failure message.
// Ignore the case ("CAT" = "cat" = "CaT").

#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <future>
#include <thread>
#include <cctype>
#include <algorithm>

std::string words[10] = {"CAT", "RAT", "BAT", "CAP", "BAG", "RAG", "RAP", "BET", "BEG", "LET"};

// The Reflex Game, main()
// Summary: This application measures the time it takes a user to type in a random 3-letter word.

class Gated_cin
{
public:
    std::string input;

    auto operator()()
    {
        std::future<std::string> result = std::async(std::launch::async, &Gated_cin::ReadInput, this);

        if (result.wait_for(std::chrono::seconds(2)) == std::future_status::ready)
        {
            input = result.get();
        }
        else
        {
            input = "";
            std::cout << "\nTimed out... Press enter twice..."; //i couldnt figure out why there was another empty line
        }
        return input;
    }

private:
    std::string ReadInput()
    {
        std::string temp;
        std::getline(std::cin, temp);
        return temp;
    }
};

int main()
{
    std::cout << "\n";
    std::cout << "                   The Reflex Game\n";
    std::cout << "                   === ====== ====\n";
    std::cout << "After a random delay, you'll be asked to type in a 3-letter word.\n";
    std::cout << "When that happens, type in the word as fast as you can, and hit Enter.\n";
    std::cout << "Don't worry about the character case (\"CAT\" = \"cat\" = \"CaT\").\n\n";
    std::cout << "            Press Enter when you're ready to start." << std::flush;

    std::string try_again;
    std::getline(std::cin, try_again);

    std::random_device rd;
    std::minstd_rand gen(rd());
    std::uniform_int_distribution distrib(0, 9);
    int rand_i{};
    std::string word{};

    auto to_upper = [](const std::string &guess)
    {
        std::string uppercase_guess{};

        for (auto c : guess)
        {
            uppercase_guess += std::toupper(c);
        }

        return uppercase_guess;
    };

    const auto threshold = std::chrono::duration<double, std::milli>(2000);
    bool slow{false};
    Gated_cin get;

    rand_i = distrib(gen);
    std::this_thread::sleep_for(std::chrono::seconds(rand_i%5 + 1));
    do
    {
        slow = false;
        rand_i = distrib(gen);
        word = words[rand_i];

        std::cout << "Your word is: " << word << "\t";
        auto t1 = std::chrono::steady_clock::now();
        
        while (!slow)
        {
            auto answer_timer = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> answer_time = answer_timer - t1;
            if (answer_time >= threshold)
                slow = true;
            
            auto answer = get();
            if (!answer.empty())
            {
                auto t2 = std::chrono::steady_clock::now();
                std::chrono::duration<double, std::milli> time = t2 - t1;
                std::cout << "Time taken: " << time;

                if (to_upper(answer) == word)
                {
                    std::cout << "\nGood job!\n";
                    break;
                }
                else
                {
                    std::cout << "\nIncorrect!\n";
                    break;
                }
            }
        }
        if (slow)
            std::cout << "\nFAILURE! Too slow!\n";

        std::cout << "Try again? (Y/N): " << std::flush;
        std::getline(std::cin, try_again);
    } while (try_again[0] == 'Y' || try_again[0] == 'y');
    return 0;
}

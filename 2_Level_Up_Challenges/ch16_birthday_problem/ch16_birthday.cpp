// C++ Code Challenges, LinkedIn Learning

// Challenge #16: The Birthday Problem
// The birthday problem consists in finding the probability of having at least two people with the same birthday in a group of n people.
// Create an application that simulates the Birthday Problem 1 million times, with the number of people specified by the user.
// Use this application to prove (empirically) that the probability of having at least 2 people with the same birthday is approximately 0.5 for a group of 23 people.
// https://en.wikipedia.org/wiki/Birthday_problem

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

// The Birthday Problem, main()
// Summary: This application simulates the birthday problem a large number of times to reveal the probability of a birthday match in a groupd of a given number of people.
int main()
{
    const int total = 1000000;
    int n{}, matches{};

    std::cout << "Enter the number of people in the group: " << std::flush;
    std::cin >> n;

    if (n > 366)
        matches = total;
    else
    {
        // Write your code here
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(1, 365);

        std::vector<int> birthdays{};
        int trials{total}; // num of trials equals total
        do
        {
            birthdays.clear();
            for (int i = 0; i < n; i++)
            {
                birthdays.push_back(distrib(gen));
            }
            std::sort(birthdays.begin(), birthdays.end());
            for(int i = 1; i < birthdays.size(); i++){
                if (birthdays[i-1] == birthdays[i]) {
                    matches++;
                    break;
                }
            }
            trials--;
        } while (trials > 0);
    }

    std::cout << "The probability of a birthday match is " << (double)matches / total << "\n\n"
              << std::flush;

    return 0;
}

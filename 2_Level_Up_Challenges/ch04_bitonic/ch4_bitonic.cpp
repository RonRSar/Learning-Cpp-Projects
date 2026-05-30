// C++ Code Challenges, LinkedIn Learning

// Challenge #4: Checking for Bitonic Sequences
// Write a function to check if a vector of integers is bitonic or not.
// Bitonic sequences have an ascending segment followed by a descending segment (sort of).
// Circular shifts of these sequences are also bitonic.

// Formally, a bitonic sequence is a sequence with x[0] <= ... <= x[k] >= ... >= x[n-1]
//           for some k between 0 and n-1, or a circular shift of such a sequence.

// Special bitonic cases: Monotonic sequences and sequences where all elements have the same value.

#include <iostream>
#include <vector>

// is_bitonic()
// Summary: This function receives an STL vector of integers and returns true if it contains a bitonic sequence, false otherwise.
// Arguments:
//           v: A reference to the vector to analyze.
// Returns: A boolean value: True for bitonic sequences, false otherwise.

// This one was quite difficult! I worked out that it required the number of directional
// switches to be n <= 2, but I failed to initially see that you needed to count the switch 
// by comparing against some stored value each loop of the variable. 
bool is_bitonic(const std::vector<int> &v)
{
    size_t n = v.size();
    // if size < 3 then sequence is always bitonic.
    if (n <= 3)
        return true;

    bool direction{};
    for (size_t i = 0; i < n - 1; i++)
    {
        if (v[i] != v[i + 1])
        {
            direction = v[i] > v[i + 1];
            break;
        }
    }

    int curr{}, next{};
    size_t dir_switches{0};
    for (size_t i = 0; i < n && dir_switches <= 2; i++)
    {
        curr = v[i];

        // next of last element loops to first
        if (i != n - 1)
        {
            next = v[i + 1];
        }
        else
        {
            next = v[0];
        }

        if (curr == next)
            continue;
        if (curr > next != direction)
        {
            dir_switches += 1;
            direction = curr > next;
        }
    }

    return (dir_switches <= 2);
}

// Main function
int main()
{
    // Uncomment one of these lines and make sure you get the result at the right.

    std::vector<int> myvec0 = {1, 2, 5, 4, 3};  // Yes
    std::vector<int> myvec1 = {1, 1, 1, 1, 1};  // Yes
    std::vector<int> myvec2 = {3, 4, 5, 2, 2};  // Yes
    std::vector<int> myvec3 = {3, 4, 5, 2, 4};  // No
    std::vector<int> myvec4 = {1, 2, 3, 4, 5};  // Yes
    std::vector<int> myvec5 = {1, 2, 3, 1, 2};  // No
    std::vector<int> myvec6 = {5, 4, 6, 2, 6};  // No
    std::vector<int> myvec7 = {5, 4, 3, 2, 1};  // Yes
    std::vector<int> myvec8 = {5, 4, 3, 2, 6};  // Yes
    std::vector<int> myvec9 = {5, 4, 6, 5, 4};  // No
    std::vector<int> myvec10 = {5, 4, 6, 5, 5}; // Yes

    // Additional test cases — varying lengths
    std::vector<int> myvec11 = {7, 7};                                   // Yes (len 2)
    std::vector<int> myvec12 = {4, 2, 7};                                // Yes (len 3)
    std::vector<int> myvec13 = {2, 4, 6, 8, 10, 12};                     // Yes (len 6, monotonic)
    std::vector<int> myvec14 = {9, 7, 5, 3, 1};                          // Yes (len 5, decreasing)
    std::vector<int> myvec15 = {1, 3, 5, 7, 9, 7, 5, 3};                 // Yes (len 8)
    std::vector<int> myvec16 = {1, 3, 5, 7, 9, 11, 13, 15};              // Yes (len 8, increasing)
    std::vector<int> myvec17 = {1, 2, 1, 2, 1, 2};                       // No (len 6)
    std::vector<int> myvec18 = {10, 20, 30, 40, 50, 60, 55, 45, 35, 25}; // Yes (len 10)
    std::vector<int> myvec19 = {10, 20, 30, 20, 10, 30, 20, 10};         // No (len 8)
    std::vector<int> myvec20 = {2, 2, 2, 2, 3, 4, 3, 2, 2, 2};           // Yes (len 10)

    std::cout << (is_bitonic(myvec0) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec1) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec2) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec3) == true ? "(FAIL) Yes, it is bitonic.\n" : "(PASS) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec4) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec5) == true ? "(FAIL) Yes, it is bitonic.\n" : "(PASS) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec6) == true ? "(FAIL) Yes, it is bitonic.\n" : "(PASS) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec7) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec8) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec9) == true ? "(FAIL) Yes, it is bitonic.\n" : "(PASS) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec10) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec11) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec12) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec13) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec14) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec15) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec16) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec17) == true ? "(FAIL) Yes, it is bitonic.\n" : "(PASS) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec18) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec19) == true ? "(FAIL) Yes, it is bitonic.\n" : "(PASS) No, it is not bitonic.\n");
    std::cout << (is_bitonic(myvec20) == true ? "(PASS) Yes, it is bitonic.\n" : "(FAIL) No, it is not bitonic.\n");
    std::cout << std::endl
              << std::endl
              << std::flush;
    return 0;
}

// C++ Code Challenges, LinkedIn Learning

// Challenge #1: Checking for Palindromes
// Write a function to check if a string is a palindrome or not.
// Examples: civic, radar, level.

#include <iostream>
#include <algorithm>

// is_palindrome()
// Summary: This function receives a string and returns true if the string is a palindrome, false otherwise.
// Arguments:
//           str: The string to analyze.
// Returns: A boolean value. True for palindromes, false otherwise.

bool is_palindrome(const std::string &str)
// My initial goal here was to try and avoid having to use loops, 
// hence why the solution uses 2 half substrings. 
{
    size_t len_str = str.size();
    if (len_str == 1)
        return true;

    std::string half_1_str{};
    std::string half_2_str{};

    size_t half_len_str = (len_str / 2);

    half_1_str = str.substr(0, half_len_str);

    if (len_str % 2 == 0)
    {
        half_2_str = str.substr(half_len_str, len_str);
    }
    else
    {
        half_2_str = str.substr(half_len_str + 1, len_str);
    }

    half_2_str = std::string(half_2_str.rbegin(), half_2_str.rend());

    if (half_1_str == half_2_str)
        return true;

    return false;
}

bool optimal_is_palindrome(const std::string &str)
// This is more optimal in terms of space complexity
{
    for (size_t i = 0, j = str.length(); i < j; i++, j--)
    {
        if (str[i] != str[j - 1])
            return false;
    }
    return true;
}

void assertPalindrome(bool palindrome, bool expected)
{
    std::cout << ((palindrome == expected) ? " TEST PASSED" : " TEST FAILED");
}

void testPalindrome()
{
    auto p1 = is_palindrome("civic");
    auto p2 = is_palindrome("pullup");
    auto p3 = is_palindrome("aa");
    auto p4 = is_palindrome("i");
    auto p5 = is_palindrome("tot");
    auto p6 = is_palindrome("level");
    auto p7 = is_palindrome("radar");
    auto ps1 = is_palindrome("rats live on no evil star");
    auto ps2 = is_palindrome("step on no pets");

    assertPalindrome(p1, true);
    assertPalindrome(p2, true);
    assertPalindrome(p3, true);
    assertPalindrome(p4, true);
    assertPalindrome(p5, true);
    assertPalindrome(p6, true);
    assertPalindrome(p7, true);
    assertPalindrome(ps1, true);
    assertPalindrome(ps2, true);
}

void testNotPalindrome()
{
    auto x1 = is_palindrome("pious");
    auto x2 = is_palindrome("summon");
    auto x3 = is_palindrome("ok");
    auto xs1 = is_palindrome("abc dcba");
    auto xs2 = is_palindrome("Hello World!");

    assertPalindrome(x1, false);
    assertPalindrome(x2, false);
    assertPalindrome(x3, false);
    assertPalindrome(xs1, false);
    assertPalindrome(xs2, false);
}

void testoptimalPalindrome()
{
    auto p1 = optimal_is_palindrome("civic");
    auto p2 = optimal_is_palindrome("pullup");
    auto p3 = optimal_is_palindrome("aa");
    auto p4 = optimal_is_palindrome("i");
    auto p5 = optimal_is_palindrome("tot");
    auto p6 = optimal_is_palindrome("level");
    auto p7 = optimal_is_palindrome("radar");

    assertPalindrome(p1, true);
    assertPalindrome(p2, true);
    assertPalindrome(p3, true);
    assertPalindrome(p4, true);
    assertPalindrome(p5, true);
    assertPalindrome(p6, true);
    assertPalindrome(p7, true);
}

void testoptimalNotPalindrome()
{
    auto x1 = optimal_is_palindrome("pious");
    auto x2 = optimal_is_palindrome("summon");
    auto x3 = optimal_is_palindrome("ok");

    assertPalindrome(x1, false);
    assertPalindrome(x2, false);
    assertPalindrome(x3, false);
}

// Main function
int main()
{
    testPalindrome();
    std::cout << "\n";
    testNotPalindrome();

    std::cout << "\n";

    testoptimalPalindrome();
    std::cout << "\n";
    testoptimalNotPalindrome();

    // This was the original code from the course. 
    // std::string s;
    // std::cout << "Enter a string: " << std::flush;
    // std::getline(std::cin, s);
    // std::cout << "\n\"" << s << (is_palindrome(s) ? "\" is" : "\" is not") << " a palindrome.\n\n";
    return 0;
}

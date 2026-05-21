#pragma once
#ifndef NUMWORDS_H
#define NUMWORDS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <concepts>

namespace n2w
{
    const std::vector<std::string> ones_map{"zero",
                                            "one",
                                            "two",
                                            "three",
                                            "four",
                                            "five",
                                            "six",
                                            "seven",
                                            "eight",
                                            "nine",
                                            "ten",
                                            "eleven",
                                            "twelve",
                                            "thirteen",
                                            "fourteen",
                                            "fifteen",
                                            "sixteen",
                                            "seventeen",
                                            "eighteen",
                                            "nineteen"};

    const std::vector<std::string> tens_map{"", "",
                                            "twenty",
                                            "thirty",
                                            "forty",
                                            "fifty",
                                            "sixty",
                                            "seventy",
                                            "eighty",
                                            "ninety"};

    const std::vector<std::string> hundreds_map{"",
                                                "thousand",
                                                "million",
                                                "billion",
                                                "trillion",
                                                "quadrillion",
                                                "quintillion"};

    template <std::integral T = int> //default int argument but allow any int-like type
    class Numword
    {
    public:
        Numword(T i_num)
        {
            num = i_num;
            num_in_words = num2word(num);
        };

        T operator=(const T &i_num)
        {
            num = i_num;
            num_in_words = num2word(num);
            return num;
        };

        void getnum() const
        {
            std::cout << num << ": " << num_in_words << "\n";
        }

    private:
        T num;
        std::list<std::string> num_list;
        std::string num_in_words;

        std::string num2word(T num)
        {
            std::list<std::string> num2word;
            std::list<std::string> temp_num_list;

            if constexpr (std::signed_integral<T>)
            {
                if (num < 0)
                {
                    num2word.push_back("negative");
                    num *= -1;
                }
            }

            if (num >= 1000)
            {
                temp_num_list = convert_num_above_1000(num);
                num2word.insert(num2word.end(), temp_num_list.begin(), temp_num_list.end());
                num %= 1000;
                if (num != 0)
                {
                    temp_num_list = convert_num_below_1000(num);
                    num2word.insert(num2word.end(), temp_num_list.begin(), temp_num_list.end());
                }
            }
            else
            {
                temp_num_list = convert_num_below_1000(num);
                num2word.insert(num2word.end(), temp_num_list.begin(), temp_num_list.end());
            }

            return convert_list_to_string(num2word);
        }

        // Private
        std::string convert_list_to_string(const std::list<std::string> &num_list)
        {
            std::string num2words{};
            bool first_word{true};

            for (const auto &word : num_list)
            {
                if (!first_word)
                    num2words += " ";
                num2words += word;
                first_word = false;
            }
            return num2words;
        }

        std::list<std::string> convert_num_99between20(T num)
        {
            std::list<std::string> num_list{};
            int ntens = num / 10;

            num_list.push_back(tens_map[ntens]);
            if (num % 10 != 0)
            {
                num_list.push_back(ones_map[num % 10]);
            }
            return num_list;
        }

        std::list<std::string> convert_num_999between100(T num)
        {
            std::list<std::string> num_list{};
            int nhundreds = num / 100;

            num_list.push_back(ones_map[nhundreds]);
            num_list.push_back("hundred");

            if (num % 100 == 0)
                return num_list;
            if ((num % 100) > 19)
            {
                auto temp_num_list = convert_num_99between20(num % 100);
                num_list.insert(num_list.end(), temp_num_list.begin(), temp_num_list.end());
            }
            else
            {
                num_list.push_back(ones_map[num % 100]);
            }
            return num_list;
        }

        std::list<std::string> convert_num_below_1000(T num)
        {
            std::list<std::string> num_list{};
            if (num < 20)
                num_list.push_back(ones_map[num]);
            if (num < 100 && num >= 20)
            {
                auto temp_num_list = convert_num_99between20(num);
                num_list.insert(num_list.end(), temp_num_list.begin(), temp_num_list.end());
            }
            if (num < 1000 && num >= 100)
            {
                auto temp_num_list = convert_num_999between100(num);
                num_list.insert(num_list.end(), temp_num_list.begin(), temp_num_list.end());
            }
            return num_list;
        }

        std::list<std::string> convert_num_above_1000(T num)
        {
            size_t check_size{static_cast<size_t>(num)};
            T quotient{};
            T remainder{};
            size_t thousands_power{};
            std::list<std::string> thousands2words{};

            while (check_size >= 1000)
            {
                check_size /= 1000;
                thousands_power++;
            }
            while (thousands_power >= 1)
            {
                quotient = num / static_cast<T>(pow(1000, thousands_power));
                remainder = num % static_cast<T>(pow(1000, thousands_power));

                if (quotient != 0)
                {
                    auto temp_num_list = convert_num_below_1000(quotient);
                    thousands2words.insert(thousands2words.end(), temp_num_list.begin(), temp_num_list.end());
                    thousands2words.push_back(hundreds_map[thousands_power]);
                }

                thousands_power--;
                num = remainder;
            }
            return thousands2words;
        }
    };
}

#endif
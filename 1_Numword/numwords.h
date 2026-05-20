#pragma once
#ifndef NUMWORDS_H
#define NUMWORDS_H

#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <cmath>

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
                                                "quadrillion"};

    class Numword
    {
        std::string num2word(int num);
    public:

        Numword(int i_num)
        {
            num = i_num;
            num_in_words = num2word(num); 
        };

        int operator= (const int& i_num){
            num = i_num;
            num_in_words = num2word(num);
            return num;
        };

        const void getnum(){
            printf("%d: %s\n", num, num_in_words.c_str());
        }

    private:
        int num;
        std::list<std::string> num_list;
        std::string num_in_words;

        std::string convert_list_to_string(const std::list<std::string> &num_list);
        std::list<std::string> convert_num_99between20(int num);
        std::list<std::string> convert_num_999between100(int num);
        std::list<std::string> convert_num_below_1000(int num);
        std::list<std::string> convert_num_above_1000(int num);
    };
}

#endif
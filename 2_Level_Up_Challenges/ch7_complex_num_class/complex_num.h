#pragma once
#ifndef COMPLEX_NUM_H
#define COMPLEX_NUM_H

#include <iostream>

class complex_num
{

    // Write your code here

public:
    complex_num ();
    complex_num(double re);
    complex_num(double re, double im);
    complex_num operator=(const complex_num &z);
    complex_num operator+(complex_num);
    complex_num operator-(complex_num);
    complex_num operator*(complex_num);
    complex_num operator/(complex_num);
    void print(std::ostream &os);

private:
    double real, imag;
};

#endif /* COMPLEX_NUM_H */

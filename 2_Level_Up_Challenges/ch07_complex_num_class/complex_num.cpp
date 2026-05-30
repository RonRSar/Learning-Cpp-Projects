#include "complex_num.h"

complex_num::complex_num(){
    real = 0.0;
    imag = 0.0;
}

complex_num::complex_num(double re) {
    real = re;
    imag = 0.0;
}

complex_num::complex_num(double re, double im){
    real = re;
    imag = im;
}

complex_num complex_num::operator =(const complex_num &z){
   this->real = z.real;
   this->imag = z.imag;
    return *this;
};

complex_num complex_num::operator +(complex_num w){
    return complex_num(this->real + w.real, this->imag + w.imag);
}

complex_num complex_num::operator -(complex_num w){
    return complex_num(this-> real - w.real, this->imag - w.imag);
}

complex_num complex_num::operator *(complex_num w){
    complex_num z;
    z.real = (this->real * w.real) - (this->imag * w.imag);
    z.imag = (this->real * w.imag) + (this-> imag * w.real);
    return z;
}

complex_num complex_num::operator /(complex_num w){
    complex_num z;
    z.real = ((this->real * w.real) + (this->imag * w.imag))/(w.real * w.real + w.imag * w.imag);
    z.imag = (-(this->real * w.imag) + (this-> imag * w.real))/(w.real * w.real + w.imag * w.imag);
    return z;
}

void complex_num::print(std::ostream &os){
    if (this->imag > 0) os << this->real << " + " << this->imag << "i";
    else if(this->imag < 0) os << this->real << " - " << (this->imag)*-1.0 << "i";
    else os << this->real;
}
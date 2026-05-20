#include "numwords.h"

int main()
{
    // temp obj + .getnum()
    n2w::Numword(0).getnum();
    n2w::Numword(1).getnum();

    // var then .getnum()
    n2w::Numword n2(11);
    n2.getnum();

    // =
    n2w::Numword n3 = 30;
    n3.getnum();

    // var + .getnum()
    n2w::Numword n4(36);
    n4.getnum();

    // reuse = operator
    n2w::Numword n5(100);
    n5.getnum();
    n5 = 101;
    n5.getnum();
    n5 = 114;
    n5.getnum();
    n5 = -123;
    n5.getnum();

    // mix styles
    n2w::Numword(1000).getnum();

    n2w::Numword n10(1500);
    n10.getnum();

    n2w::Numword(1512).getnum();
    n2w::Numword(1540).getnum();
    n2w::Numword(10000).getnum();

    n2w::Numword n14(15403);
    n14.getnum();

    n2w::Numword(32500).getnum();

    n2w::Numword n16(999999);
    n16.getnum();

    n2w::Numword(1000000).getnum();
    n2w::Numword(4000242).getnum();
    n2w::Numword(6789012).getnum();

    // copy then reassign
    n2w::Numword n20 = 50000000;
    n20.getnum();
    n20 = 50020050;
    n20.getnum();
    n20 = 218417802;
    n20.getnum();

    n2w::Numword(1000000000).getnum();
    n2w::Numword(1000000030).getnum();
    n2w::Numword(1878486865).getnum();
    return 0;
}
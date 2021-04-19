#include <iostream>

#include "variant.h"





int main()
{
    auto v = meta::make_variant<int, int, char>(10, 23, '@');
    auto pv = v.get();
    unsigned int indx = 2;

    std::cout << pv;
    std::cout << "res(" << indx << ") = " << pv->get<int>(indx) << "\n"; 


    return 0;
}
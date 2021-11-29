#include <iostream>
// #include "typel_list.h"
// #include"type_list2.h"
// #include "type_list3.h"
#include "variant.h"

template<bool cond, class T1, class T2>
typename CondType<cond, T1, T2>::type foo(const typename CondType<cond ,T1, T2>::type& value) {
    return value;
}


int main() { 

    typedef Variant<int> Variant1;
    typedef Variant<int, char> Variant2;
    typedef Variant<int, char, float> Variant3;

    Variant2 v2(122);


    

    // MyStruct myStruct;

    // unsigned long offset = (unsigned long)(&((MyStruct *)0)->s);

    // std::cout << "offset : " << offset << "\n"; 
    // std::cout << (unsigned long)(&((MyStruct*)0)->s) << "\n";
    // std::cout << (unsigned long)(&(((MyStruct*)0)->s)) << "\n";
    // std::cout << (&((MyStruct*)0)->s) << "\n";

    // std::cout << "foo<10 != 12, int, char>(10) : " << foo<10 != 12, int, char>(10) << "\n";
    // std::cout << "foo<10 >= 100, char, float>(12.34F) : " << foo<10 >= 100, char, float>(12.34F) << "\n";
    // std::cout << "Error : " << foo<10 == 100, int, char>(100) << "\n";

    return 0;
}

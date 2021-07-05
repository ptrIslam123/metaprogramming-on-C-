#include <iostream>
#include <assert.h>
#include <memory>
#include <type_traits>
#include <tuple>


//#include "template_list/template_list.h"
#include "tuple/tuple.h"




int main()
{   
   
    return 0;
}

/*


template<std::size_t pos>
struct pos_t
{};


template<class T, std::size_t indx>
void print(const T& t, pos_t<indx> pos)
{
    std::cout << std::get<std::tuple_size<T>::value - indx>(t) << ", ";
    print(t, pos_t<indx - 1>());
}


template<class T>
void print(const T& t, pos_t<1> )
{
    std::cout << std::get<std::tuple_size<T>::value - 1>(t);
}


template<class T, std::size_t size>
void print_tuple(const T& t)
{
    std::cout << "{ ";
        print(t, pos_t<size>());
    std::cout << " }\n";
}

*/
#include <iostream>
#include <assert.h>
#include <memory>
#include <type_traits>
#include <tuple>


//#include "template_list/template_list.h"
//#include "tuple/tuple.h"
#include "any/any.h"


struct foo
{
    foo (int id):
        _id(id)
    {
        //std::cout << "foo()\n";
    }

    ~foo ()
    {
        //std::cout << "~foo()\n";
    }

    int id()
    {
        return _id;
    }

private:

    int _id;
};

int main()
{   

    meta::any a1(foo(10));
    meta::any a2(foo(20));
    meta::any a3('f');

    std::cout << a2.is_can_cast<foo>() << "\n";
    std::cout << a3.is_can_cast<int>() << "\n";
    std::cout << a3.is_can_cast<char>() << "\n";

    auto ca1 = a1.cast<foo>();

    std::cout << "ca1.id = " << ca1.id() << "\n";


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
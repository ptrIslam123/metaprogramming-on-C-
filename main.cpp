#include <iostream>
#include <assert.h>

#include "shared.h"





struct foo
{
    foo():
        x_(0), y_(0)
    {}

    foo(int x, int y):
        x_(x), y_(y)
    {}
    
    ~foo() = default;

   void print()
    {
        std::cout << x_ << "\n";
        std::cout << y_ << "\n";
    }

    int x_, y_;
};



int main()
{
    using namespace meta;

   
    shared_ptr<foo> f1(10, 20);
    shared_ptr<foo> f2(shared_ptr<foo>(0, 0));

    f1.get()->print();
    f2.get()->print();

    shared_ptr<foo> f3 = std::move(f2);

    f3.get()->print();
    

    return 0;
}
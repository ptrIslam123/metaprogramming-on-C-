#include <iostream>
#include <assert.h>
#include <memory>


#include "template_list/template_list.h"
//#include "tuple/tuple.h"





int main()
{   
    
    meta::list_helper<int, char> l1(10, 'g');

    std::cout << "l1.value : " << l1.get_value() << "\n";
    std::cout << "l1.pos : " << l1.get_pos() << "\n";

    std::cout << "l1.tail.value : " << l1.get_tail().get_value() << "\n";
    std::cout << "l1.tail.pos : " << l1.get_tail().get_pos() << "\n";


    return 0;
}


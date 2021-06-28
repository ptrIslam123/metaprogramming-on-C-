#include <iostream>
#include <assert.h>
#include <memory>


#include "template_list/template_list.h"
//#include "tuple/tuple.h"






int main()
{   

    meta::list<int> l1(10);
    meta::list<int, char> l2(23, 'g');
   
    std::cout << "l1.value : " << l1.get_value() << "\n";
    std::cout << "l2.tail.value : " <<l2.get_tail().get_value() << "\n";

    std::cout << "l2.value.pos : " << l2.get_element().first << "\n"; 
    std::cout << "l2.tail.value.pos : " << l2.get_tail().get_element().first << "\n";


    std::cout << "Successful\n";

   
    return 0;
}


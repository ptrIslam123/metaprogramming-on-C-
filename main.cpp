#include <iostream>

#include "template_list.h"





int main()
{
    auto l = meta::make_list<int, float, char>(10, 12.54, '$');
    
    auto v1 = l->get_value();
    auto v2 = l->get_ptr_twin()->get_value();
    auto v3 = l->get_ptr_twin()->get_ptr_twin()->get_value();
    
    std::cout   << "\nv1 = " << v1
                << "\nv2 = " << v2
                << "\nv3 = " << v3 << "\n"; 
   
    return 0;
}
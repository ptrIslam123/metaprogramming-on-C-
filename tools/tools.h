#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <iostream>

namespace meta
{

    struct nil 
    {
        nil() = default;
        ~nil() = default;

        friend std::ostream& operator << (std::ostream& os, nil& n)
        {
            os << "_nil_" << std::endl;
            return os;
        }
    };
}

#endif // !_TOOLS_H_

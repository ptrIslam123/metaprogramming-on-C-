#ifndef _TUPLE_H_
#define _TUPLE_H_


#include <iostream>

#include "tools.h"

namespace meta
{
    
    template<class ... Args>
    struct tuple;


    template<class T, class ... Args>
    struct tuple
    {};

    template<>
    struct tuple<>
    {};
    

} // namespace meta::end;

#endif // !_TUPLE_H_


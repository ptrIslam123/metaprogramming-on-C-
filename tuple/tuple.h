#ifndef _TUPLE_H_
#define _TUPLE_H_


#include <iostream>

#include "tools.h"

namespace meta
{
    
    template<class ... Args>
    struct tuple;


    template<>
    struct tuple<>
    {};

    template<class T>
    struct data_wraper
    {
        typedef T data;
    };



    template<class T, class ... Args>
    struct tuple<T, Args ...> : public tuple<Args ...> 
    {
        using size_type                 = std::size_t;
        using pos_type                  = size_type;
        using value_type                = T;
        using element_type              = std::pair<pos_type, value_type>;
        using base_class_type           = tuple<Args ...>;


        const size_type size = sizeof ... (Args) + 1;


        tuple(const value_type& value, const Args& ... args):
            tuple<Args ...>(args ...),
            _element(std::pair<pos_type, value_type>(0 , value))
        {}


        base_class_type& get_base()
        {
            return _base;
        }

        value_type& get_value()
        {
            return _element.second;
        }

        const pos_type& get_pos() const
        {
            return _element.first;
        }

        const size_type& get_size() const 
        {
            return size;
        }


    private:
        element_type        _element;
        base_class_type& _base = static_cast<base_class_type&>(*this);
    };

    
    

  
} // namespace meta::end;

#endif // !_TUPLE_H_


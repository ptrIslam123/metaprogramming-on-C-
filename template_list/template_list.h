#ifndef _TEMPLATE_LIST_H_
#define _TEMPLATE_LIST_H_

#include <iostream>
#include <memory>

#include "tools.h"

namespace meta
{

   template<class ... Args>
   struct list_helper;


   template<>
   struct list_helper<>
   {};

    template<std::size_t pos, class T>
    struct list_element;


   template<class T, class ... Args>
   struct list_helper<T, Args ...>
   {
        using value_type = T;
        using tail_type = list_helper<Args ...>;
        using element_type = list_element<sizeof ... (Args), value_type>;


        list_helper(const value_type& value, const Args& ... args);

        const value_type& get_value() const;
        const tail_type& get_tail() const;
        constexpr std::size_t get_pos() const; 

    private:
        tail_type   _tail;
        element_type _element;
   };


    template<class T, class ... Args>
    list_helper<T, Args ...>::list_helper(const value_type& value, const Args& ... args):
        _tail(tail_type(args ...)),
        _element(element_type(value))
    {}


    template<class T, class ... Args>
    const typename list_helper<T, Args ...>::value_type& 
    list_helper<T, Args ...>::get_value() const
    {
        return _element.get_value();
    }


    template<class T, class ... Args>
    const typename list_helper<T, Args ...>::tail_type& 
    list_helper<T, Args ...>::get_tail() const
    {
        return _tail;
    }



    template<class T, class ... Args>
    constexpr std::size_t list_helper<T, Args ...>::get_pos() const
    {
        return _element.get_pos();
    }





    template<std::size_t pos, class T>
    struct list_element
    {
        typedef T value_type;

        list_element(const value_type& value);

        const value_type& get_value() const;
        constexpr std::size_t get_pos() const;

    private:
        value_type _value;
    };


    template<std::size_t pos, class T>
    list_element<pos, T>::list_element(const value_type& value):
        _value(value)
    {}


    template<std::size_t pos, class T>
    const typename list_element<pos, T>::value_type& 
    list_element<pos, T>::get_value() const
    {
        return _value;
    }

   
    template<std::size_t pos, class T>
    constexpr std::size_t list_element<pos, T>::get_pos() const
    {
        return pos;
    }



} // namespace meta


#endif // !_TEMPLATE_LIST_H_

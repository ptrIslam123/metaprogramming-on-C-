#ifndef _TUPLE_H_
#define _TUPLE_H_


#include <iostream>

#include "tools.h"

namespace meta
{

    template<std::size_t _index>
    struct element_index
    {
        static constexpr std::size_t index = _index;
    };

    template<class ... Args>
    struct tuple_helper;

    template<>
    struct tuple_helper<>
    {};



    template<class T>
    void print_tuple(const T& tuple);


    template<class T, class ... Args>
    struct tuple_helper<T, Args ...>
    {
        typedef T                                   value_type;
        typedef tuple_helper<Args ...>              tail_type;
        typedef element_index<sizeof ... (Args)>    pos_type;

        tuple_helper(const value_type& value, const Args& ... args);

        const value_type&                           get_value() const;
        const tail_type&                            get_tail() const;
        constexpr std::size_t                       get_pos() const;
        

    private:
        value_type                                  _value;
        tail_type                                   _tail;
        pos_type                                    _pos;
    };


    template<class T, class ... Args>
    tuple_helper<T, Args ...>::tuple_helper(const value_type& value, const Args& ... args):
        _value(value),
        _tail(tail_type(args ...))
    {}


    template<class T, class ... Args>
    const typename tuple_helper<T, Args ...>::value_type&
    tuple_helper<T, Args ...>::get_value() const
    {
        return _value;
    } 

    template<class T, class ... Args>
    const typename tuple_helper<T, Args ...>::tail_type&
    tuple_helper<T, Args ...>::get_tail() const
    {
        return _tail;
    } 


    template<class T, class ... Args>
    constexpr std::size_t
    tuple_helper<T, Args ...>::get_pos() const
    {
        return _pos.index;
    } 


    
    template<class T>
    struct print_tuple_element;

    template<>
    struct print_tuple_element<element_index<0>>;

   
    template<class T>
    void print_tuple(const T& tuple)
    {
        print_tuple_element<T> p;
        
        std::cout << "{";
            p(tuple);   
        std::cout << "}\n";
    }


    template<class T>
    struct print_tuple_element
    {
        void operator () (const T& tuple)
        {
            //print_tuple_element<decltype(tuple.get_tail())> p;

            std::cout << tuple.get_value();
            //p(tuple.get_tail());
        }
    };

    template<>
    struct print_tuple_element<element_index<0>>
    {};

    


} // namespace meta::end;

#endif // !_TUPLE_H_


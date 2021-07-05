#ifndef _TUPLE_H_
#define _TUPLE_H_


#include <iostream>

#include "tools.h"

namespace meta
{

    template<class ... Args>
    struct tuple;


    template<class T>
    struct tuple_size;


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



    template<class ... Args>
    struct tuple
    {
        typedef tuple_helper<Args ...>              helper_type;

        tuple(const Args& ... args);

        const helper_type&                          get_helper() const; 
        

    private:
        helper_type                                  _helper;
    };



    template<class ... Args>
    tuple<Args ...>::tuple(const Args& ... args):
        _helper(helper_type(args ...))
    {}


    template<class ... Args>
    const typename tuple<Args ...>::helper_type& 
    tuple<Args ...>::get_helper() const
    {
        return _helper;
    }




    template<class T>
    struct tuple_size
    {
        typedef typename T::helper_type             tuple_type;
        typedef typename tuple_type::size_type      size_value_type;
    };





    template<class T, class ... Args>
    struct tuple_helper<T, Args ...>
    {
        typedef T                                       value_type;
        typedef tuple_helper<Args ...>                  tail_type;
        typedef element_index<sizeof ... (Args) + 1>    size_type;

        tuple_helper(const value_type& value, const Args& ... args);

        const value_type&                           get_value() const;
        const tail_type&                            get_tail() const;
        constexpr std::size_t                       get_size() const;
        

    private:
        value_type                                  _value;
        tail_type                                   _tail;
        size_type                                   _pos;
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
    tuple_helper<T, Args ...>::get_size() const
    {
        return _pos.index;
    } 



} // namespace meta::end;

#endif // !_TUPLE_H_


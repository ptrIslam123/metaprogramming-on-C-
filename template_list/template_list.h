#ifndef _TEMPLATE_LIST_H_
#define _TEMPLATE_LIST_H_

#include <iostream>
#include <memory>

#include "tools.h"

namespace meta
{

    template<class ... Args>
    struct list;


    template<>
    struct list<>
    {
        using size_type = std::size_t;
        static constexpr size_type size = 0;
    };


    template<class ... Args>
    std::unique_ptr<list<Args ...>> make_list(const Args& ... args);



    template<class T, class ... Args>
    struct list<T, Args...>
    {
        using size_type                 = std::size_t; 
        using pos_type                  = size_type;
        using value_type                = T;
        using element_type              = std::pair<pos_type, value_type>;
        using tail_type                 = list<Args ...>;

        static constexpr size_type size = sizeof ... (Args) + 1;

        list(const value_type& value, const Args& ... args);
        ~list() = default;


        const element_type&             get_element() const;
        value_type&                     get_value();
        tail_type&                      get_tail();

    private:
        pos_type                        eval_pos();

    private:
        
        element_type _element;
        tail_type _tail;
    };


    template<class T, class ... Args>
    using value_type = typename list<T, Args ...>::value_type;

    template<class T, class ... Args>
    using tail_type = typename list<T, Args ...>::tail_type;

    template<class T, class ... Args>
    using element_type = typename list<T, Args ...>::element_type;

    template<class T, class ... Args>
    using pos_type = typename list<T, Args ...>::pos_type;



   template<class T, class ... Args>
   list<T, Args ...>::list(const value_type& value, const Args& ... args):
        _element(std::pair<pos_type, value_type>(eval_pos(), value)),
        _tail(tail_type(args ...))
   {}


   template<class T, class ... Args>
   typename list<T, Args ...>::value_type& list<T, Args ...>::get_value()
   {
       return _element.second;
   }
    
    
   template<class T, class ... Args>
   typename list<T, Args ...>::tail_type& list<T, Args ...>::get_tail()
   {
       return _tail;
   }


    template<class T, class ... Args>
    const typename list<T, Args ...>::element_type& list<T, Args ...>::get_element() const
    {
        return _element;
    }
   




    template<class ... Args>
    std::unique_ptr<list<Args ...>> make_list(const Args& ... args)
    {
        return std::make_unique<list<Args ...>>(
            list<Args ...>(args ...)
        );
    }


    template<class T, class ... Args>
    typename list<T, Args ...>::pos_type list<T, Args ...>::eval_pos()
    {
        return sizeof ... (Args) + 1;
    }





    template<class T>
    void print_list(const T& _list)
    {

    }

} // namespace meta


#endif // !_TEMPLATE_LIST_H_

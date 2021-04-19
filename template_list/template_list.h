#ifndef _TEMPLATE_LIST_H_
#define _TEMPLATE_LIST_H_

#include <iostream>
#include <memory>
#define _DEBUG_META_LIST_

namespace meta
{

    struct nil;

    template<class T, class ... Args>
    class list;

    template<class ... Args>
    std::unique_ptr<list<Args ...>> make_list(const Args& ... args);



    template<class T = nil, class ... Args>
    class list
    {
    public:
        using value_type    = T;
        using twin_type     = list<Args ...>;

        value_type*         value_;
        twin_type*          twin_;

        list(const value_type& value, const Args& ... args);
        ~list();

        
       friend std::ostream& operator << (std::ostream& os, list<T, Args ...>* pl)
       {
           pl->print_list(pl->twin_);
           return os;
       }
       

       value_type&          get_value();
       twin_type&           get_twin();

       value_type*          get_ptr_value();
       twin_type*           get_ptr_twin();
    
        void                print_list(twin_type* p_twin);
        void                clear_list(twin_type* p_twin);
    };



    template<class T, class ... Args>
    using _value_type = typename list<T, Args...>::value_type;


    template<class T, class ... Args>
    using _twin_type = typename list<T, Args...>::twin_type;





    template<class T, class ... Args>
    list<T, Args ...>::list(const value_type& value, const Args& ... args):
        value_(nullptr),
        twin_(nullptr)
    {
        value_ = new value_type(value);

        if constexpr (sizeof ... (args) > 0)
        {
            twin_ = new twin_type(args ...);
        }
    }


    template<class T, class ... Args>
    typename list<T, Args ...>::value_type& 
    list<T, Args ...>::get_value()
    {
        return *value_;
    }



    template<class T, class ... Args>
    typename list<T, Args ...>::twin_type& 
    list<T, Args ...>::get_twin()
    {
        return *twin_;
    }


    template<class T, class ... Args>
    typename list<T, Args ...>::value_type* 
    list<T, Args ...>::get_ptr_value()
    {
        return value_;
    }



    template<class T, class ... Args>
    typename list<T, Args ...>::twin_type* 
    list<T, Args ...>::get_ptr_twin()
    {
        return twin_;
    }

    template<class T, class ... Args>
    list<T, Args ...>::~list()
    {
        this->clear_list(this->twin_);
    }




    template<class T, class ... Args>
    void list<T, Args ...>::print_list(list<T, Args ...>::twin_type* p_twin)
    {
        std::cout << *value_ << std::endl;

        if (p_twin != nullptr)
        {
            p_twin->print_list(p_twin->twin_);
        }
    }


    template<class T, class ... Args>
    void list<T, Args ...>::clear_list(list<T, Args ...>::twin_type* p_twin)
    {
        if (p_twin != nullptr)
        {
            p_twin->clear_list(p_twin->twin_);
        }

        #ifndef _DEBUG_META_LIST_
            std::cout << "delete : " << *(value_) << std::endl;
        #endif // !_DEBUG_META_LIST_
        
        delete value_;
        value_ = nullptr;
    }


    struct nil 
    {
        friend std::ostream& operator << (std::ostream& os, nil& n)
        {
            os << "_nil_" << std::endl;
            return os;
        }
    };


    template<class ... Args>
    std::unique_ptr<list<Args ...>> make_list(const Args& ... args)
    {
        return std::make_unique<list<Args ...>>(args ...);
    }
}

#endif // !_TEMPLATE_LIST_H_

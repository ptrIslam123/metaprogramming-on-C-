#ifndef _VARIANT_H_
#define _VARIANT_H_

#define _DEBUG_META_VARIANT_

#include <iostream>
#include <memory>

#include "tools.h"

namespace meta
{

    template<class T, class ... Args>
    class variant;

    template<class T, class ... Args>
    std::unique_ptr<variant<T, Args ...>> make_variant(T value, Args ... args);


    template<class T = nil, class ... Args>
    class variant
    {
    public:
        using value_type    = T;
        using index_type    = unsigned int;
        using pair_type     = std::pair<index_type, value_type>;
        using twin_type     = variant<Args ...>;

        pair_type*          value_;
        twin_type*          twin_;
        

        variant(value_type value, Args ... args);
        ~variant();

        friend std::ostream& operator << (std::ostream& os, variant<T, Args ...>* pv)
        {
            pv->print_variant(pv->twin_);
            return os;
        }

        template<class F>
        F&              get(const index_type indx);

        void*           get_element(const index_type indx, twin_type* p_twin);
        void            print_variant(twin_type* p_twin);
        void            free_memory(twin_type* p_twin);
    };
    

    template<class T, class ... Args>
    using value_type = typename variant<T, Args ...>::value_type;

    template<class T, class ... Args>
    using pair_type = typename variant<T, Args ...>::pair_type;

    template<class T, class ... Args>
    using twin_type = typename variant<T, Args ...>::twin_type;


    template<class T, class ... Args>
    variant<T, Args ...>::variant(value_type value, Args ... args):
        value_(nullptr),
        twin_(nullptr)
    {
        value_ = new pair_type(
                sizeof ... (args), value 
        );

        if constexpr (sizeof ... (args) > 0)
        {
            twin_ = new twin_type(
                args ...
            );
        }
    }

    template<class T, class ... Args>
    variant<T, Args ...>::~variant()
    {
        free_memory(twin_);
    }


    template<class T, class ... Args>
    template<class F>
    F&
    variant<T, Args ...>::get(const index_type indx)
    {
        auto res = get_element(indx, twin_);
        
        if (res != nullptr)
        {
            return *(static_cast<F*>(res));
        }
        
        throw std::runtime_error("ERROR VARINAT: out of range");
    }


    template<class T, class ... Args>
    void* 
    variant<T, Args ...>::get_element(
        const index_type indx, 
        variant<T, Args ...>::twin_type* p_twin
    )
    {

        if (value_->first == indx)
                return &(value_->second);

        if (p_twin != nullptr)
        {
            return p_twin->get_element(indx, p_twin->twin_);
        }
    
        return nullptr;
    }

    template<class T, class ... Args>
    void variant<T, Args ...>::print_variant
    (variant<T, Args ...>::twin_type* p_twin)
    {
        std::cout   << "{ " << value_->first << " : "
                    << value_->second << " }" << std::endl;

        if (p_twin != nullptr)
        {
            p_twin->print_variant(p_twin->twin_);
        }
    }

    template<class T, class ... Args>
    void variant<T, Args ...>::free_memory(variant<T, Args ...>::twin_type* p_twin)
    {
        if (p_twin != nullptr)
        {
            p_twin->free_memory(p_twin->twin_);
        }

        #ifndef _DEBUG_META_VARIANT_
            std::cout << "delete->second : " << (value_->second) << std::endl;
        #endif // !_DEBUG_META_VARIANT_

        delete value_;
        value_ = nullptr;
    }



    template<class T, class ... Args>
    std::unique_ptr<variant<T, Args ...>> 
    make_variant(T value, Args ... args)
    {
        return std::make_unique<variant<T, Args ...>>(
            value, args ...
        );
    }

} // namespace meta


#endif // !_VARIANT_H_

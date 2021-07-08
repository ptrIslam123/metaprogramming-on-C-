#ifndef _ANY_H_
#define _ANY_H_

//#define _DEBUG_META_ANY_CLASS_

#include <iostream>
#include <memory>
#include <typeinfo>

namespace meta
{
    
    class any
    {
        struct base_data_holder;

        template<class T>
        struct data_holder;

        typedef std::unique_ptr<base_data_holder> any_data_type;


    public:
        template<class T>
        any(const T& value);
        ~any();

        const std::type_info& get_type() const;

        template<class U>
        bool is_can_cast() const;

        template<class U>
        U cast() const;

    private:
        struct base_data_holder
        {
            virtual const std::type_info& get_data_type() const = 0;
            virtual ~base_data_holder() = default;
        };

        template<class T>
        struct data_holder : public base_data_holder
        {
            typedef T data_type;

            data_holder(const data_type& data);
            ~data_holder();

            data_type& get_data();
            const std::type_info& get_data_type() const override;

        private:
            data_type _data;
        };
        
        
    private:
        any_data_type _any_data;
    };


    template<class T>
    any::any(const T& value):
        _any_data(std::make_unique<data_holder<T>>(value))
    {
        #ifdef _DEBUG_META_ANY_CLASS_
            std::cout << "any(const T& )" << std::endl;
        #endif // !_DEBUG_META_ANY_CLASS_
    }


    any::~any()
    {
       #ifdef _DEBUG_META_ANY_CLASS_
            std::cout << "~any()" << std::endl;
        #endif // !_DEBUG_META_ANY_CLASS_
    }

    

    template<class T>
    any::data_holder<T>::data_holder(const data_type& data): 
        _data(data) 
    {
        #ifdef _DEBUG_META_ANY_CLASS_
            std::cout << "data_holder(const data_type& )" << std::endl;
        #endif // !_DEBUG_META_ANY_CLASS_
    }

    template<class T>
    any::data_holder<T>::~data_holder()
    {
        #ifdef _DEBUG_META_ANY_CLASS_
            std::cout << "~data_holder()" << std::endl;
        #endif // !_DEBUG_META_ANY_CLASS_
    }



    const std::type_info& any::get_type() const
    {
        return _any_data->get_data_type();
    }



    template<class U>
    bool any::is_can_cast() const
    {
        if (this->get_type() != typeid(U))
            return false;

        return true;
    }


    template<class U>
    U any::cast() const
    {
        if (!is_can_cast<U>())
        {
            throw std::runtime_error("error!");
        }

        auto p_data_holder = static_cast<data_holder<U>*>(_any_data.get());
        return p_data_holder->get_data();
    }


    template<class T>
    typename any::data_holder<T>::data_type& 
    any::data_holder<T>::get_data()
    {
        return _data;
    }


    template<class T>
    const std::type_info& any::data_holder<T>::get_data_type() const
    {
        return typeid(data_type);
    }


    

} // namespace meta


#endif // !_ANY_H_

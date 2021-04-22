#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#define _SHARED_PTR_DEBUG_
#define _FIRST_SHRED_PTR_ 1

#include <stdlib.h>
#include <stdio.h>

namespace meta
{
    
    template<class T>
    class shared_ptr;



    template<class T>
    class shared_ptr
    {
    public:
        using value_type    = T;
        using size_type     = size_t;

        template<class ... Args>
        shared_ptr(Args&& ... args);

        shared_ptr(shared_ptr<T>& other);
        shared_ptr(shared_ptr<T>&& other);

        void operator= (shared_ptr<T>& other);
        void operator= (shared_ptr<T>&& other);

        ~shared_ptr();

        value_type&     operator* ();
        value_type*     get();

    private:
        bool            is_last_ptr() const;

        size_type&      get_size();
        void            set_size(const size_type size);

        void            incr_size();
        void            decr_size();


    private:
        struct mem_struct
        {
            size_type       size_;
            value_type*     p_value_;
        };  

        mem_struct*         p_mem_;
    };


    

    template<class T>
    using value_type = typename shared_ptr<T>::value_type;


    template<class T>
    template<class ... Args>
    shared_ptr<T>::shared_ptr(Args&& ... args):
        p_mem_(nullptr)  
    {
       
        const size_type total_size  = sizeof(mem_struct) + sizeof(value_type);

        p_mem_                      = (mem_struct*)malloc(total_size);

        p_mem_->p_value_            = (value_type*)(
            (char*)p_mem_ + sizeof(mem_struct)
        );

        ::new (p_mem_->p_value_) value_type(args ...);
        set_size(_FIRST_SHRED_PTR_);



        #ifdef _SHARED_PTR_DEBUG_

        printf("\t\tallocate %d bytes => %p\n", 
            sizeof(value_type) + sizeof(mem_struct), p_mem_);

        #endif // _SHARED_PTR_DEBUG_
    }


    template<class T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>& other)
    {
        p_mem_ = other.p_mem_;
        incr_size();
    }

    
    template<class T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&& other)
    {
        p_mem_ = other.p_mem_;
    }

    template<class T>
    shared_ptr<T>::~shared_ptr()
    {
        decr_size();

        if (is_last_ptr())
        {
            p_mem_->~mem_struct();
            free(p_mem_);

        
            #ifdef _SHARED_PTR_DEBUG_

            printf("\t\tdeallocate %d bytes => %p\n", 
                    sizeof(value_type) + sizeof(mem_struct), p_mem_);

            #endif // _SHARED_PTR_DEBUG_
        }  
    }



    template<class T>
    void shared_ptr<T>::operator= (shared_ptr<T>& other)
    {
        p_mem_ = other.p_mem_;
        incr_size();
    }

    template<class T>
    void shared_ptr<T>::operator= (shared_ptr<T>&& other)
    {
        p_mem_ = other.p_mem_;
    }

    template<class T>
    typename shared_ptr<T>::value_type& shared_ptr<T>::operator* ()
    {
        return *(p_mem_->p_value_);
    }


    template<class T>
    typename shared_ptr<T>::value_type* shared_ptr<T>::get()
    {
        return p_mem_->p_value_;
    }


    template<class T>
    bool shared_ptr<T>::is_last_ptr() const
    {
        return (p_mem_->size_ == 0);
    }

    template<class T>
    void shared_ptr<T>::incr_size()
    {
        p_mem_->size_++;
    }

    template<class T>
    void shared_ptr<T>::decr_size()
    {
        p_mem_->size_--;
    }

    template<class T>
    void shared_ptr<T>::set_size(const size_type size)
    {
        p_mem_->size_ = size;
    }

    template<class T>
    typename shared_ptr<T>::size_type& shared_ptr<T>::get_size()
    {
        return p_mem_->size_;
    }


} // namespace meta


#endif // !_SHARED_PTR_H_

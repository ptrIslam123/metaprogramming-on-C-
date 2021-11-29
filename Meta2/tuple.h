#pragma once

#include <iostream>

template<class T, class ... Args>
struct TupleHelper;

template<class T>
struct TupleHelper<T>;


template<class T>
struct TupleElement;


template<class ... Args>
using Tuple = TupleHelper<Args ...>;

template<class T, class ... Args>
struct TupleHelper : public TupleElement<T> {
    typedef T HeadType;
    typedef TupleHelper<Args ...> TailType;

    TupleHelper(const T& value, const Args& ... args);

    HeadType head_;
    TailType tail_;
};


template<class T, class ... Args>
TupleHelper<T, Args ...>::TupleHelper(const T& value, const Args& ... args):
    TupleElement<T>(value),
    head_(value),
    tail_(TailType(args ...))
{}


template<class T>
struct TupleHelper<T> {
    typedef T HeadType;
    
    TupleHelper(const T& value);

    HeadType head_;
};

template<class T>
TupleHelper<T>::TupleHelper(const T& value):
    head_(value) 
{}


template<class T>
struct TupleElement {
    typedef T TupleElementType;

    TupleElement(const T& value);

    TupleElementType value_;
};

template<class T>
TupleElement<T>::TupleElement(const T& value):
    value_(value)
{}


template<std::size_t index>
struct Getter;


template<std::size_t index, class T, class ... Args>
auto get(const TupleHelper<T, Args ...>& tuple) -> decltype(Getter<index>::at(tuple)) {
    return Getter<index>::at(tuple);
}

template<std::size_t index>
struct Getter {
    template<class T, class ... Args>
    static auto at(const TupleHelper<T, Args ...>& tuple) -> decltype(Getter<index - 1>::at(tuple.tail_)){
        return Getter<index - 1>::at(tuple.tail_);
    }
};

template<>
struct Getter<0> {
    template<class T, class ... Args>
    static typename TupleHelper<T, Args ...>::HeadType at(const TupleHelper<T, Args ...>& tuple) {
        return tuple.head_;
    }
};


template<class CT, class T, class ... Args>
auto tupleCast(const TupleHelper<T, Args ...>& tuple) -> decltype(static_cast<TupleElement<T>>(tuple).value_) {
    return static_cast<TupleElement<CT>>(tuple).value_;
}
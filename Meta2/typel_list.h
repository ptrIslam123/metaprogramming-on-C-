#pragma once

#include <iostream>

struct Nil {};

template<class T>
struct Holder;

template<class T, class ... Args>
struct TypeList;

template<class ... Args>
using Typelist = TypeList<Args ...>;

template<class T, class TYPELIST>
T valueOf(const TYPELIST& typeList);


template<class T, class ... Args>
struct TypeList : public Holder<T>, TypeList<Args ...> {
    typedef T HeadType;
    typedef TypeList<Args ...> TailType;

    TypeList(const T& value, const Args& ... args):
        Holder<HeadType>(value),
        TypeList<Args ...>(args ...)
    {}
};

template<class T>
struct TypeList<T> : public Holder<T> {
    typedef T HeadType;
    typedef Nil TailType;

    TypeList(const T& value):
        Holder<HeadType>(value)
    {}
};

template<class T, class TYPELIST>
T valueOf(const TYPELIST& typeList) {
    return (static_cast<Holder<T>>(typeList).value_);
}

template<class T>
struct Holder {
    typedef T Type;

    Holder(const T& value):
        value_(value) 
    {}

    Type value_;
};
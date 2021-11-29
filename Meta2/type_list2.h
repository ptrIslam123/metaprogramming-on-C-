#pragma once

typedef unsigned int SizeType;

struct Nil {};

template<SizeType index, class T, class ... Args>
struct TList;

template<SizeType index, class T>
struct Holder {
    typedef T Type;

    Holder(const T& value):
        value_(value) {}

    Type value_;
};


template<SizeType index, class T, class ... Args>
struct TList : public Holder<index, T>, TList<index + 1 ,Args ...> {
    typedef T HeadType;
    typedef TList<index + 1, Args ...> TailType;

    TList(const T& value, const Args& ... args):
        Holder<index, T>(value),
        TList<index + 1, Args ...>(args ...) {}

};


template<SizeType index, class T>
struct TList<index, T> : public Holder<index, T> {
    typedef T HeadType;
    typedef Nil TailType;

    TList(const T& value):
        Holder<index, T>(value) {}
};

template<class ... Args>
using TypeList2 = TList<0, Args ...>;


template<SizeType index, class T, class TLIST>
T valueOf(const TLIST& typeList) {
    return (static_cast<Holder<index, T>>(typeList).value_);
}
#pragma once


typedef unsigned int SizeType;

struct Nil {};

template<SizeType pos, class T>
struct Holder {
    typedef T Type;
    static const SizeType index = pos;

    Holder(const T& value):
        value_(value)
    {}

    Type value_;
};




template<class T, class ... Args>
struct TList;

template<class T, class ... Args>
struct GetIndex;

template<class T, class ... Args>
struct GetIndex {
    static const SizeType getIndex(const TList<T, Args ...>& typeList) {
        return GetIndex<Args ...>::getIndex(typeList.tail_);  
    }
};


template<class T>
struct GetIndex<T> {
    static const SizeType getIndex(const TList<T>& typeList) {
        return 0;
    }
};

template<class T, class ... Args>
struct TList : public TList<Args ...> {
    typedef T HeadType;
    typedef TList<Args ...> TailType;

    TList(const T& value, const Args& ... args):
        TList<Args ...>(args ...), 
        value_(value)
    {}

    TailType tail_;
    Holder<GetInde::getIndex(TList<Args ...>()  ), HeadType> value_;
};

template<class T>
struct TList<T> {
    typedef T HeadType;
    typedef Nil TailType;

    TList(const T& value) {}

    Holder<0, HeadType> value_;
};

template<class ... Args>
using TypeList3 = TList<Args ...>;
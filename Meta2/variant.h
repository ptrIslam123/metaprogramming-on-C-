#include <iostream>

typedef int SizeType;

struct Nil {};

template<bool cond, class T1, class T>
struct CondType;

template<class T1, class T2>
struct CondType<true, T1, T2> {
    typedef T1 type; 
};

template<class T1, class T2>
struct CondType<false, T1, T2> {
    typedef T2 type;
};

template<class T1, class T2>
struct IsEq {
    static const bool value = false;
};

template<class T>
struct IsEq<T, T> {
    static const bool value = true;
};


template<bool cond, class T>
struct HasTypeIf;

template<class T> 
struct HasTypeIf<true, T> {
    typedef T type;
};


template<bool cond, class T>
struct HasValueIf;

template<class T>
struct HasValueIf<true, T> {
    static const T get(const T& value) {
        return value;
    }
};

template<class T>
struct HasValueIf<false, T> {};

template<class T1, class T2>
struct Pair {
    typedef T1 Type1;
    typedef T2 Type2;

    Pair(const Type1& v1, const Type2& v2):
        value1_(v1), value2_(v2) 
    {}

    Type1 value1_;
    Type2 value2_;
};


template<class T, class ... Args>
struct Variant {

    template<class Head, class ... Tail>
    union VarUnion;

    template<SizeType index, class Type, class Head, class ... Tail>
    struct GetterUnionIndexByType;

    template<class Head, class ... Tail>
    struct GetterUnionByIndex;

    template<SizeType index, class TVarUnion>
    struct GetterUnionTypeByIndex;


    template<class Head, class ... Tail>
    union VarUnion {
        typedef Head HeadType;
        typedef VarUnion<Tail ...> TailType;

        VarUnion():
            tail_()
        {}

        void construct(const HeadType& headValue) {
            new (&head_) HeadType(headValue);
        }

        HeadType head_;
        TailType tail_;
    };

    template<class Head>
    union VarUnion <Head> {
        typedef Head HeadType;
        typedef Nil TailType;

        VarUnion():
            head_()
        {}

        void construct(const HeadType& headValue) {
            new (&head_) HeadType(headValue);
        }

        void destroy() {
            head_.~HeadType();
        }

        HeadType head_;
    };


    template<SizeType index, class Head, class ... Tail>
    struct GetterUnionTypeByIndex<index, VarUnion<Head, Tail ...>> {
        typedef typename GetterUnionTypeByIndex<index - 1, VarUnion<Tail ...>>::type type;
    };

    template<class Head, class ... Tail>
    struct GetterUnionTypeByIndex<0, VarUnion<Head, Tail ...>> {
        typedef VarUnion<Head, Tail ...> type;
    };


    template<SizeType index, class Type, class Head, class ... Tail>
    struct GetterUnionIndexByType {
        static constexpr SizeType value = IsEq<Type, typename VarUnion<Head, Tail ...>::HeadType>::value ? index : 
            GetterUnionIndexByType<index + 1, Type, Tail ...>::value;
    };

    template<SizeType index, class Type, class Head>
    struct GetterUnionIndexByType<index, Type, Head> {
        static constexpr SizeType value = IsEq<Type, typename VarUnion<Head>::HeadType>::value ? index : -1;
    };




    template<class Head, class ... Tail>
    struct GetterUnionByIndex {
        static void* get(SizeType index, VarUnion<Head, Tail ...>* var) {
            return index != 0 ? GetterUnionByIndex<Tail ...>::get(index - 1, &var->tail_) : &(*var);
        }
    };

    template<class Head>
    struct GetterUnionByIndex<Head> {
        static void* get(SizeType index, VarUnion<Head>* var) {
            return index != 0 ? NULL : &(*var);
        }
    };


    Variant():
        curActiveUnionIndex_(0),
        value_()
    {}

    template<class ElementType>
    Variant(const ElementType& value):
        curActiveUnionIndex_(0),
        value_() {
        constexpr SizeType index = GetterUnionIndexByType<0, ElementType, T, Args ...>::value;
        typedef typename GetterUnionTypeByIndex<index, VarUnion<T, Args ...>>::type VarUnionType;

        VarUnionType* unionMember = static_cast<VarUnionType*>(GetterUnionByIndex<T, Args ...>::get(index, &value_));
        unionMember->construct(value);
        curActiveUnionIndex_ = index;
    }

    ~Variant() {
        // GetterUnionByIndex<T, Args ...>::get(curActiveUnionIndex_, &value_)->destroy();
    }

    SizeType curActiveUnionIndex_;
    VarUnion<T, Args ...> value_;
};



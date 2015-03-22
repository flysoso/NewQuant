#ifndef BASE_EXPRESSION_H
#define BASE_EXPRESSION_H

#include <assert.h>

#include "FunctionObject.h"
#include "Parameter.h"

namespace NewQuant
{
    template<typename T>
    class BaseExpression
    {
    protected:
        BaseExpression(){}
        //BaseExpression(const BaseExpression<T> &be){}
    public:
        virtual ~BaseExpression(){}

        virtual T operator[](const Parameter<T> &) const = 0;

        virtual T eval() const = 0;
        virtual T eval(const T &x) const = 0;
        virtual T eval(const T &x1, const T&x2) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3, const T&x4) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8) const = 0;
        virtual T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8, const T&x9) const = 0;


        virtual T operator () () const = 0;
        virtual T operator () (const T &x) const = 0;
        virtual T operator () (const T &x1, const T&x2) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3, const T&x4) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8) const = 0;
        virtual T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8, const T&x9) const = 0;

    };

}

#endif //BASE_EXPRESSION_H



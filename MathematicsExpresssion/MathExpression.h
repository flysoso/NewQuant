#ifndef MATH_EXPRESSION_H
#define MATH_EXPRESSION_H

#include <memory>
#include <vector>

#include "ConstantAndVariable.h"
#include "BinaryExpression.h"
#include "UnitaryExpression.h"
#include "Parameter.h"

namespace NewQuant
{

    template<typename T>
    class MathExpression
    {
    private:
        std::shared_ptr<const BaseExpression<T> > be;
    public:
        MathExpression(){}

        explicit MathExpression(const Constant<T> &c)
        {
            be.reset(new Constant<T>(c));
        }

        explicit MathExpression(const Variable<T> &v)
        {
            be.reset(new Variable<T>(v));
        }

        template<class ExprT1, class ExprT2, template<typename ELEM> class BinOp>
        explicit MathExpression(const BinaryExpression<T, ExprT1, ExprT2, BinOp> &b)
        {
            be.reset(new BinaryExpression<T, ExprT1, ExprT2, BinOp>(b));
        }

        template<class ExprT, template<typename ELEM> class BinOp>
        explicit MathExpression(const UnitaryExpression<T, ExprT, BinOp> &b)
        {
            be.reset(new UnitaryExpression<T, ExprT, BinOp>(b));
        }

        MathExpression(const MathExpression<T> &me) : be(me.be){}

        MathExpression<T> & operator = (const MathExpression<T> &me)
        {
            if (me == this)
            {
                return *this;
            }
            be.reset(me.be);
            return *this;
        }

        template<class ExprT1, class ExprT2, template<typename ELEM> class BinOp>
        MathExpression<T> & operator = (const BinaryExpression<T, ExprT1, ExprT2, BinOp> &b)
        {
            be.reset(new BinaryExpression<T, ExprT1, ExprT2, BinOp>(b));
            return *this;
        }

        template<class ExprT, template<typename ELEM> class BinOp>
        MathExpression<T> & operator = (const UnitaryExpression<T, ExprT, BinOp> &b)
        {
            be.reset(new UnitaryExpression<T, ExprT, BinOp>(b));
            return *this;
        }

        ~MathExpression(){}

        T operator[](const Parameter<T> &p) const
        {
            return be->operator[](p);
        }

        T operator () () const
        {
            return be->eval();
        }
        T operator () (const T &x) const
        {
            return be->eval(x);
        }
        T operator () (const T &x1, const T &x2) const
        {
            return be->eval(x1, x2);
        }
        T operator () (const T &x1, const T &x2, const T &x3) const
        {
            return be->eval(x1, x2, x3);
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4) const
        {
            return be->eval(x1, x2, x3, x4);
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
        {
            return be->eval(x1, x2, x3, x4, x5);
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                       const T &x6) const
        {
            return be->eval(x1, x2, x3, x4, x5, x6);
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                       const T &x6, const T &x7) const
        {
            return be->eval(x1, x2, x3, x4, x5, x6, x7);
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                       const T &x6, const T &x7, const T &x8) const
        {
            return be->eval(x1, x2, x3, x4, x5, x6, x7, x8);
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                       const T &x6, const T &x7, const T &x8, const T &x9) const
        {
            return be->eval(x1, x2, x3, x4, x5, x6, x7, x8, x9);
        }
    };


}



#endif //MATH_EXPRESSION_H

#ifndef BINARY_EXPRESSION_H
#define BINARY_EXPRESSION_H

#include <functional>
#include "BaseExpression.h"

namespace NewQuant
{
    template<typename T, typename ExprT, template<typename ELEM> class UniOp> class UnitaryExpression;
    template<typename T> class Constant;
    template<typename T> class Variable;

    template<typename T, typename ExprT1, typename ExprT2, template<typename ELEM> class BinOp>
    class BinaryExpression : public BaseExpression < T >
    {
    private:
        typename ExprTraits<ExprT1>::expr_type expr1;
        typename ExprTraits<ExprT2>::expr_type expr2;
        BinOp<T> op;
    public:
        BinaryExpression(const ExprT1 &e1, const ExprT2 &e2, const BinOp<T> &o) : expr1(e1), expr2(e2), op(o) {}

        BinaryExpression(const BinaryExpression<T, ExprT1, ExprT2, BinOp> &be) : expr1(be.expr1), expr2(be.expr2), op(be.op){}

        ~BinaryExpression(){}

        T eval() const
        {
            return op(expr1.eval(), expr2.eval());
        }
        T eval(const T &x) const
        {
            return op(expr1.eval(x), expr2.eval(x));
        }
        T eval(const T &x1, const T &x2) const
        {
            return op(expr1.eval(x1, x2), expr2.eval(x1, x2));
        }
        T eval(const T &x1, const T &x2, const T &x3) const
        {
            return op(expr1.eval(x1, x2, x3), expr2.eval(x1, x2, x3));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4) const
        {
            return op(expr1.eval(x1, x2, x3, x4), expr2.eval(x1, x2, x3, x4));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5), expr2.eval(x1, x2, x3, x4, x5));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6), expr2.eval(x1, x2, x3, x4, x5, x6));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6, x7), expr2.eval(x1, x2, x3, x4, x5, x6, x7));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6, x7, x8), expr2.eval(x1, x2, x3, x4, x5, x6, x7, x8));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6, x7, x8, x9), expr2.eval(x1, x2, x3, x4, x5, x6, x7, x8, x9));
        }

        T operator () () const
        {
            return op(expr1.eval(), expr2.eval());
        }
        T operator () (const T &x) const
        {
            return op(expr1.eval(x), expr2.eval(x));
        }
        T operator () (const T &x1, const T &x2) const
        {
            return op(expr1.eval(x1, x2), expr2.eval(x1, x2));
        }
        T operator () (const T &x1, const T &x2, const T &x3) const
        {
            return op(expr1.eval(x1, x2, x3), expr2.eval(x1, x2, x3));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4) const
        {
            return op(expr1.eval(x1, x2, x3, x4), expr2.eval(x1, x2, x3, x4));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5), expr2.eval(x1, x2, x3, x4, x5));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6), expr2.eval(x1, x2, x3, x4, x5, x6));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6, x7), expr2.eval(x1, x2, x3, x4, x5, x6, x7));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6, x7, x8), expr2.eval(x1, x2, x3, x4, x5, x6, x7, x8));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) const
        {
            return op(expr1.eval(x1, x2, x3, x4, x5, x6, x7, x8, x9), expr2.eval(x1, x2, x3, x4, x5, x6, x7, x8, x9));
        }


    };

    // operator +
    //c+C
    template <typename T, typename constant>
    BinaryExpression<T, constant, Constant<T>, std::plus> operator + (const constant &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, constant, Constant<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //C+c
    template <typename T, typename constant>
    BinaryExpression<T, Constant<T>, constant, std::plus> operator + (const Constant<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Constant<T>, constant, std::plus>(e1, e2, std::plus<T>());
    }
    //C+C
    template <typename T>
    BinaryExpression<T, Constant<T>, Constant<T>, std::plus> operator + (const Constant<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Constant<T>, std::plus>(e1, e2, std::plus<T>());
    }

    //c+V
    template <typename T, typename constant>
    BinaryExpression<T, constant, Variable<T>, std::plus> operator + (const constant &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, constant, Variable<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //V+c
    template <typename T, typename constant>
    BinaryExpression<T, Variable<T>, constant, std::plus> operator + (const Variable<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Variable<T>, constant, std::plus>(e1, e2, std::plus<T>());
    }
    //V+C
    template <typename T>
    BinaryExpression<T, Variable<T>, Constant<T>, std::plus> operator + (const Variable<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Constant<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //C+V
    template <typename T>
    BinaryExpression<T, Constant<T>, Variable<T>, std::plus> operator + (const Constant<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Variable<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //V+V
    template <typename T>
    BinaryExpression<T, Variable<T>, Variable<T>, std::plus> operator + (const Variable<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Variable<T>, std::plus>(e1, e2, std::plus<T>());
    }

    //c+U
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::plus> operator + (const constant &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::plus>(e1, e2, std::plus<T>());
    }
    //U+c
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::plus> operator + (const UnitaryExpression<T, T1, T2> &e1, const constant &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::plus>(e1, e2, std::plus<T>());
    }
    //C+U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::plus> operator + (const Constant<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::plus>(e1, e2, std::plus<T>());
    }
    //U+C
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::plus> operator + (const UnitaryExpression<T, T1, T2> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //U+V
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::plus> operator + (const UnitaryExpression<T, T1, T2> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //V+U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::plus> operator + (const Variable<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::plus>(e1, e2, std::plus<T>());
    }
    //U+U
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, template<typename ELEM> class T4>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::plus> operator + (const UnitaryExpression<T, T1, T2> &e1, const UnitaryExpression<T, T3, T4> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::plus>(e1, e2, std::plus<T>());
    }

    //c+B
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::plus> operator + (const constant e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::plus>(e1, e2, std::plus<T>());
    }
    //B+c
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::plus> operator + (const BinaryExpression<T, T1, T2, T3> e1, const constant &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::plus>(e1, e2, std::plus<T>());
    }
    //C+B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::plus> operator + (const Constant<T> e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::plus>(e1, e2, std::plus<T>());
    }
    //B+C
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::plus> operator + (const BinaryExpression<T, T1, T2, T3> e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //V+B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::plus> operator + (const Variable<T> &e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::plus>(e1, e2, std::plus<T>());
    }
    //B+V
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::plus> operator + (const BinaryExpression<T, T1, T2, T3> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::plus>(e1, e2, std::plus<T>());
    }
    //U+B
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::plus> operator + (const UnitaryExpression<T, T1, T2> &e1, const BinaryExpression<T, T3, T4, T5> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::plus>(e1, e2, std::plus<T>());
    }
    //B+U
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::plus> operator + (const BinaryExpression<T, T1, T2, T3> &e1, const UnitaryExpression<T, T4, T5> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::plus>(e1, e2, std::plus<T>());
    }
    //B+B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, typename T5, template<typename ELEM> class T6>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::plus> operator + (const BinaryExpression<T, T1, T2, T3> &e1, const BinaryExpression<T, T4, T5, T6> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::plus>(e1, e2, std::plus<T>());
    }


    // operator -
    //c-C
    template <typename T, typename constant>
    BinaryExpression<T, constant, Constant<T>, std::minus> operator - (const constant &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, constant, Constant<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //C-c
    template <typename T, typename constant>
    BinaryExpression<T, Constant<T>, constant, std::minus> operator - (const Constant<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Constant<T>, constant, std::minus>(e1, e2, std::minus<T>());
    }
    //C-C
    template <typename T>
    BinaryExpression<T, Constant<T>, Constant<T>, std::minus> operator - (const Constant<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Constant<T>, std::minus>(e1, e2, std::minus<T>());
    }

    //c-V
    template <typename T, typename constant>
    BinaryExpression<T, constant, Variable<T>, std::minus> operator - (const constant &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, constant, Variable<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //V-c
    template <typename T, typename constant>
    BinaryExpression<T, Variable<T>, constant, std::minus> operator - (const Variable<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Variable<T>, constant, std::minus>(e1, e2, std::minus<T>());
    }
    //V-C
    template <typename T>
    BinaryExpression<T, Variable<T>, Constant<T>, std::minus> operator - (const Variable<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Constant<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //C-V
    template <typename T>
    BinaryExpression<T, Constant<T>, Variable<T>, std::minus> operator - (const Constant<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Variable<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //V-V
    template <typename T>
    BinaryExpression<T, Variable<T>, Variable<T>, std::minus> operator - (const Variable<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Variable<T>, std::minus>(e1, e2, std::minus<T>());
    }

    //c-U
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::minus> operator - (const constant &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::minus>(e1, e2, std::minus<T>());
    }
    //U-c
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::minus> operator - (const UnitaryExpression<T, T1, T2> &e1, const constant &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::minus>(e1, e2, std::minus<T>());
    }
    //C-U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::minus> operator - (const Constant<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::minus>(e1, e2, std::minus<T>());
    }
    //U-C
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::minus> operator - (const UnitaryExpression<T, T1, T2> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //U-V
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::minus> operator - (const UnitaryExpression<T, T1, T2> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //V-U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::minus> operator - (const Variable<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::minus>(e1, e2, std::minus<T>());
    }
    //U-U
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, template<typename ELEM> class T4>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::minus> operator - (const UnitaryExpression<T, T1, T2> &e1, const UnitaryExpression<T, T3, T4> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::minus>(e1, e2, std::minus<T>());
    }

    //c-B
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::minus> operator - (const constant e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::minus>(e1, e2, std::minus<T>());
    }
    //B-c
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::minus> operator - (const BinaryExpression<T, T1, T2, T3> e1, const constant &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::minus>(e1, e2, std::minus<T>());
    }
    //C-B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::minus> operator - (const Constant<T> e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::minus>(e1, e2, std::minus<T>());
    }
    //B-C
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::minus> operator - (const BinaryExpression<T, T1, T2, T3> e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //V-B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::minus> operator - (const Variable<T> &e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::minus>(e1, e2, std::minus<T>());
    }
    //B-V
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::minus> operator - (const BinaryExpression<T, T1, T2, T3> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::minus>(e1, e2, std::minus<T>());
    }
    //U-B
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::minus> operator - (const UnitaryExpression<T, T1, T2> &e1, const BinaryExpression<T, T3, T4, T5> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::minus>(e1, e2, std::minus<T>());
    }
    //B-U
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::minus> operator - (const BinaryExpression<T, T1, T2, T3> &e1, const UnitaryExpression<T, T4, T5> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::minus>(e1, e2, std::minus<T>());
    }
    //B-B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, typename T5, template<typename ELEM> class T6>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::minus> operator - (const BinaryExpression<T, T1, T2, T3> &e1, const BinaryExpression<T, T4, T5, T6> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::minus>(e1, e2, std::minus<T>());
    }


    // operator *
    //c*C
    template <typename T, typename constant>
    BinaryExpression<T, constant, Constant<T>, std::multiplies> operator * (const constant &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, constant, Constant<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //C*c
    template <typename T, typename constant>
    BinaryExpression<T, Constant<T>, constant, std::multiplies> operator * (const Constant<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Constant<T>, constant, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //C*C
    template <typename T>
    BinaryExpression<T, Constant<T>, Constant<T>, std::multiplies> operator * (const Constant<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Constant<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }

    //c*V
    template <typename T, typename constant>
    BinaryExpression<T, constant, Variable<T>, std::multiplies> operator * (const constant &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, constant, Variable<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //V*c
    template <typename T, typename constant>
    BinaryExpression<T, Variable<T>, constant, std::multiplies> operator * (const Variable<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Variable<T>, constant, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //V*C
    template <typename T>
    BinaryExpression<T, Variable<T>, Constant<T>, std::multiplies> operator * (const Variable<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Constant<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //C*V
    template <typename T>
    BinaryExpression<T, Constant<T>, Variable<T>, std::multiplies> operator * (const Constant<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Variable<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //V*V
    template <typename T>
    BinaryExpression<T, Variable<T>, Variable<T>, std::multiplies> operator * (const Variable<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Variable<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }

    //c*U
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::multiplies> operator * (const constant &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //U*c
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::multiplies> operator * (const UnitaryExpression<T, T1, T2> &e1, const constant &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //C*U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::multiplies> operator * (const Constant<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //U*C
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::multiplies> operator * (const UnitaryExpression<T, T1, T2> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //U*V
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::multiplies> operator * (const UnitaryExpression<T, T1, T2> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //V*U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::multiplies> operator * (const Variable<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //U*U
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, template<typename ELEM> class T4>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::multiplies> operator * (const UnitaryExpression<T, T1, T2> &e1, const UnitaryExpression<T, T3, T4> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::multiplies>(e1, e2, std::multiplies<T>());
    }

    //c*B
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::multiplies> operator * (const constant e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //B*c
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::multiplies> operator * (const BinaryExpression<T, T1, T2, T3> e1, const constant &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //C*B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::multiplies> operator * (const Constant<T> e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //B*C
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::multiplies> operator * (const BinaryExpression<T, T1, T2, T3> e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //V*B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::multiplies> operator * (const Variable<T> &e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //B*V
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::multiplies> operator * (const BinaryExpression<T, T1, T2, T3> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //U*B
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::multiplies> operator * (const UnitaryExpression<T, T1, T2> &e1, const BinaryExpression<T, T3, T4, T5> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //B*U
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::multiplies> operator * (const BinaryExpression<T, T1, T2, T3> &e1, const UnitaryExpression<T, T4, T5> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::multiplies>(e1, e2, std::multiplies<T>());
    }
    //B*B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, typename T5, template<typename ELEM> class T6>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::multiplies> operator * (const BinaryExpression<T, T1, T2, T3> &e1, const BinaryExpression<T, T4, T5, T6> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::multiplies>(e1, e2, std::multiplies<T>());
    }


    // operator /
    //c/C
    template <typename T, typename constant>
    BinaryExpression<T, constant, Constant<T>, std::divides> operator / (const constant &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, constant, Constant<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //C/c
    template <typename T, typename constant>
    BinaryExpression<T, Constant<T>, constant, std::divides> operator / (const Constant<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Constant<T>, constant, std::divides>(e1, e2, std::divides<T>());
    }
    //C/C
    template <typename T>
    BinaryExpression<T, Constant<T>, Constant<T>, std::divides> operator / (const Constant<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Constant<T>, std::divides>(e1, e2, std::divides<T>());
    }

    //c/V
    template <typename T, typename constant>
    BinaryExpression<T, constant, Variable<T>, std::divides> operator / (const constant &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, constant, Variable<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //V/c
    template <typename T, typename constant>
    BinaryExpression<T, Variable<T>, constant, std::divides> operator / (const Variable<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Variable<T>, constant, std::divides>(e1, e2, std::divides<T>());
    }
    //V/C
    template <typename T>
    BinaryExpression<T, Variable<T>, Constant<T>, std::divides> operator / (const Variable<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Constant<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //C/V
    template <typename T>
    BinaryExpression<T, Constant<T>, Variable<T>, std::divides> operator / (const Constant<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Variable<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //V/V
    template <typename T>
    BinaryExpression<T, Variable<T>, Variable<T>, std::divides> operator / (const Variable<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Variable<T>, std::divides>(e1, e2, std::divides<T>());
    }

    //c/U
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::divides> operator / (const constant &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, std::divides>(e1, e2, std::divides<T>());
    }
    //U/c
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::divides> operator / (const UnitaryExpression<T, T1, T2> &e1, const constant &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, std::divides>(e1, e2, std::divides<T>());
    }
    //C/U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::divides> operator / (const Constant<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, std::divides>(e1, e2, std::divides<T>());
    }
    //U/C
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::divides> operator / (const UnitaryExpression<T, T1, T2> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //U/V
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::divides> operator / (const UnitaryExpression<T, T1, T2> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //V/U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::divides> operator / (const Variable<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, std::divides>(e1, e2, std::divides<T>());
    }
    //U/U
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, template<typename ELEM> class T4>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::divides> operator / (const UnitaryExpression<T, T1, T2> &e1, const UnitaryExpression<T, T3, T4> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, std::divides>(e1, e2, std::divides<T>());
    }

    //c/B
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::divides> operator / (const constant e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, std::divides>(e1, e2, std::divides<T>());
    }
    //B/c
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::divides> operator / (const BinaryExpression<T, T1, T2, T3> e1, const constant &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, std::divides>(e1, e2, std::divides<T>());
    }
    //C/B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::divides> operator / (const Constant<T> e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, std::divides>(e1, e2, std::divides<T>());
    }
    //B/C
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::divides> operator / (const BinaryExpression<T, T1, T2, T3> e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //V/B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::divides> operator / (const Variable<T> &e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, std::divides>(e1, e2, std::divides<T>());
    }
    //B/V
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::divides> operator / (const BinaryExpression<T, T1, T2, T3> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, std::divides>(e1, e2, std::divides<T>());
    }
    //U/B
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::divides> operator / (const UnitaryExpression<T, T1, T2> &e1, const BinaryExpression<T, T3, T4, T5> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, std::divides>(e1, e2, std::divides<T>());
    }
    //B/U
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::divides> operator / (const BinaryExpression<T, T1, T2, T3> &e1, const UnitaryExpression<T, T4, T5> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, std::divides>(e1, e2, std::divides<T>());
    }
    //B/B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, typename T5, template<typename ELEM> class T6>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::divides> operator / (const BinaryExpression<T, T1, T2, T3> &e1, const BinaryExpression<T, T4, T5, T6> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, std::divides>(e1, e2, std::divides<T>());
    }


    // operator ^
    //c^C
    template <typename T, typename constant>
    BinaryExpression<T, constant, Constant<T>, pow_func> pow(const constant &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, constant, Constant<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //C^c
    template <typename T, typename constant>
    BinaryExpression<T, Constant<T>, constant, pow_func> pow(const Constant<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Constant<T>, constant, pow_func>(e1, e2, pow_func<T>());
    }
    //C^C
    template <typename T>
    BinaryExpression<T, Constant<T>, Constant<T>, pow_func> pow(const Constant<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Constant<T>, pow_func>(e1, e2, pow_func<T>());
    }

    //c^V
    template <typename T, typename constant>
    BinaryExpression<T, constant, Variable<T>, pow_func> pow(const constant &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, constant, Variable<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //V^c
    template <typename T, typename constant>
    BinaryExpression<T, Variable<T>, constant, pow_func> pow(const Variable<T> &e1, const constant &e2)
    {
        return BinaryExpression<T, Variable<T>, constant, pow_func>(e1, e2, pow_func<T>());
    }
    //V^C
    template <typename T>
    BinaryExpression<T, Variable<T>, Constant<T>, pow_func> pow(const Variable<T> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Constant<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //C^V
    template <typename T>
    BinaryExpression<T, Constant<T>, Variable<T>, pow_func> pow(const Constant<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Constant<T>, Variable<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //V^V
    template <typename T>
    BinaryExpression<T, Variable<T>, Variable<T>, pow_func> pow(const Variable<T> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, Variable<T>, Variable<T>, pow_func>(e1, e2, pow_func<T>());
    }

    //c^U
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, pow_func> pow(const constant &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, constant, UnitaryExpression<T, T1, T2>, pow_func>(e1, e2, pow_func<T>());
    }
    //U^c
    template <typename T, typename constant, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, pow_func> pow(const UnitaryExpression<T, T1, T2> &e1, const constant &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, constant, pow_func>(e1, e2, pow_func<T>());
    }
    //C^U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, pow_func> pow(const Constant<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Constant<T>, UnitaryExpression<T, T1, T2>, pow_func>(e1, e2, pow_func<T>());
    }
    //U^C
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, pow_func> pow(const UnitaryExpression<T, T1, T2> &e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Constant<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //U^V
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, pow_func> pow(const UnitaryExpression<T, T1, T2> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, Variable<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //V^U
    template <typename T, typename T1, template<typename ELEM> class T2>
    BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, pow_func> pow(const Variable<T> &e1, const UnitaryExpression<T, T1, T2> &e2)
    {
        return BinaryExpression<T, Variable<T>, UnitaryExpression<T, T1, T2>, pow_func>(e1, e2, pow_func<T>());
    }
    //U^U
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, template<typename ELEM> class T4>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, pow_func> pow(const UnitaryExpression<T, T1, T2> &e1, const UnitaryExpression<T, T3, T4> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, UnitaryExpression<T, T3, T4>, pow_func>(e1, e2, pow_func<T>());
    }

    //c^B
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, pow_func> pow(const constant e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, constant, BinaryExpression<T, T1, T2, T3>, pow_func>(e1, e2, pow_func<T>());
    }
    //B^c
    template <typename T, typename constant, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, pow_func> pow(const BinaryExpression<T, T1, T2, T3> e1, const constant &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, constant, pow_func>(e1, e2, pow_func<T>());
    }
    //C^B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, pow_func> pow(const Constant<T> e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Constant<T>, BinaryExpression<T, T1, T2, T3>, pow_func>(e1, e2, pow_func<T>());
    }
    //B^C
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, pow_func> pow(const BinaryExpression<T, T1, T2, T3> e1, const Constant<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Constant<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //V^B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, pow_func> pow(const Variable<T> &e1, const BinaryExpression<T, T1, T2, T3> &e2)
    {
        return BinaryExpression<T, Variable<T>, BinaryExpression<T, T1, T2, T3>, pow_func>(e1, e2, pow_func<T>());
    }
    //B^V
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, pow_func> pow(const BinaryExpression<T, T1, T2, T3> &e1, const Variable<T> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, Variable<T>, pow_func>(e1, e2, pow_func<T>());
    }
    //U^B
    template <typename T, typename T1, template<typename ELEM> class T2, typename T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, pow_func> pow(const UnitaryExpression<T, T1, T2> &e1, const BinaryExpression<T, T3, T4, T5> &e2)
    {
        return BinaryExpression<T, UnitaryExpression<T, T1, T2>, BinaryExpression<T, T3, T4, T5>, pow_func>(e1, e2, pow_func<T>());
    }
    //B^U
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, template<typename ELEM> class T5>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, pow_func> pow(const BinaryExpression<T, T1, T2, T3> &e1, const UnitaryExpression<T, T4, T5> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, UnitaryExpression<T, T4, T5>, pow_func>(e1, e2, pow_func<T>());
    }
    //B^B
    template <typename T, typename T1, typename T2, template<typename ELEM> class T3, typename T4, typename T5, template<typename ELEM> class T6>
    BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, pow_func> pow(const BinaryExpression<T, T1, T2, T3> &e1, const BinaryExpression<T, T4, T5, T6> &e2)
    {
        return BinaryExpression<T, BinaryExpression<T, T1, T2, T3>, BinaryExpression<T, T4, T5, T6>, pow_func>(e1, e2, pow_func<T>());
    }

}

#endif //BINARY_EXPRESSION_H


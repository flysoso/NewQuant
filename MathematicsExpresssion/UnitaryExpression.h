#ifndef UNITARY_EXPRESSION_H
#define UNITARY_EXPRESSION_H

#include <functional>
#include "BaseExpression.h"

namespace NewQuant
{
    template<typename T, typename ExprT1, typename ExprT2, template<typename ELEM> class BinOp> class BinaryExpression;
    template<typename T> class Constant;
    template<typename T> class Variable;

    template<typename T, typename ExprT, template<typename ELEM> class UniOp>
    class UnitaryExpression : public BaseExpression < T >
    {
    private:
        typename ExprTraits<ExprT>::expr_type expr;
        UniOp<T> op;
    public:
        UnitaryExpression(const ExprT &e, const UniOp<T> &o) : expr(e), op(o) {}

        UnitaryExpression(const UnitaryExpression<T, ExprT, UniOp> &ue) : expr(ue.expr), op(ue.op){}

        ~UnitaryExpression(){}

        T operator[](const Parameter<T> &p) const
        {
            return op(expr[p]);
        }

        T eval() const
        {
            return op(expr.eval());
        }
        T eval(const T &x) const
        {
            return op(expr.eval(x));
        }
        T eval(const T &x1, const T &x2) const
        {
            return op(expr.eval(x1, x2));
        }
        T eval(const T &x1, const T &x2, const T &x3) const
        {
            return op(expr.eval(x1, x2, x3));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4) const
        {
            return op(expr.eval(x1, x2, x3, x4));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6, x7));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6, x7, x8));
        }
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6, x7, x8, x9));
        }

        T operator () () const
        {
            return op(expr.eval());
        }
        T operator () (const T &x) const
        {
            return op(expr.eval(x));
        }
        T operator () (const T &x1, const T &x2) const
        {
            return op(expr.eval(x1, x2));
        }
        T operator () (const T &x1, const T &x2, const T &x3) const
        {
            return op(expr.eval(x1, x2, x3));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4) const
        {
            return op(expr.eval(x1, x2, x3, x4));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6, x7));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6, x7, x8));
        }
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) const
        {
            return op(expr.eval(x1, x2, x3, x4, x5, x6, x7, x8, x9));
        }

    };

    //-C
    template<typename T>
    UnitaryExpression<T, Constant<T>, std::negate> operator - (const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, std::negate>(e, std::negate<T>());
    }
    //-V
    template<typename T>
    UnitaryExpression<T, Variable<T>, std::negate> operator - (const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, std::negate>(e, std::negate<T>());
    }

    //-------sin
    //sin(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, sin_func> sin(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, sin_func>(e, sin_func<T>());
    }
    //sin(V)

    template<typename T>
    UnitaryExpression<T, Variable<T>, sin_func> sin(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, sin_func>(e, sin_func<T>());
    }
    //sin(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, sin_func> sin(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, sin_func>(e, sin_func<T>());
    }
    //sin(B)

    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, sin_func> sin(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, sin_func>(e, sin_func<T>());
    }

    //------------cos
    //cos(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, cos_func> cos(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, cos_func>(e, cos_func<T>());
    }
    //cos(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, cos_func> cos(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, cos_func>(e, cos_func<T>());
    }
    //cos(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, cos_func> cos(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, cos_func>(e, cos_func<T>());
    }
    //cos(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, cos_func> cos(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, cos_func>(e, cos_func<T>());
    }

    //------------tan
    //tan(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, tan_func> tan(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, tan_func>(e, tan_func<T>());
    }
    //tan(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, tan_func> tan(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, tan_func>(e, tan_func<T>());
    }
    //tan(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, tan_func> tan(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, tan_func>(e, tan_func<T>());
    }
    //tan(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, tan_func> tan(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, tan_func>(e, tan_func<T>());
    }

    //------------cot
    //cot(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, cot_func> cot(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, cot_func>(e, cot_func<T>());
    }
    //cot(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, cot_func> cot(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, cot_func>(e, cot_func<T>());
    }
    //cot(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, cot_func> cot(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, cot_func>(e, cot_func<T>());
    }
    //cot(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, cot_func> cot(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, cot_func>(e, cot_func<T>());
    }

    //------------sinh
    //sinh(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, sinh_func> sinh(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, sinh_func>(e, sinh_func<T>());
    }
    //sinh(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, sinh_func> sinh(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, sinh_func>(e, sinh_func<T>());
    }
    //sinh(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, sinh_func> sinh(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, sinh_func>(e, sinh_func<T>());
    }
    //sinh(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, sinh_func> sinh(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, sinh_func>(e, sinh_func<T>());
    }

    //------------cosh
    //cosh(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, cosh_func> cosh(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, cosh_func>(e, cosh_func<T>());
    }
    //cosh(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, cosh_func> cosh(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, cosh_func>(e, cosh_func<T>());
    }
    //cosh(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, cosh_func> cosh(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, cosh_func>(e, cosh_func<T>());
    }
    //cosh(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, cosh_func> cosh(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, cosh_func>(e, cosh_func<T>());
    }

    //------------tanh
    //tanh(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, tanh_func> tanh(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, tanh_func>(e, tanh_func<T>());
    }
    //tanh(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, tanh_func> tanh(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, tanh_func>(e, tanh_func<T>());
    }
    //tanh(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, tanh_func> tanh(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, tanh_func>(e, tanh_func<T>());
    }
    //tanh(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, tanh_func> tanh(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, tanh_func>(e, tanh_func<T>());
    }

    //------------coth
    //coth(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, coth_func> coth(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, coth_func>(e, coth_func<T>());
    }
    //coth(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, coth_func> coth(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, coth_func>(e, coth_func<T>());
    }
    //coth(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, coth_func> coth(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, coth_func>(e, coth_func<T>());
    }
    //coth(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, coth_func> coth(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, coth_func>(e, coth_func<T>());
    }

    //-------exp
    //exp(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, exp_func> exp(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, exp_func>(e, exp_func<T>());
    }
    //exp(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, exp_func> exp(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, exp_func>(e, exp_func<T>());
    }
    //exp(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, exp_func> exp(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, exp_func>(e, exp_func<T>());
    }
    //exp(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, exp_func> exp(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, exp_func>(e, exp_func<T>());
    }

    //-------log
    //log(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, log_func> log(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, log_func>(e, log_func<T>());
    }
    //log(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, log_func> log(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, log_func>(e, log_func<T>());
    }
    //log(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, log_func> log(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, log_func>(e, log_func<T>());
    }
    //log(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, log_func> log(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, log_func>(e, log_func<T>());
    }

    //-------log10
    //log10(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, log10_func> log10(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, log10_func>(e, log10_func<T>());
    }
    //log10(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, log10_func> log10(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, log10_func>(e, log10_func<T>());
    }
    //log10(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, log10_func> log10(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, log10_func>(e, log10_func<T>());
    }
    //log10(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, log10_func> log10(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, log10_func>(e, log10_func<T>());
    }

    //-------abs
    //abs(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, abs_func> abs(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, abs_func>(e, abs_func<T>());
    }
    //abs(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, abs_func> abs(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, abs_func>(e, abs_func<T>());
    }
    //abs(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, abs_func> abs(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, abs_func>(e, abs_func<T>());
    }
    //abs(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, abs_func> abs(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, abs_func>(e, abs_func<T>());
    }

    //-------sqrt
    //sqrt(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, sqrt_func> sqrt(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, sqrt_func>(e, sqrt_func<T>());
    }
    //sqrt(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, sqrt_func> sqrt(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, sqrt_func>(e, sqrt_func<T>());
    }
    //sqrt(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, sqrt_func> sqrt(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, sqrt_func>(e, sqrt_func<T>());
    }
    //sqrt(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, sqrt_func> sqrt(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, sqrt_func>(e, sqrt_func<T>());
    }

    //-------asin
    //asin(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, asin_func> asin(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, asin_func>(e, asin_func<T>());
    }
    //asin(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, asin_func> asin(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, asin_func>(e, asin_func<T>());
    }
    //asin(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, asin_func> asin(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, asin_func>(e, asin_func<T>());
    }
    //asin(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, asin_func> asin(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, asin_func>(e, asin_func<T>());
    }

    //-------acos
    //acos(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, acos_func> acos(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, acos_func>(e, acos_func<T>());
    }
    //acos(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, acos_func> acos(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, acos_func>(e, acos_func<T>());
    }
    //acos(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, acos_func> acos(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, acos_func>(e, acos_func<T>());
    }
    //acos(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, acos_func> acos(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, acos_func>(e, acos_func<T>());
    }

    //-------atan
    //atan(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, atan_func> atan(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, atan_func>(e, atan_func<T>());
    }
    //atan(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, atan_func> atan(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, atan_func>(e, atan_func<T>());
    }
    //atan(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, atan_func> atan(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, atan_func>(e, atan_func<T>());
    }
    //atan(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, atan_func> atan(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, atan_func>(e, atan_func<T>());
    }

    //-------acot
    //acot(C)
    template<typename T>
    UnitaryExpression<T, Constant<T>, acot_func> acot(const Constant<T> &e)
    {
        return UnitaryExpression<T, Constant<T>, acot_func>(e, acot_func<T>());
    }
    //acot(V)
    template<typename T>
    UnitaryExpression<T, Variable<T>, acot_func> acot(const Variable<T> &e)
    {
        return UnitaryExpression<T, Variable<T>, acot_func>(e, acot_func<T>());
    }
    //acot(U)
    template<typename T, typename T1, template<typename ELEM> class T2>
    UnitaryExpression<T, UnitaryExpression<T, T1, T2>, acot_func> acot(const UnitaryExpression<T, T1, T2> &e)
    {
        return UnitaryExpression<T, UnitaryExpression<T, T1, T2>, acot_func>(e, acot_func<T>());
    }
    //acot(B)
    template<typename T, typename T1, typename T2, template<typename ELEM> class T3>
    UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, acot_func> acot(const BinaryExpression<T, T1, T2, T3> &e)
    {
        return UnitaryExpression<T, BinaryExpression<T, T1, T2, T3>, acot_func>(e, acot_func<T>());
    }

}


#endif //UNITARY_EXPRESSION_H


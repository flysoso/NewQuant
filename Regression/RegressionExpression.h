#ifndef REGRESSION_EXPRESSION_H
#define REGRESSION_EXPRESSION_H

#include <assert.h>
#include <memory>
#include <vector>

#include "../MathematicsExpresssion/MathExpression.h"

namespace NewQuant
{
    template<typename TYPE> class BaseExpression;

    template<typename TYPE>
    class RegressionExpression
    {
    private:
        std::vector<MathExpression<TYPE> > regr_expr;

    public:
        RegressionExpression(){}

        RegressionExpression(const int &n) :regr_expr(n){}

        ~RegressionExpression(){}

        RegressionExpression<TYPE> & operator << (const Constant<TYPE> &c)
        {
            MathExpression<TYPE> me(c);
            regr_expr.push_back(me);
            return *this;
        }

        RegressionExpression<TYPE> & operator << (const Variable<TYPE> &v)
        {
            MathExpression<TYPE> me(v);
            regr_expr.push_back(me);
            return *this;
        }
        
        template<class ExprT1, class ExprT2, template<typename ELEM> class BinOp>
        RegressionExpression<TYPE> & operator << (const BinaryExpression<TYPE, ExprT1, ExprT2, BinOp> &be)
        {
            MathExpression<TYPE> me(be);
            regr_expr.push_back(me);
            return *this;
        }

        template<class ExprT, template<typename ELEM> class BinOp>
        RegressionExpression<TYPE> & operator << (const UnitaryExpression<TYPE, ExprT, BinOp> &ue)
        {
            MathExpression<TYPE> me(ue);
            regr_expr.push_back(me);
            return *this;
        }

        MathExpression<TYPE> operator () (const int &i) const
        {
            assert(0 < i&&i <= regr_expr.size() + 1);
            return regr_expr[i - 1];
        }

        MathExpression<TYPE> & operator () (const int &i)
        {
            assert(0 < i&&i <= regr_expr.size() + 1);
            return regr_expr[i - 1];
        }

        int Size() const
        {
            return regr_expr.size();
        }


    };

}




#endif //REGRESSION_EXPRESSION_H

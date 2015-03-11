#ifndef INCOMPLETE_BETA_H
#define INCOMPLETE_BETA_H

#include "include.h"
#include "Beta.h"

namespace NewQuant
{
    template<typename TYPE, int MAX_ITER = 60>
    class IncompleteBeta
    {
    protected:
        static Beta<TYPE> beta;

        IncompleteBeta<TYPE, MAX_ITER> & operator = (const IncompleteBeta<TYPE, MAX_ITER> &);

        TYPE Method1(const TYPE &, const TYPE &, const TYPE &) const;
        /*
        compute incomplete_BETA(a, b, x),when x <= (a+1)/(a+b+2)
        */
        TYPE Method2(const TYPE &, const TYPE &, const TYPE &) const;
        /*
        compute incomplete_BETA(a, b, x),when x > (a+1)/(a+b+2)
        */
    public:
        IncompleteBeta(){}

        ~IncompleteBeta(){}

        TYPE operator () (const TYPE &a, const TYPE &b, const TYPE &x) const
        {
            static const TYPE one(1), two(2);

            if (x < (a + one) / (a + b + two))
            {
                return Method1(a, b, x);
            }
            else
            {
                return Method2(a, b, x);
            }

        }
    };

    template<typename TYPE, int MAX_ITER>
    Beta<TYPE> IncompleteBeta<TYPE, MAX_ITER>::beta;

    template<typename TYPE, int MAX_ITER>
    TYPE IncompleteBeta<TYPE, MAX_ITER>::Method1(const TYPE &a, const TYPE &b, const TYPE &x) const
    {
        static const TYPE one(1), zero(0), two(2);
        if (x <= std::numeric_limits<TYPE>::epsilon())
        {
            return zero;
        }
        TYPE d_odd, d_even;
        TYPE P_1, P_2, Q_1, Q_2, P, Q;
        P_1 = one, P_2 = one;
        Q_1 = zero, Q_2 = one;
        int i = 1;
        TYPE k(0), last = one;
        while (true)
        {
            if (i % 2 == 1)
            {
                d_odd = -(a + k)*(a + b + k)*x / ((a + two*k)*(a + two*k + one));
                P = P_2 + d_odd*P_1;
                Q = Q_2 + d_odd*Q_1;
                ++k;
            }
            else
            {
                d_even = k*(b - k)*x / ((a + two*k - one)*(a + two*k));
                P = P_2 + d_even*P_1;
                Q = Q_2 + d_even*Q_1;
            }
            if (fabs((P / Q) - last) <= std::numeric_limits<TYPE>::epsilon() || i > MAX_ITER)
            {
                break;
            }
            P_1 = P_2, Q_1 = Q_2;
            P_2 = P, Q_2 = Q;
            last = P / Q;
            ++i;
        }
        return Q / P*std::exp(a*std::log(x) + b*std::log(one - x)) / a;
    }

    template<typename TYPE, int MAX_ITER>
    TYPE IncompleteBeta<TYPE, MAX_ITER>::Method2(const TYPE &a, const TYPE &b, const TYPE &x) const
    {
        static const TYPE one(1);
        return beta(a, b) - Method1(b, a, one - x);
    }
}

#endif //INCOMPLETE_BETA_H

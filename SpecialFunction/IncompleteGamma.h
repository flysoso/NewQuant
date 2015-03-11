#ifndef INCOMPLETE_GAMMA_H
#define INCOMPLETE_GAMMA_H

#include "include.h"
#include "Gamma.h"

namespace NewQuant
{
    template<typename TYPE, int MAX_ITER = 60>
    class IncompleteGamma
    {
    protected:
        static Gamma<TYPE> gamma;

        IncompleteGamma<TYPE, MAX_ITER> & operator = (const IncompleteGamma<TYPE, MAX_ITER> &);

        TYPE Method1(const TYPE &, const TYPE &) const;
        /*
        compute incomplete_gamma(a, x),when x <= a + 1
        */
        TYPE Method2(const TYPE &, const TYPE &) const;
        /*
        compute incomplete_gamma(a, x),when x > a + 1
        */
    public:
        IncompleteGamma(){}

        ~IncompleteGamma(){}

        TYPE operator () (const TYPE &a, const TYPE &x) const
        {
            static const TYPE one(1);
            if (x <= a + one)
            {
                return Method1(a, x);
            }
            else
            {
                return Method2(a, x);
            }
        }
    };
    template<typename TYPE, int MAX_ITER>
    Gamma<TYPE> IncompleteGamma<TYPE, MAX_ITER>::gamma;

    template<typename TYPE, int MAX_ITER>
    TYPE IncompleteGamma<TYPE, MAX_ITER>::Method1(const TYPE &a, const TYPE &x) const
    {
        static const TYPE one(1),zero(0);
        if (x <= std::numeric_limits<TYPE>::epsilon())
            return zero;
        TYPE l = a*std::log(x) - x;
        TYPE iter = one / a;
        TYPE sum(0), k(1);
        int i = 1;
        while (true)
        {
            sum += iter;
            iter *= x / (a + k);

            if (iter / sum <= std::numeric_limits<TYPE>::epsilon() || i > MAX_ITER)
            {
                break;
            }
            ++k;
            ++i;
        }
        return std::exp(l)*sum;
    }

    template<typename TYPE, int MAX_ITER>
    TYPE IncompleteGamma<TYPE, MAX_ITER>::Method2(const TYPE &a, const TYPE &x) const
    {
        static const TYPE one(1), zero(0);
        TYPE a_even, a_odd, b_even, b_odd;
        a_even = one - a, a_odd = one;
        b_even = x, b_odd = one;
        TYPE P_1, P_2, Q_1, Q_2, P, Q, last;
        P_1 = one, P_2 = b_even;
        Q_1 = zero, Q_2 = one;
        last = x;
        int k = 1;
        while (true)
        {
            if (k % 2 == 1)
            {
                P = b_odd*P_2 + a_even*P_1;
                Q = b_odd*Q_2 + a_even*Q_1;
                ++a_even;
            }
            else
            {
                P = b_even*P_2 + a_odd*P_1;
                Q = b_even*Q_2 + a_odd*Q_1;
                ++a_odd;
            }

            if (fabs((P / Q) - last) <= std::numeric_limits<TYPE>::epsilon() || k > MAX_ITER)
            {
                break;
            }
            ++k;
            P_1 = P_2, Q_1 = Q_2;
            P_2 = P, Q_2 = Q;
            last = P / Q;
        }

        return gamma(a) - Q / P*std::exp(a*std::log(x) - x);
    }
}

#endif //INCOMPLETE_GAMMA_H

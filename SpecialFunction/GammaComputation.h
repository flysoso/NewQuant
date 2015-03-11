#ifndef GAMMA_COMPUTATION_H
#define GAMMA_COMPUTATION_H

#include "include.h"

namespace NewQuant
{
    template<typename TYPE>
    class GammaComputation
    {
    protected:
        static TYPE coefficient1[];
        static TYPE coefficient2[];
        static TYPE up_bound;
        GammaComputation<TYPE> & operator = (const GammaComputation<TYPE> &);

        TYPE Method1(const TYPE &, const TYPE &, const TYPE &) const;
        /*
        compute gamma(x),when x is not large
        */
        TYPE Method2(const TYPE &) const;
        /*
        compute lngamma(x),when x is blarge
        */
    public:
        GammaComputation(){}

        ~GammaComputation(){}

        TYPE operator () (const TYPE &) const;
    };

    template<typename TYPE>
    TYPE GammaComputation<TYPE>::coefficient1[26] = {
        static_cast<TYPE>(+1.0000000000000000),
        static_cast<TYPE>(+0.5772156649015329),
        static_cast<TYPE>(-0.6558780715202538),
        static_cast<TYPE>(-0.0420026350340952),
        static_cast<TYPE>(+0.1665386113822915),
        static_cast<TYPE>(-0.0421977345555443),
        static_cast<TYPE>(-0.0096219715278770),
        static_cast<TYPE>(+0.0072189432466630),
        static_cast<TYPE>(-0.0011651675918591),
        static_cast<TYPE>(-0.0002152416741149),
        static_cast<TYPE>(+0.0001280502823882),
        static_cast<TYPE>(-0.0000201348547807),
        static_cast<TYPE>(-0.0000012504934821),
        static_cast<TYPE>(+0.0000011330272320),
        static_cast<TYPE>(-0.0000002056338417),
        static_cast<TYPE>(+0.0000000061160950),
        static_cast<TYPE>(+0.0000000050020075),
        static_cast<TYPE>(-0.0000000011812746),
        static_cast<TYPE>(+0.0000000001043427),
        static_cast<TYPE>(+0.0000000000077823),
        static_cast<TYPE>(-0.0000000000036968),
        static_cast<TYPE>(+0.0000000000005100),
        static_cast<TYPE>(-0.0000000000000206),
        static_cast<TYPE>(-0.0000000000000054),
        static_cast<TYPE>(+0.0000000000000014),
        static_cast<TYPE>(+0.0000000000000001) };

    template<typename TYPE>
    TYPE GammaComputation<TYPE>::coefficient2[10] = {
        static_cast<TYPE>(+8.333333333333333e-2),
        static_cast<TYPE>(-2.777777777777778e-3),
        static_cast<TYPE>(+7.936507936507937e-4),
        static_cast<TYPE>(-5.952380952380952e-4),
        static_cast<TYPE>(+8.417508417508418e-4),
        static_cast<TYPE>(-1.917526917526918e-3),
        static_cast<TYPE>(+6.410256410256410e-3),
        static_cast<TYPE>(-2.955065359477124e-2),
        static_cast<TYPE>(+1.796443723688307e-1),
        static_cast<TYPE>(-1.392432216905900) };

    template<typename TYPE>
    TYPE GammaComputation<TYPE>::up_bound(10);

    template<typename TYPE>
    TYPE GammaComputation<TYPE>::Method1(const TYPE &diff, const TYPE &x, const TYPE &y) const
    {
        static const TYPE one(1), half(0.5);
        TYPE r = diff * HornerMethod(coefficient1, 25, diff);
        if (r > std::numeric_limits<TYPE>::epsilon())
        {
            r = one / r;
            for (TYPE i = one; i <= y + half; ++i)
            {
                r *= x - i;
            }
        }
        else
        {
            r = one;
            for (TYPE i = one; i <= x - half; ++i)
            {
                r *= i;
            }
        }

        return r;
    }

    template<typename TYPE>
    TYPE GammaComputation<TYPE>::Method2(const TYPE &x) const
    {
        static const TYPE half(0.5), one(1), two(2);
        TYPE y = one / x;
        y = y*y;
        TYPE r = (x - half)*std::log(x) - x + half*std::log(two * Pi<TYPE>::value());
        r += x * y*HornerMethod(coefficient2, 9, y);
        return r;
    }
}

#endif //GAMMA_COMPUTATION_H

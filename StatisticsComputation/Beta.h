#ifndef SC_BETA_H
#define SC_BETA_H

#include "../SpecialFunction/IncompleteBeta.h"
#include "../SpecialFunction/Beta.h"

namespace NewQuant
{
    template<typename TYPE>
    class BetaPdf
    {
    private:
        static Beta<TYPE> beta;

        BetaPdf<TYPE> & operator = (const BetaPdf<TYPE> &);
    public:
        BetaPdf(){}

        ~BetaPdf(){}

        TYPE operator () (const TYPE &a, const TYPE &b, const TYPE &x) const
        {
            static const TYPE one(1);
            TYPE r = (a - one)*std::log(x) + (b - one)*std::log(one - x);
            return std::exp(r) / beta(a, b);
        }
    };

    template<typename TYPE>
    Beta<TYPE> BetaPdf<TYPE>::beta;

    template<typename TYPE>
    class BetaCdf
    {
    private:
        static IncompleteBeta<TYPE> incomplete_beta;
        static Beta<TYPE> beta;

        BetaCdf<TYPE> & operator = (const BetaCdf<TYPE> &);
    public:
        BetaCdf(){}

        ~BetaCdf(){}

        TYPE operator () (const TYPE &a, const TYPE &b, const TYPE &x) const
        {
            return incomplete_beta(a, b, x) / beta(a, b);
        }
    };

    template<typename TYPE>
    IncompleteBeta<TYPE> BetaCdf<TYPE>::incomplete_beta;

    template<typename TYPE>
    Beta<TYPE> BetaCdf<TYPE>::beta;

    template<typename TYPE, int MAX_ITER = 60>
    class BetaQuantile
    {
    private:
        static BetaCdf<TYPE> cdf;
        static BetaPdf<TYPE> pdf;

        BetaQuantile<TYPE, MAX_ITER> & operator = (const BetaQuantile<TYPE, MAX_ITER> &);
    public:
        BetaQuantile(){}

        ~BetaQuantile(){}

        TYPE operator () (const TYPE &a, const TYPE &b, const TYPE &p) const
        {
            static const TYPE zero(0), one(1), two(2);
            if (p <= std::numeric_limits<TYPE>::epsilon())
            {
                return zero;
            }
            TYPE low = zero, up = one, mid;
            int i = 1;
            
            while (true)
            {
                mid = (up + low) / two;
                if (cdf(a, b, mid) < p)
                {
                    low = mid;
                }
                else
                {
                    up = mid;
                }
                if (fabs(up - low) <= std::numeric_limits<TYPE>::epsilon() || i > MAX_ITER)
                {
                    break;
                }
                ++i;
            }
            return mid;
        }
    };

    template<typename TYPE, int MAX_ITER>
    BetaCdf<TYPE> BetaQuantile<TYPE, MAX_ITER>::cdf;

    template<typename TYPE, int MAX_ITER>
    BetaPdf<TYPE> BetaQuantile<TYPE, MAX_ITER>::pdf;

}



#endif //SC_BETA_H

#ifndef SC_GAMMA_H
#define SC_GAMMA_H

#include "../SpecialFunction/IncompleteGamma.h"
#include "../SpecialFunction/LnGamma.h"

namespace NewQuant
{
    template<typename TYPE>
    class GammaPdf
    {
    private:
        static LnGamma<TYPE> ln_gamma;

        GammaPdf<TYPE> & operator = (const GammaPdf<TYPE> &);
    public:
        GammaPdf(){}

        ~GammaPdf(){}

        TYPE operator () (const TYPE &a, const TYPE &b, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE r = a*std::log(b) + (a - one)*std::log(x) - b*x - ln_gamma(a);
            return std::exp(r);
        }
    };

    template<typename TYPE>
    LnGamma<TYPE> GammaPdf<TYPE>::ln_gamma;

    template<typename TYPE>
    class GammaCdf
    {
    private:
        static IncompleteGamma<TYPE> incomplete_gamma;
        static LnGamma<TYPE> ln_gamma;

        GammaCdf<TYPE> & operator = (const GammaCdf<TYPE> &);
    public:
        GammaCdf(){}

        ~GammaCdf(){}

        TYPE operator () (const TYPE &a, const TYPE &b, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE r = std::log(incomplete_gamma(a, b*x)) - ln_gamma(a);
            return std::exp(r);
        }
    };

    template<typename TYPE>
    IncompleteGamma<TYPE> GammaCdf<TYPE>::incomplete_gamma;

    template<typename TYPE>
    LnGamma<TYPE> GammaCdf<TYPE>::ln_gamma;

    template<typename TYPE, int MAX_ITER = 60>
    class GammaQuantile
    {
    private:
        static GammaCdf<TYPE> cdf;
        static GammaPdf<TYPE> pdf;

        GammaQuantile<TYPE, MAX_ITER> & operator = (const GammaQuantile<TYPE, MAX_ITER> &);
    public:
        GammaQuantile(){}

        ~GammaQuantile(){}

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
                if (cdf(a, b, up) <= p)
                {
                    up += up;
                }
                else
                {
                    break;
                }
            }

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
    GammaCdf<TYPE> GammaQuantile<TYPE, MAX_ITER>::cdf;

    template<typename TYPE, int MAX_ITER>
    GammaPdf<TYPE> GammaQuantile<TYPE, MAX_ITER>::pdf;

}


#endif //SC_GAMMA_H

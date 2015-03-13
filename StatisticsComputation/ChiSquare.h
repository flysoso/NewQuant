#ifndef CHI_SQUARE_H
#define CHI_SQUARE_H

#include "Gamma.h"
#include "../SpecialFunction/LnGamma.h"

namespace NewQuant
{
    template<typename TYPE>
    class ChiSquarePdf
    {
    private:
        static LnGamma<TYPE> ln_gamma;

        ChiSquarePdf<TYPE> & operator = (const ChiSquarePdf<TYPE> &);
    public:
        ChiSquarePdf(){}

        ~ChiSquarePdf(){}

        TYPE operator () (const TYPE &free, const TYPE &x) const
        {
            static const TYPE two(2);
            TYPE r = (free*std::log(x / two) - x) / two - std::log(x) - ln_gamma(free / two);
            return std::exp(r);
        }
    };

    template<typename TYPE>
    LnGamma<TYPE> ChiSquarePdf<TYPE>::ln_gamma;

    template<typename TYPE>
    class ChiSquareCdf
    {
    private:
        static GammaCdf<TYPE> gamma_cdf;

        ChiSquareCdf<TYPE> & operator = (const ChiSquareCdf<TYPE> &);
    public:
        ChiSquareCdf(){}

        ~ChiSquareCdf(){}

        TYPE operator () (const TYPE &free, const TYPE &x) const
        {
            static const TYPE two(2), one(1);
            return gamma_cdf(free / two, one, x / two);
        }
    };

    template<typename TYPE>
    GammaCdf<TYPE> ChiSquareCdf<TYPE>::gamma_cdf;

    template<typename TYPE>
    class ChiSquareQuantile
    {
    private:
        static GammaQuantile<TYPE> gamma_q;

        ChiSquareQuantile<TYPE> & operator = (const ChiSquareQuantile<TYPE> &);
    public:
        ChiSquareQuantile(){}

        ~ChiSquareQuantile(){}

        TYPE operator () (const TYPE &free, const TYPE &p) const
        {
            static const TYPE two(2), one(1);
            return two*gamma_q(free / two, one, p);
        }
    };

    template<typename TYPE>
    GammaQuantile<TYPE> ChiSquareQuantile<TYPE>::gamma_q;


}


#endif //CHI_SQUARE_H

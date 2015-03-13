#ifndef WEIBULL_H
#define WEIBULL_H

#include "../SpecialFunction/include.h"

namespace NewQuant
{
    template<typename TYPE>
    class WeibullPdf
    {
    private:
        WeibullPdf<TYPE> & operator = (const WeibullPdf<TYPE> &);
    public:
        WeibullPdf(){}

        ~WeibullPdf(){}

        TYPE operator () (const TYPE &alpha, const TYPE &beta, const TYPE &x) const
        {
            static const TYPE one(1);
            TYPE r = (alpha - one)*std::log(x) - alpha*std::log(beta) - std::pow(x / beta, alpha);
            return alpha*std::exp(r);
        }
    };

    template<typename TYPE>
    class WeibullCdf
    {
    private:
        WeibullCdf<TYPE> & operator = (const WeibullCdf<TYPE> &);
    public:
        WeibullCdf(){}

        ~WeibullCdf(){}

        TYPE operator () (const TYPE &alpha, const TYPE &beta, const TYPE &x) const
        {
            static const TYPE one(1);
            return one - std::exp(-std::pow(x / beta, alpha));
        }
    };

    template<typename TYPE>
    class WeibullQuantile
    {
    private:
        WeibullQuantile<TYPE> & operator = (const WeibullQuantile<TYPE> &);
    public:
        WeibullQuantile(){}

        ~WeibullQuantile(){}

        TYPE operator () (const TYPE &alpha, const TYPE &beta, const TYPE &p) const
        {
            static const TYPE one(1);
            return beta*(std::pow(std::log(one - p), one / alpha));
        }
    };
}

#endif //WEIBULL_H

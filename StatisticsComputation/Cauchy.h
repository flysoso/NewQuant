#ifndef CAUCHY_H
#define CAUCHY_H

#include "../SpecialFunction/include.h"

namespace NewQuant
{
    template<typename TYPE>
    class CauchyPdf
    {
    private:
        CauchyPdf<TYPE> & operator = (const CauchyPdf<TYPE> &);
    public:
        CauchyPdf(){}

        ~CauchyPdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1);
            TYPE norm = (x - mu) / sigma;
            TYPE p = Pi<TYPE>::value()*sigma;
            return one / (p*(one + norm*norm));
        }
    };

    template<typename TYPE>
    class CauchyCdf
    {
    private:
        CauchyCdf<TYPE> & operator = (const CauchyCdf<TYPE> &);
    public:
        CauchyCdf(){}

        ~CauchyCdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE half(0.5);
            TYPE norm = (x - mu) / sigma;
            return half + std::atan(norm) / Pi<TYPE>::value();
        }
    };

    template<typename TYPE>
    class CauchyQuantile
    {
    private:
        CauchyQuantile<TYPE> & operator = (const CauchyQuantile<TYPE> &);
    public:
        CauchyQuantile(){}

        ~CauchyQuantile(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &p) const
        {
            static const TYPE half(0.5);
            return mu + sigma*std::tan(Pi<TYPE>::value()*(p - half));
        }
    };

}



#endif //CAUCHY_H

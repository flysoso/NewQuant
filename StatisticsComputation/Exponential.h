#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include"../SpecialFunction/include.h"

namespace NewQuant
{
    template<typename TYPE>
    class ExponentialPdf
    {
    private:
        ExponentialPdf<TYPE> & operator = (const ExponentialPdf<TYPE> &);
    public:
        ExponentialPdf(){}

        ~ExponentialPdf(){}

        TYPE operator () (const TYPE &beta, const TYPE &x) const
        {
            return beta*std::exp(-beta*x);
        }
    };

    template<typename TYPE>
    class ExponentialCdf
    {
    private:
        ExponentialCdf<TYPE> & operator = (const ExponentialCdf<TYPE> &);
    public:
        ExponentialCdf(){}

        ~ExponentialCdf(){}

        TYPE operator () (const TYPE &beta, const TYPE &x) const
        {
            return one - std::exp(-beta*x);
        }
    };

    template<typename TYPE>
    class ExponentialQuantile
    {
    private:
        ExponentialQuantile<TYPE> & operator = (const ExponentialQuantile<TYPE> &);
    public:
        ExponentialQuantile(){}

        ~ExponentialQuantile(){}

        TYPE operator () (const TYPE &beta, const TYPE &p) const
        {
            static const TYPE one(1);
            return -std::log(one - p) / beta;
        }
    };

}

#endif //EXPONENTIAL_H


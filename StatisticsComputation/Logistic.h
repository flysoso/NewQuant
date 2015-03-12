#ifndef LOGISTIC_H
#define LOGISTIC_H

#include "../SpecialFunction/include.h"

namespace NewQuant
{
    template<typename TYPE>
    class LogisticPdf
    {
    private:
        LogisticPdf<TYPE> & operator = (const LogisticPdf<TYPE> &);
    public:
        LogisticPdf(){}

        ~LogisticPdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE two(2), three(3), four(4);
            TYPE sqrt_3 = std::sqrt(three);
            TYPE norm = Pi<TYPE>::value()*(x - mu) / (sigma * two * sqrt_3);
            TYPE p = Pi<TYPE>::value() / (four*sigma*sqrt_3);
            return p*std::sch(norm)*std::sch(norm);
        }
    };

    template<typename TYPE>
    class LogisticCdf
    {
    private:
        LogisticCdf<TYPE> & operator = (const LogisticCdf<TYPE> &);
    public:
        LogisticCdf(){}

        ~LogisticCdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1), three(3);
            TYPE sqrt_3 = std::sqrt(three);
            TYPE norm = -Pi<TYPE>::value()*(x - mu) / (sigma * sqrt_3);
            return one / (one + std::exp(norm));
        }
    };

    template<typename TYPE>
    class LogisticQuantile
    {
    private:
        LogisticQuantile<TYPE> & operator = (const LogisticQuantile<TYPE> &);
    public:
        LogisticQuantile(){}

        ~LogisticQuantile(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &p) const
        {
            static const TYPE one(1), three(3);
            TYPE sqrt_3 = std::sqrt(three);
            return mu + sqrt_3*std::log(p / (one - p)) * sigma / Pi<TYPE>::value();
        }
    };

}

#endif //LOGISTIC_H

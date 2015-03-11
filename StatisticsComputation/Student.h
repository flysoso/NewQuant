#ifndef STUDENT_H
#define STUDENT_H

#include "../SpecialFunction/LnGamma.h"
#include "Beta.h"

namespace NewQuant
{
    template<typename TYPE>
    class StudentPdf
    {
    private:
        static LnGamma<TYPE> ln_gamma;

        StudentPdf<TYPE> & operator = (const StudentPdf<TYPE> &);
    public:
        StudentPdf(){}

        ~StudentPdf(){}

        TYPE operator () (const TYPE &free, const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE norm = (x - mu) / sigma;
            TYPE p = std::sqrt(Pi<TYPE>::value()*free)*sigma;
            TYPE r = LnGamma((free + one) / two) - LnGamma(free / two) - (free + one) / two*std::log(one + norm*norm / free);
            return std::exp(r) / p;
        }
    };

    template<typename TYPE>
    LnGamma<TYPE> StudentPdf<TYPE>::ln_gamma;

    template<typename TYPE>
    class StudentCdf
    {
    private:
        static BetaCdf<TYPE> beta_cdf;

        StudentCdf<TYPE> & operator = (const StudentCdf<TYPE> &);
    public:
        StudentCdf(){}

        ~StudentCdf(){}

        TYPE operator () (const TYPE &free, const TYPE &mu, const TYPE &sigma, const TYPE &t) const
        {
            static const TYPE half(0.5), one(1);
            TYPE norm = (t - mu) / sigma;
            TYPE x = free / (free + norm*norm);
            if (t <= mu)
            {
                return half*beta_cdf(half*free, half, x);
            }
            else
            {
                return one - half*beta_cdf(half*free, half, x);
            }
        }
    };

    template<typename TYPE>
    BetaCdf<TYPE> StudentCdf<TYPE>::beta_cdf;


    template<typename TYPE>
    class StudentQuantile
    {
    private:
        static BetaQuantile<TYPE> beta_q;

        StudentQuantile<TYPE> & operator = (const StudentQuantile<TYPE> &);
    public:
        StudentQuantile(){}

        ~StudentQuantile(){}

        TYPE operator () (const TYPE &free, const TYPE &mu, const TYPE &sigma, const TYPE &p) const
        {
            static const TYPE half(0.5), one(1),two(2);
            TYPE x, t;
            if (p <= half)
            {
                x = beta_q(half*free, half, two*p);
                t = mu - sigma*std::sqrt(free / x - free);
            }
            else
            {
                x = beta_q(half*free, half, two*(one - p));
                t = mu + sigma*std::sqrt(free / x - free);
            }
            return t;
        }
    };

    template<typename TYPE>
    BetaQuantile<TYPE> StudentQuantile<TYPE>::beta_q;


}



#endif //STUDENT_H

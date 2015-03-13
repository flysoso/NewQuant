#ifndef F_H
#define F_H

#include "../SpecialFunction/Beta.h"
#include "Beta.h"

namespace NewQuant
{
    template<typename TYPE>
    class F_Pdf
    {
    private:
        static Beta<TYPE> beta;

        F_Pdf<TYPE> & operator = (const F_Pdf<TYPE> &);
    public:
        F_Pdf(){}

        ~F_Pdf(){}

        TYPE operator () (const TYPE &v1, const TYPE &v2, const TYPE &x) const
        {
            static const TYPE half(0.5), two(2);
            TYPE r = (v1*std::log(v1) + v2*std::log(v2) + v1*std::log(x)) / two - std::log(x) - half*(v1 + v2)*std::log(v2 + v1*x);
            return std::exp(r) / beta(half*v1, half*v2);
        }
    };

    template<typename TYPE>
    Beta<TYPE> F_Pdf<TYPE>::beta;

    template<typename TYPE>
    class F_Cdf
    {
    private:
        static BetaCdf<TYPE> beta_cdf;

        F_Cdf<TYPE> & operator = (const F_Cdf<TYPE> &);
    public:
        F_Cdf(){}

        ~F_Cdf(){}

        TYPE operator () (const TYPE &v1, const TYPE &v2, const TYPE &x) const
        {
            static const TYPE half(0.5);
            TYPE y = v1*x / (v2 + v1*x);
            return beta_cdf(half*v1, half*v2, y);
        }
    };

    template<typename TYPE>
    BetaCdf<TYPE> F_Cdf<TYPE>::beta_cdf;

    template<typename TYPE>
    class F_Quantile
    {
    private:
        static BetaQuantile<TYPE> beta_q;

        F_Quantile<TYPE> & operator = (const F_Quantile<TYPE> &);
    public:
        F_Quantile(){}

        ~F_Quantile(){}

        TYPE operator () (const TYPE &v1, const TYPE &v2, const TYPE &p) const
        {
            static const TYPE half(0.5), one(1);
            TYPE u = beta_q(half*v1, half*v2, p);
            return v2*u / (v1*(one - u));
        }
    };

    template<typename TYPE>
    BetaQuantile<TYPE> F_Quantile<TYPE>::beta_q;

}



#endif //F_H


#ifndef LN_NORMAL_H
#define LN_NORMAL_H

#include "../SpecialFunction/ErrorFunction.h"
#include "../SpecialFunction/ComplementErrorFunction.h"

namespace NewQuant
{
    template<typename TYPE>
    class LnNormalPdf
    {
    private:
        LnNormalPdf<TYPE> & operator = (const LnNormalPdf<TYPE> &);
    public:
        LnNormalPdf(){}

        ~LnNormalPdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE norm = (std::log(x) - mu) / sigma;
            TYPE p = one / (std::sqrt(two*Pi<TYPE>::value())*sigma*x);
            return p*std::exp(-norm*norm / two);
        }
    };

    template<typename TYPE>
    class LnNormalCdf
    {
    private:
        static ErrorFunction<TYPE> error_function;

        LnNormalCdf<TYPE> & operator = (const LnNormalCdf<TYPE> &);
    public:
        LnNormalCdf(){}

        ~LnNormalCdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE norm = (std::log(x) - mu) / sigma;
            return (one - error_function(-norm / std::sqrt(two))) / two;
        }
    };

    template<typename TYPE>
    ErrorFunction<TYPE> LnNormalCdf<TYPE>::error_function;

    template<typename TYPE>
    class LnNormalQuantile
    {
    private:
        static InvComplementErrorFunction<TYPE> inv_com_error;

        LnNormalQuantile<TYPE> & operator = (const LnNormalQuantile<TYPE> &);
    public:
        LnNormalQuantile(){}

        ~LnNormalQuantile(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &p) const
        {
            static const TYPE two(2);
            return std::exp(mu - std::sqrt(two)*sigma*inv_com_error(two*p));
        }
    };

    template<typename TYPE>
    InvComplementErrorFunction<TYPE> LnNormalQuantile<TYPE>::inv_com_error;


}



#endif //LN_NORMAL_H

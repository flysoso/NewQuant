#ifndef SC_NORMAL_H
#define SC_NORMAL_H

#include "../SpecialFunction/ErrorFunction.h"
#include "../SpecialFunction/ComplementErrorFunction.h"

namespace NewQuant
{
    template<typename TYPE>
    class NormalPdf
    {
    private:
        NormalPdf<TYPE> & operator = (const NormalPdf<TYPE> &);
    public:
        NormalPdf(){}

        ~NormalPdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE norm = (x - mu) / sigma;
            TYPE p = one / (std::sqrt(two*Pi<TYPE>::value())*sigma);
            return p*std::exp(-norm*norm / two);
        }
    };

    template<typename TYPE>
    class NormalCdf
    {
    private:
        static ErrorFunction<TYPE> error_function;

        NormalCdf<TYPE> & operator = (const NormalCdf<TYPE> &);
    public:
        NormalCdf(){}

        ~NormalCdf(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &x) const
        {
            static const TYPE one(1), two(2);
            TYPE norm = (x - mu) / sigma;
            return (one - error_function(-norm / std::sqrt(two))) / two;
        }
    };

    template<typename TYPE>
    ErrorFunction<TYPE> NormalCdf<TYPE>::error_function;

    template<typename TYPE>
    class NormalQuantile
    {
    private:
        static InvComplementErrorFunction<TYPE> inv_com_error;

        NormalQuantile<TYPE> & operator = (const NormalQuantile<TYPE> &);
    public:
        NormalQuantile(){}

        ~NormalQuantile(){}

        TYPE operator () (const TYPE &mu, const TYPE &sigma, const TYPE &p) const
        {
            static const TYPE two(2);
            return mu - std::sqrt(two)*sigma*inv_com_error(two*p);
        }
    };

    template<typename TYPE>
    InvComplementErrorFunction<TYPE> NormalQuantile<TYPE>::inv_com_error;


}



#endif //SC_NORMAL_H

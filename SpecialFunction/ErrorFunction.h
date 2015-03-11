#ifndef ERROR_FUNCTION_H
#define ERROR_FUNCTION_H

#include "IncompleteGamma.h"
#include "ComplementErrorFunction.h"

namespace NewQuant
{
    template<typename TYPE, int MAX_ITER> class InvComplementErrorFunction;

    template<typename TYPE, int MAX_ITER = 60>
    class ErrorFunction
    {
    private:
        static IncompleteGamma<TYPE, MAX_ITER> incomplete_gamma;
        static TYPE half;
        ErrorFunction<TYPE, MAX_ITER> & operator = (const ErrorFunction<TYPE, MAX_ITER> &);
    public:
        ErrorFunction(){}

        ~ErrorFunction(){}

        TYPE operator () (const TYPE &x) const
        {
            static const TYPE zero(0);
            if (x >= zero)
            {
                return incomplete_gamma(half, x*x) / std::sqrt(Pi<TYPE>::value());
            }
            else
            {
                return -incomplete_gamma(half, x*x) / std::sqrt(Pi<TYPE>::value());
            }
        }
    };

    template<typename TYPE, int MAX_ITER>
    IncompleteGamma<TYPE, MAX_ITER> ErrorFunction<TYPE, MAX_ITER>::incomplete_gamma;

    template<typename TYPE, int MAX_ITER>
    TYPE ErrorFunction<TYPE, MAX_ITER>::half(0.5);

    /**/

    template<typename TYPE, int MAX_ITER = 60>
    class InvErrorFunction
    {
    private:
        static InvComplementErrorFunction<TYPE, MAX_ITER> invcomplement_error;

        InvErrorFunction<TYPE, MAX_ITER> & operator = (const InvErrorFunction<TYPE, MAX_ITER> &);
    public:
        InvErrorFunction(){}

        ~InvErrorFunction(){}

        TYPE operator () (const TYPE &p) const
        {
            static const TYPE one(1);
            assert(p < one && p > -one);
            return invcomplement_error(one - p);
        }
    };

    template<typename TYPE, int MAX_ITER>
    InvComplementErrorFunction<TYPE, MAX_ITER> InvErrorFunction<TYPE, MAX_ITER>::invcomplement_error;
}

#endif //ERROR_FUNCTION_H


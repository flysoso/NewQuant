#ifndef COMPLEMENT_ERROR_FUNCTION_H
#define COMPLEMENT_ERROR_FUNCTION_H

#include "ErrorFunction.h"

namespace NewQuant
{
    template<typename TYPE, int MAX_ITER> class ErrorFunction;
    template<typename TYPE, int MAX_ITER = 60>
    class ComplementErrorFunction
    {
    private:
        static ErrorFunction<TYPE, MAX_ITER> error_function;

        ComplementErrorFunction<TYPE, MAX_ITER> & operator = (const ComplementErrorFunction<TYPE, MAX_ITER> &);
    public:
        ComplementErrorFunction(){}

        ~ComplementErrorFunction(){}

        TYPE operator () (const TYPE &x) const
        {
            static const TYPE one(1);
            return one - error_function(x);
        }
    };

    template<typename TYPE, int MAX_ITER>
    ErrorFunction<TYPE, MAX_ITER> ComplementErrorFunction<TYPE, MAX_ITER>::error_function;

    template<typename TYPE, int MAX_ITER = 60>
    class InvComplementErrorFunction
    {
    private:
        static ComplementErrorFunction<TYPE, MAX_ITER> complement_error;

        InvComplementErrorFunction<TYPE, MAX_ITER> & operator = (const InvComplementErrorFunction<TYPE, MAX_ITER> &);
    public:
        InvComplementErrorFunction(){}

        ~InvComplementErrorFunction(){}

        TYPE operator () (const TYPE &p) const
        {
            static const TYPE one(1), two(2), zero(0);
            assert(p > zero && p < two);
            TYPE x(1), y;
            TYPE c = two / std::sqrt(Pi<TYPE>::value());
            int i = 1;
            while (true)
            {
                y = x - (complement_error(x) - p) / ((complement_error(x) - p)*x - std::exp(-x*x));
                if (fabs(x - y) <= std::numeric_limits<TYPE>::epsilon() || i > MAX_ITER)
                {
                    break;
                }
                x = y;
                ++i;
            }
            return y;
        }
    };

    template<typename TYPE, int MAX_ITER>
    ComplementErrorFunction<TYPE, MAX_ITER> InvComplementErrorFunction<TYPE, MAX_ITER>::complement_error;


}




#endif //COMPLEMENT_ERROR_FUNCTION_H

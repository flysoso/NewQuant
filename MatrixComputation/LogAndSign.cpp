#ifndef LOGANDSIGN_CPP
#define LOGANDSIGN_CPP

#include "LogAndSign.h"

namespace NewQuant
{
    template<typename TYPE>
    LogAndSign<TYPE>::LogAndSign(const TYPE &f)
    {
        static const TYPE zero(0);
        if (f == zero)
        {
            log_val = zero;
            sign_val = 0;
            return;
        }
        else if (f < zero)
        {
            sign_val = -1;
            log_val = std::log(-f);
        }
        else
        {
            sign_val = 1;
            log_val = std::log(f);
        }
    }

    template<typename TYPE>
    void LogAndSign<TYPE>::operator*=(const TYPE &x)
    {
        static const TYPE zero(0);
        if (x > zero)
        {
            log_val += std::log(x);
        }
        else if (x < zero)
        {
            log_val += std::log(-x);
            sign_val = -sign_val;
        }
        else
        {
            sign_val = 0;
        }
    }

    template<typename TYPE>
    void LogAndSign<TYPE>::PowEq(const int &k)
    {
        if (sign_val)
        {
            log_val *= TYPE(k);
            if ((k & 1) == 0)
                sign_val = 1;
        }
    }

    template<typename TYPE>
    TYPE LogAndSign<TYPE>::Value() const
    {
        if (log_val >= FloatingPointPrecision<TYPE>::LnMaximum())
        {
            Singleton<Tracer>::Instance()->AddMessage("LogAndSign::Value");
            throw OverflowException("Overflow in exponential");
        }
        return TYPE(sign_val) * exp(log_val);
    }
}
#endif //LOGANDSIGN_CPP

#ifndef LOGANDSIGN_H
#define LOGANDSIGN_H

#include <math.h>
#include "include.h"
#include "FloatingPointPrecision.h"
#include "../ExceptionClass/OverflowException.h"

/// Return from LogDeterminant function.
/// Members are the log of the absolute value and the sign (+1, -1 or 0)
template <typename TYPE>
class LogAndSign
{
private:
    TYPE log_val;
    int sign_val;
public:
    LogAndSign() : log_val(0), sign_val(1) {}

    LogAndSign(const TYPE &);

    void operator*=(const TYPE &);          //<- multiply by a real

    void PowEq(const int &);                //<- raise to power of k

    void ChangeSign()
    {
        sign_val = -sign_val;
    }

    const TYPE & LogValue() const
    {
        return log_val;
    }

    const int & Sign() const
    {
        return sign_val;
    }

    TYPE Value() const;             //<- the value
};

#include "LogAndSign.cpp"

#endif //LOGANDSIGN_H

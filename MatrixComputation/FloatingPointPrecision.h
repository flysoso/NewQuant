#ifndef FLOATING_POINT_PRECISION_H
#define FLOATING_POINT_PRECISION_H

#include "include.h"
#include <limits>
#include <math.h>

namespace NewQuant
{
    /// Floating point precision.
    template<typename TYPE>
    class FloatingPointPrecision
    {
    public:
        static int Dig()              // number of decimal digits or precision
        {
            return std::numeric_limits<TYPE>::digits10;
        }

        static TYPE Epsilon()         // smallest number such that 1+Eps!=Eps
        {
            return std::numeric_limits<TYPE>::epsilon();
        }

        static int Mantissa()         // bits in mantisa
        {
            return std::numeric_limits<TYPE>::digits;
        }

        static TYPE Maximum()         // maximum value
        {
            return std::numeric_limits<TYPE>::max();
        }

        static int MaximumDecimalExponent()  // maximum decimal exponent
        {
            return std::numeric_limits<TYPE>::max_exponent10;
        }

        static int MaximumExponent()  // maximum binary exponent
        {
            return std::numeric_limits<TYPE>::max_exponent;
        }

        static TYPE LnMaximum()       // natural log of maximum
        {
            return (TYPE)log(Maximum());
        }

        static TYPE Minimum()         // minimum positive value
        {
            return std::numeric_limits<TYPE>::min();
        }

        static int MinimumDecimalExponent() // minimum decimal exponent
        {
            return std::numeric_limits<TYPE>::min_exponent10;
        }

        static int MinimumExponent()  // minimum binary exponent
        {
            return std::numeric_limits<TYPE>::min_exponent;
        }

        static TYPE LnMinimum()       // natural log of minimum
        {
            return (TYPE)log(Minimum());
        }

        static int Radix()            // exponent radix
        {
            return std::numeric_limits<TYPE>::radix;
        }

        static int Rounds()           // addition rounding (1 = does round)
        {
            return std::numeric_limits<TYPE>::round_style == std::round_to_nearest ? 1 : 0;
        }
    };
}

#endif //FLOATING_POINT_PRECISION_H


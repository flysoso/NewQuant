#ifndef INCLUDE_H
#define INCLUDE_H

#include <memory>
#include <limits>
#include <iostream>
#include <assert.h>

namespace NewQuant
{
    template<typename TYPE>
    inline TYPE square(const TYPE &x)
    {
        return x*x;
    }

    template<>
    inline int square(const int &x)
    {
        return x*x;
    }

    inline int tristore(const int &n)                    // elements in triangular matrix
    {
        return (n*(n + 1)) / 2;
    }

    template<typename TYPE>
    void NewQuantBlockCopy(int n, TYPE* from, TYPE* to)
    {
        int i = (n >> 3);
        while (i--)
        {
            *to++ = *from++;
            *to++ = *from++;
            *to++ = *from++;
            *to++ = *from++;
            *to++ = *from++;
            *to++ = *from++;
            *to++ = *from++;
            *to++ = *from++;
        }
        i = n & 7;
        while (i--)
        {
            *to++ = *from++;
        }
    }

    template<typename TYPE>
    class Precision
    {
    private:
        static std::shared_ptr<TYPE> precision, default_precision;

        Precision(){}
    public:
        static const TYPE & GetPrecision()
        {
            if (precision.get() == NULL)
            {
                precision.reset(new TYPE(std::numeric_limits<TYPE>::epsilon()));
                default_precision.reset(new TYPE(std::numeric_limits<TYPE>::epsilon()));
            }
            return *precision;
        }

        static void SetPrecision(const TYPE &x)
        {
            if (precision.get() == NULL)
            {
                precision.reset(new TYPE(x));
                default_precision.reset(new TYPE(std::numeric_limits<TYPE>::epsilon()));
                return;
            }
            precision.reset(new TYPE(x));
        }

        static void SetDefaultPrecision()
        {
            precision.reset(new TYPE(*default_precision));
        }
    };

    template<typename TYPE>
    std::shared_ptr<TYPE> Precision<TYPE>::precision;

    template<typename TYPE>
    std::shared_ptr<TYPE> Precision<TYPE>::default_precision;

}
#endif //INCLUDE_H



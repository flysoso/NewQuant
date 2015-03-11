#ifndef SF_INCLUDE_H
#define SF_INCLUDE_H

#include <assert.h>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <limits>
namespace NewQuant
{
    /*
    p[] is the parameters of polynomial
    n is the order of polynomial
    */
    template<typename TYPE>
    TYPE HornerMethod(const TYPE p[], const  int &n, const TYPE &x)
    {
        TYPE sum;
        sum = p[n];
        for (int i = n - 1; i >= 0; --i)
        {
            sum = sum*x + p[i];
        }
        return sum;
    }

    template<typename TYPE>
    class Pi
    {
    private:
        static std::shared_ptr<TYPE> pi;

        Pi(){}

        Pi<TYPE> & operator = (const Pi<TYPE> &);
    public:
        ~Pi(){}

        static TYPE value()
        {
            if (pi == NULL)
            {
                pi.reset(new TYPE);
                *pi = static_cast<TYPE>(3.1415926535897932384626433832795);
            }
            return *pi;
        }
    };

    template<typename TYPE>
    std::shared_ptr<TYPE> Pi<TYPE>::pi;
}

#endif //SF_INCLUDE_H

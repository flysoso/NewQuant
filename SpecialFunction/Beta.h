#ifndef BETA_H
#define BETA_H

#include "LnGamma.h"

namespace NewQuant
{
    template<typename TYPE>
    class Beta
    {
    private:
        static LnGamma<TYPE> ln_gamma;

        Beta<TYPE> & operator = (const Beta<TYPE> &);
    public:
        Beta(){}

        ~Beta(){}

        TYPE operator () (const TYPE &a, const TYPE &b) const
        {
            return std::exp(ln_gamma(a) + ln_gamma(b) - ln_gamma(a + b));
        }

    };

    template<typename TYPE>
    LnGamma<TYPE> Beta<TYPE>::ln_gamma;
}




#endif //BETA_H

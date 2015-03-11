#ifndef LN_GAMMA_H
#define LN_GAMMA_H

#include "GammaComputation.h"

namespace NewQuant
{
    template<typename TYPE>
    class LnGamma :public GammaComputation < TYPE >
    {
    private:
        LnGamma<TYPE> & operator = (const LnGamma<TYPE> &);
    public:
        LnGamma() :GammaComputation(){}

        ~LnGamma(){}

        TYPE operator () (const TYPE &) const;
    };

    template<typename TYPE>
    TYPE LnGamma<TYPE>::operator () (const TYPE &x) const
    {
        static const TYPE zero(0);
        assert(x >= zero);

        TYPE y = std::floor(x);
        TYPE diff = x - y;

        if (y <= GammaComputation<TYPE>::up_bound)
        {
            return std::log(GammaComputation<TYPE>::Method1(diff, x, y));
        }
        else
        {
            return GammaComputation<TYPE>::Method2(x);
        }
    }

}


#endif //LN_GAMMA_H

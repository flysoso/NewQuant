#ifndef SF_GAMMA_H
#define SF_GAMMA_H

#include "GammaComputation.h"

namespace NewQuant
{
    template<typename TYPE>
    class Gamma :public GammaComputation < TYPE >
    {
    private:
        Gamma<TYPE> & operator = (const Gamma<TYPE> &);
    public:
        Gamma() :GammaComputation(){}

        ~Gamma(){}

        TYPE operator () (const TYPE &) const;
    };

    template<typename TYPE>
    TYPE Gamma<TYPE>::operator () (const TYPE &x) const
    {
        static const TYPE zero(0);
        assert(x >= zero);

        TYPE y = std::floor(x);
        TYPE diff = x - y;

        if (y <= GammaComputation<TYPE>::up_bound)
        {
            return GammaComputation<TYPE>::Method1(diff, x, y);
        }
        else
        {
            return std::exp(GammaComputation<TYPE>::Method2(x));
        }
    }

}


#endif //SF_GAMMA_H

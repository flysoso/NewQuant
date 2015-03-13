#ifndef OZAKI_METHOD1D_H
#define OZAKI_METHOD1D_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class OzakiMethod1D
    {
    public :

        // Constructer
        OzakiMethod1D(){}
        ~OzakiMethod1D(){}
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;
        
    private :
        OzakiMethod1D(const OzakiMethod1D &em);
        OzakiMethod1D & operator = (const OzakiMethod1D &em);
    };

    template <typename TYPE>
    template <typename SDE>
    void OzakiMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        assert(sde.DriftX() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void OzakiMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE x = contain(1);

        TYPE e, v, k;
        static TYPE one(1), two(2);
        TYPE sigma = sde.Diffusion(x);
        for (unsigned int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            e = x + sde.Drift(x) / sde.DriftX(x)*(exp(sde.DriftX(x)*dt) - one);
            k = log(e / x) / dt;
            v = sigma*sigma*(exp(two*k*dt) - one) / (two*k);
            contain(i) = sqrt(v)*norm() + e;
            x = contain(i);
        }
    }
}


#endif //OZAKI_METHOD1D_H


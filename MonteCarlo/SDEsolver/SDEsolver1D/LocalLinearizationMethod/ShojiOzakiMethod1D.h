#ifndef SHOJI_OZAKI_METHOD1D_H
#define SHOJI_OZAKI_METHOD1D_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class ShojiOzakiMethod1D
    {
    public:

        // Constructer
        ShojiOzakiMethod1D(){}
        ~ShojiOzakiMethod1D(){}
        // Accessing functions

        template <typename SDECLASS>
        void ChackInitialization(const ItoDiffusion1D<TYPE, SDECLASS> &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;

    private:
        ShojiOzakiMethod1D(const ShojiOzakiMethod1D &em);
        ShojiOzakiMethod1D & operator = (const ShojiOzakiMethod1D &em);
    };

    template <typename TYPE>
    template <typename SDECLASS>
    void ShojiOzakiMethod1D<TYPE> ::ChackInitialization(const ItoDiffusion1D<TYPE, SDECLASS> &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        assert(sde.DriftX() != nullptr);
        assert(sde.DriftXX() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void ShojiOzakiMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE x = contain(1);

        TYPE l, m, a, b;
        static TYPE half(0.5), one(1), two(2);
        TYPE sigma = sde.Diffusion(x);
        for (unsigned int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            l = sde.DriftX(x);
            m = half*sigma*sigma*sde.DriftXX(x);
            a = one + sde.Drift(x)*(exp(l*dt) - one) / (x*l) + m*(exp(l*dt) - one - l*dt) / (x*l*l);
            b = sigma*sqrt((exp(two*l*dt) - one) / (two*l));
            contain(i) = norm()*b + a*x;
            x = contain(i);
        }
    }
}


#endif //SHOJI_OZAKI_METHOD1D_H


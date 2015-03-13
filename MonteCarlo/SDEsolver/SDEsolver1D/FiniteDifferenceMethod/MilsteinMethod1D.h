#ifndef MILSTEIN_METHOD1D_H
#define MILSTEIN_METHOD1D_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class MilsteinMethod1D
    {
    public :

        // Constructer
        MilsteinMethod1D(){}
        ~MilsteinMethod1D(){}
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;

    private :
        MilsteinMethod1D(const MilsteinMethod1D &mm);
        MilsteinMethod1D & operator = (const MilsteinMethod1D &mm);
    };

    template <typename TYPE>
    template <typename SDE>
    void MilsteinMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        assert(sde.DiffusionX() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void MilsteinMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);
        TYPE half(0.5);
        TYPE random;
        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            random = norm();
            contain(i) = x + sde.Drift(x)*dt + sde.Diffusion(x)*sqrt_dt*random + half*sde.Diffusion(x)*sde.DiffusionX(x)*(random*random*dt - dt);
            x = contain(i);
        }
    }
}




#endif //MILSTEIN_METHOD1D_H


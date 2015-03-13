#ifndef EULER_METHOD1D_H
#define EULER_METHOD1D_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class EulerMethod1D
    {
    public:

        // Constructer
        EulerMethod1D(){}
        ~EulerMethod1D(){}
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;

    private:
        EulerMethod1D(const EulerMethod1D<TYPE> &);
        EulerMethod1D & operator = (const EulerMethod1D<TYPE> &);
    };


    template <typename TYPE>
    template <typename SDE>
    void EulerMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void EulerMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);

        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            contain(i) = x + sde.Drift(x) * dt + sde.Diffusion(x) * sqrt_dt * norm();
            x = contain(i);
        }
    }
}




#endif //EULER_METHOD1D_H


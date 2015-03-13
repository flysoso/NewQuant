#ifndef STRONG_ORDER1_0RUNGE_KUTTA_METHOD_H
#define STRONG_ORDER1_0RUNGE_KUTTA_METHOD_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class StrongOrder1_0RungeKuttaMethod1D
    {
    public :

        // Constructer
        StrongOrder1_0RungeKuttaMethod1D(){}
        ~StrongOrder1_0RungeKuttaMethod1D(){}
        
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;
        
    private :
        StrongOrder1_0RungeKuttaMethod1D(const StrongOrder1_0RungeKuttaMethod1D &em);
        StrongOrder1_0RungeKuttaMethod1D & operator = (const StrongOrder1_0RungeKuttaMethod1D &em);

        template <typename SDECLASS>
        TYPE Postfix(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE x, const TYPE &norm, const TYPE &dt, const TYPE &sqrt_dt) const;
    };

    template <typename TYPE>
    template <typename SDE>
    void StrongOrder1_0RungeKuttaMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void StrongOrder1_0RungeKuttaMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);
        TYPE temp_norm;
        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            temp_norm = norm();
            contain(i) = x + sde.Drift(x) * dt + sde.Diffusion(x) * sqrt_dt * temp_norm;
            contain(i) += Postfix(sde, x, temp_norm, dt, sqrt_dt);
            x = contain(i);
        }
    }

    template <typename TYPE>
    template <typename SDECLASS>
    TYPE StrongOrder1_0RungeKuttaMethod1D<TYPE> ::Postfix(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE x, const TYPE &norm, const TYPE &dt, const TYPE &sqrt_dt) const
    {
        static TYPE half(0.5);
        TYPE r = half * (sde.Drift(x + sde.Drift(x)*sqrt_dt) - sde.Drift(x)) * (norm*norm*dt - dt) / sqrt_dt;
        return r;
    }

}



#endif //STRONG_ORDER1_0RUNGE_KUTTA_METHOD_H


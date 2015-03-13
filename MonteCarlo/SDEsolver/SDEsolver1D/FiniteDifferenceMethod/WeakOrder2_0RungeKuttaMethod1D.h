#ifndef WEAK_ORDER2_0RUNGE_KUTTA_METHOD_H
#define WEAK_ORDER2_0RUNGE_KUTTA_METHOD_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class WeakOrder2_0RungeKuttaMethod1D
    {
    public :

        // Constructer
        WeakOrder2_0RungeKuttaMethod1D(){}
        ~WeakOrder2_0RungeKuttaMethod1D(){}
        
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;
        
    private :
        WeakOrder2_0RungeKuttaMethod1D(const WeakOrder2_0RungeKuttaMethod1D &em);
        WeakOrder2_0RungeKuttaMethod1D & operator = (const WeakOrder2_0RungeKuttaMethod1D &em);

    };

    template <typename TYPE>
    template <typename SDE>
    void WeakOrder2_0RungeKuttaMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void WeakOrder2_0RungeKuttaMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);
        TYPE temp_norm;
        TYPE u0, u, u_plus, u_minus;
        TYPE t1, t2, t3;
        static TYPE half(0.5), quarter(0.25), two(2);
        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            temp_norm = norm();
            u0 = x + sde.Drift(x)*dt;
            u = u0 + sde.Diffusion(x)*temp_norm*sqrt_dt;
            u_plus = u0 + temp_norm*sqrt_dt;
            u_minus = u0 - temp_norm*sqrt_dt;

            t1 = x + half*(sde.Drift(u) + sde.Drift(x))*dt;
            t2 = quarter*(sde.Diffusion(u_plus) + sde.Diffusion(u_minus) + two*sde.Diffusion(x))*temp_norm*sqrt_dt;
            t3 = quarter*(sde.Diffusion(u_plus) - sde.Diffusion(u_minus))*(temp_norm*temp_norm*dt - dt) / sqrt_dt;
            contain(i) = t1 + t2 + t3;
            x = contain(i);
        }
    }

}



#endif //WEAK_ORDER2_0RUNGE_KUTTA_METHOD_H


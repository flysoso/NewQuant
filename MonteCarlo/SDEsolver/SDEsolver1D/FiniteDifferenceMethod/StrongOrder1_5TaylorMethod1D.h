#ifndef STRONG_ORDER1_5TAYLOR_METHOD_H
#define STRONG_ORDER1_5TAYLOR_METHOD_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class StrongOrder1_5TaylorMethod1D
    {
    public :

        // Constructer
        StrongOrder1_5TaylorMethod1D(){}
        ~StrongOrder1_5TaylorMethod1D(){}
        
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm1, RAND &norm2, CONTAINER &contain) const;
        
    private :
        StrongOrder1_5TaylorMethod1D(const StrongOrder1_5TaylorMethod1D &em);
        StrongOrder1_5TaylorMethod1D & operator = (const StrongOrder1_5TaylorMethod1D &em);

        template <typename SDECLASS>
        TYPE Postfix(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE &x, const TYPE &norm1, const TYPE &norm2, const TYPE &dt, const TYPE &sqrt_dt) const;
    };

    template <typename TYPE>
    template <typename SDE>
    void StrongOrder1_5TaylorMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        assert(sde.DriftX() != nullptr);
        assert(sde.DiffusionX() != nullptr);
        assert(sde.DriftXX() != nullptr);
        assert(sde.DiffusionXX() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void StrongOrder1_5TaylorMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);
        TYPE norm1, norm2;
        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            norm1 = norm();
            norm2 = norm();
            contain(i) = x + sde.Drift(x) * dt + sde.Diffusion(x) * sqrt_dt * norm1;
            contain(i) += Postfix(sde, x, norm1, norm2, dt, sqrt_dt);
            x = contain(i);
        }
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void StrongOrder1_5TaylorMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm1, RAND &norm2, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);
        TYPE n1, n2;
        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            n1 = norm1();
            n2 = norm2();
            contain(i) = x + sde.Drift(x) * dt + sde.Diffusion(x) * sqrt_dt * n1;
            contain(i) += Postfix(sde, x, n1, n2, dt, sqrt_dt);
            x = contain(i);
        }
    }

    template <typename TYPE>
    template <typename SDECLASS>
    TYPE StrongOrder1_5TaylorMethod1D<TYPE> ::Postfix(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE &x, const TYPE &norm1, const TYPE &norm2, const TYPE &dt, const TYPE &sqrt_dt) const
    {
        static TYPE half(0.5);
        static TYPE one_third(1.0 / 3.0);
        static TYPE sqrt_3(std::sqrt(3.0));
        TYPE z = half*dt*sqrt_dt*(norm1 + norm2 / sqrt_3);

        TYPE d = sde.Drift(x);
        TYPE d_x = sde.DriftX(x);
        TYPE d_xx = sde.DriftXX(x);

        TYPE s = sde.Diffusion(x);
        TYPE s_x = sde.DiffusionX(x);
        TYPE s_xx = sde.DiffusionXX(x);

        TYPE p1 = half*s*s_x * (norm1*norm1*dt - dt);
        TYPE p2 = s*d_x*z + half*(d*d_x + half*s*s*d_xx)*dt*dt;
        TYPE p3 = (d*s_x + half*s*s*s_xx) * (norm1*sqrt_dt*dt - z);
        TYPE p4 = half*s*(s_x*s_x + s*s_xx) * (one_third*norm1*norm1*dt - dt)*norm1*sqrt_dt;
        TYPE r = p1 + p2 + p3 + p4;
        return r;
    }
}




#endif //STRONG_ORDER1_5TAYLOR_METHOD_H


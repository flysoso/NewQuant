#ifndef SECOND_MILSTEIN_METHOD1D_H
#define SECOND_MILSTEIN_METHOD1D_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class SecondMilsteinMethod1D
    {
    public :

        // Constructer
        SecondMilsteinMethod1D(){}
        ~SecondMilsteinMethod1D(){}
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;

    private :
        SecondMilsteinMethod1D(const SecondMilsteinMethod1D &mm);
        SecondMilsteinMethod1D & operator = (const SecondMilsteinMethod1D &mm);

        template <typename SDECLASS>
        TYPE Postfix(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE x, const TYPE &norm, const TYPE &dt, const TYPE &sqrt_dt) const;
    };

    template <typename TYPE>
    template <typename SDE>
    void SecondMilsteinMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
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
    void SecondMilsteinMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = std::sqrt(dt);
        TYPE x = contain(1);
        TYPE random;
        for (int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            random = norm();
            contain(i) = x + sde.Drift(x)*dt + sde.Diffusion(x)*sqrt_dt*random + Postfix(sde, x, random, dt, sqrt_dt);
            x = contain(i);
        }
    }

    template <typename TYPE>
    template <typename SDECLASS>
    TYPE SecondMilsteinMethod1D<TYPE> ::Postfix(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE x, const TYPE &norm, const TYPE &dt, const TYPE &sqrt_dt) const
    {
        static TYPE half(0.5), one(1);

        TYPE d = sde.Drift(x);
        TYPE d_x = sde.DriftX(x);
        TYPE d_xx = sde.DriftXX(x);

        TYPE s = sde.Diffusion(x);
        TYPE s_x = sde.DiffusionX(x);
        TYPE s_xx = sde.DiffusionXX(x);

        TYPE p1 = half*s*s_x*dt*(norm*norm - one);
        TYPE p2 = half*dt*sqrt_dt*(d*s_x + d_x*s + half*s*s_xx)*norm;
        TYPE p3 = half*dt*dt*(d*d_x + half*d_xx*d*d);
        TYPE r = p1 + p2 + p3;
        return r;
    }

}


#endif //SECOND_MILSTEIN_METHOD1D_H


#ifndef PREDICTOR_CORRECTOR_METHOD_H
#define PREDICTOR_CORRECTOR_METHOD_H

#include "../../../SDE/SDE1D/ItoDiffusion1D.h"

namespace NewQuant
{
    template <typename TYPE>
    class PredictorCorrectorMethod1D
    {
    public :

        // Constructer
        PredictorCorrectorMethod1D(const TYPE &a, const TYPE &b) : alpha_(a), beta_(b){}
        ~PredictorCorrectorMethod1D(){}
        // Accessing functions

        template <typename SDE>
        void ChackInitialization(const SDE &sde) const;

        template <typename SDECLASS, typename RAND, typename CONTAINER>
        void Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const;
    
    private :
        TYPE alpha_;
        TYPE beta_;
        PredictorCorrectorMethod1D(const PredictorCorrectorMethod1D &pcm);
        PredictorCorrectorMethod1D & operator = (const PredictorCorrectorMethod1D &pcm);
        
        template <typename SDECLASS>
        TYPE drift_correct(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE &predict, const TYPE &x) const;

        template <typename SDECLASS>
        TYPE diffusion_correct(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE &predict, const TYPE &x) const;
    };

    template <typename TYPE>
    template <typename SDE>
    void PredictorCorrectorMethod1D<TYPE> ::ChackInitialization(const SDE &sde) const
    {
        assert(sde.Drift() != nullptr);
        assert(sde.Diffusion() != nullptr);
        assert(sde.DiffusionX() != nullptr);
        sde.ChackInitialTime();
        sde.ChackInitialValue();
    }

    template <typename TYPE>
    template <typename SDECLASS, typename RAND, typename CONTAINER>
    void PredictorCorrectorMethod1D<TYPE> ::Simulate(const ItoDiffusion1D<TYPE, SDECLASS> &sde, RAND &norm, CONTAINER &contain) const
    {
        ChackInitialization(sde);

        contain(1) = sde.GetInitialValue();
        TYPE dt = sde.GetDelta();
        TYPE sqrt_dt = sqrt(dt);
        TYPE temp = contain(1);
        TYPE predict, sqrt_norm;
        for (unsigned int i = 2; i <= sde.GetSteps() + 1; ++i)
        {
            sqrt_norm = sqrt_dt * norm();
            predict = temp + sde.Drift(temp) * dt + sde.Diffusion(temp) * sqrt_norm;
            contain(i) = temp + drift_correct(sde, predict, temp) * dt + diffusion_correct(sde, predict, temp) * sqrt_norm;
            temp = contain(i);
        }
    }

    template <typename TYPE>
    template <typename SDECLASS>
    TYPE PredictorCorrectorMethod1D<TYPE> ::drift_correct(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE &predict, const TYPE &x) const
    {
        TYPE d1 = sde.Drift(predict) - beta_*sde.Diffusion(predict)*sde.DiffusionX(predict);
        TYPE d2 = sde.Drift(x) - beta_*sde.Diffusion(x)*sde.DiffusionX(x);
        static TYPE one(1);
        TYPE correct = alpha_*d1 + (one - alpha_)*d2;
        return correct;
    }

    template <typename TYPE>
    template <typename SDECLASS>
    TYPE PredictorCorrectorMethod1D<TYPE> ::diffusion_correct(const ItoDiffusion1D<TYPE, SDECLASS> &sde, const TYPE &predict, const TYPE &x) const
    {
        static TYPE one(1);
        TYPE correct = alpha_*sde.Diffusion(predict) + (one - alpha_)*sde.Diffusion(x);
        return correct;
    }
}


#endif //PREDICTOR_CORRECTOR_METHOD_H


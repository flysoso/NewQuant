#ifndef ITODIFFUSION_H
#define ITODIFFUSION_H

#include <memory>
#include "../../Range.h"

namespace NewQuant
{
    template <typename TYPE, typename SDECLASS>
    class ItoDiffusion1D
    {
    public:

        // Constructors
        ItoDiffusion1D();

        ItoDiffusion1D(SDECLASS * drift, SDECLASS * diffusion);
        ItoDiffusion1D(SDECLASS * drift, SDECLASS * diffusion, SDECLASS * drift_x, SDECLASS * diffusion_x);
        ItoDiffusion1D(SDECLASS * drift, SDECLASS * diffusion, SDECLASS * drift_x, SDECLASS * diffusion_x, SDECLASS * drift_xx, SDECLASS * diffusion_xx);

        ItoDiffusion1D(std::shared_ptr<SDECLASS> drift, std::shared_ptr<SDECLASS> diffusion);
        ItoDiffusion1D(std::shared_ptr<SDECLASS> drift, std::shared_ptr<SDECLASS> diffusion, std::shared_ptr<SDECLASS> driftd_x, std::shared_ptr<SDECLASS> diffusiond_x);
        ItoDiffusion1D(std::shared_ptr<SDECLASS> drift, std::shared_ptr<SDECLASS> diffusion, std::shared_ptr<SDECLASS> driftd_x, std::shared_ptr<SDECLASS> diffusiond_x, std::shared_ptr<SDECLASS> driftd_xx, std::shared_ptr<SDECLASS> diffusiond_xx);

        // Modifier functions

        void SetDrift(SDECLASS * drift){ drift_.reset(drift); }
        void SetDiffusion(SDECLASS * diffusion){ diffusion_.reset(diffusion); }
        void SetDriftX(SDECLASS * drift_x){ drift_x_.reset(drift_x); }
        void SetDiffusionX(SDECLASS * diffusion_x){ diffusion_x_.reset(diffusion_x); }
        void SetDriftXX(SDECLASS * drift_xx){ drift_xx_.reset(drift_xx); }
        void SetDiffusionXX(SDECLASS * diffusion_xx){ diffusion_xx_.reset(diffusion_xx); }

        void SetDrift(std::shared_ptr<SDECLASS> drift){ drift_ = drift; }
        void SetDiffusion(std::shared_ptr<SDECLASS> diffusion){ diffusion_ = diffusion; }
        void SetDriftX(std::shared_ptr<SDECLASS> drift_x){ drift_x_ = drift_x; }
        void SetDiffusionX(std::shared_ptr<SDECLASS> diffusion_x){ diffusion_x_ = diffusion_x; }
        void SetDriftXX(std::shared_ptr<SDECLASS> drift_xx){ drift_xx_ = drift_xx; }
        void SetDiffusionXX(std::shared_ptr<SDECLASS> diffusion_xx){ diffusion_xx_ = diffusion_xx; }

        void SetRange(const TYPE &start, const TYPE &end, int n)
        {
            range.SetStart(start);
            range.SetEnd(end);
            range.SetSteps(n);
            set_initial_time = true;
        }

        void SetRange()
        {
            set_initial_time = true;
        }

        void SetInitialValue(const TYPE &iv)
        {
            initial_value = iv;
            set_initial_value = true;
        }

        //Range<TYPE> * SetRange(){return &range;}

        Range<TYPE> GetRange() const { return range; }
        TYPE GetDelta() const { return range.GetDelta(); }
        int GetSteps() const { return range.GetSteps(); }
        TYPE GetInitialTime() const { return initial_time; }
        TYPE GetInitialValue() const { return initial_value; }

        TYPE Drift(const TYPE &x) const { return drift_->operator()(x); }
        TYPE Diffusion(const TYPE &x) const { return diffusion_->operator()(x); }
        TYPE DriftX(const TYPE &x) const { return drift_x_->operator()(x); }
        TYPE DiffusionX(const TYPE &x) const { return diffusion_x_->operator()(x); }
        TYPE DriftXX(const TYPE &x) const { return drift_xx_->operator()(x); }
        TYPE DiffusionXX(const TYPE &x) const { return diffusion_xx_->operator()(x); }

        std::shared_ptr<SDECLASS> Drift() const { return drift_; }
        std::shared_ptr<SDECLASS> Diffusion() const { return diffusion_; }
        std::shared_ptr<SDECLASS> DriftX() const { return drift_x_; }
        std::shared_ptr<SDECLASS> DiffusionX() const { return diffusion_x_; }
        std::shared_ptr<SDECLASS> DriftXX() const { return drift_xx_; }
        std::shared_ptr<SDECLASS> DiffusionXX() const { return diffusion_xx_; }

        void ChackInitialTime() const
        {
            assert(set_initial_time == true);
        }
        void ChackInitialValue() const
        {
            assert(set_initial_value == true);
        }

    private:
        TYPE initial_time;
        TYPE initial_value;
        TYPE dt;
        std::shared_ptr<SDECLASS> drift_;
        std::shared_ptr<SDECLASS> diffusion_;
        std::shared_ptr<SDECLASS> drift_x_;
        std::shared_ptr<SDECLASS> diffusion_x_;
        std::shared_ptr<SDECLASS> drift_xx_;
        std::shared_ptr<SDECLASS> diffusion_xx_;
        Range<TYPE> range;
        bool set_initial_time;
        bool set_initial_value;

        ItoDiffusion1D(const ItoDiffusion1D<TYPE, SDECLASS> &ito);
        ItoDiffusion1D & operator = (const ItoDiffusion1D<TYPE, SDECLASS> &ito) const;
    };

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D()
    {
        drift_.reset();
        diffusion_.reset();
        drift_x_.reset();
        diffusion_x_.reset();
        drift_xx_.reset();
        diffusion_xx_.reset();
        set_initial_time = false;
        set_initial_value = false;
    }

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D(SDECLASS * drift, SDECLASS * diffusion)
    {
        drift_.reset(drift);
        diffusion_.reset(diffusion);
        drift_x_.reset();
        diffusion_x_.reset();
        drift_xx_.reset();
        diffusion_xx_.reset();
        set_initial_time = false;
        set_initial_value = false;
    }

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D(SDECLASS * drift, SDECLASS * diffusion, SDECLASS * drift_x, SDECLASS * diffusion_x)
    {
        drift_.reset(drift);
        diffusion_.reset(diffusion);
        drift_x_.reset(drift_x);
        diffusion_x_.reset(diffusion_x);
        drift_xx_.reset();
        diffusion_xx_.reset();
        set_initial_time = false;
        set_initial_value = false;
    }

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D(SDECLASS * drift, SDECLASS * diffusion, SDECLASS * drift_x, SDECLASS * diffusion_x, SDECLASS * drift_xx, SDECLASS * diffusion_xx)
    {
        drift_.reset(drift);
        diffusion_.reset(diffusion);
        drift_x_.reset(drift_x);
        diffusion_x_.reset(diffusion_x);
        drift_xx_.reset(drift_xx);
        diffusion_xx_.reset(diffusion_xx);
        set_initial_time = false;
        set_initial_value = false;
    }

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D(std::shared_ptr<SDECLASS> drift, std::shared_ptr<SDECLASS> diffusion)
    {
        drift_ = drift;
        diffusion_ = diffusion;
        drift_x_.reset();
        diffusion_x_.reset();
        drift_xx_.reset();
        diffusion_xx_.reset();
        set_initial_time = false;
        set_initial_value = false;
    }

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D(std::shared_ptr<SDECLASS> drift, std::shared_ptr<SDECLASS> diffusion, std::shared_ptr<SDECLASS> drift_x, std::shared_ptr<SDECLASS> diffusion_x)
    {
        drift_ = drift;
        diffusion_ = diffusion;
        drift_x_ = drift_x;
        diffusion_x_ = diffusion_x;
        drift_xx_.reset();
        diffusion_xx_.reset();
        set_initial_time = false;
        set_initial_value = false;
    }

    template <typename TYPE, typename SDECLASS>
    ItoDiffusion1D<TYPE, SDECLASS> ::ItoDiffusion1D(std::shared_ptr<SDECLASS> drift, std::shared_ptr<SDECLASS> diffusion, std::shared_ptr<SDECLASS> drift_x, std::shared_ptr<SDECLASS> diffusion_x, std::shared_ptr<SDECLASS> drift_xx, std::shared_ptr<SDECLASS> diffusion_xx)
    {
        drift_ = drift;
        diffusion_ = diffusion;
        drift_x_ = drift_x;
        diffusion_x_ = diffusion_x;
        drift_xx_ = drift_xx;
        diffusion_xx_ = diffusion_xx;
        set_initial_time = false;
        set_initial_value = false;
    }

}


#endif //ITODIFFUSION_H

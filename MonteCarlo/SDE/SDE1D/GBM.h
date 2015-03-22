#ifndef GBM_H
#define GBM_H

namespace NewQuant
{
    //dX_t = drift*Xdt + diffusion*XdW

    template <typename TYPE>
    class GBM
    {
    protected:
        TYPE drift_;
        TYPE diffusion_;
        GBM(TYPE d1, TYPE d2) : drift_(d1), diffusion_(d2){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        virtual ~GBM(){}
    };

    template <typename TYPE>
    class GBMdrift : public GBM < TYPE >
    {
    public:
        GBMdrift(TYPE d1, TYPE d2) : GBM<TYPE>(d1, d2){}
        TYPE operator () (const TYPE &x) const
        {
            return x * drift_;
        }
        ~GBMdrift(){}
    };

    template <typename TYPE>
    class GBMdiffusion : public GBM < TYPE >
    {
    public:
        GBMdiffusion(TYPE d1, TYPE d2) : GBM<TYPE>(d1, d2){}
        TYPE operator () (const TYPE &x) const
        {
            return x * diffusion_;
        }
        ~GBMdiffusion(){}
    };

    template <typename TYPE>
    class GBMdrift_x : public GBM < TYPE >
    {
    public:
        GBMdrift_x(TYPE d1, TYPE d2) : GBM<TYPE>(d1, d2){}
        TYPE operator () (const TYPE &x) const
        {
            return drift_;
        }
        ~GBMdrift_x(){}
    };

    template <typename TYPE>
    class GBMdiffusion_x : public GBM < TYPE >
    {
    public:
        GBMdiffusion_x(TYPE d1, TYPE d2) : GBM<TYPE>(d1, d2){}
        TYPE operator () (const TYPE &x) const
        {
            return diffusion_;
        }
        ~GBMdiffusion_x(){}
    };

    template <typename TYPE>
    class GBMdrift_xx : public GBM < TYPE >
    {
    public:
        GBMdrift_xx(TYPE d1, TYPE d2) : GBM<TYPE>(d1, d2){}
        TYPE operator () (const TYPE &x) const
        {
            static TYPE zero(0); return zero;
        }
        ~GBMdrift_xx(){}
    };

    template <typename TYPE>
    class GBMdiffusion_xx : public GBM < TYPE >
    {
    public:
        GBMdiffusion_xx(TYPE d1, TYPE d2) : GBM<TYPE>(d1, d2){}
        TYPE operator () (const TYPE &x) const
        {
            static TYPE zero(0); return zero;
        }
        ~GBMdiffusion_xx(){}
    };
}









#endif


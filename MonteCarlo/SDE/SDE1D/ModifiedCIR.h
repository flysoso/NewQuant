#ifndef MODIFIED_GBM_H
#define MODIFIED_GBM_H

namespace NewQuant
{
    //dX_t = -theta1*Xdt + theta2*std::sqrt(1+X^2)dW

    template <typename TYPE>
    class ModifiedCIR
    {
    protected:
        TYPE theta1_;
        TYPE theta2_;
        ModifiedCIR(TYPE t1, TYPE t2) : theta1_(t1), theta2_(t2){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        virtual ~ModifiedCIR(){}
    };

    template <typename TYPE>
    class ModifiedCIRdrift : public ModifiedCIR<TYPE>
    {
    public :
        ModifiedCIRdrift(TYPE t1, TYPE t2) : ModifiedCIR<TYPE>(t1, t2){}
        TYPE operator () (const TYPE &x) const
        {return -theta1_*x;}
        ~ModifiedCIRdrift(){}
    };

    template <typename TYPE>
    class ModifiedCIRdiffusion : public ModifiedCIR<TYPE>
    {
    public :
        ModifiedCIRdiffusion(TYPE t1, TYPE t2) : ModifiedCIR<TYPE>(t1, t2){}
        TYPE operator () (const TYPE &x) const
        {static TYPE one(1);return theta2_*std::sqrt(one + x*x);}
        ~ModifiedCIRdiffusion(){}
    };

    template <typename TYPE>
    class ModifiedCIRdrift_x : public ModifiedCIR<TYPE>
    {
    public :
        ModifiedCIRdrift_x(TYPE t1, TYPE t2) : ModifiedCIR<TYPE>(t1, t2){}
        TYPE operator () (const TYPE &x) const
        {return theta1_;}
        ~ModifiedCIRdrift_x(){}
    };

    template <typename TYPE>
    class ModifiedCIRdiffusion_x : public ModifiedCIR<TYPE>
    {
    public :
        ModifiedCIRdiffusion_x(TYPE t1, TYPE t2) : ModifiedCIR<TYPE>(t1, t2){}
        TYPE operator () (const TYPE &x) const
        {static TYPE one(1);return theta2_*x/std::sqrt(one + x*x);}
        ~ModifiedCIRdiffusion_x(){}
    };

    template <typename TYPE>
    class ModifiedCIRdrift_xx : public ModifiedCIR<TYPE>
    {
    public :
        ModifiedCIRdrift_xx(TYPE t1, TYPE t2) : ModifiedCIR<TYPE>(t1, t2){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~ModifiedCIRdrift_xx(){}
    };

    template <typename TYPE>
    class ModifiedCIRdiffusion_xx : public ModifiedCIR<TYPE>
    {
    public :
        ModifiedCIRdiffusion_xx(TYPE t1, TYPE t2) : ModifiedCIR<TYPE>(t1, t2){}
        TYPE operator () (const TYPE &x) const
        {static TYPE one(1);return theta2_/(one + x*x)/std::sqrt(one + x*x);}
        ~ModifiedCIRdiffusion_xx(){}
    };
}


#endif


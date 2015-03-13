#ifndef CIR_TYPE2_H
#define CIR_TYPE2_H

namespace NewQuant
{
    //dX_t = theta1*(theta2 - X)dt + theta3*std::sqrt(X)dW

    template <typename TYPE>
    class CIRtype2
    {
    protected:
        TYPE theta1_;
        TYPE theta2_;
        TYPE theta3_;
        CIRtype2(TYPE t1, TYPE t2, TYPE t3) : theta1_(t1), theta2_(t2), theta3_(t3){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        ~CIRtype2(){}
    };

    template <typename TYPE>
    class CIRtype2drift : public CIRtype2<TYPE>
    {
    public :
        CIRtype2drift(TYPE t1, TYPE t2, TYPE t3) : CIRtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta1_ * (theta2_ - x);}
        ~CIRtype2drift(){}
    };

    template <typename TYPE>
    class CIRtype2diffusion : public CIRtype2<TYPE>
    {
    public :
        CIRtype2diffusion(TYPE t1, TYPE t2, TYPE t3) : CIRtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta3_ * std::sqrt(x);}
        ~CIRtype2diffusion(){}
    };

    template <typename TYPE>
    class CIRtype2drift_x : public CIRtype2<TYPE>
    {
    public :
        CIRtype2drift_x(TYPE t1, TYPE t2, TYPE t3) : CIRtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return -theta1_;}
        ~CIRtype2drift_x(){}
    };

    template <typename TYPE>
    class CIRtype2diffusion_x : public CIRtype2<TYPE>
    {
    public :
        CIRtype2diffusion_x(TYPE t1, TYPE t2, TYPE t3) : CIRtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE half(0.5); return half*theta3_/std::sqrt(x);}
        ~CIRtype2diffusion_x(){}
    };

    template <typename TYPE>
    class CIRtype2drift_xx : public CIRtype2<TYPE>
    {
    public :
        CIRtype2drift_xx(TYPE t1, TYPE t2, TYPE t3) : CIRtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~CIRtype2drift_xx(){}
    };

    template <typename TYPE>
    class CIRtype2diffusion_xx : public CIRtype2<TYPE>
    {
    public :
        CIRtype2diffusion_xx(TYPE t1, TYPE t2, TYPE t3) : CIRtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE quarter(0.25),index(-1.5); return -quarter*pow(x,index);}
        ~CIRtype2diffusion_xx(){}
    };
}








#endif //CIR_TYPE2_H



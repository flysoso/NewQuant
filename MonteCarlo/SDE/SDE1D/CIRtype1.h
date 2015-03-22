#ifndef CIR_TYPE1_H
#define CIR_TYPE1_H

namespace NewQuant
{
    //dX_t = (theta1 - theta2*X)dt + theta3*std::sqrt(X)dW

    template <typename TYPE>
    class CIRtype1
    {
    protected:
        TYPE theta1_;
        TYPE theta2_;
        TYPE theta3_;
        CIRtype1(TYPE t1, TYPE t2, TYPE t3) : theta1_(t1), theta2_(t2), theta3_(t3){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        virtual ~CIRtype1(){}
    };

    template <typename TYPE>
    class CIRtype1drift : public CIRtype1<TYPE>
    {
    public :
        CIRtype1drift(TYPE t1, TYPE t2, TYPE t3) : CIRtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta1_ - theta2_*x;}
        ~CIRtype1drift(){}
    };

    template <typename TYPE>
    class CIRtype1diffusion : public CIRtype1<TYPE>
    {
    public :
        CIRtype1diffusion(TYPE t1, TYPE t2, TYPE t3) : CIRtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta3_ * std::sqrt(x);}
        ~CIRtype1diffusion(){}
    };

    template <typename TYPE>
    class CIRtype1drift_x : public CIRtype1<TYPE>
    {
    public :
        CIRtype1drift_x(TYPE t1, TYPE t2, TYPE t3) : CIRtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return -theta2_;}
        ~CIRtype1drift_x(){}
    };

    template <typename TYPE>
    class CIRtype1diffusion_x : public CIRtype1<TYPE>
    {
    public :
        CIRtype1diffusion_x(TYPE t1, TYPE t2, TYPE t3) : CIRtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE half(0.5); return half*theta3_/std::sqrt(x);}
        ~CIRtype1diffusion_x(){}
    };

    template <typename TYPE>
    class CIRtype1drift_xx : public CIRtype1<TYPE>
    {
    public :
        CIRtype1drift_xx(TYPE t1, TYPE t2, TYPE t3) : CIRtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~CIRtype1drift_xx(){}
    };

    template <typename TYPE>
    class CIRtype1diffusion_xx : public CIRtype1<TYPE>
    {
    public :
        CIRtype1diffusion_xx(TYPE t1, TYPE t2, TYPE t3) : CIRtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE quarter(0.25),index(-1.5); return -quarter*pow(x,index);}
        ~CIRtype1diffusion_xx(){}
    };
}








#endif //CIR_TYPE1_H



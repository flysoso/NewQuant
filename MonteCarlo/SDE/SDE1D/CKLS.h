#ifndef CKLS_H
#define CKLS_H

namespace NewQuant
{
    //dX_t = (theta1 + theta2*X)dt + theta3*(X^{theta4})dW

    template <typename TYPE>
    class CKLS
    {
    protected:
        TYPE theta1_;
        TYPE theta2_;
        TYPE theta3_;
        TYPE theta4_;
        CKLS(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : theta1_(t1), theta2_(t2), theta3_(t3), theta4_(t4){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        ~CKLS(){}
    };

    template <typename TYPE>
    class CKLSdrift : public CKLS<TYPE>
    {
    public :
        CKLSdrift(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : CKLS<TYPE>(t1, t2, t3, t4){}
        TYPE operator () (const TYPE &x) const
        {return theta1_ + theta2_ * x);}
        ~CKLSdrift(){}
    };

    template <typename TYPE>
    class CKLSdiffusion : public CKLS<TYPE>
    {
    public :
        CKLSdiffusion(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : CKLS<TYPE>(t1, t2, t3, t4){}
        TYPE operator () (const TYPE &x) const
        {return theta3_ * pow(x,theta4_);}
        ~CKLSdiffusion(){}
    };

    template <typename TYPE>
    class CKLSdrift_x : public CKLS<TYPE>
    {
    public :
        CKLSdrift_x(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : CKLS<TYPE>(t1, t2, t3, t4){}
        TYPE operator () (const TYPE &x) const
        {return theta2_;}
        ~CKLSdrift_x(){}
    };

    template <typename TYPE>
    class CKLSdiffusion_x : public CKLS<TYPE>
    {
    public :
        CKLSdiffusion_x(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : CKLS<TYPE>(t1, t2, t3, t4){}
        TYPE operator () (const TYPE &x) const
        {static TYPE one(1); return theta3_*theta4_*pow(x,theta4_-one);}
        ~CKLSdiffusion_x(){}
    };

    template <typename TYPE>
    class CKLSdrift_xx : public CKLS<TYPE>
    {
    public :
        CKLSdrift_xx(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : CKLS<TYPE>(t1, t2, t3, t4){}
        TYPE operator () (const TYPE &x) const
        {static TYPE one(1),two(2); return theta3_*theta4_*(theta4_-one)*pow(x,theta4_-two);}
        ~CKLSdrift_xx(){}
    };

    template <typename TYPE>
    class CKLSdiffusion_xx : public CKLS<TYPE>
    {
    public :
        CKLSdiffusion_xx(TYPE t1, TYPE t2, TYPE t3, TYPE t4) : CKLS<TYPE>(t1, t2, t3, t4){}
        TYPE operator () (const TYPE &x) const
        {static TYPE quarter(0.25),index(-1.5); return -quarter*pow(x,index);}
        ~CKLSdiffusion_xx(){}
    };
}








#endif //CKLS_H



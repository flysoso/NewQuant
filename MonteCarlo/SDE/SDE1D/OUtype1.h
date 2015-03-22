#ifndef OU_TYPE1_H
#define OU_TYPE1_H

namespace NewQuant
{
    //dX_t = (theta1 - theta2*X)dt + theta3dW

    template <typename TYPE>
    class OUtype1
    {
    protected:
        TYPE theta1_;
        TYPE theta2_;
        TYPE theta3_;
        OUtype1(TYPE t1, TYPE t2, TYPE t3) : theta1_(t1), theta2_(t2), theta3_(t3){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        virtual ~OUtype1(){}
    };

    template <typename TYPE>
    class OUtype1drift : public OUtype1<TYPE>
    {
    public :
        OUtype1drift(TYPE t1, TYPE t2, TYPE t3) : OUtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta1_ - theta2_*x;}
        ~OUtype1drift(){}
    };

    template <typename TYPE>
    class OUtype1diffusion : public OUtype1<TYPE>
    {
    public :
        OUtype1diffusion(TYPE t1, TYPE t2, TYPE t3) : OUtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta3_;}
        ~OUtype1diffusion(){}
    };

    template <typename TYPE>
    class OUtype1drift_x : public OUtype1<TYPE>
    {
    public :
        OUtype1drift_x(TYPE t1, TYPE t2, TYPE t3) : OUtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return -theta2_;}
        ~OUtype1drift_x(){}
    };

    template <typename TYPE>
    class OUtype1diffusion_x : public OUtype1<TYPE>
    {
    public :
        OUtype1diffusion_x(TYPE t1, TYPE t2, TYPE t3) : OUtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~OUtype1diffusion_x(){}
    };

    template <typename TYPE>
    class OUtype1drift_xx : public OUtype1<TYPE>
    {
    public :
        OUtype1drift_xx(TYPE t1, TYPE t2, TYPE t3) : OUtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~OUtype1drift_xx(){}
    };

    template <typename TYPE>
    class OUtype1diffusion_xx : public OUtype1<TYPE>
    {
    public :
        OUtype1diffusion_xx(TYPE t1, TYPE t2, TYPE t3) : OUtype1<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~OUtype1diffusion_xx(){}
    };
}








#endif //OU_TYPE1_H



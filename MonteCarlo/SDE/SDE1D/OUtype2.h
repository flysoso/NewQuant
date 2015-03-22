#ifndef OU_TYPE2_H
#define OU_TYPE2_H

namespace NewQuant
{
    //dX_t = theta1*(theta2 - X)dt + theta3dW

    template <typename TYPE>
    class OUtype2
    {
    protected:
        TYPE theta1_;
        TYPE theta2_;
        TYPE theta3_;
        OUtype2(TYPE t1, TYPE t2, TYPE t3) : theta1_(t1), theta2_(t2), theta3_(t3){}
    public:
        virtual TYPE operator () (const TYPE &x) const = 0;
        virtual ~OUtype2(){}
    };

    template <typename TYPE>
    class OUtype2drift : public OUtype2<TYPE>
    {
    public :
        OUtype2drift(TYPE t1, TYPE t2, TYPE t3) : OUtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta1_ * (theta2_ - x);}
        ~OUtype2drift(){}
    };

    template <typename TYPE>
    class OUtype2diffusion : public OUtype2<TYPE>
    {
    public :
        OUtype2diffusion(TYPE t1, TYPE t2, TYPE t3) : OUtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return theta3_;}
        ~OUtype2diffusion(){}
    };

    template <typename TYPE>
    class OUtype2drift_x : public OUtype2<TYPE>
    {
    public :
        OUtype2drift_x(TYPE t1, TYPE t2, TYPE t3) : OUtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {return -theta1_;}
        ~OUtype2drift_x(){}
    };

    template <typename TYPE>
    class OUtype2diffusion_x : public OUtype2<TYPE>
    {
    public :
        OUtype2diffusion_x(TYPE t1, TYPE t2, TYPE t3) : OUtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~OUtype2diffusion_x(){}
    };

    template <typename TYPE>
    class OUtype2drift_xx : public OUtype2<TYPE>
    {
    public :
        OUtype2drift_xx(TYPE t1, TYPE t2, TYPE t3) : OUtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~OUtype2drift_xx(){}
    };

    template <typename TYPE>
    class OUtype2diffusion_xx : public OUtype2<TYPE>
    {
    public :
        OUtype2diffusion_xx(TYPE t1, TYPE t2, TYPE t3) : OUtype2<TYPE>(t1, t2, t3){}
        TYPE operator () (const TYPE &x) const
        {static TYPE zero(0); return zero;}
        ~OUtype2diffusion_xx(){}
    };
}



#endif //OU_TYPE2_H



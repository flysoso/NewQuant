#ifndef FUNCTION_OBJECT_H
#define FUNCTION_OBJECT_H

#include <math.h>
#include <cmath>
#include <cstdlib>

namespace NewQuant
{
    template<typename T>
    class pow_func
    {
    public:
        T operator () (const T &b, const T &x) const
        {
            return std::pow(b, x);
        }
    };

    template<typename T>
    class sin_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::sin(x);
        }
    };

    template<typename T>
    class cos_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::cos(x);
        }
    };

    template<typename T>
    class tan_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::tan(x);
        }
    };

    template<typename T>
    class cot_func
    {
    public:
        T operator () (const T &x) const
        {
            static const T one(1);
            return one / std::tan(x);
        }
    };


    template<typename T>
    class sinh_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::sinh(x);
        }
    };

    template<typename T>
    class cosh_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::cosh(x);
        }
    };

    template<typename T>
    class tanh_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::tanh(x);
        }
    };

    template<typename T>
    class coth_func
    {
    public:
        T operator () (const T &x) const
        {
            static const T one(1);
            return one / std::tanh(x);
        }
    };

    template<typename T>
    class exp_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::exp(x);
        }
    };

    template<typename T>
    class log_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::log(x);
        }
    };

    template<typename T>
    class log10_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::log10(x);
        }
    };

    template<typename T>
    class abs_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::abs(x);
        }
    };

    template<typename T>
    class sqrt_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::sqrt(x);
        }
    };

    template<typename T>
    class asin_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::asin(x);
        }
    };

    template<typename T>
    class acos_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::acos(x);
        }
    };

    template<typename T>
    class atan_func
    {
    public:
        T operator () (const T &x) const
        {
            return std::atan(x);
        }
    };

    template<typename T>
    class acot_func
    {
    public:
        T operator () (const T &x) const
        {
            static const T one(1);
            return std::atan(one / x);
        }
    };
}

#endif //FUNCTION_OBJECT_H


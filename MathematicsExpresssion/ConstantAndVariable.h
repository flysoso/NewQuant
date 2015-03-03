#ifndef CONSTANT_AND_VARIABLE_H
#define CONSTANT_AND_VARIABLE_H

#include "BaseExpression.h"

namespace NewQuant
{
    template<typename T>
    class Constant : public BaseExpression < T >
    {
    private:
        const T value;
        Constant<T> & operator = (const T &);
        Constant<T> & operator = (const Constant<T> &);
    public:
        explicit Constant(const T &v) : value(v) {}

        Constant(const T &v, int o) : value(v) {}

        Constant(const Constant<T> &c) : value(c.value){}

        ~Constant(){}

        T eval() const
        {
            return value;
        }
        T eval(const T &x) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3, const T&x4) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8) const
        {
            return value;
        }
        T eval(const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8, const T&x9) const
        {
            return value;
        }

        T operator () () const
        {
            return value;
        }
        T operator () (const T &x) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3, const T&x4) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8) const
        {
            return value;
        }
        T operator () (const T &x1, const T&x2, const T&x3, const T&x4, const T&x5, const T&x6, const T&x7, const T&x8, const T&x9) const
        {
            return value;
        }

    };

    template<class T>
    class Variable : public BaseExpression < T >
    {
    private:
        int order;
    public:
        Variable() : order(1) {}

        explicit Variable(int o) : order(o){}

        Variable(const Variable<T> &x) : order(x.order){}

        ~Variable(){}

        T eval() const;
        T eval(const T &x) const;
        T eval(const T &x1, const T &x2) const;
        T eval(const T &x1, const T &x2, const T &x3) const;
        T eval(const T &x1, const T &x2, const T &x3, const T &x4) const;
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const;
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6) const;
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7) const;
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8) const;
        T eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) const;

        T operator () () const;
        T operator () (const T &x) const;
        T operator () (const T &x1, const T &x2) const;
        T operator () (const T &x1, const T &x2, const T &x3) const;
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4) const;
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const;
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6) const;
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7) const;
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8) const;
        T operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5, const T &x6, const T &x7, const T &x8, const T &x9) const;

    };

    template<typename ExprT>
    class ExprTraits
    {
    public:
        typedef ExprT expr_type;
    };

    template<>
    class ExprTraits < double >
    {
    public:
        typedef Constant<double> expr_type;
    };

    template<>
    class ExprTraits < int >
    {
    public:
        typedef Constant<int> expr_type;
    };


    /*****Variable*****/
    /*eval*/

    template<typename T>
    T Variable<T> ::eval() const
    {
        assert(order == 0);
        return T(0);
    }

    template<typename T>
    T Variable<T> ::eval(const T &x) const
    {
        assert(order == 1);
        switch (order)
        {
        case 1:
            return x;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2) const
    {
        assert(1 <= order&&order <= 2);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3) const
    {
        assert(1 <= order&&order <= 3);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3, const T &x4) const
    {
        assert(1 <= order&&order <= 4);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
    {
        assert(1 <= order&&order <= 5);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                         const T &x6) const
    {
        assert(1 <= order&&order <= 6);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                         const T &x6, const T &x7) const
    {
        assert(1 <= order&&order <= 7);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        case 7:
            return x7;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                         const T &x6, const T &x7, const T &x8) const
    {
        assert(1 <= order&&order <= 8);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        case 7:
            return x7;
            break;
        case 8:
            return x8;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> ::eval(const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                         const T &x6, const T &x7, const T &x8, const T &x9) const
    {
        assert(1 <= order&&order <= 9);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        case 7:
            return x7;
            break;
        case 8:
            return x8;
            break;
        case 9:
            return x9;
            break;
        default:
            return T(0);
        }
    }

    /*operator()*/
    template<typename T>
    T Variable<T> :: operator () () const
    {
        assert(1==0);
        return T(0);
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x) const
    {
        assert(1==1);
        switch (order)
        {
        case 1:
            return x;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2) const
    {
        assert(1 <= order&&order <= 2);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3) const
    {
        assert(1 <= order&&order <= 3);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3, const T &x4) const
    {
        assert(1 <= order&&order <= 4);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5) const
    {
        assert(1 <= order&&order <= 5);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                                  const T &x6) const
    {
        assert(1 <= order&&order <= 6);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                                  const T &x6, const T &x7) const
    {
        assert(1 <= order&&order <= 7);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        case 7:
            return x7;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                                  const T &x6, const T &x7, const T &x8) const
    {
        assert(1 <= order&&order <= 8);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        case 7:
            return x7;
            break;
        case 8:
            return x8;
            break;
        default:
            return T(0);
        }
    }

    template<typename T>
    T Variable<T> :: operator () (const T &x1, const T &x2, const T &x3, const T &x4, const T &x5,
                                  const T &x6, const T &x7, const T &x8, const T &x9) const
    {
        assert(1 <= order&&order <= 9);
        switch (order)
        {
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        case 6:
            return x6;
            break;
        case 7:
            return x7;
            break;
        case 8:
            return x8;
            break;
        case 9:
            return x9;
            break;
        default:
            return T(0);
        }
    }


}
#endif //CONSTANT_AND_VARIABLE_H



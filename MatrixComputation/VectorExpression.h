#ifndef VECTOR_EXPRESSION_H
#define VECTOR_EXPRESSION_H

#include "../ExceptionClass/NotDefinedException.h"

namespace NewQuant
{
    template<typename TYPE> class GeneralMatrix;

    template<typename TYPE>
    class VectorExpression
    {
    protected:
        int length;

        VectorExpression(){}

        VectorExpression(const int &l) : length(l) {}

        VectorExpression(const VectorExpression<TYPE> &v) : length(v.length){}

        void SetLength(const int &l)
        {
            length = l;
        }
    public:
        virtual int Search(const GeneralMatrix<TYPE> &) const = 0;

        ~VectorExpression() {}

        const int & Length() const
        {
            return length;
        }

        virtual TYPE operator () (const int &i) const = 0;

        virtual TYPE & operator () (const int &i)
        {
            Singleton<Tracer>::Instance()->AddMessage("TYPE & VectorExpression::operator () (r, c)");
            throw NotDefinedException("TYPE & operator () (i)", "VectorExpression");
        }
    };

    template<typename TYPE>
    TYPE Norm1(const VectorExpression<TYPE> &v)
    {
        TYPE sum(0);
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += std::fabs(v(i));
        }
        return sum;
    }

    template<typename TYPE>
    TYPE Norm2(const VectorExpression<TYPE> &v)
    {
        TYPE sum(0);
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += v(i)*v(i);
        }
        return std::sqrt(sum);
    }

    template<typename TYPE>
    TYPE NormInf(const VectorExpression<TYPE> &v)
    {
        TYPE sum(0);
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum = std::max(sum, std::fabs(v(i)));
        }
        return sum;
    }

    template<typename TYPE>
    TYPE Mean(const VectorExpression<TYPE> &v)
    {
        TYPE sum(0), n(v.Length());
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += v(i);
        }
        return sum / n;
    }

    template<typename TYPE>
    TYPE Var(const VectorExpression<TYPE> &v)
    {
        TYPE sum(0);
        TYPE mean2 = Mean(v), n(v.Length());
        mean2 *= mean2;
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += v(i)*v(i) - mean2;
        }
        return sum / n;
    }

    template<typename TYPE>
    TYPE Sd(const VectorExpression<TYPE> &v)
    {
        return std::sqrt(Var(v));
    }

    template<typename TYPE>
    TYPE Cov(const VectorExpression<TYPE> &v1, const VectorExpression<TYPE> &v2)
    {
        assert(v1.Length() == v2.Length());
        TYPE sum(0);
        TYPE mean1 = Mean(v1), mean2 = Mean(v2), n(v1.Length());
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += (v1(i) - mean1)*(v2(i) - mean2);
        }
        return sum / n;
    }

    template<typename TYPE>
    TYPE Cor(const VectorExpression<TYPE> &v1, const VectorExpression<TYPE> &v2)
    {
        assert(v1.Length() == v2.Length());
        TYPE s1 = Sd(v1), s2 = Sd(v2);
        TYPE cov = Cov(v1, v2);
        return cov / (s1*s2);
    }

}

#endif // VECTOR_EXPRESSION_H

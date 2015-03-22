#ifndef VECTOR_H
#define VECTOR_H

namespace NewQuant
{
    template<typename TYPE>
    class Vector
    {
    protected:
        int length;

        Vector(){}

        Vector(const int &l) : length(l) {}

        Vector(const Vector<TYPE> &v) : length(v.length){}

        void SetLength(const int &l)
        {
            length = l;
        }
    public:
        virtual ~Vector() {}

        const int & Length() const
        {
            return length;
        }

        virtual void Resize(const int &) = 0;

        virtual TYPE operator () (const int &) const = 0;

        virtual TYPE & operator () (const int &) = 0;

    };

    template<typename TYPE>
    TYPE Norm1(const Vector<TYPE> &v)
    {
        TYPE sum(0);
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += std::fabs(v(i));
        }
        return sum;
    }

    template<typename TYPE>
    TYPE Norm2(const Vector<TYPE> &v)
    {
        TYPE sum(0);
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += v(i)*v(i);
        }
        return std::sqrt(sum);
    }

    template<typename TYPE>
    TYPE NormInf(const Vector<TYPE> &v)
    {
        TYPE sum(0);
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum = std::max(sum, std::fabs(v(i)));
        }
        return sum;
    }

    template<typename TYPE>
    TYPE Mean(const Vector<TYPE> &v)
    {
        TYPE sum(0), n(v.Length());
        for (int i = 1; i <= v.Length(); ++i)
        {
            sum += v(i);
        }
        return sum / n;
    }

    template<typename TYPE>
    TYPE Var(const Vector<TYPE> &v)
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
    TYPE Sd(const Vector<TYPE> &v)
    {
        return std::sqrt(Var(v));
    }

    template<typename TYPE>
    TYPE Cov(const Vector<TYPE> &v1, const Vector<TYPE> &v2)
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
    TYPE Cor(const Vector<TYPE> &v1, const Vector<TYPE> &v2)
    {
        assert(v1.Length() == v2.Length());
        TYPE s1 = Sd(v1), s2 = Sd(v2);
        TYPE cov = Cov(v1, v2);
        return cov / (s1*s2);
    }

}

#endif // VECTOR_H

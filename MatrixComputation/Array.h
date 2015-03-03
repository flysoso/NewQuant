#ifndef ARRAY_H
#define ARRAY_H

#include <math.h>
#include <vector>
#include <assert.h>

template <typename TYPE>
class Array
{
private:
    std::vector<TYPE> data;
public:
    Array(){}

    Array(const int &n) :data(n){}

    ~Array(){}

    Array<TYPE> & operator = (const Array<TYPE> &a)
    {
        if (&a == this)
        {
            return *this;
        }
        data = a.data;
        return *this;
    }

    int Size() const
    {
        return data.size();
    }

    void Resize(const int &n)
    {
        data.resize(n);
    }

    void Max(TYPE &x, int &idx) const
    {
        x = data[0];
        idx = 1;
        for (int i = 1; i < data.size(); ++i)
        {
            if (x < data[i])
            {
                x = data[i];
                idx = i + 1;
            }
        }
    }

    void Min(TYPE &x, int &idx) const
    {
        x = data[0];
        idx = 1;
        for (int i = 1; i < data.size(); ++i)
        {
            if (x > data[i])
            {
                x = data[i];
                idx = i + 1;
            }
        }
    }

    void AbsMax(TYPE &x, int &idx) const
    {
        x = fabs(data[0]);
        idx = 1;
        for (int i = 1; i < data.size(); ++i)
        {
            if (x < fabs(data[i]))
            {
                x = fabs(data[i]);
                idx = i + 1;
            }
        }
    }

    void AbsMin(TYPE &x, int &idx) const
    {
        x = fabs(data[0]);
        idx = 1;
        for (int i = 1; i < data.size(); ++i)
        {
            if (x > fabs(data[i]))
            {
                x = fabs(data[i]);
                idx = i + 1;
            }
        }
    }

    const TYPE & operator () (const int &i) const
    {
        assert(i - 1 <= data.size());
        return data[i - 1];
    }

    TYPE & operator () (const int &i)
    {
        assert(i - 1 <= data.size());
        return data[i - 1];
    }

    void Swap(const int &i1, const int &i2)
    {
        assert(i1 - 1 <= data.size() && i2 - 1 <= data.size());
        TYPE t;
        t = data[i1 - 1];
        data[i1 - 1] = data[i2 - 1];
        data[i2 - 1] = t;
    }

    void Swap(Array<TYPE> &a)
    {
        data.swap(a.data);
    }
};

template <typename TYPE>
inline void SwapArray(Array<TYPE> &a, Array<TYPE> &b)
{
    a.Swap(b);
}




#endif // !ARRAY_H

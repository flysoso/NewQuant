#ifndef MATRIX_BAND_WIDTH_H
#define MATRIX_BAND_WIDTH_H

#include <memory>
#include "include.h"

template<typename TYPE> class GeneralMatrix;

///Upper and lower bandwidths of a matrix.
///That is number of diagonals strictly above or below main diagonal,
///e.g. diagonal matrix has 0 upper and lower bandwiths.
template<typename TYPE>
class MatrixBandWidth
{
private:
    bool evalued;
    int lower_val;
    int upper_val;
public:
    MatrixBandWidth() : lower_val(-1), upper_val(-1), evalued(false) {}

    MatrixBandWidth(const int &l, const int &u) : lower_val(l), upper_val(u)
    {
        if (l < 0 || u < 0)
            evalued = false;
        else
            evalued = true;
    }

    MatrixBandWidth(const int &i) : lower_val(i), upper_val(i)
    {
        if (i < 0)
            evalued = false;
        else
            evalued = true;
    }

    MatrixBandWidth(const MatrixBandWidth<TYPE> &bw)
    {
        lower_val = bw.lower_val;
        upper_val = bw.upper_val;
        evalued = bw.evalued;
    }

    ~MatrixBandWidth(){}

    MatrixBandWidth<TYPE> & operator = (const MatrixBandWidth<TYPE> &bw)
    {
        if (&bw == this)
        {
            return *this;
        }
        lower_val = bw.lower_val;
        upper_val = bw.upper_val;
        evalued = bw.evalued;
        return *this;
    }

    MatrixBandWidth<TYPE> operator+(const MatrixBandWidth<TYPE>&) const;

    MatrixBandWidth<TYPE> minimum(const MatrixBandWidth<TYPE>&) const;

    MatrixBandWidth<TYPE> t() const
    {
        return MatrixBandWidth<TYPE>(upper_val, lower_val);
    }

    bool operator==(const MatrixBandWidth<TYPE>& bw) const
    {
        return (lower_val == bw.lower_val) && (upper_val == bw.upper_val);
    }

    bool operator!=(const MatrixBandWidth<TYPE>& bw) const
    {
        return !operator==(bw);
    }

    int Upper() const
    {
        return upper_val;
    }

    int Lower() const
    {
        return lower_val;
    }

    void SetUpper(const int &u)
    {
        assert(u >= -1);
        upper_val = u;
    }

    void SetLower(const int &l)
    {
        assert(l >= -1);
        lower_val = l;
    }

    void SetEvalued(bool x)
    {
        evalued = x;
    }

    bool Evalued() const
    {
        return evalued;
    }

    void Set(const int &l, const int &u, const bool &e)
    {
        assert(u >= -1);
        assert(l >= -1);
        lower_val = l;
        upper_val = u;
        evalued = e;
    }
};

template<typename TYPE>
MatrixBandWidth<TYPE> MatrixBandWidth<TYPE>::operator+(const MatrixBandWidth<TYPE>& bw) const
{
    int l = bw.lower_val;
    int u = bw.upper_val;
    l = (lower_val < 0 || l < 0) ? -1 : (lower_val > l) ? lower_val : l;
    u = (upper_val < 0 || u < 0) ? -1 : (upper_val > u) ? upper_val : u;
    return MatrixBandWidth<TYPE>(l, u);
}

template<typename TYPE>
MatrixBandWidth<TYPE> MatrixBandWidth<TYPE>::minimum(const MatrixBandWidth<TYPE>& bw) const
{
    int l = bw.lower_val;
    int u = bw.upper_val;
    if ((lower_val >= 0) && ((l < 0) || (l > lower_val))) l = lower_val;
    if ((upper_val >= 0) && ((u < 0) || (u > upper_val))) u = upper_val;
    return MatrixBandWidth<TYPE>(l, u);
}


template<typename TYPE>
MatrixBandWidth<TYPE> Mult(const MatrixBandWidth<TYPE> &bw1, const MatrixBandWidth<TYPE> &bw2, const int dim)
{
    int l1 = bw1.Lower(), l2 = bw2.Lower();
    int u1 = bw1.Upper(), u2 = bw2.Upper();
    int l = (l1 < 0 || l2 < 0) ? -1 : std::min(l1 + l2, dim - 1);
    int u = (u1 < 0 || u2 < 0) ? -1 : std::min(u1 + u2, dim - 1);
    return MatrixBandWidth<TYPE>(l, u);
}



#endif //MATRIX_BAND_WIDTH_H


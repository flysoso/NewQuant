#ifndef CONSTANT_MATRIX_H
#define CONSTANT_MATRIX_H

#include "GeneralMatrix.h"
#include "ConstantSolver.h"

/// Constant matrix.
template <typename TYPE>
class ConstantMatrix : public GeneralMatrix < TYPE >
{
public:
    ConstantMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
    {
        GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
    }

    explicit ConstantMatrix(const int &n) : GeneralMatrix<TYPE>(n, n, 1)
    {
        GeneralMatrix<TYPE>::band_width.Set(n - 1, n - 1, true);
    }

    ConstantMatrix(const int &r, const int &c) : GeneralMatrix<TYPE>(r, c, 1)
    {
        if (r == c)
        {
            GeneralMatrix<TYPE>::band_width.Set(r - 1, c - 1, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    ConstantMatrix(const int &n, const TYPE &x) : GeneralMatrix<TYPE>(n, n, 1)
    {
        GeneralMatrix<TYPE>::store[0] = x;
        GeneralMatrix<TYPE>::band_width.Set(n - 1, n - 1, true);
    }

    ConstantMatrix(const int &r, const int &c, const TYPE &x) : GeneralMatrix<TYPE>(r, c, 1)
    {
        GeneralMatrix<TYPE>::store[0] = x;

        if (r == c)
        {
            GeneralMatrix<TYPE>::band_width.Set(r - 1, c - 1, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    ConstantMatrix(const ConstantMatrix<TYPE>& gm)
    {
        GeneralMatrix<TYPE>::CopyMatrix(gm);
    }

    ~ConstantMatrix() {}

    ConstantMatrix<TYPE> & operator=(const BaseMatrix<TYPE>&);

    ConstantMatrix<TYPE> & operator=(const ConstantMatrix<TYPE> &m)
    {
        if (&m == this)
        {
            return *this;
        }
        GeneralMatrix<TYPE>::CopyMatrix(m);
        return *this;
    }

    ConstantMatrix<TYPE> & operator=(const TYPE &x)
    {
        GeneralMatrix<TYPE>::store[0] = x;
        return *this;
    }

    void operator<<(const BaseMatrix<TYPE>&);

    void operator<<(const TYPE &x)
    {
        GeneralMatrix<TYPE>::operator<<(x);
    }

    void operator<<(const int &x)
    {
        GeneralMatrix<TYPE>::operator<<(x);
    }

    TYPE& operator()(const int &, const int &);                  // access element

    TYPE operator()(const int &, const int &) const;             // access element

    MatrixType Type() const;

    TYPE Trace() const;

    std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const;

    std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
    {
        std::shared_ptr<LinearEquationSolver<TYPE> > solver(new ConstantSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        return solver;
    }

    void Solve(const BaseMatrix<TYPE>&, BaseMatrix<TYPE>&) const;

    void Resize(const int &, const int &);

    void Swap(ConstantMatrix<TYPE>& gm)
    {
        GeneralMatrix<TYPE>::Swap(gm);
    }

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
        mi.Clear();
        mi.Append(1, GeneralMatrix<TYPE>::ncols);
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
        mi.Clear();
        mi.Append(1, GeneralMatrix<TYPE>::nrows);
    }
};

template <typename TYPE>
inline void Swap(ConstantMatrix<TYPE>& A, ConstantMatrix<TYPE>& B)
{
    A.Swap(B);
}

#include "ConstantMatrix.cpp"

#endif //CONSTANT_MATRIX_H



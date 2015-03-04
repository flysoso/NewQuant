#ifndef IDENTIFY_MATRIX_CPP
#define IDENTIFY_MATRIX_CPP

#include "IdentityMatrix.h"

namespace NewQuant
{
    template <typename TYPE>
    IdentityMatrix<TYPE> & IdentityMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        assert(bm.BandWidth().Evalued());
        assert(bm.BandWidth().Upper() == bm.BandWidth().Lower() && bm.BandWidth().Lower() == 0);

        int n = bm.Nrows();
        if (bm.Search(*this) == 0)
        {
            Resize(n);
            operator()(1, 1) = bm(1, 1);
        }
        else
        {
            IdentityMatrix<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template <typename TYPE>
    void IdentityMatrix<TYPE>::operator<<(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return;
        }
        assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows && bm.Ncols() == GeneralMatrix<TYPE>::ncols);
        operator()(1, 1) = bm(1, 1);
    }

    template <typename TYPE>
    TYPE& IdentityMatrix<TYPE>::operator()(const int &m, const int &n)
    {
        assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
        if (m == n)
        {
            return GeneralMatrix<TYPE>::store[0];
        }
        else
        {
            GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
            return GeneralMatrix<TYPE>::zero_buff;
        }
    }

    template <typename TYPE>
    TYPE& IdentityMatrix<TYPE>::operator()(const int &m)
    {
        assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows);
        return GeneralMatrix<TYPE>::store[0];
    }

    template <typename TYPE>
    TYPE IdentityMatrix<TYPE>::operator()(const int &m, const int &n) const
    {
        assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
        if (m == n)
        {
            return GeneralMatrix<TYPE>::store[0];
        }
        else
        {
            return GeneralMatrix<TYPE>::zero;
        }
    }

    template <typename TYPE>
    TYPE IdentityMatrix<TYPE>::operator()(const int &m) const
    {
        assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows);
        return GeneralMatrix<TYPE>::store[0];
    }

    template <typename TYPE>
    MatrixType IdentityMatrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::IdentityMatrix);
    }

    template <typename TYPE>
    TYPE IdentityMatrix<TYPE>::Trace() const
    {
        TYPE sum = GeneralMatrix<TYPE>::store[0] * TYPE(GeneralMatrix<TYPE>::nrows);
        return sum;
    }

    template <typename TYPE>
    void IdentityMatrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
    {
        int n = GeneralMatrix<TYPE>::nrows;
        assert(n == in.Nrows());
        assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

        std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
        solver->Solve(in, out);
    }


    template <typename TYPE>
    void IdentityMatrix<TYPE>::Resize(const int &n)
    {
        assert(n > 0);
        GeneralMatrix<TYPE>::GeneralResize(n, n, 1);
    }
}
#endif //IDENTIFY_MATRIX_CPP


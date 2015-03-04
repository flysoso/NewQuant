#ifndef BAND_MATRIX_CPP
#define BAND_MATRIX_CPP

#include "BandMatrix.h"
#include "SquareMatrix.h"
#include "IdentityMatrix.h"
#include "LowerTriangularMatrix.h"
#include "UpperTriangularMatrix.h"
#include "DiagonalMatrix.h"
#include "DiagonalSolver.h"
#include "LowerBandSolver.h"
#include "UpperBandSolver.h"
#include "BandLUsolverPartialPivot.h"
#include "LUsolverPartialPivot.h"

namespace NewQuant
{
    template <typename TYPE>
    void BandMatrix<TYPE>::CornerClear() const
    {
        int i = GeneralMatrix<TYPE>::band_width.Lower();
        TYPE* s = GeneralMatrix<TYPE>::store;
        int bw = GeneralMatrix<TYPE>::band_width.Lower() + 1 + GeneralMatrix<TYPE>::band_width.Upper();

        while (i)
        {
            int j = i--;
            TYPE* sj = s;
            s += bw;
            while (j--)
            {
                *sj++ = GeneralMatrix<TYPE>::zero;
            }
        }
        i = GeneralMatrix<TYPE>::band_width.Upper();
        s = GeneralMatrix<TYPE>::store + GeneralMatrix<TYPE>::storage;
        while (i)
        {
            int j = i--;
            TYPE* sj = s;
            s -= bw;
            while (j--)
            {
                *(--sj) = GeneralMatrix<TYPE>::zero;
            }
        }
    }

    template <typename TYPE>
    BandMatrix<TYPE>::BandMatrix(const int &n, const int &lb, const int &ub) : GeneralMatrix<TYPE>(n, n, n*(lb + 1 + ub))
    {
        GeneralMatrix<TYPE>::band_width.Set(lb, ub, true);
        CornerClear();
    }

    template <typename TYPE>
    BandMatrix<TYPE> & BandMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        assert(bm.BandWidth().Evalued());
        int lb = bm.BandWidth().Lower(), ub = bm.BandWidth().Upper();
        int n = bm.Nrows();
        if (bm.Search(*this) == 0)
        {
            Resize(n, lb, ub);
            for (int i = 1; i <= ub; ++i)
            {
                for (int j = i + 1; j <= n; ++j)
                {
                    operator()(j - i, j) = bm(j - i, j);
                }
            }
            for (int i = 1; i <= lb; ++i)
            {
                for (int j = 1; j <= n - i; ++j)
                {
                    operator()(j + i, j) = bm(j + i, j);
                }
            }
            for (int i = 1; i <= n; ++i)
            {
                operator()(i, i) = bm(i, i);
            }
        }
        else
        {
            BandMatrix<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template <typename TYPE>
    void BandMatrix<TYPE>::operator<<(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return;
        }
        assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows && bm.Ncols() == GeneralMatrix<TYPE>::ncols);
        int lb = GeneralMatrix<TYPE>::band_width.Lower();
        int ub = GeneralMatrix<TYPE>::band_width.Upper();
        int n = GeneralMatrix<TYPE>::nrows;

        if (bm.Search(*this) == 0)
        {
            for (int i = 1; i <= ub; ++i)
            {
                for (int j = i + 1; j <= n; ++j)
                {
                    operator()(j - i, j) = bm(j - i, j);
                }
            }
            for (int i = 1; i <= lb; ++i)
            {
                for (int j = 1; j <= n - i; ++j)
                {
                    operator()(j + i, j) = bm(j + i, j);
                }
            }
            for (int i = 1; i <= n; ++i)
            {
                operator()(i, i) = bm(i, i);
            }
        }
        else
        {
            BandMatrix<TYPE> t(n, lb, ub);
            t << bm;
            this->Swap(t);
        }
    }

    template <typename TYPE>
    MatrixType BandMatrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::BandMatrix);
    }

    template <typename TYPE>
    TYPE& BandMatrix<TYPE>::operator()(const int &m, const int &n)
    {
        int w = GeneralMatrix<TYPE>::band_width.Upper() + GeneralMatrix<TYPE>::band_width.Lower() + 1;
        int i = GeneralMatrix<TYPE>::band_width.Lower() + n - m;
        assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n > 0 && n <= GeneralMatrix<TYPE>::ncols);
        if (i < 0 || i >= w)
        {
            GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
            return GeneralMatrix<TYPE>::zero_buff;
        }
        else
        {
            return GeneralMatrix<TYPE>::store[w*(m - 1) + i];
        }
    }

    template <typename TYPE>
    TYPE BandMatrix<TYPE>::operator()(const int &m, const int &n) const
    {
        int w = GeneralMatrix<TYPE>::band_width.Upper() + GeneralMatrix<TYPE>::band_width.Lower() + 1;
        int i = GeneralMatrix<TYPE>::band_width.Lower() + n - m;
        assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n > 0 && n <= GeneralMatrix<TYPE>::ncols);
        if (i < 0 || i >= w)
        {
            return GeneralMatrix<TYPE>::zero;
        }
        else
        {
            return GeneralMatrix<TYPE>::store[w*(m - 1) + i];
        }
    }

    template <typename TYPE>
    std::shared_ptr<GeneralMatrix<TYPE> > BandMatrix<TYPE>::MakeInv() const
    {
        int lbw = GeneralMatrix<TYPE>::band_width.Lower();
        int ubw = GeneralMatrix<TYPE>::band_width.Upper();
        int n = GeneralMatrix<TYPE>::nrows;
        std::shared_ptr<GeneralMatrix<TYPE> > inv;
        IdentityMatrix<TYPE> imat(n);
        if (lbw > 0 && ubw > 0)
        {
            inv.reset(new SquareMatrix<TYPE>(n));
        }
        if (ubw == 0 && lbw > 0)
        {
            inv.reset(new LowerTriangularMatrix<TYPE>(n));
        }
        if (ubw > 0 && lbw == 0)
        {
            inv.reset(new UpperTriangularMatrix<TYPE>(n));
        }
        if (ubw == 0 && lbw == 0)
        {
            inv.reset(new DiagonalMatrix<TYPE>(n));
        }
        Solve(imat, *inv);
        return inv;
    }

    template <typename TYPE>
    std::shared_ptr<LinearEquationSolver<TYPE> > BandMatrix<TYPE>::MakeSolver() const
    {
        std::shared_ptr<LinearEquationSolver<TYPE> > solver;
        int lbw = GeneralMatrix<TYPE>::band_width.Lower();
        int ubw = GeneralMatrix<TYPE>::band_width.Upper();
        int n = GeneralMatrix<TYPE>::nrows;
        if (lbw > 0 && ubw > 0)
        {
            if (lbw + ubw < n / 2)
            {
                solver.reset(new BandLUsolverPartialPivot<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            }
            else
            {
                solver.reset(new LUsolverPartialPivot<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            }
        }
        if (lbw > 0 && ubw == 0)
        {
            solver.reset(new LowerBandSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        }
        if (lbw == 0 && ubw > 0)
        {
            solver.reset(new UpperBandSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        }
        if (lbw == 0 && ubw == 0)
        {
            solver.reset(new DiagonalSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        }
        return solver;
    }

    template <typename TYPE>
    void BandMatrix<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        int n = GeneralMatrix<TYPE>::nrows;
        assert(n == in.Nrows());
        assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

        std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
        solver->Solve(in, out);
    }

    template <typename TYPE>
    void BandMatrix<TYPE>::Resize(const int &n, const int &lb, const int &ub)
    {
        assert(n > 0 && lb < n && ub < n);
        GeneralMatrix<TYPE>::GeneralResize(n, n, n*(lb + 1 + ub));
        GeneralMatrix<TYPE>::band_width.Set(lb, ub, true);
        CornerClear();
    }
}

#endif //BAND_MATRIX_CPP


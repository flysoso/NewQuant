#ifndef PERMUTE_MATRIX_H
#define PERMUTE_MATRIX_H

#include <math.h>
#include "GeneralMatrix.h"
#include "Array.h"
#include "PermuteSolver.h"

namespace NewQuant
{
    template<typename TYPE> class PermuteSolver;

    template<typename TYPE>
    class PermuteMatrix :public GeneralMatrix < TYPE >
    {
    private:
        static const TYPE one;
        int swap_times;
        Array<int> row_idx, col_idx;

        void AdjustBandWidth()
        {
            int min = 0, max = 0;
            for (int i = 1; i <= row_idx.Size(); ++i)
            {
                min = std::min(min, row_idx(i) - i);
                max = std::max(max, row_idx(i) - i);
            }
            GeneralMatrix<TYPE>::band_width.Set(std::abs(min), max, true);
        }

    public:
        PermuteMatrix() :GeneralMatrix<TYPE>(1, 1, 1), row_idx(1), col_idx(1), swap_times(0)
        {
            TYPE one(1);
            GeneralMatrix<TYPE>::store[0] = one;
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
            row_idx(1) = 1;
            col_idx(1) = 1;
        }

        PermuteMatrix(const int &n) :GeneralMatrix<TYPE>(n, n, 1), row_idx(n), col_idx(n), swap_times(0)
        {
            TYPE one(1);
            GeneralMatrix<TYPE>::store[0] = one;
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
            for (int i = 1; i <= n; ++i)
            {
                row_idx(i) = i;
                col_idx(i) = i;
            }
        }

        PermuteMatrix(const PermuteMatrix<TYPE> &pm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(pm);
            row_idx = pm.row_idx;
            col_idx = pm.col_idx;
            swap_times = pm.swap_times;
        }

        PermuteMatrix<TYPE> & operator = (const PermuteMatrix<TYPE> &pm)
        {
            if (&pm == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(pm);
            row_idx = pm.row_idx;
            col_idx = pm.col_idx;
            swap_times = pm.swap_times;
            return *this;
        }

        void InvEq(const PermuteMatrix<TYPE> &pm)
        {
            if (&pm == this)
            {
                row_idx.Swap(col_idx);
            }
            else
            {
                GeneralMatrix<TYPE>::CopyMatrix(pm);
                row_idx = pm.col_idx;
                col_idx = pm.row_idx;
                swap_times = pm.swap_times;
                GeneralMatrix<TYPE>::band_width.Set(pm.band_width.Upper(), pm.band_width.Lower(), true);
            }
        }

        void TranEq(const PermuteMatrix<TYPE> &pm)
        {
            if (&pm == this)
            {
                row_idx.Swap(col_idx);
            }
            else
            {
                GeneralMatrix<TYPE>::CopyMatrix(pm);
                row_idx = pm.col_idx;
                col_idx = pm.row_idx;
                swap_times = pm.swap_times;
                GeneralMatrix<TYPE>::band_width.Set(pm.band_width.Upper(), pm.band_width.Lower(), true);
            }
        }

        TYPE & operator () (const int &r, const int &c)
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            if (row_idx(r) != c)
            {
                return GeneralMatrix<TYPE>::zero_buff;
            }
            else
            {
                return GeneralMatrix<TYPE>::store[0];
            }
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            if (row_idx(r) != c)
            {
                return GeneralMatrix<TYPE>::zero;
            }
            else
            {
                GeneralMatrix<TYPE>::store[0] = one;
                return GeneralMatrix<TYPE>::store[0];
            }
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            mi.Clear();
            mi.Append(row_idx(r), row_idx(r));
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            mi.Clear();
            mi.Append(col_idx(c), col_idx(c));
        }

        MatrixType Type() const
        {
            return MatrixType(MatrixType::PermuteMatrix);
        }

        std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const
        {
            std::shared_ptr<PermuteMatrix<TYPE> > inv(new PermuteMatrix<TYPE>);
            inv->InvEq(*this);
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new PermuteSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
        {
            int n = GeneralMatrix<TYPE>::nrows;
            assert(n == in.Nrows());
            assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());
            this->MakeSolver()->Solve(in, out);
        }

        void SwapRow(const int &r1, const int &r2)
        {
            assert(r1 > 0 && r1 <= GeneralMatrix<TYPE>::nrows);
            assert(r2 > 0 && r2 <= GeneralMatrix<TYPE>::nrows);
            if (r1 == r2)
            {
                return;
            }
            col_idx(row_idx(r1)) = r2;
            col_idx(row_idx(r2)) = r1;
            row_idx.Swap(r1, r2);
            ++swap_times;
            AdjustBandWidth();
        }

        void SwapCol(const int &c1, const int &c2)
        {
            assert(c1 > 0 && c2 <= GeneralMatrix<TYPE>::ncols);
            assert(c1 > 0 && c2 <= GeneralMatrix<TYPE>::ncols);
            if (c1 == c2)
            {
                return;
            }
            row_idx(col_idx(c1)) = c2;
            row_idx(col_idx(c2)) = c1;
            col_idx.Swap(c1, c2);
            ++swap_times;
            AdjustBandWidth();
        }

        const int & SwapTimes()const
        {
            return swap_times;
        }

        void Swap(PermuteMatrix<TYPE> &p)
        {
            row_idx.Swap(p.row_idx);
            col_idx.Swap(p.col_idx);
            int t;
            t = swap_times;
            swap_times = p.swap_times;
            p.swap_times = t;
        }

        const int & RowIndex(const int &r) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            return row_idx(r);
        }

        const int & ColIndex(const int &c) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            return col_idx(c);
        }

    private:
        void operator << (const BaseMatrix<TYPE> &bm){}

        void operator << (const TYPE &x){}

        void operator << (const int &x){}

        void operator *= (const TYPE &x){}

        void operator /= (const TYPE &x){}
    };

    template<typename TYPE>
    const TYPE PermuteMatrix<TYPE>::one(1);

    template<typename TYPE>
    void Swap(PermuteMatrix<TYPE> &p1, PermuteMatrix<TYPE> &p2)
    {
        p1.Swap(p2);
    }
}
#endif //PERMUTE_MATRIX_H

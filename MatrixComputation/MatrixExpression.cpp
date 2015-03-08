#ifndef MATRIX_EXPRESSION_CPP
#define MATRIX_EXPRESSION_CPP

#include "MatrixExpression.h"
#include "IdentityMatrix.h"
#include "DiagonalMatrix.h"
#include "LowerTriangularMatrix.h"
#include "UpperTriangularMatrix.h"
#include "SquareMatrix.h"
#include "BandLUsolverPartialPivot.h"
#include "LowerBandSolver.h"
#include "UpperBandSolver.h"

namespace NewQuant
{
    template<typename TYPE> class DiagonalSolver;
    template<typename TYPE> class LowerBandSolver;
    template<typename TYPE> class UpperBandSolver;
    template<typename TYPE> class BandLUsolverPartialPivot;
    template<typename TYPE> class LUsolverPartialPivot;

    template<typename TYPE>
    std::shared_ptr<GeneralMatrix<TYPE> > MatrixExpression<TYPE>::MakeInv()const
    {
        assert(nrows == ncols);

        int lbw = band_width.Lower(), ubw = band_width.Upper();
        int n = nrows;
        std::shared_ptr<GeneralMatrix<TYPE> > inv;

        if (lbw == 0 && ubw == 0)
        {
            inv.reset(new DiagonalMatrix<TYPE>(n));
        }
        if (lbw > 0 && ubw == 0)
        {
            inv.reset(new LowerTriangularMatrix<TYPE>(n));
        }
        if (lbw == 0 && ubw > 0)
        {
            inv.reset(new UpperTriangularMatrix<TYPE>(n));
        }
        if (lbw > 0 && ubw > 0)
        {
            inv.reset(new SquareMatrix<TYPE>(n));
        }
        IdentityMatrix<TYPE> imat(n);
        Solve(imat, *inv);
        return inv;
    }

    template<typename TYPE>
    std::shared_ptr<LinearEquationSolver<TYPE> > MatrixExpression<TYPE>::MakeSolver()const
    {
        assert(nrows == ncols);

        int lbw = band_width.Lower(), ubw = band_width.Upper();
        std::shared_ptr<LinearEquationSolver<TYPE> > solve;
        TYPE e = Precision<TYPE>::GetPrecision();

        if (lbw == 0 && ubw == 0)
        {
            solve.reset(new DiagonalSolver<TYPE>(*this, e));
        }
        if (lbw != 0 && ubw == 0)
        {
            solve.reset(new LowerBandSolver<TYPE>(*this, e));
        }
        if (lbw == 0 && ubw != 0)
        {
            solve.reset(new UpperBandSolver<TYPE>(*this, e));
        }
        if (lbw != 0 && ubw != 0)
        {
            if (lbw + ubw < nrows / 2)
            {
                solve.reset(new BandLUsolverPartialPivot<TYPE>(*this, e));
            }
            else
            {
                solve.reset(new LUsolverPartialPivot<TYPE>(*this, e));
            }
        }

        return solve;
    }

    template<typename TYPE>
    std::ostream& operator<<(std::ostream& s, const MatrixExpression<TYPE>& X)
    {
        using namespace std;
        ostream::fmtflags f = s.flags();
        if (f & ios::scientific)
        {
            s.setf(ios::scientific, ios::floatfield);
        }
        else
        {
            s.setf(ios::fixed, ios::floatfield);
        }

        std::streamsize w = s.width();
        int nr = X.Nrows(), nc = X.Ncols();
        MatrixIndex<TYPE> mi;
        for (int i = 1; i <= nr; ++i)
        {
            X.GetRowIndex(i, mi);
            for (int j = 1; j <= nc; ++j)
            {
                if (mi.HaveIndex(j))
                {
                    s.width(w);
                    s << X(i, j) << ' ';
                }
                else
                {
                    s.width(w);
                    s << ' ' << ' ';
                }
            }
            s << '\n';
        }
        s << flush;
        s.flags();
        return s;
    }

}

#endif //MATRIX_EXPRESSION_CPP


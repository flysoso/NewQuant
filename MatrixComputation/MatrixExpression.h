#ifndef MATRIX_EXPRESSION_H
#define MATRIX_EXPRESSION_H

#include "BaseMatrix.h"
#include "MatrixBandWidth.h"
#include "MatrixType.h"
#include "GeneralMatrix.h"
#include "MatrixIndex.h"

#include "../ExceptionClass/NotDefinedException.h"

namespace NewQuant
{
    template<typename TYPE> class LinearEquationSolver;
    template<typename TYPE> class Matrix;
    template<typename TYPE> class DiagonalMatrix;
    template<typename TYPE> class LowerTriangularMatrix;
    template<typename TYPE> class SquareMatrix;

    template<typename TYPE>
    class MatrixExpression :public BaseMatrix < TYPE >
    {
    protected:
        int nrows, ncols;
        MatrixBandWidth<TYPE> band_width;

        MatrixExpression() {}

        MatrixExpression(const MatrixExpression &m) :
            nrows(m.nrows), ncols(m.ncols), band_width(m.band_width) {}

        void Set(const int &r, const int &c)
        {
            assert(r > 0 && c > 0);
            nrows = r, ncols = c;
        }
    public:
        ~MatrixExpression() {}

        int Nrows() const
        {
            return nrows;
        }

        int Ncols() const
        {
            return ncols;
        }

        virtual void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const = 0;

        virtual void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const = 0;

        virtual int Search(const GeneralMatrix<TYPE> &m) const = 0;

        const MatrixBandWidth<TYPE> & BandWidth() const
        {
            return band_width;
        }

        virtual TYPE operator () (const int &, const int &) const = 0;

        virtual TYPE & operator () (const int &r, const int &c)
        {
            Singleton<Tracer>::Instance()->AddMessage("TYPE & MatrixExpression::operator () (r, c)");
            throw NotDefinedException("TYPE & operator () (r, c)", "The Majority Of Matrix Expression Classes");
        }

        virtual std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const;

        virtual MatrixType Type() const
        {
            return MatrixType(MatrixType::MatrixExpression);
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const;

        void Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
        {
            this->MakeSolver()->Solve(in, out);
        }

        LogAndSign<TYPE> LogDeterminant() const
        {
            return this->MakeSolver()->LogDeterminabt();
        }
    };

    template<typename TYPE, typename MATRIX>
    class UnitaryMatrixExpression : public MatrixExpression < TYPE >
    {
    protected:
        const MATRIX &mat;
    public:
        UnitaryMatrixExpression(const MATRIX &m) : mat(m) {}

        UnitaryMatrixExpression(const UnitaryMatrixExpression &um) :
            mat(um.mat), MatrixExpression<TYPE>(um) {}

        ~UnitaryMatrixExpression() {}

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return mat.Search(m);
        }
    };

    template<typename TYPE, typename MATRIX1, typename MATRIX2>
    class BinaryMatrixExpression : public MatrixExpression < TYPE >
    {
    protected:
        const MATRIX1 &mat1;
        const MATRIX2 &mat2;
    public:
        BinaryMatrixExpression(const MATRIX1 &m1, const MATRIX2 &m2) :
            mat1(m1), mat2(m2), MatrixExpression<TYPE>() {}

        BinaryMatrixExpression(const BinaryMatrixExpression &bm) :
            mat1(bm.mat1), mat2(bm.mat2), MatrixExpression<TYPE>(bm) {}
        ~BinaryMatrixExpression() {}

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return mat1.Search(m) + mat2.Search(m);
        }
    };

    template<typename TYPE>
    std::ostream& operator<<(std::ostream& s, const MatrixExpression<TYPE>&);

    template<typename TYPE>
    void FindAbsMax(const MatrixExpression<TYPE> &m, TYPE &x, int &r, int &c)
    {
        int row = m.Nrows();
        int col = m.Ncols();

        r = c = 1;
        x = m(1, 1);
        for (int i = 1; i <= row; ++i)
        {
            for (int j = 1; j <= col; ++j)
            {
                if (fabs(m(i, j)) > fabs(x))
                {
                    r = i, c = j;
                    x = m(i, j);
                }
            }
        }
    }

}
#include "MatrixExpression.cpp"

#endif //MATRIX_EXPRESSION_H

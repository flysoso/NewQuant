#ifndef QR_SOLVER_H
#define QR_SOLVER_H

#include "LeastSquareSolver.h"
#include "SquareMatrix.h"
#include "Matrix.h"
#include "UpperTriangularMatrix.h"
#include "PermuteMatrix.h"
#include "MatrixExpression.h"

template<typename TYPE> class QRcombine;

template<typename TYPE>
class QRsolver :public LeastSquareSolver < TYPE >
{
protected:
    TYPE epsilon;
    SquareMatrix<TYPE> qr_q;
    Matrix<TYPE> qr_a;
    UpperTriangularMatrix<TYPE> qr_r;
    PermuteMatrix<TYPE> right;
    QRcombine<TYPE> combine;
    const BaseMatrix<TYPE> &mat;
public:
    QRsolver(const BaseMatrix<TYPE> &, const TYPE &);

    ~QRsolver(){}

    const SquareMatrix<TYPE> & Q() const
    {
        return qr_q;
    }

    const UpperTriangularMatrix<TYPE> & R() const
    {
        return qr_r;
    }

    const PermuteMatrix<TYPE> & Right() const
    {
        return right;
    }
};

template<typename TYPE>
class QRcombine :public MatrixExpression < TYPE >
{
private:
    Matrix<TYPE> &mat;
    UpperTriangularMatrix<TYPE> &upper;
public:
    QRcombine(Matrix<TYPE> &, UpperTriangularMatrix<TYPE> &);

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        mi.Clear();
        mi.Append(1, MatrixExpression<TYPE>::ncols);
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        mi.Clear();
        mi.Append(1, MatrixExpression<TYPE>::nrows);
    }

    int Search(const GeneralMatrix<TYPE> &m) const
    {
        return mat.Search(m) + upper.Search(m);
    }

    TYPE operator () (const int &r, const int &c) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        if (c >= r)
        {
            return upper(r, c);
        }
        else
        {
            return mat(r, c);
        }
    }

    TYPE & operator () (const int &r, const int &c)
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        if (c >= r)
        {
            return upper(r, c);
        }
        else
        {
            return mat(r, c);
        }
    }

    void SwapCol(const int &c1, const int &c2)
    {
        assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
        assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
        TYPE t;
        for (int i = 1; i <= dim; ++i)
        {
            t = operator()(i, c1);
            operator()(i, c1) = operator()(i, c2);
            operator()(i, c2) = t;
        }
    }

    void SwapCol(const int &c1, const int &c2, const int &r1, const int &r2)
    {
        assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
        assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
        assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
        assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
        TYPE t;
        for (int i = r1; i <= r2; ++i)
        {
            t = operator()(i, c1);
            operator()(i, c1) = operator()(i, c2);
            operator()(i, c2) = t;
        }
    }

};

template<typename TYPE>
QRsolver<TYPE>::QRsolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
LeastSquareSolver<TYPE>(), mat(bm), qr_r(bm.Ncols()),
qr_a(bm.Nrows(), bm.Ncols()), qr_q(bm.Nrows()),
right(bm.Ncols()), combine(qr_a, qr_r), epsilon(e)
{
    static const TYPE zero(0), one(1);

    qr_q << zero;

    for (int j = 1; j <= qr_q.Ncols(); ++j)
    {
        qr_q(j, j) = one;
    }


}

template<typename TYPE>
QRcombine<TYPE>::QRcombine(Matrix<TYPE> &m, UpperTriangularMatrix<TYPE> &up) :mat(m), upper(up)
{
    int r = m.Nrows(), c = m.Ncols();
    MatrixExpression<TYPE>::Set(r, c);
    if (r == c)
    {
        MatrixExpression<TYPE>::band_width.Set(r - 1, r - 1, true);
    }
    else
    {
        MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
    }
}

#endif //QR_SOLVER_H

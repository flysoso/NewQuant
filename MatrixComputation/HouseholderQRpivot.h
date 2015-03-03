#ifndef HOUSEHOLDER_QR_PIVOT_H
#define HOUSEHOLDER_QR_PIVOT_H

#include "QRsolver.h"
#include "ColumnVector.h"
#include "RowVector.h"
#include "GetSubMatrix.h"
#include "ConstGetSubMatrix.h"
#include "TransposedMatrix.h"
#include "PermutedMatrix.h"
#include "Array.h"
#include "ProgramException.h"

template<typename TYPE> class BaseMatrix;
template<typename TYPE> class GeneralMatrix;

template<typename TYPE>
class HouseholderQRpivot :public QRsolver < TYPE >
{
private:
    int rank;

    void HouseholderVector(const MatrixExpression<TYPE> &, ColumnVector<TYPE> &, TYPE &) const;

    void HouseholderTransform();
public:
    HouseholderQRpivot(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        QRsolver<TYPE>(bm, e), rank(0)
    {
        QRsolver<TYPE>::qr_a << bm;
        HouseholderTransform();
    }

    ~HouseholderQRpivot(){}
    const int & Rank()const
    {
        return rank;
    }
    void SolveLS(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;
};

template<typename TYPE>
void HouseholderQRpivot<TYPE>::HouseholderVector(const MatrixExpression<TYPE> &x, ColumnVector<TYPE> &hv, TYPE &beta) const
{
    assert(x.Ncols() == 1);
    static const TYPE one(1), zero(0), two(2);
    int n = x.Nrows();
    TYPE sigma = (t(x)*x)(1, 1) - x(1, 1)*x(1, 1);
    hv = x;
    hv(1) = one;

    const TYPE &e = QRsolver<TYPE>::epsilon;

    if (sigma <= e)
    {
        beta = zero;
    }
    else
    {
        TYPE mu = sqrt(x(1, 1)*x(1, 1) + sigma), v;
        if (x(1, 1) <= zero)
        {
            hv(1) = x(1, 1) - mu;
        }
        else
        {
            hv(1) = -sigma / (x(1, 1) + mu);
        }
        v = hv(1);
        beta = two*v*v / (sigma + v*v);
        hv /= v;
    }
}

template<typename TYPE>
void HouseholderQRpivot<TYPE>::HouseholderTransform()
{
    Matrix<TYPE> &A = QRsolver<TYPE>::qr_a;
    SquareMatrix<TYPE> &Q = QRsolver<TYPE>::qr_q;
    PermuteMatrix<TYPE> &pm = QRsolver<TYPE>::right;
    UpperTriangularMatrix<TYPE> &R = QRsolver<TYPE>::qr_r;
    const TYPE &e = QRsolver<TYPE>::epsilon;
    int m = A.Nrows(), n = A.Ncols(), idx_max;
    TYPE beta, x;
    ColumnVector<TYPE> v;
    RowVector<TYPE> w;
    Array<TYPE> norms;
    for (int i = 1; i <= n; ++i)
    {
        norms.Resize(n - i + 1);
        for (int j = 1; j <= norms.Size(); ++j)
        {
            norms(j) = (t(sub(A, i, m, i, n))*sub(A, i, m, i, n))(j, j);
        }
        norms.Max(x, idx_max);
        A.SwapCol(i, idx_max + i - 1);  //col skip is i-1
        pm.SwapCol(i, idx_max + i - 1);

        HouseholderVector(sub(A, i, m, i, i), v, beta);
        w = t(v)*sub(A, i, m, i, n);
        sub(A, i, m, i, n) -= beta*v*w;

        if (fabs(A(i, i)) <= e)
        {
            LeastSquareSolver<TYPE>::fail = true;
            return;
        }

        ++rank;

        w = t(sub(Q, 1, m, i, m)*v);
        sub(Q, 1, m, i, m) -= beta*t(v*w);
    }

    R.Resize(rank);
    R << sub(A, 1, rank, 1, rank);
}

template<typename TYPE>
void HouseholderQRpivot<TYPE>::SolveLS(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
{
    const SquareMatrix<TYPE> &Q = QRsolver<TYPE>::qr_q;
    const UpperTriangularMatrix<TYPE> &R = QRsolver<TYPE>::qr_r;
    const PermuteMatrix<TYPE> &P = QRsolver<TYPE>::right;
    assert(in.Nrows() == Q.Nrows());
    assert(in.Ncols() == out.Ncols());
    assert(out.Nrows() == R.Ncols());

    if (LeastSquareSolver<TYPE>::IsFailed())
    {
        throw ProgramException("This Matrix Is Column Rank Deficiency", QRsolver<TYPE>::mat);
    }
    PermuteMatrix<TYPE> inv_p;
    inv_p.InvEq(P);
    PermutedMatrix<TYPE, BaseMatrix<TYPE> > perm_out(out, inv_p, PermutedMatrix<TYPE, BaseMatrix<TYPE> >::PermuteType::row_perm);
    int m = in.Ncols(), n = R.Ncols();
    R.Solve(c_sub(t(Q)*in, 1, n, 1, m), perm_out);
}

#endif //HOUSEHOLDER_QR_PIVOT_H

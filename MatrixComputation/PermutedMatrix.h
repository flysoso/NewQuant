#ifndef PERMUTED_MATRIX_H
#define PERMUTED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template <typename TYPE> class PermuteMatrix;

    template <typename TYPE, typename MATRIX>
    class PermutedMatrix :public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        enum PermuteType{ row_perm, col_perm };
    private:
        const PermuteMatrix<TYPE> &perm_mat;
        PermuteType type;
        MATRIX &mat_copy;
    public:
        PermutedMatrix(MATRIX &m, const PermuteMatrix<TYPE> &pm, const PermuteType &t) :
            UnitaryMatrixExpression < TYPE, MATRIX >(m), perm_mat(pm), type(t), mat_copy(m)
        {
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());

            switch (type)
            {
            case row_perm:
                MatrixExpression<TYPE>::band_width = Mult(pm.BandWidth(), m.BandWidth(), MatrixExpression<TYPE>::nrows);
                break;
            case col_perm:
                MatrixExpression<TYPE>::band_width = Mult(m.BandWidth(), pm.BandWidth(), MatrixExpression<TYPE>::nrows);
                break;
            }
        }

        ~PermutedMatrix(){}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            switch (type)
            {
            case row_perm:
                UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(perm_mat.RowIndex(r), mi);
                break;
            case col_perm:
                mi.Clear();
                mi.Append(1, MatrixExpression<TYPE>::ncols);
                break;
            }
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            switch (type)
            {
            case row_perm:
                mi.Clear();
                mi.Append(1, MatrixExpression<TYPE>::nrows);
                break;
            case col_perm:
                UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetColIndex(perm_mat.ColIndex(c), mi);
                break;
            }
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            switch (type)
            {
            case row_perm:
                return UnitaryMatrixExpression<TYPE, MATRIX>::mat(perm_mat.RowIndex(r), c);
            case col_perm:
                return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, perm_mat.ColIndex(c));
            }
        }

        TYPE & operator () (const int &r, const int &c)
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            switch (type)
            {
            case row_perm:
                return mat_copy(perm_mat.RowIndex(r), c);
            case col_perm:
                return mat_copy(r, perm_mat.ColIndex(c));
            }
        }
    };


    // GeneralMatrix
    template <typename TYPE>
    PermutedMatrix<TYPE, GeneralMatrix<TYPE> > perm(GeneralMatrix<TYPE> &mat, const PermuteMatrix<TYPE> &pm)
    {
        assert(mat.Ncols() == pm.Nrows());
        return PermutedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, pm, PermutedMatrix<TYPE, GeneralMatrix<TYPE> >::PermuteType::col_perm);
    }

    template <typename TYPE>
    PermutedMatrix<TYPE, GeneralMatrix<TYPE> > perm(const PermuteMatrix<TYPE> &pm, GeneralMatrix<TYPE> &mat)
    {
        assert(mat.Nrows() == pm.Ncols());
        return PermutedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, pm, PermutedMatrix<TYPE, GeneralMatrix<TYPE> >::PermuteType::row_perm);
    }

    template <typename TYPE>
    PermutedMatrix<TYPE, PermuteMatrix<TYPE> > perm(const PermuteMatrix<TYPE> &pm, PermuteMatrix<TYPE> &mat)
    {
        assert(mat.Nrows() == pm.Ncols());
        return PermutedMatrix<TYPE, PermuteMatrix<TYPE> >(mat, pm, PermutedMatrix<TYPE, PermuteMatrix<TYPE> >::PermuteType::row_perm);
    }

    // MatrixExpression
    template <typename TYPE>
    PermutedMatrix<TYPE, MatrixExpression<TYPE> > perm(MatrixExpression<TYPE> &mat, const PermuteMatrix<TYPE> &pm)
    {
        assert(mat.Ncols() == pm.Nrows());
        return PermutedMatrix<TYPE, MatrixExpression<TYPE> >(mat, pm, PermutedMatrix<TYPE, MatrixExpression<TYPE> >::PermuteType::col_perm);
    }

    template <typename TYPE>
    PermutedMatrix<TYPE, MatrixExpression<TYPE> > perm(const PermuteMatrix<TYPE> &pm, MatrixExpression<TYPE> &mat)
    {
        assert(mat.Nrows() == pm.Ncols());
        return PermutedMatrix<TYPE, MatrixExpression<TYPE> >(mat, pm, PermutedMatrix<TYPE, MatrixExpression<TYPE> >::PermuteType::row_perm);
    }

    // BaseMatrix
    template <typename TYPE>
    PermutedMatrix<TYPE, BaseMatrix<TYPE> > perm(BaseMatrix<TYPE> &mat, const PermuteMatrix<TYPE> &pm)
    {
        assert(mat.Ncols() == pm.Nrows());
        return PermutedMatrix<TYPE, BaseMatrix<TYPE> >(mat, pm, PermutedMatrix<TYPE, BaseMatrix<TYPE> >::PermuteType::col_perm);
    }

    template <typename TYPE>
    PermutedMatrix<TYPE, BaseMatrix<TYPE> > perm(const PermuteMatrix<TYPE> &pm, BaseMatrix<TYPE> &mat)
    {
        assert(mat.Nrows() == pm.Ncols());
        return PermutedMatrix<TYPE, BaseMatrix<TYPE> >(mat, pm, PermutedMatrix<TYPE, BaseMatrix<TYPE> >::PermuteType::row_perm);
    }
}
#endif //PERMUTED_MATRIX_H


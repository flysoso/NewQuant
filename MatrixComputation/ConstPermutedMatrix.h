#ifndef CONST_PERMUTED_MATRIX_H
#define CONST_PERMUTED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template <typename TYPE> class PermuteMatrix;

    template <typename TYPE, typename MATRIX>
    class ConstPermutedMatrix :public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        enum PermuteType{ row_perm, col_perm };
    private:
        const PermuteMatrix<TYPE> &perm_mat;
        PermuteType type;
    public:
        ConstPermutedMatrix(const MATRIX &m, const PermuteMatrix<TYPE> &pm, const PermuteType &t) :
            UnitaryMatrixExpression < TYPE, MATRIX >(m), perm_mat(pm), type(t)
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

        ~ConstPermutedMatrix(){}

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
            default:
                return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, perm_mat.ColIndex(c));
            }
        }

    };


    // GeneralMatrix
    template <typename TYPE>
    ConstPermutedMatrix<TYPE, GeneralMatrix<TYPE> > c_perm(const GeneralMatrix<TYPE> &mat, const PermuteMatrix<TYPE> &pm)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, GeneralMatrix<TYPE> >::PermuteType::col_perm);
    }

    template <typename TYPE>
    ConstPermutedMatrix<TYPE, GeneralMatrix<TYPE> > c_perm(const PermuteMatrix<TYPE> &pm, const GeneralMatrix<TYPE> &mat)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, GeneralMatrix<TYPE> >::PermuteType::row_perm);
    }

    template <typename TYPE>
    ConstPermutedMatrix<TYPE, PermuteMatrix<TYPE> > c_perm(const PermuteMatrix<TYPE> &pm, const PermuteMatrix<TYPE> &mat)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, PermuteMatrix<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, PermuteMatrix<TYPE> >::PermuteType::row_perm);
    }

    // MatrixExpression
    template <typename TYPE>
    ConstPermutedMatrix<TYPE, MatrixExpression<TYPE> > c_perm(const MatrixExpression<TYPE> &mat, const PermuteMatrix<TYPE> &pm)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, MatrixExpression<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, MatrixExpression<TYPE> >::PermuteType::col_perm);
    }

    template <typename TYPE>
    ConstPermutedMatrix<TYPE, MatrixExpression<TYPE> > c_perm(const PermuteMatrix<TYPE> &pm, const MatrixExpression<TYPE> &mat)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, MatrixExpression<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, MatrixExpression<TYPE> >::PermuteType::row_perm);
    }

    // BaseMatrix
    template <typename TYPE>
    ConstPermutedMatrix<TYPE, BaseMatrix<TYPE> > c_perm(const BaseMatrix<TYPE> &mat, const PermuteMatrix<TYPE> &pm)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, BaseMatrix<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, BaseMatrix<TYPE> >::PermuteType::col_perm);
    }

    template <typename TYPE>
    ConstPermutedMatrix<TYPE, BaseMatrix<TYPE> > c_perm(const PermuteMatrix<TYPE> &pm, const BaseMatrix<TYPE> &mat)
    {
        assert(mat.Ncols() == pm.Nrows());
        return ConstPermutedMatrix<TYPE, BaseMatrix<TYPE> >(mat, pm, ConstPermutedMatrix<TYPE, BaseMatrix<TYPE> >::PermuteType::row_perm);
    }
}
#endif //CONST_PERMUTED_MATRIX_H


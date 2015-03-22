#ifndef GENERAL_MATRIX_H
#define GENERAL_MATRIX_H

#include "BaseMatrix.h"
#include "LogAndSign.h"
#include "MatrixType.h"
#include "MatrixBandWidth.h"
#include "MatrixIndex.h"
#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class LinearEquationSolver;

    template<typename TYPE> class MatrixExpression;

    template<typename TYPE> class Matrix;
    template<typename TYPE> class SquareMatrix;

    template<typename TYPE> class RowVector;
    template<typename TYPE> class ColumnVector;
    template<typename TYPE> class SymmetricMatrix;
    template<typename TYPE> class UpperTriangularMatrix;
    template<typename TYPE> class LowerTriangularMatrix;
    template<typename TYPE> class DiagonalMatrix;

    template<typename TYPE> class BandMatrix;
    template<typename TYPE> class LowerBandMatrix;
    template<typename TYPE> class UpperBandMatrix;
    template<typename TYPE> class SymmetricBandMatrix;
    template<typename TYPE> class TridiagonalMatrix;

    /// The classes for matrices that can contain data are derived from this.
    template<typename TYPE>
    class GeneralMatrix :public BaseMatrix < TYPE >
    {
    protected:

        int nrows, ncols;               // dimensions
        int storage;                    // total store required
        TYPE* store;                    // point to store (NULL = not set)
        MatrixBandWidth<TYPE> band_width;

        static const TYPE zero;
        TYPE zero_buff;

        GeneralMatrix();                        // initialise with no store

        GeneralMatrix(const int &, const int &, const int &, const MatrixBandWidth<TYPE> &);

        GeneralMatrix(const int &, const int &, const int &);

        void Add(const TYPE &);                         // add TYPE to this

        void NegAdd(const TYPE &);                      // this = this - TYPE

        void Multiply(const TYPE &);                    // multiply this by TYPE

        void Negate();                                   // change sign

        void ReverseElements();                       // internal reverse of elements

        TYPE* GetStore() const                       // get store or copy
        {
            return store;
        }

        void CopyMatrix(const GeneralMatrix<TYPE> &);   // used by = and initialise

        void GeneralResize(const int &, const int &, const int &);                     // change dimensions

        void PlusEqual(const GeneralMatrix<TYPE>& gm);

        void SP_Equal(const GeneralMatrix<TYPE>& gm);

        void MinusEqual(const GeneralMatrix<TYPE>& gm);

        void Swap(GeneralMatrix<TYPE>& gm);                // Swap values
    public:
        virtual ~GeneralMatrix();   // delete store if set

        virtual void operator << (const BaseMatrix<TYPE> &) = 0;

        virtual void operator << (const TYPE &);      // set matrix to constant

        virtual void operator << (const int &);       // set matrix to constant

        void operator *= (const TYPE &);

        void operator /= (const TYPE &r)
        {
            static const TYPE one(1);
            operator*=(one / r);
        }

        void ChangeSign()
        {
            Negate();
        }

        int Search(const GeneralMatrix<TYPE> &s) const
        {
            return (&s == this) ? 1 : 0;
        }

        const MatrixBandWidth<TYPE> & BandWidth() const
        {
            return band_width;
        }

        virtual void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const = 0;

        virtual void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const = 0;

        virtual TYPE & operator () (const int &r, const int &c) = 0;

        virtual TYPE operator () (const int &r, const int &c) const = 0;

        virtual MatrixType Type() const = 0;                  // type of a matrix

        int Nrows() const
        {
            return nrows;    // get dimensions
        }

        int Ncols() const
        {
            return ncols;
        }

        const int & Storage() const
        {
            return storage;
        }

        TYPE* Store() const
        {
            return store;
        }

        bool IsZero() const;    // test matrix has all zeros

        virtual std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const = 0;

        virtual std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const = 0;

        virtual void Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const = 0;

        virtual TYPE Trace() const;

        LogAndSign<TYPE> LogDeterminant() const
        {
            return this->MakeSolver()->LogDeterminant();
        }

    };

    template<typename TYPE>
    inline bool IsZero(const GeneralMatrix<TYPE>& A)
    {
        return A.IsZero();
    }

    template<typename TYPE>
    void AddTo(const GeneralMatrix<TYPE> &from, GeneralMatrix<TYPE> &to)
    {
        assert(from.Storage() == to.Storage());
        TYPE *s = to.Store();
        TYPE *f = from.Store();
        int i = (to.Storage() >> 2);
        while (i--)
        {
            *s++ += *f++;
            *s++ += *f++;
            *s++ += *f++;
            *s++ += *f++;
        }
        i = to.Storage() & 3;
        while (i--)
        {
            *s++ += *f++;
        }
    }

    template<typename TYPE>
    std::ostream& operator<<(std::ostream& s, const GeneralMatrix<TYPE>& X);

    template<typename TYPE>
    void FindAbsMax(const GeneralMatrix<TYPE> &m, TYPE &x, int &r, int &c)
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

#include "GeneralMatrix.cpp"

#endif //GENERAL_MATRIX_H



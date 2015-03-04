#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H

#include "include.h"
#include "MatrixIndex.h"

namespace NewQuant
{
    class MatrixType;
    template<typename TYPE> class MatrixIndex;
    template<typename TYPE> class MatrixBandWidth;
    template<typename TYPE> class GeneralMatrix;

    template<typename TYPE>
    class BaseMatrix
    {
    protected:
        BaseMatrix(){}
    public:
        virtual TYPE & operator()(const int &, const int &) = 0;
        virtual TYPE operator () (const int &, const int &) const = 0;
        virtual int Nrows()const = 0;
        virtual int Ncols()const = 0;
        virtual const MatrixBandWidth<TYPE> & BandWidth() const = 0;
        virtual MatrixType Type() const = 0;
        virtual int Search(const GeneralMatrix<TYPE> &s) const = 0;
        virtual void GetRowIndex(const int &, MatrixIndex<TYPE> &) const = 0;
        virtual void GetColIndex(const int &, MatrixIndex<TYPE> &) const = 0;
    };
}

#endif //BASE_MATRIX_H

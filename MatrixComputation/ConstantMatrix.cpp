#ifndef CONSTANT_MATRIX_CPP
#define CONSTANT_MATRIX_CPP

#include "ConstantMatrix.h"
#include "SingularException.h"

namespace NewQuant
{
    template<typename TYPE>
    ConstantMatrix<TYPE> & ConstantMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }

        int r = bm.Nrows(), c = bm.Ncols();
        Resize(r, c);
        operator()(1, 1) = bm(1, 1);
        return *this;
    }

    template<typename TYPE>
    void ConstantMatrix<TYPE>::operator<<(const BaseMatrix<TYPE> &bm)
    {
        assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows && bm.Ncols() == GeneralMatrix<TYPE>::ncols);
        if (&bm == this)
        {
            return;
        }
        operator()(1, 1) = bm(1, 1);
    }

    template<typename TYPE>
    TYPE& ConstantMatrix<TYPE>::operator()(const int &m, const int &n)
    {
        assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
        return GeneralMatrix<TYPE>::store[0];
    }

    template<typename TYPE>
    TYPE ConstantMatrix<TYPE>::operator()(const int &m, const int &n) const
    {
        assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
        return GeneralMatrix<TYPE>::store[0];
    }

    template<typename TYPE>
    MatrixType ConstantMatrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::ConstantMatrix);
    }

    template<typename TYPE>
    TYPE ConstantMatrix<TYPE>::Trace() const
    {
        int r = GeneralMatrix<TYPE>::nrows, c = GeneralMatrix<TYPE>::ncols;
        assert(r == c);
        TYPE sum = GeneralMatrix<TYPE>::store[0] * TYPE(GeneralMatrix<TYPE>::nrows);
        return sum;
    }

    template<typename TYPE>
    std::shared_ptr<GeneralMatrix<TYPE> > ConstantMatrix<TYPE>::MakeInv() const
    {
        assert(GeneralMatrix<TYPE>::nrows == GeneralMatrix<TYPE>::ncols);
        std::shared_ptr<GeneralMatrix<TYPE> > inv;
        TYPE x = operator()(1, 1);
        const static TYPE one(1);

        if (GeneralMatrix<TYPE>::nrows != 1 || fabs(x) <= Precision<TYPE>::GetPrecision())
        {
            Singleton<Tracer>::Instance()->AddMessage("ConstantMatrix::MakeInv()");
            throw SingularException(*this);
        }
        else
        {
            inv.reset(new ConstantMatrix<TYPE>(1, one / x));
        }
        return inv;
    }

    template<typename TYPE>
    void ConstantMatrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
    {
        int n = GeneralMatrix<TYPE>::nrows;
        assert(n == in.Nrows());
        assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

        std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
        solver->Solve(in, out);
    }

    template<typename TYPE>
    void ConstantMatrix<TYPE>::Resize(const int &r, const int &c)
    {
        GeneralMatrix<TYPE>::GeneralResize(r, c, 1);
    }
}
#endif //IDENTIFY_MATRIX_CPP


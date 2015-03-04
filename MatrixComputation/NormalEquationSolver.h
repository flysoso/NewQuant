#ifndef NORMAL_EQUATION_SOLVER_H
#define NORMAL_EQUATION_SOLVER_H

#include "LeastSquareSolver.h"
#include "CholeskySolver.h"
#include "TransposedMatrix.h"
#include "MultipliedMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;

    template<typename TYPE>
    class NormalEquationSolver :public LeastSquareSolver < TYPE >
    {
    private:
        TYPE epsilon;
        const BaseMatrix<TYPE> &mat;
        CholeskySolver<TYPE> ch;
    public:
        NormalEquationSolver(const BaseMatrix<TYPE> &m, const TYPE &e) :LeastSquareSolver<TYPE>(), mat(m), epsilon(e), ch(t(m)*m, e) {}

        ~NormalEquationSolver(){}

        void SolveLS(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
        {
            assert(in.Nrows() == mat.Nrows());
            assert(in.Ncols() == out.Ncols());
            assert(out.Nrows() == mat.Ncols());
            ch.Solve(t(mat)*in, out);
        }
    };

}

#endif //NORMAL_EQUATION_SOLVER_H

#ifndef SIMPLE_SOLVER_H
#define SIMPLE_SOLVER_H

#include "LinearEquationSolver.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;

    template<typename TYPE>
    class SimpleSolver : public LinearEquationSolver < TYPE >
    {
    protected:
        const BaseMatrix<TYPE> &mat;
        TYPE epsilon;
    public:
        SimpleSolver(const BaseMatrix<TYPE> &bm, const TYPE &e) : LinearEquationSolver<TYPE>(), mat(bm), epsilon(e) {}

        virtual LogAndSign<TYPE> LogDeterminant() const = 0;

        virtual void TestSingular();
    };
}
#include "SimpleSolver.cpp"

#endif //SIMPLE_SOLVER_H

#ifndef SIMPLE_SOLVER_CPP
#define SIMPLE_SOLVER_CPP

#include "SimpleSolver.h"

namespace NewQuant
{
    template<typename TYPE>
    void SimpleSolver<TYPE>::TestSingular()
    {
        bool not_sig = true;
        for (int i = 1; i <= mat.Nrows(); ++i)
        {
            not_sig = not_sig && (fabs(mat(i, i)) > epsilon);
        }
        LinearEquationSolver<TYPE>::fail = !not_sig;
    }
}
#endif //SIMPLE_SOLVER_CPP

#ifndef CYCLIC_JACOBI_SOLVER_H
#define CYCLIC_JACOBI_SOLVER_H

#include "JacobiSolver.h"

namespace NewQuant
{

    template<typename TYPE>
    class CyclicJacobiSolver :public JacobiSolver < TYPE >
    {
    private:
        void CyclicJacobiIterate();
    public:
        CyclicJacobiSolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
            JacobiSolver<TYPE>(bm, e)
        {
            CyclicJacobiIterate();
        }

        ~CyclicJacobiSolver(){}
    };

    template<typename TYPE>
    void CyclicJacobiSolver<TYPE>::CyclicJacobiIterate()
    {
        const TYPE &e = JacobiSolver<TYPE>::epsilon;
        int n = JacobiSolver<TYPE>::combine.Nrows();
        TYPE norm;
        TYPE c, s;
        norm = JacobiSolver<TYPE>::JacobiNorm();
        while (norm > e)
        {
            for (int i = 1; i <= n - 1; ++i)
            {
                for (int j = i + 1; j <= n; ++j)
                {
                    JacobiSolver<TYPE>::JacobiMatrix(i, j, c, s);
                    JacobiSolver<TYPE>::JacobiTransform(i, j, c, s);
                    JacobiSolver<TYPE>::ColJacobiTransform(c, s, i, j);
                    norm = JacobiSolver<TYPE>::JacobiNorm();
                    if (norm <= e)
                    {
                        return;
                    }
                }
            }
        }
    }
}



#endif //CYCLIC_JACOBI_SOLVER_H

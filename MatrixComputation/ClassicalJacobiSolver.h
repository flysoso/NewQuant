#ifndef CLASSICAL_JACOBI_SOLVER_H
#define CLASSICAL_JACOBI_SOLVER_H

#include "JacobiSolver.h"

namespace NewQuant
{

    template<typename TYPE>
    class ClassicalJacobiSolver :public JacobiSolver < TYPE >
    {
    private:
        void ClassicalJacobiIterate();
    public:
        ClassicalJacobiSolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
            JacobiSolver<TYPE>(bm, e)
        {
            ClassicalJacobiIterate();
        }

        ~ClassicalJacobiSolver(){}
    };

    template<typename TYPE>
    void ClassicalJacobiSolver<TYPE>::ClassicalJacobiIterate()
    {
        SymmetricMatrix<TYPE> &sm = JacobiSolver<TYPE>::sym_mat;
        const TYPE &e = JacobiSolver<TYPE>::epsilon;
        int p, q;
        TYPE max, norm;
        TYPE c, s;
        norm = JacobiSolver<TYPE>::JacobiNorm();
        while (norm > e)
        {
            FindAbsMax(sm, max, p, q);
            if (p >= q)
            {
                std::swap(p, q);
            }
            JacobiSolver<TYPE>::JacobiMatrix(p, q, c, s);
            JacobiSolver<TYPE>::JacobiTransform(p, q, c, s);
            JacobiSolver<TYPE>::ColJacobiTransform(c, s, p, q);
            norm = JacobiSolver<TYPE>::JacobiNorm();
        }
    }
}



#endif //CLASSICAL_JACOBI_SOLVER_H

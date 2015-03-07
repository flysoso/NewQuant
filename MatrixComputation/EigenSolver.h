#ifndef EIGEN_SOLVER_H
#define EIGEN_SOLVER_H

namespace NewQuant
{
    template<typename TYPE> class DiagonalMatrix;
    template<typename TYPE> class SquareMatrix;

    template<typename TYPE>
    class EigenSolver
    {
    protected:
        EigenSolver(){}
    public:
        ~EigenSolver(){}

        virtual const DiagonalMatrix<TYPE> & EigenValue()const = 0;

        virtual const SquareMatrix<TYPE> & EigenVector()const = 0;
    };
}



#endif //EIGEN_SOLVER_H

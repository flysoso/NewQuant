#ifndef LINEAR_EQUATION_SOLVER_H
#define LINEAR_EQUATION_SOLVER_H


template <typename TYPE> class BaseMatrix;
template <typename TYPE> class LogAndSign;

///linear equation solving
template <typename TYPE>
class LinearEquationSolver
{
protected:
    bool fail;
    LinearEquationSolver() :fail(false) {}
public:

    ~LinearEquationSolver() {}

    bool IsFailed() const
    {
        return fail;
    }

    virtual void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const = 0;

    virtual LogAndSign<TYPE> LogDeterminant() const = 0;
};

#endif //LINEAR_EQUATION_SOLVER_H



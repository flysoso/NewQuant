#include "testEigenSolver.h"

void testEigenSolver()
{
    using namespace std;
    using namespace NewQuant;

    std::default_random_engine dre;
    std::normal_distribution<Type> nd;

    int r = 20, c = 20;
    Matrix<Type> m(r, c);
    SymmetricMatrix<Type> sym;
    for (int i = 1; i <= m.Nrows(); ++i)
    {
        for (int j = 1; j <= m.Ncols(); ++j)
        {
            m(i, j) = nd(dre);
        }
    }
    sym = t(m)*m;

    Type e = Precision<Type>::GetPrecision();
    ClassicalJacobiSolver<Type> cl_j(sym, e);
    cout << "test ClassicalJacobiSolver" << endl;
    cout << setw(10) << setprecision(5) << sym - cl_j.EigenVector()*cl_j.EigenValue()*t(cl_j.EigenVector()) << endl;

    CyclicJacobiSolver<Type> cy_j(sym, e);
    cout << "test CyclicJacobiSolver" << endl;
    cout << setw(10) << setprecision(5) << sym - cy_j.EigenVector()*cy_j.EigenValue()*t(cy_j.EigenVector()) << endl;

    cout << "TEST IS OVER" << endl;
}

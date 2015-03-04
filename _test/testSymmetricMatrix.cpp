#include "testSymmetricMatrix.h"

void testSymmetricMatrix()
{
    using namespace std;
    using namespace NewQuant;
    default_random_engine dre;
    normal_distribution<Type> nd;
    SymmetricMatrix<Type> sym1(10), sym2(10), sym3(10);
    IdentityMatrix<Type> imat(10);

    for (int i = 1; i <= sym1.Nrows(); ++i)
    {
        for (int j = 1; j <= sym1.Ncols(); ++j)
        {
            sym1(i, j) = nd(dre);
        }
    }
    cout << "sym1(10)" << endl;
    cout << setw(10) << sym1 << endl;

    cout << "test sym2(10) << sym1" << endl;
    sym2 << sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 = sym2+sym1" << endl;
    sym2 = sym2 + sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 << sym1+sym1" << endl;
    sym2 << sym1 + sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 = sym1" << endl;
    sym2 = sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 = sym1+sym1" << endl;
    sym2 = sym1 + sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 = 2.0*sym1" << endl;
    Type two(2);
    sym2 = two*sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 *= 2" << endl;
    sym2 *= two;
    cout << setw(10) << sym2 << endl;

    cout << "test sym2 = sym1*sym1" << endl;
    sym2 = sym1*sym1;
    cout << setw(10) << sym2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "sym1.MakeInv() = " << endl;
    cout << setw(10) << *sym1.MakeInv() << endl;
    cout << "sym1.MakeInv() * sym1" << endl;
    cout << setw(10) << (*sym1.MakeInv())*sym1 << endl;

    cout << "test sym1.MakeInv() * sym2 - sym1" << endl;
    cout << setw(10) << *sym1.MakeInv() * sym2 - sym1 << endl;

    cout << "Swap(sym1,sym2)" << endl;
    Swap(sym1, sym2);
    cout << "sym1" << endl;
    cout << setw(10) << sym1 << endl;
    cout << "sym2" << endl;
    cout << setw(10) << sym2 << endl;

    cout << "test Cholesky Decomposition" << endl;
    CholeskySolver<Type> ch(sym1, epsilon);
    cout << "L" << endl;
    cout << setw(10) << ch.Lower() << endl;
    cout << "sym1 - L * L'" << endl;
    cout << setw(10) << sym1 - ch.Lower()*t(ch.Lower()) << endl;
    cout << "determinant" << endl;
    cout << sym1.LogDeterminant().Value() << " = " << ch.LogDeterminant().Value() << endl;

    ch.Solve(imat, sym3);

    cout << setw(10) << sym3 * sym1 << endl;

    cout << "TEST IS OVER" << endl;
}



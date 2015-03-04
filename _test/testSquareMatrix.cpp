#include "testSquareMatrix.h"

void testSquareMatrix()
{
    using namespace std;
    using namespace NewQuant;
    default_random_engine dre;
    normal_distribution<Type> nd;
    SquareMatrix<Type> sqr1(10), sqr2(10);

    for (int i = 1; i <= sqr1.Nrows(); ++i)
    {
        for (int j = 1; j <= sqr1.Ncols(); ++j)
        {
            sqr1(i, j) = nd(dre);
        }
    }
    cout << "sqr1(10,10)" << endl;
    cout << setw(10) << sqr1 << endl;

    cout << "test sqr2(10,10) << sqr1" << endl;
    sqr2 << sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 = sqr2+sqr1" << endl;
    sqr2 = sqr2 + sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 << sqr1+sqr1" << endl;
    sqr2 << sqr1 + sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 = sqr1" << endl;
    sqr2 = sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 = sqr1+sqr1" << endl;
    sqr2 = sqr1 + sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 = 2.0*sqr1" << endl;
    Type two(2);
    sqr2 = two*sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 *= 2" << endl;
    sqr2 *= two;
    cout << setw(10) << sqr2 << endl;

    cout << "test sqr2 = sqr1*sqr1" << endl;
    sqr2 = sqr1*sqr1;
    cout << setw(10) << sqr2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "sqr1.MakeInv() = " << endl;
    cout << setw(10) << *sqr1.MakeInv() << endl;
    cout << "sqr1.MakeInv() * sqr1" << endl;
    cout << setw(10) << (*sqr1.MakeInv())*sqr1 << endl;

    cout << "test sqr1.MakeInv() * sqr2 - sqr1" << endl;
    cout << setw(10) << *sqr1.MakeInv() * sqr2 - sqr1 << endl;

    cout << "Swap(sqr1,sqr2)" << endl;
    Swap(sqr1, sqr2);
    cout << "sqr1" << endl;
    cout << setw(10) << sqr1 << endl;
    cout << "sqr2" << endl;
    cout << setw(10) << sqr2 << endl;

    cout << "TEST IS OVER" << endl;
}



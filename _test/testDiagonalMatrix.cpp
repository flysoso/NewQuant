#include "testDiagonalMatrix.h"

void testDiagonalMatrix()
{
    using namespace std;
    using namespace NewQuant;
    default_random_engine dre;
    normal_distribution<Type> nd;
    DiagonalMatrix<Type> d1(5),d2;

    for (int i = 1; i <= 5; ++i)
    {
        d1(i) = nd(dre);
    }
    d2 = d1;
    cout << "d1=" << endl;
    cout << setw(10) << d1 << endl;

    cout << "d1+=d2" << endl;
    d1 += d2;
    cout << setw(10) << d1 << endl;

    cout << "d1.MakeInv()=" << endl;
    cout << setw(10) << *d1.MakeInv() << endl;

    cout << "d1.MakeInv() * d1" << endl;
    cout << setw(10) << *d1.MakeInv() * d1 << endl;

    cout << "TEST IS OVER" << endl;
}

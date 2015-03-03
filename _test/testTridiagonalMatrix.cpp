#include "testTridiagonalMatrix.h"

void testTridiagonalMatrix()
{
    using namespace std;
    default_random_engine dre;
    normal_distribution<Type> nd;
    TridiagonalMatrix<Type> trid1(10), trid2(10);
    BandMatrix<Type> band;
    for (int i = 1; i <= trid1.Nrows(); ++i)
    {
        for (int j = 1; j <= trid1.Ncols(); ++j)
        {
            trid1(i, j) = nd(dre);
        }
    }
    cout << "trid1(10)" << endl;
    cout << setw(10) << trid1 << endl;

    cout << "test trid2(10) << trid1" << endl;
    trid2 << trid1;
    cout << setw(10) << trid2 << endl;

    cout << "test trid2(10) = trid2+trid1" << endl;
    trid2 = trid2 + trid1;
    cout << setw(10) << trid2 << endl;

    cout << "test trid2(10) << trid1+trid1" << endl;
    trid2 << trid1 + trid1;
    cout << setw(10) << trid2 << endl;

    cout << "test trid2 = trid1" << endl;
    trid2 = trid1;
    cout << setw(10) << trid2 << endl;

    cout << "test trid2 = trid1+trid1" << endl;
    trid2 = trid1 + trid1;
    cout << setw(10) << trid2 << endl;

    cout << "test trid2 = 2.0*trid1" << endl;
    Type two(2);
    trid2 = two*trid1;
    cout << setw(10) << trid2 << endl;

    cout << "test trid2 *= 2" << endl;
    trid2 *= two;
    cout << setw(10) << trid2 << endl;

    cout << "test band = trid1*trid1" << endl;
    band = trid1*trid1;
    cout << setw(10) << band << endl;

    cout << "test MakeInv()" << endl;
    cout << "trid1.MakeInv() = " << endl;
    cout << setw(10) << *trid1.MakeInv() << endl;
    cout << "trid1.MakeInv() * trid1" << endl;
    cout << setw(10) << (*trid1.MakeInv())*trid1 << endl;

    cout << "test trid1.MakeInv() * band - trid1" << endl;
    cout << setw(10) << *trid1.MakeInv() * band - trid1 << endl;

    cout << "Swap(trid1,trid2)" << endl;
    Swap(trid1, trid2);
    cout << "trid1" << endl;
    cout << setw(10) << trid1 << endl;
    cout << "trid2" << endl;
    cout << setw(10) << trid2 << endl;

    cout << "TEST IS OVER" << endl;
}



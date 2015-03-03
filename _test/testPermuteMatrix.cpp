#include "testPermuteMatrix.h"

void testPermuteMatrix()
{
    using namespace std;
    PermuteMatrix<Type> perm1(10), perm2(10);

    cout << "perm1(10)" << endl;
    perm1.SwapRow(1, 4);
    perm1.SwapRow(2, 3);
    perm1.SwapRow(4, 5);
    cout << setw(10) << perm1 << endl;

    cout << "test perm2(10) << perm1" << endl;
    cout << setw(10) << perm2 << endl;

    cout << "test perm2(10) = perm1" << endl;
    perm2 = perm1;
    cout << setw(10) << perm2 << endl;

    
    cout << "test MakeInv()" << endl;
    cout << "perm1.MakeInv() = " << endl;
    cout << setw(10) << *perm1.MakeInv() << endl;
    cout << "perm1.MakeInv() * perm1" << endl;
    cout << setw(10) << (*perm1.MakeInv())*perm1 << endl;

    cout << "test perm1.MakeInv() * perm2 - perm1" << endl;
    cout << setw(10) << *perm1.MakeInv() * perm2 - perm1 << endl;

    cout << "Swap(perm1,perm2)" << endl;
    Swap(perm1, perm2);
    cout << "perm1" << endl;
    cout << setw(10) << perm1 << endl;
    cout << "perm2" << endl;
    cout << setw(10) << perm2 << endl;

    cout << "TEST IS OVER" << endl;
}



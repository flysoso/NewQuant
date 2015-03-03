#include "testIdentityMatrix.h"

void testIdentityMatrix()
{
    using namespace std;
    Type one(1), one_half(1.5), two(2);
    IdentityMatrix<Type> c1(5, one), c2(5, two), c3(5, one_half),c4;

    cout << "c1" << endl;
    cout << setw(10) << c1 << endl;

    cout << "c2" << endl;
    cout << setw(10) << c2 << endl;

    cout << "c3" << endl;
    cout << setw(10) << c3 << endl;

    cout << "c4=c1*c3" << endl;
    c4 = c1*c3;
    cout << setw(10) << c4 << endl;

    cout << "c4=c1+c3" << endl;
    c4 = c1+c3;
    cout << setw(10) << c4 << endl;

    cout << "c4=t(c1)" << endl;
    c4 = t(c1);
    cout << setw(10) << c4 << endl;

    c4.Resize(5);
    c3.Solve(c1, c4);
    cout << "c3.MakeInv()" << endl;
    cout << setw(10) << *c3.MakeInv() << endl;

    cout << "TEST IS OVER" << endl;
}

#include "testLeastSquareSolver.h"

void testLeastSquareSolver()
{
    using namespace std;
    using namespace NewQuant;
    std::default_random_engine dre;
    std::normal_distribution<Type> nd;

    int r = 30, c = 10;
    Matrix<Type> A(r, c), B(r, r), Binv1(r, r), Binv2(r, r), Binv3(r, r), Binv4(r, r);
    ColumnVector<Type> b(r), x(c), y(c), z(c), w(c);
    IdentityMatrix<Type> I(r, 1.0);

    for (int i = 1; i <= A.Nrows(); ++i)
    {
        for (int j = 1; j <= A.Ncols(); ++j)
        {
            A(i, j) = nd(dre);
        }
    }


    for (int i = 1; i <= B.Nrows(); ++i)
    {
        for (int j = 1; j <= B.Ncols(); ++j)
        {
            B(i, j) = nd(dre);
        }
    }

    for (int i = 1; i <= b.Length(); ++i)
    {
        b(i) = nd(dre);
    }


    NormalEquationSolver<Type> nes(A, epsilon);
    nes.SolveLS(b, y);

    HouseholderQR<Type> h_qr(A, epsilon);
    h_qr.SolveLS(b, x);

    HouseholderQRpivot<Type> h_qr_p(A, epsilon);
    h_qr_p.SolveLS(b, z);

    GivensQR<Type> g_qr(A, epsilon);
    g_qr.SolveLS(b, w);

    cout << "A = " << endl;
    cout << setw(10) << A << endl;
    cout << "b = " << endl;
    cout << setw(10) << b << endl;
    cout << "x = " << endl;
    cout << setw(10) << x << endl;

    cout << "the difference of x,y,z, and w" << endl;
    cout << setw(10) << (y - x) << endl;
    cout << setw(10) << (z - x) << endl;
    cout << setw(10) << (w - x) << endl;

    NormalEquationSolver<Type> s1(B, epsilon);
    HouseholderQR<Type> s2(B, epsilon);
    HouseholderQRpivot<Type> s3(B, epsilon);
    GivensQR<Type> s4(B, epsilon);
    s1.SolveLS(I, Binv1);
    s2.SolveLS(I, Binv2);
    s2.SolveLS(I, Binv3);
    s4.SolveLS(I, Binv4);

    cout << setw(10) << B << endl;
    cout << "test using SolveLS() to get the inv of B" << endl;
    cout << setw(3) << setprecision(0) << B*Binv1 << endl;
    cout << setw(3) << setprecision(0) << B*Binv2 << endl;
    cout << setw(3) << setprecision(0) << B*Binv3 << endl;
    cout << setw(3) << setprecision(0) << B*Binv4 << endl;

    cout << "TEST IS OVER" << endl;
}
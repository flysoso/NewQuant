#include "testSpeFuncAndStatComp.h"

void testSpecFuncAndStatComp()
{
    using namespace std;
    using namespace NewQuant;

    Gamma<Type> gamma;
    Beta<Type> beta;
    IncompleteGamma<Type> igamma;
    IncompleteBeta<Type> ibeta;
    ErrorFunction<Type> error_f;
    InvErrorFunction<Type> ie;
    ComplementErrorFunction<Type> com_error;
    InvComplementErrorFunction<Type> inv_com_error;

    NormalPdf<Type> norm_pdf;
    NormalCdf<Type> norm_cdf;
    NormalQuantile<Type> norm_q;

    GammaPdf<Type> gamma_pdf;
    GammaCdf<Type> gamma_cdf;
    GammaQuantile<Type> gamma_q;

    BetaPdf<Type> beta_pdf;
    BetaCdf<Type> beta_cdf;
    BetaQuantile<Type> beta_q;

    StudentPdf<Type> t_pdf;
    StudentCdf<Type> t_cdf;
    StudentQuantile<Type> t_q;

    ChiSquarePdf<Type> chi_pdf;
    ChiSquareCdf<Type> chi_cdf;
    ChiSquareQuantile<Type> chi_q;

    F_Cdf<Type> f_cdf;
    F_Pdf<Type> f_pdf;
    F_Quantile<Type> f_q;

    WeibullCdf<Type> w_cdf;
    WeibullPdf<Type> w_pdf;
    WeibullQuantile<Type> w_q;

    //cout << Pi<Type>::value() << endl;
    //cout << setw(25) << scientific << setprecision(20) << g(4.53) << endl;
    //cout << setw(25) << scientific << setprecision(20) << g(13) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta(2.3, 5.6) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta(5.0, 5.0) << endl;
    //cout << setw(25) << scientific << setprecision(20) << ib(5.0, 5.0, 0.2) << endl;
    //cout << setw(25) << scientific << setprecision(20) << error_f(ie(-0.192)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << std::erf(ie(-0.192)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_pdf(-0.23, 1.5, 0.64) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_cdf(-0.23, 1.5, 0.64) << endl;
    //cout << setw(25) << scientific << setprecision(20) << ie(0.952) << endl;
    //cout << setw(25) << scientific << setprecision(20) << error_f(ie(0.62)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta_pdf(20.56, 30.23, 0.5) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta_cdf(20.56, 30.23, 0.5) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta_q(20.56, 30.23, 0.5) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_q(20.56, 30.23, 0.235) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_cdf(0.0, 1.0, norm_q(0.0, 1.0, 1e-2)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << t_cdf(55.0, 2.0, 1.0, t_q(55.0, 2.0, 1.0, 0.05992)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << chi_cdf(55.0, 20.0) << endl;
    //cout << setw(25) << scientific << setprecision(20) << chi_pdf(55.0, 20.0) << endl;
    //cout << setw(25) << scientific << setprecision(20) << chi_cdf(55.0, chi_q(55.0, 0.23)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << f_pdf(56.0, 55.0, 1.051) << endl;
    //cout << setw(25) << scientific << setprecision(20) << f_cdf(56.0, 55.0, 1.051) << endl;
    //cout << setw(25) << scientific << setprecision(20) << f_cdf(56.0, 55.0, f_q(56.0, 55.0, .90051)) << endl;
    cout << setw(25) << scientific << setprecision(20) << w_pdf(56.0, 55.0, 55.0) << endl;
    cout << setw(25) << scientific << setprecision(20) << w_cdf(56.0, 55.0, 55.0) << endl;

}


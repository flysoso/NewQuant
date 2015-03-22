#include "testSDEandSP.h"


void testSDEandSP()
{
    using namespace std;
    using namespace NewQuant;

    std::mt19937 dre, c_dre;
    dre.seed(123);
    c_dre.seed(123);
    std::normal_distribution<Type> di;
    RandomSource<Type, mt19937, normal_distribution<Type> > random(dre, di);
    RandomSource<Type, mt19937, normal_distribution<Type> > c_random(c_dre, di);
    /*
    Type r = 0.05, sigma = 0.4;
    shared_ptr<GBM<Type> > drift          (new GBMdrift<Type>(r, sigma));
    shared_ptr<GBM<Type> > diffusion      (new GBMdiffusion<Type>(r, sigma));
    shared_ptr<GBM<Type> > drift_x        (new GBMdrift_x<Type>(r, sigma));
    shared_ptr<GBM<Type> > diffusion_x    (new GBMdiffusion_x<Type>(r, sigma));
    shared_ptr<GBM<Type> > drift_xx       (new GBMdrift_x<Type>(r, sigma));
    shared_ptr<GBM<Type> > diffusion_xx   (new GBMdiffusion_x<Type>(r, sigma));

    ItoDiffusion1D<Type, GBM<Type> > gbm(drift, diffusion);
    gbm.SetDriftX(drift_x);
    gbm.SetDiffusionX(diffusion_x);
    gbm.SetDriftXX(drift_xx);
    gbm.SetDiffusionXX(diffusion_xx);

    gbm.SetRange(0.0, 1.0, 1000);
    gbm.SetInitialValue(1.1);
    */
    
    Type theta1 = 0.04*0.04, theta2 = 0.04, theta3 = 0.17;
    shared_ptr<OUtype1<Type> > drift          (new OUtype1drift<Type>(theta1, theta2, theta3));
    shared_ptr<OUtype1<Type> > diffusion      (new OUtype1diffusion<Type>(theta1, theta2, theta3));
    shared_ptr<OUtype1<Type> > drift_x        (new OUtype1drift_x<Type>(theta1, theta2, theta3));
    shared_ptr<OUtype1<Type> > diffusion_x    (new OUtype1diffusion_x<Type>(theta1, theta2, theta3));
    shared_ptr<OUtype1<Type> > drift_xx       (new OUtype1drift_x<Type>(theta1, theta2, theta3));
    shared_ptr<OUtype1<Type> > diffusion_xx   (new OUtype1diffusion_x<Type>(theta1, theta2, theta3));

    ItoDiffusion1D<Type, OUtype1<Type> > ou(drift, diffusion);
    ou.SetDriftX(drift_x);
    ou.SetDiffusionX(diffusion_x);
    ou.SetDriftXX(drift_xx);
    ou.SetDiffusionXX(diffusion_xx);

    ou.SetRange(0.0, 1.0, 1000);
    ou.SetInitialValue(0.04);
    
    EulerMethod1D<Type>                       euler;
    MilsteinMethod1D<Type>                    milstein;
    PredictorCorrectorMethod1D<Type>          pc_method(0.5, 0.5);
    StrongOrder1_0RungeKuttaMethod1D<Type>    rk_method;
    StrongOrder1_5TaylorMethod1D<Type>        taylor;
    WeakOrder2_0TaylorMethod1D<Type>          w_taylor;
    WeakOrder2_0RungeKuttaMethod1D<Type>      w_rk_method;
    SecondMilsteinMethod1D<Type>              s_milstein;
    OzakiMethod1D<Type>                       ozaki;
    ShojiOzakiMethod1D<Type>                  shoji_ozaki;

    Range<Type> range(0.0, 1.0, 1000);

    BrownianMotion<Type> bm(range);

    ColumnVector<Type> v(1001);
    ofstream fout1, fout2;
    fout1.open("E:/SDE/test1.txt");
    fout2.open("E:/SDE/test2.txt");
    
    euler.Simulate(ou, random, v);
    //bm.GetPath(v, random);
    for (int i = 1; i <= v.Length(); ++i)
        fout1 << v(i) << endl;

    taylor.Simulate(ou, c_random, random, v);
    //bm.GetPath(v, random);
    for (int i = 1; i <= v.Length(); ++i)
        fout2 << v(i) << endl;

    cout << "TEST IS OVER" << endl;

}



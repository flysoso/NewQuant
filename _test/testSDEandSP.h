#ifndef testSDEandSP_h
#define testSDEandSP_h

#include "testBase.h"
#include "../MonteCarlo/SDE/SDE1D/ItoDiffusion1D.h"
#include "../MonteCarlo/RandomSource.h"
#include "../MonteCarlo/SDE/SDE1D/GBM.h"
#include "../MonteCarlo/SDE/SDE1D/CIRtype1.h"
#include "../MonteCarlo/SDE/SDE1D/OUtype1.h"

#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/EulerMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/MilsteinMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/SecondMilsteinMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/StrongOrder1_0RungeKuttaMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/StrongOrder1_5TaylorMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/WeakOrder2_0RungeKuttaMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/FiniteDifferenceMethod/WeakOrder2_0TaylorMethod1D.h"

#include "../MonteCarlo/SDEsolver/SDEsolver1D/LocalLinearizationMethod/OzakiMethod1D.h"
#include "../MonteCarlo/SDEsolver/SDEsolver1D/LocalLinearizationMethod/ShojiOzakiMethod1D.h"

#include "../MonteCarlo/SDEsolver/SDEsolver1D/PredictorCorrectorMethod/PredictorCorrectorMethod1D.h"

#include "../MonteCarlo/StochasticProcess/Continuous/BMExactSolution.h"
#include "../MonteCarlo/StochasticProcess/Continuous/BrownianMotion.h"
#include "../MonteCarlo/StochasticProcess/Discrete/RandomWalk.h"

#include "../MatrixComputation/ColumnVector.h"

void testSDEandSP();

#endif //testSDEandSP_h


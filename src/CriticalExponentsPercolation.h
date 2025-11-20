//
//  CriticalExponentsPercolation.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 13/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__CriticalExponentsPercolation__
#define __SpatialAnalysis__CriticalExponentsPercolation__

#include <stdio.h>
#include <vector>
class CriticalExponentsPercolation{
public:
    double beta;
    double gamma;
    double gamma_measured;
    double alpha;
    double nu;
    double sigma;
    double tau;
    double anglePhaseTransition;
    double probabilityPhaseTransition;
    double d;
    double D;
    double D_measured;
    double beta_div_nu;
    double gamma_div_nu;
    double mass;
    double mass_phaseTransition;
    double length_lattice;
    std::vector<double> angles;
    std::vector<double> probabilities;
    std::vector<double> massesGC;
    std::vector<double> averageClusterSize;
   // std::vector<double> thresholds;
   std::vector<double> entropies;
   
};

#endif /* defined(__SpatialAnalysis__CriticalExponentsPercolation__) */

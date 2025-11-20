//
//  RoadNetworkGeneration.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 14/03/2017.
//  Copyright (c) 2017 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__RoadNetworkGeneration__
#define __SpatialAnalysis__RoadNetworkGeneration__

#include <stdio.h>
#include <vector>
#include "SpatialInteraction.h"
#include "FractalDimension.h"
#include "Entropy.h"
#include "Distribution.h"
//NOTE in class network there is another generation of roads (my algorithm) currently unused
class RoadNetworkGeneration{
public:
  static void straightenGraph(Grafo* graph,double increment,long numberTimes,std::vector<double>& edgeFlows);
  static double calculateStraightnessEfficiency(Grafo* G);
  static std::vector<double> calculateStraightnessEfficiencyAndTripEfficiency(Grafo* G,double d0);
    static std::tuple<double,double,double,double,double,double> getComponentsOfPerformance(Grafo* G);
    static double performance(Grafo* G,double beta1,double beta2);
       static void createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> &multiplierTopography,std::vector<long> &idsEdgesBelongingToCities,double proportionBetweenSpeedInCityAndOutside,std::vector<double> &multiplierRivers,double alpha,double d0);
       static void createRoadNetworkFromCities(std::tuple<std::vector<double>, std::vector<double>,std::vector<double> > x_y_mass_ofCities,Grafo* result,double alpha,double d0,long numberDummyNodes);
       static void getDelanuayGraphFromCities(std::tuple<std::vector<double>, std::vector<double>,std::vector<double> > x_y_mass_ofCities,Grafo* result,long numberDummyNodes);
//       static void createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,double exponentDecayDistance,std::vector<double> &speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion);
    // static std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>,std::vector<double>   >  experiments_optimizeAlpha(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time);
    // static std::tuple<std::vector<double>,std::vector<double>  >  experiments_measureFractalDimension(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time);
    //     static  std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>  >  experiments_measureEntropy(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time);
    //     static std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>   > experiments_calculateFlows(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time);
    //     static std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double>     >   experiments_final(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time);
//     static std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>    >   experiments_final_B(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time);
// static     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>   >   experiments_final_C(Grafo* cities);
        static std::vector<double> getGaussianSpeedLimits(Grafo* delanuayGraph,double d0,double exponent);
static void keepOnlySimplestPathsBetweenNodes(Grafo* G,Grafo* result);
private:
};
#endif /* defined(__SpatialAnalysis__RoadNetworkGeneration__) */

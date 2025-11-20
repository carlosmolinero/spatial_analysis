//
//  Link.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__SpatialInteraction__
#define __SpatialAnalysis__SpatialInteraction__

#include <stdio.h>
#include "Grafo.h"
#include "Functions.h"
#include <utility>
#include "DualExtendedGraph.h"
#include "Distribution.h"
#include "ShapeFile.h"
#include "InterfaceFlows.h"

class SpatialInteraction{
public:
  static double calculate_pd(double distance,double D,double maxDistance,std::vector<double>& N);
  static Distribution calculate_pd_forCity_i(Grafo* G,long idNodeInit,double maxDistanceSystem, double pop_max_mun);
  static double kernelDistanceDecay(double distance, double L, Distribution& cdf_pd);
   static double kernelDistanceDecay(double distance);
    static double kernelDistanceDecay(double distance,double d0);
   static double modificationSpeedWithCongestion(double flow, double capacity,double alpha, double beta);
   static void calculateTotalTripsFromEachNode(Grafo* G,double distanceLimit,std::vector<double> &trips);
   static void calculateTotalDistanceTravelledFromEachNode(Grafo* G,double distanceLimit,std::vector<double> &distances);
    static std::pair<double,double>  calculateRobustness(Grafo* G);
    static std::pair<double,double> calculateRobustness(Grafo* G,long repetitions);
    static void calculateFlow(Grafo* G,double distanceLimit,std::vector<double> &flows);
   static void calculateFlow_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &flows);
   static void calculateEdgeFlow(Grafo* G,double distanceLimit,InterfaceFlows& flows);
   static void calculateNormalisedEdgeFlow(Grafo* G,double distanceLimit,InterfaceFlows& flows,double& outgoingTrips);
   static void calculateEdgeFlow_singleNode(Grafo* G,InterfaceDijkstra &minDistances,InterfaceFlows& flows,double normalisingValueTrips);
   static void calculateEdgeFlow_singleNode(Grafo* G,InterfaceDijkstra &minDistances,InterfaceFlows& flows,double normalisingValueTrips, Distribution& cdf_pd);
   static void calculateFlowPerMeterAndIntersectionsPerMeter(Grafo* G,double distanceLimit,std::vector<double> &edgeFlows,std::vector<double>& flowPerMeter,std::vector<double>& intersectionsPerMeter);
   static void calculateFlowPerMeterAndIntersectionsPerMeter_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &edgeFlows,double normalisingValueTrips,std::vector<double>& flowPerMeter,std::vector<double>& intersectionsPerMeter);

    static void calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar(Grafo* G,double& flowTraversedPerCar,double& distancesPerCar,double& intersectionsTraversedPerCar,double& outgoingTrips);
    static void calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &edgeFlows,double& flowTraversedPerCar,double& intersectionsTraversedPerCar,double& distancesPerCar,double& outgoingTrips);
    static void calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &edgeFlows,double normalisingValueTrips,double& flowTraversedPerCar,double& intersectionsTraversedPerCar,double& distancesPerCar);

   static std::vector<double> calculateTimesSegments(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta,double acceleration,double t,std::vector<double>& edgeFlows,double& numberTripsGenerated);
   static std::vector<double> calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta,double t);
   static std::vector<double> calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta,double t,std::vector<double>& edgeFlows,double& numberTripsGenerated);

   static double calculateWaitingTimesAtIntersections(double flow);
   static void setMultiplierN(double multiplierN);
private:
  static double multiplierN;
    static void calculateTotalTrips_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &trips);
    static void calculateTotalDistanceTravelled_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &distances);
    static void calculateFlow_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &flows);
   static void calculateFlowPerMeterAndIntersectionsPerMeter_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &edgeFlows,std::vector<double>& flowPerMeter,std::vector<double>& intersectionsPerMeter);
    static void calculateNormalisedEdgeFlow_aux(Grafo* G,long startNode,long endNode,double distanceLimit,InterfaceFlows& flows,double& outgoingTrips);
    static void calculateEdgeFlow_aux(Grafo* G,long startNode,long endNode,double distanceLimit,double maxPopMun,InterfaceFlows& flows);

static double normalisingFactorTripsFromCity(Grafo* G,InterfaceDijkstra& ID);
static double normalisingFactorTripsFromCity(Grafo* G,long idNodeInit,Distribution& cdf_pd);
static double getProbabilityFlowBasedInTime(double t_seconds);
static void calculateFlowsInVehiclesPerSecond(Grafo* G,double t,std::vector<double>& flows,double& numberTripsGenerated);

};

#endif /* defined(__SpatialAnalysis__SpatialInteraction__) */

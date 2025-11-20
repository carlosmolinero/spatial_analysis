//
//  Programs.h
//  harmonicCities
//
//  Created by Carlos Molinero on 06/07/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#ifndef __harmonicCities__Programs__
#define __harmonicCities__Programs__

#include <stdio.h>
#include "Graph.h"
#include "InterfaceCityGeneration.h"
#include <math.h>
#include <stdlib.h>
#include "City.h"
#include "PotentialField.h"
#include "VectorNDim.h"
//#include "Eigen/Dense"
//#include "Eigen/Eigenvalues"
#include "Plot.h"
#include "FractalDimension.h"
#include "Walker.h"
#include "TextFile.h"
#include "Functor.h"
#include <unordered_map>
#include "DrawingObjects.h"
#include "Singleton.h"
#include "Windows.h"
#include "Network.h"
#include "RTree.h"

class Programs{
public:
    
    static void createLineGraph(Graph* graph,Graph* lineGraph);
    static void saveResultsCentralities(Graph* graph,int indexDistance,std::string nameFile);
    static void performAngularNetworkPercolation();
    static void performMetricNetworkPercolation(Graph* loadedGraph,std::vector<double> setOfDistances);
//    static void performBondAngularNetworkPercolation();
//    static void performAngularNetworkPercolationLegion(std::string nameNCOL,std::string nameCoordinates,std::string separatorNCOL,std::string separatorCoordinates,double startAngle,double endAngle,double separationAngles);
    static void createRoadNetwork();
    static void createRoadNetwork(Graph& graph,double minSizeCity,double definition);
    static void percolateAndCreateRoadNetwork(Graph* G,Graph* result,double distancePercolation,double minSizeCity,double definition);
    static void loadGraph(Graph* graph,std::string nameFileWithCoordinates,std::string separator);
//    static void saveGraph(Graph* graph,std::string nameNCOL,std::string nameCoordinates,std::string separatorNCOL,std::string separatorCoordinates);
    static void calculateCentralitiesGraph(Graph* graph,int indexDistance);
    static void generateCities(InterfaceCityGeneration* interface);
    static void migrate(InterfaceCityGeneration* interface,double proportionMigrations);
    static void loopGenerateCities(InterfaceCityGeneration* interface,long generation,bool draw);
    static void addMetropolisis(InterfaceCityGeneration* interface,long clusterId);
    static long cascade(InterfaceCityGeneration* interface,long idClusterInit,long numberPeopleToMove);
    static void addValuesToPotentialField(InterfaceCityGeneration* interface,long idCluster,long numberPeopleAdded);
    static void calculateNumberIntersectionsCloseToIntersections();
    static void expandValuesThroughNetwork();
    static void calculateHierarchicalIndexPercolation(Graph* graph);
    static void calculateRenormalisedGraph();
    static void performProbabilisticNetworkPercolation(Graph* loadedGraph);
    static void generateGridGraph(Graph* gridGraph,long sizeX,long sizeY,double euclideanWidth);
    static void generateTreeFromPercolation(Graph* graph,std::vector<double> setOfDistances,long numberOfClusters);
    static void findCityBorder(Graph* graph);
    static void analyseHierarchyUsingDerivativePercolation(Graph* graph);
    static void calculateMelbourne(Graph* graph,long startNode,long endNode,double metricRadius,long typeFirstDistance,long typeSecondDistance, long typeDistanceCombined,long indexDistanceCutoff, long indexDistanceCalculation,bool customize);
    static double detectPhaseTransitionAngularPercolation(Graph *graph,Graph* lineGraph,double definition);
    static void extractSkeletonAndGenerateSubClusters(Graph* graph,Graph* lineGraph,Graph* skeleton, double anglePhaseTransition,std::vector<Graph> &separatedSubgraphs, double definitionPhaseTransition);
    static void extractSkeleton(Graph* graph,Graph* lineGraph,Graph* skeleton, double anglePhaseTransition,double definitionPhaseTransition);
    static void assignFirstAngleInPhaseTransition(Graph* graph,Graph* lineGraph,double initialAngle);
    static double detectPhaseTransitionOfASubclusterAndExtractSkeleton(Graph* graph,Graph* lineGraph,Graph* skeleton,std::vector<Node*> nodesOfCluster);
    static void simplifyNetwork(Graph* graph);
};
#endif /* defined(__harmonicCities__Programs__) */

//
//  Network.h
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Network__
#define __harmonicCities__Network__

#include <stdio.h>
#include "Graph.h"
#include "PotentialField.h"
#include "Functor.h"
#include "Functions.h"
#include "City.h"
#include "QTree.h"
#include <list>
#include "Singleton.h"
#include "Windows.h"


class Network{
public:
    void generateRoadNetworkBetweenNodes(Graph* mainGraph,double minSizeCity,double definition);
    static void changeWeightsGraphToBetweenness(Graph* lineGraph,int indexDistance,bool includeDistance);
    void addTransitionsGraph(Graph* graph,Graph* potentialFieldGraph,PotentialField* potentialField,double minPopulationToAdd,int hierarchicalLevel);
    static void correctPositions(Graph* graph);
    void saveOriginalPositions(Graph* graph);
    void resetPositions(Graph* graph);
    static void straightenGraphs(Graph* graph);
    static void saveStatistics(Graph& mainGraph,Graph& minRealGraph,double minSizeCity);
    static void calculateCentralitiesOfCities(Graph* graph,int indexDistance,double minSizeCity,bool useMassesForValuesToPass);
        static void calculateEdgeBetweennessOfCitiesAndUseItAsWidthTransition(Graph* lineGraph,int indexDistance,double minSizeCity,bool useMassesForValuesToPass);
    static void calculateEdgeBetweennessOfCities(Graph* lineGraph,int indexDistance,double minSizeCity,bool useMassesForValuesToPass);
    static void extractGraphOfCities(Graph* graph,Graph* originalGraph,double minPopulationToAdd,int hierarchicalLevel);
    std::vector<Point2d> originalPositions;
    static void imitateShortestPath(Graph* generated,Graph* original,Graph* realShortestPath,Node* nodeInit,Node* nodeEnd,Graph* pathInGenerated,Graph* pathInOriginal);
    static double comparePaths(Graph& path1,Graph& path2,Node* originA,Node* originB,Node* endA,Node* endB);
    static std::vector<double> getYBasedOnDistanceFromStartThroughPath(Graph& path,Node* origin,Node* destination);
    static std::vector<double> getXBasedOnDistanceFromStartThroughPath(Graph& path,Node* origin,Node* destination);
    static std::vector<double> getYBasedOnAbsoluteDistanceFromStart(Graph& path,Node* origin,Node* destination);
    static std::vector<double> getXBasedOnAbsoluteDistanceFromStart(Graph& path,Node* origin,Node* destination);
    static std::vector<double> getLocalAnglesBasedOnAbsoluteDistanceFromStart(Graph& path,Node* origin,Node* destination);
    static void detectSinks(Graph* sinks, PotentialField* potentialField,double multiplier,double minSizeCity);
    static void insertEstimatedBoundaryConditions(Graph* boundaryConditions, PotentialField* potentialField,double multiplier,double minSizeCity);
    static void generatePotentialFieldFromGraph(Graph* graph,PotentialField* potentialField,long numberElements);
};

#endif /* defined(__harmonicCities__Network__) */

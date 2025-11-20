//
//  GeometryGraph.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 10/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__GeometryGraph__
#define __SpatialAnalysis__GeometryGraph__

#include <stdio.h>
#include "Geometry.h"
#include "Grafo.h"
#include "DualExtendedGraph.h"
#include "Point2d.h"

class GeometryGraph{

public:
    static void createBoundaryGraph(Grafo* G,Grafo* boundaryGraph,double alpha);
    static void createBoundaryGraphUsingDelanuay(Grafo* G,Grafo* boundaryGraph,double multiplierOfMeanWeightToDetermineWhichLinksStay);

    static std::set<long> nodesInPolygon(Grafo* G,Grafo* polygon);
    static void getSubgraphWithinABoundary(Grafo* G,Grafo* boundary,Grafo* result);
    // static std::tuple<std::vector<long>,std::vector<long> > getNodesFromOtherGraphClosestToNodes(Grafo* G,Grafo OG);
    // static void geometricApproximationOfAGraph_simplifyLanes(Grafo* G,double distanceLimit)
    static double calculateAproxDiameterGraph(Grafo *G);
    static double calculateAreaPolygon(Grafo* polygon);
    static double calculateAreaSetOfPoints(std::set<Point2d>& points);
    static void calculateAreaSetOfPoints_preparationForParallel(std::vector<std::set<Point2d> >& pointsPerIdCluster,long startIndex,long endIndex,std::vector<double>& areas);
    static std::vector<double> calculateHuMoments(Grafo* region);
};

#endif /* defined(__SpatialAnalysis__GeometryGraph__) */

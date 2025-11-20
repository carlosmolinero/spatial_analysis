//
//  FractalDimension.h
//  harmonicCities
//
//  Created by Carlos Molinero on 12/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__FractalDimension__
#define __harmonicCities__FractalDimension__

#include <stdio.h>
#include "Point2d.h"
#include "Grafo.h"
#include "LinearRegression.h"
#include "InterfaceMultiFractalAnalysis.h"
#include "DualExtendedGraph.h"
#include "Fxy.h"
//#include "Node.h"
//#include "Graph.h"
//#include "QTree.h"
//#include "City.h"
//#include "Network.h"


class FractalDimension{
public:
    
    FractalDimension();
//    static Point2d calculateCentroid(std::vector<Node> &nodes);
//    static double calculateFractalDimensionGyrationRadius(Graph &graph);
    static double calculateDimensionSpatiallyEmbeddedGraph(Grafo* graph,int type);
    
    static InterfaceMultiFractalAnalysis calculateDimensionSpatiallyEmbeddedGraph(Grafo* G,std::vector<double> &qs);
    
    
//    static double calculateBoxCounting(Graph* graph);
//    static double calculateBoxCounting(std::vector<Point2d> &points);
//    static double calculateBoxCounting(std::vector<double> &xs,std::vector<double> &ys,double max,double min,double widthPoint);
//    static std::vector<std::vector<double> >   calculateBoxCounting_getPoints(std::vector<double> &xs,std::vector<double> &ys,double max,double min,double widthPoint);
    static double calculateBoxCounting(Grafo* G);
    static std::vector<std::vector<double> >  calculateBoxCounting_getPoints(std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint);
    static double calculateBoxCounting(std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint);
    static std::vector<std::vector<double> >  generateSetOfPointsInvertedBoxCounting(double gamma,double maxX,double minX,double maxY,double minY,double max,double min ,bool regular,bool random);
    static double calculateCapacityDimension(Grafo* G);
    static InterfaceMultiFractalAnalysis MultifractalAnalysis_sandBox(Grafo* G,std::vector<double> &qs);
    static InterfaceMultiFractalAnalysis MultifractalAnalysis_boxCounting(Grafo* G,std::vector<double> &qs,std::vector<double> & radii);
    static InterfaceMultiFractalAnalysis MultifractalAnalysis_slidingBox(Grafo* G,std::vector<double> &qs);
    static std::tuple<std::vector<double>,std::vector<double> >  boxCountingPlaneSweep(Grafo* G,long depthLimit);
    static std::tuple<std::vector<double>,std::vector<double> >  boxCountingPlaneSweep_mixScales(Grafo* G,long depthLimit);
    static std::tuple<std::vector<double>,std::vector<double> >  boxCountingPlaneSweep_bug(Grafo* G,long depthLimit);
    static std::tuple<std::vector<double>,std::vector<double> >  boxCountingCheckPlaneSweep(Grafo* G,long depthLimit);
    static std::vector<double> sandBox_severalNodes(Grafo* G,long idStartNode,long idEndNode);
    static void calculateFDSetOfPoints_preparationForParallel(std::vector<std::set<Point2d> >& pointsPerIdCluster,long startIndex,long endIndex,std::vector<double>& fd);

private:
    static std::pair<double,std::pair<long,long> > detectStartingGridSize(Grafo* G,double maxDepth);
};

#endif /* defined(__harmonicCities__FractalDimension__) */

//
//  Fxy.h
//  harmonicCities
//
//  Created by Carlos Molinero on 12/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Fxy__
#define __harmonicCities__Fxy__

#include <stdio.h>
#include "Point2d.h"
#include "Grafo.h"
#include "LinearRegression.h"
#include "InterfaceMultiFractalAnalysis.h"
#include "DualExtendedGraph.h"
#include "Point2d.h"
// #include <Eigen/Dense>
//#include "Node.h"
//#include "Graph.h"
//#include "QTree.h"
//#include "City.h"
//#include "Network.h"


class Fxy{
public:

    Fxy();
    std::vector<double> x;
    std::vector<double> y;
    double scaleX;
    double scaleY;
    double minX;
    double minY;
    double totalDistance;
    bool initialised;
    double spacingX;
    double spacingY;
    std::vector<double> derivative;
    std::vector<double> integral;
    bool derivated;
    bool integrated;
    std::vector<Point2d> setOfPoints;
    // bool equalSpacing;
    static const int GAUSSIAN_AV=0;
    static const int UNIFORM_AV=1;

    static void movingAverage(Fxy* f,int type,int width);
    static void interpolateDataInX(Fxy* f,double numberBreaks);
    static void interpolateDataInY(Fxy* f,double numberBreaks);
    static void interpolateData(Fxy* f,double numberBreaks);
    static Fxy interpolateDataInX(Fxy* f,std::vector<double>& newX);
    static void insertSetOfPoints(Fxy* f);
    // static void getDistribution(Fxy* f,std::vector<double> data);
    static void insertData(Fxy* f,std::vector<double>& x, std::vector<double>& y);
    static Fxy createFunction(std::vector<double>& x, std::vector<double>& y);
    static void approximate(Fxy* f);
    static Fxy getDerivative(Fxy* f);
    static Fxy getIntegral(Fxy* f);
    static void derivate(Fxy* f);
    static void integrate(Fxy* f);
    static double integrate(Fxy* f,double from,double to);

private:
	double definitionSubdivisionX;

};

#endif /* defined(__harmonicCities__Fxy__) */

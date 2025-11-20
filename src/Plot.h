//
//  Plot.h
//  harmonicCities
//
//  Created by Carlos Molinero on 10/06/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#ifndef __harmonicCities__Plot__
#define __harmonicCities__Plot__

#include <stdio.h>
#include <list>
//#include "Eigen/Dense"
#include "Point2d.h"
#include <vector>
#include <math.h>
#include <iostream>
#include "TextFile.h"

class Plot{
public:
    static const int DYNAMIC=0;
    static const int BINS=1;
    static const int EUCLIDEAN=2;

    bool regression;
    int mode;
    double width;
    double height;
    bool multiple;
    bool limited=true;
    long maxSize=500;
    double max;
    double min;
    double maxX,maxY,minX,minY;
    double slopeRegression;
    double interceptRegression;
    Point2d location;
//    std::queue<Eigen::VectorXcd> setOfMatrixOfValues;
    std::list<double> setOfValuesDynamic;
    std::vector<double> setOfValuesBins;
    std::list<Point2d> setOfValuesEuclidean;
//    void setStaticMode();
    void addValue(double value);
    void addValue(double value,long position);
    void addValue(Point2d point);
    void addValues(std::vector<double> x,std::vector<double> y);
    
    void save(std::string nameFile);
    
    Plot();
//    std::queue<double> getValue
};
#endif /* defined(__harmonicCities__Plot__) */

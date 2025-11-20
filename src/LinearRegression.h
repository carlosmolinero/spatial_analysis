//
//  LinearRegression.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 01/11/2014.
//  modification of a class posted online by David C. Swaim II, http://www.oocities.org/david_swaim/cpp/linregc.htm
//  Copyright (c) 2014 UCL. All rights reserved.
//

#ifndef __centralitiesPureCpp11__LinearRegression__
#define __centralitiesPureCpp11__LinearRegression__

#include <stdio.h>
#include <vector>
#include <math.h>
#include "Point2d.h"
#include <list>
class LinearRegression
{
public:
    LinearRegression();
    virtual ~LinearRegression();
    static std::pair<long,long> detectUpperAndLowerCutoff(std::vector<double> &x,std::vector<double> &y,bool logged);
    static std::pair<LinearRegression,std::pair<long,long> > computeBestFit(std::vector<double> &x,std::vector<double> &y,bool logged);
    static LinearRegression compute(std::vector<double> &x,std::vector<double> &y,bool logged);
    static LinearRegression compute(std::vector<Point2d> &points,bool logged);
    static LinearRegression compute(std::vector<double> &x,std::vector<double> &y,long lowerCutoff,long upperCutoff,bool logged);
    
    double slope,intercept,R2,R,adjusted_R2,stdError;
    
protected:
private:
    void calculate(std::vector<double> &x,std::vector<double> &y,long init,long end,bool logged);
    
    void calculate(std::vector<double> &x,std::vector<double> &y);
    void calculate(std::vector<double> &x,std::vector<double> &y,long init,long end);
    void calculate(std::vector<Point2d> &points);
    void calculate(std::vector<Point2d> &points,bool logged);
    void calculate(std::vector<Point2d> &points,long init,long end);
    void calculate(std::list<Point2d> &points);
    void calculate(std::vector<double> &x,std::vector<double> &y,bool logged);
};

#endif /* defined(__centralitiesPureCpp11__LinearRegression__) */

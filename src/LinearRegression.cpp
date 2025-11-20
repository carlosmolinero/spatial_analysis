//
//  LinearRegression.cpp
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 01/11/2014.
//  modification of a class posted online by David C. Swaim II, http://www.oocities.org/david_swaim/cpp/linregc.htm
//  Copyright (c) 2014 UCL. All rights reserved.
//

#include "LinearRegression.h"

LinearRegression::LinearRegression(){
    intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    
}
LinearRegression::~LinearRegression(){
    
}


std::pair<long,long> LinearRegression::detectUpperAndLowerCutoff(std::vector<double> &x,std::vector<double> &y,bool logged){
    LinearRegression linearRegression;
    linearRegression.calculate(x, y,logged);
    LinearRegression lrTemp;
    long finalUpperCutoff=1;
    lrTemp.calculate(x, y,0,x.size()-finalUpperCutoff,logged);
    if(lrTemp.adjusted_R2<=linearRegression.adjusted_R2){
        finalUpperCutoff=0;
    }else{
        double previousAdjustedR2=linearRegression.adjusted_R2;
        finalUpperCutoff=1;
        //                        finalUpperCutoff=0;
//        while(std::isfinite(lrTemp.adjusted_R2)&&lrTemp.adjusted_R2>previousAdjustedR2&&x.size()-finalUpperCutoff>=1){
        while(std::isfinite(lrTemp.adjusted_R2)&&lrTemp.adjusted_R2>previousAdjustedR2){
            finalUpperCutoff++;
            previousAdjustedR2=lrTemp.R2;
            lrTemp.calculate(x, y,0,x.size()-finalUpperCutoff,logged);
        }
        finalUpperCutoff--;
    }
    
    
    long finalLowerCutoff=1;
    linearRegression.calculate(x, y,0,x.size()-finalUpperCutoff,logged);
    lrTemp.calculate(x, y,finalLowerCutoff,x.size()-finalUpperCutoff,logged);
    if(lrTemp.adjusted_R2<=linearRegression.adjusted_R2){
        finalLowerCutoff=0;
    }else{
        double previousAdjustedR2=linearRegression.adjusted_R2;
        //                        finalUpperCutoff=0;
//        while(std::isfinite(lrTemp.adjusted_R2)&&lrTemp.adjusted_R2>previousAdjustedR2&&x.size()-finalUpperCutoff-finalLowerCutoff>=1){
        while(std::isfinite(lrTemp.adjusted_R2)&&lrTemp.adjusted_R2>previousAdjustedR2){
            finalLowerCutoff++;
            previousAdjustedR2=lrTemp.adjusted_R2;
            lrTemp.calculate(x, y,finalLowerCutoff,x.size()-finalUpperCutoff,logged);
        }
        finalLowerCutoff--;
    }
    return std::pair<long,long> (finalLowerCutoff,finalUpperCutoff);
}

std::pair<LinearRegression,std::pair<long,long> > LinearRegression::computeBestFit(std::vector<double> &x,std::vector<double> &y,bool logged){
    LinearRegression lr;
    std::pair<long,long> lowerUpperCutoffs=LinearRegression::detectUpperAndLowerCutoff(x, y, logged);
    lr.calculate(x, y, lowerUpperCutoffs.first, x.size()-lowerUpperCutoffs.second, logged);
    return std::pair<LinearRegression,std::pair<long,long> > (lr,lowerUpperCutoffs);
}

LinearRegression LinearRegression::compute(std::vector<double> &x,std::vector<double> &y,bool logged){
    LinearRegression lr;
//    std::pair<long,long> lowerUpperCutoffs=LinearRegression::detectUpperAndLowerCutoff(x, y, logged);
    lr.calculate(x, y, logged);

    return lr;
}
LinearRegression LinearRegression::compute(std::vector<Point2d> &points,bool logged){
    LinearRegression lr;
    //    std::pair<long,long> lowerUpperCutoffs=LinearRegression::detectUpperAndLowerCutoff(x, y, logged);
    lr.calculate(points, logged);
    
    return lr;
}
LinearRegression LinearRegression::compute(std::vector<double> &x,std::vector<double> &y,long lowerCutoff,long upperCutoff,bool logged){
    LinearRegression lr;
    //    std::pair<long,long> lowerUpperCutoffs=LinearRegression::detectUpperAndLowerCutoff(x, y, logged);
    lr.calculate(x, y,lowerCutoff,upperCutoff, logged);
    return lr;
}

void LinearRegression::calculate(std::vector<double> &x,std::vector<double> &y,long init, long end)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (x.size()>0&&x.size()==y.size())
    {
        for(long i=init;i<end;i++){
            double xTemp=x[i];
            double yTemp=y[i];
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=end-init;
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2 =adjusted_R2 = R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2 =adjusted_R2 = R = stdError = 0.0;
    }
}
void LinearRegression::calculate(std::vector<double> &x,std::vector<double> &y)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (x.size()>0&&x.size()==y.size())
    {
        for(long i=0;i<x.size();i++){
            double xTemp=x[i];
            double yTemp=y[i];
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=(double)x.size();
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    }
}

void LinearRegression::calculate(std::vector<double> &x,std::vector<double> &y,bool logged)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (x.size()>0&&x.size()==y.size())
    {
        for(long i=0;i<x.size();i++){
            double xTemp=x[i];
            double yTemp=y[i];
            if(logged){
                xTemp=log(xTemp);
                yTemp=log(yTemp);
            }
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=(double)x.size();
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    }
}

void LinearRegression::calculate(std::vector<double> &x,std::vector<double> &y,long init,long end,bool logged)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (x.size()>0&&x.size()==y.size())
    {
        for(long i=init;i<end;i++){
            double xTemp=x[i];
            double yTemp=y[i];
            if(logged){
                xTemp=log(xTemp);
                yTemp=log(yTemp);
            }
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=end-init;
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    }
}


void LinearRegression::calculate(std::vector<Point2d> &points)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (points.size()>0)
    {
        for(long i=0;i<points.size();i++){
            double xTemp=points[i].x;
            double yTemp=points[i].y;
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=(double)points.size();
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    }
}
void LinearRegression::calculate(std::vector<Point2d> &points,bool logged)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (points.size()>0)
    {
        for(long i=0;i<points.size();i++){
            double xTemp=points[i].x;
            double yTemp=points[i].y;
            if(logged){
                xTemp=log(xTemp);
                yTemp=log(yTemp);
            }
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=(double)points.size();
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    }
}

void LinearRegression::calculate(std::vector<Point2d> &points,long init,long end)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (points.size()>0)
    {
        for(long i=init;i<end;i++){
            double xTemp=points[i].x;
            double yTemp=points[i].y;
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=end-init;
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2  =adjusted_R2= R = stdError = 0.0;
    }
}

void LinearRegression::calculate(std::list<Point2d> &points)
{
    double n=0;
    double sumX=0;
    double sumY=0;
    double sumXsquared=0;
    double sumYsquared=0;
    double sumXY=0;
    double EPSILON=0.000000000001;
    
    if (points.size()>0)
    {
        while(points.size()>0){
            Point2d point=points.front();
            points.pop_front();
            double xTemp=point.x;
            double yTemp=point.y;
            n++;
            sumX += xTemp;
            sumY += yTemp;
            sumXsquared += xTemp * xTemp;
            sumYsquared += yTemp * yTemp;
            sumXY += xTemp * yTemp;
        }
        
        if (fabs( double(n) * sumXsquared - sumX * sumX) > EPSILON)
        {
            slope = ( double(n) * sumXY - sumY * sumX) /
            ( double(n) * sumXsquared - sumX * sumX);
            intercept = (sumY - slope * sumX) / double(n);
            
            double sx = slope * ( sumXY - sumX * sumY / double(n) );
            double sy2 = sumYsquared - sumY * sumY / double(n);
            double sy = sy2 - sx;
            
            R2 = sx / sy2;
            R = sqrt(R2);
            stdError = sqrt(sy / double(n - 2));
            double numberVariables=1;
            double N=(double)points.size();
            adjusted_R2=1-((1-R2)*(N-1)/(N-numberVariables-1));
        }
        else
        {
            intercept = slope = R2 =adjusted_R2= R = stdError = 0.0;
        }
    }
    else
    {
        intercept = slope = R2 =adjusted_R2 = R = stdError = 0.0;
    }
}

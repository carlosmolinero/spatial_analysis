//
//  Plot.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 10/06/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#include "Plot.h"

Plot::Plot(){
    width=450;
    height=450;
    multiple=false;
    maxSize=150;
    limited=true;
    max=-INFINITY;
    maxX=-INFINITY;
    maxY=-INFINITY;
    
    min=INFINITY;
    minX=INFINITY;
    minY=INFINITY;
    location=Point2d(0,0);
   
    mode=DYNAMIC;
    regression=false;
    
}
//void Plot::setStaticMode(){
//    if(setOfValuesStatic.size()==0){
//        setOfValuesStatic.resize(maxSize,0);
//    }
//}

void Plot::addValue(double value){
    
    if(limited&&setOfValuesDynamic.size()==0){
        for(long i=0;i<maxSize-1;i++){
            setOfValuesDynamic.push_back(value);
        }
        
    }
    setOfValuesDynamic.push_back(value);
    if(limited&&setOfValuesDynamic.size()>maxSize){
        setOfValuesDynamic.pop_front();
    }
    
    
    if(value>max){
        max=value+value/1000+.000000001;
    }
    if(value<min){
        min=value-value/1000-.000000001;
    }
    if(!limited){
        maxSize=setOfValuesDynamic.size();
    }
}
void Plot::addValue(double value,long position){
    mode=BINS;
    if(setOfValuesBins.size()==0){
        setOfValuesBins.resize(maxSize,0);
    }
    setOfValuesBins[position]=value;
    
    
    if(value>max){
        max=value+value/1000+.000000001;
    }
    if(value<min){
        min=value-value/1000-.000000001;
    }
}
void Plot::addValue(Point2d point){
    mode=EUCLIDEAN;

    setOfValuesEuclidean.push_back(point);
    
    
    if(point.x>maxX){
        maxX=point.x+point.x/1000+.000000001;
    }
    if(point.x<minX){
        minX=point.x-point.x/1000-.000000001;
    }
    
    if(point.y>maxY){
        maxY=point.y+point.y/1000+.000000001;
    }
    if(point.y<minY){
        minY=point.y-point.y/1000-.000000001;
    }
}
void Plot::addValues(std::vector<double> x,std::vector<double> y){
//    maxX=-INFINITY;
//    maxY=-INFINITY;
//    
//
//    minX=INFINITY;
//    minY=INFINITY;
    setOfValuesEuclidean.clear();
    mode=EUCLIDEAN;
    for(long i=0;i<x.size();i++){
        Point2d point(x[i],y[i]);
        setOfValuesEuclidean.push_back(point);
    
        
        if(point.x>maxX){
            maxX=point.x+point.x/1000+.000000001;
        }
        if(point.x<minX){
            minX=point.x-point.x/1000-.000000001;
        }
        
        if(point.y>maxY){
            maxY=point.y+point.y/1000+.000000001;
        }
        if(point.y<minY){
            minY=point.y-point.y/1000-.000000001;
        }
    }
}

void Plot::save(std::string nameFile){
   

    if(mode==DYNAMIC){
        std::vector<double> values;
        for (auto it=setOfValuesDynamic.cbegin(); it != setOfValuesDynamic.cend(); ++it)
        {
            double value=*it;
            values.push_back(value);
            
        }
        TextFile::writeToFile(nameFile, values, false);
    }
    if(mode==EUCLIDEAN){
        std::vector<std::string> values;
        for (auto it=setOfValuesEuclidean.cbegin(); it != setOfValuesEuclidean.cend(); ++it)
        {
            double x=it->x;
            double y=it->y;
            std::stringstream stringstream;
            stringstream<<x<<" "<<y;
            values.push_back(stringstream.str());
            
        }
        TextFile::writeToFile(nameFile, values, false);
    }
}

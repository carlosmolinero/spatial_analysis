//
//  Metropolis.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 19/09/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Metropolis.h"
double Metropolis::calculateSize(InterfaceCityGeneration* interface){
    double value=0;
    for(long i=0;i<citiesIndexes.size();i++){
        value+=interface->cities[citiesIndexes[i]].x;
    }
    return value;
}




Point2d Metropolis::calculateCentroid(InterfaceCityGeneration* interface){
    Point2d centroid;
    centroid.x=0.0;
    centroid.y=0.0;
    double totalMass=0.0;
    for(long i=0;i<citiesIndexes.size();i++){
       
            centroid.x+=interface->cities[citiesIndexes[i]].node->location.x*interface->cities[citiesIndexes[i]].x;
            centroid.y+=interface->cities[citiesIndexes[i]].node->location.y*interface->cities[citiesIndexes[i]].x;
            
            totalMass+=interface->cities[citiesIndexes[i]].x;
        
    }
    centroid.x/=totalMass;
    centroid.y/=totalMass;
    
    
    return centroid;
    
}


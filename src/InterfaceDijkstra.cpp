//
//  InterfaceDijkstra.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 08/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "InterfaceDijkstra.h"

InterfaceDijkstra::InterfaceDijkstra(){
    onlyDistances=true;
    minDistancesResult.clear();
    parents.clear();
    numChildren.clear();
    idNodeInit=-1;
    numberNodesInCutoff=0;
    totalDistance=0;
    includingBorderLinks=false;
    totalDistanceIncludingBorderLinks=0;
    measuringTotalDistances=false;
    birdEyeCutoff=false;
    percentagesOfOutsideNodes=0;
    maxDistanceInSystem=0;
    idsInCutoff.clear();
}

long InterfaceDijkstra::size(){
    return minDistancesResult.size();
}
bool InterfaceDijkstra::isBirdEyeCutoff(){
    return birdEyeCutoff;
}
void InterfaceDijkstra::setBirdEyeCutoff(bool b){
    birdEyeCutoff=b;
}

void InterfaceDijkstra::resize(long newSize){
    if(onlyDistances){
        minDistancesResult.resize(newSize,INFINITY);
    }
    else{
        minDistancesResult.resize(newSize,INFINITY);
        parents.resize(newSize,-1);
        numChildren.resize(newSize,0);
    }

}
bool InterfaceDijkstra::isMeasuringTotalDistances(){
    return measuringTotalDistances;
}
void InterfaceDijkstra::includeBorderLinks(bool b){
    includingBorderLinks=b;
}
bool InterfaceDijkstra::onlyCalculatingDistances(){
    return onlyDistances;
}

bool InterfaceDijkstra::includeBorderLinks(){
    return includingBorderLinks;
}

void InterfaceDijkstra::reset(){

        minDistancesResult.clear();
        parents.clear();
        numChildren.clear();
        idsInCutoff.clear();
        maxDistanceInSystem=0;


}

void InterfaceDijkstra::increaseNumChildren(long id){
    if(!onlyDistances){
        numChildren[id]++;
    }
}
void InterfaceDijkstra::decreaseNumChildren(long id){
    if(!onlyDistances){
        numChildren[id]--;
    }
}
void InterfaceDijkstra::setNumChildren(long id,long num){
    numChildren[id]=num;
}
long InterfaceDijkstra::getNumChildren(long id){
    if(!onlyDistances){
        return numChildren[id];
    }else{
        return 0;
    }
}
void InterfaceDijkstra::setParentID(long id, long parentID){
    if(!onlyDistances){
        parents[id]=parentID;
    }
}
long InterfaceDijkstra::getParentID(long id){
    if(!onlyDistances){
        return parents[id];
    }else{
        return -1;
    }

}
void InterfaceDijkstra::setMinDistance(long id,double distance){
    minDistancesResult[id]=distance;
}
double InterfaceDijkstra::getMinDistance(long id){
    return minDistancesResult[id];
}

void InterfaceDijkstra::prepareForBetweenness(){
    onlyDistances=false;
    if(minDistancesResult.size()>0){
        parents.resize(minDistancesResult.size(),-1);
        numChildren.resize(minDistancesResult.size(),0);
    }
}

void InterfaceDijkstra::prepareToMeasureTotalDistances(){
    prepareForBetweenness();
    measuringTotalDistances=true;
}

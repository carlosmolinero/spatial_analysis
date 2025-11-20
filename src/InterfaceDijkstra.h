//
//  InterfaceDijkstra.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 08/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__InterfaceDijkstra__
#define __SpatialAnalysis__InterfaceDijkstra__

#include <stdio.h>
#include <deque>
#include <vector>
#include <cmath>

class InterfaceDijkstra{
public:
    static const int WEIGHTED=0;
    static const int TOPOLOGICAL=1;
    static const int EUCLIDEAN=2;
    InterfaceDijkstra();
    void resize(long newSize);
    void increaseNumChildren(long id);
    void decreaseNumChildren(long id);
    void setNumChildren(long id,long num);
    long getNumChildren(long id);
    void setParentID(long id, long parentID);
    long getParentID(long id);
    void setMinDistance(long id,double distance);
    double getMinDistance(long id);
    void prepareForBetweenness();
    void prepareToMeasureTotalDistances();
    long idNodeInit;
    long numberNodesInCutoff;
    void reset();
    long size();
    bool onlyCalculatingDistances();
    std::vector<long> idsInCutoff;
    double totalDistance;
    double totalDistanceIncludingBorderLinks;
    double maxDistanceInSystem;
    bool includeBorderLinks();
    void includeBorderLinks(bool b);
    bool isMeasuringTotalDistances();
    bool isBirdEyeCutoff();
    void setBirdEyeCutoff(bool b);
    double percentagesOfOutsideNodes;
//    double maxEuclideanDistance;

private:
    bool birdEyeCutoff;
    bool measuringTotalDistances;
    bool onlyDistances;
    bool includingBorderLinks;
    std::vector<double> minDistancesResult;
    std::vector<long> parents;
    std::vector<long> numChildren;

};

#endif /* defined(__SpatialAnalysis__InterfaceDijkstra__) */

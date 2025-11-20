//
//  Customize.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 11/02/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __centralitiesPureCpp11__Customize__
#define __centralitiesPureCpp11__Customize__

#include <stdio.h>
#include "QTree.h"
//class Graph;
//#include "Graph.h"
//#include "Node.h"
#include <vector>


class Customize
{
    
    
public:
    
    static const int BICYCLE_COMMUTER=1;
    static const int BICYCLE_LEISURE=2;
    static const int BICYCLE_SPORT=3;
    
    double applyDistributionDistancesByMode(int mode,double distance);
//    void prepareGeneratedRoundTrips(Graph* graph,QTree* quadTree,Node* &nodeInit,double distanceLimit);
//    void modifyGeneratedTripsMelbourne(std::vector<Node*> orderedCutoff,Node* nodeInit,std::vector<int> setOfDistancesToCalculate,int distanceIndex);
    
    Customize();
    
    bool useDistributionDistances;
    bool useGeneratedAndAttractedTrips;
   
};

#endif /* defined(__centralitiesPureCpp11__Customize__) */

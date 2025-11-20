//
//  ClusterField.h
//  harmonicCities
//
//  Created by Carlos Molinero on 08/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__ClusterField__
#define __harmonicCities__ClusterField__

#include <stdio.h>
#include "Functions.h"
#include "Point2d.h"
//#include "Node.h"
//#include "Graph.h"

class ClusterField{
public:
    double value;
//    double normDistributedValue;
//    double artificialResources;
    Point2d corner1;
    Point2d corner2;
    ClusterField(Point2d corner1,Point2d corner2);
    Point2d calculateCentroid();
    long numberNodes;
    long id;
    std::vector<long> idsNodesInCluster;
//    std::vector<Node*> getNodes(Graph* graph);
    
};

#endif /* defined(__harmonicCities__ClusterField__) */

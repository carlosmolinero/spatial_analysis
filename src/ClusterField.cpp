//
//  ClusterField.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 08/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "ClusterField.h"


ClusterField::ClusterField(Point2d corner1,Point2d corner2){
//    value=Functions::random(-300,300,true);
    value=0;
    this->corner1=corner1;
    this->corner2=corner2;
    numberNodes=0;
    
}
Point2d ClusterField::calculateCentroid(){
    Point2d centroid=Point2d((corner1.x+corner2.x)/2.0,(corner1.y+corner2.y)/2.0);
    return centroid;
}

//std::vector<Node*> ClusterField::getNodes(Graph* graph){
//    std::vector<Node*> nodes;
//    nodes.resize(idsNodesInCluster.size());
//    for(long i=0;i<idsNodesInCluster.size();i++){
//        nodes[i]=&graph->nodes[idsNodesInCluster[i]];
//    }
//    return nodes;
//}
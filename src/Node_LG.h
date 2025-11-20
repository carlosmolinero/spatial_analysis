//
//  Node_LG.h
//  spatialTools
//
//  Created by Carlos Molinero on 04/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __spatialTools__Node_LG__
#define __spatialTools__Node_LG__

#include <stdio.h>
#include <vector>
#include "Point2d.h"

class Node_LG{
public:
    long id;
    long id_inOriginalGraph;
    long long originalID;
    std::vector<long> idsNeighbors;
    std::vector<double> weights;
    Point2d location;
    
//    void operator = (const Node_LG& other){
//        id=(other.id);
//        id_inOriginalGraph=other.id_inOriginalGraph;
//        originalID=other.originalID;
//        idsNeighbors.resize(other.idsNeighbors.size());
//        weights.resize(other.weights.size());
//        for(long i=0;i<other.idsNeighbors.size();i++){
//            idsNeighbors[i]=other.idsNeighbors[i];
//            weights[i]=other.weights[i];
//        }
//        location=other.location;
//        
//    }
};
#endif /* defined(__spatialTools__Node_LG__) */

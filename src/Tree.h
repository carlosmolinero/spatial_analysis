//
//  Tree.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 14/03/2017.
//  Copyright (c) 2017 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__Tree__
#define __SpatialAnalysis__Tree__

#include <stdio.h>
#include <vector>
#include "Grafo.h"

class Tree{
public:
       static long getParent(Grafo* tree,long node);
       static std::vector<long> getAllParents(Grafo* tree,long node);
       static std::unordered_map<long,double> getCoordinatesOfANodeInATree(Grafo* tree,long node);
       static std::vector<long> getParentsInHierarchicalMetricTreeUpToADepth(Grafo* tree,std::vector<long> currentClusters,std::vector<long> depths,long referenceDepth);
       static std::vector<long> getSonsInHierarchicalMetricTree(Grafo* tree,long node);
       static std::vector<long> getSonsAllLevelsInHierarchicalMetricTree(Grafo* tree,long node);
       static std::vector<long> getLeavesSonsOfANode(Grafo* tree,long node);
       static double distanceBetweenNodesInATree(std::unordered_map<long,double> coordinatesA,std::unordered_map<long,double> coordinatesB);
       static long calculateTopologicalDistancesInATreeBetweenTwoNodes(Grafo* T,long idA,long idB);
private:
};
#endif /* defined(__SpatialAnalysis__Tree__) */

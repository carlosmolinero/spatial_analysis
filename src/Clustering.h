//
//  Clustering.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 14/03/2017.
//  Copyright (c) 2017 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__Clustering__
#define __SpatialAnalysis__Clustering__

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "Grafo.h"
#include <iostream>

class Clustering{
public:
        static const int manhattan=0;
        static const int euclidean=1;
        static const int chisquared=2;

       static std::vector<long> kMeans(std::vector<std::unordered_map<long,double> >& coordinates,long numClusters,int typeDistance);
       static double manhattanDistance(std::unordered_map<long,double>& coordinatesA,std::unordered_map<long,double> coordinatesB);

private:
};
#endif /* defined(__SpatialAnalysis__Clustering__) */

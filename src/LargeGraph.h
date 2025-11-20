//
//  LargeGraph.h
//  spatialTools
//
//  Created by Carlos Molinero on 04/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __spatialTools__LargeGraph__
#define __spatialTools__LargeGraph__

#include <stdio.h>
#include <vector>
#include "Node_LG.h"
#include <queue>
#include "Point2d.h"
#include "Functions.h"

class LargeGraph{
public:
    LargeGraph();
    long n;
    long m;
    std::vector<Node_LG> nodes;
    bool bidirectional;
    static void create(LargeGraph* G,std::vector<std::vector<double> > ncol,std::vector<std::vector<double> > coordinates,bool directed);
    static void transformToBidirectional(LargeGraph* G);
    static void removeNodesDegree2(LargeGraph* G);
    static void removeNodesDegree2(LargeGraph* G,LargeGraph* result);
    static void networkPercolation(LargeGraph* G,LargeGraph* result,double threshold);
    static void getColorsFromComponents(LargeGraph* G,LargeGraph* separatedComponents,std::vector<long> &colors,std::vector<long> &sizes,long &maxColor);
    static void generateSuperGraphFromColors(LargeGraph* G,LargeGraph* superGraph,std::vector<long> &colors,long maxColor);
    
};
#endif /* defined(__spatialTools__LargeGraph__) */

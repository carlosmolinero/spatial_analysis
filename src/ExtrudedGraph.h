//
//  CA.h
//  harmonicCities
//
//  Created by Carlos Molinero on 28/01/2016.
//  Copyright (c) 2016 UCL. All rights reserved.
//

#ifndef __ExtrudedGraph__
#define __ExtrudedGraph__

#include <stdio.h>
#include <unordered_map>
#include<vector>
#include "Grafo.h"
#include <string>


class ExtrudedGraph{
public:
    Grafo G;
    Point2d centroid;
    double heightPerLevel;
    long numberLevels;
    double totalHeight;
    std::string note;
};
#endif /* defined(__harmonicCities__CA__) */

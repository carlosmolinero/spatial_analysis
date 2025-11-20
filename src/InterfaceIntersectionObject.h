//
//  Fxy.h
//  harmonicCities
//
//  Created by Carlos Molinero on 12/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __InterfaceIntersectionObject__
#define __InterfaceIntersectionObject__

#include <stdio.h>
#include "Point2d.h"
// class Grafo;
// #include "Grafo.h"
// #include "Point2d.h"
#include <vector>
// #include <tuple>




class InterfaceIntersectionObject{
public:

    // InterfaceIntersectionObject();
    // Grafo* G;
    std::vector<std::vector<long> > idsIntersected;
    std::vector<Point2d> intersections;
    // std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
    // bool keepTrackChanges;



};

#endif /* defined(__InterfaceIntersectionObject__) */

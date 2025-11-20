//
//  potentialField.h
//  harmonicCities
//
//  Created by Carlos Molinero on 08/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__PotentialField__
#define __harmonicCities__PotentialField__

#include <stdio.h>
#include <vector>
#include "ClusterField.h"

class PotentialField{
    public:
    Point2d initLocation;
    long numberObjectsInRow;
    double width;
    double minX,minY,maxX,maxY;
    std::vector<ClusterField> clusters;
    double max;
    double min;
    PotentialField();
    void setValue(ClusterField* cluster,double value);
    void reset();
    ClusterField* getCluster(Point2d &location);
    void create(double minX,double minY,double maxX,double maxY,double definition);
    double getNormalizedValue(ClusterField* cluster);
        double getNormalizedLoggedValue(ClusterField* cluster);
    std::vector<ClusterField*> vonNeumannNeighborhood(ClusterField* cluster);
    std::vector<ClusterField*> squareNeighborhood(ClusterField* cluster);
    
};

#endif /* defined(__harmonicCities__PotentialField__) */

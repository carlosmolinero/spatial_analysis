//
//  Metropolis.h
//  harmonicCities
//
//  Created by Carlos Molinero on 19/09/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Metropolis__
#define __harmonicCities__Metropolis__

#include <stdio.h>
#include "City.h"
#include <vector>
class InterfaceCityGeneration;
#include "InterfaceCityGeneration.h"
#include "Point2d.h"

class Metropolis{
public:
    std::vector<long> citiesIndexes;
    long id;
    double calculateSize(InterfaceCityGeneration* interface);
    Point2d calculateCentroid(InterfaceCityGeneration* interface);
    
};
#endif /* defined(__harmonicCities__Metropolis__) */

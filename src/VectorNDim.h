//
//  VectorNDim.h
//  harmonicCities
//
//  Created by Carlos Molinero on 08/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__VectorNDim__
#define __harmonicCities__VectorNDim__

#include <stdio.h>
#include <cstdarg>
#include <vector>
#include <iostream>
#include <sstream>

class VectorNDim{
    public:
//    int dimensions;
    VectorNDim();
//    VectorNDim(int dimensions);
    VectorNDim(std::vector<double> values);
//    VectorNDim(double a,...);
    std::vector<double> values;
    double operator [](long index) const{return values[index];}
    double operator [](long index){return values[index];}
};

#endif /* defined(__harmonicCities__VectorNDim__) */

//
//  CA.h
//  harmonicCities
//
//  Created by Carlos Molinero on 28/01/2016.
//  Copyright (c) 2016 UCL. All rights reserved.
//

#ifndef __harmonicCities__CA__
#define __harmonicCities__CA__

#include <stdio.h>
#include <unordered_map>
#include "CellCA.h"
#include<vector>
class CA{
public:
    CA();
    long module;
    void init(long numCol,long numRow);
    bool bidirectional;
//    std::vector<float> values;
    std::vector<CellCA> cells;
//    void set(double value,long col,long row);
//    void set(CellCA* cell,long col,long row);
    CellCA* get(long col,long row);
};
#endif /* defined(__harmonicCities__CA__) */

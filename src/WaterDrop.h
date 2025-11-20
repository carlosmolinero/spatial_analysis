//
//  WaterDrop.h
//  centralityMeasuresPureCpp11
//
//  Created by Carlos Molinero on 09/08/2014.
//  Copyright (c) 2014 Carlos Molinero. All rights reserved.
//

#ifndef __centralityMeasuresPureCpp11__WaterDrop__
#define __centralityMeasuresPureCpp11__WaterDrop__

#include <iostream>
class WaterDrop
{
public:
    WaterDrop();
    virtual ~WaterDrop();
    long location;
    double level;
    double residue;
    double flow;
    double spilled;

private:
};

#endif /* defined(__centralityMeasuresPureCpp11__WaterDrop__) */

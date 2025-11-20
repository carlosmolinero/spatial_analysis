//
//  View.h
//  harmonicCities
//
//  Created by Carlos Molinero on 05/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__View__
#define __harmonicCities__View__

#include <stdio.h>
#include "DrawingObjects.h"
class View{
public:
    long current;
    std::vector<DrawingObjects> objects;
    View();
    std::string title;
};

#endif /* defined(__harmonicCities__View__) */

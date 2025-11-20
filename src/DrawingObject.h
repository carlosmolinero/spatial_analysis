//
//  DrawingObject.h
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__DrawingObject__
#define __harmonicCities__DrawingObject__

#include <stdio.h>
#include "Point2d.h"
#include "VectorNDim.h"
#include <string>

class DrawingObject{
public:
    DrawingObject();
    bool remove;
    bool active;
    int type;
    static const int LINE=0;
    static const int CIRCLE=1;
    static const int RECTANGLE=2;
    static const int CIRCLE_FILLED=3;
    static const int RECTANGLE_FILLED=4;
    static const int POINT=5;
    static const int TEXT=6;
    Point2d start,end;
    Point2d center;
    double radius;
    Point2d corner1,corner2;
    VectorNDim colorLine;
    VectorNDim colorFill;
    double widthLine;
    std::string text;
    double size;
    
};

#endif /* defined(__harmonicCities__DrawingObject__) */

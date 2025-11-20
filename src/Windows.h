//
//  Window.h
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Window__
#define __harmonicCities__Window__

#include <stdio.h>
#include "DrawingObjects.h"
#include "View.h"
#include <unordered_map>

class Windows{
public:
    
    long add(Point2d location,double sizeX,double sizeY);
    void setTitle(long index,std::string title);
    long add(long index);
    DrawingObjects* get(long indexWindow);
    DrawingObjects* get(std::string title);
    long size();
    void decreaseCurrent();
    void increaseCurrent();
    std::string getTitle(long index);

    std::unordered_map<std::string,long> indexByTitle;
    
private:
    std::vector<View> views;
};

#endif /* defined(__harmonicCities__Window__) */

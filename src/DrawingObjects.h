//
//  DrawingObjects.h
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__DrawingObjects__
#define __harmonicCities__DrawingObjects__

#include <stdio.h>
#include "DrawingObject.h"
//#include "Graph.h"
#include "Plot.h"
#include "PotentialField.h"

class DrawingObjects{
public:
    DrawingObjects();
    double scale;
    double startX;
    double startY;
    double startWindowX;
    double startWindowY;
    double widthWindowX;
    double heightWindowY;
    bool drawing;
    void addStableObject(DrawingObject object);
    void addTemporaryObject(DrawingObject object);
    void deleteTemporary();
    DrawingObject* getStableObject();
    DrawingObject* getTemporaryObject();
//    void drawGraph(Graph* graph);
//    void drawGraph(Graph* graph,VectorNDim colorEdges);
//    void drawGraphEdges(Graph* graph,VectorNDim colorEdges);
    void drawPotentialField(PotentialField* potentialField,bool BW,bool logged,bool minIs0);
    void zoomExtents();
    void copyViewParameters(DrawingObjects* otherWindow);
    void copyAllParameters(DrawingObjects* otherWindow);
    void drawPlot(std::vector<Plot> &plots);
    static VectorNDim rgb2hsv(VectorNDim rgb);
    static VectorNDim HSVtoRGB(VectorNDim hsv);
    static VectorNDim getColor(double value,double min,double max);
    
    
    
private:
    void setColor(VectorNDim color);
    void setColor(VectorNDim color,double alpha);
    void setColor(double r,double g,double b);
    void line(double x1,double y1,double x2,double y2,double width);
    void line(double x1,double y1,double x2,double y2);
    void text(std::string quote,Point2d location,int size);
    void filledCircle(double x, double y,double radius);
    void filledRectangle(double x1, double y1,double x2, double y2);
    void point(double x, double y,double radius);
    long indexStableObject;
    long indexTemporaryObject;
    std::vector<DrawingObject> stableObjects;
    std::vector<DrawingObject> temporaryObjects;
    VectorNDim colorNextObject;
    
};

#endif /* defined(__harmonicCities__DrawingObjects__) */

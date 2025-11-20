//
//  Nodo.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__Nodo__
#define __SpatialAnalysis__Nodo__

#include <stdio.h>
#include "Point2d.h"
#include <stdlib.h>
#include <string>
#include "LinkPointerVector.h"
class Link;
#include "Link.h"

class Nodo{
public:

    long id; //current id in vector

    std::string identifier; // GIS identifier from the original data set
    long originalID; //original id in vector, in case somethings are deleted
    Point2d location;
    LinkPointerVector<Link> links;

    double mass;
    double equivalentArea;
    double mass_upperLevel;

    Nodo();
    long getDegreeOut();
    long getDegreeIn();
    long getDegree();
    void copyProperties(Nodo* nodeToCopyFrom);

    std::vector<Link*> getLinksThatReachMe(bool directedGraph);
    void setLinksThatReachMe(std::vector<Link*> newLinksThatReachMe);
    void addLinkThatReachMe(Link* link);


private:
    std::vector<Link*> linksThatReachMe;


};

#endif /* defined(__SpatialAnalysis__Nodo__) */

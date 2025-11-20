//
//  Link.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__Link__
#define __SpatialAnalysis__Link__

#include <stdio.h>
class Nodo;
#include "Nodo.h"

class Link{
public:
    long id; //current id in vector

    std::string identifier; // GIS identifier from the original data set
    long originalID; //original id in vector, in case somethings are deleted

    // std::vector<long> labelsLevels;
    double weight;
    // bool inverted;


    Nodo* A();
    Nodo* B();
    void setB(Nodo* node);
    void setA(Nodo* node);
    Link();
    ~Link();
//    void checkDirection(bool invert);
    std::unordered_map<std::string,std::string> data;
    // std::vector<std::string> getDataVariableNames(long idLink);


    void copyProperties(Link* linkToCopyFrom);


    Nodo* commonNode(Link* other);
    Nodo* getOtherNode(Nodo* node);
private:
    Nodo* a;
    Nodo* b;


};

#endif /* defined(__SpatialAnalysis__Link__) */

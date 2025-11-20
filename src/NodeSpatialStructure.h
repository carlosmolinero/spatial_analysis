//
//  NodeSpatialStructure.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 16/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//
// #ifndef hashPoint2d
// #define hashPoint2d
// #include "Point2d.h"
// template <>
// struct std::__1::hash<Point2d > {
// public:
//     size_t operator()(Point2d point) const throw() {
//
//         return hash<double>()(point.x) ^ hash<double>()(point.y);
//
//     }
// };
// template <>
// struct std::__1::hash<Number > {
// public:
//     size_t operator()(Number n) const throw() {
//
//         return hash<double>()(n.value);
//
//     }
// };
// #endif

#ifndef __SpatialAnalysis__NodeSpatialStructure__
#define __SpatialAnalysis__NodeSpatialStructure__

#include <stdio.h>
#include <map>
#include "Number.h"
#include "Nodo.h"
#include "Grafo.h"
#include <unordered_map>
class NodeSpatialStructure{
public:
    // std::multimap<double,std::multimap<double, std::vector<Number> > > structure;
    std::unordered_map<Point2d, std::set<Nodo*> > matrix;
    // double minX=INFINITY;
    // double minY=INFINITY;
    // double maxX=-INFINITY;
    // double maxY=-INFINITY;
    double definition;

    void create(std::vector<Nodo*> &nodes,double definition);
    void create(Grafo* G,double definition);
    void moveNode(Nodo* node, Point2d finalPosition);
    std::vector<Nodo*> getNodesAround(Nodo* node,double distance);
    std::vector<Nodo*> getNodesAround(Point2d location,double distance);
    long getIdClosestNodeInOtherGraph(Nodo* node,Grafo* og,double definition);
    // long getIdClosestNodeInOtherGraph(Nodo* node,Grafo* og,double definition);
private:

};

#endif /* defined(__SpatialAnalysis__NodeSpatialStructure__) */

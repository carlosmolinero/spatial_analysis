//
//  SparseMatrix.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 04/10/2014.
//  Copyright (c) 2014 UCL. All rights reserved.
//
#ifndef hashPoint2d
#define hashPoint2d
#include "Point2d.h"
namespace std{
template <>
struct hash<Point2d > {
public:
    size_t operator()(Point2d point) const throw() {

        return hash<double>()(point.x) ^ hash<double>()(point.y);

    }
};
template <>
struct hash<Number > {
public:
    size_t operator()(Number n) const throw() {

        return hash<double>()(n.value);

    }
};
}
#endif

#ifndef __centralitiesPureCpp11__SparseMatrix__
#define __centralitiesPureCpp11__SparseMatrix__







#include <stdio.h>
#include <unordered_map>
#include "Number.h"
#include "Point2d.h"

//template <class T>
class SparseMatrix
{
public:
    SparseMatrix();
    long module;
//    void init(long numCol,long numRow);
    bool bidirectional;
    std::unordered_map<Point2d, Number > cells;
    void set(long col,long row,Number value);
    void setValue(long col,long row,double value);
    void setId(long col,long row,long value);
    void setValue(double col,double row,double value);
    void setId(double col,double row,long value);
    double getValue(long col,long row);
    long getId(long col,long row);
    void increase(long col,long row);
    void increaseBy(long col,long row,double increaseFactor);
    double getValue(double col,double row);
    long getId(double col,double row);
    void increase(double col,double row);
    void increaseBy(double col,double row,double increaseFactor);
    void set_NULL_Value(double valueNULL);
    long size();


private:

    Number NULL_;

};


#endif /* defined(__centralitiesPureCpp11__SparseMatrix__) */

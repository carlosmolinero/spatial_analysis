//
//  Functions.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 23/12/2014.
//  Copyright (c) 2014 Carlos Molinero. All rights reserved.
//

#ifndef __centralitiesPureCpp11__Functions__
#define __centralitiesPureCpp11__Functions__

#include <stdio.h>
class Point2d;
#include "Point2d.h"
#include <math.h>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <random>
#include "VectorNDim.h"
#include <chrono>
#include "Heap.h"
#include "Number.h"
#include <set>


// typedef std::unordered_map<long,double> MultiDimensionalCoordinates;

class Functions
{


public:
    static double median(std::vector<double> values);
    static double min(std::vector<double> values);
    static double max(std::vector<double> values);
    static double mean(std::vector<double>& values);
    static double area(std::vector<Point2d> points);
    static int sign(double x);
    static double getDistanceBetweenAngles(double angle1,double angle2);
    static double interpolate2d(Point2d origin, Point2d destination,double xPoint);
    static VectorNDim getMinMax(std::vector<double> values);
    static double decay(double input,double input0);
    static double decay(double input,double input0,double amplitude);
    static double decay(double input,double input0,double amplitude,double center);
    static double angularDecay(double input,double input0,double amplitude,double center);
    static double gaussianFunction(double x,double amplitude, double offset, double width);
    static bool containedInInterval(double value,double min,double max);
    static bool containedInArea(Point2d point,Point2d corner1,Point2d corner2);
    static bool rectangleContainedInRectangle(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B);
    static bool overlappingCornersOfRectangles(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B);
    static bool overlappingSidesOfRectangles(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B);
    static bool containedOrOverlappingRectangles(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B);
    static double random(double min, double max,bool normal);
    static double rnorm(double average, double deviation);
    static double rgamma(double shape, double rate);
    static double runiform(double min, double max);
    static double getAngle(Point2d initPoint,Point2d intermediatePoint,Point2d finalPoint);
    static double getAngle(Point2d initPoint,Point2d finalPoint);
    static double getAngleRadians(Point2d initPoint,Point2d intermediatePoint,Point2d finalPoint);
    static double getAngleRadians(Point2d initPoint,Point2d finalPoint);
    static double getAngularDistance(Point2d initPoint,Point2d intermediatePoint,Point2d finalPoint);
    static double getDistance(Point2d initPoint,Point2d finalPoint);
    static double getSquaredDistance(Point2d initPoint,Point2d finalPoint);
    static double getManhattanDistance(std::vector<double> initPoint,std::vector<double> finalPoint);
    static double getChiSquaredDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint);
    static double normalize(double value, double min, double max);
    static double normalize(double value, double max);
    static std::vector<double> normalize(std::vector<double> values);
    static double getCanberraDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint);
    static double getManhattanDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint);
    static double getEuclideanDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint);
    static std::unordered_map<long,double> sum(std::unordered_map<long,double> a,std::unordered_map<long,double>  b);
    static std::unordered_map<long,double> div(std::unordered_map<long,double> numerator,double  denominator);

    // static Point2d intersectionWithVerticalLine(Point2d &start,Point2d &end,Point2d &startVert,Point2d &endVert,bool &valid);
    // static Point2d intersectionWithHorizontalLine(Point2d &start,Point2d &end,Point2d &startHoriz,Point2d &endHoriz,bool &valid);

    static std::unordered_map<long,double> norm(std::unordered_map<long,double> vector);
//    static std::unordered_map<long,double> fullNorm(std::unordered_map<long,double> vector);
    static double abs(double number);
    static double max(double a,double b);
    static double mean(double a,double b);
    static double min(double a,double b);
    static long max(long a,long b);

    static long min(long a,long b);
    static double logNormalDist(double value,double m, double mu,double sigma,double divisor,double multiplier);

    static double gammaDistribution(double x, double beta,double amplitude, double width);
    static std::vector<double> orderValues(std::vector<double>& values,bool minToMax);
    static std::vector<long> orderValues(std::vector<long>& values,bool minToMax);
    static std::vector<long> getIndexesOfOrderedValues(std::vector<double> &values,bool minToMax);
    static std::vector<long> getIndexesOfOrderedValues(std::vector<long> &values,bool minToMax);
//    static void orderValues(std::vector<double>* values,bool minToMax);
    static std::vector<double> unique(std::vector<double> values);
    static std::vector<long> unique(std::vector<long> values);
    static std::vector<double> uniqueFromAlreadyOrderedVector(std::vector<double> valuesOrderedFromMinToMax);
    static std::vector<long> getIndexesOfUniqueValuesFromAlreadyOrderedVector(std::vector<double> valuesOrderedFromMinToMax);
    static std::vector<long> getIndexesOfUniqueValues(std::vector<double> values);
    static std::vector<long> getIndexesOfUniqueValues(std::vector<long> values);
    static std::vector<double> derivative(std::vector<double> values);
    static std::vector<double> derivative(std::vector<double> values,std::vector<double> separations);
    static long getLocationMaximum(std::vector<double> values);
    static long getLocationMinimum(std::vector<double> values);
    static long findLastPositionValue(std::vector<double> orderedValuesFromMinToMax,double value);
    static std::vector<double> orderVectorUsingAnotherVectorWithPositions(std::vector<double> values,std::vector<long> positions);
    static std::vector<long> orderVectorUsingAnotherVectorWithPositions(std::vector<long> values,std::vector<long> positions);
    static void intersection(Point2d &p1, Point2d &p2, Point2d &p3, Point2d &p4,Point2d &intersection, bool &validIntersection);
    static std::vector<long> getQuadrantsLine(Point2d &center,Point2d &start,Point2d &end,double sizeX,double sizeY);
    static std::vector<long> getQuadrantsLineOld(Point2d &center,Point2d &start,Point2d &end,double sizeX,double sizeY);
    static std::vector<Point2d> instersectionsLineWithBoundaryOfARectangle(Point2d &center,double sideX,double sideY,Point2d &start,Point2d &end);
    static long getQuadrant(Point2d center,Point2d point);
    static bool inBoundaryOfASquare(Point2d center, Point2d point,double sizeX,double sizeY);


    static float area_intersectionCircleWithRectangle(float x0,  float y0,float x1, float y1, float cx, float cy, float r);
    static double sampleDagumDistribution(double a,double b,double c);
    static double getValueAt(std::unordered_map<long,double>& map,long index,double valueToReturnIfNotExist);

private:
     static float positiveSectionCircle(float h, float r = 1);
    static float integralCircleSegment(float x, float h, float r = 1);
    static float area_intersectionCircleWithRectangle(float x0, float x1, float h, float r);
    static float area_intersectionCircleWithRectangle(float x0, float x1, float y0, float y1, float r);

//    static long getIndexOfValuesEqualOrUnderAValue(double value,std::vector<double> &values,std::vector<long> orderedIndexes);
};

#endif /* defined(__centralitiesPureCpp11__Functions__) */

//
//  Programs.h
//  harmonicCities
//
//  Created by Carlos Molinero on 06/07/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

//
//  Programs.h
//  harmonicCities
//
//  Created by Carlos Molinero on 06/07/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#ifndef __GenerativeProcedures__
#define __GenerativeProcedures__

#include <stdio.h>
#include "Grafo.h"
#include "InterfaceCityGeneration.h"
#include <math.h>
#include <stdlib.h>
#include "City.h"
#include "PotentialField.h"
#include "VectorNDim.h"
//#include "Eigen/Dense"
//#include "Eigen/Eigenvalues"
#include "Plot.h"
#include "FractalDimension.h"
//#include "Walker.h"
#include "TextFile.h"
#include "Functor.h"
#include <unordered_map>
#include "DrawingObjects.h"
#include "Singleton.h"
#include "Functions.h"
#include "Windows.h"
// #include "Network.h"
// #include "RTree.h"

class GenerativeProcedures{
public:
    
    static void generateInitialCities(InterfaceCityGeneration* interface,double d0,double saturationLevel,double maxX,double maxY,long numberCitiesPerRow);
//    static void migrate(InterfaceCityGeneration* interface,double proportionMigrations);
    static void loopGenerateCities(InterfaceCityGeneration* interface,double lambda,double alpha,long numberIterations);
    static void addMetropolisis(InterfaceCityGeneration* interface,long clusterId);
    static void cascade(InterfaceCityGeneration* interface,long idClusterInit,long numberPeopleToMove);
    static void addValuesToPotentialField(InterfaceCityGeneration* interface,long idCluster,long numberPeopleAdded);
    static void resetValuesPotentialField(InterfaceCityGeneration* interface);
    static double interpolate(double a,double b,double x);
    static double findnoise(double x,double y,int noiseKey);
    static double noise(double x,double y,int noiseKey);
    static std::vector<std::vector<double> > fractal_noise(long xInit,long yInit,int w,int h,double zoom,double expansionFactor,double p,int octaves,int noiseKey,bool ridged);
    static std::vector<std::vector<double> > generateTerrain(long xInit,long yInit,int w,int h,double zoom);
    static std::vector<std::vector<double> > getSlopeTerrain(std::vector<std::vector<double> > &terrain,long w,long h);
 
};
#endif /* defined(__GenerativeProcedures__) */

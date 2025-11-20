//
//  Entropy.h
//  harmonicCities
//
//  Created by Carlos Molinero on 12/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Entropy__
#define __harmonicCities__Entropy__

#include <stdio.h>
#include "Point2d.h"
#include "Grafo.h"
#include "LinearRegression.h"
#include "InterfaceMultiFractalAnalysis.h"
#include "DualExtendedGraph.h"
#include "Distribution.h"
#include "Geometry.h"
#include <tuple>

class Entropy{
public:
    
    // Entropy();
    
    static double calculateEntropyAreas(std::vector<double>& data);
    static std::tuple<double,double> calculateDiscreteEntropyAreas(std::vector<double>& x);
    static std::tuple<double,double> calculateDiscreteEntropyAreas(std::vector<long>& x);
    static double calculateEntropy(std::vector<double>& data);
    static std::tuple<double,double> createDelanuayAndCalculateItsEntropies(double totalArea,long numberAreas);
    
    
    
    
private:
    Fxy f;

};

#endif /* defined(__harmonicCities__Entropy__) */

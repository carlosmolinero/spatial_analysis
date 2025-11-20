//
//  Distribution.h
//  harmonicCities
//
//  Created by Carlos Molinero on 12/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Distribution__
#define __harmonicCities__Distribution__

#include <stdio.h>
#include "Point2d.h"
#include "Grafo.h"
#include "LinearRegression.h"
#include "InterfaceMultiFractalAnalysis.h"
#include "DualExtendedGraph.h"
#include "Fxy.h"
//#include "Node.h"
//#include "Graph.h"
//#include "QTree.h"
//#include "City.h"
//#include "Network.h"


class Distribution{
public:

    // Distribution();

    static Distribution createDistribution(std::vector<double>& data);
    static Distribution createCDFDistributionFromData(Fxy f);
    static double getMoment(Distribution* dis,double n);
    static double getMode(Distribution* dis);
    Fxy getP(std::vector<double>& x);
    Fxy getP(double x);
    bool initialised;
    Fxy f;

private:
    Distribution();

};

#endif /* defined(__harmonicCities__Distribution__) */

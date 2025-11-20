//
//  InterfaceCityGeneration.h
//  harmonicCities
//
//  Created by Carlos Molinero on 18/09/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#ifndef __harmonicCities__InterfaceCityGeneration__
#define __harmonicCities__InterfaceCityGeneration__

#include <stdio.h>
#include "PotentialField.h"
#include <vector>
#include "City.h"
#include "Grafo.h"
class Metropolis;
#include "Metropolis.h"
#include "Plot.h"

class InterfaceCityGeneration{
public:
    PotentialField cityField;
    PotentialField metropolisField;
    PotentialField potentialField;
    std::vector<City> cities;
    double d0;
    std::vector<long> indexCitiesByClusterId;
    double increment;
    Grafo cityGraph;
    double saturationLevel;
    std::vector<Metropolis> metropolises;
    Plot cascadesMovements;
    long maxIdMetropolis;
    InterfaceCityGeneration();
};

#endif /* defined(__harmonicCities__InterfaceCityGeneration__) */

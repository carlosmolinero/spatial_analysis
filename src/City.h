//
//  City.h
//  harmonicCities
//
//  Created by Carlos Molinero on 04/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__City__
#define __harmonicCities__City__

#include <stdio.h>
#include "Point2d.h"
#include "Nodo.h"
#include "Functions.h"
#include "PotentialField.h"

class City{
    public:
    long id;
    long metropolisId;
    bool withMemory;
    double a,b1,b2;
    double d0;
    double inc_t;
    double lambda;
    bool useAbs=true;
    double newTotalPopulation;
    Nodo* node;
    double numberTimes;
//    void calculateEigenVectors(std::vector<City> &citiesInRange);
    double calculatePop();
    static double calculateTotalPopulation(std::vector<City> &citiesInRange);
    void updateRandomValues();
    void updateRandomValues(double valuePotential);
    bool updatePopulation(std::vector<City> &citiesInRange);
    void updateIncreasePopulation(std::vector<City> &citiesInRange);
    void updateFinalValues();
    void init();
    void init(long id);
    double f;
    double v;
    double u;
    double u_prev;
    double x;
    double maxPopulation;
    double initialTotalPopulation;
    void decreaseLambda();
    
    
    
};

#endif /* defined(__harmonicCities__City__) */

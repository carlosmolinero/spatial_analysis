//
//  Functor.h
//  harmonicCities
//
//  Created by Carlos Molinero on 19/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Functor__
#define __harmonicCities__Functor__

#include <stdio.h>
#include <vector>
#include <math.h>
#include "Functions.h"
#include "VectorNDim.h"
class Functor{
public:
    Functor();
    Functor(double minRange, double maxRange, double incrementRange, bool circular, int mode);
    
    int mode;
    static const int SUM=0;
    static const int MIN=1;
    static const int MAX=2;
    static const int AVERAGE=2;
    void changeMode(int mode);
    void setFunction(double (*function)(double input));
    void setFunction(double (*function)(double input,double ),double param1);
    void setFunction(double (*function)(double input,double ,double ),double param1,double param2);
    void setFunction(double (*function)(double input,double ,double ,double),double param1,double param2,double param3);
    double minRange;
    double maxRange;
    double incrementRange;
    void insertManuallyOutputs(std::vector<double> outputs);
    
    double output(double input);
    double normOutput(double input);
    bool circular;
    
//    void makeOutputs(double param1);
//    void makeOutputs(double param1,double param2);
    
private:
    double param1,param2,param3;
    int numberArguments;
    double (*function1)(  double val);
    double (*function2)(  double val,double val2);
    double (*function3)(  double val,double val2,double val3);
    double (*function4)(  double val,double val2,double val3,double val4);
    std::vector<double> inputs;
    std::vector<double> outputs;
    std::vector<double> strengths;
    void makeOutputs();
};

#endif /* defined(__harmonicCities__Functor__) */

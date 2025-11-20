//
//  City.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 04/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "City.h"
//#include "Eigen/Dense"
//#include "Eigen/Eigenvalues"
//
//using namespace Eigen;

void City::updateIncreasePopulation(std::vector<City> &citiesInRange){
    a=0.0;
    for(long i=0;i<citiesInRange.size();i++){
        double distance=Functions::getDistance(citiesInRange[i].node->location, node->location);
//        double d0=450;
        double R_ij=1.0/(1.0+pow((distance/d0),2.0));
        double v_temp=citiesInRange[i].f*R_ij;
        a=a+v_temp;
        if(!withMemory){
            v=a;
        }
        
        
        
    }
//    v=f;


}

//void City::calculateEigenVectors(std::vector<City> &citiesInRange){
//    MatrixXd R(citiesInRange.size(),citiesInRange.size());
//    
//    for(long i=0;i<citiesInRange.size();i++){
//        double distance=Functions::getDistance(citiesInRange[i].node->location, node->location);
//        double d0=80;
//        double R_ij=1/(1+pow((distance/d0),2));
//        r(i,j)
//        
//        
//        
//        
//        
//    }
//}

double City::calculateTotalPopulation(std::vector<City> &citiesInRange){
    double newTotalPopulation=0.0;
//    double correction=0;
//    double inc_t=.05;
//    bool useAbs=true;
//    bool valid=true;
    for(long i=0;i<citiesInRange.size();i++){
//        if(!useAbs){
//            double pop=exp(citiesInRange[i].u_prev+(citiesInRange[i].v)*inc_t);
//            correction+=pop;
//            //            correction+=(citiesInRange[i].v*exp(citiesInRange[i].u_prev));
//        }else{
//            double pop=exp(Functions::abs(citiesInRange[i].u_prev+citiesInRange[i].v*inc_t));
//            correction+=pop;
//            //            correction+=Functions::abs(citiesInRange[i].v*exp(citiesInRange[i].u_prev));
//        }
        if(!citiesInRange[i].useAbs){
            newTotalPopulation+=exp((citiesInRange[i].calculatePop()));
        }else{
            newTotalPopulation+=exp(Functions::abs(citiesInRange[i].calculatePop()));
        }
    }
    for(long i=0;i<citiesInRange.size();i++){
        citiesInRange[i].newTotalPopulation=newTotalPopulation;
    }
    return newTotalPopulation;
}

double City::calculatePop(){
    double pop;
    if(!withMemory){
       pop=u_prev+v*inc_t;
    }else{
        pop=u + b1*inc_t*(v + a/2.0);
    }
    
    return pop;
}

bool City::updatePopulation(std::vector<City> &citiesInRange){
    

    bool valid=true;

     double norm_correction=log(newTotalPopulation/(initialTotalPopulation));
//    norm_correction=0;
//
    for(long i=0;i<citiesInRange.size();i++){
//        double pop=Functions::abs(citiesInRange[i].u_prev+(citiesInRange[i].v)*inc_t)+log(initialTotalPopulation/newTotalPopulation);
        double pop=citiesInRange[i].calculatePop()-norm_correction;
        if(pop<=0){
            valid=false;
        }
    }

   
    
//    if(newTotalPopulation>initialTotalPopulation){
//        norm_correction=(initialTotalPopulation-newTotalPopulation)*(exp(u_prev+v*inc_t)/newTotalPopulation);
//    }else{
//        norm_correction=(initialTotalPopulation-newTotalPopulation)/(double)(citiesInRange.size());
//    }

    if(valid){
        if(!useAbs){
            
//            u=(u_prev+(v)*inc_t)+log(initialTotalPopulation/newTotalPopulation);
//            u=(u_prev+(v-norm_correction)*inc_t);
                        u=calculatePop()-norm_correction;
        }else{
            u=Functions::abs(calculatePop()-norm_correction);
//            u=Functions::abs(u_prev+(v)*inc_t)+log(initialTotalPopulation/newTotalPopulation);
        }
//        std::cout<<"u "<<u<<'\n';
        x=exp(u);
//        std::cout<<"x "<<x<<'\n';
    }else{
        if(withMemory){
            v = b2*v + b1*a;
        }
    }
//    std::cout<<valid<<'\n';
    
//    x=x+norm_correction;
//
//    u=log(x);
    return valid;

}
void City::updateFinalValues(){
    if(withMemory){
        v = b2*v + b1*a;
    }
        u_prev=u;
        node->mass=x;
    if(x>maxPopulation){
        maxPopulation=x;
    }
//    if(x>200){
        numberTimes+=x/1000.0;
//    }
}

void City::updateRandomValues(){
//    if(f==0){
        f=Functions::rnorm(0.0,1.0);
//    double shape=x;
//    f=-Functions::rgamma(shape,.5)+(shape)/2.0;
//    std::cout<<"u "<<u<<" f "<<f<<'\n';
//        if(f<0){
//            f=-.01;
//        }else{
//            f=.01;
//        }
//    }else{
//        f=-f;
//    }

}
void City::updateRandomValues(double valuePotential){
    f=(f+valuePotential*.3)/1.3;
    
}

void City::decreaseLambda(){
//    lambda=lambda/pow(lambda,.001);
    if(lambda<10){
        lambda=10;
    }
    b1 = 1.0/(1.0+lambda*inc_t/2.0);
    b2 = (1.0-lambda*inc_t/2.0)/(1.0+lambda*inc_t/2.0);
//    std::cout<<lambda<<'\n';
}

void City::init(){
    lambda=10;
    v=0.0;
    numberTimes=0.0;
    x=node->mass;
    maxPopulation=x;
    u=log(x);
    u_prev=u;
     inc_t=.0001;
     useAbs=true;
    f=0.0;
    d0=10;
    b1 = 1.0/(1.0+lambda*inc_t/2.0);
    b2 = (1.0-lambda*inc_t/2.0)/(1.0+lambda*inc_t/2.0);
    withMemory=true;
    
}
void City::init(long id){
    this->id=id;
    lambda=10;
    v=0.0;
    numberTimes=0.0;
    x=node->mass;
    maxPopulation=x;
    u=log(x);
    u_prev=u;
     inc_t=.0001;
     useAbs=true;
    f=0.0;
    d0=10;
    b1 = 1.0/(1.0+lambda*inc_t/2.0);
    b2 = (1.0-lambda*inc_t/2.0)/(1.0+lambda*inc_t/2.0);
    withMemory=true;
    
}
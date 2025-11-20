//
//  VectorNDim.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 08/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "VectorNDim.h"


VectorNDim::VectorNDim(){

}
//VectorNDim::VectorNDim(int dimensions){
//    values.resize(dimensions, 0.0);
//    this->dimensions=dimensions;
//}
VectorNDim::VectorNDim(std::vector<double> values){
    this->values=values;
//    this->dimensions=values.size();
}

//VectorNDim::VectorNDim(double a,...){
//    
//    
//    va_list arguments;
//
//    
//    va_start ( arguments, a );
//    double number=a;
////    std::stringstream first;
//    std::string first;
////    first<<a;
////    const char* numberS;
////    const std::string temp=first.str();
////    numberS=temp.c_str();
//    std::cout<<"before "<<number<<'\n';
//    do {
//        
//        values.push_back(number);
//        number= va_arg ( arguments, double);
//        std::cout<<"number "<<number<<'\n';
////        first.str("");
//        first=std::to_string(number);
//        std::cout<<first<<'\n';
//        
////        if(numberS!=NULL&&strlen(numberS)>0){
////            std::cout<<"numberS "<<numberS<<" "<<'\n';
////            number=std::stod(numberS);
////            std::cout<<"number "<<number<<" "<<'\n';
////        }
//    }while(first.length()>0);
//    
//    std::cout<<"after "<<number<<'\n';
//    va_end ( arguments );
//    this->dimensions=values.size();
// 
//}
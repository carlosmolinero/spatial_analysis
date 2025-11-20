//
//  Functor.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 19/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Functor.h"

Functor::Functor(){
    incrementRange=1.0;
    minRange=-179;
    maxRange=180.0;
    circular=true;
    mode=SUM;
    
    for(long i=0;i<=(maxRange-minRange)/incrementRange;i++){
        inputs.push_back((double)(i)*incrementRange+minRange);
    }

}

Functor::Functor(double minRange, double maxRange, double incrementRange, bool circular, int mode){
    this->incrementRange=incrementRange;
    this->minRange=minRange;
    this->maxRange=maxRange;
    this->circular=circular;
    this->mode=mode;
    
    for(long i=0;i<=(maxRange-minRange)/incrementRange;i++){
        inputs.push_back((double)(i)*incrementRange+minRange);
    }
    
}

void Functor::changeMode(int mode){
    this->mode=mode;
}
void Functor::setFunction(double (*function)(double input)){
    numberArguments=1;
    function1=function;
    makeOutputs();
   
}
void Functor::setFunction(double (*function)(double input,double ),double param1){
    numberArguments=2;
    function2=function;
    this->param1=param1;
    makeOutputs();
    
    
}
void Functor::setFunction(double (*function)(double input,double ,double ),double param1,double param2){
    numberArguments=3;
    function3=function;
    this->param1=param1;
    this->param2=param2;
    makeOutputs();
}
void Functor::setFunction(double (*function)(double input,double ,double,double ),double param1,double param2,double param3){
    numberArguments=4;
    function4=function;
    this->param1=param1;
    this->param2=param2;
    this->param3=param3;
    makeOutputs();
}

void Functor::makeOutputs(){
    if(outputs.size()==0){
        if(numberArguments==1){
            for(long i=0;i<inputs.size();i++){
                outputs.push_back(function1(inputs[i]));
//                strengths.push_back(Functions::angularDecay(inputs[i], 2, 1, param3));
            }
            
        }
        if(numberArguments==2){
                for(long i=0;i<inputs.size();i++){
                    outputs.push_back(function2(inputs[i],param1));
                }
        }
        if(numberArguments==3){
                for(long i=0;i<inputs.size();i++){
                    outputs.push_back(function3(inputs[i],param1,param2));
                }
        }
        if(numberArguments==4){
            if(mode==SUM){
                for(long i=0;i<inputs.size();i++){
                    outputs.push_back(function4(inputs[i],param1,param2,param3));
                   
                    
                }
            }
            if(mode==MIN){
                for(long i=0;i<inputs.size();i++){
                    double strengthTemp=function4(inputs[i], param1, 1/param2, param3);
                    
                    double result=function4(inputs[i], param1, param2, param3)*strengthTemp;
                    outputs.push_back(result);
                    strengths.push_back(strengthTemp);
                }
            }
            if(mode==AVERAGE){
                for(long i=0;i<inputs.size();i++){
                    double strengthTemp=function4(inputs[i], param1, 1, param3);
                    
                    double result=function4(inputs[i], param1, param2, param3)*strengthTemp;
                    outputs.push_back(result);
                    strengths.push_back(strengthTemp);
                }
            }
        }
    }else{
        if(mode==SUM){
            if(numberArguments==1){
                for(long i=0;i<inputs.size();i++){
                    outputs[i]=(outputs[i]+function1(inputs[i]));
                }
            }
            if(numberArguments==2){
                for(long i=0;i<inputs.size();i++){
                    outputs[i]=(outputs[i]+function2(inputs[i],param1));
                }
            }
            if(numberArguments==3){
                for(long i=0;i<inputs.size();i++){
                    outputs[i]=(outputs[i]+function3(inputs[i],param1,param2));
                }
            }
            if(numberArguments==4){
                for(long i=0;i<inputs.size();i++){
                    outputs[i]=outputs[i]+function4(inputs[i],param1,param2,param3);
                }
            }
        }
        if(mode==MIN){
            if(numberArguments==1){
                
            }
            if(numberArguments==2){
             
            }
            if(numberArguments==3){
            
            }
            if(numberArguments==4){
                for(long i=0;i<inputs.size();i++){

                    double strengthTemp=function4(inputs[i], param1, 1/param2, param3);

                    double result=function4(inputs[i], param1, param2, param3)*strengthTemp;
                    outputs[i]+=result;
                    
                }
                 for(long i=0;i<inputs.size();i++){
                     double strengthTemp=function4(inputs[i], param1, 1/param2, param3);

                     strengths[i]+=strengthTemp;
                 }
            }
        }
        if(mode==AVERAGE){
            if(numberArguments==1){
                
            }
            if(numberArguments==2){
                
            }
            if(numberArguments==3){
                
            }
            if(numberArguments==4){
                for(long i=0;i<inputs.size();i++){
                    
                    double strengthTemp=function4(inputs[i], param1, 1, param3);
                    
                    double result=function4(inputs[i], param1, param2, param3)*strengthTemp;
                    outputs[i]+=result;
                    
                }
                for(long i=0;i<inputs.size();i++){
                    double strengthTemp=function4(inputs[i], param1, 1, param3);
                    
                    strengths[i]+=strengthTemp;
                }
            }
        }
    }

}

double Functor::output(double input){

    long inputA=floor(input);
    long inputB=ceil(input);
    
    if (input<-179){
        inputA=180;
        inputB=-179;
        input=Functions::abs(input);
    }
    if(input>=180){
        inputA=180;
        inputB=-179;
    }
    double outputA=0;
    double outputB=0;
    if(mode==SUM){
     outputA=outputs[(inputA-minRange)/incrementRange];
     outputB=outputs[(inputB-minRange)/incrementRange];
    }
    if(mode==MIN||mode==AVERAGE){
        outputA=outputs[(inputA-minRange)/incrementRange]/strengths[(inputA-minRange)/incrementRange];
        outputB=outputs[(inputB-minRange)/incrementRange]/strengths[(inputA-minRange)/incrementRange];
    }
    double distanceA=Functions::abs((input-inputA)/incrementRange);

    double result=(outputB-outputA)*distanceA+outputA;
    
//    std::cout<<"output in functor "<<input<<" "<<result<<" "<<outputA<<" "<<outputB<<'\n';

    return result;
}
double Functor::normOutput(double input){
    double result=output(input);
    VectorNDim minMax=Functions::getMinMax(outputs);
    result=Functions::normalize(result, minMax[0], minMax[1]);
    return result;
}
//void Functor::makeOutputs(double param1){
//    
//    for(long i=0;i<inputs.size();i++){
//        outputs.push_back(function2(inputs[i],param1));
//    }
//    
//}
//void Functor::makeOutputs(double param1,double param2){
//    
//    for(long i=0;i<inputs.size();i++){
//        outputs.push_back(function3(inputs[i],param1,param2));
//    }
//    
//}



void Functor::insertManuallyOutputs(std::vector<double> outputs){
    this->outputs=outputs;
}


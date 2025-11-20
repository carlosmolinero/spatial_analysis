//
//  Functions.cpp
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 23/12/2014.
//  Copyright (c) 2014 Carlos Molinero. All rights reserved.
//

#include "Functions.h"


double Functions::getValueAt(std::unordered_map<long,double>& map,long index,double valueToReturnIfNotExist){
  double value=valueToReturnIfNotExist;
  try
    {
        value=map.at(index);
    }

    catch(std::out_of_range &e)
    {
        // cerr << "Exception at " << e.what() << endl;
    }
    return value;
}

double Functions::median(std::vector<double> values){
    std::vector<double> orderedValues=Functions::orderValues(values,true);
    return(orderedValues[floor(double(orderedValues.size())/2.0)]);
}

VectorNDim Functions::getMinMax(std::vector<double> values){
    double min=INFINITY;
    double max=-INFINITY;
    for(long i=0;i<values.size();i++){
        if(values[i]>max){
            max=values[i];
        }
        if(values[i]<min){
            min=values[i];
        }
    }
    VectorNDim minMax;
    minMax.values.clear();
    minMax.values.push_back(min);
    minMax.values.push_back(max);
//    hsv.values.push_back(255);
//    minMax.values={min,max};
//    std::cout<<"minmax "<<minMax[0]<<" "<<minMax[1]<<'\n';
    return minMax;
}
double Functions::decay(double input,double input0){
    return (1/(1+(input/input0)*(input/input0)));
}
double Functions::decay(double input,double input0,double amplitude){
    return (amplitude/(1+(input/input0)*(input/input0)));
}
double Functions::decay(double input,double input0,double amplitude,double center){

    return (amplitude/(1+((input-center)/input0)*((input-center)/input0)));
}

double Functions::angularDecay(double input,double input0,double amplitude,double center){
    double value=input-center;
    while(value<=-180){
        value+=360;
    }
    while(value>180){
        value-=360;
    }
    return (amplitude/(1+((value)/input0)*((value)/input0)));
}
//This returns angle between 0 and 180
double Functions::getAngularDistance(Point2d initPoint,Point2d intermediatePoint,Point2d finalPoint){
    double x1=intermediatePoint.x-initPoint.x;
    double x2=finalPoint.x-intermediatePoint.x;
    double y1=intermediatePoint.y-initPoint.y;
    double y2=finalPoint.y-intermediatePoint.y;
    double dot = x1*x2 + y1*y2;
    double lenSq1 = x1*x1 + y1*y1;
    double lenSq2 = x2*x2 + y2*y2;

//    dot = x1*x2 + y1*y2 + z1*z2
//    lenSq1 = x1*x1 + y1*y1 + z1*z1
//    lenSq2 = x2*x2 + y2*y2 + z2*z2
    double value=dot/sqrt(lenSq1 * lenSq2);
    if(value>1&&round(value)==1){
        value=1;
    }
    double angle = acos(value);
    if(angle<0.0){
        angle=angle+M_PI*2.0;
    }
    angle=angle*180.0/M_PI;
    return angle;

}
//This returns angle between -180 and 180
double Functions::getAngle(Point2d initPoint,Point2d finalPoint){
    return(atan2(finalPoint.y-initPoint.y,finalPoint.x-initPoint.x)*180.0/M_PI);
}
double Functions::getAngleRadians(Point2d initPoint,Point2d finalPoint){
    return(atan2(finalPoint.y-initPoint.y,finalPoint.x-initPoint.x));
}
//This returns angle between -180 and 180
double Functions::getAngle(Point2d initPoint,Point2d intermediatePoint,Point2d finalPoint){
    double angleB=atan2(finalPoint.y-intermediatePoint.y,finalPoint.x-intermediatePoint.x);
    double angleA=atan2(intermediatePoint.y-initPoint.y,intermediatePoint.x-initPoint.x);
    double rel_angle = angleB-angleA;
    // Normalize to -PI .. +PI

//    rel_angle -= floor((rel_angle + M_PI)/(2*M_PI)) * (2*M_PI) - M_PI;
    rel_angle=rel_angle*180.0/M_PI;
    if((rel_angle)>180.0){
        rel_angle-=360.0;
    }else if(rel_angle<-180.0){
        rel_angle+=360.0;
    }
    return(rel_angle);
}
double Functions::getAngleRadians(Point2d initPoint,Point2d intermediatePoint,Point2d finalPoint){
    double angleB=atan2(finalPoint.y-intermediatePoint.y,finalPoint.x-intermediatePoint.x);
    double angleA=atan2(intermediatePoint.y-initPoint.y,intermediatePoint.x-initPoint.x);
    double rel_angle = angleB-angleA;
    // Normalize to -PI .. +PI

    //    rel_angle -= floor((rel_angle + M_PI)/(2*M_PI)) * (2*M_PI) - M_PI;
//    rel_angle=rel_angle;
    if((rel_angle)>M_PI){
        rel_angle-=2.0*M_PI;
    }else if(rel_angle<-M_PI){
        rel_angle+=2.0*M_PI;
    }
    return(rel_angle);
}
double Functions::normalize(double value, double min, double max){
    if(max!=min){
       return (value-min)/(max-min);
    }else{
        return 1;
    }

}

std::vector<double> Functions::normalize(std::vector<double> values){
    VectorNDim minMax=getMinMax(values);
    std::vector<double> normValues;
    normValues.reserve(values.size());
    for(long i=0;i<values.size();i++){
        double value=normalize(values[i], minMax[0], minMax[1]);
        normValues.push_back(value);
    }
    return normValues;
}
double Functions::normalize(double value, double max){
    return value/max;
}
double Functions::logNormalDist(double value,double m, double mu,double sigma,double divisor,double multiplier){
    value=value/divisor;
    return ((exp(-(((log(value-mu)/m))*((log(value-mu)/m))/(2*sigma*sigma))))/((value-mu)*sigma*sqrt(2*M_PI)))*multiplier;
}
double Functions::getDistance(Point2d initPoint,Point2d finalPoint){
    double x=finalPoint.x-initPoint.x;
    double y=finalPoint.y-initPoint.y;
    double xx=x*x;
    double yy=y*y;
    return (sqrt(xx+yy));

}
double Functions::getSquaredDistance(Point2d initPoint,Point2d finalPoint){
    double x=finalPoint.x-initPoint.x;
    double y=finalPoint.y-initPoint.y;
    double xx=x*x;
    double yy=y*y;
    return (xx+yy);

}
double Functions::getManhattanDistance(std::vector<double> initPoint,std::vector<double> finalPoint){
    double result=0;
    for(long i=0;i<initPoint.size();i++){
        double first=initPoint[i];
        double second=finalPoint[i];
        double resultTemp=first-second;
        if(resultTemp<0){
            result-=resultTemp;
        }else{
            result+=(resultTemp);
        }
    }
    return result;
}


std::unordered_map<long,double> Functions::sum(std::unordered_map<long,double> a,std::unordered_map<long,double>  b){
    std::unordered_map<long,int> alreadyChecked;
    std::unordered_map<long,double> result;
//    if(finalPoint.size()>0){
//        double data=1;
//    }
    for(auto i=a.begin();i!=a.end();++i){
        double first=a[i->first];
        double second=b[i->first];
        double resultTemp=first+second;
//        if(resultTemp<0){
//            result-=resultTemp;
//        }else{
            result[i->first]+=(resultTemp);
//        }
        alreadyChecked[i->first]=1;
    }
    for(auto i=b.begin();i!=b.end();++i){
        if(alreadyChecked[i->first]!=1){
//        std::cout<<"i->first "<<i->first<<'\n';
//        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
//        std::cout<<"i->second "<<i->second<<'\n';
//            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';

            double first=a[i->first];
            double second=b[i->first];
            double resultTemp=first+second;
//            if(resultTemp<0){
//                result-=resultTemp;
//            }else{
                 result[i->first]+=(resultTemp);
//            }


//        alreadyChecked[i->first]=1;
        }
    }
    return result;
}
std::unordered_map<long,double> Functions::div(std::unordered_map<long,double> numerator,double denominator){
    std::unordered_map<long,int> alreadyChecked;
    std::unordered_map<long,double> result;
    //    if(finalPoint.size()>0){
    //        double data=1;
    //    }
    for(auto i=numerator.begin();i!=numerator.end();++i){
        double first=numerator[i->first];
        double second=denominator;
        double resultTemp=first/second;
        //        if(resultTemp<0){
        //            result-=resultTemp;
        //        }else{
        result[i->first]=(resultTemp);
        //        }
        alreadyChecked[i->first]=1;
    }
//    for(auto i=b.begin();i!=b.end();++i){
//        if(alreadyChecked[i->first]!=1){
//            //        std::cout<<"i->first "<<i->first<<'\n';
//            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
//            //        std::cout<<"i->second "<<i->second<<'\n';
//            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';
//
//            double first=a[i->first];
//            double second=b[i->first];
//            double resultTemp=first+second;
//            //            if(resultTemp<0){
//            //                result-=resultTemp;
//            //            }else{
//            result[i->first]+=(resultTemp);
//            //            }
//
//
//            //        alreadyChecked[i->first]=1;
//        }
//    }
    return result;
}

std::unordered_map<long,double> Functions::norm(std::unordered_map<long,double> vector){
    std::unordered_map<long,int> alreadyChecked;
    std::unordered_map<long,double> result;
    //    if(finalPoint.size()>0){
    //        double data=1;
    //    }
    double second=0;
    for(auto i=vector.begin();i!=vector.end();++i){
        second+=vector[i->first];
    }
    for(auto i=vector.begin();i!=vector.end();++i){
        double first=vector[i->first];
//        double second=denominator;
        double resultTemp=first/second;
        //        if(resultTemp<0){
        //            result-=resultTemp;
        //        }else{
        result[i->first]=(resultTemp);
        //        }
        alreadyChecked[i->first]=1;
    }
    //    for(auto i=b.begin();i!=b.end();++i){
    //        if(alreadyChecked[i->first]!=1){
    //            //        std::cout<<"i->first "<<i->first<<'\n';
    //            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
    //            //        std::cout<<"i->second "<<i->second<<'\n';
    //            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';
    //
    //            double first=a[i->first];
    //            double second=b[i->first];
    //            double resultTemp=first+second;
    //            //            if(resultTemp<0){
    //            //                result-=resultTemp;
    //            //            }else{
    //            result[i->first]+=(resultTemp);
    //            //            }
    //
    //
    //            //        alreadyChecked[i->first]=1;
    //        }
    //    }
    return result;
}



//std::unordered_map<long,double> Functions::fullNorm(std::unordered_map<long,double> vector){
//    std::unordered_map<long,int> alreadyChecked;
//    std::unordered_map<long,double> result;
//    //    if(finalPoint.size()>0){
//    //        double data=1;
//    //    }
//    double second=0;
//    for(auto i=vector.begin();i!=vector.end();++i){
//        second+=vector[i->first];
//    }
//    for(auto i=vector.begin();i!=vector.end();++i){
//        double first=vector[i->first];
//        //        double second=denominator;
//        double resultTemp=first/second;
//        //        if(resultTemp<0){
//        //            result-=resultTemp;
//        //        }else{
//        result[i->first]=(resultTemp);
//        //        }
//        alreadyChecked[i->first]=1;
//    }
//    //    for(auto i=b.begin();i!=b.end();++i){
//    //        if(alreadyChecked[i->first]!=1){
//    //            //        std::cout<<"i->first "<<i->first<<'\n';
//    //            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
//    //            //        std::cout<<"i->second "<<i->second<<'\n';
//    //            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';
//    //
//    //            double first=a[i->first];
//    //            double second=b[i->first];
//    //            double resultTemp=first+second;
//    //            //            if(resultTemp<0){
//    //            //                result-=resultTemp;
//    //            //            }else{
//    //            result[i->first]+=(resultTemp);
//    //            //            }
//    //
//    //
//    //            //        alreadyChecked[i->first]=1;
//    //        }
//    //    }
//    return result;
//}


double Functions::getManhattanDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint){
    std::unordered_map<long,int> alreadyChecked;
    double result=0;
    //    if(finalPoint.size()>0){
    //        double data=1;
    //    }
    for(auto i=initPoint.begin();i!=initPoint.end();++i){
        double first=initPoint[i->first];
        double second=finalPoint[i->first];
        double resultTemp=first-second;
        if(resultTemp<0){
            result-=resultTemp;
        }else{
            result+=(resultTemp);
        }
        alreadyChecked[i->first]=1;
    }
    for(auto i=finalPoint.begin();i!=finalPoint.end();++i){
        if(alreadyChecked[i->first]!=1){
            //        std::cout<<"i->first "<<i->first<<'\n';
            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
            //        std::cout<<"i->second "<<i->second<<'\n';
            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';

            double first=initPoint[i->first];
            double second=finalPoint[i->first];
            double resultTemp=first-second;
            if(resultTemp<0){
                result-=resultTemp;
            }else{
                result+=(resultTemp);
            }


            //        alreadyChecked[i->first]=1;
        }
    }
    return result;
}
double Functions::getChiSquaredDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint){
    std::unordered_map<long,int> alreadyChecked;
    double result=0.0;
    //    if(finalPoint.size()>0){
    //        double data=1;
    //    }
    for(auto i=initPoint.begin();i!=initPoint.end();++i){
        double first=initPoint[i->first];
        double second=finalPoint[i->first];
        double resultTemp=(first-second)*(first-second);
        double resultTempb=first+second;
        resultTemp=(resultTemp/resultTempb);
        if(resultTemp<0){
            result-=resultTemp;
        }else{
            result+=(resultTemp);
        }
        alreadyChecked[i->first]=1;
    }
    for(auto i=finalPoint.begin();i!=finalPoint.end();++i){
        if(alreadyChecked[i->first]!=1){
            //        std::cout<<"i->first "<<i->first<<'\n';
            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
            //        std::cout<<"i->second "<<i->second<<'\n';
            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';

            double first=initPoint[i->first];
            double second=finalPoint[i->first];
            double resultTemp=(first-second)*(first-second);
            double resultTempb=first+second;
            resultTemp=(resultTemp/resultTempb);
            if(resultTemp<0){
                result-=resultTemp;
            }else{
                result+=(resultTemp);
            }


            //        alreadyChecked[i->first]=1;
        }
    }
    return result/2.0;
}


double Functions::getCanberraDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint){
    std::unordered_map<long,int> alreadyChecked;
    double result=0;
    //    if(finalPoint.size()>0){
    //        double data=1;
    //    }
    for(auto i=initPoint.begin();i!=initPoint.end();++i){
        double first=initPoint[i->first];
        double second=finalPoint[i->first];
        double resultTemp=Functions::abs(first-second);
        double resultTempb=Functions::abs(first)+Functions::abs(second);
        resultTemp=(resultTemp/resultTempb);
        if(resultTemp<0){
            result-=resultTemp;
        }else{
            result+=(resultTemp);
        }
        alreadyChecked[i->first]=1;
    }
    for(auto i=finalPoint.begin();i!=finalPoint.end();++i){
        if(alreadyChecked[i->first]!=1){
            //        std::cout<<"i->first "<<i->first<<'\n';
            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
            //        std::cout<<"i->second "<<i->second<<'\n';
            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';

            double first=initPoint[i->first];
            double second=finalPoint[i->first];
            double resultTemp=Functions::abs(first-second);
            double resultTempb=Functions::abs(first)+Functions::abs(second);
            resultTemp=(resultTemp/resultTempb);
            if(resultTemp<0){
                result-=resultTemp;
            }else{
                result+=(resultTemp);
            }


            //        alreadyChecked[i->first]=1;
        }
    }
    return result;
}

bool Functions::containedInInterval(double value,double min,double max){
    if(value>min&&value<max){
        return true;
    }else{
        return false;
    }
}
bool Functions:: containedInArea(Point2d point,Point2d corner1,Point2d corner2){
    if(containedInInterval(point.x, corner1.x, corner2.x)&&containedInInterval(point.y, corner1.y, corner2.y)){
        return true;
    }else{
        return false;
    }
}

bool Functions::rectangleContainedInRectangle(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B){
    if(containedInInterval(corner1A.x, corner1B.x, corner2B.x)&&containedInInterval(corner2A.x, corner1B.x, corner2B.x)&&containedInInterval(corner1A.y, corner1B.y, corner2B.y)&&containedInInterval(corner2A.y, corner1B.y, corner2B.y)){
        return true;
    }else{
        return false;
    }
//    return false;

}

bool Functions::overlappingCornersOfRectangles(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B){
    Point2d corner3A=Point2d(corner1A.x,corner2A.y);
    Point2d corner4A=Point2d(corner2A.x,corner1A.y);
    if (containedInArea(corner1A, corner1B, corner2B)||containedInArea(corner2A, corner1B, corner2B)||containedInArea(corner3A, corner1B, corner2B)||containedInArea(corner4A, corner1B, corner2B)){
        return true;
    }else{
        return false;
    }
//    return false;
}
bool Functions::overlappingSidesOfRectangles(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B){
//    Point2d corner3A=Point2d(corner1A.x,corner2A.y);
//    Point2d corner4A=Point2d(corner2A.x,corner1A.y);
//     if(containedInInterval(corner1A.x, corner1B.x, corner2B.x)&&containedInInterval(corner2A.x, corner1B.x, corner2B.x)&&((!containedInInterval(corner1A.y, corner1B.y, corner2B.y)&&containedInInterval(corner2A.y, corner1B.y, corner2B.y))||(containedInInterval(corner1A.y, corner1B.y, corner2B.y)&&!containedInInterval(corner2A.y, corner1B.y, corner2B.y)))){
//        return true;
//    }else if(containedInInterval(corner1A.y, corner1B.y, corner2B.y)&&containedInInterval(corner2A.y, corner1B.y, corner2B.y)&&((!containedInInterval(corner1A.x, corner1B.x, corner2B.x)&&containedInInterval(corner2A.x, corner1B.x, corner2B.x))||(containedInInterval(corner1A.x, corner1B.x, corner2B.x)&&!containedInInterval(corner2A.x, corner1B.x, corner2B.x)))){
//        return true;
//    }else{
//        return false;
//    }

    Point2d corner3A=Point2d(corner1A.x,corner2A.y);
    Point2d corner4A=Point2d(corner2A.x,corner1A.y);

    int numberCornersContained=0;
    if(containedInArea(corner1A, corner1B, corner2B)){
        numberCornersContained++;
    }
    if(containedInArea(corner2A, corner1B, corner2B)){
        numberCornersContained++;
    }
    if(containedInArea(corner3A, corner1B, corner2B)){
        numberCornersContained++;
    }
    if(containedInArea(corner4A, corner1B, corner2B)){
        numberCornersContained++;
    }
    if(numberCornersContained>0){
        return true;
    }else{
        return false;
    }
}
bool Functions::containedOrOverlappingRectangles(Point2d corner1A,Point2d corner2A,Point2d corner1B,Point2d corner2B){
    if(rectangleContainedInRectangle(corner1A, corner2A, corner1B, corner2B)||rectangleContainedInRectangle(corner1B, corner2B,corner1A, corner2A)||overlappingCornersOfRectangles(corner1A, corner2A, corner1B, corner2B)||overlappingSidesOfRectangles(corner1A, corner2A, corner1B, corner2B)||overlappingSidesOfRectangles(corner1B, corner2B,corner1A, corner2A)){
        return true;
    }else{
        return false;
    }

//        if(rectangleContainedInRectangle(corner1B, corner2B,corner1A, corner2A)){
//            return true;
//        }else{
//            return false;
//        }

//    return false;
}

double Functions::abs(double number){
    if (number<0){
        return -number;
    }else{
        return number;
    }
}

//void Functions::setRandomSeed(bool normal){
//    if(normal){
//
//
//    }
//}
double Functions::random(double min, double max,bool normal)
{
    double random;

    if(!normal){
        random=((double(rand()) / double(RAND_MAX)) * (max - min)) + min;
    }else{
//        double x=((double(rand()) / double(RAND_MAX))*2-1)*4;
//        random=gaussianFunction(x,(max-min),0,1)+min;
//        random=x;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()+rand()%100000;
                std::default_random_engine generator (seed);
//        std::default_random_engine generator;
        std::normal_distribution<double> distribution (0.0,1.0);

        random=distribution(generator)/8.0*(max-min)+(max+min)/2.0;
    }
    return random;
}

double Functions::rnorm(double average, double deviation){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()+rand()%100000;
    std::default_random_engine generator (seed);
    //        std::default_random_engine generator;
    std::normal_distribution<double> distribution (average,deviation);

    double random=distribution(generator);
    return random;
}
double Functions::rgamma(double shape, double rate){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()+rand()%100000;
    std::default_random_engine generator (seed);
    //        std::default_random_engine generator;
    std::gamma_distribution<double> distribution (shape,rate);

    double random=distribution(generator);
    return random;
}

double Functions::runiform(double min, double max){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()+rand()%100000;
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution (min,max);

    double random=distribution(generator);
    return random;
}
double Functions::gaussianFunction(double x,double amplitude, double offset, double width){
    double a=amplitude;
    double b=offset;
    double c=width;
    double value=a*exp(-((x-b)*(x-b))/(2*c*c));
    return value;
}

double Functions::getEuclideanDistance(std::unordered_map<long,double> initPoint,std::unordered_map<long,double>  finalPoint){
    std::unordered_map<long,int> alreadyChecked;
    double result=0;
    //    if(finalPoint.size()>0){
    //        double data=1;
    //    }
    for(auto i=initPoint.begin();i!=initPoint.end();++i){
        double first=initPoint[i->first];
        double second=finalPoint[i->first];
        double resultTemp=first-second;
//        if(resultTemp<0){
//            result-=resultTemp;
//        }else{
            result+=(resultTemp)*resultTemp;
//        }
        alreadyChecked[i->first]=1;
    }
    for(auto i=finalPoint.begin();i!=finalPoint.end();++i){
        if(alreadyChecked[i->first]!=1){
            //        std::cout<<"i->first "<<i->first<<'\n';
            //        std::cout<<"finalPoint[i->first] "<<finalPoint[i->first]<<'\n';
            //        std::cout<<"i->second "<<i->second<<'\n';
            //            std::cout<<"initPoint[i->first] "<<initPoint[i->first]<<'\n';

            double first=initPoint[i->first];
            double second=finalPoint[i->first];
            double resultTemp=first-second;
//            if(resultTemp<0){
//                result-=resultTemp;
//            }else{
                result+=(resultTemp)*resultTemp;
//            }


            //        alreadyChecked[i->first]=1;
        }
    }
    result=sqrt(result);
    return result;
}



double Functions::gammaDistribution(double x, double beta,double amplitude, double width){
    return (amplitude*((beta*beta)*x/width*exp(-beta*x/width)));
}






int Functions::sign(double x) {
    return (x>0) - (x<0);
}

double Functions::max(double a,double b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
long Functions::max(long a,long b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
double Functions::mean(double a,double b){
    return (a+b)/2.0;
}
double Functions::min(double a,double b){
    if(a<=b){
        return a;
    }else{
        return b;
    }
}
long Functions::min(long a,long b){
    if(a<=b){
        return a;
    }else{
        return b;
    }
}
double Functions::min(std::vector<double> values){
    std::vector<double> orderedValues=Functions::orderValues(values,true);
    return(orderedValues[0]);
}
double Functions::max(std::vector<double> values){
    std::vector<double> orderedValues=Functions::orderValues(values,false);
    return(orderedValues[0]);
}
double Functions::mean(std::vector<double>& values){
    double mean=0;
    for(long i=0;i<values.size();i++){
        mean+=values[i];
    }
    mean/=(double)(values.size());
    return(mean);
}
double Functions::interpolate2d(Point2d origin, Point2d destination,double xPoint){
    double xFromOrigin=xPoint-origin.x;
    double span=destination.x-origin.x;
    double variationValues=destination.y-origin.y;
    return origin.y+variationValues/span*xFromOrigin;
}


double Functions::getDistanceBetweenAngles(double angle1,double angle2){
    if(Functions::sign(angle1*angle2)==1||Functions::sign(angle1*angle2)==0){
        return Functions::abs(angle1-angle2);

    }else{

        double distanceTo0A=Functions::abs(angle1);
        double distanceTo0B=Functions::abs(angle2);

        return std::min(Functions::abs(distanceTo0A+distanceTo0B),Functions::abs((180-distanceTo0A)+(180-distanceTo0B)));

    }

}





//  Public-domain function by Darel Rex Finley, 2006. modified by Carlos Molinero

double Functions::area(std::vector<Point2d> points) {

    double  area=0.0;
    long j=points.size()-1;

    for (long i=0; i<points.size(); i++) {
        area+=(points[j].x+points[i].x)*(points[j].y-points[i].y);
        j=i;
    }

    return Functions::abs(area*.5);
}
















//VectorNDim getMinMax(std::vector<double> values){
//    double min=INFINITY;
//    double max=-INFINITY;
//    for(long i=0;i<values.size();i++){
//        if(values[i]>max){
//            max=values[i];
//        }
//        if(values[i]<min){
//            min=values[i];
//        }
//    }
//    return VectorNDim({min,max});
//}
//VectorNDim getMinMax(VectorXd values){
//    double min=INFINITY;
//    double max=-INFINITY;
//    for(long i=0;i<values.size();i++){
//        if(values(i)>max){
//            max=values(i);
//        }
//        if(values(i)<min){
//            min=values(i);
//        }
//    }
//    return VectorNDim({min,max});
//}
//VectorNDim getMinMax(MatrixXd values){
//    double min=INFINITY;
//    double max=-INFINITY;
//    for(long i=0;i<values.size();i++){
//        if(values(i)>max){
//            max=values(i);
//        }
//        if(values(i)<min){
//            min=values(i);
//        }
//    }
//    return VectorNDim({min,max});
//}
//VectorNDim getMinMax(MatrixXcd values){
//    double min=INFINITY;
//    double max=-INFINITY;
//    for(long i=0;i<values.size();i++){
//        if(values(i).real()>max){
//            max=values(i).real();
//        }
//        if(values(i).real()<min){
//            min=values(i).real();
//        }
//    }
//    return VectorNDim({min,max});
//}

std::vector<double> Functions::orderValues(std::vector<double>& values,bool minToMax){
    std::vector<double> orderedValues;
    std::vector<Number> numbers;
    orderedValues.reserve(values.size());
    numbers.reserve(values.size());

    for(long i=0;i<values.size();i++){
        Number number;
        number.value=values[i];
        number.id=i;
        numbers.push_back(number);
    }

    Heap<Number*> heap(Heap<Number*>::MIN,&Number::compare,&Number::getValue,&Number::setIndexInHeap, &Number::getIndexInHeap,true);
    if(!minToMax){
        heap.mode=Heap<Number*>::MAX;
    }
    for(long i=0;i<numbers.size();i++){
        Number* number=&numbers[i];
        heap.push(number);
    }

    while(heap.size()>0){
        Number* number=heap.pop();
        orderedValues.push_back(number->value);

    }
    return orderedValues;
}
std::vector<long> Functions::orderValues(std::vector<long>& values,bool minToMax){
    std::vector<long> orderedValues;
    std::vector<Number> numbers;
    orderedValues.reserve(values.size());
    numbers.reserve(values.size());

    for(long i=0;i<values.size();i++){
        Number number;
        number.value=values[i];
        number.id=i;
        numbers.push_back(number);
    }


    Heap<Number*> heap(Heap<Number*>::MIN,&Number::compare,&Number::getValue,&Number::setIndexInHeap, &Number::getIndexInHeap,true);
    if(!minToMax){
        heap.mode=Heap<Number*>::MAX;
    }
    for(long i=0;i<numbers.size();i++){
        Number* number=&numbers[i];
        heap.push(number);
    }

    while(heap.size()>0){
        Number* number=heap.pop();
        orderedValues.push_back(number->value);

    }
    return orderedValues;
}

//void Functions::orderValues(std::vector<double>* values,bool minToMax){
//    std::vector<double> orderedValues;
//    std::vector<Number> numbers;
//
//    for(long i=0;i<values->size();i++){
//        Number number;
//        number.value=values->operator[](i);
//        number.id=i;
//        numbers.push_back(number);
//    }
//
//    Heap<Number*> heap(Heap<Number*>::MIN,&Number::compare,&Number::getValue,&Number::setIndexInHeap, &Number::getIndexInHeap,true);
//    if(!minToMax){
//        heap.mode=Heap<Number*>::MAX;
//    }
//    for(long i=0;i<numbers.size();i++){
//        Number* number=&numbers[i];
//        heap.push(number);
//    }
//    values->clear();
//    while(heap.size()>0){
//        Number* number=heap.pop();
//        values->push_back(number->value);
//
//    }//    return orderedValues;
//}

std::vector<long> Functions::getIndexesOfOrderedValues(std::vector<double> &values,bool minToMax){
    std::vector<long> orderedValues;
    std::vector<Number> numbers;

    for(long i=0;i<values.size();i++){
        Number number;
        number.value=values[i];
        number.id=i;
        numbers.push_back(number);
    }
//     std::cout<<"Values"<<'\n';
//    for(long i=0;i<values.size();i++){
//        std::cout<<values[i]<<" ";
//    }
//    std::cout<<'\n';

    Heap<Number*> heap(Heap<Number*>::MIN,&Number::compare,&Number::getValue,&Number::setIndexInHeap, &Number::getIndexInHeap,true);
    if(!minToMax){
        heap.mode=Heap<Number*>::MAX;
    }
    for(long i=0;i<numbers.size();i++){
        Number* number=&numbers[i];
        heap.push(number);
    }
//    std::cout<<"Order"<<'\n';
    while(heap.size()>0){
        Number* number=heap.pop();
//        std::cout<<number->id<<" ";
        orderedValues.push_back(number->id);

    }
//        std::cout<<'\n';
    return orderedValues;
}

std::vector<long> Functions::getIndexesOfOrderedValues(std::vector<long> &values,bool minToMax){
    std::vector<long> orderedValues;
    std::vector<Number> numbers;

    for(long i=0;i<values.size();i++){
        Number number;
        number.value=values[i];
        number.id=i;
        numbers.push_back(number);
    }
    //     std::cout<<"Values"<<'\n';
    //    for(long i=0;i<values.size();i++){
    //        std::cout<<values[i]<<" ";
    //    }
    //    std::cout<<'\n';

    Heap<Number*> heap(Heap<Number*>::MIN,&Number::compare,&Number::getValue,&Number::setIndexInHeap, &Number::getIndexInHeap,true);
    if(!minToMax){
        heap.mode=Heap<Number*>::MAX;
    }
    for(long i=0;i<numbers.size();i++){
        Number* number=&numbers[i];
        heap.push(number);
    }
    //    std::cout<<"Order"<<'\n';
    while(heap.size()>0){
        Number* number=heap.pop();
        //        std::cout<<number->id<<" ";
        orderedValues.push_back(number->id);

    }
    //        std::cout<<'\n';
    return orderedValues;
}










std::vector<double> Functions::uniqueFromAlreadyOrderedVector(std::vector<double> valuesOrderedFromMinToMax){
    std::vector<double>  result;
//    std::vector<double> ordered=orderValues(values, true);
    if(valuesOrderedFromMinToMax.size()>0){
        double previous=valuesOrderedFromMinToMax[0];
        result.push_back(valuesOrderedFromMinToMax[0]);
        for(long i=0;i<valuesOrderedFromMinToMax.size();i++){
            if(valuesOrderedFromMinToMax[i]!=previous){
                result.push_back(valuesOrderedFromMinToMax[i]);
                previous=valuesOrderedFromMinToMax[i];
            }
        }
    }
    return result;
}

std::vector<long> Functions::getIndexesOfUniqueValuesFromAlreadyOrderedVector(std::vector<double> valuesOrderedFromMinToMax){
    std::vector<long>  result;
    //    std::vector<double> ordered=orderValues(values, true);
    if(valuesOrderedFromMinToMax.size()>0){
        double previous=valuesOrderedFromMinToMax[0];
        result.push_back(valuesOrderedFromMinToMax[0]);
        for(long i=0;i<valuesOrderedFromMinToMax.size();i++){
            if(valuesOrderedFromMinToMax[i]!=previous){
                result.push_back(i);
                previous=valuesOrderedFromMinToMax[i];
            }
        }
    }
    return result;
}

std::vector<long> Functions::getIndexesOfUniqueValues(std::vector<double> values){
    std::vector<long>  result;
    //    std::vector<double> ordered=orderValues(values, true);
    if(values.size()>0){
        std::vector<long> indexOrderedValues=getIndexesOfOrderedValues(values, true);
        double previous=values[indexOrderedValues[0]];
        result.push_back(indexOrderedValues[0]);
        for(long i=0;i<indexOrderedValues.size();i++){
            if(values[indexOrderedValues[i]]!=previous){
                result.push_back(indexOrderedValues[i]);
                previous=values[indexOrderedValues[i]];
            }
        }
    }
    return result;

}
std::vector<long> Functions::getIndexesOfUniqueValues(std::vector<long> values){
    std::vector<long>  result;
    //    std::vector<double> ordered=orderValues(values, true);
    if(values.size()>0){
        std::vector<long> indexOrderedValues=getIndexesOfOrderedValues(values, true);
        long previous=values[indexOrderedValues[0]];
        result.push_back(indexOrderedValues[0]);
        for(long i=0;i<indexOrderedValues.size();i++){
            if(values[indexOrderedValues[i]]!=previous){
                result.push_back(indexOrderedValues[i]);
                previous=values[indexOrderedValues[i]];
            }
        }
    }
    return result;

}

std::vector<double> Functions::unique(std::vector<double> values){
    std::vector<double>  result;
    std::vector<double> ordered=orderValues(values, true);
    if(ordered.size()>0){
        double previous=ordered[0];
        result.push_back(ordered[0]);
        for(long i=0;i<ordered.size();i++){
            if(ordered[i]!=previous){
                result.push_back(ordered[i]);
                previous=ordered[i];
            }
        }
    }
    return result;
}
 std::vector<long> Functions::unique(std::vector<long> values){
     std::vector<long> result;
     std::vector<long> ordered=orderValues(values, true);
     if(ordered.size()>0){
         double previous=ordered[0];
         result.push_back(ordered[0]);
         for(long i=0;i<ordered.size();i++){
             if(ordered[i]!=previous){
                 result.push_back(ordered[i]);
                 previous=ordered[i];
             }
         }
     }
     return result;
}


std::vector<double> Functions::derivative(std::vector<double> values){
    std::vector<double> derivative;
    for(long i=0;i<values.size()-1;i++){
        derivative.push_back(values[i+1]-values[i]);
    }
    return derivative;
}

std::vector<double> Functions::derivative(std::vector<double> values,std::vector<double> separations){
    std::vector<double> derivative;
//    std::vector<double> derivativeSeparations;
    for(long i=0;i<values.size()-1;i++){
        double value=(values[i+1]-values[i]);
        double sep=(separations[i+1]-separations[i]);
        derivative.push_back(value/sep);
    }
    return derivative;
}

std::vector<double> Functions::orderVectorUsingAnotherVectorWithPositions(std::vector<double> values,std::vector<long> positions){
    std::vector<double> newVector;
    for(long i=0;i<positions.size();i++){
        newVector.push_back(values[positions[i]]);
    }
    return newVector;
}

std::vector<long> Functions::orderVectorUsingAnotherVectorWithPositions(std::vector<long> values,std::vector<long> positions){
    std::vector<long> newVector;
    for(long i=0;i<positions.size();i++){
        newVector.push_back(values[positions[i]]);
    }
    return newVector;
}

long Functions::findLastPositionValue(std::vector<double> orderedValuesFromMinToMax,double value){
//    std::cout<<"looking for value "<<value<<'\n';

//    long indexMin=0;
//    long indexMax=orderedValuesFromMinToMax.size()-1;
//
//    long index=round((indexMax+indexMin)/2);
//
////    double min=orderedValuesFromMinToMax[indexMin];
////    if(value==min){
////        return indexMin;
////    }
//
//    double max=orderedValuesFromMinToMax[indexMax];
//    if(value==max){
//        if(orderedValuesFromMinToMax[indexMax-1]<value){
//            return max;
//        }
//    }
//    double possibleValue=orderedValuesFromMinToMax[index];
//    while(true){
////        std::cout<<"index of possible position "<<index<<" value "<<possibleValue<<'\n';
//        if(value>possibleValue){
//            if(indexMax-index>1){
//                indexMin=index;
//                index=round((indexMax+indexMin)/2);
//            }else{
//                return index;
//            }
//            possibleValue=orderedValuesFromMinToMax[index];
//        }else if(value<possibleValue){
//            if(index-indexMin>1){
//                indexMax=index;
//                index=round((indexMax+indexMin)/2);
//            }else{
//                return indexMin;
//            }
//            possibleValue=orderedValuesFromMinToMax[index];
//        }else{
//            if(indexMax-index>1&&orderedValuesFromMinToMax[index+1]==value){
//                indexMin=index;
//                index=round((indexMax+indexMin)/2);
//            }else{
//                return index;
//            }
//        }
//    }
    long index=0;
    for(long i=0;i<orderedValuesFromMinToMax.size();i++){
        if(orderedValuesFromMinToMax[i]<=value){
            index=i;
        }
    }

    return index;
}


long Functions::getLocationMaximum(std::vector<double> values){
    long index=0;
    double max=-INFINITY;
    for(long i=0;i<values.size();i++){
        if (max<values[i]){
            max=values[i];
            index=i;
        }
    }
    return index;
}
long Functions::getLocationMinimum(std::vector<double> values){
    long index=0;
    double min=INFINITY;
    for(long i=0;i<values.size();i++){
        if (min>values[i]){
            min=values[i];
            index=i;
        }
    }
    return index;
}
// double Functions::max(std::vector<double> values){
//     long index=0;
//     double max=-INFINITY;
//     for(long i=0;i<values.size();i++){
//         if (max<values[i]){
//             max=values[i];
//             index=i;
//         }
//     }
//     return max;
// }
// double Functions::min(std::vector<double> values){
//     long index=0;
//     double min=INFINITY;
//     for(long i=0;i<values.size();i++){
//         if (min>values[i]){
//             min=values[i];
//             index=i;
//         }
//     }
//     return min;
// }

//long getIndexOfValuesEqualOrUnderAValue(double value,std::vector<double> &values){
//
//    long indexMax=values.size()-1;
//    long indexMin=0;
//
//
//
//}


void Functions::intersection(Point2d &p1, Point2d &p2, Point2d &p3, Point2d &p4,Point2d &intersection, bool &validIntersection) {
//     // Store the values for fast access and easy
//     // equations-to-code conversion
//     intersection=Point2d(0,0);
//     validIntersection=true;
//
//     double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
//     double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
// // std::cout<<"testing vertical "<<x3-x4<<'\n';
// bool verticala=false;
// bool verticalb=false;
// bool horizontala=false;
// bool horizontalb=false;
// double epsilon=0.00001;
// if(Functions::abs(x1-x2)<epsilon&&Functions::abs(y1-y2)>epsilon){
//   verticala=true;
// }
// if(Functions::abs(x3-x4)<epsilon&&Functions::abs(y3-y4)>epsilon){
//   verticalb=true;
// }
// if(Functions::abs(y1-y2)<epsilon&&Functions::abs(x1-x2)>epsilon){
//   horizontala=true;
// }
// if(Functions::abs(y3-y4)<epsilon&&Functions::abs(x3-x4)>epsilon){
//   horizontalb=true;
// }
// epsilon=0.0;
//     // std::cout<<x1<<" ,"<<y1<<" "<<x2<<","<<y2<<" "<<x3<<","<<y3<<" "<<x4<<","<<y4<<'\n';
//
//     double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
//     // If d is zero, there is no intersection
//     if (d == 0) validIntersection=false;
//     // if(abs(x1-789979)<.1){
//     //   std::cout<<"d "<<d<<'\n';
//     // }
//
//     // Get the x and y
//     double pre = (x1*y2 - y1*x2);
//     double post = (x3*y4 - y3*x4);
//     double x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
//     double y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
//
//     // Check if the x and y coordinates are within both lines
//     if ( x < Functions::min(x1-epsilon, x2-epsilon) || x > Functions::max(x1+epsilon, x2+epsilon) ||
//         x < Functions::min(x3-epsilon, x4-epsilon) || x > Functions::max(x3+epsilon, x4+epsilon) ) validIntersection=false;
//         // if(abs(x1-789979)<.1){
//         //   std::cout<<"fail 1 "<<d<<'\n';
//         // }
//     if ( y < Functions::min(y1-epsilon, y2-epsilon) || y > Functions::max(y1+epsilon, y2+epsilon) ||
//         y < Functions::min(y3-epsilon, y4-epsilon) || y > Functions::max(y3+epsilon, y4+epsilon) ) validIntersection=false;
//
// epsilon=.00001;
//
//         if(horizontala){
//           if(horizontalb){
//             if(Functions::abs(y1-y3)>epsilon){
//             validIntersection=false;
//             }else{
//               validIntersection=true;
//               std::cout<<"Attention, coincident horizontal lines"<<'\n';
//             }
//           }else if (verticalb){
//             if((y3-y1)*(y4-y1)<=0&&(x1-x3)*(x2-x3)<=0){
//               validIntersection=true;
//             }
//           }else{
//             if((y3-y1)*(y4-y1)<=0&&x >= Functions::min(x1, x2) && x <= Functions::max(x1, x2)){
//               validIntersection=true;
//             }
//           }
//
//         }
//         if(horizontalb){
//           if(horizontala){
//             if(Functions::abs(y1-y3)>epsilon){
//             validIntersection=false;
//           }else{
//             validIntersection=true;
//             std::cout<<"Attention, coincident horizontal lines"<<'\n';
//           }
//           }else if (verticala){
//             if((y1-y3)*(y2-y3)<=0&&(x3-x1)*(x4-x1)<=0){
//               validIntersection=true;
//             }
//           }else{
//             if((y1-y3)*(y2-y3)<=0&&x >= Functions::min(x3, x4) && x <= Functions::max(x3, x4)){
//               validIntersection=true;
//             }
//           }
//
//         }
//         if(verticala){
//
//           if(horizontalb){
//             if((y1-y3)*(y2-y3)<=0&&(x3-x1)*(x4-x1)<=0){
//               validIntersection=true;
//             }
//
//           }else if (verticalb){
//             if(Functions::abs(x1-x3)>epsilon){
//             validIntersection=false;
//             }else{
//               validIntersection=true;
//               std::cout<<"Attention, coincident vertical lines"<<'\n';
//             }
//           }else{
//             if((x3-x1)*(x4-x1)<=0&&y >= Functions::min(y1, y2) && y <= Functions::max(y1, y2)){
//               validIntersection=true;
//             }
//           }
//
//         }
//         if(verticalb){
//
//           if(horizontala){
//             if((y3-y1)*(y4-y1)<=0&&(x1-x3)*(x2-x3)<=0){
//               validIntersection=true;
//             }
//
//           }else if (verticala){
//             if(Functions::abs(x1-x3)>epsilon){
//             validIntersection=false;
//             }else{
//               validIntersection=true;
//               std::cout<<"Attention, coincident vertical lines"<<'\n';
//             }
//           }else{
//             if((x1-x3)*(x2-x3)<=0&&y >= Functions::min(y3, y4) && y <= Functions::max(y3, y4)){
//               validIntersection=true;
//             }
//           }
//
//         }
//
//     intersection.x = x;
//     intersection.y = y;







//method 2
// validIntersection=true;
// Point2d A2=p2;
// Point2d A1=p1;
// Point2d B2=p4;
// Point2d B1=p3;
// // A2-=A1;
// Point2d a=Point2d(A2.x-A1.x,A2.y-A1.y);
//    Point2d b=Point2d(B2.x-B1.x,B2.y-B1.y);
//
//    double f = (a.y*b.x) - (a.x*b.y);
//
//    if(!f)      // lines are parallel
//        validIntersection= false;
//
//    Point2d c=Point2d(B2.x-A2.x,B2.y-A2.y);
//    double aa = (a.y*c.x) - (a.x*c.y);
//    double bb = (b.y*c.x) - (b.x*c.y);
//
//    if(f < 0)
//    {
//        if(aa > 0)     validIntersection= false;
//        if(bb > 0)     validIntersection= false;
//        if(aa < f)     validIntersection= false;
//        if(bb < f)     validIntersection= false;
//    }
//    else
//    {
//        if(aa < 0)     validIntersection= false;
//        if(bb < 0)     validIntersection= false;
//        if(aa > f)     validIntersection= false;
//        if(bb > f)     validIntersection= false;
//    }
//
//    // if(out)
//        double out = 1.0 - (aa / f);
//        intersection=Point2d((B2.x-B1.x)*out+B1.x,(B2.y-B1.y)*out+B1.y);
//         // intersection = ((B2 - B1) * out) + B1
//    // return true;
//    // return intersection;


//  public domain function by Darel Rex Finley, 2006



//  Determines the intersection point of the line defined by points A and B with the
//  line defined by points C and D.
//
//  Returns YES if the intersection point was found, and stores that point in X,Y.
//  Returns NO if there is no determinable intersection point, in which case X,Y will
//  be unmodified.

// bool lineIntersection(
validIntersection=true;
double Ax=p1.x;
double Ay=p1.y;
double Bx=p2.x;
double By=p2.y;
double Cx=p3.x;
double Cy=p3.y;
double Dx=p4.x;
double Dy=p4.y;
double X;
 double Y;

  double  distAB, theCos, theSin, newX, ABpos ;

  //  Fail if either line is undefined.
  if (Ax==Bx && Ay==By || Cx==Dx && Cy==Dy) validIntersection=false;

  //  (1) Translate the system so that point A is on the origin.
  Bx-=Ax; By-=Ay;
  Cx-=Ax; Cy-=Ay;
  Dx-=Ax; Dy-=Ay;

  //  Discover the length of segment A-B.
  distAB=sqrt(Bx*Bx+By*By);

  //  (2) Rotate the system so that point B is on the positive X axis.
  theCos=Bx/distAB;
  theSin=By/distAB;
  newX=Cx*theCos+Cy*theSin;
  Cy  =Cy*theCos-Cx*theSin; Cx=newX;
  newX=Dx*theCos+Dy*theSin;
  Dy  =Dy*theCos-Dx*theSin; Dx=newX;

  //  Fail if the lines are parallel.
  if (Cy==Dy) validIntersection=false;

  //  (3) Discover the position of the intersection point along line A-B.
  ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);
  //  Fail if segment C-D doesn't cross line A-B.
if (Cy<0. && Dy<0. || Cy>=0. && Dy>=0.) validIntersection=false;

//  (3) Discover the position of the intersection point along line A-B.
// ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

//  Fail if segment C-D crosses line A-B outside of segment A-B.
if (ABpos<0. || ABpos>distAB) validIntersection=false;

  //  (4) Apply the discovered position to line A-B in the original coordinate system.
  X=Ax+ABpos*theCos;
  Y=Ay+ABpos*theSin;

  intersection=Point2d(X,Y);

  //  Success.
  // return YES;

}

long Functions::getQuadrant(Point2d center,Point2d point){
    if(point.x<=center.x&&point.y>=center.y){
        return 2;
    }else if(point.x<=center.x&&point.y<center.y){
        return 0;
    }else if(point.x>center.x&&point.y>=center.y){
        return 3;
    }else{
        return 1;
    }
}
bool Functions::inBoundaryOfASquare(Point2d center, Point2d point,double sizeX,double sizeY){
    // double EPSILON=1/9999999;

    double dx=Functions::abs(point.x-center.x);
    double dy=Functions::abs(point.y-center.y);
    // if(dx>(sizeX/2.0+EPSILON)||dy>(sizeY/2.0+EPSILON)){
    //     return false;
    // }else{
    //     return true;
    // }
    if(dx<=sizeX/2.0&&dy<=sizeY/2.0){
      return true;
    }else{
      return false;
    }
}
// Point2d Functions::intersectionWithHorizontalLine(Point2d &start,Point2d &end,Point2d &startHoriz,Point2d &endHoriz,bool &valid){
//   Point2d intersectionX;
//   valid=true;
//   double dax=Functions::abs(start.x-startHoriz.x);
//   double day=Functions::abs(start.y-startHoriz.y);
//   double x,y;
//   double dx=Functions::abs(start.x-end.x);
//   double dy=Functions::abs(start.y-end.y);
//   double percentage=day/dy;
//   y=startHoriz.y;
//   x=start.x+percentage*(end.x-start.x);
//   intersectionX=Point2d(x,y);
//   double minX=Functions::min(startHoriz.x,endHoriz.x);
//   double maxX=Functions::max(startHoriz.x,endHoriz.x);
//   if(x>=minX&&x<=maxX){
//     valid=true;
//   }else{
//     valid=false;
//   }
//   return intersectionX;
// }
// Point2d Functions::intersectionWithVerticalLine(Point2d &start,Point2d &end,Point2d &startVert,Point2d &endVert,bool &valid){
//   Point2d intersection;
//   valid=true;
//   double dax=Functions::abs(start.x-startVert.x);
//   double day=Functions::abs(start.y-startVert.y);
//   double x,y;
//   double dx=Functions::abs(start.x-end.x);
//   double dy=Functions::abs(start.y-end.y);
//   double percentage=dax/dx;
//   x=startVert.x;
//   y=start.y+percentage*(end.y-start.y);
//   intersection=Point2d(x,y);
//   double minY=Functions::min(startVert.y,endVert.y);
//   double maxY=Functions::max(startVert.y,endVert.y);
//   if(y>=minY&&y<=maxY){
//     valid=true;
//   }else{
//     valid=false;
//   }
//   return intersection;
// }
// std::vector<Point2d> Functions::instersectionsLineWithBoundaryOfASquare(Point2d center,double side,Point2d &start,Point2d &end){
//   std::vector<Point2d> points;
//   bool valid;
//   Point2d intersection=intersectionWithHorizontalLine(start,end,Point2d(center.x-side/2.0,center.y+side/2.0),Point2d(center.x+side/2.0,center.y+side/2.0),valid);
//   if(valid){
//     points.push_back(intersection);
//   }
//   intersection=intersectionWithHorizontalLine(start,end,Point2d(center.x-side/2.0,center.y-side/2.0),Point2d(center.x+side/2.0,center.y-side/2.0),valid);
//   if(valid){
//     points.push_back(intersection);
//   }
//   intersection=intersectionWithVerticalLine(start,end,Point2d(center.x-side/2.0,center.y-side/2.0),Point2d(center.x-side/2.0,center.y+side/2.0),valid);
//   if(valid){
//     points.push_back(intersection);
//   }
//   intersection=intersectionWithVerticalLine(start,end,Point2d(center.x+side/2.0,center.y-side/2.0),Point2d(center.x+side/2.0,center.y+side/2.0),valid);
//   if(valid){
//     points.push_back(intersection);
//   }
//   return points;
// }
std::vector<Point2d> Functions::instersectionsLineWithBoundaryOfARectangle(Point2d &center,double sideX,double sideY,Point2d &start,Point2d &end){
  std::vector<Point2d> points;
  bool valid;
  Point2d intersection;
  Point2d a=Point2d(center.x-sideX/2.0,center.y+sideY/2.0);
  Point2d b=Point2d(center.x+sideX/2.0,center.y+sideY/2.0);
  Functions::intersection(start,end,a,b,intersection,valid);
  // Point2d intersection=intersectionWithHorizontalLine(start,end,Point2d(center.x-sideX/2.0,center.y+sideY/2.0),Point2d(center.x+sideX/2.0,center.y+sideY/2.0),valid);
  if(valid){
    points.push_back(intersection);
  }
  // Point2d intersection;
   a=Point2d(center.x-sideX/2.0,center.y-sideY/2.0);
   b=Point2d(center.x+sideX/2.0,center.y-sideY/2.0);
  Functions::intersection(start,end,a,b,intersection,valid);
  // intersection=intersectionWithHorizontalLine(start,end,Point2d(center.x-sideX/2.0,center.y-sideY/2.0),Point2d(center.x+sideX/2.0,center.y-sideY/2.0),valid);
  if(valid){
    points.push_back(intersection);
  }
  // Point2d intersection;
   a=Point2d(center.x-sideX/2.0,center.y-sideY/2.0);
   b=Point2d(center.x-sideX/2.0,center.y+sideY/2.0);
  Functions::intersection(start,end,a,b,intersection,valid);
  // Functions::intersection(start,end,Point2d(center.x-sideX/2.0,center.y-sideY/2.0),Point2d(center.x-sideX/2.0,center.y+sideY/2.0),intersection,valid);
  // intersection=intersectionWithVerticalLine(start,end,Point2d(center.x-sideX/2.0,center.y-sideY/2.0),Point2d(center.x-sideX/2.0,center.y+sideY/2.0),valid);
  if(valid){
    points.push_back(intersection);
  }
   a=Point2d(center.x+sideX/2.0,center.y-sideY/2.0);
   b=Point2d(center.x+sideX/2.0,center.y+sideY/2.0);
  Functions::intersection(start,end,a,b,intersection,valid);
  // Functions::intersection(start,end,Point2d(center.x+sideX/2.0,center.y-sideY/2.0),Point2d(center.x+sideX/2.0,center.y+sideY/2.0),intersection,valid);
  // intersection=intersectionWithVerticalLine(start,end,Point2d(center.x+sideX/2.0,center.y-sideY/2.0),Point2d(center.x+sideX/2.0,center.y+sideY/2.0),valid);
  if(valid){
    points.push_back(intersection);
  }
  return points;
}
std::vector<long> Functions::getQuadrantsLine(Point2d &center,Point2d &start,Point2d &end,double sizeX,double sizeY){
  std::set<long> quadrants;
  bool startInBoundary=Functions::inBoundaryOfASquare(center, start, sizeX, sizeY);
  bool endInBoundary=Functions::inBoundaryOfASquare(center, end, sizeX, sizeY);
  long quadrantA=Functions::getQuadrant(center, start);
  long quadrantB=Functions::getQuadrant(center, end);
  if(startInBoundary){
    quadrants.insert(quadrantA);
    // quadrants.push_back(quadrantB);
  }
  if(endInBoundary){
    quadrants.insert(quadrantB);
    // quadrants.push_back(quadrantB);
  }
  Point2d centerQ=Point2d(center.x-sizeX/4.0,center.y+sizeY/4.0);
  std::vector<Point2d> intersectionsWithQuadrant=Functions::instersectionsLineWithBoundaryOfARectangle(centerQ,sizeX/2.0,sizeY/2.0,start,end);
  if(intersectionsWithQuadrant.size()>0){
    quadrants.insert(getQuadrant(center,centerQ));
  }
  centerQ=Point2d(center.x+sizeX/4.0,center.y+sizeY/4.0);
  intersectionsWithQuadrant=Functions::instersectionsLineWithBoundaryOfARectangle(centerQ,sizeX/2.0,sizeY/2.0,start,end);
  if(intersectionsWithQuadrant.size()>0){
    quadrants.insert(getQuadrant(center,centerQ));
  }
  centerQ=Point2d(center.x+sizeX/4.0,center.y-sizeY/4.0);
  intersectionsWithQuadrant=Functions::instersectionsLineWithBoundaryOfARectangle(centerQ,sizeX/2.0,sizeY/2.0,start,end);
  if(intersectionsWithQuadrant.size()>0){
    quadrants.insert(getQuadrant(center,centerQ));
  }
  centerQ=Point2d(center.x-sizeX/4.0,center.y-sizeY/4.0);
  intersectionsWithQuadrant=Functions::instersectionsLineWithBoundaryOfARectangle(centerQ,sizeX/2.0,sizeY/2.0,start,end);
  if(intersectionsWithQuadrant.size()>0){
    quadrants.insert(getQuadrant(center,centerQ));
  }
  std::vector<long> quadrantsVector(quadrants.begin(),quadrants.end());
  // quadrants
  // for(auto it:quadrants){
  //   quadrantsVector.push_back(it);
  // }
  return quadrantsVector;
}
std::vector<long> Functions::getQuadrantsLineOld(Point2d &center,Point2d &start,Point2d &end,double sizeX,double sizeY){
    std::vector<long> quadrants;
    bool startInBoundary=Functions::inBoundaryOfASquare(center, start, sizeX, sizeY);
    bool endInBoundary=Functions::inBoundaryOfASquare(center, end, sizeX, sizeY);
    long quadrantA=Functions::getQuadrant(center, start);
    long quadrantB=Functions::getQuadrant(center, end);
    if(startInBoundary&&endInBoundary){
        if(quadrantA==quadrantB){
            quadrants.push_back(quadrantA);
        }else{
            if((quadrantA==2&&quadrantB==0)||(quadrantA==0&&quadrantB==2)){
                quadrants.push_back(quadrantA);
                quadrants.push_back(quadrantB);
            }else if((quadrantA==2&&quadrantB==3)||(quadrantA==3&&quadrantB==2)){
                quadrants.push_back(quadrantA);
                quadrants.push_back(quadrantB);
            }else if((quadrantA==0&&quadrantB==1)||(quadrantA==1&&quadrantB==0)){
                quadrants.push_back(quadrantA);
                quadrants.push_back(quadrantB);
            }else if((quadrantA==3&&quadrantB==1)||(quadrantA==1&&quadrantB==3)){
                quadrants.push_back(quadrantA);
                quadrants.push_back(quadrantB);
            }else{
                Point2d intersectionX,intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double day=Functions::abs(start.y-center.y);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                quadrants.push_back(quadrantA);
                quadrants.push_back(quadrantB);
                Point2d point=Point2d((intersectionX.x+intersectionY.x)/2.0,(intersectionX.y+intersectionY.y)/2.0);
                quadrants.push_back(Functions::getQuadrant(center, point));
            }
        }
    }else if(startInBoundary){
        if(quadrantA==quadrantB){
            quadrants.push_back(quadrantA);
        }else{
            quadrants.push_back(quadrantA);
            if((quadrantA==2&&quadrantB==0)||(quadrantA==0&&quadrantB==2)){
                Point2d intersectionX;
                double day=Functions::abs(start.y-center.y);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantB);
                }
            }else if((quadrantA==2&&quadrantB==3)||(quadrantA==3&&quadrantB==2)){
                Point2d intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantB);
                }
            }else if((quadrantA==0&&quadrantB==1)||(quadrantA==1&&quadrantB==0)){
                Point2d intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantB);
                }
            }else if((quadrantA==3&&quadrantB==1)||(quadrantA==1&&quadrantB==3)){
                Point2d intersectionX;
                double day=Functions::abs(start.y-center.y);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantB);
                }
            }else{
                if((quadrantA==2&&quadrantB==1)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x>0){
                            quadrants.push_back(3);
                        }else if(x-center.x<0){
                            quadrants.push_back(0);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantB);
                        }
                    }else{
                        quadrants.push_back(3);
                    }
                }else if((quadrantA==1&&quadrantB==2)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x<0){
                            quadrants.push_back(0);
                        }else if(x-center.x>0){
                            quadrants.push_back(3);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantB);
                        }
                    }else{
                        quadrants.push_back(0);
                    }
                }else if((quadrantA==3&&quadrantB==0)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x<0){
                            quadrants.push_back(2);
                        }else if(x-center.x>0){
                            quadrants.push_back(1);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantB);
                        }
                    }else{
                        quadrants.push_back(2);
                    }
                }else if((quadrantA==0&&quadrantB==3)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x<0){
                            quadrants.push_back(2);
                        }else if(x-center.x>0){
                            quadrants.push_back(1);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantB);
                        }
                    }else{
                        quadrants.push_back(1);
                    }
                }
            }
        }
    }else if(endInBoundary){
        if(quadrantA==quadrantB){
            quadrants.push_back(quadrantB);
        }else{
            quadrants.push_back(quadrantB);
            if((quadrantA==2&&quadrantB==0)||(quadrantA==0&&quadrantB==2)){
                Point2d intersectionX;
                double day=Functions::abs(start.y-center.y);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else if((quadrantA==2&&quadrantB==3)||(quadrantA==3&&quadrantB==2)){
                Point2d intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else if((quadrantA==0&&quadrantB==1)||(quadrantA==1&&quadrantB==0)){
                Point2d intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else if((quadrantA==3&&quadrantB==1)||(quadrantA==1&&quadrantB==3)){
                Point2d intersectionX;
                double day=Functions::abs(start.y-center.y);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else{
                if((quadrantA==2&&quadrantB==1)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x>0){
                            quadrants.push_back(3);
                        }else if(x-center.x<0){
                            quadrants.push_back(0);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantA);
                        }
                    }else{
                        quadrants.push_back(0);
                    }
                }else if((quadrantA==1&&quadrantB==2)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x<0){
                            quadrants.push_back(0);
                        }else if(x-center.x>0){
                            quadrants.push_back(3);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantA);
                        }
                    }else{
                        quadrants.push_back(3);
                    }
                }else if((quadrantA==3&&quadrantB==0)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x<0){
                            quadrants.push_back(2);
                        }else if(x-center.x>0){
                            quadrants.push_back(1);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantA);
                        }
                    }else{
                        quadrants.push_back(1);
                    }
                }else if((quadrantA==0&&quadrantB==3)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x<0){
                            quadrants.push_back(2);
                        }else if(x-center.x>0){
                            quadrants.push_back(1);
                        }
                        Point2d intersectionY;
                        double dax=Functions::abs(start.x-center.x);
                        double x,y;
                        double dx=Functions::abs(start.x-end.x);
                        double percentage=dax/dx;
                        y=start.y+percentage*(end.y-start.y);
                        x=center.x;
                        intersectionY=Point2d(x,y);
                        if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                            quadrants.push_back(quadrantA);
                        }
                    }else{
                        quadrants.push_back(2);
                    }
                }
            }
        }
    }else{
        if(quadrantA==quadrantB){
            if(quadrantA==2){
                Point2d intersectionX;
                double day=Functions::abs(start.y-(center.y+sizeY/2.0));
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y+sizeY/2.0;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
                Point2d intersectionY;
                double dax=Functions::abs(start.x-(center.x-sizeX/2.0));
                double dx=Functions::abs(start.x-end.x);
                percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x-sizeX/2.0;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else if(quadrantA==3){
                Point2d intersectionX;
                double day=Functions::abs(start.y-(center.y+sizeY/2.0));
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y+sizeY/2.0;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
                Point2d intersectionY;
                double dax=Functions::abs(start.x-(center.x+sizeX/2.0));
                double dx=Functions::abs(start.x-end.x);
                percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x+sizeX/2.0;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else if (quadrantA==1){
                Point2d intersectionX;
                double day=Functions::abs(start.y-(center.y-sizeY/2.0));
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y-sizeY/2.0;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
                Point2d intersectionY;
                double dax=Functions::abs(start.x-(center.x+sizeX/2.0));
                double dx=Functions::abs(start.x-end.x);
                percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x+sizeX/2.0;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }else{
                Point2d intersectionX;
                double day=Functions::abs(start.y-(center.y-sizeY/2.0));
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y-sizeY/2.0;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
                Point2d intersectionY;
                double dax=Functions::abs(start.x-(center.x-sizeX/2.0));
                double dx=Functions::abs(start.x-end.x);
                percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x-sizeX/2.0;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                }
            }
        }else{
            if((quadrantA==2&&quadrantB==0)||(quadrantA==0&&quadrantB==2)){
                Point2d intersectionX;
                double day=Functions::abs(start.y-center.y);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                    quadrants.push_back(quadrantB);
                }else{
                    Point2d intersectionY;
                    double dax=Functions::abs(start.x-(center.x-sizeX/2.0));
                    double x,y;
                    double dx=Functions::abs(start.x-end.x);
                    double percentage=dax/dx;
                    y=start.y+percentage*(end.y-start.y);
                    x=center.x-sizeX/2.0;
                    intersectionY=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                        quadrants.push_back(getQuadrant(center, intersectionY));
                    }
                }
            }else if((quadrantA==2&&quadrantB==3)||(quadrantA==3&&quadrantB==2)){
                Point2d intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                    quadrants.push_back(quadrantB);
                }else{
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-(center.y+sizeY/2.0));
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y+sizeY/2.0;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        quadrants.push_back(getQuadrant(center, intersectionX));
                    }
                }
            }else if((quadrantA==0&&quadrantB==1)||(quadrantA==1&&quadrantB==0)){
                Point2d intersectionY;
                double dax=Functions::abs(start.x-center.x);
                double x,y;
                double dx=Functions::abs(start.x-end.x);
                double percentage=dax/dx;
                y=start.y+percentage*(end.y-start.y);
                x=center.x;
                intersectionY=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                    quadrants.push_back(quadrantB);
                }else{
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-(center.y-sizeY/2.0));
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y-sizeY/2.0;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        quadrants.push_back(getQuadrant(center, intersectionX));
                    }
                }
            }else if((quadrantA==3&&quadrantB==1)||(quadrantA==1&&quadrantB==3)){
                Point2d intersectionX;
                double day=Functions::abs(start.y-center.y);
                double dy=Functions::abs(start.y-end.y);
                double percentage=day/dy;
                double x,y;
                y=center.y;
                x=start.x+percentage*(end.x-start.x);
                intersectionX=Point2d(x,y);
                if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                    quadrants.push_back(quadrantA);
                    quadrants.push_back(quadrantB);
                }else{
                    Point2d intersectionY;
                    double dax=Functions::abs(start.x-(center.x+sizeX/2.0));
                    double x,y;
                    double dx=Functions::abs(start.x-end.x);
                    double percentage=dax/dx;
                    y=start.y+percentage*(end.y-start.y);
                    x=center.x+sizeX/2.0;
                    intersectionY=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                        quadrants.push_back(getQuadrant(center, intersectionY));
                    }
                }
            }else{
                if((quadrantA==2&&quadrantB==1)||(quadrantA==1&&quadrantB==2)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x>0){
                            quadrants.push_back(3);
                            quadrants.push_back(1);
                        }else if(x-center.x<=0){
                            quadrants.push_back(0);
                            quadrants.push_back(2);
                        }
                    }
                    Point2d intersectionY;
                    double dax=Functions::abs(start.x-center.x);
                    double dx=Functions::abs(start.x-end.x);
                    percentage=dax/dx;
                    y=start.y+percentage*(end.y-start.y);
                    x=center.x;
                    intersectionY=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                        if(y-center.y>=0){
                            quadrants.push_back(3);
                            quadrants.push_back(2);
                        }else if(y-center.y<0){
                            quadrants.push_back(0);
                            quadrants.push_back(1);
                        }
                    }
                }else if((quadrantA==3&&quadrantB==0)||(quadrantA==0&&quadrantB==3)){
                    Point2d intersectionX;
                    double day=Functions::abs(start.y-center.y);
                    double dy=Functions::abs(start.y-end.y);
                    double percentage=day/dy;
                    double x,y;
                    y=center.y;
                    x=start.x+percentage*(end.x-start.x);
                    intersectionX=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionX, sizeX, sizeY)){
                        if(x-center.x>0){
                            quadrants.push_back(3);
                            quadrants.push_back(1);
                        }else if(x-center.x<=0){
                            quadrants.push_back(0);
                            quadrants.push_back(2);
                        }
                    }
                    Point2d intersectionY;
                    double dax=Functions::abs(start.x-center.x);
                    double dx=Functions::abs(start.x-end.x);
                    percentage=dax/dx;
                    y=start.y+percentage*(end.y-start.y);
                    x=center.x;
                    intersectionY=Point2d(x,y);
                    if(Functions::inBoundaryOfASquare(center, intersectionY, sizeX, sizeY)){
                        if(y-center.y>=0){
                            quadrants.push_back(3);
                            quadrants.push_back(2);
                        }else if(y-center.y<0){
                            quadrants.push_back(0);
                            quadrants.push_back(1);
                        }
                    }
                }
            }
        }
    }
    std::vector<long> result;
    result=Functions::unique(quadrants);
//    for(long i=0;i<quadrants.size();i++){
//        result.insert(quadrants[i]);
//    }
    return result;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INTERSECTION BOX WITH CIRCLE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Functions::positiveSectionCircle(float h, float r ) // returns the positive root of intersection of line y = h with circle centered at the origin and radius r
{
//    assert(r >= 0); // assume r is positive, leads to some simplifications in the formula below (can factor out r from the square root)
    return (h < r)? sqrt(r * r - h * h) : 0; // http://www.wolframalpha.com/input/?i=r+*+sin%28acos%28x+%2F+r%29%29+%3D+h
}

float Functions::integralCircleSegment(float x, float h, float r ) // indefinite integral of circle segment
{
    return .5f * (sqrt(1 - x * x / (r * r)) * x * r + r * r * asin(x / r) - 2 * h * x); // http://www.wolframalpha.com/input/?i=r+*+sin%28acos%28x+%2F+r%29%29+-+h
}

float Functions::area_intersectionCircleWithRectangle(float x0, float x1, float h, float r) // area of intersection of an infinitely tall box with left edge at x0, right edge at x1, bottom edge at h and top edge at infinity, with circle centered at the origin with radius r
{
    if(x0 > x1)
        std::swap(x0, x1); // this must be sorted otherwise we get negative area
    float s = positiveSectionCircle(h, r);
    return integralCircleSegment(std::max(-s, std::min(s, x1)), h, r) - integralCircleSegment(std::max(-s, std::min(s, x0)), h, r); // integrate the area
}

float Functions::area_intersectionCircleWithRectangle(float x0, float x1, float y0, float y1, float r) // area of the intersection of a finite box with a circle centered at the origin with radius r
{
    if(y0 > y1)
        std::swap(y0, y1); // this will simplify the reasoning
    if(y0 < 0) {
        if(y1 < 0)
            return area_intersectionCircleWithRectangle(x0, x1, -y0, -y1, r); // the box is completely under, just flip it above and try again
        else
            return area_intersectionCircleWithRectangle(x0, x1, 0, -y0, r) + area_intersectionCircleWithRectangle(x0, x1, 0, y1, r); // the box is both above and below, divide it to two boxes and go again
    } else {
//        assert(y1 >= 0); // y0 >= 0, which means that y1 >= 0 also (y1 >= y0) because of the swap at the beginning
        return area_intersectionCircleWithRectangle(x0, x1, y0, r) - area_intersectionCircleWithRectangle(x0, x1, y1, r); // area of the lower box minus area of the higher box
    }
}

float Functions::area_intersectionCircleWithRectangle(float x0, float y0, float x1,float y1, float cx, float cy, float r) // area of the intersection of a general box with a general circle
{
    x0 -= cx; x1 -= cx;
    y0 -= cy; y1 -= cy;
    // get rid of the circle center

    return area_intersectionCircleWithRectangle(x0, x1, y0, y1, r);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



double Functions::sampleDagumDistribution(double a,double b,double c){

  double p=Functions::runiform(0,1);

  double x=pow((pow(p,-1/c)-1)/exp(a*b),-1/a);
  return x;

}

// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <unordered_set>
#include <vector>


#include <iterator>
#include "../SpatialAnalysis/SpatialAnalysis/Functions.h"
#include "../SpatialAnalysis/SpatialAnalysis/ShapeFile.h"

#include "../SpatialAnalysis/SpatialAnalysis/FractalDimension.h"
#include "../SpatialAnalysis/SpatialAnalysis/Geometry.h"
#include "../SpatialAnalysis/SpatialAnalysis/GeometryGraph.h"
#include "../SpatialAnalysis/SpatialAnalysis/DualExtendedGraph.h"
#include "../SpatialAnalysis/SpatialAnalysis/Grafo.h"
#include <stdio.h>
#include <sstream>
#include <queue>
#include <string>
#include <tuple>
#include "../SpatialAnalysis/SpatialAnalysis/InterfaceCityGeneration.h"
#include "../SpatialAnalysis/SpatialAnalysis/InterfaceMultiFractalAnalysis.h"
#include "../SpatialAnalysis/SpatialAnalysis/GenerativeProcedures.h"
#include "../SpatialAnalysis/SpatialAnalysis/CriticalExponentsPercolation.h"
#include "../SpatialAnalysis/SpatialAnalysis/InterfaceDijkstra.h"
#include "../SpatialAnalysis/SpatialAnalysis/SpatialInteraction.h"
#include "../SpatialAnalysis/SpatialAnalysis/RoadNetworkGeneration.h"
using namespace Rcpp;

template <>
struct std::hash<std::vector<long> > {
public:
    size_t operator()(std::vector<long> n) const throw() {
        size_t value=hash<long>() (n[0]);
        for(long i=1;i<n.size();i++){
          value=value^hash<long>() (n[i]);
        }
        return value;

    }
};

template <>
struct std::hash<std::vector<double> > {
public:
    size_t operator()(std::vector<double> n) const throw() {
        size_t value=hash<double>() (n[0]);
        for(long i=1;i<n.size();i++){
          value=value^hash<double>() (n[i]);
        }
        return value;

    }
};

RCPP_EXPOSED_CLASS(Grafo)
RCPP_EXPOSED_CLASS(DualExtendedGraph)
RCPP_EXPOSED_CLASS(InterfaceCityGeneration)
RCPP_EXPOSED_CLASS(InterfaceMultiFractalAnalysis)



//
// // [[Rcpp::export]]
// DataFrame generateCloud(long xInit,long yInit,long maxNumberObjects){
//
//
//   std::vector<std::vector<double> >  matrix=GenerativeProcedures::generateTerrain(xInit,yInit,w,h,zoom);
//
//
//
//
//   List list(3);
//   list[0]=wrap(matrix[0]);
//   list[1]=wrap(matrix[1]);
//   list[2]=wrap(matrix[2]);
//
//
//
//
//
//   CharacterVector namevec;
//   namevec.push_back("x");
//   namevec.push_back("y");
//   namevec.push_back("z");
//
//
//
//   list.attr("names") = namevec;
//   DataFrame df(list);
//   return df;
//
// }



// [[Rcpp::export]]
DataFrame generateTerrain(long xInit,long yInit,long w,long h,double zoom){


  std::vector<std::vector<double> >  matrix=GenerativeProcedures::generateTerrain(xInit,yInit,w,h,zoom);




  List list(3);
  list[0]=wrap(matrix[0]);
  list[1]=wrap(matrix[1]);
  list[2]=wrap(matrix[2]);





  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");
  namevec.push_back("z");



  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}








// [[Rcpp::export]]
NumericVector evolveCities(NumericVector currentState,long generations,double alpha,double lambda,double increaseInPopulation){
  std::vector<long> colors;
  double totalSize=0;

  for(long j=0;j<currentState.size();j++){
    totalSize+=(currentState[j]);
  }
  for(long i=0;i<generations;i++){

    long indexMax=0;
    double max=0;
    for(long j=0;j<currentState.size();j++){
      double random1=Functions::runiform(0,1);
      double random2=Functions::runiform(0,1);
      double newValue=random1*pow((currentState[j])/totalSize,alpha)+lambda*random2;
      if(newValue>max){
        max=newValue;
        indexMax=j;
      }
    }
    currentState[indexMax]+=increaseInPopulation;
    totalSize+=increaseInPopulation;
  }
  return currentState;

}


// [[Rcpp::export]]
NumericVector evolveCitiesLinearSpace(NumericVector currentState,long generations,double d0,double increaseInPopulation){
  std::vector<long> colors;
  // double totalSize=0;
  std::vector<double> probabilityField;
  probabilityField.resize(currentState.size(),0.0);

  double max=0;
  for(long j=0;j<currentState.size();j++){
    if(currentState[j]>0){
      double miny=.1;
      double dmax=d0*sqrt(log(currentState[j])/miny-1);
      double minx=Functions::max(0,floor((double)j-dmax));
      double maxx=Functions::min((double)(currentState.size()),floor((double)j+dmax));
      for(long h=minx;h<maxx;h++){
        probabilityField[h]+=log(currentState[j])/(1+sqrt(Functions::abs(j-h)/d0));
        if(probabilityField[h]>max){
          max=probabilityField[h];
        }

      }
    }
      // totalSize+=currentState[j];
  }
  for(long i=0;i<generations;i++){

    long indexMax=0;
    // double maxTemp=0;
    std::vector<long> possibleIndex;
    for(long j=0;j<probabilityField.size();j++){
      double random1=Functions::runiform(0,1);
      // double random2=Functions::runiform(0,1);
      // if(probabilityField[j]/max-random1>maxTemp){
        // maxTemp=probabilityField[j]/max-random1;
        // indexMax=j;
      for(long h=0;h<(probabilityField[j]/max-random1)*20;h++){
        possibleIndex.push_back(j);
      }

      // }
    }
    if(possibleIndex.size()>0){
      indexMax=possibleIndex[(long)Functions::runiform(0,possibleIndex.size()-1)];
      currentState[indexMax]+=increaseInPopulation;
      double miny=.1;
      double dmax=d0*sqrt(log(currentState[indexMax])/miny-1);
      double minx=Functions::max(0,floor((double)indexMax-dmax));
      double maxx=Functions::min((double)(currentState.size()),floor((double)indexMax+dmax));
      for(long h=minx;h<maxx;h++){
        probabilityField[h]+=log(currentState[indexMax])/(1+sqrt(Functions::abs(indexMax-h)/d0));
        if(probabilityField[h]>max){
          max=probabilityField[h];
        }

      }
    // totalSize+=increaseInPopulation;
    }
  }
  return currentState;

}










// [[Rcpp::export]]
XPtr<InterfaceCityGeneration> generateInitialCities(double d0,double saturationLevel,double maxX,double maxY,long numberCitiesPerRow){
  InterfaceCityGeneration* interface=new InterfaceCityGeneration();
  GenerativeProcedures::generateInitialCities(interface,d0,saturationLevel,maxX,maxY,numberCitiesPerRow);
  Rcpp::XPtr< InterfaceCityGeneration > p(interface,true) ;
  return (p);
}

// [[Rcpp::export]]
XPtr<InterfaceCityGeneration> loopGenerateCities(XPtr<InterfaceCityGeneration> interface,double lambda,double alpha,long numberIterations){
  GenerativeProcedures::loopGenerateCities(interface,lambda,alpha,numberIterations);
  // Rcpp::XPtr< interface > p(interface,true) ;
  return (interface);
}

// [[Rcpp::export]]
DataFrame get_generatedCities(XPtr<InterfaceCityGeneration> interface ,double minSize){
  NumericVector x;
  NumericVector y;
  NumericVector size;
  NumericVector idMetropolis;
  NumericVector ids;

  for(long i=0;i<interface->cities.size();i++){
    if(interface->cities[i].x>minSize){
      x.push_back(interface->cities[i].node->location.x);
      y.push_back(interface->cities[i].node->location.y);
      size.push_back(interface->cities[i].x);
    // idCity=interface->cities[i].id;
      ids.push_back(interface->cities[i].id);
      idMetropolis.push_back(interface->cities[i].metropolisId);
    }
  }

  List list(5);
  list[0]=(x);
  list[1]=y;
  list[2]=size;
  list[3]=ids;
  list[4]=idMetropolis;




  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");
  namevec.push_back("size");
  namevec.push_back("id");
  namevec.push_back("idMetropolis");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



// [[Rcpp::export]]
DataFrame getPotentialField(XPtr<InterfaceCityGeneration> interface){
  NumericVector x;
  NumericVector y;
  NumericVector values;
  // NumericVector idMetropolis;
  // NumericVector ids;

  for(long i=0;i<interface->potentialField.clusters.size();i++){

      x.push_back(interface->potentialField.clusters[i].calculateCentroid().x);
      y.push_back(interface->potentialField.clusters[i].calculateCentroid().y);
      values.push_back(interface->potentialField.clusters[i].value);

  }

  List list(3);
  list[0]=(x);
  list[1]=y;
  list[2]=values;
  // list[3]=ids;
  // list[4]=idMetropolis;




  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");
  namevec.push_back("value");
  // namevec.push_back("id");
  // namevec.push_back("idMetropolis");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

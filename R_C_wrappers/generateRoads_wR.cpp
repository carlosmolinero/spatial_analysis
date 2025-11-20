// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <unordered_set>
#include <vector>

//NOTE in class network there is another generation of roads (my algorithm) currently unused
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



// [[Rcpp::export]]
void straightenGraph(XPtr<Grafo> G,double increment, long numberTimes,NumericVector edgeFlows){
  // std::vector<double>& edgeFlows;
  std::vector<double> edgeFlows_=as<std::vector<double> > (edgeFlows);
  RoadNetworkGeneration::straightenGraph(G,increment,numberTimes,edgeFlows_);
}

// [[Rcpp::export]]
double calculateStraightnessEfficiency(XPtr<Grafo> G){
  // std::vector<double>& edgeFlows;
  // std::vector<double> edgeFlows_=as<std::vector<double> > (edgeFlows);
  double E=RoadNetworkGeneration::calculateStraightnessEfficiency(G);
  return E;
}

// [[Rcpp::export]]
NumericVector calculateStraightnessAndTripsEfficiency(XPtr<Grafo> G,double d0){
  // std::vector<double>& edgeFlows;
  // std::vector<double> edgeFlows_=as<std::vector<double> > (edgeFlows);
  std::vector<double> result=RoadNetworkGeneration::calculateStraightnessEfficiencyAndTripEfficiency(G,d0);
  NumericVector v={(result[0]),result[1]};
  return v;
}


// [[Rcpp::export]]
DataFrame getComponentsOfPerformanceNetwork(XPtr<Grafo> G){
  std::tuple<double,double,double,double,double,double> componentsPerformance=RoadNetworkGeneration::getComponentsOfPerformance(G);
  List list(6);
    list[0]=wrap(std::get<0>(componentsPerformance));
    list[1]=wrap(std::get<1>(componentsPerformance));
    list[2]=wrap(std::get<2>(componentsPerformance));
    list[3]=wrap(std::get<3>(componentsPerformance));
    list[4]=wrap(std::get<4>(componentsPerformance));
    list[5]=wrap(std::get<5>(componentsPerformance));








  CharacterVector namevec;
  namevec.push_back("r");
  namevec.push_back("l");
  namevec.push_back("d");
  namevec.push_back("v");
  namevec.push_back("n");
  namevec.push_back("N");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}



// [[Rcpp::export]]
double performanceRoadNetwork(XPtr<Grafo> G,double beta1,double beta2){
  double performance=RoadNetworkGeneration::performance(G, beta1, beta2);
return performance;
}


// [[Rcpp::export]]
XPtr<Grafo> keepOnlySimplestPaths(XPtr<Grafo> G){



    Grafo* result=new Grafo();
    RoadNetworkGeneration::keepOnlySimplestPathsBetweenNodes(G,result);

     Rcpp::XPtr< Grafo > p(result,true) ;
 return (p);

}



// [[Rcpp::export]]
XPtr<Grafo> createRoadNetworkFromCities(DataFrame x_y_mass_ofCities,double alpha,double d0,long numberDummyNodes){



    Grafo* G=new Grafo();

    std::vector<double> x=Rcpp::as<std::vector<double> > (x_y_mass_ofCities[0]);
    std::vector<double> y=Rcpp::as<std::vector<double> > (x_y_mass_ofCities[1]);
    std::vector<double> mass=Rcpp::as<std::vector<double> > (x_y_mass_ofCities[2]);
    std::tuple<std::vector<double>, std::vector<double>,std::vector<double> > x_y_mass_ofCities_=std::make_tuple(x,y,mass);
    RoadNetworkGeneration::createRoadNetworkFromCities(x_y_mass_ofCities_,G,alpha,d0,numberDummyNodes);

    // std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
    // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,5,false);
    // G->reset();
    // Grafo::removeSuperfluousNodes(R,G,pairsOldNew,15,false);
    // R->reset();
    // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,30,false);
    // delete G;
     Rcpp::XPtr< Grafo > p(G,true) ;
 return (p);

}


// [[Rcpp::export]]
XPtr<Grafo> getDelanuayGraphFromCities(DataFrame x_y_mass_ofCities,long numberDummyNodes){



    Grafo* G=new Grafo();

    std::vector<double> x=Rcpp::as<std::vector<double> > (x_y_mass_ofCities[0]);
    std::vector<double> y=Rcpp::as<std::vector<double> > (x_y_mass_ofCities[1]);
    std::vector<double> mass=Rcpp::as<std::vector<double> > (x_y_mass_ofCities[2]);
    std::tuple<std::vector<double>, std::vector<double>,std::vector<double> > x_y_mass_ofCities_=std::make_tuple(x,y,mass);
    RoadNetworkGeneration::getDelanuayGraphFromCities(x_y_mass_ofCities_,G,numberDummyNodes);

    // std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
    // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,5,false);
    // G->reset();
    // Grafo::removeSuperfluousNodes(R,G,pairsOldNew,15,false);
    // R->reset();
    // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,30,false);
    // delete G;
     Rcpp::XPtr< Grafo > p(G,true) ;
 return (p);

}



// [[Rcpp::export]]
XPtr<Grafo> createRoadNetwork(XPtr<Grafo> delanuayWithCities,NumericVector multiplierTopo,NumericVector idEdgesPerCity,NumericVector multiplierRivers,double alpha,double d0,double proportionBetweenSpeedInCityAndOutside){


    std::vector<double> multiplierTopo_=as<std::vector<double> > (multiplierTopo);
    std::vector<double> multiplierRivers_=as<std::vector<double> > (multiplierRivers);
    std::vector<long> idEdgesPerCity_=as<std::vector<long> > (idEdgesPerCity);
    Grafo* G=new Grafo();
    RoadNetworkGeneration::createRoadNetwork(delanuayWithCities,G,multiplierTopo_,idEdgesPerCity_,proportionBetweenSpeedInCityAndOutside,multiplierRivers_,alpha,d0);
    // std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
    // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,5,false);
    // G->reset();
    // Grafo::removeSuperfluousNodes(R,G,pairsOldNew,15,false);
    // R->reset();
    // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,30,false);
    // delete G;
     Rcpp::XPtr< Grafo > p(G,true) ;
 return (p);

}

// // [[Rcpp::export]]
// XPtr<Grafo> createRoadNetwork_exponentDecay(XPtr<Grafo> delanuayWithCities,double exponentDecayDistance,NumericVector speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion){


//     std::vector<double> speedLimits_=as<std::vector<double> > (speedLimits);
//     Grafo* G=new Grafo();
//     RoadNetworkGeneration::createRoadNetwork(delanuayWithCities,G,exponentDecayDistance,speedLimits_,alpha,d0,angleAllowed,capacityLink,alpha_congestion,beta_congestion);
//     // std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
//     // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,5,false);
//     // G->reset();
//     // Grafo::removeSuperfluousNodes(R,G,pairsOldNew,15,false);
//     // R->reset();
//     // Grafo::removeSuperfluousNodes(G,R,pairsOldNew,30,false);
//     // delete G;
//      Rcpp::XPtr< Grafo > p(G,true) ;
//  return (p);

// }




// [[Rcpp::export]]
NumericVector calculateTotalDistanceTravelledFromEachNode(XPtr< Grafo > G, double distanceLimit){

  std::vector<double> distances;

    SpatialInteraction::calculateTotalDistanceTravelledFromEachNode(G,distanceLimit,distances);


  return wrap(distances);

}


// [[Rcpp::export]]
NumericVector calculateTotalTimeTravelledFromEachNode(XPtr< Grafo > G,NumericVector speedLimits,double capacity,double alpha_congestion, double beta_congestion,double time){
  std::vector<double> speedLimits_=as<std::vector<double> > (speedLimits);

  std::vector<double> distances;
  DualExtendedGraph deg;
  DualExtendedGraph::addPrimal(&deg,G);
 // calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta);

    distances=SpatialInteraction::calculateTotalTimesTravelledFromEachNode(&deg,speedLimits_,capacity,alpha_congestion,beta_congestion,time);


  return wrap(distances);
}


// [[Rcpp::export]]
NumericVector calculateFlows(XPtr< Grafo > G, double distanceLimit){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  std::vector<double> flows;

    SpatialInteraction::calculateFlow(G,distanceLimit,flows);


  return wrap(flows);
}

// [[Rcpp::export]]
NumericVector calculateEdgeFlows(XPtr< Grafo > G, double distanceLimit){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  // std::vector<double> flows;
//double outgoingTrips=0;
  InterfaceFlows flows;
  flows.initFlows(G->links.size());
  flows.initValuesToPass(G->nodes.size());
  SpatialInteraction::calculateEdgeFlow(G,distanceLimit,flows);


  return wrap(flows.getFlows(0));
}

// [[Rcpp::export]]
DataFrame calculateEdgeFlowsSeveralDistances(XPtr< Grafo > G, double distanceLimitForDijkstra, NumericVector distances){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  // std::vector<double> flows;

//double outgoingTrips=0;
  InterfaceFlows flows;
  // flows.setNumberSubdivisions(numberDistances);
  std::vector<double> distances_=as<std::vector<double> > (distances);
  flows.setDistances(distances_);
  flows.initFlows(G->links.size());
  flows.initValuesToPass(G->nodes.size());
  SpatialInteraction::calculateEdgeFlow(G,distanceLimitForDijkstra,flows);
  std::cout<<"ended calculation, exporting results"<<'\n';
  List list(flows.distancesTrips.size());
   for (long i=0;i<flows.distancesTrips.size();i++){
     list[i]=wrap(flows.getFlows(i));
   }






 CharacterVector namevec;
 for (long i=0;i<flows.distancesTrips.size();i++){
   namevec.push_back(std::to_string(floor(flows.distancesTrips[i])));
 }

 list.attr("names") = namevec;
 DataFrame df(list);
 return df;
 // namevec.push_back("lengthRemoved");
 // namevec.push_back("linksRemoved");
 //  return wrap(i need to see how to return this);
}
// [[Rcpp::export]]
NumericVector calculateNormalisedEdgeFlows(XPtr< Grafo > G, double distanceLimit){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  // std::vector<double> flows;
double outgoingTrips=0;
// numberTripsGenerated=0;
InterfaceFlows flows;
// flows.setNumberSubdivisions(1);
flows.initFlows(G->links.size());
flows.initValuesToPass(G->nodes.size());
    SpatialInteraction::calculateNormalisedEdgeFlow(G,distanceLimit,flows,outgoingTrips);
 // std::vector<double> edgeFlows=flows.getFlows(0);

  return wrap(flows.getFlows(0));
}

// [[Rcpp::export]]
DataFrame calculateRobustness(XPtr<Grafo> G){

  std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(G);
   List list(2);
  list[0]=robustness.first;
  list[1]=robustness.second;






  CharacterVector namevec;
  namevec.push_back("lengthRemoved");
  namevec.push_back("linksRemoved");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}

// [[Rcpp::export]]
NumericVector calculateTotalNumberOfTripsFromEachNode(XPtr< Grafo > G, double distanceLimit){

  std::vector<double> trips;

    SpatialInteraction::calculateTotalTripsFromEachNode(G,distanceLimit,trips);


  return wrap(trips);
}


// // [[Rcpp::export]]
// DataFrame experiments_optimizeAlpha(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//
//
//
// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double>  >  results=RoadNetworkGeneration::experiments_optimizeAlpha(d0,capacityLink,alpha_congestion,beta_congestion,time);
//
//
//      List list(9);
//   list[0]=wrap(std::get<0>(results));
//   list[1]=wrap(std::get<1>(results));
//   list[2]=wrap(std::get<2>(results));
//   list[3]=wrap(std::get<3>(results));
//   list[4]=wrap(std::get<4>(results));
//   list[5]=wrap(std::get<5>(results));
//   list[6]=wrap(std::get<6>(results));
//   list[7]=wrap(std::get<7>(results));
//   list[8]=wrap(std::get<8>(results));
//
//
//
//
//
//
//   CharacterVector namevec;
//   namevec.push_back("alpha");
//   namevec.push_back("robustnessLengths");
//   namevec.push_back("robustnessNumLinks");
//   namevec.push_back("totalTimeDistanceFromNodes");
//   namevec.push_back("tsl");
//   namevec.push_back("numIntersections");
//   namevec.push_back("flowPerMeter");
//   namevec.push_back("intersectionsPerMeter");
//   namevec.push_back("numberTripsGenerated");
//
//
//
//
//   list.attr("names") = namevec;
//   DataFrame df(list);
//   return df;
//
//
//
//
//
// }
//
//
//






// [[Rcpp::export]]
NumericVector getSpeedLimitsMultiplierRoadsGaussianOfMass(XPtr< Grafo > delanuayGraph,double d0,double exponent){

  std::vector<double> speedLimitsMultiplier=RoadNetworkGeneration::getGaussianSpeedLimits(delanuayGraph,d0,exponent);


  return wrap(speedLimitsMultiplier);
}

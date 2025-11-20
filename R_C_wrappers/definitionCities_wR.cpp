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
#include "../SpatialAnalysis/SpatialAnalysis/Tree.h"
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
DataFrame initialMeasurements(XPtr<DualExtendedGraph> deg,NumericVector thresholds){
    
  std::vector<double> gammas;
  std::vector<double> epsilons;
  std::vector<double> Ns;
  std::vector<double> areas;
  std::vector<double> tsls;
  std::vector<double> Hs;
  std::vector<double> Has;
  std::vector<double> Nareas;
  
  std::vector<double> EFAs;
  std::vector<double> EFDs;
  std::vector<double> FCs;
  


  for(long i=0;i<thresholds.size();i++){

    double threshold=thresholds[i];
    std::cout<<"Threshold "<<threshold<<'\n';
    std::vector<long> colors;
    std::vector<long> sizes;

    DualExtendedGraph::metricPercolation(deg,threshold,colors,sizes);
    std::vector<long> indexes=Functions::getIndexesOfOrderedValues(sizes,false);
    std::vector<long> idsLinksLargestCluster;
    for(long j=0;j<colors.size();j++){
      if(colors[j]==indexes[0]){
        idsLinksLargestCluster.push_back(j);
      }
    }
    Grafo sg;
     Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(), &sg, idsLinksLargestCluster);
     Grafo boundary;
     GeometryGraph::createBoundaryGraph(&sg, &boundary, 0);
     Grafo G;
    // Grafo* boundary=new Grafo();
    // GeometryGraph::createBoundaryGraph(G, boundary, 0);
    GeometryGraph::getSubgraphWithinABoundary(deg->getPrimalGraph(), &boundary, &G);
    // std::cout<<G.nodes.size()<<" "<<G.links.size()<<'\n';
    // std::cout<<sizes[indexes[0]]<<" "<<indexes[0]<<'\n';

    double gamma=0;
    double epsilonA=INFINITY;
    double epsilon=INFINITY;
    double N=0;
    double maxRuns=1.0;
    // double finalFd=0;
    long depthlimit=15;
std::vector<double> possibleFds;
  double fd=0;
    for(long run=0;run<maxRuns;run++){
      std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep_mixScales(&G,10);
      // std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep_bug(&G,20);
      std::vector<double> x;
      std::vector<double> y;
      for(long j=0;j<std::get<0>(points).size();j++){
          // if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1||(std::get<1>(points)[std::get<0>(points).size()-2-j]==1&&std::get<1>(points)[std::get<0>(points).size()-1-j]!=1)){
            // std::cout<<std::get<0>(points).size()<<" "<<std::get<0>(points).size()-1-j<<" "<<std::get<1>(points)[std::get<0>(points).size()-1-j]<<'\n';
  //                if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1){
                x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
                y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
            // }
      }
      // std::cout<<x.size()<<'\n';
      Fxy f=Fxy::createFunction(x,y);
      Fxy::derivate(&f);
      // fd=INFINITY;
      // for(long j=0;j<f.x.size();j++){
      //     if(f.derivative[j]<fd){
      //         fd=f.derivative[j];
      //         if(exp(f.x[j])<epsilon){
      //           epsilon=exp(f.x[j]); 
      //           N=exp(f.y[j]); 

      //         }
              
      //     }
      // }

      fd=Functions::min(f.derivative);
      std::cout<<"fdTemp "<<fd<<'\n';
      gamma-=fd;
      possibleFds.push_back(-fd);
      for(long j=f.x.size()-1;j>=0;j--){
        if(f.derivative[j]==fd){
          // std::cout<<exp(f.x[j])<<'\n';
          if(exp(f.x[j])<epsilon){
            epsilon=exp(f.x[j]); 
            N=exp(f.y[j]); 
          }
          
          
        }
      }

      std::cout<<"epsilon A "<<epsilon<<" "<<N<<" "<<fd<<'\n';


      // fd=INFINITY;
      // epsilon=INFINITY;
      //   for(long j=0;j<f.x.size();j++){
      //       if(f.derivative[j]<fd){
      //           fd=f.derivative[j];
      //           if(fd==-gamma){
      //             std::cout<<exp(f.x[j])<<'\n';
      //           }
      //           if(exp(f.x[j])<epsilon){
      //             epsilon=exp(f.x[j]); 
      //             N=exp(f.y[j]); 

      //           }
                
      //       }
      //   }

      //    std::cout<<"epsilon B "<<epsilon<<" "<<N<<" "<<fd<<'\n';




    }


    gamma/=maxRuns;
    gamma=Functions::median(possibleFds);





    

    std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep(&G,15);
    std::vector<double> x;
    std::vector<double> y;
    for(long j=0;j<std::get<0>(points).size();j++){
        // if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1||(std::get<1>(points)[std::get<0>(points).size()-2-j]==1&&std::get<1>(points)[std::get<0>(points).size()-1-j]!=1)){
          // std::cout<<std::get<0>(points).size()<<" "<<std::get<0>(points).size()-1-j<<" "<<std::get<1>(points)[std::get<0>(points).size()-1-j]<<'\n';
//                if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1){
              x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
              y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
          // }
    }
    // std::cout<<x.size()<<'\n';
    Fxy f=Fxy::createFunction(x,y);
    Fxy::derivate(&f);
    double fd_final=INFINITY;
    std::vector<double> minRange,maxRange;
    for(long j=0;j<x.size();j++){
      if(x[j]<log(epsilon)){
        minRange.push_back(x[j]);
      }
      if(x[j]>log(epsilon)){
        maxRange.push_back(x[j]);
      }
    }
    double minRangeX=x[0];
    double maxRangeX=x[x.size()-1];
    if(minRange.size()>0){
        minRangeX=minRange[Functions::max(0,minRange.size()-2)];
    }
    if(maxRange.size()>0){
        maxRangeX=maxRange[Functions::min(maxRange.size()-1,1)];
    }
    std::vector<double> values;
    for(long j=0;j<f.x.size();j++){
      if(f.x[j]>=minRangeX&&f.x[j]<=maxRangeX){
        values.push_back(f.derivative[j]);
      }
    }
    fd_final=Functions::median(values);


            
    // fd=f.derivative[floor(double(f.derivative.size())/2.0)];
    // gamma-=fd;




    double minDif=INFINITY;
    for(long j=f.x.size()-1;j>=0;j--){
        if(Functions::abs(f.x[j]-log(epsilonA))<minDif){
          minDif=Functions::abs(f.x[j]-log(epsilonA));
           
              epsilon=exp(f.x[j]); 
              N=exp(f.y[j]); 

            
        }
    }
    // epsilon=exp(f.x[0]);
    // N=exp(f.y[0]);

















    // double depthLimit=0;
    // for(long j=0;j<x.size();j++){
    //   if(exp(x[j])<epsilon){
    //     depthLimit=x.size()-j+1;
    //   }
    // }
    // std::cout<<"depthlimit "<<depthLimit<<'\n';

    // for(double run=0;run<maxRuns;run++){
    //     // points.clear();
    //     points=FractalDimension::boxCountingPlaneSweep(&G,depthLimit);
    //     x.clear();
    //     y.clear();
    //     for(long j=0;j<std::get<0>(points).size();j++){
    //         x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
    //         y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
    //     }
    //     std::cout<<x.size()<<'\n';
    //     Fxy f=Fxy::createFunction(x,y);
    //     Fxy::derivate(&f);
    //     double fd=INFINITY;
    //     for(long j=0;j<f.x.size();j++){
    //         if(f.derivative[j]<fd){
    //             fd=f.derivative[j];
    //             if(exp(f.x[j])<epsilon){
    //               epsilon=exp(f.x[j]); 
    //               N=exp(f.y[j]); 

    //             }
                
    //         }
    //     }
    //     gamma-=fd;
    // }
    // gamma/=maxRuns;
    std::cout<<"gamma "<<gamma<<'\n';
    std::cout<<"epsilon "<<epsilon<<'\n';
    std::cout<<"N "<<N<<'\n';
    // std:::cout<<"gamma "<<gamma<<'\n';
    DualExtendedGraph degb;
    DualExtendedGraph::addPrimal(&degb,&G);
    std::vector<double> masses;
    Grafo* dual=degb.getDualGraph();
    double H=0;
    double Ha=0;
    double area=0;
    // std::cout<<dual->nodes.size()<<'\n';
    if(dual->nodes.size()>1){
      area=dual->nodes[0]->mass;
      masses.reserve(dual->nodes.size()-1);
      for(long j=1;j<dual->nodes.size();j++){
        masses.push_back(dual->nodes[j]->mass);
      }
       H=Entropy::calculateEntropy(masses);
       Ha=Entropy::calculateEntropyAreas(masses);
    }else if(dual->nodes.size()>0){
      area=dual->nodes[0]->mass;
    }
    double tsl=0;
    for(long j=0;j<G.links.size();j++){
      tsl+=G.links[j]->weight;
    }
    double Narea=masses.size();
    double EFA=area*pow(N,1.0-2.0/gamma);
    double EFD=pow(N,1.0-2.0/gamma);
    double FC=EFA/N;

    gammas.push_back(gamma);
    epsilons.push_back(epsilon);
    Ns.push_back(N);
    areas.push_back(area);
    tsls.push_back(tsl);
    Hs.push_back(H);
    Has.push_back(Ha);
    Nareas.push_back(Narea);
    EFAs.push_back(EFA);

    EFDs.push_back(EFD);
    FCs.push_back(FC);



  }









  List list(12);
  list[0]=thresholds;
  list[1]=gammas;
  list[2]=epsilons;
  list[3]=Ns;
  list[4]=areas;
  list[5]=tsls;
  list[6]=Hs;
  list[7]=Has;
  list[8]=Nareas;
  list[9]=EFAs;
  list[10]=EFDs;
  list[11]=FCs;

  CharacterVector namevec;
  namevec.push_back("threshold");
  namevec.push_back("gamma");
  namevec.push_back("epsilon");
  namevec.push_back("N");
  namevec.push_back("area");
  namevec.push_back("tsl");
  namevec.push_back("H");
  namevec.push_back("Ha");
  namevec.push_back("Nareas");
  namevec.push_back("EFA");
  namevec.push_back("EFD");
  namevec.push_back("FC");
  
  


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}




// [[Rcpp::export]]
DataFrame initialMeasurements_bug(XPtr<DualExtendedGraph> deg,std::vector<double> thresholds){
    
  std::vector<double> gammas;
  std::vector<double> epsilons;
  std::vector<double> Ns;
  std::vector<double> areas;
  std::vector<double> tsls;
  std::vector<double> Hs;
  std::vector<double> Has;
  std::vector<double> Nareas;
  
  std::vector<double> EFAs;
  std::vector<double> EFDs;
  std::vector<double> FCs;
  


  for(long i=0;i<thresholds.size();i++){

    double threshold=thresholds[i];
    std::cout<<"Threshold "<<threshold<<'\n';
    std::vector<long> colors;
    std::vector<long> sizes;

    DualExtendedGraph::metricPercolation(deg,threshold,colors,sizes);
    std::vector<long> indexes=Functions::getIndexesOfOrderedValues(sizes,false);
    std::vector<long> idsLinksLargestCluster;
    for(long j=0;j<colors.size();j++){
      if(colors[j]==indexes[0]){
        idsLinksLargestCluster.push_back(j);
      }
    }
    Grafo sg;
     Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(), &sg, idsLinksLargestCluster);
     Grafo boundary;
     GeometryGraph::createBoundaryGraph(&sg, &boundary, 0);
     Grafo G;
    // Grafo* boundary=new Grafo();
    // GeometryGraph::createBoundaryGraph(G, boundary, 0);
    GeometryGraph::getSubgraphWithinABoundary(deg->getPrimalGraph(), &boundary, &G);
    std::cout<<G.nodes.size()<<" "<<G.links.size()<<'\n';
    std::cout<<sizes[indexes[0]]<<" "<<indexes[0]<<'\n';

    double gamma=0;
    double epsilon=INFINITY;
    double N=0;
    double maxRuns=10.0;
    // double finalFd=0;
    for(double run=0;run<maxRuns;run++){
        std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep_bug(&G,20);
        std::vector<double> x;
        std::vector<double> y;
        for(long j=0;j<std::get<0>(points).size();j++){
            x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
            y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
        }
        std::cout<<x.size()<<'\n';
        Fxy f=Fxy::createFunction(x,y);
        Fxy::derivate(&f);
        double fd=INFINITY;
        for(long j=0;j<f.x.size();j++){
            if(f.derivative[j]<fd){
                fd=f.derivative[j];
                if(exp(f.x[j])<epsilon){
                  epsilon=exp(f.x[j]); 
                  N=exp(f.y[j]); 

                }
                
            }
        }
        gamma-=fd;
    }
    gamma/=maxRuns;
    std::cout<<"gamma "<<gamma<<'\n';
    std::cout<<"epsilon "<<epsilon<<'\n';
    std::cout<<"N "<<N<<'\n';
    // std:::cout<<"gamma "<<gamma<<'\n';
    DualExtendedGraph degb;
    DualExtendedGraph::addPrimal(&degb,&G);
    std::vector<double> masses;
    Grafo* dual=degb.getDualGraph();
    double H=0;
    double Ha=0;
    double area=0;
    std::cout<<dual->nodes.size()<<'\n';
    if(dual->nodes.size()>1){
      area=dual->nodes[0]->mass;
      masses.reserve(dual->nodes.size()-1);
      for(long j=1;j<dual->nodes.size();j++){
        masses.push_back(dual->nodes[j]->mass);
      }
       H=Entropy::calculateEntropy(masses);
       Ha=Entropy::calculateEntropyAreas(masses);
    }else if(dual->nodes.size()>0){
      area=dual->nodes[0]->mass;
    }
    double tsl=0;
    for(long j=0;j<G.links.size();j++){
      tsl+=G.links[j]->weight;
    }
    double Narea=masses.size();
    double EFA=area*pow(N,1.0-2.0/gamma);
    double EFD=pow(N,1.0-2.0/gamma);
    double FC=EFA/N;

    gammas.push_back(gamma);
    epsilons.push_back(epsilon);
    Ns.push_back(N);
    areas.push_back(area);
    tsls.push_back(tsl);
    Hs.push_back(H);
    Has.push_back(Ha);
    Nareas.push_back(Narea);
    EFAs.push_back(EFA);

    EFDs.push_back(EFD);
    FCs.push_back(FC);



  }









  List list(12);
  list[0]=thresholds;
  list[1]=gammas;
  list[2]=epsilons;
  list[3]=Ns;
  list[4]=areas;
  list[5]=tsls;
  list[6]=Hs;
  list[7]=Has;
  list[8]=Nareas;
  list[9]=EFAs;
  list[10]=EFDs;
  list[11]=FCs;

  CharacterVector namevec;
  namevec.push_back("threshold");
  namevec.push_back("gamma");
  namevec.push_back("epsilon");
  namevec.push_back("N");
  namevec.push_back("area");
  namevec.push_back("tsl");
  namevec.push_back("H");
  namevec.push_back("Ha");
  namevec.push_back("Nareas");
  namevec.push_back("EFA");
  namevec.push_back("EFD");
  namevec.push_back("FC");
  
  


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}






















// [[Rcpp::export]]
NumericVector massNodesInADistance(XPtr<Grafo> G){

  // SparseMatrix matrix;
  // double width=1000;
  // std::tuple<std::vector<double>, std::vector<double> > points=Grafo::getPointsEvenBreaks(G,5);
  // for(long i=0;i<std::get<0>(points).size();i++){
  //   double x=floor(std::get<0>(points)[i]/width);
  //   double y=floor(std::get<1>(points)[i]/width);
  //   matrix.increase(x,y);
  // }
  // double maxDistance=5000;
  // std::vector<double> values;
  // values.resize(G->nodes.size(),0);
  // for(long i=0;i<G->nodes.size();i++){
  //   double col=floor(G->nodes[i]->location.x/width);
  //   double row=floor(G->nodes[i]->location.y/width);
  //   for(auto it:matrix.cells){
  //     Point2d point=it.first;
  //     double value=it.second.value;
  //     double distance=Functions::getDistance(Point2d(col,row),point);
  //     values[i]+=value*(exp(-distance));

  //   }
  //   // for(long d=0;d<maxDistance;d+=100){

  //   // }
  // }
  // return wrap(values);



// SparseMatrix matrix;
//   double width=1000;
//   std::tuple<std::vector<double>, std::vector<double> > points=Grafo::getPointsEvenBreaks(G,5);
//   for(long i=0;i<std::get<0>(points).size();i++){
//     double x=floor(std::get<0>(points)[i]/width);
//     double y=floor(std::get<1>(points)[i]/width);
//     matrix.increase(x,y);
//   }
  // double maxDistance=5000;
  std::vector<double> values;
  values.resize(G->nodes.size(),0);
  std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    double distanceLimit=3000;
  for(long i=0;i<G->nodes.size();i++){

    // for (long i=startNode; i<endNode; i++)
    // {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY){
                    values[i]+=1/(1+pow(distance/1000,4));
                    // distances[i]+=distance*G->nodes[id]->mass;
                }
            }
        }


    //    ID.reset();
        
    // }
    
    // double col=floor(G->nodes[i]->location.x/width);
    // double row=floor(G->nodes[i]->location.y/width);
    // for(auto it:matrix.cells){
    //   Point2d point=it.first;
    //   double value=it.second.value;
    //   double distance=Functions::getDistance(Point2d(col,row),point);
    //   values[i]+=value*(exp(-distance));

    // }
    // for(long d=0;d<maxDistance;d+=100){

    // }
  }
  Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  return wrap(values);

}

// [[Rcpp::export]]
NumericVector massStreetsInADistance(XPtr<Grafo> G){
  double distanceLimit=3000;
  std::vector<double> values;
  values.resize(G->nodes.size(),0);
  std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;

    double breakEach=10;
    // double distanceLimit=3000;
  // for(long i=0;i<G->nodes.size();i++){

    // for (long i=startNode; i<endNode; i++)
    // {
        // if(G->nodes[i]->mass>0){
    // std::vector<long> idNodes;
    // std::vector<double> fds;
    // fds.resize(idEndNode-idStartNode,0);

    for(long i=0;i<G->nodes.size();i++){
        Nodo* node=G->nodes[i];
    
        std::vector<double> xs;
        std::vector<double> ys;
        // std::vector<double> gridSizes;
        for(long j=0;j<ceil(log(distanceLimit));j++){
            xs.push_back(exp(j));
        }
        ys.resize(xs.size(),0);

        double distanceLimit_temp=distanceLimit;
        for(long j=0;j<G->nodes[i]->links.size();j++){
            if(G->nodes[i]->links[j]->weight>distanceLimit_temp){
                distanceLimit_temp=G->nodes[i]->links[j]->weight+1;
            }
        }
        Grafo::calculateDijkstra(G,node,ID,distanceLimit_temp,numbersRepresentingNodes,inDijkstra,inCutoff);
        Grafo sg;

        Grafo::inducedSubgraph(G,&sg,ID.idsInCutoff);
        for(long j=0;j<sg.links.size();j++){
            long idA=G->getNodeByLocation(sg.links[j]->A()->location)->id;
            long idB=G->getNodeByLocation(sg.links[j]->B()->location)->id;
            double distanceA=ID.getMinDistance(idA);
            double distanceB=ID.getMinDistance(idB);
            if(distanceA>distanceB){
                std::swap(distanceA,distanceB);
                std::swap(idA,idB);
            }
            // double dx=G->nodes[idB]->location.x-G->nodes[idA]->location.x;
            // double dy=G->nodes[idB]->location.y-G->nodes[idA]->location.y;
            double distanceTemp=Functions::getDistance(G->nodes[idA]->location,G->nodes[idB]->location);
            double counter=0.0;
            double distanceTT=breakEach*counter;
            while(distanceTT<distanceTemp){
                double distanceFromNode=Functions::min(ID.getMinDistance(idA)+distanceTT,ID.getMinDistance(idB)-distanceTT+distanceTemp);
                if(distanceFromNode<distanceLimit){
                    // ys[ceil(log(distanceFromNode+1))]++;
                // }
                  values[i]+=breakEach/(1.0+pow(distanceFromNode/(distanceLimit/3.0),4));
                }
                counter+=1.0;
                distanceTT=breakEach*counter;
            }

        }
        ID.reset();
        // for(long j=0;j<ys.size()-1;j++){
        //     ys[j+1]+=ys[j];
        // }

        // LinearRegression lr=LinearRegression::compute(xs,ys,true);
        // double slope=lr.slope;
        //   if(!isfinite(slope)){
        //     slope=1;
        //   }
        // values[i]=slope;
    }
            // std::swap(idNodes,ID.idsInCutoff);
            // for(long j=0;j<ID.idsInCutoff.size();j++){
            //     double id=ID.idsInCutoff[j];
            //     double distance=ID.getMinDistance(id);
            //     if(distance<INFINITY){
            //         values[i]+=1/(1+pow(distance/1000,4));
            //         // distances[i]+=distance*G->nodes[id]->mass;
            //     }
            // }
        // }


    //    ID.reset();
        
    // }
    
    // double col=floor(G->nodes[i]->location.x/width);
    // double row=floor(G->nodes[i]->location.y/width);
    // for(auto it:matrix.cells){
    //   Point2d point=it.first;
    //   double value=it.second.value;
    //   double distance=Functions::getDistance(Point2d(col,row),point);
    //   values[i]+=value*(exp(-distance));

    // }
    // for(long d=0;d<maxDistance;d+=100){

    // }
  // }
  Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  return wrap(values);

}




// [[Rcpp::export]]
NumericVector getSandBoxDimensionOfSingleNodes(XPtr<Grafo> G){
  return wrap(FractalDimension::sandBox_severalNodes(G,0,G->nodes.size()));
}


// // [[Rcpp::export]]
// NumericVector getSandBoxDimensionOfSingleNodes_explicit(XPtr<Grafo> G,long idStart,long idEnd){
//   return wrap(FractalDimension::sandBox_severalNodes(G,idStart,idEnd,1000));
// }

  

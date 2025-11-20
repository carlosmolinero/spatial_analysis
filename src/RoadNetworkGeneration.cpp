//
//  RoadNetworkGeneration.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 14/03/2017.
//  Copyright (c) 2017 Carlos Molinero. All rights reserved.
//

#include "RoadNetworkGeneration.h"


// void Network::saveOriginalPositions(Graph* graph){
//     originalPositions.clear();
//     for(long i=0;i<graph->nodes.size();i++){
//         originalPositions.push_back(graph->nodes[i].location);
//     }
// }
// void Network::resetPositions(Graph* graph){
//     for(long i=0;i<graph->nodes.size();i++){
//         graph->nodes[i].location=originalPositions[i];
//     }
// }




void RoadNetworkGeneration::straightenGraph(Grafo* graph,double increment,long numberTimes,std::vector<double>& edgeFlows){
  std::vector<Point2d> originalPositions;
  originalPositions.clear();
  for(long i=0;i<graph->nodes.size();i++){
      originalPositions.push_back(graph->nodes[i]->location);
  }

    // double increment=5;

    for(long rep=0;rep<numberTimes;++rep){
    for(long i=0;i<graph->nodes.size();i++){
      double maxFlow=0;
        if(graph->nodes[i]->mass<1){
          // for(long j=0;j<graph->nodes[i]->links.size();j++){
          //     // double angle=Functions::getAngleRadians(graph->nodes[i]->location,graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location);
          //     // double weight=1.0;
          //     // double weight=edgeFlows[graph->nodes[i]->links[j]->id]*graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->links.size()/graph->nodes[i]->links.size();
          //     // std::cout<<"weight in roadnetworkgeneration straightengraph "<<weight<<'\n';
          //     Point2d a=graph->nodes[i]->location;
          //     Point2d b=graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location;
          //
          //     Point2d vector;
          //     double module=Functions::getDistance(a,b)+.001;
          //     double incrementTemp=module*(1.0+increment/5.0);
          //     vector.x=(b.x-a.x)/(module)*incrementTemp;
          //     vector.y=(b.y-a.y)/(module)*incrementTemp;
          //     graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location.x=a.x+vector.x;
          //     graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location.y=a.y+vector.y;
          //     // centroid.x+=graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location.x*weight;
          //     // centroid.y+=graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location.y*weight;
          //     // totalWeight+=weight;
          // }
            Point2d centroid(0,0);
            double totalWeight=0;
            for(long j=0;j<graph->nodes[i]->links.size();j++){
                // double weight=edgeFlows[graph->nodes[i]->links[j]->id]*graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->links.size()/graph->nodes[i]->links.size();
                // double weight=edgeFlows[graph->nodes[i]->links[j]->id]*(graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->getDegree());
                if(edgeFlows[graph->nodes[i]->links[j]->id]>maxFlow){
                  maxFlow=edgeFlows[graph->nodes[i]->links[j]->id];
                }
                double weight=edgeFlows[graph->nodes[i]->links[j]->id];
                // std::cout<<"weight in roadnetworkgeneration straightengraph "<<weight<<'\n';
                centroid.x+=graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location.x*weight;
                centroid.y+=graph->nodes[i]->links[j]->getOtherNode(graph->nodes[i])->location.y*weight;
                totalWeight+=weight;
            }
            // centroid.x/=(double)(graph->nodes[i]->links.size());
            // centroid.y/=(double)(graph->nodes[i]->links.size());
            centroid.x/=totalWeight;
            centroid.y/=totalWeight;
            Point2d vector;
            double module=Functions::getDistance(centroid, graph->nodes[i]->location);
            // double moduleFromPrevLocation=(Functions::getDistance(originalPositions[i], graph->nodes[i]->location)+1.0)/(log(maxFlow+1)+1);
            double moduleFromPrevLocation=(Functions::getDistance(originalPositions[i], graph->nodes[i]->location)+1.0);
            double incrementTemp=increment;
            // vector.x=(centroid.x-graph->nodes[i]->location.x)/(module)*incrementTemp/moduleFromPrevLocation/moduleFromPrevLocation;
            // vector.y=(centroid.y-graph->nodes[i]->location.y)/(module)*incrementTemp/moduleFromPrevLocation/moduleFromPrevLocation;
            vector.x=(centroid.x-graph->nodes[i]->location.x)/(module)*incrementTemp/moduleFromPrevLocation/moduleFromPrevLocation;
            vector.y=(centroid.y-graph->nodes[i]->location.y)/(module)*incrementTemp/moduleFromPrevLocation/moduleFromPrevLocation;
            Point2d newLocation;
            newLocation.x=graph->nodes[i]->location.x+vector.x;
            newLocation.y=graph->nodes[i]->location.y+vector.y;


            graph->nodes[i]->location=newLocation;



        }
    }
  }
}


void RoadNetworkGeneration::getDelanuayGraphFromCities(std::tuple<std::vector<double>, std::vector<double>,std::vector<double> > x_y_mass_ofCities,Grafo* result,long numberDummyNodes){
  std::vector<long> id;
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> mass;
  long n_cities=std::get<0>(x_y_mass_ofCities).size();
  double xSize;
  double ySize;
  double xMin=INFINITY;
  double yMin=INFINITY;
  double xMax=-INFINITY;
  double yMax=-INFINITY;

  for(long i=0;i<n_cities;i++){
    if(xMin>std::get<0>(x_y_mass_ofCities)[i]){
      xMin=std::get<0>(x_y_mass_ofCities)[i];
    }
    if(yMin>std::get<1>(x_y_mass_ofCities)[i]){
      yMin=std::get<1>(x_y_mass_ofCities)[i];
    }
    if(xMax<std::get<0>(x_y_mass_ofCities)[i]){
      xMax=std::get<0>(x_y_mass_ofCities)[i];
    }
    if(yMax<std::get<1>(x_y_mass_ofCities)[i]){
      yMax=std::get<1>(x_y_mass_ofCities)[i];
    }
  }
  xSize=xMax-xMin;
  ySize=yMax-yMin;
  // std::cout<<xMin<<" "<<xMax<<","<<yMin<<" "<<yMax<<'\n';
  // long n_tempNodes=10000.0/65000.0/65000.0*xSize*ySize*(.1+spatialQuality_0_1*1.9)+n_cities;//10000
  long n_tempNodes=numberDummyNodes;
  // std::cout<<n_tempNodes<<" "<<n_cities<<'\n';
  id.reserve(n_cities+n_tempNodes);
  x.reserve(n_cities+n_tempNodes);
  y.reserve(n_cities+n_tempNodes);
  mass.reserve(n_cities+n_tempNodes);
  for(long i=0;i<n_cities;i++){
      id.push_back(i);
      x.push_back(std::get<0>(x_y_mass_ofCities)[i]);
      y.push_back(std::get<1>(x_y_mass_ofCities)[i]);
      mass.push_back(std::get<2>(x_y_mass_ofCities)[i]);
  }
  // cities$mass=massInitMax*cities$id^-1
  for(long i=0;i<n_tempNodes;i++){
      id.push_back(i+n_cities);
      x.push_back(Functions::runiform(xMin,xMax));
      y.push_back(Functions::runiform(yMin,yMax));
      mass.push_back(0);
  }
  // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
  // tempNodes$mass=0
  // nodes=rbind(cities,tempNodes)
  // nodes$id=1:nrow(nodes)-1
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
  std::vector<long> linksRemoved;

  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
  Grafo delanuayGraph;
  Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
  Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
  coords=Grafo::getCoordinates(&delanuayGraph);





  // delanuay$inCity=0
  std::vector<bool> inCity;
  inCity.resize(std::get<0>(delaunay).size(),false);
  std::vector<double> radii;
  radii.resize(n_cities,0);
  std::vector<double> speedLimits;
  std::vector<double> multiplierRivers;
  multiplierRivers.resize(std::get<0>(delaunay).size(),1);
  speedLimits.resize(std::get<0>(delaunay).size(),90);

  for(long i=0;i<n_cities;i++){
      radii[i]=sqrt((mass[i]/3.1415));
      for(long j=0;j<std::get<0>(delaunay).size();j++){
          double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
          double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
          if(distance1<=radii[i]&&distance2<=radii[i]){
              inCity[j]=true;
              speedLimits[j]=50;
          }
      }

  }


  // DualExtendedGraph::create(&deg,delaunay,coords,false);

  // Grafo G;
  Grafo::create(result,delaunay,coords,mass,false);

}
void RoadNetworkGeneration::createRoadNetworkFromCities(std::tuple<std::vector<double>, std::vector<double>,std::vector<double> > x_y_mass_ofCities,Grafo* result,double alpha,double d0,long numberDummyNodes){
  std::vector<long> id;
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> mass;
  long n_cities=std::get<0>(x_y_mass_ofCities).size();
  double xSize;
  double ySize;
  double xMin=INFINITY;
  double yMin=INFINITY;
  double xMax=-INFINITY;
  double yMax=-INFINITY;

  for(long i=0;i<n_cities;i++){
    if(xMin>std::get<0>(x_y_mass_ofCities)[i]){
      xMin=std::get<0>(x_y_mass_ofCities)[i];
    }
    if(yMin>std::get<1>(x_y_mass_ofCities)[i]){
      yMin=std::get<1>(x_y_mass_ofCities)[i];
    }
    if(xMax<std::get<0>(x_y_mass_ofCities)[i]){
      xMax=std::get<0>(x_y_mass_ofCities)[i];
    }
    if(yMax<std::get<1>(x_y_mass_ofCities)[i]){
      yMax=std::get<1>(x_y_mass_ofCities)[i];
    }
  }
  xSize=xMax-xMin;
  ySize=yMax-yMin;
  // std::cout<<xMin<<" "<<xMax<<","<<yMin<<" "<<yMax<<'\n';
  // long n_tempNodes=10000.0/65000.0/65000.0*xSize*ySize*(.1+spatialQuality_0_1*1.9)+n_cities;//10000
  long n_tempNodes=numberDummyNodes;
  // std::cout<<n_tempNodes<<" "<<n_cities<<'\n';
  id.reserve(n_cities+n_tempNodes);
  x.reserve(n_cities+n_tempNodes);
  y.reserve(n_cities+n_tempNodes);
  mass.reserve(n_cities+n_tempNodes);
  for(long i=0;i<n_cities;i++){
      id.push_back(i);
      x.push_back(std::get<0>(x_y_mass_ofCities)[i]);
      y.push_back(std::get<1>(x_y_mass_ofCities)[i]);
      mass.push_back(std::get<2>(x_y_mass_ofCities)[i]);
  }
  // cities$mass=massInitMax*cities$id^-1
  for(long i=0;i<n_tempNodes;i++){
      id.push_back(i+n_cities);
      x.push_back(Functions::runiform(xMin,xMax));
      y.push_back(Functions::runiform(yMin,yMax));
      mass.push_back(0);
  }
  // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
  // tempNodes$mass=0
  // nodes=rbind(cities,tempNodes)
  // nodes$id=1:nrow(nodes)-1
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
  std::vector<long> linksRemoved;

  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
  Grafo delanuayGraph;
  Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
  Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
  coords=Grafo::getCoordinates(&delanuayGraph);





  // delanuay$inCity=0
  std::vector<bool> inCity;
  inCity.resize(std::get<0>(delaunay).size(),false);
  std::vector<double> radii;
  radii.resize(n_cities,0);
  std::vector<double> speedLimits;
  std::vector<long> idsEdgesCities;
  std::vector<double> multiplierRivers;
  multiplierRivers.resize(std::get<0>(delaunay).size(),1);
  speedLimits.resize(std::get<0>(delaunay).size(),1);
  idsEdgesCities.resize(std::get<0>(delaunay).size(),-1);

  // for(long i=0;i<n_cities;i++){
  //     radii[i]=sqrt((mass[i]/3.1415));
  //     for(long j=0;j<std::get<0>(delaunay).size();j++){
  //         double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
  //         double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
  //         if(distance1<=radii[i]&&distance2<=radii[i]){
  //             inCity[j]=true;
  //             speedLimits[j]=50;
  //         }
  //     }
  //
  // }


  // DualExtendedGraph::create(&deg,delaunay,coords,false);

  Grafo G;
  Grafo::create(&G,delaunay,coords,mass,false);
  RoadNetworkGeneration::createRoadNetwork(&G,result,speedLimits,idsEdgesCities,1.0,multiplierRivers,alpha,d0);
  std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
  Grafo::forcePlanarityPlaneSweep(result, Grafo::SPEED, pairsOldIdNewIds, false);

}

// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>,std::vector<double>   >  RoadNetworkGeneration::experiments_optimizeAlpha(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//     long n_cities=44;
//     long n_tempNodes=10000.0+n_cities;//10000
//     double xSize=65000;
//     double ySize=65000;
//     double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(massInitMax*pow((i+1),-.89));
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//     speedLimits.resize(std::get<0>(delaunay).size(),90);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=50;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > robustnessLengths;
//      std::vector<double > robustnessNumLinks;
//     std::vector<double > timeDistancesFromNodes;
//     std::vector<double> tsl;
//
//
//     std::vector<double> alphas;
//     for(double i=0.05;i<=1.04;i+=.05){
//         alphas.push_back(i);
//     }
//     tsl.resize(alphas.size(),0);
//     timeDistancesFromNodes.resize(alphas.size(),0);
//     robustnessLengths.resize(alphas.size(),0);
//     robustnessNumLinks.resize(alphas.size(),0);
//     std::vector<double> numIntersections;
//     numIntersections.resize(alphas.size(),0);
//     std::vector<double> flowPerMeter;
//     std::vector<double> intersectionsPerMeter;
//     flowPerMeter.resize(alphas.size(),0);
//     intersectionsPerMeter.resize(alphas.size(),0);
//
//     std::vector<double> numberOfTripsGenerated;
//     numberOfTripsGenerated.resize(alphas.size(),0);
//     std::vector<double> numLinks;
//     numLinks.resize(alphas.size(),0);
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         Grafo roads;
//         Grafo roadsT;
//
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//         std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
//         Grafo::forcePlanarityPlaneSweep(&roadsT, Grafo::SPEED, pairsOldIdNewIds, false);
//         std::vector<std::pair<std::vector<long>, long> > pairsOldNewB;
//         Grafo::removeNonStructuralNodes(&roadsT, &roads, pairsOldNewB, false);
//
//         for(long j=0;j<roads.links.size();j++){
//             tsl[i]+=roads.links[j]->weight;
//         }
// //        for(long j=0;j<roads.nodes.size();j++){
// //            if(roads.nodes[j]->getDegree()>2){
//                 numIntersections[i]=roads.nodes.size();
//         numLinks[i]=roads.links.size();
// //            }
// //        }
//         DualExtendedGraph deg;
//         DualExtendedGraph::addPrimal(&deg,&roads);
//         DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
//
//         std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(deg.getStructuralGraph());
//         robustnessLengths[i]=robustness.first;
//         robustnessNumLinks[i]=robustness.second;
//         // calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta);
//
//         std::vector<double> edgeFlows;
//         double numberTripsGenerated;
//         std::vector<double> timeDistancesFromNodes_=SpatialInteraction::calculateTotalTimesTravelledFromEachNode(&deg,speedLimits,capacityLink,alpha_congestion,beta_congestion,time,edgeFlows,numberTripsGenerated);
//         numberOfTripsGenerated[i]=numberTripsGenerated;
//         std::cout<<"numberTripsGenerated "<<numberTripsGenerated<<'\n';
//         std::vector<double> flowPerMeter_;
//         std::vector<double> intersectionsPerMeter_;
//         SpatialInteraction::calculateFlowPerMeterAndIntersectionsPerMeter(deg.getStructuralGraph(),0,edgeFlows,flowPerMeter_,intersectionsPerMeter_);
//
//         for(long j=0;j<timeDistancesFromNodes_.size();j++){
//             timeDistancesFromNodes[i]+=timeDistancesFromNodes_[j];
//         }
//         for(long j=0;j<flowPerMeter_.size();j++){
//             flowPerMeter[i]+=flowPerMeter_[j];
//             intersectionsPerMeter[i]+=intersectionsPerMeter_[j];
//         }
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>,std::vector<double>  > results;
//     results=std::make_tuple(alphas,robustnessLengths,robustnessNumLinks,timeDistancesFromNodes,tsl,numIntersections,flowPerMeter,intersectionsPerMeter,numberOfTripsGenerated,numLinks);
//
//     return results;
//
//
//
//
// }
//
//
//
// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>   >   RoadNetworkGeneration::experiments_calculateFlows(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//     long n_cities=44;
//     long n_tempNodes=10000.0+n_cities;//10000
//     double xSize=65000;
//     double ySize=65000;
//     double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(massInitMax*pow((i+1),-.89));
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//     speedLimits.resize(std::get<0>(delaunay).size(),90);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=50;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > realBetAv;
//      std::vector<double > realBetTot;
//     std::vector<double > betAv;
//     std::vector<double> betSD;
//     std::vector<double> realNumLinks;
//     std::vector<double> betTot;
//     std::vector<double> betEntr;
//     std::vector<double> realNumIntersections;
//     std::vector<double> realBetEntr;
//     std::vector<double> numIntersections;
//     std::vector<double> numLinks;
//
//     std::vector<double> alphas;
//     for(double i=0.05;i<=1.04;i+=.05){
//         alphas.push_back(i);
//     }
//     betSD.resize(alphas.size(),0);
//     betAv.resize(alphas.size(),0);
//     realBetAv.resize(alphas.size(),0);
//     realBetTot.resize(alphas.size(),0);
//
//     realNumLinks.resize(alphas.size(),0);
//     betTot.resize(alphas.size(),0);
//     betEntr.resize(alphas.size(),0);
//     realNumIntersections.resize(alphas.size(),0);
//     numIntersections.resize(alphas.size(),0);
//     numLinks.resize(alphas.size(),0);
//     realBetEntr.resize(alphas.size(),0);
//     // std::vector<double> numIntersections;
//     // numIntersections.resize(alphas.size(),0);
//     // std::vector<double> flowPerMeter;
//     // std::vector<double> intersectionsPerMeter;
//     // flowPerMeter.resize(alphas.size(),0);
//     // intersectionsPerMeter.resize(alphas.size(),0);
//
//     // std::vector<double> numberOfTripsGenerated;
//     // numberOfTripsGenerated.resize(alphas.size(),0);
//     // std::vector<double> numLinks;
//     // numLinks.resize(alphas.size(),0);
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         Grafo roads;
//         Grafo roadsT;
//
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//         std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
//         Grafo::forcePlanarityPlaneSweep(&roadsT, Grafo::SPEED, pairsOldIdNewIds, false);
//         std::vector<std::pair<std::vector<long>, long> > pairsOldNewB;
//         Grafo::removeNonStructuralNodes(&roadsT, &roads, pairsOldNewB, false);
//
//         // for(long j=0;j<roads.links.size();j++){
//         //     tsl[i]+=roads.links[j]->weight;
//         // }
// //        for(long j=0;j<roads.nodes.size();j++){
// //            if(roads.nodes[j]->getDegree()>2){
//                 // numIntersections[i]=roads.nodes.size();
// //        numLinks[i]=roads.links.size();
// //            }
// //        }
//         // DualExtendedGraph deg;
//         // DualExtendedGraph::addPrimal(&deg,&roads);
//         // DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
//
//         // std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(deg.getStructuralGraph());
//         // robustnessLengths[i]=robustness.first;
//         // robustnessNumLinks[i]=robustness.second;
//         // calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta);
//
//         std::vector<double> realEdgeBetweenness;
//         std::vector<double> edgeBetweenness;
//
//         Grafo::calculateEdgeBetweenness(&roads,0,edgeBetweenness);
//
//         Distribution disBetweenness=Distribution::createDistribution(edgeBetweenness);
//         betSD[i]=Distribution::getMoment(&disBetweenness,2);
//
//         betEntr[i]=Entropy::calculateEntropy(edgeBetweenness);
//         double totalLength=0;
//          for(long j=0;j<edgeBetweenness.size();j++){
//              betTot[i]+=edgeBetweenness[j]*roads.links[j]->weight;
//              totalLength+=roads.links[j]->weight;
//
//          }
//          betAv[i]=betTot[i]/totalLength;
//
//          numLinks[i]=(double)(roads.links.size());
//          numIntersections[i]=(double)(roads.nodes.size());
//
//
//
// //         for(long j=0;j<roadsT.nodes.size();j++){
// //            roadsT.nodes[j]->mass=1;
// //         }
// //         Grafo roadsSimple;
// //        Grafo::removeNonStructuralNodes(&roadsT, &roadsSimple, pairsOldNewB, false);
// //
// //  Grafo::calculateEdgeBetweenness(&roadsSimple,0,realEdgeBetweenness);
// //
// //        Distribution disBetweennessSimple=Distribution::createDistribution(realEdgeBetweenness);
// //        // betSD[i]=Distribution::getMoment(&disBetweenness,2);
// //
// //        realBetEntr[i]=Entropy::calculateEntropy(realEdgeBetweenness);
// //        totalLength=0;
// //         for(long j=0;j<realEdgeBetweenness.size();j++){
// //             realBetTot[i]+=realEdgeBetweenness[j]*roadsSimple.links[j]->weight;
// //             totalLength+=roadsSimple.links[j]->weight;
// //         }
// //         realBetAv[i]=realBetTot[i]/totalLength;
// //
// //         realNumLinks[i]=(double)(roadsSimple.links.size());
// //         realNumIntersections[i]=(double)(roadsSimple.nodes.size());
//
//
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>   > results;
//     results=std::make_tuple(alphas,realBetAv,realBetTot,realBetEntr,realNumLinks,realNumIntersections,betAv,betTot,betEntr,numLinks,numIntersections);
//
//     return results;
//
//
//
//
// }
//
//
//
//
//
//
//
//
//
//
// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double>    >   RoadNetworkGeneration::experiments_final(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//     long n_cities=44;
//     long n_tempNodes=10000.0+n_cities;//10000
//     double xSize=65000;
//     double ySize=65000;
//     double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(massInitMax*pow((i+1),-.89));
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//     speedLimits.resize(std::get<0>(delaunay).size(),90);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=50;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > robustnessLengths;
//      std::vector<double > robustnessNumLinks;
//     std::vector<double > betAv;
//     std::vector<double> tsl;
//     std::vector<double> sumDegreesComplexity;
//     std::vector<double> betTot;
//     std::vector<double> betEntr;
//     std::vector<double> numIntersections;
//     std::vector<double> sumDegrees;
//     std::vector<double> numIntersectionsDegLarger2;
//     std::vector<double> numLinks;
//     std::vector<double> entrAreas;
//     std::vector<double> closenessTot;
//     std::vector<double> closenessAvPerCity;
//     std::vector<double> closenessAvPerIntersection;
//     std::vector<double> closenessTotNoMass;
//     std::vector<double> closenessAvNoMass;
//     std::vector<double> numAreas;
//     std::vector<double> totalArea;
//
//
//     std::vector<double> alphas;
//     for(double i=0.05;i<=1.04;i+=.05){
//         alphas.push_back(i);
//     }
//     tsl.resize(alphas.size(),0);
//     betAv.resize(alphas.size(),0);
//     robustnessLengths.resize(alphas.size(),0);
//     robustnessNumLinks.resize(alphas.size(),0);
//
//     sumDegreesComplexity.resize(alphas.size(),0);
//     betTot.resize(alphas.size(),0);
//     betEntr.resize(alphas.size(),0);
//     numIntersections.resize(alphas.size(),0);
//     numIntersectionsDegLarger2.resize(alphas.size(),0);
//     numLinks.resize(alphas.size(),0);
//     sumDegrees.resize(alphas.size(),0);
//     entrAreas.resize(alphas.size(),0);
//     closenessTot.resize(alphas.size(),0);
//     closenessAvPerCity.resize(alphas.size(),0);
//     closenessAvPerIntersection.resize(alphas.size(),0);
//     closenessTotNoMass.resize(alphas.size(),0);
//     closenessAvNoMass.resize(alphas.size(),0);
//     numAreas.resize(alphas.size(),0);
//     totalArea.resize(alphas.size(),0);
//     // std::vector<double> numIntersections;
//     // numIntersections.resize(alphas.size(),0);
//     // std::vector<double> flowPerMeter;
//     // std::vector<double> intersectionsPerMeter;
//     // flowPerMeter.resize(alphas.size(),0);
//     // intersectionsPerMeter.resize(alphas.size(),0);
//
//     // std::vector<double> numberOfTripsGenerated;
//     // numberOfTripsGenerated.resize(alphas.size(),0);
//     // std::vector<double> numLinks;
//     // numLinks.resize(alphas.size(),0);
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         Grafo roads;
//         Grafo roadsT;
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//         std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
//         Grafo::forcePlanarityPlaneSweep(&roadsT, Grafo::SPEED, pairsOldIdNewIds, false);
//         std::vector<std::pair<std::vector<long>, long> > pairsOldNewB;
//         Grafo::removeNonStructuralNodes(&roadsT, &roads, pairsOldNewB, false);
//
//
//
//
//
//
//
//
//
//
//
//
//        for(long j=0;j<roads.nodes.size();j++){
//            if(roads.nodes[j]->getDegree()>2){
//                 numIntersectionsDegLarger2[i]++;
// //                if(roads.nodes[j]->mass<=1){
//
// //                }
//
//            }
//             numIntersections[i]++;
// //           if(roads.nodes[j]->getDegree()!=2){
// ////                numIntersectionsDegDif2[i]++;
// //                if(roads.nodes[j]->mass<=1){
// //                    numIntersectionsDegDif2NotCity[i]++;
// //                }
// //
// //           }
//            sumDegrees[i]+=roads.nodes[j]->getDegree();
// //           if(roads.nodes[j]->mass<=1){
//                sumDegreesComplexity[i]+=roads.nodes[j]->getDegree()*(roads.nodes[j]->getDegree()-1)/2;
// //           }
//        }
// //        for(long j=0;j<roads.links.size();j++){
// //            sumDegreesPerMeter[i]+=2*floor(roads.links[j]->weight);
// //            sumDegreesPerMeterNotCity[i]+=2*floor(roads.links[j]->weight);
// //        }
//         DualExtendedGraph deg;
//         DualExtendedGraph::addPrimal(&deg,&roads);
//         DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
//
//
//
//         std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(deg.getStructuralGraph());
//         robustnessLengths[i]=robustness.first;
//         robustnessNumLinks[i]=robustness.second;
//
//
//
//
//
//
//         std::vector<double> edgeBetweenness;
//
//         Grafo::calculateEdgeBetweenness(&roads,0,edgeBetweenness);
//
//         std::vector<double> closenessVector;
//
//         Grafo::calculateCloseness(&roads,0,closenessVector);
//
//         Distribution disBetweenness=Distribution::createDistribution(edgeBetweenness);
// //        betSD[i]=Distribution::getMoment(&disBetweenness,2);
//
//         DualExtendedGraph deg2;
//         DualExtendedGraph::addPrimal(&deg2,&roadsT);
//         DualExtendedGraph::setPrimalAsStructuralGraph(&deg2);
//
//         betEntr[i]=Entropy::calculateEntropy(edgeBetweenness);
//         Grafo* dual=deg2.getDualGraph();
//         std::vector<double> masses;
//         if(dual->nodes.size()>1){
//             for(long j=1;j<dual->nodes.size();j++){
//                 masses.push_back(dual->nodes[j]->mass);
//             }
//             totalArea[i]=dual->nodes[0]->mass;
//             entrAreas[i]=Entropy::calculateEntropyAreas(masses);
//             numAreas[i]=masses.size();
//         }else{
//             totalArea[i]=0;
//             entrAreas[i]=0;
//             numAreas[i]=0;
//         }
//
//         double totalLength=0;
//          for(long j=0;j<edgeBetweenness.size();j++){
//              betTot[i]+=edgeBetweenness[j]*roads.links[j]->weight;
//              totalLength+=roads.links[j]->weight;
//
//          }
//          betAv[i]=betTot[i]/totalLength;
//          tsl[i]=totalLength;
//          double totalPop=0;
//          for(long j=0;j<roads.nodes.size();j++){
//             totalPop+=roads.nodes[j]->mass;
//          }
//          double numberCities=0;
//          for(long j=0;j<closenessVector.size();j++){
//             if(roads.nodes[j]->mass>1){
//                  closenessTot[i]+=closenessVector[j];
//                  closenessAvPerIntersection[i]+=closenessVector[j]/roads.nodes[j]->mass;
//                  numberCities++;
//              }
//
//          }
//          closenessAvPerCity[i]=closenessTot[i]/numberCities;
//          closenessAvPerIntersection[i]/=numberCities;
//
// //         for(long j=0;j<roads.nodes.size();j++){
// //            if(roads.nodes[j]->mass>0){
// //                roads.nodes[j]->mass=1;
// //            }
// //         }
// //
// //         closenessVector.clear();
// //
// //        Grafo::calculateCloseness(&roads,0,closenessVector);
// //         numberCities=0;
// //         for(long j=0;j<closenessVector.size();j++){
// //            if(roads.nodes[j]->mass>0){
// //                 closenessTotNoMass[i]+=closenessVector[j];
// //                 // closenessAvPerIntersection[i]+=closenessVector[j]/roads.nodes[j]->mass;
// //                 numberCities++;
// //             }
// //
// //         }
// //         closenessAvNoMass[i]=0;
//          // closenessAvPerIntersection[i]/=numberCities;
//
//
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double> ,std::vector<double>   > results;
//     results=std::make_tuple(alphas,robustnessLengths,robustnessNumLinks,tsl,sumDegrees,sumDegreesComplexity,numIntersectionsDegLarger2,numIntersections,betAv,betTot,betEntr,entrAreas,totalArea,numAreas,closenessTot,closenessAvPerIntersection,closenessAvPerCity,closenessTotNoMass,closenessAvNoMass);
//
//     return results;
//
//
//
//
// }
//
//
//
//
//
//
//
//
//
// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>   >   RoadNetworkGeneration::experiments_final_B(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//     long n_cities=44;
//     long n_tempNodes=10000.0+n_cities;//10000
//     double xSize=65000;
//     double ySize=65000;
//     double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(massInitMax*pow((i+1),-.89));
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//
//     double speedHighway=1;//90
//     double speedUrbanRoad=1;//50
//
//
//     speedLimits.resize(std::get<0>(delaunay).size(),speedHighway);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=speedUrbanRoad;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > robustnessLengths;
//     std::vector<double > robustnessNumLinks;
//     std::vector<double > betAv;
//     std::vector<double> tsl;
//     std::vector<double> sumDegreesComplexity;
//     std::vector<double> betTot;
//     std::vector<double> betEntr;
//     std::vector<double> numIntersections;
//     std::vector<double> sumDegrees;
//     std::vector<double> numIntersectionsDegLarger2;
//     std::vector<double> numLinks;
//     std::vector<double> entrAreas;
//     std::vector<double> closenessTot;
//     std::vector<double> closenessAvPerCity;
//     std::vector<double> closenessAvPerIntersection;
//     std::vector<double> outoingTrips;
//     std::vector<double> intersectionsPerCar;
//     std::vector<double> distancePerCar;
//     std::vector<double> flowPerCar;
//
//
//     std::vector<double> alphas;
//     for(double i=0.025;i<=1.024;i+=.025){
//         alphas.push_back(i);
//     }
//     tsl.resize(alphas.size(),0);
//     flowPerCar.resize(alphas.size(),0);
//     robustnessLengths.resize(alphas.size(),0);
//     robustnessNumLinks.resize(alphas.size(),0);
//
//     distancePerCar.resize(alphas.size(),0);
//     intersectionsPerCar.resize(alphas.size(),0);
//     outoingTrips.resize(alphas.size(),0);
//     numIntersections.resize(alphas.size(),0);
//     numIntersectionsDegLarger2.resize(alphas.size(),0);
//     numLinks.resize(alphas.size(),0);
//     sumDegrees.resize(alphas.size(),0);
//     entrAreas.resize(alphas.size(),0);
//     closenessTot.resize(alphas.size(),0);
//     closenessAvPerCity.resize(alphas.size(),0);
//     closenessAvPerIntersection.resize(alphas.size(),0);
// //    closenessTotNoMass.resize(alphas.size(),0);
// //    closenessAvNoMass.resize(alphas.size(),0);
// //    numAreas.resize(alphas.size(),0);
// //    totalArea.resize(alphas.size(),0);
//     // std::vector<double> numIntersections;
//     // numIntersections.resize(alphas.size(),0);
//     // std::vector<double> flowPerMeter;
//     // std::vector<double> intersectionsPerMeter;
//     // flowPerMeter.resize(alphas.size(),0);
//     // intersectionsPerMeter.resize(alphas.size(),0);
//
//     // std::vector<double> numberOfTripsGenerated;
//     // numberOfTripsGenerated.resize(alphas.size(),0);
//     // std::vector<double> numLinks;
//     // numLinks.resize(alphas.size(),0);
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         Grafo roads;
//         Grafo roadsT;
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//         std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
//         Grafo::forcePlanarityPlaneSweep(&roadsT, Grafo::SPEED, pairsOldIdNewIds, false);
//         std::vector<std::pair<std::vector<long>, long> > pairsOldNewB;
//         Grafo::removeNonStructuralNodes(&roadsT, &roads, pairsOldNewB, false);
//
//
//
//
//
//
//
//
//
//
//
//
// //        for(long j=0;j<roads.nodes.size();j++){
// //            if(roads.nodes[j]->getDegree()>2){
// //                numIntersectionsDegLarger2[i]++;
// //                //                if(roads.nodes[j]->mass<=1){
// //
// //                //                }
// //
// //            }
// //            numIntersections[i]++;
// //            //           if(roads.nodes[j]->getDegree()!=2){
// //            ////                numIntersectionsDegDif2[i]++;
// //            //                if(roads.nodes[j]->mass<=1){
// //            //                    numIntersectionsDegDif2NotCity[i]++;
// //            //                }
// //            //
// //            //           }
// //            sumDegrees[i]+=roads.nodes[j]->getDegree();
// //            //           if(roads.nodes[j]->mass<=1){
// //            sumDegreesComplexity[i]+=roads.nodes[j]->getDegree()*(roads.nodes[j]->getDegree()-1)/2;
// //            //           }
// //        }
//         //        for(long j=0;j<roads.links.size();j++){
//         //            sumDegreesPerMeter[i]+=2*floor(roads.links[j]->weight);
//         //            sumDegreesPerMeterNotCity[i]+=2*floor(roads.links[j]->weight);
//         //        }
//         DualExtendedGraph deg;
//         DualExtendedGraph::addPrimal(&deg,&roads);
//         DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
//
//
//
//         std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(deg.getStructuralGraph());
//         robustnessLengths[i]=robustness.first;
//         robustnessNumLinks[i]=robustness.second;
//
//
//
//
//
//
// //        std::vector<double> edgeBetweenness;
// //
// //        Grafo::calculateEdgeBetweenness(&roads,0,edgeBetweenness);
// //
// //        std::vector<double> closenessVector;
// //
// //        Grafo::calculateCloseness(&roads,0,closenessVector);
// //
// //        Distribution disBetweenness=Distribution::createDistribution(edgeBetweenness);
// //        //        betSD[i]=Distribution::getMoment(&disBetweenness,2);
// //
// //        DualExtendedGraph deg2;
// //        DualExtendedGraph::addPrimal(&deg2,&roadsT);
// //        DualExtendedGraph::setPrimalAsStructuralGraph(&deg2);
// //
// //        betEntr[i]=Entropy::calculateEntropy(edgeBetweenness);
// //        Grafo* dual=deg2.getDualGraph();
// //        std::vector<double> masses;
// //        if(dual->nodes.size()>1){
// //            for(long j=1;j<dual->nodes.size();j++){
// //                masses.push_back(dual->nodes[j]->mass);
// //            }
// //            totalArea[i]=dual->nodes[0]->mass;
// //            entrAreas[i]=Entropy::calculateEntropyAreas(masses);
// //            numAreas[i]=masses.size();
// //        }else{
// //            totalArea[i]=0;
// //            entrAreas[i]=0;
// //            numAreas[i]=0;
// //        }
//
//         double totalLength=0;
//         for(long j=0;j<roads.links.size();j++){
// //            betTot[i]+=edgeBetweenness[j]*roads.links[j]->weight;
//             totalLength+=roads.links[j]->weight;
//
//         }
//
//
//
// //        betAv[i]=betTot[i]/totalLength;
//         tsl[i]=totalLength;
//
//
//         SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar(&roads, flowPerCar[i], distancePerCar[i], intersectionsPerCar[i],outoingTrips[i]);
//
//
//
// //        double totalPop=0;
// //        for(long j=0;j<roads.nodes.size();j++){
// //            totalPop+=roads.nodes[j]->mass;
// //        }
// //        double numberCities=0;
// //        for(long j=0;j<closenessVector.size();j++){
// //            if(roads.nodes[j]->mass>1){
// //                closenessTot[i]+=closenessVector[j];
// //                closenessAvPerIntersection[i]+=closenessVector[j]/roads.nodes[j]->mass;
// //                numberCities++;
// //            }
// //
// //        }
// //        closenessAvPerCity[i]=closenessTot[i]/numberCities;
// //        closenessAvPerIntersection[i]/=numberCities;
//
//         //         for(long j=0;j<roads.nodes.size();j++){
//         //            if(roads.nodes[j]->mass>0){
//         //                roads.nodes[j]->mass=1;
//         //            }
//         //         }
//         //
//         //         closenessVector.clear();
//         //
//         //        Grafo::calculateCloseness(&roads,0,closenessVector);
//         //         numberCities=0;
//         //         for(long j=0;j<closenessVector.size();j++){
//         //            if(roads.nodes[j]->mass>0){
//         //                 closenessTotNoMass[i]+=closenessVector[j];
//         //                 // closenessAvPerIntersection[i]+=closenessVector[j]/roads.nodes[j]->mass;
//         //                 numberCities++;
//         //             }
//         //
//         //         }
//         //         closenessAvNoMass[i]=0;
//         // closenessAvPerIntersection[i]/=numberCities;
//
//
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>  > results;
//     results=std::make_tuple(alphas,robustnessLengths,robustnessNumLinks,tsl,flowPerCar, distancePerCar, intersectionsPerCar,outoingTrips);
//
//     return results;
//
//
//
//
// }
//
//
// //void RoadNetworkGeneration::createRoadNetwork(Grafo* roads,Grafo* cities,double d0){
// //
// //}
//
// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>   >   RoadNetworkGeneration::experiments_final_C(Grafo* cities){
//     long n_cities=0;
//     long ymax=LONG_MIN;
//         long xmax=LONG_MIN;
//         long ymin=LONG_MAX;
//         long xmin=LONG_MAX;
//     std::vector<double> masses;
//     for(long i=0;i<cities->nodes.size();i++){
//         if(cities->nodes[i]->mass>=100){
//             n_cities++;
//             masses.push_back(cities->nodes[i]->mass);
//             if(xmin>cities->nodes[i]->location.x){
//                 xmin=cities->nodes[i]->location.x;
//             }
//             if(xmax<cities->nodes[i]->location.x){
//                 xmax=cities->nodes[i]->location.x;
//             }
//             if(ymin>cities->nodes[i]->location.y){
//                 ymin=cities->nodes[i]->location.y;
//             }
//             if(ymax<cities->nodes[i]->location.y){
//                 ymax=cities->nodes[i]->location.y;
//             }
//         }
//     }
//     std::cout<<"number cities "<<n_cities<<'\n';
// //        long n_cities=cities->nodes.size();
//     long n_tempNodes=10000.0+n_cities;//10000
//
//     double xSize=xmax-xmin;
//     double ySize=ymax-ymin;
// //    double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(masses[i]);
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//
//     double speedHighway=1;//90
//     double speedUrbanRoad=1;//50
//
//
//     speedLimits.resize(std::get<0>(delaunay).size(),speedHighway);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=speedUrbanRoad;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > robustnessLengths;
//     std::vector<double > robustnessNumLinks;
//     std::vector<double > betAv;
//     std::vector<double> tsl;
//     std::vector<double> sumDegreesComplexity;
//     std::vector<double> betTot;
//     std::vector<double> betEntr;
//     std::vector<double> numIntersections;
//     std::vector<double> sumDegrees;
//     std::vector<double> numIntersectionsDegLarger2;
//         std::vector<double> fractalDimension;
//     std::vector<double> numLinks;
//     std::vector<double> entrAreas;
//     std::vector<double> closenessTot;
//     std::vector<double> closenessAvPerCity;
//     std::vector<double> closenessAvPerIntersection;
//     std::vector<double> outoingTrips;
//     std::vector<double> intersectionsPerCar;
//     std::vector<double> distancePerCar;
//     std::vector<double> flowPerCar;
//
//
//     std::vector<double> alphas;
//     for(double i=0.025;i<=1.024;i+=.025){
//         alphas.push_back(i);
//     }
//     tsl.resize(alphas.size(),0);
//     flowPerCar.resize(alphas.size(),0);
//     robustnessLengths.resize(alphas.size(),0);
//     robustnessNumLinks.resize(alphas.size(),0);
//
//     distancePerCar.resize(alphas.size(),0);
//     intersectionsPerCar.resize(alphas.size(),0);
//     outoingTrips.resize(alphas.size(),0);
//     numIntersections.resize(alphas.size(),0);
//     numIntersectionsDegLarger2.resize(alphas.size(),0);
//     numLinks.resize(alphas.size(),0);
//     sumDegrees.resize(alphas.size(),0);
//     entrAreas.resize(alphas.size(),0);
//     closenessTot.resize(alphas.size(),0);
//     closenessAvPerCity.resize(alphas.size(),0);
//     closenessAvPerIntersection.resize(alphas.size(),0);
//         fractalDimension.resize(alphas.size(),0);
//     //    closenessTotNoMass.resize(alphas.size(),0);
//     //    closenessAvNoMass.resize(alphas.size(),0);
//     //    numAreas.resize(alphas.size(),0);
//     //    totalArea.resize(alphas.size(),0);
//     // std::vector<double> numIntersections;
//     // numIntersections.resize(alphas.size(),0);
//     // std::vector<double> flowPerMeter;
//     // std::vector<double> intersectionsPerMeter;
//     // flowPerMeter.resize(alphas.size(),0);
//     // intersectionsPerMeter.resize(alphas.size(),0);
//
//     // std::vector<double> numberOfTripsGenerated;
//     // numberOfTripsGenerated.resize(alphas.size(),0);
//     // std::vector<double> numLinks;
//     // numLinks.resize(alphas.size(),0);
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     double d0=80000;
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         Grafo roads;
//         Grafo roadsT;
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//         std::tuple<double,double,double,double,double,double> performanceComponents;
//         performanceComponents=RoadNetworkGeneration::getComponentsOfPerformance(&roadsT);
//         robustnessLengths[i]=std::get<0>(performanceComponents);
//                 robustnessNumLinks[i]=0;
//         tsl[i]=std::get<1>(performanceComponents);
//                 distancePerCar[i]=std::get<2>(performanceComponents);
//         flowPerCar[i]=std::get<3>(performanceComponents);
//
//         intersectionsPerCar[i]=std::get<4>(performanceComponents);
//         outoingTrips[i]=std::get<5>(performanceComponents);
//         fractalDimension[i]=FractalDimension::calculateBoxCounting(&roadsT);
//         for(long j=0;j<roads.nodes.size();j++){
//             if(roads.nodes[i]->getDegree()!=2){
//                 numIntersections[i]++;
//             }
//         }
//
//
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double> ,std::vector<double> > results;
//     results=std::make_tuple(alphas,robustnessLengths,robustnessNumLinks,tsl,flowPerCar, distancePerCar, intersectionsPerCar,outoingTrips,fractalDimension,numIntersections);
//
//     return results;
//
//
//
//
// }






double RoadNetworkGeneration::performance(Grafo* G,double beta1,double beta2){
//    double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time;
//    long n_cities=44;
//    long n_tempNodes=10000.0+n_cities;//10000
//    double xSize=65000;
//    double ySize=65000;
//    double massInitMax=48370;
//    // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//    std::vector<long> id;
//    std::vector<double> x;
//    std::vector<double> y;
//    std::vector<double> mass;
//    id.reserve(n_cities+n_tempNodes);
//    x.reserve(n_cities+n_tempNodes);
//    y.reserve(n_cities+n_tempNodes);
//    mass.reserve(n_cities+n_tempNodes);
//    for(long i=0;i<n_cities;i++){
//        id.push_back(i);
//        x.push_back(Functions::runiform(0,xSize));
//        y.push_back(Functions::runiform(0,ySize));
//        mass.push_back(massInitMax*pow((i+1),-.89));
//    }
//    // cities$mass=massInitMax*cities$id^-1
//    for(long i=0;i<n_tempNodes;i++){
//        id.push_back(i+n_cities);
//        x.push_back(Functions::runiform(0,xSize));
//        y.push_back(Functions::runiform(0,ySize));
//        mass.push_back(0);
//    }
//    // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//    // tempNodes$mass=0
//    // nodes=rbind(cities,tempNodes)
//    // nodes$id=1:nrow(nodes)-1
//    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//    std::vector<long> linksRemoved;
//
//    std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//    Grafo delanuayGraph;
//    Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//    Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//    coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//    // delanuay$inCity=0
//    std::vector<bool> inCity;
//    inCity.resize(std::get<0>(delaunay).size(),false);
//    std::vector<double> radii;
//    radii.resize(n_cities,0);
//    std::vector<double> speedLimits;
//    speedLimits.resize(std::get<0>(delaunay).size(),90);
//    for(long i=0;i<n_cities;i++){
//        radii[i]=sqrt((mass[i]/3.1415));
//        for(long j=0;j<std::get<0>(delaunay).size();j++){
//            double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//            double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//            if(distance1<=radii[i]&&distance2<=radii[i]){
//                inCity[j]=true;
//                speedLimits[j]=50;
//            }
//        }
//
//    }
//
//
//    // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//    Grafo G;
//    Grafo::create(&G,delaunay,coords,mass,false);
//
//
//    std::vector<double > robustnessLengths;
//    std::vector<double > robustnessNumLinks;
//    std::vector<double > betAv;
//    std::vector<double> tsl;
//    std::vector<double> sumDegreesComplexity;
//    std::vector<double> betTot;
//    std::vector<double> betEntr;
//    std::vector<double> numIntersections;
//    std::vector<double> sumDegrees;
//    std::vector<double> numIntersectionsDegLarger2;
//    std::vector<double> numLinks;
//    std::vector<double> entrAreas;
//    std::vector<double> closenessTot;
//    std::vector<double> closenessAvPerCity;
//    std::vector<double> closenessAvPerIntersection;
//    std::vector<double> outoingTrips;
//    std::vector<double> intersectionsPerCar;
//    std::vector<double> distancePerCar;
//    std::vector<double> flowPerCar;
//
//
//    std::vector<double> alphas;
//    for(double i=0.05;i<=1.04;i+=.05){
//        alphas.push_back(i);
//    }
//    tsl.resize(alphas.size(),0);
//    flowPerCar.resize(alphas.size(),0);
//    robustnessLengths.resize(alphas.size(),0);
//    robustnessNumLinks.resize(alphas.size(),0);
//
//    distancePerCar.resize(alphas.size(),0);
//    intersectionsPerCar.resize(alphas.size(),0);
//    outoingTrips.resize(alphas.size(),0);
//    numIntersections.resize(alphas.size(),0);
//    numIntersectionsDegLarger2.resize(alphas.size(),0);
//    numLinks.resize(alphas.size(),0);
//    sumDegrees.resize(alphas.size(),0);
//    entrAreas.resize(alphas.size(),0);
//    closenessTot.resize(alphas.size(),0);
//    closenessAvPerCity.resize(alphas.size(),0);
//    closenessAvPerIntersection.resize(alphas.size(),0);
//    //    closenessTotNoMass.resize(alphas.size(),0);
//    //    closenessAvNoMass.resize(alphas.size(),0);
//    //    numAreas.resize(alphas.size(),0);
//    //    totalArea.resize(alphas.size(),0);
//    // std::vector<double> numIntersections;
//    // numIntersections.resize(alphas.size(),0);
//    // std::vector<double> flowPerMeter;
//    // std::vector<double> intersectionsPerMeter;
//    // flowPerMeter.resize(alphas.size(),0);
//    // intersectionsPerMeter.resize(alphas.size(),0);
//
//    // std::vector<double> numberOfTripsGenerated;
//    // numberOfTripsGenerated.resize(alphas.size(),0);
//    // std::vector<double> numLinks;
//    // numLinks.resize(alphas.size(),0);
//    for(long i=0;i<alphas.size();i++){

//        double alpha=alphas[i];
//        std::cout<<"alpha "<<alpha<<'\n';
        Grafo roads;
//        Grafo roadsT;
//        // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//        RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,alpha,d0,180,capacityLink,0,0);
        std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
        Grafo::forcePlanarityPlaneSweep(G, Grafo::SPEED, pairsOldIdNewIds, false);
        std::vector<std::pair<std::vector<long>, long> > pairsOldNewB;
        Grafo::removeNonStructuralNodes(G, &roads, pairsOldNewB, false);












        //        for(long j=0;j<roads.nodes.size();j++){
        //            if(roads.nodes[j]->getDegree()>2){
        //                numIntersectionsDegLarger2[i]++;
        //                //                if(roads.nodes[j]->mass<=1){
        //
        //                //                }
        //
        //            }
        //            numIntersections[i]++;
        //            //           if(roads.nodes[j]->getDegree()!=2){
        //            ////                numIntersectionsDegDif2[i]++;
        //            //                if(roads.nodes[j]->mass<=1){
        //            //                    numIntersectionsDegDif2NotCity[i]++;
        //            //                }
        //            //
        //            //           }
        //            sumDegrees[i]+=roads.nodes[j]->getDegree();
        //            //           if(roads.nodes[j]->mass<=1){
        //            sumDegreesComplexity[i]+=roads.nodes[j]->getDegree()*(roads.nodes[j]->getDegree()-1)/2;
        //            //           }
        //        }
        //        for(long j=0;j<roads.links.size();j++){
        //            sumDegreesPerMeter[i]+=2*floor(roads.links[j]->weight);
        //            sumDegreesPerMeterNotCity[i]+=2*floor(roads.links[j]->weight);
        //        }
        DualExtendedGraph deg;
        DualExtendedGraph::addPrimal(&deg,&roads);
        DualExtendedGraph::setPrimalAsStructuralGraph(&deg);



        std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(deg.getStructuralGraph());
        double r=robustness.first;
//        robustnessNumLinks[i]=robustness.second;






        //        std::vector<double> edgeBetweenness;
        //
        //        Grafo::calculateEdgeBetweenness(&roads,0,edgeBetweenness);
        //
        //        std::vector<double> closenessVector;
        //
        //        Grafo::calculateCloseness(&roads,0,closenessVector);
        //
        //        Distribution disBetweenness=Distribution::createDistribution(edgeBetweenness);
        //        //        betSD[i]=Distribution::getMoment(&disBetweenness,2);
        //
        //        DualExtendedGraph deg2;
        //        DualExtendedGraph::addPrimal(&deg2,&roadsT);
        //        DualExtendedGraph::setPrimalAsStructuralGraph(&deg2);
        //
        //        betEntr[i]=Entropy::calculateEntropy(edgeBetweenness);
        //        Grafo* dual=deg2.getDualGraph();
        //        std::vector<double> masses;
        //        if(dual->nodes.size()>1){
        //            for(long j=1;j<dual->nodes.size();j++){
        //                masses.push_back(dual->nodes[j]->mass);
        //            }
        //            totalArea[i]=dual->nodes[0]->mass;
        //            entrAreas[i]=Entropy::calculateEntropyAreas(masses);
        //            numAreas[i]=masses.size();
        //        }else{
        //            totalArea[i]=0;
        //            entrAreas[i]=0;
        //            numAreas[i]=0;
        //        }

        double l=0;
        for(long j=0;j<roads.links.size();j++){
            //            betTot[i]+=edgeBetweenness[j]*roads.links[j]->weight;
            l+=roads.links[j]->weight;

        }



        //        betAv[i]=betTot[i]/totalLength;
//        tsl[i]=totalLength;

    double v,d,n,N;
        SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar(&roads, v,d,n,N);



        //        double totalPop=0;
        //        for(long j=0;j<roads.nodes.size();j++){
        //            totalPop+=roads.nodes[j]->mass;
        //        }
        //        double numberCities=0;
        //        for(long j=0;j<closenessVector.size();j++){
        //            if(roads.nodes[j]->mass>1){
        //                closenessTot[i]+=closenessVector[j];
        //                closenessAvPerIntersection[i]+=closenessVector[j]/roads.nodes[j]->mass;
        //                numberCities++;
        //            }
        //
        //        }
        //        closenessAvPerCity[i]=closenessTot[i]/numberCities;
        //        closenessAvPerIntersection[i]/=numberCities;

        //         for(long j=0;j<roads.nodes.size();j++){
        //            if(roads.nodes[j]->mass>0){
        //                roads.nodes[j]->mass=1;
        //            }
        //         }
        //
        //         closenessVector.clear();
        //
        //        Grafo::calculateCloseness(&roads,0,closenessVector);
        //         numberCities=0;
        //         for(long j=0;j<closenessVector.size();j++){
        //            if(roads.nodes[j]->mass>0){
        //                 closenessTotNoMass[i]+=closenessVector[j];
        //                 // closenessAvPerIntersection[i]+=closenessVector[j]/roads.nodes[j]->mass;
        //                 numberCities++;
        //             }
        //
        //         }
        //         closenessAvNoMass[i]=0;
        // closenessAvPerIntersection[i]/=numberCities;



//    }

//    std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>  > results;
//    results=std::make_tuple(alphas,robustnessLengths,robustnessNumLinks,tsl,flowPerCar, distancePerCar, intersectionsPerCar,outoingTrips);
    std::cout<<"r "<<r/l<<" l "<<l<<" d "<<d<<" v "<<v/N<<" n "<<n<<" N "<<N<<"\n";
    return ((r/l)/l)*pow(1/d,beta1)*pow(1/((v/N)*n),beta2);




}
std::tuple<double,double,double,double,double,double> RoadNetworkGeneration::getComponentsOfPerformance(Grafo* G){
    Grafo roads;
    std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
    Grafo::forcePlanarityPlaneSweep(G, Grafo::SPEED, pairsOldIdNewIds, false);
    std::vector<std::pair<std::vector<long>, long> > pairsOldNewB;
    Grafo::removeNonStructuralNodes(G, &roads, pairsOldNewB, false);









    DualExtendedGraph deg;
    DualExtendedGraph::addPrimal(&deg,&roads);
    DualExtendedGraph::setPrimalAsStructuralGraph(&deg);



    std::pair<double,double> robustness=SpatialInteraction::calculateRobustness(deg.getStructuralGraph(),1000);
    double r=robustness.first;

    double l=0;
    for(long j=0;j<roads.links.size();j++){
        l+=roads.links[j]->weight;

    }





    double v,d,n,N;
    SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar(&roads, v,d,n,N);


//    std::cout<<"r "<<r/l<<" l "<<l<<" d "<<d<<" v "<<v/N<<" n "<<n<<" N "<<N<<"\n";
//    return ((r/l)/l)*pow(1/d,beta1)*pow(1/((v/N)*n),beta2);

    std::tuple<double,double,double,double,double,double> result;
    //r is normalised for different lengths therefore robustness=r/l
    result=std::make_tuple(r/l,l,d,v,n,N);
    return result;




}






// std::tuple<std::vector<double>,std::vector<double>  >  RoadNetworkGeneration::experiments_measureFractalDimension(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//     long n_cities=44;
//     long n_tempNodes=10000.0+n_cities;//10000
//     double xSize=65000;
//     double ySize=65000;
//     double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(massInitMax*pow((i+1),-.89));
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//     speedLimits.resize(std::get<0>(delaunay).size(),90);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=50;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > robustnessLengths;
//      std::vector<double > robustnessNumLinks;
//     std::vector<double > timeDistancesFromNodes;
//     std::vector<double> tsl;
//
//
//     std::vector<double> alphas;
//     for(double i=0.05;i<=1.04;i+=.05){
//         alphas.push_back(i);
//     }
//
//
//     std::vector<double> fractalDimension;
//     fractalDimension.resize(alphas.size(),0);
//
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         // Grafo roads;
//         Grafo roadsT;
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//
//         std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
//         Grafo::forcePlanarityPlaneSweep(&roadsT, Grafo::SPEED, pairsOldIdNewIds, false);
//
//
//         fractalDimension[i]=FractalDimension::calculateBoxCounting(&roadsT);
//
//
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double> > results;
//     results=std::make_tuple(alphas,fractalDimension);
//
//     return results;
//
//
//
//
// }
//
//
// std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>  >  RoadNetworkGeneration::experiments_measureEntropy(double d0,double capacityLink,double alpha_congestion,double beta_congestion,double time){
//     long n_cities=44;
//     long n_tempNodes=10000.0+n_cities;//10000
//     double xSize=65000;
//     double ySize=65000;
//     double massInitMax=48370;
//     // cities=data.frame(id=1:n.cities,x=runif(n.cities,min=0,max=xSize),y=runif(n.cities,min=0,max=xSize))
//     std::vector<long> id;
//     std::vector<double> x;
//     std::vector<double> y;
//     std::vector<double> mass;
//     id.reserve(n_cities+n_tempNodes);
//     x.reserve(n_cities+n_tempNodes);
//     y.reserve(n_cities+n_tempNodes);
//     mass.reserve(n_cities+n_tempNodes);
//     for(long i=0;i<n_cities;i++){
//         id.push_back(i);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(massInitMax*pow((i+1),-.89));
//     }
//     // cities$mass=massInitMax*cities$id^-1
//     for(long i=0;i<n_tempNodes;i++){
//         id.push_back(i+n_cities);
//         x.push_back(Functions::runiform(0,xSize));
//         y.push_back(Functions::runiform(0,ySize));
//         mass.push_back(0);
//     }
//     // tempNodes=data.frame(id=1:n.tempNodes,x=runif(n.tempNodes,min=0,max=xSize),y=runif(n.tempNodes,min=0,max=ySize))
//     // tempNodes$mass=0
//     // nodes=rbind(cities,tempNodes)
//     // nodes$id=1:nrow(nodes)-1
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delanuay_temp=Geometry::delaunay(id,x,y);
//     std::vector<long> linksRemoved;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coords=std::make_tuple(id,x,y);
//     Grafo delanuayGraph;
//     Grafo::create(&delanuayGraph,delanuay_temp,coords,false);
//     Grafo::cleanDuplicatedLinks(&delanuayGraph,1,linksRemoved,false);
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay=Grafo::getNCOL(&delanuayGraph);
//     coords=Grafo::getCoordinates(&delanuayGraph);
//
//
//
//
//
//     // delanuay$inCity=0
//     std::vector<bool> inCity;
//     inCity.resize(std::get<0>(delaunay).size(),false);
//     std::vector<double> radii;
//     radii.resize(n_cities,0);
//     std::vector<double> speedLimits;
//     speedLimits.resize(std::get<0>(delaunay).size(),90);
//     for(long i=0;i<n_cities;i++){
//         radii[i]=sqrt((mass[i]/3.1415));
//         for(long j=0;j<std::get<0>(delaunay).size();j++){
//             double distance1=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<0>(delaunay)[j]],y[std::get<0>(delaunay)[j]]));
//             double distance2=Functions::getDistance(Point2d(x[i],y[i]),Point2d(x[std::get<1>(delaunay)[j]],y[std::get<1>(delaunay)[j]]));
//             if(distance1<=radii[i]&&distance2<=radii[i]){
//                 inCity[j]=true;
//                 speedLimits[j]=50;
//             }
//         }
//
//     }
//
//
//     // DualExtendedGraph::create(&deg,delaunay,coords,false);
//
//     Grafo G;
//     Grafo::create(&G,delaunay,coords,mass,false);
//
//
//     std::vector<double > Ha;
//     std::vector<double > Hda;
//     std::vector<double > H;
//     std::vector<double > Hd;
//     std::vector<double > totalAreas;
//     std::vector<double> n;
//
//
//     std::vector<double> alphas;
//     for(double i=0.05;i<=1.04;i+=.05){
//         alphas.push_back(i);
//     }
//
//
// //    std::vector<double> fractalDimension;
//     Ha.resize(alphas.size(),0);
//     Hda.resize(alphas.size(),0);
//     H.resize(alphas.size(),0);
//     Hd.resize(alphas.size(),0);
//     totalAreas.resize(alphas.size(),0);
//     n.resize(alphas.size(),0);
//
//     std::vector<double> multiplierRivers;
//     multiplierRivers.resize(std::get<0>(delaunay).size(),1);
//     for(long i=0;i<alphas.size();i++){
//
//         double alpha=alphas[i];
//         std::cout<<"alpha "<<alpha<<'\n';
//         // Grafo roads;
//         Grafo roadsT;
//         // void SpatialInteraction::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion)
//         RoadNetworkGeneration::createRoadNetwork(&G,&roadsT,speedLimits,multiplierRivers,alpha,d0);
//
//         std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
//         Grafo::forcePlanarityPlaneSweep(&roadsT, Grafo::SPEED, pairsOldIdNewIds, false);
//         DualExtendedGraph degRoads;
//         DualExtendedGraph::addPrimal(&degRoads,&roadsT);
//         std::vector<double> areas;
//         for(long j=1;j<degRoads.getDualGraph()->nodes.size();j++){
//             areas.push_back(degRoads.getDualGraph()->nodes[j]->mass);
//         }
//         double H_a=Entropy::calculateEntropyAreas(areas);
//         double H_=Entropy::calculateEntropy(areas);
//         double largestMass_=degRoads.getDualGraph()->nodes[0]->mass;
//         double n_=areas.size();
//         std::tuple<double,double> Hds_=Entropy::createDelanuayAndCalculateItsEntropies(largestMass_,n_);
//         Ha[i]=H_a;
//         H[i]=H_;
//         Hda[i]=std::get<1>(Hds_);
//         Hd[i]=std::get<0>(Hds_);
//         totalAreas[i]=largestMass_;
//         n[i]=n_;
//
//
//
// //        fractalDimension[i]=FractalDimension::calculateBoxCounting(&roadsT);
//
//
//
//     }
//
//     std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>  > results;
//     results=std::make_tuple(alphas,H,Hd,Ha,Hda,totalAreas,n);
//
//     return results;
//
//
//
//
// }






void RoadNetworkGeneration::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,std::vector<double> &multiplierTopography,std::vector<long> &idsEdgesBelongingToCities,double proportionBetweenSpeedInCityAndOutside,std::vector<double> &multiplierRivers,double alpha,double d0){
    // Grafo* G=new Grafo();
    // Grafo G;
    G->bidirectional=true;
    G->spatialGraph=true;
    G->copyGraph(delanuayWithCities);
    double distanceLimit=0;
    std::vector<bool> constructed;
    constructed.resize(G->links.size(),false);
    std::vector<std::pair<long,long> > pairsOfCities;
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    std::vector<double> flows;
    // std::vector<double> speedLimits;
    // speedLimits=as<std::vector<double> > (speedLimits);
    std::vector<double> speeds;
    speeds.resize(delanuayWithCities->links.size(),1);
    std::unordered_map<long, std::vector<long> > idEdgesPerCity;

    for(long i=0;i<idsEdgesBelongingToCities.size();i++){
      if(idsEdgesBelongingToCities[i]!=-1){
        speeds[i]/=proportionBetweenSpeedInCityAndOutside;
        idEdgesPerCity[idsEdgesBelongingToCities[i]].push_back(i);
      }
    }

    std::vector<double> originalWeights;
    originalWeights.resize(delanuayWithCities->links.size(),0);
    flows.resize(delanuayWithCities->links.size(),0);
    // speeds.resize(delanuayWithCities->links.size,0);
    // std::vector<double> distances;
    std::vector<double> strengthPairs;

    std::vector<long> idsCities;
    // idsCities.resize()
    long numCities=0;
    for(long i=0;i<G->nodes.size();i++){
        if(G->nodes[i]->mass>0){
            numCities++;
            idsCities.push_back(i);
        }
    }
    strengthPairs.reserve(numCities);
    // distances.reserve(numCities);
    pairsOfCities.reserve(numCities);
    // double d0=80000;

    for(long i=0;i<G->links.size();i++){
        originalWeights[i]=G->links[i]->weight;
        G->links[i]->weight/=multiplierTopography[i]*multiplierRivers[i]*speeds[i];
    }

    bool properCalculation=false;
    if(properCalculation){
        Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
        for(long i=0;i<G->nodes.size();i++){
            if(G->nodes[i]->mass>0){
                InterfaceDijkstra ID;

                Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
                for(long j=0;j<ID.idsInCutoff.size();j++){
                    double id=ID.idsInCutoff[j];
                    if(G->nodes[id]->mass>0){
                        double d=ID.getMinDistance(id);
                        if(d<INFINITY&&d>0){
                            std::pair<long,long> pairCities;
                            pairCities.first=i;
                            pairCities.second=id;
                            pairsOfCities.push_back(pairCities);
                            // distances.push_back(distance);

    //                        double strength=(2/(M_PI*d0)*(G->nodes[i]->mass*G->nodes[id]->mass)/(1+(d/d0)*(d/d0));
                            double strength=SpatialInteraction::kernelDistanceDecay(d,d0)*(G->nodes[i]->mass*G->nodes[id]->mass);
                            strengthPairs.push_back(strength);

                        }
                    }
                }
            }
        }
        Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
      }else{
        for(long i=0;i<idsCities.size();i++){
            // if(G->nodes[i]->mass>0){
                for(long j=0;j<idsCities.size();j++){
                  double d=Functions::getDistance(G->nodes[idsCities[i]]->location,G->nodes[idsCities[j]]->location);
                  if(d<INFINITY&&d>0){
                      std::pair<long,long> pairCities;
                      pairCities.first=idsCities[i];
                      pairCities.second=idsCities[j];
                      pairsOfCities.push_back(pairCities);
                      // distances.push_back(distance);

//                        double strength=(2/(M_PI*d0)*(G->nodes[i]->mass*G->nodes[id]->mass)/(1+(d/d0)*(d/d0));
                      double strength=SpatialInteraction::kernelDistanceDecay(d,d0)*(G->nodes[idsCities[i]]->mass*G->nodes[idsCities[j]]->mass);
                      strengthPairs.push_back(strength);


                }
              }
            // }
        }
      }
        Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);

    std::vector<long> indexOrderStrength=Functions::getIndexesOfOrderedValues(strengthPairs,false);

    std::unordered_map<Point2d, bool > alreadyCalculated;





    for(long i=0;i<pairsOfCities.size();i++){
        bool skip=false;
        long indexPair=indexOrderStrength[i];
        if(i>0){
            // long indexPreviousPair=indexOrderStrength[i-1];
            // if(pairsOfCities[indexPreviousPair].second==pairsOfCities[indexPair].first&&pairsOfCities[indexPair].second==pairsOfCities[indexPreviousPair].first){
            if(alreadyCalculated[Point2d(pairsOfCities[indexPair].first,pairsOfCities[indexPair].second)] || alreadyCalculated[Point2d(pairsOfCities[indexPair].second,pairsOfCities[indexPair].first)]){
                skip=true;
            }
        }
        if(!skip){
            long id1=pairsOfCities[indexPair].first;
            long id2=pairsOfCities[indexPair].second;
            alreadyCalculated[Point2d(id1,id2)]=true;
            for(long j=0;j<idEdgesPerCity[id1].size();j++){
              G->links[idEdgesPerCity[id1][j]]->weight/=proportionBetweenSpeedInCityAndOutside;
            }
            for(long j=0;j<idEdgesPerCity[id2].size();j++){
              G->links[idEdgesPerCity[id2][j]]->weight/=proportionBetweenSpeedInCityAndOutside;
            }
            InterfaceDijkstra ID;
            ID.prepareForBetweenness();
            double angleAllowed=180.0;
            Grafo::calculateAStar_angleBased(G,G->nodes[id1],G->nodes[id2],angleAllowed,ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            long idCurrent=id2;
            long idParent=ID.getParentID(idCurrent);
            double distance=ID.getMinDistance(id2);
            double flowToAdd=SpatialInteraction::kernelDistanceDecay(distance,d0)*G->nodes[id1]->mass*G->nodes[id2]->mass;
            while(idParent!=-1){
                for(long j=0;j<G->nodes[idCurrent]->links.size();j++){
                    if(G->nodes[idCurrent]->links[j]->getOtherNode(G->nodes[idCurrent])==G->nodes[idParent]){
                        // if(!constructed[G->nodes[idCurrent]->links[j]->id]){
                        long idLink=G->nodes[idCurrent]->links[j]->id;
                        flows[idLink]+=flowToAdd;
//                        double speed=speedLimits[idLink]/alpha*SpatialInteraction::modificationSpeedWithCongestion(flows[idLink],capacityLink,alpha_congestion,beta_congestion);
                        double speed=multiplierTopography[idLink]/alpha;
                        G->nodes[idCurrent]->links[j]->weight=originalWeights[idLink]/speed;
                        // }
                        constructed[G->nodes[idCurrent]->links[j]->id]=true;

                    }
                }
                idCurrent=idParent;
                idParent=ID.getParentID(idCurrent);
            }
            for(long j=0;j<idEdgesPerCity[id1].size();j++){
              G->links[idEdgesPerCity[id1][j]]->weight*=proportionBetweenSpeedInCityAndOutside;
            }
            for(long j=0;j<idEdgesPerCity[id2].size();j++){
              G->links[idEdgesPerCity[id2][j]]->weight*=proportionBetweenSpeedInCityAndOutside;
            }
        }
    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    std::set<long> idLinksToRemove;
    for(long i=0;i<G->links.size();i++){
        G->links[i]->weight=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
        if(!constructed[i]){
            idLinksToRemove.insert(i);
        }
    }
    G->removeLinks(idLinksToRemove);
    G->removeNodesDegree0();
}



//void RoadNetworkGeneration::createRoadNetwork(Grafo* delanuayWithCities,Grafo* G,double exponentDecayDistance,std::vector<double> &speedLimits,double alpha,double d0,double angleAllowed,double capacityLink,double alpha_congestion, double beta_congestion){
//    // Grafo* G=new Grafo();
//    // Grafo G;
//    G->bidirectional=true;
//    G->spatialGraph=true;
//    G->copyGraph(delanuayWithCities);
//    double distanceLimit=0;
//    std::vector<bool> constructed;
//    constructed.resize(G->links.size(),false);
//    std::vector<std::pair<long,long> > pairsOfCities;
//    std::vector<Number*> numbersRepresentingNodes;
//    std::vector<bool> inDijkstra;
//    std::vector<bool> inCutoff;
//    std::vector<double> flows;
//    // std::vector<double> speedLimits;
//    // speedLimits=as<std::vector<double> > (speedLimits);
//    std::vector<double> speeds;
//    speeds.resize(delanuayWithCities->links.size(),0);
//    std::vector<double> originalWeights;
//    originalWeights.resize(delanuayWithCities->links.size(),0);
//    flows.resize(delanuayWithCities->links.size(),0);
//    // speeds.resize(delanuayWithCities->links.size,0);
//    // std::vector<double> distances;
//    std::vector<double> strengthPairs;
//
//    long numCities=0;
//    for(long i=0;i<G->nodes.size();i++){
//        if(G->nodes[i]->mass>0){
//            numCities++;
//        }
//    }
//    strengthPairs.reserve(numCities);
//    // distances.reserve(numCities);
//    pairsOfCities.reserve(numCities);
//    // double d0=80000;
//
//    for(long i=0;i<G->links.size();i++){
//        originalWeights[i]=G->links[i]->weight;
//        G->links[i]->weight/=speedLimits[i];
//    }
//
//    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
//    for(long i=0;i<G->nodes.size();i++){
//    // long i=0;
//    // {
//        if(G->nodes[i]->mass>0){
//            InterfaceDijkstra ID;
//
//            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
//            for(long j=0;j<ID.idsInCutoff.size();j++){
//                double id=ID.idsInCutoff[j];
//                if(G->nodes[id]->mass>0){
//                    double d=ID.getMinDistance(id);
//                    if(d<INFINITY&&d>0){
//                        std::pair<long,long> pairCities;
//                        pairCities.first=i;
//                        pairCities.second=id;
//                        pairsOfCities.push_back(pairCities);
//                        // distances.push_back(distance);
//                        double strength=(G->nodes[i]->mass*G->nodes[id]->mass)/(1+pow((d/d0),exponentDecayDistance));
//                        strengthPairs.push_back(strength);
//
//                    }
//                }
//            }
//        }
//    }
//
//    std::vector<long> indexOrderStrength=Functions::getIndexesOfOrderedValues(strengthPairs,false);
//    for(long i=0;i<pairsOfCities.size();i++){
//        bool skip=false;
//        long indexPair=indexOrderStrength[i];
//        if(i>0){
//            long indexPreviousPair=indexOrderStrength[i-1];
//            if(pairsOfCities[indexPreviousPair].second==pairsOfCities[indexPair].first&&pairsOfCities[indexPair].second==pairsOfCities[indexPreviousPair].first){
//                skip=true;
//            }
//        }
//        if(!skip){
//            long id1=pairsOfCities[indexPair].first;
//            long id2=pairsOfCities[indexPair].second;
//            InterfaceDijkstra ID;
//            ID.prepareForBetweenness();
//            Grafo::calculateAStar_angleBased(G,G->nodes[id1],G->nodes[id2],angleAllowed,ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
//            long idCurrent=id2;
//            long idParent=ID.getParentID(idCurrent);
//            double distance=ID.getMinDistance(id2);
//            double flowToAdd=SpatialInteraction::kernelDistanceDecay(distance)*G->nodes[id1]->mass*G->nodes[id2]->mass;
//            while(idParent!=-1){
//                for(long j=0;j<G->nodes[idCurrent]->links.size();j++){
//                    if(G->nodes[idCurrent]->links[j]->getOtherNode(G->nodes[idCurrent])==G->nodes[idParent]){
//                        // if(!constructed[G->nodes[idCurrent]->links[j]->id]){
//                        long idLink=G->nodes[idCurrent]->links[j]->id;
//                        flows[idLink]+=flowToAdd;
//                        double speed=speedLimits[idLink]/alpha*SpatialInteraction::modificationSpeedWithCongestion(flows[idLink],capacityLink,alpha_congestion,beta_congestion);
//                        G->nodes[idCurrent]->links[j]->weight=originalWeights[idLink]/speed;
//                        // }
//                        constructed[G->nodes[idCurrent]->links[j]->id]=true;
//
//                    }
//                }
//                idCurrent=idParent;
//                idParent=ID.getParentID(idCurrent);
//            }
//        }
//    }
//    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
//    std::set<long> idLinksToRemove;
//    for(long i=0;i<G->links.size();i++){
//        G->links[i]->weight=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
//        if(!constructed[i]){
//            idLinksToRemove.insert(i);
//        }
//    }
//    G->removeLinks(idLinksToRemove);
//    G->removeNodesDegree0();
//}




std::vector<double> RoadNetworkGeneration::getGaussianSpeedLimits(Grafo* delanuayGraph,double d0,double exponent){
    std::vector<double> speedLimitMultiplierNodes;
    speedLimitMultiplierNodes.resize(delanuayGraph->nodes.size(),0);
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(delanuayGraph,numbersRepresentingNodes,inDijkstra,inCutoff);
    for(long i=0;i<delanuayGraph->nodes.size();i++){
        if(delanuayGraph->nodes[i]->mass>0){
            double m=delanuayGraph->nodes[i]->mass;
            // double distanceLimit=sqrt(-2*c*c*log(0.01/m));
            double distanceLimit=d0*pow(((m/0.01)-1),1/exponent);
            InterfaceDijkstra ID;
            Grafo::calculateDijkstra(delanuayGraph,delanuayGraph->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY){
                    // speedLimitMultiplierNodes[id]+=m*exp(-distance*distance/(2*c*c));
                    speedLimitMultiplierNodes[id]+=m/(1+pow(distance/d0,exponent));
                }
            }
        }
    }
    Grafo::finishCalculatingShortestPaths(delanuayGraph,numbersRepresentingNodes,inDijkstra,inCutoff);
    std::vector<double> speedLimitMultiplierLinks;
    speedLimitMultiplierLinks.resize(delanuayGraph->links.size(),0);
    for(long i=0;i<delanuayGraph->links.size();i++){
        speedLimitMultiplierLinks[i]=(speedLimitMultiplierNodes[delanuayGraph->links[i]->A()->id]+speedLimitMultiplierNodes[delanuayGraph->links[i]->B()->id])/2.0;
    }
    return speedLimitMultiplierLinks;
}




void RoadNetworkGeneration::keepOnlySimplestPathsBetweenNodes(Grafo* G,Grafo* result){
//    std::vector<bool> keepLink;
//    keepLink.resize(G->links.size(),false);
    std::vector<long> idsToKeep;
            std::vector<Number*> numbersRepresentingNodes;
            std::vector<bool> inDijkstra;
            std::vector<bool> inCutoff;
            Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long i=0;i<G->nodes.size();i++){
                if(G->nodes[i]->mass>0){
//                    double m=G->nodes[i]->mass;
                    // double distanceLimit=sqrt(-2*c*c*log(0.01/m));
//                    double distanceLimit=d0*pow(((m/0.01)-1),1/exponent);
                    double distanceLimit=0;
                    InterfaceDijkstra ID;
                    Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
                    for(long j=0;j<ID.idsInCutoff.size();j++){
                        double id=ID.idsInCutoff[j];
                        double distance=ID.getMinDistance(id);
                        if(distance<INFINITY&&distance>0&&G->nodes[id]->mass>0){
                            long node=id;
                            long parent=ID.getParentID(id);
                            while(parent!=-1){
//                                long node=node;

                                for(long h=0;h<G->nodes[parent]->links.size();h++){
                                    if(G->nodes[parent]->links[h]->getOtherNode(G->nodes[parent])->id==node){
                                        idsToKeep.push_back(G->nodes[parent]->links[h]->id);
                                    }
                                }
                                node=parent;
                                parent=ID.getParentID(parent);

                            }
                        }
                    }
                }
            }
            Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);

    Grafo::inducedSubgraphFromLinks(G, result, idsToKeep);

}


double RoadNetworkGeneration::calculateStraightnessEfficiency(Grafo* G){
//    std::vector<bool> keepLink;
//    keepLink.resize(G->links.size(),false);
    std::vector<long> idsToKeep;
            std::vector<Number*> numbersRepresentingNodes;
            std::vector<bool> inDijkstra;
            std::vector<bool> inCutoff;
            Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
            double E=0.0;
            double N=0.0;
            for(long i=0;i<G->nodes.size();i++){
                if(G->nodes[i]->mass>0){
                  N+=1.0;
//                    double m=G->nodes[i]->mass;
                    // double distanceLimit=sqrt(-2*c*c*log(0.01/m));
//                    double distanceLimit=d0*pow(((m/0.01)-1),1/exponent);
                    double distanceLimit=0;
                    InterfaceDijkstra ID;
                    Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
                    for(long j=0;j<ID.idsInCutoff.size();j++){
                        double id=ID.idsInCutoff[j];
                        double distance=ID.getMinDistance(id);
                        if(distance<INFINITY&&distance>0&&G->nodes[id]->mass>0){
                            double distanceCrow=Functions::getDistance(G->nodes[i]->location,G->nodes[id]->location);
                            E=E+distanceCrow/distance;
//                             long node=id;
//                             long parent=ID.getParentID(id);
//                             while(parent!=-1){
// //                                long node=node;
//
//                                 for(long h=0;h<G->nodes[parent]->links.size();h++){
//                                     if(G->nodes[parent]->links[h]->getOtherNode(G->nodes[parent])->id==node){
//                                         idsToKeep.push_back(G->nodes[parent]->links[h]->id);
//                                     }
//                                 }
//                                 node=parent;
//                                 parent=ID.getParentID(parent);
//
//                             }
                        }
                    }
                }
            }
            Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
            E=E/(N*(N-1));
            return E;
    // Grafo::inducedSubgraphFromLinks(G, result, idsToKeep);

}

std::vector<double> RoadNetworkGeneration::calculateStraightnessEfficiencyAndTripEfficiency(Grafo* G,double d0){
//    std::vector<bool> keepLink;
//    keepLink.resize(G->links.size(),false);
            std::vector<long> idsToKeep;
            std::vector<Number*> numbersRepresentingNodes;
            std::vector<bool> inDijkstra;
            std::vector<bool> inCutoff;
            Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
            double E=0.0;
            double ETrips=0.0;
            double N=0.0;
            double trips=0.0;
            for(long i=0;i<G->nodes.size();i++){
                if(G->nodes[i]->mass>0){
                  N+=1.0;
//                    double m=G->nodes[i]->mass;
                    // double distanceLimit=sqrt(-2*c*c*log(0.01/m));
//                    double distanceLimit=d0*pow(((m/0.01)-1),1/exponent);
                    double distanceLimit=0;
                    InterfaceDijkstra ID;
                    Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
                    for(long j=0;j<ID.idsInCutoff.size();j++){
                        double id=ID.idsInCutoff[j];
                        double distance=ID.getMinDistance(id);

                        if(distance<INFINITY&&distance>0&&G->nodes[id]->mass>0){

                            double distanceCrow=Functions::getDistance(G->nodes[i]->location,G->nodes[id]->location);
                            double flowToAdd=SpatialInteraction::kernelDistanceDecay(distanceCrow,d0)*G->nodes[i]->mass*G->nodes[id]->mass;
                            E=E+distanceCrow/distance;
                            ETrips=ETrips+distanceCrow/distance*flowToAdd;
                            trips+=flowToAdd;
//                             long node=id;
//                             long parent=ID.getParentID(id);
//                             while(parent!=-1){
// //                                long node=node;
//
//                                 for(long h=0;h<G->nodes[parent]->links.size();h++){
//                                     if(G->nodes[parent]->links[h]->getOtherNode(G->nodes[parent])->id==node){
//                                         idsToKeep.push_back(G->nodes[parent]->links[h]->id);
//                                     }
//                                 }
//                                 node=parent;
//                                 parent=ID.getParentID(parent);
//
//                             }
                        }
                    }
                }
            }
            Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
            E=E/(N*(N-1));
            ETrips/=trips;
            std::vector<double> result={E,ETrips};
            return result;
    // Grafo::inducedSubgraphFromLinks(G, result, idsToKeep);

}

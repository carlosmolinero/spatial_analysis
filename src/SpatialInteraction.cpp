#include "SpatialInteraction.h"
double SpatialInteraction::multiplierN=1;

void SpatialInteraction::setMultiplierN(double multiplierN){
  SpatialInteraction::multiplierN=multiplierN;
}
double SpatialInteraction::calculate_pd(double distance,double D,double maxDistance,std::vector<double>& N){
  double p_d=0;
  // std::cout<<N.size()<<'\n';
  for(long i=0;i<N.size();i++){
    // std::cout<<D<<" "<<distance<<" "<<maxDistance<<" "<<N[i]<<'\n';
    if (distance>=maxDistance){
      distance=maxDistance-.1;
    }
    p_d+=D*N[i]*pow(maxDistance,-D)*pow(distance,D-1)*pow(1-pow(maxDistance,-D)*pow(distance,D),N[i]-1);
  }
  return p_d;
}

Distribution SpatialInteraction::calculate_pd_forCity_i(Grafo* G,long idNodeInit,double maxDistanceSystem, double pop_max_mun){
  // std::vector<double>& distances,double D,double maxDistance,std::vector<double>& pop_i,std::vector<double>& area_j)
  // std::cout<<SpatialInteraction::multiplierN<<'\n';
  double D=1.85;
  // double N_min=2.46E3;
  // if (maxDistanceSystem<1.9E6){
  //   maxDistanceSystem=1.9E6;
  // }

  double N_min=7120/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  if (N_min<1){
    N_min=1;
  }

  double N_max0=770403/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  // double N_max0=maxDistanceSystem;
  double N_max1=(7030634+N_max0)/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);


  // double N_min=1367/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  // // double N_min=1;
  // if (N_min<1){
  //   N_min=1;
  // }
  //
  // // double N_max0=437732/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  // double N_max0=478021/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  // // double N_max0=maxDistanceSystem;
  // // double N_max1=(9351060+N_max0)/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  // double N_max1=(3650404+N_max0)/pow(1.9E6/2,D)*pow(maxDistanceSystem/2,D);
  // // double N_max1=std::pow(maxDistanceSystem,1.2);
  double pop_i_min=1E3;

  double normalised_pop_i_mun=(G->nodes[idNodeInit]->mass_upperLevel)-pop_i_min;
  if (normalised_pop_i_mun<0){
    normalised_pop_i_mun=0;
  }
  normalised_pop_i_mun=normalised_pop_i_mun/(pop_max_mun-pop_i_min);
  double N_max_current=normalised_pop_i_mun*(N_max1-N_max0)+N_max0;
  std::vector<double> N;
  N.reserve(5000);
  for(double i=0;i<5000;i++){
    N.push_back(exp(log(N_max_current-N_min)*i/4999.)+N_min);
    // std::cout<<N[i]<<'\n';
  }
  // std::vector<double> distances_logged;
  // distances_logged.reserve(100);
  Fxy p_d;
  p_d.x.resize(100,0);
  p_d.y.resize(100,0);
  // double locationMaximum=0;
  // double maximum=0;
  for(double i=0;i<100;i++){
    p_d.x[i]=exp(log(maxDistanceSystem+1)*i/99.)-1;
    p_d.y[i]=SpatialInteraction::calculate_pd(p_d.x[i],D,maxDistanceSystem,N);
    // if (p_d.y[i]>maximum){
    //   maximum=p_d.y[i];
    //   locationMaximum=p_d.x[i];
    // }

    // std::cout<<p_d.x[i]<<" "<<p_d.y[i]<<" "<<ID.maxDistanceInSystem<<'\n';
  }
  // std::cout<<"location maximum p_d: "<<locationMaximum<<'\n';
  // std::cout<<"max distance: "<<ID.maxDistanceInSystem<<'\n';
  // if(ID.idNodeInit==227020){
  //   std::cout<<"data.frame(x=c(";
  //   for(long i=0;i<p_d.x.size();i++){
  //     std::cout<<p_d.x[i];
  //     if(i<p_d.x.size()-1){
  //       std::cout<<",";
  //     }
  //   }
  //   std::cout<<"),y=c(";
  //   for(long i=0;i<p_d.x.size();i++){
  //     std::cout<<p_d.y[i];
  //     if(i<p_d.x.size()-1){
  //       std::cout<<",";
  //     }
  //   }
  //   std::cout<<"))"<<'\n';
  // }
  // std::cout<<'\n';
  Distribution cdf_pd=Distribution::createCDFDistributionFromData(p_d);
  // if(ID.idNodeInit==227020){
  //   std::cout<<"data.frame(x=c(";
  //   for(long i=0;i<cdf_pd.f.x.size();i++){
  //     std::cout<<cdf_pd.f.x[i];
  //     if(i<cdf_pd.f.x.size()-1){
  //       std::cout<<",";
  //     }
  //   }
  //   std::cout<<"),y=c(";
  //   for(long i=0;i<cdf_pd.f.x.size();i++){
  //     std::cout<<cdf_pd.f.y[i];
  //     if(i<cdf_pd.f.x.size()-1){
  //       std::cout<<",";
  //     }
  //   }
  //   std::cout<<"))"<<'\n';
  // }
  return cdf_pd;

}

double SpatialInteraction::kernelDistanceDecay(double distance, double L, Distribution& cdf_pd){
  double maxDistance=distance+L/2;
  double minDistance=distance-L/2;
  double maxDistanceB=0;
  if (minDistance<0){
    maxDistanceB=Functions::abs(minDistance);
    minDistance=0;
  }
  std::vector<double> ds;
  ds.push_back(maxDistance);
  ds.push_back(maxDistanceB);

  std::vector<double> orderedDs=Functions::orderValues(ds,true);
  Fxy ps=cdf_pd.getP(orderedDs);
  // std::vector<double> orderedPs=Functions::orderValues(ps,true);
  // std::cout<<ps.y[0]<<" "<<ps.y[1]<<" "<<cdf_pd.getP(maxDistance).y[0]<<" "<<L<<" "<<cdf_pd.f.y[3]<<'\n';
  return (ps.y[0]+ps.y[1]-cdf_pd.getP(minDistance).y[0]+.000005)*L;//the +.05 is to try to avoid rounding errors when distance is large
}

double SpatialInteraction::kernelDistanceDecay(double distance,double d0){
//    double d0=80000;//80000

    // return (1.0/(distance*distance));
    // double beta=1.0;
    // return (exp(-beta*distance));
    // double a=1;
    // double b=.1;
    // double c=100;
    // return (a-a/(1+exp(-b*(distance-c))));

    return (2.0/(1.0+distance*distance/d0/d0)/(M_PI*d0));
}
double SpatialInteraction::kernelDistanceDecay(double distance){
    double d0=1300;//80000

    // return (1.0/(distance*distance));
    // double beta=1.0;
    // return (exp(-beta*distance));
    // double a=1;
    // double b=.1;
    // double c=100;
    // return (a-a/(1+exp(-b*(distance-c))));

    return (2.0/(1.0+distance*distance/d0/d0)/(M_PI*d0));
}
double SpatialInteraction::modificationSpeedWithCongestion(double flow, double capacity,double alpha, double beta){
    // double alpha=.15;
    // double beta=4;

    return 1.0/(1.0+alpha*pow(flow/capacity,beta));
//    double J=1;
//    double modifier=1.0/(1.0+J*flow/(capacity-flow));
//    return Functions::max(.001,modifier);


}

double SpatialInteraction::normalisingFactorTripsFromCity(Grafo* G,InterfaceDijkstra& ID){

      double sumProbabilitiesGoingToCities=0;
      for(long i=0;i<G->nodes.size();i++){
          if(G->nodes[i]->mass>0){
            double distance=ShapeFile::calculateDistanceLatLon(G->nodes[i]->location,G->nodes[ID.idNodeInit]->location);
              // double distance=ID.getMinDistance(G->nodes[i]->id);
              sumProbabilitiesGoingToCities+=kernelDistanceDecay(distance)*G->nodes[i]->mass;

          }
      }


    return sumProbabilitiesGoingToCities;
}

double SpatialInteraction::normalisingFactorTripsFromCity(Grafo* G,long idNodeInit,Distribution& cdf_pd){

      double sumProbabilitiesGoingToCities=0;
      std::vector<double> distances;
      std::vector<double> kernels;
      // std::cout<<"id node init: "<<ID.idNodeInit<<'\n';
      for(long i=0;i<G->nodes.size();i++){
          if(G->nodes[i]->mass>0){
              double distance=ShapeFile::calculateDistanceLatLon(G->nodes[i]->location,G->nodes[idNodeInit]->location);
              // std::cout<<"normalisingFactorTripsFromCity"<<" "<<distance<<" "<<(G->nodes[i]->equivalentArea)<<" "<<cdf_pd.f.x[1]<<'\n';
              sumProbabilitiesGoingToCities+=kernelDistanceDecay(distance,std::sqrt(G->nodes[i]->equivalentArea),cdf_pd);
                // if(ID.idNodeInit==227020){
                  // distances.push_back(distance);
                  // kernels.push_back(kernelDistanceDecay(distance,std::sqrt(G->nodes[i]->equivalentArea),cdf_pd));
                // }
              // std::cout<<"normalisingFactorTripsFromCity"<<" "<<kernelDistanceDecay(distance,std::sqrt(G->nodes[i]->equivalentArea),cdf_pd)<<'\n';
          }
      }
      // if(ID.idNodeInit==227020||sumProbabilitiesGoingToCities<0){
      //   std::cout<<"data.frame(x=c(";
      //   for(long i=0;i<distances.size();i++){
      //     std::cout<<distances[i];
      //     if(i<distances.size()-1){
      //       std::cout<<",";
      //     }
      //   }
      //   std::cout<<"),y=c(";
      //   for(long i=0;i<distances.size();i++){
      //     std::cout<<kernels[i];
      //     if(i<distances.size()-1){
      //       std::cout<<",";
      //     }
      //   }
      //   std::cout<<"))"<<'\n';
      // }
      // std::cout<<"sumProbabilitiesGoingToCities="<<sumProbabilitiesGoingToCities<<'\n';

    return sumProbabilitiesGoingToCities;
}

void SpatialInteraction::calculateTotalTrips_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &trips){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY&&distance>0){
                    trips[i]+=SpatialInteraction::kernelDistanceDecay(distance)*(G->nodes[id]->mass);
                }
            }
        }
//        ID.reset();

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}

void SpatialInteraction::calculateTotalDistanceTravelled_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &distances){
std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            double normalisingFactorTripsFromCity=SpatialInteraction::normalisingFactorTripsFromCity(G,ID);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY&&distance>0){
                    distances[i]+=SpatialInteraction::kernelDistanceDecay(distance)*(G->nodes[id]->mass)*distance/normalisingFactorTripsFromCity;
                }
            }
        }
//        ID.reset();

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}

void SpatialInteraction::calculateTotalTripsFromEachNode(Grafo* G,double distanceLimit,std::vector<double> &trips){
    int numThreads=Configuration::numThreads;
    trips.clear();
    if(trips.size()==0){
        trips.resize(G->nodes.size(),0);
    }
     double numNodesPerThread=floor(G->nodes.size()/numThreads);

     std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&SpatialInteraction::calculateTotalTrips_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(trips)));

    }

    for(auto& thread : threads)
    {
        thread.join();
    }
    for(long i=0;i<trips.size();i++){
        trips[i]*=G->nodes[i]->mass;
    }

}
void SpatialInteraction::calculateTotalDistanceTravelledFromEachNode(Grafo* G,double distanceLimit,std::vector<double> &distances){
  int numThreads=Configuration::numThreads;
    distances.clear();
    if(distances.size()==0){
        distances.resize(G->nodes.size(),0);
    }
     double numNodesPerThread=floor(G->nodes.size()/numThreads);

     std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&SpatialInteraction::calculateTotalDistanceTravelled_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(distances)));

    }

    for(auto& thread : threads)
    {
        thread.join();
    }
    for(long i=0;i<distances.size();i++){
        distances[i]*=G->nodes[i]->mass;
    }

}

std::pair<double,double> SpatialInteraction::calculateRobustness(Grafo* G){
    DualExtendedGraph deg;
    DualExtendedGraph::addPrimal(&deg,G);
//    G->reset();
//    Grafo G2;
//    G2=deg.getStructuralGraph();
    std::pair<double,double> pair;
    double repetitions=50.0;
    double averagedLengthRemoved=0;
    double averagedNumberLinksRemoved=0;
    double totalMass=0;
    for(long i=0;i<deg.getStructuralGraph()->nodes.size();i++){
        totalMass+=deg.getStructuralGraph()->nodes[i]->mass;
    }
    double tsl=0;
    for(long i=0;i<deg.getStructuralGraph()->links.size();i++){
        tsl+=deg.getStructuralGraph()->links[i]->weight;
    }
    std::vector<long> idRoadsPerMeter;
    idRoadsPerMeter.reserve(tsl);
    for(long i=0;i<deg.getStructuralGraph()->links.size();i++){
        for(long j=0;j<deg.getStructuralGraph()->links[i]->weight;j++){
            idRoadsPerMeter.push_back(i);
        }
    }

    for(long i=0;i<repetitions;i++){
        Grafo LG_;
        Grafo::getLargestComponent(deg.getStructuralGraph(),&LG_);

        bool STOP=false;
        double lengthLinksRemoved=0;
        long numberLinksRemoved=0;
        long numberLinksToRemove=0;
        while(!STOP){
            numberLinksToRemove++;
            Grafo LG;
            LG.reset();
            LG.copyGraph(&LG_);
            std::set<long> linksToRemove;
            for(long j=0;j<numberLinksToRemove;j++){
                long indexRandomMeter=Functions::runiform(0,idRoadsPerMeter.size()-1);
                long indexRandomLink=idRoadsPerMeter[indexRandomMeter];
                linksToRemove.insert(indexRandomLink);
            }

            numberLinksRemoved=linksToRemove.size();
            lengthLinksRemoved=numberLinksToRemove;
            LG.removeLinks(linksToRemove);
            std::vector<long> colors;
            std::vector<double> sizes;
            long maxColor;
            Grafo::getLinkColorsFromNetworkPercolation(&LG,INFINITY,colors,sizes,maxColor);

            for(long j=0;j<LG.nodes.size();j++){
                if(LG.nodes[j]->getDegree()==0&&LG.nodes[j]->mass>0){
                    STOP=true;
                }
            }
            if(maxColor>0){
                std::vector<long> nodesColor;
                Grafo::transformColorsLinksIntoColorsNodes(&LG, colors, nodesColor);
                std::vector<double> massesInClusters;
                massesInClusters.resize(maxColor+1,0);
                for(long j=0;j<LG.nodes.size();j++){
                    if(nodesColor[j]!=-1){
                        massesInClusters[nodesColor[j]]+=LG.nodes[j]->mass;
                    }
                }
                for(long j=0;j<massesInClusters.size();j++){
                    if(massesInClusters[j]!=totalMass&&massesInClusters[j]!=0){
                        STOP=true;
                        break;
                    }
                }

            }

        }
        averagedLengthRemoved+=lengthLinksRemoved;
        averagedNumberLinksRemoved+=numberLinksRemoved;
    }
    averagedLengthRemoved/=repetitions;
    averagedNumberLinksRemoved/=repetitions;
    pair.first=averagedLengthRemoved;
    pair.second=averagedNumberLinksRemoved;
    return pair;

}


std::pair<double,double> SpatialInteraction::calculateRobustness(Grafo* G,long repetitions){
    DualExtendedGraph deg;
    DualExtendedGraph::addPrimal(&deg,G);
    //    G->reset();
    //    Grafo G2;
    //    G2=deg.getStructuralGraph();
    std::pair<double,double> pair;
//    double repetitions=50.0;
    double averagedLengthRemoved=0;
    double averagedNumberLinksRemoved=0;
    double totalMass=0;
    for(long i=0;i<deg.getStructuralGraph()->nodes.size();i++){
        totalMass+=deg.getStructuralGraph()->nodes[i]->mass;
    }
    double tsl=0;
    for(long i=0;i<deg.getStructuralGraph()->links.size();i++){
        tsl+=deg.getStructuralGraph()->links[i]->weight;
    }
    std::vector<long> idRoadsPerMeter;
    idRoadsPerMeter.reserve(tsl);
    for(long i=0;i<deg.getStructuralGraph()->links.size();i++){
        for(long j=0;j<deg.getStructuralGraph()->links[i]->weight;j++){
            idRoadsPerMeter.push_back(i);
        }
    }

    for(long i=0;i<repetitions;i++){
        Grafo LG_;
        Grafo::getLargestComponent(deg.getStructuralGraph(),&LG_);

        bool STOP=false;
        double lengthLinksRemoved=0;
        long numberLinksRemoved=0;
        long numberLinksToRemove=0;
        while(!STOP){
            numberLinksToRemove++;
            Grafo LG;
            LG.reset();
            LG.copyGraph(&LG_);
            std::set<long> linksToRemove;
            for(long j=0;j<numberLinksToRemove;j++){
                long indexRandomMeter=Functions::runiform(0,idRoadsPerMeter.size()-1);
                long indexRandomLink=idRoadsPerMeter[indexRandomMeter];
                linksToRemove.insert(indexRandomLink);
            }

            numberLinksRemoved=linksToRemove.size();
            lengthLinksRemoved=numberLinksToRemove;
            LG.removeLinks(linksToRemove);
            std::vector<long> colors;
            std::vector<double> sizes;
            long maxColor;
            Grafo::getLinkColorsFromNetworkPercolation(&LG,INFINITY,colors,sizes,maxColor);

            for(long j=0;j<LG.nodes.size();j++){
                if(LG.nodes[j]->getDegree()==0&&LG.nodes[j]->mass>0){
                    STOP=true;
                }
            }
            if(maxColor>0){
                std::vector<long> nodesColor;
                Grafo::transformColorsLinksIntoColorsNodes(&LG, colors, nodesColor);
                std::vector<double> massesInClusters;
                massesInClusters.resize(maxColor+1,0);
                for(long j=0;j<LG.nodes.size();j++){
                    if(nodesColor[j]!=-1){
                        massesInClusters[nodesColor[j]]+=LG.nodes[j]->mass;
                    }
                }
                for(long j=0;j<massesInClusters.size();j++){
                    if(massesInClusters[j]!=totalMass&&massesInClusters[j]!=0){
                        STOP=true;
                        break;
                    }
                }

            }

        }
        averagedLengthRemoved+=lengthLinksRemoved;
        averagedNumberLinksRemoved+=numberLinksRemoved;
    }
    averagedLengthRemoved/=repetitions;
    averagedNumberLinksRemoved/=repetitions;
    pair.first=averagedLengthRemoved;
    pair.second=averagedNumberLinksRemoved;
    return pair;

}









void SpatialInteraction::calculateFlow(Grafo* G,double distanceLimit,std::vector<double> &flows){
    int numThreads=Configuration::numThreads;
    flows.clear();
    if(flows.size()==0){
        flows.resize(G->nodes.size(),0);
    }
    double numNodesPerThread=floor(G->nodes.size()/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&SpatialInteraction::calculateFlow_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(flows)));

    }
    for(auto& thread : threads)
    {
        thread.join();
    }
}


void SpatialInteraction::calculateFlow_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &flows){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
//    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);

            SpatialInteraction::calculateFlow_singleNode(G, ID, flows);
            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}



void SpatialInteraction::calculateFlow_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &flows){
    std::vector<double> valuesToPass;
//    bool fillingUpValuesToPass=false;
//    if(valuesToPass.size()==0){
//        fillingUpValuesToPass=true;
        valuesToPass.resize(G->nodes.size(),1);
//    }
    std::vector<double> originalValuesToPass;
    originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;

    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
//        if(fillingUpValuesToPass){
            valuesToPass[i]=G->nodes[i]->mass*SpatialInteraction::kernelDistanceDecay(minDistances.getMinDistance(G->nodes[i]->id));
//        }
        originalValuesToPass[i]=valuesToPass[i];
    }
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

//    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
//            double valueToPass;
//            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                if(parent!=nodeInit){
                    flows[parent->id]=flows[parent->id]+((valuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                }
                valuesToPass[parent->id]+=valuesToPass[node->id];

                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else{
                valuesToPass[parent->id]+=valuesToPass[node->id];

                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }
        }
//        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
//        {
//            valuesToPass[parent->id]+=valuesToPass[node->id];
//
//            numChildrenThatReachMe[parent->id]++;
//        }
    }
    valuesToPass.clear();


}













void SpatialInteraction::calculateEdgeFlow(Grafo* G,double distanceLimit,InterfaceFlows& flows){
    int numThreads=Configuration::numThreads;
    // flows.clear();
    // if(flows.size()==0){
    //     flows.resize(G->links.size(),0);
    // }
    double numNodesPerThread=floor(G->nodes.size()/numThreads);
    double maxPopMun=0;
    for(long i=0;i<G->nodes.size();i++){
      if (G->nodes[i]->mass_upperLevel>maxPopMun){
        maxPopMun=G->nodes[i]->mass_upperLevel;
      }
    }
    // std::vector<std::thread> threads;
    // for (int i=0; i<numThreads; i++)
    // {
    //
    //     long startNode=i*numNodesPerThread;
    //     long endNode=(i+1)*numNodesPerThread;
    //     if (i==numThreads-1)
    //     {
    //         endNode=G->nodes.size();
    //     }
    //
    //     threads.push_back(std::thread(&SpatialInteraction::calculateEdgeFlow_aux,std::ref(G),startNode,endNode,distanceLimit,maxPopMun,std::ref(flows)));
    //
    // }
    // for(auto& thread : threads)
    // {
    //     thread.join();
    // }
    SpatialInteraction::calculateEdgeFlow_aux(G,0,G->nodes.size(),distanceLimit,maxPopMun,flows);

}

void SpatialInteraction::calculateNormalisedEdgeFlow(Grafo* G,double distanceLimit,InterfaceFlows& flows,double& outgoingTrips){
    std::cout<<"coming back after a long time to the code, I do not understand the use of this function, beware, seems it is used to calculate the flow traversed"<<'\n';
    int numThreads=Configuration::numThreads;
    // flows.clear();
    // if(flows.size()==0){
    //     flows.resize(G->links.size(),0);
    // }
    double numNodesPerThread=floor(G->nodes.size()/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&SpatialInteraction::calculateNormalisedEdgeFlow_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(flows),std::ref(outgoingTrips)));

    }
    for(auto& thread : threads)
    {
        thread.join();
    }
    double totalFlow=0;

    for(long i=0;i<G->links.size();i++){
        totalFlow+=flows.flows[0][i];
    }
    for(long i=0;i<G->links.size();i++){
        flows.flows[0][i]/=totalFlow;
    }
}

void SpatialInteraction::calculateEdgeFlow_aux(Grafo* G,long startNode,long endNode,double distanceLimit,double maxPopMun,InterfaceFlows& flows){
    // int type=0; //using kernel distance from 1/(d^2+1)
    int type=1; // using kernel distance based on closest objects
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
    double maxx=-INFINITY;
    double minx=INFINITY;
    double maxy=-INFINITY;
    double miny=INFINITY;
    for(long i=0;i<G->nodes.size();i++){
      if(G->nodes[i]->location.x>maxx){
        maxx=G->nodes[i]->location.x;
      }
      if(G->nodes[i]->location.x<minx){
        minx=G->nodes[i]->location.x;
      }
      if(G->nodes[i]->location.y>maxy){
        maxy=G->nodes[i]->location.y;
      }
      if(G->nodes[i]->location.y<miny){
        miny=G->nodes[i]->location.y;
      }
    }
    double maxPossibleDistance=ShapeFile::calculateDistanceLatLon(maxx,maxy,minx,miny);

//    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
      if(i%10000==0){
        std::cout<<"calculating node "<<i<<" where endNode is "<<endNode<<'\n';
      }
        if(G->nodes[i]->mass>0){
          // endNode=startNode+1;
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);

            if (type==0){
              // flows.setDistances(maxPossibleDistance);
              double normalisingFactorTripsFromCity=SpatialInteraction::normalisingFactorTripsFromCity(G,ID);
              SpatialInteraction::calculateEdgeFlow_singleNode(G, ID, flows,normalisingFactorTripsFromCity);
            }
            if (type==1){
              // flows.setDistances(maxPossibleDistance);
              Distribution cdf_pd=SpatialInteraction::calculate_pd_forCity_i(G,G->nodes[i]->id,maxPossibleDistance, maxPopMun);
              double normalisingFactorTripsFromCity=SpatialInteraction::normalisingFactorTripsFromCity(G,G->nodes[i]->id,cdf_pd);
              SpatialInteraction::calculateEdgeFlow_singleNode(G, ID, flows,normalisingFactorTripsFromCity,cdf_pd);
            }


            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}
void SpatialInteraction::calculateNormalisedEdgeFlow_aux(Grafo* G,long startNode,long endNode,double distanceLimit,InterfaceFlows& flows,double& outgoingTrips){

    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
    //    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            double normalisingFactorTripsFromCity=SpatialInteraction::normalisingFactorTripsFromCity(G,ID);
            for(long j=0;j<G->nodes.size();j++){
                if(j!=i&&G->nodes[j]->mass>0){
                    outgoingTrips+=SpatialInteraction::kernelDistanceDecay(ID.getMinDistance(j))/normalisingFactorTripsFromCity*G->nodes[j]->mass*G->nodes[i]->mass;
                }
            }
            SpatialInteraction::calculateEdgeFlow_singleNode(G, ID, flows,normalisingFactorTripsFromCity);
            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}


void SpatialInteraction::calculateEdgeFlow_singleNode(Grafo* G,InterfaceDijkstra &minDistances,InterfaceFlows& flows,double normalisingValueTrips){
    // std::vector<double> valuesToPass;
//    bool fillingUpValuesToPass=false;
//    if(valuesToPass.size()==0){
//        fillingUpValuesToPass=true;
        // valuesToPass.resize(G->nodes.size(),0);
//    }
    // std::vector<double> originalValuesToPass;
    // originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;

    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
//        if(fillingUpValuesToPass){
          if (G->nodes[i]->mass>0){
            double distance=ShapeFile::calculateDistanceLatLon(G->nodes[minDistances.idNodeInit]->location,G->nodes[i]->location);
            double value=G->nodes[i]->mass*SpatialInteraction::kernelDistanceDecay(distance)/normalisingValueTrips*nodeInit->mass;
            flows.setValuesToPass(i,distance,value);
          }
//        }
        // originalValuesToPass[i]=valuesToPass[i];
    }
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

//    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
//            double valueToPass;
//            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                // if(parent!=nodeInit){
                    Link* currentLink=NULL;
                    for(long j=0;j<parent->links.size();j++){
                        if(parent->links[j]->getOtherNode(parent)==node){
                            currentLink=parent->links[j];
                        }
                    }
                    // flows[currentLink->id]=flows[currentLink->id]+((valuesToPass[node->id]))*nodeInit->mass;
                    flows.accumulateFlow(currentLink->id,node->id);
    //                flows[node->id]=flows[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                // }
                // valuesToPass[parent->id]+=valuesToPass[node->id];
                flows.passValuesToParent(node->id,parent->id);

                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else{
                // valuesToPass[parent->id]+=valuesToPass[node->id];
                Link* currentLink=NULL;
                for(long j=0;j<parent->links.size();j++){
                    if(parent->links[j]->getOtherNode(parent)==node){
                        currentLink=parent->links[j];
                    }
                }
                // flows[currentLink->id]=flows[currentLink->id]+((valuesToPass[node->id]))*nodeInit->mass;
                flows.accumulateFlow(currentLink->id,node->id);
                flows.passValuesToParent(node->id,parent->id);
                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }
        }
//        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
//        {
//            valuesToPass[parent->id]+=valuesToPass[node->id];
//
//            numChildrenThatReachMe[parent->id]++;
//        }
    }
    // valuesToPass.clear();


}



void SpatialInteraction::calculateEdgeFlow_singleNode(Grafo* G,InterfaceDijkstra &minDistances,InterfaceFlows& flows,double normalisingValueTrips, Distribution& cdf_pd){
    // std::vector<double> valuesToPass;
//    bool fillingUpValuesToPass=false;
//    if(valuesToPass.size()==0){
//        fillingUpValuesToPass=true;
        // valuesToPass.resize(G->nodes.size(),0);
//    }
    // std::vector<double> originalValuesToPass;
    // originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;
    // double totalValuesToPass=0;
    flows.resetValuesToPass();
    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
//        if(fillingUpValuesToPass){
            // std::cout<<SpatialInteraction::kernelDistanceDecay(minDistances.getMinDistance(G->nodes[i]->id),std::sqrt(G->nodes[i]->equivalentArea),cdf_pd)<<" "<<normalisingValueTrips<<'\n';
            if (G->nodes[i]->mass>0){
              double distance=ShapeFile::calculateDistanceLatLon(G->nodes[minDistances.idNodeInit]->location,G->nodes[i]->location);

              double value=(SpatialInteraction::kernelDistanceDecay(distance,std::sqrt(G->nodes[i]->equivalentArea),cdf_pd)/normalisingValueTrips)*nodeInit->mass;
              flows.setValuesToPass(i,distance,value);
              // totalValuesToPass+=valuesToPass[i]/nodeInit->mass;
              // std::cout<<valuesToPass[i]<<" "<<SpatialInteraction::kernelDistanceDecay(minDistances.getMinDistance(G->nodes[i]->id),std::sqrt(G->nodes[i]->equivalentArea),cdf_pd)<<" "<<normalisingValueTrips<<'\n';
            }else{
              // valuesToPass[i]=0;
            }

//        }
        // originalValuesToPass[i]=valuesToPass[i];
    }
    // std::cout<<"values to pass total normalised"<<totalValuesToPass<<'\n';
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

//    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
//            double valueToPass;
//            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                // if(parent!=nodeInit){
                    Link* currentLink=NULL;
                    for(long j=0;j<parent->links.size();j++){
                        if(parent->links[j]->getOtherNode(parent)==node){
                            currentLink=parent->links[j];
                        }
                    }
                    flows.accumulateFlow(currentLink->id,node->id);
                    // flows[currentLink->id]=flows[currentLink->id]+((valuesToPass[node->id]));
    //                flows[node->id]=flows[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                // }
                flows.passValuesToParent(node->id,parent->id);
                // valuesToPass[parent->id]+=valuesToPass[node->id];
                // valuesToPass[node->id]=0;
                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else if(minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1){

                Link* currentLink=NULL;
                for(long j=0;j<parent->links.size();j++){
                    if(parent->links[j]->getOtherNode(parent)==node){
                        currentLink=parent->links[j];
                    }
                }
                // flows[currentLink->id]=flows[currentLink->id]+((valuesToPass[node->id]));
                flows.accumulateFlow(currentLink->id,node->id);
                flows.passValuesToParent(node->id,parent->id);
                // valuesToPass[parent->id]+=valuesToPass[node->id];
                // valuesToPass[node->id]=0;
                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }else{
              STOP=true;
              std::cout<<"this is very strange"<<'\n';
            }
        }
//        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
//        {
//            valuesToPass[parent->id]+=valuesToPass[node->id];
//
//            numChildrenThatReachMe[parent->id]++;
//        }
    }
    // valuesToPass.clear();


}



void SpatialInteraction::calculateFlowPerMeterAndIntersectionsPerMeter(Grafo* G,double distanceLimit,std::vector<double> &edgeFlows,std::vector<double>& flowPerMeter,std::vector<double>& intersectionsPerMeter){
    int numThreads=Configuration::numThreads;
    flowPerMeter.clear();
    if(flowPerMeter.size()==0){
        flowPerMeter.resize(G->nodes.size(),0);
    }
    intersectionsPerMeter.clear();
    if(intersectionsPerMeter.size()==0){
        intersectionsPerMeter.resize(G->nodes.size(),0);
    }
    double numNodesPerThread=floor(G->nodes.size()/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&SpatialInteraction::calculateFlowPerMeterAndIntersectionsPerMeter_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(edgeFlows),std::ref(flowPerMeter),std::ref(intersectionsPerMeter)));

    }
    for(auto& thread : threads)
    {
        thread.join();
    }

}

void SpatialInteraction::calculateFlowPerMeterAndIntersectionsPerMeter_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &edgeFlows,std::vector<double>& flowPerMeter,std::vector<double>& intersectionsPerMeter){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
//    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            double normalisingFactorTripsFromCity=SpatialInteraction::normalisingFactorTripsFromCity(G,ID);

            SpatialInteraction::calculateFlowPerMeterAndIntersectionsPerMeter_singleNode(G, ID, edgeFlows,normalisingFactorTripsFromCity,flowPerMeter,intersectionsPerMeter);
            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}





void SpatialInteraction::calculateFlowPerMeterAndIntersectionsPerMeter_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &edgeFlows,double normalisingValueTrips,std::vector<double>& flowPerMeter,std::vector<double>& intersectionsPerMeter){
    std::vector<double> valuesToPass;
//    bool fillingUpValuesToPass=false;
//    if(valuesToPass.size()==0){
//        fillingUpValuesToPass=true;
        valuesToPass.resize(G->nodes.size(),1);
//    }
    std::vector<double> originalValuesToPass;
    originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;

    double distance=0;

    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
//        if(fillingUpValuesToPass){
            valuesToPass[i]=G->nodes[i]->mass*SpatialInteraction::kernelDistanceDecay(minDistances.getMinDistance(G->nodes[i]->id))/normalisingValueTrips;
//        }
        originalValuesToPass[i]=valuesToPass[i];
    }
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

//    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        double flowPerMeter_=0;
        double intersectionsPerMeter_=0;
        double distance_=0;
        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
//            double valueToPass;
//            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                // if(parent!=nodeInit){
                    Link* currentLink=NULL;
                    for(long j=0;j<parent->links.size();j++){
                        if(parent->links[j]->getOtherNode(parent)==node){
                            currentLink=parent->links[j];
                        }
                    }
                    flowPerMeter_+=edgeFlows[currentLink->id]*currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
                    intersectionsPerMeter_+=1.0*((valuesToPass[node->id]))*nodeInit->mass/(double)(minDistances.getNumChildren(parent->id));
                    distance_+=currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                // }
                valuesToPass[parent->id]+=valuesToPass[node->id];

                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else{
                valuesToPass[parent->id]+=valuesToPass[node->id];
                Link* currentLink=NULL;
                for(long j=0;j<parent->links.size();j++){
                    if(parent->links[j]->getOtherNode(parent)==node){
                        currentLink=parent->links[j];
                    }
                }
                flowPerMeter_+=edgeFlows[currentLink->id]*currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
                intersectionsPerMeter_+=1.0*((valuesToPass[node->id]))*nodeInit->mass/(double)(minDistances.getNumChildren(parent->id));
                distance_+=currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }
        }
        if(distance_>0){
            flowPerMeter[nodeInit->id]+=flowPerMeter_/distance_;
            intersectionsPerMeter[nodeInit->id]+=intersectionsPerMeter_/distance_;
//                        flowPerMeter[nodeInit->id]+=flowPerMeter_;
//                        intersectionsPerMeter[nodeInit->id]=intersectionsPerMeter_;

        }else{
//            std::cout<<"distance_ was "<<distance_<<'\n';
        }
//        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
//        {
//            valuesToPass[parent->id]+=valuesToPass[node->id];
//
//            numChildrenThatReachMe[parent->id]++;
//        }
    }
    valuesToPass.clear();

    flowPerMeter[nodeInit->id]/=(double)(leaves.size());
    intersectionsPerMeter[nodeInit->id]/=(double)(leaves.size());


}








void SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar(Grafo* G,double& flowTraversedPerCar,double& distancesPerCar,double& intersectionsTraversedPerCar,double& outgoingTrips){
    int numThreads=Configuration::numThreads;

    double distanceLimit=0;
    std::vector<double> edgeFlows;
    flowTraversedPerCar=0;
    distancesPerCar=0;
    intersectionsTraversedPerCar=0;
    outgoingTrips=0;

    // flowPerMeter.clear();
    // if(flowPerMeter.size()==0){
    //     flowPerMeter.resize(G->nodes.size(),0);
    // }
    // intersectionsPerMeter.clear();
    // if(intersectionsPerMeter.size()==0){
    //     intersectionsPerMeter.resize(G->nodes.size(),0);
    // }

    InterfaceFlows flows;
    // flows.setNumberSubdivisions(1);
    flows.initFlows(G->links.size());
    flows.initValuesToPass(G->nodes.size());
    SpatialInteraction::calculateEdgeFlow(G,distanceLimit,flows);
    edgeFlows=flows.getFlows(0);


    double numNodesPerThread=floor(G->nodes.size()/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(edgeFlows),std::ref(flowTraversedPerCar),std::ref(intersectionsTraversedPerCar),std::ref(distancesPerCar),std::ref(outgoingTrips)));

    }
    for(auto& thread : threads)
    {
        thread.join();
    }
    flowTraversedPerCar/=(double)(outgoingTrips*outgoingTrips);
    distancesPerCar/=(double)(outgoingTrips);
    intersectionsTraversedPerCar/=(double)(outgoingTrips);
}

void SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &edgeFlows,double& flowTraversedPerCar,double& intersectionsTraversedPerCar,double& distancesPerCar,double& outgoingTrips){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
    //    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            double normalisingFactorTripsFromCity=SpatialInteraction::normalisingFactorTripsFromCity(G,ID);
            for(long j=0;j<G->nodes.size();j++){
                if(j!=i&&G->nodes[j]->mass>0){
                    outgoingTrips+=SpatialInteraction::kernelDistanceDecay(ID.getMinDistance(j))/normalisingFactorTripsFromCity*G->nodes[j]->mass*G->nodes[i]->mass;
                }
            }
            SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar_singleNode(G, ID, edgeFlows,normalisingFactorTripsFromCity,flowTraversedPerCar,intersectionsTraversedPerCar,distancesPerCar);
            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}





void SpatialInteraction::calculateFlowTraversedAndDistanceAndIntersectionsTraversedPerCar_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &edgeFlows,double normalisingValueTrips,double& flowTraversedPerCar,double& intersectionsTraversedPerCar,double& distancesPerCar){
    std::vector<double> valuesToPass;
    //    bool fillingUpValuesToPass=false;
    //    if(valuesToPass.size()==0){
    //        fillingUpValuesToPass=true;
    valuesToPass.resize(G->nodes.size(),1);
    //    }
    std::vector<double> originalValuesToPass;
    originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;

//    double distance=0;

    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
        //        if(fillingUpValuesToPass){
        valuesToPass[i]=G->nodes[i]->mass*SpatialInteraction::kernelDistanceDecay(minDistances.getMinDistance(G->nodes[i]->id))/normalisingValueTrips;
        //        }
        originalValuesToPass[i]=valuesToPass[i];
    }
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

    //    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        // double flowPerMeter_=0;
        // double intersectionsPerMeter_=0;
        // double distance_=0;

        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
            //            double valueToPass;
            //            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                // if(parent!=nodeInit){
                Link* currentLink=NULL;
                for(long j=0;j<parent->links.size();j++){
                    if(parent->links[j]->getOtherNode(parent)==node){
                        currentLink=parent->links[j];
                    }
                }
                flowTraversedPerCar+=edgeFlows[currentLink->id]*currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
                if(parent->getDegree()>2){
                  intersectionsTraversedPerCar+=(parent->getDegree()-2.0)*((valuesToPass[node->id]))*nodeInit->mass;
                }
                // intersectionsTraversedPerCar+=1.0*((valuesToPass[node->id]))*nodeInit->mass;
                // intersectionsPerMeter_+=1.0*((valuesToPass[node->id]))*nodeInit->mass/(double)(minDistances.getNumChildren(parent->id));
                distancesPerCar+=currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
                //                flows[node->id]=flows[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
                //                flows[node->id]=flows[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                // }
                valuesToPass[parent->id]+=valuesToPass[node->id];

                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else{
                valuesToPass[parent->id]+=valuesToPass[node->id];
                Link* currentLink=NULL;
                for(long j=0;j<parent->links.size();j++){
                    if(parent->links[j]->getOtherNode(parent)==node){
                        currentLink=parent->links[j];
                    }
                }
                flowTraversedPerCar+=edgeFlows[currentLink->id]*currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
//                intersectionsTraversedPerCar+=1.0*((valuesToPass[node->id]))*nodeInit->mass;
                // intersectionsPerMeter_+=1.0*((valuesToPass[node->id]))*nodeInit->mass/(double)(minDistances.getNumChildren(parent->id));
                distancesPerCar+=currentLink->weight*((valuesToPass[node->id]))*nodeInit->mass;
                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }
        }
//        if(distance_>0){
            // flowPerMeter[nodeInit->id]+=flowPerMeter_/distance_;
            // intersectionsPerMeter[nodeInit->id]+=intersectionsPerMeter_/distance_;
            //                        flowPerMeter[nodeInit->id]+=flowPerMeter_;
            //                        intersectionsPerMeter[nodeInit->id]=intersectionsPerMeter_;

//        }else{
//                        std::cout<<"distance_ was "<<distance_<<'\n';
//        }
        //        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
        //        {
        //            valuesToPass[parent->id]+=valuesToPass[node->id];
        //
        //            numChildrenThatReachMe[parent->id]++;
        //        }
    }
    valuesToPass.clear();

    // flowPerMeter[nodeInit->id]/=(double)(leaves.size());
    // intersectionsPerMeter[nodeInit->id]/=(double)(leaves.size());


}























std::vector<double> SpatialInteraction::calculateTimesSegments(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta,double acceleration,double t,std::vector<double>& edgeFlows,double& numberTripsGenerated){
    Grafo* G=deg->getStructuralGraph();
    // std::vector<double> edgeFlows;
    // double outgoingTrips=0;
    if(edgeFlows.size()==0){
        SpatialInteraction::calculateFlowsInVehiclesPerSecond(G,t,edgeFlows,numberTripsGenerated);
    }
    std::vector<double> speedLimitsWithCongestion;
    speedLimitsWithCongestion.resize(speedLimits.size(),0);
    std::vector<double> times;
    times.resize(G->links.size(),0);


    for(long i=0;i<G->links.size();i++){
        speedLimitsWithCongestion[i]=speedLimits[i]*modificationSpeedWithCongestion(edgeFlows[i]/2.0,capacity,alpha,beta)*1000.0/3600.0;// m/
//            double waitingTimesAtIntersections=SpatialInteraction::calculateWaitingTimesAtIntersections(speedLimitsWithCongestion[i]*3600/1000);
        double waitingTimesAtIntersections=SpatialInteraction::calculateWaitingTimesAtIntersections(edgeFlows[i]);
          //flows divided by 2 because I am summing cars in both directions on top of the same segment
        double e=G->links[i]->weight;
//        double e1=pow(speedLimitsWithCongestion[i],2.0)/acceleration;
        double s=speedLimitsWithCongestion[i];
//        e=100
//        s=90
//        a=6
        double a=4.0;
        double t1=(s*1000.0/3600.0)/a;
        double e1=a*(t1*t1)/2.0;
        double t3=0;
        double t2=0;

        if(e1>e/2.0){
            t1=sqrt(e/a);
            e1=1.0/2.0*a*t1*t1;
            t3=t1;
            t2=0;
        }else{

            t3=t1;
            t2=(e-2.0*e1)/(s*1000.0/3600.0);
        }
        times[i]=(t1+t2+t3+waitingTimesAtIntersections)/3600.0;//h
//        times[i]=e/speedLimitsWithCongestion[i]+waitingTimesAtIntersections;
    }
    return times;

}



double SpatialInteraction::calculateWaitingTimesAtIntersections(double flow){
    double redSignalTime=100.0;//s
    double greenSignalTime=70.0;//s
    double T=redSignalTime+greenSignalTime;
    double G=greenSignalTime;
    double waitingTimes;
//    waitingTimes.resize(flows.size());
//    for(long i=0;i<modifiedSpeed.size();i++){
//        double rho=flows[i]/2.0;//divided by 2 because I am summing cars in both directions on top of the same segment
    double rho=flow;
//        double speed=modifiedSpeed;//km/h
//        double metersAtThisSpeedIn2seconds=speed*1000/3600*2;
//        double rho=1/(((5+metersAtThisSpeedIn2seconds)*3600.0)/(1000.0*speed));
//    if(modifiedSpeed==90){
//        rho=0.0;
//    }
//        if(rho>maxFlow){
//            rho=maxFlow;
//        }

         double speed=5;//km/h
         double metersAtThisSpeedIn2seconds=speed*1000/3600*2;
         double c=1/(((5+metersAtThisSpeedIn2seconds)*3600.0)/(1000.0*speed));
        double lambda=rho*c;
//        if(rho!=0&&rho!=1){
            double value=T*(1.0-G/T)*(1.0-G/T)/2.0/(1.0-G/T*rho)+rho*rho/(2.0*lambda*(1-rho))-0.65*pow((T/lambda/lambda),3.0)*pow(rho,2.0+5.0*G/T);//s
        double maxValue=redSignalTime*2;
        double probRed=redSignalTime/T;
//       double minWaitingTime=probRed*redSignalTime;
//         minWaitingTime=0;
        if(isfinite(value)){
            if(value<0){
                value=maxValue;
            }
            waitingTimes=Functions::min(value,maxValue);

        }else{
            if(rho>c){
                waitingTimes=maxValue;
            }else{
                waitingTimes=0;
            }
        }
//        waitingTimes[i]=Functions::max(waitingTimes[i],minWaitingTime);
//    }
    // waitingTimes+=redSignalTime/2.0;
    return waitingTimes;

}


std::vector<double> SpatialInteraction::calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta,double t){
    // double stopTimeAtIntersection=77.5;//   s
    double acceleration=4;// m/s
    Grafo* G=deg->getStructuralGraph();
    // for(long i=0;i<G->nodes.size();i++){
    //     std::cout<<"masses structural "<<G->nodes[i]->mass<<'\n';
    //     // Nodo* node=deg->getPrimalGraph()->getNodeByLocation(G->nodes[i]->location);
    //     // G->nodes[i]->mass=node->mass;
    // }
    std::vector<double> edgeFlows;
    double numberTripsGenerated=0;
    std::vector<double> timeWeights=SpatialInteraction::calculateTimesSegments(deg,speedLimits,capacity,alpha,beta,acceleration,t,edgeFlows,numberTripsGenerated);
    std::vector<double> originalWeights;
    originalWeights.resize(G->links.size(),0);
    std::vector<double> timesTravelled;
    std::vector<double> timesTravelled_structural;
    timesTravelled.resize(deg->getPrimalGraph()->nodes.size(),0);
    for(long i=0;i<G->links.size();i++){
        originalWeights[i]=G->links[i]->weight;
        G->links[i]->weight=timeWeights[i];
    }

    SpatialInteraction::calculateTotalDistanceTravelledFromEachNode(G,0,timesTravelled_structural);
    for(long i=0;i<G->links.size();i++){
        // originalWeights[i]=G->links[i]->weight;
        G->links[i]->weight=originalWeights[i];
    }

    // std::vector<double> valuesInPrimal;
    // valuesInPrimal.resize(deg->getPrimalGraph()->nodes.size(),0);

    for(long i=0;i<G->nodes.size();i++){
        Nodo* node=deg->getPrimalGraph()->getNodeByLocation(G->nodes[i]->location);
            // std::cout<<"masses structural= "<<G->nodes[i]->mass<<" timesTravelledStructural= "<<timesTravelled_structural[i]<<'\n';
        // Nodo* node=deg->getPrimalGraph()->nodes[G->nodes[i]->originalID];
        timesTravelled[node->id]=timesTravelled_structural[i];
    }


    return timesTravelled;

}


std::vector<double> SpatialInteraction::calculateTotalTimesTravelledFromEachNode(DualExtendedGraph* deg,std::vector<double>& speedLimits,double capacity,double alpha,double beta,double t,std::vector<double>& edgeFlows,double& numberTripsGenerated){
    // double stopTimeAtIntersection=77.5;//   s
    double acceleration=4;// m/s2
    Grafo* G=deg->getStructuralGraph();
    // for(long i=0;i<G->nodes.size();i++){
    //     std::cout<<"masses structural "<<G->nodes[i]->mass<<'\n';
    //     // Nodo* node=deg->getPrimalGraph()->getNodeByLocation(G->nodes[i]->location);
    //     // G->nodes[i]->mass=node->mass;
    // }
    // std::vector<double> edgeFlows;
    std::vector<double> timeWeights=SpatialInteraction::calculateTimesSegments(deg,speedLimits,capacity,alpha,beta,acceleration,t,edgeFlows,numberTripsGenerated);
    std::vector<double> originalWeights;
    originalWeights.resize(G->links.size(),0);
    std::vector<double> timesTravelled;
    std::vector<double> timesTravelled_structural;
    timesTravelled.resize(deg->getPrimalGraph()->nodes.size(),0);
    for(long i=0;i<G->links.size();i++){
        originalWeights[i]=G->links[i]->weight;
        G->links[i]->weight=timeWeights[i];
    }

    SpatialInteraction::calculateTotalDistanceTravelledFromEachNode(G,0,timesTravelled_structural);
    for(long i=0;i<G->links.size();i++){
        // originalWeights[i]=G->links[i]->weight;
        G->links[i]->weight=originalWeights[i];
    }

    // std::vector<double> valuesInPrimal;
    // valuesInPrimal.resize(deg->getPrimalGraph()->nodes.size(),0);

    for(long i=0;i<G->nodes.size();i++){
        Nodo* node=deg->getPrimalGraph()->getNodeByLocation(G->nodes[i]->location);
            // std::cout<<"masses structural= "<<G->nodes[i]->mass<<" timesTravelledStructural= "<<timesTravelled_structural[i]<<'\n';
        // Nodo* node=deg->getPrimalGraph()->nodes[G->nodes[i]->originalID];
        timesTravelled[node->id]=timesTravelled_structural[i];
    }


    return timesTravelled;

}



double SpatialInteraction::getProbabilityFlowBasedInTime(double t_hours){
    double standardDeviation=2.2;
    double t=t_hours;
    return 1.0/2.0/sqrt(2.0*standardDeviation*standardDeviation*M_PI)*(exp(-(t-8)*(t-8)/2.0/standardDeviation/standardDeviation)+exp(-(t-16)*(t-16)/2.0/standardDeviation/standardDeviation));
}


void SpatialInteraction::calculateFlowsInVehiclesPerSecond(Grafo* G,double t,std::vector<double>& edgeFlows,double& numberTripsGenerated){


    numberTripsGenerated=0;
    InterfaceFlows flows;
    // flows.setNumberSubdivisions(1);
    flows.initFlows(G->links.size());
    flows.initValuesToPass(G->nodes.size());


    SpatialInteraction::calculateNormalisedEdgeFlow(G,0,flows,numberTripsGenerated);
    edgeFlows=flows.getFlows(0);
    double timeIncrement=1.0/60.0/60.0;
    for(long i=0;i<G->links.size();i++){
        edgeFlows[i]*=numberTripsGenerated*Functions::min(SpatialInteraction::getProbabilityFlowBasedInTime(t+timeIncrement),SpatialInteraction::getProbabilityFlowBasedInTime(t))*timeIncrement+timeIncrement*Functions::abs(SpatialInteraction::getProbabilityFlowBasedInTime(t+timeIncrement)-SpatialInteraction::getProbabilityFlowBasedInTime(t));
    }

}

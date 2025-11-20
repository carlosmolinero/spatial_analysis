#include "Clustering.h"


std::vector<long> Clustering::kMeans(std::vector<std::unordered_map<long,double> >& coordinates,long numClusters,int typeDistance){
  std::vector<long> clusters;
  std::cout<<"Clustering::kMeans start"<<'\n';
  std::unordered_map<long,double> maxCoordinatePerDimension;
  std::unordered_map<long,double> minCoordinatePerDimension;
    std::cout<<"Clustering::kMeans calculate max and min"<<'\n';
  for(long i=0;i<coordinates.size();i++){
    for(auto it:coordinates[i]){
      if(Functions::getValueAt(maxCoordinatePerDimension,it.first,-3172946.287563142588)==-3172946.287563142588){
        maxCoordinatePerDimension[it.first]=it.second;
      }else if(maxCoordinatePerDimension[it.first]<it.second){
        maxCoordinatePerDimension[it.first]=it.second;
      }
      if(Functions::getValueAt(minCoordinatePerDimension,it.first,-3172946.287563142588)==-3172946.287563142588){
        minCoordinatePerDimension[it.first]=it.second;
      }else if (minCoordinatePerDimension[it.first]>it.second){
        minCoordinatePerDimension[it.first]=it.second;
      }
    }
  }
  std::cout<<"Clustering::kMeans calculate initial centres"<<'\n';
  std::vector<std::unordered_map<long,double> > centres;
  centres.resize(numClusters,std::unordered_map<long,double>());
  for(long i=0;i<numClusters;i++){
    // for(auto it:maxCoordinatePerDimension){
      // centres[i][it.first]=Functions::runiform(minCoordinatePerDimension[it.first],maxCoordinatePerDimension[it.first]);
    // }
      long index=std::floor(Functions::runiform(0,coordinates.size()));
      centres[i]=coordinates[index];

  }
  clusters.resize(coordinates.size(),-1);
  std::vector<long> clustersPrev;
  clustersPrev.resize(coordinates.size(),-1);
  std::vector<double> numObjectsInCluster;
  numObjectsInCluster.resize(centres.size(),0);

  long numChanges=0;
  bool firstTime=true;
  long counter=0;
  std::cout<<"Clustering::kMeans start calculation"<<'\n';
  while((firstTime||numChanges>0)&&counter<1000){

    numChanges=0;
    for(long i=0;i<coordinates.size();i++){
      double minDistance=INFINITY;
      long indexCentre=clustersPrev[i];
      // if(clustersPrev[i])
      for(long j=0;j<centres.size();j++){
        if(typeDistance==Clustering::manhattan){
          double distance=manhattanDistance(coordinates[i],centres[j]);
          if(distance<minDistance){
            minDistance=distance;
            indexCentre=j;
          }
        }else{
          std::cout<<"not yet implemented this type of distance"<<'\n';
        }
      }
      clusters[i]=indexCentre;
      if(clusters[i]!=clustersPrev[i]){
        numChanges++;
      }
      numObjectsInCluster[indexCentre]++;
    }

    for(long j=0;j<centres.size();j++){
      centres[j].clear();
    }
    for(long i=0;i<clusters.size();i++){
      for(auto it:coordinates[i]){
        centres[clusters[i]][it.first]+=it.second/=numObjectsInCluster[clusters[i]];
      }
    }
    // for(long j=0;j<centres.size();j++){
    //   for(auto it:centres[j]){
    //     centres[j][it.first]/=numObjectsInCluster[j];
    //   }
    // }
    std::swap(clustersPrev,clusters);
    std::fill(numObjectsInCluster.begin(), numObjectsInCluster.end(), 0.0);

    counter++;
    firstTime=false;
    // std::cout<<"Num changes in Clustering::kMeans "<<numChanges<<" ,counter "<<counter<<'\n';
    std::cout<<"Counter in Clustering::kMeans "<<counter<<" ,numChanges="<<numChanges<<'\n';
  }
  std::swap(clustersPrev,clusters);
  return clusters;


}

double Clustering::manhattanDistance(std::unordered_map<long,double>& coordinatesA,std::unordered_map<long,double> coordinatesB){
  double distance=0;
  std::vector<long> indexes;
  for(auto it:coordinatesA){
    indexes.push_back(it.first);
  }
  for(auto it:coordinatesB){
    indexes.push_back(it.first);
  }
  for(long i=0;i<indexes.size();i++){
    double valueA=0;
    double valueB=0;
    // if(coordinatesA.find(i)!=coordinatesA.end()){
      valueA=Functions::getValueAt(coordinatesA,indexes[i],0);
    // }
    // if(coordinatesB.find(i)!=coordinatesB.end()){
      valueB=Functions::getValueAt(coordinatesB,indexes[i],0);
    // }
    distance+=Functions::abs(valueA-valueB);
  }
  return distance;
}

// double Clustering::chiSquaredDistance(std::unordered_map<long,double>& coordinatesA,std::unordered_map<long,double> coordinatesB){
//   double distance=0;
//   std::vector<long> indexes;
//   for(auto it:coordinatesA){
//     indexes.push_back(it.first);
//   }
//   for(auto it:coordinatesB){
//     indexes.push_back(it.first);
//   }
//   for(long i=0;i<indexes.size();i++){
//     double valueA=0;
//     double valueB=0;
//     // if(coordinatesA.find(i)!=coordinatesA.end()){
//       valueA=Functions::getValueAt(coordinatesA,indexes[i],0);
//     // }
//     // if(coordinatesB.find(i)!=coordinatesB.end()){
//       valueB=Functions::getValueAt(coordinatesB,indexes[i],0);
//     // }
//     distance+=Functions::abs(valueA-valueB);
//   }
//   return distance;
// }

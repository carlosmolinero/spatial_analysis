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
#include "../SpatialAnalysis/SpatialAnalysis/TextFile.h"
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
DataFrame readDataCalculateFrequencyTowers(String path){


    std::ifstream file;
    bool abierto=TextFile::open(path,file);
    long currentMaxId=1;
    std::unordered_map<std::string,long> userIds;
    std::unordered_map<long,std::unordered_map <std::string,long > > freqsPerUserAndTower;
    if (abierto)
    {

        std::string linea;
        linea=TextFile::getLine(file);//skipping the names of variables
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            if (linea.length()>0)
            {
                std::vector<std::string> words=TextFile::extractWords(linea, ",");                
                std::string idUser=words[3];
                std::string idTower=words[6];
                if(userIds[idUser]==0){
                  userIds[idUser]=currentMaxId;
                  currentMaxId++;
                }
                freqsPerUserAndTower[userIds[idUser]][idTower]++;
                
            }
        }

        TextFile::close(file);
    }

    std::vector<long> freqs;
    std::vector<long> ranks;
    std::vector<long> user;

    for(auto it:freqsPerUserAndTower){
      std::vector<long> freqsTemp;
      for(auto it2:freqsPerUserAndTower[it.first]){
        freqsTemp.push_back(it2.second);
      }
      std::vector<long> orderedfreqsTemp=Functions::orderValues(freqsTemp,false);
      for(long i=0;i<orderedfreqsTemp.size();i++){
        freqs.push_back(orderedfreqsTemp[i]);
        ranks.push_back(i+1);
        user.push_back(it.first);
      }

    }



  List list(3);
list[0]=freqs;
list[1]=ranks;
list[2]=user;

  CharacterVector namevec;
  namevec.push_back("numberVisits");
  namevec.push_back("rank");
  namevec.push_back("user");

  
  


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


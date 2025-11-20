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
#include "../SpatialAnalysis/SpatialAnalysis/Clustering.h"
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




//////////////////////////////////////////////////////////////////////////////////////
//VOTING PAPER
//////////////////////////////////////////////////////////////////////////////////////

// [[Rcpp::export]]
List firstVotes(XPtr< Grafo > tree,DataFrame nodes,DataFrame politicalParties){

  NumericVector mins=as<NumericVector>(politicalParties[1]);
  NumericVector maxs=as<NumericVector>(politicalParties[2]);
  NumericVector clusters=as<NumericVector>(nodes[4]);
  NumericVector HIs=as<NumericVector>(nodes[3]);

  std::vector<std::vector<long> > ppByNode;
  ppByNode.resize(tree->nodes.size(),std::vector<long> ());

  NumericVector votes(mins.size());
  NumericVector votesPerNode(clusters.size());
  NumericVector idTreeNodesOfEachPP=as<NumericVector>(politicalParties[0]);

  for(long j=0;j<idTreeNodesOfEachPP.size();j++){
    votes[j]=0;
    ppByNode[idTreeNodesOfEachPP[j]].push_back(j);
  }

  for(long i=0;i<clusters.size();i++){
    long cluster=clusters[i];
    double HI=HIs[i];
    double allowedSpread=INFINITY;
    double ppToVoteFor=-1;
    bool STOP=false;
    while(!STOP){
      for(long j=0;j<ppByNode[cluster].size();j++){
        long indexPP=ppByNode[cluster][j];
        double min=mins[indexPP];
        double max=maxs[indexPP];
        double spread=max-min;

        if(HI>=min&&HI<=max&&spread<allowedSpread){
          allowedSpread=spread;
          ppToVoteFor=indexPP;
        }

      }
      if(ppToVoteFor==-1){
        cluster=Tree::getParent(tree,cluster);
      }else{
        STOP=true;
      }
    }

    votesPerNode[i]=ppToVoteFor;
    votes[ppToVoteFor]+=1;


  }
  List list(2);
  list[0]=votes;
  list[1]=votesPerNode;

  CharacterVector namevec;
  namevec.push_back("votes");
  namevec.push_back("votesPerNode");

  list.attr("names") = namevec;
  return list;
}

// [[Rcpp::export]]
DataFrame getSpectrumElectorate(XPtr< Grafo > tree,DataFrame nodes){

// NumericVector mins=as<NumericVector>(politicalParties[1]);
// NumericVector maxs=as<NumericVector>(politicalParties[2]);
  NumericVector clusters=as<NumericVector>(nodes[4]);
  NumericVector HIs=as<NumericVector>(nodes[3]);

  std::vector<std::vector<long> > spectrum;
  spectrum.resize(10,std::vector<long>());
  for(long i=0;i<10;i++){
    spectrum[i].resize(clusters.size(),0);
  }

  for(long i=0;i<clusters.size();i++){

    long index=(long)(floor(HIs[i]*10));
    spectrum[index][clusters[i]]++;
    long parent=clusters[i];
    while(parent!=-1){
      parent=Tree::getParent(tree,parent);
      if(parent!=-1){
        spectrum[index][parent]++;
      }

    }
  }

  List list(10);
  for(long i=0;i<10;i++){
    list[i]=wrap(spectrum[i]);
  }

  CharacterVector namevec;
  for(long i=0;i<10;i++){
  // list[i]=wrap(spectrum[i]);
   namevec.push_back(std::to_string(i));
 }
  // namevec.push_back("votes");
  // namevec.push_back("votesPerNode");

 list.attr("names") = namevec;
 DataFrame df(list);
 return df;
}


std::unordered_map<long,double> getCoordinatesOfAParty(XPtr< Grafo > tree,long nodeOfParty, double minHIParty,double maxHIParty,DataFrame& nodes){
  // std::unordered_map<long,double> getCoordinatesOfAParty(XPtr< Grafo > tree,long nodeOfParty, double minHIParty,double maxHIParty,DataFrame& nodes,std::unordered_map<long,std::unordered_map<long,double> >& coordinatesNodes){
  std::vector<long> allSons=Tree::getSonsAllLevelsInHierarchicalMetricTree(tree,nodeOfParty);
  std::vector<long> clusters=as<std::vector<long> >(nodes[4]);
  std::vector<long> HIs=as<std::vector<long> >(nodes[3]);

  std::unordered_map<long,long> clustersThatBelongToSons;
  for(long i=0;i<allSons.size();i++){
    clustersThatBelongToSons[allSons[i]]=1;
  }
  std::unordered_map<long,double> coordinates;
  double numberSons=0;
  // coordinates.resize(tree->nodes.size(),0);
  for(long i=0;i<clusters.size();i++){

    if(HIs[i]>=minHIParty&HIs[i]<=maxHIParty&clustersThatBelongToSons[clusters[i]]==1){
      std::vector<long> parents=Tree::getAllParents(tree,clusters[i]);
      for(long j=0;j<parents.size();j++){
        coordinates[parents[j]]++;
      }
      coordinates[clusters[i]]++;
      numberSons++;
    }
  }
  if(numberSons>0){
    for(auto it:coordinates){
      it.second/=numberSons;
    }
  }
  return (coordinates);
}


std::vector<std::unordered_map<long,double> > getCoordinatesAllPoliticalParties(XPtr< Grafo > tree,DataFrame& politicalParties,DataFrame& nodes){

  NumericVector idTreeNodesOfEachPP=as<NumericVector>(politicalParties[0]);
  NumericVector mins=as<NumericVector>(politicalParties[1]);
  NumericVector maxs=as<NumericVector>(politicalParties[2]);
  std::vector<std::unordered_map<long,double> > coordinatesPoliticalParties;
  coordinatesPoliticalParties.reserve(idTreeNodesOfEachPP.size());
  for(long i=0;i<idTreeNodesOfEachPP.size();i++){
    // std::cout<<"index node of political party in calculating coordinates "<<i<<"/"<<idTreeNodesOfEachPP.size()<<'\n';
    coordinatesPoliticalParties.push_back(getCoordinatesOfAParty(tree,idTreeNodesOfEachPP[i],mins[i],maxs[i],nodes));
  }
  return coordinatesPoliticalParties;
}


std::vector<std::vector<double> > aggregateVotersByNodeAndHI(DataFrame& nodes){
  NumericVector ids=as<NumericVector>(nodes[0]);
  NumericVector xs=as<NumericVector>(nodes[1]);
  NumericVector ys=as<NumericVector>(nodes[2]);
  NumericVector HIs=as<NumericVector>(nodes[3]);
  NumericVector clusters=as<NumericVector>(nodes[4]);
  NumericVector depthNode=as<NumericVector>(nodes[5]);

  std::unordered_map<std::vector<double>, std::vector<double> > resultTemp;
  // std::unordered_map<std::vector<double>, double> ys_;
  // std::unordered_map<std::vector<double>, double> sizes_;
  // std::unordered_map<std::vector<double>, double> ys_;

  std::vector<std::vector<double> > result;
  for(long i=0;i<ids.size();i++){
      std::vector<double> coords;
      coords.push_back(HIs[i]);
      coords.push_back(clusters[i]);
      if(resultTemp[coords].size()==0){
        resultTemp[coords].reserve(4);
        resultTemp[coords].push_back(xs[i]);
        resultTemp[coords].push_back(ys[i]);
        resultTemp[coords].push_back(depthNode[i]);
        resultTemp[coords].push_back(1);
      }else{
        resultTemp[coords][0]+=xs[i];
        resultTemp[coords][1]+=ys[i];
        resultTemp[coords][3]++;
      }
  }
  result.reserve(resultTemp.size());
  long i=0;
  for(auto it:resultTemp){
    it.second[0]/=it.second[3];
    it.second[1]/=it.second[3];
    result[i].reserve(6);
    result[i].push_back(it.first[0]);
    result[i].push_back(it.first[1]);
    result[i].push_back(it.second[0]);
    result[i].push_back(it.second[1]);
    result[i].push_back(it.second[2]);
    result[i].push_back(it.second[3]);
    i++;
  }
  return result;
}


std::vector<double> measureConcentrationsOfVoterInAParty(long totalNumberOfNodes,double HI,std::vector<long>& spectrumParty,std::unordered_map<long,double> coordinatesParty,std::unordered_map<long,double> coordinatesCluster,double maxDistanceInTree){
  std::vector<double> result;
  result.resize(3,0);
  // double sumSpectrumNode=0;
  // for(long i=0;i<spectrumNode.size();i++){
  //   sumSpectrumNode+=spectrumNode[i];
  // }
  long index=(long)(floor(HI*10));
  // double howConcentratedIsOnMeMyNode=spectrumNode[index]/sumSpectrumNode;


  double sumSpectrumParty=0;
  for(long i=0;i<spectrumParty.size();i++){
    sumSpectrumParty+=spectrumParty[i];
  }

  double howConcentratedIsOnMeMyParty=spectrumParty[index]/sumSpectrumParty;
  result[0]=howConcentratedIsOnMeMyParty;
  double distance=Tree::distanceBetweenNodesInATree(coordinatesParty,coordinatesCluster);

  double howConcentratedIsOnMyRegion=1/((distance+.1)/(maxDistanceInTree+.1));
  result[1]=howConcentratedIsOnMyRegion;
  // double whatAreChancesOfWinningOfNode=sumSpectrumNode/(double)totalNumberOfNodes;
  double whatAreChancesOfWinningOfParty=sumSpectrumParty/(double)totalNumberOfNodes;
  // double increaseInChancesOfWinning=whatAreChancesOfWinningOfParty/whatAreChancesOfWinningOfNode;
  result[2]=whatAreChancesOfWinningOfParty;
  return result;

}

// std::vector<double> measureConcentrationsOfPartyInAVoterAndOneInSameCluster(long totalNumberOfNodes,double HI,std::vector<long>& spectrumNode,std::vector<long>& spectrumOther,NumericVector coordinatesParent,NumericVector coordinatesCluster){
//   std::vector<double> result;
//   result.resize(3,0);
//   double sumSpectrumNode=0;
//   for(long i=0;i<spectrumNode.size();i++){
//     sumSpectrumNode+=spectrumNode[i];
//   }
//   long index=(long)(floor(HI*10));
//   // double howConcentratedIsInMe=spectrumNode[index]/sumSpectrumNode;
//   // result[0]=howConcentratedIsInMe;
//   double sumSpectrumOther=0;
//   for(long i=0;i<spectrumOther.size();i++){
//     sumSpectrumOther+=spectrumOther[i];
//   }
//   double howConcentratedIsOnMeMyNode=spectrumNode[index]/sumSpectrumNode;
//   double howConcentratedIsOnMeOtherNode=spectrumOther[index]/sumSpectrumOther;
//   result[0]=howConcentratedIsOnMeOtherNode;
//   double howConcentratedIsInMyRegion=sumSpectrumNode/sumSpectrumOther;
//   // double howConcentratedIsInMyRegion=1;
//   result[1]=howConcentratedIsInMyRegion;
//   double whatAreChancesOfWinningOfNode=sumSpectrumNode/(double)totalNumberOfNodes;
//   double whatAreChancesOfWinningOfParent=sumSpectrumOther/(double)totalNumberOfNodes;
//   double increaseInChancesOfWinning=whatAreChancesOfWinningOfParent/whatAreChancesOfWinningOfNode;
//   result[2]=whatAreChancesOfWinningOfParent;
//   return result;
// }

double heuristicInterestInAParty(std::vector<double> concentrationOnMeOfParty,double howMuchICareAboutTheIssuesOfMyDemographic,double myInterestInRegionality,double howMuchIAmInterestedInWinning){
  double result=howMuchICareAboutTheIssuesOfMyDemographic*concentrationOnMeOfParty[0]+myInterestInRegionality*concentrationOnMeOfParty[1]+howMuchIAmInterestedInWinning*concentrationOnMeOfParty[2];
  // double win=0;
  // if(concentrationOnMeOfParty[2]>1){
  //   win+=.0001;
  // }
  // double result=howMuchICareAboutTheIssuesOfMyDemographic*concentrationOnMeOfParty[0]+myInterestInRegionality*concentrationOnMeOfParty[1]+win;
  return result;


}




// // [[Rcpp::export]]
// List reVote(XPtr< Grafo > tree,DataFrame nodes,DataFrame politicalParties,NumericVector whoDidIVoteFor,long lastWinner,DataFrame spectrumElectorate,double tolerance1,double tolerance2){

//   std::vector<std::vector<double> > spectrum;
//   spectrum.resize(10,std::vector<double>());
//   for(long i=0;i<10;i++){
//     spectrum[i]=as<std::vector<double> >(spectrumElectorate[i]);
//   }

// NumericVector mins=as<NumericVector>(politicalParties[1]);
// NumericVector maxs=as<NumericVector>(politicalParties[2]);
//  NumericVector clusters=as<NumericVector>(nodes[4]);
// NumericVector HIs=as<NumericVector>(nodes[3]);

//   std::vector<std::vector<long> > ppByNode;
//   ppByNode.resize(tree->nodes.size(),std::vector<long> ());

//   NumericVector votes(mins.size(),0);
//   NumericVector votesPerNode(clusters.size());
//   NumericVector idTreeNodesOfEachPP=as<NumericVector>(politicalParties[0]);

//     for(long j=0;j<idTreeNodesOfEachPP.size();j++){
//       // votes[j]=0;
//       ppByNode[idTreeNodesOfEachPP[j]].push_back(j);
//     }

//   for(long i=0;i<whoDidIVoteFor.size();i++){
//     if(whoDidIVoteFor[i]!=lastWinner){
//       long cluster=idTreeNodesOfEachPP[whoDidIVoteFor[i]];
//       double HI=HIs[i];
//       long indexSpectrum=(long)(floor(HI*10));
//       double allowedSpread=maxs[whoDidIVoteFor[i]]-mins[whoDidIVoteFor[i]];
//       double ppToVoteFor=whoDidIVoteFor[i];
//       bool STOP=false;
//       double probToSpread=1.0-HI;
//       double probToGeneralise=HI;
//       long repetitions=10;
//       std::vector<long> actions;
//       // actions.resize(repetitions,0)
//       for(long j=0;j<repetitions;j++){
//         double random=Functions::runiform(0,1);
//         if(random<probToSpread){
//           actions.push_back(1);
//         }
//       }
//       for(long j=0;j<repetitions;j++){
//         double random=Functions::runiform(0,1);
//         if(random<probToGeneralise){
//           actions.push_back(2);
//         }
//       }
//       long action=2;
//       if(actions.size()>0){
//         long randomIndex=(long)(floor(Functions::runiform(0,actions.size())));
//         action=actions[randomIndex];
//       }
//       if(cluster==0){
//         action=1;
//       }







//       if(action==2){
//         cluster=getParent(tree,cluster);



//         while(!STOP){
//           for(long j=0;j<ppByNode[cluster].size();j++){
//             long indexPP=ppByNode[cluster][j];
//             double min=mins[indexPP];
//             double max=maxs[indexPP];
//             double spread=max-min;
//             double sumSpectrum=0;
//             for(long h=floor(min*10);h<floor(max*10);h++){
//               sumSpectrum+=spectrum[h][cluster];
//             }
//             double percentage=spectrum[indexSpectrum][cluster]/sumSpectrum;
//             if(HI>=min&&HI<=max&&spread<allowedSpread&&percentage>tolerance1){
//               allowedSpread=spread;
//               ppToVoteFor=indexPP;
//             }

//           }
//           if(ppToVoteFor==-1){
//             long parent=getParent(tree,cluster);
//             double percentage=spectrum[indexSpectrum][cluster]/spectrum[indexSpectrum][parent];
//             if(percentage>tolerance2){
//               cluster=parent;
//             }else{
//               STOP=true;
//               if(ppToVoteFor==-1){
//                 ppToVoteFor=whoDidIVoteFor[i];
//               }
//             }
//           }else{
//             STOP=true;
//           }
//         }
//       }else if (action==1){
//         double minSpread=allowedSpread;
//         allowedSpread=INFINITY;
//         while(!STOP){
//           for(long j=0;j<ppByNode[cluster].size();j++){
//             long indexPP=ppByNode[cluster][j];
//             double min=mins[indexPP];
//             double max=maxs[indexPP];
//             double spread=max-min;
//             double sumSpectrum=0;
//             for(long h=floor(min*10);h<floor(max*10);h++){
//               sumSpectrum+=spectrum[h][cluster];
//             }
//             double percentage=spectrum[indexSpectrum][cluster]/sumSpectrum;
//             if(HI>=min&&HI<=max&&spread<allowedSpread&&spread>minSpread&&percentage>tolerance1){
//               allowedSpread=spread;
//               ppToVoteFor=indexPP;
//             }

//           }
//           if(ppToVoteFor==-1){
//             long parent=getParent(tree,cluster);
//             double percentage=spectrum[indexSpectrum][cluster]/spectrum[indexSpectrum][parent];
//             if(percentage>tolerance2){
//               cluster=parent;
//             }else{
//               STOP=true;
//               if(ppToVoteFor==-1){
//                 ppToVoteFor=whoDidIVoteFor[i];
//               }
//             }
//             minSpread=0;
//             // allowedSpread=INFINITY;
//           }else{
//             STOP=true;
//           }
//         }
//       }

//       votesPerNode[i]=ppToVoteFor;
//       votes[ppToVoteFor]+=1;
//     }else{
//       votesPerNode[i]=whoDidIVoteFor[i];
//       votes[whoDidIVoteFor[i]]+=1;
//     }


//   }
//     List list(2);
//   list[0]=votes;
//   list[1]=votesPerNode;

//   CharacterVector namevec;
//   namevec.push_back("votes");
//   namevec.push_back("votesPerNode");

//   list.attr("names") = namevec;
//   return list;
// }






// [[Rcpp::export]]
List reVote(XPtr< Grafo > tree,long numberDepths,DataFrame nodes,DataFrame politicalParties,NumericVector whoDidIVoteFor,long lastWinner,DataFrame spectrumElectorate,double tolerance1,double tolerance2){
  double maxDistanceInTree=numberDepths*2.0;


  std::vector<std::vector<double> > aggregatedVoters=aggregateVotersByNodeAndHI(nodes);

  std::vector<std::vector<double> > spectrum;
  spectrum.resize(10,std::vector<double>());
  for(long i=0;i<10;i++){
    spectrum[i]=as<std::vector<double> >(spectrumElectorate[i]);
  }


  NumericVector mins=as<NumericVector>(politicalParties[1]);
  NumericVector maxs=as<NumericVector>(politicalParties[2]);
  NumericVector lastVotes=as<NumericVector>(politicalParties[4]);
  NumericVector clusters=as<NumericVector>(nodes[4]);
  NumericVector HIs=as<NumericVector>(nodes[3]);

// std::cout<<lastVotes[lastWinner]<<'\n';

  std::vector<std::vector<long> > ppByNode;
  ppByNode.resize(tree->nodes.size(),std::vector<long> ());

  NumericVector votes(mins.size(),0);
  NumericVector votesPerNode(clusters.size());
  NumericVector idTreeNodesOfEachPP=as<NumericVector>(politicalParties[0]);


std::unordered_map<long,std::unordered_map<long,double> > coordinatesPoliticalParties;

// std::cout<<"start calculating coordinates political parties"<<'\n';
// std::vector<std::unordered_map<long,double> > coordinatesPoliticalParties=getCoordinatesAllPoliticalParties(tree,politicalParties,nodes);
// std::cout<<"finish calculating coordinates political parties"<<'\n';


  for(long j=0;j<idTreeNodesOfEachPP.size();j++){

    ppByNode[idTreeNodesOfEachPP[j]].push_back(j);
  }
  std::unordered_map<long,std::unordered_map<long,double> > coordinatesNodes;

  for(long i=0;i<whoDidIVoteFor.size();i++){
    long myNode=clusters[i];

    long cluster=idTreeNodesOfEachPP[whoDidIVoteFor[i]];
    double HI=HIs[i];

    double ppToVoteFor=whoDidIVoteFor[i];

    double importanceDemographic=(HI)*tolerance2+(1-tolerance2);
    double importanceRegion=(1-HI)*tolerance2+(1-tolerance2);
      // probToSpread=tolerance2;
      // probToGeneralise=tolerance2;
    double howMuchINeedToWin=((lastVotes[lastWinner]-lastVotes[whoDidIVoteFor[i]])/lastVotes[lastWinner])*tolerance1;

      // double howMuchINeedToWin=tolerance1;
    long parent=Tree::getParent(tree,cluster);
    // std::vector<long> spectrumOfMyParty;
    // spectrumOfMyParty.resize(10,0);
    // for(long j=0;j<10;j++){
    //   double min=mins[whoDidIVoteFor[i]];
    //   double max=maxs[whoDidIVoteFor[i]];
    //     // std::cout<<"here "<<(double)(j)/10.0<<" "<<min<<" "<<max<<"      "<<spectrum[j][cluster]<<" "<<HI<<'\n';
    //   if((double)(j)/10.0+.01>=min&&(double)(j)/10.0<max){
    //     spectrumOfMyParty[j]=spectrum[j][cluster];
    //   }
    // }
    std::vector<long> idNode;
    std::vector<long> indexPartyInCluster;
    std::vector<double> heuristicValues;
      // std::cout<<ppByNode[cluster].size()<<'\n';
    std::cout<<"calculating coordinates node "<<myNode<<" "<<i<<"/"<<whoDidIVoteFor.size()<<'\n';
    std::unordered_map<long,double> coordinatesVoter;
    if(coordinatesNodes[myNode].size()>0){
      coordinatesVoter=coordinatesNodes[myNode];
    }else{
      coordinatesNodes[myNode]=Tree::getCoordinatesOfANodeInATree(tree,myNode);
      coordinatesVoter=coordinatesNodes[myNode];
    }

    // std::cout<<"end calculating coordinates node"<<'\n';
    for(long h=0;h<ppByNode[cluster].size();h++){
      std::vector<long> spectrumOfOther;
      spectrumOfOther.resize(10,0);
      double sumSpectrumOfOther=0;
      double min=mins[ppByNode[cluster][h]];
      double max=maxs[ppByNode[cluster][h]];
      std::unordered_map<long,double> coordinatesParty;
      if(coordinatesPoliticalParties[ppByNode[cluster][h]].size()>0){
        coordinatesParty=coordinatesPoliticalParties[ppByNode[cluster][h]];
      }else{
        coordinatesPoliticalParties[ppByNode[cluster][h]]=getCoordinatesOfAParty(tree,cluster,min,max,nodes);
        coordinatesParty=coordinatesPoliticalParties[ppByNode[cluster][h]];
      }
      for(long j=0;j<10;j++){


        if((double)(j)/10.0+.01>=min&&(double)(j)/10.0<max){
          spectrumOfOther[j]=spectrum[j][cluster];
          sumSpectrumOfOther+=spectrum[j][cluster];
        }
      }


      std::vector<double> concentrations=measureConcentrationsOfVoterInAParty(clusters.size(),HI,spectrumOfOther,coordinatesParty,coordinatesVoter,maxDistanceInTree);
      // measureConcentrationsOfVoterInAParty(long totalNumberOfNodes,double HI,std::vector<long>& spectrumParty,NumericVector coordinatesParty,NumericVector coordinatesCluster,double maxDistanceInTree){
        // std::stringstream ss;
        // for(long u=0;u<10;u++){
        //   ss<<" "<<spectrumOfMyParty[u];
        // }
        // std::cout<<ss.str()<<'\n';

      double heuristic=heuristicInterestInAParty(concentrations,importanceDemographic,importanceRegion,howMuchINeedToWin);
      if(!(HI>=min&&HI<=max)){
        heuristic=0;
      }
        // std::cout<<concentrations[0]<<" "<<concentrations[1]<<" "<<concentrations[2]<<" "<<heuristic<<'\n';
      if(sumSpectrumOfOther>0){
        heuristicValues.push_back(heuristic);
        idNode.push_back(cluster);
        indexPartyInCluster.push_back(h);
      }
    }
    if(parent!=-1){
      for(long h=0;h<ppByNode[parent].size();h++){
        std::vector<long> spectrumOfOther;
        spectrumOfOther.resize(10,0);
        double min=mins[ppByNode[parent][h]];
        double max=maxs[ppByNode[parent][h]];
        std::unordered_map<long,double> coordinatesParty;
        if(coordinatesPoliticalParties[ppByNode[parent][h]].size()>0){
          coordinatesParty=coordinatesPoliticalParties[ppByNode[parent][h]];
        }else{
          coordinatesPoliticalParties[ppByNode[parent][h]]=getCoordinatesOfAParty(tree,parent,min,max,nodes);
          coordinatesParty=coordinatesPoliticalParties[ppByNode[parent][h]];
        }
        for(long j=0;j<10;j++){

          if((double)(j)/10.0+.01>=min&&(double)(j)/10.0<max){
            spectrumOfOther[j]=spectrum[j][parent];
          }
        }
        std::vector<double> concentrations=measureConcentrationsOfVoterInAParty(clusters.size(),HI,spectrumOfOther,coordinatesParty,coordinatesVoter,maxDistanceInTree);
        double heuristic=heuristicInterestInAParty(concentrations,importanceDemographic,importanceRegion,howMuchINeedToWin);
        if(!(HI>=min&&HI<=max)){
          heuristic=0;
        }
        heuristicValues.push_back(heuristic);
        idNode.push_back(parent);
        indexPartyInCluster.push_back(h);
      }
    }

    long chosenCluster=-1;
    long chosenIndex=-1;
    double max=-INFINITY;
    for(long h=0;h<heuristicValues.size();h++){
      if(heuristicValues[h]>max){
        chosenCluster=idNode[h];
        chosenIndex=indexPartyInCluster[h];
        max=heuristicValues[h];

      }
    }
    ppToVoteFor=ppByNode[chosenCluster][chosenIndex];
      // }else{
      //   ppToVoteFor=whoDidIVoteFor[i];
      // }
      // if(ppToVoteFor==-1){
      // std::cout<<'\n';
      // std::cout<<heuristicValues.size()<<'\n';
      // std::cout<<ppToVoteFor<<" "<<chosenCluster<<" "<<chosenIndex<<" "<<max<<'\n';
      // if(chosenCluster==-1){
      //   std::cout<<heuristicValues[0]<<'\n';
      // }
      // }
    votesPerNode[i]=ppToVoteFor;
    votes[ppToVoteFor]+=1;



  }
  List list(2);
  list[0]=votes;
  list[1]=votesPerNode;

  CharacterVector namevec;
  namevec.push_back("votes");
  namevec.push_back("votesPerNode");

  list.attr("names") = namevec;
  return list;
}



void createCoordinatesConstituency(Grafo* tree,std::vector<long>& idIntersectionsInConstituency,long maxNumClusters,NumericVector& idClusterOfIntersections,std::unordered_map<long,double>& sparseCoordinatesResult){
    std::unordered_map<long,long> numIntersectionsPerCluster;

  // for(long i=0;i<maxNumClusters;i++){
  //   numIntersectionsPerCluster[i]
  // }
// std::cout<<"c"<<'\n';
long maxInt=0;
    // numIntersectionsPerCluster.resize(maxNumClusters,0);
    // std::unordered_set<long> summaryClusters;
    double numIntersectionsInConstituency=0;
    for(long i=0;i<idIntersectionsInConstituency.size();i++){
      long id=idIntersectionsInConstituency[i];
      numIntersectionsInConstituency++;
      if(id>=0){

        long cluster=idClusterOfIntersections[id];
        numIntersectionsPerCluster[cluster]++;

        if(numIntersectionsPerCluster[cluster]>maxInt){
          maxInt=numIntersectionsPerCluster[cluster];
        }
        // summaryClusters.insert(cluster);

      }
    }
    // std::cout<<"max num intersections in a cluster "<<maxInt<<'\n';
    // std::cout<<"d"<<'\n';
    if(idIntersectionsInConstituency.size()>0){
      for(auto it:numIntersectionsPerCluster){
        long cluster=it.first;
        if(cluster>=0){
          std::vector<long> parents=Tree::getAllParents(tree,cluster);
          double num=(double)(it.second)/numIntersectionsInConstituency;
          // double num=(double)(numIntersectionsPerCluster[cluster]);
          sparseCoordinatesResult[cluster]+=num;
          for(long j=0;j<parents.size();j++){
            sparseCoordinatesResult[parents[j]]+=num;
          }
        }
      }
    }
}


// [[Rcpp::export]]
DataFrame calculateCoordinatesConstituencies(XPtr< Grafo > tree,NumericVector idClusterOfIntersections,NumericVector idIntersectionsPerConstituency){
  long maxNumConstituencies=0;
  long maxNumClusters=0;
  for(long i=0;i<idIntersectionsPerConstituency.size();i++){
    if(idIntersectionsPerConstituency[i]>maxNumConstituencies){
      maxNumConstituencies=idIntersectionsPerConstituency[i];
    }
  }
  for(long i=0;i<idClusterOfIntersections.size();i++){
    if(idClusterOfIntersections[i]>maxNumClusters){
      maxNumClusters=idClusterOfIntersections[i];
    }
  }
  maxNumConstituencies++;
  maxNumClusters++;
  std::vector<std::vector<long> > intersectionsPerConstituency_;
  intersectionsPerConstituency_.resize(maxNumConstituencies,std::vector<long>());
  // std::cout<<"a, maxNumConst. "<<maxNumConstituencies<<'\n';


  for(long i=0;i<idIntersectionsPerConstituency.size();i++){
    // std::cout<<i<<" "<<idIntersectionsPerConstituency[i]<<'\n';
    if(idIntersectionsPerConstituency[i]>=0){
      intersectionsPerConstituency_[idIntersectionsPerConstituency[i]].push_back(i);
    }
  }
// std::cout<<"b"<<'\n';
  // long constituency=1;
  std::vector<std::unordered_map<long,double> > coordinatesConstituencies;
  coordinatesConstituencies.resize(maxNumConstituencies,std::unordered_map<long,double>());
  for(long constituency=0;constituency<maxNumConstituencies;constituency++){
    // std::unordered_map<long,long> sparseCoordinatesResult;
    createCoordinatesConstituency(tree,intersectionsPerConstituency_[constituency],maxNumClusters,idClusterOfIntersections,coordinatesConstituencies[constituency]);

  // std::cout<<"coordinates constituency in votingModelR"<<'\n';
  }



  List list(maxNumClusters);
  CharacterVector namevec;
  // namevec.push_back("votes");
  // namevec.push_back("votesPerNode");
  for(long i=0;i<maxNumClusters;i++){
    NumericVector a(maxNumConstituencies,0);
    list[i]=a;
    namevec.push_back(std::to_string(i));
  }
  for(long i=0;i<coordinatesConstituencies.size();i++){
    // a.resize;

    for(auto it:coordinatesConstituencies[i]){
      // std::cout<<it.first<<" , "<<i<<" = "<<it.second<<'\n';
        as<NumericVector>(list[it.first])[i]=it.second;
    }


  }

  // list[0]=votes;
  // list[1]=votesPerNode;



  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



// [[Rcpp::export]]
NumericVector calculateKmeansConstituencies(XPtr< Grafo > tree,NumericVector idClusterOfIntersections,NumericVector idIntersectionsPerConstituency,long numClusters){
  long maxNumConstituencies=0;
  long maxNumClusters=0;
  // std::cout<<"a"<<'\n';
  for(long i=0;i<idIntersectionsPerConstituency.size();i++){
    if(idIntersectionsPerConstituency[i]>maxNumConstituencies){
      maxNumConstituencies=idIntersectionsPerConstituency[i];
    }
  }
  // std::cout<<"b"<<'\n';
  for(long i=0;i<idClusterOfIntersections.size();i++){
    if(idClusterOfIntersections[i]>maxNumClusters){
      maxNumClusters=idClusterOfIntersections[i];
    }
  }
  // std::cout<<"c"<<'\n';
  maxNumConstituencies++;
  maxNumClusters++;
  std::vector<std::vector<long> > intersectionsPerConstituency_;
  intersectionsPerConstituency_.resize(maxNumConstituencies,std::vector<long>());
  // std::cout<<"a, maxNumConst. "<<maxNumConstituencies<<'\n';

  // std::cout<<"d"<<'\n';
  for(long i=0;i<idIntersectionsPerConstituency.size();i++){
    // std::cout<<i<<" "<<idIntersectionsPerConstituency[i]<<'\n';
    if(idIntersectionsPerConstituency[i]>=0){
      intersectionsPerConstituency_[idIntersectionsPerConstituency[i]].push_back(i);
    }
  }
  // std::cout<<"e"<<'\n';
// std::cout<<"b"<<'\n';
  // long constituency=1;
  std::vector<std::unordered_map<long,double> > coordinatesConstituencies;
  coordinatesConstituencies.resize(maxNumConstituencies,std::unordered_map<long,double>());
  for(long constituency=0;constituency<maxNumConstituencies;constituency++){
    // std::unordered_map<long,long> sparseCoordinatesResult;
    std::cout<<"Constituency in calculateKmeansConstituencies "<<constituency<<'\n';
    createCoordinatesConstituency(tree,intersectionsPerConstituency_[constituency],maxNumClusters,idClusterOfIntersections,coordinatesConstituencies[constituency]);

  // std::cout<<"coordinates constituency in votingModelR"<<'\n';
  }
  // std::cout<<"f"<<'\n';
// static std::vector<long> kMeans(std::vector<std::unordered_map<long,double> > coordinate,long numClusters);
  std::vector<long> clusters;
  // std::cout<<"just before of kmeans"<<'\n';
  clusters=Clustering::kMeans(coordinatesConstituencies,numClusters,Clustering::manhattan);
  return wrap(clusters);

}



//////////////////////////////////////////////////////////////////////////////////////
// [[Rcpp::export]]
NumericMatrix getDistanceMatrixOfConstituencies(XPtr< Grafo > tree,NumericVector idClusterOfIntersections,NumericVector idIntersectionsPerConstituency,String distanceType){
  long maxNumConstituencies=0;
  long maxNumClusters=0;
  // std::cout<<"a"<<'\n';
  for(long i=0;i<idIntersectionsPerConstituency.size();i++){
    if(idIntersectionsPerConstituency[i]>maxNumConstituencies){
      maxNumConstituencies=idIntersectionsPerConstituency[i];
    }
  }
  // std::cout<<"b"<<'\n';
  for(long i=0;i<idClusterOfIntersections.size();i++){
    if(idClusterOfIntersections[i]>maxNumClusters){
      maxNumClusters=idClusterOfIntersections[i];
    }
  }
  // std::cout<<"c"<<'\n';
  maxNumConstituencies++;
  maxNumClusters++;
  std::vector<std::vector<long> > intersectionsPerConstituency_;
  intersectionsPerConstituency_.resize(maxNumConstituencies,std::vector<long>());
  // std::cout<<"a, maxNumConst. "<<maxNumConstituencies<<'\n';

  // std::cout<<"d"<<'\n';
  for(long i=0;i<idIntersectionsPerConstituency.size();i++){
    // std::cout<<i<<" "<<idIntersectionsPerConstituency[i]<<'\n';
    if(idIntersectionsPerConstituency[i]>=0){
      intersectionsPerConstituency_[idIntersectionsPerConstituency[i]].push_back(i);
    }
  }
  // std::cout<<"e"<<'\n';
// std::cout<<"b"<<'\n';
  // long constituency=1;
  std::vector<std::unordered_map<long,double> > coordinatesConstituencies;
  coordinatesConstituencies.resize(maxNumConstituencies,std::unordered_map<long,double>());
  for(long constituency=0;constituency<maxNumConstituencies;constituency++){
    // std::unordered_map<long,long> sparseCoordinatesResult;
    std::cout<<"Constituency in calculateKmeansConstituencies "<<constituency<<'\n';
    createCoordinatesConstituency(tree,intersectionsPerConstituency_[constituency],maxNumClusters,idClusterOfIntersections,coordinatesConstituencies[constituency]);

  // std::cout<<"coordinates constituency in votingModelR"<<'\n';
  }
  int n=maxNumConstituencies;
  NumericMatrix d = no_init_matrix(n, n);

  for(int i=0; i<n;i++){
    for(int j=i+1; j<n;j++){
      // d(i,j)=Tree::calculateTopologicalDistancesInATreeBetweenTwoNodes(tree,tree->nodes[i]->id,tree->nodes[j]->id);
      if(distanceType=="manhattan"){
        d(i,j)=Clustering::manhattanDistance(coordinatesConstituencies[i],coordinatesConstituencies[j]);
      }else if (distanceType=="chiSquared"){
        d(i,j)=Functions::getChiSquaredDistance(coordinatesConstituencies[i],coordinatesConstituencies[j]);
      }
      d(j,i)=d(i,j);
    }

    d(i,i)=0;

  }
  return d;
}

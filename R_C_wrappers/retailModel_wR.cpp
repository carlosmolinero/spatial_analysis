

//////////////////////////////////////////////////////////////////////////////////////
//RETAIL PERCOLATION
//////////////////////////////////////////////////////////////////////////////////////


// [[Rcpp::export]]
DataFrame calculateJr(DataFrame centroids,double exponent){
  NumericVector ids=as<NumericVector>(centroids[0]);
  NumericVector x=as<NumericVector>(centroids[1]);
  NumericVector y=as<NumericVector>(centroids[2]);
  NumericVector masses=as<NumericVector>(centroids[3]);

    // NumericVector xs(numClusters,0.0);
    // NumericVector ys(numClusters,0.0);
  NumericVector Jr(ids.size(),0.0);
    // NumericVector Ir(ids.size(),0.0);


  for(long i=0;i<ids.size();i++){
    Point2d A=Point2d(x[i],y[i]);
    for(long j=0;j<ids.size();j++){
      Point2d B=Point2d(x[j],y[j]);
      double distance=Functions::getDistance(A,B);
      if(distance>0){
        Jr[i]+=masses[j]/pow(distance,exponent);
      }

    }

  }

  List list(2);
  list[0]=ids;
  list[1]=Jr;

  




  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("Jr");
  


  
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;



}



// [[Rcpp::export]]
DataFrame calculateIr(DataFrame centroids,DataFrame populationCentroids,double exponent){
  NumericVector ids=as<NumericVector>(centroids[0]);
  NumericVector x=as<NumericVector>(centroids[1]);
  NumericVector y=as<NumericVector>(centroids[2]);
  NumericVector massShop=as<NumericVector>(centroids[3]);

  NumericVector x_pop=as<NumericVector>(populationCentroids[1]);
  NumericVector y_pop=as<NumericVector>(populationCentroids[2]);

  NumericVector masses=as<NumericVector>(populationCentroids[3]);

    // NumericVector xs(numClusters,0.0);
    // NumericVector ys(numClusters,0.0);
  NumericVector Ir(ids.size(),0.0);
    // NumericVector Ir(ids.size(),0.0);


  for(long i=0;i<ids.size();i++){
    Point2d A=Point2d(x[i],y[i]);
    for(long j=0;j<x_pop.size();j++){
      Point2d B=Point2d(x_pop[j],y_pop[j]);
      double distance=Functions::getDistance(A,B);
      if(distance>0){
        Ir[i]+=masses[j]/pow(distance,exponent);
      }

    }

  }

  List list(2);
  list[0]=ids;
  list[1]=Ir;

  




  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("Ir");
  


  
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;



}




// [[Rcpp::export]]
NumericVector simulatedAnnealingRetailFloorSpaceClusters(XPtr< Grafo > G, DataFrame originalShops,DataFrame resultModel,double tolerance,double initialT,double e1,double e2,double e3,double m1,double m2,double m3,double decreaseT,double eD){
  std::vector<long> ids=as<std::vector<long> > (resultModel[0]);
  std::vector<double> currentSizes=as<std::vector<double> > (resultModel[1]);
  std::vector<double> originalSizes=as<std::vector<double> > (originalShops[2]);
  std::vector<double> xs=as<std::vector<double> > (originalShops[0]);
  std::vector<double> ys=as<std::vector<double> > (originalShops[1]);
  std::vector<long> massCluster;
  std::vector<long> clusters;
  std::vector<double> floorSpaceCluster;
  double floorSpaceOutsideClusters=0;
  std::vector<long> numDifN;
  double numDifNOutsideClusters=0;
  std::vector<Point2d> centroids;
  std::vector<Point2d> originalPositions;
  std::vector<double> distances;
  double totalDegrees=0;
  bool firstTime=true;
  double initialEnergy=0;

  // std::set<long> idsExternalFrontierNodes;
  std::queue<long> idsFrontierNodes;
  // std::vector<double> currentSizes_;
//  std::vector<double> originalSizes_=as<std::vector<double> > (originalSizes);
  // currentSizes_.resize(originalSizes_.size(),0);
 clusters.resize(originalSizes.size(),-1);
  floorSpaceCluster.resize(currentSizes.size(),0);
    numDifN.resize(currentSizes.size(),0);
    massCluster.resize(currentSizes.size(),0);
    std::vector<double> minDistances;
    distances.resize(currentSizes.size(),0);
    minDistances.resize(currentSizes.size(),0);
    centroids.resize(currentSizes.size(),Point2d(0,0));
    originalPositions.resize(currentSizes.size(),Point2d(0,0));
    std::vector<double> maxDistances;
    maxDistances.resize(currentSizes.size(),0);
    std::vector<long> massClusterInitial;
    massClusterInitial.resize(currentSizes.size(),0);
  // double tolerance=.1;
  double energy=0;
  double totalFloorSpace=0;
  std::vector<bool> isOriginalShop;
  isOriginalShop.resize(originalSizes.size(),false);

  std::vector<long> numberBorderNodes;
numberBorderNodes.resize(currentSizes.size(),0);


long numberExternalNodes=0;
// double externalDistance=0;
Point2d originLargestNode=Point2d(0,0);
long indexLargestShop;
double maxSize=0;
double totalMinDistance=0;

std::vector<InterfaceDijkstra> distancesFromShoppingCenters;
distancesFromShoppingCenters.resize(currentSizes.size(),InterfaceDijkstra());
std::vector<double> initialFloorSpace;
initialFloorSpace.resize(currentSizes.size(),0);
 std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  for(long i=0;i<currentSizes.size();i++){
    // currentSizes_[ids[i]]=currentSizes[i];
    clusters[ids[i]]=i;
    // floorSpaceCluster[i]+=originalSizes[ids[i]];
    isOriginalShop[ids[i]]=true;
    centroids[i]=Point2d(xs[ids[i]],ys[ids[i]]);
    originalPositions[i]=Point2d(xs[ids[i]],ys[ids[i]]);
    if(currentSizes[i]>maxSize){
      maxSize=currentSizes[i];
      originLargestNode=Point2d(xs[ids[i]],ys[ids[i]]);
      indexLargestShop=i;
    }
    // idsFrontierNodes.insert(ids[i]);
    // for(long j=0;j<G->nodes[ids[i]]->links.size();j++){
    //     numDifN[i]++;
    //     // idsExternalFrontierNodes.insert(G->nodes[ids[i]]->links[j]->b->id);
    //     // numDifN[G->nodes[i].links->b->id]++;
    //   }
      // massCluster[i]++;
     Grafo::calculateDijkstra(G,G->nodes[ids[i]],distancesFromShoppingCenters[i],0,numbersRepresentingNodes,inDijkstra,inCutoff);


  }
  Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);


  double worstCaseDistance=0;

  for(long i=0;i<originalSizes.size();i++){
    totalDegrees+=G->nodes[i]->getDegree();
    totalFloorSpace+=originalSizes[i];
    double min=INFINITY;
    // std::vector<long> shopCentersRankedByCloseness;
    // std::vector<double> distanceShopCentersRankedByCloseness;
    // shopCentersRankedByCloseness.resize(currentSizes,0);
    // distanceShopCentersRankedByCloseness.resize(currentSizes.size(),0);
    for(long j=0;j<currentSizes.size();j++){
      // shopCentersRankedByCloseness[j]=j;
      // distanceShopCentersRankedByCloseness[j]=distancesFromShoppingCenters[j].getMinDistance(i);
      if(distancesFromShoppingCenters[j].getMinDistance(i)<min){
        maxDistances[j]+=distancesFromShoppingCenters[j].getMinDistance(i);
        min=distancesFromShoppingCenters[j].getMinDistance(i);
        clusters[i]=j;
      }

    }
    // std::vector<long> orderRankDistances=Functions::getIndexesOfOrderedValues(distanceShopCentersRankedByCloseness,true);
    // for(long j=0;j<currentSizes.size();j++){
    //   distancesFromShoppingCenters[j].setMinDistance(i,orderRankDistances[j]+0);
    // }

    if(min==INFINITY){
    //  std::cout<<"error in the distance "<<'\n';
    }
    // sstd::cout<<"minDistance to a shopping center "<<min<<'\n';
    floorSpaceCluster[clusters[i]]+=originalSizes[i];
    massCluster[clusters[i]]++;
    if(clusters[i]==-1){

      floorSpaceOutsideClusters+=originalSizes[i];
      
    }
    Point2d point;
      point.x=xs[i];
      point.y=ys[i];
    worstCaseDistance+=pow(distancesFromShoppingCenters[indexLargestShop].getMinDistance(i),eD);
    

    if(clusters[i]==-1){
      numberExternalNodes++;
      
      // externalDistance+=Functions::getDistance(point,originLargestNode);
      numDifNOutsideClusters+=G->nodes[i]->getDegree();
    }
    
  }
  for(long i=0;i<originalSizes.size();i++){
    if(clusters[i]!=-1){
      initialFloorSpace[clusters[i]]+=originalSizes[i];
      totalMinDistance+=pow(distancesFromShoppingCenters[clusters[i]].getMinDistance(i),eD);
      minDistances[clusters[i]]+=pow(distancesFromShoppingCenters[clusters[i]].getMinDistance(i),eD);
      distances[clusters[i]]+=pow(distancesFromShoppingCenters[clusters[i]].getMinDistance(i),eD);
      long numberDifferentClusters=0;
      for(long j=0;j<G->nodes[i]->links.size();j++){
        if(clusters[i]!=clusters[G->nodes[i]->links[j]->getOtherNode(G->nodes[i])->id]){
          numberDifferentClusters++;
        }
      }
      if(numberDifferentClusters>0){
        idsFrontierNodes.push(i);
        numDifN[clusters[i]]+=numberDifferentClusters;
        numberBorderNodes[clusters[i]]++;
      }
    }
  }

 for(long i=0;i<currentSizes.size();i++){
  std::cout<<"distances "<<distances[i]<<'\n';
  std::cout<<"minDistances "<<minDistances[i]<<'\n';
  std::cout<<"massCluster "<<massCluster[i]<<'\n';
 }
 std::cout<<"total min distance "<<totalMinDistance<<'\n';
  double T=initialT;

double numAccepted=0;
double numWrong=0;
  energy=INFINITY;
  std::cout<<"energy "<<energy<<" T "<<T<<" "<<energy/totalFloorSpace<<'\n';
  long counter=0;
  while(T>tolerance){
    counter++;


    long indexRandomNode=idsFrontierNodes.front();
    idsFrontierNodes.pop();




    if(!isOriginalShop[indexRandomNode]){
      long currentCluster=clusters[indexRandomNode];
      std::vector<long> clustersOfNeighbours;
   
      std::vector<long> idN;
      for(long i=0;i<G->nodes[indexRandomNode]->links.size();i++){
        if(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=-1&&clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=currentCluster){
          clustersOfNeighbours.push_back(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]);

          idN.push_back(G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id);
          
        }

      }
      if(clustersOfNeighbours.size()>0){

        long indexNewNode=Functions::runiform(0,clustersOfNeighbours.size()-1);
        long newCluster=clustersOfNeighbours[indexNewNode];
        massCluster[newCluster]++;
        
        if(currentCluster==-1){

          numberExternalNodes--;

          Point2d point;
      point.x=xs[indexRandomNode];
      point.y=ys[indexRandomNode];

          // externalDistance-=Functions::getDistance(point,originLargestNode);
            numDifNOutsideClusters-=G->nodes[indexRandomNode]->getDegree();
            numDifN[newCluster]+=G->nodes[indexRandomNode]->getDegree();
    
            point.x=xs[G->nodes[indexRandomNode]->id];
            point.y=ys[G->nodes[indexRandomNode]->id];
            distances[newCluster]+=pow(distancesFromShoppingCenters[newCluster].getMinDistance(indexRandomNode),eD);
            centroids[newCluster].x+=point.x;
            centroids[newCluster].y+=point.y;
          }else{
            massCluster[currentCluster]--;
            numDifN[currentCluster]-=G->nodes[indexRandomNode]->getDegree();
            numDifN[newCluster]+=G->nodes[indexRandomNode]->getDegree();
            Point2d point;
            point.x=xs[G->nodes[indexRandomNode]->id];
            point.y=ys[G->nodes[indexRandomNode]->id];
            distances[newCluster]+=pow(distancesFromShoppingCenters[newCluster].getMinDistance(indexRandomNode),eD);
            if(currentCluster<0||currentCluster>=currentSizes.size()||indexRandomNode<0||indexRandomNode>=G->nodes.size()){
              std::cout<<"what???"<<'\n';
            }
            if (!isfinite(distancesFromShoppingCenters[currentCluster].getMinDistance(indexRandomNode))){
              std::cout<<"weird, current cluster "<<currentCluster<<" clusters size "<<clusters.size()<<" indexNode "<<indexRandomNode<<" nodes size "<<G->nodes.size()<<'\n';
            }else{
                
            }
            distances[currentCluster]+=pow(distancesFromShoppingCenters[currentCluster].getMinDistance(indexRandomNode),eD);
            centroids[currentCluster].x-=point.x;
            centroids[currentCluster].y-=point.y;
            centroids[newCluster].x+=point.x;
            centroids[newCluster].y+=point.y;
          }
          std::queue<long> possibleNewFrontierNodes;
          long numberDifferentClustersFromNewCluster=0;
        for(long i=0;i<G->nodes[indexRandomNode]->links.size();i++){

          if(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=-1&&clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]==currentCluster){
              numDifN[currentCluster]+=2;
            }
            if(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=-1&&clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=newCluster){
              numberDifferentClustersFromNewCluster++;
              possibleNewFrontierNodes.push(G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id);
            }
            if(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=-1&&clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]==newCluster){
              numDifN[newCluster]-=2;
            }
            

        }
        if(numberDifferentClustersFromNewCluster>0){
          possibleNewFrontierNodes.push(indexRandomNode);
        }

  
        if(currentCluster!=newCluster){


          if(currentCluster==-1){
            floorSpaceOutsideClusters-=originalSizes[indexRandomNode];
          }else{
            floorSpaceCluster[currentCluster]-=originalSizes[indexRandomNode];
            
          }
       
              floorSpaceCluster[newCluster]+=originalSizes[indexRandomNode];
          










          double energyTemp=0;
          for(long i=0;i<currentSizes.size();i++){

            Point2d centroid;
    
            centroid.x=centroids[i].x/massCluster[i];
            centroid.y=centroids[i].y/massCluster[i];
            // double distanceCentroid=Functions::getDistance(centroid,originalPositions[i]);
            double diffD=pow((Functions::abs(distances[i]))/massCluster[i],e3);
            double originalD=pow((Functions::abs(minDistances[i]))/maxDistances[i],e3);
            double averK=pow((numDifN[i])/sqrt(massCluster[i]),e1);
           double difFloorSpace=pow(Functions::abs(currentSizes[i]-floorSpaceCluster[i]),e2);
// double difFloorSpace=pow(Functions::max(0,currentSizes[i]-floorSpaceCluster[i])*pow(currentSizes[i],e1),e2);

           //double difFloorSpace=pow(Functions::max(0,currentSizes[i]-floorSpaceCluster[i])/totalFloorSpace,e2);
            //double difFloorSpace=pow(Functions::abs((currentSizes[i])-(floorSpaceCluster[i]))*pow((currentSizes[i]),e2),2)/pow(totalFloorSpace,2);
            // std::cout<<difFloorSpace<<" "<<massCluster[i]<<" "<<floorSpaceCluster[i]<<" "<<currentSizes[i]<<" other: "<<averK<<" "<<averD<<'\n';
            // energyTemp+=m2*(difFloorSpace)*pow((currentSizes[i]/totalFloorSpace),e2)+m1*averK+m3*averD;


            // energyTemp+=difFloorSpace*(m2+m3*diffD);
           // energyTemp+=difFloorSpace*m2+m3*diffD+m1*averK;
           energyTemp=pow(difFloorSpace*m2,m1*averK);

          }
          // double currentEnergy=energyTemp+m2*pow(floorSpaceOutsideClusters/(numberExternalNodes+1)+1,e2)+m1*pow(numDifNOutsideClusters/(sqrt(numberExternalNodes)+1)+1,e1)+m3*pow(externalDistance/(sqrt(numberExternalNodes)+1)+1,e3);
          double currentEnergy=energyTemp;
          if (firstTime){
            initialEnergy=currentEnergy;
            firstTime=false;
          }
          // currentEnergy/=initialEnergy;












          // std::cout<<"energy "<<energy<<" "<<currentEnergy<<" T "<<T<<'\n';
           if(Functions::runiform(0,1)<.0000005||counter%1000000==0){
                std::cout<<"E_t-1 "<<energy<<" E_t "<<currentEnergy<<" %A "<<numAccepted/numWrong<<" F_shop "<<originalSizes[indexRandomNode]<<" F_newcluster "<<currentSizes[newCluster]<<" F_oldCluster "<<currentSizes[currentCluster]<<" T "<<T<<'\n';
          }
          bool accepted=true;
          if(currentEnergy<energy){
            energy=currentEnergy;
            clusters[indexRandomNode]=newCluster;
            
          }else{
            if(energy-currentEnergy!=0){
              numWrong++;
            }
            double random=Functions::runiform(0,1);
            if (random<exp((energy-currentEnergy)/T)){
              if(energy-currentEnergy!=0){
                numAccepted++;
              }
              energy=currentEnergy;
              clusters[indexRandomNode]=newCluster;
                  // std::cout<<"energy "<<energy<<" T "<<T<<" "<<energy/totalFloorSpace<<'\n';
            }else{
              accepted=false;
            }
          }
         
          if(!accepted){
            idsFrontierNodes.push(indexRandomNode);
            massCluster[newCluster]--;
        massCluster[currentCluster]++;
  
         if(currentCluster==-1){
          numberExternalNodes++;
          Point2d point;
      point.x=xs[indexRandomNode];
      point.y=ys[indexRandomNode];

          // externalDistance+=Functions::getDistance(point,originLargestNode);
            numDifNOutsideClusters+=G->nodes[indexRandomNode]->getDegree();
            numDifN[newCluster]-=G->nodes[indexRandomNode]->getDegree();

            point.x=xs[G->nodes[indexRandomNode]->id];
            point.y=ys[G->nodes[indexRandomNode]->id];
            distances[newCluster]-=pow(distancesFromShoppingCenters[newCluster].getMinDistance(indexRandomNode),eD);
            centroids[newCluster].x-=point.x;
            centroids[newCluster].y-=point.y;
          }else{
            numDifN[currentCluster]+=G->nodes[indexRandomNode]->getDegree();
            numDifN[newCluster]-=G->nodes[indexRandomNode]->getDegree();
            Point2d point;
            point.x=xs[G->nodes[indexRandomNode]->id];
            point.y=ys[G->nodes[indexRandomNode]->id];
            distances[newCluster]-=pow(distancesFromShoppingCenters[newCluster].getMinDistance(indexRandomNode),eD);
            if(currentCluster<0||currentCluster>=currentSizes.size()){
              std::cout<<"what???"<<'\n';
            }
            if (!isfinite(distancesFromShoppingCenters[currentCluster].getMinDistance(indexRandomNode))){
              std::cout<<"weird, current cluster "<<currentCluster<<" clusters size "<<clusters.size()<<" indexNode "<<indexRandomNode<<" nodes size "<<G->nodes.size()<<'\n';
            }else{
                
            }
            distances[currentCluster]+=pow(distancesFromShoppingCenters[currentCluster].getMinDistance(indexRandomNode),eD);
            centroids[currentCluster].x+=point.x;
            centroids[currentCluster].y+=point.y;
            centroids[newCluster].x-=point.x;
            centroids[newCluster].y-=point.y;
          }
        for(long i=0;i<G->nodes[indexRandomNode]->links.size();i++){

          if(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=-1&&clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]==currentCluster){
              numDifN[currentCluster]-=2;
            }
            if(clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]!=-1&&clusters[G->nodes[indexRandomNode]->links[i]->getOtherNode(G->nodes[indexRandomNode])->id]==newCluster){
              numDifN[newCluster]+=2;
            }

        }


            floorSpaceCluster[newCluster]-=originalSizes[indexRandomNode];
            if(currentCluster!=-1){
              floorSpaceCluster[currentCluster]+=originalSizes[indexRandomNode];
            }else{
              floorSpaceOutsideClusters+=originalSizes[indexRandomNode];
            }
          }else{
            while(possibleNewFrontierNodes.size()>0){
              idsFrontierNodes.push(possibleNewFrontierNodes.front());
              possibleNewFrontierNodes.pop();
            }
          }


        }
      }
    }

      T*=decreaseT;



  }

double energyF=0;
  double energyD=0;
for(long i=0;i<currentSizes.size();i++){

            Point2d centroid;
    
            centroid.x=centroids[i].x/massCluster[i];
            centroid.y=centroids[i].y/massCluster[i];
            
            double diffD=pow((Functions::abs(distances[i])),e3);
            double originalD=pow((Functions::abs(minDistances[i]))/maxDistances[i],e3);
            double averK=pow((numDifN[i])/sqrt(massCluster[i]+1),e1);
           double difFloorSpace=pow(Functions::abs(currentSizes[i]-floorSpaceCluster[i]),e2);

           energyD+=m3*diffD;
           energyF+=difFloorSpace*m2;

          }
std::cout<<"energyF "<<energyF<<" energyD "<<energyD<<'\n';
  return wrap(clusters);


}



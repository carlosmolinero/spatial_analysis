#include "Tree.h"


long Tree::getParent(Grafo* tree,long node){
  // NumericVector parents;
  if(node<tree->nodes.size()){
    // long parent=node;
    std::vector<Link*> linksThatReachMe=tree->nodes[node]->getLinksThatReachMe(true);
    if(linksThatReachMe.size()>0){
      long parent=linksThatReachMe[0]->A()->id;
      // std::cout<<"parent "<<parent<<'\n';
      // linksThatReachMe=tree->nodes[parent]->getLinksThatReachMe(true);
      // parents.push_back(parent);
      return parent;
    }
    else return -1;

  }else {
    return -1;
  }


}


std::vector<long> Tree::getAllParents(Grafo* tree,long node){
  std::vector<long> parents;
  if(node<tree->nodes.size()){
//    long parent=node;
//    std::vector<Link*> linksThatReachMe=;
if(tree->nodes[node]->getLinksThatReachMe(true).size()>0){
    long parent=tree->nodes[node]->getLinksThatReachMe(true)[0]->A()->id;
      parents.push_back(parent);
    while(parent!=-1){
//      long parent=linksThatReachMe[0]->A()->id;
        if(tree->nodes[parent]->getLinksThatReachMe(true).size()>0){
            parent=tree->nodes[parent]->getLinksThatReachMe(true)[0]->A()->id;
            parents.push_back(parent);
        }else{
            parent=-1;
        }
      // std::cout<<"parent "<<parent<<'\n';
//      tree->nodes[parent]->getLinksThatReachMe(true);


    }
  }

  }
  return parents;


}






std::unordered_map<long,double> Tree::getCoordinatesOfANodeInATree(Grafo* tree,long node){
  // NumericVector allSons=getSonsAllLevelsInHierarchicalMetricTree(tree,node);

  std::unordered_map<long,double> coordinates;

  // coordinates.resize(tree->nodes.size(),0);


      std::vector<long> parents=getAllParents(tree,node);
      for(long j=0;j<parents.size();j++){
        coordinates[parents[j]]++;
      }
      coordinates[node]++;



  return coordinates;
}



std::vector<long> Tree::getParentsInHierarchicalMetricTreeUpToADepth(Grafo* tree,std::vector<long> currentClusters,std::vector<long> depths,long referenceDepth){

std::vector<long> newClusters;
newClusters.resize(currentClusters.size(),-1);
  for(long i=0;i<currentClusters.size();i++){
    if(depths[currentClusters[i]]>referenceDepth){
      long cluster=currentClusters[i];
      while(depths[cluster]>referenceDepth){
        Nodo* node=tree->nodes[cluster];
        std::vector<Link*> linksThatReachMe=node->getLinksThatReachMe(true);
        Nodo* parentNode=NULL;
        if(linksThatReachMe.size()>0){
          parentNode=linksThatReachMe[0]->A();
        }
        newClusters[i]=parentNode->id;
        cluster=parentNode->id;
      }
    }else{
      newClusters[i]=currentClusters[i];
    }
  }
  return newClusters;

}






std::vector<long> Tree::getSonsInHierarchicalMetricTree(Grafo* tree,long node){
	 std::vector<long> sons;
	 sons.resize(tree->nodes[node]->links.size(),-1);
  if(node<tree->nodes.size()){

    for(long i=0;i<tree->nodes[node]->links.size();i++){
      sons[i]=tree->nodes[node]->links[i]->B()->id;
    }

  }
   return sons;


}


std::vector<long> Tree::getSonsAllLevelsInHierarchicalMetricTree(Grafo* tree,long node){

  std::vector<long> sons;
  std::vector<long> sonsToCheck;
  sons=Tree::getSonsInHierarchicalMetricTree(tree,node);
  for(long i=0;i<sons.size();i++){
    sonsToCheck.push_back(sons[i]);
  }
  while(sonsToCheck.size()>0){
    std::vector<long> sonsTemp=Tree::getSonsInHierarchicalMetricTree(tree,sonsToCheck[sonsToCheck.size()-1]);
    sonsToCheck.pop_back();
    for(long i=0;i<sonsTemp.size();i++){
      sonsToCheck.push_back(sonsTemp[i]);
      sons.push_back(sonsTemp[i]);
    }
  }
  return sons;

}




std::vector<long> Tree::getLeavesSonsOfANode(Grafo* tree,long node){


  std::vector<long> sons;
  std::vector<long> sonsToCheck;
  sons=Tree::getSonsInHierarchicalMetricTree(tree,node);
  for(long i=0;i<sons.size();i++){
    sonsToCheck.push_back(sons[i]);
  }
  while(sonsToCheck.size()>0){
    std::vector<long> sonsTemp=Tree::getSonsInHierarchicalMetricTree(tree,sonsToCheck[sonsToCheck.size()-1]);
    sonsToCheck.pop_back();
    for(long i=0;i<sonsTemp.size();i++){
      sonsToCheck.push_back(sonsTemp[i]);
      std::vector<long> sonsTempTemp=Tree::getSonsInHierarchicalMetricTree(tree,sonsTemp[i]);
      if(sonsTempTemp.size()==0){
        sons.push_back(sonsTemp[i]);
      }
    }
  }
  return sons;

}




double Tree::distanceBetweenNodesInATree(std::unordered_map<long,double> coordinatesA,std::unordered_map<long,double> coordinatesB){
  double distance=0;
  for(long i=0;i<coordinatesA.size();i++){
    double valueA=0;
    double valueB=0;
    valueA=Functions::getValueAt(coordinatesA,i,0);
  // }
  // if(coordinatesB.find(i)!=coordinatesB.end()){
    valueB=Functions::getValueAt(coordinatesB,i,0);
    distance+=Functions::abs(valueA-valueB);
  }
  return distance;
}



long Tree::calculateTopologicalDistancesInATreeBetweenTwoNodes(Grafo* T,long idA,long idB){
  if(idA==idB){
    return 0;
  }else{
    std::unordered_map<long,long> depthsByVertexFromA;
    Nodo* a=T->nodes[idA];
    Nodo* b=T->nodes[idB];

    Nodo* current=a;
    std::vector<Link*> linksReachMe=current->getLinksThatReachMe(true);
    Nodo* parent=NULL;
    if(linksReachMe.size()>0){
      parent=linksReachMe[0]->getOtherNode(current);
    }
    double d=0;
    if(parent==b){
      d++;

    }
    while(parent!=NULL&&parent!=b){
      linksReachMe=current->getLinksThatReachMe(true);
      parent=NULL;
      if(linksReachMe.size()>0){
        parent=linksReachMe[0]->getOtherNode(current);
      }
      d++;
      current=parent;
    }
    current=b;
    linksReachMe=current->getLinksThatReachMe(true);
    parent=NULL;
    if(linksReachMe.size()>0){
      parent=linksReachMe[0]->getOtherNode(current);
    }
    double d2=0;
    if(parent==a){
      d++;
      d2++;
    }
    while(parent!=NULL&&parent!=a){
      linksReachMe=current->getLinksThatReachMe(true);
      parent=NULL;
      if(linksReachMe.size()>0){
        parent=linksReachMe[0]->getOtherNode(current);
      }
      d++;
      d2++;
      if(parent==a){
        d=d2;
      }
      current=parent;
    }
    return d;
  }
}

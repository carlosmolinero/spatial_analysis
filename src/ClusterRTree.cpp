#include "ClusterRTree.h"

ClusterRTree::ClusterRTree()
{
    //ctor
    maxNumberNodes=1;
    depth=0;
    numVertDivisions=2;
    numHorDivisions=2;
    graphCreated=false;
    parent=NULL;
    idClusters=0;
    isLeave=true;
    idTransitions=0;
    northIsExternal=false;
    westIsExternal=false;
    eastIsExternal=false;
    southIsExternal=false;
    completedBackwardsProcess=false;
    inCalculateDistances=false;
    inConstruction=false;
    distancesCalculated=false;
//    matrixDistances=NULL;
}

ClusterRTree::~ClusterRTree()
{
    //dtor
//    for(int i=0;i<nodesInCluster.size();i++){
//        delete nodesInCluster[i];
//    }
//    for(int i=0;i<frontierNodes.size();i++){
//        delete frontierNodes[i];
//    }

}
//void ClusterRTree::insertDistance(double value,long col,long row,long module){
//    long index=row*module+col;
////    mainCluster->matrixDistances->operator[](index)=value;
//}
//double ClusterRTree::getDistance (long col,long row,long module){
//    long index=row*module+col;
////    return mainCluster->matrixDistances->operator[](index);
//    return 1;
//}
bool ClusterRTree::compareByDepth(ClusterRTree* &a, ClusterRTree* &b)
{
    return (a->depth<b->depth);
}
void ClusterRTree::addNode(Node* &node)
{
    if (isLeave)
    {
        if (nodesInCluster.size()<maxNumberNodes)
        {
            node->depthInRTree=depth;
            nodesInCluster.push_back(node);
        }
        else
        {
            divide();
            getSonThatCorrespondToNode(node)->addNode(node);
        }
    }
    else
    {
        getSonThatCorrespondToNode(node)->addNode(node);
    }
}
void ClusterRTree::addExternalNode(Node* &node)
{
    if(southIsExternal||northIsExternal||eastIsExternal||westIsExternal){
        if (isLeave)
        {
            if (nodesInCluster.size()<maxNumberNodes)
            {
                node->depthInRTree=depth;
                nodesInCluster.push_back(node);
            }
            else
            {
                divide();
                getSonThatCorrespondToNode(node)->addExternalNode(node);
            }
        }
        else
        {
            getSonThatCorrespondToNode(node)->addExternalNode(node);
        }
    }
}
ClusterRTree* ClusterRTree::getSonThatCorrespondToNode(Node* &node)
{

    if (isLeave)
    {
        return NULL;
    }
    else
    {
        bool outside=false;
        if (node->location.x<corners[0].x||node->location.x>corners[1].x||node->location.y<corners[0].y||node->location.y>corners[1].y)
        {
            outside=true;
        }
        if (!outside)
        {
            int numColumn=floor((node->location.x-corners[0].x)/widthClusterSons);
            int numRow=floor((node->location.y-corners[0].y)/heightClusterSons);
            int realIndex=numRow*numVertDivisions+numColumn;
            //        std::cout<<realIndex<<'\n';
            return &(sons[realIndex]);
        }
        else
        {
            return NULL;
        }
    }
}
ClusterRTree* ClusterRTree::getCommonLevelOfTwoNodes(Node* a,Node* b)
{
    ClusterRTree* current=(mainCluster);

    ClusterRTree* clA=current->getSonThatCorrespondToNode(a);
    ClusterRTree* clB=current->getSonThatCorrespondToNode(b);
    while(clA!=NULL&&clB!=NULL&&clA==clB)
    {
        current=clA;

        clA=current->getSonThatCorrespondToNode(a);
        clB=current->getSonThatCorrespondToNode(b);
    }
    return current;
}
//long ClusterRTree::getHighestLevelOfNode(Node* a){
//    ClusterRTree* cluster=getClusterOfNode(a);
//    while(a->idEquivalentUpperVerticalNode!=-1){
//        a=&(cluster->parent->graphTemp->nodes[a->idEquivalentUpperVerticalNode]);
//        cluster=cluster->parent;
//    }
//    return a->depthInRTree;
//
//}
//ClusterRTree* ClusterRTree::getCommonUpperLevelOfTwoNodes(Node* a,Node* b){
//    ClusterRTree* current=(mainCluster);
//    long commonDepth=max(getHighestLevelOfNode(a),getHighestLevelOfNode(b));
//    if(commonDepth>0){
//        ClusterRTree* clA=current->getSonThatCorrespondToNode(a);
//        ClusterRTree* clB=current->getSonThatCorrespondToNode(b);
//        while(clA!=NULL&&clB!=NULL&&clA==clB&&commonDepth>=current->depth){
//            current=clA;
//
//            clA=current->getSonThatCorrespondToNode(a);
//            clB=current->getSonThatCorrespondToNode(b);
//        }
//    }
//    return current;
//}
ClusterRTree* ClusterRTree::getClusterOfNode(Node* a)
{
    ClusterRTree* current=(mainCluster);
    while (current->depth<a->depthInRTree)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
ClusterRTree* ClusterRTree::getDeepestClusterOfNode(Node* a)
{
    ClusterRTree* current=(mainCluster);
    while (!current->isLeave)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
//Node* ClusterRTree::getHighestRepresentativeOfNode(Node* a){
//    Node* node=a;
//    if (a->upperRepresentative==NULL){
//        ClusterRTree* cluster=getClusterOfNode(a);
//        while(node->idEquivalentUpperVerticalNode!=-1){
//            node=&(cluster->parent->graphTemp->nodes[node->idEquivalentUpperVerticalNode]);
//            cluster=cluster->parent;
//        }
//        a->upperLevel=node->depthInRTree;
//        a->upperRepresentative=node;
//        return node;
//    }else{
//        return a->upperRepresentative;
//    }
//
//}
//Node* ClusterRTree::getLowestRepresentativeOfNode(Node* a){
//    Node* node=a;
//    if (a->lowerRepresentative==NULL){
//        ClusterRTree* cluster=getClusterOfNode(a);
//        while(node->idEquivalentLowerVerticalNode!=-1){
//            node=&(cluster->parent->graphTemp->nodes[node->idEquivalentUpperVerticalNode]);
//            cluster=cluster->parent;
//        }
//        a->upperLevel=node->depthInRTree;
//        a->upperRepresentative=node;
//        return node;
//    }else{
//        return a->upperRepresentative;
//    }
//
//}
void ClusterRTree::divide()
{
    isLeave=false;
    mainCluster->leavesById.deleteNode(id);
//    if (parent!=NULL){
//        widthClusterSons=parent->widthClusterSons/(double)(numHorDivisions);
//        heightClusterSons=parent->heightClusterSons/(double)(numVertDivisions);
//    }else{
//        widthClusterSons=(corners[1].x-corners[0].x)/2.0;
//        heightClusterSons=(corners[1].x-corners[0].x)/2.0;
//    }
    int column=0;
    int row=0;
    for(int i=0; i<numVertDivisions*numHorDivisions; i++)
    {
        ClusterRTree cluster;
        cluster.depth=depth+1;
        cluster.parent=this;
        cluster.corners[0]=Point2d(corners[0].x+column*widthClusterSons,corners[0].y+row*heightClusterSons);
        cluster.corners[1]=Point2d(corners[0].x+(column+1)*widthClusterSons,corners[0].y+(row+1)*heightClusterSons);
        cluster.widthClusterSons=widthClusterSons/cluster.numHorDivisions;
        cluster.heightClusterSons=heightClusterSons/cluster.numVertDivisions;
        column++;
        if (column>=numHorDivisions)
        {
            column=0;
            row++;
        }
        cluster.mainCluster=this->mainCluster;
        cluster.id=mainCluster->idClusters;
        mainCluster->idClusters++;


        sons.push_back(cluster);



    }
    if(southIsExternal||northIsExternal||eastIsExternal||westIsExternal)
    {
        mainCluster->externalLeavesById.deleteNode(id);
    }

    for(int i=0; i<sons.size(); i++)
    {
        mainCluster->leavesById.add(sons[i].id, &sons[i]);
        ClusterRTree* clusterTemp=&sons[i];
        mainCluster->clustersByDepth.push(clusterTemp, &compareByDepth);
        if(i==0)
        {
            if(northIsExternal)
            {
                sons[i].northIsExternal=true;
            }
            if(westIsExternal)
            {
                sons[i].westIsExternal=true;
            }
        }
        if(i==1)
        {
            if(northIsExternal)
            {
                sons[i].northIsExternal=true;
            }
            if(eastIsExternal)
            {
                sons[i].eastIsExternal=true;
            }
        }
        if(i==2)
        {
            if(southIsExternal)
            {
                sons[i].southIsExternal=true;
            }
            if(westIsExternal)
            {
                sons[i].westIsExternal=true;
            }
        }
        if(i==3)
        {
            if(southIsExternal)
            {
                sons[i].southIsExternal=true;
            }
            if(eastIsExternal)
            {
                sons[i].eastIsExternal=true;
            }
        }
        
        if(sons[i].southIsExternal||sons[i].northIsExternal||sons[i].eastIsExternal||sons[i].westIsExternal)
        {
            mainCluster->externalLeavesById.add(sons[i].id,&sons[i]);
            ClusterRTree* clusterTemp=&sons[i];
            mainCluster->externalClustersByDepth.push(clusterTemp, &ClusterRTree::compareByDepth);

        }



//        if (i==0){
//            for(int j=0;j<transitionsNorth.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsNorth[j].cb;
//                trans.oppositeTransitionId=transitionsNorth[j].oppositeTransitionId;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->cb=&sons[i];
//
//
//                trans.id=mainCluster->idTransitions;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->oppositeTransitionId=trans.id;
//                mainCluster->idTransitions++;
//                clusterTemp->transitionsNorth.push_back(trans);
//                transitionsById.add(trans.id,&trans);
//            }
//            for(int j=0;j<transitionsWest.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsWest[j].cb;
//                trans.oppositeTransitionId=transitionsWest[j].oppositeTransitionId;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->cb=&sons[i];
//
//
//                trans.id=mainCluster->idTransitions;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->oppositeTransitionId=trans.id;
//                mainCluster->idTransitions++;
//                clusterTemp->transitionsWest.push_back(trans);
//                transitionsById.add(trans.id,&trans);
//            }
//        }
//        if (i==1){
//            for(int j=0;j<transitionsNorth.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsNorth[j].cb;
//                trans.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//
//
//                TransitionCluster trans2;
//                trans2.ca=trans.cb;
//                trans2.cb=&sons[i];
////                trans2.weight=1;
//                trans2.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//                trans2.oppositeTransitionId=trans.id;
//
//                trans.oppositeTransitionId=trans2.id;
//                trans2.ca->transitionsById.add(trans2.id,&trans2);
//                trans2.ca->transitionsSouth.push_back(trans2);
//                clusterTemp->transitionsNorth.push_back(trans);
//                transitionsById.add(trans.id,&trans);
//
//
//            }
//            for(int j=0;j<transitionsEast.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsEast[j].cb;
//                trans.oppositeTransitionId=transitionsEast[j].oppositeTransitionId;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->cb=&sons[i];
//
//
//                trans.id=mainCluster->idTransitions;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->oppositeTransitionId=trans.id;
//                mainCluster->idTransitions++;
//                clusterTemp->transitionsEast.push_back(trans);
//                transitionsById.add(trans.id,&trans);
//            }
//        }
//        if (i==2){
//            for(int j=0;j<transitionsSouth.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsSouth[j].cb;
//                trans.oppositeTransitionId=transitionsSouth[j].oppositeTransitionId;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->cb=&sons[i];
//
//
//                trans.id=mainCluster->idTransitions;
//                trans.cb->transitionsById.get(trans.oppositeTransitionId)->oppositeTransitionId=trans.id;
//                mainCluster->idTransitions++;
//                clusterTemp->transitionsSouth.push_back(trans);
//                transitionsById.add(trans.id,&trans);
//
//
//            }
//            for(int j=0;j<transitionsWest.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsWest[j].cb;
//                trans.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//
//                TransitionCluster trans2;
//                trans2.ca=trans.cb;
//                trans2.cb=&sons[i];
////                trans2.weight=1;
//                trans2.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//                trans2.oppositeTransitionId=trans.id;
//
//                trans.oppositeTransitionId=trans2.id;
//                transitionsById.add(trans.id,&trans);
//                clusterTemp->transitionsWest.push_back(trans);
//                trans2.ca->transitionsById.add(trans2.id,&trans2);
//                trans2.ca->transitionsEast.push_back(trans2);
//            }
//        }
//        if (i==3){
//            for(int j=0;j<transitionsSouth.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsWest[j].cb;
//                trans.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//
//                TransitionCluster trans2;
//                trans2.ca=trans.cb;
//                trans2.cb=&sons[i];
////                trans2.weight=1;
//                trans2.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//                trans2.oppositeTransitionId=trans.id;
//
//                trans.oppositeTransitionId=trans2.id;
//                transitionsById.add(trans.id,&trans);
//                clusterTemp->transitionsWest.push_back(trans);
//                trans2.ca->transitionsById.add(trans2.id,&trans2);
//                trans2.ca->transitionsNorth.push_back(trans2);
//
//
//            }
//            for(int j=0;j<transitionsEast.size();j++){
//                TransitionCluster trans;
//                trans.ca=clusterTemp;
//                trans.cb=transitionsEast[j].cb;
//                trans.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//
//                TransitionCluster trans2;
//                trans2.ca=trans.cb;
//                trans2.cb=&sons[i];
////                trans2.weight=1;
//                trans2.id=mainCluster->idTransitions;
//                mainCluster->idTransitions++;
//
//                trans2.oppositeTransitionId=trans.id;
//
//                trans.oppositeTransitionId=trans2.id;
//                transitionsById.add(trans.id,&trans);
//                clusterTemp->transitionsEast.push_back(trans);
//                trans2.ca->transitionsById.add(trans2.id,&trans2);
//                trans2.ca->transitionsWest.push_back(trans2);
//            }
//        }
    }
    while(nodesInCluster.size()>0)
    {
        Node* node=nodesInCluster[nodesInCluster.size()-1];
        getSonThatCorrespondToNode(node)->addNode(node);
        nodesInCluster.pop_back();
    }

}

void ClusterRTree::generateRTreeGraph(Graph* mainGraph,std::vector<Transition> &originDestinationPairs,int mode)
{
    bool save=false;
////    if (isLeave){
////        generateRTreeGraphAux(mainGraph);
////    }else{
////        for(int i=0;i<sons.size();i++){
////            sons[i].generateRTreeGraph(mainGraph);
////        }
////    }
//    std::vector<ClusterRTree*> leaves=mainCluster->leavesById.getAll();
//    BST<ClusterRTree*> clusters;
//    for(int i=0;i<leaves.size();i++){
//        leaves[i]->generateRTreeGraphAux(mainGraph);
//        if (leaves[i]->parent!=NULL){
//            clusters.add(leaves[i]->parent->id, leaves[i]->parent);
//        }
//    }
////    for(int i=0;i<leaves.size();i++){
////        leaves[i]->handleGraphGenerationAux();
////    }
//    std::vector<ClusterRTree*> clustersVector=clusters.getAll();
//    while(clustersVector.size()>0){
//        clusters.deleteAll();
////        BST<ClusterRTree*> clusters;
//        for(int i=0;i<clustersVector.size();i++){
//            clustersVector[i]->generateRTreeGraphAux(mainGraph);
//            if (clustersVector[i]->parent!=NULL){
//                clusters.add(clustersVector[i]->parent->id, clustersVector[i]->parent);
//            }
//        }
////        for(int i=0;i<clustersVector.size();i++){
////            for(int j=0;j<clustersVector[i]->sons.size();j++){
////                clustersVector[i]->sons[j].handleGraphGenerationAux();
////            }
////
//////            clustersVector[i]->handleGraphGenerationAux();
////        }
//        clustersVector=clusters.getAll();
//
//    }


//    if(originDestinationPairs.size()==0)
//    {
//        std::vector<ClusterRTree*> clustersExternalLeaves=externalLeavesById.getAll();
//
//        for(long i=0; i<clustersExternalLeaves.size(); i++)
//        {
//            for(long j=0; j<clustersExternalLeaves.size(); j++)
//            {
//                if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
//                {
//                    Transition trans;
//                    trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
//                    trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
//                    originDestinationPairs.push_back(trans);
//                }
//
//            }
//        }
//    }

//    mainCluster->timer.start("setClustersToConstructBackwards");

    setClustersToConstructBackwards(originDestinationPairs);
    setClustersToCalculateDistances(originDestinationPairs);
//    mainCluster->timer.stop();
    long currentDepth=mainCluster->clustersByDepth.getMin(&compareByDepth)->depth;
    std::vector<ClusterRTree*> clustersByDepthTemp;
    std::vector<ClusterRTree*> clustersOfALevel;
    long level=0;
//    mainCluster->timer.start("handleGraphGeneration");
    while(mainCluster->clustersByDepth.size()>0)
    {
        ClusterRTree* cluster=mainCluster->clustersByDepth.pop(&compareByDepth);

        if (cluster->depth!=currentDepth)
        {

            currentDepth=cluster->depth;
//            fixHorizontalTransitions(clustersOfALevel);
//            ArchivoTexto textFile;
//            for(int h=0;h<clustersOfALevel.size();h++){
//                std::stringstream nameSS;
//                nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/levels/exampleGraph_level"<<level<<".txt";
//                std::string name=nameSS.str();
//                    textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graph), name);
////                                    textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graphTemp), name);
////                level++;
//            }
            level++;
            clustersOfALevel.clear();

        }
//        else{
        cluster->generateRTreeGraphAux(mainGraph);
        clustersOfALevel.push_back(cluster);
//         }
//        if(mainCluster->clustersByDepth.size()>1){
        clustersByDepthTemp.push_back(cluster);

//        }


    }
//    level++;
    if (clustersOfALevel.size()>0)
    {
//        clustersOfALevel[0]->generateRTreeGraphAux(mainGraph);
//        if (clustersOfALevel[0]->depth!=currentDepth){
//            fixHorizontalTransitions(clustersOfALevel);
//            ArchivoTexto textFile;
//            for(int h=0;h<clustersOfALevel.size();h++){
//                std::stringstream nameSS;
//                nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/levels/exampleGraph_level"<<level<<".txt";
//                std::string name=nameSS.str();
//                textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graph), name);
////                                textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graphTemp), name);
//        //        level++;
//            }
        clustersOfALevel.clear();
//        }
//        clustersByDepthTemp.push_back(cluster);

    }
    while(clustersByDepthTemp.size()>0)
    {
        ClusterRTree* cluster=clustersByDepthTemp[clustersByDepthTemp.size()-1];
        clustersByDepthTemp.pop_back();
        mainCluster->clustersByDepth.push(cluster, &compareByDepth);
    }
//    mainCluster->timer.stop();
//    mainCluster->timer.start("prepareVerticalTransitionsAndShortcuts");
    prepareVerticalTransitionsAndShortcuts();
//    mainCluster->timer.stop();
    std::vector<ClusterRTree*> nextLevel;
    std::vector<ClusterRTree*> leavesInUpperLevel;
//    mainCluster->timer.start("handleGraphGenerationBackwards");
    nextLevel.push_back(mainCluster);

    handleGraphGenerationBackwards(nextLevel,mode);
//    mainCluster->timer.stop();
//    mainCluster->timer.start("after_handleGraphGenerationBackwards");
//    completeConnectionsOfLevel(nextLevel, leavesInUpperLevel);
//    calculateDiameter();


//    mainCluster->timer.start("getMin_cluster_depth");
    currentDepth=mainCluster->clustersByDepth.getMin(&compareByDepth)->depth;
//    mainCluster->timer.stop();
//    std::vector<ClusterRTree*> clustersByDepthTemp;
//    std::vector<ClusterRTree*> clustersOfALevel;
    level=0;
    if (save)
    {
//            mainCluster->timer.start("saving_levels");
        while(mainCluster->clustersByDepth.size()>0)
        {
            ClusterRTree* cluster=mainCluster->clustersByDepth.pop(&compareByDepth);

            if (cluster->depth!=currentDepth)
            {

                currentDepth=cluster->depth;
                //            fixHorizontalTransitions(clustersOfALevel);
//                ArchivoTexto textFile;
                for(int h=0; h<clustersOfALevel.size(); h++)
                {
                    std::stringstream nameSS;
                    nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/levels/exampleGraph_level"<<level<<".txt";
                    std::string name=nameSS.str();
                    TextFile::writeNCOLPlusCoordinatesFile((clustersOfALevel[h]->graph), name);
                    //                                    textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graphTemp), name);
                    //                level++;
                }
                level++;
                clustersOfALevel.clear();

            }
            //        else{
            //        cluster->generateRTreeGraphAux(mainGraph);
            clustersOfALevel.push_back(cluster);
            //         }
            //        if(mainCluster->clustersByDepth.size()>1){
            clustersByDepthTemp.push_back(cluster);

            //        }


        }
        //    level++;
        if (clustersOfALevel.size()>0)
        {
            //        clustersOfALevel[0]->generateRTreeGraphAux(mainGraph);
            //        if (clustersOfALevel[0]->depth!=currentDepth){
            //        fixHorizontalTransitions(clustersOfALevel);
//            ArchivoTexto textFile;
            for(int h=0; h<clustersOfALevel.size(); h++)
            {
                std::stringstream nameSS;
                nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/levels/exampleGraph_level"<<level<<".txt";
                std::string name=nameSS.str();
                TextFile::writeNCOLPlusCoordinatesFile((clustersOfALevel[h]->graph), name);
                //                                textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graphTemp), name);
                //        level++;
            }
            clustersOfALevel.clear();
            //        }
            //                clustersByDepthTemp.push_back(cluster);

        }
//        mainCluster->timer.stop();
    }
//    mainCluster->timer.start("reinsertClusters_in_clusterByDepth");
    while(clustersByDepthTemp.size()>0)
    {
        ClusterRTree* cluster=clustersByDepthTemp[clustersByDepthTemp.size()-1];
        clustersByDepthTemp.pop_back();
        mainCluster->clustersByDepth.push(cluster, &compareByDepth);
    }
//    mainCluster->timer.stop();
//    mainCluster->clustersByDepth=clustersByDepthTemp


}
void ClusterRTree::fixHorizontalTransitions(std::vector<ClusterRTree*> clusters)
{
    for(int i=0; i<clusters.size(); i++)
    {
        for(int j=0; j<clusters[i]->graph->nodes.size(); j++)
        {
            for(int h=0; h<clusters[i]->graph->nodes[j].transitions.size(); h++)
            {
                if(clusters[i]->graph->nodes[j].transitions[h]->a->nodeRepresentedBy!=NULL)
                {
                    clusters[i]->graph->nodes[j].transitions[h]->a=clusters[i]->graph->nodes[j].transitions[h]->a->nodeRepresentedBy;
                }
                if(clusters[i]->graph->nodes[j].transitions[h]->b->nodeRepresentedBy!=NULL)
                {
                    clusters[i]->graph->nodes[j].transitions[h]->b=clusters[i]->graph->nodes[j].transitions[h]->b->nodeRepresentedBy;
                }
            }
        }

    }
}
void ClusterRTree::fixExternalTransitions(ClusterRTree* cluster)
{
//    for(int i=0;i<clusters.size();i++){

    for(int j=0; j<cluster->externalTransitions.size(); j++)
    {
        cluster->externalTransitions[j].a=cluster->externalTransitions[j].a->nodeRepresentedBy;
        cluster->externalTransitions[j].b=cluster->externalTransitions[j].b->nodeRepresentedBy;
    }
//    }
}
void ClusterRTree::prepareVerticalTransitionsAndShortcuts()
{
//    //    if (isLeave){
//    //        generateRTreeGraphAux(mainGraph);
//    //    }else{
//    //        for(int i=0;i<sons.size();i++){
//    //            sons[i].generateRTreeGraph(mainGraph);
//    //        }
//    //    }
//    std::vector<ClusterRTree*> leaves=mainCluster->leavesById.getAll();
//    BST<ClusterRTree*> clusters;
//    for(int i=0;i<leaves.size();i++){
//        leaves[i]->handleGraphGenerationAux();
//        if (leaves[i]->parent!=NULL){
//            clusters.add(leaves[i]->parent->id, leaves[i]->parent);
//        }
//    }
//    //    for(int i=0;i<leaves.size();i++){
//    //        leaves[i]->handleGraphGenerationAux();
//    //    }
//    std::vector<ClusterRTree*> clustersVector=clusters.getAll();
//    while(clustersVector.size()>0){
//        clusters.deleteAll();
//        //        BST<ClusterRTree*> clusters;
//        for(int i=0;i<clustersVector.size();i++){
//            clustersVector[i]->handleGraphGenerationAux();
//            if (clustersVector[i]->parent!=NULL){
//                clusters.add(clustersVector[i]->parent->id, clustersVector[i]->parent);
//            }
//        }
//        //        for(int i=0;i<clustersVector.size();i++){
//        //            for(int j=0;j<clustersVector[i]->sons.size();j++){
//        //                clustersVector[i]->sons[j].handleGraphGenerationAux();
//        //            }
//        //
//        ////            clustersVector[i]->handleGraphGenerationAux();
//        //        }
//        clustersVector=clusters.getAll();
//
//    }
    MinHeap<ClusterRTree*> clustersByDepthTemp;
    while(mainCluster->clustersByDepth.size()>0)
    {
        ClusterRTree* cluster=mainCluster->clustersByDepth.pop(&compareByDepth);
        clustersByDepthTemp.push(cluster, &compareByDepth);
        cluster->handleGraphGenerationAux();

    }
    while(clustersByDepthTemp.size()>0)
    {
        ClusterRTree* cluster=clustersByDepthTemp.pop(&compareByDepth);
        mainCluster->clustersByDepth.push(cluster, &compareByDepth);
    }


}
void ClusterRTree::generateRTreeGraphAux(Graph* mainGraph)
{
    if (!graphCreated)
    {
        if (isLeave)
        {
            handleGraphGeneration(mainGraph);
            graphCreated=true;
//            if (parent!=NULL){
//                parent->generateRTreeGraphAux(mainGraph);
//            }
        }
        else
        {
            bool sonsFinishedCreatingGraphs=true;
            for(long i=0; i<sons.size(); i++)
            {
                if (!sons[i].graphCreated)
                {
                    sonsFinishedCreatingGraphs=false;
                }
            }
            if (sonsFinishedCreatingGraphs)
            {
                handleGraphGeneration(graphTemp);
                graphCreated=true;
//                if (parent!=NULL){
//                    parent->generateRTreeGraphAux(parent->graphTemp);
//                }
            }
        }

    }
}



void ClusterRTree::handleGraphGeneration(Graph* graphOrigin)
{
//    mainCluster->timer.start("handleGraphGeneration");
    if (!isLeave)
    {
//        for (long j=0;j<sons.size();j++){
//            fixExternalTransitions(&sons[j]);
//        }
        for (long j=0; j<sons.size(); j++)
        {

            for(long i=0; i<sons[j].externalTransitionsToSolveLater.size(); i++)
            {
                sons[j].externalTransitionsToSolveLater[i].node->transitions[sons[j].externalTransitionsToSolveLater[i].idTrans]->b=&(graphTemp->nodes[sons[j].graphTemp->nodes[externalTransitionsToSolveLater[i].idB].idEquivalentUpperVerticalNode]);
//                if(&(graphTemp->nodes[sons[j].graphTemp->nodes[externalTransitionsToSolveLater[i].idB].idEquivalentUpperVerticalNode])==NULL){
//                    std::cout<<"a NULL bad sign"<<'\n';
//                }
            }
            for(long i=0; i<sons[j].externalTransitions.size(); i++)
            {

//                if(depth==2){
//                    if(sons[j].externalTransitions[i].b->originalID==4000000003258738&&sons[j].externalTransitions[i].a->originalID==4000000003258733){
//                        std::cout<<"aqui es donde estoy teninedo el problema"<<'\n';
//                    }
//                }
                Transition trans;
//                ClusterRTree* commonlevel=getCommonLevelOfTwoNodes(sons[j].externalTransitions[i].a, sons[j].externalTransitions[i].b);
//                commonlevel=this;
//                if(commonlevel==this){
                if (/* DISABLES CODE */ (false))
                {

                    trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i].a->idEquivalentUpperVerticalNode]);
                    trans.b=&(graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode]);
                    trans.weight=sons[j].externalTransitions[i].weight;
                    graphTemp->addDirectedTransition(trans);
                }
                else
                {
                    ClusterRTree* clusterA;
                    clusterA=getClusterOfNode(sons[j].externalTransitions[i].a);
                    ClusterRTree* clusterB;
                    clusterB=getClusterOfNode(sons[j].externalTransitions[i].b);

                    //                                if (sons[j].externalTransitions[i]->b->nodeRepresentedBy!=NULL) {
//                    std::cout<<sons[j].externalTransitions[i]->a->depthInRTree<<"<"<<sons[j].externalTransitions[i]->b->depthInRTree<<" "<<(sons[j].externalTransitions[i]->a->depthInRTree<sons[j].externalTransitions[i]->b->depthInRTree)<<'\n';


                    if (sons[j].externalTransitions[i].a->depthInRTree>sons[j].externalTransitions[i].b->depthInRTree)
                    {

                        trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i].a->idEquivalentUpperVerticalNode]);
                        trans.b=(sons[j].externalTransitions[i].b);
                        trans.weight=sons[j].externalTransitions[i].weight;
//                        trans.a->transitions.push_back(trans);
//                        CoordinatesTransition coordTrans;
//                        coordTrans.node=trans.a;
////                        coordTrans.idTrans=trans.a->transitions.size()-1;
//                        coordTrans.trans=trans;
//                        clusterB->externalTransitionsToInsertNodeRepresentedBy.push_back(coordTrans);
                        graphTemp->addDirectedTransition(trans);
//                        std::cout<<"a is depper "<<'\n';
//                        Transition trans2;
//                        trans2.b=&(graphTemp->nodes[sons[j].externalTransitions[i].a->nodeRepresentedBy->idEquivalentUpperVerticalNode]);
//                        trans2.a=(sons[j].externalTransitions[i].b);
//                        trans2.weight=sons[j].externalTransitions[i].weight;
//                        trans2.a->transitions.push_back(trans2);
//                        CoordinatesTransition coordTrans2;
//                        coordTrans2.node=trans2.a;
//                        coordTrans2.trans=trans;
////                        coordTrans2.idTrans=trans2.a->transitions.size()-1;
//                        coordTrans2.fixB=false;
//                        trans2.a->transitions.push_back(trans2);
//                        clusterB->externalTransitionsToInsertNodeRepresentedBy.push_back(coordTrans2);
                    }
                    else if (sons[j].externalTransitions[i].a->depthInRTree<sons[j].externalTransitions[i].b->depthInRTree)
                    {
//                        trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i]->a->nodeRepresentedBy->idEquivalentUpperVerticalNode]);
//                        trans.b=(sons[j].externalTransitions[i]->b->nodeRepresentedBy);
//                        trans.weight=sons[j].externalTransitions[i]->weight;
//                        trans.a->transitions.push_back(trans);


//                        ClusterRTree* clusterBParent=clusterB->parent->parent;
//                        bool sonsFinishedCreatingGraphs=true;
//                        for(long h=0;h<clusterBParent->sons.size();h++){
//                            if (!clusterBParent->sons[h].graphCreated){
//                                sonsFinishedCreatingGraphs=false;
//                            }
//                        }
//                        if (sonsFinishedCreatingGraphs){
                        Transition trans;



//                            trans.b=&(clusterB->parent->graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode]);
//                        std::cout<<"ids "<<sons[j].externalTransitions[i].a->originalID<<" "<<sons[j].externalTransitions[i].b->originalID<<'\n';
//                        std::cout<<"depths before "<<sons[j].externalTransitions[i].a->depthInRTree<<" "<<sons[j].externalTransitions[i].b->depthInRTree<<'\n';
//                            trans.b=&(clusterB->parent->parent->graphTemp->nodes[clusterB->parent->graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode].idEquivalentUpperVerticalNode]);
                        ClusterRTree* clusterBTemp=clusterB;
                        Node* nodeBTemp=sons[j].externalTransitions[i].b;
                        while(nodeBTemp->depthInRTree!=sons[j].externalTransitions[i].a->depthInRTree)
                        {
                            nodeBTemp=&clusterBTemp->parent->graphTemp->nodes[nodeBTemp->idEquivalentUpperVerticalNode];
                            clusterBTemp=clusterBTemp->parent;

                        }

                        trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i].a->idEquivalentUpperVerticalNode]);

                        trans.weight=sons[j].externalTransitions[i].weight;


                        ClusterRTree* clusterBParent=clusterBTemp->parent;
                        bool sonsFinishedCreatingGraphs=true;
                        for(long h=0; h<clusterBParent->sons.size(); h++)
                        {
                            if (!clusterBParent->sons[h].graphCreated)
                            {
                                sonsFinishedCreatingGraphs=false;
                            }
                        }
                        if (sonsFinishedCreatingGraphs)
                        {
                            trans.b=&clusterBParent->graphTemp->nodes[nodeBTemp->idEquivalentUpperVerticalNode];
                            graphTemp->addDirectedTransition(trans);
                        }
                        else
                        {

                            trans.b=NULL;
                            trans.idB=(nodeBTemp->id);
                            trans.originalIdB=nodeBTemp->originalID;
                            trans.weight=sons[j].externalTransitions[i].weight;
                            graphTemp->addDirectedTransition(trans);
                            CoordinatesTransition coordTrans;
                            coordTrans.node=trans.a;
                            coordTrans.idTrans=trans.a->transitions.size()-1;
                            coordTrans.idB=trans.idB;
                            clusterBTemp->externalTransitionsToSolveLater.push_back(coordTrans);
                        }

//                        std::cout<<"depths "<<trans.a->depthInRTree<<" "<<trans.b->depthInRTree<<'\n';


//                        }else{
//                            Transition trans;
//
//
//
//                            //                        trans.b=&(clusterB->parent->graphTemp->nodes[clusterB->graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode].idEquivalentUpperVerticalNode]);
//
////                            trans.b=&(clusterB->parent->parent->graphTemp->nodes[clusterB->parent->graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode].idEquivalentUpperVerticalNode]);
//
//                            trans.idB=clusterB->parent->graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode].id;
//                            trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i].a->idEquivalentUpperVerticalNode]);
//                            trans.weight=sons[j].externalTransitions[i].weight;
//                            trans.a->transitions.push_back(trans);
//
//                            CoordinatesTransition coordTrans;
//                            coordTrans.node=trans.a;
//                            coordTrans.idTrans=trans.a->transitions.size()-1;
//                            coordTrans.idB=trans.idB;
//                            clusterB->parent->externalTransitionsToSolveLater.push_back(coordTrans);
//                        }




//                        CoordinatesTransition coordTrans2;
//                        coordTrans2.node=trans2.a;
//                        coordTrans2.trans=trans;
////                        coordTrans2.idTrans=trans2.a->transitions.size()-1;
//                        coordTrans2.fixB=false;
//                        trans2.a->transitions.push_back(trans2);
//                        std::cout<<"b is depper "<<'\n';
                    }
                    else
                    {

                        ClusterRTree* clusterBParent=clusterB->parent;
                        bool sonsFinishedCreatingGraphs=true;
                        for(long h=0; h<clusterBParent->sons.size(); h++)
                        {
                            if (!clusterBParent->sons[h].graphCreated)
                            {
                                sonsFinishedCreatingGraphs=false;
                            }
                        }
                        if (sonsFinishedCreatingGraphs)
                        {
//                        if (clusterB->graphCreated){
//                            if(sons[j].externalTransitions[i].weight==173){
//                                std::cout<<"a ver "<<'\n';
//                            }
                            trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i].a->idEquivalentUpperVerticalNode]);
                            trans.b=&(clusterBParent->graphTemp->nodes[sons[j].externalTransitions[i].b->idEquivalentUpperVerticalNode]);
                            trans.weight=sons[j].externalTransitions[i].weight;
                            graphTemp->addDirectedTransition(trans);
                        }
                        else
                        {

                            trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i].a->idEquivalentUpperVerticalNode]);
//                            trans.b=trans.a;
                            trans.idB=(sons[j].externalTransitions[i].b->id);
                            trans.weight=sons[j].externalTransitions[i].weight;
                            graphTemp->addDirectedTransition(trans);
                            CoordinatesTransition coordTrans;
                            coordTrans.node=trans.a;
                            coordTrans.idTrans=trans.a->transitions.size()-1;
                            coordTrans.idB=trans.idB;
                            clusterB->externalTransitionsToSolveLater.push_back(coordTrans);
                        }
                    }


//                    if (clusterB->depth)
//                    //                                }else if(sons[j].externalTransitions[i]->b->depthInRTree==-1){
//                    //                                    clusterB=getDeepestClusterOfNode(sons[j].externalTransitions[i]->b)->parent;
//                    //                                }else{
//                    //                                    clusterB=getClusterOfNode(sons[j].externalTransitions[i]->b)->parent;
//                    //                                }
//
//                    trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i]->a->nodeRepresentedBy->idEquivalentUpperVerticalNode]);
//                    trans.b=sons[j].externalTransitions[i]->b;
//                    trans.weight=sons[j].externalTransitions[i]->weight;
//                    clusterB->externalTransitionsToSolveLater.push_back(trans);
                }
                //recuperar esto?
//                Transition trans2;
//                trans2.a=sons[j].externalTransitions[i]->a->nodeRepresentedBy;
//                trans2.b=sons[j].externalTransitions[i]->b->nodeRepresentedBy;
//                trans2.weight=sons[j].externalTransitions[i]->weight;
//                trans2.a->transitions.push_back(trans2);
            }
            //                        for(long i=0;i<sons[j].externalTransitionsToSolveLater.size();i++){
            //                            Transition trans;
            //                            trans.a=sons[j].externalTransitionsToSolveLater[i].a;
            //                            trans.b=(graphTemp->nodes[sons[j].externalTransitionsToSolveLater[i].b->idEquivalentUpperVerticalNode].nodeRepresentedBy);
            //                            trans.weight=sons[j].externalTransitionsToSolveLater[i].weight;
            //                            trans.a->transitions.push_back(trans);
            //                        }
            //                        for(long i=0;i<sons[j].externalTransitions.size();i++){
            //                            sons[j].handleGraphGenerationAux();
            //                        }
        }
        //???????????????????????????
//        long initIdParentNodes=graphTemp->nodes.size();
//        std::vector<Node*> frontierNodesTemp;
//        for(long i=0;i<externalTransitionsToSolveLater.size();i++){
//            Node* frontierNode=externalTransitionsToSolveLater[i].b->nodeRepresentedBy;
//
//
//            if (!frontierNode->isFrontierOfDifferentLevel){
//                frontierNodesTemp.push_back(frontierNode);
//
//                graphTemp->addNode();
//                //                frontierNode->equivalentUpperVerticalNode=&(parent->graph->nodes[initIdParentNodes+i]);
//                //                parent->graph->nodes[initIdParentNodes+i].equivalentLowerVerticalNode=frontierNode;
//            }
//            frontierNode->isFrontierOfDifferentLevel=true;
//        }
//        for(long i=0;i<frontierNodesTemp.size();i++){
//            //                            frontierNode=externalTransitions[i]->a->nodeRepresentedBy;
//            //                frontierNode->isFrontier=true;
//            //                frontierNodes.add(frontierNode->id,frontierNode);
//            //                parent->graph->addNode();
//            Node* frontierNode=frontierNodesTemp[i];
//            frontierNode->idEquivalentUpperVerticalNode=initIdParentNodes+i;
//            graphTemp->nodes[initIdParentNodes+i].depthInRTree=depth;
//            graphTemp->nodes[initIdParentNodes+i].idEquivalentLowerVerticalNode=frontierNode->id;
//            graphTemp->nodes[initIdParentNodes+i].location=frontierNode->location;
////            frontierNode->isFrontierOfDifferentLevel=false;
//        }
        //???????????????????????????

        //                    for (long j=0;j<sons.size();j++){
        //                    for(long i=0;i<sons[j].externalTransitions.size();i++){
        //                        Transition trans;
        //                        trans.a=&(graphTemp->nodes[sons[j].externalTransitions[i]->a->nodeRepresentedBy->idEquivalentUpperVerticalNode]);
        //                        trans.b=&(graphTemp->nodes[sons[j].externalTransitions[i]->b->nodeRepresentedBy->idEquivalentUpperVerticalNode]);
        //                        trans.weight=sons[j].externalTransitions[i]->weight;
        //                        trans.a->transitions.push_back(trans);
        //                        Transition trans2;
        //                        trans2.a=sons[j].externalTransitions[i]->a->nodeRepresentedBy;
        //                        trans2.b=sons[j].externalTransitions[i]->b->nodeRepresentedBy;
        //                        trans2.weight=sons[j].externalTransitions[i]->weight;
        //                        trans2.a->transitions.push_back(trans2);
        //                    }
        //                        for(long i=0;i<sons[j].externalTransitions.size();i++){
        //                        std::cout<<"depth "<<sons[j].depth<<'\n';
        //                        sons[j].handleGraphGenerationAux();
        //                        }
        //                    }

    }

    this->graph->numberDistances=graphOrigin->numberDistances;
    if (isLeave)
    {
        graphOrigin->getRTreeInducedSubgraphAndReturnFrontierTransitions((this->graph),nodesInCluster,externalTransitions);
        for(int i=0; i<graph->nodes.size(); i++)
        {
            graph->nodes[i].nodeInOriginalGraph=graph->nodes[i].nodeThatRepresents;
            graph->nodes[i].nodeThatRepresents->nodeInOriginalGraph=graph->nodes[i].nodeThatRepresents;
        }
    }
    else
    {
        std::vector<Node*> nodesInClusterTemp;
        for(int i=0; i<graphOrigin->nodes.size(); i++)
        {
            nodesInClusterTemp.push_back(&(graphOrigin->nodes[i]));
        }
        graphOrigin->getRTreeInducedSubgraphAndReturnFrontierTransitions((this->graph),nodesInClusterTemp,externalTransitions);
    }
//    graph->transformToBidirectional();
//    for (long j=0;j<sons.size();j++){
//        fixExternalTransitions(this);
//    }
//    graph->transformToBidirectional();
//    for (int i=0;i<externalTransitionsToInsertNodeRepresentedBy.size();i++){
////        if (externalTransitionsToInsertNodeRepresentedBy[i].fixB){
//            Transition trans;
//            trans.a=externalTransitionsToInsertNodeRepresentedBy[i].trans.a->nodeRepresentedBy;
//            trans.b=externalTransitionsToInsertNodeRepresentedBy[i].trans.b->nodeRepresentedBy;
//            trans.weight=externalTransitionsToInsertNodeRepresentedBy[i].trans.weight;
//            trans.a->transitions.push_back(trans);
//
////            externalTransitionsToInsertNodeRepresentedBy[i].node->transitions[externalTransitionsToInsertNodeRepresentedBy[i].idTrans].b=externalTransitionsToInsertNodeRepresentedBy[i].node->transitions[externalTransitionsToInsertNodeRepresentedBy[i].idTrans].b->nodeRepresentedBy;
////        externalTransitionsToInsertNodeRepresentedBy[i].node->transitions[externalTransitionsToInsertNodeRepresentedBy[i].idTrans].b=externalTransitionsToInsertNodeRepresentedBy[i].node->transitions[externalTransitionsToInsertNodeRepresentedBy[i].idTrans].b->nodeRepresentedBy;
////        }else{
////            externalTransitionsToInsertNodeRepresentedBy[i].node->transitions[externalTransitionsToInsertNodeRepresentedBy[i].idTrans].a=externalTransitionsToInsertNodeRepresentedBy[i].node->transitions[externalTransitionsToInsertNodeRepresentedBy[i].idTrans].a->nodeRepresentedBy;
////
////        }
//    }
    if (parent!=NULL)
    {
        long initIdParentNodes=parent->graphTemp->nodes.size();
        parent->graphTemp->numberDistances=graph->numberDistances;
        if (externalTransitions.size()==0&&nodesInCluster.size()>0)
        {
            std::cout<<"external transitions.size=0!!!"<<'\n';
        }
        else
        {
            //            std::cout<<"external transitions.size>0"<<'\n';
        }
        for(long i=0; i<externalTransitions.size(); i++)
        {
            Node* frontierNode=externalTransitions[i].a;


            if (!frontierNode->isFrontier)
            {
                frontierNodes.push_back(frontierNode);

                parent->graphTemp->addNode();
                //                frontierNode->equivalentUpperVerticalNode=&(parent->graph->nodes[initIdParentNodes+i]);
                //                parent->graph->nodes[initIdParentNodes+i].equivalentLowerVerticalNode=frontierNode;
            }

            frontierNode->isFrontier=true;
        }
        for(long i=0; i<frontierNodes.size(); i++)
        {
            //                            frontierNode=externalTransitions[i]->a->nodeRepresentedBy;
            //                frontierNode->isFrontier=true;
            //                frontierNodes.add(frontierNode->id,frontierNode);
            //                parent->graph->addNode();
            Node* frontierNode=frontierNodes[i];
            frontierNode->idEquivalentUpperVerticalNode=initIdParentNodes+i;
            parent->graphTemp->nodes[initIdParentNodes+i].depthInRTree=parent->depth;
            parent->graphTemp->nodes[initIdParentNodes+i].idEquivalentLowerVerticalNode=frontierNode->id;
            parent->graphTemp->nodes[initIdParentNodes+i].location=frontierNode->location;
            parent->graphTemp->nodes[initIdParentNodes+i].originalID=frontierNode->originalID;
            parent->graphTemp->nodes[initIdParentNodes+i].nodeInOriginalGraph=frontierNode->nodeInOriginalGraph;

//            frontierNode->isFrontier=false;
        }



    }
    else
    {
        ////                long initIdParentNodes=0;
        //                for(long i=0;i<externalTransitions.size();i++){
        //                    Node* frontierNode=externalTransitions[i]->a->nodeRepresentedBy;
        //                    frontierNode->isFrontier=true;
        //                    frontierNodes.add(frontierNode->id,frontierNode);
        ////                    parent->graph->addNode();
        //                    //                frontierNode->equivalentUpperVerticalNode=&(parent->graph->nodes[initIdParentNodes+i]);
        //                    //                parent->graph->nodes[initIdParentNodes+i].equivalentLowerVerticalNode=frontierNode;
        //                }
        //                for(long i=0;i<externalTransitions.size();i++){
        //                    Node* frontierNode=externalTransitions[i]->a->nodeRepresentedBy;
        //                    //                frontierNode->isFrontier=true;
        //                    //                frontierNodes.add(frontierNode->id,frontierNode);
        //                    //                parent->graph->addNode();
        //                    frontierNode->equivalentUpperVerticalNode=&(parent->graph->nodes[initIdParentNodes+i]);
        //                    parent->graph->nodes[initIdParentNodes+i].equivalentLowerVerticalNode=frontierNode;
        //                    parent->graph->nodes[initIdParentNodes+i].location=frontierNode->location;
        //                }
    }

//    if (parent==NULL){
//        prepareVerticalTransitionsAndShortcuts();
//    }


//            for(int i=0;i<this->graph->nodes.size();i++){
//                this->graph->nodes[i].depthInRTree=depth;
////                if (isLeave){
//                    this->graph->nodes[i].location=this->graph->nodes[i].nodeThatRepresents->location;
////                }
//            }

//    mainCluster->timer.stop();

}

void ClusterRTree::handleGraphGenerationAux()
{
//    mainCluster->timer.start("handleGraphGenerationAux");
    if (parent!=NULL)
    {
//            matrixDistancesCluster.init(graph->nodes.size(),graph->nodes.size());
        //    std::vector<Node*> frontierNodesTemp=frontierNodes.getAll();
        for(long i=0; i<frontierNodes.size(); i++)
        {
            std::vector<Node*> nodesCutoff;
            Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//            Heap<Node*> nodesToCheckDijkstra
            Node* nodeTemp=(frontierNodes[i]->nodeRepresentedBy);
            nodeTemp->minDistance=0;
            nodesCutoff.push_back(nodeTemp);

            nodesToCheckDijkstra.push(nodeTemp);


//            std::vector<Node*> nodesCutoff2;
//            MinHeap<Node*> nodesToCheckDijkstra2;
//            Node* nodeTemp2=(frontierNodes[i]);
//            nodesCutoff2.push_back(nodeTemp2);
//            nodesToCheckDijkstra2.push(nodeTemp2, &Graph::compareByDistance);

            if (!isLeave)
            {
//                mainCluster->timer.start("dijkstra1_hggaux");
                this->graph->calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra);
//                mainCluster->timer.restart("handleGraphGenerationAux");
            }
            //                frontierNodes[i]->depthInRTree=depth;
            //                frontierNodes[i]->location=frontierNodes[i].nodeThatRepresents->location;
            //                if (this->graph->nodes[i].isFrontier){
            for(long j=0; j<frontierNodes.size(); j++)
            {
                //                    if(sons[j].externalTransitions[i].b->originalID==4000000003258738&&sons[j].externalTransitions[i].a->originalID==4000000003258733){
                //                        std::cout<<"aqui es donde estoy teninedo el problema"<<'\n';
                //                    }


                std::vector<Node*> visitedNodes;
                bool insertShortcut=false;
//                if(graph->nodes[i].originalID==4000000003259325&&graph->nodes[j].originalID==4000000003259323){
//                    std::cout<<"que pasa?"<<'\n';
//                }
                if (isLeave)
                {
//                    if(frontierNodes[j]->nodeRepresentedBy->minDistance==INFINITY){
//                    mainCluster->timer.start("AStar_hggaux");
                    mainCluster->originalGraph->AStar(frontierNodes[i],(frontierNodes[j]),visitedNodes,&Graph::metricHeuristic);
//                    mainCluster->timer.restart("handleGraphGenerationAux");
//                    }else{
//                        frontierNodes[j]->minDistance=frontierNodes[j]->nodeRepresentedBy->minDistance;
//                    }
                    if(frontierNodes[j]->minDistance<frontierNodes[j]->nodeRepresentedBy->minDistance)
                    {
                        insertShortcut=true;
                        if(insertShortcut)
                        {
//                            Transition trans2;
//                            trans2.a=&(graph->nodes[i]);
//                            trans2.b=&(graph->nodes[j]);
//                            trans2.weight=graph->nodes[j].nodeThatRepresents->minDistance;
//                            trans2.a->transitions.push_back(trans2);
//                            Transition trans3;
//                            trans3.b=&(graph->nodes[i]);
//                            trans3.a=&(graph->nodes[j]);
//                            trans3.weight=graph->nodes[j].nodeThatRepresents->minDistance;
//                            trans3.a->transitions.push_back(trans3);
////                            graph->nodes[j].minDistance=graph->nodes[j].nodeThatRepresents->minDistance;


                        }
                    }
                }
                else if (frontierNodes[j]->nodeRepresentedBy->minDistance==INFINITY)
                {
//                    Node* lowestNodeA=graph->nodes[i].nodeInOriginalGraph;
//                    Node* lowestNodeB=graph->nodes[j].nodeInOriginalGraph;
//                    std::vector<Node*> visitedNodes2;
//                    mainCluster->originalGraph->AStar(lowestNodeA,lowestNodeB,visitedNodes2);
//
////                    if(graph->nodes[j].nodeThatRepresents->minDistance<graph->nodes[j].minDistance){
//                        insertShortcut=true;
//                        if(insertShortcut){
////                            Transition trans2;
////                            trans2.a=&(graph->nodes[i]);
////                            trans2.b=&(graph->nodes[j]);
////                            trans2.weight=lowestNodeB->minDistance;
////                            trans2.a->transitions.push_back(trans2);
//////                            graph->nodes[j].minDistance=lowestNodeB->minDistance;
////                            Transition trans3;
////                            trans3.b=&(graph->nodes[i]);
////                            trans3.a=&(graph->nodes[j]);
////                            trans3.weight=lowestNodeB->minDistance;
////                            trans3.a->transitions.push_back(trans3);
//
//
//
//
//                        }
//                    for(long h=0;h<visitedNodes2.size();h++){
//
//                        visitedNodes2[h]->minDistance=INFINITY;
//                        visitedNodes2[h]->inAStar=false;
//                        visitedNodes2[h]->inVisitedNodes=false;
//                        visitedNodes2[h]->parent=NULL;
//
//                    }
//                    visitedNodes2.clear();
//                    }
                }
                //                        if (nodeTemp->nodeRepresentedBy!=&(this->graph->nodes[j])){
                if (frontierNodes[j]->isFrontier&&frontierNodes[i]->isFrontier)
                {
                    Node* nodeCurrentDestiny;
                    if (!isLeave)
                    {
                        nodeCurrentDestiny=frontierNodes[j]->nodeRepresentedBy;
                    }
                    else
                    {
                        nodeCurrentDestiny=frontierNodes[j];
                    }


//                    if(inConstruction&&parent!=NULL){
//                        matrixDistancesCluster.set(nodeCurrentDestiny->minDistance,frontierNodes[i]->nodeRepresentedBy->id,frontierNodes[j]->nodeRepresentedBy->id);
//                    }


                    if (nodeCurrentDestiny->minDistance>0&&nodeCurrentDestiny->minDistance<INFINITY)
                    {
                        Transition trans;
                        trans.a=(parent->graphTemp->nodes[frontierNodes[i]->idEquivalentUpperVerticalNode]).nodeRepresentedBy;
                        trans.b=(parent->graphTemp->nodes[frontierNodes[j]->idEquivalentUpperVerticalNode].nodeRepresentedBy);

                        trans.weight=nodeCurrentDestiny->minDistance;

                        parent->graphTemp->addDirectedTransition(trans);

                        Transition trans2;
                        trans2.a=trans.b;
                        trans2.b=trans.a;
                        trans2.weight=trans.weight;
                        parent->graphTemp->addDirectedTransition(trans2);


                    }
                    else
                    {
                        if(graph->nodes[j].minDistance==INFINITY&&graph->nodes[j].nodeThatRepresents->minDistance==INFINITY)
                        {
//                            Transition trans2;
//                            trans2.a=frontierNodes[i]->nodeRepresentedBy;
//                            trans2.b=&(graph->nodes[j]);
//                            trans2.weight=graph->nodes[j].nodeThatRepresents->minDistance;
//                            trans2.a->transitions.push_back(trans2);
//                            std::cout<<"error "<<graph->nodes[i].originalID<<" "<<graph->nodes[j].originalID<<'\n';
                        }
                    }

                    //                            else{
                    //                                if (this->graph->nodes[j].minDistance>0){
                    if (nodeCurrentDestiny->minDistance<INFINITY)
                    {
                        if (nodeCurrentDestiny->minDistance==0)
                        {
                            Transition trans;
                            //                                    Node** pointerToFirstA=frontierNodes.data();
                            long idATemp=frontierNodes[i]->idEquivalentUpperVerticalNode;
                            //                                    Node* pointerToFirst=graph->nodes.data();
                            Node* bTemp= frontierNodes[j]->nodeRepresentedBy;
                            //                                    long idBTemp=graph->nodes[j].id;
                            trans.a=parent->graphTemp->nodes[idATemp].nodeRepresentedBy;
                            trans.b=bTemp;

                            trans.weight=nodeCurrentDestiny->minDistance;

                            trans.a->verticalPathsTowardsLowerLevel.push_back(trans);
                        }
                    }
                    if (frontierNodes[j]->nodeRepresentedBy->minDistance<INFINITY)
                    {
                        if (frontierNodes[j]->nodeRepresentedBy->minDistance==0)
                        {
                            long idATemp=frontierNodes[i]->idEquivalentUpperVerticalNode;
                            Node* bTemp= frontierNodes[j]->nodeRepresentedBy;
                            Transition trans2;
                            trans2.a=bTemp;
                            trans2.b=parent->graphTemp->nodes[idATemp].nodeRepresentedBy;

                            trans2.weight=nodeCurrentDestiny->minDistance;

                            trans2.a->verticalPathsTowardsUpperLevel.push_back(trans2);
                        }
                    }
                    //                                }
                    //                            }
                    //                        }
                    //                        this->graph->nodes[j].minDistance=INFINITY;
//                    if (this->graph->nodes[j].minDistance==INFINITY){
//    //                    std::cout<<"minDistance INFINITY"<<'\n';
//                    }else{
//        //                std::cout<<"minDistanceDespuesAStarGraph "<<this->graph->nodes[j].minDistance<<'\n';
//                    }
                }

                if (isLeave)
                {
                    for(long h=0; h<visitedNodes.size(); h++)
                    {

                        visitedNodes[h]->minDistance=INFINITY;
                        visitedNodes[h]->inAStar=false;
                        visitedNodes[h]->inVisitedNodes=false;
                        visitedNodes[h]->parent=NULL;

                    }
                    visitedNodes.clear();
                }

            }
//            if (!isLeave){
            for(long h=0; h<nodesCutoff.size(); h++)
            {

                nodesCutoff[h]->minDistance=INFINITY;
                nodesCutoff[h]->inDijkstra=false;
                nodesCutoff[h]->inCutoff=false;
                nodesCutoff[h]->numOtherChildren.clear();
                nodesCutoff[h]->parent=NULL;

            }
            nodesCutoff.clear();
            nodesToCheckDijkstra.clear();
//            }
//            nodesCutoff.clear();

            //                }else{
            //                    for(long j=0;j<this->graph->nodes.size();j++){
            ////                        graph->AStar(&(graph->nodes[i]),&(graph->nodes[j]));
            //                        if (i!=j){
            //                            if (this->graph->nodes[j].isFrontier){
            //                                if (this->graph->nodes[j].minDistance>0){
            //                                    Transition trans;
            //                                    trans.a=&(this->graph->nodes[i]);
            //                                    trans.b=this->graph->nodes[j].equivalentUpperVerticalNode;
            //                                    trans.weight=this->graph->nodes[j].minDistance;
            //                                    trans.a->verticalPathsTowardsUpperLevel.push_back(trans);
            //                                }
            //                            }else{
            ////                                if (graph->nodes[j].minDistance>0){
            ////                                    Transition trans;
            ////                                    trans.a=&(graph->nodes[i]);
            ////                                    trans.b=&(graph->nodes[j]);
            ////                                    trans.weight=graph->nodes[j].minDistance;
            ////                                    trans.a->horizontalPaths.push_back(trans);
            ////                                }
            //                            }
            //                        }
            //                        this->graph->nodes[j].minDistance=INFINITY;
            //                    }
            //                }



        }
    }
//    mainCluster->timer.stop();
}
void ClusterRTree::handleGraphGenerationBackwards(std::vector<ClusterRTree*> &nextLevel,int mode)
{
//    mainCluster->timer.start("handleGraphGenerationBackwardsInsideRecursive");
    std::vector<ClusterRTree*> nextLevelTemp;
    while(nextLevel.size()>0)
    {

        ClusterRTree* nextCluster=nextLevel[nextLevel.size()-1];
        nextLevel.pop_back();
//        for(long i=0;i<nextLevel.size();i++){
        //        for(long j=0;j<nextLevel[i]->graph->nodes.size();j++){
        //            nodesInLowerLevel.push_back(&nextLevel[i]->graph->nodes[j]);
        //        }
//        mainCluster->timer.start("pushing_back_nextLevel");
        for(int j=0; j<nextCluster->sons.size(); j++)
        {
            nextLevelTemp.push_back(&(nextCluster->sons[j]));
        }
//        mainCluster->timer.start("init_handleGraphGenerationBackwards_Aux");
        nextCluster->handleGraphGenerationBackwardsAux(mode);
//        mainCluster->timer.restart("handleGraphGenerationBackwardsInsideRecursive");
        //        if(nextLevel[i]->sons.size()==0){
        //            leavesInUpperLevels.push_back(nextLevel[i]);
        //        }

//        }
        if(nextLevel.size()==0)
        {
//            for(int j=0;j<nextLevelTemp.size();j++){
//                nextLevel.push_back(nextLevelTemp[j]);
            nextLevel=nextLevelTemp;
//            }
            nextLevelTemp.clear();
        }
//        mainCluster->timer.start("handleGraphGenerationBackwardsInsideRecursive");

    }
//    mainCluster->timer.restart("handleGraphGenerationBackwards");

//    nextLevel[i]->handleGraphGenerationBackwardsAux();

}
void ClusterRTree::handleGraphGenerationBackwardsAux(int mode)
{
//        std::vector<Node*> nodesInLowerLevel;
//    mainCluster->timer.start("handleGraphGenerationBackwardsInside");
    if(inConstruction)
    {
        if (!isLeave)
        {
            //    std::vector<Node*> frontierNodesTemp=frontierNodes.getAll();
            for(long i=0; i<graph->nodes.size(); i++)
            {

                std::vector<Node*> nodesCutoff;
                Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                Node* nodeTemp=&(graph->nodes[i]);
                nodeTemp->minDistance=0;
                nodesCutoff.push_back(nodeTemp);
                nodesToCheckDijkstra.push(nodeTemp);
//                mainCluster->timer.stop();
//                mainCluster->timer.start("handleGraphGenerationBackwardsAux->dijkstra_01");
                this->graph->calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra);
//                mainCluster->timer.stop();
//                mainCluster->timer.restart("handleGraphGenerationBackwardsInside");
                ClusterRTree* clusterA=getSonThatCorrespondToNode(nodeTemp);
                Node* nodeSonA;
                if(!clusterA->isLeave)
                {
                    nodeSonA=(clusterA->graphTemp->nodes[graph->nodes[i].idEquivalentLowerVerticalNode]).nodeRepresentedBy;
                }
                else
                {
                    nodeSonA=(mainCluster->originalGraph->nodes[graph->nodes[i].idEquivalentLowerVerticalNode]).nodeRepresentedBy;
                }
//                Node* nodeSonA=nodeTemp->verticalPathsTowardsLowerLevel[0].b;

                std::vector<Node*> nodesCutoffSon;
                Heap<Node*> nodesToCheckDijkstraSon(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//                Node* nodeTemp=&(graph->nodes[i]);
                nodesCutoffSon.push_back(nodeSonA);
                nodesToCheckDijkstraSon.push(nodeSonA);
//                mainCluster->timer.stop();
//                mainCluster->timer.start("handleGraphGenerationBackwardsAux->dijkstra_02");
                clusterA->graph->calculateDijkstraSpeed(nodeSonA, 0, nodesCutoffSon, nodesToCheckDijkstraSon);
//                mainCluster->timer.stop();
//                mainCluster->timer.start("for_loop_over_nodes_to_set_something");
                for(long j=0; j<this->graph->nodes.size(); j++)
                {

                    if(parent==NULL&&mode==TREE_DISTANCE&&inCalculateDistances)
                    {
//                        mainCluster->timer.start("setDistancesOf_Main_Cluster");
                        double distance=graph->nodes[j].minDistance;
                        mainCluster->matrixDistances->set(distance, graph->nodes[i].nodeInOriginalGraph->id, graph->nodes[j].nodeInOriginalGraph->id);
                        if(!mainCluster->matrixDistances->bidirectional)
                        {
                            mainCluster->matrixDistances->set(distance, graph->nodes[j].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id);
                        }

//                        if(distance>mainCluster->originalGraph->diameterWeighted){
//                            mainCluster->originalGraph->diameterWeighted=distance;
//                        }
                    }
                    else if(mode==TREE_DISTANCE&&inCalculateDistances)
                    {
//                        mainCluster->timer.start("setDistancesOf_nonMain_Cluster");
                        ClusterRTree* cluster=this;

                        double distance1=graph->nodes[j].minDistance;

//                            insertDistance(distance1, graph->nodes[i].nodeInOriginalGraph->id, graph->nodes[j].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                            insertDistance(distance1, graph->nodes[j].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());

                        mainCluster->matrixDistances->set(distance1, graph->nodes[i].nodeInOriginalGraph->id, graph->nodes[j].nodeInOriginalGraph->id);
                        if(!mainCluster->matrixDistances->bidirectional)
                        {
                            mainCluster->matrixDistances->set(distance1, graph->nodes[j].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id);
                        }
                        if(graph->nodes[j].nodeThatRepresents->isFrontier&&!graph->nodes[i].nodeThatRepresents->isFrontier)
                        {
                            while(cluster->parent!=NULL&&cluster->inCalculateDistances)
                            {
                                for(int h=0; h<cluster->parent->graph->nodes.size(); h++)
                                {
                                    Node* nodeTemp=&cluster->parent->graph->nodes[h];
                                    ClusterRTree* clusterOfSonOfFrontier=getSonThatCorrespondToNode(nodeTemp);
                                    if(clusterOfSonOfFrontier!=this)
                                    {
//                                            double distance=distance1+getDistance(graph->nodes[j].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                                        double distance=distance1+mainCluster->matrixDistances->get(graph->nodes[j].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id);
                                        double distanceTemp=mainCluster->matrixDistances->get(graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id);
                                        if(distanceTemp==-1||distance<distanceTemp)
                                        {
//                                                insertDistance(distance, graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                                                insertDistance(distance, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                                            mainCluster->matrixDistances->set(distance, graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id);
                                            if(!mainCluster->matrixDistances->bidirectional)
                                            {
                                                mainCluster->matrixDistances->set(distance, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id);
                                            }
                                            //                                        if(distance>mainCluster->originalGraph->diameterWeighted){
                                            //                                            mainCluster->originalGraph->diameterWeighted=distance;
                                            //                                        }
                                        }
                                    }
                                    else
                                    {
                                        // std::cout<<'\n';
                                    }
                                }
                                cluster=cluster->parent;
                            }
                        }
//                        mainCluster->timer.restart("handleGraphGenerationBackwardsInside");

                    }
                    Node* nodeB=&graph->nodes[j];
                    ClusterRTree* clusterB=getSonThatCorrespondToNode(nodeB);
                    Node* nodeSonB;
                    if(!clusterB->isLeave)
                    {
                        nodeSonB=(clusterB->graphTemp->nodes[graph->nodes[j].idEquivalentLowerVerticalNode]).nodeRepresentedBy;
                    }
                    else
                    {
                        nodeSonB=(mainCluster->originalGraph->nodes[graph->nodes[j].idEquivalentLowerVerticalNode]).nodeRepresentedBy;
                    }
//                    Node* nodeSonB=(clusterB->graphTemp->nodes[graph->nodes[j].idEquivalentLowerVerticalNode]).nodeRepresentedBy;
//                    Node* nodeSonB=nodeB->verticalPathsTowardsLowerLevel[0].b;
                    if(clusterA==clusterB)
                    {
//                        nodeSonB->minDistance=clusterA->matrixDistancesCluster.get(nodeSonA->id,nodeSonB->id);
//                        std::cout<<nodeSonB->minDistance<<" "<<nodeB->minDistance<<'\n';
                        if(nodeSonB->minDistance>nodeB->minDistance||nodeSonB->minDistance==-1)
                        {
//                            mainCluster->timer.start("pushBack_Transitions");
                            Transition trans;
                            trans.a=nodeSonA;
                            trans.b=nodeSonB;
                            trans.weight=nodeB->minDistance;
                            clusterA->graph->addDirectedTransition(trans);
                            Transition trans2;
                            trans2.a=nodeSonB;
                            trans2.b=nodeSonA;
                            trans2.weight=nodeB->minDistance;
                            clusterB->graph->addDirectedTransition(trans2);
                        }
//                        nodeSonB->minDistance=INFINITY;
                    }



                }
                distancesCalculated=true;
//                mainCluster->timer.start("empty_nodesCutoff_current");

                for(long h=0; h<nodesCutoff.size(); h++)
                {

                    nodesCutoff[h]->minDistance=INFINITY;
                    nodesCutoff[h]->inDijkstra=false;
                    nodesCutoff[h]->inCutoff=false;
//                    nodesCutoff[h]->numOtherChildren.clear();
                    nodesCutoff[h]->parent=NULL;

                }

                nodesCutoff.clear();

                nodesToCheckDijkstra.clear();
//                mainCluster->timer.start("empty_nodesCutoffSon");
                for(long h=0; h<nodesCutoffSon.size(); h++)
                {

                    nodesCutoffSon[h]->minDistance=INFINITY;
                    nodesCutoffSon[h]->inDijkstra=false;
                    nodesCutoffSon[h]->inCutoff=false;
//                    nodesCutoffSon[h]->numOtherChildren.clear();
                    nodesCutoffSon[h]->parent=NULL;

                }

                nodesCutoffSon.clear();

                nodesToCheckDijkstraSon.clear();
//                mainCluster->timer.restart("handleGraphGenerationBackwardsInside");
            }
        }
        else
        {
//            for(long i=0;i<graph->nodes.size();i++){
//
//                std::vector<Node*> nodesCutoff;
//                MinHeap<Node*> nodesToCheckDijkstra;
//                Node* nodeTemp=&(graph->nodes[i]);
//                nodeTemp->minDistance=0;
//                nodesCutoff.push_back(nodeTemp);
//                nodesToCheckDijkstra.push(nodeTemp, &Graph::compareByDistance);
//
//                this->graph->calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra);
//
////                ClusterRTree* clusterA=getSonThatCorrespondToNode(nodeTemp);
//
//                for(long j=0;j<this->graph->nodes.size();j++){
//
//                    ClusterRTree* cluster=this;
//
//                    double distance1=graph->nodes[j].minDistance;
//
////                    insertDistance(distance1, graph->nodes[i].nodeInOriginalGraph->id, graph->nodes[j].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
////                    insertDistance(distance1, graph->nodes[j].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                    mainCluster->matrixDistances->set(distance1, graph->nodes[i].nodeInOriginalGraph->id, graph->nodes[j].nodeInOriginalGraph->id);
//                    if(!mainCluster->matrixDistances->bidirectional){
//                        mainCluster->matrixDistances->set(distance1, graph->nodes[j].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id);
//                    }
//                    if(graph->nodes[j].nodeThatRepresents->isFrontier&&!graph->nodes[i].nodeThatRepresents->isFrontier){
//
//                        while(cluster->parent!=NULL&&cluster->parent->inCalculateDistances){
//                            for(int h=0;h<cluster->parent->graph->nodes.size();h++){
//                                Node* nodeTemp=&cluster->parent->graph->nodes[h];
//                                ClusterRTree* clusterOfSonOfFrontier=getSonThatCorrespondToNode(nodeTemp);
//                                if(clusterOfSonOfFrontier!=this){
////                                    double distance=distance1+getDistance(graph->nodes[j].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                                    double distance=distance1+mainCluster->matrixDistances->get(graph->nodes[j].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id);
//                                    double distanceTemp=mainCluster->matrixDistances->get(graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id);
//
//                                    if(distanceTemp==-1||distance<distanceTemp){
////                                        insertDistance(distance, graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
////                                        insertDistance(distance, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                                        mainCluster->matrixDistances->set(distance, graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id);
//                                        if(!mainCluster->matrixDistances->bidirectional){
//                                            mainCluster->matrixDistances->set(distance, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id);
//                                        }
//                                        //                                        if(distance>mainCluster->originalGraph->diameterWeighted){
//                                        //                                            mainCluster->originalGraph->diameterWeighted=distance;
//                                        //                                        }
//                                    }
//                                }else{
//                                    //std::cout<<'\n';
//                                }
//                            }
//                            cluster=cluster->parent;
//                        }
//
//                    }
//
//
//
//
//
//                }
//                distancesCalculated=true;
//                for(long h=0;h<nodesCutoff.size();h++){
//
//                    nodesCutoff[h]->minDistance=INFINITY;
//                    nodesCutoff[h]->inDijkstra=false;
//                    nodesCutoff[h]->inCutoff=false;
//                    nodesCutoff[h]->numOtherChildren.clear();
//                    nodesCutoff[h]->parent=NULL;
//
//                }
//
//                nodesCutoff.clear();
//
//                nodesToCheckDijkstra.clear();
//
//            }
        }





//        if(parent==NULL){
//
//                for(int i=0;i<sons.size();i++){
//                    sons[i].handleGraphGenerationBackwardsAux();
//                    for(int h=0;h<sons[i].graph->nodes.size();h++){
//                        nodesInLowerLevel.push_back(&sons[i].graph->nodes[i]);
//                    }
//                }
//            completedBackwardsProcess=true;
////            completeConnectionsOfLevel(nodesInLowerLevel);
//        }else{
//            bool completed=true;
//            for(int i=0;i<parent->sons.size();i++){
//                if(!parent->sons[i].completedBackwardsProcess){
//                    completed=false;
//                }
//            }
//                if(completed){
//                    for(int i=0;i<parent->sons.size();i++){
//                        for(int j=0;j<parent->sons[i].sons.size();j++){
//                            parent->sons[i].sons[j].handleGraphGenerationBackwardsAux();
//                        }
//
////                        completeConnectionsOfLevel(nodesInLowerLevel);
//                    }
//
//                }
//                completedBackwardsProcess=true;
//            }
//        }
    }
}
void ClusterRTree::completeConnectionsOfLevel(std::vector<ClusterRTree*> &nextLevel,std::vector<ClusterRTree*> &leavesInUpperLevels)
{
    if(nextLevel.size()>0)
    {
        std::vector<Node*> nodesInLowerLevel;
        std::vector<ClusterRTree*> nextLevelTemp;
//        for(long i=0;i<leavesInUpperLevels.size();i++){
//            for(long j=0;j<leavesInUpperLevels[i]->graph->nodes.size();j++){
//                nodesInLowerLevel.push_back(&leavesInUpperLevels[i]->graph->nodes[j]);
//            }
//        }
        for(long i=0; i<nextLevel.size(); i++)
        {
            for(long j=0; j<nextLevel[i]->graph->nodes.size(); j++)
            {
                nodesInLowerLevel.push_back(&nextLevel[i]->graph->nodes[j]);
            }
            for(int j=0; j<nextLevel[i]->sons.size(); j++)
            {
                nextLevelTemp.push_back(&(nextLevel[i]->sons[j]));
            }
            if(nextLevel[i]->sons.size()==0)
            {
                leavesInUpperLevels.push_back(nextLevel[i]);
            }

        }

        for(long i=0; i<nodesInLowerLevel.size(); i++)
        {
            for(long j=0; j<nodesInLowerLevel.size(); j++)
            {
                ClusterRTree* clusterA=getClusterOfNode(nodesInLowerLevel[i]);
                ClusterRTree* clusterB=getClusterOfNode(nodesInLowerLevel[j]);
                if(clusterA!=clusterB)
                {
                    double distance=INFINITY;
                    for(int h=0; h<clusterB->frontierNodes.size(); h++)
                    {
//                        double distance1=getDistance(nodesInLowerLevel[i]->nodeInOriginalGraph->id, clusterB->frontierNodes[h]->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                        double distance1=mainCluster->matrixDistances->get(nodesInLowerLevel[i]->nodeInOriginalGraph->id, clusterB->frontierNodes[h]->nodeInOriginalGraph->id);
//                        double distance2=getDistance(nodesInLowerLevel[j]->nodeInOriginalGraph->id, clusterB->frontierNodes[h]->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                        double distance2=mainCluster->matrixDistances->get(nodesInLowerLevel[j]->nodeInOriginalGraph->id, clusterB->frontierNodes[h]->nodeInOriginalGraph->id);
                        if(distance1==-1)
                        {
                            distance1=calculateDistance(nodesInLowerLevel[i], clusterB->frontierNodes[h]->nodeRepresentedBy );
                            //                            distance1=findDistanceRecursive(nodesInLowerLevel[i], clusterB->frontierNodes[h]->nodeRepresentedBy);
                        }
                        if(distance2==-1)
                        {
                            distance2=calculateDistance(nodesInLowerLevel[j], clusterB->frontierNodes[h]->nodeRepresentedBy);
                            //distance2=findDistanceRecursive(nodesInLowerLevel[j], clusterB->frontierNodes[h]->nodeRepresentedBy);
                        }
                        if(distance1+distance2<distance)
                        {
                            distance=distance1+distance2;
                        }
                    }
                    double distanceTemp=mainCluster->matrixDistances->get(nodesInLowerLevel[i]->nodeInOriginalGraph->id, nodesInLowerLevel[j]->nodeInOriginalGraph->id);
                    if(distanceTemp==-1||distance<distanceTemp)
                    {
                        if(distance>mainCluster->originalGraph->diameters[mainCluster->originalGraph->indexOfMainDistanceInOtherDistances])
                        {
                            mainCluster->originalGraph->diameters[mainCluster->originalGraph->indexOfMainDistanceInOtherDistances]=distance;
                        }
//                        insertDistance(distance, nodesInLowerLevel[i]->nodeInOriginalGraph->id, nodesInLowerLevel[j]->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                        insertDistance(distance, nodesInLowerLevel[j]->nodeInOriginalGraph->id, nodesInLowerLevel[i]->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                        mainCluster->matrixDistances->set(distance, nodesInLowerLevel[i]->nodeInOriginalGraph->id, nodesInLowerLevel[j]->nodeInOriginalGraph->id);
                        if(!mainCluster->matrixDistances->bidirectional)
                        {
                            mainCluster->matrixDistances->set(distance, nodesInLowerLevel[j]->nodeInOriginalGraph->id, nodesInLowerLevel[i]->nodeInOriginalGraph->id);
                        }
                    }
                }
            }
        }
        nextLevel.clear();
        completeConnectionsOfLevel(nextLevelTemp, leavesInUpperLevels);
    }
    else
    {

    }
//    for(long i=0;i<mainCluster->matrixDistances->size();i++){
//        if(mainCluster->matrixDistances->operator[](i)>mainCluster->originalGraph->diameterWeighted){
//            mainCluster->originalGraph->diameterWeighted=mainCluster->matrixDistances->operator[](i);
//        }
//    }
}

double ClusterRTree::findDistanceRecursive(Node* a, Node* b)
{
    double distanceTemp=mainCluster->matrixDistances->get(a->nodeInOriginalGraph->id, b->nodeInOriginalGraph->id);
    if(distanceTemp!=-1)
    {
        return distanceTemp;
    }
    else
    {
        std::vector<double> possibleDistances;
        ClusterRTree* clusterA=getClusterOfNode(a);
        ClusterRTree* clusterB=getClusterOfNode(b);
        while(a->nodeThatRepresents->isFrontier)
        {
            clusterA=clusterA->parent;
            a=(clusterA->graphTemp->nodes[a->nodeThatRepresents->idEquivalentUpperVerticalNode]).nodeRepresentedBy;
        }
        while(b->nodeThatRepresents->isFrontier)
        {
            clusterB=clusterB->parent;
            b=(clusterB->graphTemp->nodes[b->nodeThatRepresents->idEquivalentUpperVerticalNode]).nodeRepresentedBy;
        }
        for(long i=0; i<clusterA->frontierNodes.size(); i++)
        {
            for(long j=0; j<clusterB->frontierNodes.size(); j++)
            {
                double distance3;
//                double distance1=findDistanceRecursive(a, clusterA->frontierNodes[i]->nodeRepresentedBy);
//                double distance2=findDistanceRecursive(b, clusterB->frontierNodes[j]->nodeRepresentedBy);
//                double distance1=getDistance(a->nodeInOriginalGraph->id, clusterA->frontierNodes[i]->nodeRepresentedBy->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                double distance1=mainCluster->matrixDistances->get(a->nodeInOriginalGraph->id, clusterA->frontierNodes[i]->nodeRepresentedBy->nodeInOriginalGraph->id);
//                double distance2=getDistance(b->nodeInOriginalGraph->id, clusterB->frontierNodes[j]->nodeRepresentedBy->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                double distance2=mainCluster->matrixDistances->get(b->nodeInOriginalGraph->id, clusterB->frontierNodes[j]->nodeRepresentedBy->nodeInOriginalGraph->id);
                double hDis=sqrt((b->location.x-a->location.x)*(b->location.x-a->location.x)+(b->location.y-a->location.y)*(b->location.y-a->location.y));
                double hDis1=sqrt((clusterB->frontierNodes[j]->location.x-clusterA->frontierNodes[i]->location.x)*(clusterB->frontierNodes[j]->location.x-clusterA->frontierNodes[i]->location.x)+(clusterB->frontierNodes[j]->location.y-clusterA->frontierNodes[i]->location.y)*(clusterB->frontierNodes[j]->location.y-clusterA->frontierNodes[i]->location.y));
//                double heuristicDistanceToGoal=hDis*(1+log(hDis)*multiplierHeuristic)+summerHeuristic;
                if(distance1+distance2+hDis1<hDis*1.15||possibleDistances.size()<1)
                {
                    distance3=findDistanceRecursive(clusterB->frontierNodes[j]->nodeRepresentedBy, clusterA->frontierNodes[i]->nodeRepresentedBy);

                    possibleDistances.push_back(distance1+distance2+distance3);
                }
            }
        }
        double distance=INFINITY;
        for(long i=0; i<possibleDistances.size(); i++)
        {
            if(possibleDistances[i]<distance)
            {
                distance=possibleDistances[i];
            }
        }
        if(distance>mainCluster->originalGraph->diameters[mainCluster->originalGraph->indexOfMainDistanceInOtherDistances])
        {
            mainCluster->originalGraph->diameters[mainCluster->originalGraph->indexOfMainDistanceInOtherDistances]=distance;
        }
        return distance;
    }
}
double ClusterRTree::calculateDistance(Node* a,Node* b)
{
    bool errorPrinted=false;
    double distanceTemp=mainCluster->matrixDistances->get(a->nodeInOriginalGraph->id, b->nodeInOriginalGraph->id);
    ClusterRTree* cluster=getCommonLevelOfTwoNodes(a,b);
    if(distanceTemp!=-1)
    {
//            if(getCommonLevelOfTwoNodes())
        return distanceTemp;
    }
    else
    {

        double distance=INFINITY;
        for(long i=0; i<cluster->graph->nodes.size(); i++)
        {
            Node* c=&(cluster->graph->nodes[i]);
//            double distance1=getDistance(a->nodeInOriginalGraph->id, c->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
            double distance1=mainCluster->matrixDistances->get(a->nodeInOriginalGraph->id, c->nodeInOriginalGraph->id);
            if(distance1==-1)
            {
                calculateDistanceNodeInLeaveCluster(a);
                distance1=mainCluster->matrixDistances->get(a->nodeInOriginalGraph->id, c->nodeInOriginalGraph->id);
            }
//            double distance2=getDistance(b->nodeInOriginalGraph->id, c->nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
            double distance2=mainCluster->matrixDistances->get(b->nodeInOriginalGraph->id, c->nodeInOriginalGraph->id);
            if(distance2==-1)
            {
                calculateDistanceNodeInLeaveCluster(b);
                distance2=mainCluster->matrixDistances->get(b->nodeInOriginalGraph->id, c->nodeInOriginalGraph->id);
            }

            if(distance1!=-1&&distance2!=-1)
            {
                if(distance>distance2+distance1)
                {
                    distance=distance1+distance2;
                }
//                std::cout<<"ok"<<'\n';
            }
            else if(!errorPrinted)
            {
//                std::cout<<"error"<<'\n';
                errorPrinted=true;
            }

        }
        return distance;
    }
}
void ClusterRTree::setClustersToCalculateDistances(std::vector<Transition> &originDestinationPairs)
{

//    for(long i=0;i<originDestinationPairs;i++){
//
//
//        ClusterRTree* clusterA=getDeepestClusterOfNode(originDestinationPairs[i]->a);
//        ClusterRTree* clusterB=getDeepestClusterOfNode(originDestinationPairs[i]->b);
//        ClusterRTree* clusterCommon=getCommonLevelOfTwoNodes(originDestinationPairs[i]->a,originDestinationPairs[i]->b);
//        while(clusterA->parent!=NULL&&clusterA.depth>clusterCommon->depth){
//            clusterA->inCalculateDistances=true;
//            clusterA=clusterA->parent;
//        }
//        clusterA->inCalculateDistances=true;
//        while(clusterB->parent!=NULL&&clusterA.depth>clusterCommon->depth){
//            clusterB->inCalculateDistances=true;
//            clusterB=clusterB->parent;
//        }
//        clusterB->inCalculateDistances=true;
//
//    }
}
void ClusterRTree::setClustersToConstructBackwards(std::vector<Transition> &originDestinationPairs)
{
    if(originDestinationPairs.size()>0){
    for(long i=0; i<originDestinationPairs.size(); i++)
    {


        ClusterRTree* clusterA=getDeepestClusterOfNode(originDestinationPairs[i].a);
        ClusterRTree* clusterB=getDeepestClusterOfNode(originDestinationPairs[i].b);
        ClusterRTree* clusterCommon=getCommonLevelOfTwoNodes(originDestinationPairs[i].a,originDestinationPairs[i].b);
        while(clusterA->parent!=NULL)
        {
            clusterA->inConstruction=true;
            if(clusterA->depth>=clusterCommon->depth)
            {
                clusterA->inCalculateDistances=true;
            }
            clusterA=clusterA->parent;

        }
        clusterA->inConstruction=true;
        if(clusterA->depth>=clusterCommon->depth)
        {
            clusterA->inCalculateDistances=true;
        }
        while(clusterB->parent!=NULL)
        {
            clusterB->inConstruction=true;
            if(clusterB->depth>=clusterCommon->depth)
            {
                clusterB->inCalculateDistances=true;
            }
            clusterB=clusterB->parent;

        }
        clusterB->inConstruction=true;
        if(clusterB->depth>=clusterCommon->depth)
        {
            clusterB->inCalculateDistances=true;
        }

    }
    }else{
        std::vector<ClusterRTree*> clusters=mainCluster->clustersByDepth.heap;
        for(long i=0;i<clusters.size();i++){
            clusters[i]->inCalculateDistances=true;
            clusters[i]->inConstruction=true;
        }
    }
}

void ClusterRTree::calculateDistanceNodeInLeaveCluster(Node* a)
{
//    for(long i=0;i<graph->nodes.size();i++){
    ClusterRTree* cluster=getDeepestClusterOfNode(a);
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    Node* nodeTemp=a;
    nodeTemp->minDistance=0;
    nodesCutoff.push_back(nodeTemp);
    nodesToCheckDijkstra.push(nodeTemp);

    cluster->graph->calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra);

//                ClusterRTree* clusterA=getSonThatCorrespondToNode(nodeTemp);

    for(long j=0; j<cluster->graph->nodes.size(); j++)
    {



        double distance1=cluster->graph->nodes[j].minDistance;

//                    insertDistance(distance1, graph->nodes[i].nodeInOriginalGraph->id, graph->nodes[j].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                    insertDistance(distance1, graph->nodes[j].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
        mainCluster->matrixDistances->set(distance1, a->nodeInOriginalGraph->id, cluster->graph->nodes[j].nodeInOriginalGraph->id);
        if(!mainCluster->matrixDistances->bidirectional)
        {
            mainCluster->matrixDistances->set(distance1, cluster->graph->nodes[j].nodeInOriginalGraph->id, a->nodeInOriginalGraph->id);
        }
        ClusterRTree* clusterTemp=cluster;
        if(cluster->graph->nodes[j].nodeThatRepresents->isFrontier&&!a->nodeThatRepresents->isFrontier)
        {

            while(clusterTemp->parent!=NULL&&clusterTemp->inCalculateDistances)
            {
                for(int h=0; h<clusterTemp->parent->graph->nodes.size(); h++)
                {
                    Node* nodeTemp=&clusterTemp->parent->graph->nodes[h];
                    ClusterRTree* clusterOfSonOfFrontier=getSonThatCorrespondToNode(nodeTemp);
                    if(clusterOfSonOfFrontier!=this)
                    {
//                                    double distance=distance1+getDistance(graph->nodes[j].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                        double distance=distance1+mainCluster->matrixDistances->get(cluster->graph->nodes[j].nodeInOriginalGraph->id, clusterTemp->parent->graph->nodes[h].nodeInOriginalGraph->id);
                        double distanceTemp=mainCluster->matrixDistances->get(a->nodeInOriginalGraph->id, clusterTemp->parent->graph->nodes[h].nodeInOriginalGraph->id);

                        if(distanceTemp==-1||distance<distanceTemp)
                        {
//                                        insertDistance(distance, graph->nodes[i].nodeInOriginalGraph->id, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
//                                        insertDistance(distance, cluster->parent->graph->nodes[h].nodeInOriginalGraph->id, graph->nodes[i].nodeInOriginalGraph->id, mainCluster->originalGraph->nodes.size());
                            mainCluster->matrixDistances->set(distance, a->nodeInOriginalGraph->id, clusterTemp->parent->graph->nodes[h].nodeInOriginalGraph->id);
                            if(!mainCluster->matrixDistances->bidirectional)
                            {
                                mainCluster->matrixDistances->set(distance, clusterTemp->parent->graph->nodes[h].nodeInOriginalGraph->id, a->nodeInOriginalGraph->id);
                            }
                            //                                        if(distance>mainCluster->originalGraph->diameterWeighted){
                            //                                            mainCluster->originalGraph->diameterWeighted=distance;
                            //                                        }
                        }
                    }
                    else
                    {
                        //std::cout<<'\n';
                    }
                }

                clusterTemp=clusterTemp->parent;
            }

        }





    }
    distancesCalculated=true;
    for(long h=0; h<nodesCutoff.size(); h++)
    {

        nodesCutoff[h]->minDistance=INFINITY;
        nodesCutoff[h]->inDijkstra=false;
        nodesCutoff[h]->inCutoff=false;
        nodesCutoff[h]->numOtherChildren.clear();
        nodesCutoff[h]->parent=NULL;

    }

    nodesCutoff.clear();

    nodesToCheckDijkstra.clear();

//            }
//        }
}

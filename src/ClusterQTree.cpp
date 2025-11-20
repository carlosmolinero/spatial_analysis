#include "ClusterQTree.h"

ClusterQTree::ClusterQTree()
{
    //ctor
    maxNumberNodes=10000;
    depth=0;
    numVertDivisions=4;
    numHorDivisions=4;
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

ClusterQTree::~ClusterQTree()
{
    //dtor
//    for(int i=0;i<nodesInCluster.size();i++){
//        delete nodesInCluster[i];
//    }
//    for(int i=0;i<frontierNodes.size();i++){
//        delete frontierNodes[i];
//    }

}
//void ClusterQTree::insertDistance(double value,long col,long row,long module){
//    long index=row*module+col;
////    mainCluster->matrixDistances->operator[](index)=value;
//}
//double ClusterQTree::getDistance (long col,long row,long module){
//    long index=row*module+col;
////    return mainCluster->matrixDistances->operator[](index);
//    return 1;
//}
bool ClusterQTree::compareByDepth(ClusterQTree* &a, ClusterQTree* &b)
{
    return (a->depth<b->depth);
}
void ClusterQTree::addNode(Node* &node)
{
    if (isLeave)
    {
        if (nodesInCluster.size()<maxNumberNodes)
        {
            node->depthInQTree=depth;
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
void ClusterQTree::addExternalNode(Node* &node)
{
//    std::cout<<"clusterQTree->addExternalNode original id of node "<<node->originalID<<'\n';
    if(southIsExternal||northIsExternal||eastIsExternal||westIsExternal){
//        std::cout<<"is external "<<'\n';
        if (isLeave)
        {
//            std::cout<<"is leaf "<<'\n';
            if (nodesInCluster.size()<maxNumberNodes)
            {
//                std::cout<<"is less than the allowed bucket size "<<'\n';
                node->depthInQTree=depth;
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
ClusterQTree* ClusterQTree::getSonThatCorrespondToNode(Node* &node)
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

ClusterQTree* ClusterQTree::getCommonLevelOfTwoNodes(Node* a,Node* b)
{
    ClusterQTree* current=(mainCluster);

    ClusterQTree* clA=current->getSonThatCorrespondToNode(a);
    ClusterQTree* clB=current->getSonThatCorrespondToNode(b);
    while(clA!=NULL&&clB!=NULL&&clA==clB)
    {
        current=clA;

        clA=current->getSonThatCorrespondToNode(a);
        clB=current->getSonThatCorrespondToNode(b);
    }
    return current;
}
//long ClusterQTree::getHighestLevelOfNode(Node* a){
//    ClusterQTree* cluster=getClusterOfNode(a);
//    while(a->idEquivalentUpperVerticalNode!=-1){
//        a=&(cluster->parent->graphTemp->nodes[a->idEquivalentUpperVerticalNode]);
//        cluster=cluster->parent;
//    }
//    return a->depthInQTree;
//
//}
//ClusterQTree* ClusterQTree::getCommonUpperLevelOfTwoNodes(Node* a,Node* b){
//    ClusterQTree* current=(mainCluster);
//    long commonDepth=max(getHighestLevelOfNode(a),getHighestLevelOfNode(b));
//    if(commonDepth>0){
//        ClusterQTree* clA=current->getSonThatCorrespondToNode(a);
//        ClusterQTree* clB=current->getSonThatCorrespondToNode(b);
//        while(clA!=NULL&&clB!=NULL&&clA==clB&&commonDepth>=current->depth){
//            current=clA;
//
//            clA=current->getSonThatCorrespondToNode(a);
//            clB=current->getSonThatCorrespondToNode(b);
//        }
//    }
//    return current;
//}
ClusterQTree* ClusterQTree::getClusterOfNode(Node* a)
{
    ClusterQTree* current=(mainCluster);
    while (current->depth<a->depthInQTree)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
ClusterQTree* ClusterQTree::getDeepestClusterOfNode(Node* a)
{
    ClusterQTree* current=(mainCluster);
    while (!current->isLeave)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
//Node* ClusterQTree::getHighestRepresentativeOfNode(Node* a){
//    Node* node=a;
//    if (a->upperRepresentative==NULL){
//        ClusterQTree* cluster=getClusterOfNode(a);
//        while(node->idEquivalentUpperVerticalNode!=-1){
//            node=&(cluster->parent->graphTemp->nodes[node->idEquivalentUpperVerticalNode]);
//            cluster=cluster->parent;
//        }
//        a->upperLevel=node->depthInQTree;
//        a->upperRepresentative=node;
//        return node;
//    }else{
//        return a->upperRepresentative;
//    }
//
//}
//Node* ClusterQTree::getLowestRepresentativeOfNode(Node* a){
//    Node* node=a;
//    if (a->lowerRepresentative==NULL){
//        ClusterQTree* cluster=getClusterOfNode(a);
//        while(node->idEquivalentLowerVerticalNode!=-1){
//            node=&(cluster->parent->graphTemp->nodes[node->idEquivalentUpperVerticalNode]);
//            cluster=cluster->parent;
//        }
//        a->upperLevel=node->depthInQTree;
//        a->upperRepresentative=node;
//        return node;
//    }else{
//        return a->upperRepresentative;
//    }
//
//}
void ClusterQTree::divide()
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
        ClusterQTree cluster;
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
        ClusterQTree* clusterTemp=&sons[i];
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
            ClusterQTree* clusterTemp=&sons[i];
            mainCluster->externalClustersByDepth.push(clusterTemp, &ClusterQTree::compareByDepth);

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


void ClusterQTree::fixExternalTransitions(ClusterQTree* cluster)
{
//    for(int i=0;i<clusters.size();i++){

    for(int j=0; j<cluster->externalTransitions.size(); j++)
    {
        cluster->externalTransitions[j].a=cluster->externalTransitions[j].a->nodeRepresentedBy;
        cluster->externalTransitions[j].b=cluster->externalTransitions[j].b->nodeRepresentedBy;
    }
//    }
}




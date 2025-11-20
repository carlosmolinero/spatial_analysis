#include "QTree.h"

QTree::QTree(int mode)
{
    this->mode=mode;


    //ctor

}
QTree::QTree()
{
  
    
}

QTree::~QTree()
{
    //dtor
//    matrixDistances.values.clear();
//std::vector<BST<float>>().swap(matrixDistances.values);
}
//void QTree::insertDistance(double value,long col,long row,long module){
//    long index=row*module+col;
////    matrixDistances[index]=value;
//}
//double QTree::getDistance (long col,long row,long module){
//    long index=row*module+col;
////    return matrixDistances[index];
//    return 1;
//}
void QTree::generateCornersOfMainCluster(double minX,double maxX,double minY,double maxY)
{
//    double INF=std::numeric_limits<double>::infinity();
//    double maxX=-INF;
//    double maxY=-INF;
//    double minX=INF;
//    double minY=INF;
//    for(int i=0; i<mainGraph->nodes.size(); i++)
//    {
//        if (mainGraph->nodes[i].location.x>=maxX)
//        {
//            maxX=mainGraph->nodes[i].location.x+1;
//        }
//        if (mainGraph->nodes[i].location.y>=maxY)
//        {
//            maxY=mainGraph->nodes[i].location.y+1;
//        }
//        if (mainGraph->nodes[i].location.x<=minX)
//        {
//            minX=mainGraph->nodes[i].location.x-1;
//        }
//        if (mainGraph->nodes[i].location.y<=minY)
//        {
//            minY=mainGraph->nodes[i].location.y-1;
//        }
//    }
    mainCluster.corners[0]=Point2d(minX,minY);
    mainCluster.corners[1]=Point2d(maxX,maxY);
    mainCluster.widthClusterSons=(maxX-minX)/mainCluster.numHorDivisions;
    mainCluster.heightClusterSons=(maxY-minY)/mainCluster.numHorDivisions;
    mainCluster.mainCluster=&mainCluster;
    mainCluster.id=0;
    mainCluster.idClusters=1;
    mainCluster.leavesById.add(0,&mainCluster);
//    mainCluster.originalGraph=mainGraph;
    mainCluster.clustersByDepth.push(mainCluster.mainCluster,&ClusterQTree::compareByDepth);
    mainCluster.externalCluster=&externalCluster;

    mainCluster.northIsExternal=true;
    mainCluster.eastIsExternal=true;
    mainCluster.westIsExternal=true;
    mainCluster.southIsExternal=true;

    mainCluster.externalLeavesById.add(0,&mainCluster);
    mainCluster.externalClustersByDepth.push(mainCluster.mainCluster, &ClusterQTree::compareByDepth);
    
    
    TransitionCluster transN;
    transN.a=&mainCluster;
    transN.b=&externalCluster;
    mainCluster.transitionsNorth.push_back(transN);
    TransitionCluster transNB;
    transNB.b=&mainCluster;
    transNB.a=&externalCluster;
    externalCluster.transitionsNorth.push_back(transNB);
    
    
    TransitionCluster transS;
    transS.a=&mainCluster;
    transS.b=&externalCluster;
    mainCluster.transitionsSouth.push_back(transS);
    TransitionCluster transE;
    transE.a=&mainCluster;
    transE.b=&externalCluster;
    mainCluster.transitionsEast.push_back(transE);
    TransitionCluster transW;
    transW.a=&mainCluster;
    transW.b=&externalCluster;
    mainCluster.transitionsWest.push_back(transW);
    
    
    
    
    
    
    
    
    
    
//    matrixDistances.values.resize(mainGraph.nodes.size(),BST<float>());
//    matrixDistances.resize(mainGraph.nodes.size()*mainGraph.nodes.size(), -1);
//    for(int i=0;i<mainGraph.nodes.size();i++){
//        insertDistance(0, i, i, mainGraph.nodes.size());
//    }

//    matrixDistances.init(mainGraph->nodes.size(),mainGraph->nodes.size());
//    mainCluster.matrixDistances=&matrixDistances;

//    TransitionCluster trans;
//    trans.ca=&mainCluster;
//    trans.cb=&externalCluster;
////    trans.weight=1;
//    trans.id=0;
//    trans.oppositeTransitionId=4;
//    trans.ca->transitionsNorth.push_back(trans);
//    trans.ca->transitionsById.add(trans.id,&trans);
//
////    externalCluster.transitionsById.add(trans.id,&trans);
//
//    TransitionCluster trans2;
//    trans2.ca=&mainCluster;
//    trans2.cb=&externalCluster;
////    trans2.weight=1;
//    trans2.id=1;
//    trans2.oppositeTransitionId=5;
//    trans2.ca->transitionsWest.push_back(trans2);
//
//    mainCluster.transitionsById.add(trans2.id,&trans2);
////    externalCluster.transitionsById.add(trans2.id,&trans2);
//
//    TransitionCluster trans3;
//    trans3.ca=&mainCluster;
//    trans3.cb=&externalCluster;
////    trans3.weight=1;
//    trans3.id=2;
//    trans3.oppositeTransitionId=6;
//    trans3.ca->transitionsEast.push_back(trans3);
//
//    mainCluster.transitionsById.add(trans3.id,&trans3);
////    externalCluster.transitionsById.add(trans3.id,&trans3);
//
//    TransitionCluster trans4;
//    trans4.ca=&mainCluster;
//    trans4.cb=&externalCluster;
////    trans4.weight=1;
//    trans4.id=3;
//    trans4.oppositeTransitionId=7;
//    trans4.ca->transitionsSouth.push_back(trans4);
//
//    mainCluster.transitionsById.add(trans4.id,&trans4);
////    externalCluster.transitionsById.add(trans4.id,&trans4);
//
//    TransitionCluster trans5;
//    trans5.cb=&mainCluster;
//    trans5.ca=&externalCluster;
////    trans5.weight=1;
//    trans5.id=4;
//    trans5.oppositeTransitionId=0;
//    trans5.ca->transitionsNorth.push_back(trans5);
//
////    trans.ca->transitionsById.add(trans.id,&trans);
//    externalCluster.transitionsById.add(trans5.id,&trans5);
//
//    TransitionCluster trans6;
//    trans6.cb=&mainCluster;
//    trans6.ca=&externalCluster;
////    trans6.weight=1;
//    trans6.id=5;
//    trans6.oppositeTransitionId=1;
//    trans6.ca->transitionsWest.push_back(trans6);
////    mainCluster.transitionsById.add(trans2.id,&trans2);
//    externalCluster.transitionsById.add(trans6.id,&trans6);
//
//    TransitionCluster trans7;
//    trans7.cb=&mainCluster;
//    trans7.ca=&externalCluster;
////    trans7.weight=1;
//    trans7.id=6;
//    trans7.oppositeTransitionId=2;
//    trans7.ca->transitionsEast.push_back(trans7);
////    mainCluster.transitionsById.add(trans3.id,&trans3);
//    externalCluster.transitionsById.add(trans7.id,&trans7);
//
//    TransitionCluster trans8;
//    trans8.cb=&mainCluster;
//    trans8.ca=&externalCluster;
////    trans8.weight=1;
//    trans8.id=7;
//    trans8.oppositeTransitionId=3;
//    trans8.ca->transitionsSouth.push_back(trans8);
////    mainCluster.transitionsById.add(trans4.id,&trans4);
//    externalCluster.transitionsById.add(trans8.id,&trans8);
//
//    mainCluster.idTransitions=8;




}


ClusterQTree* QTree::getCommonParent(ClusterQTree* a,ClusterQTree* b)
{

    while (a!=b)
    {
        if(a->depth==b->depth)
        {
            a=a->parent;
            b=b->parent;
        }
        else if(a->depth>b->depth)
        {
            a=a->parent;
        }
        else
        {
            b=b->parent;
        }
    }
    return a;
}
ClusterQTree* QTree::getDeepestClusterOfNode(Node* a)
{
    ClusterQTree* current=&(mainCluster);
    while (!current->isLeave)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
ClusterQTree* QTree::getClusterOfNode(Node* a)
{
    ClusterQTree* current=&(mainCluster);
    while (current->depth<a->depthInQTree)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
//void QTree::insertGraph(Graph* graph){
//    double maxX=-INFINITY;
//    double minX=INFINITY;
//    double maxY=-INFINITY;
//    double minY=INFINITY;
//    for(long i=0;i<graph->nodes.size();i++){
//       
//        if (graph->nodes[i].location.x>=maxX)
//        {
//            maxX=graph->nodes[i].location.x+1;
//        }
//        if (graph->nodes[i].location.y>=maxY)
//        {
//            maxY=graph->nodes[i].location.y+1;
//        }
//        if (graph->nodes[i].location.x<=minX)
//        {
//            minX=graph->nodes[i].location.x-1;
//        }
//        if (graph->nodes[i].location.y<=minY)
//        {
//            minY=graph->nodes[i].location.y-1;
//        }
//    }
//    generateCornersOfMainCluster(minX,maxX,minY,maxY);
//    
//   
//    for(long i=0;i<graph->nodes.size();i++){
//        Node* node=&graph->nodes[i];
//        mainCluster.addNode(node);
//    }
//}

ClusterQTree* QTree::getCommonLevelOfTwoNodes(Node* a,Node* b)
{
    ClusterQTree* current=&(mainCluster);

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
//ClusterQTree* QTree::getCommonUpperLevelOfTwoNodes(Node* a,Node* b)
//{
//    ClusterQTree* current=(mainCluster.mainCluster);
//    long commonDepth=max(getHighestLevelOfNode(a),getHighestLevelOfNode(b));
//    if(commonDepth>0)
//    {
//        ClusterQTree* clA=current->getSonThatCorrespondToNode(a);
//        ClusterQTree* clB=current->getSonThatCorrespondToNode(b);
//        while(clA!=NULL&&clB!=NULL&&clA==clB&&commonDepth>current->depth)
//        {
//            current=clA;
//
//            clA=current->getSonThatCorrespondToNode(a);
//            clB=current->getSonThatCorrespondToNode(b);
//        }
//    }
//    return current;
//}

std::vector<Transition> QTree::getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(double minX,double maxX,double minY,double maxY,std::vector<Node*> &nodesOfGraph)
{
    //    double INF=std::numeric_limits<double>::infinity();
    //    double maxX=-INF;
    //    double maxY=-INF;
    //    double minX=INF;
    //    double minY=INF;
    //    for(int i=0; i<mainGraph->nodes.size(); i++)
    //    {
    //        if (mainGraph->nodes[i].location.x>=maxX)
    //        {
    //            maxX=mainGraph->nodes[i].location.x+1;
    //        }
    //        if (mainGraph->nodes[i].location.y>=maxY)
    //        {
    //            maxY=mainGraph->nodes[i].location.y+1;
    //        }
    //        if (mainGraph->nodes[i].location.x<=minX)
    //        {
    //            minX=mainGraph->nodes[i].location.x-1;
    //        }
    //        if (mainGraph->nodes[i].location.y<=minY)
    //        {
    //            minY=mainGraph->nodes[i].location.y-1;
    //        }
    //    }
    std::vector<Transition> originDestinationPairs;
//                    originDestinationPairs.clear();
//                    QTree.mainCluster.
    
    
    
    generateCornersOfMainCluster(minX,maxX,minY,maxY);
//                    std::cout<<"QTree created"<<'\n';
    for(int i=0; i<nodesOfGraph.size(); i++)
    {
        Node* node=(nodesOfGraph[i]);
        mainCluster.addExternalNode(node);
    }
//                    std::cout<<"nodes added"<<'\n';




//                    std::vector<Transition> originDestinationPairs;
//
    //                    long numberTimes=mainGraph.nodes.size()/25;
    std::vector<ClusterQTree*> clustersExternalLeaves=mainCluster.externalLeavesById.getAll();
    
//    std::cout<<"clustersExternalLeaves size:"<<clustersExternalLeaves.size()<<'\n';

    for(long i=0; i<clustersExternalLeaves.size(); i++)
    {
        for(long j=0; j<clustersExternalLeaves.size(); j++)
        {
//            std::cout<<'\n';
//            
//            std::cout<<"clustersExternalLeaves[i]->nodesInCluster.size() "<<clustersExternalLeaves[i]->nodesInCluster.size()<<'\n';
//                        std::cout<<"clustersExternalLeaves[j]->nodesInCluster.size() "<<clustersExternalLeaves[j]->nodesInCluster.size()<<'\n';
            if(i!=j&&clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
            {
                Transition trans;
                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                originDestinationPairs.push_back(trans);
            }

        }
    }
    return originDestinationPairs;
}

std::vector<ClusterQTree*> QTree::getClustersInARange(double minX,double minY,double maxX,double maxY){
    ClusterQTree* current=&(mainCluster);
    std::vector<ClusterQTree*> possibles;
    std::vector<ClusterQTree*> finals;
    possibles.push_back(current);
    while(possibles.size()>0){
        current=possibles.back();
        possibles.pop_back();
        if (current->sons.size()>0)
        {
            for(int i=0;i<current->sons.size();i++){
//                bool xIn=false;
//                bool yIn=false;
                bool contained=false;
                
//                if(current->sons[i].corners[0].x>minX&&current->sons[i].corners[0].x<maxX){
//                    xIn=true;
//                }
//                if(current->sons[i].corners[0].y>minY&&current->sons[i].corners[0].y<maxY){
//                    yIn=true;
//                }
//                
//                
//                if(xIn&&yIn){
//                    contained=true;
//                }
//                xIn=false;
//                yIn=false;
//                if(current->sons[i].corners[1].x>minX&&current->sons[i].corners[1].x<maxX){
//                    xIn=true;
//                }
//                
//                if(current->sons[i].corners[1].y>minY&&current->sons[i].corners[1].y<maxY){
//                    yIn=true;
//                }
//                if(xIn&&yIn){
//                    contained=true;
//                }
//                xIn=false;
//                yIn=false;
//                if(current->sons[i].corners[0].x<minX&&current->sons[i].corners[1].x>maxX){
//                    xIn=true;
//                }
//                
//                if(current->sons[i].corners[0].y<minY&&current->sons[i].corners[1].y>maxY){
//                    yIn=true;
//                }
//                
//                if(xIn&&yIn){
//                    contained=true;
//                }
//                xIn=false;
//                yIn=false;
//                if(current->sons[i].corners[0].x>minX&&current->sons[i].corners[1].x<maxX){
//                    xIn=true;
//                }
//                if(current->sons[i].corners[0].y>minY&&current->sons[i].corners[1].y<maxY){
//                    yIn=true;
//                }
//                if(xIn&&yIn){
//                    contained=true;
//                }
                
                
                
                if(Functions::containedOrOverlappingRectangles(current->sons[i].corners[0], current->sons[i].corners[1], Point2d(minX,minY), Point2d(maxX,maxY))){
                    contained=true;
                }
                
                
                
                
//                contained=true;|
//                bool outside1=false;
//                bool outside2=false;
//                bool outside3=false;
//                bool outside4=false;
//                Point2d corner1;
//                corner1.x=minX;
//                corner1.y=minY;
//                Point2d corner2;
//                corner2.x=minX;
//                corner2.y=maxY;
//                Point2d corner3;
//                corner3.x=maxX;
//                corner3.y=minY;
//                Point2d corner4;
//                corner4.x=maxX;
//                corner4.y=maxY;
//                if (corner1.x<current->sons[i].corners[0].x||corner1.x>current->sons[i].corners[1].x||corner1.y<current->sons[i].corners[0].y||corner1.y>current->sons[i].corners[1].y)
//                {
//                    outside1=true;
//                }
//                if (corner2.x<current->sons[i].corners[0].x||corner2.x>current->sons[i].corners[1].x||corner2.y<current->sons[i].corners[0].y||corner2.y>current->sons[i].corners[1].y)
//                {
//                    outside2=true;
//                }
//                if (corner3.x<current->sons[i].corners[0].x||corner3.x>current->sons[i].corners[1].x||corner3.y<current->sons[i].corners[0].y||corner3.y>current->sons[i].corners[1].y)
//                {
//                    outside3=true;
//                }
//                if (corner4.x<current->sons[i].corners[0].x||corner4.x>current->sons[i].corners[1].x||corner4.y<current->sons[i].corners[0].y||corner4.y>current->sons[i].corners[1].y)
//                {
//                    outside4=true;
//                }
//                bool outside=false;
//                if(outside1&&outside2&&outside3&&outside4){
//                    outside=true;
//                }
                if(contained){
                    possibles.push_back(&(current->sons[i]));
                }
//                else if (!outside){
//                    possibles.push_back(&(current->sons[i]));
//                }
                
            }
        }else{
//            bool xIn=false;
//            bool yIn=false;
            bool contained=false;
//            if(current->corners[0].x>minX&&current->corners[0].x<maxX){
//                xIn=true;
//            }
//            if(current->corners[1].x>minX&&current->corners[1].x<maxX){
//                xIn=true;
//            }
//            if(current->corners[0].y>minY&&current->corners[0].y<maxY){
//                yIn=true;
//            }
//            if(current->corners[1].y>minY&&current->corners[1].y<maxY){
//                yIn=true;
//            }
//            
//            if(xIn||yIn){
//                contained=true;
//            }
//            xIn=false;
//            yIn=false;
//            if(current->corners[0].x<minX&&current->corners[1].x>maxX){
//                xIn=true;
//            }
//            
//            if(current->corners[0].y<minY&&current->corners[1].y>maxY){
//                yIn=true;
//            }
//            
//            if(xIn&&yIn){
//                contained=true;
//            }
//            xIn=false;
//            yIn=false;
//            if(current->corners[0].x>minX&&current->corners[1].x<maxX){
//                xIn=true;
//            }
//            if(current->corners[0].y>minY&&current->corners[1].y<maxY){
//                yIn=true;
//            }
//            if(xIn&&yIn){
//                contained=true;
//            }
            
            
            
            if(Functions::containedOrOverlappingRectangles(current->corners[0], current->corners[1], Point2d(minX,minY), Point2d(maxX,maxY))){
                contained=true;
            }
            
            
//            contained=true;
            
//            bool outside1=false;
//            bool outside2=false;
//            bool outside3=false;
//            bool outside4=false;
//            Point2d corner1;
//            corner1.x=minX;
//            corner1.y=minY;
//            Point2d corner2;
//            corner2.x=minX;
//            corner2.y=maxY;
//            Point2d corner3;
//            corner3.x=maxX;
//            corner3.y=minY;
//            Point2d corner4;
//            corner4.x=maxX;
//            corner4.y=maxY;
//            if (corner1.x<current->corners[0].x||corner1.x>current->corners[1].x||corner1.y<current->corners[0].y||corner1.y>current->corners[1].y)
//            {
//                outside1=true;
//            }
//            if (corner2.x<current->corners[0].x||corner2.x>current->corners[1].x||corner2.y<current->corners[0].y||corner2.y>current->corners[1].y)
//            {
//                outside2=true;
//            }
//            if (corner3.x<current->corners[0].x||corner3.x>current->corners[1].x||corner3.y<current->corners[0].y||corner3.y>current->corners[1].y)
//            {
//                outside3=true;
//            }
//            if (corner4.x<current->corners[0].x||corner4.x>current->corners[1].x||corner4.y<current->corners[0].y||corner4.y>current->corners[1].y)
//            {
//                outside4=true;
//            }
//            bool outside=false;
//            if(outside1&&outside2&&outside3&&outside4){
//                outside=true;
//            }
            if(contained){
                finals.push_back(current);
            }
//            else if (!outside){
//                finals.push_back(current);
//            }
        }
    }
    return finals;
}
std::vector<Node*> QTree::getNodesOfClusters(std::vector<ClusterQTree*> clusters){
    std::vector<Node*> nodes;
    for(long i=0;i<clusters.size();i++){
        for(long j=0;j<clusters[i]->nodesInCluster.size();j++){
            nodes.push_back(clusters[i]->nodesInCluster[j]);
        }
    }
    return nodes;
}
std::vector<Node*> QTree::getNodesInARange(double minX,double minY,double maxX,double maxY){
    std::vector<ClusterQTree*> clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
//    std::cout<<"clustersInRange size "<<clustersInRange.size()<<'\n';
    std::vector<Node*> nodesInRange=getNodesOfClusters(clustersInRange);
    std::vector<Node*> nodesInRangeFinal;
    for(long i=0;i<nodesInRange.size();i++){
//        double distance=Functions::getDistance(center,nodesInRange[i]->location);
        if(nodesInRange[i]->location.x>minX&&nodesInRange[i]->location.x<maxX&&nodesInRange[i]->location.y>minY&&nodesInRange[i]->location.y<maxY){
            nodesInRangeFinal.push_back(nodesInRange[i]);
        }
    }
    return nodesInRangeFinal;
//    return nodesInRange;
}

std::vector<Node*> QTree::getNodesInARange(Point2d center,double radius){
    double minX=center.x-radius;
    double maxX=center.x+radius;
    double minY=center.y-radius;
    double maxY=center.y+radius;
    std::vector<ClusterQTree*> clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
    std::vector<Node*> nodesInRange=getNodesOfClusters(clustersInRange);
    std::vector<Node*> nodesInRangeFinal;
    for(long i=0;i<nodesInRange.size();i++){
        double distance=Functions::getDistance(center,nodesInRange[i]->location);
        if(distance<radius){
            nodesInRangeFinal.push_back(nodesInRange[i]);
        }
    }
    return nodesInRangeFinal;
}
Node* QTree::getClosestNode(Point2d point){
    Node* node=NULL;
    double radius=100;
    double increment=1000;
    double minX=point.x-radius;
    double maxX=point.x+radius;
    double minY=point.y-radius;
    double maxY=point.y+radius;
    std::vector<ClusterQTree*> clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
    std::vector<Node*> nodesInRange=getNodesOfClusters(clustersInRange);
    for(long i=0;i<nodesInRange.size();i++){
        if(nodesInRange[i]->mass==0){
            nodesInRange.erase(nodesInRange.begin()+i);
            i--;
        }
    }
    while(nodesInRange.size()==0){
        radius+=increment;
         minX=point.x-radius;
         maxX=point.x+radius;
         minY=point.y-radius;
         maxY=point.y+radius;
        clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
        nodesInRange=getNodesOfClusters(clustersInRange);
    }
    double min=INFINITY;
    for(long i=0;i<nodesInRange.size();i++){
        double distance=Functions::getDistance(point,nodesInRange[i]->location);
        if(distance<min){
            node=nodesInRange[i];
            min=distance;
        }
    }
    return node;
}
//Node* QTree::getClosestNode(Point2d point){
//    Node* node=NULL;
//    double radius=100;
//    double increment=1000;
//    double minX=point.x-radius;
//    double maxX=point.x+radius;
//    double minY=point.y-radius;
//    double maxY=point.y+radius;
//    std::vector<ClusterQTree*> clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
//    std::vector<Node*> nodesInRange=getNodesOfClusters(clustersInRange);
////    for(long i=0;i<nodesInRange.size();i++){
////        if(nodesInRange[i]->mass==0){
////            nodesInRange.erase(nodesInRange.begin()+i);
////            i--;
////        }
////    }
//    while(nodesInRange.size()==0){
//        radius+=increment;
//        minX=point.x-radius;
//        maxX=point.x+radius;
//        minY=point.y-radius;
//        maxY=point.y+radius;
//        clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
//        nodesInRange=getNodesOfClusters(clustersInRange);
//    }
//    double min=INFINITY;
//    for(long i=0;i<nodesInRange.size();i++){
//        double distance=Functions::getDistance(point,nodesInRange[i]->location);
//        if(distance<min){
//            node=nodesInRange[i];
//            min=distance;
//        }
//    }
//    return node;
//}
Node* QTree::getClosestNode(Node* nodeInit){
    Point2d point=nodeInit->location;
    Node* node=NULL;
    double radius=100;
    double increment=100;
    double minX=point.x-radius;
    double maxX=point.x+radius;
    double minY=point.y-radius;
    double maxY=point.y+radius;
    std::vector<ClusterQTree*> clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
    std::vector<Node*> nodesInRange=getNodesOfClusters(clustersInRange);
    for(long i=0;i<nodesInRange.size();i++){
        if(nodesInRange[i]->mass==0){
            nodesInRange.erase(nodesInRange.begin()+i);
            i--;
        }
    }

    while(nodesInRange.size()==0){
        radius+=increment;
        minX=point.x-radius;
        maxX=point.x+radius;
        minY=point.y-radius;
        maxY=point.y+radius;
        clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
        nodesInRange=getNodesOfClusters(clustersInRange);
    }
    double min=INFINITY;
    for(long i=0;i<nodesInRange.size();i++){
        double distance=Functions::getDistance(point,nodesInRange[i]->location);
        if(distance<min&&nodesInRange[i]!=nodeInit){
            node=nodesInRange[i];
            min=distance;
        }
    }
    return node;
}
#include "RTree.h"

RTree::RTree(int mode)
{
    this->mode=mode;


    //ctor

}
RTree::RTree()
{
  
    
}

RTree::~RTree()
{
    //dtor
//    matrixDistances.values.clear();
//std::vector<BST<float>>().swap(matrixDistances.values);
}
//void RTree::insertDistance(double value,long col,long row,long module){
//    long index=row*module+col;
////    matrixDistances[index]=value;
//}
//double RTree::getDistance (long col,long row,long module){
//    long index=row*module+col;
////    return matrixDistances[index];
//    return 1;
//}
void RTree::generateCornersOfMainCluster(Graph* mainGraph)
{
    double INF=std::numeric_limits<double>::infinity();
    double maxX=-INF;
    double maxY=-INF;
    double minX=INF;
    double minY=INF;
    for(int i=0; i<mainGraph->nodes.size(); i++)
    {
        if (mainGraph->nodes[i].location.x>=maxX)
        {
            maxX=mainGraph->nodes[i].location.x+1;
        }
        if (mainGraph->nodes[i].location.y>=maxY)
        {
            maxY=mainGraph->nodes[i].location.y+1;
        }
        if (mainGraph->nodes[i].location.x<=minX)
        {
            minX=mainGraph->nodes[i].location.x-1;
        }
        if (mainGraph->nodes[i].location.y<=minY)
        {
            minY=mainGraph->nodes[i].location.y-1;
        }
    }
    mainCluster.corners[0]=Point2d(minX,minY);
    mainCluster.corners[1]=Point2d(maxX,maxY);
    mainCluster.widthClusterSons=(maxX-minX)/mainCluster.numHorDivisions;
    mainCluster.heightClusterSons=(maxY-minY)/mainCluster.numHorDivisions;
    mainCluster.mainCluster=&mainCluster;
    mainCluster.id=0;
    mainCluster.idClusters=1;
    mainCluster.leavesById.add(0,&mainCluster);
    mainCluster.originalGraph=mainGraph;
    mainCluster.clustersByDepth.push(mainCluster.mainCluster,&ClusterRTree::compareByDepth);
    mainCluster.externalCluster=&externalCluster;

    mainCluster.northIsExternal=true;
    mainCluster.eastIsExternal=true;
    mainCluster.westIsExternal=true;
    mainCluster.southIsExternal=true;

    mainCluster.externalLeavesById.add(0,&mainCluster);
    mainCluster.externalClustersByDepth.push(mainCluster.mainCluster, &ClusterRTree::compareByDepth);
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

void RTree::generateRTreeGraph(Graph* mainGraph,std::vector<Transition> &originDestinationPairs)
{
//    mainCluster.graph
    mainCluster.generateRTreeGraph(mainGraph,originDestinationPairs,mode);
}
ClusterRTree* RTree::getCommonParent(ClusterRTree* a,ClusterRTree* b)
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
ClusterRTree* RTree::getDeepestClusterOfNode(Node* a)
{
    ClusterRTree* current=&(mainCluster);
    while (!current->isLeave)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
ClusterRTree* RTree::getClusterOfNode(Node* a)
{
    ClusterRTree* current=&(mainCluster);
    while (current->depth<a->depthInRTree)
    {
        current=(current->getSonThatCorrespondToNode(a));
    }
    return current;
}
ClusterRTree* RTree::getCommonLevelOfTwoNodes(Node* a,Node* b)
{
    ClusterRTree* current=&(mainCluster);

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
long RTree::getHighestLevelOfNode(Node* a)
{
    Node* node=a;
    if (a->upperLevel==-1)
    {
        ClusterRTree* cluster=getClusterOfNode(a);
        while(node->idEquivalentUpperVerticalNode!=-1)
        {
            node=&(cluster->parent->graphTemp->nodes[node->idEquivalentUpperVerticalNode]);
            cluster=cluster->parent;
        }
        a->upperLevel=node->depthInRTree;
        a->uppestRepresentative=node;
        return node->depthInRTree;
    }
    else
    {
        return a->upperLevel;
    }

}
Node* RTree::getHighestRepresentativeOfNode(Node* a)
{
    Node* node=a;
    if (a->uppestRepresentative==NULL)
    {
        ClusterRTree* cluster=getClusterOfNode(a);
        while(node->idEquivalentUpperVerticalNode!=-1)
        {
            node=&(cluster->parent->graphTemp->nodes[node->idEquivalentUpperVerticalNode]);
            cluster=cluster->parent;
        }
        a->upperLevel=node->depthInRTree;
        a->uppestRepresentative=node;
        return node;
    }
    else
    {
        return a->uppestRepresentative;
    }

}
ClusterRTree* RTree::getCommonUpperLevelOfTwoNodes(Node* a,Node* b)
{
    ClusterRTree* current=(mainCluster.mainCluster);
    long commonDepth=max(getHighestLevelOfNode(a),getHighestLevelOfNode(b));
    if(commonDepth>0)
    {
        ClusterRTree* clA=current->getSonThatCorrespondToNode(a);
        ClusterRTree* clB=current->getSonThatCorrespondToNode(b);
        while(clA!=NULL&&clB!=NULL&&clA==clB&&commonDepth>current->depth)
        {
            current=clA;

            clA=current->getSonThatCorrespondToNode(a);
            clB=current->getSonThatCorrespondToNode(b);
        }
    }
    return current;
}
double RTree::AStar(Node* a,Node* b,bool save)
{
    //        std::cout<<"a: "<<a->originalID<<" b: "<<b->originalID<<'\n';
    //    std::cout<<"a: "<<a<<" b: "<<b<<'\n';

    double multiplierHeuristic=0;
    double summerHeuristic=-1;
    if (a==b)
    {
        a->minDistance=0;
        b->minDistance=0;
        return 0;
    }
//    if (a.originalID==4000000003258486&&b.originalID==4000000003259313){
//        std::cout<<"aqui hay un error"<<'\n';
//    }
//std::cout<<b.originalID<<'\n';
//    ClusterRTree* commonLevelUpper=getCommonLevelOfTwoNodes(a,b);
    ClusterRTree* commonLevelUpper=getCommonUpperLevelOfTwoNodes(getHighestRepresentativeOfNode(a), getHighestRepresentativeOfNode(b));
//    if (commonLevel->depth==0){

//    }
//    if (a.id==0&&b.id==184){
//        std::cout<<"commonLevel "<<commonLevel->depth<<'\n';
//    }

//    if (&commonLevel->graph.nodes[60]==b.nodeRepresentedBy && &commonLevel->graph.nodes[140]==a.nodeRepresentedBy){
//        std::cout<<"commonLevel "<<commonLevel->depth<<'\n';
//    }
    ClusterRTree* initialCluster=getClusterOfNode(a);
//    ClusterRTree* endCluster=getDeepestClusterOfNode(b);
    ClusterRTree* currentCluster=initialCluster;
    MinHeap<Node*> visitedNodes;

//    a=a.nodeRepresentedBy;
//    b=b->nodeRepresentedBy;
    double currentPathWeight=0;
    MinHeap<Node*> bestNodes;
    Node* node=a->nodeRepresentedBy;
    node->inAStar=true;
    node->minDistance=0;
    double hDis=sqrt((b->location.x-node->location.x)*(b->location.x-node->location.x)+(b->location.y-node->location.y)*(b->location.y-node->location.y));
    double heuristicDistanceToGoal=hDis*(1+log(hDis)*multiplierHeuristic)+summerHeuristic;
    node->heuristicDistanceToGoal=heuristicDistanceToGoal;
    bestNodes.push(node, &Graph::compareByDistanceAndHeuristic);
//    visitedNodes
//    visitedNodes.push(node, &Graph::compareByDistanceAndHeuristic);

    bool reached=false;

    bool dontgoupagain=false;
//    std::cout<<"proportion heuristic distance "<<4195.0/node->heuristicDistanceToGoal<<'\n';
//    Node* bestNode=node;
    while(bestNodes.size()>0)
    {
        bool goingUp=true;

        Node* nodeTempA;

        nodeTempA=bestNodes.pop(&Graph::compareByDistanceAndHeuristic);


        if (node!=a->nodeRepresentedBy)
        {
            nodeTempA->parent=&*node;
        }
        else
        {

        }
        node=nodeTempA;


        currentCluster=getClusterOfNode(node);
        node->inAStar=false;
        if (!node->inVisitedNodes)
        {
            node->inVisitedNodes=true;
            visitedNodes.push(node,&Graph::compareByDistanceAndHeuristic);
        }
        currentPathWeight=node->minDistance;
        if (node->minDistance+node->heuristicDistanceToGoal<=b->nodeRepresentedBy->minDistance)
        {
            if(save)
            {
//                ArchivoTexto textFile;
                //            for(int h=0;h<clustersOfALevel.size();h++){
                std::stringstream nameSS;
                nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/levels/exampleGraph_currentNode"<<".txt";
                std::string name=nameSS.str();
                std::vector<std::string> values;
                values.push_back(to_string(node->originalID));
                values.push_back(to_string(node->depthInRTree));
                TextFile::writeToFile(name, values, true);
                //                                textFile.writeNCOLPlusCoordinatesFile(&(clustersOfALevel[h]->graphTemp), name);
                //        level++;
                //
            }
            //        if (node->minDistance+node->heuristicDistanceToGoal<)

            bool insertInBestNodes=false;
            commonLevelUpper=getCommonLevelOfTwoNodes(getHighestRepresentativeOfNode(node->nodeThatRepresents), getHighestRepresentativeOfNode(b));
            if (goingUp)
            {
                if ((node->depthInRTree<=commonLevelUpper->depth||node->verticalPathsTowardsUpperLevel.size()==0)||reached)
                {
                    goingUp=false;
                }
            }
//            if (currentCluster->parent!=NULL){
//                if (node->nodeThatRepresents->idEquivalentUpperVerticalNode!=-1){
//                    Node* nodeTemp=currentCluster->parent->graphTemp.nodes[node->nodeThatRepresents->idEquivalentUpperVerticalNode].nodeRepresentedBy;
//                    double possiblePathWeight=currentPathWeight+0;
//                    insertInBestNodes=false;
//                    if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance){
//                        nodeTemp->minDistance=possiblePathWeight;
//                        insertInBestNodes=true;
//                    }
//                    //                double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
//                    //                nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                    if (!nodeTemp->inDijkstra&&insertInBestNodes){
//                        //                    if (!nodeTemp->inDijkstra){
//                        double heuristicDistanceToGoal=sqrt((b.location.x-nodeTemp->location.x)*(b.location.x-nodeTemp->location.x)+(b.location.y-nodeTemp->location.y)*(b.location.y-nodeTemp->location.y));
//                        nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                        bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
//                        nodeTemp->inDijkstra=true;
//
//
//                    }else if (insertInBestNodes){
//                        bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
//                    }
//                    if (nodeTemp==b.nodeRepresentedBy){
//                        //                        reached=true;
//                    }
//
//                    if (!nodeTemp->inCutoff){
//                        nodeTemp->inCutoff=true;
//                        visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
//                    }
//                }
//            }
//            dontgoupagain=false;

            if (goingUp&&!dontgoupagain)
            {
//                currentCluster=currentCluster->parent;
                for(int i=0; i<node->verticalPathsTowardsUpperLevel.size(); i++)
                {
                    Node* nodeTemp=node->verticalPathsTowardsUpperLevel[i].b;
//                    Node* nodeTemp=(currentCluster->parent->graphTemp.nodes[node->verticalPathsTowardsUpperLevel[i].idB]).nodeRepresentedBy;
                    if (node->verticalPathsTowardsUpperLevel[i].weight==INFINITY)
                    {
//                        std::cout<<"mal hecha la transicion towards upper level"<<'\n';
                    }
                    double possiblePathWeight=currentPathWeight+0;

//                    double possiblePathWeight=currentPathWeight+node->verticalPathsTowardsUpperLevel[i].weight;
                    insertInBestNodes=false;
                    if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance)
                    {
                        nodeTemp->minDistance=possiblePathWeight;
                        insertInBestNodes=true;
                        if(nodeTemp->originalID==b->originalID)
                        {
                            reached=true;
                            b->nodeRepresentedBy->minDistance=nodeTemp->minDistance;
                            if(!b->nodeRepresentedBy->inVisitedNodes)
                            {
                                b->nodeRepresentedBy->inVisitedNodes=true;
                                visitedNodes.push(b->nodeRepresentedBy,&Graph::compareByDistanceAndHeuristic);
                            }
                        }
                    }
                    //                double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
                    //                nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                    if (!nodeTemp->inAStar&&insertInBestNodes)
                    {
                        //                    if (!nodeTemp->inDijkstra){
                        double hDis=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
                        double heuristicDistanceToGoal=hDis*(1+log(hDis)*multiplierHeuristic)+summerHeuristic;
                        nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                        bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
                        nodeTemp->inAStar=true;


                    }
                    else if (insertInBestNodes)
                    {
                        bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
                    }
                    if (nodeTemp==b->nodeRepresentedBy)
                    {
//                        reached=true;
                    }
                    if (!nodeTemp->inVisitedNodes)
                    {
                        nodeTemp->inVisitedNodes=true;
                        visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
                    }
                }
            }
            else
            {
                bool goingDown=false;
//
                Node* nodeBTemp=getHighestRepresentativeOfNode(b);
                Node* nodeTempTemp=getHighestRepresentativeOfNode(node->nodeThatRepresents);
                ClusterRTree* clusterSonA=currentCluster->getSonThatCorrespondToNode(nodeTempTemp);
                ClusterRTree* clusterSonB=currentCluster->getSonThatCorrespondToNode(nodeBTemp);
                if (clusterSonA!=NULL&&clusterSonB!=NULL&&clusterSonA==clusterSonB&&currentCluster->depth<commonLevelUpper->depth)
                {
                    goingDown=true;
                }
                if(node->heuristicDistanceToGoal==0&&node->depthInRTree<b->depthInRTree)
                {
                    goingDown=true;
                    reached=true;
                }

                if (goingDown)
                {
                    dontgoupagain=true;
                    bool goingDownVertically=true;
//                    double tolerance=0.0001;
//                    if (node->heuristicDistanceToGoal>tolerance){
                    goingDownVertically=false;
//                    }
                    if (!goingDownVertically)
                    {

                        for(int i=0; i<node->verticalPathsTowardsLowerLevel.size(); i++)
                        {
                            //                        while(clusterTemp.depth>node)
                            //                        ClusterRTree* clusterTemp=getDeepestClusterOfNode(node)
                            Node* nodeTempTemp=node->verticalPathsTowardsLowerLevel[i].b;
                            Node* nodeTemp=nodeTempTemp;
                            if (node->verticalPathsTowardsLowerLevel[i].weight==INFINITY)
                            {
                                //                                std::cout<<"mal hecha la transicion towards lower level"<<'\n';
                            }
                            double possiblePathWeight=currentPathWeight+0;

                            insertInBestNodes=false;
                            if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance)
                            {
                                nodeTemp->minDistance=possiblePathWeight;
                                insertInBestNodes=true;
                                if(nodeTemp->originalID==b->originalID)
                                {
                                    reached=true;
                                    b->nodeRepresentedBy->minDistance=nodeTemp->minDistance;
                                    if(!b->nodeRepresentedBy->inVisitedNodes)
                                    {
                                        b->nodeRepresentedBy->inVisitedNodes=true;
                                        visitedNodes.push(b->nodeRepresentedBy,&Graph::compareByDistanceAndHeuristic);
                                    }
                                }
                                //                                currentCluster=currentCluster->getSonThatCorrespondToNode(node);
                            }




                            //                    double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
                            //                    nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                            if (!nodeTemp->inAStar&&insertInBestNodes)
                            {
                                //                        if (!nodeTemp->inDijkstra){
                                double hDis=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
                                double heuristicDistanceToGoal=hDis*(1+log(hDis)*multiplierHeuristic)+summerHeuristic;
                                nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                                bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
                                nodeTemp->inAStar=true;

                            }
                            else if (insertInBestNodes)
                            {
                                bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
                            }
                            if (nodeTemp==b->nodeRepresentedBy)
                            {
                                reached=true;
                            }
                            if (!nodeTemp->inVisitedNodes)
                            {
                                nodeTemp->inVisitedNodes=true;
                                visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
                            }

//                            for(int h=0;h<nodeTempTemp->transitions.size();h++){
//                                Node* nodeTemp=nodeTempTemp->transitions[h].b;
//
//                                if (node->verticalPathsTowardsLowerLevel[i].weight==INFINITY){
//    //                                std::cout<<"mal hecha la transicion towards lower level"<<'\n';
//                                }
//                                double possiblePathWeight=currentPathWeight+0;

//                                insertInBestNodes=false;
//                                if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance){
//                                    nodeTemp->minDistance=possiblePathWeight;
//                                    insertInBestNodes=true;
//                                    if(nodeTemp->originalID==b.originalID){
//                                        reached=true;
//                                        b.nodeRepresentedBy->minDistance=nodeTemp->minDistance;
//                                        if(!b.nodeRepresentedBy->inVisitedNodes){
//                                            b.nodeRepresentedBy->inVisitedNodes=true;
//                                            visitedNodes.push(b.nodeRepresentedBy,&Graph::compareByDistanceAndHeuristic);
//                                        }
//                                    }
//    //                                currentCluster=currentCluster->getSonThatCorrespondToNode(node);
//                                }
//
//
//
//
//            //                    double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
//            //                    nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                                if (!nodeTemp->inAStar&&insertInBestNodes){
//            //                        if (!nodeTemp->inDijkstra){
//                                    double heuristicDistanceToGoal=sqrt((b.location.x-nodeTemp->location.x)*(b.location.x-nodeTemp->location.x)+(b.location.y-nodeTemp->location.y)*(b.location.y-nodeTemp->location.y));
//                                    nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                                    bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
//                                    nodeTemp->inAStar=true;
//
//                                }else if (insertInBestNodes){
//                                    bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
//                                }
//                                if (nodeTemp==b.nodeRepresentedBy){
//                                    reached=true;
//                                }
//                                if (!nodeTemp->inVisitedNodes){
//                                    nodeTemp->inVisitedNodes=true;
//                                    visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
//                                }
//                            }
                        }
                    }
                    else
                    {
////                        currentCluster=currentCluster->getSonThatCorrespondToNode(node);
//                        Node* nodeTemp=&(currentCluster->getSonThatCorrespondToNode(node)->graph.nodes[node->idEquivalentLowerVerticalNode]);
//                        double possiblePathWeight=currentPathWeight;
//                        insertInBestNodes=false;
//                        if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance){
//                            nodeTemp->minDistance=possiblePathWeight;
//                            insertInBestNodes=true;
//                        }
//                        //                    double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
//                        //                    nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                        if (!nodeTemp->inDijkstra&&insertInBestNodes){
//                            //                        if (!nodeTemp->inDijkstra){
//                            double heuristicDistanceToGoal=sqrt((b.location.x-nodeTemp->location.x)*(b.location.x-nodeTemp->location.x)+(b.location.y-nodeTemp->location.y)*(b.location.y-nodeTemp->location.y));
//                            nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                            bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
//                            nodeTemp->inDijkstra=true;
//
//                        }else if (insertInBestNodes){
//                            bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
//                        }
//                        if (nodeTemp==b.nodeRepresentedBy){
//                            reached=true;
//                        }
//                        if (!nodeTemp->inCutoff){
//                            nodeTemp->inCutoff=true;
//                            visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
//                        }
                    }

                }
                else
                {
                    for(int i=0; i<node->transitions.size(); i++)
                    {
                        if (node->transitions[i]->b->depthInRTree==node->depthInRTree)
                        {
                            Node* nodeTemp=node->transitions[i]->b;

                            if (nodeTemp==NULL)
                            {
                                nodeTemp=&(currentCluster->graph->nodes[node->transitions[i]->idB]);
                            }
                            if (node->transitions[i]->weight==INFINITY)
                            {
                                //                            std::cout<<"mal hecha la transicion horizontal"<<'\n';
                            }
                            double possiblePathWeight=currentPathWeight+node->transitions[i]->weight;

                            //                    double distanceTemp=nodeTemp->minDistance;
                            //                    bool lessThan=(possiblePathWeight<nodeTemp->minDistance);
                            insertInBestNodes=false;
                            if (nodeTemp->minDistance==INFINITY||possiblePathWeight<nodeTemp->minDistance)
                            {
                                nodeTemp->minDistance=possiblePathWeight;
                                insertInBestNodes=true;
                                if(nodeTemp->originalID==b->originalID)
                                {
                                    reached=true;
                                    b->nodeRepresentedBy->minDistance=nodeTemp->minDistance;
                                    if(!b->nodeRepresentedBy->inVisitedNodes)
                                    {
                                        b->nodeRepresentedBy->inVisitedNodes=true;
                                        visitedNodes.push(b->nodeRepresentedBy,&Graph::compareByDistanceAndHeuristic);
                                    }
                                }

                            }
                            //                        insertInBestNodes=true;
                            //                    double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-node->location.x)+(b->location.y-node->location.y)*(b->location.y-node->location.y));
                            //                    nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                            if (!nodeTemp->inAStar&&insertInBestNodes)
                            {
                                //                        if (!nodeTemp->inDijkstra){
                                double hDis=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
                                double heuristicDistanceToGoal=hDis*(1+log(hDis)*multiplierHeuristic)+summerHeuristic;
                                nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                                bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
                                nodeTemp->inAStar=true;

                            }
                            else if (insertInBestNodes)
                            {
                                bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
                            }
                            if (nodeTemp==b->nodeRepresentedBy)
                            {
                                //                            reached=true;
                            }
                            if (!nodeTemp->inVisitedNodes)
                            {
                                nodeTemp->inVisitedNodes=true;
                                visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
                            }
                        }
                    }
                }
            }
        }

//        if (bestNodes.size()==0&&b.nodeRepresentedBy->minDistance==INFINITY){
//////            bestNodes.push((visitedNodes.getMin(&Graph::compareByDistanceAndHeuristic)),&Graph::compareByDistanceAndHeuristic);
////            Node* nodeMin=visitedNodes.getMin(&Graph::compareByDistanceAndHeuristic);
////            bestNodes.push(nodeMin, &Graph::compareByDistanceAndHeuristic);
//            node=a.nodeRepresentedBy;
////            node->inDijkstra=true;
////            node->minDistance=0;
////            double heuristicDistanceToGoal=sqrt((b.location.x-node->location.x)*(b.location.x-node->location.x)+(b.location.y-node->location.y)*(b.location.y-node->location.y));
////            node->heuristicDistanceToGoal=heuristicDistanceToGoal;
////            bestNodes.push(node, &Graph::compareByDistanceAndHeuristic);
//            //    visitedNodes
//            //    visitedNodes.push(node, &Graph::compareByDistanceAndHeuristic);
//
//             reached=false;
//             goingUp=true;
//             dontgoupagain=false;
//            bool insertInBestNodes=false;
//            for(int i=0;i<node->verticalPathsTowardsUpperLevel.size();i++){
//                Node* nodeTemp=node->verticalPathsTowardsUpperLevel[i].b;
//                //                    Node* nodeTemp=(currentCluster->parent->graphTemp.nodes[node->verticalPathsTowardsUpperLevel[i].idB]).nodeRepresentedBy;
//                if (node->verticalPathsTowardsUpperLevel[i].weight==INFINITY){
//                    //                        std::cout<<"mal hecha la transicion towards upper level"<<'\n';
//                }
//                double possiblePathWeight=currentPathWeight+node->verticalPathsTowardsUpperLevel[i].weight;
//                insertInBestNodes=false;
//                if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance){
//                    nodeTemp->minDistance=possiblePathWeight;
//                    insertInBestNodes=true;
//                }
//                //                double heuristicDistanceToGoal=sqrt((b->location.x-nodeTemp->location.x)*(b->location.x-nodeTemp->location.x)+(b->location.y-nodeTemp->location.y)*(b->location.y-nodeTemp->location.y));
//                //                nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                if (!nodeTemp->inDijkstra&&insertInBestNodes){
//                    //                    if (!nodeTemp->inDijkstra){
//                    double heuristicDistanceToGoal=sqrt((b.location.x-nodeTemp->location.x)*(b.location.x-nodeTemp->location.x)+(b.location.y-nodeTemp->location.y)*(b.location.y-nodeTemp->location.y));
//                    nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
//                    bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
//                    nodeTemp->inDijkstra=true;
//
//
//                }else if (insertInBestNodes){
//                    bestNodes.buildHeap(&Graph::compareByDistanceAndHeuristic);
//                }
//                if (nodeTemp==b.nodeRepresentedBy){
//                    //                        reached=true;
//                }
//                if (!nodeTemp->inCutoff){
//                    nodeTemp->inCutoff=true;
//                    visitedNodes.push(nodeTemp,&Graph::compareByDistanceAndHeuristic);
//                }
//            }
//        }

    }
    if (!node->inVisitedNodes)
    {
        node->inVisitedNodes=true;
        visitedNodes.push(node,&Graph::compareByDistanceAndHeuristic);
    }
    double distance=b->nodeRepresentedBy->minDistance;

//    ArchivoTexto textFile;
//    //            for(int h=0;h<clustersOfALevel.size();h++){
//    std::stringstream nameSS;
//    nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/levels/exampleGraph_analyseHeuristic"<<".txt";
//    std::string name=nameSS.str();
//    std::vector<std::string> values;
//    hDis=sqrt((b.location.x-a.location.x)*(b.location.x-a.location.x)+(b.location.y-a.location.y)*(b.location.y-a.location.y));
////    double heuristicDistanceToGoal=hDis*(1+log(hDis)*multiplierHeuristic);
//    std::stringstream valueSS;
//    valueSS<<to_string(hDis)<<" "<<to_string(b.nodeRepresentedBy->minDistance);
//    std::string value=valueSS.str();
//    values.clear();
//    values.push_back(value);
////    values.push_back(to_string(node->depthInRTree));
//    textFile.writeToFile(name, values, true);

    for(long i=0; i<visitedNodes.size(); i++)
    {
        visitedNodes.heap[i]->inVisitedNodes=false;
        visitedNodes.heap[i]->inAStar=false;
        visitedNodes.heap[i]->minDistance=INFINITY;
    }
    visitedNodes.clear();
    bestNodes.clear();
    return distance;

}
double RTree::calculateDiameter()
{
    double diameter=-1;

    std::vector<ClusterRTree*> clustersByDepthTemp;
//    std::vector<TransitionCluster*> externalTransitions=externalCluster.transitionsById.getAll();
//    std::vector<ClusterRTree*> externalLeaves=mainCluster.externalLeavesById.getAll();
//    for(long i=0;i<externalTransitions.size();i++){
////        externalLeaves.push_back(externalTransitions[i]->cb);
////        std::cout<<"external leave id "<<externalTransitions[i]->cb->id;
//    }

    bool aprox=false;
    if(aprox)
    {
        while(mainCluster.externalClustersByDepth.size()>0)
        {
            ClusterRTree* cluster=mainCluster.externalClustersByDepth.pop(&ClusterRTree::compareByDepth);
            if(cluster->parent!=NULL)
            {
                std::vector<Node*> nodesFrontierTemp;
                for(long i=0; i<cluster->frontierNodes.size(); i++)
                {
                    Node* node=cluster->frontierNodes[i];
                    nodesFrontierTemp.push_back(node);
                }
                while (nodesFrontierTemp.size()>0)
                {
                    //            for(long i=0;i<cluster->frontierNodes.size();i++){
                    Node* node=nodesFrontierTemp[nodesFrontierTemp.size()-1];
                    nodesFrontierTemp.pop_back();

                    std::vector<Node*> nodesCutoff;
                    Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                    Node* nodeTemp=node->nodeRepresentedBy;
                    nodesCutoff.push_back(nodeTemp);
                    nodesToCheckDijkstra.push(nodeTemp);
                    nodeTemp->minDistance=0;
                    cluster->graph->calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra);

                    for(long j=0; j<cluster->graph->nodes.size(); j++)
                    {

                        double previousDiameterToThatNode=INFINITY;
                        Transition* transTemp=NULL;
                        bool exist=cluster->subDiameters.exist(cluster->graph->nodes[j].id);
                        if(exist)
                        {
                            transTemp=cluster->subDiameters.get(cluster->graph->nodes[j].id);

                            previousDiameterToThatNode=transTemp->weight;
                        }

                        if(!cluster->graph->nodes[j].nodeThatRepresents->isFrontier)
                        {
                            if(cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax<INFINITY&&node->nodeRepresentedBy->dMax<cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax&&cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax<previousDiameterToThatNode)
                            {
                                node->nodeRepresentedBy->dMax=cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax;
                                if(exist)
                                {
                                    transTemp->a->dMax=0;
                                    //                                cluster->parent->graphTemp.nodes[node->idEquivalentUpperVerticalNode].dMax=0;
                                    nodesFrontierTemp.push_back(transTemp->a->nodeThatRepresents);

                                }
                                if(cluster->isLeave)
                                {
                                    node->initialNodeOfDiameter=(cluster->graph->nodes[j].nodeThatRepresents);
                                }
                                else
                                {
                                    //                                node->initialNodeOfDiameter=&(cluster->graph.nodes[j]);
                                }
                                Transition transTemp2;
                                transTemp2.a=node->nodeRepresentedBy;
                                transTemp2.b=&(cluster->graph->nodes[j]);
                                transTemp2.weight=cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax;
                                cluster->subDiameters.add(transTemp2.b->id, &transTemp2);
                            }
                        }
                    }


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
                    //            if(cluster->parent!=NULL){

                    //                    cluster->parent->graphTemp.nodes[node->idEquivalentUpperVerticalNode].dMax=max(node->nodeRepresentedBy->dMax,node->dMax);


                }
                for(long i=0; i<cluster->frontierNodes.size(); i++)
                {
                    if(cluster->isLeave&&cluster->frontierNodes[i]->initialNodeOfDiameter==NULL)
                    {
                        cluster->frontierNodes[i]->initialNodeOfDiameter=cluster->frontierNodes[i];
                    }
                    cluster->parent->graphTemp->nodes[cluster->frontierNodes[i]->idEquivalentUpperVerticalNode].initialNodeOfDiameter=cluster->frontierNodes[i]->initialNodeOfDiameter;
                    cluster->parent->graphTemp->nodes[cluster->frontierNodes[i]->idEquivalentUpperVerticalNode].dMax=max(cluster->frontierNodes[i]->nodeRepresentedBy->dMax,cluster->frontierNodes[i]->dMax);
                }
            }
            else
            {
                for(long i=0; i<cluster->graph->nodes.size(); i++)
                {
                    Transition possibleDiameterTransition;
                    std::vector<Node*> nodesCutoff;
                    Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                    Node* nodeTemp=&(cluster->graph->nodes[i]);
                    nodesCutoff.push_back(nodeTemp);
                    nodeTemp->minDistance=0;
                    nodesToCheckDijkstra.push(nodeTemp);
                    cluster->graph->calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra);

                    for(long j=0; j<cluster->graph->nodes.size(); j++)
                    {
                        if(i!=j)
                        {
                            //                        //                    if(!cluster->graph.nodes[j].nodeThatRepresents->isFrontier){
                            //                        //                    double previousDiameterToThatNode=INFINITY;
                            //                        //                    Transition* transTemp=NULL;
                            //                        //                    bool exist=cluster->subDiameters.exist(cluster->graph.nodes[j].id);
                            //                        //                    if(exist){
                            //                        //                        transTemp=cluster->subDiameters.get(cluster->graph.nodes[j].id);
                            //                        //
                            //                        //                        previousDiameterToThatNode=transTemp->weight;
                            //                        //                    }
                            //
                            double possibleDiameter=0;
                            if(cluster->graph->nodes[i].nodeThatRepresents->dMax+cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax<INFINITY)
                            {
                                possibleDiameter=cluster->graph->nodes[i].nodeThatRepresents->dMax+cluster->graph->nodes[j].minDistance+cluster->graph->nodes[j].nodeThatRepresents->dMax;

                                //                            possibleDiameter=AStar(cluster->graph.nodes[i].nodeThatRepresents->initialNodeOfDiameter, cluster->graph.nodes[j].nodeThatRepresents->initialNodeOfDiameter);

                                //                            std::cout<<"aproximate diameter "<<possibleDiameter<<'\n';
                            }
                            else
                            {

                                possibleDiameter=max(cluster->graph->nodes[i].nodeThatRepresents->dMax,cluster->graph->nodes[j].nodeThatRepresents->dMax);
                            }

//                            double possibleDiameter=AStar(possibleDiameterTransition.a, possibleDiameterTransition.b);

                            if(cluster->graph->nodes[i].dMax<possibleDiameter)
                            {
                                cluster->graph->nodes[i].dMax=possibleDiameter;
                                possibleDiameterTransition.a=cluster->graph->nodes[i].nodeThatRepresents->initialNodeOfDiameter;
                                possibleDiameterTransition.b=cluster->graph->nodes[j].nodeThatRepresents->initialNodeOfDiameter;
                            }
                        }
                        //                    }
                    }


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

                    //                std::cout<<"real diameter "<<realDiameter<<'\n';
                    if(cluster->graph->nodes[i].dMax>diameter)
                    {
                        diameter=cluster->graph->nodes[i].dMax;

                    }
                    //                std::cout<<"ids "<<cluster->graph.nodes[i]
                    //                std::cout<<"possible diameter "<<cluster->graph.nodes[i].dMax<<'\n';



                }
            }

//            clustersByDepthTemp.push_back(cluster);



        }
        std::cout<<"diameter "<<diameter<<'\n';
//        while(clustersByDepthTemp.size()>0){
//            ClusterRTree* cluster=clustersByDepthTemp[clustersByDepthTemp.size()-1];
//            clustersByDepthTemp.pop_back();
//            mainCluster.clustersByDepth.push(cluster, &ClusterRTree::compareByDepth);
//        }
    }
    else
    {
        ClusterRTree* possibleClustersOfDiameter[2];
        possibleClustersOfDiameter[0]=NULL;
        possibleClustersOfDiameter[1]=NULL;
        std::vector<ClusterRTree*> leaves=mainCluster.externalLeavesById.getAll();
        for(int i=0; i<leaves.size(); i++)
        {
            for(int j=0; j<leaves.size(); j++)
            {
                if(i<=j)
                {
                    ClusterRTree* commonParent=getCommonParent(leaves[i], leaves[j]);
                    if(commonParent->depth==0)
                    {
//                        for(long h=0;h<leaves[i]->graph.nodes.size();h++){
//                            for(long g=0;g<leaves[j]->graph.nodes.size();g++){
                        if(leaves[i]->graph->nodes.size()>0&&leaves[j]->graph->nodes.size()>0)
                        {
                            long h=0;
                            long g=0;
                            double possibleDiameter;
                            if(mode==A_STAR)
                            {
                                possibleDiameter=AStar(leaves[i]->graph->nodes[h].nodeThatRepresents, leaves[j]->graph->nodes[g].nodeThatRepresents,false);
                            }
                            else
                            {
                                possibleDiameter=mainCluster.calculateDistance(&leaves[i]->graph->nodes[h], &leaves[j]->graph->nodes[g]);
                            }


//                                double possibleDiameter=AStar(leaves[i]->graph.nodes[h].nodeThatRepresents, leaves[j]->graph.nodes[g].nodeThatRepresents,false);
                            // double possibleDiameter=mainCluster.findDistanceRecursive(&leaves[i]->graph.nodes[h], &leaves[j]->graph.nodes[g]);
//                            double possibleDiameter=mainCluster.calculateDistance(&leaves[i]->graph.nodes[h], &leaves[j]->graph.nodes[g]);
                            if(diameter<possibleDiameter&&possibleDiameter<INFINITY)
                            {
                                possibleClustersOfDiameter[0]=leaves[i];
                                possibleClustersOfDiameter[1]=leaves[j];
                                diameter=possibleDiameter;
//                                    std::cout<<possibleDiameter<<'\n';
                            }
                        }
//                            }
//                        }
                    }
                }

            }
        }
        if(possibleClustersOfDiameter[0]!=NULL)
        {
            for(long h=0; h<possibleClustersOfDiameter[0]->graph->nodes.size(); h++)
            {
                for(long g=0; g<possibleClustersOfDiameter[1]->graph->nodes.size(); g++)
                {
//                if(leaves[i]->graph.nodes.size()>0&&leaves[j]->graph.nodes.size()>0){
                    double possibleDiameter;
                    if(mode==A_STAR)
                    {
                        possibleDiameter=AStar(possibleClustersOfDiameter[0]->graph->nodes[h].nodeThatRepresents, possibleClustersOfDiameter[1]->graph->nodes[g].nodeThatRepresents,false);
                    }
                    else
                    {
                        possibleDiameter=mainCluster.calculateDistance(&possibleClustersOfDiameter[0]->graph->nodes[h], &possibleClustersOfDiameter[1]->graph->nodes[g]);
                    }

//                    double possibleDiameter=AStar(possibleClustersOfDiameter[0]->graph.nodes[h].nodeThatRepresents, possibleClustersOfDiameter[1]->graph.nodes[g].nodeThatRepresents,false);
                    // double possibleDiameter=mainCluster.findDistanceRecursive(&possibleClustersOfDiameter[0]->graph.nodes[h], &possibleClustersOfDiameter[1]->graph.nodes[g]);
//                                            double possibleDiameter=mainCluster.calculateDistance(&possibleClustersOfDiameter[0]->graph.nodes[h], &possibleClustersOfDiameter[1]->graph.nodes[g]);
                    if(diameter<possibleDiameter&&possibleDiameter<INFINITY)
                    {
                        diameter=possibleDiameter;
                    }
//                }
                }
            }
        }
    }


    return diameter;

}

double RTree::calculateAllToAllDistances()
{
//    ClusterRTree* possibleClustersOfDiameter[2];
    std::vector<ClusterRTree*> leaves=mainCluster.leavesById.getAll();
    double diameter=0;
    for(int i=0; i<leaves.size(); i++)
    {
        for(int j=0; j<leaves.size(); j++)
        {
            if(i<=j)
            {
                ClusterRTree* commonParent=getCommonParent(leaves[i], leaves[j]);
                if(commonParent->depth==0)
                {
//                         long h=0;
//                            long g=0;
                    if(leaves[i]->graph->nodes.size()>0&&leaves[j]->graph->nodes.size()>0)
                    {
                        for(long h=0; h<leaves[i]->graph->nodes.size(); h++)
                        {
                            for(long g=0; g<leaves[j]->graph->nodes.size(); g++)
                            {

//                                double possibleDiameter=AStar(leaves[i]->graph.nodes[h].nodeThatRepresents, leaves[j]->graph.nodes[g].nodeThatRepresents,false);
                                /// double possibleDiameter=mainCluster.findDistanceRecursive(&leaves[i]->graph.nodes[h], &leaves[j]->graph.nodes[g]);
                                double possibleDiameter=mainCluster.calculateDistance(&leaves[i]->graph->nodes[h], &leaves[j]->graph->nodes[g]);
                                if(diameter<possibleDiameter&&possibleDiameter<INFINITY)
                                {
//                                    possibleClustersOfDiameter[0]=leaves[i];
//                                    possibleClustersOfDiameter[1]=leaves[j];
                                    diameter=possibleDiameter;
//                                    std::cout<<possibleDiameter<<'\n';
                                }
                            }
//                            }
//                        }
                        }
                    }

                }
            }
//        if(possibleClustersOfDiameter[0]!=NULL){
//        for(long h=0;h<possibleClustersOfDiameter[0]->graph.nodes.size();h++){
//            for(long g=0;g<possibleClustersOfDiameter[1]->graph.nodes.size();g++){
////                if(leaves[i]->graph.nodes.size()>0&&leaves[j]->graph.nodes.size()>0){
//
////                    double possibleDiameter=AStar(possibleClustersOfDiameter[0]->graph.nodes[h].nodeThatRepresents, possibleClustersOfDiameter[1]->graph.nodes[g].nodeThatRepresents,true);
//                   // double possibleDiameter=mainCluster.findDistanceRecursive(&possibleClustersOfDiameter[0]->graph.nodes[h], &possibleClustersOfDiameter[1]->graph.nodes[g]);
//                                            double possibleDiameter=mainCluster.calculateDistance(&possibleClustersOfDiameter[0]->graph.nodes[h], &possibleClustersOfDiameter[1]->graph.nodes[g]);
//                    if(diameter<possibleDiameter&&possibleDiameter<INFINITY){
//                        diameter=possibleDiameter;
//                    }
////                }
//            }
        }
    }



    return diameter;
}
std::vector<double> RTree::calculateDistances(std::vector<Transition> &originDestinationPairs)
{
    std::vector<double> distances;

    for(int i=0; i<originDestinationPairs.size(); i++)
    {

//                    ClusterRTree* commonParent=getCommonLevelOfTwoNodes(originDestinationPairs[i].a, originDestinationPairs[i].b);


        double distance;
        if(mode==RTree::TREE_DISTANCE)
        {
            distance=mainCluster.calculateDistance(originDestinationPairs[i].a->nodeRepresentedBy, originDestinationPairs[i].b->nodeRepresentedBy);
        }
        else if(mode==RTree::A_STAR)
        {
            distance=AStar(originDestinationPairs[i].a, originDestinationPairs[i].b,false);
        }
//                    std::cout<<"distance "<<distance<<'\n';
        distances.push_back(distance);








    }




    return distances;
}

std::vector<Transition> RTree::getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(Graph* graph)
{

    std::vector<Transition> originDestinationPairs;
//                    originDestinationPairs.clear();
//                    rTree.mainCluster.
    generateCornersOfMainCluster(graph);
//                    std::cout<<"QTree created"<<'\n';
    for(int i=0; i<graph->nodes.size(); i++)
    {
        Node* node=&(graph->nodes[i]);
        mainCluster.addExternalNode(node);
    }
//                    std::cout<<"nodes added"<<'\n';




//                    std::vector<Transition> originDestinationPairs;
//
    //                    long numberTimes=mainGraph.nodes.size()/25;
    std::vector<ClusterRTree*> clustersExternalLeaves=mainCluster.externalLeavesById.getAll();
    
    std::cout<<"RTREE clustersExternalLeaves size : "<<clustersExternalLeaves.size()<<'\n';

    for(long i=0; i<clustersExternalLeaves.size(); i++)
    {
        for(long j=0; j<clustersExternalLeaves.size(); j++)
        {
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

std::vector<ClusterRTree*> RTree::getClustersInARange(double minX,double minY,double maxX,double maxY){
    ClusterRTree* current=&(mainCluster);
    std::vector<ClusterRTree*> possibles;
    std::vector<ClusterRTree*> finals;
    possibles.push_back(current);
    while(possibles.size()>0){
        current=possibles.back();
        possibles.pop_back();
        if (current->sons.size()>0)
        {
            for(int i=0;i<current->sons.size();i++){
                bool xIn=false;
                bool yIn=false;
                if(current->sons[i].corners[0].x>minX&&current->sons[i].corners[0].x<maxX){
                    xIn=true;
                }
                if(current->sons[i].corners[1].x>minX&&current->sons[i].corners[1].x<maxX){
                    xIn=true;
                }
                if(current->sons[i].corners[0].y>minX&&current->sons[i].corners[0].y<maxX){
                    yIn=true;
                }
                if(current->sons[i].corners[1].y>minX&&current->sons[i].corners[1].y<maxX){
                    yIn=true;
                }
                if(xIn&&yIn){
                    possibles.push_back(current);
                }
            }
        }else{
            bool xIn=false;
            bool yIn=false;
            if(current->corners[0].x>minX&&current->corners[0].x<maxX){
                xIn=true;
            }
            if(current->corners[1].x>minX&&current->corners[1].x<maxX){
                xIn=true;
            }
            if(current->corners[0].y>minX&&current->corners[0].y<maxX){
                yIn=true;
            }
            if(current->corners[1].y>minX&&current->corners[1].y<maxX){
                yIn=true;
            }
            if(xIn&&yIn){
                finals.push_back(current);
            }
        }
    }
    return finals;
}
std::vector<Node*> RTree::getNodesOfClusters(std::vector<ClusterRTree*> clusters){
    std::vector<Node*> nodes;
    for(long i=0;i<clusters.size();i++){
        for(long j=0;j<clusters[i]->nodesInCluster.size();j++){
            nodes.push_back(clusters[i]->nodesInCluster[j]);
        }
    }
    return nodes;
}
std::vector<Node*> RTree::getNodesInARange(double minX,double minY,double maxX,double maxY){
    std::vector<ClusterRTree*> clustersInRange=getClustersInARange(minX,minY,maxX,maxY);
    std::vector<Node*> nodesInRange=getNodesOfClusters(clustersInRange);
    return nodesInRange;
}
//void RTree::generateSpatialPercolation(Graph* graph,double distanceLimit,std::vector<Graph> &clusters){
//        std::vector<std::vector<Node*>> gridPoints;
//    
//        RTree quadTree;
//        quadTree.generateCornersOfMainCluster(graph);
//    //    quadTree.maxNumberNodes=100;
//        Graph graphOfCloseness;
//        for(long i=0;i<graph->nodes.size();i++){
//            graphOfCloseness.addNode();
//        }
//        for(long i=0;i<graph->nodes.size();i++){
//            graphOfCloseness.nodes[i].location=graph->nodes[i].location;
//            graphOfCloseness.nodes[i].originalID=graph->nodes[i].originalID;
//            graphOfCloseness.nodes[i].nodeThatRepresents=&(graph->nodes[i]);
//        }
//        for(long i=0;i<graphOfCloseness.nodes.size();i++){
//            Node* node=&graphOfCloseness.nodes[i];
//            quadTree.mainCluster.addNode(node);
//        }
//
//        for(long i=0;i<graphOfCloseness.nodes.size();i++){
//            double width=distanceLimit;
//                std::vector<Node*> nodesClose;
//            std::vector<Node*> nodesInRange=quadTree.getNodesInARange(graphOfCloseness.nodes[i].location.x-width, graphOfCloseness.nodes[i].location.x+width, graphOfCloseness.nodes[i].location.y-width, graphOfCloseness.nodes[i].location.y+width);
//            for(long j=0;j<nodesInRange.size();j++){
//                double distance=Functions::getDistance(graph->nodes[i].location, nodesInRange[j]->location);
//                if(distance<distanceLimit){
//                    Transition trans;
//                    trans.a=&graphOfCloseness.nodes[i];
//                    trans.b=nodesInRange[j];
//                    trans.weight=distance;
//                    graphOfCloseness.addDirectedTransition(trans);
//                }
//            }
//            
//        }
//        std::vector<Graph> clusters;
//        graphOfCloseness.calculateClusterUsingNetworkPercolation(distanceLimit, clusters, false, true, "", 0);
//    
//    
//    
//}
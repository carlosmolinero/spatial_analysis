//
//  Customize.cpp
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 11/02/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Customize.h"

Customize::Customize(){
    useDistributionDistances=true;
    useGeneratedAndAttractedTrips=false;
}



double Customize::applyDistributionDistancesByMode(int mode,double distance){
    double value=0;
    if(useDistributionDistances){
        
        if(mode==BICYCLE_COMMUTER){
    //        16.98338
            value=Functions::gammaDistribution(distance, 2, 1.36, 5627.92995);
        }
        if(mode==BICYCLE_LEISURE){
            value=Functions::gammaDistribution(distance, 2, 1.36, 5627.92995);
        }
        if(mode==BICYCLE_SPORT){
            value=Functions::gammaDistribution(distance, 2, 1.36, 30000);
        }
    }
//    value=1;

    return value;
}

//void Customize::modifyGeneratedTripsMelbourne(std::vector<Node*> orderedCutoff,Node* nodeInit,std::vector<int> setOfDistancesToCalculate,int distanceIndex){
//    if(useGeneratedAndAttractedTrips){
//    
////    for(long i=0;i<orderedCutoff.size();i++){
////
////        double euclidianDistance=Functions::getDistance(orderedCutoff[i]->location, nodeInit->location);
////        if(euclidianDistance<INFINITY){
////
////            
////            
////            
////            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[distanceIndex]]=orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[distanceIndex]]*multiplierValuesToPass;
////            double tripsGeneratedByPopulation=nodeInit->tripsGenerated;
////            double tripsGeneratedByUse=nodeInit->tripsReceivedFromNodeByID[orderedCutoff[i]->originalID];
////
////            
////
////            double tripsGenerated=tripsGeneratedByPopulation+tripsGeneratedByUse;
////            
////            
////
////            
////            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[distanceIndex]]=orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[distanceIndex]]*tripsGenerated;
////            
////        
////        }
////    }
//    }
//}

//void Customize::prepareGeneratedRoundTrips(Graph* graph,QTree* quadTree,Node* &nodeInit,double distanceLimit)
//{
//    if(useGeneratedAndAttractedTrips){
//        nodeInit->minDistance=0;
//        Node* startNode=nodeInit;
//        std::vector<Node*> nodesCutoff;
//        nodesCutoff.push_back(startNode);
//        startNode->inCutoff=true;
//        
//        Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//        
//        nodesToCheckDijkstra.push(startNode);
//        startNode->inDijkstra=true;
//
//        
//            graph->calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
//    //    nodesCutoff=quadTree->getNodesInARange(nodeInit->location, distanceLimit);
//
//          
//            double sumTrips=1;
//                    sumTrips=0;
//                    for (long i=0; i<nodesCutoff.size(); i++)
//                    {
//                        double tripsAttracted=0;
//                        double euclideanDistance=Functions::getDistance(nodeInit->location, nodesCutoff[i]->location);
//            
//                        for(long h=0;h<nodesCutoff[i]->customizedAttractedTrips.size();h++){
//                            double value=Customize::applyDistributionDistancesByMode(nodesCutoff[i]->customizedAttractedTrips[h][0], euclideanDistance);
//                            tripsAttracted+=value*nodesCutoff[i]->customizedAttractedTrips[h][1];
//                        }
//                        sumTrips+=tripsAttracted;
//            //            double tripsGenerated=nodeInit->customizedGeneratedTrips[0][1];
//                        //            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=tripsAttracted;
//            //            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=(tripsAttracted+1)*tripsGenerated;
//                    }
//        
//            if(sumTrips>0){
//                
//                
//                for (long i=0; i<nodesCutoff.size(); i++)
//                {
//                    double tripsAttracted=0;
//                    double euclideanDistance=Functions::getDistance(nodeInit->location, nodesCutoff[i]->location);
//                    
//                    for(long h=0;h<nodesCutoff[i]->customizedAttractedTrips.size();h++){
//                        double value=Customize::applyDistributionDistancesByMode(nodesCutoff[i]->customizedAttractedTrips[h][0], euclideanDistance);
//                        
//                        tripsAttracted+=value*nodesCutoff[i]->customizedAttractedTrips[h][1];
//
//                        
//                    }
//                    double tripsGenerated;
//                    if(nodeInit->customizedGeneratedTrips.size()>0){
//                        tripsGenerated=nodeInit->customizedGeneratedTrips[0][1];
//                    }else{
//                        tripsGenerated=0;
//                    }
//                    double populationMoved=((tripsAttracted)/sumTrips)*tripsGenerated;
//                    Transition* trans=nodeInit->transitionThatRepresents;
//                    Transition* oppositeTrans=trans->getSimetricTransition();
//                    if(oppositeTrans!=NULL){
//                        Node* simetricNode=oppositeTrans->nodeOfLineGraphThatRepresentsThis;
//                        
//                        
//                    
//    //                    nodesCutoff[i]->tripsReceivedFromNodeByID[simetricNode->originalID]=populationMoved;
//                    }
//    //                else{
//                        nodesCutoff[i]->tripsReceivedFromNodeByID[nodeInit->originalID]=populationMoved;
//    //                }
//                    
//    //                Transition* transB=nodesCutoff[i]->transitionThatRepresents;
//    //                Transition* oppositeTransB=transB->getSimetricTransition();
//    //                if(oppositeTransB!=NULL){
//    //                    Node* simetricNodeB=oppositeTransB->nodeOfLineGraphThatRepresentsThis;
//    //                    
//    //                    simetricNodeB->tripsReceivedFromNodeByID[nodeInit->originalID]=populationMoved;
//    ////                    Transition* trans=nodeInit->transitionThatRepresents;
//    ////                    Transition* oppositeTrans=trans->getSimetricTransition();
//    //                    if(oppositeTrans!=NULL){
//    //                        Node* simetricNode=oppositeTrans->nodeOfLineGraphThatRepresentsThis;
//    //                        if(simetricNode!=NULL){
//    //                            simetricNodeB->tripsReceivedFromNodeByID[simetricNode->originalID]=populationMoved;
//    //                        }
//    //                        
//    //                        
//    //                         simetricNodeB->tripsReceivedFromNodeByID[nodeInit->originalID]=populationMoved;
//    //                    }
//    //
//    //                }
//                    
//    //                std::cout<<nodesCutoff[i]->originalID<<"->"<<nodeInit->originalID<<" population moved "<<tripsAttracted<<" "<<sumTrips<<" "<<tripsGenerated<<" "<<populationMoved<<'\n';
//                    
//    //                double tripsGenerated=nodeInit->customizedGeneratedTrips[0][1];
//                    
//                    //                if(tripsGenerated>0){
//                    //                    tripsGenerated=1;
//                    //                }
//                    //                if(tripsAttracted>0){
//                    //                    tripsAttracted=1;
//                    //                }
//                    
//                    //                tripsAttracted=1;
//                    //                tripsGenerated=1;
//                    
//                    
//                    //            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=tripsAttracted;
//                    
//                }
//            }else{
//    //            for (long i=0; i<orderedCutoff.size(); i++)
//    //            {
//    //                nodesCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
//    //            }
//                
//            }
//     
//
//        
//        for(long i=0; i<nodesCutoff.size(); i++)
//        {
//         
//            
//            nodesCutoff[i]->inCutoff=false;
//            
//            nodesCutoff[i]->inDijkstra=false;
//            nodesCutoff[i]->numChildren=0;
//            nodesCutoff[i]->numChildrenThatReachedMe=0;
//            nodesCutoff[i]->parent=NULL;
//            nodesCutoff[i]->minDistance=INFINITY;
//            nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
//
//            
//
//
//            
//        }
//        
//        nodesCutoff.clear();
//        std::vector<Node*>().swap(nodesCutoff);
//    }
//}
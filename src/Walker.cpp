//
//  Walker.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 13/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Walker.h"

Node* Walker::walk(PotentialField &potentialField,QTree &quadTree,Node* objective){
//    std::cout<<"location Start " <<location.x<<" "<<location.y<<'\n';
    long row=(long)((location.y-potentialField.initLocation.y)/potentialField.width);
    long column=(long)((location.x-potentialField.initLocation.x)/potentialField.width);
//        std::cout<<"column "<<column<<" row "<<row<<'\n';
    ClusterField currentCluster=potentialField.clusters[column+row*potentialField.numberObjectsInRow];
    Point2d centroid=Point2d((currentCluster.corner1.x+currentCluster.corner2.x)/2.0,(currentCluster.corner1.y+currentCluster.corner2.y)/2.0);
//    std::cout<<"cluster center A "<<" " <<centroid.x<<" "<<centroid.y<<'\n';
//    std::cout<<"objective " <<objective->location.x<<" "<<objective->location.y<<'\n';
//    std::cout<<"location A " <<location.x<<" "<<location.y<<'\n';
//    std::cout<<"corners "<<currentCluster.corner1.x<<" "<<currentCluster.corner2.x<<'\n';
    std::vector<Node*> nodesInARange=quadTree.getNodesInARange(currentCluster.corner1.x, currentCluster.corner1.y, currentCluster.corner2.x, currentCluster.corner2.y);
    Node* node=NULL;

        
        
        for(long i=0;i<nodesInARange.size();i++){
            if (nodesInARange[i]==objective){
                node=nodesInARange[i];
            }
        }

    if(node==objective){
        return node;
    }
    else{
        
    
    

//    double radius=potentialField.width*2;
    
    std::vector<ClusterField> clustersClose;
        if(column>0){
            clustersClose.push_back(potentialField.clusters[column-1+row*potentialField.numberObjectsInRow]);
            if(row<potentialField.clusters.size()/potentialField.numberObjectsInRow-1){
                clustersClose.push_back(potentialField.clusters[column-1+(row+1)*potentialField.numberObjectsInRow]);
            }
            if(row>0){
                clustersClose.push_back(potentialField.clusters[column-1+(row-1)*potentialField.numberObjectsInRow]);
            }
        }
        if(column<potentialField.numberObjectsInRow-1){
            clustersClose.push_back(potentialField.clusters[column+1+row*potentialField.numberObjectsInRow]);
            if(row<potentialField.clusters.size()/potentialField.numberObjectsInRow-1){
                clustersClose.push_back(potentialField.clusters[column+1+(row+1)*potentialField.numberObjectsInRow]);
            }
            if(row>0){
                clustersClose.push_back(potentialField.clusters[column+1+(row-1)*potentialField.numberObjectsInRow]);
            }
        }
        if(row<potentialField.clusters.size()/potentialField.numberObjectsInRow-1){
            clustersClose.push_back(potentialField.clusters[column+(row+1)*potentialField.numberObjectsInRow]);
        }
        if(row>0){
            clustersClose.push_back(potentialField.clusters[column+(row-1)*potentialField.numberObjectsInRow]);
        }

    

    std::vector<ClusterField> clustersCorrectAngle;
        Heap<Node*> heap(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        
        bool found=false;
        std::vector<Node> nodes;
        for(long i=0;i<clustersClose.size();i++){
            Node node;
            nodes.push_back(node);
        }
    for(long i=0;i<clustersClose.size();i++){
        Point2d centroid=Point2d((clustersClose[i].corner1.x+clustersClose[i].corner2.x)/2.0,(clustersClose[i].corner1.y+clustersClose[i].corner2.y)/2.0);
//        std::cout<<"cluster "<<i<<" " <<centroid.x<<" "<<centroid.y<<'\n';
        if(Functions::containedInArea(objective->location, clustersClose[i].corner1, clustersClose[i].corner2)&&!found){
            clustersCorrectAngle.clear();
            clustersCorrectAngle.push_back(clustersClose[i]);
            found=true;
        }else if(!found){
//            std::cout<<"location A " <<location.x<<" "<<location.y<<'\n';

            double distance=Functions::getDistance(location, centroid)+Functions::getDistance( centroid, objective->location);
            Node* nodeTemp=&nodes[i];
            nodeTemp->id=i;
            nodeTemp->minDistance=distance;
            heap.push(nodeTemp);
//            std::cout<<"angle "<<angle<<'\n';
//            if(angle<=90){
//                clustersCorrectAngle.push_back(clustersClose[i]);
//            }
        }
    }
    if(clustersCorrectAngle.size()==0){
         for(long i=0;i<2;i++){
             Node* node=heap.pop();
             clustersCorrectAngle.push_back(clustersClose[node->id]);
         }
    }
    double min=INFINITY;
    long index=-1;
    for(long i=0;i<clustersCorrectAngle.size();i++){
        if(clustersCorrectAngle[i].value<min){
            min=clustersCorrectAngle[i].value;
            index=i;
        }
        
    }
    currentCluster=clustersCorrectAngle[index];
//        std::cout<<"current cluster location B "<<currentCluster.corner1.x<<" "<< currentCluster.corner1.y<<" "<< currentCluster.corner2.x<<" "<< currentCluster.corner2.y<<'\n';
         Point2d centroid=Point2d((currentCluster.corner1.x+currentCluster.corner2.x)/2.0,(currentCluster.corner1.y+currentCluster.corner2.y)/2.0);
        
        location=centroid;
//        std::cout<<"location B "<<location.x<<" "<<location.y<<'\n';
    std::vector<Node*> nodesInARange=quadTree.getNodesInARange(currentCluster.corner1.x, currentCluster.corner1.y, currentCluster.corner2.x, currentCluster.corner2.y);
//        std::cout<<"nodesInRange size "<<nodesInARange.size()<<'\n';
    if(nodesInARange.size()>0){
        Node* node=nodesInARange[0];
        
        for(long i=0;i<nodesInARange.size();i++){
            if (nodesInARange[i]==objective){
                node=nodesInARange[i];
            }
        }
        return node;
    }else{
        return NULL;
    }
}


}
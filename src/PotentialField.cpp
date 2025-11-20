//
//  potentialField.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 08/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "PotentialField.h"
void PotentialField::setValue(ClusterField* cluster,double value){
    
    cluster->value=value;
    
    if (max<value){
        max=value;
    }
    if (min>value){
        min=value;
    }
  
}

void PotentialField::reset(){
    for(long j=0;j<clusters.size();j++){
        clusters[j].value=0;
    }
    max=-INFINITY;
    min=INFINITY;
}

PotentialField::PotentialField(){
    max=-INFINITY;
    min=INFINITY;
}
ClusterField* PotentialField::getCluster(Point2d &location){
    long row=(long)((location.y-initLocation.y)/width);
    long column=(long)((location.x-initLocation.x)/width);
//        std::cout<<"row "<<row<<" column "<<column<<'\n';
//    ClusterField currentCluster=clusters[column+row*numberObjectsInRow];
//    std::cout<<"clusterid overthere "<<clusters[column+row*numberObjectsInRow].id<<" "<<clusters[column+row*numberObjectsInRow].value<<'\n';
    return &clusters[column+row*numberObjectsInRow];
}

void PotentialField::create(double minX,double minY,double maxX,double maxY,double definition){
    //GENERATE POTENTIALFIELD
    this->minX=minX;
    this->minY=minY;
    this->maxX=maxX;
    this->maxY=maxY;
    double width=Functions::max(maxX-minX,maxY-minY);
//    double definition=10;
    double widthCluster=definition*width/100;
    long numberElements=width/widthCluster+1;
    double startX=minX;
    double startY=minY;
    this->initLocation=Point2d(startX,startY);
    this->width=widthCluster;
    this->numberObjectsInRow=numberElements;
    
    for(long i=0;i<numberElements*numberElements;i++){
        
        
        ClusterField cluster(Point2d(i%numberElements*widthCluster+startX-widthCluster/2,i/numberElements*widthCluster+startY-widthCluster/2),Point2d(i%numberElements*widthCluster+startX+widthCluster/2,i/numberElements*widthCluster+startY+widthCluster/2));
        
        this->clusters.push_back(cluster);
        this->clusters[i].id=i;
        
        
        
    }
}

double PotentialField::getNormalizedValue(ClusterField* cluster){
    return Functions::normalize(cluster->value, min, max);
}

double PotentialField::getNormalizedLoggedValue(ClusterField* cluster){
    return Functions::normalize(log(cluster->value+1), log(min+1), log(max+1));
}

std::vector<ClusterField*> PotentialField::vonNeumannNeighborhood(ClusterField* cluster){
    std::vector<ClusterField*> clustersNeighbors;
    Point2d point=cluster->calculateCentroid();
    Point2d pointA=Point2d(point.x+width,point.y);
    ClusterField* clusterTemp=getCluster(pointA);
    if(point.x+width<=maxX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x-width,point.y);
    clusterTemp=getCluster(pointA);
    if(point.x-width>minX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x,point.y+width);
    clusterTemp=getCluster(pointA);
    if(point.y+width<=maxY&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x,point.y-width);
    clusterTemp=getCluster(pointA);
    if(point.y-width>minY&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    return clustersNeighbors;
}


std::vector<ClusterField*> PotentialField::squareNeighborhood(ClusterField* cluster){
    std::vector<ClusterField*> clustersNeighbors;
    Point2d point=cluster->calculateCentroid();
    Point2d pointA=Point2d(point.x+width,point.y);
    ClusterField* clusterTemp=getCluster(pointA);
    if(point.x+width<=maxX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x-width,point.y);
    clusterTemp=getCluster(pointA);
    if(point.x-width>minX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x,point.y+width);
    clusterTemp=getCluster(pointA);
    if(point.y+width<=maxY&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x,point.y-width);
    clusterTemp=getCluster(pointA);
    if(point.y-width>minY&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    
    pointA=Point2d(point.x-width,point.y-width);
    clusterTemp=getCluster(pointA);
    if(point.y-width>minY&&point.x-width>minX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    pointA=Point2d(point.x+width,point.y-width);
    clusterTemp=getCluster(pointA);
    if(point.y-width>minY&&point.x+width<=maxX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    
    pointA=Point2d(point.x-width,point.y+width);
    clusterTemp=getCluster(pointA);
    if(point.y+width<=maxY&&point.x-width>minX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    
    pointA=Point2d(point.x+width,point.y+width);
    clusterTemp=getCluster(pointA);
    if(point.y+width<=maxY&&point.x+width<=maxX&&clusterTemp!=NULL){
        clustersNeighbors.push_back(clusterTemp);
    }
    return clustersNeighbors;
}










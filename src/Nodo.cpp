//
//  Nodo.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "Nodo.h"

Nodo::Nodo(){
    // nodeThatReferences=NULL;
    mass=1;
    equivalentArea=0;
    mass_upperLevel=1;
    identifier="";
    originalID=-1;

//    nodeThatRepresents=NULL;
//    nodeRepresentedBy=NULL;
}

//void Nodo::copyPropertiesAndReference(Nodo* nodeToCopyFrom){
//    nodeThatRepresents=nodeToCopyFrom;
//    nodeToCopyFrom->nodeRepresentedBy=this;
//    copyProperties(nodeToCopyFrom);
//}
void Nodo::copyProperties(Nodo* nodeToCopyFrom){
    mass=nodeToCopyFrom->mass;
    equivalentArea=nodeToCopyFrom->equivalentArea;
    mass_upperLevel=nodeToCopyFrom->mass_upperLevel;
    location=nodeToCopyFrom->location;
    identifier=nodeToCopyFrom->identifier;
    originalID=nodeToCopyFrom->originalID;
    // nodeThatReferences=nodeToCopyFrom;
}

long Nodo::getDegree(){
    return links.size()+linksThatReachMe.size();
}
long Nodo::getDegreeOut(){
    return links.size();
}
long Nodo::getDegreeIn(){
    return linksThatReachMe.size();
}
std::vector<Link*> Nodo::getLinksThatReachMe(bool directedGraph){
    if(directedGraph){
        return linksThatReachMe;
    }else{
        std::vector<Link*> linksTemp;
        linksTemp.reserve(links.size());
        for(long i=0;i<links.size();i++){
            linksTemp.push_back(links[i]);
        }
        return linksTemp;
    }
}

void Nodo::addLinkThatReachMe(Link* link){
    linksThatReachMe.push_back(link);
}

void Nodo::setLinksThatReachMe(std::vector<Link*> newLinksThatReachMe){
    linksThatReachMe=newLinksThatReachMe;
}

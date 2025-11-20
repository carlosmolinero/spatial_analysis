//
//  Link.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "Link.h"

Link::Link(){
    // inverted=false;
    identifier="";
    originalID=-1;
    data=std::unordered_map<std::string,std::string> ();
}

Link::~Link(){
  data.clear();
}

//void Link::checkDirection(bool invert){
//
//    if (invert!=inverted){
//        std::swap(a,b);
//        inverted=!inverted;
//    }
//
//}

void Link::copyProperties(Link* linkToCopyFrom){
    originalID=linkToCopyFrom->originalID;
    identifier=linkToCopyFrom->identifier;
    data=linkToCopyFrom->data;
    // labelsLevels.reserve(linkToCopyFrom->labelsLevels.size());
    // for(long i=0;i<linkToCopyFrom->labelsLevels.size();i++){
    //   labelsLevels.push_back(linkToCopyFrom->labelsLevels[i]);
    // }

}


Nodo* Link::commonNode(Link* other){
    if(a==other->a){
        return a;
    }else if(b==other->a){
        return b;
    }else if(a==other->b){
        return a;
    }else if(b==other->b){
        return b;
    }else{
        return NULL;
    }
}

Nodo* Link::getOtherNode(Nodo* node){
    if(a==node){
        return b;
    }else if(b==node){
        return a;
    }else{
        return NULL;
    }
}


Nodo* Link::A(){
    // if(inverted){
    //     return b;
    // }else{
        return a;
    // }
}

void Link::setA(Nodo* node){
    // if(inverted){
    //     b=node;
    // }else{
        a=node;
    // }
}
Nodo* Link::B(){
    // if(inverted){
    //     return a;
    // }else{
        return b;
    // }
}
void Link::setB(Nodo* node){
    // if(inverted){
    //     a=node;
    // }else{
        b=node;
    // }
}

// std::vector<std::string> Link::getDataVariableNames(long idLink){
//   std::vector<std::string> keys;
//   keys.reserve(this->data[idLink].size());
//   // std::vector<Val> vals;
//   // vals.reserve(map.size());
//
//   for(auto kv : this->data[idLink]) {
//       keys.push_back(kv.first);
//       // vals.push_back(kv.second);
//   }
//   return keys;
// }
// std::string Link::getData(long idLink,std::string tag){
//   return this->data[idLink][tag];
// }

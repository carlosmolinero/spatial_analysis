//
//  LinkPointerVector.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 29/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__LinkPointerVector__
#define __SpatialAnalysis__LinkPointerVector__

#include <stdio.h>
#include "LinkPointer.h"
#include <vector>

template<typename T>
class LinkPointerVector{
public:
    LinkPointerVector(){
        container.clear();
    }

    void push_back(T* object){
        LinkPointer<T> lp(object);
        container.push_back(lp);
    }
//    void push_back(T* object,bool invert){
//        LinkPointer<T> lp(object,invert);
//        container.push_back(lp);
//    }
    long size() const{
        return container.size();
    }
    void clear(){
        container.clear();
    }
    void reserve(long size){
        container.reserve(size);
    }
    void resize(long size){
        container.resize(size);
    }
    void operator = (const LinkPointerVector other){
        container=other.container;
    }
    T* operator [](long index){
        return container[index].getPointer();
    }
    //    void erase(typename std::vector<T>::iterator index){container.erase(index);}
    
    const T* operator [](long index) const{
        return container[index].getPointer();
    }
    
    LinkPointer<T> getLinkPointer(long i){
        return container[i];
    }
//    long getIndexInOriginalVector(long index){
//        return container[index].getIndex();
//    }
//    T getObject(long index){
//        return container[index];
//    }
private:
    std::vector<LinkPointer<T> > container;
};

#endif /* defined(__SpatialAnalysis__LinkPointerVector__) */

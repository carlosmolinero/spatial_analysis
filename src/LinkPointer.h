//
//  LinkPointer.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__LinkPointer__
#define __SpatialAnalysis__LinkPointer__

#include <stdio.h>


template<typename T>
class LinkPointer{
public:
    LinkPointer(T* link){
        this->pointer=link;
//        invert=false;
    }
//    LinkPointer(T* link,bool invert){
//        this->pointer=link;
////        this->invert=invert;
//    }
//    void setAsInverted(){
//        invert=true;
//    }
//    bool isInverted(){
//        return invert;
//    }
    bool operator==(T* other){
        return pointer==other;
    }
    bool operator==(LinkPointer other){
        return pointer==other.pointer;
    }
    void operator = (const LinkPointer other){
        pointer=other.pointer;
//        invert=other.invert;
        
    }
    T& operator*(){
//        pointer->checkDirection(invert);
        return *pointer;
    }
    T* operator->() {
//        pointer->checkDirection(invert);
        return pointer;
    }
    T* getPointer() const{
//        pointer->checkDirection(invert);
        return pointer;
    }
    const LinkPointer* getObject(){
        return this;
    }

private:
    T* pointer;
//    bool invert;

};

#endif /* defined(__SpatialAnalysis__LinkPointer__) */

//
//  Heap.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 16/02/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#ifndef __centralitiesPureCpp11__Heap__
#define __centralitiesPureCpp11__Heap__

#include <stdio.h>
#include <vector>
#include <iostream>
#include "CompareFunc.h"
#include <algorithm>
#include "Number.h"

//template<class T>
//class TNode
//{
//private:
//public:
////    unsigned long long id;
//    double value;
//    T object;
//    long index;
//};
//class HeapException: public std::exception
//{
//    virtual   char* what()   throw()
//    {
//        return "My exception happened";
//    }
//};

template<class T>
class Heap
{
public:
   
    static const int MIN=0;
    static const int MAX=1;
    static const int SIMPLE=0;
    static const int COMPLEX=1;
    int mode;
    int modeComparison;
    Heap();
    Heap(bool updatable);
    Heap(int mode,bool (*compare)(  T &a,T &b),double (*getValue)(T&),void (*setIndex)(T&,long,long),long (*getIndex)(  T&,long),bool updatable);
    Heap(int mode,bool (*compare)(  T &a,T &b),double (*getValue)(T&),void (*setIndex)(T&,long,long),long (*getIndex)(  T&,long),bool updatable,long indexOfTheHeap);
//    Heap(int mode,long indexDistance, long modeComparison);
    virtual ~Heap();
    void push(T &val);
    T pop();
    void update(T &val,double previousValue);
    T getRoot();
    long size();
    void print(bool popValues);
    void clear();
    void changeGetValueFunction(bool (*compare)(  T &a,T &b),double (*getValue)(T));
    void changeGetValueFunction(bool (*compare)(  T &a,T &b,int c),double (*getValue)(T&,int c),int indexInArray,int modeOfObjectComparison);

private:
    int indexInArray;
    bool updatable;
    long increment;
    long capacity;
    long sizeOfData;
    std::vector<T > data;
    void bubbleDown(long currentIndex);
    void bubbleUp(long currentIndex);
    double (*_getValue)(  T &val);
    double (*_getValueB)(  T &val,int c);
    bool (*_compare)(  T &a,T &b);
    bool (*_compareB)(  T &a,T &b,int c);
    void (*setIndex)(T &val,long index,long indexOfTheHeap);
    long (*getIndex)(  T &val,long indexOfTheHeap);
    double getValue(  T &val);
     bool compare(  T &a,  T &b);
     bool compare(T &a,double value);
    bool compare(double a,double b);
    bool isEmpty();
    long getLeftChildIndex(long nodeIndex);
    long getRightChildIndex(long nodeIndex);
    long getParentIndex(long nodeIndex);
    CompareFunc<T> compareObject;
    long indexOfIndexInHeap;
    
};




template<class T>
Heap<T>::Heap(){
    indexOfIndexInHeap=0;
    increment=0;
    this->updatable=false;
    if(updatable){
        data.reserve(increment);
    }
    capacity=increment;
    
    sizeOfData=0;
    this->mode=Heap::MIN;
    this->modeComparison=SIMPLE;
    this->_compare=Number::compare;
    this->setIndex=Number::setIndexInHeap;
    this->getIndex=Number::getIndexInHeap;
    this->_getValue=Number::getValue;
    
    if(!updatable){
        make_heap(data.begin(),data.end(),Number::compare);
    }
}


template<class T>
Heap<T>::Heap(bool updatable){
    indexOfIndexInHeap=0;
    increment=0;
    this->updatable=updatable;
    if(updatable){
        data.reserve(increment);
    }
    capacity=increment;
    
    sizeOfData=0;
    this->mode=Heap::MIN;
    this->modeComparison=SIMPLE;
    this->_compare=Number::compare;
    this->setIndex=Number::setIndexInHeap;
    this->getIndex=Number::getIndexInHeap;
    this->_getValue=Number::getValue;
    
    if(!updatable){
        make_heap(data.begin(),data.end(),Number::compare);
    }
}


template<class T>
Heap<T>::Heap(int mode,bool (*compare)(  T &a,T &b),double (*getValue)(T&),void (*setIndex)(T&,long,long),long (*getIndex)(  T&,long),bool updatable)
{
    indexOfIndexInHeap=0;
    increment=0;
    this->updatable=updatable;
    if(updatable){
        data.reserve(increment);
    }
    capacity=increment;

    sizeOfData=0;
    this->mode=mode;
    this->modeComparison=SIMPLE;
    this->_compare=compare;
    this->setIndex=setIndex;
    this->getIndex=getIndex;
    this->_getValue=getValue;

    if(!updatable){
        make_heap(data.begin(),data.end(),compare);
    }
    
}



template<class T>
Heap<T>::Heap(int mode,bool (*compare)(  T &a,T &b),double (*getValue)(T&),void (*setIndex)(T&,long,long),long (*getIndex)(  T&,long),bool updatable,long indexOfTheHeap)
{
    indexOfIndexInHeap=indexOfTheHeap;
    increment=0;
    this->updatable=updatable;
    if(updatable){
        data.reserve(increment);
    }
    capacity=increment;
    
    sizeOfData=0;
    this->mode=mode;
    this->modeComparison=SIMPLE;
    this->_compare=compare;
    this->setIndex=setIndex;
    this->getIndex=getIndex;
    this->_getValue=getValue;
    
    if(!updatable){
        make_heap(data.begin(),data.end(),compare);
    }
    
}


//template<class T>
//Heap<T>::Heap(int mode,long indexDistance, long modeComparison)
//{
//    this->mode=modeComparison;
//    this->extractId=extractId;
//    compareObject.set(indexDistance,mode);
//    this->modeGetValue=OBJECT;
//}
template<class T>
void Heap<T>::changeGetValueFunction(bool (*compare)(  T &a,T &b),double (*getValue)(T)){
    this->_getValue=getValue;
    this->_compare=compare;
    this->modeComparison=SIMPLE;
}
template<class T>
void Heap<T>::changeGetValueFunction(bool (*compare)(  T &a,T &b,int c),double (*getValue)(T&,int c),int indexInArray,int modeOfObjectComparison){
    compareObject.set(indexInArray,modeOfObjectComparison);
    this->modeComparison=COMPLEX;
    this->_getValueB=getValue;
    this->indexInArray=indexInArray;
    this->_compareB=compare;
    
}
template<class T>
Heap<T>::~Heap(){

}
template<class T>
void Heap<T>::clear(){
    data.clear();
    sizeOfData=0;
}
template<class T>
long Heap<T>::size(){
    if(!updatable){
        sizeOfData=data.size();
    }
    return sizeOfData;
}
template<class T>
double Heap<T>::getValue(  T &val){
    if(modeComparison==SIMPLE){
        return _getValue(val);
    }else{
        return _getValueB(val,indexInArray);
    }
}
template<class T>
void Heap<T>::push(T &val){
    if(updatable){
//        if(sizeOfData>=capacity-1){
//            data.reserve(capacity+increment);
//            capacity=data.capacity();
//        }
        setIndex(val,sizeOfData,indexOfIndexInHeap);
//        data[sizeOfData]=val;
        data.push_back(val);
        long currentIndex=sizeOfData;
        sizeOfData++;
//        setIndex(val,currentIndex);
        bubbleUp(currentIndex);
        
    }else{
        data.push_back(val);
        if(modeComparison==SIMPLE){
            push_heap(data.begin(), data.end(), _compare);
        }else{
            push_heap(data.begin(), data.end(), compareObject);
        }
    }
}
//template<class T>
//void Heap<T>::push(T &val,bool (*function)(T,T)){
//
////    if(updatable){
////        if(sizeOfData>=capacity-1){
////            data.resize(capacity+increment,NULL);
////            capacity=data.size();
////        }
////        setIndex(val,sizeOfData);
////        data[sizeOfData]=val;
////        bubbleUp(val);
////        sizeOfData++;
////    }else{
//        data.push_back(val);
//        push_heap(data.begin(), data.end(),function);
////    }
//}

template<class T>
void Heap<T>::print(bool popValues){
    if(!updatable){
        sizeOfData=data.size();
    }
//    std::cout<<"__________getMin()_________"<<'\n';
//    if(getRoot()!=NULL){
//        T node=getRoot();
//        std::cout<<" : "<<getValue(node)<<"-"<<'\n';
//    }
//    std::cout<<"__________data_________"<<'\n';
//    for(long i=0;i<sizeOfData;i++){
//        std::cout<<i<<" : "<<getValue(data[i])<<'\n';
//    }
    if(popValues){
        std::cout<<"__________popping_________"<<'\n';
        while(sizeOfData>0){
            T object=pop();
            std::cout<<getValue(object)<<'\n';
            if(!updatable){
                sizeOfData=data.size();
            }
        }
    }
    std::cout<<"___________________"<<'\n';
}
//template<class T>
//void Heap<T>::print(bool popValues,bool (*function)(T,T)){
////    if(!updatable){
////        sizeOfData=data.size();
////    }
////    std::cout<<"__________getMin()_________"<<'\n';
////    if(getRoot()!=NULL){
////        T node=getRoot();
////        std::cout<<" : "<<getValue(node)<<"-"<<'\n';
////    }
////    std::cout<<"__________data_________"<<'\n';
////    for(long i=0;i<sizeOfData;i++){
////        std::cout<<i<<" : "<<getValue(data[i])<<'\n';
////    }
////    if(popValues){
////        std::cout<<"__________popping_________"<<'\n';
////        while(sizeOfData>0){
////            T object=pop(function);
////            std::cout<<getValue(object)<<'\n';
////            if(!updatable){
////                sizeOfData=data.size();
////            }
////        }
////    }
////    std::cout<<"___________________"<<'\n';
//}
template <class T>
T Heap<T>::pop(){
    if(updatable){
        T object;
        if(sizeOfData>2){
            object=data[0];
            
            std::swap(data[0],data[sizeOfData-1]);
            setIndex(data[0],0,indexOfIndexInHeap);
            sizeOfData--;
            data.pop_back();
            bubbleDown(0);
        }else if (sizeOfData==2){
            object=data[0];
            
            std::swap(data[0],data[sizeOfData-1]);
            setIndex(data[0],0,indexOfIndexInHeap);
            sizeOfData--;
            data.pop_back();
        }else if (sizeOfData==1){
            object=data[0];
            data.pop_back();
            sizeOfData--;
        }else{
            return NULL;
        }
        setIndex(object,-1,indexOfIndexInHeap);
        return object;
    }else{
        T val;
        if (data.size()>0){
            val = data.front();
            if(modeComparison==SIMPLE){
                pop_heap(data.begin(), data.end(), _compare);
            }else{
                pop_heap(data.begin(), data.end(), compareObject);
            }
            data.pop_back();
        }else{
            val=NULL;
        }        
        return val;
    }
}
//template <class T>
//T Heap<T>::pop(bool (*function)(T,T)){
//    if(updatable){
//        T object;
//        if(sizeOfData>0){
//            object=data[0];
//        std::swap(data[0],data[sizeOfData-1]);
//            setIndex(data[0],0);
//            sizeOfData--;
//            bubbleDown(data[0]);
//        }else{
//            return NULL;
//        }
//        return object;
//    }else{
//        T val;
//        if (data.size()>0){
//            val = data.front();
//            pop_heap(data.begin(), data.end(), function);
//            data.pop_back();
//        }else{
//            val=NULL;
//        }
//        return val;
//    }
//}
template<class T>
void Heap<T>::update(T &val,double previousValue){
    if(updatable){
        double currentValue=getValue(val);
        long currentIndex = getIndex(val,indexOfIndexInHeap);
        if(currentValue!=previousValue){
            if(!compare(currentValue,previousValue)){
                bubbleDown(currentIndex);
            }else{
                bubbleUp(currentIndex);
            }
        }
    }else{
        double currentValue=getValue(val);
        
        if(currentValue!=previousValue){
            if(modeComparison==SIMPLE){
                make_heap(data.begin(),data.end(),_compare);
            }else{
                make_heap(data.begin(),data.end(),compareObject);
            }
        }
    }

}
//template<class T>
//void Heap<T>::update(T &val,double previousValue,bool (*function)(T,T)){
//    if(updatable){
//        double currentValue=getValue(val);
//        
//        if(currentValue!=previousValue){
//            if(!compare(val,previousValue)){
//                bubbleDown(val);
//            }else{
//                bubbleUp(val);
//            }
//        }
//    }else{
//        make_heap(data.begin(),data.end(),function);
//    }
//    
//}
template<class T>
T Heap<T>::getRoot() {
    if (isEmpty()){

            return NULL;

    }else{
        return data[0];
    }
}
template<class T>
bool Heap<T>::isEmpty() {
    if(!updatable){
        sizeOfData=data.size();
    }
    return (sizeOfData == 0);
}

template<class T>
long Heap<T>::getLeftChildIndex(long nodeIndex) {
    return 2 * nodeIndex + 1;
}
template<class T>
long Heap<T>::getRightChildIndex(long nodeIndex) {
    return 2 * nodeIndex + 2;
}
template<class T>
long Heap<T>::getParentIndex(long nodeIndex) {
    return (nodeIndex - 1) / 2;
}
template<class T>
bool Heap<T>::compare(  T &a,  T &b){
    if(modeComparison==SIMPLE){
        if(mode==MIN){
            return !(_compare(a,b));
        }else {
            return (_compare(a,b));
        }
    }else{
        if(mode==MIN){
            return !(_compareB(a,b,indexInArray));
        }else {
            return (_compareB(a,b,indexInArray));
        }
    }

}
template<class T>
bool Heap<T>::compare(T &a,double value){
    if(mode==MIN){
        return getValue(a)<value;
    }else{
        return getValue(a)>value;
    }
}
template<class T>
bool Heap<T>::compare(double a,double b){
    if(mode==MIN){
        return a<b;
    }else{
        return a>b;
    }
}

template<class T>
void Heap<T>::bubbleUp(long currentIndex){
    
    long parentIndex = (currentIndex - 1) / 2;
    while (currentIndex > 0) 
    {
      
            if (currentIndex>0&&compare(data[currentIndex],data[parentIndex]))
            {
                setIndex(data[currentIndex],parentIndex,indexOfIndexInHeap);
                setIndex(data[parentIndex],currentIndex,indexOfIndexInHeap);

                std::swap(data[currentIndex],data[parentIndex]);

                currentIndex=parentIndex;
                parentIndex = (currentIndex - 1) / 2;

                
            } else {

               break;
            }
        
    }

}
template<class T>
void Heap<T>::bubbleDown(long currentIndex){
   
//    long leftChildIndex = 2 * currentIndex + 1;
    long rightChildIndex=2 * currentIndex + 2;
    long childIndex=2 * currentIndex + 1;
    while (childIndex < sizeOfData) {
        if(rightChildIndex<sizeOfData){
            if (!compare(data[childIndex],data[rightChildIndex])){
                childIndex=rightChildIndex;
            }
        }
      
            if (childIndex<sizeOfData&&!compare(data[currentIndex],data[childIndex])) {
                setIndex(data[currentIndex],childIndex,indexOfIndexInHeap);
                setIndex(data[childIndex],currentIndex,indexOfIndexInHeap);
                std::swap(data[currentIndex],data[childIndex]);
                currentIndex=childIndex;
                childIndex = 2 * currentIndex + 1;
                rightChildIndex=2 * currentIndex + 2;
            } else {
                break;
            }
        
    }

}



#endif /* defined(__centralitiesPureCpp11__Heap__) */

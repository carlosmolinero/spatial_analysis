#ifndef MINHEAP_H
#define MINHEAP_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
//class CompareFunc;
#include "CompareFunc.h"

template<class T>
class MinHeap
{
    public:
        MinHeap& operator=(const MinHeap& heapTemp);
        std::vector<T> heap;
        MinHeap();
        virtual ~MinHeap();
        void push(T &val,bool (*function)(T&,T&));
        void push(T &val,CompareFunc<T> &compare);
        T pop(bool (*function)(T&,T&));
        T pop(CompareFunc<T> &compare);
    T getMin(bool (*function)(T&,T&));
    T getMin(CompareFunc<T> &compare);
        long size();
        T& get(long index);
        void buildHeap(bool (*function)(T&,T&));
        void buildHeap(CompareFunc<T> &compare);
        void clear();
        void remove();
        void print(double (*function)(T));
        void erase(long index,bool (*function)(T&,T&));
        void erase(long index,CompareFunc<T> &compare);
    protected:
    private:
};

template<class T>
MinHeap<T>::MinHeap()
{
    //ctor
//    std::vector<T>& heap;
}
template<class T>
MinHeap<T>::~MinHeap()
{
    //dtor
    heap.clear();
    std::vector<T>(heap).swap(heap);
}
template<class T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap& heapTemp){
    *this=heapTemp;
    return *this;
}
template<class T>
void MinHeap<T>::push(T &val,bool (*function)(T&,T&)) {
    heap.push_back(val);
    push_heap(heap.begin(), heap.end(), function);
}
template<class T>
void MinHeap<T>::push(T &val,CompareFunc<T> &compare) {
    heap.push_back(val);
    push_heap(heap.begin(), heap.end(), compare);
}
template<class T>
void MinHeap<T>::erase(long index,bool (*function)(T&,T&)) {
    heap.erase(heap.begin()+index);
    make_heap(heap.begin(),heap.end(),function);
}
template<class T>
void MinHeap<T>::buildHeap(bool (*function)(T&,T&)) {
    make_heap(heap.begin(),heap.end(),function);
}
template<class T>
void MinHeap<T>::buildHeap(CompareFunc<T> &compare) {
    make_heap(heap.begin(),heap.end(),compare);
}
template<class T>
void MinHeap<T>::erase(long index,CompareFunc<T> &compare) {
    heap.erase(heap.begin()+index);
    make_heap(heap.begin(),heap.end(),compare);
}

template<class T>
T MinHeap<T>::pop(bool (*function)(T&,T&)) {
    T val;
    if (heap.size()>0){
       val = heap.front();
        pop_heap(heap.begin(), heap.end(), function);
        
        
        //Remove the last element from vector, which is the smallest element
        heap.pop_back();
    }else{
        val=NULL;
    }
    //This operation will move the smallest element to the end of the vector

    return val;
}
template<class T>
T MinHeap<T>::pop(CompareFunc<T> &compare) {
    T val;
    if (heap.size()>0){
       val = heap.front();
        pop_heap(heap.begin(), heap.end(), compare);
        
        
        //Remove the last element from vector, which is the smallest element
        heap.pop_back();
    }else{
        val=NULL;
    }
    return val;
}


template<class T>
T MinHeap<T>::getMin(bool (*function)(T&,T&)) {
    T val;
    if (heap.size()>0){
//        pop_heap(heap.begin(), heap.end(), function);
        val = heap.front();
//        pop_heap(heap.begin(), heap.end(), function);
        
        
        //Remove the last element from vector, which is the smallest element
//        heap.pop_back();
    }else{
        val=NULL;
    }
    //This operation will move the smallest element to the end of the vector
    
    return val;
}
template<class T>
T MinHeap<T>::getMin(CompareFunc<T> &compare) {
    T val;
    if (heap.size()>0){
        val = heap.front();
//        pop_heap(heap.begin(), heap.end(), compare);
        
        
        //Remove the last element from vector, which is the smallest element
//        heap.pop_back();
    }else{
        val=NULL;
    }
    return val;
}


template<class T>
long MinHeap<T>::size(){
    return (heap.size());
}

template<class T>
T& MinHeap<T>::get(long index){
    return (heap[index]);
}
template<class T>
void MinHeap<T>::clear(){
    heap.clear();
}
template<class T>
void MinHeap<T>::print(double (*function)(T)){
    for (int i=0;i<heap.size();i++){
        std::cout<<function(heap[i])<<'\n';
    }
}
template<class T>
void MinHeap<T>::remove(){
    heap.clear();
    std::vector<T>().swap(heap);
}


#endif // MINHEAP_H

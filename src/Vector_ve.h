//
//  Vector_ve.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 02/06/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#ifndef __centralitiesPureCpp11__Vector_ve__
#define __centralitiesPureCpp11__Vector_ve__


#include <stdio.h>
#include <vector>
#include "Vector_elem.h"


template<typename T>
class Vector_ve
{
public:
    Vector_ve()
    { }
    
//    bool operator==(T& other) { return &m_container[m_element_index]==other; }
//    T& operator*() { return m_container[m_element_index]; }
//    T* operator->() { return &m_container[m_element_index]; }
    void push_back(Vector_elem<T> object){
        container.push_back(object);
    }
    long size() const{return container.size();}
    void clear(){container.clear();}

    T* operator [](long index){return container[index].getPointer();}
//    void erase(typename std::vector<T>::iterator index){container.erase(index);}
//    typename std::vector<T>::iterator begin(){return container.begin();}
    const T* operator [](long index) const{return container[index].getPointer();}
    long getIndexInOriginalVector(long index){
        return container[index].getIndex();
    }
    Vector_elem<T> getObject(long index){
        return container[index];
    }
private:
    std::vector<Vector_elem<T> > container;
    
//    std::size_t m_element_index;
};

#endif /* defined(__centralitiesPureCpp11__Vector_ve__) */

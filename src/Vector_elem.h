//
//  Vector_elem.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 02/06/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
// modification of a code found in http://stackoverflow.com/questions/19138805/keeping-track-of-vector-elements-adresses

#ifndef __centralitiesPureCpp11__Vector_elem__
#define __centralitiesPureCpp11__Vector_elem__

#include <stdio.h>
#include <vector>


template<typename T>
class Vector_elem
{
public:
    Vector_elem( std::vector<T>& v )
    : m_container( v ), m_element_index(v.size()-1)
    {
        invert=false;
    }
    Vector_elem( std::vector<T>& v,long index,bool invert)
    : m_container( v ), m_element_index(index)
    {
        this->invert=invert;
        if(invert){
            v[index].bidirectional=true;
        }
    }
    Vector_elem( std::vector<T>& v,long index )
    : m_container( v ), m_element_index(index)
    {
        invert=true;
        v[index].bidirectional=true;
    }
    void setInverted(){invert=true;}
    bool operator==(T& other) { return &m_container[m_element_index]==other; }
    void operator = (const Vector_elem& other){
        m_container=(other.m_container);
        m_element_index=other.m_element_index;
        invert=other.invert;
    
    }
    T& operator*() { return m_container[m_element_index]; }
    T* operator->() { return &m_container[m_element_index]; }
    T* getPointer() const{
        m_container[m_element_index].checkDirection(invert);
        return &m_container[m_element_index]; }
    long getIndex(){return m_element_index;}
private:
    std::vector<T>& m_container;
    long m_element_index;
    bool invert;
};

#endif /* defined(__centralitiesPureCpp11__Vector_elem__) */
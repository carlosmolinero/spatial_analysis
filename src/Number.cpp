//
//  Number.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 19/09/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Number.h"
 double Number::getValue( Number* &a){
    return a->value;
}
 bool Number::compare(Number* &a,Number* &b){
    return (a->value>b->value);
}
 void Number::setIndexInHeap(Number* &number,long index,long indexOfTheHeap){
//    while(indexOfTheHeap>=number->indexInHeap.size()){
//        number->indexInHeap.push_back(-1);
//    }
//    number->indexInHeap[indexOfTheHeap]=index;
     number->indexInHeap=index;
}
 long Number::getIndexInHeap( Number* &number,long indexOfTheHeap){
//     return (number->indexInHeap[indexOfTheHeap]);
     return number->indexInHeap;
}

void Number::operator =(double value){
    this->value=value;
}

bool Number::operator < ( const Number& s ) const{
    return this->value<s.value;
}
bool Number::operator < ( const Number* s ) const{
    return this->value<s->value;
}
bool Number::operator > ( const Number& s ) const{
    return this->value>s.value;
}
bool Number::operator == ( const Number& s ) const{
    return this->value==s.value;
}
bool Number::operator >= ( const Number& s ) const{
    return this->value>=s.value;
}
bool Number::operator <= ( const Number& s ) const{
    return this->value<=s.value;
}
bool Number::operator()(const Number* comp1, const Number* comp2) const {
    return comp1->value < comp2->value;
}
bool Number::operator()(const Number &comp1, const Number &comp2) const {
    return comp1.value < comp2.value;
}

//Proxy getValue(){
//    return Proxy();
//}
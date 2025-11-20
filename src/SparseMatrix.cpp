//
//  SparseMatrix.cpp
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 04/10/2014.
//  Copyright (c) 2014 UCL. All rights reserved.
//

#include "SparseMatrix.h"


//template <class T>
SparseMatrix::SparseMatrix()
{
    bidirectional=false;
    NULL_.value=0;
    NULL_.id=-1;

}

//template <class T>
long SparseMatrix::size(){
  return cells.size();
}

//template <class T>
void SparseMatrix::set(long col,long row,Number value)
{

    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    cells[Point2d(col,row)]=value;

}
void SparseMatrix::setId(long col,long row,long value)
{

    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    cells[Point2d(col,row)].id=value;

}
void SparseMatrix::setId(double col,double row,long value)
{

    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    cells[Point2d(col,row)].id=value;

}
void SparseMatrix::setValue(long col,long row,double value)
{

    if(bidirectional)
    {
        if(row>col)
        {
            double colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    cells[Point2d(col,row)].value=value;

}
void SparseMatrix::setValue(double col,double row,double value)
{

    if(bidirectional)
    {
        if(row>col)
        {
            double colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    cells[Point2d(col,row)].value=value;

}
void SparseMatrix::increase(long col,long row)
{

    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        Number number;
        number.value=1;
        set(col,row,number);
    }else{
        cells[Point2d(col,row)].value++;
    }

}
void SparseMatrix::increase(double col,double row)
{

    if(bidirectional)
    {
        if(row>col)
        {
            double colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        Number number;
        number.value=1;
        set(col,row,number);
    }else{
        cells[Point2d(col,row)].value++;
    }

}
void SparseMatrix::increaseBy(long col,long row,double increaseFactor){
    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        Number number;
        number.value=increaseFactor;
        set(col,row,number);
    }else{
        cells[Point2d(col,row)].value+=increaseFactor;
    }
}
void SparseMatrix::increaseBy(double col,double row,double increaseFactor){
    if(bidirectional)
    {
        if(row>col)
        {
            double colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        Number number;
        number.value=increaseFactor;
        set(col,row,number);
    }else{
        cells[Point2d(col,row)].value+=increaseFactor;
    }
}
void SparseMatrix::set_NULL_Value(double NULL_){
    this->NULL_.value=NULL_;
}

//template <class T>
double SparseMatrix::getValue(long col,long row)
{
    //    col=col+1;
    //    long index=row*module+col;
    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        return NULL_.value;
    }else{
        //    double value=;
        return cells[Point2d(col,row)].value;
    }
}
double SparseMatrix::getValue(double col,double row)
{
    //    col=col+1;
    //    long index=row*module+col;
    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        return NULL_.value;
    }else{
        //    double value=;
        return cells[Point2d(col,row)].value;
    }
}
long SparseMatrix::getId(long col,long row)
{
    //    col=col+1;
    //    long index=row*module+col;
    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        return NULL_.id;
    }else{
        //    double value=;
        return cells[Point2d(col,row)].id;
    }
}
long SparseMatrix::getId(double col,double row)
{
    //    col=col+1;
    //    long index=row*module+col;
    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }

    if(cells.find(Point2d(col,row))==cells.end()){
        return NULL_.id;
    }else{
        //    double value=;
        return cells[Point2d(col,row)].id;
    }
}

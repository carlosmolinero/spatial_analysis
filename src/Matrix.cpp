//
//  Matrix.cpp
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 04/10/2014.
//  Copyright (c) 2014 UCL. All rights reserved.
//

#include "Matrix.h"
Matrix::Matrix()
{
    bidirectional=false;
}

void Matrix::init(long numCol,long numRow)
{
    values.resize(numCol*numRow,-1);
    module=numCol;
}

void Matrix::set(float value,long col,long row)
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
    long index=row*module+col;
    values[index]=value;
}
//void Matrix::add(Node* node,long col,long row)
//{
//    if(bidirectional)
//    {
//        if(row>col)
//        {
//            long colTemp=col;
//            col=row;
//            row=colTemp;
//        }
//    }
//    long index=row*module+col;
//    nodes[index].push_back(node);
//}
float Matrix::get(long col,long row)
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
    long index=row*module+col;
    return values[index];
}

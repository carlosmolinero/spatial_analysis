//
//  CA.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 28/01/2016.
//  Copyright (c) 2016 UCL. All rights reserved.
//

#include "CA.h"

CA::CA()
{
    bidirectional=false;
    //    values.resize(0,BST<float>());
    
}
void CA::init(long numCol,long numRow)
{
    //    values.resize(numRow,BST<double>());
    //    values.resize(numRow,std::unordered_map<long, double>());
    //    for(long i=0;i<numRow;i++){
    //        values[i].add(i,0);
    //    }
    module=numCol;
    for(long i=0;i<numCol*numRow;i++){
        CellCA cell;
        cells.push_back(cell);
    }
    
}







//void CA::set(double value,long col,long row)
//{
//    //    col=col+1;
//    long index=row*module+col;
//    if(bidirectional)
//    {
//        if(row>col)
//        {
//            long colTemp=col;
//            col=row;
//            row=colTemp;
//        }
//    }
//    //    values[row].add(col, value);
//    values[index]=value+1;
//    //    [col]=value;
//}



//void CA::set(CellCA* cell,long col,long row)
//{
//    //    col=col+1;
//    long index=row*module+col;
//    if(bidirectional)
//    {
//        if(row>col)
//        {
//            long colTemp=col;
//            col=row;
//            row=colTemp;
//        }
//    }
//    //    values[row].add(col, value);
//    cells[index]=(cell);
//    //    [col]=value;
//}


CellCA* CA::get(long col,long row)
{
    //    col=col+1;
    long index=row*module+col;
    if(bidirectional)
    {
        if(row>col)
        {
            long colTemp=col;
            col=row;
            row=colTemp;
        }
    }
    
    //    if(values.find(index)==values.end()){
    //        return -1;
    //    }else{
    return &cells[index];
    
    //    }
}




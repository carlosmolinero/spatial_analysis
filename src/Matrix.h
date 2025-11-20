//
//  Matrix.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 04/10/2014.
//  Copyright (c) 2014 UCL. All rights reserved.
//

#ifndef __centralitiesPureCpp11__Matrix__
#define __centralitiesPureCpp11__Matrix__

#include <stdio.h>
#include<vector>
//#include "Node.h"

class Matrix
{
public:
    Matrix();
    long module;
    std::vector<float> values;
//    std::vector<std::vector<Node*> > nodes;
    void init(long numCol,long numRow);
    bool bidirectional;
    void set(float value,long col,long row);
//    void add(Node* node,long col,long row);
    float get(long col,long row);
};
#endif /* defined(__centralitiesPureCpp11__Matrix__) */

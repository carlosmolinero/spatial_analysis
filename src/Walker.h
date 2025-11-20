//
//  Walker.h
//  harmonicCities
//
//  Created by Carlos Molinero on 13/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#ifndef __harmonicCities__Walker__
#define __harmonicCities__Walker__

#include <stdio.h>
#include "Node.h"
#include "PotentialField.h"
#include "QTree.h"
#include "Point2d.h"
#include "ClusterField.h"
#include "Functions.h"
#include "Heap.h"
#include "Graph.h"

class Walker{
public:
    Node* previousCity;
    Node* walk(PotentialField &potentialField,QTree &quadTree,Node* objective);
    Point2d location;
};


#endif /* defined(__harmonicCities__Walker__) */

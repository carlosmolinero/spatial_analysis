//
//  TransitionCluster.h
//  centralitiesPureCpp11
//
//  Created by Carlos Molinero on 02/10/2014.
//  Copyright (c) 2014 UCL. All rights reserved.
//

#ifndef __centralitiesPureCpp11__TransitionCluster__
#define __centralitiesPureCpp11__TransitionCluster__

#include <stdio.h>

class ClusterQTree;
class TransitionCluster
{
public:
    ClusterQTree* a;
    ClusterQTree* b;
    long id;
    long oppositeTransitionId;
    TransitionCluster();

};

#endif /* defined(__centralitiesPureCpp11__TransitionCluster__) */

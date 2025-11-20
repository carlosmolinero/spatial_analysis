//
//  InterfaceFlows.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 08/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__InterfaceFlows__
#define __SpatialAnalysis__InterfaceFlows__

#include <stdio.h>
#include <iostream>
#include <deque>
#include <vector>
#include <unordered_map>
#include <cmath>

class InterfaceFlows{
public:
    int subdivisionsDistance;    
    InterfaceFlows();
    // void setDistances(double maxDistance);
    void setDistances(std::vector<double> distances);
    // void setNumberSubdivisions(int numberSubdivisionsPerDistance);
    std::vector<double> distancesTrips;
    std::vector<std::vector<double> >flows;
    std::vector<std::unordered_map<long,double> > valuesToPass;
    std::vector<double> getFlows(long indexDistance);
    void initFlows(long numberLinks);
    void initValuesToPass(long numberNodes);
    void accumulateFlow(long idLink,long idNode);
    void passValuesToParent(long idNode,long idParent);
    void resetValuesToPass();
    void setValuesToPass( long idNode,double distance, double value);
    long getIndexOfDistance(double distance);
private:


};

#endif /* defined(__SpatialAnalysis__InterfaceFlows__) */

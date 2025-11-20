//
//  Data.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 06/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__Data__
#define __SpatialAnalysis__Data__

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Link.h"

class Data{
public:
    Data();
    static const int DISTANCE=0;
    static const int FLOW=1;
    static const int MODIFIER=2;

    std::unordered_map<long,std::vector<double> >  dataByOriginalId;
    std::vector<std::string> names;
    std::vector<int> types;
    // std::vector<std::unordered_map<std::string,std::string> > tags;

    long size();
    void split(long &initialID,std::vector<long> &newIds,std::vector<double> &percentages);
    void combine(std::vector<long> &oldIds,long &newID);
    void collapse(std::vector<long> &oldIds,long &newID);
    void insert(std::string &name,std::vector<long> &ids,std::vector<double> &values);
    void insert(std::string &name,int type,std::vector<long> &ids,std::vector<double> &values);
//    void load(std::string &name,int type,std::string &fileName,std::string &separator,bool header);
    void modifyType(std::string &name,int type);
    double getData(long &ID,std::string &name);
    std::vector<double> getData(std::vector<Link*> &links,std::string &name);
    void remove(std::vector<long> &linksRemoved);
    // std::vector<std::string> getTagNames(long idLink);
    // std::string getTag(long idLink,std::string tag);

};

#endif /* defined(__SpatialAnalysis__Data__) */

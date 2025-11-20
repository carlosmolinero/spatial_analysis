//
//  Data.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 06/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "Data.h"

Data::Data(){
  // tags=std::vector<std::unordered_map<std::string,std::string> >();
}

long Data::size(){
    return dataByOriginalId.size();
}

void Data::split(long &initialID,std::vector<long> &newIds,std::vector<double> &percentages){

    std::vector<double> completeData=dataByOriginalId[initialID];
    dataByOriginalId.erase(initialID);
    if(names.size()>0){

        for(long i=0;i<newIds.size();i++){
            std::vector<double> newData;
            newData.resize(completeData.size());
            for(long k=0;k<names.size();k++){


                    int type=types[k];

                        if(type==DISTANCE){
                            newData[k]=completeData[k]*percentages[i];
                        }
                        if(type==FLOW){
                            newData[k]=completeData[k];
                        }
                        if(type==MODIFIER){
                            newData[k]=completeData[k];
                        }




            }
            dataByOriginalId[newIds[i]]=newData;
        }

    }


}

void Data::remove(std::vector<long> &linksRemoved){
    for(long i=0;i<linksRemoved.size();i++){

        dataByOriginalId.erase(linksRemoved[i]);
    }
}
void Data::combine(std::vector<long> &oldIds,long &newID){


    std::vector<std::vector<double> > completeValues;
    for(long i=0;i<oldIds.size();i++){
        completeValues.push_back(dataByOriginalId[oldIds[i]]);

        dataByOriginalId.erase(oldIds[i]);
    }

    if(names.size()>0){
        std::vector<double> newData;


        newData.resize(names.size(),0.0);

         for(long i=0;i<oldIds.size();i++){
            std::vector<double>  currentData=completeValues[i];
            for(long k=0;k<names.size();k++){

                int type=types[k];

                if(type==DISTANCE){
                    newData[k]+=currentData[k];
                }
                if(type==FLOW){
                    newData[k]+=currentData[k]/(double)(currentData.size());
                }
                if(type==MODIFIER){
                    newData[k]=currentData[k];
                }

            }

        }
        dataByOriginalId[newID]=newData;
    }


}

void Data::collapse(std::vector<long> &oldIds,long &newID){
    std::cout<<"Not implemented collapse data"<<'\n';
}

void Data::insert(std::string &name,std::vector<long> &ids,std::vector<double> &values){

    for(long i=0;i<ids.size();i++){

        dataByOriginalId[ids[i]].push_back(values[i]);
    }
    names.push_back(name);
    types.push_back(0);
}
void Data::insert(std::string &name,int type,std::vector<long> &ids,std::vector<double> &values){
    for(long i=0;i<ids.size();i++){
        dataByOriginalId[ids[i]].push_back(values[i]);
    }
    names.push_back(name);
    types.push_back(type);
}

//void Data::load(std::string &name,int type,std::string &fileName,std::string &separator,bool header){
//    std::vector<std::string> ids;
//    std::vector<std::string> columnNames;
//    std::vector<std::vector<double> > values;
//    TextFile::loadData(ids, columnNames, values, fileName, separator, header);
//    long currentNumberData=names.size();
//    if(columnNames.size()>0){
//        for(long i=0;i<columnNames.size();i++){
//            names.push_back(columnNames[i]);
//            types.push_back(type);
//
//        }
//        for(long i=0;i<columnNames.size();i++){
//            for(long j=0;j<ids.size();j++){
//                dataByOriginalId[ids[j]].push_back(values[i][j]);
//            }
//        }
//    }else{
//        for(long i=0;i<values.size();i++){
//            std::stringstream ss;
//            ss<<i+currentNumberData;
//            names.push_back(ss.str());
//            types.push_back(type);
//        }
//        for(long i=0;i<values.size();i++){
//            for(long j=0;j<ids.size();j++){
//                dataByOriginalId[ids[j]].push_back(values[i][j]);
//            }
//        }
//    }
//
//
//}
void Data::modifyType(std::string &name,int type){
    for(long i=0;i<names.size();i++){
        if(names[i]==name){
            types[i]=type;
        }
    }
}


double Data::getData(long &ID,std::string &name){
    long index=-1;
    for(long i=0;i<names.size();i++){
        if(names[i]==name){
            index=i;
        }
    }
    if(index==-1){
        return 0.0;
    }else{
        return dataByOriginalId[ID][index];
    }
}

std::vector<double> Data::getData(std::vector<Link*> &links,std::string &name){
    long index=-1;
    std::vector<double> values;
    for(long i=0;i<names.size();i++){
        if(names[i]==name){
            index=i;
        }
    }
    if(index==-1){
        return values;
    }else{
        for(long i=0;i<links.size();i++){
            values.push_back(dataByOriginalId[links[i]->originalID][index]);
        }
        return values;
    }

}

// std::vector<std::string> Data::getTagNames(long idLink){
//   std::vector<std::string> keys;
//   keys.reserve(this->tags[idLink].size());
//   // std::vector<Val> vals;
//   // vals.reserve(map.size());
//
//   for(auto kv : this->tags[idLink]) {
//       keys.push_back(kv.first);
//       // vals.push_back(kv.second);
//   }
//   return keys;
//
// }
// std::string Data::getTag(long idLink,std::string tag){
//   return this->tags[idLink][tag];
// }

//
//  LargeGraph.cpp
//  spatialTools
//
//  Created by Carlos Molinero on 04/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "LargeGraph.h"

LargeGraph::LargeGraph(){
    bidirectional=false;
    n=0;
    m=0;
}

void LargeGraph::create(LargeGraph* G,std::vector<std::vector<double> > ncol,std::vector<std::vector<double> > coordinates,bool directed){
    long n=coordinates[0].size();
//    long m=ncol.size();
    G->nodes.resize(n);
    G->n=n;
    for(long i=0;i<coordinates[0].size();i++){
        G->nodes[i].id=i;
        G->nodes[i].originalID=coordinates[0][i];
        G->nodes[i].location=Point2d(coordinates[1][i],coordinates[2][i]);
    }
    G->m=0;
    for(long i=0;i<ncol[0].size();i++){
        if(ncol[1][i]!=ncol[0][i]){
            G->nodes[ncol[0][i]].idsNeighbors.push_back(ncol[1][i]);
            G->nodes[ncol[0][i]].weights.push_back(ncol[2][i]);
            G->m++;
        }
        
    }
    
    if(!directed){
        transformToBidirectional(G);
    }
}

void LargeGraph::transformToBidirectional(LargeGraph* G){
    G->bidirectional=true;
    std::vector<std::unordered_map<long, long> > indexNeighborsPerId;
    indexNeighborsPerId.resize(G->nodes.size());
    for(long i=0;i<G->nodes.size();i++){
        for(long j=0;j<G->nodes[i].idsNeighbors.size();j++){
            indexNeighborsPerId[i][G->nodes[i].idsNeighbors[j]]=j+1;
        }
    }
    for(long i=0;i<G->nodes.size();i++){
        for(long j=0;j<G->nodes[i].idsNeighbors.size();j++){
            if(indexNeighborsPerId[G->nodes[i].idsNeighbors[j]][i]==0){
                G->m++;
                indexNeighborsPerId[G->nodes[i].idsNeighbors[j]][i]=(G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size()-1)+1;
                G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.push_back(i);
                G->nodes[G->nodes[i].idsNeighbors[j]].weights.push_back(G->nodes[i].weights[j]);
                
            }else{
                long index=indexNeighborsPerId[G->nodes[i].idsNeighbors[j]][i]-1;
                double weight=Functions::min(G->nodes[i].weights[j], G->nodes[G->nodes[i].idsNeighbors[j]].weights[index]);
                G->nodes[i].weights[j]=weight;
                G->nodes[G->nodes[i].idsNeighbors[j]].weights[index]=weight;
            }
        }
    }
}


void LargeGraph::removeNodesDegree2(LargeGraph* G){
    std::vector<bool> isVisited;
    isVisited.resize(G->nodes.size(),false);
    for(long i=0;i<G->nodes.size();i++){
        if(G->nodes[i].idsNeighbors.size()!=2){
            isVisited[i]=true;
            long previousId=i;
            for(long j=0;j<G->nodes[i].idsNeighbors.size();j++){
                long subCounter=0;
//                std::cout<<"pI "<<previousId<<" j "<<j<<" size neighbors "<<G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size()<<'\n';
                if(G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size()==2){
//                    std::cout<<i<<'\n';
                    bool collapsed=false;
                    isVisited[G->nodes[i].idsNeighbors[j]]=true;
                    for(long h=0;h<G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size();h++){
                        if(!isVisited[G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[h]]||(G->nodes[G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[h]].idsNeighbors.size()!=2&&((G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[h]!=i)||subCounter>0))){
                            
                            
//                            else{
                            if(G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size()==2){
                                previousId=G->nodes[i].idsNeighbors[j];
                                
                                G->nodes[i].idsNeighbors[j]=G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[h];
                                G->nodes[i].weights[j]+=G->nodes[G->nodes[i].idsNeighbors[j]].weights[h];
                                subCounter++;
                                collapsed=true;
                            }
                            
                        }
                    }
                    if(collapsed){
                        j--;
                    }
                }else{
//                    if(G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size()!=2){
                        //                                G->nodes[i].idsNeighbors[j]=G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[h];
                        //                                G->nodes[i].weights[j]+=G->nodes[G->nodes[i].idsNeighbors[j]].weights[h];
//                        collapsed=false;
                        for(long k=0;k<G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size();k++){
                            if(G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[k]==previousId){
                                G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors[k]=i;
                                G->nodes[G->nodes[i].idsNeighbors[j]].weights[k]=G->nodes[i].weights[j];
//                                collapsed=true;
                            }
                        }
                        subCounter=0;
                        
//                    }
                }
            }
        }
    }
    
    
    
    
    
    ///correct ids
    long id=0;
    long numberNodes_new=0;
    for(long i=0;i<G->nodes.size();i++){
        if(G->nodes[i].idsNeighbors.size()!=2){
            G->nodes[i].id=id;
            id++;
            numberNodes_new++;
        }else{
//            G->nodes[i].id=-1;
        }
    }
    id=0;
    G->n=numberNodes_new;
    G->m=0;
    std::vector<Node_LG> newNodes(numberNodes_new);
    for(long i=0;i<G->nodes.size();i++){
        if(G->nodes[i].idsNeighbors.size()!=2){
            newNodes[id]=G->nodes[i];
            for(long j=0;j<G->nodes[i].idsNeighbors.size();j++){
                G->m++;
                //                if(result->nodes[result->nodes[i].idsNeighbors[j]].id!=result->nodes[i].idsNeighbors[j]){
                newNodes[id].idsNeighbors[j]=G->nodes[G->nodes[i].idsNeighbors[j]].id;
                if(G->nodes[G->nodes[i].idsNeighbors[j]].idsNeighbors.size()==2){
                    std::cout<<"there is an issue here, i "<<i<<" j "<<j<<'\n';
                }
                //                }
            }
            
            id++;
        }
    }
    G->nodes=newNodes;
    
}
void LargeGraph::removeNodesDegree2(LargeGraph* G,LargeGraph* result){
    result->nodes=G->nodes;
    result->n=G->n;
    result->m=G->m;
    result->bidirectional=G->bidirectional;
    
    std::vector<bool> isVisited;
    isVisited.resize(result->nodes.size(),false);
    for(long i=0;i<result->nodes.size();i++){
        if(result->nodes[i].idsNeighbors.size()!=2){
            isVisited[i]=true;
            long previousId=i;
            for(long j=0;j<result->nodes[i].idsNeighbors.size();j++){
                long subCounter=0;
                //                std::cout<<"pI "<<previousId<<" j "<<j<<" size neighbors "<<result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size()<<'\n';
                if(result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size()==2){
                    //                    std::cout<<i<<'\n';
                    bool collapsed=false;
                    isVisited[result->nodes[i].idsNeighbors[j]]=true;
                    for(long h=0;h<result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size();h++){
                        if(!isVisited[result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[h]]||(result->nodes[result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[h]].idsNeighbors.size()!=2&&((result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[h]!=i)||subCounter>0))){
                            
                            
                            //                            else{
                            if(result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size()==2){
                                previousId=result->nodes[i].idsNeighbors[j];
                                
                                result->nodes[i].idsNeighbors[j]=result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[h];
                                result->nodes[i].weights[j]+=result->nodes[result->nodes[i].idsNeighbors[j]].weights[h];
                                subCounter++;
                                collapsed=true;
                            }
                            
                        }
                    }
                    if(collapsed){
                        j--;
                    }
                }else{
                    //                    if(result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size()!=2){
                    //                                result->nodes[i].idsNeighbors[j]=result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[h];
                    //                                result->nodes[i].weights[j]+=result->nodes[result->nodes[i].idsNeighbors[j]].weights[h];
                    //                        collapsed=false;
                    for(long k=0;k<result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size();k++){
                        if(result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[k]==previousId){
                            result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors[k]=i;
                            result->nodes[result->nodes[i].idsNeighbors[j]].weights[k]=result->nodes[i].weights[j];
                            //                                collapsed=true;
                        }
                    }
                    subCounter=0;
                    
                    //                    }
                }
            }
        }
    }
    
    
    
    
    
    ///correct ids
    long id=0;
    long numberNodes_new=0;
    for(long i=0;i<result->nodes.size();i++){
        if(result->nodes[i].idsNeighbors.size()!=2){
            result->nodes[i].id=id;
            id++;
            numberNodes_new++;
        }else{
            //            result->nodes[i].id=-1;
        }
    }
    id=0;
    result->n=numberNodes_new;
    result->m=0;
    std::vector<Node_LG> newNodes(numberNodes_new);
    for(long i=0;i<result->nodes.size();i++){
        if(result->nodes[i].idsNeighbors.size()!=2){
            newNodes[id]=result->nodes[i];
            for(long j=0;j<result->nodes[i].idsNeighbors.size();j++){
                result->m++;
//                if(result->nodes[result->nodes[i].idsNeighbors[j]].id!=result->nodes[i].idsNeighbors[j]){
                    newNodes[id].idsNeighbors[j]=result->nodes[result->nodes[i].idsNeighbors[j]].id;
                if(result->nodes[result->nodes[i].idsNeighbors[j]].idsNeighbors.size()==2){
                    std::cout<<"there is an issue here, i "<<i<<" j "<<j<<'\n';
                }
//                }
            }
            
            id++;
        }
    }
    result->nodes=newNodes;
    
}




void LargeGraph::networkPercolation(LargeGraph* G,LargeGraph* result,double threshold){
    result->nodes.resize(G->nodes.size());
    std::vector<long> numberTransitionsThatReachMe;
    numberTransitionsThatReachMe.resize(G->nodes.size(),0);
    result->m=0;
    for(long i=0;i<G->nodes.size();i++){
        std::vector<long> newIds;
        std::vector<double> newWeigths;
        
        for(long j=0;j<G->nodes[i].weights.size();j++){
            if(G->nodes[i].weights[j]<=threshold){
                newIds.push_back(G->nodes[i].idsNeighbors[j]);
                newWeigths.push_back(G->nodes[i].weights[j]);
                numberTransitionsThatReachMe[G->nodes[i].idsNeighbors[j]]++;
                result->m++;
            }
        }
        result->nodes[i]=G->nodes[i];
//        result->nodes[i].originalID=G->nodes[i].originalID;
        result->nodes[i].id_inOriginalGraph=i;
        result->nodes[i].weights=newWeigths;
        result->nodes[i].idsNeighbors=newIds;
    }
    
    
    ///correct ids
    long id=0;
    long numberNodes_new=0;
    for(long i=0;i<G->nodes.size();i++){
        if(result->nodes[i].idsNeighbors.size()>0||numberTransitionsThatReachMe[i]>0){
            result->nodes[i].id=id;
//            result->nodes[i].originalID=G->nodes[i].originalID;
            id++;
            numberNodes_new++;
        }
    }
    id=0;
    std::vector<Node_LG> newNodes(numberNodes_new);
    result->n=numberNodes_new;
    for(long i=0;i<result->nodes.size();i++){
//        result->nodes[i].idsNeighbors.clear();
//        result->nodes[i].weights.clear();
        if(result->nodes[i].idsNeighbors.size()>0||numberTransitionsThatReachMe[i]>0){
            for(long j=0;j<result->nodes[i].idsNeighbors.size();j++){
                if(result->nodes[result->nodes[i].idsNeighbors[j]].id!=result->nodes[i].idsNeighbors[j]){
                    result->nodes[i].idsNeighbors[j]=(result->nodes[result->nodes[i].idsNeighbors[j]].id);
                }
//                    result->nodes[i].idsNeighbors.push_back(G->nodes[result->nodes[i].idsNeighbors[j]].id);
//                result->nodes[i].weights.push_back(result->nodes[i].weights[j]);
//                }
            }
            newNodes[id]=result->nodes[i];
            id++;
        }
    }
    result->nodes=newNodes;
    if(G->bidirectional){
        result->bidirectional=true;
    }
    
   
    
    
}




void LargeGraph::getColorsFromComponents(LargeGraph* G,LargeGraph* separatedComponents,std::vector<long> &colors,std::vector<long> &sizes,long &maxColor){
    colors.resize(G->nodes.size(),-1);
    std::vector<bool> isVisited;
    maxColor=0;
    long color=0;
    isVisited.resize(separatedComponents->nodes.size(),false);
    for(long i=0;i<separatedComponents->nodes.size();i++){
        if(colors[separatedComponents->nodes[i].id_inOriginalGraph]==-1){
            long size=0;
            colors[separatedComponents->nodes[i].id_inOriginalGraph]=color;
            isVisited[i]=true;
            size++;
            maxColor=color;
            std::queue<long> idsNodesToVisit;
            for(long j=0;j<separatedComponents->nodes[i].idsNeighbors.size();j++){
                if(!isVisited[separatedComponents->nodes[i].idsNeighbors[j]]){
                    idsNodesToVisit.push(separatedComponents->nodes[i].idsNeighbors[j]);
                    isVisited[separatedComponents->nodes[i].idsNeighbors[j]]=true;
                }
            }
            while(idsNodesToVisit.size()>0){
                long currentId=idsNodesToVisit.front();
                isVisited[currentId]=true;
                idsNodesToVisit.pop();
                colors[separatedComponents->nodes[currentId].id_inOriginalGraph]=color;
                size++;
                for(long j=0;j<separatedComponents->nodes[currentId].idsNeighbors.size();j++){
//                    long idTemp=separatedComponents->nodes[currentId].idsNeighbors[j];
                    if(!isVisited[separatedComponents->nodes[currentId].idsNeighbors[j]]){
                        idsNodesToVisit.push(separatedComponents->nodes[currentId].idsNeighbors[j]);
                        isVisited[separatedComponents->nodes[currentId].idsNeighbors[j]]=true;
                    }
                }
            }
            color++;
            sizes.push_back(size);
            
            
        }
    }
    
    
}


void LargeGraph::generateSuperGraphFromColors(LargeGraph* G,LargeGraph* superGraph,std::vector<long> &colors,long maxColor){
    if(G->bidirectional){
        superGraph->bidirectional=true;
    }
    long numberNewNodes=0;
    std::vector<double> masses;
    masses.resize(maxColor+1,0);
    for(long i=0;i<colors.size();i++){
        masses[colors[i]+1]++;
    }

    numberNewNodes=masses[0]+maxColor+1;//all nodes that have -1 as color+the number of clusters and since ids of color start in 0 we add 1
//    std::vector<Point2d> centroids;
//    centroids.resize(numberNewNodes);
    superGraph->nodes.resize(numberNewNodes);
    std::vector<long> dictionaryIds;
    dictionaryIds.resize(G->nodes.size(),0);
    std::vector<long> getIndexesOrderedColors=Functions::getIndexesOfOrderedValues(colors,true);
    long currentColor=0;
    long previousColor=-1;
    Point2d centroid;
    superGraph->n=0;
    superGraph->m=0;
    for(long i=0;i<getIndexesOrderedColors.size();i++){
        if(colors[getIndexesOrderedColors[i]]==-1){
            superGraph->nodes[i].location=G->nodes[getIndexesOrderedColors[i]].location;
            superGraph->nodes[i].id=i;
            dictionaryIds[G->nodes[getIndexesOrderedColors[i]].id]=i;
            superGraph->n++;
         
        }else{
            currentColor=colors[getIndexesOrderedColors[i]];
            if(previousColor!=currentColor){
                if(previousColor!=-1){
                    centroid.x/=masses[previousColor+1];
                    centroid.y/=masses[previousColor+1];
                    superGraph->nodes[masses[0]+previousColor].location=centroid;
                }
                superGraph->nodes[masses[0]+currentColor].id=masses[0]+currentColor;
                
                centroid=G->nodes[getIndexesOrderedColors[i]].location;
                dictionaryIds[G->nodes[getIndexesOrderedColors[i]].id]=masses[0]+currentColor;
                previousColor=colors[getIndexesOrderedColors[i]];
                superGraph->n++;
            }else{
                dictionaryIds[G->nodes[getIndexesOrderedColors[i]].id]=masses[0]+currentColor;
                centroid.y+=G->nodes[getIndexesOrderedColors[i]].location.y;
                centroid.y+=G->nodes[getIndexesOrderedColors[i]].location.y;
            }
        }
    }
    
    
    
    currentColor=0;
    previousColor=-1;
    for(long i=0;i<getIndexesOrderedColors.size();i++){
        if(colors[getIndexesOrderedColors[i]]==-1){
            
            long prevColorTemp=-1;
            long currentColorTemp=0;
            std::vector<long> colorsTemp;
            colorsTemp.resize(G->nodes[getIndexesOrderedColors[i]].idsNeighbors.size());
            for(long j=0;j<G->nodes[getIndexesOrderedColors[i]].idsNeighbors.size();j++){
                colorsTemp[j]=colors[G->nodes[getIndexesOrderedColors[i]].idsNeighbors[j]];
            }
            std::vector<long> orderedIndexesNeighbors=Functions::getIndexesOfOrderedValues(colorsTemp, true);
            for(long j=0;j<orderedIndexesNeighbors.size();j++){
                if(colorsTemp[orderedIndexesNeighbors[j]]==-1){
                    long newId=dictionaryIds[G->nodes[getIndexesOrderedColors[i]].idsNeighbors[orderedIndexesNeighbors[j]]];
                    superGraph->nodes[i].idsNeighbors.push_back(newId);
                    superGraph->nodes[i].weights.push_back(G->nodes[getIndexesOrderedColors[i]].weights[orderedIndexesNeighbors[j]]);
                    superGraph->m++;
                }else{
                    currentColorTemp=colorsTemp[orderedIndexesNeighbors[j]];
                    if(prevColorTemp!=currentColorTemp){
                        long newId=dictionaryIds[G->nodes[getIndexesOrderedColors[i]].idsNeighbors[orderedIndexesNeighbors[j]]];
                        superGraph->nodes[i].idsNeighbors.push_back(newId);
                        superGraph->nodes[i].weights.push_back(G->nodes[getIndexesOrderedColors[i]].weights[orderedIndexesNeighbors[j]]);
                        prevColorTemp=currentColorTemp;
                        superGraph->m++;
                    }
                }
            }
        }else{
            long prevColorTemp=-1;
            long currentColorTemp=0;
            std::vector<long> colorsTemp;
            currentColor=colors[getIndexesOrderedColors[i]];
            colorsTemp.resize(G->nodes[getIndexesOrderedColors[i]].idsNeighbors.size());
            for(long j=0;j<G->nodes[getIndexesOrderedColors[i]].idsNeighbors.size();j++){
                colorsTemp[j]=colors[G->nodes[getIndexesOrderedColors[i]].idsNeighbors[j]];
            }
            std::vector<long> orderedIndexesNeighbors=Functions::getIndexesOfOrderedValues(colorsTemp, true);
            for(long j=0;j<orderedIndexesNeighbors.size();j++){
                if(colorsTemp[orderedIndexesNeighbors[j]]==-1){
                    long newId=dictionaryIds[G->nodes[getIndexesOrderedColors[i]].idsNeighbors[orderedIndexesNeighbors[j]]];
                    superGraph->nodes[i].idsNeighbors.push_back(newId);
                    superGraph->nodes[i].weights.push_back(G->nodes[getIndexesOrderedColors[i]].weights[orderedIndexesNeighbors[j]]);
                    superGraph->m++;
                }else{
                    currentColorTemp=colorsTemp[orderedIndexesNeighbors[j]];
                    if(currentColorTemp!=currentColor){
                        if(prevColorTemp!=currentColorTemp){
                            long newId=dictionaryIds[G->nodes[getIndexesOrderedColors[i]].idsNeighbors[orderedIndexesNeighbors[j]]];
                            superGraph->nodes[i].idsNeighbors.push_back(newId);
                            superGraph->nodes[i].weights.push_back(G->nodes[getIndexesOrderedColors[i]].weights[orderedIndexesNeighbors[j]]);
                            prevColorTemp=currentColorTemp;
                            superGraph->m++;
                        }
                    }
                }
            }
        }
    }
    
    
}















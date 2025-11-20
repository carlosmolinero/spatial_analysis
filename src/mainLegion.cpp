////
////  main.cpp
////  harmonicCities
////
////  Created by Carlos Molinero on 04/06/2015.
////  Copyright (c) 2015 Carlos Molinero. All rights reserved.
////
//
//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}



#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Programs.h"







int main(int argc,char* argv[])

{

    Configuration::setFolder("/Users/carlos/Documents/");
    Configuration::setSubFolderIn("data/GIS/Melbourne/");
    Configuration::setSubFolderOut("results/CyclistAnalysis/");
    
    if (argc>1){
        Configuration::setFolder(argv[1]);
        Configuration::setSubFolderIn(argv[2]);
        Configuration::setSubFolderOut(argv[3]);
    }
    
    std::stringstream nameSS,nameCoordinatesSS;
    std::string separatorNCOL=" ";
    std::string separatorCoordinates=" ";
    bool header=true;
    bool readIdsSegments=true;

    Graph loadedGraph;
    loadedGraph.strictlyDirectional=true;
    
//    nameSS<<Configuration::folderIn()<<"melbourneNCOLPureSubArea"<<".txt";
//    nameCoordinatesSS<<Configuration::folderIn()<<"melbourneCoordinatesSubArea"<<".txt";
    
    nameSS<<Configuration::folderIn()<<"melbourneNCOLPure"<<".txt";
    nameCoordinatesSS<<Configuration::folderIn()<<"pointsFinal"<<".txt";
    
    if (argc>4){
        nameSS.str("");
        nameSS<<Configuration::folderIn()<<argv[4];
        nameCoordinatesSS.str("");
        nameCoordinatesSS<<Configuration::folderIn()<<argv[5];
        separatorNCOL=argv[6];
        separatorCoordinates=argv[7];
        string argument;
        argument=argv[8];
        if(argument=="true"){
            header=true;
        }else{
            header=false;
        }
        argument=argv[9];
        if(argument=="true"){
            readIdsSegments=true;
        }else{
            readIdsSegments=false;
        }
        
    }
    
    TextFile::parseNCOLandSeparateCoordinatesFile(nameSS.str(), nameCoordinatesSS.str(), &loadedGraph, separatorNCOL, separatorCoordinates, header, readIdsSegments);
    
//    Graph simplifiedGraph;
//    std::vector<Graph> clusters;
//    loadedGraph.generateSpatialPercolation(&loadedGraph, 50, clusters);
//    loadedGraph.generateSuperGraphFromClusters(clusters, &loadedGraph, &simplifiedGraph);
    
    
    
    
    
//    double startDistance=60;
//    double endDistance=65;
//    long minClusterSize=50000;
//    double separationBetweenDistances=5;
    
    
    long indexCombinedDistanceCutoff=0;
    long indexCombinedDistanceCalculation=0;
    double metricRadius=500;
    if(argc>9){
        metricRadius=stod(argv[10]);
        indexCombinedDistanceCutoff=atol(argv[11]);
        indexCombinedDistanceCalculation=atol(argv[12]);
//        endDistance=stod(argv[11]);
//        separationBetweenDistances=stod(argv[12]);
//        minClusterSize=atol(argv[13]);
    }
    float startNode=0;
    float endNode=0;
//    long separationBetweenPercentages=1;
//    long initRepetitions=0;
//    long endRepetitions=1;
    long typeFirstDistance=Graph::ANGULAR;
    long typeSecondDistance=Graph::ANGULAR;
    long typeDistanceCombined=Graph::ANGULAR;
    bool customize=false;
    
    if (argc>12){
        startNode=atol(argv[13]);
        endNode=atol(argv[14]);
        typeFirstDistance=atol(argv[15]);
        typeSecondDistance=atol(argv[16]);
        typeDistanceCombined=atol(argv[17]);
        string argument=argv[18];
        if(argument=="true"){
            customize=true;
        }else{
            customize=false;
        }
//        separationBetweenPercentages=atol(argv[16]);
//        initRepetitions=atol(argv[17]);
//        endRepetitions=atol(argv[18]);
    }
    
//    Programs::calculateMelbourne(&loadedGraph, startNode, endNode, metricRadius, <#long indexDistanceCutoff#>, <#long indexDistanceCalculation#>, <#bool customize#>)
    
    
//    BST<Node*> nodesTree;
//    Node node;
//        Node node2;
//    nodesTree.add(node.originalID,&node);
//
//    nodesTree.add(node2.originalID, &node2);
//    std::cout<<nodesTree.exist(node.originalID)<<'\n';
//        std::cout<<nodesTree.exist(node2.originalID)<<'\n';
//    nodesTree.deleteNode(40);
////    nodesTree.deleteAll();
////        nodesTree.add(node2.originalID, &node2);
////    nodesTree.add(node.originalID,&node);
//    
//
//        std::cout<<nodesTree.exist(node.originalID)<<'\n';
//            std::cout<<nodesTree.exist(node2.originalID)<<'\n';
    
    
    Programs::calculateMelbourne(&loadedGraph, startNode, endNode, metricRadius, typeFirstDistance, typeSecondDistance, typeDistanceCombined, indexCombinedDistanceCutoff, indexCombinedDistanceCalculation, customize);
    
    return 0;
}
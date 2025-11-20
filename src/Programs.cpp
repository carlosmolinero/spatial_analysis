//
//  Programs.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 06/07/2015.
//  Copyright (c) 2015 UCL. All rights reserved.
//

#include "Programs.h"



void Programs::calculateCentralitiesGraph(Graph* graph,int indexDistance){
//    Network::calculateCentralitiesOfCities(graph, indexDistance, 0, false);
    graph->useGaussianBetweenness=false;
    graph->prepareForCentralitiesCalculation();
//    if(useMassesForValuesToPass){
//        for(long i=0;i<graph->nodes.size();i++){
//            
//            graph->nodes[i].valuesToPass[indexDistance]=graph->nodes[i].mass;
//            graph->nodes[i].originalValuesToPass[indexDistance]=graph->nodes[i].mass;
//            
//            
//        }
//    }
//    for(long i=0;i<graph->nodes.size();i++){
//        
//        
//        Node* node=&graph->nodes[i];
//        
//        if(graph->nodes[i].mass>0){
    
            graph->calculationCentralities(graph, 0, 0,graph->nodes.size(), 0, indexDistance,indexDistance);
            
//        }
    
//    }
}

void Programs::saveResultsCentralities(Graph* graph,int indexDistance,std::string nameFile){
    std::vector<std::string> lines;
    std::stringstream line;
    line<<"idA idB closeness betweenness";
    lines.push_back(line.str());
    for(long i=0;i<graph->nodes.size();i++){
        line.str("");
        Transition* trans=graph->nodes[i].transitionThatRepresents;
        line<<trans->a->originalID<<" "<<trans->b->originalID<<" "<<graph->closenessMeasures[indexDistance][i]<<" "<<graph->betweennessMeasures[indexDistance][i];
        lines.push_back(line.str());
    }
    TextFile::writeToFile(nameFile, lines, false);
}
void Programs::createLineGraph(Graph* graph,Graph* lineGraph){
    graph->createLineGraph(graph,lineGraph);
}

void Programs::createRoadNetwork(){
    Graph minRealGraph;
    Graph mainGraph;
//    minRealGraph.strictlyDirectional=true;
    double minSizeCity=4;
        TextFile::parseNCOLWithCoordinates("/Users/carlos/Dropbox/CASA/results/harmonicCities/minRealGraph2.txt", &minRealGraph, " ", false);
        TextFile::includeMasses(&minRealGraph, "/Users/carlos/Documents/results/harmonicCities/massesMinRealGraph.txt", " ", false);
//     TextFile::includeMasses(&minRealGraph, "/Users/carlos/Dropbox/CASA/results/harmonicCities/masses.txt", " ", false);
    minRealGraph.transformToBidirectional();
        for(long i=0;i<minRealGraph.nodes.size();i++){
            if(minRealGraph.nodes[i].mass<minSizeCity){
                minRealGraph.nodes[i].mass=0;
            }
        }
    
    minRealGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    
    
    Graph percolatedGraph;
    std::vector<Graph> clusters;
    minRealGraph.generateNetworkPercolation(0, clusters, false, true, "", 0, false);
    
//    minRealGraph.generateSpatialPercolation(&minRealGraph, 5000, clusters);
    minRealGraph.generateSuperGraphFromClusters(clusters, &minRealGraph, &percolatedGraph);
    

    ////////////////////////
    

    for(long i=0;i<percolatedGraph.nodes.size();i++){

                if(percolatedGraph.nodes[i].mass>0){
                    mainGraph.addNode();
                    mainGraph.nodes[mainGraph.nodes.size()-1].location=percolatedGraph.nodes[i].location;
                    mainGraph.nodes[mainGraph.nodes.size()-1].mass=percolatedGraph.nodes[i].mass;
                    mainGraph.nodes[mainGraph.nodes.size()-1].originalID=percolatedGraph.nodes[i].originalID;
                }
    }

    
    ///////The rest is in networks class file
    Network network;
    Singleton<Windows>::instance().add(Point2d(0,0), 600,600);
    Singleton<Windows>::instance().add(Point2d(600,0), 600,600);
    Singleton<Windows>::instance().add(Point2d(1200,0), 600,600);
    
    network.generateRoadNetworkBetweenNodes(&mainGraph,minSizeCity,3);
    
    
    VectorNDim vec;
    vec.values.clear();
    vec.values.push_back(0);
    vec.values.push_back(0);
    vec.values.push_back(0);
    vec.values.push_back(100);
//    Singleton<Windows>::instance().get(0)->drawGraph(&mainGraph,vec);

//    Singleton<Windows>::instance().get(2)->drawGraph(&mainGraph,vec);
//    Singleton<Windows>::instance().get(2)->zoomExtents();


//    Singleton<Windows>::instance().get(1)->drawGraph(&minRealGraph,vec);
//    Singleton<Windows>::instance().get(1)->zoomExtents();

}

void Programs::createRoadNetwork(Graph& graph,double minSizeCity,double definition){
//        double minSizeCity=4;
    
//    Graph minRealGraph;
//    Graph mainGraph;
//    //    minRealGraph.strictlyDirectional=true;
//    TextFile::parseNCOLWithCoordinates("/Users/carlos/Dropbox/CASA/results/harmonicCities/minRealGraph2.txt", &minRealGraph, " ", false);
//    TextFile::includeMasses(&minRealGraph, "/Users/carlos/Documents/results/harmonicCities/massesMinRealGraph.txt", " ", false);
//    //     TextFile::includeMasses(&minRealGraph, "/Users/carlos/Dropbox/CASA/results/harmonicCities/masses.txt", " ", false);
//    minRealGraph.transformToBidirectional();
//    for(long i=0;i<minRealGraph.nodes.size();i++){
//        if(minRealGraph.nodes[i].mass<minSizeCity){
//            minRealGraph.nodes[i].mass=0;
//        }
//    }
//    
//    minRealGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
//    
//    
//    Graph percolatedGraph;
//    std::vector<Graph> clusters;
//    minRealGraph.generateNetworkPercolation(0, clusters, false, true, "", 0, false);
//    
//    //    minRealGraph.generateSpatialPercolation(&minRealGraph, 5000, clusters);
//    minRealGraph.generateSuperGraphFromClusters(clusters, &minRealGraph, &percolatedGraph);
//    
//    
//    ////////////////////////
//    
//    
//    for(long i=0;i<percolatedGraph.nodes.size();i++){
//        
//        if(percolatedGraph.nodes[i].mass>0){
//            mainGraph.addNode();
//            mainGraph.nodes[mainGraph.nodes.size()-1].location=percolatedGraph.nodes[i].location;
//            mainGraph.nodes[mainGraph.nodes.size()-1].mass=percolatedGraph.nodes[i].mass;
//            mainGraph.nodes[mainGraph.nodes.size()-1].originalID=percolatedGraph.nodes[i].originalID;
//        }
//    }
    
    
    ///////The rest is in networks class file
    Network network;
//    Singleton<Windows>::instance().add(Point2d(0,0), 600,600);
//    Singleton<Windows>::instance().add(Point2d(600,0), 600,600);
//    Singleton<Windows>::instance().add(Point2d(1200,0), 600,600);
    
    network.generateRoadNetworkBetweenNodes(&graph,minSizeCity,definition);
    
    
//    VectorNDim vec;
//    vec.values.clear();
//    vec.values.push_back(0);
//    vec.values.push_back(0);
//    vec.values.push_back(0);
//    vec.values.push_back(100);
//    Singleton<Windows>::instance().get(0)->drawGraph(&graph,vec);
//    //    Singleton<Windows>::instance().get(0)->zoomExtents();
//    Singleton<Windows>::instance().get(2)->drawGraph(&graph,vec);
//    Singleton<Windows>::instance().get(2)->zoomExtents();
//    //    Singleton<Windows>::instance().get(2)->copyViewParameters(Singleton<Windows>::instance().get(0));
//    
//    Singleton<Windows>::instance().get(1)->drawGraph(&minRealGraph,vec);
//    Singleton<Windows>::instance().get(1)->zoomExtents();
    //        mainGraph.createLineGraph(&mainGraph, &lineGraph);
    //        calculateEdgeBetweennessOfCities(&lineGraph, lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0], minSizeCity, true);
    //        mainGraph.insertGraphIntoQTree(&quadTreeGenerated);
    //        saveStatistics(mainGraph,minRealGraph);
}



void Programs::percolateAndCreateRoadNetwork(Graph* G,Graph* result,double distancePercolation,double minSizeCity,double definition){
    std::vector<Graph> clusters;
    G->generateNetworkPercolation(distancePercolation, clusters, false, true, "", 1, false);

    Graph sg;
    G->generateSuperGraphFromClusters(clusters, G, &sg);
    
    for(long i=0;i<sg.nodes.size();i++){
        result->addNode();
        result->nodes[i].location=sg.nodes[i].location;
        result->nodes[i].mass=sg.nodes[i].mass;
    }
    
    Network net;
    net.generateRoadNetworkBetweenNodes(result, minSizeCity, definition);
}

void Programs::performAngularNetworkPercolation(){
    bool saveClusters=false;
     bool measureCorrelationLength=false;
    bool visualizeResult=false;
    bool calculateFractalDimension=true;
    bool generateSuperGraph=false;
    Graph loadedGraph;
    //    double minSizeCity=50;
    ////////LOAD MINREALGRAPH
    //        loadedGraph.strictlyDirectional=false;
    //    minRealGraph.pseudoGraph=false;
    
    
    
    Graph uk;
    std::cout<<"IMPORTING FILE UK"<<'\n';
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, ",", " ", true, false);
    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/results/angularNetworkPercolation/UK/subAreaUK_pointsix/subAreaUK_pointsix.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, " ", " ", true, false);
//      TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/harmonicCities/uk_subArea.txt", &loadedGraph, " ", false);
    
    Configuration::setFolder("/Users/carlos/Documents/");
    Configuration::setSubFolderOut("results/angularNetworkPercolation/UK/subAreaUK_pointsix/");
    
    Graph minRealGraph;
    
//        TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/harmonicCities/uk_subArea.txt", &loadedGraph, " ", false);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/zzz_/gridNCOLAndCoord.txt", &loadedGraph, " ", true);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Dropbox/CASA/results/harmonicCities/minRealGraph2.txt", &minRealGraph, " ", false);
    //    TextFile::includeMasses(&minRealGraph, "/Users/carlos/Documents/results/harmonicCities/massesMinRealGraph.txt", " ", false);
    loadedGraph.transformToBidirectional();
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //        if(minRealGraph.nodes[i].mass<minSizeCity){
    //            minRealGraph.nodes[i].mass=0;
    //        }
    //    }
    
    loadedGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    loadedGraph.getGiantComponent(&loadedGraph, &minRealGraph);
    minRealGraph.transformToBidirectional();
    
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //
    //
    //        minRealGraph.nodes[i].location.x+=-minX;
    //        minRealGraph.nodes[i].location.y+=-minY;
    //        minRealGraph.nodes[i].location.x*=width/75/1000;
    //        minRealGraph.nodes[i].location.y*=width/75/1000;
    //
    //
    //
    //
    //
    //    }
    ////////////////////////
    
    std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
    for(long i=0;i<minRealGraph.nodes.size();i++){
        nodesOriginalGraphByOriginalId[minRealGraph.nodes[i].originalID]=&minRealGraph.nodes[i];
        //        if(minRealGraph.nodes[i].mass>0){
        //            mainGraph.addNode();
        //            mainGraph.nodes[mainGraph.nodes.size()-1].location=minRealGraph.nodes[i].location;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].mass=minRealGraph.nodes[i].mass;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].originalID=minRealGraph.nodes[i].originalID;
        //
        //
        //
        //        }
    }
    if(visualizeResult){
        //////////////////
        Singleton<Windows>::instance().add(Point2d(15,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(475,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(935,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(1395,465), 430,200);
        //////////////////
        Singleton<Windows>::instance().add(Point2d(15,7.5), 430,430);
        Singleton<Windows>::instance().add(Point2d(475,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(475,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(935,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(935,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,465+230), 430,200);
        //////////////////
        
        Singleton<Windows>::instance().setTitle(0,"Original graph");
        Singleton<Windows>::instance().setTitle(1,"Giant cluster");
        Singleton<Windows>::instance().setTitle(2,"Second largest cluster");
        Singleton<Windows>::instance().setTitle(3,"Correlation length");
        Singleton<Windows>::instance().setTitle(4,"Log-Log of masses of clusters");
        Singleton<Windows>::instance().setTitle(5,"R2 of the correlation of masses");
        Singleton<Windows>::instance().setTitle(7,"Proportion between largest and second largest cluster");
        Singleton<Windows>::instance().setTitle(6,"Slopes of correlation of masses");
        Singleton<Windows>::instance().setTitle(8,"<S*>");
        Singleton<Windows>::instance().setTitle(9,"P_N(p)");
        Singleton<Windows>::instance().setTitle(10,"Evolution of masses");
        Singleton<Windows>::instance().setTitle(11,"Fractal dimension box-counting");
        VectorNDim vec;
        vec.values.clear();
        vec.values.push_back(0);
        vec.values.push_back(0);
        vec.values.push_back(0);
        vec.values.push_back(100);
//        Singleton<Windows>::instance().get(0)->drawGraph(&minRealGraph,vec);
        Singleton<Windows>::instance().get(0)->zoomExtents();
    }
    
    
    
    
    Plot evolutionR2Masses;
    //    Plot evolutionR2Transitions;
    evolutionR2Masses.limited=false;
    //    evolutionR2Transitions.limited=false;
    Plot proportionFirstAndSecond;
    proportionFirstAndSecond.limited=false;
    Plot slopeMasses;
    slopeMasses.limited=false;
    Plot averageMasses;
    averageMasses.limited=false;
    Plot numberClusters;
    numberClusters.limited=false;
    
    Plot evolutionMass1;
    evolutionMass1.limited=false;
    Plot evolutionMass2;
    evolutionMass2.limited=false;
    Plot evolutionMass3;
    evolutionMass3.limited=false;
    Plot evolutionMass4;
    evolutionMass4.limited=false;
    Plot evolutionMass5;
    evolutionMass5.limited=false;
    Plot correlationLength;
    correlationLength.limited=false;
    std::vector<double> entropy;
    Plot fd;
    fd.limited=false;
    
    //      saveGraph(&minRealGraph, "/Users/carlos/Documents/zzz_/smallAreaUKNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKCoordinates.txt", " ", " ");
    
    Graph lineGraph;
    lineGraph.strictlyDirectional=true;
    minRealGraph.createLineGraph(&minRealGraph,&lineGraph);
    
    double totalMassOfSystem=lineGraph.transitions.size()/2;//I need to divide it by two because it is strictlyDirectional and the clusters are not strictlyDirectionals so they have half the number of transitions.
    
    
    //    lineGraph.transformToBidirectional();
    
    //    saveGraph(&lineGraph, "/Users/carlos/Documents/zzz_/smallAreaUKLGNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKLGCoordinates.txt", " ", " ");
    
   
    Graph lineGraphlineGraph;
    if(measureCorrelationLength){
        lineGraphlineGraph.resetGraph();
        lineGraph.createLineGraph(&lineGraph, &lineGraphlineGraph);
        int indexWeight=lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0];
        for(long k=0;k<lineGraphlineGraph.transitions.size();k++){
            
            Node* a=lineGraphlineGraph.transitions[k].a;
            Node* b=lineGraphlineGraph.transitions[k].b;
            Transition* transA=a->transitionThatRepresents;
            Transition* transB=b->transitionThatRepresents;
            lineGraphlineGraph.transitions[k].weight=(transA->otherWeights[indexWeight]+transB->otherWeights[indexWeight])/2;
            //        lineGraphlineGraph.transitions[k].weight=lineGraphlineGraph.transitions[k].otherWeights[lineGraphlineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
            //        lineGraphlineGraph.transitions[k].weight=1;
            //        std::cout<<"new weights "<<lineGraphlineGraph.transitions[k].weight<<'\n';
        }
    }
    QTree quadTreeLGLG;
    if(measureCorrelationLength){
        lineGraphlineGraph.insertGraphIntoQTree(&quadTreeLGLG);
    }
    
    
    
    
    
    
    
    //    saveGraph(&lineGraphlineGraph, "/Users/carlos/Documents/zzz_/smallAreaUKLGLGNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKLGLGCoordinates.txt", " ", " ");
    
    
    
    std::vector<double> setOfAngles;
    //    setOfAngles.push_back(45);
    //    setOfAngles.push_back(60);
    //    setOfAngles.push_back(85);
    //    setOfAngles.push_back(175);
    
    //    for(double i=10;i<20;i+=10){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=20;i<30;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=30;i<44;i+=1){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=44;i<45;i+=.5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=45;i<60;i+=1){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=60;i<70;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=70;i<85;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=85;i<95;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=95;i<100;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    double minAngle=0;
    double maxAngle=180;
    for(double i=minAngle;i<maxAngle;i+=1){
        setOfAngles.push_back(i);
    }
    //    setOfAngles.push_back(45);
    
    
    std::vector<std::string> linesFileMasses;
    for(double h=0;h<setOfAngles.size();h++){
        double angle=setOfAngles[h];
        std::cout<<"===================="<<'\n';
        std::cout<<"angle : "<<angle<<'\n';
        Plot boxCounting;
        boxCounting.mode=Plot::EUCLIDEAN;
//        long repetitions=1;
        std::vector<Graph> clusters;
        double averageMassGiantCluster=0;
        double massGiantCluster=0;
        
//        for(long i=0;i<repetitions;i++){
            clusters.clear();
            minRealGraph.generateAngularPercolation(&minRealGraph,&lineGraph, angle, clusters,0,false);
        std::vector<double> massesClustersTemp;
        for(long i=0;i<clusters.size();i++){
            massesClustersTemp.push_back(clusters[i].transitions.size());
        }
        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
        
            averageMassGiantCluster=clusters[indexesOrderClusters[0]].transitions.size();
            massGiantCluster=clusters[indexesOrderClusters[0]].transitions.size();
//        }
//        averageMassGiantCluster/=(double)(repetitions);
        evolutionMass1.addValue(averageMassGiantCluster/(double)(totalMassOfSystem));
        
        
        FractalDimension fractalDimension;
        if(calculateFractalDimension){
//            fd.addValue(fractalDimension.calculateBoxCounting(&clusters[indexesOrderClusters[0]]));
        }
        Graph superGraphClusters;
        if(generateSuperGraph){
            lineGraph.generateSuperGraphFromClusters(clusters, &lineGraph, &superGraphClusters);
        
        
        //        std::vector<double> values;
        //        for(long i=0;i<superGraphClusters.nodes.size();i++){
        //            values.push_back(superGraphClusters.nodes[i].transitions.size());
        //        }
            std::stringstream nameFileSuperGraph;
            nameFileSuperGraph<<Configuration::folderOut()<<"superGraph_"<<angle<<".txt";
            TextFile::writeNCOLPlusCoordinatesFile(&superGraphClusters, nameFileSuperGraph.str());
        }
        
        
        
        
        
        //            minRealGraph.generateNetworkPercolation(angle, clusters,false, true, "", 0);
        //            minRealGraph.orderClustersByMass(clusters);
        
        std::vector<Graph> clustersPrimal;
        if(saveClusters||visualizeResult){
            for(long j=0;j<2;j++){
                Graph clusterPrimal;
                std::vector<Transition*> transitions;
                for(long i=0;i<clusters[indexesOrderClusters[j]].nodes.size();i++){
                    transitions.push_back(clusters[indexesOrderClusters[j]].nodes[i].transitionThatRepresents);
                }
                
                minRealGraph.getInducedSubgraph(&clusterPrimal, transitions);
                clustersPrimal.push_back(clusterPrimal);
            }
        }
        
        double entropyTemp=0;
        for(double i=0;i<clusters.size();i++){
            
            double probabilityCluster=((double)clusters[i].transitions.size()/(double)totalMassOfSystem);
            entropyTemp+=probabilityCluster*log10(probabilityCluster);
        }
        //        for(double i=0;i<clusters.size();i++){
        //
        //            //            double probabilityCluster=((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
        //            //            entropyTemp+=probabilityCluster*log(probabilityCluster);
        //
        //            for(long j=0;j<clusters[i].transitions.size();j++){
        //                Node* a=nodesOriginalGraphByOriginalId[clusters[i].transitions[j].a->originalID];
        //
        //                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=(double)lclusters[i].transitions.size()/(double)lineGraph.nodes.size()*log((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
        //                double normalizedSize=Functions::normalize(log((double)clusters[i].transitions.size()),log((double)clusters[clusters.size()-1].transitions.size()),log((double)clusters[0].transitions.size()));
        //                //                double normalizedSize=Functions::normalize(((double)clusters[i].transitions.size()),((double)clusters[clusters.size()-1].transitions.size()),((double)clusters[0].transitions.size()));
        //                double maxRanking=clusters.size();
        //                double normalizedRanking=Functions::normalize(maxRanking-i, 0, maxRanking);
        //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=normalizedSize*(-entropyTemp);
        //                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=i;
        //
        //
        //
        //            }
        //        }
        for(double i=0;i<clusters.size();i++){
            for(long j=0;j<clusters[i].nodes.size();j++){
                Node* a=nodesOriginalGraphByOriginalId[clusters[i].nodes[j].transitionThatRepresents->a->originalID];
                
                
//                double normalizedSize=Functions::normalize(log((double)clusters[i].transitions.size()),log((double)clusters[clusters.size()-1].transitions.size()),log((double)clusters[0].transitions.size()));
                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].nodes[j].transitionThatRepresents->b->originalID]-1]->levelHierarchyRoad+=log((double)clusters[i].transitions.size())*(-entropyTemp);
                
                
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=i;
            }
        }
        
        entropy.push_back(-entropyTemp);
        
        
        if(angle>minAngle){
            if(visualizeResult){
                Singleton<Windows>::instance().add(1);
                Singleton<Windows>::instance().add(2);
                Singleton<Windows>::instance().add(3);
                Singleton<Windows>::instance().add(4);
            }
        }
        
        
        
        if(visualizeResult){
//            Singleton<Windows>::instance().get(1)->drawGraph(&clustersPrimal[0]);
            Singleton<Windows>::instance().get(1)->copyViewParameters(Singleton<Windows>::instance().get(0));
            if(clustersPrimal.size()>1){
//                Singleton<Windows>::instance().get(2)->drawGraph(&clustersPrimal[1]);
                Singleton<Windows>::instance().get(2)->copyViewParameters(Singleton<Windows>::instance().get(0));
            }
        }
        
        //        Singleton<Windows>::instance().get(3)->copyViewParameters(Singleton<Windows>::instance().get(0));
        
        
        
        
        Plot masses;
        masses.mode=Plot::EUCLIDEAN;
        
        double averageMass=0;
        double totalMassWithoutGiantCluster=0;
        std::vector<Point2d> numberClustersOfASize;
        std::vector<double> radiiGyrationSquared;
        
        
        
        for(double i=0;i<clusters.size();i++){
            
            masses.addValue(Point2d(log(i+1),log((double)(clusters[i].transitions.size())+1)));
            if(i!=indexesOrderClusters[0]){
                averageMass+=clusters[i].transitions.size();
            }
            if(i==0){
                //                evolutionMass1.addValue((double)(clusters[i].nodes.size())/(double)(lineGraph.nodes.size()));
            }
            if(i==1){
                evolutionMass2.addValue(clusters[i].transitions.size());
            }
            if(i==2){
                evolutionMass3.addValue(clusters[i].transitions.size());
            }
            if(i==3){
                evolutionMass4.addValue(clusters[i].transitions.size());
            }
            if(i==4){
                evolutionMass5.addValue(clusters[i].transitions.size());
            }
            
            
            
//            if(i!=indexesOrderClusters[0]||angle<=45){
            if(i!=indexesOrderClusters[0]){
            
                if(numberClustersOfASize.size()==0||clusters[i].transitions.size()!=numberClustersOfASize[numberClustersOfASize.size()-1].x){
                    Point2d point;
                    point.x=clusters[i].transitions.size();
                    point.y=1;
                    numberClustersOfASize.push_back(point);
                    
                    Graph subGraphLineGraphLineGraph;
                    //                    std::vector<Node*> nodesLGLG;
                    //                    for(long k=0;k<clusters[i].nodes.size();k++){
                    //                        for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                    //                            Node* a=clusters[i].nodes[k].transitions[g]->a->nodeThatRepresents;
                    //                            Node* b=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                    //                            Transition* trans=a->transitions[a->indexOfTransitionsByIdOfDestination[b->originalID]-1];
                    //                            Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                    //                            nodesLGLG.push_back(nodeLGLG);
                    //                        }
                    //                    }
                    //                    if(i>0){
                    
                    
                    
                    
                    
                    
                    
                    
                    if(measureCorrelationLength){
                        std::vector<Node*> nodesSubgraphLGLG;
                        for(long k=0;k<clusters[i].nodes.size();k++){
                            Node* nodeALG=clusters[i].nodes[k].nodeThatRepresents;
                            Node* nodeBLG=NULL;
                            for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                                nodeBLG=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                            }
                            if(nodeBLG!=NULL){
                                Transition* trans=nodeALG->transitions[nodeALG->indexOfTransitionsByIdOfDestination[nodeBLG->originalID]-1];
                                Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                                nodesSubgraphLGLG.push_back(nodeLGLG);
                            }
                        }
                        lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesSubgraphLGLG);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    //                    lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesLGLG);
                    //                    if (angle==7){
                    //                        saveGraph(&subGraphLineGraphLineGraph, "/Users/carlos/Documents/zzz_/subsmallAreaUKLGLGNCOL.txt", "/Users/carlos/Documents/zzz_/subsmallAreaUKLGLGCoordinates.txt", " ", " ");
                    //                        std::cout<<"index subgraph "<<i<<'\n';
                    //                        if(i==1){
                    //                            std::cout<<"problem"<<'\n';
                    //                        }
                    //                    }
                    
                        double radiusGyrationSquared=Graph::calculateSquaredGyrationRadiusInGraphSpace(&subGraphLineGraphLineGraph,&lineGraphlineGraph,&quadTreeLGLG);
                        
                        radiiGyrationSquared.push_back(radiusGyrationSquared);
                    }
                    //                    }else{
                    //                        radiiGyrationSquared.push_back(0);
                    //                    }
                }else{
                    numberClustersOfASize[numberClustersOfASize.size()-1].y++;
                    //                    Graph lineGraphlineGraph;
                    Graph subGraphLineGraphLineGraph;
                    //                    std::vector<Node*> nodesLGLG;
                    //                    for(long k=0;k<clusters[i].nodes.size();k++){
                    //                        for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                    //                            Node* a=clusters[i].nodes[k].transitions[g]->a->nodeThatRepresents;
                    //                            Node* b=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                    //                            Transition* trans=a->transitions[a->indexOfTransitionsByIdOfDestination[b->originalID]-1];
                    //                            Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                    //                            nodesLGLG.push_back(nodeLGLG);
                    //                        }
                    //                    }
                    //                    lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesLGLG);
                    //                    if(i>0){
                    
                    if(measureCorrelationLength){
                        std::vector<Node*> nodesSubgraphLGLG;
                        for(long k=0;k<clusters[i].nodes.size();k++){
                            Node* nodeALG=clusters[i].nodes[k].nodeThatRepresents;
                            Node* nodeBLG=NULL;
                            for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                                nodeBLG=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                            }
                            if(nodeBLG!=NULL){
                                Transition* trans=nodeALG->transitions[nodeALG->indexOfTransitionsByIdOfDestination[nodeBLG->originalID]-1];
                                Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                                nodesSubgraphLGLG.push_back(nodeLGLG);
                            }
                        }
                        lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesSubgraphLGLG);
                        
                        double radiusGyrationSquared=Graph::calculateSquaredGyrationRadiusInGraphSpace(&subGraphLineGraphLineGraph,&lineGraphlineGraph,&quadTreeLGLG);
                        radiiGyrationSquared[numberClustersOfASize.size()-1]+=radiusGyrationSquared;
                    }
                    //                    }else{
                    ////                        radiiGyrationSquared.push_back(0);
                    //                    }
                }
                totalMassWithoutGiantCluster+=clusters[i].transitions.size();
                
                
                
            }
            
        }
        averageMass/=(double)(clusters.size()-1);
        
        double averageS=0;
        double squaredSumOfMassesFiniteAndNotGiant=0;
        double numeratorCorrelationLength=0;
        double denominatorCorrelationLength=0;
        
        for(long i=0;i<numberClustersOfASize.size();i++){
            averageS+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y/totalMassWithoutGiantCluster);
            squaredSumOfMassesFiniteAndNotGiant+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y);
            if(measureCorrelationLength){
                double radiusGyrationSquared=radiiGyrationSquared[i]/numberClustersOfASize[i].y;
                //            numeratorCorrelationLength+=
                numeratorCorrelationLength+=2*radiusGyrationSquared*numberClustersOfASize[i].x*(numberClustersOfASize[i].x)*numberClustersOfASize[i].y/(double)(totalMassOfSystem);
                denominatorCorrelationLength+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x)*numberClustersOfASize[i].y/(double)(totalMassOfSystem);
            }
        }
        std::cout<<"averageS "<<averageS<<'\n';
        
        if(measureCorrelationLength){
            correlationLength.addValue(pow(numeratorCorrelationLength/denominatorCorrelationLength,.5));
            std::cout<<"correlation length "<<pow(numeratorCorrelationLength/denominatorCorrelationLength,.5)<<'\n';
        }
        
        
        std::stringstream lineTemp;
        lineTemp<<angle<<" "<<massGiantCluster<<" "<<totalMassOfSystem<<" "<<squaredSumOfMassesFiniteAndNotGiant<<" "<<totalMassWithoutGiantCluster;
        linesFileMasses.push_back(lineTemp.str());
        
        
        
        
        
        
        
        
        
        
        
        
        
        std::vector<string> lines;
        stringstream line;
        line<<"totalMassPrimal"<<" "<<minRealGraph.transitions.size();
        lines.push_back(line.str());
        line.str("");
        line<<"totalMassLineGraph"<<" "<<totalMassOfSystem;
        lines.push_back(line.str());
        stringstream nameFile;
        nameFile<<Configuration::folderOut()<<"globalMasses.txt";
        TextFile::writeToFile(nameFile.str(), lines, false);
        
        //        lines.clear();
        nameFile.str("");
        nameFile<<Configuration::folderOut()<<"masses"<<angle<<".txt";
        //        TextFile::writeToFile(nameFile.str(), masses, false);
        masses.save(nameFile.str());
        
        
        averageMasses.addValue(averageS);
        numberClusters.addValue(clusters.size());
        LinearRegression lr;
        lr.calculate(masses.setOfValuesEuclidean);
        masses.slopeRegression=lr.slope;
        masses.interceptRegression=lr.intercept;
        masses.regression=true;
        std::cout<<"R2 masses clusters: "<<lr.R2<<'\n';
        evolutionR2Masses.addValue(lr.R2);
        slopeMasses.addValue(lr.slope);
        std::cout<<"slope of the loglog (aka. exponent distribution): "<<lr.slope<<'\n';
        
        //        Plot transitions;
        //        transitions.mode=Plot::EUCLIDEAN;
        //
        //        for(double i=0;i<clusters.size();i++){
        //            transitions.addValue(Point2d(log(i+1),log((double)(clusters[i].transitions.size())+1)));
        //        }
        
        //        lr.calculate(transitions.setOfValuesEuclidean);
        //        transitions.slopeRegression=lr.slope;
        //        transitions.interceptRegression=lr.intercept;
        //        transitions.regression=true;
        //        std::cout<<"R2 masses transitions: "<<lr.R2<<'\n';
        //        evolutionR2Transitions.addValue(lr.R2);
        
        
        if(visualizeResult){
            std::vector<Plot> plots;
            plots.clear();
            plots.push_back(masses);
            //        plots.push_back(transitions);
            Singleton<Windows>::instance().get(4)->drawPlot(plots);
            
        }
        if(clusters.size()>1){
            proportionFirstAndSecond.addValue((double)(clusters[indexesOrderClusters[0]].transitions.size())/(double)(clusters[indexesOrderClusters[1]].transitions.size()));
            std::cout<<"proportion: "<<(double)(clusters[indexesOrderClusters[0]].transitions.size())/(double)(clusters[indexesOrderClusters[1]].transitions.size())<<'\n';
        }
        //    Singleton<Windows>::instance().get(4)->zoomExtents();
        
        
        
        //    Singleton<Windows>::instance().get(5)->zoomExtents();
        
        
        
        stringstream nameNCOL;
        if(saveClusters){
            nameNCOL<<Configuration::folderOut()<<"giantClusterNCOL"<<angle<<".txt";
            //        stringstream nameCoordinates;
            //        nameCoordinates<<"/Users/carlos/Documents/results/angularNetworkPercolation/UK/smallAreaUK/"/<<"giantClusterCoordinates"<<angle<<".txt";
            TextFile::writeNCOLFile(&clustersPrimal[0], nameNCOL.str());
            //        saveGraph(&clustersPrimal[0], nameNCOL.str(), nameCoordinates.str(), " ", " ");
            
            nameNCOL.str("");
            nameNCOL<<Configuration::folderOut()<<"secondClusterNCOL"<<angle<<".txt";
            //        nameCoordinates.str("");
            //        nameCoordinates<<Configuration::folderOut()<<"secondClusterCoordinates"<<angle<<".txt";
            if(clustersPrimal.size()>1){
                TextFile::writeNCOLFile(&clustersPrimal[1], nameNCOL.str());
            }
        }
        
        
    }
    if(visualizeResult){
        std::vector<Plot> plots;
        plots.push_back(evolutionR2Masses);
        //    plots.push_back(evolutionR2Transitions);
        Singleton<Windows>::instance().get(5)->drawPlot(plots);
        plots.clear();
        plots.push_back(correlationLength);
        Singleton<Windows>::instance().get(3)->drawPlot(plots);
        plots.clear();
        plots.push_back(proportionFirstAndSecond);
        Singleton<Windows>::instance().get(7)->drawPlot(plots);
        plots.clear();
        plots.push_back(slopeMasses);
        Singleton<Windows>::instance().get(6)->drawPlot(plots);
        plots.clear();
        plots.push_back(averageMasses);
        Singleton<Windows>::instance().get(8)->drawPlot(plots);
        plots.clear();
        plots.push_back(evolutionMass1);
        Singleton<Windows>::instance().get(9)->drawPlot(plots);
        plots.clear();
        //    plots.push_back(evolutionMass1);
        plots.push_back(evolutionMass2);
        plots.push_back(evolutionMass3);
        plots.push_back(evolutionMass4);
        plots.push_back(evolutionMass5);
        Singleton<Windows>::instance().get(10)->drawPlot(plots);
        plots.clear();
        plots.push_back(fd);
        Singleton<Windows>::instance().get(11)->drawPlot(plots);
    }
    std::stringstream nameFile;
    nameFile<<Configuration::folderOut()<<"averageS.txt";
    
    averageMasses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"fractalDimension.txt";
    if(calculateFractalDimension){
        fd.save(nameFile.str());
    }
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"proportionFirstAndScond.txt";
    
    proportionFirstAndSecond.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"evolutionGiantCluster.txt";
    evolutionMass1.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"R2Masses.txt";
    evolutionR2Masses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"slopeMasses.txt";
    slopeMasses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"correlationLength.txt";
    if(measureCorrelationLength){
        correlationLength.save(nameFile.str());
    }
    std::vector<std::string> lines;
    lines.clear();
    for(long i=0;i<minRealGraph.transitions.size();i++){
        std::stringstream line;
        line.str("");
        line<<minRealGraph.transitions[i].a->originalID<<" "<<minRealGraph.transitions[i].b->originalID<<" "<<minRealGraph.transitions[i].levelHierarchyRoad;
        lines.push_back(line.str());
    }
    //    std::stringstream nameFile;
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"levelHierarchyRoad"<<".txt";
    TextFile::writeToFile(nameFile.str(), lines, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"entropy"<<".txt";
    TextFile::writeToFile(nameFile.str(), entropy, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"summaryEvolutionMasses"<<".txt";
    TextFile::writeToFile(nameFile.str(), linesFileMasses, false);
    
    
    
    
    
}


void Programs::performMetricNetworkPercolation(Graph* loadedGraph,std::vector<double> setOfDistances){
    bool generateSuperGraph=false;
    
    bool calculateCorrelationLength=false;
    bool calculateFractalDimension=false;
//    Graph loadedGraph;
    bool draw=false;
    bool saveClusters=false;
    
    //    double minSizeCity=50;
    ////////LOAD MINREALGRAPH
    
    //    minRealGraph.pseudoGraph=false;
    
//    Configuration::setFolder("/Users/carlos/Documents/");
//    Configuration::setSubFolderOut("results/hierarchicalPercolation/sum/UK/completeUK/");
    //
    //    Graph uk;
    //    uk.strictlyDirectional=false;
    //    std::cout<<"IMPORTING FILE UK"<<'\n';
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/UK_hierarchySumMetricAngular.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, " ", " ", true, false);
    //    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, ",", " ", true, false);
    //    uk.transformToBidirectional();
    //
    //    std::vector<Graph> clustersUK;
    //    uk.generateNetworkPercolation(300, clustersUK, false, true, "", 0, false);
    //    uk.orderClustersByMass(clustersUK);
    //    clustersUK[0].copyGraph(&clustersUK[0], &loadedGraph, false);
    //    loadedGraph.transformToBidirectional();
    //    std::stringstream nameLondon;
    //    nameLondon<<Configuration::folderOut()<<"londonNCOL.txt";
    //    TextFile::writeNCOLPlusCoordinatesFile(&loadedGraph, nameLondon.str());
    
    
    
    Graph minRealGraph;
    minRealGraph.strictlyDirectional=true;
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/clustersFromPercolation/UK/london/londonNCOL.txt", &loadedGraph, " ", false);
    //    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaNCOL.txt", "/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaCoordinates.txt", &loadedGraph, " ", " ", false, false);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/harmonicCities/uk_subArea.txt", &loadedGraph, " ", false);
//    loadedGraph.transformToBidirectional();
    //        std::stringstream nameLondon;
    //        nameLondon<<Configuration::folderOut()<<"londonNCOL.txt";
    //    std::stringstream nameLondonCoordinates;
    //    nameLondonCoordinates<<Configuration::folderOut()<<"londonCoordinates.txt";
    //    TextFile::writeNCOLFileAndSeparateCoordinatesFile(&loadedGraph, nameLondon.str(), nameLondonCoordinates.str(), " ", " ");
    
    
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/zzz_/gridNCOLAndCoord.txt", &loadedGraph, " ", true);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Dropbox/CASA/results/harmonicCities/minRealGraph2.txt", &minRealGraph, " ", false);
    //    TextFile::includeMasses(&minRealGraph, "/Users/carlos/Documents/results/harmonicCities/massesMinRealGraph.txt", " ", false);
    
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //        if(minRealGraph.nodes[i].mass<minSizeCity){
    //            minRealGraph.nodes[i].mass=0;
    //        }
    //    }
    
//    loadedGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    loadedGraph->getGiantComponent(loadedGraph, &minRealGraph);
    minRealGraph.transformToBidirectional();
    double totalMassOfTheSystem=minRealGraph.transitions.size()/2;//I need to divide it by 2 because minRealGraph is strictly directional and the clusters aren't so they have half the number of transitions
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //
    //
    //        minRealGraph.nodes[i].location.x+=-minX;
    //        minRealGraph.nodes[i].location.y+=-minY;
    //        minRealGraph.nodes[i].location.x*=width/75/1000;
    //        minRealGraph.nodes[i].location.y*=width/75/1000;
    //
    //
    //
    //
    //
    //    }
    ////////////////////////
    
    std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
    for(long i=0;i<minRealGraph.nodes.size();i++){
        nodesOriginalGraphByOriginalId[minRealGraph.nodes[i].originalID]=&minRealGraph.nodes[i];
        //        if(minRealGraph.nodes[i].mass>0){
        //            mainGraph.addNode();
        //            mainGraph.nodes[mainGraph.nodes.size()-1].location=minRealGraph.nodes[i].location;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].mass=minRealGraph.nodes[i].mass;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].originalID=minRealGraph.nodes[i].originalID;
        //
        //
        //
        //        }
    }
    
    if(draw){
        //////////////////
        Singleton<Windows>::instance().add(Point2d(15,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(475,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(935,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(1395,465), 430,200);
        //////////////////
        Singleton<Windows>::instance().add(Point2d(15,7.5), 430,430);
        Singleton<Windows>::instance().add(Point2d(475,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(475,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(935,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(935,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,465+230), 430,200);
        //////////////////
        
        Singleton<Windows>::instance().setTitle(0,"Original graph");
        Singleton<Windows>::instance().setTitle(1,"Giant cluster");
        Singleton<Windows>::instance().setTitle(2,"Second largest cluster");
        Singleton<Windows>::instance().setTitle(3,"Correlation length");
        Singleton<Windows>::instance().setTitle(4,"Log-Log of masses of clusters");
        Singleton<Windows>::instance().setTitle(5,"R2 of the correlation of masses");
        Singleton<Windows>::instance().setTitle(7,"Proportion between largest and second largest cluster");
        Singleton<Windows>::instance().setTitle(6,"Slopes of correlation of masses");
        Singleton<Windows>::instance().setTitle(8,"<S*>");
        Singleton<Windows>::instance().setTitle(9,"P_N(p)");
        Singleton<Windows>::instance().setTitle(10,"Evolution of masses");
        Singleton<Windows>::instance().setTitle(11,"Fractal dimension box-counting");
        
        VectorNDim vec;
        vec.values.clear();
        vec.values.push_back(0);
        vec.values.push_back(0);
        vec.values.push_back(0);
        vec.values.push_back(100);
//        Singleton<Windows>::instance().get(0)->drawGraph(&minRealGraph,vec);
        Singleton<Windows>::instance().get(0)->zoomExtents();
    }
    
    Plot evolutionR2Masses;
    //    Plot evolutionR2Transitions;
    evolutionR2Masses.limited=false;
    //    evolutionR2Transitions.limited=false;
    Plot proportionFirstAndSecond;
    proportionFirstAndSecond.limited=false;
    Plot slopeMasses;
    slopeMasses.limited=false;
    Plot averageMasses;
    averageMasses.limited=false;
    Plot numberClusters;
    numberClusters.limited=false;
    
    Plot evolutionMass1;
    evolutionMass1.limited=false;
    Plot evolutionMass2;
    evolutionMass2.limited=false;
    Plot evolutionMass3;
    evolutionMass3.limited=false;
    Plot evolutionMass4;
    evolutionMass4.limited=false;
    Plot evolutionMass5;
    evolutionMass5.limited=false;
    Plot correlationLength;
    correlationLength.limited=false;
    std::vector<std::vector<double> > probabilityRandomNodeInClusterOfNode;
    std::vector<double> entropy;
    Plot fd;
    fd.limited=false;
    
    //      saveGraph(&minRealGraph, "/Users/carlos/Documents/zzz_/smallAreaUKNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKCoordinates.txt", " ", " ");
    
    Graph lineGraph;
    if(calculateCorrelationLength){
        //    lineGraph.strictlyDirectional=false;
        minRealGraph.createLineGraph(&minRealGraph,&lineGraph);
    }
    //        lineGraph.transformToBidirectional();
    
    
    //    std::stringstream nameModel;
    //            nameModel<<Configuration::folderOut()<<"modelNCOL.txt";
    //    std::stringstream nameModelCoordinates;
    //nameModelCoordinates<<Configuration::folderOut()<<"modelCoordinates.txt";
    //        saveGraph(&minRealGraph,nameModel.str(), nameModelCoordinates.str(), " ", " ");
    
    
    //    Graph lineGraphlineGraph;
    //    lineGraphlineGraph.resetGraph();
    //    lineGraph.createLineGraph(&lineGraph, &lineGraphlineGraph);
    //    int indexWeight=lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0];
    //    for(long k=0;k<lineGraphlineGraph.transitions.size();k++){
    //
    //        Node* a=lineGraphlineGraph.transitions[k].a;
    //        Node* b=lineGraphlineGraph.transitions[k].b;
    //        Transition* transA=a->transitionThatRepresents;
    //        Transition* transB=b->transitionThatRepresents;
    //        lineGraphlineGraph.transitions[k].weight=(transA->otherWeights[indexWeight]+transB->otherWeights[indexWeight])/2;
    //        //        lineGraphlineGraph.transitions[k].weight=lineGraphlineGraph.transitions[k].otherWeights[lineGraphlineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
    //        //        lineGraphlineGraph.transitions[k].weight=1;
    //        //        std::cout<<"new weights "<<lineGraphlineGraph.transitions[k].weight<<'\n';
    //    }
    //    saveGraph(&lineGraphlineGraph, "/Users/carlos/Documents/zzz_/smallAreaUKLGLGNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKLGLGCoordinates.txt", " ", " ");
    
    QTree quadTreeLG;
    if(calculateCorrelationLength){
        lineGraph.insertGraphIntoQTree(&quadTreeLG);
    }
    
//    std::vector<double> setOfDistances;
    //    setOfAngles.push_back(45);
    //    setOfAngles.push_back(60);
    //    setOfAngles.push_back(85);
    //    setOfAngles.push_back(175);
    
    //    for(double i=10;i<20;i+=10){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=20;i<30;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=30;i<44;i+=1){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=44;i<45;i+=.5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=45;i<60;i+=1){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=60;i<70;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=70;i<85;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=85;i<95;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=95;i<100;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    double minDistance=Functions::min(setOfDistances);
//    double maxDistance=Functions::max(setOfDistances);
//    for(double i=minDistance;i<maxDistance;i+=.1){
//        setOfDistances.push_back(i);
//    }
    //    setOfAngles.push_back(45);
    
    std::vector<std::string> linesFileMasses;
    
    for(double h=0;h<setOfDistances.size();h++){
        double distance=setOfDistances[h];
        std::cout<<"===================="<<'\n';
        std::cout<<"distance : "<<distance<<'\n';
        Plot boxCounting;
        boxCounting.mode=Plot::EUCLIDEAN;
        long repetitions=1;
        std::vector<Graph> clusters;
        double averageMassGiantCluster=0;
        
        std::vector<long> indexesClustersOrderedBySize;
        
        for(long i=0;i<repetitions;i++){
            clusters.clear();
            std::stringstream nameClustersFile;
            nameClustersFile<<Configuration::folderOut()<<"clusters"<<distance<<".txt";
            //            saveClusters
            //            minRealGraph.generateNetworkPercolatio
            minRealGraph.generateNetworkPercolation(distance, clusters, saveClusters, true, nameClustersFile.str(), 0, false);
//            minRealGraph.orderClustersByMass(clusters);
            
            //            minRealGraph.generateAngularPercolation(&minRealGraph,&lineGraph, angle, clusters,0,false,false);
            
        }
        std::vector<double> values;
        
        for(long i=0;i<clusters.size();i++){
            values.push_back(clusters[i].transitions.size());
        }
        indexesClustersOrderedBySize=Functions::getIndexesOfOrderedValues(values, false);
        averageMassGiantCluster+=clusters[indexesClustersOrderedBySize[0]].transitions.size();
        
        averageMassGiantCluster/=(double)(repetitions);
        evolutionMass1.addValue(averageMassGiantCluster/(double)(totalMassOfTheSystem));
        
        
        FractalDimension fractalDimension;
        if(calculateFractalDimension){
//            fd.addValue(fractalDimension.calculateBoxCounting(&clusters[indexesClustersOrderedBySize[0]]));
        }
        
        Graph superGraphClusters;
        if(generateSuperGraph){
            minRealGraph.generateSuperGraphFromClusters(clusters, &minRealGraph, &superGraphClusters);
            
            //        std::vector<double> values;
            //        for(long i=0;i<superGraphClusters.nodes.size();i++){
            //            values.push_back(superGraphClusters.nodes[i].transitions.size());
            //        }
            std::stringstream nameFileSuperGraph;
            nameFileSuperGraph<<Configuration::folderOut()<<"superGraph_"<<distance<<".txt";
            TextFile::writeNCOLPlusCoordinatesFile(&superGraphClusters, nameFileSuperGraph.str());
        }
        
        
        
        
        
        //            minRealGraph.generateNetworkPercolation(angle, clusters,false, true, "", 0);
        //            minRealGraph.orderClustersByMass(clusters);
        
        //        std::vector<Graph> clustersPrimal;
        //        for(long j=0;j<clusters.size();j++){
        //            Graph clusterPrimal;
        //            std::vector<Transition*> transitions;
        //            for(long i=0;i<clusters[j].nodes.size();i++){
        //                transitions.push_back(clusters[j].nodes[i].transitionThatRepresents);
        //            }
        //
        //            minRealGraph.getInducedSubgraph(&clusterPrimal, transitions);
        //            clustersPrimal.push_back(clusterPrimal);
        //        }
        
        //        if(distance==minDistance){
        //            for(long i=0;i<lineGraph.nodes.size();i++){
        //                std::vector<double> values;
        //                probabilityRandomNodeInClusterOfNode.push_back(values);
        //                probabilityRandomNodeInClusterOfNode[i].push_back(0);
        //            }
        //        }
        double entropyTemp=0;
        for(double i=0;i<clusters.size();i++){
            
            double probabilityCluster=((double)clusters[i].transitions.size()/(double)totalMassOfTheSystem);
            entropyTemp+=probabilityCluster*log10(probabilityCluster);
        }
        for(double i=0;i<clusters.size();i++){
            
            //            double probabilityCluster=((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
            //            entropyTemp+=probabilityCluster*log(probabilityCluster);
            
            for(long j=0;j<clusters[i].transitions.size();j++){
                Node* a=nodesOriginalGraphByOriginalId[clusters[i].transitions[j].a->originalID];
//                Node* a=clusters[i].transitions[j].a->nodeThatRepresents;
                
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=(double)lclusters[i].transitions.size()/(double)lineGraph.nodes.size()*log((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
                //                double normalizedSize=Functions::normalize(log((double)clusters[i].transitions.size()),log((double)clusters[clusters.size()-1].transitions.size()),log((double)clusters[0].transitions.size()));
                //                double normalizedSize=Functions::normalize(((double)clusters[i].transitions.size()),((double)clusters[clusters.size()-1].transitions.size()),((double)clusters[0].transitions.size()));
                //                double maxRanking=clusters.size();
                //                double normalizedRanking=Functions::normalize(maxRanking-i, 0, maxRanking);
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=log((double)clusters[i].transitions.size());
                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=log((double)clusters[i].transitions.size())*(-entropyTemp);
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=i;
                
                
                
                
                
                //                Node* nodeLG=a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->nodeOfLineGraphThatRepresentsThis;
                //                if(distance==minDistance){
                //                    probabilityRandomNodeInClusterOfNode[nodeLG->id][0]=((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
                //                }else{
                //                    while(probabilityRandomNodeInClusterOfNode[nodeLG->id].size()<(h)){
                //                        probabilityRandomNodeInClusterOfNode[nodeLG->id].push_back(0);
                //                    }
                //                    probabilityRandomNodeInClusterOfNode[nodeLG->id].push_back((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
                //                }
            }
        }
        
        entropy.push_back(-entropyTemp);
        
        
        if((distance>minDistance)&draw){
            Singleton<Windows>::instance().add(1);
            Singleton<Windows>::instance().add(2);
            Singleton<Windows>::instance().add(3);
            Singleton<Windows>::instance().add(4);
        }
        
        
        if(draw){
            
//            Singleton<Windows>::instance().get(1)->drawGraph(&clusters[0]);
            Singleton<Windows>::instance().get(1)->copyViewParameters(Singleton<Windows>::instance().get(0));
            if(clusters.size()>1){
//                Singleton<Windows>::instance().get(2)->drawGraph(&clusters[1]);
                Singleton<Windows>::instance().get(2)->copyViewParameters(Singleton<Windows>::instance().get(0));
            }
        }
        //        Singleton<Windows>::instance().get(3)->copyViewParameters(Singleton<Windows>::instance().get(0));
        
        
        
        
        Plot masses;
        masses.mode=Plot::EUCLIDEAN;
        
        double averageMass=0;
        double totalMassWithoutGiantCluster=0;
        std::vector<Point2d> numberClustersOfASize;
        std::vector<double> radiiGyrationSquared;
        
        
        
        for(double i=0;i<clusters.size();i++){
            
            masses.addValue(Point2d(log(i+1),log((double)(clusters[indexesClustersOrderedBySize[i]].transitions.size())+1)));
            if(i>0){
                averageMass+=clusters[indexesClustersOrderedBySize[i]].transitions.size();
            }
            if(i==0){
                //                evolutionMass1.addValue((double)(clusters[i].nodes.size())/(double)(lineGraph.nodes.size()));
            }
            if(i==1){
                evolutionMass2.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            if(i==2){
                evolutionMass3.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            if(i==3){
                evolutionMass4.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            if(i==4){
                evolutionMass5.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            
            
            //
//            if(i>0||distance<=183){
            
            if(i!=indexesClustersOrderedBySize[0]){
                
                if(numberClustersOfASize.size()==0||clusters[indexesClustersOrderedBySize[i]].transitions.size()!=numberClustersOfASize[numberClustersOfASize.size()-1].x){
                    Point2d point;
                    point.x=clusters[indexesClustersOrderedBySize[i]].transitions.size();
                    point.y=1;
                    numberClustersOfASize.push_back(point);
                    
                    if(calculateCorrelationLength){
                        
                        Graph subGraphLineGraph;
                        //                    std::vector<Node*> nodesLGLG;
                        //                    for(long k=0;k<clusters[i].nodes.size();k++){
                        //                        for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                        //                            Node* a=clusters[i].nodes[k].transitions[g]->a->nodeThatRepresents;
                        //                            Node* b=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                        //                            Transition* trans=a->transitions[a->indexOfTransitionsByIdOfDestination[b->originalID]-1];
                        //                            Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                        //                            nodesLGLG.push_back(nodeLGLG);
                        //                        }
                        //                    }
                        //                    if(i>0){
                        std::vector<Node*> nodesSubgraphLG;
                        for(long k=0;k<clusters[indexesClustersOrderedBySize[i]].nodes.size();k++){
                            Node* nodeALG=clusters[indexesClustersOrderedBySize[i]].nodes[k].nodeThatRepresents;
                            Node* nodeBLG=NULL;
                            for(long g=0;g<clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions.size();g++){
                                nodeBLG=clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions[g]->b->nodeThatRepresents;
                            }
                            if(nodeBLG!=NULL){
                                Transition* trans=nodeALG->transitions[nodeALG->indexOfTransitionsByIdOfDestination[nodeBLG->originalID]-1];
                                Node* nodeLG=trans->nodeOfLineGraphThatRepresentsThis;
                                nodesSubgraphLG.push_back(nodeLG);
                            }
                        }
                        lineGraph.getInducedSubgraph(&subGraphLineGraph, nodesSubgraphLG);
                        //                    lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesLGLG);
                        //                    if (angle==7){
                        //                        saveGraph(&subGraphLineGraphLineGraph, "/Users/carlos/Documents/zzz_/subsmallAreaUKLGLGNCOL.txt", "/Users/carlos/Documents/zzz_/subsmallAreaUKLGLGCoordinates.txt", " ", " ");
                        //                        std::cout<<"index subgraph "<<i<<'\n';
                        //                        if(i==1){
                        //                            std::cout<<"problem"<<'\n';
                        //                        }
                        //                    }
                        
                        double radiusGyrationSquared=Graph::calculateSquaredGyrationRadiusInGraphSpace(&subGraphLineGraph,&lineGraph,&quadTreeLG);
                        
                        radiiGyrationSquared.push_back(radiusGyrationSquared);
                    }
                    //                    }else{
                    //                        radiiGyrationSquared.push_back(0);
                    //                    }
                }else{
                    numberClustersOfASize[numberClustersOfASize.size()-1].y++;
                    //                    Graph lineGraphlineGraph;
                    if(calculateCorrelationLength){
                        Graph subGraphLineGraph;
                        //                    std::vector<Node*> nodesLGLG;
                        //                    for(long k=0;k<clusters[i].nodes.size();k++){
                        //                        for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                        //                            Node* a=clusters[i].nodes[k].transitions[g]->a->nodeThatRepresents;
                        //                            Node* b=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                        //                            Transition* trans=a->transitions[a->indexOfTransitionsByIdOfDestination[b->originalID]-1];
                        //                            Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                        //                            nodesLGLG.push_back(nodeLGLG);
                        //                        }
                        //                    }
                        //                    lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesLGLG);
                        //                    if(i>0){
                        std::vector<Node*> nodesSubgraphLG;
                        for(long k=0;k<clusters[indexesClustersOrderedBySize[i]].nodes.size();k++){
                            Node* nodeALG=clusters[indexesClustersOrderedBySize[i]].nodes[k].nodeThatRepresents;
                            Node* nodeBLG=NULL;
                            for(long g=0;g<clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions.size();g++){
                                nodeBLG=clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions[g]->b->nodeThatRepresents;
                            }
                            if(nodeBLG!=NULL){
                                Transition* trans=nodeALG->transitions[nodeALG->indexOfTransitionsByIdOfDestination[nodeBLG->originalID]-1];
                                Node* nodeLG=trans->nodeOfLineGraphThatRepresentsThis;
                                nodesSubgraphLG.push_back(nodeLG);
                            }
                        }
                        lineGraph.getInducedSubgraph(&subGraphLineGraph, nodesSubgraphLG);
                        
                        double radiusGyrationSquared=Graph::calculateSquaredGyrationRadiusInGraphSpace(&subGraphLineGraph,&lineGraph,&quadTreeLG);
                        radiiGyrationSquared[numberClustersOfASize.size()-1]+=radiusGyrationSquared;
                    }
                    //                    }else{
                    ////                        radiiGyrationSquared.push_back(0);
                    //                    }
                }
                totalMassWithoutGiantCluster+=clusters[indexesClustersOrderedBySize[i]].transitions.size();
                
                
                
            }
            
        }
        averageMass/=(double)(clusters.size()-1);
        
        double averageS=0;
           double squaredSumOfMassesFiniteAndNotGiant=0;
        //        if(calculateCorrelationLength){
        double numeratorCorrelationLength=0;
        double denominatorCorrelationLength=0;
        
        for(long i=0;i<numberClustersOfASize.size();i++){
            averageS+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y/totalMassWithoutGiantCluster);
            squaredSumOfMassesFiniteAndNotGiant+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y);
            if(calculateCorrelationLength){
                double radiusGyrationSquared=radiiGyrationSquared[i]/numberClustersOfASize[i].y;
                //            numeratorCorrelationLength+=
                numeratorCorrelationLength+=2*radiusGyrationSquared*numberClustersOfASize[i].x*(numberClustersOfASize[i].x)*numberClustersOfASize[i].y/(double)(totalMassOfTheSystem);
                denominatorCorrelationLength+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x)*numberClustersOfASize[i].y/(double)(totalMassOfTheSystem);
            }
        }
        if(calculateCorrelationLength){
            correlationLength.addValue(pow(numeratorCorrelationLength/denominatorCorrelationLength,.5));
            std::cout<<"correlation length "<<pow(numeratorCorrelationLength/denominatorCorrelationLength,.5)<<'\n';
        }
        //        }
        
        std::stringstream lineTemp;
        lineTemp<<distance<<" "<<averageMassGiantCluster<<" "<<totalMassOfTheSystem<<" "<<squaredSumOfMassesFiniteAndNotGiant<<" "<<totalMassWithoutGiantCluster;
        linesFileMasses.push_back(lineTemp.str());
        
        std::vector<string> lines;
        stringstream line;
        line<<"totalMassPrimal"<<" "<<totalMassOfTheSystem;
        lines.push_back(line.str());
        line.str("");
        line<<"totalMassLineGraph"<<" "<<lineGraph.transitions.size();
        lines.push_back(line.str());
        stringstream nameFile;
        nameFile<<Configuration::folderOut()<<"globalMasses.txt";
        TextFile::writeToFile(nameFile.str(), lines, false);
        
        //        lines.clear();
        nameFile.str("");
        nameFile<<Configuration::folderOut()<<"masses"<<distance<<".txt";
        //        TextFile::writeToFile(nameFile.str(), masses, false);
        masses.save(nameFile.str());
        
        
        averageMasses.addValue(averageS);
        numberClusters.addValue(clusters.size());
        LinearRegression lr;
        lr.calculate(masses.setOfValuesEuclidean);
        masses.slopeRegression=lr.slope;
        masses.interceptRegression=lr.intercept;
        masses.regression=true;
        std::cout<<"R2 masses clusters: "<<lr.R2<<'\n';
        evolutionR2Masses.addValue(lr.R2);
        slopeMasses.addValue(lr.slope);
        std::cout<<"slope of the loglog (aka. exponent distribution): "<<lr.slope<<'\n';
        
        //        Plot transitions;
        //        transitions.mode=Plot::EUCLIDEAN;
        //
        //        for(double i=0;i<clusters.size();i++){
        //            transitions.addValue(Point2d(log(i+1),log((double)(clusters[i].transitions.size())+1)));
        //        }
        
        //        lr.calculate(transitions.setOfValuesEuclidean);
        //        transitions.slopeRegression=lr.slope;
        //        transitions.interceptRegression=lr.intercept;
        //        transitions.regression=true;
        //        std::cout<<"R2 masses transitions: "<<lr.R2<<'\n';
        //        evolutionR2Transitions.addValue(lr.R2);
        
        
        
        std::vector<Plot> plots;
        plots.clear();
        plots.push_back(masses);
        //        plots.push_back(transitions);
        if(draw){
            Singleton<Windows>::instance().get(4)->drawPlot(plots);
        }
        if(clusters.size()>1){
            proportionFirstAndSecond.addValue((double)(clusters[indexesClustersOrderedBySize[0]].transitions.size())/(double)(clusters[indexesClustersOrderedBySize[1]].transitions.size()));
            std::cout<<"proportion: "<<(double)(clusters[indexesClustersOrderedBySize[0]].transitions.size())/(double)(clusters[indexesClustersOrderedBySize[1]].transitions.size())<<'\n';
        }
        //    Singleton<Windows>::instance().get(4)->zoomExtents();
        
        
        
        //    Singleton<Windows>::instance().get(5)->zoomExtents();
        
        
        
        stringstream nameNCOL;
        nameNCOL<<Configuration::folderOut()<<"giantClusterNCOL"<<distance<<".txt";
        //        stringstream nameCoordinates;
        //        nameCoordinates<<"/Users/carlos/Documents/results/angularNetworkPercolation/UK/smallAreaUK/"/<<"giantClusterCoordinates"<<angle<<".txt";
        TextFile::writeNCOLFile(&clusters[indexesClustersOrderedBySize[0]], nameNCOL.str());
        //        saveGraph(&clustersPrimal[0], nameNCOL.str(), nameCoordinates.str(), " ", " ");
        
        nameNCOL.str("");
        nameNCOL<<Configuration::folderOut()<<"secondClusterNCOL"<<distance<<".txt";
        //        nameCoordinates.str("");
        //        nameCoordinates<<Configuration::folderOut()<<"secondClusterCoordinates"<<angle<<".txt";
        if(clusters.size()>1){
            TextFile::writeNCOLFile(&clusters[indexesClustersOrderedBySize[1]], nameNCOL.str());
        }
        
        
    }
    if(draw){
        std::vector<Plot> plots;
        plots.push_back(evolutionR2Masses);
        //    plots.push_back(evolutionR2Transitions);
        Singleton<Windows>::instance().get(5)->drawPlot(plots);
        plots.clear();
        plots.push_back(correlationLength);
        Singleton<Windows>::instance().get(3)->drawPlot(plots);
        plots.clear();
        plots.push_back(proportionFirstAndSecond);
        Singleton<Windows>::instance().get(7)->drawPlot(plots);
        plots.clear();
        plots.push_back(slopeMasses);
        Singleton<Windows>::instance().get(6)->drawPlot(plots);
        plots.clear();
        plots.push_back(averageMasses);
        Singleton<Windows>::instance().get(8)->drawPlot(plots);
        plots.clear();
        plots.push_back(evolutionMass1);
        Singleton<Windows>::instance().get(9)->drawPlot(plots);
        plots.clear();
        //    plots.push_back(evolutionMass1);
        plots.push_back(evolutionMass2);
        plots.push_back(evolutionMass3);
        plots.push_back(evolutionMass4);
        plots.push_back(evolutionMass5);
        Singleton<Windows>::instance().get(10)->drawPlot(plots);
        plots.clear();
        plots.push_back(fd);
        Singleton<Windows>::instance().get(11)->drawPlot(plots);
    }
    std::stringstream nameFile;
    nameFile<<Configuration::folderOut()<<"averageS.txt";
    
    averageMasses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"fractalDimension.txt";
    fd.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"proportionFirstAndScond.txt";
    
    proportionFirstAndSecond.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"evolutionGiantCluster.txt";
    evolutionMass1.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"R2Masses.txt";
    evolutionR2Masses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"slopeMasses.txt";
    slopeMasses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"correlationLength.txt";
    correlationLength.save(nameFile.str());
    
    std::vector<std::string> lines;
    lines.clear();
    for(long i=0;i<minRealGraph.transitions.size();i++){
        std::stringstream line;
        line.str("");
        line<<minRealGraph.transitions[i].a->originalID<<" "<<minRealGraph.transitions[i].b->originalID<<" "<<minRealGraph.transitions[i].levelHierarchyRoad;
        lines.push_back(line.str());
    }
    //    std::stringstream nameFile;
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"levelHierarchyRoad"<<".txt";
    TextFile::writeToFile(nameFile.str(), lines, false);
    
    
    lines.clear();
//    for(long i=0;i<minRealGraph.transitions.size();i++){
//        
//        std::stringstream line;
//        line.str("");
//        line<<minRealGraph.transitions[i].a->originalID<<" "<<minRealGraph.transitions[i].b->originalID;
//        for(long j=0;j<probabilityRandomNodeInClusterOfNode[i].size();j++){
//            line<<" "<<probabilityRandomNodeInClusterOfNode[i][j];
//        }
//        if(probabilityRandomNodeInClusterOfNode[i].size()>1){
//            lines.push_back(line.str());
//        }
//    }
//    //    std::stringstream nameFile;
//    nameFile.str("");
//    nameFile<<Configuration::folderOut()<<"probabilityRandomNodeInClusterOfNode"<<".txt";
//    TextFile::writeToFile(nameFile.str(), lines, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"entropy"<<".txt";
    TextFile::writeToFile(nameFile.str(), entropy, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"summaryEvolutionMasses"<<".txt";
    TextFile::writeToFile(nameFile.str(), linesFileMasses, false);
    
    
}










void Programs::generateCities(InterfaceCityGeneration* interface){
    
    interface->d0=2;//1.325;//.33/.3
    double minX=0;
    double minY=0;
    double maxX=1000;
    double maxY=1000;
    double definition=.5;
    interface->d0*=definition;
    interface->increment=1;
    interface->cityField.create(minX,minY,maxX,maxY,definition);
    interface->potentialField.create(minX,minY,maxX,maxY,definition*1);
    interface->saturationLevel=5*interface->increment;
    interface->saturationLevel=5;
    
//    std::vector<City> cities;
//    std::vector<long> indexCitiesByClusterId;
    
    interface->indexCitiesByClusterId.resize(interface->cityField.clusters.size(),-1);
    
    
    for(long i=0;i<interface->cityField.clusters.size();i++){
        interface->cityGraph.addNode();
        interface->cityGraph.nodes[interface->cityGraph.nodes.size()-1].location=interface->cityField.clusters[i].calculateCentroid();
        
    }
    
//    GENERATE INITIAL CITIES
    double initialIncrement=interface->increment;
    Point2d center=Point2d(500,500);
    long numberCitiesPerRow=2;
    double widthDispersion=800;
    for(long i=0;i<numberCitiesPerRow*numberCitiesPerRow;i++){
//        Point2d point=Point2d(Functions::runiform(minX, maxX),Functions::runiform(minY,maxY));
        long column=i%numberCitiesPerRow;
        long row=i/numberCitiesPerRow;
        double separation=(widthDispersion)/(numberCitiesPerRow-1);
        Point2d point=Point2d(center.x-widthDispersion/2+(column*separation),center.y-widthDispersion/2+(row*separation));
//        Point2d point=Point2d(Functions::runiform(minX,maxX),Functions::runiform(minY,maxY));
        interface->cityField.addValue(interface->cityField.getCluster(point), interface->cityField.getCluster(point)->value+initialIncrement);
        City city;
        city.node=&interface->cityGraph.nodes[interface->cityField.getCluster(point)->id];
        city.x=interface->cityField.getCluster(point)->value;
        interface->cities.push_back(city);
        interface->indexCitiesByClusterId[interface->cityField.getCluster(point)->id]=interface->cities.size()-1;
        addValuesToPotentialField(interface, interface->cityField.getCluster(point)->id, interface->increment);
        addMetropolisis(interface, interface->cityField.getCluster(point)->id);

    }
    Singleton<Windows>::instance().add(Point2d(15,15), 850,850);
    Singleton<Windows>::instance().setTitle(0,"Cities");
    Singleton<Windows>::instance().get(0)->drawPotentialField(&interface->cityField,true,false,true);
    Singleton<Windows>::instance().get(0)->zoomExtents();
    Singleton<Windows>::instance().add(Point2d(900,15), 500,500);
    Singleton<Windows>::instance().setTitle(1,"Potential field");
    Singleton<Windows>::instance().get(1)->drawPotentialField(&interface->potentialField,false,false,false);
    Singleton<Windows>::instance().get(1)->zoomExtents();
    Singleton<Windows>::instance().add(Point2d(900,560), 500,300);
//    return interface;
    
    
    
    
}

void Programs::loopGenerateCities(InterfaceCityGeneration* interface,long generation,bool draw){
    bool random=false;
    if(random){
        interface->saturationLevel=INFINITY;
    }
    Plot plotPopulationSquares;
    plotPopulationSquares.mode=Plot::EUCLIDEAN;
    long numberIterations=1;
    
    std::vector<double> values;
    double totalmass=0;
    if(draw){
        
        for(long i=0;i<interface->metropolises.size();i++){
            double value=interface->metropolises[i].calculateSize(interface);
//            std::cout<<"metropolis "<<i<<" "<<generation<<" "<<value<<'\n';
            if(value>0){
                values.push_back(value);
            }
            totalmass+=value;
        }
//        for(long j=0;j<interface->cities.size();j++){
//            double value=interface->cities[j].x;
//            if(value>0){
//                values.push_back(value);
//            }
//        }
        
    }
    values=Functions::orderValues(values,false);
    double ranking=1;
    double entropy=0;
    double k=1;
    for(long i=0;i<values.size();i++){
        plotPopulationSquares.addValue(Point2d(log(ranking),log(values[i])));
        double probability=values[i]/totalmass;
        entropy+=-k*probability*log10(probability);
        ranking++;
    }

    if(draw){
        std::cout<<entropy<<'\n';
        LinearRegression lr;
        lr.calculate(plotPopulationSquares.setOfValuesEuclidean);
        plotPopulationSquares.slopeRegression=lr.slope;
        plotPopulationSquares.interceptRegression=lr.intercept;
        plotPopulationSquares.regression=true;
//        std::cout<<"regression slope "<<lr.slope<<'\n';
    }
//    interface->metropolises=getMetropolises(interface);
    

    for(long k=0;k<numberIterations;k++){
        
//        interface->potentialField.reset();
//        for (long i=0;i<interface->cities.size();i++){
//            
//            double population=interface->cities[i].x;
//            
//            for(long j=0;j<interface->potentialField.clusters.size();j++){
//                double distance=Functions::getDistance(interface->potentialField.clusters[j].calculateCentroid(), interface->cities[i].node->location);
//                double valueToAdd=Functions::decay(distance, interface->d0)*population;
//                interface->potentialField.addValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd);
//                
//            }
//            
//        }
        std::vector<double> idsToRandomlyChooseFromDistributionOfPotential;
        if(!random){
            long numberRepetitions=10;
            for(long j=0;j<interface->potentialField.clusters.size();j++){
                double value=interface->potentialField.getNormalizedValue(&interface->potentialField.clusters[j]);
                for(long i=0;i<numberRepetitions;i++){
                    double random=Functions::runiform(0, 1);
                    if (random<value){
                        idsToRandomlyChooseFromDistributionOfPotential.push_back(interface->potentialField.clusters[j].id);
                    }
                }
            }
        }else{
            idsToRandomlyChooseFromDistributionOfPotential.push_back(Functions::runiform(0,interface->potentialField.clusters.size()-1));
        }
        double randomId=-1;
        long numberOfCitiesToAddPerIteration=1;
        if(idsToRandomlyChooseFromDistributionOfPotential.size()>0){
            for(long j=0;j<numberOfCitiesToAddPerIteration;j++){
                randomId=idsToRandomlyChooseFromDistributionOfPotential[Functions::runiform(0, idsToRandomlyChooseFromDistributionOfPotential.size()-1)];
                double initialPopulationValue=interface->cityField.clusters[randomId].value;
                long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                if(initialPopulationValue==0){
                    interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
                
                    City city;
                    city.node=&interface->cityGraph.nodes[interface->cityField.clusters[randomId].id];
                    city.x=interface->cityField.clusters[randomId].value;
                    interface->cities.push_back(city);
                    interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id]=interface->cities.size()-1;
                    indexCity=interface->cities.size()-1;
                    if(!random){
                        addValuesToPotentialField(interface, randomId, interface->increment);
                    }
                    addMetropolisis(interface, interface->cityField.clusters[randomId].id);
                }else{
                    if(interface->cityField.clusters[randomId].value+interface->increment<interface->saturationLevel){
                        interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
//                        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                        if(!random){
                            addValuesToPotentialField(interface, randomId, interface->increment);
                        }
                    }else{
                        double remaining=interface->cityField.clusters[randomId].value+interface->increment-interface->saturationLevel;
                        interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->saturationLevel);
                        if(!random){
                            addValuesToPotentialField(interface, randomId, interface->saturationLevel-interface->cityField.clusters[randomId].value);
                        }
                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                        
                        std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
                        std::vector<City*> cityNeighbors;
                        if(neighbors.size()>0){
//                            for(long i=0;i<neighbors.size();i++){
//                                if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                                    cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                                    Transition trans;
//                                    trans.a=interface->cities[indexCity].node;
//                                    trans.b=cityNeighbors[cityNeighbors.size()-1]->node;
//                                    trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                                    if(trans.a!=NULL&&trans.b!=NULL){
//                                        if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
//                                            interface->cityGraph.addDirectedTransition(trans);
//                                        }else{
//                                            trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                                        }
//                                    }
//                                }
//                                
//                            }
                            if(remaining>0&&!random){
                                randomId=cascade(interface,interface->cityField.clusters[randomId].id,remaining);
                            }
                        }
                        
                        
                        
                        
                        
                    }
                }
//                std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//                std::vector<City*> cityNeighbors;
//                if(neighbors.size()>0){
//                    for(long i=0;i<neighbors.size();i++){
//                        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                            cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                            Transition trans;
//                            trans.a=cityNeighbors[cityNeighbors.size()-1]->node;
//                            trans.b=interface->cities[indexCity].node;
//                            trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                            if(trans.a!=NULL&&trans.b!=NULL){
//                                if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1!=-1){
//                                    trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                                }
//                            }
//                        }
//                    }
//                }
            }
        }
       
        
    }
    if(draw){
        Singleton<Windows>::instance().get(0)->deleteTemporary();
        Singleton<Windows>::instance().get(1)->deleteTemporary();
        Singleton<Windows>::instance().get(2)->deleteTemporary();
        Singleton<Windows>::instance().get(0)->drawPotentialField(&interface->cityField,true,false,true);
        Singleton<Windows>::instance().get(1)->drawPotentialField(&interface->potentialField,false,false,false);
        std::vector<Plot> plots;
        plots.push_back(plotPopulationSquares);
        Singleton<Windows>::instance().get(2)->drawPlot(plots);
    }
}



long Programs::cascade(InterfaceCityGeneration* interface,long idClusterInit,long numberPeopleToMove){
    long idReturn=idClusterInit;
//    long previousId=idClusterInit;
    
    while(numberPeopleToMove>0){
    std::vector<ClusterField*> neighbors=interface->potentialField.vonNeumannNeighborhood(&interface->potentialField.clusters[idClusterInit]);
    std::vector<double> values;
    for(long i=0;i<neighbors.size();i++){
        
        values.push_back(neighbors[i]->value);
    }
//    std::vector<long> indexOrderedValues=Functions::getIndexesOfOrderedValues(values, true);
    double remaining=numberPeopleToMove;
    
    
    
    
     
//    for(long j=0;j<numberOfCitiesToAddPerIteration;j++){
        std::vector<double> normValues=Functions::normalize(values);
    std::vector<long> idsToChooseFrom;
    for(long i=0;i<normValues.size();i++){
//        double min=neighbors[indexOrderedValues[0]]->value;
//        if(neighbors[indexOrderedValues[i]]->id==previousId){
//            min=neighbors[indexOrderedValues[1]]->value;
//        }
//        if(neighbors[indexOrderedValues[i]]->value==min){
        for(long j=0;j<10;j++){
            
            double random=Functions::runiform(0,1);
            if(random<1-normValues[i]){
                idsToChooseFrom.push_back(i);
            }
//            idsToChooseFrom.push_back(indexOrderedValues[i]);
        }
    }
        if(idsToChooseFrom.size()==0){
            for(long i=0;i<neighbors.size();i++){
                idsToChooseFrom.push_back(i);
            }
        }
  
        double randomId=neighbors[idsToChooseFrom[Functions::runiform(0, idsToChooseFrom.size()-1)]]->id;
//        double randomId=neighbors[random()%neighbors.size()]->id;
    
        double initialPopulationValue=interface->cityField.clusters[randomId].value;
        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
        if(initialPopulationValue==0){
            interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
            
            City city;
            city.node=&interface->cityGraph.nodes[interface->cityField.clusters[randomId].id];
            city.x=interface->cityField.clusters[randomId].value;
            interface->cities.push_back(city);
            interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id]=interface->cities.size()-1;
            indexCity=interface->cities.size()-1;
            remaining=0;
            addValuesToPotentialField(interface, randomId, interface->increment);
            addMetropolisis(interface, interface->cityField.clusters[randomId].id);
        }else{
            if(interface->cityField.clusters[randomId].value+interface->increment<=interface->saturationLevel){
                interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
                //                        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                remaining=0;
                addValuesToPotentialField(interface, randomId, interface->increment);
            }else{
                remaining=interface->cityField.clusters[randomId].value+interface->increment-interface->saturationLevel;
                interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->saturationLevel);
                addValuesToPotentialField(interface, randomId, interface->saturationLevel-interface->cityField.clusters[randomId].value);
                interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                
//                std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//                std::vector<City*> cityNeighbors;
//                if(neighbors.size()>0){
//                    for(long i=0;i<neighbors.size();i++){
//                        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                            cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                            Transition trans;
//                            trans.a=interface->cities[indexCity].node;
//                            trans.b=cityNeighbors[cityNeighbors.size()-1]->node;
//                            trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                            if(trans.a!=NULL&&trans.b!=NULL){
//                                if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
//                                    interface->cityGraph.addDirectedTransition(trans);
//                                }else{
//                                    trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                                }
//                            }
//                        }
//                        
//                    }
//                    
//                }
                
                
                
                
                
            }
        }
//        neighbors.clear();
//        neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//        std::vector<City*> cityNeighbors;
//        if(neighbors.size()>0){
//            for(long i=0;i<neighbors.size();i++){
//                if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                    cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                    Transition trans;
//                    trans.a=cityNeighbors[cityNeighbors.size()-1]->node;
//                    trans.b=interface->cities[indexCity].node;
//                    trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                    if(trans.a!=NULL&&trans.b!=NULL){
//                        if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1!=-1){
//                            trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                        }
//                    }
//                }
//            }
//        }
        
//    }
        numberPeopleToMove=remaining;
        idClusterInit=interface->cityField.clusters[randomId].id;
        idReturn=idClusterInit;
    }
    
//    if(remaining>0){
//        idReturn=cascade(interface,interface->cityField.clusters[randomId].id,remaining);
//    }
    
    return idReturn;
    
    
    
}

void Programs::addValuesToPotentialField(InterfaceCityGeneration* interface,long idCluster,long numberPeopleAdded){
    long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[idCluster].id];
    double population=numberPeopleAdded;
    
    for(long j=0;j<interface->potentialField.clusters.size();j++){
        Point2d pointTemp=interface->potentialField.clusters[j].calculateCentroid();
        double distance=Functions::getDistance(pointTemp, interface->cities[indexCity].node->location);
        double valueToAdd=Functions::decay(distance, interface->d0)*population;
        interface->potentialField.addValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd);
        
    }
}


void Programs::addMetropolisis(InterfaceCityGeneration* interface,long clusterId){
//    std::vector<Metropolis> metropolises;
//    std::vector<int> occupiedClusters;
    std::vector<ClusterField*> neighbors=interface->potentialField.vonNeumannNeighborhood(&interface->potentialField.clusters[clusterId]);
    std::vector<City*> neighboringCities;
    std::vector<long> metropolisIds;
    for(long i=0;i<neighbors.size();i++){
        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
            neighboringCities.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
            metropolisIds.push_back(interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]].metropolisId);
        }
    }
    if(neighboringCities.size()==0){
        interface->maxIdMetropolis++;
        Metropolis metropolis;
        metropolis.citiesIndexes.push_back(interface->indexCitiesByClusterId[clusterId]);
        metropolis.id=interface->maxIdMetropolis;
        interface->cities[interface->indexCitiesByClusterId[clusterId]].metropolisId=interface->maxIdMetropolis;
        interface->metropolises.push_back(metropolis);
    }else{
        std::vector<long> uniqueMetropolisIds=Functions::unique(metropolisIds);
        if(uniqueMetropolisIds.size()==1){
//            interface->maxIdMetropolis++;
//            Metropolis metropolis;
            interface->metropolises[uniqueMetropolisIds[0]].citiesIndexes.push_back(interface->indexCitiesByClusterId[clusterId]);
//            metropolis.id=interface->maxIdMetropolis;
            interface->cities[interface->indexCitiesByClusterId[clusterId]].metropolisId=uniqueMetropolisIds[0];
//            interface->metropolises.push_back(metropolis);
        }else{
            std::vector<long> sizesMetropolises;
            for(long i=0;i<uniqueMetropolisIds.size();i++){
                sizesMetropolises.push_back(interface->metropolises[uniqueMetropolisIds[i]].calculateSize(interface));
            }
            std::vector<long> indexesMetropolisesBySize=Functions::getIndexesOfOrderedValues(sizesMetropolises, false);
            Metropolis* mainMetropolis=&interface->metropolises[uniqueMetropolisIds[indexesMetropolisesBySize[0]]];
            for(long i=1;i<indexesMetropolisesBySize.size();i++){
                Metropolis* currentMetropolis=&interface->metropolises[uniqueMetropolisIds[indexesMetropolisesBySize[i]]];
                
                
                for(long j=0;j<currentMetropolis->citiesIndexes.size();j++){
                    interface->cities[currentMetropolis->citiesIndexes[j]].metropolisId=mainMetropolis->id;
                    mainMetropolis->citiesIndexes.push_back(currentMetropolis->citiesIndexes[j]);
                }
                currentMetropolis->citiesIndexes.clear();
            }
            interface->metropolises[uniqueMetropolisIds[0]].citiesIndexes.push_back(interface->indexCitiesByClusterId[clusterId]);
            interface->cities[interface->indexCitiesByClusterId[clusterId]].metropolisId=uniqueMetropolisIds[0];
        }
    }
    
//    occupiedClusters.resize(interface->cityField.clusters.size(),0);
//    for(long i=0;i<interface->cityField.clusters.size();i++){
//        if(interface->cityField.clusters[i].value>=interface->saturationLevel){
//            //            interface->cityField.clusters[i].
//        }
//    }
//    return metropolises;
}





void Programs::migrate(InterfaceCityGeneration* interface,double proportionMigrations){

//    long totalNumberMigrations=(long)((double)interface->cities.size()*proportionMigrations);
    long totalNumberMigrations=1;
    
    
    bool random=false;
    long totalNumberMigrationsFinal=totalNumberMigrations;
    for(long i=0;i<totalNumberMigrations;i++){
        long idCity=long(Functions::runiform(0, interface->cities.size()));
        if(interface->cities[idCity].x>=interface->increment){
            interface->cities[idCity].x=-interface->increment;
        }else{
            totalNumberMigrationsFinal--;
        }
        
    }
    
    
    
    
    
    
    
    
    
    
    for(long k=0;k<totalNumberMigrationsFinal;k++){
        
        //        interface->potentialField.reset();
        //        for (long i=0;i<interface->cities.size();i++){
        //
        //            double population=interface->cities[i].x;
        //
        //            for(long j=0;j<interface->potentialField.clusters.size();j++){
        //                double distance=Functions::getDistance(interface->potentialField.clusters[j].calculateCentroid(), interface->cities[i].node->location);
        //                double valueToAdd=Functions::decay(distance, interface->d0)*population;
        //                interface->potentialField.addValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd);
        //
        //            }
        //
        //        }
        std::vector<double> idsToRandomlyChooseFromDistributionOfPotential;
        if(!random){
            long numberRepetitions=10;
            for(long j=0;j<interface->potentialField.clusters.size();j++){
                double value=interface->potentialField.getNormalizedValue(&interface->potentialField.clusters[j]);
                for(long i=0;i<numberRepetitions;i++){
                    double random=Functions::runiform(0, 1);
                    if (random<value){
                        idsToRandomlyChooseFromDistributionOfPotential.push_back(interface->potentialField.clusters[j].id);
                    }
                }
            }
        }else{
            idsToRandomlyChooseFromDistributionOfPotential.push_back(Functions::runiform(0,interface->potentialField.clusters.size()-1));
        }
        double randomId=-1;
        long numberOfCitiesToAddPerIteration=1;
        if(idsToRandomlyChooseFromDistributionOfPotential.size()>0){
            for(long j=0;j<numberOfCitiesToAddPerIteration;j++){
                randomId=idsToRandomlyChooseFromDistributionOfPotential[Functions::runiform(0, idsToRandomlyChooseFromDistributionOfPotential.size()-1)];
                double initialPopulationValue=interface->cityField.clusters[randomId].value;
                long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                if(initialPopulationValue==0){
                    interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
                    
                    City city;
                    city.node=&interface->cityGraph.nodes[interface->cityField.clusters[randomId].id];
                    city.x=interface->cityField.clusters[randomId].value;
                    interface->cities.push_back(city);
                    interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id]=interface->cities.size()-1;
                    indexCity=interface->cities.size()-1;
                    if(!random){
                        addValuesToPotentialField(interface, randomId, interface->increment);
                    }
                    addMetropolisis(interface, interface->cityField.clusters[randomId].id);
                }else{
                    if(interface->cityField.clusters[randomId].value+interface->increment<interface->saturationLevel){
                        interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
                        //                        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                        if(!random){
                            addValuesToPotentialField(interface, randomId, interface->increment);
                        }
                    }else{
                        double remaining=interface->cityField.clusters[randomId].value+interface->increment-interface->saturationLevel;
                        interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->saturationLevel);
                        if(!random){
                            addValuesToPotentialField(interface, randomId, interface->saturationLevel-interface->cityField.clusters[randomId].value);
                        }
                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                        
                        std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
                        std::vector<City*> cityNeighbors;
                        if(neighbors.size()>0){
                            //                            for(long i=0;i<neighbors.size();i++){
                            //                                if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
                            //                                    cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
                            //                                    Transition trans;
                            //                                    trans.a=interface->cities[indexCity].node;
                            //                                    trans.b=cityNeighbors[cityNeighbors.size()-1]->node;
                            //                                    trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
                            //                                    if(trans.a!=NULL&&trans.b!=NULL){
                            //                                        if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
                            //                                            interface->cityGraph.addDirectedTransition(trans);
                            //                                        }else{
                            //                                            trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
                            //                                        }
                            //                                    }
                            //                                }
                            //
                            //                            }
                            if(remaining>0&&!random){
                                randomId=cascade(interface,interface->cityField.clusters[randomId].id,remaining);
                            }
                        }
                        
                        
                        
                        
                        
                    }
                }
                //                std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
                //                std::vector<City*> cityNeighbors;
                //                if(neighbors.size()>0){
                //                    for(long i=0;i<neighbors.size();i++){
                //                        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
                //                            cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
                //                            Transition trans;
                //                            trans.a=cityNeighbors[cityNeighbors.size()-1]->node;
                //                            trans.b=interface->cities[indexCity].node;
                //                            trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
                //                            if(trans.a!=NULL&&trans.b!=NULL){
                //                                if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1!=-1){
                //                                    trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
                //                                }
                //                            }
                //                        }
                //                    }
                //                }
            }
        }
    }
}


void Programs::calculateNumberIntersectionsCloseToIntersections(){
    
    Graph uk;
    std::cout<<"IMPORTING FILE UK"<<'\n';
    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &uk, ",", " ", true, false);
    uk.transformToBidirectional();
    uk.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    Configuration::setFolder("/Users/carlos/Documents/");
    Configuration::setSubFolderOut("results/cityGrowth/");
    std::vector<Graph> clusters;
    std::cout<<"PERCOLATING "<<'\n';
    uk.generateNetworkPercolation(300, clusters, false, true, "", 244, false);
//    std::cout<<"ORDER CLUSTERS "<<'\n';
//    uk.orderClustersByMass(clusters);
    std::vector<string> strings;
    
    for(long j=0;j<clusters.size();j++){
        std::cout<<"cluster "<<j<<" mass "<<clusters[j].nodes.size()<<'\n';
        QTree qtree;
        clusters[j].insertGraphIntoQTree(&qtree);
        for(long i=0;i<clusters[j].nodes.size();i++){
            if((long)(((double)(i)/(double)(clusters[j].nodes.size())*100))%10==0){
                std::cout<<(double)(i)/(double)(clusters[j].nodes.size())*100<<" %"<<'\n';
            }
            std::vector<Node*> nodes=qtree.getNodesInARange(clusters[j].nodes[i].location, 180);
            std::stringstream ss;
            ss<<clusters[j].nodes[i].originalID<<" "<<nodes.size();
            strings.push_back(ss.str());
        }
    }
    std::stringstream name;
    name<<Configuration::folderOut()<<"numberIntersectionsPerIntersection.txt";
    TextFile::writeToFile(name.str(), strings, false);
    
    
    
}




void Programs::expandValuesThroughNetwork(){
    std::vector<Point2d> locations;
    std::vector<double> strength;
//    std::vector<Node*> nodesAirports;
    std::cout<<"loading graph"<<'\n';
    bool useLocations=false;
    
    
    
    Graph uk;
    Graph graph;
    //    /Users/carlos/Dropbox/CASA/results/cityGrowth/UK_timeWeights.txt
    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/UK_hierarchyAngularWeights.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &graph, " ", " ", true, false);
    //    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &uk, ",", " ", true, false);
    
    //    uk.transformToBidirectional();
    //
    //    uk.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    //        std::cout<<"get giant component"<<'\n';
    ////      Graph graph;
    //    uk.getGiantComponent(&uk, &graph);
    graph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    graph.transformToBidirectional();
    if(useLocations){
        TextFile::loadPointLocationsAndValue("/Users/carlos/Dropbox/CASA/results/cityGrowth/LocationNodesAndHierarchyMetric.txt", locations, strength, true, " ");
//      TextFile::loadPointLocationsAndValue("/Users/carlos/Dropbox/CASA/data/GIS/UK/massesOfHierarchyMetric.txt", airportLocations, numberPassengers, true, " ");
    }else{
        TextFile::includeMasses(&graph, "/Users/carlos/Dropbox/CASA/results/cityGrowth/massesOfHierarchyMetric.txt", " ", true);
    }

    QTree qTree;
    std::vector<double> diffusionValues;
    if(useLocations){
        std::cout<<"insert into quadTree"<<'\n';
        graph.insertGraphIntoQTree(&qTree);
    
        
        diffusionValues.resize(graph.nodes.size(), 0);
        std::cout<<"starting calculations"<<'\n';
        
        for(long j=0;j<locations.size();j++){
                std::cout<<"element "<<j<<" of "<<locations.size()<<'\n';
            Node* nodeInit;

            nodeInit=qTree.getClosestNode(locations[j]);
   
//            nodesAirports.push_back(nodeInit);
            double limitSensitivity=.1;
            double softenParameter=1;
            double numberFinal=softenParameter*strength[j];
            double d0=10;
            double distanceLimit=d0*pow((numberFinal-limitSensitivity)/limitSensitivity,.5);
            nodeInit->minDistance=0;
            
            std::vector<Node*> nodesCutoff;
            Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
            nodesCutoff.push_back(nodeInit);
            nodeInit->inCutoff=true;
            nodesToCheckDijkstra.push(nodeInit);
            nodeInit->inDijkstra=true;

            graph.calculateDijkstraSpeed(nodeInit, distanceLimit, nodesCutoff, nodesToCheckDijkstra);
            
            for(long i=0;i<nodesCutoff.size();i++){
    //            if(nodesCutoff[i]->minDistance<1){
    //                diffusionValues[nodesCutoff[i]->id]+=softenParameter*numberPassengers[j];
    //            }else
                    if(nodesCutoff[i]->minDistance<INFINITY){
                        diffusionValues[nodesCutoff[i]->id]+=numberFinal/(1+pow(nodesCutoff[i]->minDistance/d0,2));
                }
            }
            
            for(long i=0; i<graph.nodes.size(); i++)
            {
                
                graph.nodes[i].inCutoff=false;
                
                graph.nodes[i].inDijkstra=false;
                graph.nodes[i].numChildren=0;
                graph.nodes[i].numChildrenThatReachedMe=0;
                graph.nodes[i].parent=NULL;
                graph.nodes[i].minDistance=INFINITY;
                graph.nodes[i].valueToPass= graph.nodes[i].originalValueToPass;
                
                
            }
        }
    }else{
        
        diffusionValues.resize(graph.nodes.size(), 0);
        std::cout<<"starting calculations"<<'\n';
//        graph.nodes.size()
        for(long j=0;j< graph.nodes.size();j++){
            std::cout<<"element "<<j<<" of "<<graph.nodes.size()<<'\n';
            Node* nodeInit=&graph.nodes[j];

            double limitSensitivity=.5;
            double softenParameter=.1;
            
            double numberFinal=softenParameter*nodeInit->mass;
            double d0=5;
            double distanceLimit=d0*pow((numberFinal-limitSensitivity)/limitSensitivity,.5);
            nodeInit->minDistance=0;
            
            std::vector<Node*> nodesCutoff;
            Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
            nodesCutoff.push_back(nodeInit);
            nodeInit->inCutoff=true;
            nodesToCheckDijkstra.push(nodeInit);
            nodeInit->inDijkstra=true;
            
            graph.calculateDijkstraSpeed(nodeInit, distanceLimit, nodesCutoff, nodesToCheckDijkstra);
            
            for(long i=0;i<nodesCutoff.size();i++){
                //            if(nodesCutoff[i]->minDistance<1){
                //                diffusionValues[nodesCutoff[i]->id]+=softenParameter*numberPassengers[j];
                //            }else
                if(nodesCutoff[i]->minDistance<INFINITY){
                    diffusionValues[nodesCutoff[i]->id]+=numberFinal/(1+pow(nodesCutoff[i]->minDistance/d0,2));
                }
            }
            
            for(long i=0; i<graph.nodes.size(); i++)
            {
                
                graph.nodes[i].inCutoff=false;
                
                graph.nodes[i].inDijkstra=false;
                graph.nodes[i].numChildren=0;
                graph.nodes[i].numChildrenThatReachedMe=0;
                graph.nodes[i].parent=NULL;
                graph.nodes[i].minDistance=INFINITY;
                graph.nodes[i].valueToPass= graph.nodes[i].originalValueToPass;
                
                
            }
        }
    }
    std::cout<<"saving result"<<'\n';
    std::vector<std::string> result;
    for(long i=0;i<graph.nodes.size();i++){
        std::stringstream ss;
        ss<<graph.nodes[i].originalID<<" "<<diffusionValues[i];
        result.push_back(ss.str());
    }
    TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/diffusionHVMLorentziana.txt", result, false);
 
    
}





void Programs::calculateHierarchicalIndexPercolation(Graph* graph){
    double numberDivisions=15;
    bool saveClusters=false;
    Plot masses;
    masses.mode=Plot::EUCLIDEAN;
//    Configuration::setFolder("/Users/carlos/Documents/");
//    Configuration::setSubFolderOut("results/clustersFromPercolation/UK/completeUK/HI/");
//std::cout<<"loading graph"<<'\n';
//    Graph loadedGraph;
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/UK_hierarchySumMetricAngular.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, " ", " ", true, false);
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, ",", " ", true, false);
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaNCOL.txt", "/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaCoordinates.txt", &loadedGraph, " ", " ", false, false);
    
    
    Graph minRealGraph;
    minRealGraph.strictlyDirectional=true;

//    loadedGraph.transformToBidirectional();

//    loadedGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
//    std::cout<<"getting giant component"<<'\n';
    graph->getGiantComponent(graph, &minRealGraph);
    minRealGraph.transformToBidirectional();
    double totalMassOfTheSystem=minRealGraph.transitions.size()/2;
    std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
    for(long i=0;i<minRealGraph.nodes.size();i++){
        nodesOriginalGraphByOriginalId[minRealGraph.nodes[i].originalID]=&minRealGraph.nodes[i];
        //        if(minRealGraph.nodes[i].mass>0){
        //            mainGraph.addNode();
        //            mainGraph.nodes[mainGraph.nodes.size()-1].location=minRealGraph.nodes[i].location;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].mass=minRealGraph.nodes[i].mass;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].originalID=minRealGraph.nodes[i].originalID;
        //
        //
        //
        //        }
    }
    std::vector<double> sizesClustersAllThresholds;
    std::vector<double> setOfDistances;

    std::vector<double> weights;
    for(long i=0;i<minRealGraph.transitions.size();i++){
        weights.push_back(minRealGraph.transitions[i].weight);
    }
    weights=Functions::orderValues(weights, true);
    std::vector<double> probabilities;
    for(double i=1;i<numberDivisions;i++){
        probabilities.push_back(1/numberDivisions*i);
    }
    long j=0;
    double currentProbability=probabilities[j];
//    bool setDistance=true;
    for(long i=0;i<weights.size();i++){
//    long i=0;
//    while(i<weights.size()){
        
        if((double)(i)/(double)weights.size()>currentProbability&&(double)(i-1)/(double)weights.size()<=currentProbability){
            j++;
            currentProbability=probabilities[j];
            setOfDistances.push_back(weights[i]);
            
        }
    }
    

    
    
//    double minDistance=setOfDistances[0];
//    double maxDistance=setOfDistances[setOfDistances.size()-1];
//    for(double i=minDistance;i<maxDistance;i+=100){
//        setOfDistances.push_back(i);
//    }

    
    std::vector<double> entropy;
    
    for(double h=0;h<setOfDistances.size();h++){

        double distance=setOfDistances[h];
        std::cout<<"distance: "<<distance<<'\n';
        long repetitions=1;
        std::vector<Graph> clusters;

        
        for(long i=0;i<repetitions;i++){
            clusters.clear();
            std::stringstream nameClustersFile;
            nameClustersFile<<Configuration::folderOut()<<"clusters"<<distance<<".txt";

            minRealGraph.generateNetworkPercolation(distance, clusters, saveClusters, true, nameClustersFile.str(), 0, false);

        }
        std::vector<double> valuesMasses;
        for(double i=0;i<clusters.size();i++){
            valuesMasses.push_back(clusters[i].transitions.size());
            
        }
        std::vector<long> orderMasses=Functions::getIndexesOfOrderedValues(valuesMasses, false);
        double entropyTemp=0;
        double totalMass=0;
        for(double i=0;i<clusters.size();i++){
            //            std::cout<<i<<" "<<clusters[orderMasses[i]].transitions.size()<<'\n';
            masses.addValue(Point2d(log(i+1),log((double)(clusters[orderMasses[i]].transitions.size())+1)));
            totalMass+=(double)(clusters[orderMasses[i]].transitions.size());
        }
        for(double i=0;i<clusters.size();i++){
//            std::cout<<i<<" "<<clusters[orderMasses[i]].transitions.size()<<'\n';
//            masses.addValue(Point2d(log(i+1),log((double)(clusters[orderMasses[i]].transitions.size())+1)));
//            totalMass+=(double)(clusters[orderMasses[i]].transitions.size());
//            double probabilityCluster=((double)clusters[i].transitions.size()/(double)minRealGraph.transitions.size());
            double probabilityCluster=((double)clusters[i].transitions.size()/totalMassOfTheSystem);
            entropyTemp+=probabilityCluster*log10(probabilityCluster);
        }
        LinearRegression lr;
        lr.calculate(masses.setOfValuesEuclidean);
        masses.slopeRegression=lr.slope;
        masses.interceptRegression=lr.intercept;
        masses.regression=true;

        for(double i=0;i<clusters.size();i++){
//            std::cout<<clusters[orderMasses[i]].transitions.size()<<" ranking "<<exp(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept)*lr.R2*(-entropyTemp)<<'\n';
//            std::cout<<lr.slope<<" "<<log((double)(clusters[orderMasses[i]].transitions.size()))<<" "<<lr.intercept<<" "<<lr.R2<<" "<<entropyTemp<<" "<<exp(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept)<<" "<<exp(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept)*lr.R2*(-entropyTemp)<<'\n';
//            double probabilityCluster=((double)clusters[orderMasses[i]].transitions.size()/(double)minRealGraph.transitions.size());
            double probabilityCluster=((double)clusters[orderMasses[i]].transitions.size()/totalMassOfTheSystem);
            sizesClustersAllThresholds.push_back((double)(clusters[orderMasses[i]].transitions.size())*(-entropyTemp));
            for(long j=0;j<clusters[orderMasses[i]].transitions.size();j++){
                 Node* a=nodesOriginalGraphByOriginalId[clusters[orderMasses[i]].transitions[j].a->originalID];
                
                if(a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.size()==0){
                    
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(log((double)(clusters[orderMasses[i]].transitions.size()*(-entropyTemp))));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(log((double)(clusters[orderMasses[i]].transitions.size()))*(-entropyTemp));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(log((double)(clusters[orderMasses[i]].transitions.size())));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(((double)(clusters[orderMasses[i]].transitions.size())*(-entropyTemp)));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(((double)(clusters[orderMasses[i]].transitions.size())));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(-(probabilityCluster*log10(probabilityCluster)));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()*(-entropyTemp)))+lr.intercept);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back((lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept)*(-entropyTemp));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept);
                    double maxRankingApprox=(lr.slope*log((double)(clusters[orderMasses[orderMasses.size()-1]].transitions.size()))+lr.intercept);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(maxRankingApprox-(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept));
                    double maxRanking=orderMasses.size();
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(maxRanking-i+1);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(maxRanking-i+1);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(log(maxRanking-i+1));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(i+1);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(i+1);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues.push_back(log(i+1));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->numberTimesInPercolationThreshold++;
                    
                }else{
                    
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[0]+=(log((double)(clusters[orderMasses[i]].transitions.size()*(-entropyTemp))));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[1]+=(log((double)(clusters[orderMasses[i]].transitions.size()))*(-entropyTemp));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[2]+=(log((double)(clusters[orderMasses[i]].transitions.size())));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[3]+=(((double)(clusters[orderMasses[i]].transitions.size())*(-entropyTemp)));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[4]+=(((double)(clusters[orderMasses[i]].transitions.size())));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[5]+=(-(probabilityCluster*log10(probabilityCluster)));
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[6]+=(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()*(-entropyTemp)))+lr.intercept);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[7]+=((lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept)*(-entropyTemp));
                    
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[8]+=(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept);//best?
                    double maxRankingApprox=(lr.slope*log((double)(clusters[orderMasses[orderMasses.size()-1]].transitions.size()))+lr.intercept);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[9]+=maxRankingApprox-(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept);
                    double maxRanking=orderMasses.size();
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[10]+=maxRanking-i+1;
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[11]*=maxRanking-i+1;
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[12]+=log(maxRanking-i+1);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[13]+=i+1;
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[14]*=i+1;
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->hierarchicalValues[15]+=log(i+1);
                    a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->numberTimesInPercolationThreshold++;
                    
                    
                }
                
                
                
//                Node* a=clusters[i].transitions[j].a->nodeThatRepresents;
//                std::cout<<a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad<<'\n';
//                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=exp(lr.slope*log((double)(clusters[orderMasses[i]].transitions.size()))+lr.intercept)*lr.R2*(-entropyTemp);
//                 a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=log((double)(clusters[orderMasses[i]].transitions.size()))*(-entropyTemp);
//                 a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=log((double)(clusters[orderMasses[i]].transitions.size()));
//                  a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=(clusters.size()-i+1)*(-entropyTemp);
//                      a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=(clusters.size()-i+1)*(1);
//            a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=-(probabilityCluster*log10(probabilityCluster)/log10(clusters.size()))*(-entropyTemp);
                
                
                
                
                
                
                 a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=(((double)(clusters[orderMasses[i]].transitions.size())*(-entropyTemp)));
//                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad=Functions::max((log((double)(clusters[orderMasses[i]].transitions.size())*(-entropyTemp))),a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad);
                
                
                
                
                
                
                
                
                
//                  a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[orderMasses[i]].transitions[j].b->originalID]-1]->levelHierarchyRoad+=-(probabilityCluster*log10(probabilityCluster)/log10(clusters.size()));
//                std::cout<<a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad<<'\n';
//                std::cout<<lr.slope<<" "<<log((double)(clusters[i].transitions.size()))<<" "<<lr.intercept<<" "<<lr.R2<<" "<<entropyTemp<<" "<<exp(lr.slope*log((double)(clusters[i].transitions.size()))+lr.intercept)<<" "<<exp(lr.slope*log((double)(clusters[i].transitions.size()))+lr.intercept)*lr.R2*(-entropyTemp)<<'\n';

            }
        }
        
        entropy.push_back(-entropyTemp);
    }

    
    
    std::vector<std::string> lines;
    lines.clear();
    for(long i=0;i<minRealGraph.transitions.size();i++){
        std::stringstream line;
        line.str("");
        line<<minRealGraph.transitions[i].a->originalID<<" "<<minRealGraph.transitions[i].b->originalID;
        if(minRealGraph.transitions[i].hierarchicalValues.size()>0){
            for(long j=0;j<minRealGraph.transitions[i].hierarchicalValues.size();j++){
                line<<" "<<minRealGraph.transitions[i].hierarchicalValues[j];
                line<<" "<<minRealGraph.transitions[i].hierarchicalValues[j]/minRealGraph.transitions[i].numberTimesInPercolationThreshold;
            }

        }else{
            for(long j=0;j<16;j++){
                line<<" "<<0;
                line<<" "<<0;
            }
        }
        lines.push_back(line.str());
    }
    std::stringstream nameFile;
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"levelHierarchyRoad"<<".txt";
    TextFile::writeToFile(nameFile.str(), lines, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"entropy"<<".txt";
    TextFile::writeToFile(nameFile.str(), entropy, false);
    
    
    std::cout<<"calculating global regression for ranks "<<'\n';
    std::vector<long> orderMassesAllThresholds=Functions::getIndexesOfOrderedValues(sizesClustersAllThresholds, false);
    std::vector<Point2d> orderedSizes;
    for(double i=0;i<sizesClustersAllThresholds.size();i++){
        orderedSizes.push_back(Point2d(log(i+1),log(sizesClustersAllThresholds[orderMassesAllThresholds[i]]+1)));
    }
    LinearRegression lr;
    lr.calculate(orderedSizes);
    
    lines.clear();
    std::stringstream line;
    line.str("");
    line<<lr.slope<<" "<<lr.intercept<<" "<<lr.R2;
    lines.push_back(line.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"slopeInterceptGlobalRanking"<<".txt";
    TextFile::writeToFile(nameFile.str(), lines, false);
}






void Programs::calculateRenormalisedGraph(){
    
//    double numberDivisions=15;
    bool saveClusters=false;
    Plot masses;
    masses.mode=Plot::EUCLIDEAN;
    Configuration::setFolder("/Users/carlos/Documents/");
    Configuration::setSubFolderOut("results/clustersFromPercolation/UK/modules/");
    std::cout<<"loading graph"<<'\n';
    Graph loadedGraph;
    //    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/UK_hierarchySumMetricAngular.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, " ", " ", true, false);
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, ",", " ", true, false);
//        TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaNCOL.txt", "/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaCoordinates.txt", &loadedGraph, " ", " ", false, false);
     TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/cities/londonNCOL.txt", "/Users/carlos/Documents/data/GIS/UK/cities/londonCoordinates.txt", &loadedGraph, " ", " ", true, false);
    
    Graph minRealGraph;
    minRealGraph.strictlyDirectional=true;
    
    loadedGraph.transformToBidirectional();
    
    loadedGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    for(long i=0;i<loadedGraph.transitions.size();i++){
        loadedGraph.transitions[i].weight=1;
    }
    loadedGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::TOPOLOGICAL);
    for(long i=0;i<loadedGraph.transitions.size();i++){
        loadedGraph.transitions[i].weight=loadedGraph.transitions[i].otherWeights[Graph::METRIC];
    }
    
    
    std::cout<<"getting giant component"<<'\n';
    loadedGraph.getGiantComponent(&loadedGraph, &minRealGraph);
    minRealGraph.transformToBidirectional();
//    double totalMassOfTheSystem=minRealGraph.transitions.size()/2;
    std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
    for(long i=0;i<minRealGraph.nodes.size();i++){
        nodesOriginalGraphByOriginalId[minRealGraph.nodes[i].originalID]=&minRealGraph.nodes[i];
        //        if(minRealGraph.nodes[i].mass>0){
        //            mainGraph.addNode();
        //            mainGraph.nodes[mainGraph.nodes.size()-1].location=minRealGraph.nodes[i].location;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].mass=minRealGraph.nodes[i].mass;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].originalID=minRealGraph.nodes[i].originalID;
        //
        //
        //
        //        }
    }
    std::vector<double> sizesClustersAllThresholds;
    std::vector<double> setOfDistances;
    
    std::vector<double> weights;
    for(long i=0;i<minRealGraph.transitions.size();i++){
        weights.push_back(minRealGraph.transitions[i].weight);
    }
    weights=Functions::orderValues(weights, true);
    
    
    
    
    
    
    
    
//    std::vector<double> probabilities;
//    for(double i=1;i<numberDivisions;i++){
//        probabilities.push_back(1/numberDivisions*i);
//    }
//    long j=0;
//    double currentProbability=probabilities[j];
//    //    bool setDistance=true;
//    for(long i=0;i<weights.size();i++){
//        //    long i=0;
//        //    while(i<weights.size()){
//        
//        if((double)(i)/(double)weights.size()>currentProbability&&(double)(i-1)/(double)weights.size()<=currentProbability){
//            j++;
//            currentProbability=probabilities[j];
//            setOfDistances.push_back(weights[i]);
//            
//        }
//    }
//    
//    
//    
//    
//    double minDistance=setOfDistances[0];
// //     double maxDistance=setOfDistances[setOfDistances.size()-1];
    
    
    
    
    
    
    
    
    double minDistance=300;
    double maxDistance=310;
    
    
    for(double i=minDistance;i<maxDistance;i+=10){
        setOfDistances.push_back(i);
    }
    
    
//    std::vector<double> entropy;
    
    for(double h=0;h<setOfDistances.size();h++){
        
        double distance=setOfDistances[h];
        std::cout<<"distance: "<<distance<<'\n';
        long repetitions=1;
        std::vector<Graph> clusters;
        
        
        for(long i=0;i<repetitions;i++){
            clusters.clear();
            std::stringstream nameClustersFile;
            nameClustersFile<<Configuration::folderOut()<<"clusters"<<distance<<".txt";
            minRealGraph.generateNetworkPercolation(distance, clusters, saveClusters, true, nameClustersFile.str(), 0, false);
            
        }
        
        
        std::vector<double> valuesMasses;
        for(double i=0;i<clusters.size();i++){
            valuesMasses.push_back(clusters[i].transitions.size());
            
        }
        std::vector<long> orderMasses=Functions::getIndexesOfOrderedValues(valuesMasses, false);
        
//        for(long indexCluster=0;indexCluster<orderMasses.size();indexCluster++){
        {long indexCluster=0;
            Graph* currentCluster=&clusters[orderMasses[indexCluster]];
            currentCluster->transformToBidirectional();
            
    //        Graph kReachableGraph;
    //        currentCluster->generateInverseOfKReachableGraph(&kReachableGraph, 5, Graph::TOPOLOGICAL);
    //        currentCluster->colorInvertedKReachableGraph(currentCluster, &kReachableGraph);
            std::vector<Graph> modules;
    //        currentCluster->calculateClustersFromColors(modules, false, true);
            
            
            Plot fd;
            fd.mode=Plot::EUCLIDEAN;
            Plot Q_makse;
            Q_makse.mode=Plot::EUCLIDEAN;
            Plot Q_newmann;
            Q_newmann.mode=Plot::EUCLIDEAN;
            Plot Clustering;
            Clustering.mode=Plot::EUCLIDEAN;
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
//            for(long lb=1000;lb<1001;lb++){
//                std::cout<<lb<<'\n';
//                modules.clear();
//                currentCluster->calculateColorsWithMEMB(currentCluster, lb, currentCluster->getIndexesOfDistanceType(Graph::METRIC)[0]);
//                currentCluster->calculateClustersFromColors(currentCluster,modules);
//                fd.addValue(Point2d(lb,modules.size()));
////                std::vector<std::string> lines;
////                for(long i=0;i<modules.size();i++){
////    //                std::cout<<"i "<<i<<'\n';
////                    for(long j=0;j<modules[i].transitions.size();j++){
////                        std::stringstream line;
////                        line<<modules[i].transitions[j].a->originalID<<" "<<modules[i].transitions[j].b->originalID<<" "<<i;
////                        lines.push_back(line.str());
////                    }
////                }
////                TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/modulesOfClusterLondon.txt", lines, false);
//                
//                std::vector<std::string> lines;
//            
//                for(long g=0;g<currentCluster->nodes.size();g++){
//                    std::stringstream line;
//                    line<<currentCluster->nodes[g].originalID<<" "<<currentCluster->nodes[g].location.x<<" "<<currentCluster->nodes[g].location.y<<" "<<currentCluster->nodes[g].numColor;
//                    lines.push_back(line.str());
//                }
//                std::stringstream nameFileClustersPercolationSmallWorld;
//                nameFileClustersPercolationSmallWorld<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clustersMEMB_lb"<<lb<<".txt";
//                TextFile::writeToFile(nameFileClustersPercolationSmallWorld.str(), lines, false);
//
//                
//                Graph hyperGraph;
//                currentCluster->generateSuperGraphFromClusters(modules, currentCluster, &hyperGraph);
//                std::stringstream name;
//                name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/hyperGraph_MEMB_lb"<<lb<<".txt";
//                TextFile::writeNCOLPlusCoordinatesFile(&hyperGraph, name.str());
//                
//                
////                std::vector<std::string> lines;
//                lines.clear();
//                for(long i=0;i<hyperGraph.nodes.size();i++){
//                    //                std::cout<<"i "<<i<<'\n';
////                            for(long j=0;j<modules[i].transitions.size();j++){
//                        std::stringstream line;
//                        line<<hyperGraph.nodes[i].originalID<<" "<<hyperGraph.nodes[i].mass;
//                        lines.push_back(line.str());
////                            }
//                }
//                name.str("");
//                name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/hyperGraph_masses_lb_"<<lb<<".txt";
//                TextFile::writeToFile(name.str(), lines, false);
//                
//            }
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
//            for(long i=0;i<currentCluster->transitions.size();i++){
//                currentCluster->transitions[i].weight=currentCluster->transitions[i].otherWeights[Graph::METRIC];
//            }
//            for(long subDistance=50;subDistance<290;subDistance+=10){
//                std::vector<Graph> subClusters;
//                Graph clusterStrictlyDirectional;
//                clusterStrictlyDirectional.strictlyDirectional=true;
//                currentCluster->getGiantComponent(currentCluster, &clusterStrictlyDirectional);
//                clusterStrictlyDirectional.transformToBidirectional();
//                clusterStrictlyDirectional.generateNetworkPercolation(subDistance, subClusters, false, true,"", 0, false);
////                if(subDistance==100){
//                {//save cluster colors
//                    std::vector<std::string> lines;
//                    clusterStrictlyDirectional.assignColorsFromClusters(&clusterStrictlyDirectional, subClusters);
//                    for(long g=0;g<clusterStrictlyDirectional.nodes.size();g++){
//                        std::stringstream line;
//                        line<<clusterStrictlyDirectional.nodes[g].originalID<<" "<<clusterStrictlyDirectional.nodes[g].location.x<<" "<<clusterStrictlyDirectional.nodes[g].location.y<<" "<<clusterStrictlyDirectional.nodes[g].numColor;
//                        lines.push_back(line.str());
//                    }
//                    std::stringstream nameFileClustersPercolationSmallWorld;
//                    nameFileClustersPercolationSmallWorld<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clustersPercolationSmallWorld"<<subDistance<<".txt";
//                    TextFile::writeToFile(nameFileClustersPercolationSmallWorld.str(), lines, false);
//                }
//                std::vector<double> subValuesMasses;
//                for(double i=0;i<subClusters.size();i++){
//                    subValuesMasses.push_back(subClusters[i].transitions.size());
//                    
//                }
//                std::vector<long> subOrderMasses=Functions::getIndexesOfOrderedValues(subValuesMasses, false);
//                Graph hyperGraph;
//                clusterStrictlyDirectional.generateSuperGraphFromClusters(subClusters, &clusterStrictlyDirectional, &hyperGraph);
//                std::stringstream name;
//                name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/hyperGraph_percolation"<<subDistance<<".txt";
//                TextFile::writeNCOLPlusCoordinatesFile(&hyperGraph, name.str());
//                for(long g=0;g<hyperGraph.transitions.size();g++){
//                    hyperGraph.transitions[g].weight=1;
//                }
//                hyperGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::TOPOLOGICAL);
//                std::vector<Point2d> resultsFD;
////                hyperGraph.calculateFractalDimension(resultsFD);
//                
//                
//                
//                
//                
////                std::vector<std::string> lines;
////                for(long f=2;f<10;f++){
////                    double averageN=0;
//////                    for(long d=0;d<hyperGraph.nodes.size();d++){
//////                    for(long d=0;d<Functions::min(100,hyperGraph.nodes.size());d++){
////                    long d=0;
////                        Node* nodeInit=&hyperGraph.nodes[d];
////                        std::vector<Node*> nodesCutoff;
////                        hyperGraph.calculateCutoffSpeed(nodeInit, f, nodesCutoff);
////                        
////                        
//////                        std::stringstream line;
//////                        line<<nodeInit->originalID<<" "<<f<<" "<<nodesCutoff.size();
//////                        lines.push_back(line.str());
////                        
////                        
////                        averageN+=nodesCutoff.size();
//////                    }
//////                    averageN/=(double)(hyperGraph.nodes.size());
////                    resultsFD.push_back(Point2d(f,averageN));
////                }
////                
////                
////                
////                
////                
////                
////                
////                for(long i=0;i<resultsFD.size();i++){
////                    //                std::cout<<"i "<<i<<'\n';
//////                    for(long j=0;j<resultsFD[i].transitions.size();j++){
////                        std::stringstream line;
////                        line<<resultsFD[i].x<<" "<<resultsFD[i].y;
////                        lines.push_back(line.str());
//////                    }
////                }
////                std::stringstream nameFileFD;
////                nameFileFD<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/fractalDimensionSubHyperGraphPercolation_singleNode"<<subDistance<<".txt";
////                TextFile::writeToFile(nameFileFD.str(), lines, false);
//                
//                
//                
//                
//                
//                
//                
//                
//                
//            }
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            Graph copiedCluster;
            currentCluster->copyGraph(currentCluster, &copiedCluster, false);
            std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
            std::unordered_map<long, std::vector<Node*> > nodesByColor;
            Graph hyperGraph;
            
            for(long i=0;i<currentCluster->nodes.size();i++){
                currentCluster->nodes[i].numColor=i;
                nodesOriginalGraphByOriginalId[currentCluster->nodes[i].originalID]=&currentCluster->nodes[i];
                nodesByColor[currentCluster->nodes[i].numColor].push_back(&currentCluster->nodes[i]);
            }
            
            for(long level=0;level<10;level++){
                std::cout<<level<<'\n';
                long lb=2;
                {
                    
                    modules.clear();
                    copiedCluster.calculateColorsWithMEMB(&copiedCluster, lb,copiedCluster.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]);
                    copiedCluster.calculateClustersFromColors(&copiedCluster,modules);
                    if(modules.size()>1){
                        
                        
                        
                            
                        
                        
                        
    //                    fd.addValue(Point2d(lb,modules.size()));
    //                    std::vector<std::string> lines;
    //                    for(long i=0;i<modules.size();i++){
    //                        //                std::cout<<"i "<<i<<'\n';
    //                        for(long j=0;j<modules[i].transitions.size();j++){
    //                            std::stringstream line;
    //                            line<<modules[i].transitions[j].a->originalID<<" "<<modules[i].transitions[j].b->originalID<<" "<<i;
    //                            lines.push_back(line.str());
    //                        }
    //                    }
    //                    TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/modulesOfClusterLondon.txt", lines, false);
                        hyperGraph.resetGraph();
                        copiedCluster.generateSuperGraphFromClusters(modules, &copiedCluster, &hyperGraph);
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        for(long i=0;i<hyperGraph.nodes.size();i++){
                            //                                std::vector<long> colorsToCollapse;
                            for(long j=0;j<hyperGraph.nodes[i].nodesCollapsed.size();j++){
                                long currentColor=(nodesOriginalGraphByOriginalId[hyperGraph.nodes[i].nodesCollapsed[j]->originalID]->numColor);
                                for(long h=0;h<nodesByColor[currentColor].size();h++){
                                    nodesByColor[currentColor][h]->numColor=i;
                                    
                                }
                                nodesByColor[currentColor].clear();
                            }
                            
                            
                        }
                        
                        for(long i=0;i<currentCluster->nodes.size();i++){
                            nodesByColor[currentCluster->nodes[i].numColor].push_back(&currentCluster->nodes[i]);
                        }
                        
                        
                        
                        
                        std::vector<std::string> lines;
                        
                        for(long g=0;g<currentCluster->nodes.size();g++){
                            std::stringstream line;
                            line<<currentCluster->nodes[g].originalID<<" "<<currentCluster->nodes[g].location.x<<" "<<currentCluster->nodes[g].location.y<<" "<<currentCluster->nodes[g].numColor;
                            lines.push_back(line.str());
                        }
                        std::stringstream nameFileClustersPercolationSmallWorld;
                        nameFileClustersPercolationSmallWorld<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clusters_renormalization_level"<<level<<".txt";
                        TextFile::writeToFile(nameFileClustersPercolationSmallWorld.str(), lines, false);
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        std::stringstream name;
                        name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/hyperGraph_level"<<level<<".txt";
                        TextFile::writeNCOLPlusCoordinatesFile(&hyperGraph, name.str());
                        
//                        std::vector<std::string> lines;
                        lines.clear();
                        for(long i=0;i<hyperGraph.nodes.size();i++){
                            //                std::cout<<"i "<<i<<'\n';
//                            for(long j=0;j<modules[i].transitions.size();j++){
                                std::stringstream line;
                                line<<hyperGraph.nodes[i].originalID<<" "<<hyperGraph.nodes[i].mass;
                                lines.push_back(line.str());
//                            }
                        }
                        name.str("");
                        name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/hyperGraph_level"<<level<<"_masses.txt";
                        TextFile::writeToFile(name.str(), lines, false);
                        
                        copiedCluster.resetGraph();
                        hyperGraph.copyGraph(&hyperGraph, &copiedCluster, false);
//                        copiedCluster.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);//This is not true, I am just doing to push the index of otherweights and put something in slot 0, the distance in main is the accumulation of the topological
                        for(long g=0;g<copiedCluster.transitions.size();g++){
                            copiedCluster.transitions[g].weight=1;
                        }
                        copiedCluster.setTypeOfMainDistanceAndInsertIntoDistances(Graph::TOPOLOGICAL);
                        
                    }else{
                        break;
                    }
                }
            }
            
            
            
            
            
            
            
            
            
            
            
            
            
    //
    //        lines.clear();
    //        std::vector<std::string> lines;
            std::stringstream name;
//            name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/pointsFractalPlot_approximation_"<<indexCluster<<".txt";
            
               name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/pointsFractalPlot"<<".txt";
            fd.save(name.str());
        }
        
//        for(long i=0;i<kReachableGraph.transitions.size();i++){
////            for(long j=0;j<modules[i].transitions.size();j++){
//                std::stringstream line;
//                line<<kReachableGraph.transitions[i].a->originalID<<" "<<kReachableGraph.transitions[i].b->originalID<<" "<<kReachableGraph.transitions[i].a->numColor<<" "<<kReachableGraph.transitions[i].b->numColor;
//                lines.push_back(line.str());
////            }
//        }
//        TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/kReachableLondon.txt", lines, false);
//        
//        
//        lines.clear();
//        for(long i=0;i<clusters[orderMasses[indexCluster]].transitions.size();i++){
//            //            for(long j=0;j<modules[i].transitions.size();j++){
//            std::stringstream line;
//            line<<clusters[orderMasses[indexCluster]].transitions[i].a->originalID<<" "<<clusters[orderMasses[indexCluster]].transitions[i].b->originalID<<" "<<clusters[orderMasses[indexCluster]].transitions[i].a->numColor<<" "<<clusters[orderMasses[indexCluster]].transitions[i].b->numColor;
//            lines.push_back(line.str());
//            //            }
//        }
//        TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clusterLondon.txt", lines, false);
        
        
        
        
        
        
    }
    
    
}


void Programs::generateGridGraph(Graph* gridGraph,long sizeX,long sizeY,double euclideanWidth){
    
    for(long i=0;i<sizeX;i++){
        for(long j=0;j<sizeY;j++){
            gridGraph->addNode();
        }
    }
//    long currentRow=0;
//    long currentCol=0;
    for(long i=0;i<sizeX;i++){
        for(long j=0;j<sizeY;j++){
            
            long index=i+sizeX*j;
            
            
            gridGraph->nodes[index].location.x=i*euclideanWidth;
            gridGraph->nodes[index].location.y=j*euclideanWidth;
            
            if(j<sizeY-1){
                long indexNext=i+sizeX*(j+1);
                Transition trans;
                trans.a=&gridGraph->nodes[index];
                trans.b=&gridGraph->nodes[indexNext];
                trans.weight=euclideanWidth;
                gridGraph->addDirectedTransition(trans);
            }
            if(i<sizeX-1){
                long indexNext=(i+1)+sizeX*(j);
                Transition trans;
                trans.a=&gridGraph->nodes[index];
                trans.b=&gridGraph->nodes[indexNext];
                trans.weight=euclideanWidth;
                gridGraph->addDirectedTransition(trans);
            }
        }
    }
    gridGraph->transformToBidirectional();
    gridGraph->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    
}





void Programs::performProbabilisticNetworkPercolation(Graph* loadedGraph){
    bool generateSuperGraph=false;
    
    bool calculateCorrelationLength=false;
    bool calculateFractalDimension=true;
//    Graph loadedGraph;
    bool draw=false;
    bool saveClusters=false;
    
    //    double minSizeCity=50;
    ////////LOAD MINREALGRAPH
    
    //    minRealGraph.pseudoGraph=false;
    
   
    //
    //    Graph uk;
    //    uk.strictlyDirectional=false;
    //    std::cout<<"IMPORTING FILE UK"<<'\n';
//    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/UK_hierarchySumMetricAngular.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, " ", " ", true, false);
    //    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &loadedGraph, ",", " ", true, false);
    //    uk.transformToBidirectional();
    //
    //    std::vector<Graph> clustersUK;
    //    uk.generateNetworkPercolation(300, clustersUK, false, true, "", 0, false);
    //    uk.orderClustersByMass(clustersUK);
    //    clustersUK[0].copyGraph(&clustersUK[0], &loadedGraph, false);
    //    loadedGraph.transformToBidirectional();
    //    std::stringstream nameLondon;
    //    nameLondon<<Configuration::folderOut()<<"londonNCOL.txt";
    //    TextFile::writeNCOLPlusCoordinatesFile(&loadedGraph, nameLondon.str());
    
    
    
    Graph minRealGraph;
    minRealGraph.strictlyDirectional=true;
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/clustersFromPercolation/UK/london/londonNCOL.txt", &loadedGraph, " ", false);
    //    TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaNCOL.txt", "/Users/carlos/Documents/data/GIS/UK/smallAreaUK/uk_subAreaCoordinates.txt", &loadedGraph, " ", " ", false, false);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/harmonicCities/uk_subArea.txt", &loadedGraph, " ", false);
//    loadedGraph.transformToBidirectional();
    //        std::stringstream nameLondon;
    //        nameLondon<<Configuration::folderOut()<<"londonNCOL.txt";
    //    std::stringstream nameLondonCoordinates;
    //    nameLondonCoordinates<<Configuration::folderOut()<<"londonCoordinates.txt";
    //    TextFile::writeNCOLFileAndSeparateCoordinatesFile(&loadedGraph, nameLondon.str(), nameLondonCoordinates.str(), " ", " ");
    
    
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/zzz_/gridNCOLAndCoord.txt", &loadedGraph, " ", true);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Dropbox/CASA/results/harmonicCities/minRealGraph2.txt", &minRealGraph, " ", false);
    //    TextFile::includeMasses(&minRealGraph, "/Users/carlos/Documents/results/harmonicCities/massesMinRealGraph.txt", " ", false);
    
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //        if(minRealGraph.nodes[i].mass<minSizeCity){
    //            minRealGraph.nodes[i].mass=0;
    //        }
    //    }
    
//    loadedGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    
    for(long i=0;i<loadedGraph->transitions.size();i++){
        loadedGraph->transitions[i].weight=Functions::runiform(0,1);
    }
    
    
    
    
    loadedGraph->getGiantComponent(loadedGraph, &minRealGraph);
    minRealGraph.transformToBidirectional();
    double totalMassOfTheSystem=minRealGraph.transitions.size()/2;//I need to divide it by 2 because minRealGraph is strictly directional and the clusters aren't so they have half the number of transitions
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //
    //
    //        minRealGraph.nodes[i].location.x+=-minX;
    //        minRealGraph.nodes[i].location.y+=-minY;
    //        minRealGraph.nodes[i].location.x*=width/75/1000;
    //        minRealGraph.nodes[i].location.y*=width/75/1000;
    //
    //
    //
    //
    //
    //    }
    ////////////////////////
    
    std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
    for(long i=0;i<minRealGraph.nodes.size();i++){
        nodesOriginalGraphByOriginalId[minRealGraph.nodes[i].originalID]=&minRealGraph.nodes[i];
        //        if(minRealGraph.nodes[i].mass>0){
        //            mainGraph.addNode();
        //            mainGraph.nodes[mainGraph.nodes.size()-1].location=minRealGraph.nodes[i].location;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].mass=minRealGraph.nodes[i].mass;
        //            mainGraph.nodes[mainGraph.nodes.size()-1].originalID=minRealGraph.nodes[i].originalID;
        //
        //
        //
        //        }
    }
    
    if(draw){
        //////////////////
        Singleton<Windows>::instance().add(Point2d(15,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(475,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(935,465), 430,430);
        Singleton<Windows>::instance().add(Point2d(1395,465), 430,200);
        //////////////////
        Singleton<Windows>::instance().add(Point2d(15,7.5), 430,430);
        Singleton<Windows>::instance().add(Point2d(475,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(475,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(935,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,7.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(935,237.5), 430,200);
        Singleton<Windows>::instance().add(Point2d(1395,465+230), 430,200);
        //////////////////
        
        Singleton<Windows>::instance().setTitle(0,"Original graph");
        Singleton<Windows>::instance().setTitle(1,"Giant cluster");
        Singleton<Windows>::instance().setTitle(2,"Second largest cluster");
        Singleton<Windows>::instance().setTitle(3,"Correlation length");
        Singleton<Windows>::instance().setTitle(4,"Log-Log of masses of clusters");
        Singleton<Windows>::instance().setTitle(5,"R2 of the correlation of masses");
        Singleton<Windows>::instance().setTitle(7,"Proportion between largest and second largest cluster");
        Singleton<Windows>::instance().setTitle(6,"Slopes of correlation of masses");
        Singleton<Windows>::instance().setTitle(8,"<S*>");
        Singleton<Windows>::instance().setTitle(9,"P_N(p)");
        Singleton<Windows>::instance().setTitle(10,"Evolution of masses");
        Singleton<Windows>::instance().setTitle(11,"Fractal dimension box-counting");
        
        VectorNDim vec;
        vec.values.clear();
        vec.values.push_back(0);
        vec.values.push_back(0);
        vec.values.push_back(0);
        vec.values.push_back(100);
//        Singleton<Windows>::instance().get(0)->drawGraph(&minRealGraph,vec);
        Singleton<Windows>::instance().get(0)->zoomExtents();
    }
    
    Plot evolutionR2Masses;
    //    Plot evolutionR2Transitions;
    evolutionR2Masses.limited=false;
    //    evolutionR2Transitions.limited=false;
    Plot proportionFirstAndSecond;
    proportionFirstAndSecond.limited=false;
    Plot slopeMasses;
    slopeMasses.limited=false;
    Plot averageMasses;
    averageMasses.limited=false;
    Plot numberClusters;
    numberClusters.limited=false;
    
    Plot evolutionMass1;
    evolutionMass1.limited=false;
    Plot evolutionMass2;
    evolutionMass2.limited=false;
    Plot evolutionMass3;
    evolutionMass3.limited=false;
    Plot evolutionMass4;
    evolutionMass4.limited=false;
    Plot evolutionMass5;
    evolutionMass5.limited=false;
    Plot correlationLength;
    correlationLength.limited=false;
    std::vector<std::vector<double> > probabilityRandomNodeInClusterOfNode;
    std::vector<double> entropy;
    Plot fd;
    fd.limited=false;
    
    //      saveGraph(&minRealGraph, "/Users/carlos/Documents/zzz_/smallAreaUKNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKCoordinates.txt", " ", " ");
    
    Graph lineGraph;
    if(calculateCorrelationLength){
        //    lineGraph.strictlyDirectional=false;
        minRealGraph.createLineGraph(&minRealGraph,&lineGraph);
    }
    //        lineGraph.transformToBidirectional();
    
    
    //    std::stringstream nameModel;
    //            nameModel<<Configuration::folderOut()<<"modelNCOL.txt";
    //    std::stringstream nameModelCoordinates;
    //nameModelCoordinates<<Configuration::folderOut()<<"modelCoordinates.txt";
    //        saveGraph(&minRealGraph,nameModel.str(), nameModelCoordinates.str(), " ", " ");
    
    
    //    Graph lineGraphlineGraph;
    //    lineGraphlineGraph.resetGraph();
    //    lineGraph.createLineGraph(&lineGraph, &lineGraphlineGraph);
    //    int indexWeight=lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0];
    //    for(long k=0;k<lineGraphlineGraph.transitions.size();k++){
    //
    //        Node* a=lineGraphlineGraph.transitions[k].a;
    //        Node* b=lineGraphlineGraph.transitions[k].b;
    //        Transition* transA=a->transitionThatRepresents;
    //        Transition* transB=b->transitionThatRepresents;
    //        lineGraphlineGraph.transitions[k].weight=(transA->otherWeights[indexWeight]+transB->otherWeights[indexWeight])/2;
    //        //        lineGraphlineGraph.transitions[k].weight=lineGraphlineGraph.transitions[k].otherWeights[lineGraphlineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
    //        //        lineGraphlineGraph.transitions[k].weight=1;
    //        //        std::cout<<"new weights "<<lineGraphlineGraph.transitions[k].weight<<'\n';
    //    }
    //    saveGraph(&lineGraphlineGraph, "/Users/carlos/Documents/zzz_/smallAreaUKLGLGNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKLGLGCoordinates.txt", " ", " ");
    
    QTree quadTreeLG;
    if(calculateCorrelationLength){
        lineGraph.insertGraphIntoQTree(&quadTreeLG);
    }
    
    std::vector<double> setOfDistances;
    //    setOfAngles.push_back(45);
    //    setOfAngles.push_back(60);
    //    setOfAngles.push_back(85);
    //    setOfAngles.push_back(175);
    
    //    for(double i=10;i<20;i+=10){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=20;i<30;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=30;i<44;i+=1){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=44;i<45;i+=.5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=45;i<60;i+=1){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=60;i<70;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=70;i<85;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=85;i<95;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    //    for(double i=95;i<100;i+=5){
    //        setOfAngles.push_back(i);
    //    }
    double minDistance=0.1;
    double maxDistance=1.01;
    for(double i=minDistance;i<maxDistance;i+=.01){
        setOfDistances.push_back(i);
    }
    //    setOfAngles.push_back(45);
    
    std::vector<std::string> linesFileMasses;
    
    for(double h=0;h<setOfDistances.size();h++){
        double distance=setOfDistances[h];
        std::cout<<"===================="<<'\n';
        std::cout<<"distance : "<<distance<<'\n';
        Plot boxCounting;
        boxCounting.mode=Plot::EUCLIDEAN;
        long repetitions=1;
        std::vector<Graph> clusters;
        double averageMassGiantCluster=0;
        
        std::vector<long> indexesClustersOrderedBySize;
        
        for(long i=0;i<repetitions;i++){
            clusters.clear();
        std::stringstream nameClustersFile;
            nameClustersFile<<Configuration::folderOut()<<"clusters"<<distance<<".txt";
            //            saveClusters
            //            minRealGraph.generateNetworkPercolatio
            minRealGraph.generateNetworkPercolation(distance, clusters, saveClusters, true, nameClustersFile.str(), 0, false);
            //            minRealGraph.orderClustersByMass(clusters);
            
            //            minRealGraph.generateAngularPercolation(&minRealGraph,&lineGraph, angle, clusters,0,false,false);
            
        }
        std::vector<double> values;
        
        for(long i=0;i<clusters.size();i++){
            values.push_back(clusters[i].transitions.size());
        }
        indexesClustersOrderedBySize=Functions::getIndexesOfOrderedValues(values, false);
        averageMassGiantCluster+=clusters[indexesClustersOrderedBySize[0]].transitions.size();
        
        averageMassGiantCluster/=(double)(repetitions);
        evolutionMass1.addValue(averageMassGiantCluster/(double)(totalMassOfTheSystem));
        
        
        FractalDimension fractalDimension;
        if(calculateFractalDimension){
//            fd.addValue(fractalDimension.calculateBoxCounting(&clusters[indexesClustersOrderedBySize[0]] ));
        }
        
        Graph superGraphClusters;
        if(generateSuperGraph){
            minRealGraph.generateSuperGraphFromClusters(clusters, &minRealGraph, &superGraphClusters);
            
            //        std::vector<double> values;
            //        for(long i=0;i<superGraphClusters.nodes.size();i++){
            //            values.push_back(superGraphClusters.nodes[i].transitions.size());
            //        }
            std::stringstream nameFileSuperGraph;
            nameFileSuperGraph<<Configuration::folderOut()<<"superGraph_"<<distance<<".txt";
            TextFile::writeNCOLPlusCoordinatesFile(&superGraphClusters, nameFileSuperGraph.str());
        }
        
        
        
        
        
        //            minRealGraph.generateNetworkPercolation(angle, clusters,false, true, "", 0);
        //            minRealGraph.orderClustersByMass(clusters);
        
        //        std::vector<Graph> clustersPrimal;
        //        for(long j=0;j<clusters.size();j++){
        //            Graph clusterPrimal;
        //            std::vector<Transition*> transitions;
        //            for(long i=0;i<clusters[j].nodes.size();i++){
        //                transitions.push_back(clusters[j].nodes[i].transitionThatRepresents);
        //            }
        //
        //            minRealGraph.getInducedSubgraph(&clusterPrimal, transitions);
        //            clustersPrimal.push_back(clusterPrimal);
        //        }
        
        //        if(distance==minDistance){
        //            for(long i=0;i<lineGraph.nodes.size();i++){
        //                std::vector<double> values;
        //                probabilityRandomNodeInClusterOfNode.push_back(values);
        //                probabilityRandomNodeInClusterOfNode[i].push_back(0);
        //            }
        //        }
        double entropyTemp=0;
        for(double i=0;i<clusters.size();i++){
            
            double probabilityCluster=((double)clusters[i].transitions.size()/(double)totalMassOfTheSystem);
            entropyTemp+=probabilityCluster*log10(probabilityCluster);
        }
        for(double i=0;i<clusters.size();i++){
            
            //            double probabilityCluster=((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
            //            entropyTemp+=probabilityCluster*log(probabilityCluster);
            
            for(long j=0;j<clusters[i].transitions.size();j++){
                Node* a=nodesOriginalGraphByOriginalId[clusters[i].transitions[j].a->originalID];
                //                Node* a=clusters[i].transitions[j].a->nodeThatRepresents;
                
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=(double)lclusters[i].transitions.size()/(double)lineGraph.nodes.size()*log((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
                //                double normalizedSize=Functions::normalize(log((double)clusters[i].transitions.size()),log((double)clusters[clusters.size()-1].transitions.size()),log((double)clusters[0].transitions.size()));
                //                double normalizedSize=Functions::normalize(((double)clusters[i].transitions.size()),((double)clusters[clusters.size()-1].transitions.size()),((double)clusters[0].transitions.size()));
                //                double maxRanking=clusters.size();
                //                double normalizedRanking=Functions::normalize(maxRanking-i, 0, maxRanking);
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=log((double)clusters[i].transitions.size());
                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=log((double)clusters[i].transitions.size())*(-entropyTemp);
                //                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->levelHierarchyRoad+=i;
                
                
                
                
                
                //                Node* nodeLG=a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].transitions[j].b->originalID]-1]->nodeOfLineGraphThatRepresentsThis;
                //                if(distance==minDistance){
                //                    probabilityRandomNodeInClusterOfNode[nodeLG->id][0]=((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
                //                }else{
                //                    while(probabilityRandomNodeInClusterOfNode[nodeLG->id].size()<(h)){
                //                        probabilityRandomNodeInClusterOfNode[nodeLG->id].push_back(0);
                //                    }
                //                    probabilityRandomNodeInClusterOfNode[nodeLG->id].push_back((double)clusters[i].transitions.size()/(double)lineGraph.nodes.size());
                //                }
            }
        }
        
        entropy.push_back(-entropyTemp);
        
        
        if((distance>minDistance)&draw){
            Singleton<Windows>::instance().add(1);
            Singleton<Windows>::instance().add(2);
            Singleton<Windows>::instance().add(3);
            Singleton<Windows>::instance().add(4);
        }
        
        
        if(draw){
            
//            Singleton<Windows>::instance().get(1)->drawGraph(&clusters[0]);
            Singleton<Windows>::instance().get(1)->copyViewParameters(Singleton<Windows>::instance().get(0));
            if(clusters.size()>1){
//                Singleton<Windows>::instance().get(2)->drawGraph(&clusters[1]);
                Singleton<Windows>::instance().get(2)->copyViewParameters(Singleton<Windows>::instance().get(0));
            }
        }
        //        Singleton<Windows>::instance().get(3)->copyViewParameters(Singleton<Windows>::instance().get(0));
        
        
        
        
        Plot masses;
        masses.mode=Plot::EUCLIDEAN;
        
        double averageMass=0;
        double totalMassWithoutGiantCluster=0;
        std::vector<Point2d> numberClustersOfASize;
        std::vector<double> radiiGyrationSquared;
        
        
        
        for(double i=0;i<clusters.size();i++){
            
            masses.addValue(Point2d(log(i+1),log((double)(clusters[indexesClustersOrderedBySize[i]].transitions.size())+1)));
            if(i>0){
                averageMass+=clusters[indexesClustersOrderedBySize[i]].transitions.size();
            }
            if(i==0){
                //                evolutionMass1.addValue((double)(clusters[i].nodes.size())/(double)(lineGraph.nodes.size()));
            }
            if(i==1){
                evolutionMass2.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            if(i==2){
                evolutionMass3.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            if(i==3){
                evolutionMass4.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            if(i==4){
                evolutionMass5.addValue(clusters[indexesClustersOrderedBySize[i]].transitions.size());
            }
            
            
            //
            //            if(i>0||distance<=183){
            
            if(i!=indexesClustersOrderedBySize[0]){
                
                if(numberClustersOfASize.size()==0||clusters[indexesClustersOrderedBySize[i]].transitions.size()!=numberClustersOfASize[numberClustersOfASize.size()-1].x){
                    Point2d point;
                    point.x=clusters[indexesClustersOrderedBySize[i]].transitions.size();
                    point.y=1;
                    numberClustersOfASize.push_back(point);
                    
                    if(calculateCorrelationLength){
                        
                        Graph subGraphLineGraph;
                        //                    std::vector<Node*> nodesLGLG;
                        //                    for(long k=0;k<clusters[i].nodes.size();k++){
                        //                        for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                        //                            Node* a=clusters[i].nodes[k].transitions[g]->a->nodeThatRepresents;
                        //                            Node* b=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                        //                            Transition* trans=a->transitions[a->indexOfTransitionsByIdOfDestination[b->originalID]-1];
                        //                            Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                        //                            nodesLGLG.push_back(nodeLGLG);
                        //                        }
                        //                    }
                        //                    if(i>0){
                        std::vector<Node*> nodesSubgraphLG;
                        for(long k=0;k<clusters[indexesClustersOrderedBySize[i]].nodes.size();k++){
                            Node* nodeALG=clusters[indexesClustersOrderedBySize[i]].nodes[k].nodeThatRepresents;
                            Node* nodeBLG=NULL;
                            for(long g=0;g<clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions.size();g++){
                                nodeBLG=clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions[g]->b->nodeThatRepresents;
                            }
                            if(nodeBLG!=NULL){
                                Transition* trans=nodeALG->transitions[nodeALG->indexOfTransitionsByIdOfDestination[nodeBLG->originalID]-1];
                                Node* nodeLG=trans->nodeOfLineGraphThatRepresentsThis;
                                nodesSubgraphLG.push_back(nodeLG);
                            }
                        }
                        lineGraph.getInducedSubgraph(&subGraphLineGraph, nodesSubgraphLG);
                        //                    lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesLGLG);
                        //                    if (angle==7){
                        //                        saveGraph(&subGraphLineGraphLineGraph, "/Users/carlos/Documents/zzz_/subsmallAreaUKLGLGNCOL.txt", "/Users/carlos/Documents/zzz_/subsmallAreaUKLGLGCoordinates.txt", " ", " ");
                        //                        std::cout<<"index subgraph "<<i<<'\n';
                        //                        if(i==1){
                        //                            std::cout<<"problem"<<'\n';
                        //                        }
                        //                    }
                        
                        double radiusGyrationSquared=Graph::calculateSquaredGyrationRadiusInGraphSpace(&subGraphLineGraph,&lineGraph,&quadTreeLG);
                        
                        radiiGyrationSquared.push_back(radiusGyrationSquared);
                    }
                    //                    }else{
                    //                        radiiGyrationSquared.push_back(0);
                    //                    }
                }else{
                    numberClustersOfASize[numberClustersOfASize.size()-1].y++;
                    //                    Graph lineGraphlineGraph;
                    if(calculateCorrelationLength){
                        Graph subGraphLineGraph;
                        //                    std::vector<Node*> nodesLGLG;
                        //                    for(long k=0;k<clusters[i].nodes.size();k++){
                        //                        for(long g=0;g<clusters[i].nodes[k].transitions.size();g++){
                        //                            Node* a=clusters[i].nodes[k].transitions[g]->a->nodeThatRepresents;
                        //                            Node* b=clusters[i].nodes[k].transitions[g]->b->nodeThatRepresents;
                        //                            Transition* trans=a->transitions[a->indexOfTransitionsByIdOfDestination[b->originalID]-1];
                        //                            Node* nodeLGLG=trans->nodeOfLineGraphThatRepresentsThis;
                        //                            nodesLGLG.push_back(nodeLGLG);
                        //                        }
                        //                    }
                        //                    lineGraphlineGraph.getInducedSubgraph(&subGraphLineGraphLineGraph, nodesLGLG);
                        //                    if(i>0){
                        std::vector<Node*> nodesSubgraphLG;
                        for(long k=0;k<clusters[indexesClustersOrderedBySize[i]].nodes.size();k++){
                            Node* nodeALG=clusters[indexesClustersOrderedBySize[i]].nodes[k].nodeThatRepresents;
                            Node* nodeBLG=NULL;
                            for(long g=0;g<clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions.size();g++){
                                nodeBLG=clusters[indexesClustersOrderedBySize[i]].nodes[k].transitions[g]->b->nodeThatRepresents;
                            }
                            if(nodeBLG!=NULL){
                                Transition* trans=nodeALG->transitions[nodeALG->indexOfTransitionsByIdOfDestination[nodeBLG->originalID]-1];
                                Node* nodeLG=trans->nodeOfLineGraphThatRepresentsThis;
                                nodesSubgraphLG.push_back(nodeLG);
                            }
                        }
                        lineGraph.getInducedSubgraph(&subGraphLineGraph, nodesSubgraphLG);
                        
                        double radiusGyrationSquared=Graph::calculateSquaredGyrationRadiusInGraphSpace(&subGraphLineGraph,&lineGraph,&quadTreeLG);
                        radiiGyrationSquared[numberClustersOfASize.size()-1]+=radiusGyrationSquared;
                    }
                    //                    }else{
                    ////                        radiiGyrationSquared.push_back(0);
                    //                    }
                }
                totalMassWithoutGiantCluster+=clusters[indexesClustersOrderedBySize[i]].transitions.size();
                
                
                
            }
            
        }
        averageMass/=(double)(clusters.size()-1);
        
        double averageS=0;
        double squaredSumOfMassesFiniteAndNotGiant=0;
        //        if(calculateCorrelationLength){
        double numeratorCorrelationLength=0;
        double denominatorCorrelationLength=0;
        
        for(long i=0;i<numberClustersOfASize.size();i++){
            averageS+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y/totalMassWithoutGiantCluster);
            squaredSumOfMassesFiniteAndNotGiant+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y);
            if(calculateCorrelationLength){
                double radiusGyrationSquared=radiiGyrationSquared[i]/numberClustersOfASize[i].y;
                //            numeratorCorrelationLength+=
                numeratorCorrelationLength+=2*radiusGyrationSquared*numberClustersOfASize[i].x*(numberClustersOfASize[i].x)*numberClustersOfASize[i].y/(double)(totalMassOfTheSystem);
                denominatorCorrelationLength+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x)*numberClustersOfASize[i].y/(double)(totalMassOfTheSystem);
            }
        }
        if(calculateCorrelationLength){
            correlationLength.addValue(pow(numeratorCorrelationLength/denominatorCorrelationLength,.5));
            std::cout<<"correlation length "<<pow(numeratorCorrelationLength/denominatorCorrelationLength,.5)<<'\n';
        }
        //        }
        
        std::stringstream lineTemp;
        lineTemp<<distance<<" "<<averageMassGiantCluster<<" "<<totalMassOfTheSystem<<" "<<squaredSumOfMassesFiniteAndNotGiant<<" "<<totalMassWithoutGiantCluster;
        linesFileMasses.push_back(lineTemp.str());
        
        std::vector<string> lines;
        stringstream line;
        line<<"totalMassPrimal"<<" "<<totalMassOfTheSystem;
        lines.push_back(line.str());
        line.str("");
        line<<"totalMassLineGraph"<<" "<<lineGraph.transitions.size();
        lines.push_back(line.str());
        stringstream nameFile;
        nameFile<<Configuration::folderOut()<<"globalMasses.txt";
        TextFile::writeToFile(nameFile.str(), lines, false);
        
        //        lines.clear();
        nameFile.str("");
        nameFile<<Configuration::folderOut()<<"masses"<<distance<<".txt";
        //        TextFile::writeToFile(nameFile.str(), masses, false);
        masses.save(nameFile.str());
        
        
        averageMasses.addValue(averageS);
        numberClusters.addValue(clusters.size());
        LinearRegression lr;
        lr.calculate(masses.setOfValuesEuclidean);
        masses.slopeRegression=lr.slope;
        masses.interceptRegression=lr.intercept;
        masses.regression=true;
        std::cout<<"R2 masses clusters: "<<lr.R2<<'\n';
        evolutionR2Masses.addValue(lr.R2);
        slopeMasses.addValue(lr.slope);
        std::cout<<"slope of the loglog (aka. exponent distribution): "<<lr.slope<<'\n';
        
        //        Plot transitions;
        //        transitions.mode=Plot::EUCLIDEAN;
        //
        //        for(double i=0;i<clusters.size();i++){
        //            transitions.addValue(Point2d(log(i+1),log((double)(clusters[i].transitions.size())+1)));
        //        }
        
        //        lr.calculate(transitions.setOfValuesEuclidean);
        //        transitions.slopeRegression=lr.slope;
        //        transitions.interceptRegression=lr.intercept;
        //        transitions.regression=true;
        //        std::cout<<"R2 masses transitions: "<<lr.R2<<'\n';
        //        evolutionR2Transitions.addValue(lr.R2);
        
        
        
        std::vector<Plot> plots;
        plots.clear();
        plots.push_back(masses);
        //        plots.push_back(transitions);
        if(draw){
            Singleton<Windows>::instance().get(4)->drawPlot(plots);
        }
        if(clusters.size()>1){
            proportionFirstAndSecond.addValue((double)(clusters[indexesClustersOrderedBySize[0]].transitions.size())/(double)(clusters[indexesClustersOrderedBySize[1]].transitions.size()));
            std::cout<<"proportion: "<<(double)(clusters[indexesClustersOrderedBySize[0]].transitions.size())/(double)(clusters[indexesClustersOrderedBySize[1]].transitions.size())<<'\n';
        }
        //    Singleton<Windows>::instance().get(4)->zoomExtents();
        
        
        
        //    Singleton<Windows>::instance().get(5)->zoomExtents();
        
        
        
        stringstream nameNCOL;
        nameNCOL<<Configuration::folderOut()<<"giantClusterNCOL"<<distance<<".txt";
        //        stringstream nameCoordinates;
        //        nameCoordinates<<"/Users/carlos/Documents/results/angularNetworkPercolation/UK/smallAreaUK/"/<<"giantClusterCoordinates"<<angle<<".txt";
        TextFile::writeNCOLFile(&clusters[indexesClustersOrderedBySize[0]], nameNCOL.str());
        //        saveGraph(&clustersPrimal[0], nameNCOL.str(), nameCoordinates.str(), " ", " ");
        
        nameNCOL.str("");
        nameNCOL<<Configuration::folderOut()<<"secondClusterNCOL"<<distance<<".txt";
        //        nameCoordinates.str("");
        //        nameCoordinates<<Configuration::folderOut()<<"secondClusterCoordinates"<<angle<<".txt";
        if(clusters.size()>1){
            TextFile::writeNCOLFile(&clusters[indexesClustersOrderedBySize[1]], nameNCOL.str());
        }
        
        
    }
    if(draw){
        std::vector<Plot> plots;
        plots.push_back(evolutionR2Masses);
        //    plots.push_back(evolutionR2Transitions);
        Singleton<Windows>::instance().get(5)->drawPlot(plots);
        plots.clear();
        plots.push_back(correlationLength);
        Singleton<Windows>::instance().get(3)->drawPlot(plots);
        plots.clear();
        plots.push_back(proportionFirstAndSecond);
        Singleton<Windows>::instance().get(7)->drawPlot(plots);
        plots.clear();
        plots.push_back(slopeMasses);
        Singleton<Windows>::instance().get(6)->drawPlot(plots);
        plots.clear();
        plots.push_back(averageMasses);
        Singleton<Windows>::instance().get(8)->drawPlot(plots);
        plots.clear();
        plots.push_back(evolutionMass1);
        Singleton<Windows>::instance().get(9)->drawPlot(plots);
        plots.clear();
        //    plots.push_back(evolutionMass1);
        plots.push_back(evolutionMass2);
        plots.push_back(evolutionMass3);
        plots.push_back(evolutionMass4);
        plots.push_back(evolutionMass5);
        Singleton<Windows>::instance().get(10)->drawPlot(plots);
        plots.clear();
        plots.push_back(fd);
        Singleton<Windows>::instance().get(11)->drawPlot(plots);
    }
    std::stringstream nameFile;
    nameFile<<Configuration::folderOut()<<"averageS.txt";
    
    averageMasses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"fractalDimension.txt";
    fd.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"proportionFirstAndScond.txt";
    
    proportionFirstAndSecond.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"evolutionGiantCluster.txt";
    evolutionMass1.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"R2Masses.txt";
    evolutionR2Masses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"slopeMasses.txt";
    slopeMasses.save(nameFile.str());
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"correlationLength.txt";
    correlationLength.save(nameFile.str());
    
    std::vector<std::string> lines;
    lines.clear();
    for(long i=0;i<minRealGraph.transitions.size();i++){
        std::stringstream line;
        line.str("");
        line<<minRealGraph.transitions[i].a->originalID<<" "<<minRealGraph.transitions[i].b->originalID<<" "<<minRealGraph.transitions[i].levelHierarchyRoad;
        lines.push_back(line.str());
    }
    //    std::stringstream nameFile;
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"levelHierarchyRoad"<<".txt";
    TextFile::writeToFile(nameFile.str(), lines, false);
    
    
//    lines.clear();
//    for(long i=0;i<minRealGraph.transitions.size();i++){
//        
//        std::stringstream line;
//        line.str("");
//        line<<minRealGraph.transitions[i].a->originalID<<" "<<minRealGraph.transitions[i].b->originalID;
//        for(long j=0;j<probabilityRandomNodeInClusterOfNode[i].size();j++){
//            line<<" "<<probabilityRandomNodeInClusterOfNode[i][j];
//        }
//        if(probabilityRandomNodeInClusterOfNode[i].size()>1){
//            lines.push_back(line.str());
//        }
//    }
//    //    std::stringstream nameFile;
//    nameFile.str("");
//    nameFile<<Configuration::folderOut()<<"probabilityRandomNodeInClusterOfNode"<<".txt";
//    TextFile::writeToFile(nameFile.str(), lines, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"entropy"<<".txt";
    TextFile::writeToFile(nameFile.str(), entropy, false);
    nameFile.str("");
    nameFile<<Configuration::folderOut()<<"summaryEvolutionMasses"<<".txt";
    TextFile::writeToFile(nameFile.str(), linesFileMasses, false);
    
}




void Programs::generateTreeFromPercolation(Graph* graph,std::vector<double> setOfDistances,long numberOfClusters){
    std::unordered_map<signed long long,long> currentCluster;
    std::vector<std::string> ncolPairs;
    std::vector<std::string> masses;
    std::vector<std::vector<signed long long> > nodesBelongingToClusters;
    std::unordered_map<signed long long,long> nodesByOriginalId;
    
    
    
    
    //
    long uniqueId=0;
//    bool generateTree=false;
    std::unordered_map<long,long> massesOfClustersByOriginalId;
    

    
        for(long i=0;i<graph->nodes.size();i++){
            std::vector<signed long long> pair;
            pair.push_back(graph->nodes[i].originalID);
            pair.push_back(-1);
            nodesBelongingToClusters.push_back(pair);
            nodesByOriginalId[graph->nodes[i].originalID]=i;
        }
        
//        
//        std::vector<long> setOfDistances;
        //                        for(long distance=50;distance<=5000;distance+=50){
        //                            setOfDistances.push_back(distance);
        //                        }
//        setOfDistances.push_back(300);
//        setOfDistances.push_back(450);
//        setOfDistances.push_back(800);
        //                        setOfDistances.push_back(600);
//        setOfDistances.push_back(900);
        //                                                setOfDistances.push_back(900);
//        setOfDistances.push_back(1400);
//        setOfDistances.push_back(5000);
        //                                                setOfDistances.push_back(4800);
        //                                                setOfDistances.push_back(4850);
        //                                                setOfDistances.push_back(5000);
        
        
        for(long proxyDistance=0;proxyDistance<setOfDistances.size();proxyDistance++){
            long distance=setOfDistances[proxyDistance];
            //                    std::unordered_map<long,signed long long> correspondancesBetweenRealIdsAndUniqueIds;
            std::vector<Graph> clusters;
            graph->generateNetworkPercolation(distance, clusters, false, true, "", 75,false);
//            graph->generateNetworkPercolation(<#double distanceLimit#>, <#std::vector<Graph> &clusters#>, <#bool saveResultClusters#>, <#bool returnClusters#>, <#std::string nameOfFolderForFiles#>, <#long minClusterSize#>, <#bool probabilistic#>)
            //                    std::vector<std::string> masses;
            
            
            
            
            long maxNumberLoop=0;
            
            if(numberOfClusters==0){
                maxNumberLoop=clusters.size();
            }else{
                maxNumberLoop=Functions::min(numberOfClusters,clusters.size());
            }
            
            std::vector<long> indexOfOrderedClusters;
            std::vector<double> values;
            for(long i=0;i<clusters.size();i++){
                values.push_back(clusters[i].nodes.size());
            }
            
            indexOfOrderedClusters=Functions::getIndexesOfOrderedValues(values, false);
            
            
            for (long i=0;i<maxNumberLoop;i++){
                
                clusters[indexOfOrderedClusters[i]].id=uniqueId;
                std::stringstream mass;
                mass<<distance<<" "<<uniqueId<<" "<<clusters[indexOfOrderedClusters[i]].nodes.size();
                masses.push_back(mass.str());
                uniqueId++;
                for(long j=0;j<clusters[indexOfOrderedClusters[i]].nodes.size();j++){
                    long index=nodesByOriginalId[clusters[indexOfOrderedClusters[i]].nodes[j].originalID];
                    long value=nodesBelongingToClusters[index][1];
                    if(value==-1){
                        nodesBelongingToClusters[index][1]=clusters[indexOfOrderedClusters[i]].id;
                    }
                    if(currentCluster[clusters[indexOfOrderedClusters[i]].nodes[j].originalID]!=0){
                        std::stringstream pair;
                        pair<<(clusters[indexOfOrderedClusters[i]].id)<<" "<<(currentCluster[clusters[indexOfOrderedClusters[i]].nodes[j].originalID]-1)<<" "<<"1";
                        ncolPairs.push_back(pair.str());
                        currentCluster[clusters[indexOfOrderedClusters[i]].nodes[j].originalID]=0;
                        
                    }
                    
                }
                
            }
            for (long i=0;i<clusters.size();i++){
                
                currentCluster[clusters[i].nodes[0].originalID]=clusters[i].id+1;
                
            }
            
        }
        std::vector<std::string> belongingOfNodes;
        for(long i=0;i<nodesBelongingToClusters.size();i++){
            std::stringstream value;
            value<<nodesBelongingToClusters[i][0]<<" "<<nodesBelongingToClusters[i][1];
            belongingOfNodes.push_back(value.str());
        }
        std::stringstream textFileOut;
        textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
        TextFile::writeToFile(textFileOut.str(), ncolPairs, false);
        textFileOut.str("");
        textFileOut<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
        TextFile::writeToFile(textFileOut.str(), masses, false);
        textFileOut.str("");
        textFileOut<<Configuration::folderOut()<<"clusterOfEachNode.txt";
        TextFile::writeToFile(textFileOut.str(), belongingOfNodes, false);

}

void Programs::findCityBorder(Graph* graph){
    
    std::vector<double> setOfDistances;
    for(double i=50;i<500;i+=50){
        setOfDistances.push_back(i);
    }
//    setOfDistances.push_back(200);
//    setOfDistances.push_back(300);
    
    std::vector<std::string> lines;
    for(long proxyDistance=0;proxyDistance<setOfDistances.size();proxyDistance++){
        long distance=setOfDistances[proxyDistance];
        std::cout<<distance<<'\n';
        //                    std::unordered_map<long,signed long long> correspondancesBetweenRealIdsAndUniqueIds;
        std::vector<Graph> clusters;
        graph->generateNetworkPercolation(distance, clusters, false, true, "", 75,false);
        //            graph->generateNetworkPercolation(<#double distanceLimit#>, <#std::vector<Graph> &clusters#>, <#bool saveResultClusters#>, <#bool returnClusters#>, <#std::string nameOfFolderForFiles#>, <#long minClusterSize#>, <#bool probabilistic#>)
        //                    std::vector<std::string> masses;
        
        
        
        
       
        
        std::vector<long> indexOfOrderedClusters;
        std::vector<double> values;
        for(long i=0;i<clusters.size();i++){
            values.push_back(clusters[i].nodes.size());
        }
        
        indexOfOrderedClusters=Functions::getIndexesOfOrderedValues(values, false);
        
        
        std::vector<Node*> externalNodesTemp;
        std::vector<Transition> originDestinationsPairs;
        
//        RTree rTree(RTree::A_STAR);
        
        originDestinationsPairs=clusters[indexOfOrderedClusters[0]].getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&clusters[indexOfOrderedClusters[0]]);
        
        //            originDestinationsPairs.clear();
        //
        //            Transition transTmp;
        //            transTmp.a=&lineGraph.nodes[572784];
        //            transTmp.b=&lineGraph.nodes[1252687];
        //            originDestinationsPairs.push_back(transTmp);
        
        clusters[indexOfOrderedClusters[0]].transformToBidirectional();
        std::stringstream name;
        name<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/cities/london/compactness/clustersPercolation/giantCluster"<<distance<<".txt";
        TextFile::writeNCOLPlusCoordinatesFile(&clusters[indexOfOrderedClusters[0]], name.str());
//
//        clusters[indexOfOrderedClusters[0]].calculateDiameter(Graph::METRIC,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
        clusters[indexOfOrderedClusters[0]].calculateDiameterUsingMainDistance(Configuration::PRECISE, externalNodesTemp, originDestinationsPairs);
        externalNodesTemp.clear();
//        originDestinationsPairs.clear();
//        clusters[indexOfOrderedClusters[0]].calculateDiameter(Graph::TOPOLOGICAL,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
        
        for(long i=0;i<clusters[indexOfOrderedClusters[0]].transitions.size();i++){
            clusters[indexOfOrderedClusters[0]].transitions[i].weight=1;
        }
        clusters[indexOfOrderedClusters[0]].indexOfMainDistanceInOtherDistances=Graph::TOPOLOGICAL;
        clusters[indexOfOrderedClusters[0]].calculateDiameterUsingMainDistance(Configuration::PRECISE, externalNodesTemp, originDestinationsPairs);
        for(long i=0;i<clusters[indexOfOrderedClusters[0]].transitions.size();i++){
            clusters[indexOfOrderedClusters[0]].transitions[i].weight=clusters[indexOfOrderedClusters[0]].transitions[i].otherWeights[clusters[indexOfOrderedClusters[0]].getIndexesOfDistanceType(Graph::METRIC)[0]];
        }
        clusters[indexOfOrderedClusters[0]].indexOfMainDistanceInOtherDistances=Graph::METRIC;
        
        double diameterMetric=clusters[indexOfOrderedClusters[0]].diameters[clusters[indexOfOrderedClusters[0]].getIndexesOfDistanceType(Graph::METRIC)[0]];
        double diameterTopological=clusters[indexOfOrderedClusters[0]].diameters[clusters[indexOfOrderedClusters[0]].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
        
        double m=clusters[indexOfOrderedClusters[0]].transitions.size();
        double tsl=0;
        double minMetricDistance=INFINITY;
        for(long i=0;i<clusters[indexOfOrderedClusters[0]].transitions.size();i++){
            tsl+=clusters[indexOfOrderedClusters[0]].transitions[i].weight;
            if(clusters[indexOfOrderedClusters[0]].transitions[i].weight<minMetricDistance){
                minMetricDistance=clusters[indexOfOrderedClusters[0]].transitions[i].weight;
            }
        }
        
        double compactnessTopological=1-(diameterTopological-1)/(m-1);
        double compactnessMetric=1-(diameterMetric-minMetricDistance)/(tsl-minMetricDistance);
        
        std::stringstream ss;
        
        ss<<distance<<" "<<diameterMetric<<" "<<diameterTopological<<" "<<compactnessMetric<<" "<<compactnessTopological<<" "<<tsl<<" "<<m<<" "<<minMetricDistance<<" 1";
        lines.push_back(ss.str());
        
        
        
    }
    std::stringstream name;
    name<<Configuration::folderOut()<<"valuesCompactnessPreciseB.txt";
    TextFile::writeToFile(name.str(), lines, false);
    
    
    
    
}







void Programs::analyseHierarchyUsingDerivativePercolation(Graph* graph){
    
    
    std::vector<double> averageMasses;
    
    //1. generate percolation
    Graph minRealGraph;
    
    //        TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/results/harmonicCities/uk_subArea.txt", &loadedGraph, " ", false);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Documents/zzz_/gridNCOLAndCoord.txt", &loadedGraph, " ", true);
    //    TextFile::parseNCOLWithCoordinates("/Users/carlos/Dropbox/CASA/results/harmonicCities/minRealGraph2.txt", &minRealGraph, " ", false);
    //    TextFile::includeMasses(&minRealGraph, "/Users/carlos/Documents/results/harmonicCities/massesMinRealGraph.txt", " ", false);
//    graph->transformToBidirectional();
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //        if(minRealGraph.nodes[i].mass<minSizeCity){
    //            minRealGraph.nodes[i].mass=0;
    //        }
    //    }
    
//    graph->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    graph->getGiantComponent(graph, &minRealGraph);
    minRealGraph.transformToBidirectional();
    
    
    //    for(long i=0;i<minRealGraph.nodes.size();i++){
    //
    //
    //        minRealGraph.nodes[i].location.x+=-minX;
    //        minRealGraph.nodes[i].location.y+=-minY;
    //        minRealGraph.nodes[i].location.x*=width/75/1000;
    //        minRealGraph.nodes[i].location.y*=width/75/1000;
    //
    //
    //
    //
    //
    //    }
    ////////////////////////
    
    std::unordered_map<unsigned long long, Node*> nodesOriginalGraphByOriginalId;
    for(long i=0;i<minRealGraph.nodes.size();i++){
        nodesOriginalGraphByOriginalId[minRealGraph.nodes[i].originalID]=&minRealGraph.nodes[i];

    }
   
    
    
    
    

    std::vector<double> entropy;

    
    //      saveGraph(&minRealGraph, "/Users/carlos/Documents/zzz_/smallAreaUKNCOL.txt", "/Users/carlos/Documents/zzz_/smallAreaUKCoordinates.txt", " ", " ");
    
    Graph lineGraph;
    lineGraph.strictlyDirectional=true;
    minRealGraph.createLineGraph(&minRealGraph,&lineGraph);
    
    double totalMassOfSystem=lineGraph.transitions.size()/2;//I need to divide it by two because it is strictlyDirectional and the clusters are not strictlyDirectionals so they have half the number of transitions.
    
    for(long i=0;i<lineGraph.transitions.size();i++){
        lineGraph.transitions[i].weight=lineGraph.transitions[i].otherWeights[lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
    }
    lineGraph.setTypeOfMainDistance(Graph::ANGULAR, 0);
//
//    
////    Graph lineGraphlineGraph;
//    
    std::vector<double> weights;
    for(long i=0;i<lineGraph.transitions.size();i++){
        weights.push_back(lineGraph.transitions[i].weight);
    }
    weights=Functions::orderValues(weights, true);
    std::vector<double> probabilities;
    double numberDivisions=2;
    for(double i=1;i<numberDivisions;i++){
        probabilities.push_back(1/numberDivisions*i);
    }
    long j=0;
    double currentProbability=probabilities[j];
    //    bool setDistance=true;
    
    std::vector<double> setOfAngles;
    
    for(long i=0;i<weights.size();i++){
        //    long i=0;
        //    while(i<weights.size()){
        
        if((double)(i)/(double)weights.size()>currentProbability&&(double)(i-1)/(double)weights.size()<=currentProbability){
            j++;
            currentProbability=probabilities[j];
            setOfAngles.push_back(weights[i]);
            
        }
    }
    
    
    
    
//    double minAngle=setOfAngles[0];
    for(double h=0;h<setOfAngles.size();h++){
        double angle=setOfAngles[h];
        std::cout<<"===================="<<'\n';
        std::cout<<"angle : "<<angle<<'\n';
     
             std::vector<Graph> clusters;
        double averageMassGiantCluster=0;
        double massGiantCluster=0;
        
        //        for(long i=0;i<repetitions;i++){
        clusters.clear();
        minRealGraph.generateAngularPercolation(&minRealGraph,&lineGraph, angle, clusters,0,false);
        std::vector<double> massesClustersTemp;
        for(long i=0;i<clusters.size();i++){
            massesClustersTemp.push_back(clusters[i].transitions.size());
        }
        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
        
        averageMassGiantCluster=clusters[indexesOrderClusters[0]].transitions.size();
        massGiantCluster=clusters[indexesOrderClusters[0]].transitions.size();
 
        
  
        
        double entropyTemp=0;
        for(double i=0;i<clusters.size();i++){
            
            double probabilityCluster=((double)clusters[i].transitions.size()/(double)totalMassOfSystem);
            entropyTemp+=probabilityCluster*log10(probabilityCluster);
        }

        for(double i=0;i<clusters.size();i++){
            for(long j=0;j<clusters[i].nodes.size();j++){
                Node* a=nodesOriginalGraphByOriginalId[clusters[i].nodes[j].transitionThatRepresents->a->originalID];
                
                

                a->transitions[a->indexOfTransitionsByIdOfDestination[clusters[i].nodes[j].transitionThatRepresents->b->originalID]-1]->levelHierarchyRoad+=log((double)clusters[i].transitions.size())*(-entropyTemp);
                
          
            }
        }
        
        entropy.push_back(-entropyTemp);
    
        
        
        
        
        double averageMass=0;
        double totalMassWithoutGiantCluster=0;
        std::vector<Point2d> numberClustersOfASize;
        std::vector<double> radiiGyrationSquared;
        
        
        
        for(double i=0;i<clusters.size();i++){
            
            if(i!=indexesOrderClusters[0]){
                averageMass+=clusters[i].transitions.size();
            }
            
            
            

            if(i!=indexesOrderClusters[0]){
                
                if(numberClustersOfASize.size()==0||clusters[i].transitions.size()!=numberClustersOfASize[numberClustersOfASize.size()-1].x){
                    Point2d point;
                    point.x=clusters[i].transitions.size();
                    point.y=1;
                    numberClustersOfASize.push_back(point);
                    

                }else{
                    numberClustersOfASize[numberClustersOfASize.size()-1].y++;
                
                }
                totalMassWithoutGiantCluster+=clusters[i].transitions.size();
                
                
                
            }
            
        }
        averageMass/=(double)(clusters.size()-1);
        
        double averageS=0;
        double squaredSumOfMassesFiniteAndNotGiant=0;
//        double numeratorCorrelationLength=0;
//        double denominatorCorrelationLength=0;
        
        for(long i=0;i<numberClustersOfASize.size();i++){
            averageS+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y/totalMassWithoutGiantCluster);
            squaredSumOfMassesFiniteAndNotGiant+=numberClustersOfASize[i].x*(numberClustersOfASize[i].x*numberClustersOfASize[i].y);
            
        }
        std::cout<<"averageS "<<averageS<<'\n';
   
        averageMasses.push_back(averageS);
        
       
    }

//    2. detect phase transition automatically
    std::cout<<"===================="<<'\n';
    std::cout<<"2. detect phase transition automatically"<<'\n';
    std::cout<<"===================="<<'\n';
    double definitionPhaseTransition=.1;
    
    
//    double anglePhaseTransition=detectPhaseTransitionAngularPercolation(&minRealGraph, &lineGraph,definitionPhaseTransition);
    double anglePhaseTransition=45.1;
    std::cout<<"===================="<<'\n';
    std::cout<<"Angle of the phase transition "<<anglePhaseTransition<<'\n';
    std::cout<<"===================="<<'\n';
    
  
    std::vector<std::vector<Node*> > finalClusters;
    std::queue<std::vector<Node*> > clustersToExpand;
    
    
    //8. once clusters are detected, then we need to recursively apply the process again to each one of them, and generate a tree in the meantime and an adjacency graph. The adjacency graph can be generated from the hypergraph in which we assign a color 0 to the giant cluster and a different cluster to each of the elements detected in 7. Need to somehow keep track of which node of the hypergraph represents which subArea.
    std::vector<Graph> separatedSubgraphs;
    Graph skeleton;
    
    extractSkeletonAndGenerateSubClusters(&minRealGraph,&lineGraph,&skeleton,anglePhaseTransition,separatedSubgraphs,definitionPhaseTransition);
    std::stringstream nameNCOL;
    
    
    nameNCOL<<Configuration::folderOut()<<"skeleton.txt";
    TextFile::writeNCOLFile(&skeleton, nameNCOL.str());
    
    
    bool useMaximumClusterSize=false;
    
    if(useMaximumClusterSize){
//        for(long i=0;i<separatedSubgraphs.size();i++){
//            std::cout<<"size cluster to expand. First phase. "<<separatedSubgraphs[i].nodes.size()<<'\n';
//    //        std::cout<<"phaseTransition "<<anglePhaseTransition<<'\n';
//            std::vector<Node*> nodes;
//            for(long j=0;j<separatedSubgraphs[i].nodes.size();j++){
//                Node* node=nodesOriginalGraphByOriginalId[separatedSubgraphs[i].nodes[j].originalID];
//    //            std::cout<<separatedSubgraphs[i].nodes[j].nodeThatRepresents->originalID<<'\n';
//                nodes.push_back(node);
//    //            std::cout<<separatedSubgraphs[i].nodes[j].nodeThatRepresents->originalID<<'\n';
//            }
//            if(separatedSubgraphs[i].transitions.size()<600){
//                finalClusters.push_back(nodes);
//            }else{
//                clustersToExpand.push(nodes);
//            }
//        }
//        
//        while(clustersToExpand.size()>0){
//            std::cout<<"size cluster to expand "<<clustersToExpand.front().size()<<'\n';
//            separatedSubgraphs.clear();
//            Graph lineGraphTemp;
//            lineGraphTemp.strictlyDirectional=true;
//            Graph subGraph;
//            minRealGraph.getInducedSubgraph(&subGraph, clustersToExpand.front());
//            subGraph.createLineGraph(&subGraph, &lineGraphTemp);
//            anglePhaseTransition=detectPhaseTransitionAngularPercolation(&subGraph, &lineGraphTemp, definitionPhaseTransition);
//            std::cout<<"phaseTransition "<<anglePhaseTransition<<'\n';
//            Graph subSkeleton;
//            extractSkeletonAndGenerateSubClusters(&minRealGraph,&subGraph,&lineGraphTemp,&subSkeleton,anglePhaseTransition,separatedSubgraphs,definitionPhaseTransition);
//            clustersToExpand.pop();
//            for(long i=0;i<separatedSubgraphs.size();i++){
//                std::vector<Node*> nodes;
//                for(long j=0;j<separatedSubgraphs[i].nodes.size();j++){
//                    Node* node=nodesOriginalGraphByOriginalId[separatedSubgraphs[i].nodes[j].originalID];
//                    //            std::cout<<separatedSubgraphs[i].nodes[j].nodeThatRepresents->originalID<<'\n';
//                    nodes.push_back(node);
//                }
//                if(separatedSubgraphs[i].transitions.size()<600){
//                    finalClusters.push_back(nodes);
//                }else{
//                    clustersToExpand.push(nodes);
//                }
//            }
//        }
    }else{
        for(long i=0;i<separatedSubgraphs.size();i++){
            std::cout<<"size cluster to expand. First phase. "<<separatedSubgraphs[i].nodes.size()<<'\n';
            //        std::cout<<"phaseTransition "<<anglePhaseTransition<<'\n';
            std::vector<Node*> nodes;
            for(long j=0;j<separatedSubgraphs[i].nodes.size();j++){
                Node* node=nodesOriginalGraphByOriginalId[separatedSubgraphs[i].nodes[j].originalID];
                node->numColor=i;
                //            std::cout<<separatedSubgraphs[i].nodes[j].nodeThatRepresents->originalID<<'\n';
                nodes.push_back(node);
                //            std::cout<<separatedSubgraphs[i].nodes[j].nodeThatRepresents->originalID<<'\n';
            }
//            if(separatedSubgraphs[i].transitions.size()<600){
                finalClusters.push_back(nodes);
//            }else{
//                clustersToExpand.push(nodes);
//            }
        }

    }
    
    
    std::vector<double> massesClusters;
    for(long i=0;i<finalClusters.size();i++){
        Graph subGraph;
        minRealGraph.getInducedSubgraph(&subGraph, finalClusters[i]);
        massesClusters.push_back(subGraph.transitions.size());
    }
    std::vector<long> indexOrderedSeparatedSubgraphs=Functions::getIndexesOfOrderedValues(massesClusters, false);
    
    
    
    
    
    
    std::vector<std::string> lines;
//    for(long i=0;i< separatedSubgraphs.size();i++){
////        Graph subGraph;
////        minRealGraph.getInducedSubgraph(&subGraph, finalClusters[indexOrderedSeparatedSubgraphs[i]]);
//        if(separatedSubgraphs[i].transitions.size()>=3){
//            separatedSubgraphs[i].transformToBidirectional();
//            
//            Graph lineGraphSubGraph;
//            
//            lineGraphSubGraph.strictlyDirectional=true;
//            separatedSubgraphs[i].createLineGraph(&separatedSubgraphs[i], &lineGraphSubGraph);
//            
//            //            for(long j=0;j<lineGraphSubGraph.transitions.size();j++){
//            //                lineGraphSubGraph.transitions[j].weight=lineGraphSubGraph.transitions[j].otherWeights[lineGraphSubGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
//            //            }
//            
//            std::cout<<"***************** before detecting the phase transition ********************"<<'\n';
//            std::cout<<"subgraph "<<indexOrderedSeparatedSubgraphs[i]<<" size "<<separatedSubgraphs[i].transitions.size()<<'\n';
//            std::cout<<"********************************************************************"<<'\n';
//            
//            double anglePhaseTransition=detectPhaseTransitionAngularPercolation(&separatedSubgraphs[i], &lineGraphSubGraph, definitionPhaseTransition);
//            std::cout<<"***************** phase transition of subgraphs ********************"<<'\n';
//            std::cout<<"subgraph "<<indexOrderedSeparatedSubgraphs[i]<<" size "<<separatedSubgraphs[i].transitions.size()<<" phase transition "<<anglePhaseTransition<<'\n';
//            std::cout<<"********************************************************************"<<'\n';
//            
//            
//            for(long j=0;j<separatedSubgraphs[i].nodes.size();j++){
//                std::stringstream line;
//                line<<indexOrderedSeparatedSubgraphs[i]<<" "<<separatedSubgraphs[i].nodes[j].originalID<<" "<<separatedSubgraphs[i].transitions.size()<<" "<<anglePhaseTransition;
//                lines.push_back(line.str());
//            }
//        }
//    }
    
    
    
    std::vector<std::string> linesSubSkeleton;
    
    assignFirstAngleInPhaseTransition(&minRealGraph, &lineGraph,floor(anglePhaseTransition));
    
    for(long i=0;i< finalClusters.size();i++){
        
        Graph subSkeleton;
        double anglePhaseTransition=detectPhaseTransitionOfASubclusterAndExtractSkeleton(&minRealGraph,&lineGraph,&subSkeleton,finalClusters[i]);
        if(anglePhaseTransition>0){
            for(long j=0;j<subSkeleton.transitions.size();j++){
                std::stringstream line;
                line<<subSkeleton.transitions[j].a->originalID<<" "<<subSkeleton.transitions[j].b->originalID<<" "<<subSkeleton.transitions[j].weight;
                linesSubSkeleton.push_back(line.str());
            }
            Graph subGraph;
            minRealGraph.getInducedSubgraphIncludingExternalTransitions(&subGraph, finalClusters[indexOrderedSeparatedSubgraphs[i]]);
//            minRealGraph.getInducedSubgraph(&subGraph, finalClusters[indexOrderedSeparatedSubgraphs[i]]);
            for(long j=0;j<subGraph.nodes.size();j++){
                std::stringstream line;
                line<<indexOrderedSeparatedSubgraphs[i]<<" "<<subGraph.nodes[j].originalID<<" "<<subGraph.transitions.size()<<" "<<anglePhaseTransition;
                lines.push_back(line.str());
            }
        }
        
        
//        Graph subGraph;
//        minRealGraph.getInducedSubgraph(&subGraph, finalClusters[indexOrderedSeparatedSubgraphs[i]]);
//        
//        if(subGraph.transitions.size()>=2){
//            subGraph.transformToBidirectional();
//            
//            Graph lineGraphSubGraph;
//            
//            lineGraphSubGraph.strictlyDirectional=true;
//            subGraph.createLineGraph(&subGraph, &lineGraphSubGraph);
//            
////            for(long j=0;j<lineGraphSubGraph.transitions.size();j++){
////                lineGraphSubGraph.transitions[j].weight=lineGraphSubGraph.transitions[j].otherWeights[lineGraphSubGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
////            }
//            
//            std::cout<<"***************** before detecting the phase transition ********************"<<'\n';
//            std::cout<<"subgraph "<<indexOrderedSeparatedSubgraphs[i]<<" size "<<subGraph.transitions.size()<<'\n';
//            std::cout<<"********************************************************************"<<'\n';
//
//            double anglePhaseTransition=detectPhaseTransitionAngularPercolation(&subGraph, &lineGraphSubGraph, definitionPhaseTransition);
//            Graph subSkeleton;
//            extractSkeleton(&minRealGraph,&subGraph,&lineGraphSubGraph,&subSkeleton,anglePhaseTransition,definitionPhaseTransition);
//            for(long j=0;j<subSkeleton.transitions.size();j++){
//                std::stringstream line;
//                line<<subSkeleton.transitions[j].a->originalID<<" "<<subSkeleton.transitions[j].b->originalID<<" "<<subSkeleton.transitions[j].weight;
//                linesSubSkeleton.push_back(line.str());
//            }
//            
//            std::cout<<"***************** phase transition of subgraphs ********************"<<'\n';
//            std::cout<<"subgraph "<<indexOrderedSeparatedSubgraphs[i]<<" size "<<subGraph.transitions.size()<<" phase transition "<<anglePhaseTransition<<'\n';
//            std::cout<<"********************************************************************"<<'\n';
//            
//
//            for(long j=0;j<subGraph.nodes.size();j++){
//                std::stringstream line;
//                line<<indexOrderedSeparatedSubgraphs[i]<<" "<<subGraph.nodes[j].originalID<<" "<<subGraph.transitions.size()<<" "<<anglePhaseTransition;
//                lines.push_back(line.str());
//            }
//        }
    }
    std::stringstream nameFileSubSkeleton;
    nameFileSubSkeleton<<Configuration::folderOut()<<"subSkeleton.txt";
    TextFile::writeToFile(nameFileSubSkeleton.str(), linesSubSkeleton, false);
    std::stringstream nameFile;
    nameFile<<Configuration::folderOut()<<"resultsPhaseTransitionsSubgraphs.txt";
    TextFile::writeToFile(nameFile.str(), lines, false);
    
    
    
    
    
    
    
    
    
    
    
}
void Programs::extractSkeleton(Graph* graph,Graph* lineGraph,Graph* skeleton, double anglePhaseTransition,double definitionPhaseTransition){
    std::vector<Graph> clusters;
    graph->generateAngularPercolation(graph,lineGraph, anglePhaseTransition+definitionPhaseTransition, clusters,0,false);
    std::vector<double> massesClustersTemp;
    for(long i=0;i<clusters.size();i++){
        massesClustersTemp.push_back(clusters[i].transitions.size());
    }
    std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
    
    //skeleton=clusters[indexesOrderClusters[0]];
    
    
    //5. select nodes not in main cluster
    
    for(long i=0;i<clusters[indexesOrderClusters[0]].nodes.size();i++){
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->inCutoff=true;
//        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->inCluster=true;
    }
//    std::vector<Node*> nodesNotInSkeleton;
    std::vector<Transition*> transitionsInSkeleton;
    for(long i=0;i<graph->transitions.size();i++){
        if(!graph->transitions[i].inCutoff){
//            nodesNotInSkeleton.push_back(&graph->nodes[i]);
        }else{
            transitionsInSkeleton.push_back(&graph->transitions[i]);
        }
    }
    
    //    if(saveSkeleton){
    
    graph->getInducedSubgraph(skeleton, transitionsInSkeleton);
    for(long i=0;i<clusters[indexesOrderClusters[0]].nodes.size();i++){
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->inCutoff=false;
        //        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->inCluster=true;
    }
}

double Programs::detectPhaseTransitionOfASubclusterAndExtractSkeleton(Graph* graph,Graph* lineGraph,Graph* skeleton, std::vector<Node*> nodesOfCluster){
    std::vector<double> vectorOfWeights;
    std::vector<double> vectorOfFirstAngleOfPhaseTransitionMainGraph;
    
//    std::vector<Node*> nodesCluster;
//    for(long i=0;i<graph->nodes.size();i++){
//        if(graph->nodes[i].numColor==numColor){
//            nodesCluster.push_back(&graph->nodes[i]);
//            vectorOfFirstAngleOfPhaseTransitionMainGraph.push_back(graph->nodes[i].firstAngleInPhaseTransition);
////            vectorOfWeights.push_back(graph->nodes[i].firstAngleInPhaseTransition);
//        }
//    }
    std::vector<double> massGC;
    long numColor=-2;
    Graph subgraph;
    graph->getInducedSubgraphIncludingExternalTransitions(&subgraph, nodesOfCluster);
//    graph->getInducedSubgraph(&subgraph, nodesOfCluster);
    subgraph.transformToBidirectional();
   
        for(long i=0;i<subgraph.transitions.size();i++){
            if(nodesOfCluster.size()>0){
                subgraph.transitions[i].numColor=nodesOfCluster[0]->numColor;
                numColor=nodesOfCluster[0]->numColor;
            }
            vectorOfFirstAngleOfPhaseTransitionMainGraph.push_back(subgraph.transitions[i].transitionThatRepresents->firstAngleInPhaseTransition);
        }
    
    
//    std::vector<Node*> nodesExtendedSubgraph;
    
//    for(long i=0;i<subgraph.nodes.size();i++){
//        nodesExtendedSubgraph.push_back(subgraph.nodes[i].nodeThatRepresents);
//    }
//    
//    Graph extendedSubgraph;
//    graph->getInducedSubgraphIncludingExternalTransitions(&extendedSubgraph, nodesExtendedSubgraph);
//    
//    nodesExtendedSubgraph.clear();
//    
//    for(long i=0;i<extendedSubgraph.nodes.size();i++){
//        nodesExtendedSubgraph.push_back(extendedSubgraph.nodes[i].nodeThatRepresents);
//    }
    
//    Graph extendedSubgraph;
//    extendedSubgraph.resetGraph();
//    graph->getInducedSubgraphIncludingExternalTransitions(&extendedSubgraph, nodesExtendedSubgraph);
//    Graph lineGraph;
//    subgraph.createLineGraph(&extendedSubgraph, &lineGraph);
    
    for(long i=0;i<lineGraph->transitions.size();i++){
        vectorOfWeights.push_back(lineGraph->transitions[i].otherWeights[lineGraph->getIndexesOfDistanceType(Graph::ANGULAR)[0]]);
    }
//    for(long i=0;i<=180;i++){
//        vectorOfWeights.push_back((double)i);
//    }
    double anglePhaseTransition=0;
    if(vectorOfWeights.size()>1){
    
    
        std::vector<double> orderedVectorOfWeights;
        orderedVectorOfWeights=Functions::orderValues(vectorOfWeights, true);
        
        std::vector<double> orderedVectorOfFirstAngleOfPhaseTransitionMainGraph;
        orderedVectorOfFirstAngleOfPhaseTransitionMainGraph=Functions::orderValues(vectorOfFirstAngleOfPhaseTransitionMainGraph, true);
        

        
        std::vector<double> setOfAngles;
        double min=(orderedVectorOfWeights[0]);
        double max=(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
        for(long i=min;i<=max;i++){
            setOfAngles.push_back((double)i);
        }
        std::vector<double> setOfProbabilities;
        std::vector<double> massesGC;
        for(long i=0;i<setOfAngles.size();i++){
            double totalNumberTransitions=orderedVectorOfWeights.size();
            long index=Functions::findLastPositionValue(orderedVectorOfWeights, setOfAngles[i]);
            double probability=(double)(index)/totalNumberTransitions;
            setOfProbabilities.push_back(probability);
    //        massesGC.push_back((double)(index));
        }
        
        
        
        
        std::vector<long> indexOrderForAngles=Functions::getIndexesOfOrderedValues(setOfAngles, true);
        setOfAngles=Functions::orderVectorUsingAnotherVectorWithPositions(setOfAngles, indexOrderForAngles);
        setOfProbabilities=Functions::orderVectorUsingAnotherVectorWithPositions(setOfProbabilities, indexOrderForAngles);
        
        
    //    massesGC=Functions::orderVectorUsingAnotherVectorWithPositions(massesGC, indexOrderForAngles);
        indexOrderForAngles.clear();
        indexOrderForAngles=Functions::getIndexesOfUniqueValuesFromAlreadyOrderedVector(setOfProbabilities);
        setOfAngles=Functions::orderVectorUsingAnotherVectorWithPositions(setOfAngles, indexOrderForAngles);
        setOfProbabilities=Functions::orderVectorUsingAnotherVectorWithPositions(setOfProbabilities, indexOrderForAngles);
        
        
        for(long i=0;i<setOfAngles.size();i++){
            long index=Functions::findLastPositionValue(orderedVectorOfFirstAngleOfPhaseTransitionMainGraph, setOfAngles[i]);
            massesGC.push_back((double)index/(double)orderedVectorOfFirstAngleOfPhaseTransitionMainGraph.size());
        }
        
    //    massesGC=Functions::orderVectorUsingAnotherVectorWithPositions(massesGC, indexOrderForAngles);
        std::vector<double> derivativeMassGC;
        derivativeMassGC.clear();
        derivativeMassGC=Functions::derivative(massesGC,setOfProbabilities);
        long indexMax=Functions::getLocationMaximum(derivativeMassGC);//plus 1 because the derivative has one object less than the angles
        anglePhaseTransition=setOfAngles[indexMax];
        
        std::vector<Transition*> transitionsInSkeleton;
        for(long i=0;i<subgraph.transitions.size();i++){
            if(subgraph.transitions[i].transitionThatRepresents->firstAngleInPhaseTransition<=anglePhaseTransition+1){
                transitionsInSkeleton.push_back(subgraph.transitions[i].transitionThatRepresents);
            }
        }
        
        graph->getInducedSubgraph(skeleton, transitionsInSkeleton);
        
        std::vector<std::string> lines;
        for(long i=0;i<massesGC.size();i++){
            std::stringstream line;
            line<<numColor<<" "<<setOfAngles[i]<<" "<<setOfProbabilities[i]<<" "<<massesGC[i];
            lines.push_back(line.str());
        }
        
        if(anglePhaseTransition<45.1){
            std::stringstream nameFile;
            nameFile<<Configuration::folderOut()<<"dataAnalysisSubClusters.txt";
            TextFile::writeToFile(nameFile.str(), lines, true);
        }
    }
    
    return anglePhaseTransition;
    
}


void Programs::assignFirstAngleInPhaseTransition(Graph* graph,Graph* lineGraph,double initialAngle){
    
   
    std::cout<<"ASSIGNING FIRST ANGLE IN PHASE TRANSITION"<<'\n';
    for(double angle=initialAngle;angle<=180;angle+=1){
        std::cout<<"angle percolation "<<angle<<'\n';
        std::vector<Graph> clusters;
        graph->generateAngularPercolation(graph,lineGraph, angle, clusters,0,false);
        std::vector<double> massesClustersTemp;
        for(long i=0;i<clusters.size();i++){
            massesClustersTemp.push_back(clusters[i].transitions.size());
        }
        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
        
        for(long i=0;i<clusters[indexesOrderClusters[0]].nodes.size();i++){
            clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->firstAngleInPhaseTransition=Functions::min(angle,clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->firstAngleInPhaseTransition);
//            clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->firstAngleInPhaseTransition=Functions::min(angle,clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->firstAngleInPhaseTransition);
        }
    }

}



void Programs::extractSkeletonAndGenerateSubClusters(Graph* graph,Graph* lineGraph,Graph* skeleton, double anglePhaseTransition,std::vector<Graph> &separatedSubgraphs, double definitionPhaseTransition){
    //4. extract skeleton network
    
    std::vector<Graph> clusters;
    graph->generateAngularPercolation(graph,lineGraph, anglePhaseTransition+definitionPhaseTransition, clusters,0,false);
    std::vector<double> massesClustersTemp;
    for(long i=0;i<clusters.size();i++){
        massesClustersTemp.push_back(clusters[i].transitions.size());
    }
    std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
    
    //skeleton=clusters[indexesOrderClusters[0]];
    
    
    //5. select nodes not in main cluster
    std::vector<Transition*> transitionsSkeleton;
    for(long i=0;i<clusters[indexesOrderClusters[0]].nodes.size();i++){
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->inCutoff=true;
        transitionsSkeleton.push_back(clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents);
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->a->inCluster=true;
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->inCluster=true;
    }
    std::vector<Node*> nodesNotInSkeleton;
    
    for(long i=0;i<graph->nodes.size();i++){
        if(!graph->nodes[i].inCluster){
            nodesNotInSkeleton.push_back(&graph->nodes[i]);
        }
    }
    
//    if(saveSkeleton){
    
        graph->getInducedSubgraph(skeleton, transitionsSkeleton);
        
//        std::stringstream nameNCOL;
//        std::stringstream nameCoordinates;
    
//        nameNCOL<<Configuration::folderOut()<<"skeleton.txt";
        //    nameCoordinates<<Configuration::folderOut()<<"skeletonCoordinates.txt";
        
        //    TextFile::writeNCOLFileAndSeparateCoordinatesFile(&skeleton, <#std::string fileNameNCOL#>, <#std::string fileNameCoordinates#>, <#std::string separatorNCOL#>, <#std::string separatorCoordinates#>)
//        TextFile::writeNCOLFile(skeleton, nameNCOL.str());
//    }
    
    for(long i=0;i<clusters[indexesOrderClusters[0]].nodes.size();i++){
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->inCutoff=false;
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->a->inCluster=false;
        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->inCluster=false;
//        clusters[indexesOrderClusters[0]].nodes[i].nodeThatRepresents->transitionThatRepresents->b->inCluster=false;
    }
    
   
    
    //6. get induced subgraph from the complete network
    
    Graph subGraph;
    subGraph.strictlyDirectional=true;
    graph->getInducedSubgraph(&subGraph, nodesNotInSkeleton);
    //7. generate network percolation with infinite threshold.
    
//    std::vector<Graph> separatedSubgraphs;
    subGraph.generateNetworkPercolation(INFINITY, separatedSubgraphs, false, true, "", 0, false);
}

double Programs::detectPhaseTransitionAngularPercolation(Graph* graph,Graph* lineGraph,double definition){
 
    double anglePhaseTransition=0;
    std::vector<double> setOfAngles;
//    std::vector<double> averageMasses;

    
    
    int indexDistanceCurrent=lineGraph->indexOfMainDistanceInOtherDistances;
    
    std::vector<double> vectorOfWeights;
    
        for(long j=0;j<lineGraph->transitions.size();j++){
            if(lineGraph->getIndexesOfDistanceType(Graph::ANGULAR)[0]!=indexDistanceCurrent){
                lineGraph->transitions[j].weight=lineGraph->transitions[j].otherWeights[lineGraph->getIndexesOfDistanceType(Graph::ANGULAR)[0]];
            }
            vectorOfWeights.push_back(lineGraph->transitions[j].weight);
        }
    
    
    std::vector<double> orderedVectorOfWeights;
    orderedVectorOfWeights=Functions::orderValues(vectorOfWeights, true);
    
    
    
    //    Graph lineGraphlineGraph;
    
//        std::vector<double> weights;
//        for(long i=0;i<lineGraph->transitions.size();i++){
//            weights.push_back(lineGraph->transitions[i].weight);
//        }
//        Functions::orderValues(&weights, true);
//        std::vector<double> probabilities;
////        double numberDivisions=15;
//        for(double i=1;i<numberDivisions;i++){
//            probabilities.push_back(1/numberDivisions*i);
//        }
//        long j=0;
//        double currentProbability=probabilities[j];
//        //    bool setDistance=true;
//    
////        std::vector<double> setOfAngles;
//    
//        for(long i=0;i<orderedVectorOfWeights.size();i++){
//            //    long i=0;
//            //    while(i<weights.size()){
//    
//            if((double)(i)/(double)orderedVectorOfWeights.size()>currentProbability&&(double)(i-1)/(double)orderedVectorOfWeights.size()<=currentProbability){
//                j++;
//                currentProbability=probabilities[j];
//                setOfAngles.push_back(orderedVectorOfWeights[i]);
//    
//            }
//        }
    
    
    setOfAngles.push_back(orderedVectorOfWeights[0]+.1);
    setOfAngles.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]+.1);
    std::vector<double> setOfProbabilities;
    std::vector<double> massesGC;
    for(long i=0;i<setOfAngles.size();i++){
        double totalNumberTransitions=lineGraph->transitions.size();
        long index=Functions::findLastPositionValue(orderedVectorOfWeights, setOfAngles[i]);
        double probability=(double)(index)/totalNumberTransitions;
        setOfProbabilities.push_back(probability);
    }

    
        for(double h=0;h<setOfAngles.size();h++){
            double angle=setOfAngles[h];
//            std::cout<<"===================="<<'\n';
//            std::cout<<"angle : "<<angle<<'\n';
    
                 std::vector<Graph> clusters;
            double averageMassGiantCluster=0;
            double massGiantCluster=0;

            clusters.clear();
            graph->generateAngularPercolation(graph,lineGraph, angle, clusters,0,false);
            std::vector<double> massesClustersTemp;
            for(long i=0;i<clusters.size();i++){
                massesClustersTemp.push_back(clusters[i].transitions.size());
            }
            if(clusters.size()>0){
                std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
        
                averageMassGiantCluster=clusters[indexesOrderClusters[0]].transitions.size();
                massGiantCluster=clusters[indexesOrderClusters[0]].transitions.size();
                massesGC.push_back(massGiantCluster);
            }else{

            }
            

    
    
        }
    
//        2. detect phase transition automatically
//        std::cout<<"===================="<<'\n';
//        std::cout<<"2. detect phase transition automatically"<<'\n';
//        std::cout<<"===================="<<'\n';
    
    
        std::vector<double> derivativeMassGC;
        derivativeMassGC=Functions::derivative(massesGC,setOfProbabilities);
        long indexMax=Functions::getLocationMaximum(derivativeMassGC);//plus 1 because the derivative has one object less than the angles
        anglePhaseTransition=setOfAngles[indexMax];
    


    
        //3. (increase definition analysis around phase transition) and repeat previous
    
    
    
    
    
//        std::cout<<"===================="<<'\n';
//        std::cout<<"3. (increase definition analysis around phase transition) and repeat previous"<<'\n';
//        std::cout<<"===================="<<'\n';
    
    
    
    double currentAngle=setOfAngles[indexMax];
    double nextAngle=(currentAngle+setOfAngles[indexMax+1])/2.0;
    double previousAngle=(currentAngle+setOfAngles[indexMax-1])/2.0;
    
    double ca=0,na=0,pa=0;
    
    double distanceBetweenAngles=Functions::max(nextAngle-currentAngle,currentAngle-previousAngle);
        while(distanceBetweenAngles>definition&&!(ca==currentAngle&&pa==previousAngle&&na==nextAngle)){
            
            ca=currentAngle;
            na=nextAngle;
            pa=previousAngle;
    
//            setOfAngles.clear();
//            numberDivisions=2;
//            for(long i=1;i<numberDivisions;i++){
//                setOfAngles.push_back(anglePhaseTransition+i*distanceBetweenAngles/numberDivisions);
//            }

//            minAngle=setOfAngles[0];
//            for(double h=0;h<setOfAngles.size();h++){
            
            
            double angle=nextAngle;
            
            std::vector<Graph> clusters;
        
            clusters.clear();
            graph->generateAngularPercolation(graph,lineGraph, angle, clusters,0,false);
            std::vector<double> massesClustersTemp;
            for(long i=0;i<clusters.size();i++){
                massesClustersTemp.push_back(clusters[i].transitions.size());
            }
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
            if(clusters.size()>0){
                double massGiantCluster=massesClustersTemp[indexesOrderClusters[0]];
                setOfAngles.push_back(angle);
                long index=Functions::findLastPositionValue(orderedVectorOfWeights, angle);
                double totalNumberTransitions=lineGraph->transitions.size();
                double probability=(double)(index)/totalNumberTransitions;
                setOfProbabilities.push_back(probability);
                massesGC.push_back(massGiantCluster);
                
                
                
                
                angle=previousAngle;
                //                std::cout<<"===================="<<'\n';
                //                std::cout<<"angle : "<<angle<<'\n';
    //            std::vector<Graph> clusters;
                
                clusters.clear();
                graph->generateAngularPercolation(graph,lineGraph, angle, clusters,0,false);
                if(clusters.size()>0){
                    massesClustersTemp.clear();
                    for(long i=0;i<clusters.size();i++){
                        massesClustersTemp.push_back(clusters[i].transitions.size());
                    }
                    indexesOrderClusters.clear();
                    indexesOrderClusters=Functions::getIndexesOfOrderedValues(massesClustersTemp, false);
                    massGiantCluster=massesClustersTemp[indexesOrderClusters[0]];
                    setOfAngles.push_back(angle);
                    index=Functions::findLastPositionValue(orderedVectorOfWeights, angle);
                    totalNumberTransitions=lineGraph->transitions.size();
                    probability=(double)(index)/totalNumberTransitions;
                    setOfProbabilities.push_back(probability);
                    massesGC.push_back(massGiantCluster);
                    
                    
                    
                    
                    
                    
                    std::vector<long> indexOrderForAngles=Functions::getIndexesOfOrderedValues(setOfAngles, true);
                    setOfAngles=Functions::orderVectorUsingAnotherVectorWithPositions(setOfAngles, indexOrderForAngles);
                    setOfProbabilities=Functions::orderVectorUsingAnotherVectorWithPositions(setOfProbabilities, indexOrderForAngles);
                    massesGC=Functions::orderVectorUsingAnotherVectorWithPositions(massesGC, indexOrderForAngles);
                    indexOrderForAngles.clear();
                    indexOrderForAngles=Functions::getIndexesOfUniqueValuesFromAlreadyOrderedVector(setOfProbabilities);
                    setOfAngles=Functions::orderVectorUsingAnotherVectorWithPositions(setOfAngles, indexOrderForAngles);
                    setOfProbabilities=Functions::orderVectorUsingAnotherVectorWithPositions(setOfProbabilities, indexOrderForAngles);
                    massesGC=Functions::orderVectorUsingAnotherVectorWithPositions(massesGC, indexOrderForAngles);
                    
                    derivativeMassGC.clear();
                    derivativeMassGC=Functions::derivative(massesGC,setOfProbabilities);
                    indexMax=Functions::getLocationMaximum(derivativeMassGC);//plus 1 because the derivative has one object less than the angles
                    anglePhaseTransition=setOfAngles[indexMax];
                    
                    currentAngle=setOfAngles[indexMax];
                    nextAngle=(currentAngle+setOfAngles[indexMax+1])/2.0;
                    previousAngle=(currentAngle+setOfAngles[indexMax-1])/2.0;

                    distanceBetweenAngles=Functions::max(nextAngle-currentAngle,currentAngle-previousAngle);
                    
                    
                    
                    std::cout<<"===================="<<'\n';
                    std::cout<<"angle : "<<currentAngle<<'\n';
                    std::cout<<"nextAngle : "<<nextAngle<<'\n';
                    std::cout<<"previousAngle : "<<previousAngle<<'\n';
                    std::cout<<"set of angles ";
                    for(long i=0;i<setOfAngles.size();i++){
                        std::cout<<setOfAngles[i]<<" ";
                    }
                    std::cout<<'\n';
                    std::cout<<"set of probabilities ";
                    for(long i=0;i<setOfProbabilities.size();i++){
                        std::cout<<setOfProbabilities[i]<<" ";
                    }
                    std::cout<<'\n';
                    std::cout<<"masses GC ";
                    
                    for(long i=0;i<massesGC.size();i++){
                        std::cout<<massesGC[i]<<" ";
                    }
                    std::cout<<'\n';

                    std::cout<<"derivative masses GC ";
                    
                    for(long i=0;i<derivativeMassGC.size();i++){
                        std::cout<<derivativeMassGC[i]<<" ";
                    }
                    std::cout<<'\n';
                }
            }
//            }
        }
    
    
//    anglePhaseTransition=detectPhaseTransitionAngularPercolation(&minRealGraph, &lineGraph);
//    std::cout<<anglePhaseTransition<<'\n';
    
    
    if(lineGraph->getIndexesOfDistanceType(Graph::ANGULAR)[0]!=indexDistanceCurrent){
        for(long j=0;j<lineGraph->transitions.size();j++){
            lineGraph->transitions[j].weight=lineGraph->transitions[j].otherWeights[indexDistanceCurrent];
        }
    }
    
    return anglePhaseTransition;

}

void Programs::calculateMelbourne(Graph* graph,long startNode,long endNode,double metricRadius,long typeFirstDistance,long typeSecondDistance, long typeDistanceCombined,long indexDistanceCutoff, long indexDistanceCalculation,bool customize){
  
    
    bool testing=false;
    bool combined=false;
    bool isMetric=true;
    if(typeFirstDistance!=typeSecondDistance){
        combined=true;
        isMetric=false;
    }else{
        if(typeFirstDistance!=Graph::METRIC){
            isMetric=false;
        }
    }
    
    
    //            nameSS<<Configuration::folder()<<"data/GIS/UK/uk_ncolCoordinates"<<".txt";
    
//    std::string name=nameSS.str();
//    mainGraph.resetGraph();
    //            mainGraph.numberNodes=0;
    
    //            textFile.parseNCOLWithCoordinates(ncolsTextLines[numClusterTemp],&mainGraph,",");
    
    //            mainGraph.transformToBidirectional();
    
    
//    ArchivoTexto textFile;
    
    

        
    
        //            mainGraph.strictlyDirectional=true;
//        textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true,true);
    
        //            importPrimalGraph(&mainGraph, name);
        graph->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
        graph->insertTopologicalWeights();
        
        graph->calculateGlobalProperties=true;
        graph->calculateCentralities=false;
        graph->calculateOtherDistances=false;
        std::stringstream nameWeights;
        nameWeights<<Configuration::folderIn()<<"weightsGreenAreas.txt";
        
        TextFile::addWeightsToGraph(graph, nameWeights.str(), " ", true, Graph::GREEN_AREAS_IMPEDANCE);
        
        nameWeights.str("");
        nameWeights<<Configuration::folderIn()<<"modifierCognitiveDistance.txt";
        
        TextFile::addWeightsToGraph(graph, nameWeights.str(), " ", true, Graph::COGNITIVE);
        
        nameWeights.str("");
        nameWeights<<Configuration::folderIn()<<"weightTimeDistance.txt";
        
        TextFile::addWeightsToGraph(graph, nameWeights.str(), " ", true, Graph::TIME_DISTANCE);
        
        nameWeights.str("");
        nameWeights<<Configuration::folderIn()<<"weightsTimeDistanceBasedInSlope.txt";
        
        TextFile::addWeightsToGraph(graph, nameWeights.str(), " ", true, Graph::SLOPE);
    
        nameWeights.str("");
        nameWeights<<Configuration::folderIn()<<"pointsDegrees.txt";
        
        
        TextFile::includeOriginalDegreeOfNodes(graph, nameWeights.str(), " ", true);
    
        std::cout<<"graph imported, numberNodes= "<<graph->nodes.size()<<'\n';
        
        //                    mainGraph.transformToBidirectional();
        //            mainGraph.bidirectional=true;
        
        Graph lineGraph;
        graph->createLineGraphMelbourne(graph, &lineGraph);
        
        
        std::cout<<"lineGraph generated, numberNodes= "<<lineGraph.nodes.size()<<'\n';
        lineGraph.avoidBacktrackingInLineGraph=false;
        std::vector<double> max;
        //
        for(long j=0;j<lineGraph.nodes.size();j++){
            for(long h=0;h<lineGraph.nodes[j].transitions.size();h++){
                for(int i=0;i<lineGraph.nodes[j].transitions[h]->otherWeights.size();i++){
                    if(i>=max.size()){
                        max.push_back(lineGraph.nodes[j].transitions[h]->otherWeights[i]);
                    }else{
                        if(max[i]<lineGraph.nodes[j].transitions[h]->otherWeights[i]){
                            max[i]=lineGraph.nodes[j].transitions[h]->otherWeights[i];
                        }
                    }
                }
            }
        }
        std::cout<<"max. calculated "<<'\n';
        std::vector<Node*> externalNodesTemp;
        std::vector<Transition> originDestinationsPairs;
    std::vector<Transition> originDestinationsPairsTemp;
        
//        RTree rTree(RTree::A_STAR);
//    QTree qTree;
    
    originDestinationsPairs=Graph::getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&lineGraph);
    std::cout<<"size of originDestinationsPairs : "<<originDestinationsPairs.size()<<'\n';
    
//    originDestinationsPairs.push_back(originDestinationsPairsTemp[0]);
    
    
        
        //            originDestinationsPairs.clear();
        //
        //            Transition transTmp;
        //            transTmp.a=&lineGraph.nodes[572784];
        //            transTmp.b=&lineGraph.nodes[1252687];
        //            originDestinationsPairs.push_back(transTmp);
        
        
        if((!testing&&combined)||!isMetric){
            lineGraph.calculateDiameter(Graph::METRIC,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
        }
        double originalMetricDiameter=1;
        if((!testing&&combined)||!isMetric){
            originalMetricDiameter=lineGraph.diameters[lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0]];
        }
        std::cout<<"metric diameter calculated "<<originalMetricDiameter<<'\n';
        
        int firstDistance=lineGraph.getIndexesOfDistanceType((int)typeFirstDistance)[0];
        int secondDistance=lineGraph.getIndexesOfDistanceType((int)typeSecondDistance)[0];
//        int typeDistanceCombined=Graph::COMBINED_METRIC_COGNITIVE;
    if(combined){
        for(double alpha=0;alpha<=1;alpha+=.25){
            lineGraph.pushNewDistance((int)typeDistanceCombined);
            for(long i=0;i<lineGraph.nodes.size();i++){
                for(long j=0;j<lineGraph.nodes[i].transitions.size();j++){
                    //                    int indexMetric=lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0];
                    //                    int indexAngular=lineGraph.getIndexesOfDistanceType(Graph::COGNITIVE)[0];
                    //                    int indexCombined=lineGraph.getIndexesOfDistanceType(Graph::COMBINED_METRIC_COGNITIVE)[alpha*10];
                    
                    //
                    double combined=alpha*lineGraph.nodes[i].transitions[j]->otherWeights[firstDistance]/max[firstDistance]+(1-alpha)*lineGraph.nodes[i].transitions[j]->otherWeights[secondDistance]/max[secondDistance];
                    //                    double combined=alpha*lineGraph.nodes[i].transitions[j].otherWeights[firstDistance]+(1-alpha)*lineGraph.nodes[i].transitions[j].otherWeights[secondDistance];
                    lineGraph.nodes[i].transitions[j]->otherWeights.push_back(combined);
                    
                }
            }
            std::cout<<"combined distance "<<alpha<<". generated "<<'\n';
        }
    }
        std::vector<double> proportions;
        if(!testing&&combined){
            lineGraph.calculateDiameter((int)typeDistanceCombined,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
            std::cout<<"diameters combined calculated "<<'\n';
            //        for(int i=0;i<14;i++){
            //            std::cout<<"diameters "<<i<<" : "<<lineGraph.diameters[i]<<'\n';
            //        }
            
            for(int h=0;h<lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined).size();h++){
                proportions.push_back(lineGraph.diameters[lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[h]]/originalMetricDiameter);
                std::cout<<"proportions "<<h<<" : "<<proportions[h]<<'\n';
            }
        }else if(!isMetric){
            lineGraph.calculateDiameter((int)typeDistanceCombined,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
            std::cout<<"other diameter "<<lineGraph.diameters[lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[0]]/originalMetricDiameter<<'\n';
            proportions.push_back(lineGraph.diameters[lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[0]]/originalMetricDiameter);
        }
        std::cout<<"proportions calculated "<<'\n';
        lineGraph.customize.useDistributionDistances=customize;
        nameWeights.str("");
        nameWeights<<Configuration::folderIn()<<"tripsGeneratedByUse.txt";
        if(lineGraph.customize.useGeneratedAndAttractedTrips){
            TextFile::includeTripsGeneratedByType(graph,&lineGraph, nameWeights.str(), " ", true);
        }
        
        
        
        
        //            textFile.includeValuesToPassBetweenness(&lineGraph, nameWeights.str(), " ", true);
        
        
        
        
        
        //            nameWeights.str("");
        //            nameWeights<<Configuration::folderIn()<<"population.txt";
        //            textFile.includePopulation(&lineGraph, nameWeights.str(), " ", true);
        //            std::cout<<"population included"<<'\n';
        //            for(long i=0;i<lineGraph.nodes.size();i++){
        //                lineGraph.nodes[i].tripsGenerated=lineGraph.nodes[i].population;
        //                lineGraph.nodes[i].tripsReceived=lineGraph.nodes[i].valueToPass;
        //            }
        //            std::cout<<"diameters and max calculated, metric= "<<lineGraph.diameters[lineGraph.getIndexesOfDistanceType(lineGraph.METRIC)[0]]<<" angular= "<<lineGraph.diameters[lineGraph.getIndexesOfDistanceType(lineGraph.ANGULAR)[0]]<<'\n';
        
        
        
//        double metricRadius=5000;
//        int indexDistanceCutOff=0;
//        int indexDistanceCalculation=0;
        double radius;
        if(testing){
            radius=.2;
            //                radius=metricRadius/max[firstDistance];
            //                radius=0;
        }else if (!isMetric){
            std::cout<<"proportion "<<proportions[indexDistanceCutoff]<<'\n';
            radius=metricRadius*proportions[indexDistanceCutoff];
        }else{
            radius=metricRadius;
        }
        
        //        radius=0;
        std::cout<<"radius "<<radius<<'\n';
        //        int indexAlpha=0;
//        long startNode=0;
        if(endNode==0){
            endNode=lineGraph.nodes.size();
        }
        //                long endNode=101;
        int threadNumber=0;
        int indexDistanceInOtherDistancesCutoff=lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[indexDistanceCutoff];
        
        
        int indexDistanceInOtherDistancesCalculation=lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[indexDistanceCalculation];
        //        calculateSubgraphsAndCentralities(&lineGraph,radius,startNode,endNode,threadNumber,indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
        std::vector<int> setOfDistancesToCalculate;
        setOfDistancesToCalculate.push_back((int)indexDistanceCalculation);
        for(long i=startNode;i<endNode;i++){
            for(long j=0;j<lineGraph.nodes[i].transitions.size();j++){
                lineGraph.nodes[i].transitions[j]->weight=lineGraph.nodes[i].transitions[j]->otherWeights[indexDistanceInOtherDistancesCutoff];
            }
        }
        lineGraph.indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCutoff;
        
    
        if(lineGraph.customize.useGeneratedAndAttractedTrips){
            
//            QTree quadTree;
//            lineGraph.insertGraphIntoQTree(&quadTree);
//            for(long i=startNode;i<endNode;i++){
//                Node* nodeInit=&lineGraph.nodes[i];


//                lineGraph.customize.prepareGeneratedRoundTrips(&lineGraph,&quadTree,nodeInit, radius);
//            }
        }
        lineGraph.prepareForCentralitiesCalculation();
    
        
        //            calculateCentralitiesEuclideanCutoff(&lineGraph,&quadTree,metricRadius,startNode,endNode,threadNumber,indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
//        calculateCentralities(&lineGraph,radius,startNode,endNode,threadNumber,indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
        lineGraph.calculationCentralities(&lineGraph, radius, startNode,endNode, threadNumber, indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
//        lineGraph.calculationCentralities(<#Graph *graph#>, <#double radius#>, <#long startNode#>, <#long endNode#>, <#int threadNumber#>, <#int indexDistanceInOtherDistancesCutoff#>, <#int indexDistanceInOtherDistancesCalculation#>)
    
        std::vector<std::string> values;
        for(long i=0;i<lineGraph.nodes.size();i++){
            std::stringstream strstr;
            Node* nodeTemp=&lineGraph.nodes[i];
            strstr<<nodeTemp->originalID<<" "<<lineGraph.closenessMeasures[lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[indexDistanceCalculation]][nodeTemp->id]<<" "<<lineGraph.betweennessMeasures[lineGraph.getIndexesOfDistanceType((int)typeDistanceCombined)[indexDistanceCalculation]][nodeTemp->id];
            values.push_back(strstr.str());
        }
        //        ArchivoTexto textFile;
        std::stringstream nameSSFileCalculationCentralities;
        nameSSFileCalculationCentralities<<Configuration::folderOut()<<"calculationCentralitiesMelbourne_"<<typeDistanceCombined<<"_"<<metricRadius<<"_"<<indexDistanceCutoff<<"_"<<indexDistanceCalculation<<"_"<<customize<<".txt";
        
        TextFile::writeToFile(nameSSFileCalculationCentralities.str(), values, false);
        values.clear();
        
        
        
        
        std::cout<<"centralities calculated "<<'\n';
    
}
void Programs::simplifyNetwork(Graph* graph){
    
    std::vector<Graph> clusters;
//    graph->generateSpatialPercolation(graph, 10, clusters);
//    graph->generateNetworkPercolation(20, clusters, false, true, "", 0, false);
    Graph lineGraph;
    graph->createLineGraph(graph, &lineGraph);
    graph->generateAngularPercolation(graph, &lineGraph, 1, clusters, 0, false);
    Graph supergraph;
    std::vector<Graph> primalClusters;
    for(long i=0;i<clusters.size();i++){
        std::vector<Transition*> transitions;
        for(long j=0;j<clusters[i].nodes.size();j++){
            transitions.push_back(clusters[i].nodes[j].nodeThatRepresents->transitionThatRepresents);
        }
        Graph subGraph;
        graph->getInducedSubgraph(&subGraph, transitions);
        primalClusters.push_back(subGraph);
    }
    graph->generateSuperGraphFromClusters(primalClusters, graph, &supergraph);
    std::stringstream name;
    name<<Configuration::folderOut()<<"simplifiedNetwork_angular.txt";
    TextFile::writeNCOLFile(&supergraph, name.str());
    
    
    
}




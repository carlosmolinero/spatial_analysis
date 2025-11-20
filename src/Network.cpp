//
//  Network.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 04/07/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "Network.h"




void Network::generateRoadNetworkBetweenNodes(Graph* mainGraph,double minSizeCity,double definition){
    std::vector<City> cities;
    PotentialField potentialField;
    Graph potentialFieldGraph;
    
    Graph lineGraphPotentialFieldGraph;
    
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;
    
    for(long i=0;i<mainGraph->nodes.size();i++){
        if(maxX<mainGraph->nodes[i].location.x){
            maxX=mainGraph->nodes[i].location.x;
        }
        if(maxY<mainGraph->nodes[i].location.y){
            maxY=mainGraph->nodes[i].location.y;
        }
   
        if(minX>mainGraph->nodes[i].location.x){
            minX=mainGraph->nodes[i].location.x;
        }
        if(minY>mainGraph->nodes[i].location.y){
            minY=mainGraph->nodes[i].location.y;
        }
    }
    
    
    
    //GENERATE POTENTIALFIELD
    double width=max(maxX-minX,maxY-minY);
//    double definition=3;
    double widthCluster=definition*width/100;
    long numberElements=width/widthCluster+1;
    double startX=minX;
    double startY=minY;
    potentialField.initLocation=Point2d(startX,startY);
    potentialField.width=widthCluster;
    potentialField.numberObjectsInRow=numberElements;
    
    
    
    
    
    
    for(long i=0;i<numberElements*numberElements;i++){
        
        
        
        ClusterField cluster(Point2d(i%numberElements*widthCluster+startX-widthCluster/2,i/numberElements*widthCluster+startY-widthCluster/2),Point2d(i%numberElements*widthCluster+startX+widthCluster/2,i/numberElements*widthCluster+startY+widthCluster/2));
        potentialField.clusters.push_back(cluster);
        potentialFieldGraph.addNode();
        potentialFieldGraph.nodes[i].location=potentialField.clusters[i].calculateCentroid();
        potentialField.clusters[i].id=i;
        
        
        
        ClusterField clusterC(Point2d(i%numberElements*widthCluster+startX-widthCluster/2,i/numberElements*widthCluster+startY-widthCluster/2),Point2d(i%numberElements*widthCluster+startX+widthCluster/2,i/numberElements*widthCluster+startY+widthCluster/2));
        
        
        
    }
    
    
    //ADD NODES TO MAINGRAPH TO REPRESENT POSITIONS OF POTENTIALFIELD NOT COVERED BY MAINGRAPH
    for(long i=0;i<mainGraph->nodes.size();i++){
        ClusterField* cluster=potentialField.getCluster(mainGraph->nodes[i].location);
        cluster->numberNodes++;
        Node* node=&mainGraph->nodes[i];
        cluster->idsNodesInCluster.push_back(node->id);
        
    }
//    QTree quadTreeTemp;
//    mainGraph->insertGraphIntoQTree(&quadTreeTemp);
    for(long i=0;i<potentialField.clusters.size();i++){
        
        ClusterField* cluster=&potentialField.clusters[i];
//        std::vector<Node*> nodesInRange=quadTreeTemp.getNodesInARange(cluster.corner1.x, cluster.corner1.y, cluster.corner2.x, cluster.corner2.y);
        if(cluster->numberNodes==0){
            mainGraph->addNode();
            mainGraph->nodes[mainGraph->nodes.size()-1].mass=0;
            
            mainGraph->nodes[mainGraph->nodes.size()-1].location=cluster->calculateCentroid();
            
            cluster->numberNodes++;
            Node* node=&mainGraph->nodes[mainGraph->nodes.size()-1];
            cluster->idsNodesInCluster.push_back(node->id);
        }
        
    }
    
    for(int i=0;i<mainGraph->nodes.size();i++){
        if(mainGraph->nodes[i].mass>minSizeCity){
            
            City city;
            city.node=&mainGraph->nodes[i];
            city.init();
            cities.push_back(city);
            
            
            //        std::cout<<"masses cities "<<cities[i].node->mass<<'\n';
        }
    }
    
        saveOriginalPositions(mainGraph);
    
    
    //INSERT VALUES FROM NODES INTO POTENTIALFIELD
    
    potentialField.reset();
    //    potentialFieldTemp.reset();
    std::vector<double> masses;
    for(long i=0;i<cities.size();i++){
        masses.push_back(cities[i].node->mass);
    }
    VectorNDim minMaxMasses=Functions::getMinMax(masses);
    
    //    accumCitiesAndSinks.resetGraph();
    
    
    
    for(long i=0;i<cities.size();i++){
        
        //        accumCitiesAndSinks.addNode();
        //        accumCitiesAndSinks.nodes[i].mass=cities[i].node->mass;
        //        accumCitiesAndSinks.nodes[i].location=cities[i].node->location;
        Functor angularStrength;
        Functor angularDecay;
        angularDecay.changeMode(Functor::MIN);
//        angularStrength.changeMode(Functor::MAX);
        
        for(long j=0;j<cities.size();j++){
            
            if(i!=j){
                double angle=Functions::getAngle(cities[i].node->location, cities[j].node->location);
                double distance=Functions::getDistance(cities[i].node->location,cities[j].node->location);
                double openness=.5;
                angularDecay.setFunction(&Functions::angularDecay, openness,(pow(distance,1)/4),angle);
                
                angularStrength.setFunction(&Functions::angularDecay, openness,(cities[j].node->mass)/pow(distance,2),angle);
                
            }
        }
        
        
        
        for(long j=0;j<potentialField.clusters.size();j++){
            Point2d centroid;
            centroid.x=(potentialField.clusters[j].corner1.x+potentialField.clusters[j].corner2.x)/2;
            centroid.y=(potentialField.clusters[j].corner1.y+potentialField.clusters[j].corner2.y)/2;
            double distance=Functions::getDistance(cities[i].node->location,centroid);
            double decay=pow(cities[i].node->mass/M_PI,.5);
            decay=(log(cities[i].node->mass));
            decay=.5;
//             decay=((cities[i].node->mass));
//            decay=80;
            
            double R_ij=1.0/(1.0+pow((distance/decay),2.0));
            
            
            double angle=Functions::getAngle(cities[i].node->location,centroid);
            double decay3=angularDecay.output(angle);
            double R3_ij=1.0/(1.0+pow(distance/decay3,2.0));
            
            double value=((cities[i].node->mass));//log
//            value=pow(cities[i].node->mass/M_PI,.5);
//            value=1;
            
            double value3=((angularStrength.output(angle)))*(cities[i].node->mass);
            
            potentialField.addValue(&potentialField.clusters[j],(potentialField.clusters[j].value+(.5*R_ij*value+1*R3_ij*value3)));
            //            potentialFieldTemp.addValue(potentialFieldTemp.clusters[j],potentialFieldTemp.clusters[j].value+(1.0*R_ij*value+1*R3_ij*value3));
            
        }
        
    }
    
//    Singleton<Windows>::instance().get(0)->drawPotentialField(&potentialField,false,true,false);
//    Singleton<Windows>::instance().get(0)->zoomExtents();
    
    //INSERT WEIGHTS INTO GRAPH OF POTENTIALFIELD
    
    
    for(long i=0;i<potentialFieldGraph.nodes.size();i++){
        potentialFieldGraph.nodes[i].transitions.clear();
        potentialFieldGraph.nodes[i].nodesThatReachMe.clear();
        potentialFieldGraph.nodes[i].indexOfTransitionsByIdOfDestination.clear();
        
    }
    potentialFieldGraph.transitions.clear();
    
    
    for(long i=0;i<potentialField.clusters.size();i++){
        
        
        double value=potentialField.clusters[i].value;
        if((value-potentialField.min)/(potentialField.max-potentialField.min)>=0){
            
            long column=i%potentialField.numberObjectsInRow;
            long row=i/potentialField.numberObjectsInRow;
            std::vector<ClusterField> clustersClose;
            if(column>0){
                clustersClose.push_back(potentialField.clusters[column-1+row*potentialField.numberObjectsInRow]);
                if(row<potentialField.clusters.size()/potentialField.numberObjectsInRow-1){
                    clustersClose.push_back(potentialField.clusters[column-1+(row+1)*potentialField.numberObjectsInRow]);
                }
                if(row>0){
                    clustersClose.push_back(potentialField.clusters[column-1+(row-1)*potentialField.numberObjectsInRow]);
                }
            }
            if(column<potentialField.numberObjectsInRow-1){
                clustersClose.push_back(potentialField.clusters[column+1+row*potentialField.numberObjectsInRow]);
                if(row<potentialField.clusters.size()/potentialField.numberObjectsInRow-1){
                    clustersClose.push_back(potentialField.clusters[column+1+(row+1)*potentialField.numberObjectsInRow]);
                }
                if(row>0){
                    clustersClose.push_back(potentialField.clusters[column+1+(row-1)*potentialField.numberObjectsInRow]);
                }
            }
            if(row<potentialField.clusters.size()/potentialField.numberObjectsInRow-1){
                clustersClose.push_back(potentialField.clusters[column+(row+1)*potentialField.numberObjectsInRow]);
            }
            if(row>0){
                clustersClose.push_back(potentialField.clusters[column+(row-1)*potentialField.numberObjectsInRow]);
            }
            Heap<Node*> heap(Heap<Node*>::MAX,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
            
            std::vector<Node> nodes;
            for(long j=0;j<clustersClose.size();j++){
                Node node;
                nodes.push_back(node);
            }
            double max=-INFINITY;
            double min=INFINITY;
            for(long j=0;j<clustersClose.size();j++){
                Node* nodeTemp=&nodes[j];
                nodeTemp->id=j;
                
                nodeTemp->minDistance=clustersClose[j].value;
                heap.push(nodeTemp);
                
                if(max<clustersClose[j].value){
                    max=clustersClose[j].value;
                }
                if(min>clustersClose[j].value){
                    min=clustersClose[j].value;
                }
            }
            long numberConnections=2;
            if(potentialField.clusters[i].value>max||potentialField.clusters[i].value<min){
                numberConnections=clustersClose.size();
                
            }
            
            while(heap.size()>0){
                
                Node* node=heap.pop();
                
                
                Point2d centroidA=potentialField.clusters[i].calculateCentroid();
                Point2d centroidB=clustersClose[node->id].calculateCentroid();
                double valueA=potentialField.clusters[i].value;
                double valueB=clustersClose[node->id].value;
                double distance=Functions::getDistance(centroidA, centroidB);
                
                std::vector<double> otherWeights;
                
                
                double weight=5*distance+distance/log((valueA)+(valueB)+1);
//                 weight=10*distance+distance/((valueA)+(valueB)+1);
                potentialFieldGraph.addDirectedTransition(&potentialFieldGraph.nodes[i],&potentialFieldGraph.nodes[clustersClose[node->id].id],weight,otherWeights);
                
                numberConnections--;
                
            }
        }
    }
    
    potentialFieldGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::POTENTIAL_FIELD);
    
    potentialFieldGraph.transformToBidirectional();
    
    
    //CALCULATE BETWEENNESS
//    
//    lineGraphPotentialFieldGraph.resetGraph();
//    
//    potentialFieldGraph.createLineGraph(&potentialFieldGraph, &lineGraphPotentialFieldGraph);
//    
//    for(long i=0;i<potentialFieldGraph.nodes.size();i++){
//        potentialFieldGraph.nodes[i].valuesToPass[potentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]]=potentialField.clusters[i].value;
//        potentialFieldGraph.nodes[i].originalValuesToPass[potentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]]=potentialField.clusters[i].value;
//        potentialFieldGraph.nodes[i].mass=potentialField.clusters[i].value;
//    }
//    for(long i=0;i<potentialFieldGraph.transitions.size();i++){
//        Transition trans=potentialFieldGraph.transitions[i];
//        potentialFieldGraph.transitions[i].nodeOfLineGraphThatRepresentsThis->valuesToPass[lineGraphPotentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]]=(trans.a->mass+trans.b->mass)/2;
//        potentialFieldGraph.transitions[i].nodeOfLineGraphThatRepresentsThis->originalValuesToPass[lineGraphPotentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]]=(trans.a->mass+trans.b->mass)/2;
//        potentialFieldGraph.transitions[i].nodeOfLineGraphThatRepresentsThis->mass=(trans.a->mass+trans.b->mass)/2;
//        
//        
//    }
//    
//    
//    
//    
//    std::cout<<"Calculation centralities "<<'\n';
//    lineGraphPotentialFieldGraph.useGaussianBetweenness=false;
//    lineGraphPotentialFieldGraph.prepareForCentralitiesCalculation();
//    for(long i=0;i<cities.size();i++){
//        std::cout<<"City id: "<<i<<'\n';
//        Node* node=cities[i].node;
//        ClusterField* cluster=potentialField.getCluster(node->location);
//        Node nodePF=potentialFieldGraph.nodes[cluster->id];
//        //        std::cout<<"masses cities in method "<<node->mass<<'\n';
//        if(node->mass>minSizeCity){
//            for(long j=0;j<nodePF.transitions.size();j++){
//                Node* nodeLGPF=nodePF.transitions[j]->nodeOfLineGraphThatRepresentsThis;
//                lineGraphPotentialFieldGraph.calculationCentralities(&lineGraphPotentialFieldGraph, 0, nodeLGPF->id,nodeLGPF->id+1, 0, lineGraphPotentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0], lineGraphPotentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]);
//                
////                 lineGraphPotentialFieldGraph.calculationCentralities(<#Graph *graph#>, <#double radius#>, <#long startNode#>, <#long endNode#>, <#int threadNumber#>, <#int indexDistanceInOtherDistancesCutoff#>, <#int indexDistanceInOtherDistancesCalculation#>)
//            }
//        }
//        
//    }
    // GENERATE NETWORK
    
    double maxMass=-INFINITY;
    double maxMass2=-INFINITY;
    for(long i=0;i<mainGraph->nodes.size();i++){
        mainGraph->nodes[i].transitions.clear();
        mainGraph->nodes[i].indexOfTransitionsByIdOfDestination.clear();
        mainGraph->nodes[i].nodesThatReachMe.clear();
        if(mainGraph->nodes[i].mass>maxMass){
            maxMass=mainGraph->nodes[i].mass;
        }else if(mainGraph->nodes[i].mass>maxMass2){
            maxMass2=mainGraph->nodes[i].mass;
        }
    }
    mainGraph->transitions.clear();
    
    
    
    
    
//    changeWeightsGraphToBetweenness(&lineGraphPotentialFieldGraph,lineGraphPotentialFieldGraph.getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0],true);
//    QTree quadTree;
//    mainGraph->insertGraphIntoQTree(&quadTree);
    addTransitionsGraph(mainGraph, &potentialFieldGraph, &potentialField,minSizeCity,2);
//
    for(long i=0;i<50;i++){
        correctPositions(mainGraph);
    }
//
//    
//    
//    
    
    
    
}







void Network::changeWeightsGraphToBetweenness(Graph* lineGraph,int indexDistance,bool includeDistance){
    //CHANGE WEIGHTS TO BETWEENNESS
    for(long j=0;j<lineGraph->nodes.size();j++){
        
        Transition* trans=lineGraph->nodes[j].transitionThatRepresents;
        double distance=Functions::getDistance(trans->a->location, trans->b->location);
        double betweenness=(lineGraph->betweennessMeasures[indexDistance][lineGraph->nodes[j].id]);
        
        
        
        double value=0;
        
        if(includeDistance){
            value=distance/pow((betweenness+.00001),.1);//.3
        }else{
            value=1/pow((betweenness+.00001),.1);//.3
        }
        
        
        lineGraph->nodes[j].transitionThatRepresents->weight=value;
    }
    lineGraph->setTypeOfMainDistanceAndInsertIntoDistances(Graph::BETWEENNESS_WEIGHT);
    
}






void Network::addTransitionsGraph(Graph* graph,Graph* potentialFieldGraph,PotentialField* potentialField,double minPopulationToAdd,int hierarchicalLevel){
    
    
    resetPositions(graph);
    
    
    std::vector<Node*> nodes;
    
    
    
    
    
    
    
    for(long i=0;i<potentialField->clusters.size();i++){
        ClusterField clusterA=potentialField->clusters[i];
        std::vector<Node*> nodesInRangeA;
//        std::vector<Node*> nodes;
        nodesInRangeA.resize(clusterA.idsNodesInCluster.size());
        for(long g=0;g<clusterA.idsNodesInCluster.size();g++){
            nodesInRangeA[g]=&graph->nodes[clusterA.idsNodesInCluster[g]];
        }
        double max=-INFINITY;
        
        for(long j=0;j<nodesInRangeA.size();j++){
            if(max<nodesInRangeA[j]->mass){
                max=nodesInRangeA[j]->mass;
            }
        }
        if(max>=minPopulationToAdd){
            nodes.push_back(&potentialFieldGraph->nodes[i]);
        }
        
    }
    
    for(long h=0;h<nodes.size();h++){
        
        
        Node* nodeInit=nodes[h];
        
        nodeInit->minDistance=0;
        
        std::vector<Node*> nodesCutoff;
        Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        nodesCutoff.push_back(nodeInit);
        nodeInit->inCutoff=true;
        nodesToCheckDijkstra.push(nodeInit);
        nodeInit->inDijkstra=true;
        
        
        potentialFieldGraph->calculateDijkstraSpeed(nodeInit,0,nodesCutoff,nodesToCheckDijkstra);
        
        std::vector<Transition*> transitionsInShortestPaths;
        
        std::vector<Node*> leaves;
        
        
        
        for(long k=0;k<nodesCutoff.size();k++){
            nodesCutoff[k]->valueToPass=0.0;
            nodesCutoff[k]->originalValueToPass=0.0;
            
            if(nodesCutoff[k]->numChildren==0){
                
                
                
                if(nodesCutoff[k]!=nodeInit){
                    leaves.push_back(nodesCutoff[k]);
                }
                
                
            }
        }
        
        
        for (long i=0; i<leaves.size(); i++){
            Node* node=leaves[i];
            bool adding=false;
            
            while((node->parent)!=NULL&&node->parent->numChildren==node->parent->numChildrenThatReachedMe+1)
            {
                adding=false;
                
                ClusterField clusterA=potentialField->clusters[node->id];
                std::vector<Node*> nodesInRangeA;
                //        std::vector<Node*> nodes;
                nodesInRangeA.resize(clusterA.idsNodesInCluster.size());
                for(long g=0;g<clusterA.idsNodesInCluster.size();g++){
                    nodesInRangeA[g]=&graph->nodes[clusterA.idsNodesInCluster[g]];
                }
                double max=-INFINITY;
                
                for(long j=0;j<nodesInRangeA.size();j++){
                    if(max<nodesInRangeA[j]->mass){
                        max=nodesInRangeA[j]->mass;
                    }
                }
                if(max>=minPopulationToAdd){
                    
                    node->valueToPass=1.0;
                }
                node->parent->valueToPass+=node->valueToPass;
                if(node->valueToPass>0.0){
                    adding=true;
                }
                if(adding){
                    long index=node->indexOfTransitionsByIdOfDestination[node->parent->originalID]-1;
                    if(index!=-1){
                        Transition* trans=node->transitions[index];
                        transitionsInShortestPaths.push_back(trans);
                    }
                    
                    
                }
                
                node=(node->parent);
                
                
                node->numChildrenThatReachedMe++;
                
                if(node!=nodeInit){
                    
                }
                
                
            }
            if ((node->parent)!=NULL&&node->parent->numChildren>node->parent->numChildrenThatReachedMe+1)
            {
                adding=false;
                ClusterField clusterA=potentialField->clusters[node->id];
                std::vector<Node*> nodesInRangeA;
                //        std::vector<Node*> nodes;
                nodesInRangeA.resize(clusterA.idsNodesInCluster.size());
                for(long g=0;g<clusterA.idsNodesInCluster.size();g++){
                    nodesInRangeA[g]=&graph->nodes[clusterA.idsNodesInCluster[g]];
                }
                double max=-INFINITY;
                
                for(long j=0;j<nodesInRangeA.size();j++){
                    if(max<nodesInRangeA[j]->mass){
                        max=nodesInRangeA[j]->mass;
                    }
                }
                if(max>=minPopulationToAdd){
                    
                    node->valueToPass=1.0;
                }
                node->parent->valueToPass+=node->valueToPass;
                if(node->valueToPass>0.0){
                    adding=true;
                }
                if(adding){
                    long index=node->indexOfTransitionsByIdOfDestination[node->parent->originalID]-1;
                    if(index!=-1){
                        Transition* trans=node->transitions[index];
                        transitionsInShortestPaths.push_back(trans);
                    }
                    
                    
                }
                
                node->parent->numChildrenThatReachedMe++;
                
            }
            
        }
        
        
        
        
        
        
        for(long k=0;k<transitionsInShortestPaths.size();k++){
            
            
            Node* nodePFa=transitionsInShortestPaths[k]->a;
            ClusterField clusterA=potentialField->clusters[nodePFa->id];
            std::vector<Node*> nodesInRangeA;
            //        std::vector<Node*> nodes;
            nodesInRangeA.resize(clusterA.idsNodesInCluster.size());
            for(long g=0;g<clusterA.idsNodesInCluster.size();g++){
                nodesInRangeA[g]=&graph->nodes[clusterA.idsNodesInCluster[g]];
            }
            
            
            Node* nodePFb=transitionsInShortestPaths[k]->b;
            
            
            
            ClusterField clusterB=potentialField->clusters[nodePFb->id];
            std::vector<Node*> nodesInRangeB;
            //        std::vector<Node*> nodes;
            nodesInRangeB.resize(clusterB.idsNodesInCluster.size());
            for(long g=0;g<clusterB.idsNodesInCluster.size();g++){
                nodesInRangeB[g]=&graph->nodes[clusterB.idsNodesInCluster[g]];
            }
            
            
            
            
            double minDistance=INFINITY;
            double maxMassA=-INFINITY;
            double maxMassB=-INFINITY;
            VectorNDim vectorMin;
//            vectorMin.values={-1.0,-1.0};
            vectorMin.values.clear();
            vectorMin.values.push_back(-1);
            vectorMin.values.push_back(-1);
            
            
            
            
            for(long i=0;i<nodesInRangeA.size();i++){
                
                for(long j=0;j<nodesInRangeB.size();j++){
                    double distance=Functions::getDistance(nodesInRangeA[i]->location, nodesInRangeB[j]->location);
                    //
                    
                    if(maxMassA<nodesInRangeA[i]->mass) {
                        maxMassA=nodesInRangeA[i]->mass;
                    }
                    if(maxMassB<nodesInRangeB[j]->mass) {
                        maxMassB=nodesInRangeB[j]->mass;
                    }
                    if(maxMassA<=nodesInRangeA[i]->mass&&maxMassB<=nodesInRangeB[j]->mass){
                        vectorMin.values.clear();
                        vectorMin.values.push_back((double)i);
                        vectorMin.values.push_back((double)j);
                        minDistance=distance;
                    }
                    
                    
                    
                    
                }
                
            }
            std::vector<double> otherWeights;
            Transition trans;
            trans.setTransition(nodesInRangeA[vectorMin[0]],nodesInRangeB[vectorMin[1]],minDistance,otherWeights);
            trans.levelHierarchyRoad=hierarchicalLevel;
            
            graph->addDirectedTransition(trans);
            for(long i=0;i<nodesInRangeA.size();i++){
                
                if(i!=vectorMin[0]&&nodesInRangeA[i]->mass>minPopulationToAdd){
                    double distance=Functions::getDistance(nodesInRangeA[i]->location, nodesInRangeA[vectorMin[0]]->location);
                    std::vector<double> otherWeights;
                    Transition trans;
                    trans.setTransition(nodesInRangeA[vectorMin[0]],nodesInRangeA[i],distance,otherWeights);
                    trans.levelHierarchyRoad=hierarchicalLevel;
                    
                    graph->addDirectedTransition(trans);
                }
            }
            
            
            
            
            for(long i=0; i<nodesCutoff.size(); i++)
            {
                
                nodesCutoff[i]->inCutoff=false;
                
                nodesCutoff[i]->inDijkstra=false;
                nodesCutoff[i]->numChildren=0;
                nodesCutoff[i]->numChildrenThatReachedMe=0;
                nodesCutoff[i]->parent=NULL;
                nodesCutoff[i]->minDistance=INFINITY;
                nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                
                
            }
            
        }
    }
    for(long i=0; i<potentialFieldGraph->nodes.size(); i++)
    {
        
        potentialFieldGraph->nodes[i].inCutoff=false;
        
        potentialFieldGraph->nodes[i].inDijkstra=false;
        potentialFieldGraph->nodes[i].numChildren=0;
        potentialFieldGraph->nodes[i].numChildrenThatReachedMe=0;
        potentialFieldGraph->nodes[i].parent=NULL;
        potentialFieldGraph->nodes[i].minDistance=INFINITY;
        potentialFieldGraph->nodes[i].valueToPass= potentialFieldGraph->nodes[i].originalValueToPass;
        
        
    }
    
    graph->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
//    graph->transformToBidirectional();
    
}

void Network::correctPositions(Graph* graph){
    double increment=.005;//.0005
    for(long i=0;i<graph->nodes.size();i++){
        if(graph->nodes[i].mass<1){
            Point2d centroid(0,0);
            for(long j=0;j<graph->nodes[i].transitions.size();j++){
                centroid.x+=graph->nodes[i].transitions[j]->b->location.x;
                centroid.y+=graph->nodes[i].transitions[j]->b->location.y;
            }
            centroid.x/=(double)(graph->nodes[i].transitions.size());
            centroid.y/=(double)(graph->nodes[i].transitions.size());
            Point2d vector;
            double module=Functions::getDistance(centroid, graph->nodes[i].location);
            double incrementTemp=increment*pow(10,log(module+1));
            vector.x=(centroid.x-graph->nodes[i].location.x)/(module)*incrementTemp;
            vector.y=(centroid.y-graph->nodes[i].location.y)/(module)*incrementTemp;
            
            Point2d newLocation;
            newLocation.x=graph->nodes[i].location.x+vector.x;
            newLocation.y=graph->nodes[i].location.y+vector.y;
            
            
            
            if(Functions::getDistance(vector, Point2d(0,0))>.0005){//.005
                graph->nodes[i].location=newLocation;
            }
            
            
        }
    }
}


void Network::saveOriginalPositions(Graph* graph){
    originalPositions.clear();
    for(long i=0;i<graph->nodes.size();i++){
        originalPositions.push_back(graph->nodes[i].location);
    }
}
void Network::resetPositions(Graph* graph){
    for(long i=0;i<graph->nodes.size();i++){
        graph->nodes[i].location=originalPositions[i];
    }
}




void Network::straightenGraphs(Graph* graph){
    double increment=5;
    for(long i=0;i<graph->nodes.size();i++){
        if(graph->nodes[i].mass<1){
            Point2d centroid(0,0);
            for(long j=0;j<graph->nodes[i].transitions.size();j++){
                centroid.x+=graph->nodes[i].transitions[j]->b->location.x;
                centroid.y+=graph->nodes[i].transitions[j]->b->location.y;
            }
            centroid.x/=(double)(graph->nodes[i].transitions.size());
            centroid.y/=(double)(graph->nodes[i].transitions.size());
            Point2d vector;
            double module=Functions::getDistance(centroid, graph->nodes[i].location);
            double incrementTemp=increment;
            vector.x=(centroid.x-graph->nodes[i].location.x)/(module)*incrementTemp;
            vector.y=(centroid.y-graph->nodes[i].location.y)/(module)*incrementTemp;
            
            Point2d newLocation;
            newLocation.x=graph->nodes[i].location.x+vector.x;
            newLocation.y=graph->nodes[i].location.y+vector.y;
            
            
            graph->nodes[i].location=newLocation;
            
            
        }
    }
}





void Network::saveStatistics(Graph& mainGraph,Graph& minRealGraph,double minSizeCity){
    double totalLenthGeneratedGraph=0;
    double totalLengthOriginalGraph=0;
    
    //    saveOriginalPositions(mainGraph);
    for(long i=0;i<mainGraph.transitions.size();i++){
        double w=Functions::getDistance(mainGraph.transitions[i].a->location,mainGraph.transitions[i].b->location);
        mainGraph.transitions[i].weight=w;
        mainGraph.transitions[i].otherWeights[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=w;
        totalLenthGeneratedGraph+=w;
    }
    for(long i=0;i<minRealGraph.transitions.size();i++){
        double w=Functions::getDistance(minRealGraph.transitions[i].a->location,minRealGraph.transitions[i].b->location);
        minRealGraph.transitions[i].weight=w;
        
        totalLengthOriginalGraph+=w;
    }
    
    minRealGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    
    mainGraph.calculateTSL=true;
    minRealGraph.calculateTSL=true;
    
    calculateCentralitiesOfCities(&mainGraph, mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0], minSizeCity, true);
    
    calculateCentralitiesOfCities(&minRealGraph, minRealGraph.getIndexesOfDistanceType(Graph::METRIC)[0], minSizeCity, true);
    
    
    
    
    
    std::vector<std::string> values;
    for(long i=0;i<mainGraph.nodes.size();i++){
        if(mainGraph.nodes[i].mass>=minSizeCity){
            std::stringstream string;
            string<<mainGraph.nodes[i].originalID<<" "<<mainGraph.nodes[i].mass<<" "<<mainGraph.closenessMeasures[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]][i]<<" "<<mainGraph.betweennessMeasures[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]][i]<<" "<<mainGraph.TSL[i]<<" "<<totalLenthGeneratedGraph;
            values.push_back(string.str());
        }
    }
    
    TextFile::writeToFile("/Users/carlos/Documents/results/harmonicCities/centralitiesGeneratedGraph.txt", values, false);
    values.clear();
    for(long i=0;i<minRealGraph.nodes.size();i++){
        if(minRealGraph.nodes[i].mass>=minSizeCity){
            std::stringstream string;
            string<<minRealGraph.nodes[i].originalID<<" "<<minRealGraph.nodes[i].mass<<" "<<minRealGraph.closenessMeasures[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]][i]<<" "<<minRealGraph.betweennessMeasures[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]][i]<<" "<<minRealGraph.TSL[i]<<" "<<totalLengthOriginalGraph;
            values.push_back(string.str());
        }
    }
    
    TextFile::writeToFile("/Users/carlos/Documents/results/harmonicCities/centralitiesOriginalGraph.txt", values, false);
}





void Network::calculateEdgeBetweennessOfCities(Graph* lineGraph,int indexDistance,double minSizeCity,bool useMassesForValuesToPass){
    lineGraph->useGaussianBetweenness=false;
    lineGraph->prepareForCentralitiesCalculation();
    if(useMassesForValuesToPass){
        for(long i=0;i<lineGraph->nodes.size();i++){
            Transition* trans=lineGraph->nodes[i].transitionThatRepresents;
            Node a=*trans->a;
            Node b =*trans->b;
            if(a.mass==1){
                a.mass=0;
            }
            if(b.mass==1){
                b.mass=0;
            }
            lineGraph->nodes[i].valuesToPass[indexDistance]=(a.mass+b.mass)/2;
            lineGraph->nodes[i].originalValuesToPass[indexDistance]=(a.mass+b.mass)/2;
            
            
        }
    }
    for(long i=0;i<lineGraph->nodes.size();i++){
        
        
        Node* node=&lineGraph->nodes[i];
        
        if(node->transitionThatRepresents->a->mass>minSizeCity||node->transitionThatRepresents->b->mass>minSizeCity){
            
            lineGraph->calculationCentralities(lineGraph, 0, node->id,node->id+1, 0, indexDistance,indexDistance);
            
        }
        
    }
//      for(long i=0;i<lineGraph->nodes.size();i++){
//            Node* node=&lineGraph->nodes[i];
//          node->transitionThatRepresents->widthDrawing=lineGraph->betweennessMeasures[indexDistance][node->id];
//      }
}




void Network::calculateEdgeBetweennessOfCitiesAndUseItAsWidthTransition(Graph* lineGraph,int indexDistance,double minSizeCity,bool useMassesForValuesToPass){
    lineGraph->useGaussianBetweenness=false;
    lineGraph->prepareForCentralitiesCalculation();
    if(useMassesForValuesToPass){
        for(long i=0;i<lineGraph->nodes.size();i++){
            Transition* trans=lineGraph->nodes[i].transitionThatRepresents;
            Node a=*trans->a;
            Node b =*trans->b;
            if(a.mass==1){
                a.mass=0;
            }
            if(b.mass==1){
                b.mass=0;
            }
            lineGraph->nodes[i].valuesToPass[indexDistance]=(a.mass+b.mass)/2;
            lineGraph->nodes[i].originalValuesToPass[indexDistance]=(a.mass+b.mass)/2;
            
            
        }
    }
    for(long i=0;i<lineGraph->nodes.size();i++){
        
        
        Node* node=&lineGraph->nodes[i];
        
        if(node->transitionThatRepresents->a->mass>minSizeCity||node->transitionThatRepresents->b->mass>minSizeCity){
            
            lineGraph->calculationCentralities(lineGraph, 0, node->id,node->id+1, 0, indexDistance,indexDistance);
            
        }
        
    }
    for(long i=0;i<lineGraph->nodes.size();i++){
        Node* node=&lineGraph->nodes[i];
        node->transitionThatRepresents->widthDrawing=lineGraph->betweennessMeasures[indexDistance][node->id];
    }
}

void Network::calculateCentralitiesOfCities(Graph* graph,int indexDistance,double minSizeCity,bool useMassesForValuesToPass){
    graph->useGaussianBetweenness=false;
    graph->prepareForCentralitiesCalculation();
    if(useMassesForValuesToPass){
        for(long i=0;i<graph->nodes.size();i++){
            
            graph->nodes[i].valuesToPass[indexDistance]=graph->nodes[i].mass;
            graph->nodes[i].originalValuesToPass[indexDistance]=graph->nodes[i].mass;
            
            
        }
    }
    for(long i=0;i<graph->nodes.size();i++){
        
        
        Node* node=&graph->nodes[i];
        
        if(graph->nodes[i].mass>=minSizeCity){
            
            graph->calculationCentralities(graph, 0, node->id,node->id+1, 0, indexDistance,indexDistance);
            
        }
        
    }
}





void Network::extractGraphOfCities(Graph* graph,Graph* originalGraph,double minPopulationToAdd,int hierarchicalLevel){
    
    for(long h=0;h<originalGraph->nodes.size();h++){
        
        
        Node* nodeInit=&originalGraph->nodes[h];
        if(nodeInit->mass>minPopulationToAdd){
            
            nodeInit->minDistance=0;
            
            std::vector<Node*> nodesCutoff;
            Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
            nodesCutoff.push_back(nodeInit);
            nodeInit->inCutoff=true;
            nodesToCheckDijkstra.push(nodeInit);
            nodeInit->inDijkstra=true;
            
            
            originalGraph->calculateDijkstraSpeed(nodeInit,0,nodesCutoff,nodesToCheckDijkstra);
            
            std::vector<Transition*> transitionsInShortestPaths;
            
            std::vector<Node*> leaves;
            
            
            
            for(long k=0;k<nodesCutoff.size();k++){
                nodesCutoff[k]->valueToPass=0.0;
                
                
                if(nodesCutoff[k]->numChildren==0){
                    
                    
                    
                    
                    
                    if(nodesCutoff[k]!=nodeInit){
                        leaves.push_back(nodesCutoff[k]);
                    }
                    
                    
                    
                }
            }
            
            
            for (long i=0; i<leaves.size(); i++)
            {
                Node* node=leaves[i];
                bool adding=false;
                
                while((node->parent)!=NULL&&node->parent->numChildren==node->parent->numChildrenThatReachedMe+1)
                {
                    adding=false;
                    
                    if(node->mass>minPopulationToAdd){
                        
                        node->valueToPass=1.0;
                    }
                    node->parent->valueToPass+=node->valueToPass;
                    if(node->valueToPass>0.0){
                        adding=true;
                    }
                    if(adding){
                        long index=node->indexOfTransitionsByIdOfDestination[node->parent->originalID]-1;
                        if(index!=-1){
                            Transition* trans=node->transitions[index];
                            transitionsInShortestPaths.push_back(trans);
                        }
                        
                    }
                    
                    node=(node->parent);
                    
                    
                    node->numChildrenThatReachedMe++;
                    
                    if(node!=nodeInit){
                        
                    }
                    
                    
                }
                if ((node->parent)!=NULL&&node->parent->numChildren>node->parent->numChildrenThatReachedMe+1)
                {
                    adding=false;
                    
                    if(node->mass>minPopulationToAdd){
                        
                        node->valueToPass=1.0;
                    }
                    node->parent->valueToPass+=node->valueToPass;
                    if(node->valueToPass>0.0){
                        adding=true;
                    }
                    if(adding){
                        long index=node->indexOfTransitionsByIdOfDestination[node->parent->originalID]-1;
                        if(index!=-1){
                            Transition* trans=node->transitions[index];
                            transitionsInShortestPaths.push_back(trans);
                        }
                        
                        
                    }
                    
                    node->parent->numChildrenThatReachedMe++;
                    
                }
                
            }
            
            
            
            
            
            
            for(long k=0;k<transitionsInShortestPaths.size();k++){
                
                std::vector<double> otherWeights;
                Transition trans;
                double distance=Functions::getDistance(graph->nodes[transitionsInShortestPaths[k]->a->id].location, graph->nodes[transitionsInShortestPaths[k]->b->id].location);
                trans.setTransition(&graph->nodes[transitionsInShortestPaths[k]->a->id],&graph->nodes[transitionsInShortestPaths[k]->b->id],distance,otherWeights);
                trans.levelHierarchyRoad=hierarchicalLevel;
                
                graph->addDirectedTransition(trans);
                
                
                
                
                
                for(long i=0; i<nodesCutoff.size(); i++)
                {
                    
                    nodesCutoff[i]->inCutoff=false;
                    
                    nodesCutoff[i]->inDijkstra=false;
                    nodesCutoff[i]->numChildren=0;
                    nodesCutoff[i]->numChildrenThatReachedMe=0;
                    nodesCutoff[i]->parent=NULL;
                    nodesCutoff[i]->minDistance=INFINITY;
                    //CUIDADO ESTO ES DIFERENTE A LO NORMAL!! (NO IGUALO A ORIGINAL VALUES TO PASS)
                    nodesCutoff[i]->valueToPass= 0;
                    
                    
                }
                
            }
        }
        
    }
    for(long i=0; i<originalGraph->nodes.size(); i++)
    {
        
        originalGraph->nodes[i].inCutoff=false;
        
        originalGraph->nodes[i].inDijkstra=false;
        originalGraph->nodes[i].numChildren=0;
        originalGraph->nodes[i].numChildrenThatReachedMe=0;
        originalGraph->nodes[i].parent=NULL;
        originalGraph->nodes[i].minDistance=INFINITY;
        originalGraph->nodes[i].valueToPass= originalGraph->nodes[i].originalValueToPass;
        
        
    }
    
    graph->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    graph->transformToBidirectional();
    
}






void Network::imitateShortestPath(Graph* generated,Graph* original,Graph* realShortestPath,Node* nodeInit,Node* nodeEnd,Graph* pathInGenerated,Graph* pathInOriginal){
    
    
    
    
    
    pathInGenerated->strictlyDirectional=true;
    pathInOriginal->strictlyDirectional=true;
    pathInGenerated->resetGraph();
    pathInOriginal->resetGraph();
    nodeInit->minDistance=0;
    
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(nodeInit);
    nodeInit->inCutoff=true;
    nodesToCheckDijkstra.push(nodeInit);
    nodeInit->inDijkstra=true;
    
    
    generated->calculateDijkstraSpeed(nodeInit,0,nodesCutoff,nodesToCheckDijkstra);
    
    std::list<Transition> transitions;
    
    Node* current=nodeEnd;
    while(current!=nodeInit)
    {
        Transition trans;
        std::vector<double> otherWeights;
        
        double distance=Functions::getDistance(current->parent->location, current->location);
        trans.setTransition(current->parent,current, distance, otherWeights);
        transitions.push_front(trans);
        current=current->parent;
        
    }
    
    
    for(long i=0; i<nodesCutoff.size(); i++)
    {
        
        nodesCutoff[i]->inCutoff=false;
        nodesCutoff[i]->inDijkstra=false;
        nodesCutoff[i]->numChildren=0;
        nodesCutoff[i]->numChildrenThatReachedMe=0;
        nodesCutoff[i]->parent=NULL;
        nodesCutoff[i]->minDistance=INFINITY;
        nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
        
    }
    for(long i=0;i<generated->nodes.size();i++){
        pathInGenerated->addNode();
        pathInGenerated->nodes[pathInGenerated->nodes.size()-1].location=generated->nodes[i].location;
        pathInGenerated->nodes[pathInGenerated->nodes.size()-1].mass=generated->nodes[i].mass;
        pathInGenerated->nodes[pathInGenerated->nodes.size()-1].originalID=generated->nodes[i].originalID;
    }
    
    
    for(auto it=transitions.begin();it!=transitions.end();it++){
        std::vector<double> otherWeights;
        double distance=Functions::getDistance(pathInGenerated->nodes[it->a->id].location, pathInGenerated->nodes[it->b->id].location);
        pathInGenerated->addDirectedTransition(&pathInGenerated->nodes[it->a->id], &pathInGenerated->nodes[it->b->id], distance, otherWeights);
        
    }
    
    
    
    
    PotentialField potentialFieldPath;
    
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;
    
    for(long i=0;i<original->nodes.size();i++){
        if(maxX<original->nodes[i].location.x){
            maxX=original->nodes[i].location.x;
        }
        if(maxY<original->nodes[i].location.y){
            maxY=original->nodes[i].location.y;
        }
        if(minX>original->nodes[i].location.x){
            minX=original->nodes[i].location.x;
        }
        if(minY>original->nodes[i].location.y){
            minY=original->nodes[i].location.y;
        }
    }
    
    
    //GENERATE POTENTIALFIELD
    double width=max(maxX-minX,maxY-minY);
    double definition=3;
    double widthCluster=definition*width/900;

    long numberElements=width/widthCluster;
    double startX=widthCluster/2;
    double startY=widthCluster/2;
    potentialFieldPath.initLocation=Point2d(startX,startY);
    potentialFieldPath.width=widthCluster;
    potentialFieldPath.numberObjectsInRow=numberElements;
    
    
    
    
    
    for(long i=0;i<numberElements*numberElements;i++){
        
        
        ClusterField cluster(Point2d(i%numberElements*widthCluster+startX-widthCluster/2,i/numberElements*widthCluster+startY-widthCluster/2),Point2d(i%numberElements*widthCluster+startX+widthCluster/2,i/numberElements*widthCluster+startY+widthCluster/2));
        
        potentialFieldPath.clusters.push_back(cluster);
        potentialFieldPath.clusters[i].id=i;
        
        
        
    }
    
    
    
    
    
    
    double widthInfluence=1;
    std::vector<double> xs=getXBasedOnDistanceFromStartThroughPath(*pathInGenerated,&pathInGenerated->nodes[nodeInit->id],&pathInGenerated->nodes[nodeEnd->id]);
    std::vector<double> ys=getYBasedOnDistanceFromStartThroughPath(*pathInGenerated,&pathInGenerated->nodes[nodeInit->id],&pathInGenerated->nodes[nodeEnd->id]);
    std::vector<Point2d> points;
    for(long j=0;j<xs.size();j++){
        points.push_back(Point2d(xs[j],ys[j]));
        Point2d point=points[j];
        
        double multiplier=1.0;
        if(j==xs.size()-1){
            multiplier=2.0;
        }
        for(long i=0;i<potentialFieldPath.clusters.size();i++){
            
            Point2d centroid=potentialFieldPath.clusters[i].calculateCentroid();
            
            double distance=Functions::getDistance(point, centroid);
            
            potentialFieldPath.addValue(&potentialFieldPath.clusters[i], potentialFieldPath.clusters[i].value+Functions::decay(distance, widthInfluence)*multiplier);
        }
        
        
        
    }
    
    
    
    pathInOriginal->resetGraph();
    for(long i=0;i<original->nodes.size();i++){
        pathInOriginal->addNode();
        pathInOriginal->nodes[pathInOriginal->nodes.size()-1].location=original->nodes[i].location;
        pathInOriginal->nodes[pathInOriginal->nodes.size()-1].mass=original->nodes[i].mass;
        pathInOriginal->nodes[pathInOriginal->nodes.size()-1].originalID=original->nodes[i].originalID;
    }
    
    
    
    QTree quadTree;
    
    original->insertGraphIntoQTree(&quadTree);
    
    Node* nodeInitO=quadTree.getClosestNode(nodeInit->location);
    Node* nodeEndO=quadTree.getClosestNode(nodeEnd->location);
    
    
    
    realShortestPath->resetGraph();
    
    for(long i=0;i<original->nodes.size();i++){
        realShortestPath->addNode();
        realShortestPath->nodes[realShortestPath->nodes.size()-1].location=original->nodes[i].location;
        realShortestPath->nodes[realShortestPath->nodes.size()-1].mass=original->nodes[i].mass;
        realShortestPath->nodes[realShortestPath->nodes.size()-1].originalID=original->nodes[i].originalID;
    }
    
    
    
    for(long i=0;i<original->transitions.size();i++){
        Transition* trans=&original->transitions[i];
        
        double distance=trans->otherWeights[original->getIndexesOfDistanceType(Graph::METRIC)[0]];
        double weight=(distance);
        trans->weight=weight;
        
    }
    
    std::vector<Node*> visitedNodes;
    
    original->AStar(nodeInitO, nodeEndO, visitedNodes, &Graph::metricHeuristic);
    
    
    current=nodeEndO;
    
    while(current!=nodeInitO)
    {
        
        Transition trans;
        std::vector<double> otherWeights;
        
        double distance=Functions::getDistance(current->parent->location, current->location);
        trans.setTransition(&realShortestPath->nodes[current->parent->id],&realShortestPath->nodes[current->id], distance, otherWeights);
        
        
        realShortestPath->addDirectedTransition(trans);
        
        
        current=current->parent;
    }
    
    
    
    for(long h=0; h<visitedNodes.size(); h++)
    {
        
        visitedNodes[h]->minDistance=INFINITY;
        visitedNodes[h]->inAStar=false;
        visitedNodes[h]->inVisitedNodes=false;
        visitedNodes[h]->parent=NULL;
        
    }
    
    
    
    
    
    
    
    
    
    
    for(long i=0;i<original->transitions.size();i++){
        Transition* trans=&original->transitions[i];
        ClusterField* clusterA=potentialFieldPath.getCluster(trans->a->location);
        ClusterField* clusterB=potentialFieldPath.getCluster(trans->b->location);
        double distance=trans->otherWeights[original->getIndexesOfDistanceType(Graph::METRIC)[0]];
        double weight=0+distance/(((clusterA->value+clusterB->value)/2));
        trans->weight=weight;
        
    }
    
    nodeInitO->minDistance=0;
    
    nodesCutoff.clear();
    nodesToCheckDijkstra.clear();
    nodesCutoff.push_back(nodeInitO);
    nodeInitO->inCutoff=true;
    nodesToCheckDijkstra.push(nodeInitO);
    nodeInitO->inDijkstra=true;
    
    
    original->calculateDijkstraSpeed(nodeInitO,0,nodesCutoff,nodesToCheckDijkstra);
    
    
    
    
    
    
    
    
    
    
    
    
    
    current=nodeEndO;
    
    while(current!=nodeInitO)
    {
        
        Transition trans;
        std::vector<double> otherWeights;
        
        double distance=Functions::getDistance(current->parent->location, current->location);
        trans.setTransition(&pathInOriginal->nodes[current->parent->id],&pathInOriginal->nodes[current->id], distance, otherWeights);
        
        
        pathInOriginal->addDirectedTransition(trans);
        
        
        current=current->parent;
    }
    
    
    std::vector<Node*> nodesCutoffFinal;
    for(long i=0; i<nodesCutoff.size(); i++)
    {
        
        nodesCutoff[i]->inCutoff=false;
        nodesCutoff[i]->inDijkstra=false;
        nodesCutoff[i]->numChildren=0;
        nodesCutoff[i]->numChildrenThatReachedMe=0;
        nodesCutoff[i]->parent=NULL;
        nodesCutoff[i]->minDistance=INFINITY;
        nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
}






double Network::comparePaths(Graph& path1,Graph& path2,Node* originA,Node* originB,Node* endA,Node* endB){
    //    Node* current=originA;
    //    double totalDistance=Functions::getDistance(originA->location, endA->location);
    //    double accumulatedAngle=0;
    //
    //    std::vector<Point2d> path1Stats;
    //    path1Stats.push_back(Point2d(0,0));
    //    double previousAngle=0;
    //    while(current->transitions.size()>0){
    //        double angle=Functions::getAngle(current->transitions[0]->a->location, current->transitions[0]->b->location);
    //        double distance=Functions::getDistance(originA->location, current->transitions[0]->b->location);
    //        double localDistance=Functions::getDistance(current->transitions[0]->a->location, current->transitions[0]->b->location);
    //        accumulatedAngle+=angle*localDistance;
    //        previousAngle=angle;
    //
    //        double percentage=distance/totalDistance*100;
    //        path1Stats.push_back(Point2d(percentage,angle));
    //        current=current->transitions[0]->b;
    //    }
    //
    //    totalDistance=0;
    //    accumulatedAngle=0;
    //
    //    totalDistance=Functions::getDistance(originB->location, endB->location);
    //    current=originB;
    //    std::vector<Point2d> path2Stats;
    //    previousAngle=0;
    //    path2Stats.push_back(Point2d(0,0));
    //    while(current->transitions.size()>0){
    //        double angle=Functions::getAngle(current->transitions[0]->a->location, current->transitions[0]->b->location);
    //        double distance=Functions::getDistance(originB->location, current->transitions[0]->b->location);
    //        double localDistance=Functions::getDistance(current->transitions[0]->a->location, current->transitions[0]->b->location);
    //        accumulatedAngle+=angle*localDistance;
    //        previousAngle=angle;
    //
    //        double percentage=distance/totalDistance*100;
    //        path2Stats.push_back(Point2d(percentage,angle));
    //        current=current->transitions[0]->b;
    //    }
    //    std::vector<Point2d> normalizedPoints;
    //    std::vector<Point2d> normalizedPointsA;
    //    std::vector<Point2d> normalizedPointsB;
    //
    //
    //    long j=0;
    //    long k=0;
    //    for(double i=0;i<100;i++){
    //        double valueA=0;
    //        double valueB=0;
    //        if(path1Stats[j].x==i){
    //            valueA=path1Stats[j].y;
    //            j++;
    //        }else {
    //            while(path1Stats[j].x<i){
    //                j++;
    //            }
    //            if(path1Stats[j].x==i){
    //                valueA=path1Stats[j].y;
    //                j++;
    //            }else{
    //
    //                valueA=Functions::interpolate2d(path1Stats[j-1], path1Stats[j], i);
    //
    //            }
    //        }
    //        if(path2Stats[k].x==i){
    //            valueB=path2Stats[k].y;
    //            k++;
    //        }else {
    //            while(path2Stats[k].x<i){
    //                k++;
    //            }
    //            if(path2Stats[k].x==i){
    //                valueB=path2Stats[k].y;
    //                k++;
    //            }else{
    //                valueB=Functions::interpolate2d(path2Stats[k-1], path2Stats[k], i);
    //            }
    //        }
    //        normalizedPoints.push_back(Point2d(valueA,valueB));
    //        normalizedPointsA.push_back(Point2d(i,valueA));
    //        normalizedPointsB.push_back(Point2d(i,valueB));
    //
    //    }
    //
    //    LinearRegression lr;
    //    lr.calculate(normalizedPoints);
    
    
    std::vector<double> xsA=getXBasedOnAbsoluteDistanceFromStart(path1, originA, endA);
    std::vector<double> xsB=getXBasedOnAbsoluteDistanceFromStart(path2, originB, endB);
    
    std::vector<double> ysA=getYBasedOnAbsoluteDistanceFromStart(path1, originA, endA);
    std::vector<double> ysB=getYBasedOnAbsoluteDistanceFromStart(path2, originB, endB);
    
    std::vector<Point2d> pointsX;
    std::vector<Point2d> pointsY;
    double R2=0;
    double distance=0;
    for(long i=0;i<xsA.size();i++){
        pointsX.push_back(Point2d(xsA[i],xsB[i]));
        pointsY.push_back(Point2d(ysA[i],ysB[i]));
        
        distance+=Functions::getDistance(Point2d(xsA[i],ysA[i]), Point2d(xsB[i],ysB[i]));
    }
    
    //    LinearRegression lr;
    //    lr.calculate(pointsX);
    //    R2+=lr.R2;
    //    lr.calculate(pointsY);
    //    R2*=lr.R2;
    ////    R2/=2;
    R2=1/distance;
    
    return R2;
}

















std::vector<double> Network::getLocalAnglesBasedOnAbsoluteDistanceFromStart(Graph& path,Node* origin,Node* destination){
    
    Node* current=origin;
    double totalDistance=Functions::getDistance(origin->location, destination->location);;
    
    std::vector<Point2d> path1Stats;
    
    while(current->transitions.size()>0){
        double angle=Functions::getAngle(current->transitions[0]->a->location, current->transitions[0]->b->location);
        double distance=Functions::getDistance(origin->location, current->transitions[0]->a->location);
        double percentage=distance/totalDistance*100;
        path1Stats.push_back(Point2d(percentage,angle));
        current=current->transitions[0]->b;
    }
    
    long j=0;
    
    std::vector<double> outputs;
    for(double i=0;i<=100;i++){
        double valueA=0;
        
        if(path1Stats[j].x==i){
            
            valueA=path1Stats[j].y;
            j++;
        }else {
            while(path1Stats[j].x<i){
                j++;
            }
            if(path1Stats[j].x==i){
                valueA=path1Stats[j].y;
                j++;
            }else{
                
                valueA=Functions::interpolate2d(path1Stats[j-1], path1Stats[j], i);
            }
        }
        
        outputs.push_back(valueA);
        
    }
    return outputs;
}
std::vector<double> Network::getXBasedOnAbsoluteDistanceFromStart(Graph& path,Node* origin,Node* destination){
    
    Node* current=origin;
    double totalDistance=Functions::getDistance(origin->location, destination->location);;
    
    std::vector<Point2d> path1Stats;
    
    while(current->transitions.size()>0){
        
        double distance=Functions::getDistance(origin->location, current->transitions[0]->a->location);
        double percentage=distance/totalDistance*100;
        path1Stats.push_back(Point2d(percentage,current->transitions[0]->a->location.x));
        current=current->transitions[0]->b;
    }
    path1Stats.push_back(Point2d(100,destination->location.x));
    long j=0;
    
    std::vector<double> outputs;
    for(double i=0;i<=100;i++){
        double valueA=0;
        
        if(path1Stats[j].x==i){
            std::cout<<"pathstats "<<path1Stats[j].x<<" "<<path1Stats[j].y<<'\n';
            valueA=path1Stats[j].y;
            j++;
        }else {
            while(path1Stats[j].x<i){
                j++;
            }
            if(path1Stats[j].x==i){
                valueA=path1Stats[j].y;
                j++;
            }else{
                
                valueA=Functions::interpolate2d(path1Stats[j-1], path1Stats[j], i);
            }
        }
        
        outputs.push_back(valueA);
        
    }
    return outputs;
}
std::vector<double> Network::getYBasedOnAbsoluteDistanceFromStart(Graph& path,Node* origin,Node* destination){
    
    Node* current=origin;
    double totalDistance=Functions::getDistance(origin->location, destination->location);;
    
    std::vector<Point2d> path1Stats;
    
    while(current->transitions.size()>0){
        
        double distance=Functions::getDistance(origin->location, current->transitions[0]->a->location);
        double percentage=distance/totalDistance*100;
        path1Stats.push_back(Point2d(percentage,current->transitions[0]->a->location.y));
        current=current->transitions[0]->b;
    }
    path1Stats.push_back(Point2d(100,destination->location.y));
    long j=0;
    
    std::vector<double> outputs;
    for(double i=0;i<=100;i++){
        double valueA=0;
        
        if(path1Stats[j].x==i){
            std::cout<<"pathstats "<<path1Stats[j].x<<" "<<path1Stats[j].y<<'\n';
            valueA=path1Stats[j].y;
            j++;
        }else {
            while(path1Stats[j].x<i){
                j++;
            }
            if(path1Stats[j].x==i){
                valueA=path1Stats[j].y;
                j++;
            }else{
                
                valueA=Functions::interpolate2d(path1Stats[j-1], path1Stats[j], i);
            }
        }
        
        outputs.push_back(valueA);
        
    }
    return outputs;
}





std::vector<double> Network::getXBasedOnDistanceFromStartThroughPath(Graph& path,Node* origin,Node* destination){
    
    Node* current=origin;
    
    double totalDistance=0;
    
    
    std::vector<Point2d> path1Stats;
    
    while(current->transitions.size()>0){
        
        
        double distance=Functions::getDistance(current->transitions[0]->a->location, current->transitions[0]->b->location);
        totalDistance+=distance;
        
        path1Stats.push_back(Point2d(totalDistance,current->transitions[0]->a->location.x));
        current=current->transitions[0]->b;
    }
    for(long i=0;i<path1Stats.size();i++){
        path1Stats[i].x*=100/totalDistance;
    }
    path1Stats.push_back(Point2d(100,destination->location.x));
    long j=0;
    
    std::vector<double> outputs;
    for(double i=0;i<=100;i++){
        double valueA=0;
        
        if(path1Stats[j].x==i){
            std::cout<<"pathstats "<<path1Stats[j].x<<" "<<path1Stats[j].y<<'\n';
            valueA=path1Stats[j].y;
            j++;
        }else {
            while(path1Stats[j].x<i){
                j++;
            }
            if(path1Stats[j].x==i){
                valueA=path1Stats[j].y;
                j++;
            }else{
                
                valueA=Functions::interpolate2d(path1Stats[j-1], path1Stats[j], i);
            }
        }
        
        outputs.push_back(valueA);
        
    }
    return outputs;
}
std::vector<double> Network::getYBasedOnDistanceFromStartThroughPath(Graph& path,Node* origin,Node* destination){
    
    Node* current=origin;
    double totalDistance=0;
    
    std::vector<Point2d> path1Stats;
    
    while(current->transitions.size()>0){
        
        double distance=Functions::getDistance(current->transitions[0]->a->location, current->transitions[0]->b->location);
        
        totalDistance+=distance;
        path1Stats.push_back(Point2d(totalDistance,current->transitions[0]->a->location.y));
        current=current->transitions[0]->b;
    }
    for(long i=0;i<path1Stats.size();i++){
        path1Stats[i].x*=100/totalDistance;
    }
    path1Stats.push_back(Point2d(100,destination->location.y));
    long j=0;
    
    std::vector<double> outputs;
    for(double i=0;i<=100;i++){
        double valueA=0;
        
        if(path1Stats[j].x==i){
            std::cout<<"pathstats "<<path1Stats[j].x<<" "<<path1Stats[j].y<<'\n';
            valueA=path1Stats[j].y;
            j++;
        }else {
            while(path1Stats[j].x<i){
                j++;
            }
            if(path1Stats[j].x==i){
                valueA=path1Stats[j].y;
                j++;
            }else{
                
                valueA=Functions::interpolate2d(path1Stats[j-1], path1Stats[j], i);
            }
        }
        
        outputs.push_back(valueA);
        
    }
    return outputs;
}














void Network::insertEstimatedBoundaryConditions(Graph* boundaryConditions, PotentialField* potentialField,double multiplier,double minSizeCity){
    for(long i=0;i<potentialField->clusters.size();i++){
        
        
        double value=potentialField->clusters[i].value;
        if((value-potentialField->min)>=0){
            
            long column=i%potentialField->numberObjectsInRow;
            long row=i/potentialField->numberObjectsInRow;
            std::vector<ClusterField> clustersClose;
            if(column>0){
                clustersClose.push_back(potentialField->clusters[column-1+row*potentialField->numberObjectsInRow]);
                if(row<potentialField->clusters.size()/potentialField->numberObjectsInRow-1){
                    clustersClose.push_back(potentialField->clusters[column-1+(row+1)*potentialField->numberObjectsInRow]);
                }
                if(row>0){
                    clustersClose.push_back(potentialField->clusters[column-1+(row-1)*potentialField->numberObjectsInRow]);
                }
            }
            if(column<potentialField->numberObjectsInRow-1){
                clustersClose.push_back(potentialField->clusters[column+1+row*potentialField->numberObjectsInRow]);
                if(row<potentialField->clusters.size()/potentialField->numberObjectsInRow-1){
                    clustersClose.push_back(potentialField->clusters[column+1+(row+1)*potentialField->numberObjectsInRow]);
                }
                if(row>0){
                    clustersClose.push_back(potentialField->clusters[column+1+(row-1)*potentialField->numberObjectsInRow]);
                }
            }
            if(row<potentialField->clusters.size()/potentialField->numberObjectsInRow-1){
                clustersClose.push_back(potentialField->clusters[column+(row+1)*potentialField->numberObjectsInRow]);
            }
            if(row>0){
                clustersClose.push_back(potentialField->clusters[column+(row-1)*potentialField->numberObjectsInRow]);
            }
            
            double max=-INFINITY;
            double min=INFINITY;
            for(long j=0;j<clustersClose.size();j++){
                
                
                if(max<clustersClose[j].value){
                    max=clustersClose[j].value;
                }
                if(min>clustersClose[j].value){
                    min=clustersClose[j].value;
                }
            }
            
            if(potentialField->clusters[i].value<min){
                if(clustersClose.size()<8){
                    boundaryConditions->addNode();
                    boundaryConditions->nodes[boundaryConditions->nodes.size()-1].location=potentialField->clusters[i].calculateCentroid();
                    
                    boundaryConditions->nodes[boundaryConditions->nodes.size()-1].mass=minSizeCity*multiplier;
                }
                
            }
        }
    }
}




void Network::detectSinks(Graph* sinks, PotentialField* potentialField,double multiplier,double minSizeCity){
    for(long i=0;i<potentialField->clusters.size();i++){
        
        
        
        double value=potentialField->clusters[i].value;
        if((value-potentialField->min)>=0){
            
            long column=i%potentialField->numberObjectsInRow;
            long row=i/potentialField->numberObjectsInRow;
            std::vector<ClusterField> clustersClose;
            if(column>0){
                clustersClose.push_back(potentialField->clusters[column-1+row*potentialField->numberObjectsInRow]);
                if(row<potentialField->clusters.size()/potentialField->numberObjectsInRow-1){
                    clustersClose.push_back(potentialField->clusters[column-1+(row+1)*potentialField->numberObjectsInRow]);
                }
                if(row>0){
                    clustersClose.push_back(potentialField->clusters[column-1+(row-1)*potentialField->numberObjectsInRow]);
                }
            }
            if(column<potentialField->numberObjectsInRow-1){
                clustersClose.push_back(potentialField->clusters[column+1+row*potentialField->numberObjectsInRow]);
                if(row<potentialField->clusters.size()/potentialField->numberObjectsInRow-1){
                    clustersClose.push_back(potentialField->clusters[column+1+(row+1)*potentialField->numberObjectsInRow]);
                }
                if(row>0){
                    clustersClose.push_back(potentialField->clusters[column+1+(row-1)*potentialField->numberObjectsInRow]);
                }
            }
            if(row<potentialField->clusters.size()/potentialField->numberObjectsInRow-1){
                clustersClose.push_back(potentialField->clusters[column+(row+1)*potentialField->numberObjectsInRow]);
            }
            if(row>0){
                clustersClose.push_back(potentialField->clusters[column+(row-1)*potentialField->numberObjectsInRow]);
            }
            
            double max=-INFINITY;
            double min=INFINITY;
            for(long j=0;j<clustersClose.size();j++){
                
                
                if(max<clustersClose[j].value){
                    max=clustersClose[j].value;
                }
                if(min>clustersClose[j].value){
                    min=clustersClose[j].value;
                }
            }
            
            if(potentialField->clusters[i].value<min){
                if(clustersClose.size()==8){
                    sinks->addNode();
                    sinks->nodes[sinks->nodes.size()-1].location=potentialField->clusters[i].calculateCentroid();
                    
                    double totalSpan=potentialField->max-potentialField->min;
                    double normValue=pow(1-(potentialField->clusters[i].value-potentialField->min)/totalSpan,2);
                    sinks->nodes[sinks->nodes.size()-1].mass=normValue*minSizeCity*multiplier;
                }
                
            }
        }
    }
}





//void addSinks(double strength,double focus){
//
//
//    sinks.resetGraph();
//    detectSinks(&sinks, &potentialFieldTemp,strength);
//    for(long i=0;i<sinks.nodes.size();i++){
//        accumCitiesAndSinks.addNode();
//        accumCitiesAndSinks.nodes[accumCitiesAndSinks.nodes.size()-1].mass=sinks.nodes[i].mass;
//        accumCitiesAndSinks.nodes[accumCitiesAndSinks.nodes.size()-1].location=sinks.nodes[i].location;
//
//        Functor angularDecay;
//
//        for(long j=0;j<cities.size();j++){
//            //                if(i!=j){
//            double angle=Functions::getAngle(sinks.nodes[i].location, cities[j].node->location);
//            double distance=Functions::getDistance(sinks.nodes[i].location, cities[j].node->location);
//
//            angularDecay.setFunction(&Functions::angularDecay, focus,(sinks.nodes[i].mass*cities[j].node->mass)/pow(distance,2),angle);
//
//        }
//
//
//
//
//        for(long j=0;j<potentialField.clusters.size();j++){
//            Point2d centroid;
//            centroid.x=(potentialField.clusters[j].corner1.x+potentialField.clusters[j].corner2.x)/2;
//            centroid.y=(potentialField.clusters[j].corner1.y+potentialField.clusters[j].corner2.y)/2;
//            double distance=Functions::getDistance(sinks.nodes[i].location,centroid);
//            double decay=pow(sinks.nodes[i].mass/M_PI,.5)*2;
//
//            double R_ij=1.0/(1.0+pow((distance/decay),2.0));
//
//            double angle=Functions::getAngle(sinks.nodes[i].location,centroid);
//
//            double valueTemp=log((sinks.nodes[i].mass+1));//log
//
//            double value=(angularDecay.output(angle))+.1;
//
//
//            potentialField.addValue(potentialField.clusters[j],potentialField.clusters[j].value+0.0*R_ij*value+1.0*R_ij*valueTemp);
//            potentialFieldTemp.addValue(potentialFieldTemp.clusters[j],potentialFieldTemp.clusters[j].value+(1.0*R_ij*valueTemp));
//
//        }
//    }
//    if(sinks.nodes.size()>0){
//        for(long j=0;j<cities.size();j++){
//
//
//            Functor angularDecay;
//
//            for(long i=0;i<sinks.nodes.size();i++){
//
//                double angle=Functions::getAngle( cities[j].node->location,sinks.nodes[i].location);
//                double distance=Functions::getDistance(sinks.nodes[i].location, cities[j].node->location);
//
//                angularDecay.setFunction(&Functions::angularDecay, focus,(sinks.nodes[i].mass*cities[j].node->mass)/pow(distance,2),angle);
//
//
//            }
//
//
//
//
//            for(long k=0;k<potentialField.clusters.size();k++){
//                Point2d centroid;
//                centroid.x=(potentialField.clusters[k].corner1.x+potentialField.clusters[k].corner2.x)/2;
//                centroid.y=(potentialField.clusters[k].corner1.y+potentialField.clusters[k].corner2.y)/2;
//                double distance=Functions::getDistance(cities[j].node->location,centroid);
//                double decay=pow(cities[j].node->mass/M_PI,.5)*2;
//
//                double R_ij=1.0/(1.0+pow((distance/decay),2.0));
//
//                double angle=Functions::getAngle(cities[j].node->location,centroid);
//
//                double value=(angularDecay.output(angle))+.1;
//
//
//
//                potentialField.addValue(potentialField.clusters[k],potentialField.clusters[k].value+0.0*R_ij*value);
//
//            }
//        }
//    }
//}


















void Network::generatePotentialFieldFromGraph(Graph* graph,PotentialField* potentialField,long numberElements){
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;
    
    for(long i=0;i<graph->nodes.size();i++){
        if(maxX<graph->nodes[i].location.x){
            maxX=graph->nodes[i].location.x;
        }
        if(maxY<graph->nodes[i].location.y){
            maxY=graph->nodes[i].location.y;
        }
        if(minX>graph->nodes[i].location.x){
            minX=graph->nodes[i].location.x;
        }
        if(minY>graph->nodes[i].location.y){
            minY=graph->nodes[i].location.y;
        }
    }
    
//GENERATE POTENTIALFIELD
    double width=max(maxX-minX+2,maxY-minY+2);
//    double definition=10;
    double widthCluster=width/(double)(numberElements);
//    long numberElements=width/widthCluster+1;
    double startX=minX;
    double startY=minY;
    potentialField->initLocation=Point2d(startX,startY);
    potentialField->width=widthCluster;
    potentialField->numberObjectsInRow=numberElements;






    for(long i=0;i<numberElements*numberElements;i++){
  
//        ClusterField cluster(Point2d(i%numberElements*widthCluster+startX-widthCluster/2.0,i/numberElements*widthCluster+startY-widthCluster/2.0),Point2d(i%numberElements*widthCluster+startX+widthCluster/2.0,i/numberElements*widthCluster+startY+widthCluster/2.0));
        ClusterField cluster(Point2d(i%numberElements*widthCluster+startX,i/numberElements*widthCluster+startY),Point2d(i%numberElements*widthCluster+startX,i/numberElements*widthCluster+startY));
        potentialField->clusters.push_back(cluster);
        potentialField->clusters[i].id=i;

    }
    
}


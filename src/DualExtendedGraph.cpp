//
//  DualExtendedGraph.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 28/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "DualExtendedGraph.h"

DualExtendedGraph::~DualExtendedGraph(){
    this->reset();
}

void DualExtendedGraph::softReset(){

    if(structuralGraphConstructed){
        getStructuralGraph()->reset();
    }
    if(lineGraphConstructed){
        getLineGraph()->reset();
    }
    if(dualGraphConstructed){
        getDualGraph()->reset();
    }
    if(isPlanarGraphConstructed){
        getPlanarGraph()->reset();
    }
     if(isPlanarGraphConstructed){
            getPlanarGraph()->reset();
        }
        if(dualPlanarGraphConstructed){
            getDualPlanarGraph()->reset();
        }
        // deg->isPlanarGraphConstructed=false;

    idsLinksPrimalByIdsLinksStructural.clear();
    dualGraph.setAsDualGraph();
    dualGraphConstructed=false;
    isSimplified=false;
    structuralGraphConstructed=false;
    primalIsStructuralGraph=false;
    primalIsBidirectional=false;
    lineGraphConstructed=false;
    currentWeightsInLineGraph=METRIC;
    keepTrackDifferencesBetweenPrimalAndStructural=true;
    isPlanarGraphConstructed=false;
    dualPlanarGraphConstructed=false;
    currentWeightsInLineGraph=DualExtendedGraph::METRIC;
}

DualExtendedGraph::DualExtendedGraph(){
    roundaboutsRemoved=false;
    dualGraph.setAsDualGraph();
    isSimplified=false;
    structuralGraphConstructed=false;
    primalIsStructuralGraph=false;
    primalIsBidirectional=false;
    lineGraphConstructed=false;
    keepTrackDifferencesBetweenPrimalAndStructural=true;
    currentWeightsInLineGraph=METRIC;
    dualGraphConstructed=false;
    isPlanarGraphConstructed=false;
    dualPlanarGraphConstructed=false;
    currentWeightsInLineGraph=DualExtendedGraph::METRIC;
    idsLinksPrimalByIdsLinksStructural.clear();
}


void DualExtendedGraph::reset(){
    roundaboutsRemoved=false;

    if(structuralGraphConstructed){
        getStructuralGraph()->reset();
    }
    if(lineGraphConstructed){
        getLineGraph()->reset();
    }
    if(dualGraphConstructed){
        getDualGraph()->reset();
    }
    if(isPlanarGraphConstructed){
        getPlanarGraph()->reset();
    }
     if(isPlanarGraphConstructed){
            getPlanarGraph()->reset();
        }
        if(dualPlanarGraphConstructed){
            getDualPlanarGraph()->reset();
        }
        // deg->isPlanarGraphConstructed=false;
        getPrimalGraph()->reset();
    idsLinksPrimalByIdsLinksStructural.clear();
    dualGraph.setAsDualGraph();
    dualGraphConstructed=false;
    isSimplified=false;
    structuralGraphConstructed=false;
    primalIsStructuralGraph=false;
    primalIsBidirectional=false;
    lineGraphConstructed=false;
    currentWeightsInLineGraph=METRIC;
    keepTrackDifferencesBetweenPrimalAndStructural=true;
    isPlanarGraphConstructed=false;
    dualPlanarGraphConstructed=false;
    currentWeightsInLineGraph=DualExtendedGraph::METRIC;
}



//DualExtendedGraph::~DualExtendedGraph(){
//    dual.~Grafo();
//    primal.~Grafo();
//}

void DualExtendedGraph::addPrimal(DualExtendedGraph* deg,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >  &coordinates,bool directed){
    Grafo::create(&deg->primalGraph, ncol, coordinates, directed);
    if(!directed){
        deg->primalIsBidirectional=true;
    }
    // for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    //   deg->dataLinksPrimal.tags.push_back(std::unordered_map<std::string,std::string> ());
    // }
    // DualExtendedGraph::simplify(deg);
}

void DualExtendedGraph::addPrimal(DualExtendedGraph* deg,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >  &coordinates,std::vector<double> masses,bool directed){
    Grafo::create(&deg->primalGraph, ncol, coordinates,masses, directed);
    if(!directed){
        deg->primalIsBidirectional=true;
    }
    // for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    //   deg->dataLinksPrimal.tags.push_back(std::unordered_map<std::string,std::string> ());
    // }
    // DualExtendedGraph::simplify(deg);
}

void DualExtendedGraph::addPrimal(DualExtendedGraph* deg,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >  &coordinates,std::vector<std::string> &originalIds,int type,bool directed){
    Grafo::create(&deg->primalGraph, ncol, coordinates,originalIds,type, directed);
    if(!directed){
        deg->primalIsBidirectional=true;
    }
    // for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    //   deg->dataLinksPrimal.tags.push_back(std::unordered_map<std::string,std::string> ());
    // }
    // DualExtendedGraph::simplify(deg);
}

void DualExtendedGraph::addPrimal(DualExtendedGraph* deg,Grafo* G){
//    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  ncol=Grafo::getNCOL(G);
//    std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >  coordinates=Grafo::getCoordinates(G);
    // DualExtendedGraph::addPrimal(deg, ncol,coordinates,!G->bidirectional);
   deg->primalGraph.copyGraph(G);
   for(long i=0;i<deg->primalGraph.links.size();i++){
    deg->primalGraph.links[i]->originalID=i;
   }
   // for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
   //   deg->dataLinksPrimal.tags.push_back(std::unordered_map<std::string,std::string> ());
   // }
//    if(G->bidirectional){
//        deg->primalIsBidirectional=true;
//    }
}

//void DualExtendedGraph::addPrimal(DualExtendedGraph* deg,Grafo* G){
//    DualExtendedGraph::addAnotherGraph(deg, G, true);
//
//}

void DualExtendedGraph::addAnotherGraph(DualExtendedGraph* deg,Grafo* otherGraph,bool finishAddingGraphs){
    for(long i=0;i<otherGraph->nodes.size();i++){
        // Nodo* node=deg->getPrimalGraph()->addNodeAndCopyProperties(otherGraph->nodes[i]);

        Nodo* node=deg->getPrimalGraph()->addNode(otherGraph->nodes[i]->location);
        node->identifier=otherGraph->nodes[i]->identifier;
        node->mass=otherGraph->nodes[i]->mass;
    }
    for(long i=0;i<otherGraph->links.size();i++){
        Nodo* nodeA=deg->getPrimalGraph()->addNode(otherGraph->links[i]->A()->location);
        Nodo* nodeB=deg->getPrimalGraph()->addNode(otherGraph->links[i]->B()->location);
        // long id=deg->getPrimalGraph()->addLinkAndCopyProperties(nodeA->id, nodeB->id,otherGraph->links[i]);
        long numberLinks=deg->getPrimalGraph()->links.size();
        long id=deg->getPrimalGraph()->addLink(nodeA->id, nodeB->id,otherGraph->links[i]->weight);
        if(deg->getPrimalGraph()->links.size()>numberLinks){
          deg->getPrimalGraph()->links[id]->copyProperties(otherGraph->links[i]);
          deg->getPrimalGraph()->links[id]->originalID=id;
          // deg->dataLinksPrimal.tags.push_back(std::unordered_map<std::string,std::string> ());
        }
        // deg->getPrimalGraph()->links[id]->identifier=otherGraph->links[i]->identifier;
        // deg->getPrimalGraph()->links[id]->identifier="a";
    }
    if(finishAddingGraphs){
        deg->getPrimalGraph()->finishedAddingNodes();
    }
    deg->isSimplified=false;
    deg->getPrimalGraph()->isPlanar=false;

    // Grafo temp;
    // temp.copyProperties(deg->getPrimalGraph());
    // // Grafo::getLargestComponent(deg->getPrimalGraph(), &LCC);
    // temp.copyGraph(deg->getPrimalGraph());
    deg->softReset();
    // deg->primalGraph.copyGraph(&temp);

    // Grafo temp;
    // for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    //     temp.addNodeAndCopyProperties(deg->getPrimalGraph()->nodes[i]);
    // }
    // for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    //     Nodo* nodeA=temp.addNode(deg->getPrimalGraph()->links[i]->A()->location);
    //     Nodo* nodeB=temp.addNode(deg->getPrimalGraph()->links[i]->B()->location);
    //     long id=temp.addLinkAndCopyProperties(nodeA->id, nodeB->id,deg->getPrimalGraph()->links[i]);
    //     temp.links[id]->originalID=id;
    // }




    // DualExtendedGraph::addPrimal(deg,&temp);

    // DualExtendedGraph::simplify(deg);
}



void DualExtendedGraph::addAnotherDEG(DualExtendedGraph* deg,DualExtendedGraph* otherDEG,bool finishAddingGraphs){
    for(long i=0;i<otherDEG->getPrimalGraph()->nodes.size();i++){
        // Nodo* node=deg->getPrimalGraph()->addNodeAndCopyProperties(otherGraph->nodes[i]);

        Nodo* node=deg->getPrimalGraph()->addNode(otherDEG->getPrimalGraph()->nodes[i]->location);
        node->identifier=otherDEG->getPrimalGraph()->nodes[i]->identifier;
        node->mass=otherDEG->getPrimalGraph()->nodes[i]->mass;
    }
    for(long i=0;i<otherDEG->getPrimalGraph()->links.size();i++){
        Nodo* nodeA=deg->getPrimalGraph()->addNode(otherDEG->getPrimalGraph()->links[i]->A()->location);
        Nodo* nodeB=deg->getPrimalGraph()->addNode(otherDEG->getPrimalGraph()->links[i]->B()->location);
        // long id=deg->getPrimalGraph()->addLinkAndCopyProperties(nodeA->id, nodeB->id,otherGraph->links[i]);
        long numberLinks=deg->getPrimalGraph()->links.size();
        long id=deg->getPrimalGraph()->addLink(nodeA->id, nodeB->id,otherDEG->getPrimalGraph()->links[i]->weight);
        if(deg->getPrimalGraph()->links.size()>numberLinks){
          deg->getPrimalGraph()->links[id]->copyProperties(otherDEG->getPrimalGraph()->links[i]);
          deg->getPrimalGraph()->links[id]->originalID=id;
          // deg->getPrimalGraph()->links[id]->identifier=otherDEG->getPrimalGraph()->links[i]->identifier;
          // deg->getData()->tags.push_back(otherDEG->getData()->tags[i]);
        }
        // deg->getPrimalGraph()->links[id]->identifier=otherGraph->links[i]->identifier;
        // deg->getPrimalGraph()->links[id]->identifier="a";
    }
    if(finishAddingGraphs){
        deg->getPrimalGraph()->finishedAddingNodes();
    }
    deg->isSimplified=false;
    deg->getPrimalGraph()->isPlanar=false;

    // Grafo temp;
    // temp.copyProperties(deg->getPrimalGraph());
    // // Grafo::getLargestComponent(deg->getPrimalGraph(), &LCC);
    // temp.copyGraph(deg->getPrimalGraph());
    deg->softReset();
    // deg->primalGraph.copyGraph(&temp);

    // Grafo temp;
    // for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    //     temp.addNodeAndCopyProperties(deg->getPrimalGraph()->nodes[i]);
    // }
    // for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    //     Nodo* nodeA=temp.addNode(deg->getPrimalGraph()->links[i]->A()->location);
    //     Nodo* nodeB=temp.addNode(deg->getPrimalGraph()->links[i]->B()->location);
    //     long id=temp.addLinkAndCopyProperties(nodeA->id, nodeB->id,deg->getPrimalGraph()->links[i]);
    //     temp.links[id]->originalID=id;
    // }




    // DualExtendedGraph::addPrimal(deg,&temp);

    // DualExtendedGraph::simplify(deg);
}




void DualExtendedGraph::useOnlyLargestConnectedComponent(DualExtendedGraph* deg){
    Grafo LCC;
    LCC.copyProperties(deg->getPrimalGraph());
    Grafo::getLargestComponent(deg->getPrimalGraph(), &LCC);
    deg->primalGraph.reset();
    deg->primalGraph.copyGraph(&LCC);
}

void DualExtendedGraph::setPrimalAsPlanar(DualExtendedGraph* deg){
    deg->primalGraph.isPlanar=true;
}
void DualExtendedGraph::setPrimalAsSimplified(DualExtendedGraph* deg){
    deg->isSimplified=true;
}

void DualExtendedGraph::setPrimalAsStructuralGraph(DualExtendedGraph* deg){
    // deg->primalGraph.isPlanar=true;
//    deg->primalStructure.copyGraph(&deg->primal);
    // deg->structuralGraphConstructed=fals;
    deg->primalIsStructuralGraph=true;
}
void DualExtendedGraph::unSetPrimalAsStructuralGraph(DualExtendedGraph* deg){
    // deg->primalGraph.isPlanar=false;
//    deg->primalStructure.copyGraph(&deg->primal);
    // deg->structuralGraphConstructed=false;
    deg->primalIsStructuralGraph=false;
}
bool DualExtendedGraph::isPrimalStructural(DualExtendedGraph* deg){
    return (deg->primalIsStructuralGraph);
}
Grafo* DualExtendedGraph::getStructuralGraph(){

    if(primalIsStructuralGraph){
        return &primalGraph;
    }else{

        if(structuralGraphConstructed){
            return &structuralGraph;
        }else{
        DualExtendedGraph::buildStructuralGraph(this);
        return &structuralGraph;
            }
    }
}

Grafo* DualExtendedGraph::getPrimalGraph(){
    return &primalGraph;
}

Grafo* DualExtendedGraph::getDualGraph(){
    if(!dualGraphConstructed){
        createDual(this,&this->primalGraph,&dualGraph);
    }
    return &dualGraph;
}
Grafo* DualExtendedGraph::getDualPlanarGraph(){
    if(!dualPlanarGraphConstructed){
        createDual(this,this->getPlanarGraph(),&this->dualPlanarGraph);
    }
    return &dualPlanarGraph;
}
Grafo* DualExtendedGraph::getLineGraph(){
    if(!lineGraphConstructed){
        createLineGraph(this);
    }
    return &lineGraph;
}

Data* DualExtendedGraph::getData(){
  return &dataLinksPrimal;
}

//void DualExtendedGraph::setPrimalAsStructuralGraph(DualExtendedGraph* deg){
//    deg->primal.isPlanar=true;
//    deg->primalStructure.copyGraph(&deg->primal);
//}

void DualExtendedGraph::constructPlanarGraph(DualExtendedGraph* deg,int mode){
    if(!deg->isPlanarGraphConstructed){
        // if(deg->getPrimalGraph()->is3d){
            // Grafo planar;
            deg->primalPlanarGraph.copyGraphForcingPlanarity(deg->getPrimalGraph());

            for(long i=0;i<deg->primalPlanarGraph.nodes.size();i++){
                deg->primalPlanarGraph.nodes[i]->originalID=deg->primalPlanarGraph.nodes[i]->id;
            }
            for(long i=0;i<deg->primalPlanarGraph.links.size();i++){
                deg->primalPlanarGraph.links[i]->originalID=deg->primalPlanarGraph.links[i]->id;
            }

            // deg->getPrimalGraph()->reset();
            // deg->getPrimalGraph().copyGraphForcingPlanarity(&temp);
        // }
        std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
        if(mode==Grafo::PLANARITY_PLANESWEEP){
            Grafo::forcePlanarityPlaneSweep(&deg->primalPlanarGraph,Grafo::SPEED,pairsOldIdNewIds,deg->dataLinksPrimal.size()>0);
        }else if(mode==Grafo::PLANARITY_LINESWEEP){
            Grafo::forcePlanaritylineSweep(&deg->primalPlanarGraph,pairsOldIdNewIds,deg->dataLinksPrimal.size()>0);
        }


        // if(deg->dataLinksPrimal.size()>0){
            for(long i=0;i<pairsOldIdNewIds.size();i++){
                for(long j=0;j<std::get<1>(pairsOldIdNewIds[i]).size();j++){
                    deg->primalPlanarGraph.links[std::get<1>(pairsOldIdNewIds[i])[j]]->originalID=std::get<0>(pairsOldIdNewIds[i]);
                }
        //         deg->dataLinksPrimal.split(std::get<0>(pairsOldIdNewIds[i]),std::get<1>(pairsOldIdNewIds[i]), std::get<2>(pairsOldIdNewIds[i]));
            }
        for(long i=0;i<deg->primalPlanarGraph.nodes.size();i++){
            Nodo* node=deg->primalGraph.getNodeByLocation(deg->primalPlanarGraph.nodes[i]->location);
            if(node==NULL){
                deg->primalPlanarGraph.nodes[i]->originalID=-1;
            }else{
                deg->primalPlanarGraph.nodes[i]->originalID=node->id;
            }
        }
        // }
        deg->isPlanarGraphConstructed=true;
    }
}
Grafo* DualExtendedGraph::getPlanarGraph(){
    if(primalGraph.isPlanar){
        return getPrimalGraph();
    }else{
        DualExtendedGraph::constructPlanarGraph(this,Grafo::PLANARITY_PLANESWEEP);
        return &primalPlanarGraph;
    }
}
void DualExtendedGraph::forcePlanarityPrimal(DualExtendedGraph* deg,int mode){
    if(!deg->primalGraph.isPlanar){
//        if(deg->getPrimalGraph()->is3d){
//            Grafo temp;
//            temp.copyGraphForcingPlanarity(deg->getPrimalGraph());
//            deg->getPrimalGraph()->reset();
//            deg->reset();
//            DualExtendedGraph::addPrimal(deg,&temp);
//            deg->getPrimalGraph()->is3d=false;
//        }
        std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
        if(mode==Grafo::PLANARITY_PLANESWEEP){
            Grafo::forcePlanarityPlaneSweep(&deg->primalGraph,Grafo::SPEED,pairsOldIdNewIds,deg->dataLinksPrimal.size()>0);
        }else if(mode==Grafo::PLANARITY_LINESWEEP){
            Grafo::forcePlanaritylineSweep(&deg->primalGraph,pairsOldIdNewIds,deg->dataLinksPrimal.size()>0);
        }


        if(deg->dataLinksPrimal.size()>0){
            for(long i=0;i<pairsOldIdNewIds.size();i++){
                deg->dataLinksPrimal.split(std::get<0>(pairsOldIdNewIds[i]),std::get<1>(pairsOldIdNewIds[i]), std::get<2>(pairsOldIdNewIds[i]));
            }
        }
        // deg->isSimplified=false;
        // if(deg->dualGraphConstructed){
        //     deg->getDualGraph()->reset();
        // }
        // deg->dualGraphConstructed=false;
        // if(deg->lineGraphConstructed){
        //     // deg->currentWeightsInLineGraph=DualExtendedGraph::METRIC;
        //     deg->getLineGraph()->reset();
        // }
        // deg->lineGraphConstructed=false;
        // if(deg->structuralGraphConstructed){
        //     deg->getStructuralGraph()->reset();
        // }
        // deg->structuralGraphConstructed=false;
        // if(deg->isPlanarGraphConstructed){
        //     deg->getPlanarGraph()->reset();
        // }
        // deg->isPlanarGraphConstructed=false;
        // if(deg->dualPlanarGraphConstructed){
        //     deg->getDualPlanarGraph()->reset();
        // }
        // deg->dualPlanarGraphConstructed=false;

        deg->softReset();

        // isPlanarGraphConstructed=true;
        // DualExtendedGraph::simplify(deg);
    }
}

void DualExtendedGraph::unPlanarizeUsingIntersectionPointsAndOriginalIdsOfLinks(DualExtendedGraph* deg,Grafo* intersectionPoints){
    // if(deg->primalGraph.isPlanar&&!deg->isPlanarGraphConstructed){
    //     deg->primalPlanarGraph.copyGraph(&deg->primalGraph);
    //     deg->isPlanarGraphConstructed=true;
    // }
    if(deg->getPrimalGraph()->bidirectional==true){
        // deg->getPrimalGraph()->is3d=true;
        deg->getPrimalGraph()->isPlanar=false; // is planar and is 3d is not the same, is 3d means that there are several nodes in the same location
//        std::cout<<"need to implement keeping the consistency of the DATA - keep track of removed links and new links";
        std::set<long> idLinksToRemove;
        for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
            if(deg->getPrimalGraph()->nodes[i]->getDegree()>2){
                Nodo* node=intersectionPoints->getNodeByLocation(deg->getPrimalGraph()->nodes[i]->location);
                if(node==NULL){
                    // std::unordered_map<std::string,std::vector<Link*> > linksByIdentifier;
                    // for(long j=0;j<deg->getPrimalGraph()->nodes[i]->links.size();j++){
                    //     linksByIdentifier[deg->getPrimalGraph()->nodes[i]->links[j]->identifier].push_back(deg->getPrimalGraph()->nodes[i]->links[j]);
                    // }
                    std::vector<std::vector<long> > idLinksPerPairs;
                    DualExtendedGraph::intersectionContinuityNegotiationPrimal(deg,deg->getPrimalGraph()->nodes[i],idLinksPerPairs);
                    int counter=0;
                    Nodo* originalNode=deg->getPrimalGraph()->nodes[i];

                    for(long k=0;k<idLinksPerPairs.size();k++){
                        if(counter!=0){
                            Point2d point;
                            point.x=(deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->A()->location.x+deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->B()->location.x)/2.0;
                            point.y=(deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->A()->location.y+deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->B()->location.y)/2.0;
                            Nodo* newNodeA=deg->getPrimalGraph()->addNode(point);
                            point.x=(deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->A()->location.x+deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->B()->location.x)/2.0;
                            point.y=(deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->A()->location.y+deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->B()->location.y)/2.0;
                            Nodo* newNodeB=deg->getPrimalGraph()->addNode(point);
                            // Nodo* newNodeB=deg->getPrimalGraph()->addNode(originalNode->location,true);
                            // for(long j=0;j<idLinksPerPairs[k].size();j++){
                                long ida=deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->A()->id;
                                long idb=deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->B()->id;
                                double weight=deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->weight/2.0;
                                idLinksToRemove.insert(deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->id);
                                if(ida==originalNode->id){
                                    ida=newNodeA->id;
                                }
                                if(idb==originalNode->id){
                                    idb=newNodeA->id;
                                }
//                                deg->getPrimalGraph()->addLink(ida,idb,weight,deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->identifier,deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->originalID);
                                deg->getPrimalGraph()->addLink(ida,idb,weight,deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->identifier);

                                ida=deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->A()->id;
                                idb=deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->B()->id;
                                weight=deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->weight/2.0;
                                idLinksToRemove.insert(deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->id);
                                if(ida==originalNode->id){
                                    ida=newNodeB->id;
                                }
                                if(idb==originalNode->id){
                                    idb=newNodeB->id;
                                }
//                                deg->getPrimalGraph()->addLink(ida,idb,weight,deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->identifier,deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->originalID);
                                deg->getPrimalGraph()->addLink(ida,idb,weight,deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->identifier);

                                ida=newNodeA->id;
                                idb=newNodeB->id;
                                weight=deg->getPrimalGraph()->links[idLinksPerPairs[k][1]]->weight/2.0+deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->weight/2.0;
                                deg->getPrimalGraph()->addLink(ida,idb,weight,deg->getPrimalGraph()->links[idLinksPerPairs[k][0]]->identifier);

                            // }
                        }
                        counter++;
                    }

                }else{
                    deg->getPrimalGraph()->nodes[i]->identifier=node->identifier;
                }
            }
        }
        deg->getPrimalGraph()->removeLinks(idLinksToRemove);
        intersectionPoints->finishedAddingNodes();
        // deg->isSimplified=false;
        deg->softReset();
        // if(deg->dualGraphConstructed){
        //     deg->getDualGraph()->reset();
        // }
        // deg->dualGraphConstructed=false;
        // if(deg->lineGraphConstructed){
        //     // deg->currentWeightsInLineGraph=DualExtendedGraph::METRIC;
        //     deg->getLineGraph()->reset();
        // }
        // deg->lineGraphConstructed=false;
        // if(deg->structuralGraphConstructed){
        //     deg->getStructuralGraph()->reset();
        // }
        // deg->structuralGraphConstructed=false;
        // if(deg->isPlanarGraphConstructed){
        //     deg->getPlanarGraph()->reset();
        // }
        // deg->isPlanarGraphConstructed=false;
        // if(deg->dualPlanarGraphConstructed){
        //     deg->getDualPlanarGraph()->reset();
        // }
        // deg->dualPlanarGraphConstructed=false;
        std::cout<<"Missing to treat the associated data"<<'\n';
    }else{
        std::cout<<"not implemented for directed graphs"<<'\n';
    }
}


void DualExtendedGraph::intersectionContinuityNegotiationPrimal(DualExtendedGraph* deg,Nodo* node,std::vector<std::vector<long> >& idLinksPerPairs){
    // DualExtendedGraph degT;
    // std::set<long> idLinks;

    if(deg->getPrimalGraph()->bidirectional){
        std::vector<bool> used;
        used.resize(node->links.size(),false);
        std::vector<long> idLinksA;
        std::vector<long> idLinksB;
        std::vector<long> angles;
        idLinksA.reserve(node->links.size()*node->links.size());
        idLinksB.reserve(node->links.size()*node->links.size());
        angles.reserve(node->links.size()*node->links.size());
        for(long i=0;i<node->links.size();i++){
            // idsLinks.insert(node->links[i]->id);
            for(long j=0;j<node->links.size();j++){
                if(i!=j){
                    Nodo* otherNodeA=node->links[i]->getOtherNode(node);
                    Nodo* otherNodeB=node->links[j]->getOtherNode(node);
                    double angle=Functions::abs(Functions::getAngle(otherNodeA->location,node->location,otherNodeB->location));
                    idLinksA.push_back(i);
                    idLinksB.push_back(j);
                    angles.push_back(angle);
                }
            }

        }
        std::vector<long> indexOfOrderedAngles=Functions::getIndexesOfOrderedValues(angles,true);
        for(long i=0;i<idLinksA.size();i++){
            long index=indexOfOrderedAngles[i];
            long idLinkA=idLinksA[index];
            long idLinkB=idLinksB[index];
            if(!used[idLinkA]&&!used[idLinkB]){
                used[idLinkA]=true;
                used[idLinkB]=true;
                std::vector<long> idsTogether;
                idsTogether.push_back(node->links[idLinkA]->id);
                idsTogether.push_back(node->links[idLinkB]->id);
                idLinksPerPairs.push_back(idsTogether);
            }
        }
    }else{
        std::cout<<"not implemented for directed graphs"<<'\n';
    }
    // Grafo G;
    // Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),G,idsLinks);
    // DualExtendedGraph::addPrimal(&degT,&G);



}

void DualExtendedGraph::cleanDuplicatedLinks(DualExtendedGraph* deg,double angularDistanceToConsiderEqual){
    std::vector<long> linksRemoved;
    Grafo::cleanDuplicatedLinks(&deg->primalGraph, angularDistanceToConsiderEqual,linksRemoved,deg->dataLinksPrimal.size()>0);
    if(deg->dataLinksPrimal.size()>0){
        deg->dataLinksPrimal.remove(linksRemoved);
    }
}

void DualExtendedGraph::simplify(DualExtendedGraph* deg){
    if(!deg->isSimplified){
        // std::cout<<"a"<<'\n';
        Grafo simplified;
        simplified.copyProperties(&deg->primalGraph);
        std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        Grafo::removeSuperfluousNodes(&deg->primalGraph, &simplified, pairsOldNew,20.0,deg->dataLinksPrimal.size()>0);
        // std::cout<<"b"<<'\n';

        if(deg->dataLinksPrimal.size()>0){
            for (long i=0;i<pairsOldNew.size(); i++) {
                deg->dataLinksPrimal.combine(pairsOldNew[i].first, pairsOldNew[i].second);
            }
        }
        // std::cout<<"c"<<'\n';
        // if(deg->dataLinksPrimal.tags.size()>0){
        //     std::vector<std::unordered_map<std::string,std::string> > tags;
        //     tags.resize(simplified.links.size());
        //     for(long i=0;i<simplified.links.size();i++){
        //       tags.push_back(deg->dataLinksPrimal.tags[i]);//just pushing some random data in
        //     }
        //     for (long i=0;i<pairsOldNew.size(); i++) {
        //         std::swap(tags[pairsOldNew[i].second],deg->dataLinksPrimal.tags[pairsOldNew[i].first[0]]);
        //         // tags.push_back(deg->dataLinksPrimal.tags[pairsOldNew[i].first[0]]);
        //     }
        //     std::swap(deg->dataLinksPrimal.tags,tags);
        // }
        deg->primalGraph.reset();
        deg->primalGraph.copyGraph(&simplified);
        deg->isSimplified=true;
        // std::cout<<"d"<<'\n';




//        std::cout<<"Simplified graph created"<<'\n';

    }
}
void DualExtendedGraph::simplify(DualExtendedGraph* deg,double angle){
    if(!deg->isSimplified){
        Grafo simplified;
        simplified.copyProperties(&deg->primalGraph);
        std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        Grafo::removeSuperfluousNodes(&deg->primalGraph, &simplified, pairsOldNew,angle,deg->dataLinksPrimal.size()>0);


        if(deg->dataLinksPrimal.size()>0){
            for (long i=0;i<pairsOldNew.size(); i++) {
                deg->dataLinksPrimal.combine(pairsOldNew[i].first, pairsOldNew[i].second);
            }
        }
        deg->primalGraph.reset();
        deg->primalGraph.copyGraph(&simplified);
        deg->isSimplified=true;





//        std::cout<<"Simplified graph created"<<'\n';

    }
}
void DualExtendedGraph::buildStructuralGraph(DualExtendedGraph* deg){

    if(!deg->structuralGraphConstructed){

        deg->structuralGraph.copyProperties(&deg->primalGraph);
        std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        Grafo::removeNonStructuralNodes(&deg->primalGraph, &deg->structuralGraph, pairsOldNew,deg->dataLinksPrimal.size()>0||deg->keepTrackDifferencesBetweenPrimalAndStructural);

        deg->structuralGraphConstructed=true;
        std::unordered_map<long,long> idsPrimal;
        std::unordered_map<long,long> idsStructural;

        // std::unordered_map<long,long> idsPrimalByOriginalId;

        for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
            idsPrimal[deg->getPrimalGraph()->links[i]->originalID]=deg->getPrimalGraph()->links[i]->id;
        }
        for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
            idsStructural[deg->getStructuralGraph()->links[i]->originalID]=deg->getStructuralGraph()->links[i]->id;
        }
        deg->idsLinksPrimalByIdsLinksStructural.resize(deg->getStructuralGraph()->links.size(),std::vector<long>());
        for(long i=0;i<pairsOldNew.size();i++){
            for(long j=0;j<pairsOldNew[i].first.size();j++){
//                std::cout<<i<<" "<<j<<" : "<<pairsOldNew[i].second<<" -> "<<idsStructural[pairsOldNew[i].second]<<" , "<<pairsOldNew[i].first[j]<<" -> "<<idsPrimal[pairsOldNew[i].first[j]]<<" . "<<pairsOldNew.size()<<" "<<deg->getStructuralGraph()->links.size()<<'\n';
                deg->idsLinksPrimalByIdsLinksStructural[idsStructural[pairsOldNew[i].second]].push_back(idsPrimal[pairsOldNew[i].first[j]]);
            }
        }
        // for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        //     if(deg->idsLinksPrimalByIdsLinksStructural[i].size()==0){
        //         deg->idsLinksPrimalByIdsLinksStructural[i].push_back(idsPrimal[deg->getStructuralGraph()->links[i]->originalID]);
        //     }
        //     //idsStructural[deg->getStructuralGraph()->links[i]->originalID]=deg->getStructuralGraph()->links[i]->id;
        // }
        std::cout<<"Structural graph created"<<'\n';
    }
}
// void DualExtendedGraph::buildStructuralGraph(DualExtendedGraph* deg,bool directed){

//     if(!deg->structuralGraphConstructed){

//         deg->structuralGraph.copyProperties(&deg->primalGraph);
//         std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
//         // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//         Grafo::removeNonStructuralNodes(&deg->primalGraph, &deg->structuralGraph, pairsOldNew,deg->dataLinksPrimal.size()>0||deg->keepTrackDifferencesBetweenPrimalAndStructural);
//         deg->structuralGraphConstructed=true;

//         std::cout<<"Structural graph created"<<'\n';
//     }
// }

void DualExtendedGraph::buildBidirectionalGraph(DualExtendedGraph* deg){
    deg->primalBidirectionalGraph.copyProperties(deg->primalGraph);
    deg->primalGraph.bidirectional=true;
    deg->primalBidirectionalGraph.copyGraph(&deg->primalGraph);
}


void DualExtendedGraph::createDual(DualExtendedGraph* deg,Grafo* originalGraph,Grafo* dual){

    if(!deg->dualGraphConstructed){
        std::vector<Grafo> components;


        // simplify(deg);
        std::vector<long> idAs;
        std::vector<long> idBs;
        std::vector<double> weights;
        idAs.resize(originalGraph->links.size());
        idBs.resize(originalGraph->links.size());
        weights.resize(originalGraph->links.size());
        Grafo::getComponents(originalGraph, components, 0);
        long accumNumberLinks=0;
        for(long i=0;i<components.size();i++){

            Grafo dualTemp;
            dualTemp.setAsDualGraph();
            Grafo::constructDual(&components[i], &dualTemp);
            accumNumberLinks+=dualTemp.links.size();
            if(i==0){

                // deg->primalGraph=Grafo();
                // deg->getPrimalGraph()->reset();
                // deg->primalGraph.bidirectional=true;
                // deg->dualGraph=Grafo();
                dual->setAsDualGraph();

                // deg->dualGraph.links.resize(deg->getPrimalGraph()->links.size);
                // for(long j=0;j<components[i].nodes.size();j++){
                //     deg->primalGraph.addNode(components[i].nodes[j]->originalID,components[i].nodes[j]->location.x,components[i].nodes[j]->location.y);
                // }

                // for(long j=0;j<components[i].links.size();j++){
                //     long idA=components[i].links[j]->a->id;
                //     long idB=components[i].links[j]->b->id;
                //     double weight=components[i].links[j]->weight;
                //     deg->primalGraph.addLink(idA,idB,weight);
                // }
                for(long j=0;j<dualTemp.nodes.size();j++){
                    dual->addNode(dualTemp.nodes[j]->location,dualTemp.nodes[j]->mass);
                }
                for(long j=0;j<dualTemp.links.size();j++){
                    Nodo* a=originalGraph->getNodeByLocation(components[i].links[j]->A()->location);
                    Nodo* b=originalGraph->getNodeByLocation(components[i].links[j]->B()->location);
                    long idInPrimal=-1;
                    for(long k=0;k<a->links.size();k++){
                        if(a->links[k]->getOtherNode(a)==b){
                            idInPrimal=a->links[k]->id;
                        }
                    }

                    long idA=dualTemp.links[j]->A()->id;
                    long idB=dualTemp.links[j]->B()->id;

                    double weight=dualTemp.links[j]->weight;
                    idAs[idInPrimal]=idA;
                    idBs[idInPrimal]=idB;
                    weights[idInPrimal]=weight;
                    // long idLink=deg->dualGraph.addLink(idA, idB, weight);


                }
            }else{


                // deg->primalGraph.nodes.reserve(deg->primalGraph.nodes.size()+components[i].nodes.size());


                // for(long j=0;j<components[i].links.size();j++){

                //     Nodo* nodeA=deg->primalGraph.addNode(components[i].links[j]->a->originalID,components[i].links[j]->a->location.x,components[i].links[j]->a->location.y);
                //     Nodo* nodeB=deg->primalGraph.addNode(components[i].links[j]->b->originalID,components[i].links[j]->b->location.x,components[i].links[j]->b->location.y);


                //     long idA=nodeA->id;
                //     long idB=nodeB->id;
                //     double weight=components[i].links[j]->weight;
                //     deg->primalGraph.addLink(idA,idB,weight);
                // }
                // std::cout<<"links dualTemp "<<dualTemp.links.size();
                // std::cout<<" links dual "<<accumNumberLinks<<'\n';

                if(dualTemp.nodes.size()>0){
                    dual->nodes[0]->mass+=dualTemp.nodes[0]->mass;

                    for(long j=0;j<dualTemp.links.size();j++){
                        long idA;
                        if(dualTemp.links[j]->A()->id==0){
                            idA=0;
                        }else{
                             Nodo* nodeA=dual->addNode(dualTemp.links[j]->A()->location,dualTemp.links[j]->A()->mass);
                            idA=nodeA->id;
                        }

                        long idB;
                        if(dualTemp.links[j]->B()->id==0){
                            idB=0;
                        }else{
                            Nodo* nodeB=dual->addNode(dualTemp.links[j]->B()->location,dualTemp.links[j]->B()->mass);
                            idB=nodeB->id;
                        }

                        double weight=dualTemp.links[j]->weight;
                        Nodo* a=originalGraph->getNodeByLocation(components[i].links[j]->A()->location);
                        Nodo* b=originalGraph->getNodeByLocation(components[i].links[j]->B()->location);
                        long idInPrimal=-1;
                        for(long k=0;k<a->links.size();k++){
                            if(a->links[k]->getOtherNode(a)==b){
                                idInPrimal=a->links[k]->id;
                            }
                        }
                        idAs[idInPrimal]=idA;
                        idBs[idInPrimal]=idB;
                        weights[idInPrimal]=weight;
                        // deg->dualGraph.addLink(idA, idB, weight);
                    }
                }
            }
        }
        for(long i=0;i<idAs.size();i++){
          dual->addLink(idAs[i],idBs[i],weights[i]);
        }
    }

    // std::cout<<"final number links dual "<<dual->links.size()<<'\n';
    if(originalGraph==deg->getPrimalGraph()){
        deg->dualGraphConstructed=true;
    }
    if(originalGraph==deg->getPlanarGraph()){
        deg->dualPlanarGraphConstructed=true;
    }
    // if(deg->lineGraphConstructed){
    //     deg->getLineGraph()->reset();
    //     deg->lineGraphConstructed=false;
    // }

}

void DualExtendedGraph::createLineGraph(DualExtendedGraph* deg){
    if(!deg->lineGraphConstructed){
        // simplify(deg);
        // std::cout<<"creating lineGraph"<<'\n';
        deg->lineGraph.reset();
        deg->currentWeightsInLineGraph=DualExtendedGraph::METRIC;
        Grafo::constructLineGraph(&deg->primalGraph, &deg->lineGraph);
        deg->lineGraphConstructed=true;
    }
}


void DualExtendedGraph::metricPercolation(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes){

        // buildStructuralGraph(deg);
//        Grafo percolated;
//        Grafo::networkPercolation(deg->getStructuralGraph(),&percolated, threshold);
        long maxColor;
        std::vector<long> colorsT;
        // std::vector<double> sizesT;
        Grafo::getLinkColorsFromNetworkPercolation(deg->getStructuralGraph(), threshold, colorsT, sizes, maxColor);
        colors.clear();
        colors.resize(deg->getPrimalGraph()->links.size());

            for(long i=0;i<colorsT.size();i++){
                if(!deg->primalIsStructuralGraph){
                    for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){

                            colors[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=colorsT[i];

                    }
                }else{
                    colors[i]=colorsT[i];
                }
            }



}
void DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes){

    // buildStructuralGraph(deg);
    //        Grafo percolated;
    //        Grafo::networkPercolation(deg->getStructuralGraph(),&percolated, threshold);
    long maxColor;
    std::vector<long> colorsT;
    // std::vector<double> sizesT;
    Grafo::getLinkColorsFromNetworkPercolation(deg->getStructuralGraph(), threshold, colorsT, sizes, maxColor);
    colors.clear();
    colors.resize(deg->getPrimalGraph()->links.size());

    for(long i=0;i<colorsT.size();i++){
        if(!deg->primalIsStructuralGraph){
            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){

                colors[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=colorsT[i];

            }
        }else{
            colors[i]=colorsT[i];
        }
    }
    std::vector<bool> nodeAlreadyCounted;
    nodeAlreadyCounted.resize(deg->getPrimalGraph()->nodes.size(),false);
    long n=sizes.size();
    sizes.clear();
    sizes.resize(n,0);
    for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
        if(colors[i]!=-1){
            if(!nodeAlreadyCounted[deg->getPrimalGraph()->links[i]->A()->id]){
                nodeAlreadyCounted[deg->getPrimalGraph()->links[i]->A()->id]=true;
                sizes[colors[i]]+=deg->getPrimalGraph()->links[i]->A()->mass;
            }
            if(!nodeAlreadyCounted[deg->getPrimalGraph()->links[i]->B()->id]){
                nodeAlreadyCounted[deg->getPrimalGraph()->links[i]->B()->id]=true;
                sizes[colors[i]]+=deg->getPrimalGraph()->links[i]->B()->mass;
            }
        }
    }



}
void DualExtendedGraph::setDistanceDual_HuMoments(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    std::vector<std::vector<double> > HM;
    HM.resize(dual->nodes.size(),std::vector<double> ());
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';
            if(HM[dual->links[i]->A()->id].size()==0){
                Grafo A;
                std::set<long> idLinksA;
                for(long j=0;j<dual->links[i]->A()->links.size();j++){
                    idLinksA.insert(dual->links[i]->A()->links[j]->id);
                }
                Grafo::inducedSubgraphFromLinks(primal,&A,idLinksA);
                std::vector<double> HuA=GeometryGraph::calculateHuMoments(&A);
                HM[dual->links[i]->A()->id]=HuA;
            }
            if(HM[dual->links[i]->B()->id].size()==0){
                Grafo B;
                std::set<long> idLinksB;
                for(long j=0;j<dual->links[i]->B()->links.size();j++){
                    idLinksB.insert(dual->links[i]->B()->links[j]->id);
                }
                Grafo::inducedSubgraphFromLinks(primal,&B,idLinksB);
                std::vector<double> HuB=GeometryGraph::calculateHuMoments(&B);
                HM[dual->links[i]->B()->id]=HuB;
            }
            double distance=0;
            for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                distance+=pow(HM[dual->links[i]->A()->id][j]-HM[dual->links[i]->B()->id][j],2.0);
            }
            distance=sqrt(distance);
            dual->links[i]->weight=log(distance+1);
        }else{
            dual->links[i]->weight=0;
        }
    }
    double maxWeight=-INFINITY;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->weight>maxWeight){
            maxWeight=dual->links[i]->weight;
        }
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

        }else{
            dual->links[i]->weight=maxWeight;
        }
    }
}
void DualExtendedGraph::setDistanceDual_difArea(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<std::vector<double> > HM;
    // HM.resize(dual->nodes.size(),std::vector<double> ());
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';

            double distance=0;
            // for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                distance=Functions::abs(dual->links[i]->A()->mass-dual->links[i]->B()->mass);
            // }
            // distance=sqrt(distance);
            dual->links[i]->weight=log(distance+1);
        }else{
            dual->links[i]->weight=0;
        }
    }
    double maxWeight=-INFINITY;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->weight>maxWeight){
            maxWeight=dual->links[i]->weight;
        }
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

        }else{
            dual->links[i]->weight=maxWeight;
        }
    }
}
void DualExtendedGraph::setDistanceDual_avArea(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<std::vector<double> > HM;
    // HM.resize(dual->nodes.size(),std::vector<double> ());
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';

            double distance=0;
            // for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                distance=(dual->links[i]->A()->mass+dual->links[i]->B()->mass)/2.0;
            // }
            // distance=sqrt(distance);
            dual->links[i]->weight=log(distance+1);
                // dual->links[i]->weight=(distance);
        }else{
            dual->links[i]->weight=0;
        }
    }
    double maxWeight=-INFINITY;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->weight>maxWeight){
            maxWeight=dual->links[i]->weight;
        }
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

        }else{
            dual->links[i]->weight=maxWeight;
        }
    }
}

void DualExtendedGraph::setDistanceDual_minArea(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<std::vector<double> > HM;
    // HM.resize(dual->nodes.size(),std::vector<double> ());
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';

            double distance=0;
            // for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                distance=Functions::min(dual->links[i]->A()->mass,dual->links[i]->B()->mass);
            // }
            // distance=sqrt(distance);
            dual->links[i]->weight=log(distance+1);
                // dual->links[i]->weight=(distance);
        }else{
            dual->links[i]->weight=0;
        }
    }
    double maxWeight=-INFINITY;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->weight>maxWeight){
            maxWeight=dual->links[i]->weight;
        }
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

        }else{
            dual->links[i]->weight=maxWeight;
        }
    }
}

void DualExtendedGraph::setDistanceDual_avNeighborhoodArea(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<std::vector<double> > HM;
    // HM.resize(dual->nodes.size(),std::vector<double> ());
    std::vector<double> neighArea;
    neighArea.resize(dual->nodes.size(),0);
    for(long i=0;i<dual->nodes.size();i++){
        double area=dual->nodes[i]->mass;
        double count=1;
        for(long j=0;j<dual->nodes[i]->links.size();j++){
            area+=dual->nodes[i]->links[j]->getOtherNode(dual->nodes[i])->mass;
            count++;
        }
        neighArea[i]=area/count;
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';

            double distance=0;
            // for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                distance=(neighArea[dual->links[i]->A()->id]+neighArea[dual->links[i]->B()->id])/2.0;
            // }
            // distance=sqrt(distance);
            dual->links[i]->weight=log(distance+1);
                // dual->links[i]->weight=(distance);
        }else{
            dual->links[i]->weight=0;
        }
    }
    double maxWeight=-INFINITY;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->weight>maxWeight){
            maxWeight=dual->links[i]->weight;
        }
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

        }else{
            dual->links[i]->weight=maxWeight;
        }
    }
}


void DualExtendedGraph::setDistancePrimal_minLengthNeighbours(DualExtendedGraph* deg){
    // Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<std::vector<double> > HM;
    // HM.resize(dual->nodes.size(),std::vector<double> ());
    // std::vector<double> neighArea;
    // neighArea.resize(dual->nodes.size(),0);
    // for(long i=0;i<dual->nodes.size();i++){
    //     double area=dual->nodes[i]->mass;
    //     double count=1;
    //     for(long j=0;j<dual->nodes[i]->links.size();j++){
    //         area+=dual->nodes[i]->links[j]->getOtherNode(dual->nodes[i])->mass;
    //         count++;
    //     }
    //     neighArea[i]=area/count;
    // }
    std::vector<double> newWeights;
    newWeights.resize(primal->links.size(),0);
    for(long i=0;i<primal->links.size();i++){
        // if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            // std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';
            double min=-INFINITY;
            min=primal->links[i]->weight;
            for(long j=0;j<primal->links[i]->A()->links.size();j++){
                if(primal->links[i]->A()->links[j]->weight<min){
                    min=primal->links[i]->A()->links[j]->weight;
                }
            }
            for(long j=0;j<primal->links[i]->B()->links.size();j++){
                if(primal->links[i]->B()->links[j]->weight<min){
                    min=primal->links[i]->B()->links[j]->weight;
                }
            }
            newWeights[i]=min;
            // double distance=0;
            // for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                // distance=(neighArea[dual->links[i]->A()->id]+neighArea[dual->links[i]->B()->id])/2.0;
            // }
            // distance=sqrt(distance);
            // dual->links[i]->weight=log(distance+1);
                // dual->links[i]->weight=(distance);
        // }else{
        //     dual->links[i]->weight=0;
        // }
    }
    for(long i=0;i<primal->links.size();i++){
        primal->links[i]->weight=newWeights[i];
    }
    // deg->softReset();
    if(deg->structuralGraphConstructed){

        deg->getStructuralGraph()->reset();
         deg->structuralGraphConstructed=false;
    }
    // double maxWeight=-INFINITY;
    // for(long i=0;i<dual->links.size();i++){
    //     if(dual->links[i]->weight>maxWeight){
    //         maxWeight=dual->links[i]->weight;
    //     }
    // }
    // for(long i=0;i<dual->links.size();i++){
    //     if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

    //     }else{
    //         dual->links[i]->weight=maxWeight;
    //     }
    // }
}



void DualExtendedGraph::setDistanceDual_difNeighborhoodArea(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<std::vector<double> > HM;
    // HM.resize(dual->nodes.size(),std::vector<double> ());
    std::vector<double> neighArea;
    neighArea.resize(dual->nodes.size(),0);
    for(long i=0;i<dual->nodes.size();i++){
        double area=dual->nodes[i]->mass;
        double count=1;
        for(long j=0;j<dual->nodes[i]->links.size();j++){
            area+=dual->nodes[i]->links[j]->getOtherNode(dual->nodes[i])->mass;
            count++;
        }
        neighArea[i]=area/count;
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){
            std::cout<<"Progress "<<i<<" / "<<dual->links.size()<<'\n';

            double distance=0;
            // for(long j=0;j<HM[dual->links[i]->A()->id].size();j++){
                distance=Functions::abs(neighArea[dual->links[i]->A()->id]-neighArea[dual->links[i]->B()->id]);
            // }
            // distance=sqrt(distance);
            dual->links[i]->weight=log(distance+1);
                // dual->links[i]->weight=(distance);
        }else{
            dual->links[i]->weight=0;
        }
    }
    double maxWeight=-INFINITY;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->weight>maxWeight){
            maxWeight=dual->links[i]->weight;
        }
    }
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id!=0&&dual->links[i]->B()->id!=0){

        }else{
            dual->links[i]->weight=maxWeight;
        }
    }
}


void DualExtendedGraph::dualPercolation(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes){

        // buildStructuralGraph(deg);
//        Grafo percolated;
//        Grafo::networkPercolation(deg->getStructuralGraph(),&percolated, threshold);
        long maxColor;
        // std::vector<long> colorsT;
        // std::vector<double> sizesT;
        Grafo::getLinkColorsFromNetworkPercolation(deg->getDualGraph(), threshold, colors, sizes, maxColor);
        // colors.clear();
        // colors.resize(deg->getPrimalGraph()->links.size());

        //     for(long i=0;i<colorsT.size();i++){
        //         if(!deg->primalIsStructuralGraph){
        //             for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){

        //                     colors[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=colorsT[i];

        //             }
        //         }else{
        //             colors[i]=colorsT[i];
        //         }
        //     }



}


void DualExtendedGraph::calculateCompleteMetricPercolation(DualExtendedGraph* deg,std::string folderNameOut){
    std::vector<long> colors;
    std::vector<double> sizes;
    std::vector<double> thresholds;
//    thresholds.push_back(150);
//    thresholds.push_back(300);
//    thresholds.push_back(600);
//    thresholds.push_back(900);
//    thresholds.push_back(1200);
//    thresholds.push_back(1600);
//    thresholds.push_back(2000);
//    thresholds.push_back(2500);
//    thresholds.push_back(3000);
//    thresholds.push_back(4000);
//    thresholds.push_back(5000);
//    thresholds.push_back(800);
//    thresholds.push_back(1400);
//    thresholds.push_back(500);
//    thresholds.push_back(1500);
//    thresholds.push_back(700);
//    thresholds.push_back(1300);
//    thresholds.push_back(400);
//    thresholds.push_back(200);
//    thresholds.push_back(1100);
//    thresholds.push_back(100);
//    thresholds.push_back(1000);
//    thresholds.push_back(1800);
//    thresholds.push_back(1100);
//    thresholds.push_back(1700);
//    thresholds.push_back(1900);
//    thresholds.push_back(2100);
//    thresholds.push_back(2200);
//    thresholds.push_back(2300);
//    thresholds.push_back(2400);
//    for(long t=2600;t<3000;t+=100){
//        thresholds.push_back(t);
//    }
//    for(long t=3100;t<4000;t+=100){
//        thresholds.push_back(t);
//    }
    for(long t=100;t<15000;t+=100){
        thresholds.push_back(t);
    }
    std::vector<double> probabilities;
    std::vector<double> weights;
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        weights.push_back(deg->getStructuralGraph()->links[i]->weight);
    }
    weights=Functions::orderValues(weights, true);
    long j=0;
    for(long i=0;i<weights.size()-1;i++){
        if(weights[i]<=thresholds[j]&&weights[i+1]>thresholds[j]){
            probabilities.push_back(double(i)/double(weights.size()));
            j++;
        }
    }
    if(j<thresholds.size()-1){
        for(long i=j;i<thresholds.size();i++){
            probabilities.push_back(1.0);
        }
    }

//    long minClusterId=0;

    std::vector<long> colorsNodes;
    std::vector<std::string> largestSizes;
    for(long i=0;i<thresholds.size();i++){
        DualExtendedGraph::metricPercolation(deg, thresholds[i], colors, sizes);
//        for(long j=0;j<colors.size();j++){
//
//            if(colors[j]!=-1){
//                colors[j]=colors[j]+minClusterId;
//            }
//        }


//        std::stringstream ss;
//        ss<<folderNameOut<<"colorsLinks_"<<thresholds[i]<<".txt";
//        TextFile::writeToFile(ss.str(), colors, false);
//
//        Grafo::transformColorsLinksIntoColorsNodes(deg->getStructuralGraph(), colors, colorsNodes);
//        ss.str("");
//        ss<<folderNameOut<<"colorsNodes_"<<thresholds[i]<<".txt";
//        TextFile::writeToFile(ss.str(), colorsNodes, false);
//        ss.str("");
//        ss<<folderNameOut<<"sizes_"<<thresholds[i]<<".txt";
//        TextFile::writeToFile(ss.str(), sizes, false);


        std::vector<double> orderedSizes;
        orderedSizes=Functions::orderValues(sizes, false);
        std::stringstream ssB;

        if(orderedSizes.size()>0){
            ssB<<thresholds[i]<<" "<<probabilities[i]<<" "<<orderedSizes[0];
            largestSizes.push_back(ssB.str());
        }

    }
    std::stringstream ss;
    ss<<folderNameOut<<"sizeLargestCluster"<<".txt";
    TextFile::writeToFile(ss.str(), largestSizes, false);

}

void DualExtendedGraph::calculateCompleteWeightStructuralGraphPercolation(DualExtendedGraph* deg,std::string folderNameOut){
    std::vector<long> colors;
    std::vector<double> sizes;
    std::vector<double> thresholds;

//    double max=-INFINITY;
//    double min=INFINITY;
    std::vector<double> weights;

    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        weights.push_back(deg->getStructuralGraph()->links[i]->weight);
    }
    weights=Functions::orderValues(weights, true);
    double current=0;
    std::vector<double> probabilities;

    for(long i=0;i<weights.size();i++){
        if((double)i/(double)(weights.size())>=current&&(double)(i-1)/(double)(weights.size())<current){
            current++;
            thresholds.push_back(weights[i]);
            probabilities.push_back((double)i/(double)(weights.size()));
        }
    }


//    for(double t=min;t<max;t+=(max-min)/50.0){
//        thresholds.push_back(t);
//    }
    std::stringstream ssT;
    ssT<<folderNameOut<<"thresholds"<<".txt";
    TextFile::writeToFile(ssT.str(), thresholds, false);
    ssT.str("");
    ssT<<folderNameOut<<"probabilities"<<".txt";
    TextFile::writeToFile(ssT.str(), probabilities, false);
    std::vector<long> colorsNodes;
    for(long i=0;i<thresholds.size();i++){
        DualExtendedGraph::metricPercolation(deg, thresholds[i], colors, sizes);
        std::stringstream ss;
        ss<<folderNameOut<<"colorsLinks_"<<thresholds[i]<<".txt";
        TextFile::writeToFile(ss.str(), colors, false);

        Grafo::transformColorsLinksIntoColorsNodes(deg->getStructuralGraph(), colors, colorsNodes);
        ss.str("");
        ss<<folderNameOut<<"colorsNodes_"<<thresholds[i]<<".txt";
        TextFile::writeToFile(ss.str(), colorsNodes, false);
        ss.str("");
        ss<<folderNameOut<<"sizes_"<<thresholds[i]<<".txt";
        TextFile::writeToFile(ss.str(), sizes, false);
    }

}

void DualExtendedGraph::angularPercolation(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes){

//    DualExtendedGraph::simplify(deg);
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    DualExtendedGraph::createLineGraph(deg);
//    Grafo percolated;
    DualExtendedGraph::setAngularWeightsLineGraph(deg);
//    Grafo::networkPercolation(deg->getLineGraph(),&percolated, threshold);
    long maxColor;

    Grafo::getLinkColorsFromNetworkPercolation(deg->getLineGraph(),threshold, colors, sizes, maxColor);
    std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
    DualExtendedGraph::setMetricWeightsLineGraph(deg);

    // std::vector<double> sizes_fromLengths;
    // std::vector<double> sizes_fromLengths_;
    // sizes_fromLengths.resize(sizes.size(),0);
    // sizes_fromLengths_.resize(sizes.size(),0);
    // for(long i=0;i<colors.size();i++){
    //     if(colors[i]!=-1){
    //         sizes_fromLengths_[colors[i]]+=deg->getLineGraph()->links[i]->weight;
    //     }
    // }
    // for(long i=0;i<sizes_fromLengths_.size();i++){
    //     sizes_fromLengths[i]=sizes_fromLengths_[i]*1000;
    // }
    // std::swap(sizes,sizes_fromLengths);



//    double massGiantCluster=sizes[indexesOrderClusters[0]];
//    std::cout<<"Mass giant cluster "<<massGiantCluster<<'\n';

//    double squaredSum=0.0;
//    double sum=0.0;
//    for(long j=0;j<sizes.size();j++){
//        squaredSum+=pow(sizes[j],2.0);
//        sum+=sizes[j];
//    }
//    if(angle>anglePhaseTransition){
//        squaredSum-=pow(sizes[indexesOrderClusters[0]],2.0);
//        sum-=sizes[indexesOrderClusters[0]];
//    }
//    if(squaredSum!=0){
//        averageFiniteMassClusters.push_back(squaredSum/sum);
//    }else{
//        averageFiniteMassClusters.push_back(0.0);
//    }

}

void DualExtendedGraph::setAngularWeightsLineGraph(DualExtendedGraph* deg){
    if(deg->currentWeightsInLineGraph!=DualExtendedGraph::ANGULAR){
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        DualExtendedGraph::createLineGraph(deg);
        for(long i=0;i<deg->lineGraph.links.size();i++){
            Link* linkA=deg->primalGraph.links[deg->lineGraph.links[i]->A()->id];
            Link* linkB=deg->primalGraph.links[deg->lineGraph.links[i]->B()->id];
            Nodo* commonNode=deg->primalGraph.commonNode(linkA,linkB);
            Nodo* otherNodeA=linkA->getOtherNode(commonNode);
            Nodo* otherNodeB=linkB->getOtherNode(commonNode);
            double angle=Functions::abs(Functions::getAngle(otherNodeA->location, commonNode->location, otherNodeB->location));
            deg->lineGraph.links[i]->weight=angle;
        }
        deg->currentWeightsInLineGraph=DualExtendedGraph::ANGULAR;
    }
}

void DualExtendedGraph::setMetricWeightsLineGraph(DualExtendedGraph* deg){
    if(deg->currentWeightsInLineGraph!=DualExtendedGraph::METRIC){
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        DualExtendedGraph::createLineGraph(deg);
        for(long i=0;i<deg->lineGraph.links.size();i++){
            Link* linkA=deg->primalGraph.links[deg->lineGraph.links[i]->A()->id];
            Link* linkB=deg->primalGraph.links[deg->lineGraph.links[i]->B()->id];
            // Nodo* commonNode=deg->primalGraph.commonNode(linkA,linkB);
            // Nodo* otherNodeA=linkA->getOtherNode(commonNode);
            // Nodo* otherNodeB=linkB->getOtherNode(commonNode);
            double weight=(linkA->weight+linkB->weight)/2.0;
            deg->lineGraph.links[i]->weight=weight;
        }
        deg->currentWeightsInLineGraph=DualExtendedGraph::METRIC;
    }
}

std::vector<double> DualExtendedGraph::getAngularWeightsLineGraph(DualExtendedGraph* deg){
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    DualExtendedGraph::createLineGraph(deg);
    std::vector<double> angularWeights;
    angularWeights.reserve(deg->lineGraph.links.size());
    for(long i=0;i<deg->lineGraph.links.size();i++){
        Link* linkA=deg->primalGraph.links[deg->lineGraph.links[i]->A()->id];
        Link* linkB=deg->primalGraph.links[deg->lineGraph.links[i]->B()->id];
        Nodo* commonNode=deg->primalGraph.commonNode(linkA,linkB);
        Nodo* otherNodeA=linkA->getOtherNode(commonNode);
        Nodo* otherNodeB=linkB->getOtherNode(commonNode);
        double angle=Functions::abs(Functions::getAngle(otherNodeA->location, commonNode->location, otherNodeB->location));
        angularWeights.push_back(angle);

    }
    return angularWeights;

}


//void DualExtendedGraph::setMetricWeightsLineGraph(DualExtendedGraph* deg){
//    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//    DualExtendedGraph::createLineGraph(deg);
//    for(long i=0;i<deg->lineGraph.links.size();i++){
//        Link* linkA=deg->primalGraph.links[deg->lineGraph.links[i]->A()->id];
//        Link* linkB=deg->primalGraph.links[deg->lineGraph.links[i]->B()->id];
//        deg->lineGraph.links[i]->weight=linkA->weight/2.0+linkB->weight/2.0;
//    }
//}

void DualExtendedGraph::setWeightsLineGraphFromData(DualExtendedGraph* deg,std::string weightType){
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    DualExtendedGraph::createLineGraph(deg);
    std::vector<double> weights=deg->dataLinksPrimal.getData(deg->primalGraph.links, weightType);
    for(long i=0;i<deg->lineGraph.links.size();i++){
        Link* linkA=deg->primalGraph.links[deg->lineGraph.links[i]->A()->id];
        Link* linkB=deg->primalGraph.links[deg->lineGraph.links[i]->B()->id];
        deg->lineGraph.links[i]->weight=weights[linkA->id]/2.0+weights[linkB->id]/2.0;
    }
}


void DualExtendedGraph::calculateCompleteAngularPercolation(DualExtendedGraph* deg,double definition,CriticalExponentsPercolation &cep,bool calculatePhaseTransition){
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    double anglePhaseTransition=0;

    double probabilityPhaseTransition=0;
    if(calculatePhaseTransition){
        DualExtendedGraph::createLineGraph(deg);
        std::pair<double,double> phaseTransition=DualExtendedGraph::detectPhaseTransitionAngularPercolation(deg,.00001);
        anglePhaseTransition=phaseTransition.first;

        probabilityPhaseTransition=phaseTransition.second;
        cep.anglePhaseTransition=anglePhaseTransition;
        cep.probabilityPhaseTransition=probabilityPhaseTransition;
    }else{
        anglePhaseTransition=cep.anglePhaseTransition;

        probabilityPhaseTransition=cep.probabilityPhaseTransition;
    }

    std::vector<double> vectorOfWeights=getAngularWeightsLineGraph(deg);
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);

    std::vector<double> massesGC;
    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    std::vector<double> acceptedProbabilities;
    std::vector<double> angles;
    //    std::vector<double> ps;



    double increaseProbability=1/definition;
    //    for(double i=0.0;i<probabilityPhaseTransition-.075;i+=increaseProbability){
    //        probabilities.push_back(i);
    //    }
    //    double increaseProbabilityB=increaseProbability/10.0;
    //    for(double i=probabilityPhaseTransition-.075;i<probabilityPhaseTransition;i+=increaseProbabilityB){
    //        probabilities.push_back(i);
    //    }
    ////    probabilities.push_back(probabilityPhaseTransition);
    //    for(double i=probabilityPhaseTransition;i<probabilityPhaseTransition+.075;i+=increaseProbabilityB){
    //        probabilities.push_back(i);
    //    }
    //    for(double i=probabilityPhaseTransition+.075;i<=1.0;i+=increaseProbability){
    //        probabilities.push_back(i);
    //    }

    for(double i=0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    long j=0;
    double currentProbability=probabilities[j];
    //    bool setDistance=true;



    for(long i=0;i<orderedVectorOfWeights.size();i++){
        //    long i=0;
        //    while(i<weights.size()){

        if((double)(i)/(double)orderedVectorOfWeights.size()>currentProbability&&(double)(i-1)/(double)orderedVectorOfWeights.size()<=currentProbability){
            j++;
            currentProbability=probabilities[j];
            angles.push_back(orderedVectorOfWeights[i]);
            acceptedProbabilities.push_back((double)(i)/(double)orderedVectorOfWeights.size());
            //            ps.push_back(currentProbability);

        }
    }
    angles.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    acceptedProbabilities.push_back(1);

    std::vector<long> colors;
    std::vector<double> sizes;
    massesGC.reserve(angles.size());
    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getLineGraph()->links.size());
    for(long i=0;i<angles.size();i++){
        std::cout<<"Current angle="<<angles[i]<<'\n';
        double angle=angles[i];
        //        double p=ps[i];
        double massGiantCluster=0;

        DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);
        if(sizes.size()>0){

          std::unordered_map<long,double> statesSystem;

//             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }
           if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }






            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);

            double squaredSum=0.0;
            double sum=0.0;
            // double entropy=0.0;
            for(long j=0;j<sizes.size();j++){
                squaredSum+=sizes[j]*sizes[j];
                sum+=sizes[j];
                // double probability=(double)sizes[j]/totalSize;
                // entropy-=probability*log(probability);
            }
            std::cout<<"entropy "<<entropy<<'\n';
            cep.entropies.push_back(entropy);
            if(angle>anglePhaseTransition){
                squaredSum-=pow(sizes[indexesOrderClusters[0]],2.0);
                sum-=sizes[indexesOrderClusters[0]];
            }
            if(squaredSum!=0){
                averageFiniteMassClusters.push_back(squaredSum/sum);
            }else{
                averageFiniteMassClusters.push_back(0.0);
            }
        }
    }
    //    std::cout<<'\n';
    //    std::cout<<'\n';
    //    std::cout<<'\n';
    //    std::cout<<'\n';
    //
    //    std::cout<<"angles =c(";
    //    for(long i=0;i<angles.size();i++){
    //        std::cout<<std::to_string(angles[i])<<",";
    //    }
    //    std::cout<<")"<<'\n';
    //    std::cout<<"p= c(";
    //    for(long i=0;i<acceptedProbabilities.size();i++){
    //        std::cout<<std::to_string(acceptedProbabilities[i])<<",";
    //    }
    //    std::cout<<")"<<'\n';
    //    std::cout<<"masses_GC =c( ";
    //    for(long i=0;i<massesGC.size();i++){
    //        std::cout<<std::to_string(massesGC[i])<<",";
    //    }
    //    std::cout<<")"<<'\n';
    //    std::cout<<"averageClusterSize =c(";
    //    for(long i=0;i<averageFiniteMassClusters.size();i++){
    //        std::cout<<std::to_string(averageFiniteMassClusters[i])<<",";
    //    }
    //    std::cout<<")"<<'\n';
    //    std::cout<<"anglePhaseTransition ="<<std::to_string(anglePhaseTransition)<<'\n';
    //    std::cout<<'\n';
    //    std::cout<<"probabilityPhaseTransition ="<<std::to_string(probabilityPhaseTransition)<<'\n';
    massesGC.swap(cep.massesGC);
    averageFiniteMassClusters.swap(cep.averageClusterSize);
    angles.swap(cep.angles);
    acceptedProbabilities.swap(cep.probabilities);
}



std::vector<double> DualExtendedGraph::calculateThresholdFromEntropyDistribution(std::vector<double> initialPs,std::vector<double> entropies){
    std::vector<double> finalPs;
    finalPs.reserve(initialPs.size());
    long indexA=0;
    long indexB=0;
    std::vector<double> integrationEntropies;
    integrationEntropies.resize(entropies.size(),0.0);

    double maxEntropy=0.0;
    double minEntropy=INFINITY;
    for(long i=1;i<entropies.size();i++){
        // std::cout<<initialPs[i]<<" "<<entropies[i]<<'\n';
        double minY=Functions::min(entropies[i],entropies[i-1]);
        double areaUnder=(initialPs[i]-initialPs[i-1])*minY;
        double areaIn=(initialPs[i]-initialPs[i-1])*Functions::abs(entropies[i]-entropies[i-1])/2.0;
        integrationEntropies[i]=integrationEntropies[i-1]+areaIn+areaUnder;
        // integrationEntropies[i]+=integrationEntropies[i-1];
        if(integrationEntropies[i]>maxEntropy){
            maxEntropy=integrationEntropies[i];
        }
        if(integrationEntropies[i]<minEntropy){
            minEntropy=integrationEntropies[i];
        }
    }

    double increment=(maxEntropy-minEntropy)/(double)(initialPs.size());
    std::vector<double> theoreticalEntropyBreaks;
    theoreticalEntropyBreaks.resize(initialPs.size(),0.0);
    for(long i=0;i<initialPs.size();i++){
        theoreticalEntropyBreaks[i]=(double)(i)*increment+minEntropy;
    }

    // while(indexA<initialPs.size()-1){
    //     if(entropies[indexA+1]>entropies[indexA]){
    //         if(theoreticalEntropyBreaks[indexB]>entropies[indexA+1]){
    //             indexA++;
    //         }else if(theoreticalEntropyBreaks[indexB]<entropies[indexA+1]){
    //             double x=initialPs[indexA+1]-initialPs[indexA];
    //             double y=entropies[indexA+1]-entropies[indexA];
    //             double y1=theoreticalEntropyBreaks[indexB]-entropies[indexA];
    //             double proportion=y1/y;
    //             double result=x*proportion+initialPs[indexA];
    //             finalPs.push_back[result];
    //             indexB++;
    //             //me he quedado aqui

    //         }else if(theoreticalEntropyBreaks[indexB]==entropies[indexA+1]){
    //             finalPs.push_back(initialPs[indexA+1]);
    //             indexA++;
    //             indexB++;
    //         }
    //     }else if(entropies[indexA+1]<entropies[indexA]){
    //         if(theoreticalEntropyBreaks[indexB]<entropies[indexA+1]){
    //             indexA++;
    //         }else if(theoreticalEntropyBreaks[indexB]>entropies[indexA+1]){
    //             double x=initialPs[indexA+1]-initialPs[indexA];
    //             double y=entropies[indexA+1]-entropies[indexA];
    //             double y1=theoreticalEntropyBreaks[indexB]-entropies[indexA];
    //             double proportion=y1/y;
    //             double result=x*proportion+initialPs[indexA];
    //             finalPs.push_back[result];
    //             indexB++;
    //             //me he quedado aqui

    //         }else if(theoreticalEntropyBreaks[indexB]==entropies[indexA+1]){
    //             finalPs.push_back(initialPs[indexA+1]);
    //             indexA++;
    //             indexB++;
    //         }
    //     }
    // }

    for(long i=0;i<initialPs.size()-1;i++){
        double entA=integrationEntropies[i];
        double entB=integrationEntropies[i+1];
        if(entB<entA){
            double entTemp=entA;
            entA=entB;
            entB=entTemp;
        }
        for(long j=0;j<theoreticalEntropyBreaks.size();j++){
            if(theoreticalEntropyBreaks[j]==integrationEntropies[i]){
                finalPs.push_back(initialPs[i]);
                // std::cout<<" theoreticalEntropy "<<theoreticalEntropyBreaks[j]<<" entropies[i] "<<entropies[i]<<'\n';
            }else if(theoreticalEntropyBreaks[j]>entA&&theoreticalEntropyBreaks[j]<entB){
                double x=initialPs[i+1]-initialPs[i];
                double y=integrationEntropies[i+1]-integrationEntropies[i];
                double y1=theoreticalEntropyBreaks[j]-integrationEntropies[i];
                double proportion=y1/y;

                double result=x*proportion+initialPs[i];
                // std::cout<<"proportion "<<proportion<<" theoreticalEntropy "<<theoreticalEntropyBreaks[j]<<" entropies[i] "<<integrationEntropies[i]<<" entropies[i+1] "<<integrationEntropies[i+1]<<" result "<<result<<'\n';
                finalPs.push_back(result);

            }
            if(theoreticalEntropyBreaks[j]>entB){
                break;
            }
        }
    }

    return finalPs;

}



double DualExtendedGraph::getEntropyFromAngularPercolation(DualExtendedGraph* deg,double angle){

    std::vector<long> colors;
    // std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double entropy=0.0;
    DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);
    double totalSize=(double)(deg->getLineGraph()->links.size());
    if(sizes.size()>0){
        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
        double massGiantCluster=sizes[indexesOrderClusters[0]];





        std::unordered_map<long,double> statesSystem;

        long totalSizeInClusters=0;
       for(long j=0;j<sizes.size();j++){
            statesSystem[sizes[j]]+=sizes[j];
            totalSizeInClusters+=sizes[j];
       }

      if(totalSize-totalSizeInClusters>0){
           statesSystem[0]+=totalSize-totalSizeInClusters;
       }



        for(auto it:statesSystem){

                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);

        }

    }else{
        // entropies.push_back(0.0);
    }
    return entropy;
}

double DualExtendedGraph::getEntropyFromMetricPercolation(DualExtendedGraph* deg,double threshold){

    std::vector<long> colors;
    // std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double entropy=0.0;
    DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    if(sizes.size()>0){
        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
        double massGiantCluster=sizes[indexesOrderClusters[0]];





        std::unordered_map<long,double> statesSystem;

        long totalSizeInClusters=0;
       for(long j=0;j<sizes.size();j++){
            statesSystem[sizes[j]]+=sizes[j];
            totalSizeInClusters+=sizes[j];
       }

      if(totalSize-totalSizeInClusters>0){
           statesSystem[0]+=totalSize-totalSizeInClusters;
       }



        for(auto it:statesSystem){

                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);

        }

    }else{
        // entropies.push_back(0.0);
    }
    return entropy;
}

double DualExtendedGraph::getEntropyFromDualPercolation(DualExtendedGraph* deg,double threshold){

    std::vector<long> colors;
    // std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double entropy=0.0;
    DualExtendedGraph::dualPercolation(deg,threshold, colors, sizes);
    double totalSize=(double)(deg->getDualGraph()->links.size());
    if(sizes.size()>0){
        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
        double massGiantCluster=sizes[indexesOrderClusters[0]];





        std::unordered_map<long,double> statesSystem;

        long totalSizeInClusters=0;
       for(long j=0;j<sizes.size();j++){
            statesSystem[sizes[j]]+=sizes[j];
            totalSizeInClusters+=sizes[j];
       }

      if(totalSize-totalSizeInClusters>0){
           statesSystem[0]+=totalSize-totalSizeInClusters;
       }



        for(auto it:statesSystem){

                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);

        }

    }else{
        // entropies.push_back(0.0);
    }
    return entropy;
}

void DualExtendedGraph::calculateHierarchicalIndexAngular(DualExtendedGraph* deg,double definition,std::vector<double> &HI){
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);


    std::vector<double> vectorOfWeights=getAngularWeightsLineGraph(deg);
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);

    std::vector<double> massesGC;
//    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> angles;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    long j=0;
    double currentProbability=probabilities[j];


    for(long i=0;i<orderedVectorOfWeights.size();i++){


        if((double)(i)/(double)orderedVectorOfWeights.size()>currentProbability&&(double)(i-1)/(double)orderedVectorOfWeights.size()<=currentProbability){
            j++;
            currentProbability=probabilities[j];
            angles.push_back(orderedVectorOfWeights[i]);
            // acceptedProbabilities.push_back((double)(i)/(double)orderedVectorOfWeights.size());


        }
    }
    angles.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);




double increaseAngle=180.0/definition;
for(long i=0;i<=definition;i++){
    angles.push_back(i*increaseAngle);
}



angles=Functions::orderValues(angles,true);





//    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
//    double minThreshold=orderedVectorOfWeights[0];
//    double incrementThreshold=(maxThreshold-minThreshold)/definition;
//
//    for(long i=0;i<definition;i++){
//        angles.push_back(minThreshold+incrementThreshold*(double)i);
//        //        acceptedProbabilities.push_back(<#const_reference __x#>)
//    }

    std::vector<long> colors;
    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    HI.resize(deg->getLineGraph()->nodes.size(),0.0);
    massesGC.reserve(angles.size());
//    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getLineGraph()->links.size());
    double prevEntropy=0;
    bool maxDetected=false;
    std::vector<double> entropies;
    entropies.reserve(angles.size());
    double sumDerivatives=0;

    for(long i=0;i<angles.size();i++){
        double angle=angles[i];

//        double massGiantCluster=0;

        sizes.clear();
        colors.clear();

        DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);
        Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colors, colorsNodes);
        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);

           // double derivativeGC=0;
           // if(i>0){
           //     derivativeGC=(massGiantCluster-massesGC[i-1])/(acceptedProbabilities[i]-acceptedProbabilities[i-1]);
           //     if(derivativeGC>0){
           //         sumDerivatives+=log(derivativeGC);
           //     }
           // }else{
           //      derivativeGC=0;
           // }
           // if(derivativeGC<1){
           //  derivativeGC=1;
           // }


            std::unordered_map<long,double> statesSystem;

//             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

          if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
//                for(long j=0;j<HI.size();j++){
//                    HI[j]=0;
//                }
//                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            // entropies.push_back(entropy*log(massGiantCluster));
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
//             std::cout<<angle<<" "<<entropy<<" "<<massGiantCluster<<'\n';

//             for(long j=0;j<colorsNodes.size();j++){
//                 if(colorsNodes[j]!=-1&&massGiantCluster>0){
// //                    if(sizes[colorsNodes[j]]>=2){
// //                    if(derivativeGC>0){

//                         HI[j]+=log(sizes[colorsNodes[j]])*entropy*log(massGiantCluster);
//                     // HI[j]+=log(sizes[colorsNodes[j]])*entropy;
// //                    }
// //                    }
//                 }
//             }

//            if(maxDetected&&entropy<.1){
//                break;
//            }
        }else{
            entropies.push_back(0.0);
        }
    }




//    angles.clear();
//
//
// std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


// for(long i=0;i<newPs.size();i++){
//     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
//     angles.push_back(orderedVectorOfWeights[index]);
//     std::cout<<"checking "<<newPs[i]<<" "<<index<<" "<<orderedVectorOfWeights[index]<<'\n';
// }

angles=calculateThresholdFromEntropyDistribution(angles,entropies);
















    for(long i=0;i<angles.size();i++){
        double angle=angles[i];

//        double massGiantCluster=0;

        sizes.clear();
        colors.clear();

        DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);
        Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colors, colorsNodes);
        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            // massesGC.push_back(massGiantCluster);

           // double derivativeGC=0;
           // if(i>0){
           //     derivativeGC=(massGiantCluster-massesGC[i-1])/(acceptedProbabilities[i]-acceptedProbabilities[i-1]);
           //     if(derivativeGC>0){
           //         sumDerivatives+=log(derivativeGC);
           //     }
           // }

            std::unordered_map<long,double> statesSystem;

//             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

          if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }
            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }




            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
//                for(long j=0;j<HI.size();j++){
//                    HI[j]=0;
//                }
//                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster)*log(massGiantCluster);
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
            if(indexesOrderClusters.size()>1){
           std::cout<<angle<<" "<<entropy<<" "<<massGiantCluster<<" "<<sizes[indexesOrderClusters[1]]<<'\n';
       }else{
           std::cout<<angle<<" "<<entropy<<" "<<massGiantCluster<<" "<<0<<'\n';
       }

            for(long j=0;j<colorsNodes.size();j++){
                if(colorsNodes[j]!=-1&&massGiantCluster>0){
//                    if(sizes[colorsNodes[j]]>=2){
//                    if(derivativeGC>0){

                        // HI[j]+=log(sizes[colorsNodes[j]])*entropy*log(massGiantCluster);
                    HI[j]+=log(sizes[colorsNodes[j]])*entropy;
//                    }
//                    }
                }
            }

//            if(maxDetected&&entropy<.1){
//                break;
//            }
        }
    }

    for(long i=0;i<HI.size();i++){
//        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getLineGraph()->links.size())));
       HI[i]/=(sumEntropies);
//        HI[i]/=sumDerivatives*log((double)(deg->getLineGraph()->links.size()));
    }



}





void DualExtendedGraph::calculateHierarchicalIndexAngularUsingMetricweightsAsMass(DualExtendedGraph* deg,double definition,std::vector<double> &HI){
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);


    std::vector<double> vectorOfWeights=getAngularWeightsLineGraph(deg);
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);

    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> angles;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    long j=0;
    double currentProbability=probabilities[j];


    for(long i=0;i<orderedVectorOfWeights.size();i++){


        if((double)(i)/(double)orderedVectorOfWeights.size()>currentProbability&&(double)(i-1)/(double)orderedVectorOfWeights.size()<=currentProbability){
            j++;
            currentProbability=probabilities[j];
            angles.push_back(orderedVectorOfWeights[i]);
            // acceptedProbabilities.push_back((double)(i)/(double)orderedVectorOfWeights.size());


        }
    }
    angles.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);




    double increaseAngle=180.0/definition;
    for(long i=0;i<=definition;i++){
        angles.push_back(i*increaseAngle);
    }



    angles=Functions::orderValues(angles,true);
    double roundingFactor=1;

    double TSL=0;
   for(long i=0;i<deg->getLineGraph()->links.size();i++){
       Link* a=deg->getPrimalGraph()->links[deg->getLineGraph()->links[i]->A()->id];
       Link* b=deg->getPrimalGraph()->links[deg->getLineGraph()->links[i]->B()->id];
       TSL+=a->weight/2.0+b->weight/2.0;
   }



    //    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        angles.push_back(minThreshold+incrementThreshold*(double)i);
    //        //        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }

    std::vector<long> colors;
    std::vector<long> colorsNodes;
    std::vector<double> sizesLinks;
    double sumEntropies=0.0;

    HI.resize(deg->getLineGraph()->nodes.size(),0.0);
    massesGC.reserve(angles.size());
    //    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getLineGraph()->links.size());
    double prevEntropy=0;
    bool maxDetected=false;
    std::vector<double> entropies;
    entropies.reserve(angles.size());
        double sumDerivatives=0;

    for(long i=0;i<angles.size();i++){
        double angle=angles[i];

        //        double massGiantCluster=0;

        sizesLinks.clear();
        colors.clear();

        DualExtendedGraph::angularPercolation(deg,angle, colors, sizesLinks);
        // Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colors, colorsNodes);
        if(sizesLinks.size()>0){
            // std::unordered_map<long,double> sizesTemp;
            std::vector<double> sizes;
            sizes.clear();
            sizes.resize(sizesLinks.size(),0);
            // TSL=0;
//            std::cout<<"what? "<<colors.size()<<" "<<deg->getLineGraph()->links.size()<<" "<<deg->getPrimalGraph()->links.size()<<'\n';
            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1){
                    Link* a=deg->getPrimalGraph()->links[deg->getLineGraph()->links[j]->A()->id];
                    Link* b=deg->getPrimalGraph()->links[deg->getLineGraph()->links[j]->B()->id];
                    double metricWeight=a->weight/2.0+b->weight/2.0;
    //                sizesTemp[colors[j]]+=round(metricWeight/roundingFactor)*roundingFactor;
    //                TSL+=round(metricWeight/roundingFactor)*roundingFactor;
                    sizes[colors[j]]+=metricWeight;
                }
                // TSL+=metricWeight;
//                std::cout<<"weight "<<deg->getLineGraph()->links[j]->weight<<'\n';
            }

            // for(auto it:sizesTemp){
            //     if(it.first!=-1){
            //         sizes[it.first]=(it.second);
            //     }
            // }
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);

            // double derivativeGC=0;
            // if(i>0){
            //     derivativeGC=(massGiantCluster-massesGC[i-1])/(acceptedProbabilities[i]-acceptedProbabilities[i-1]);
            //     if(derivativeGC>0){
            //         sumDerivatives+=log(derivativeGC);
            //     }
            // }else{
            //      derivativeGC=0;
            // }
            // if(derivativeGC<1){
            //  derivativeGC=1;
            // }


            std::unordered_map<double,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            double totalSizeInClusters=0;
            for(long j=0;j<sizes.size();j++){
                statesSystem[round(sizes[j])]+=(sizes[j]);
                totalSizeInClusters+=sizes[j];
            }

            if(TSL-totalSizeInClusters>0){
                statesSystem[0]+=TSL-totalSizeInClusters;
            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/TSL;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            // entropies.push_back(entropy*log(massGiantCluster));
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            //             std::cout<<angle<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colorsNodes.size();j++){
            //                 if(colorsNodes[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colorsNodes[j]]>=2){
            // //                    if(derivativeGC>0){

            //                         HI[j]+=log(sizes[colorsNodes[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colorsNodes[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }

            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }
        }else{
            entropies.push_back(0.0);
        }
    }




    //    angles.clear();
    //
    //
    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     angles.push_back(orderedVectorOfWeights[index]);
    //     std::cout<<"checking "<<newPs[i]<<" "<<index<<" "<<orderedVectorOfWeights[index]<<'\n';
    // }

    angles=calculateThresholdFromEntropyDistribution(angles,entropies);
















    for(long i=0;i<angles.size();i++){
        double angle=angles[i];

        //        double massGiantCluster=0;

        sizesLinks.clear();
        colors.clear();

        DualExtendedGraph::angularPercolation(deg,angle, colors, sizesLinks);
        Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colors, colorsNodes);
        if(sizesLinks.size()>0){
            std::vector<double> sizes;
            sizes.clear();
            sizes.resize(sizesLinks.size(),0);
            // double total=0;
            // std::unordered_map<long,double> sizesTemp;
            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1){
                    Link* a=deg->getPrimalGraph()->links[deg->getLineGraph()->links[j]->A()->id];
                    Link* b=deg->getPrimalGraph()->links[deg->getLineGraph()->links[j]->B()->id];
                    double metricWeight=a->weight/2.0+b->weight/2.0;
                    sizes[colors[j]]+=metricWeight;
                    // total+=metricWeight;
                }
            }
            // std::cout<<"total "<< total<<'\n';
            // std::vector<double> sizes;
            // sizes.resize(sizesLinks.size(),0);
            // for(auto it:sizesTemp){
            //     if(it.first!=-1){
            //         sizes[it.first]=(it.second);
            //     }
            // }
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);

            // double derivativeGC=0;
            // if(i>0){
            //     derivativeGC=(massGiantCluster-massesGC[i-1])/(acceptedProbabilities[i]-acceptedProbabilities[i-1]);
            //     if(derivativeGC>0){
            //         sumDerivatives+=log(derivativeGC);
            //     }
            // }else{
            //      derivativeGC=0;
            // }
            // if(derivativeGC<1){
            //  derivativeGC=1;
            // }


            std::unordered_map<double,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizes.size();j++){
                statesSystem[round(sizes[j])]+=(sizes[j]);
                totalSizeInClusters+=sizes[j];
            }

            if(TSL-totalSizeInClusters>0){
                statesSystem[0]+=TSL-totalSizeInClusters;
            }
            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/TSL;
                entropy-=probability*log(probability);
                //                }
            }




            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster)*log(massGiantCluster);
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
            if(indexesOrderClusters.size()>1){
               std::cout<<angle<<" "<<entropy<<" "<<massGiantCluster<<" "<<sizes[indexesOrderClusters[1]]<<" "<<TSL<<'\n';
           }else{
               std::cout<<angle<<" "<<entropy<<" "<<massGiantCluster<<" "<<0<<" "<<TSL<<'\n';
           }

            for(long j=0;j<colorsNodes.size();j++){
                if(colorsNodes[j]!=-1&&massGiantCluster>0){
                    //                    if(sizes[colorsNodes[j]]>=2){
                    //                    if(derivativeGC>0){

                    // HI[j]+=log(sizes[colorsNodes[j]])*entropy*log(massGiantCluster);
                    HI[j]+=log(sizes[colorsNodes[j]])*entropy;
                    //                    }
                    //                    }
                }
            }

            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }
        }
    }

    for(long i=0;i<HI.size();i++){
        //        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getLineGraph()->links.size())));
        HI[i]/=(sumEntropies);
        //        HI[i]/=sumDerivatives*log((double)(deg->getLineGraph()->links.size()));
    }



}


void DualExtendedGraph::calculateHierarchicalIndexMetric(DualExtendedGraph* deg,double definition,std::vector<double> &HI){
//    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
//        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
//    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



//    long j=0;
//    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



            thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
            // acceptedProbabilities.push_back(probabilities[i]);



    }
        thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
        // acceptedProbabilities.push_back(1);








   double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
   double increaseMetric=maxThreshold/definition;
for(long i=0;i<=definition;i++){
    thresholds.push_back(i*increaseMetric);
}

thresholds=Functions::orderValues(thresholds,true);


//    double minThreshold=orderedVectorOfWeights[0];
//    double incrementThreshold=(maxThreshold-minThreshold)/definition;
//
//    for(long i=0;i<definition;i++){
//        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
////        acceptedProbabilities.push_back(<#const_reference __x#>)
//    }



    std::vector<long> colors;
//    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    HI.resize(deg->getPrimalGraph()->links.size(),0.0);
    massesGC.reserve(thresholds.size());
//    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

//        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

//             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

           if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
//                for(long j=0;j<HI.size();j++){
//                    HI[j]=0;
//                }
//                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
             std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

//             for(long j=0;j<colors.size();j++){
//                 if(colors[j]!=-1&&massGiantCluster>0){
// //                    if(sizes[colors[j]]>=2){
// //                    if(derivativeGC>0){
//                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
//                     // HI[j]+=log(sizes[colors[j]])*entropy;
// //                    }
// //                    }
//                 }
//             }
//            if(maxDetected&&entropy<.1){
//                break;
//            }


        }else{
            entropies.push_back(0);
        }
    }






//    thresholds.clear();


// std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


// for(long i=0;i<newPs.size();i++){
//     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
//     thresholds.push_back(orderedVectorOfWeights[index]);
// }




thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);





// massesGC.clear();






    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

//        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            // massesGC.push_back(massGiantCluster);

            std::unordered_map<long,double> statesSystem;
           //             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

           if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
//                for(long j=0;j<HI.size();j++){
//                    HI[j]=0;
//                }
//                sumEntropies=0;
            }
            prevEntropy=entropy;
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
             std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1&&massGiantCluster>0){
//                    if(sizes[colors[j]]>=2){
//                    if(derivativeGC>0){
                        HI[j]+=log(sizes[colors[j]])*entropy;
                    // HI[j]+=log(sizes[colors[j]])*entropy;
//                    }
//                    }
                }
            }
//            if(maxDetected&&entropy<.1){
//                break;
//            }


        }
    }

    for(long i=0;i<HI.size();i++){
//        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
       HI[i]/=(sumEntropies);
//        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
    }

//    if (!deg->primalIsStructuralGraph){
//        std::vector<double> HI_primal;
//        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
//        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
//            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
//                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
//            }
//        }
//        HI_primal.swap(HI);
//
//    }



}










void DualExtendedGraph::calculateHierarchicalIndexMetricUsingMassesNodes(DualExtendedGraph* deg,double definition,std::vector<double> &HI){
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    //    long j=0;
    //    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
        // acceptedProbabilities.push_back(probabilities[i]);



    }
    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);








    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    double increaseMetric=maxThreshold/definition;
    for(long i=0;i<=definition;i++){
        thresholds.push_back(i*increaseMetric);
    }

    thresholds=Functions::orderValues(thresholds,true);


    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }



    std::vector<long> colors;
    //    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    HI.resize(deg->getPrimalGraph()->links.size(),0.0);
    massesGC.reserve(thresholds.size());
    //    averageFiniteMassClusters.reserve(angles.size());
//    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    double totalSize=0;
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();
        totalSize=0;

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

//            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                  statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
//                statesSystem[0]+=totalSize-totalSizeInClusters;
//            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }






    //    thresholds.clear();


    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     thresholds.push_back(orderedVectorOfWeights[index]);
    // }




    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);





    // massesGC.clear();






    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        // std::unordered_map<long,double> statesSystem;
        // totalSizeInClusters=0;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
//                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
//                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1&&massGiantCluster>0){
                    //                    if(sizes[colors[j]]>=2){
                    //                    if(derivativeGC>0){
                    HI[j]+=log(sizesUsingMassNodes[colors[j]])*entropy;
                    // HI[j]+=log(sizes[colors[j]])*entropy;
                    //                    }
                    //                    }
                }
            }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }
    }

    for(long i=0;i<HI.size();i++){
        //        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
        HI[i]/=(sumEntropies);
        //        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
    }

    //    if (!deg->primalIsStructuralGraph){
    //        std::vector<double> HI_primal;
    //        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
    //        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
    //            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
    //                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
    //            }
    //        }
    //        HI_primal.swap(HI);
    //
    //    }



}


void DualExtendedGraph::calculateHierarchicalIndexMetricUsingMassesNodes(DualExtendedGraph* deg,double definition,std::vector<double> &HI,std::vector<double>& thresholdsToUse){
  // std::cout<<"not yet implemented, right now is just a copy of normal HI";
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }


    std::vector<long> colors;
    //    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;
    double totalSize=0;
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    //    long j=0;
    //    double currentProbability=probabilities[j];
if(thresholdsToUse.size()==0){

    for(long i=0;i<probabilities.size();i++){



        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
        // acceptedProbabilities.push_back(probabilities[i]);



    }
    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);








    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    double increaseMetric=maxThreshold/definition;
    for(long i=0;i<=definition;i++){
        thresholds.push_back(i*increaseMetric);
    }

    thresholds=Functions::orderValues(thresholds,true);


    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }




    sumEntropies=0.0;

    HI.resize(deg->getPrimalGraph()->links.size(),0.0);
    massesGC.reserve(thresholds.size());
    //    averageFiniteMassClusters.reserve(angles.size());
//    double totalSize=(double)(deg->getStructuralGraph()->links.size());
     totalSize=0;
     prevEntropy=0;
     maxDetected=false;
     sumDerivatives=0;
    // std::vector<double> entropies;
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();
        totalSize=0;

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

//            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                  statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
//                statesSystem[0]+=totalSize-totalSizeInClusters;
//            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }






    //    thresholds.clear();


    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     thresholds.push_back(orderedVectorOfWeights[index]);
    // }




    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);

}else{
  for(long i=0;i<thresholdsToUse.size();i++){
    thresholds.push_back(thresholdsToUse[i]);
  }

}



    // massesGC.clear();



std::cout <<thresholds.size()<<'\n';
HI.resize(deg->getPrimalGraph()->links.size(),0.0);
massesGC.reserve(thresholds.size());

    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        std::unordered_map<long,double> statesSystem;
        // totalSizeInClusters=0;
        totalSize=0;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
               totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                   totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
            std::cout<<"calculating HI"<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1&&massGiantCluster>0){
                    //                    if(sizes[colors[j]]>=2){
                    //                    if(derivativeGC>0){
                    HI[j]+=log(sizesUsingMassNodes[colors[j]])*entropy;
                    // HI[j]+=log(sizes[colors[j]])*entropy;
                    //                    }
                    //                    }
                }
            }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }
    }

    for(long i=0;i<HI.size();i++){
        //        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
        HI[i]/=(sumEntropies);
        //        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
    }

    //    if (!deg->primalIsStructuralGraph){
    //        std::vector<double> HI_primal;
    //        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
    //        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
    //            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
    //                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
    //            }
    //        }
    //        HI_primal.swap(HI);
    //
    //    }



}



void DualExtendedGraph::calculateHierarchicalIndexMetricUsingMassesNodesAsMeasureOfStructure(DualExtendedGraph* deg,double definition,std::vector<double> &strengthConnection){
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    //    long j=0;
    //    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
        // acceptedProbabilities.push_back(probabilities[i]);



    }
    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);








    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    double increaseMetric=maxThreshold/definition;
    for(long i=0;i<=definition;i++){
        thresholds.push_back(i*increaseMetric);
    }

    thresholds=Functions::orderValues(thresholds,true);


    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }



    std::vector<long> colors;
    //    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    strengthConnection.resize(deg->getPrimalGraph()->links.size(),0.0);
    massesGC.reserve(thresholds.size());
    //    averageFiniteMassClusters.reserve(angles.size());
    //    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    double totalSize=0;
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();
        totalSize=0;

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            //                statesSystem[0]+=totalSize-totalSizeInClusters;
            //            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }






    //    thresholds.clear();


    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     thresholds.push_back(orderedVectorOfWeights[index]);
    // }




    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);





    // massesGC.clear();






    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        // std::unordered_map<long,double> statesSystem;
        // totalSizeInClusters=0;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                //                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                    //                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            sumEntropies+=entropy;
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1&&massGiantCluster>0){
                    //                    if(sizes[colors[j]]>=2){
                    //                    if(derivativeGC>0){
                    strengthConnection[j]+=entropy;
                    // HI[j]+=log(sizes[colors[j]])*entropy;
                    //                    }
                    //                    }
                }
            }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }
    }

    for(long i=0;i<strengthConnection.size();i++){
        //        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
        strengthConnection[i]/=(sumEntropies);
        //        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
    }

    //    if (!deg->primalIsStructuralGraph){
    //        std::vector<double> HI_primal;
    //        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
    //        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
    //            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
    //                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
    //            }
    //        }
    //        HI_primal.swap(HI);
    //
    //    }



}















//void DualExtendedGraph::findChristallersStructure(DualExtendedGraph* deg,double definition,std::vector<double> &strengthConnection){
//    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
//    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
//
//    std::vector<double> vectorOfWeights;
//    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
//    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
//        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
//    }
//    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
//    std::vector<double> orderedVectorOfWeights;
//    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
//    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);
//
//
//
//    std::vector<double> massesGC;
//    //    std::vector<double> averageFiniteMassClusters;
//
//    std::vector<double> probabilities;
//    // std::vector<double> acceptedProbabilities;
//    std::vector<double> thresholds;
//
//
//
//
//    double increaseProbability=1.0/definition;
//
//
//    for(double i=0.0;i<=1.0;i+=increaseProbability){
//        probabilities.push_back(i);
//    }
//
//
//
//    //    long j=0;
//    //    double currentProbability=probabilities[j];
//
//
//    for(long i=0;i<probabilities.size();i++){
//
//
//
//        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
//        // acceptedProbabilities.push_back(probabilities[i]);
//
//
//
//    }
//    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
//    // acceptedProbabilities.push_back(1);
//
//
//
//
//
//
//
//
//    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
//    double increaseMetric=maxThreshold/definition;
//    for(long i=0;i<=definition;i++){
//        thresholds.push_back(i*increaseMetric);
//    }
//
//    thresholds=Functions::orderValues(thresholds,true);
//
//
//    //    double minThreshold=orderedVectorOfWeights[0];
//    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
//    //
//    //    for(long i=0;i<definition;i++){
//    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
//    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
//    //    }
//
//
//
//    std::vector<long> colors;
//    //    std::vector<long> colorsNodes;
//    std::vector<double> sizes;
//    double sumEntropies=0.0;
//
//    strengthConnection.resize(deg->getPrimalGraph()->links.size(),0.0);
//    massesGC.reserve(thresholds.size());
//    //    averageFiniteMassClusters.reserve(angles.size());
//    //    double totalSize=(double)(deg->getStructuralGraph()->links.size());
//    double totalSize=0;
//    double prevEntropy=0;
//    bool maxDetected=false;
//    double sumDerivatives=0;
//    std::vector<double> entropies;
//    entropies.reserve(thresholds.size());
//
//
//    for(long i=0;i<thresholds.size();i++){
//        double threshold=thresholds[i];
//
//        //        double massGiantCluster=0;
//        sizes.clear();
//        colors.clear();
//        totalSize=0;
//
//        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
//        std::vector<double> sizesUsingMassNodes;
//        sizesUsingMassNodes.resize(sizes.size(),0);
//        std::vector<bool> nodeAlreadyCounted;
//        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
//        for(long j=0;j<colors.size();j++){
//            if(colors[j]!=-1){
//                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
//                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
//                    massA=0;
//                }
//                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
//                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
//                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
//                    massB=0;
//                }
//                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
//                sizesUsingMassNodes[colors[j]]+=massA+massB;
//                totalSize+=massA+massB;
//            }
//        }
//
//
//        if(sizesUsingMassNodes.size()>0){
//            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
//            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
//            massesGC.push_back(massGiantCluster);
//            std::unordered_map<long,double> statesSystem;
//
//            //             totalSize=0.0;
//            //            for(long j=0;j<sizes.size();j++){
//            // //                if(sizes[j]>=2){
//            //                    totalSize+=sizes[j];
//            // //                }
//            //            }
//            long totalSizeInClusters=0;
//            for(long j=0;j<sizesUsingMassNodes.size();j++){
//                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
//                totalSizeInClusters+=sizesUsingMassNodes[j];
//            }
//
//            //            if(totalSize-totalSizeInClusters>0){
//            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
//                if(!nodeAlreadyCounted[j]){
//                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
//                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
//                }
//            }
//            //                statesSystem[0]+=totalSize-totalSizeInClusters;
//            //            }
//
//            double entropy=0.0;
//            // for(long j=0;j<sizes.size();j++){
//            for(auto it:statesSystem){
//                //                if(sizes[j]>=2){
//                double probability=(double)it.second/totalSize;
//                entropy-=probability*log(probability);
//                //                }
//            }
//            if(prevEntropy>entropy&&!maxDetected){
//                maxDetected=true;
//                //                for(long j=0;j<HI.size();j++){
//                //                    HI[j]=0;
//                //                }
//                //                sumEntropies=0;
//            }
//            prevEntropy=entropy;
//            // sumEntropies+=entropy*log(massGiantCluster);
//            entropies.push_back(entropy);
//            // sumEntropies+=entropy;
//            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';
//
//            //             for(long j=0;j<colors.size();j++){
//            //                 if(colors[j]!=-1&&massGiantCluster>0){
//            // //                    if(sizes[colors[j]]>=2){
//            // //                    if(derivativeGC>0){
//            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
//            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
//            // //                    }
//            // //                    }
//            //                 }
//            //             }
//            //            if(maxDetected&&entropy<.1){
//            //                break;
//            //            }
//
//
//        }else{
//            entropies.push_back(0);
//        }
//    }
//
//
//
//
//
//
//    //    thresholds.clear();
//
//
//    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);
//
//
//    // for(long i=0;i<newPs.size();i++){
//    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
//    //     thresholds.push_back(orderedVectorOfWeights[index]);
//    // }
//
//
//
//
//    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);
//
//
//
//
//
//    // massesGC.clear();
//
//
//
//
//
//
//    for(long i=0;i<thresholds.size();i++){
//        double threshold=thresholds[i];
//
//        //        double massGiantCluster=0;
//        sizes.clear();
//        colors.clear();
//
//        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
//        std::vector<double> sizesUsingMassNodes;
//        sizesUsingMassNodes.resize(sizes.size(),0);
//        std::vector<bool> nodeAlreadyCounted;
//        // std::unordered_map<long,double> statesSystem;
//        // totalSizeInClusters=0;
//        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
//        for(long j=0;j<colors.size();j++){
//            if(colors[j]!=-1){
//                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
//                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
//                    massA=0;
//                }
//                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
//                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
//                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
//                    massB=0;
//                }
//                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
//                sizesUsingMassNodes[colors[j]]+=massA+massB;
//                //                totalSize+=massA+massB;
//            }
//        }
//
//
//        if(sizesUsingMassNodes.size()>0){
//            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
//            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
//            massesGC.push_back(massGiantCluster);
//            std::unordered_map<long,double> statesSystem;
//
//            //             totalSize=0.0;
//            //            for(long j=0;j<sizes.size();j++){
//            // //                if(sizes[j]>=2){
//            //                    totalSize+=sizes[j];
//            // //                }
//            //            }
//            long totalSizeInClusters=0;
//            for(long j=0;j<sizesUsingMassNodes.size();j++){
//                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
//                totalSizeInClusters+=sizesUsingMassNodes[j];
//            }
//
//            //            if(totalSize-totalSizeInClusters>0){
//            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
//                if(!nodeAlreadyCounted[j]){
//                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
//                    //                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
//                }
//            }
//            double entropy=0.0;
//            // for(long j=0;j<sizes.size();j++){
//            for(auto it:statesSystem){
//                //                if(sizes[j]>=2){
//                double probability=(double)it.second/totalSize;
//                entropy-=probability*log(probability);
//                //                }
//            }
//            if(prevEntropy>entropy&&!maxDetected){
//                maxDetected=true;
//                //                for(long j=0;j<HI.size();j++){
//                //                    HI[j]=0;
//                //                }
//                //                sumEntropies=0;
//            }
//            prevEntropy=entropy;
//            sumEntropies+=entropy;
//            // sumEntropies+=entropy;
//            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';
//
//            for(long j=0;j<colors.size();j++){
//                if(colors[j]!=-1&&massGiantCluster>0){
//                    //                    if(sizes[colors[j]]>=2){
//                    //                    if(derivativeGC>0){
//                    strengthConnection[j]+=entropy;
//                    // HI[j]+=log(sizes[colors[j]])*entropy;
//                    //                    }
//                    //                    }
//                }
//            }
//            //            if(maxDetected&&entropy<.1){
//            //                break;
//            //            }
//
//
//        }
//    }
//
//    for(long i=0;i<strengthConnection.size();i++){
//        //        HI[i]/=(sumEntropies);
//        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
//        strengthConnection[i]/=(sumEntropies);
//        //        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
//    }
//
//    //    if (!deg->primalIsStructuralGraph){
//    //        std::vector<double> HI_primal;
//    //        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
//    //        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
//    //            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
//    //                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
//    //            }
//    //        }
//    //        HI_primal.swap(HI);
//    //
//    //    }
//
//
//
//}
//






























void DualExtendedGraph::calculateHierarchicalIndexMetric_basedInDensityOfNodesThatRepresentAGrid_UsingMassesNodes(DualExtendedGraph* deg,double definition,std::vector<double> &HI,double widthSquareGrid){
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    //    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    //    long j=0;
    //    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
        // acceptedProbabilities.push_back(probabilities[i]);



    }
    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);








    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    double increaseMetric=maxThreshold/definition;
    for(long i=0;i<=definition;i++){
        thresholds.push_back(i*increaseMetric);
    }

    thresholds=Functions::orderValues(thresholds,true);


    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }



    std::vector<long> colors;
    //    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    HI.resize(deg->getPrimalGraph()->links.size(),0.0);
    massesGC.reserve(thresholds.size());
    //    averageFiniteMassClusters.reserve(angles.size());
    //    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    double totalSize=0;
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();
        totalSize=0;

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        std::vector<double> areas;
                        areas.resize(sizes.size(),0);
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                 double areaA=1.0;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                    areaA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                double areaB=1.0;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                    areaB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
//                totalSize+=(massA+massB);
                areas[colors[j]]+=areaA*widthSquareGrid*widthSquareGrid+areaB*widthSquareGrid*widthSquareGrid;
                if(areas[colors[j]]>0){
//                                totalSize+=(massA+massB)/areas[colors[j]];
                                                    totalSize+=(massA+massB);
                }
            }
        }







        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<double,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
//                statesSystem[sizesUsingMassNodes[j]/areas[j]]+=sizesUsingMassNodes[j]/areas[j];
                statesSystem[sizesUsingMassNodes[j]/areas[j]]+=sizesUsingMassNodes[j];
//                totalSizeInClusters+=sizesUsingMassNodes[j]/areas[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
//                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass/(widthSquareGrid*widthSquareGrid);
//                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass/(widthSquareGrid*widthSquareGrid);
                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            //                statesSystem[0]+=totalSize-totalSizeInClusters;
            //            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }






    //    thresholds.clear();


    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     thresholds.push_back(orderedVectorOfWeights[index]);
    // }




    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);





    // massesGC.clear();






    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();

        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
                std::vector<double> areas;
                areas.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        // std::unordered_map<long,double> statesSystem;
        // totalSizeInClusters=0;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                double areaA=1.0;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0.0;
                    areaA=0.0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                double areaB=1.0;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                    areaB=0.0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                areas[colors[j]]+=areaA*widthSquareGrid*widthSquareGrid+areaB*widthSquareGrid*widthSquareGrid;
                //                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<double,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
//                statesSystem[sizesUsingMassNodes[j]/areas[j]]+=sizesUsingMassNodes[j]/areas[j];
//                totalSizeInClusters+=sizesUsingMassNodes[j]/areas[j];
                statesSystem[sizesUsingMassNodes[j]/areas[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
//                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass/(widthSquareGrid*widthSquareGrid);
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
//                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass/(widthSquareGrid*widthSquareGrid);
                }
            }
            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1&&massGiantCluster>0){
                    //                    if(sizes[colors[j]]>=2){
                    //                    if(derivativeGC>0){
                    HI[j]+=log(sizesUsingMassNodes[colors[j]]/areas[colors[j]])*entropy;
                    // HI[j]+=log(sizes[colors[j]])*entropy;
                    //                    }
                    //                    }
                }
            }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }
    }

    for(long i=0;i<HI.size();i++){
        //        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
        HI[i]/=(sumEntropies);
        //        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
    }

    //    if (!deg->primalIsStructuralGraph){
    //        std::vector<double> HI_primal;
    //        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
    //        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
    //            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
    //                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
    //            }
    //        }
    //        HI_primal.swap(HI);
    //
    //    }



}





// std::vector<double> DualExtendedGraph::getHImetricInPrimal(DualExtendedGraph* deg,std::vector<double> &HImetricStructural){

//         if (!deg->primalIsStructuralGraph){
//             std::vector<double> HI_primal;
//             HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
//             for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
//                 for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
//                     HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HImetricStructural[i];
//                 }
//             }
//             return HI_primal;

//         }else{
//             return HImetricStructural;
//         }

// }






void DualExtendedGraph::calculateHierarchicalIndexDual(DualExtendedGraph* deg,double definition,std::vector<double> &HI){
//    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getDualGraph()->links.size(),0.0);
    for(long i=0;i<deg->getDualGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getDualGraph()->links[i]->weight);
    }
//        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
//    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



//    long j=0;
//    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



            thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
            // acceptedProbabilities.push_back(probabilities[i]);



    }
        thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
        // acceptedProbabilities.push_back(1);








   double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
   double increaseMetric=maxThreshold/definition;
for(long i=0;i<=definition;i++){
    thresholds.push_back(i*increaseMetric);
}

thresholds=Functions::orderValues(thresholds,true);


//    double minThreshold=orderedVectorOfWeights[0];
//    double incrementThreshold=(maxThreshold-minThreshold)/definition;
//
//    for(long i=0;i<definition;i++){
//        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
////        acceptedProbabilities.push_back(<#const_reference __x#>)
//    }



    std::vector<long> colors;
//    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    HI.resize(deg->getPrimalGraph()->links.size(),0.0);
    massesGC.reserve(thresholds.size());
//    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getDualGraph()->links.size());
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

//        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::dualPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

//             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

           if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
//                for(long j=0;j<HI.size();j++){
//                    HI[j]=0;
//                }
//                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
             std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

//             for(long j=0;j<colors.size();j++){
//                 if(colors[j]!=-1&&massGiantCluster>0){
// //                    if(sizes[colors[j]]>=2){
// //                    if(derivativeGC>0){
//                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
//                     // HI[j]+=log(sizes[colors[j]])*entropy;
// //                    }
// //                    }
//                 }
//             }
//            if(maxDetected&&entropy<.1){
//                break;
//            }


        }else{
            entropies.push_back(0);
        }
    }






//    thresholds.clear();


// std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


// for(long i=0;i<newPs.size();i++){
//     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
//     thresholds.push_back(orderedVectorOfWeights[index]);
// }




thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);





// massesGC.clear();






    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

//        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::dualPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            // massesGC.push_back(massGiantCluster);

            std::unordered_map<long,double> statesSystem;
           //             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

           if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
//                for(long j=0;j<HI.size();j++){
//                    HI[j]=0;
//                }
//                sumEntropies=0;
            }
            prevEntropy=entropy;
            sumEntropies+=entropy*log(massGiantCluster);
            // sumEntropies+=entropy;
             std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            for(long j=0;j<colors.size();j++){
                if(colors[j]!=-1&&massGiantCluster>0){
//                    if(sizes[colors[j]]>=2){
//                    if(derivativeGC>0){
                        HI[j]+=log(sizes[colors[j]])*entropy;
                    // HI[j]+=log(sizes[colors[j]])*entropy;
//                    }
//                    }
                }
            }
//            if(maxDetected&&entropy<.1){
//                break;
//            }


        }
    }

    for(long i=0;i<HI.size();i++){
//        HI[i]/=(sumEntropies);
        // HI[i]/=sumEntropies*(log((double)(deg->getStructuralGraph()->links.size())));
       HI[i]/=(sumEntropies);
//        HI[i]/=sumDerivatives*log((double)(deg->getStructuralGraph()->links.size()));
    }

//    if (!deg->primalIsStructuralGraph){
//        std::vector<double> HI_primal;
//        HI_primal.resize(deg->getPrimalGraph()->links.size(),0.0);
//        for(long i=0;i<deg->idsLinksPrimalByIdsLinksStructural.size();i++){
//            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
//                HI_primal[deg->idsLinksPrimalByIdsLinksStructural[i][j]]=HI[i];
//            }
//        }
//        HI_primal.swap(HI);
//
//    }



}



std::pair<double,double> DualExtendedGraph::detectPhaseTransitionAngularPercolation(DualExtendedGraph* deg,double definition){
    // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
    DualExtendedGraph::createLineGraph(deg);
    double anglePhaseTransition=0;
    double probabilityPhaseTransition=0;
    std::vector<double> setOfAngles;
    std::vector<double> vectorOfWeights=getAngularWeightsLineGraph(deg);
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);
    setOfAngles.push_back(orderedVectorOfWeights[0]+.1);
    setOfAngles.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]+.1);
    std::vector<double> setOfProbabilities;
    std::vector<double> massesGC;
    for(long i=0;i<setOfAngles.size();i++){
        double totalNumberTransitions=deg->lineGraph.links.size();
        long index=Functions::findLastPositionValue(orderedVectorOfWeights, setOfAngles[i]);
        double probability=(double)(index)/(double)totalNumberTransitions;
        setOfProbabilities.push_back(probability);
    }
    for(double h=0;h<setOfAngles.size();h++){
        double angle=setOfAngles[h];


        double massGiantCluster=0;
        std::vector<long> colors;
        std::vector<double> sizes;
        DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);
        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            massGiantCluster=sizes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
        }

    }
    std::vector<double> derivativeMassGC;
    derivativeMassGC=Functions::derivative(massesGC,setOfProbabilities);
    long indexMax=Functions::getLocationMaximum(derivativeMassGC);//plus 1 because the derivative has one object less than the angles
    anglePhaseTransition=setOfAngles[indexMax];
    double currentAngle=setOfAngles[indexMax];
    double nextAngle=(currentAngle+setOfAngles[indexMax+1])/2.0;
    double previousAngle=(currentAngle+setOfAngles[indexMax-1])/2.0;
    double ca=0,na=0,pa=0;
    double distanceBetweenAngles=Functions::max(nextAngle-currentAngle,currentAngle-previousAngle);
    std::vector<long> colors;
    std::vector<double> sizes;
    while(distanceBetweenAngles>definition&&!(ca==currentAngle&&pa==previousAngle&&na==nextAngle)){
        ca=currentAngle;
        na=nextAngle;
        pa=previousAngle;
        double angle=nextAngle;

        DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);

//        std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);

        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            setOfAngles.push_back(angle);
            long index=Functions::findLastPositionValue(orderedVectorOfWeights, angle);
            double totalNumberTransitions=deg->lineGraph.links.size();
            double probability=(double)(index)/(double)totalNumberTransitions;
            setOfProbabilities.push_back(probability);
            massesGC.push_back(massGiantCluster);
            angle=previousAngle;
//            colors.clear();
//            sizes.clear();
            DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);


            if(sizes.size()>0){
                std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
                double massGiantCluster=sizes[indexesOrderClusters[0]];
                setOfAngles.push_back(angle);
                index=Functions::findLastPositionValue(orderedVectorOfWeights, angle);
                totalNumberTransitions=deg->lineGraph.links.size();
                probability=(double)(index)/(double)totalNumberTransitions;
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
                probabilityPhaseTransition=setOfProbabilities[indexMax];
                currentAngle=setOfAngles[indexMax];
                nextAngle=(currentAngle+setOfAngles[indexMax+1])/2.0;
                previousAngle=(currentAngle+setOfAngles[indexMax-1])/2.0;
                distanceBetweenAngles=Functions::max(nextAngle-currentAngle,currentAngle-previousAngle);
               // std::cout<<"===================="<<'\n';
               // std::cout<<"angle : "<<currentAngle<<'\n';
               // std::cout<<"nextAngle : "<<nextAngle<<'\n';
               // std::cout<<"previousAngle : "<<previousAngle<<'\n';
               // std::cout<<"set of angles ";
               // for(long i=0;i<setOfAngles.size();i++){
               //     std::cout<<std::to_string(setOfAngles[i])<<",";
               // }
               // std::cout<<'\n';
               // std::cout<<"set of probabilities ";
               // for(long i=0;i<setOfProbabilities.size();i++){
               //     std::cout<<std::to_string(setOfProbabilities[i])<<",";
               // }
               // std::cout<<'\n';
               // std::cout<<"masses GC ";
               // for(long i=0;i<massesGC.size();i++){
               //     std::cout<<std::to_string(massesGC[i])<<",";
               // }
               // std::cout<<'\n';
               // std::cout<<"derivative masses GC ";
               // for(long i=0;i<derivativeMassGC.size();i++){
               //     std::cout<<std::to_string(derivativeMassGC[i])<<",";
               // }
               // std::cout<<'\n';
            }
        }
    }
//    std::cout<<"pPhaseTransition="<<std::to_string(probabilityPhaseTransition)<<" anglePhaseTransition="<<std::to_string(anglePhaseTransition)<<'\n';
    std::pair<double,double> result;
    result.first=anglePhaseTransition;
    result.second=probabilityPhaseTransition;
    return result;
}







void DualExtendedGraph::measureCriticalExponentsAngularPercolation(DualExtendedGraph* deg,CriticalExponentsPercolation &cep){

    DualExtendedGraph::createLineGraph(deg);
    cep.mass=deg->getLineGraph()->links.size();
    std::cout<<"M = "<<std::to_string(cep.mass)<<'\n';
    Grafo Lg;
    Grafo::constructLineGraph(deg->getLineGraph(),&Lg);
//    double fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg->getPrimalGraph());
//    double fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg->getLineGraph(),InterfaceDijkstra::EUCLIDEAN);
    double fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(&Lg,InterfaceDijkstra::TOPOLOGICAL);
//    Lg.reset();
    std::cout<<"d = "<<std::to_string(fractalDimension)<<'\n';
    cep.d=fractalDimension;
    cep.length_lattice=pow(cep.mass,1/cep.d);
    std::cout<<"l = "<<std::to_string(cep.length_lattice)<<'\n';

    std::pair<double,double> phaseTransition=DualExtendedGraph::detectPhaseTransitionAngularPercolation(deg, .001);
    std::cout<<"Phase transition = "<<std::get<0>(phaseTransition)<<" , p_phaseTransition "<<std::get<1>(phaseTransition)<<'\n';
    cep.anglePhaseTransition=std::get<0>(phaseTransition);
    cep.probabilityPhaseTransition=std::get<1>(phaseTransition);
    std::vector<long> colors;
    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    DualExtendedGraph::angularPercolation(deg,cep.anglePhaseTransition,colors,sizes);
    Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colors, colorsNodes);

    std::vector<Grafo> components;
//            Grafo::getComponentsFromColorsOfLinks(deg->getPrimalGraph(),components,0,colors,sizes);
    //        TextFile::saveCoordinates(&components[0],"/Users/carlos/Documents/data/GIS/UK/skeletonCoordinates.txt");
    //        TextFile::saveNCOL(&components[0],"/Users/carlos/Documents/data/GIS/UK/skeletonNCOL.txt");
    Grafo::getComponentsFromColorsOfNodes(deg->getLineGraph(),components,0,colorsNodes,sizes);

    //        std::vector<long> orderSizes=Functions::getIndexesOfOrderedValues(sizes,true);

    Grafo Lg_subgraph;
    Lg_subgraph.reset();
    Grafo::constructLineGraph(&components[0],&Lg_subgraph);
    cep.mass_phaseTransition=components[0].links.size();
    std::cout<<"M_phaseTransition = "<<std::to_string(cep.mass_phaseTransition)<<'\n';

    components[0].removeNodesDegree0();
//    fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(&components[0]);
    fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(&Lg_subgraph,InterfaceDijkstra::TOPOLOGICAL);
    components.clear();

    cep.D_measured=fractalDimension;
    DualExtendedGraph::calculateCompleteAngularPercolation(deg, 180, cep,false);
    LinearRegression lr;
    std::vector<Point2d> massesGC_forBeta;
    std::vector<Point2d> averageMasses_forGamma;
    for(long i=0;i<cep.massesGC.size();i++){
        if(cep.probabilities[i]<cep.probabilityPhaseTransition){
            if(cep.averageClusterSize[i]>0){
                averageMasses_forGamma.push_back(Point2d(log(cep.probabilityPhaseTransition-cep.probabilities[i]),log(cep.averageClusterSize[i])));
            }
        }
        if(cep.probabilities[i]>cep.probabilityPhaseTransition){
            if(cep.massesGC[i]>0){
                massesGC_forBeta.push_back(Point2d(log(cep.probabilities[i]-cep.probabilityPhaseTransition),log(cep.massesGC[i])));
            }
        }
    }
    lr=LinearRegression::compute(massesGC_forBeta,false);
    cep.beta=lr.slope;
    std::cout<<"beta = "<<std::to_string(cep.beta)<<'\n';
    lr=LinearRegression::compute(averageMasses_forGamma,false);
    cep.gamma_measured=-lr.slope;

    cep.D=log(cep.mass_phaseTransition)/log(cep.length_lattice);
    std::cout<<"D_measured = "<<std::to_string(cep.D_measured)<<'\n';
    std::cout<<"D = "<<std::to_string(cep.D)<<'\n';
    cep.nu=-cep.beta/(cep.D-cep.d);
    std::cout<<"nu = "<<std::to_string(cep.nu)<<'\n';
    cep.gamma=cep.nu*(2.0*cep.D-cep.d);
    std::cout<<"gamma_measured = "<<std::to_string(cep.gamma_measured)<<'\n';
    std::cout<<"gamma = "<<std::to_string(cep.gamma)<<'\n';
    cep.sigma=1/(cep.nu*cep.D);
    std::cout<<"sigma = "<<std::to_string(cep.sigma)<<'\n';
    cep.tau=cep.beta*cep.sigma+2.0;
    std::cout<<"tau = "<<std::to_string(cep.tau)<<'\n';

}

std::vector<double> DualExtendedGraph::getSpeedsForStructuralGraph(DualExtendedGraph* deg, std::vector<double> &HIangular,std::vector<double> &HImetric){
    std::vector<double> speeds;
    speeds.reserve(HImetric.size());
    if(!deg->primalIsStructuralGraph){
        std::cout<<deg->getPrimalGraph()->links.size()<<" "<<HIangular.size()<<" , "<<deg->getStructuralGraph()->links.size()<<" "<<HImetric.size()<<'\n';
        for(long i=0;i<HImetric.size();i++){
            double averageHIangular=0.0;
            double numberElements=0.0;
            for(long j=0;j<deg->idsLinksPrimalByIdsLinksStructural[i].size();j++){
                averageHIangular+=HIangular[deg->idsLinksPrimalByIdsLinksStructural[i][j]];
                numberElements++;
            }
            averageHIangular/=numberElements;
            speeds.push_back((2/((1-averageHIangular)+HImetric[i])));
        }
    }else{
        for(long i=0;i<HImetric.size();i++){
            speeds.push_back((2/((1-HIangular[i])+HImetric[i])));
        }

    }
    return speeds;


}



std::vector<double> DualExtendedGraph::getThresholdsForMetricPercolation(DualExtendedGraph* deg,double definition){
      // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//    std::cout<<"link size "<<deg->getStructuralGraph()->links.size();

    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
//        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
//    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



//    long j=0;
//    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){


            if(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]>0){
              thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
            }
            // acceptedProbabilities.push_back(probabilities[i]);



    }
        thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
        // acceptedProbabilities.push_back(1);








   double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
   double increaseMetric=maxThreshold/definition;
for(long i=0;i<=definition;i++){
    thresholds.push_back(i*increaseMetric);
}

thresholds=Functions::orderValues(thresholds,true);


//    double minThreshold=orderedVectorOfWeights[0];
//    double incrementThreshold=(maxThreshold-minThreshold)/definition;
//
//    for(long i=0;i<definition;i++){
//        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
////        acceptedProbabilities.push_back(<#const_reference __x#>)
//    }



    std::vector<long> colors;
//    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    // HI.resize(deg->getStructuralGraph()->links.size(),0.0);
    // massesGC.reserve(thresholds.size());
//    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    // double prevEntropy=0;
    // bool maxDetected=false;
    // double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

//        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            // massesGC.push_back(massGiantCluster);
             std::unordered_map<long,double> statesSystem;

//             totalSize=0.0;
//            for(long j=0;j<sizes.size();j++){
// //                if(sizes[j]>=2){
//                    totalSize+=sizes[j];
// //                }
//            }
            long totalSizeInClusters=0;
           for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
           }

          if(totalSize-totalSizeInClusters>0){
               statesSystem[0]+=totalSize-totalSizeInClusters;
           }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
//                if(sizes[j]>=2){
                    double probability=(double)it.second/totalSize;
                    entropy-=probability*log(probability);
//                }
            }
//             if(prevEntropy>entropy&&!maxDetected){
//                 maxDetected=true;
// //                for(long j=0;j<HI.size();j++){
// //                    HI[j]=0;
// //                }
// //                sumEntropies=0;
//             }
            // prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy*log(massGiantCluster));
            // sumEntropies+=entropy;
             // std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

//             for(long j=0;j<colors.size();j++){
//                 if(colors[j]!=-1&&massGiantCluster>0){
// //                    if(sizes[colors[j]]>=2){
// //                    if(derivativeGC>0){
//                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
//                     // HI[j]+=log(sizes[colors[j]])*entropy;
// //                    }
// //                    }
//                 }
//             }
//            if(maxDetected&&entropy<.1){
//                break;
//            }


        }else{
            entropies.push_back(0);
        }
    }






//    thresholds.clear();


// std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


// for(long i=0;i<newPs.size();i++){
//     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
//     thresholds.push_back(orderedVectorOfWeights[index]);
// }




thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);

    return thresholds;
}


std::tuple<std::vector<double>,std::vector<double> > DualExtendedGraph::getThresholdsAndEntropyForMetricPercolation(DualExtendedGraph* deg,double definition){
    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    //    long j=0;
    //    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
        // acceptedProbabilities.push_back(probabilities[i]);



    }
    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);








    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    double increaseMetric=maxThreshold/definition;
    for(long i=0;i<=definition;i++){
        thresholds.push_back(i*increaseMetric);
    }

    thresholds=Functions::orderValues(thresholds,true);


    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }



    std::vector<long> colors;
    //    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;

    // HI.resize(deg->getStructuralGraph()->links.size(),0.0);
    // massesGC.reserve(thresholds.size());
    //    averageFiniteMassClusters.reserve(angles.size());
    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    // double prevEntropy=0;
    // bool maxDetected=false;
    // double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            // massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
            }

            if(totalSize-totalSizeInClusters>0){
                statesSystem[0]+=totalSize-totalSizeInClusters;
            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            //             if(prevEntropy>entropy&&!maxDetected){
            //                 maxDetected=true;
            // //                for(long j=0;j<HI.size();j++){
            // //                    HI[j]=0;
            // //                }
            // //                sumEntropies=0;
            //             }
            // prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy*log(massGiantCluster));
            // sumEntropies+=entropy;
            // std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }






    //    thresholds.clear();


    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     thresholds.push_back(orderedVectorOfWeights[index]);
    // }




    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);
//    std::vector<double> entropies;
    entropies.clear();
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);



        if(sizes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
            double massGiantCluster=sizes[indexesOrderClusters[0]];
            // massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizes.size();j++){
                statesSystem[sizes[j]]+=sizes[j];
                totalSizeInClusters+=sizes[j];
            }

            if(totalSize-totalSizeInClusters>0){
                statesSystem[0]+=totalSize-totalSizeInClusters;
            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            //             if(prevEntropy>entropy&&!maxDetected){
            //                 maxDetected=true;
            // //                for(long j=0;j<HI.size();j++){
            // //                    HI[j]=0;
            // //                }
            // //                sumEntropies=0;
            //             }
            // prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy*log(massGiantCluster));
            // sumEntropies+=entropy;
            // std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }


    std::tuple<std::vector<double>,std::vector<double> > result;
    result=std::make_tuple(thresholds,entropies);
    return result;
}




std::tuple<std::vector<double>,std::vector<double> > DualExtendedGraph::getThresholdsAndEntropyForMetricPercolation_UsingMassNodes(DualExtendedGraph* deg,double definition){
    std::vector<double> vectorOfWeights;
    vectorOfWeights.resize(deg->getStructuralGraph()->links.size(),0.0);
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        vectorOfWeights[i]=(deg->getStructuralGraph()->links[i]->weight);
    }
    //        std::cout<<"link size "<<deg->getStructuralGraph()->links.size();
    std::vector<double> orderedVectorOfWeights;
    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(vectorOfWeights, true);
    orderedVectorOfWeights=Functions::orderVectorUsingAnotherVectorWithPositions(vectorOfWeights, orderWeights);



    std::vector<double> massesGC;
    //    std::vector<double> averageFiniteMassClusters;

    std::vector<double> probabilities;
    // std::vector<double> acceptedProbabilities;
    std::vector<double> thresholds;




    double increaseProbability=1.0/definition;


    for(double i=0.0;i<=1.0;i+=increaseProbability){
        probabilities.push_back(i);
    }



    //    long j=0;
    //    double currentProbability=probabilities[j];


    for(long i=0;i<probabilities.size();i++){



        thresholds.push_back(orderedVectorOfWeights[round(probabilities[i]*(double)(orderedVectorOfWeights.size()))]);
        // acceptedProbabilities.push_back(probabilities[i]);



    }
    thresholds.push_back(orderedVectorOfWeights[orderedVectorOfWeights.size()-1]);
    // acceptedProbabilities.push_back(1);








    double maxThreshold=orderedVectorOfWeights[orderedVectorOfWeights.size()-1];
    double increaseMetric=maxThreshold/definition;
    for(long i=0;i<=definition;i++){
        thresholds.push_back(i*increaseMetric);
    }

    thresholds=Functions::orderValues(thresholds,true);


    //    double minThreshold=orderedVectorOfWeights[0];
    //    double incrementThreshold=(maxThreshold-minThreshold)/definition;
    //
    //    for(long i=0;i<definition;i++){
    //        thresholds.push_back(minThreshold+incrementThreshold*(double)i);
    ////        acceptedProbabilities.push_back(<#const_reference __x#>)
    //    }



    std::vector<long> colors;
    //    std::vector<long> colorsNodes;
    std::vector<double> sizes;
    double sumEntropies=0.0;
//    std::vector<double>
//    HI.resize(deg->getPrimalGraph()->links.size(),0.0);
//    massesGC.reserve(thresholds.size());
    //    averageFiniteMassClusters.reserve(angles.size());
    //    double totalSize=(double)(deg->getStructuralGraph()->links.size());
    double totalSize=0;
    double prevEntropy=0;
    bool maxDetected=false;
    double sumDerivatives=0;
    std::vector<double> entropies;
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();
        totalSize=0;

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            //                statesSystem[0]+=totalSize-totalSizeInClusters;
            //            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }





    //    thresholds.clear();


    // std::vector<double> newPs=calculateThresholdFromEntropyDistribution(acceptedProbabilities,entropies);


    // for(long i=0;i<newPs.size();i++){
    //     long index=std::round(newPs[i]*orderedVectorOfWeights.size());
    //     thresholds.push_back(orderedVectorOfWeights[index]);
    // }




    thresholds=calculateThresholdFromEntropyDistribution(thresholds,entropies);

     totalSize=0;
     prevEntropy=0;
     maxDetected=false;
     sumDerivatives=0;
//    std::vector<double> entropies;
    entropies.clear();
    entropies.reserve(thresholds.size());


    for(long i=0;i<thresholds.size();i++){
        double threshold=thresholds[i];

        //        double massGiantCluster=0;
        sizes.clear();
        colors.clear();
        totalSize=0;

        DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
        std::vector<double> sizesUsingMassNodes;
        sizesUsingMassNodes.resize(sizes.size(),0);
        std::vector<bool> nodeAlreadyCounted;
        nodeAlreadyCounted.resize(deg->getStructuralGraph()->nodes.size(),false);
        for(long j=0;j<colors.size();j++){
            if(colors[j]!=-1){
                double massA=deg->getStructuralGraph()->links[j]->A()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]){
                    massA=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->A()->id]=true;
                double massB=deg->getStructuralGraph()->links[j]->B()->mass;
                if(nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]){
                    massB=0;
                }
                nodeAlreadyCounted[deg->getStructuralGraph()->links[j]->B()->id]=true;
                sizesUsingMassNodes[colors[j]]+=massA+massB;
                totalSize+=massA+massB;
            }
        }


        if(sizesUsingMassNodes.size()>0){
            std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizesUsingMassNodes, false);
            double massGiantCluster=sizesUsingMassNodes[indexesOrderClusters[0]];
            massesGC.push_back(massGiantCluster);
            std::unordered_map<long,double> statesSystem;

            //             totalSize=0.0;
            //            for(long j=0;j<sizes.size();j++){
            // //                if(sizes[j]>=2){
            //                    totalSize+=sizes[j];
            // //                }
            //            }
            long totalSizeInClusters=0;
            for(long j=0;j<sizesUsingMassNodes.size();j++){
                statesSystem[sizesUsingMassNodes[j]]+=sizesUsingMassNodes[j];
                totalSizeInClusters+=sizesUsingMassNodes[j];
            }

            //            if(totalSize-totalSizeInClusters>0){
            for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
                if(!nodeAlreadyCounted[j]){
                    statesSystem[0]+=deg->getStructuralGraph()->nodes[j]->mass;
                    totalSize+=deg->getStructuralGraph()->nodes[j]->mass;
                }
            }
            //                statesSystem[0]+=totalSize-totalSizeInClusters;
            //            }

            double entropy=0.0;
            // for(long j=0;j<sizes.size();j++){
            for(auto it:statesSystem){
                //                if(sizes[j]>=2){
                double probability=(double)it.second/totalSize;
                entropy-=probability*log(probability);
                //                }
            }
            if(prevEntropy>entropy&&!maxDetected){
                maxDetected=true;
                //                for(long j=0;j<HI.size();j++){
                //                    HI[j]=0;
                //                }
                //                sumEntropies=0;
            }
            prevEntropy=entropy;
            // sumEntropies+=entropy*log(massGiantCluster);
            entropies.push_back(entropy);
            // sumEntropies+=entropy;
            std::cout<<threshold<<" "<<entropy<<" "<<massGiantCluster<<'\n';

            //             for(long j=0;j<colors.size();j++){
            //                 if(colors[j]!=-1&&massGiantCluster>0){
            // //                    if(sizes[colors[j]]>=2){
            // //                    if(derivativeGC>0){
            //                         HI[j]+=log(sizes[colors[j]])*entropy*log(massGiantCluster);
            //                     // HI[j]+=log(sizes[colors[j]])*entropy;
            // //                    }
            // //                    }
            //                 }
            //             }
            //            if(maxDetected&&entropy<.1){
            //                break;
            //            }


        }else{
            entropies.push_back(0);
        }
    }

    std::tuple<std::vector<double>,std::vector<double> > result;
    result=std::make_tuple(thresholds,entropies);
    return result;
}





void DualExtendedGraph::createHierarchicalTreeMetric(DualExtendedGraph* deg,Grafo* tree,std::vector<double>& thresholds,std::vector<long>& colorsNodesStructuralGraph,std::vector<double>& massesTreeNodes,std::vector<long>& depths,double minMassCluster){
    colorsNodesStructuralGraph.clear();
    colorsNodesStructuralGraph.resize(deg->getPrimalGraph()->nodes.size(),0);
    tree->spatialGraph=false;
    tree->bidirectional=false;
    tree->addNode();
    depths.push_back(0);
    massesTreeNodes.push_back(deg->getPrimalGraph()->links.size());
    long depth=1;

    std::vector<long> colors;
    std::vector<double> sizes;
    if(thresholds.size()==0){
        thresholds=DualExtendedGraph::getThresholdsForMetricPercolation(deg,100);
    }
    double maxThreshold=0;
    for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
        if(deg->getStructuralGraph()->links[i]->weight>maxThreshold){
            maxThreshold=deg->getStructuralGraph()->links[i]->weight;
        }
    }
    thresholds.push_back(maxThreshold);
    // std::vector<long> originalOrderNodes;
    // originalOrderNodes.reserve(deg->getPrimalGraph()->nodes.size());
    // for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    //     originalOrderNodes.push_back(i);
    // }
    // long minClusterNumber=1;//it already has cluster 0
    std::cout<<"Number of thresholds: "<<thresholds.size()<<'\n';


    std::vector<double> finalThresholds;

    for(long j=thresholds.size()-1;j>=0;j--){
      // std::cout<<"threshold in DualExtendedGraph "<<thresholds[j]<<'\n';
        double threshold=thresholds[j];
        // if(threshold>0){

          std::cout<<"Threshold "<<threshold<<", "<<j<<"/"<<thresholds.size()<<'\n';
          sizes.clear();
          colors.clear();
          // std::cout<<"DualExtendedGraph before metricperc"<<'\n';
          DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,threshold, colors, sizes);
          // std::cout<<"DualExtendedGraph::createHierarchicalTreeMetric, size colors "<<colors.size()<<" size sizes "<<sizes.size()<<'\n';
          // std::cout<<"DualExtendedGraph after metricperc"<<'\n';
          // std::unordered_map<long,double> sizesPerColor;
          // for(long i=0;i<colors.size();i++){
          //   sizesPerColor[colors[i]]=sizes[i];
          // }
          std::vector<double> sizesNodes;
          std::vector<long> colorsNodes;
          Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
          // Grafo::transformValuesLinksIntoValuesNodes(deg->getPrimalGraph(),sizes,sizesNodes);
          // std::cout<<"DualExtendedGraph after transformnodes"<<'\n';
          // std::vector<long> orderColors=Functions::getIndexesOfOrderedValues(colorsNodes,true);
          // std::vector<long> orderedNodes=Functions::orderVectorUsingAnotherVectorWithPositions(originalOrderNodes,orderColors);
          // std::vector<long> orderedColors=Functions::orderVectorUsingAnotherVectorWithPositions(colorsNodes,orderColors);
          // std::vector<double> orderedSizes=Functions::orderVectorUsingAnotherVectorWithPositions(sizesNodes,orderColors);
          // std::unordered_map<long,bool> colorAlreadyUsed;

          long numClustersNewLayer=0;
          // std::cout<<"DualExtendedGraph before for loop"<<'\n';
          // long correctionBecauseOfMissingClusters=0;
          long lastColor=-1;
          std::unordered_map<long,Nodo*> nodesPerColor;
          for(long i=0;i<colorsNodes.size();i++){
              // std::cout<<"sizes in DualExtendedGraph "<<sizesPerColor[colorsNodes[i]]<<'\n';
              if(colorsNodes[i]!=-1&&sizes[colorsNodes[i]]>=minMassCluster){
                  if(nodesPerColor[colorsNodes[i]]==NULL){

                    // if(colorsNodes[i]-lastColor!=1){
                    //   correctionBecauseOfMissingClusters+=colorsNodes[i]-lastColor-1;
                    // }
                    // lastColor=colorsNodes[i];
                    // std::cout<<"DualExtendedGraph before addingnode to tree"<<'\n';
                      Nodo* node=tree->addNode();
                      nodesPerColor[colorsNodes[i]]=node;
                      // std::cout<<node->id<<" "<<tree->nodes.size()<<'\n';
                      numClustersNewLayer++;
                      massesTreeNodes.push_back(sizes[colorsNodes[i]]);
                      depths.push_back(depth);
                      // std::cout<<"DualExtendedGraph before adding links to tree"<<'\n';
                      long prevColor=colorsNodesStructuralGraph[i];
                      // std::cout<<"DualExtendedGraph before adding links to tree b"<<'\n';
                      // colorsNodesStructuralGraph[orderedNodes[i]]=colorsNodes[i]+minClusterNumber;
                      Link link;
                      link.setA(tree->nodes[prevColor]);
                      // std::cout<<"DualExtendedGraph before adding links to tree c "<< prevColor <<" "<<minClusterNumber<<" "<<colorsNodes[i]<<" "<<correctionBecauseOfMissingClusters<<" "<<colorsNodes[i]+minClusterNumber<<" "<<tree->nodes.size()<<'\n';
                      // link.setB(tree->nodes[colorsNodes[i]-correctionBecauseOfMissingClusters+minClusterNumber]);
                      link.setB(node);
                      // std::cout<<"DualExtendedGraph before adding links to tree d "<<'\n';
                      // std::cout<<"DualExtendedGraph before adding links to tree d "<<colorsNodes[i]+minClusterNumber]<<" "<<link.A()->id<<" "<<link.B()->id<<'\n';
                      link.weight=1;
                      tree->addLink(link);
                      // std::cout<<"DualExtendedGraph after adding links to tree"<<'\n';
                  }
                  // long prevColor=colorsNodesStructuralGraph[orderedNodes[i]];
                  colorsNodesStructuralGraph[i]=nodesPerColor[colorsNodes[i]]->id;
                  // std::cout<<"DualExtendedGraph after setting nodes"<<'\n';
                  // Link link;
                  // link.setA(tree->nodes[prevColor]);
                  // link.setB(tree->nodes[colorsNodes[i]+minClusterNumber]);
                  // link.weight=1;
                  // tree->addLink(link);
              }

          }
          if(numClustersNewLayer>0){
            // std::cout<<"DualExtendedGraph before final calculations"<<'\n';
            // minClusterNumber+=numClustersNewLayer;
            finalThresholds.push_back(threshold);
            depth++;

          }
          nodesPerColor.clear();
        // }
    }

    // DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
    // // std::vector<long> colorsNodes;
    // Grafo::transformColorsLinksIntoColorsNodes(deg->getStructuralGraph(),colors,colorsNodesStructuralGraph);


    // finalThresholds=Functions::orderValues(finalThresholds,false);
    // finalThresholds.push_back(maxThreshold);
    std::swap(finalThresholds,thresholds);
    // thresholds=Functions::orderValues(thresholds,false);


}



// previous version that works a bit slow and in some cases crashes, but I keep it just in case i cannot do better
// void DualExtendedGraph::createHierarchicalTreeMetric(DualExtendedGraph* deg,Grafo* tree,std::vector<double>& thresholds,std::vector<long>& colorsNodesStructuralGraph,std::vector<double>& massesTreeNodes,std::vector<long>& depths,double minMassCluster){
//     colorsNodesStructuralGraph.clear();
//     colorsNodesStructuralGraph.resize(deg->getPrimalGraph()->nodes.size(),0);
//     tree->spatialGraph=false;
//     tree->bidirectional=false;
//     tree->addNode();
//     depths.push_back(0);
//     massesTreeNodes.push_back(deg->getPrimalGraph()->links.size());
//     long depth=1;
//
//     std::vector<long> colors;
//     std::vector<double> sizes;
//     if(thresholds.size()==0){
//         thresholds=DualExtendedGraph::getThresholdsForMetricPercolation(deg,100);
//     }
//     double maxThreshold=0;
//     for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
//         if(deg->getPrimalGraph()->links[i]->weight>maxThreshold){
//             maxThreshold=deg->getPrimalGraph()->links[i]->weight;
//         }
//     }
//     thresholds.push_back(maxThreshold);
//     std::vector<long> originalOrderNodes;
//     originalOrderNodes.reserve(deg->getPrimalGraph()->nodes.size());
//     for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
//         originalOrderNodes.push_back(i);
//     }
//     long minClusterNumber=1;//it already has cluster 0
//     std::cout<<"Number of thresholds: "<<thresholds.size()<<'\n';
//
//
//     std::vector<double> finalThresholds;
//
//     for(long j=thresholds.size()-2;j>=0;j--){
//       // std::cout<<"threshold in DualExtendedGraph "<<thresholds[j]<<'\n';
//         double threshold=thresholds[j];
//         // if(threshold>0){
//
//           std::cout<<"Threshold "<<threshold<<", "<<j<<"/"<<thresholds.size()<<'\n';
//           sizes.clear();
//           colors.clear();
//           // std::cout<<"DualExtendedGraph before metricperc"<<'\n';
//           DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,threshold, colors, sizes);
//           // std::cout<<"DualExtendedGraph after metricperc"<<'\n';
//           // std::unordered_map<long,double> sizesPerColor;
//           // for(long i=0;i<colors.size();i++){
//           //   sizesPerColor[colors[i]]=sizes[i];
//           // }
//           std::vector<double> sizesNodes;
//           std::vector<long> colorsNodes;
//           Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
//           Grafo::transformValuesLinksIntoValuesNodes(deg->getPrimalGraph(),sizes,sizesNodes);
//           // std::cout<<"DualExtendedGraph after transformnodes"<<'\n';
//           std::vector<long> orderColors=Functions::getIndexesOfOrderedValues(colorsNodes,true);
//           std::vector<long> orderedNodes=Functions::orderVectorUsingAnotherVectorWithPositions(originalOrderNodes,orderColors);
//           std::vector<long> orderedColors=Functions::orderVectorUsingAnotherVectorWithPositions(colorsNodes,orderColors);
//           std::vector<double> orderedSizes=Functions::orderVectorUsingAnotherVectorWithPositions(sizesNodes,orderColors);
//
//           long numClustersNewLayer=0;
//           // std::cout<<"DualExtendedGraph before for loop"<<'\n';
//           long correctionBecauseOfMissingClusters=0;
//           long lastColor=-1;
//           for(long i=0;i<orderedColors.size();i++){
//               // std::cout<<"sizes in DualExtendedGraph "<<sizesPerColor[orderedColors[i]]<<'\n';
//               if(orderedColors[i]!=-1&&orderedSizes[i]>=minMassCluster){
//                   if(tree->nodes.size()<=orderedColors[i]+minClusterNumber){
//                     if(orderedColors[i]-lastColor!=1){
//                       correctionBecauseOfMissingClusters+=orderedColors[i]-lastColor-1;
//                     }
//                     lastColor=orderedColors[i];
//                     // std::cout<<"DualExtendedGraph before addingnode to tree"<<'\n';
//                       Nodo* node=tree->addNode();
//                       // std::cout<<node->id<<" "<<tree->nodes.size()<<'\n';
//                       numClustersNewLayer++;
//                       massesTreeNodes.push_back(orderedSizes[i]);
//                       depths.push_back(depth);
//                       // std::cout<<"DualExtendedGraph before adding links to tree"<<'\n';
//                       long prevColor=colorsNodesStructuralGraph[orderedNodes[i]];
//                       // std::cout<<"DualExtendedGraph before adding links to tree b"<<'\n';
//                       // colorsNodesStructuralGraph[orderedNodes[i]]=orderedColors[i]+minClusterNumber;
//                       Link link;
//                       link.setA(tree->nodes[prevColor]);
//                       // std::cout<<"DualExtendedGraph before adding links to tree c "<< prevColor <<" "<<minClusterNumber<<" "<<orderedColors[i]<<" "<<correctionBecauseOfMissingClusters<<" "<<orderedColors[i]+minClusterNumber<<" "<<tree->nodes.size()<<'\n';
//                       link.setB(tree->nodes[orderedColors[i]-correctionBecauseOfMissingClusters+minClusterNumber]);
//                       // std::cout<<"DualExtendedGraph before adding links to tree d "<<'\n';
//                       // std::cout<<"DualExtendedGraph before adding links to tree d "<<orderedColors[i]+minClusterNumber]<<" "<<link.A()->id<<" "<<link.B()->id<<'\n';
//                       link.weight=1;
//                       tree->addLink(link);
//                       // std::cout<<"DualExtendedGraph after adding links to tree"<<'\n';
//                   }
//                   // long prevColor=colorsNodesStructuralGraph[orderedNodes[i]];
//                   colorsNodesStructuralGraph[orderedNodes[i]]=orderedColors[i]-correctionBecauseOfMissingClusters+minClusterNumber;
//                   // std::cout<<"DualExtendedGraph after setting nodes"<<'\n';
//                   // Link link;
//                   // link.setA(tree->nodes[prevColor]);
//                   // link.setB(tree->nodes[orderedColors[i]+minClusterNumber]);
//                   // link.weight=1;
//                   // tree->addLink(link);
//               }
//
//           }
//           if(numClustersNewLayer>0){
//             // std::cout<<"DualExtendedGraph before final calculations"<<'\n';
//             minClusterNumber+=numClustersNewLayer;
//             finalThresholds.push_back(threshold);
//             depth++;
//           }
//         // }
//     }
//
//     // DualExtendedGraph::metricPercolation(deg,threshold, colors, sizes);
//     // // std::vector<long> colorsNodes;
//     // Grafo::transformColorsLinksIntoColorsNodes(deg->getStructuralGraph(),colors,colorsNodesStructuralGraph);
//
//
//     // finalThresholds=Functions::orderValues(finalThresholds,false);
//     // finalThresholds.push_back(maxThreshold);
//     std::swap(finalThresholds,thresholds);
//     // thresholds=Functions::orderValues(thresholds,false);
//
//
// }
//
//



void DualExtendedGraph::removeLoopsOfDualInPrimal(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    // Grafo* primal=deg->getPrimalGraph();
    std::set<long> idsLinks;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()->id==dual->links[i]->B()->id){
            idsLinks.insert(dual->links[i]->id);
        }
    }
    // deg->getDualGraph()->removeLinks(idsLinks);
    deg->getPrimalGraph()->removeLinks(idsLinks);
    deg->softReset();
    // if(deg->dualGraphConstructed){
    //         deg->getDualGraph()->reset();
    //     }
    //     deg->dualGraphConstructed=false;
    //     if(deg->lineGraphConstructed){
    //         deg->getLineGraph()->reset();
    //     }
    //     deg->lineGraphConstructed=false;
    //     if(deg->structuralGraphConstructed){
    //         deg->getStructuralGraph()->reset();
    //     }
    //     deg->structuralGraphConstructed=false;
    //     if(deg->isPlanarGraphConstructed){
    //         deg->getPlanarGraph()->reset();
    //     }
    //     deg->isPlanarGraphConstructed=false;
    //     if(deg->dualPlanarGraphConstructed){
    //         deg->getDualPlanarGraph()->reset();
    //     }
    //     deg->dualPlanarGraphConstructed=false;
}




std::vector<double> DualExtendedGraph::calculateCoefficientsAngularDeviationPerMetricLengthForAllRegions(DualExtendedGraph* deg){
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // Grafo* lineGraph=deg->getLineGraph();
    // DualExtendedGraph degT;
    std::vector<double> values;
    values.reserve(dual->nodes.size());
    for(long i=0;i<dual->nodes.size();i++){
        std::set<long> idLinks;
        double tsl=0;
        for(long j=0;j<dual->nodes[i]->links.size();j++){
            idLinks.insert(dual->nodes[i]->links[j]->id);
            tsl+=primal->links[dual->nodes[i]->links[j]->id]->weight;
        }
        double radius=tsl/(2*M_PI);
        Grafo region;
        Grafo::inducedSubgraphFromLinks(primal,&region,idLinks);
        DualExtendedGraph degRegion;
        DualExtendedGraph::addPrimal(&degRegion,&region);
        std::vector<double> angularWeights=DualExtendedGraph::getAngularWeightsLineGraph(&degRegion);
        double averageValue=0;
        for(long j=0;j<degRegion.getLineGraph()->links.size();j++){
            averageValue+=angularWeights[j]/degRegion.getLineGraph()->links[j]->weight*radius;
        }
        averageValue/=(double)(degRegion.getLineGraph()->links.size());
        values.push_back(averageValue);

    }
    return values;


}


void DualExtendedGraph::detectRoundabouts(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel){
    DualExtendedGraph::detectRoundabouts(deg,idsRoundaboutsAtNodesPrimalLevel,0,70,100,false,0,200);

}


// void DualExtendedGraph::detectRoundabouts(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,double minAngle, double maxAngle, double maxDistance,bool useSegmentDistance,double minCoef,double maxCoef){
//     DualExtendedGraph::removeTempObjects(deg);
//     // DualExtendedGraph::simplify(deg);
//     // std::swap(deg->getPrimalGraph(),deg->getPlanarGraph());
// //    std::vector<long> idsNodesRoundabouts;
//     // std::vector<long> idsLinksRoundabouts;
//     idsRoundaboutsAtNodesPrimalLevel.clear();
//     idsRoundaboutsAtNodesPrimalLevel.resize(deg->getPrimalGraph()->nodes.size(),-1);
//     // idsLinksRoundabouts.resize(deg->getPrimalGraph()->links.size(),-1);

//     std::vector<long> colorsMetric_150;
//     std::vector<double> sizesMetric_150;
//     std::vector<long> colorsAngular_05;
//     std::vector<double> sizesAngular_05;
//     std::vector<long> colorsAngular_65;
//     std::vector<double> sizesAngular_65;

//     // double maxAngle=85;
//     if(useSegmentDistance){
//         DualExtendedGraph::setPrimalAsStructuralGraph(deg);
//     }
//     DualExtendedGraph::angularPercolation(deg,minAngle,colorsAngular_05,sizesAngular_05);
//     DualExtendedGraph::angularPercolation(deg,maxAngle,colorsAngular_65,sizesAngular_65);
//     DualExtendedGraph::metricPercolation(deg,maxDistance,colorsMetric_150,sizesMetric_150);



//     std::vector<long> colorNodes_65;
//     std::vector<long> colorNodes_05;

//     Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colorsAngular_65, colorNodes_65);
//     Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colorsAngular_05, colorNodes_05);

//     std::cout<<"sizes of the percolations "<<colorsAngular_65.size()<<" "<<colorNodes_05.size()<<" "<<colorNodes_65.size()<<" "<<colorsMetric_150.size()<<'\n';

//     std::set<long> idLinksAccepted;
//     for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
//         if(colorNodes_65[i]!=-1&&colorNodes_05[i]==-1&&colorsMetric_150[i]!=-1){
//             idLinksAccepted.insert(deg->getPrimalGraph()->links[i]->id);
//         }
//     }
//     // std::cout<<"size links accepted "<<idLinksAccepted.size()<<'\n';
//     Grafo G;


//     Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&G,idLinksAccepted);


//     // std::cout<<"number nodes initial "<<deg->getPrimalGraph()->nodes.size()<<'\n';
//     // std::cout<<"number links initial "<<deg->getPrimalGraph()->links.size()<<'\n';
//     double angleToBreak=maxAngle+15;
//     Grafo::breakAcuteAnglesNodesDegree2(&G,angleToBreak);
//     // std::cout<<"number nodes initial "<<G.nodes.size()<<'\n';
//     // std::cout<<"number links initial "<<G.links.size()<<'\n';
//     Grafo burnedGraph;
//     Grafo::burnGraph(&G,&burnedGraph);
//     bool STOP=false;
//     long previousNumberNodes=burnedGraph.nodes.size();
//     long previousNumberLinks=burnedGraph.links.size();
//     // std::cout<<"number nodes initial "<<previousNumberNodes<<'\n';
//     // std::cout<<"number links initial "<<previousNumberLinks<<'\n';
//     // Grafo burnedGraph2;





//     while(!STOP){
//         DualExtendedGraph degT;
//         degT.reset();

//         DualExtendedGraph::addPrimal(&degT,&burnedGraph);

// //        colorsMetric_150.clear();
// //        sizesMetric_150.clear();
// ////        colorsAngular_05.clear();
// ////        sizesAngular_05.clear();
// //        colorsAngular_65.clear();
// //        sizesAngular_65.clear();
// //
// //        DualExtendedGraph::setPrimalAsStructuralGraph(&degT);
// //
// ////        DualExtendedGraph::angularPercolation(&degT,.5,colorsAngular_05,sizesAngular_05);
// //        DualExtendedGraph::angularPercolation(&degT,65,colorsAngular_65,sizesAngular_65);
// //        DualExtendedGraph::metricPercolation(&degT,150,colorsMetric_150,sizesMetric_150);
// //
// //        idLinksAccepted.clear();
// //
// //        Grafo G2;
// //        for(long i=0;i<degT.getPrimalGraph()->links.size();i++){
// //            if(colorsAngular_65[i]!=-1&&colorsMetric_150[i]!=-1){
// //                idLinksAccepted.insert(degT.getPrimalGraph()->links[i]->id);
// //            }
// //        }
// //        std::cout<<"size links accepted "<<idLinksAccepted.size()<<'\n';
// //        Grafo::inducedSubgraphFromLinks(degT.getPrimalGraph(),&G2,idLinksAccepted);

//         Grafo::breakAcuteAnglesNodesDegree2(degT.getPrimalGraph(),angleToBreak);
//         burnedGraph.reset();
//         // Grafo burnedGraph;
//         Grafo::burnGraph(degT.getPrimalGraph(),&burnedGraph);
//         if(previousNumberNodes==burnedGraph.nodes.size()&&previousNumberLinks==burnedGraph.links.size()){
//             STOP=true;
//         }else{
//             previousNumberNodes=burnedGraph.nodes.size();
//             previousNumberLinks=burnedGraph.links.size();
//         }
//         // std::cout<<"number nodes "<<previousNumberNodes<<'\n';

//     }
//     DualExtendedGraph degT2;
//     DualExtendedGraph::addPrimal(&degT2,&burnedGraph);
//     DualExtendedGraph::removeLoopsOfDualInPrimal(&degT2);
//     // std::cout<<"number nodes initial "<<degT2.getPrimalGraph()->nodes.size()<<'\n';
//     // std::cout<<"number links initial "<<degT2.getPrimalGraph()->links.size()<<'\n';
//     degT2.getPrimalGraph()->removeNodesDegree0();
//     // std::cout<<"number nodes initial "<<degT2.getPrimalGraph()->nodes.size()<<'\n';
//     // std::cout<<"number links initial "<<degT2.getPrimalGraph()->links.size()<<'\n';
// //    G.reset();
//     Grafo::breakAcuteAnglesNodesDegree2(degT2.getPrimalGraph(),angleToBreak);
//     burnedGraph.reset();
//     // Grafo burnedGraph;
//     Grafo::burnGraph(degT2.getPrimalGraph(),&burnedGraph);
//     degT2.reset();
//     DualExtendedGraph::addPrimal(&degT2,&burnedGraph);
//     std::vector<double> coef;
//     coef=DualExtendedGraph::calculateCoefficientsAngularDeviationPerMetricLengthForAllRegions(&degT2);

//     std::vector<bool> isRoundabout;
//     isRoundabout.resize(degT2.getDualGraph()->nodes.size(),false);
//     std::vector<long> idsRoundabouts;
//     idsRoundabouts.resize(degT2.getDualGraph()->nodes.size(),-1);

//     for(long i=0;i<degT2.getDualGraph()->nodes.size();i++){
//         if(coef[i]>minCoef&&coef[i]<maxCoef){
//             isRoundabout[i]=true;

//         }
//     }
//     long currentId=0;
//     for(long i=0;i<degT2.getDualGraph()->nodes.size();i++){
//         if(isRoundabout[i]){

//             bool separatedRoundabout=false;
//             long tempId=currentId;
//             for(long j=0;j<degT2.getDualGraph()->nodes[i]->links.size();j++){
//                 if(isRoundabout[degT2.getDualGraph()->nodes[i]->links[j]->getOtherNode(degT2.getDualGraph()->nodes[i])->id]){
// //                    std::cout<<"separated roundabout "<<'\n';
//                     separatedRoundabout=true;
//                     tempId=idsRoundabouts[degT2.getDualGraph()->nodes[i]->links[j]->getOtherNode(degT2.getDualGraph()->nodes[i])->id];
//                 }
//             }
//             if(tempId!=-1){
//                 idsRoundabouts[i]=tempId;
//                 if(!separatedRoundabout){
//                     currentId++;
//                 }
//             }else{
//                 idsRoundabouts[i]=currentId;
//                     currentId++;

//             }

//         }
//     }
// //    std::set<Link*> linksToCollapse;
// //    for(long i=0;i<degT2.getDualGraph()->links.size();i++){
// //        if(isRoundabout[degT2.getDualGraph()->links[i]->A()->id]&&isRoundabout[degT2.getDualGraph()->links[i]->B()->id]){
// //            linksToCollapse.insert(degT2.getDualGraph()->links[i]);
// //        }
// //    }
// //    for(auto it:linksToCollapse){
// //        DualExtendedGraph::joinTwoAdjacentNodesOfTheDual(&degT2,)
// //    }
//     // std::swap(deg->getPrimalGraph(),deg->getPlanarGraph());












//     for(long i=0;i<degT2.getDualGraph()->nodes.size();i++){
// //        if(coef[i]>40&&coef[i]<85){
//         if(isRoundabout[i]){
//             for(long j=0;j<degT2.getDualGraph()->nodes[i]->links.size();j++){
//                 Nodo* a=deg->getPrimalGraph()->getNodeByLocation(degT2.getPrimalGraph()->links[degT2.getDualGraph()->nodes[i]->links[j]->id]->A()->location);
//                 Nodo* b=deg->getPrimalGraph()->getNodeByLocation(degT2.getPrimalGraph()->links[degT2.getDualGraph()->nodes[i]->links[j]->id]->B()->location);


//                 idsRoundaboutsAtNodesPrimalLevel[a->id]=idsRoundabouts[i];
//                 idsRoundaboutsAtNodesPrimalLevel[b->id]=idsRoundabouts[i];
//             }
//         }
//     }


//      if(useSegmentDistance){
//         DualExtendedGraph::unSetPrimalAsStructuralGraph(deg);
//     }

// //    return idsNodesRoundabouts;

// }

// void DualExtendedGraph::joinTwoAdjacentNodesOfTheDual(DualExtendedGraph* deg,Link* link){

//     std::set<long> idLinksToRemove;
//     idLinksToRemove.insert(link->id);

//     Nodo* nodeToKeep=link->A();
//     Nodo* nodeToLoose=link->B();

//     for(long i=0;i<nodeToLoose->links.size();i++){
//         if(nodeToLoose->links[i]->A()==nodeToLoose){
//             nodeToLoose->links[i]->setA(nodeToKeep);
//         }
//         if(nodeToLoose->links[i]->B()==nodeToLoose){
//             nodeToLoose->links[i]->setB(nodeToKeep);
//         }
//         if(nodeToLoose->links[i]->A()==nodeToLoose->links[i]->B()){
//             idLinksToRemove.insert(nodeToLoose->links[i]->id);
//         }
//     }
//     deg->getDualGraph()->removeLinks(idLinksToRemove);
//     deg->getPrimalGraph()->removeLinks(idLinksToRemove);



// }

void DualExtendedGraph::detectRoundabouts(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,double minAngle, double maxAngle, double maxDistance,bool useSegmentDistance,double minCoef,double maxCoef){
    std::cout<<"Detecting roundabouts"<<'\n';
    DualExtendedGraph::removeTempObjects(deg);
    // DualExtendedGraph::simplify(deg);

    idsRoundaboutsAtNodesPrimalLevel.clear();
    idsRoundaboutsAtNodesPrimalLevel.resize(deg->getPrimalGraph()->nodes.size(),-1);


    std::vector<long> colorsMetric_150;
    std::vector<double> sizesMetric_150;
    // std::vector<long> colorsAngular_05;
    // std::vector<double> sizesAngular_05;
    std::vector<long> colorsAngular_65;
    std::vector<double> sizesAngular_65;


    if(useSegmentDistance){
        DualExtendedGraph::setPrimalAsStructuralGraph(deg);
    }
    // DualExtendedGraph::angularPercolation(deg,minAngle,colorsAngular_05,sizesAngular_05);
    DualExtendedGraph::angularPercolation(deg,maxAngle,colorsAngular_65,sizesAngular_65);
    DualExtendedGraph::metricPercolation(deg,maxDistance,colorsMetric_150,sizesMetric_150);



    std::vector<long> colorNodes_65;
    // std::vector<long> colorNodes_05;

    Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colorsAngular_65, colorNodes_65);
    // Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colorsAngular_05, colorNodes_05);

    // std::cout<<"sizes of the percolations "<<colorsAngular_65.size()<<" "<<colorNodes_05.size()<<" "<<colorNodes_65.size()<<" "<<colorsMetric_150.size()<<'\n';

    std::set<long> idLinksAccepted;

    // idLinksThatAreContinuousAndLoop.resize(deg->getPrimalGraph()->links.size(),true);


    for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
        // if(colorNodes_65[i]!=-1&&colorNodes_05[i]==-1&&colorsMetric_150[i]!=-1){
        if(colorNodes_65[i]!=-1&&colorsMetric_150[i]!=-1){
            idLinksAccepted.insert(deg->getPrimalGraph()->links[i]->id);
        }
    }

    Grafo Gtemp;


    Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&Gtemp,idLinksAccepted);


    std::vector<bool> idLinksThatAreContinuousAndLoop;
    Grafo::continuityAnglesAndLengthAndLoop(&Gtemp,200,idLinksThatAreContinuousAndLoop);
    idLinksAccepted.clear();
     for(long i=0;i<Gtemp.links.size();i++){
        if(idLinksThatAreContinuousAndLoop[Gtemp.links[i]->id]){
            idLinksAccepted.insert(Gtemp.links[i]->id);
        }
    }

    Grafo G;
    Grafo::inducedSubgraphFromLinks(&Gtemp,&G,idLinksAccepted);
    // Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&G,idLinksAccepted);




    double angleToBreak=maxAngle+.01;
    Grafo::breakAcuteAnglesNodesDegree2(&G,angleToBreak);

    // Grafo burnedGraph;
    Grafo::burnGraph(&G);
    DualExtendedGraph degT2;

    DualExtendedGraph::addPrimal(&degT2,&G);
    setPrimalAsStructuralGraph(&degT2);
    DualExtendedGraph::removeLoopsOfDualInPrimal(&degT2);
    G.reset();
    Grafo::burnGraph(degT2.getPrimalGraph(),&G);
    // degT2.reset();
    // setPrimalAsStructuralGraph(&degT2);
    // DualExtendedGraph::addPrimal(&degT2,&burnedGraph);




    // G.reset();
    // G.copyGraph(&burnedGraph);
    // G.removeNodesDegree0();


    bool STOP=false;
    long previousNumberNodes=G.nodes.size();
    long previousNumberLinks=G.links.size();






    while(!STOP){
    //     DualExtendedGraph degT;
    //     degT.reset();

    //     DualExtendedGraph::addPrimal(&degT,&burnedGraph);

            // G.reset();
    // G.copyGraph(&burnedGraph);

        Grafo::breakAcuteAnglesNodesDegree2(&G,angleToBreak);
        // burnedGraph.reset();

        Grafo::burnGraph(&G);
        if(previousNumberNodes==G.nodes.size()&&previousNumberLinks==G.links.size()){
            STOP=true;
        }else{
            previousNumberNodes=G.nodes.size();
            previousNumberLinks=G.links.size();
        }


    }
    degT2.reset();
    setPrimalAsStructuralGraph(&degT2);
    DualExtendedGraph::addPrimal(&degT2,&G);









    // DualExtendedGraph degT2;
    // DualExtendedGraph::addPrimal(&degT2,&burnedGraph);
    // DualExtendedGraph::removeLoopsOfDualInPrimal(&degT2);

    // degT2.getPrimalGraph()->removeNodesDegree0();

    // Grafo::breakAcuteAnglesNodesDegree2(degT2.getPrimalGraph(),angleToBreak);
    // burnedGraph.reset();

    // Grafo::burnGraph(degT2.getPrimalGraph(),&burnedGraph);
    // degT2.reset();
    // DualExtendedGraph::addPrimal(&degT2,&burnedGraph);




    // std::vector<double> coef;
    // coef=DualExtendedGraph::calculateCoefficientsAngularDeviationPerMetricLengthForAllRegions(&degT2);

    // std::vector<bool> isRoundabout;
    // isRoundabout.resize(degT2.getDualGraph()->nodes.size(),false);
    // std::vector<long> idsRoundabouts;
    // idsRoundabouts.resize(degT2.getDualGraph()->nodes.size(),-1);

    // for(long i=0;i<degT2.getDualGraph()->nodes.size();i++){
    //     if(coef[i]>minCoef&&coef[i]<maxCoef){
    //         isRoundabout[i]=true;
    //     }
    // }
    // long currentId=0;
    // for(long i=0;i<degT2.getDualGraph()->nodes.size();i++){
    //     if(isRoundabout[i]){

    //         bool separatedRoundabout=false;
    //         long tempId=currentId;
    //         for(long j=0;j<degT2.getDualGraph()->nodes[i]->links.size();j++){
    //             if(isRoundabout[degT2.getDualGraph()->nodes[i]->links[j]->getOtherNode(degT2.getDualGraph()->nodes[i])->id]){

    //                 separatedRoundabout=true;
    //                 tempId=idsRoundabouts[degT2.getDualGraph()->nodes[i]->links[j]->getOtherNode(degT2.getDualGraph()->nodes[i])->id];
    //             }
    //         }
    //         if(tempId!=-1){
    //             idsRoundabouts[i]=tempId;
    //             if(!separatedRoundabout){
    //                 currentId++;
    //             }
    //         }else{
    //             idsRoundabouts[i]=currentId;
    //                 currentId++;

    //         }

    //     }
    // }


    // for(long i=0;i<degT2.getDualGraph()->nodes.size();i++){

    //     if(isRoundabout[i]){
    //         for(long j=0;j<degT2.getDualGraph()->nodes[i]->links.size();j++){
    //             Nodo* a=deg->getPrimalGraph()->getNodeByLocation(degT2.getPrimalGraph()->links[degT2.getDualGraph()->nodes[i]->links[j]->id]->A()->location);
    //             Nodo* b=deg->getPrimalGraph()->getNodeByLocation(degT2.getPrimalGraph()->links[degT2.getDualGraph()->nodes[i]->links[j]->id]->B()->location);


    //             idsRoundaboutsAtNodesPrimalLevel[a->id]=idsRoundabouts[i];
    //             idsRoundaboutsAtNodesPrimalLevel[b->id]=idsRoundabouts[i];
    //         }
    //     }
    // }


    //  if(useSegmentDistance){
    //     DualExtendedGraph::unSetPrimalAsStructuralGraph(deg);
    // }

    colorsMetric_150.clear();
    sizesMetric_150.clear();
    // DualExtendedGraph::setPrimalAsStructuralGraph(&degT2);
    DualExtendedGraph::metricPercolation(&degT2,INFINITY,colorsMetric_150,sizesMetric_150);

    for(long i=0;i<degT2.getPrimalGraph()->links.size();i++){
        Nodo* node=deg->getPrimalGraph()->getNodeByLocation(degT2.getPrimalGraph()->links[i]->A()->location);
        idsRoundaboutsAtNodesPrimalLevel[node->id]=colorsMetric_150[i];
        node=deg->getPrimalGraph()->getNodeByLocation(degT2.getPrimalGraph()->links[i]->B()->location);
        idsRoundaboutsAtNodesPrimalLevel[node->id]=colorsMetric_150[i];
    }


    // for(long i=0;i<G.nodes.size();i++){
    //     Nodo* node=deg->getPrimalGraph()->getNodeByLocation(G.nodes[i]->location);
    //     idsRoundaboutsAtNodesPrimalLevel[node->id]=0;
    // }


}

// void DualExtendedGraph::joinTwoAdjacentNodesOfTheDual(DualExtendedGraph* deg,Link* link){

//     std::set<long> idLinksToRemove;
//     idLinksToRemove.insert(link->id);

//     Nodo* nodeToKeep=link->A();
//     Nodo* nodeToLoose=link->B();

//     for(long i=0;i<nodeToLoose->links.size();i++){
//         if(nodeToLoose->links[i]->A()==nodeToLoose){
//             nodeToLoose->links[i]->setA(nodeToKeep);
//         }
//         if(nodeToLoose->links[i]->B()==nodeToLoose){
//             nodeToLoose->links[i]->setB(nodeToKeep);
//         }
//         if(nodeToLoose->links[i]->A()==nodeToLoose->links[i]->B()){
//             idLinksToRemove.insert(nodeToLoose->links[i]->id);
//         }
//     }
//     deg->getDualGraph()->removeLinks(idLinksToRemove);
//     deg->getPrimalGraph()->removeLinks(idLinksToRemove);



// }



void DualExtendedGraph::assignRoundaboutsToMainDualGraph(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,std::vector<long>& idsRoundaboutsAtNodesDualLevel){
    std::cout<<"Assigning roundabout ids to dual graph"<<'\n';
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
//    std::vector<long> idsRoundaboutsAtNodesPrimalLevel=DualExtendedGraph::detectRoundabouts(deg);
    idsRoundaboutsAtNodesDualLevel.clear();
    idsRoundaboutsAtNodesDualLevel.resize(dual->nodes.size(),-1);
    for(long i=1;i<dual->nodes.size();i++){
        bool isRoundabout=true;
        long idRoundabout=-1;

        for(long j=0;j<dual->nodes[i]->links.size();j++){
            Nodo* a=primal->links[dual->nodes[i]->links[j]->id]->A();
            Nodo* b=primal->links[dual->nodes[i]->links[j]->id]->B();
            if(idsRoundaboutsAtNodesPrimalLevel[a->id]==-1||idsRoundaboutsAtNodesPrimalLevel[b->id]==-1){
                isRoundabout=false;
            }
            idRoundabout=idsRoundaboutsAtNodesPrimalLevel[a->id];
        }
        if(dual->nodes[i]->links.size()==0){
            isRoundabout=false;
        }
        if (isRoundabout){
            idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id]=idRoundabout;
        }
    }
//    return idsRoundaboutsAtNodesDualLevel;
}



void DualExtendedGraph::detectEntryPointsToRoundabouts(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,std::vector<long>& idsEntriesToRoundaboutsPrimalLevel){
    std::cout<<"Detecting entry points to roundabouts"<<'\n';
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    std::vector<long> idsRoundaboutsAtNodesDualLevel;
    DualExtendedGraph::assignRoundaboutsToMainDualGraph(deg,idsRoundaboutsAtNodesPrimalLevel,idsRoundaboutsAtNodesDualLevel);
//    std::vector<long> idsEntriesToRoundaboutsDualLevel;
//    idsEntriesToRoundaboutsDualLevel.resize(dual->nodes.size(),-1);

    idsEntriesToRoundaboutsPrimalLevel.clear();
    idsEntriesToRoundaboutsPrimalLevel.resize(primal->nodes.size(),-1);
    for(long i=0;i<dual->nodes.size();i++){
        if(idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id]!=-1){
            for(long j=0;j<dual->nodes[i]->links.size();j++){
                Nodo* adjacentRegion=dual->nodes[i]->links[j]->getOtherNode(dual->nodes[i]);
                bool valid=true;
                int countNodes=0;
                std::set<long> idNodesInRegion;
                for(long k=0;k<adjacentRegion->links.size();k++){
                    idNodesInRegion.insert(primal->links[adjacentRegion->links[k]->id]->A()->id);
                    idNodesInRegion.insert(primal->links[adjacentRegion->links[k]->id]->B()->id);

                }
                DualExtendedGraph shape;
                Grafo G;
                Grafo::inducedSubgraph(primal, &G, idNodesInRegion);
                DualExtendedGraph::addPrimal(&shape, &G);
                DualExtendedGraph::simplify(&shape, 45);
                std::set<Nodo*> nodesInRegion;
                for(long k=0;k<shape.getPrimalGraph()->nodes.size();k++){
                    Nodo* nodeOfPrimal=primal->addNode(shape.getPrimalGraph()->nodes[k]->location);
                    nodesInRegion.insert(nodeOfPrimal);
                }
                long countNodesInRoundabout=0;
                for(auto it:nodesInRegion){
                    if(it->getDegree()>2){
                        countNodes++;
                        if(idsRoundaboutsAtNodesPrimalLevel[it->id]!=-1){
                            countNodesInRoundabout++;
                        }
                    }else if (it->getDegree()==1){
                        valid=false;
                    }
                }
                if(valid&&(countNodes==3)&&countNodesInRoundabout==2){
                    valid=true;
                }else{
                    valid=false;
                }
                if(valid){
//                    idsEntriesToRoundaboutsDualLevel[adjacentRegion->id]=idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id];
                    for(auto it:idNodesInRegion){
                        idsEntriesToRoundaboutsPrimalLevel[it]=idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id];
                    }
                }
            }
        }
    }
//    return idsEntriesToRoundaboutsPrimalLevel;

}

void DualExtendedGraph::detectEntryPointsToRoundabouts(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel){
    std::cout<<"Detecting entry points to roundabouts"<<'\n';
    Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    std::vector<long> idsRoundaboutsAtNodesDualLevel;
    DualExtendedGraph::assignRoundaboutsToMainDualGraph(deg,idsRoundaboutsAtNodesPrimalLevel,idsRoundaboutsAtNodesDualLevel);
//    std::vector<long> idsEntriesToRoundaboutsDualLevel;
//    idsEntriesToRoundaboutsDualLevel.resize(dual->nodes.size(),-1);
 std::vector<long> idsEntriesToRoundaboutsPrimalLevel;
   idsEntriesToRoundaboutsPrimalLevel.clear();
   idsEntriesToRoundaboutsPrimalLevel.resize(primal->nodes.size(),-1);
    for(long i=0;i<dual->nodes.size();i++){
        if(idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id]!=-1){
            for(long j=0;j<dual->nodes[i]->links.size();j++){
                Nodo* adjacentRegion=dual->nodes[i]->links[j]->getOtherNode(dual->nodes[i]);
                bool valid=true;
                int countNodes=0;
                std::set<long> idNodesInRegion;
                for(long k=0;k<adjacentRegion->links.size();k++){
                    idNodesInRegion.insert(primal->links[adjacentRegion->links[k]->id]->A()->id);
                    idNodesInRegion.insert(primal->links[adjacentRegion->links[k]->id]->B()->id);

                }
                DualExtendedGraph shape;
                Grafo G;
                Grafo::inducedSubgraph(primal, &G, idNodesInRegion);
                DualExtendedGraph::addPrimal(&shape, &G);
                DualExtendedGraph::simplify(&shape, 45);
                std::set<Nodo*> nodesInRegion;
                for(long k=0;k<shape.getPrimalGraph()->nodes.size();k++){
                    Nodo* nodeOfPrimal=primal->addNode(shape.getPrimalGraph()->nodes[k]->location);
                    nodesInRegion.insert(nodeOfPrimal);
                }
                long countNodesInRoundabout=0;
                for(auto it:nodesInRegion){
                    if(it->getDegree()>2){
                        countNodes++;
                        if(idsRoundaboutsAtNodesPrimalLevel[it->id]!=-1){
                            countNodesInRoundabout++;
                        }
                    }else if (it->getDegree()==1){
                        valid=false;
                    }
                }
                if(valid&&(countNodes==3)&&countNodesInRoundabout==2){
                    valid=true;
                }else{
                    valid=false;
                }
                if(valid){
//                    idsEntriesToRoundaboutsDualLevel[adjacentRegion->id]=idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id];
                    for(auto it:idNodesInRegion){
                        idsEntriesToRoundaboutsPrimalLevel[it]=idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id];
                    }
                }
            }
        }
    }

    for(long i=0;i<idsEntriesToRoundaboutsPrimalLevel.size();i++){
        if(idsEntriesToRoundaboutsPrimalLevel[i]!=-1&&idsRoundaboutsAtNodesPrimalLevel[i]==-1){
            idsRoundaboutsAtNodesPrimalLevel[i]=idsEntriesToRoundaboutsPrimalLevel[i];
        }
    }
//    return idsEntriesToRoundaboutsPrimalLevel;

}



void DualExtendedGraph::hyperConnectRoundabouts(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel){
    std::cout<<"Hyper-connecting roundabouts. WARNING, hyperconnecting is not really implemented, it returns the same result as connectRoundaboutToItsCenter"<<'\n';
    DualExtendedGraph::connectRoundaboutToItsCenter(deg,idsRoundaboutsAtNodesPrimalLevel);
}




void DualExtendedGraph::connectRoundaboutToItsCenter(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel){
    std::cout<<"Connecting external points of roundabouts to their centers"<<'\n';
    // Grafo* dual=deg->getDualGraph();
    Grafo* primal=deg->getPrimalGraph();
    // std::vector<long> idsRoundaboutsAtNodesDualLevel;
     // DualExtendedGraph::assignRoundaboutsToMainDualGraph(deg,idsRoundaboutsAtNodesPrimalLevel,idsRoundaboutsAtNodesDualLevel);
//   std::vector<long> idsEntriesToRoundaboutsDualLevel;
//   idsEntriesToRoundaboutsDualLevel.resize(dual->nodes.size(),-1);

//   idsEntriesToRoundaboutsPrimalLevel.clear();
//   idsEntriesToRoundaboutsPrimalLevel.resize(primal->nodes.size(),-1);




    // for(long i=0;i<dual->nodes.size();i++){

    //     if(idsRoundaboutsAtNodesDualLevel[dual->nodes[i]->id]!=-1){
    //         std::set<Nodo*> nodesToConnect;
    //         Point2d centroid(0,0);
    //         double num=0;
    //         for(long j=0;j<dual->nodes[i]->links.size();j++){
    //             Nodo* a=primal->links[dual->nodes[i]->links[j]->id]->A();
    //             Nodo* b=primal->links[dual->nodes[i]->links[j]->id]->B();
    //             centroid.x+=a->location.x;
    //             centroid.x+=b->location.x;
    //             centroid.y+=a->location.y;
    //             centroid.y+=b->location.y;
    //             num+=2;
    //             if(a->getDegree()>2){
    //                 nodesToConnect.insert(a);
    //             }
    //             if(b->getDegree()>2){
    //                 nodesToConnect.insert(b);
    //             }
    //         }
    //         centroid.x/=num;
    //         centroid.y/=num;
    //         Nodo* centroidNode=primal->addNode(centroid);
    //         deg->idsTemporaryNodes.insert(centroidNode->id);
    //         for(auto it:nodesToConnect){
    //             // for(auto it2:nodesToConnect){
    //             //     if(it!=it2){
    //                     long idLink1=primal->addLink(it->id,centroidNode->id,Functions::getDistance(it->location,centroidNode->location),"tempLink");
    //                     long idLink2=primal->addLink(centroidNode->id,it->id,Functions::getDistance(it->location,centroidNode->location),"tempLink");
    //                     deg->idsTemporaryLinks.insert(idLink1);
    //                     deg->idsTemporaryLinks.insert(idLink2);
    //             //     }
    //             // }
    //         }
    //     }
    // }
    std::vector<bool> usedNodesById;
    usedNodesById.resize(idsRoundaboutsAtNodesPrimalLevel.size(),false);
    for(long i=0;i<idsRoundaboutsAtNodesPrimalLevel.size();i++){

        if(idsRoundaboutsAtNodesPrimalLevel[i]!=-1){
            std::set<Nodo*> nodesToConnect;
            Point2d centroid(0,0);
             double num=0;
            if(!usedNodesById[i]){
                std::queue<Nodo*> nodesToExpand;


                nodesToExpand.push(primal->nodes[i]);


                while(nodesToExpand.size()>0){
                    Nodo* a=nodesToExpand.front();
                    nodesToExpand.pop();
                    usedNodesById[a->id]=true;
                    // nodesToConnect.insert(a);
                    // Nodo* a=primal->links[dual->nodes[i]->links[j]->id]->A();
                    // Nodo* b=primal->links[dual->nodes[i]->links[j]->id]->B();
                    centroid.x+=a->location.x;
                    // centroid.x+=b->location.x;
                    centroid.y+=a->location.y;
                    // centroid.y+=b->location.y;
                    num++;
                    if(a->getDegree()>2){
                        nodesToConnect.insert(a);
                    }
                    for(long j=0;j<a->links.size();j++){
                        if(!usedNodesById[a->links[j]->getOtherNode(a)->id]&&idsRoundaboutsAtNodesPrimalLevel[a->links[j]->getOtherNode(a)->id]==idsRoundaboutsAtNodesPrimalLevel[i]){
                            nodesToExpand.push(a->links[j]->getOtherNode(a));
                        }
                    }
                }

                // if(b->getDegree()>2){
                //     nodesToConnect.insert(b);
                // }
            }
            if(num>1){
            centroid.x/=num;
            centroid.y/=num;

            bool existsNode=false;
            Nodo* centroidNode=deg->getPrimalGraph()->getNodeByLocation(centroid);
            if(centroidNode!=NULL){
              existsNode=true;
            }
            centroidNode=primal->addNode(centroid);
            if(!existsNode){
              primal->setNodeAsTemp(centroidNode);
            }
            for(auto it:nodesToConnect){

                // for(auto it2:nodesToConnect){
                //     if(it!=it2){
                        long idLink1=primal->addLink(it->id,centroidNode->id,Functions::getDistance(it->location,centroidNode->location),"temp");
                        long idLink2=primal->addLink(centroidNode->id,it->id,Functions::getDistance(it->location,centroidNode->location),"temp");
                        if(idLink1!=-1){
                          primal->setLinkAsTemp(primal->links[idLink1]);
                        }
                        if(idLink2!=-1){
                          primal->setLinkAsTemp(primal->links[idLink2]);
                        }
                //     }
                // }
            }
          }
        }
    }
    deg->softReset();
    deg->roundaboutsRemoved=true;
    // if(deg->dualGraphConstructed){
    //         deg->getDualGraph()->reset();
    //     }
    //     deg->dualGraphConstructed=false;
    //     if(deg->lineGraphConstructed){
    //         deg->getLineGraph()->reset();
    //     }
    //     deg->lineGraphConstructed=false;
    //     if(deg->structuralGraphConstructed){
    //         deg->getStructuralGraph()->reset();
    //     }
    //     deg->structuralGraphConstructed=false;
    //     if(deg->isPlanarGraphConstructed){
    //         deg->getPlanarGraph()->reset();
    //     }
    //     deg->isPlanarGraphConstructed=false;
    //     if(deg->dualPlanarGraphConstructed){
    //         deg->getDualPlanarGraph()->reset();
    //     }
    //     deg->dualPlanarGraphConstructed=false;
}




std::vector<long> DualExtendedGraph::getIdsOfLinksOfPrimalNotTemp(DualExtendedGraph* deg){
    std::vector<long> ids;
    ids.reserve(deg->getPrimalGraph()->links.size()-deg->getPrimalGraph()->sizeOfTempLinks());
    for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
        if(deg->getPrimalGraph()->links[i]->identifier!="temp"){
            ids.push_back(i);
        }
    }
    return ids;
}


void DualExtendedGraph::removeTempObjects(DualExtendedGraph* deg){
    Grafo::removeTemporaryLinks(deg->getPrimalGraph());
    Grafo::removeTemporaryNodes(deg->getPrimalGraph());
    deg->softReset();
    // if(deg->dualGraphConstructed){
    //         deg->getDualGraph()->reset();
    //     }
    //     deg->dualGraphConstructed=false;
    //     if(deg->lineGraphConstructed){
    //         deg->getLineGraph()->reset();
    //     }
    //     deg->lineGraphConstructed=false;
    //     if(deg->structuralGraphConstructed){
    //         deg->getStructuralGraph()->reset();
    //     }
    //     deg->structuralGraphConstructed=false;
    //     if(deg->isPlanarGraphConstructed){
    //         deg->getPlanarGraph()->reset();
    //     }
    //     deg->isPlanarGraphConstructed=false;
    //     if(deg->dualPlanarGraphConstructed){
    //         deg->getDualPlanarGraph()->reset();
    //     }
    //     deg->dualPlanarGraphConstructed=false;
}


void DualExtendedGraph::calculateAngularBetweenness(DualExtendedGraph* deg,double angularLimit,std::vector<double>& betweenness){
    DualExtendedGraph::setAngularWeightsLineGraph(deg);

    Grafo* G=deg->getLineGraph();

    Grafo::calculateBetweenness(G,angularLimit,betweenness);
    DualExtendedGraph::setMetricWeightsLineGraph(deg);



}
void DualExtendedGraph::calculateMetricEdgeBetweenness(DualExtendedGraph* deg,double distanceLimit,std::vector<double>& betweenness){
    // DualExtendedGraph::setAngularWeightsLineGraph(deg);

    Grafo* G=deg->getLineGraph();
    DualExtendedGraph::setMetricWeightsLineGraph(deg);
    Grafo::calculateBetweenness(G,distanceLimit,betweenness);




}



void DualExtendedGraph::collapseRoundabouts(DualExtendedGraph* deg){

    std::vector<long> idsRoundaboutsAtNodesPrimalLevel;
    DualExtendedGraph::detectRoundabouts(deg,idsRoundaboutsAtNodesPrimalLevel);
    Grafo sg;

    Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),&sg,idsRoundaboutsAtNodesPrimalLevel,false);
    deg->reset();
    DualExtendedGraph::addPrimal(deg,&sg);
    deg->roundaboutsRemoved=true;

}

void DualExtendedGraph::setRoundaboutsRemoved(DualExtendedGraph* deg,bool roundaboutsRemoved){
    deg->roundaboutsRemoved=roundaboutsRemoved;
}


void DualExtendedGraph::collapseDoubleLanes(DualExtendedGraph* deg,Grafo* final){

    DualExtendedGraph::simplify(deg);
    DualExtendedGraph::forcePlanarityPrimal(deg,Grafo::PLANARITY_PLANESWEEP);
    Grafo* dual=deg->getDualGraph();
    std::set<long> idLinksToRemoveA;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()==dual->links[i]->B()){
            idLinksToRemoveA.insert(i);
        }
    }
    deg->getPrimalGraph()->removeLinks(idLinksToRemoveA);
    Grafo largestComponent;
    Grafo::getLargestComponent(deg->getPrimalGraph(),&largestComponent);

    deg->reset();
    // deg->softReset();
    DualExtendedGraph::addPrimal(deg,&largestComponent);
    // dual=deg->getDualGraph();

    final->bidirectional=true;

    std::vector<double> HI;
    if(!deg->roundaboutsRemoved){
        DualExtendedGraph::collapseRoundabouts(deg);
    }
    dual=deg->getDualGraph();

    DualExtendedGraph::calculateHierarchicalIndexAngular(deg,100,HI);

    std::vector<double> percentageBlack;
    percentageBlack.resize(dual->nodes.size(),0);
    for(long i=1;i<dual->nodes.size();i++){//I avoid the external node;
        double blackLevel=0;
        for(long j=0;j<dual->nodes[i]->links.size();j++){
            blackLevel+=(pow(HI[dual->nodes[i]->links[j]->id],3)*13+6)*deg->getPrimalGraph()->links[dual->nodes[i]->links[j]->id]->weight;

        }
        percentageBlack[i]=blackLevel/dual->nodes[i]->mass;
    }
    // return percentageBlack;
    double limit=0.8;
    std::vector<long> idLinksInSubgraph;
    // Grafo final;
    std::vector<long> idLinksInSubgraphB;
    std::vector<long> idNodesInSubgraphC;
    Grafo whiteNodes;
    std::set<long> idBlackNodesDual;
    std::unordered_map<long,bool> isBlackByOriginalId;
    for(long i=0;i<dual->links.size();i++){
        //1 border, 2 non affected (white-white), 0 affected (black-black)
        if(dual->links[i]->A()->id==0||dual->links[i]->B()->id==0){
            if(dual->links[i]->A()->id==0&&percentageBlack[dual->links[i]->B()->id]>limit){
                dual->links[i]->weight=1.0;
                idLinksInSubgraph.push_back(i);
                idLinksInSubgraphB.push_back(i);
            //     Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
            // Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
            // final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
            }else if (dual->links[i]->B()->id==0&&percentageBlack[dual->links[i]->A()->id]>limit){
                dual->links[i]->weight=1.0;
                idLinksInSubgraph.push_back(i);
                idLinksInSubgraphB.push_back(i);
            //     Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
            // Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
            // final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
            }else{
                dual->links[i]->weight=2.0;
                Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
                Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
                final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
            }
        }else if(percentageBlack[dual->links[i]->A()->id]>limit&&percentageBlack[dual->links[i]->B()->id]>limit){
            dual->links[i]->weight=0.0;
            idLinksInSubgraph.push_back(i);

        }else if(percentageBlack[dual->links[i]->A()->id]>limit||percentageBlack[dual->links[i]->B()->id]>limit){
            dual->links[i]->weight=1.0;
            idLinksInSubgraph.push_back(i);
            idLinksInSubgraphB.push_back(i);
            // Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
            // Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
            // final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
        }else{
            dual->links[i]->weight=2.0;
            Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
            Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
            final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
        }
        if(percentageBlack[dual->links[i]->A()->id]>limit){
            isBlackByOriginalId[dual->links[i]->A()->originalID]=true;
            idBlackNodesDual.insert(dual->links[i]->A()->id);
            idNodesInSubgraphC.push_back(dual->links[i]->A()->id);
            // idLinksInSubgraphC.push_back(dual->links[i]->B()->id);
        }else{
            isBlackByOriginalId[dual->links[i]->A()->originalID]=false;
            whiteNodes.addNode(dual->links[i]->A()->location);
        }
        if(percentageBlack[dual->links[i]->B()->id]>limit){
            isBlackByOriginalId[dual->links[i]->B()->originalID]=true;
            idBlackNodesDual.insert(dual->links[i]->B()->id);
            idNodesInSubgraphC.push_back(dual->links[i]->B()->id);
            // idLinksInSubgraphC.push_back(dual->links[i]->B()->id);
        }else{
            isBlackByOriginalId[dual->links[i]->B()->originalID]=false;
            whiteNodes.addNode(dual->links[i]->B()->location);
        }
    }
    std::vector<long> initialDegrees;
    initialDegrees.resize(deg->getPrimalGraph()->nodes.size(),0);
    for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
        initialDegrees[i]=deg->getPrimalGraph()->nodes[i]->getDegree();
    }
    Grafo subg;
    Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&subg,idLinksInSubgraph);
    Grafo subgB;
    Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&subgB,idLinksInSubgraphB);



    Grafo subgC;
    Grafo::inducedSubgraph(dual,&subgC,idNodesInSubgraphC);

    DualExtendedGraph::collapseNodesDual(deg,idBlackNodesDual);

    std::set<Nodo*> nodesToReconnect;
    // for(long i=0;i<subgB.nodes.size();i++){
    //     long id=deg->getPrimalGraph()->getNodeByLocation(subgB.nodes[i]->location)->id;
    //     // initialDegrees[id]-=subg.getNodeByLocation(subgB.nodes[i]->location)->getDegree();
    //     if(initialDegrees[id]>0){
    //       nodesToReconnect.push_back(subgB.nodes[i]);
    //     }

    //  }

    // std::vector<long> ids;
    // std::vector<double> xs;
    // std::vector<double> ys;
    // std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(&subgB,20);
   // for(long i=0;i<subgB.links.size();i++){
   //     ids.push_back(ids.size());
   //     xs.push_back((subgB.links[i]->A()->location.x+subgB.links[i]->B()->location.x)/2.0);
   //     ys.push_back((subgB.links[i]->A()->location.y+subgB.links[i]->B()->location.y)/2.0);
   // }
   //  for(long i=0;i<std::get<0>(points).size();i++){
   //      ids.push_back(ids.size());
   //      xs.push_back(std::get<0>(points)[i]);
   //      ys.push_back(std::get<1>(points)[i]);
   //  }
   // for(long i=0;i<nodesToReconnect.size();i++){
   //     ids.push_back(ids.size());
   //     xs.push_back(nodesToReconnect[i]->location.x);
   //     ys.push_back(nodesToReconnect[i]->location.y);
   // }
   // for(long i=0;i<whiteNodes.nodes.size();i++){
   //     ids.push_back(ids.size());
   //     xs.push_back(whiteNodes.nodes[i]->location.x);
   //     ys.push_back(whiteNodes.nodes[i]->location.y);
   // }
     // for(long i=0;i<subgB.nodes.size();i++){
     //     ids.push_back(ids.size());
     //     xs.push_back((subgB.nodes[i]->location.x));
     //     ys.push_back((subgB.nodes[i]->location.y));
     // }


    // DualExtendedGraph degSubgB;
    // DualExtendedGraph::addPrimal(&degSubgB,&subgB);
    // Grafo* dualDegSubgB=degSubgB.getDualGraph();


    // std::vector<bool> blackRegion;
    // blackRegion.resize(dualDegSubgB->nodes.size(),false);
    // for(long i=0;i<dualDegSubgB->nodes[0]->links.size();i++){
    //     blackRegion[dualDegSubgB->nodes[0]->links[i]->getOtherNode(dualDegSubgB->nodes[0])->id]=true;
    // }

    // for(long i=0;i<dualDegSubgB->nodes.size();i++){
    //     std::vector<long> idLinksRegion;
    //     for(long j=0;j<dualDegSubgB->nodes[i]->links.size();j++){
    //         idLinksRegion.push_back(dualDegSubgB->nodes[i]->links[j]->id);
    //     }
    //     Grafo boundary;
    //     Grafo::inducedSubgraphFromLinks(degSubgB.getPrimalGraph(),&boundary,idLinksRegion);
    //     std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(dualDelanuay,&boundary);
    // }




    // Grafo::;

 //    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > result_=Geometry::delaunay(ids,xs,ys);

 //  Grafo delanuay;

 //  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
 //  coordinates=std::make_tuple(ids,xs,ys);
 //  Grafo::create(&delanuay,result_,coordinates,false);
 //  std::vector<long> linksRemoved;
 // Grafo::cleanDuplicatedLinks(&delanuay,1,linksRemoved,false);

 //  DualExtendedGraph degDelanuay;
 //  DualExtendedGraph::addPrimal(&degDelanuay,&delanuay);
 //  Grafo* dualDelanuay=degDelanuay.getDualGraph();









  std::set<long> nodesOfDualInWhiteRegion;
  std::set<long> nodesOfDualInBlackRegion;
    std::set<long> nodesOfDualNotAssigned;
  // std::vector<double> masses;
  // masses.resize(dualDegSubgB->nodes.size(),0);
  // for(long i=0;i<dualDegSubgB->nodes.size();i++){
  //     // if(i>0){
  //     //    nodesOfDualInWhiteRegion.insert(i);
  //     // nodesOfDualNotAssigned.insert(i);
  //     // }
  //   masses[i]=dualDegSubgB->nodes[i]->mass;
  // }



//     for(long i=0;i<dualDelanuay->nodes.size();i++){
//         if(i>0){
// //         nodesOfDualInWhiteRegion.insert(i);
//       nodesOfDualNotAssigned.insert(i);
//       }
//     }

  std::vector<long> idBlackAreaPerNodeDual;

//  idBlackAreaPerNodeDual.resize(dualDelanuay->nodes.size(),-1);
    Grafo finalDebug;

//   // std::vector<long> indexesOrdered=Functions::getIndexesOfOrderedValues(masses,false);
//   for(long i=1;i<deg->getDualGraph()->nodes.size();i++){
//     // long index=indexesOrdered[i];
//     // if(!blackRegion[dualDegSubgB->nodes[i]->id]){
//         std::vector<long> idLinksRegion;
//         for(long j=0;j<deg->getDualGraph()->nodes[i]->links.size();j++){
//             idLinksRegion.push_back(deg->getDualGraph()->nodes[i]->links[j]->id);
//         }
//         Grafo boundary;
//         Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&boundary,idLinksRegion);



//         std::set<long> nodesInPolygonBlack=GeometryGraph::nodesInPolygon(&subgC,&boundary);
//         // final->addNode(dualDegSubgB->nodes[i]->location);
//         if(nodesInPolygonBlack.size()==0){
//             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(dualDelanuay,&boundary);
//             for(auto it:nodesInPolygon){
//                 if(i>0){
//                     nodesOfDualInWhiteRegion.insert(it);
//                 }
//                 idBlackAreaPerNodeDual[it]=-1;
// //                nodesOfDualInBlackRegion.erase(it);
//                 nodesOfDualNotAssigned.erase(it);
//             }
//         }else{
//             for(long j=0;j<boundary.links.size();j++){
//                 Nodo* a=finalDebug.addNode(Point2d(boundary.links[j]->A()->location.x+1000*i,boundary.links[j]->A()->location.y));
//                 Nodo* b=finalDebug.addNode(Point2d(boundary.links[j]->B()->location.x+1000*i,boundary.links[j]->B()->location.y));
//                 finalDebug.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             }

//             // std::cout<<"size black nodes inside "<<nodesInPolygonBlack.size()<<'\n';
//             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(dualDelanuay,&boundary);
//             for(auto it:nodesInPolygon){
// //                nodesOfDualInWhiteRegion.erase(it);
//                 if(i>0){
//                     nodesOfDualInBlackRegion.insert(it);
//                 }
//                 idBlackAreaPerNodeDual[it]=i;
//                 nodesOfDualNotAssigned.erase(it);
//                 // final->addNode(dualDelanuay->nodes[it]->location);
//             }
//         }
//     // }
//   }
  Grafo tempSg;
  tempSg.bidirectional=true;
  for(long k=1;k<deg->getDualGraph()->nodes.size();k++){
    // long index=indexesOrdered[i];
    // if(!blackRegion[dualDegSubgB->nodes[i]->id]){
        std::vector<long> idLinksRegion;
        for(long j=0;j<deg->getDualGraph()->nodes[k]->links.size();j++){
            idLinksRegion.push_back(deg->getDualGraph()->nodes[k]->links[j]->id);
        }
        Grafo boundary;
        Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&boundary,idLinksRegion);



        // std::set<long> nodesInPolygonBlack=GeometryGraph::nodesInPolygon(&subgC,&boundary);
        // final->addNode(dualDegSubgB->nodes[i]->location);
        // if(nodesInPolygonBlack.size()==0){
        if(!isBlackByOriginalId[deg->getDualGraph()->nodes[k]->originalID]){

        }else{
                      std::vector<long> ids;
            std::vector<double> xs;
            std::vector<double> ys;
            std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(&boundary,15);
           // for(long i=0;i<subgB.links.size();i++){
           //     ids.push_back(ids.size());
           //     xs.push_back((subgB.links[i]->A()->location.x+subgB.links[i]->B()->location.x)/2.0);
           //     ys.push_back((subgB.links[i]->A()->location.y+subgB.links[i]->B()->location.y)/2.0);
           // }
            for(long i=0;i<std::get<0>(points).size();i++){
                ids.push_back(ids.size());
                xs.push_back(std::get<0>(points)[i]);
                ys.push_back(std::get<1>(points)[i]);
            }
            std::vector<long> idNodesToReconnect;
           // for(long i=0;i<nodesToReconnect.size();i++){
           //      if(boundary.getNodeByLocation(nodesToReconnect[i]->location)!=NULL){
           //          idNodesToReconnect.push_back(i);
           //         ids.push_back(ids.size());
           //         xs.push_back(nodesToReconnect[i]->location.x);
           //         ys.push_back(nodesToReconnect[i]->location.y);
           //     }
           // }
           // for(long i=0;i<whiteNodes.nodes.size();i++){
           //     ids.push_back(ids.size());
           //     xs.push_back(whiteNodes.nodes[i]->location.x);
           //     ys.push_back(whiteNodes.nodes[i]->location.y);
           // }
             for(long i=0;i<boundary.nodes.size();i++){
                if(deg->getPrimalGraph()->getNodeByLocation(boundary.nodes[i]->location)->getDegree()>2){
                     ids.push_back(ids.size());
                     xs.push_back((boundary.nodes[i]->location.x));
                     ys.push_back((boundary.nodes[i]->location.y));
                 }
             }
               std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > result_=Geometry::delaunay(ids,xs,ys);

              Grafo delanuay;

              std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
              coordinates=std::make_tuple(ids,xs,ys);
              Grafo::create(&delanuay,result_,coordinates,false);
              std::vector<long> linksRemoved;
//             Grafo::cleanDuplicatedLinks(&delanuay,.000001,linksRemoved,false);

              DualExtendedGraph degDelanuay;
              DualExtendedGraph::addPrimal(&degDelanuay,&delanuay);
              Grafo* dualDelanuay=degDelanuay.getDualGraph();

              std::set<long> linksInPolygon=GeometryGraph::nodesInPolygon(degDelanuay.getLineGraph(),&boundary);

              for(long i=0;i<dualDelanuay->links.size();i++){
                if(dualDelanuay->links[i]->A()->id!=0&&dualDelanuay->links[i]->B()->id!=0&&linksInPolygon.count(dualDelanuay->links[i]->id)>0){
                // if(nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->A()->id)>0&&nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->B()->id)>0){
                // if(linksOfDualInBlackRegion.count(dualDelanuay->links[i]->id)>0){
                    Nodo* a=tempSg.addNode(dualDelanuay->links[i]->A()->location);
                    Nodo* b=tempSg.addNode(dualDelanuay->links[i]->B()->location);
                    tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
                }
              }
              for(long i=0;i<boundary.nodes.size();i++){
                // Nodo* delanuayNode=degDelanuay.getPrimalGraph()->getNodeByLocation(nodesToReconnect[idNodesToReconnect[i]]->location);
                if(deg->getPrimalGraph()->getNodeByLocation(boundary.nodes[i]->location)->getDegree()>2){
                    nodesToReconnect.insert(deg->getPrimalGraph()->getNodeByLocation(boundary.nodes[i]->location));
                    Nodo* delanuayNode=degDelanuay.getPrimalGraph()->getNodeByLocation(boundary.nodes[i]->location);
                    double minDis=INFINITY;
                    long index=-1;
                    long AorB=-1;
                    for(long j=0;j<delanuayNode->links.size();j++){
                        long idLink=delanuayNode->links[j]->id;
                        Nodo* nodeTsgA=tempSg.getNodeByLocation(degDelanuay.getDualGraph()->links[idLink]->A()->location);
                        Nodo* nodeTsgB=tempSg.getNodeByLocation(degDelanuay.getDualGraph()->links[idLink]->B()->location);
                        if(nodeTsgA!=NULL&&nodeTsgA->getDegree()>0&&Functions::getDistance(delanuayNode->location,nodeTsgA->location)<minDis){
                            minDis=Functions::getDistance(delanuayNode->location,nodeTsgA->location);
                            index=j;
                            AorB=0;

                        }
                        if(nodeTsgB!=NULL&&nodeTsgB->getDegree()>0&&Functions::getDistance(delanuayNode->location,nodeTsgB->location)<minDis){
                            minDis=Functions::getDistance(delanuayNode->location,nodeTsgB->location);
                            index=j;
                            AorB=1;

                        }

                    }
                    if(index!=-1&&AorB==0){
                        long idLink=delanuayNode->links[index]->id;

                        Nodo* a=tempSg.addNode(delanuayNode->location);
                        Nodo* b=tempSg.getNodeByLocation(degDelanuay.getDualGraph()->links[idLink]->A()->location);
                        tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
                    }else if(index!=-1){
                        long idLink=delanuayNode->links[index]->id;

                        Nodo* a=tempSg.addNode(delanuayNode->location);
                        Nodo* b=tempSg.getNodeByLocation(degDelanuay.getDualGraph()->links[idLink]->B()->location);
                        tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));

                    }
                }

              }
        }
    // }
  }







// std::set<long> linksOfDualInWhiteRegion;
//   std::set<long> linksOfDualInBlackRegion;
//     std::set<long> nodesOfDualNotAssigned;
//   std::vector<double> masses;
//   masses.resize(dualDegSubgB->nodes.size(),0);
//   for(long i=0;i<dualDegSubgB->nodes.size();i++){
//       // if(i>0){
//       //    nodesOfDualInWhiteRegion.insert(i);
//       // nodesOfDualNotAssigned.insert(i);
//       // }
//     masses[i]=dualDegSubgB->nodes[i]->mass;
//   }

//     Grafo nodesRepresentingLinks;
//     for(long i=0;i<dualDelanuay->links.size();i++){
//         Point2d centre;
//         centre.x=(dualDelanuay->links[i]->A()->location.x+dualDelanuay->links[i]->B()->location.x)/2.0;
//         centre.y=(dualDelanuay->links[i]->A()->location.y+dualDelanuay->links[i]->B()->location.y)/2.0;
//         nodesRepresentingLinks.addNode(centre);
//     }

//   std::vector<long> indexesOrdered=Functions::getIndexesOfOrderedValues(masses,false);
//   for(long i=1;i<indexesOrdered.size();i++){
//     long index=indexesOrdered[i];
//     // if(!blackRegion[dualDegSubgB->nodes[i]->id]){
//         std::vector<long> idLinksRegion;
//         for(long j=0;j<dualDegSubgB->nodes[index]->links.size();j++){
//             idLinksRegion.push_back(dualDegSubgB->nodes[index]->links[j]->id);
//         }
//         Grafo boundary;
//         Grafo::inducedSubgraphFromLinks(degSubgB.getPrimalGraph(),&boundary,idLinksRegion);

//         // for(long j=0;j<boundary.links.size();j++){
//         //     Nodo* a=final->addNode(Point2d(boundary.links[j]->A()->location.x+1000*i,boundary.links[j]->A()->location.y));
//         //     Nodo* b=final->addNode(Point2d(boundary.links[j]->B()->location.x+1000*i,boundary.links[j]->B()->location.y));
//         //     final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//         // }

//         std::set<long> nodesInPolygonBlack=GeometryGraph::nodesInPolygon(&subgC,&boundary);
//         // final->addNode(dualDegSubgB->nodes[i]->location);
//         if(nodesInPolygonBlack.size()==0){
//             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(&nodesRepresentingLinks,&boundary);
//             for(auto it:nodesInPolygon){
//                 if(i>0){
//                     linksOfDualInWhiteRegion.insert(it);
//                 }
//                 linksOfDualInBlackRegion.erase(it);
// //                linksOfDualNotAssigned.erase(it);
//             }
//         }else{

//             // std::cout<<"size black nodes inside "<<nodesInPolygonBlack.size()<<'\n';
//             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(&nodesRepresentingLinks,&boundary);
//             for(auto it:nodesInPolygon){
//                 linksOfDualInWhiteRegion.erase(it);
//                 if(i>0){
//                     linksOfDualInBlackRegion.insert(it);
//                 }
// //                linksOfDualNotAssigned.erase(it);
//                 // final->addNode(dualDelanuay->nodes[it]->location);
//             }
//         }
//     // }
//   }










  //   for(auto it:nodesOfDualInBlackRegion){
  //       final->addNode(dualDelanuay->nodes[it]->location);
  //   }
  // for(auto it:nodesOfDualInWhiteRegion){
  //   for(long j=0;j<dualDelanuay->nodes[it]->links.size();j++){
  //       if(dualDelanuay->nodes[it]->links[j]->A()->id==it){
  //         dualDelanuay->nodes[it]->links[j]->setA(dualDelanuay->nodes[0]);
  //       }
  //       if(dualDelanuay->nodes[it]->links[j]->B()->id==it){
  //         dualDelanuay->nodes[it]->links[j]->setB(dualDelanuay->nodes[0]);
  //       }
  //   }
  // }

   // for(auto it:nodesOfDualNotAssigned){
       // nodesOfDualInWhiteRegion.erase(it);
       // nodesOfDualInBlackRegion.insert(it);
   // }




  // for(long i=0;i<dualDelanuay->links.size();i++){
  //   if(nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->A()->id)>0&&nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->B()->id)>0&&idBlackAreaPerNodeDual[dualDelanuay->links[i]->A()->id]==idBlackAreaPerNodeDual[dualDelanuay->links[i]->B()->id]){
  //   // if(nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->A()->id)>0&&nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->B()->id)>0){
  //   // if(linksOfDualInBlackRegion.count(dualDelanuay->links[i]->id)>0){
  //       Nodo* a=tempSg.addNode(dualDelanuay->links[i]->A()->location);
  //       Nodo* b=tempSg.addNode(dualDelanuay->links[i]->B()->location);
  //       tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
  //   }
  // }
  // std::set<long> idNodesToRemove;




//   Grafo lg;
// Grafo::constructLineGraph(&tempSg,&lg);















//   for(long i=0;i<nodesToReconnect.size();i++){
//    Nodo* node=degDelanuay.getPrimalGraph()->getNodeByLocation(nodesToReconnect[i]->location);
//    long index=-1;
// //      long secondIndex=-1;
// //      long AorB2=0;
//    long AorB=0;
//    double minDis=INFINITY;
// //      double minDis2=1INFINITY;
//    std::cout<<"..................."<<'\n';
//    for(long j=0;j<node->links.size();j++){
//
//        if(nodesOfDualInBlackRegion.count(dualDelanuay->links[node->links[j]->id]->A()->id)>0&&Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->A()->location)<minDis){
//        // if(linksOfDualInBlackRegion.count(node->links[j]->id)>0&&Functions::getDistance(node->location,node->links[j]->A()->location)<minDis){
//            minDis=Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->A()->location);
//            //  Nodo* dualNode=dualDelanuay->links[node->links[j]->id]->A();
//            // Nodo* a=final->addNode(node->location);
//            // Nodo* b=final->addNode(dualNode->location);
//            // final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             index=j;
//             AorB=0;
//         }
//        if(nodesOfDualInBlackRegion.count(dualDelanuay->links[node->links[j]->id]->B()->id)>0&&Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->B()->location)<minDis){
//        // if(linksOfDualInBlackRegion.count(node->links[j]->id)>0&&Functions::getDistance(node->location,node->links[j]->B()->location)<minDis){
//             minDis=Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->B()->location);
//            //  Nodo* dualNode=dualDelanuay->links[node->links[j]->id]->B();
//            // Nodo* a=final->addNode(node->location);
//            // Nodo* b=final->addNode(dualNode->location);
//            // final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             index=j;
//             AorB=1;
//         }
//        if(nodesOfDualNotAssigned.count(dualDelanuay->links[node->links[j]->id]->B()->id)>0){
//          std::cout<<"b not assigned"<<'\n';
//        }
//        if(nodesOfDualNotAssigned.count(dualDelanuay->links[node->links[j]->id]->A()->id)>0){
//          std::cout<<"a not assigned"<<'\n';
//        }
// //       if(Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->A()->location)<minDis2){
// //
// //       }
//    }
//    if(AorB==0&&index!=-1){
//      Nodo* dualNode=dualDelanuay->links[node->links[index]->id]->A();
//            Nodo* a=tempSg.addNode(node->location);
//            Nodo* b=tempSg.addNode(dualNode->location);
//            tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//    }else if(AorB==1&&index!=-1){
//      Nodo* dualNode=dualDelanuay->links[node->links[index]->id]->B();
//            Nodo* a=tempSg.addNode(node->location);
//            Nodo* b=tempSg.addNode(dualNode->location);
//            tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//    }else{
//        std::cout<<"wtf?? "<<node<<'\n';
//
//
//    }
//
//
//    // Link* link=node->links[0];
//
//   }















//std::set<long> idNodesToRemove;
// for(long i=0;i<tempSg.links.size();i++){
//   if(tempSg.links[i]->A()->getDegree()>2&&tempSg.links[i]->B()->getDegree()>2){
//       idNodesToRemove.insert(tempSg.links[i]->B()->id);
//       for(long j=0;j<tempSg.links[i]->B()->links.size();j++){
//           if(tempSg.links[i]->B()->links[j]->A()==tempSg.links[i]->B()&&tempSg.links[i]->B()->links[j]->B()!=tempSg.links[i]->A()){
//               tempSg.links[i]->B()->links[j]->setA(tempSg.links[i]->A());
//           }
//           if(tempSg.links[i]->B()->links[j]->B()==tempSg.links[i]->B()&&tempSg.links[i]->B()->links[j]->A()!=tempSg.links[i]->A()){
//               tempSg.links[i]->B()->links[j]->setB(tempSg.links[i]->A());
//           }
//       }
//       tempSg.links[i]->A()->location.x+=tempSg.links[i]->B()->location.x;
//       tempSg.links[i]->A()->location.y+=tempSg.links[i]->B()->location.y;
//       tempSg.links[i]->A()->location.x/=2.0;
//       tempSg.links[i]->A()->location.y/=2.0;
//   }
// }









    std::vector<bool> isNodeToReconnect;
    isNodeToReconnect.resize(tempSg.nodes.size(),false);
    for(auto it:nodesToReconnect){
        Nodo* node=tempSg.getNodeByLocation(it->location);
        if(node!=NULL){
            isNodeToReconnect[node->id]=true;
        }

    }


 // tempSg.removeNodes(idNodesToRemove);



    std::vector<Point2d> centroids;
    centroids.resize(tempSg.nodes.size(),Point2d(0,0));
for(long run=0;run<1;run++){
    for(long i=0;i<tempSg.nodes.size();i++){
        // if(tempSg.nodes[i]->getDegree()<2&&!isNodeToReconnect[i]){
        //     idNodesToRemove.insert(i);
        // }
        Point2d centroid;
        centroid.x=0;
        centroid.y=0;
        double sumDegrees=0.0;
        for(long j=0;j<tempSg.nodes[i]->links.size();j++){
            long degree=tempSg.nodes[i]->links[j]->getOtherNode(tempSg.nodes[i])->getDegree();
            double x=(tempSg.nodes[i]->links[j]->A()->location.x+tempSg.nodes[i]->links[j]->B()->location.x)/2.0;
            double y=(tempSg.nodes[i]->links[j]->A()->location.y+tempSg.nodes[i]->links[j]->B()->location.y)/2.0;
            centroid.x+=(double)(degree)*x;
            centroid.y+=(double)(degree)*y;
            sumDegrees+=degree;
            // centroid.y+=tempSg.nodes[i]->links[j]->getOtherNode(tempSg.nodes[i])->location.y;
        }
        centroid.x/=(double)(sumDegrees);
        centroid.y/=(double)(sumDegrees);
        centroids[i]=centroid;

    }
    for(long i=0;i<tempSg.nodes.size();i++){
        if(!isNodeToReconnect[i]){
            tempSg.nodes[i]->location=centroids[i];
        }
    }
}


  // for(long i=0;i<tempSg.links.size();i++){
  //       Nodo* a=final->addNode(tempSg.links[i]->A()->location);
  //       Nodo* b=final->addNode(tempSg.links[i]->B()->location);
  //       final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
  // }







bool STOP=false;
while(!STOP){
    std::set<long> idLinksToDelete;
    for(long i=0;i<tempSg.links.size();i++){
        if((tempSg.links[i]->A()->getDegree()==1&&!isNodeToReconnect[tempSg.links[i]->A()->id])||(tempSg.links[i]->B()->getDegree()==1&&!isNodeToReconnect[tempSg.links[i]->B()->id])){
            idLinksToDelete.insert(i);
        }
    }
    if(idLinksToDelete.size()==0){
        STOP=true;
    }else{
        tempSg.removeLinks(idLinksToDelete);
    }
}


  Grafo result;
  std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        Grafo::removeNonStructuralNodes(&tempSg, &result, pairsOldNew,false);

// isNodeToReconnect.clear();
// isNodeToReconnect.resize(result.nodes.size(),false);
// for(long i=0;i<nodesToReconnect.size();i++){
//   Nodo* node=result.getNodeByLocation(nodesToReconnect[i]->location);
//   isNodeToReconnect[node->id]=true;

// }





// std::set<long> idLinksToRemoveC;
// for(long i=0;i<result.links.size();i++){
//     if(result.links[i]->A()->getDegree()>2&&result.links[i]->B()->getDegree()>2&&result.links[i]->weight<75){
//         for(long j=0;j<result.links[i]->B()->links.size();j++){
//             if(result.links[i]->B()->links[j]->A()!=result.links[i]->A()&&result.links[i]->B()->links[j]->B()!=result.links[i]->A()){
//                 if(result.links[i]->B()->links[j]->A()==result.links[i]->B()){
//                     result.links[i]->B()->links[j]->setA(result.links[i]->A());
//                     result.links[i]->A()->links.push_back(result.links[i]);
//                 }
//                 if(result.links[i]->B()->links[j]->B()==result.links[i]->B()){
//                     result.links[i]->B()->links[j]->setB(result.links[i]->A());
//                     result.links[i]->B()->links.push_back(result.links[i]);
//                 }
//                 result.links[i]->A()->location.x=(result.links[i]->A()->location.x+result.links[i]->B()->location.x)/2.0;
//                 result.links[i]->A()->location.y=(result.links[i]->A()->location.y+result.links[i]->B()->location.y)/2.0;
//             }else{
//                 idLinksToRemoveC.insert(result.links[i]->id);
//             }
//         }
//     }
// }
// result.removeLinks(idLinksToRemoveC);
// result.removeNodesDegree0();





// for(long i=0;i<result.links.size();i++){
//     if(result.links[i]->A()->getDegree()==1||result.links[i]->B()->getDegree()==1){
//         result.links[i]->weight+=500;
//     }
// }




//         long maxColor;
//         std::vector<long> colorsT;
//         std::vector<double> sizes;
//         Grafo::getLinkColorsFromNetworkPercolation(&result, 50, colorsT, sizes, maxColor);

//         Grafo result2;
// Grafo::createSuperGraphFromClustersFromColorsLinks(&result,&result2,colorsT);

// for(long i=0;i<result.links.size();i++){
//     if(result.links[i]->A()->getDegree()==1||result.links[i]->B()->getDegree()==1){
//         result.links[i]->weight-=500;
//     }
// }







//    isNodeToReconnect.clear();
//     isNodeToReconnect.resize(result2.nodes.size(),false);
//     for(auto it:nodesToReconnect){
//         Nodo* node=result2.getNodeByLocation(it->location);
//         if(node!=NULL){
//             isNodeToReconnect[node->id]=true;
//         }

//     }

//     centroids.clear();
//     centroids.resize(result2.nodes.size(),Point2d(0,0));

// for(long run=0;run<3;run++){
//     for(long i=0;i<result2.nodes.size();i++){
//         Point2d centroid;
//         centroid.x=0;
//         centroid.y=0;
//         double sumDegrees=0.0;
//         for(long j=0;j<result2.nodes[i]->links.size();j++){
//             long degree=result2.nodes[i]->links[j]->getOtherNode(result2.nodes[i])->getDegree();
//             double x=(result2.nodes[i]->links[j]->A()->location.x+result2.nodes[i]->links[j]->B()->location.x)/2.0;
//             double y=(result2.nodes[i]->links[j]->A()->location.y+result2.nodes[i]->links[j]->B()->location.y)/2.0;
//             // double distance=Functions::getDistance(result2.nodes[i]->links[j]->A()->location,result2.nodes[i]->links[j]->B()->location);
//             centroid.x+=(double)(1.0/(result2.nodes[i]->links[j]->weight+1.0))*x;
//             centroid.y+=(double)(1.0/(result2.nodes[i]->links[j]->weight+1.0))*y;
//             sumDegrees+=1.0/(result2.nodes[i]->links[j]->weight+1.0);

//         }
//         centroid.x/=(double)(sumDegrees);
//         centroid.y/=(double)(sumDegrees);
//         centroids[i]=centroid;
//     }
//     for(long i=0;i<result2.nodes.size();i++){
//         if(!isNodeToReconnect[i]){
//             result2.nodes[i]->location=centroids[i];
//         }
//     }
// }
















  // for(long i=0;i<result2.links.size();i++){
  //       Nodo* a=final->addNode(result2.links[i]->A()->location);
  //       Nodo* b=final->addNode(result2.links[i]->B()->location);
  //       final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
  // }
  for(long i=0;i<result.links.size();i++){
        Nodo* a=final->addNode(result.links[i]->A()->location);
        Nodo* b=final->addNode(result.links[i]->B()->location);
        final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
  }













// for(long i=0;i<final->links.size();i++){
//     if(final->links[i]->A()->getDegree()==1||final->links[i]->B()->getDegree()==1){
//         final->links[i]->weight+=500;
//     }
// }




        // long maxColor;
        // std::vector<long> colorsT;
        // std::vector<double> sizes;
        // Grafo::getLinkColorsFromNetworkPercolation(final, 20, colorsT, sizes, maxColor);

Grafo final_;
        // Grafo::createSuperGraphFromClustersFromColorsLinks(final,&final_,colorsT);
 std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
        // if(mode==Grafo::PLANARITY_PLANESWEEP){
            Grafo::forcePlanarityPlaneSweep(final,Grafo::SPEED,pairsOldIdNewIds,false);
            // Grafo::removeNonStructuralNodes(final);
            std::vector<std::pair<std::vector<long>,long> > pairsOldNewB;
        // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
        Grafo::removeNonStructuralNodes(final, &final_, pairsOldNewB,false);
        // Grafo::
        // final->reset();
        // final->copyGraph(&final_);
  final->reset();
        DualExtendedGraph deg3;
        DualExtendedGraph::addPrimal(&deg3,&final_);
        Grafo* dual3=deg3.getDualGraph();
    std::set<long> idLinksToRemoveA3;
    for(long i=0;i<dual3->links.size();i++){
        if(dual3->links[i]->A()==dual3->links[i]->B()){
            idLinksToRemoveA3.insert(i);
        }
    }
    deg3.getPrimalGraph()->removeLinks(idLinksToRemoveA3);
    // Grafo largestComponent3;
    Grafo::getLargestComponent(deg3.getPrimalGraph(),final);
    // Grafo::burnGraph(&largestComponent3,final);




//            final->copyGraph(&finalDebug);


// for(long i=0;i<final->links.size();i++){
//     if(final->links[i]->A()->getDegree()==1||final->links[i]->B()->getDegree()==1){
//         final->links[i]->weight-=500;
//     }
// }



}


// void DualExtendedGraph::collapseDoubleLanesB(DualExtendedGraph* deg,Grafo* final){
// Grafo finalDebug;
//     DualExtendedGraph::simplify(deg);
//     DualExtendedGraph::forcePlanarityPrimal(deg,Grafo::PLANARITY_PLANESWEEP);
//     Grafo* dual=deg->getDualGraph();
//     std::set<long> idLinksToRemoveA;
//     for(long i=0;i<dual->links.size();i++){
//         if(dual->links[i]->A()==dual->links[i]->B()){
//             idLinksToRemoveA.insert(i);
//         }
//     }
//     deg->getPrimalGraph()->removeLinks(idLinksToRemoveA);
//     Grafo largestComponent;
//     Grafo::getLargestComponent(deg->getPrimalGraph(),&largestComponent);

//     deg->reset();
//     // deg->softReset();
//     DualExtendedGraph::addPrimal(deg,&largestComponent);
//     // dual=deg->getDualGraph();

//     final->bidirectional=true;

//     std::vector<double> HI;
//     if(!deg->roundaboutsRemoved){
//         DualExtendedGraph::collapseRoundabouts(deg);
//     }
//     dual=deg->getDualGraph();

//     DualExtendedGraph::calculateHierarchicalIndexAngular(deg,100,HI);

//     std::vector<double> percentageBlack;
//     percentageBlack.resize(dual->nodes.size(),0);
//     for(long i=1;i<dual->nodes.size();i++){//I avoid the external node;
//         double blackLevel=0;
//         for(long j=0;j<dual->nodes[i]->links.size();j++){
//             blackLevel+=(pow(HI[dual->nodes[i]->links[j]->id],2)*13+6)*deg->getPrimalGraph()->links[dual->nodes[i]->links[j]->id]->weight;
//             // blackLevel+=(deg->getPrimalGraph()->links[dual->nodes[i]->links[j]->id]->weight*15);

//         }
//         percentageBlack[i]=blackLevel/dual->nodes[i]->mass;
//     }
//     // return percentageBlack;
//     double limit=1;
//     std::vector<long> idLinksInSubgraph;
//     // Grafo final;
//     std::vector<long> idLinksInSubgraphB;
//     std::vector<long> idNodesInSubgraphC;
//     Grafo whiteNodes;
//     std::set<long> idBlackNodesDual;
//     std::unordered_map<long,bool> isBlackByOriginalId;
//     for(long i=0;i<dual->links.size();i++){
//         //1 border, 2 non affected (white-white), 0 affected (black-black)
//         if(dual->links[i]->A()->id==0||dual->links[i]->B()->id==0){
//             if(dual->links[i]->A()->id==0&&percentageBlack[dual->links[i]->B()->id]>limit){
//                 dual->links[i]->weight=1.0;
//                 idLinksInSubgraph.push_back(i);
//                 idLinksInSubgraphB.push_back(i);
//             //     Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
//             // Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
//             // final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
//             }else if (dual->links[i]->B()->id==0&&percentageBlack[dual->links[i]->A()->id]>limit){
//                 dual->links[i]->weight=1.0;
//                 idLinksInSubgraph.push_back(i);
//                 idLinksInSubgraphB.push_back(i);
//             //     Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
//             // Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
//             // final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
//             }else{
//                 dual->links[i]->weight=2.0;
//                 Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
//                 Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
//                 final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
//             }
//         }else if(percentageBlack[dual->links[i]->A()->id]>limit&&percentageBlack[dual->links[i]->B()->id]>limit){
//             dual->links[i]->weight=0.0;
//             idLinksInSubgraph.push_back(i);

//         }else if(percentageBlack[dual->links[i]->A()->id]>limit||percentageBlack[dual->links[i]->B()->id]>limit){
//             dual->links[i]->weight=1.0;
//             idLinksInSubgraph.push_back(i);
//             idLinksInSubgraphB.push_back(i);
//             // Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
//             // Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
//             // final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
//         }else{
//             dual->links[i]->weight=2.0;
//             Nodo* a=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->A()->location);
//             Nodo* b=final->addNode(deg->getPrimalGraph()->links[dual->links[i]->id]->B()->location);
//             final->addLink(a->id,b->id,deg->getPrimalGraph()->links[dual->links[i]->id]->weight);
//         }
//         if(percentageBlack[dual->links[i]->A()->id]>limit){
//             idBlackNodesDual.insert(dual->links[i]->A()->id);
//             isBlackByOriginalId[dual->links[i]->A()->originalID]=true;

//             idNodesInSubgraphC.push_back(dual->links[i]->A()->id);
//             // idLinksInSubgraphC.push_back(dual->links[i]->B()->id);
//         }else{
//             isBlackByOriginalId[dual->links[i]->A()->originalID]=false;
//             finalDebug.addNode(dual->links[i]->A()->location);
//             whiteNodes.addNode(dual->links[i]->A()->location);
//         }
//         if(percentageBlack[dual->links[i]->B()->id]>limit){
//             isBlackByOriginalId[dual->links[i]->B()->originalID]=true;
//             idBlackNodesDual.insert(dual->links[i]->B()->id);

//             idNodesInSubgraphC.push_back(dual->links[i]->B()->id);
//             // idLinksInSubgraphC.push_back(dual->links[i]->B()->id);
//         }else{
//             isBlackByOriginalId[dual->links[i]->B()->originalID]=false;
//             finalDebug.addNode(dual->links[i]->B()->location);
//             whiteNodes.addNode(dual->links[i]->B()->location);
//         }
//     }
//     std::vector<long> initialDegrees;
//     initialDegrees.resize(deg->getPrimalGraph()->nodes.size(),0);
//     for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
//         initialDegrees[i]=deg->getPrimalGraph()->nodes[i]->getDegree();
//     }
//     Grafo subg;
//     Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&subg,idLinksInSubgraph);
//     Grafo subgB;
//     Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&subgB,idLinksInSubgraphB);



//     Grafo subgC;
//     Grafo::inducedSubgraph(dual,&subgC,idNodesInSubgraphC);

//     DualExtendedGraph::collapseNodesDual(deg,idBlackNodesDual);

//     std::vector<Nodo*> nodesToReconnect;
//     for(long i=0;i<subgB.nodes.size();i++){
//         long id=deg->getPrimalGraph()->getNodeByLocation(subgB.nodes[i]->location)->id;
//         initialDegrees[id]-=subg.getNodeByLocation(subgB.nodes[i]->location)->getDegree();
//         if(initialDegrees[id]>0){
//           nodesToReconnect.push_back(subgB.nodes[i]);
//           // finalDebug.addNode(subgB.nodes[i]->location);
//         }

//     }
//     std::vector<long> ids;
//     std::vector<double> xs;
//     std::vector<double> ys;
//     std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(&subgB,10);
//    // for(long i=0;i<subgB.links.size();i++){
//    //     ids.push_back(ids.size());
//    //     xs.push_back((subgB.links[i]->A()->location.x+subgB.links[i]->B()->location.x)/2.0);
//    //     ys.push_back((subgB.links[i]->A()->location.y+subgB.links[i]->B()->location.y)/2.0);
//    // }
//     for(long i=0;i<std::get<0>(points).size();i++){
//         ids.push_back(ids.size());
//         xs.push_back(std::get<0>(points)[i]);
//         ys.push_back(std::get<1>(points)[i]);
//     }
//    for(long i=0;i<nodesToReconnect.size();i++){
//        ids.push_back(ids.size());
//        xs.push_back(nodesToReconnect[i]->location.x);
//        ys.push_back(nodesToReconnect[i]->location.y);
//    }
//    // for(long i=0;i<whiteNodes.nodes.size();i++){
//    //     ids.push_back(ids.size());
//    //     xs.push_back(whiteNodes.nodes[i]->location.x);
//    //     ys.push_back(whiteNodes.nodes[i]->location.y);
//    // }
//      // for(long i=0;i<subgB.nodes.size();i++){
//      //     ids.push_back(ids.size());
//      //     xs.push_back((subgB.nodes[i]->location.x));
//      //     ys.push_back((subgB.nodes[i]->location.y));
//      // }


//     // DualExtendedGraph degSubgB;
//     // DualExtendedGraph::addPrimal(&degSubgB,&subgB);
//     // Grafo* dualDegSubgB=degSubgB.getDualGraph();


//     // std::vector<bool> blackRegion;
//     // blackRegion.resize(dualDegSubgB->nodes.size(),false);
//     // for(long i=0;i<dualDegSubgB->nodes[0]->links.size();i++){
//     //     blackRegion[dualDegSubgB->nodes[0]->links[i]->getOtherNode(dualDegSubgB->nodes[0])->id]=true;
//     // }

//     // for(long i=0;i<dualDegSubgB->nodes.size();i++){
//     //     std::vector<long> idLinksRegion;
//     //     for(long j=0;j<dualDegSubgB->nodes[i]->links.size();j++){
//     //         idLinksRegion.push_back(dualDegSubgB->nodes[i]->links[j]->id);
//     //     }
//     //     Grafo boundary;
//     //     Grafo::inducedSubgraphFromLinks(degSubgB.getPrimalGraph(),&boundary,idLinksRegion);
//     //     std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(dualDelanuay,&boundary);
//     // }




//     // Grafo::;
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > result_=Geometry::delaunay(ids,xs,ys);

//   Grafo delanuay;

//   std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
//   coordinates=std::make_tuple(ids,xs,ys);
//   Grafo::create(&delanuay,result_,coordinates,false);
//   std::vector<long> linksRemoved;
// //  Grafo::cleanDuplicatedLinks(&delanuay,.00000001,linksRemoved,false);

//   DualExtendedGraph degDelanuay;
//   DualExtendedGraph::addPrimal(&degDelanuay,&delanuay);
//   Grafo* dualDelanuay=degDelanuay.getDualGraph();









//   std::set<long> nodesOfDualInWhiteRegion;
//   std::set<long> nodesOfDualInBlackRegion;
//     std::set<long> nodesOfDualNotAssigned;
//   // std::vector<double> masses;
//   // masses.resize(dualDegSubgB->nodes.size(),0);
//   // for(long i=0;i<dualDegSubgB->nodes.size();i++){
//   //     // if(i>0){
//   //     //    nodesOfDualInWhiteRegion.insert(i);
//   //     // nodesOfDualNotAssigned.insert(i);
//   //     // }
//   //   masses[i]=dualDegSubgB->nodes[i]->mass;
//   // }
//     for(long i=0;i<dualDelanuay->nodes.size();i++){
//         if(i>0){
// //         nodesOfDualInWhiteRegion.insert(i);
//       nodesOfDualNotAssigned.insert(i);
//       }
//     }

//   std::vector<long> idBlackAreaPerNodeDual;

//   idBlackAreaPerNodeDual.resize(dualDelanuay->nodes.size(),-1);


//   // std::vector<long> indexesOrdered=Functions::getIndexesOfOrderedValues(masses,false);
//   for(long i=1;i<deg->getDualGraph()->nodes.size();i++){
//     // long index=indexesOrdered[i];
//     // if(!blackRegion[dualDegSubgB->nodes[i]->id]){
//         std::vector<long> idLinksRegion;
//         for(long j=0;j<deg->getDualGraph()->nodes[i]->links.size();j++){
//             idLinksRegion.push_back(deg->getDualGraph()->nodes[i]->links[j]->id);
//         }
//         Grafo boundary;
//         Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&boundary,idLinksRegion);



//         std::set<long> nodesInPolygonBlack=GeometryGraph::nodesInPolygon(&subgC,&boundary);
//         // final->addNode(dualDegSubgB->nodes[i]->location);
//         // if(nodesInPolygonBlack.size()==0){
//         if(!isBlackByOriginalId[deg->getDualGraph()->nodes[i]->originalID]){
//             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(dualDelanuay,&boundary);
//             for(auto it:nodesInPolygon){
//                 if(i>0){
//                     nodesOfDualInWhiteRegion.insert(it);
//                 }
//                 idBlackAreaPerNodeDual[it]=-1;
// //                nodesOfDualInBlackRegion.erase(it);
//                 nodesOfDualNotAssigned.erase(it);
//             }
//             // for(long j=0;j<boundary.links.size();j++){
//             //     Nodo* a=finalDebug.addNode(Point2d(boundary.links[j]->A()->location.x,boundary.links[j]->A()->location.y));
//             //     Nodo* b=finalDebug.addNode(Point2d(boundary.links[j]->B()->location.x,boundary.links[j]->B()->location.y));
//             //     finalDebug.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             // }
//         }else{
//             for(long j=0;j<boundary.links.size();j++){
//                 Nodo* a=finalDebug.addNode(Point2d(boundary.links[j]->A()->location.x,boundary.links[j]->A()->location.y));
//                 Nodo* b=finalDebug.addNode(Point2d(boundary.links[j]->B()->location.x,boundary.links[j]->B()->location.y));
//                 finalDebug.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             }

//             // std::cout<<"size black nodes inside "<<nodesInPolygonBlack.size()<<'\n';
//             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(dualDelanuay,&boundary);
//             for(auto it:nodesInPolygon){
// //                nodesOfDualInWhiteRegion.erase(it);
//                 if(i>0){
//                     nodesOfDualInBlackRegion.insert(it);
//                     // finalDebug.addNode(dualDelanuay->nodes[it]->location);
//                 }
//                 idBlackAreaPerNodeDual[it]=i;
//                 nodesOfDualNotAssigned.erase(it);
//                 // final->addNode(dualDelanuay->nodes[it]->location);
//             }
//         }
//     // }
//   }









// // std::set<long> linksOfDualInWhiteRegion;
// //   std::set<long> linksOfDualInBlackRegion;
// //     std::set<long> nodesOfDualNotAssigned;
// //   std::vector<double> masses;
// //   masses.resize(dualDegSubgB->nodes.size(),0);
// //   for(long i=0;i<dualDegSubgB->nodes.size();i++){
// //       // if(i>0){
// //       //    nodesOfDualInWhiteRegion.insert(i);
// //       // nodesOfDualNotAssigned.insert(i);
// //       // }
// //     masses[i]=dualDegSubgB->nodes[i]->mass;
// //   }

// //     Grafo nodesRepresentingLinks;
// //     for(long i=0;i<dualDelanuay->links.size();i++){
// //         Point2d centre;
// //         centre.x=(dualDelanuay->links[i]->A()->location.x+dualDelanuay->links[i]->B()->location.x)/2.0;
// //         centre.y=(dualDelanuay->links[i]->A()->location.y+dualDelanuay->links[i]->B()->location.y)/2.0;
// //         nodesRepresentingLinks.addNode(centre);
// //     }

// //   std::vector<long> indexesOrdered=Functions::getIndexesOfOrderedValues(masses,false);
// //   for(long i=1;i<indexesOrdered.size();i++){
// //     long index=indexesOrdered[i];
// //     // if(!blackRegion[dualDegSubgB->nodes[i]->id]){
// //         std::vector<long> idLinksRegion;
// //         for(long j=0;j<dualDegSubgB->nodes[index]->links.size();j++){
// //             idLinksRegion.push_back(dualDegSubgB->nodes[index]->links[j]->id);
// //         }
// //         Grafo boundary;
// //         Grafo::inducedSubgraphFromLinks(degSubgB.getPrimalGraph(),&boundary,idLinksRegion);

// //         // for(long j=0;j<boundary.links.size();j++){
// //         //     Nodo* a=final->addNode(Point2d(boundary.links[j]->A()->location.x+1000*i,boundary.links[j]->A()->location.y));
// //         //     Nodo* b=final->addNode(Point2d(boundary.links[j]->B()->location.x+1000*i,boundary.links[j]->B()->location.y));
// //         //     final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
// //         // }

// //         std::set<long> nodesInPolygonBlack=GeometryGraph::nodesInPolygon(&subgC,&boundary);
// //         // final->addNode(dualDegSubgB->nodes[i]->location);
// //         if(nodesInPolygonBlack.size()==0){
// //             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(&nodesRepresentingLinks,&boundary);
// //             for(auto it:nodesInPolygon){
// //                 if(i>0){
// //                     linksOfDualInWhiteRegion.insert(it);
// //                 }
// //                 linksOfDualInBlackRegion.erase(it);
// // //                linksOfDualNotAssigned.erase(it);
// //             }
// //         }else{

// //             // std::cout<<"size black nodes inside "<<nodesInPolygonBlack.size()<<'\n';
// //             std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(&nodesRepresentingLinks,&boundary);
// //             for(auto it:nodesInPolygon){
// //                 linksOfDualInWhiteRegion.erase(it);
// //                 if(i>0){
// //                     linksOfDualInBlackRegion.insert(it);
// //                 }
// // //                linksOfDualNotAssigned.erase(it);
// //                 // final->addNode(dualDelanuay->nodes[it]->location);
// //             }
// //         }
// //     // }
// //   }










//   //   for(auto it:nodesOfDualInBlackRegion){
//   //       final->addNode(dualDelanuay->nodes[it]->location);
//   //   }
//   // for(auto it:nodesOfDualInWhiteRegion){
//   //   for(long j=0;j<dualDelanuay->nodes[it]->links.size();j++){
//   //       if(dualDelanuay->nodes[it]->links[j]->A()->id==it){
//   //         dualDelanuay->nodes[it]->links[j]->setA(dualDelanuay->nodes[0]);
//   //       }
//   //       if(dualDelanuay->nodes[it]->links[j]->B()->id==it){
//   //         dualDelanuay->nodes[it]->links[j]->setB(dualDelanuay->nodes[0]);
//   //       }
//   //   }
//   // }

//    for(auto it:nodesOfDualNotAssigned){
//        // nodesOfDualInWhiteRegion.erase(it);
//        // nodesOfDualInBlackRegion.insert(it);
//    }


//   Grafo tempSg;
//   tempSg.bidirectional=true;
//   for(long i=0;i<dualDelanuay->links.size();i++){
//     if(nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->A()->id)>0&&nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->B()->id)>0&&idBlackAreaPerNodeDual[dualDelanuay->links[i]->A()->id]==idBlackAreaPerNodeDual[dualDelanuay->links[i]->B()->id]){
//     // if(nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->A()->id)>0&&nodesOfDualInBlackRegion.count(dualDelanuay->links[i]->B()->id)>0){
//     // if(linksOfDualInBlackRegion.count(dualDelanuay->links[i]->id)>0){
//         Nodo* a=tempSg.addNode(dualDelanuay->links[i]->A()->location);
//         Nodo* b=tempSg.addNode(dualDelanuay->links[i]->B()->location);
//         tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     }
//   }
//   // std::set<long> idNodesToRemove;




// //   Grafo lg;
// // Grafo::constructLineGraph(&tempSg,&lg);















//   for(long i=0;i<nodesToReconnect.size();i++){
//    Nodo* node=degDelanuay.getPrimalGraph()->getNodeByLocation(nodesToReconnect[i]->location);
//    long index=-1;
// //      long secondIndex=-1;
// //      long AorB2=0;
//    long AorB=0;
//    double minDis=INFINITY;
// //      double minDis2=1INFINITY;
//    for(long j=0;j<node->links.size();j++){
//        if(nodesOfDualInBlackRegion.count(dualDelanuay->links[node->links[j]->id]->A()->id)>0&&Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->A()->location)<minDis){
//        // if(linksOfDualInBlackRegion.count(node->links[j]->id)>0&&Functions::getDistance(node->location,node->links[j]->A()->location)<minDis){
//            minDis=Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->A()->location);
//            //  Nodo* dualNode=dualDelanuay->links[node->links[j]->id]->A();
//            // Nodo* a=final->addNode(node->location);
//            // Nodo* b=final->addNode(dualNode->location);
//            // final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             index=j;
//             AorB=0;
//         }
//        if(nodesOfDualInBlackRegion.count(dualDelanuay->links[node->links[j]->id]->B()->id)>0&&Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->B()->location)<minDis){
//        // if(linksOfDualInBlackRegion.count(node->links[j]->id)>0&&Functions::getDistance(node->location,node->links[j]->B()->location)<minDis){
//             minDis=Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->B()->location);
//            //  Nodo* dualNode=dualDelanuay->links[node->links[j]->id]->B();
//            // Nodo* a=final->addNode(node->location);
//            // Nodo* b=final->addNode(dualNode->location);
//            // final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//             index=j;
//             AorB=1;
//         }
// //       if(Functions::getDistance(node->location,dualDelanuay->links[node->links[j]->id]->A()->location)<minDis2){
// //
// //       }
//    }
//    if(AorB==0&&index!=-1){
//      Nodo* dualNode=dualDelanuay->links[node->links[index]->id]->A();
//            Nodo* a=tempSg.addNode(node->location);
//            Nodo* b=tempSg.addNode(dualNode->location);
//            tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//    }else if(AorB==1&&index!=-1){
//      Nodo* dualNode=dualDelanuay->links[node->links[index]->id]->B();
//            Nodo* a=tempSg.addNode(node->location);
//            Nodo* b=tempSg.addNode(dualNode->location);
//            tempSg.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//    }else{
//        std::cout<<"wtf?? "<<node<<'\n';

//    }
//    // Link* link=node->links[0];

//   }















// //std::set<long> idNodesToRemove;
// // for(long i=0;i<tempSg.links.size();i++){
// //   if(tempSg.links[i]->A()->getDegree()>2&&tempSg.links[i]->B()->getDegree()>2){
// //       idNodesToRemove.insert(tempSg.links[i]->B()->id);
// //       for(long j=0;j<tempSg.links[i]->B()->links.size();j++){
// //           if(tempSg.links[i]->B()->links[j]->A()==tempSg.links[i]->B()&&tempSg.links[i]->B()->links[j]->B()!=tempSg.links[i]->A()){
// //               tempSg.links[i]->B()->links[j]->setA(tempSg.links[i]->A());
// //           }
// //           if(tempSg.links[i]->B()->links[j]->B()==tempSg.links[i]->B()&&tempSg.links[i]->B()->links[j]->A()!=tempSg.links[i]->A()){
// //               tempSg.links[i]->B()->links[j]->setB(tempSg.links[i]->A());
// //           }
// //       }
// //       tempSg.links[i]->A()->location.x+=tempSg.links[i]->B()->location.x;
// //       tempSg.links[i]->A()->location.y+=tempSg.links[i]->B()->location.y;
// //       tempSg.links[i]->A()->location.x/=2.0;
// //       tempSg.links[i]->A()->location.y/=2.0;
// //   }
// // }









//     std::vector<bool> isNodeToReconnect;
//     isNodeToReconnect.resize(tempSg.nodes.size(),false);
//     for(long i=0;i<nodesToReconnect.size();i++){
//         Nodo* node=tempSg.getNodeByLocation(nodesToReconnect[i]->location);
//         if(node!=NULL){
//             isNodeToReconnect[node->id]=true;
//         }

//     }


//  // tempSg.removeNodes(idNodesToRemove);



//     std::vector<Point2d> centroids;
//     centroids.resize(tempSg.nodes.size(),Point2d(0,0));
// for(long run=0;run<1;run++){
//     for(long i=0;i<tempSg.nodes.size();i++){
//         // if(tempSg.nodes[i]->getDegree()<2&&!isNodeToReconnect[i]){
//         //     idNodesToRemove.insert(i);
//         // }
//         Point2d centroid;
//         centroid.x=0;
//         centroid.y=0;
//         double sumDegrees=0.0;
//         for(long j=0;j<tempSg.nodes[i]->links.size();j++){
//             long degree=tempSg.nodes[i]->links[j]->getOtherNode(tempSg.nodes[i])->getDegree();
//             double x=(tempSg.nodes[i]->links[j]->A()->location.x+tempSg.nodes[i]->links[j]->B()->location.x)/2.0;
//             double y=(tempSg.nodes[i]->links[j]->A()->location.y+tempSg.nodes[i]->links[j]->B()->location.y)/2.0;
//             centroid.x+=(double)(degree)*x;
//             centroid.y+=(double)(degree)*y;
//             sumDegrees+=degree;
//             // centroid.y+=tempSg.nodes[i]->links[j]->getOtherNode(tempSg.nodes[i])->location.y;
//         }
//         centroid.x/=(double)(sumDegrees);
//         centroid.y/=(double)(sumDegrees);
//         centroids[i]=centroid;

//     }
//     for(long i=0;i<tempSg.nodes.size();i++){
//         if(!isNodeToReconnect[i]){
//             tempSg.nodes[i]->location=centroids[i];
//         }
//     }
// }


//   // for(long i=0;i<tempSg.links.size();i++){
//   //       Nodo* a=final->addNode(tempSg.links[i]->A()->location);
//   //       Nodo* b=final->addNode(tempSg.links[i]->B()->location);
//   //       final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//   // }







// bool STOP=false;
// while(!STOP){
//     std::set<long> idLinksToDelete;
//     for(long i=0;i<tempSg.links.size();i++){
//         if((tempSg.links[i]->A()->getDegree()==1&&!isNodeToReconnect[tempSg.links[i]->A()->id])||(tempSg.links[i]->B()->getDegree()==1&&!isNodeToReconnect[tempSg.links[i]->B()->id])){
//             idLinksToDelete.insert(i);
//         }
//     }
//     if(idLinksToDelete.size()==0){
//         STOP=true;
//     }else{
//         tempSg.removeLinks(idLinksToDelete);
//     }
// }


//   Grafo result;
//   std::vector<std::pair<std::vector<long>,long> > pairsOldNew;
//         // DualExtendedGraph::forcePlanarityPrimal(deg, Grafo::PLANARITY_PLANESWEEP);
//         Grafo::removeNonStructuralNodes(&tempSg, &result, pairsOldNew,false);

// // isNodeToReconnect.clear();
// // isNodeToReconnect.resize(result.nodes.size(),false);
// // for(long i=0;i<nodesToReconnect.size();i++){
// //   Nodo* node=result.getNodeByLocation(nodesToReconnect[i]->location);
// //   isNodeToReconnect[node->id]=true;

// // }







//   for(long i=0;i<result.links.size();i++){
//         Nodo* a=final->addNode(result.links[i]->A()->location);
//         Nodo* b=final->addNode(result.links[i]->B()->location);
//         final->addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//   }














// // for(long i=0;i<final->links.size();i++){
// //     if(final->links[i]->A()->getDegree()==1||final->links[i]->B()->getDegree()==1){
// //         final->links[i]->weight+=500;
// //     }
// // }




//         long maxColor;
//         std::vector<long> colorsT;
//         std::vector<double> sizes;
//         Grafo::getLinkColorsFromNetworkPercolation(final, 0, colorsT, sizes, maxColor);

// Grafo final_;
//         Grafo::createSuperGraphFromClustersFromColorsLinks(final,&final_,colorsT);
//         // Grafo::burnGraph(&final_,final);


//         final->reset();
//         DualExtendedGraph deg3;
//         DualExtendedGraph::addPrimal(&deg3,&final_);
//         Grafo* dual3=deg3.getDualGraph();
//     std::set<long> idLinksToRemoveA3;
//     for(long i=0;i<dual3->links.size();i++){
//         if(dual3->links[i]->A()==dual3->links[i]->B()){
//             idLinksToRemoveA3.insert(i);
//         }
//     }
//     deg3.getPrimalGraph()->removeLinks(idLinksToRemoveA3);
//     Grafo largestComponent3;
//     Grafo::getLargestComponent(deg3.getPrimalGraph(),&largestComponent3);
//     Grafo::burnGraph(&largestComponent3,final);









//         // final->reset();
//         // final->copyGraph(&final_);
//            // final->copyGraph(&finalDebug);


// // for(long i=0;i<final->links.size();i++){
// //     if(final->links[i]->A()->getDegree()==1||final->links[i]->B()->getDegree()==1){
// //         final->links[i]->weight-=500;
// //     }
// // }



// }











void DualExtendedGraph::collapseNodesDual(DualExtendedGraph* deg, std::set<long>& idNodesToCollapse){
    std::set<long> idLinksToRemove;
    // std::vector<std::set<long> > idNodesPerGroup;
    std::vector<long> idClusters;
    std::set<long> idNodesToRemove;
    idClusters.resize(deg->getDualGraph()->nodes.size(),-1);
    std::vector<Link> linksToAdd;
    long currentId=0;
    for(auto it:idNodesToCollapse){
        if(idClusters[it]==-1){
            idClusters[it]=currentId;
            std::deque<long> idNodesToContinue;
            for(long i=0;i<deg->getDualGraph()->nodes[it]->links.size();i++){
                if(idNodesToCollapse.count(deg->getDualGraph()->nodes[it]->links[i]->getOtherNode(deg->getDualGraph()->nodes[it])->id)>0){
                    idLinksToRemove.insert(deg->getDualGraph()->nodes[it]->links[i]->id);
                    if(idClusters[deg->getDualGraph()->nodes[it]->links[i]->getOtherNode(deg->getDualGraph()->nodes[it])->id]==-1){
                        idNodesToContinue.push_front(deg->getDualGraph()->nodes[it]->links[i]->getOtherNode(deg->getDualGraph()->nodes[it])->id);
                        idClusters[deg->getDualGraph()->nodes[it]->links[i]->getOtherNode(deg->getDualGraph()->nodes[it])->id]=currentId;
                    }
                }

            }
            while (idNodesToContinue.size()>0){
                long current=idNodesToContinue.front();
                idNodesToContinue.pop_front();
               idNodesToRemove.insert(current);


                for(long i=0;i<deg->getDualGraph()->nodes[current]->links.size();i++){
                    if(idNodesToCollapse.count(deg->getDualGraph()->nodes[current]->links[i]->getOtherNode(deg->getDualGraph()->nodes[current])->id)>0){
                        idLinksToRemove.insert(deg->getDualGraph()->nodes[current]->links[i]->id);
                        if(idClusters[deg->getDualGraph()->nodes[current]->links[i]->getOtherNode(deg->getDualGraph()->nodes[current])->id]==-1){
                            idNodesToContinue.push_front(deg->getDualGraph()->nodes[current]->links[i]->getOtherNode(deg->getDualGraph()->nodes[current])->id);
                            idClusters[deg->getDualGraph()->nodes[current]->links[i]->getOtherNode(deg->getDualGraph()->nodes[current])->id]=currentId;
                        }
                    }else{
                        if(deg->getDualGraph()->nodes[current]->links[i]->A()->id==current){
//                            Link link;
//                            link.setA(deg->getDualGraph()->nodes[it]);
//                            link.setB(deg->getDualGraph()->nodes[current]->links[i]->getOtherNode(deg->getDualGraph()->nodes[current]));
//                            link.weight=deg->getDualGraph()->nodes[current]->links[i]->weight;
//                            linksToAdd.push_back(link);

                            deg->getDualGraph()->nodes[current]->links[i]->setA(deg->getDualGraph()->nodes[it]);
                            deg->getDualGraph()->nodes[it]->links.push_back(deg->getDualGraph()->nodes[current]->links[i]);
                        }
                        if(deg->getDualGraph()->nodes[current]->links[i]->B()->id==current){
//                            Link link;
//                            link.setB(deg->getDualGraph()->nodes[it]);
//                            link.setA(deg->getDualGraph()->nodes[current]->links[i]->getOtherNode(deg->getDualGraph()->nodes[current]));
//                            link.weight=deg->getDualGraph()->nodes[current]->links[i]->weight;
//                            linksToAdd.push_back(link);

                            deg->getDualGraph()->nodes[current]->links[i]->setB(deg->getDualGraph()->nodes[it]);
                            deg->getDualGraph()->nodes[it]->links.push_back(deg->getDualGraph()->nodes[current]->links[i]);
                        }
                    }

                }
//                deg->getDualGraph()->nodes[current]->links.clear();

            }
            currentId++;
        }
    }
    deg->getDualGraph()->removeLinks(idLinksToRemove);
    deg->getPrimalGraph()->removeLinks(idLinksToRemove);
    for(auto it:idNodesToRemove){
        deg->getDualGraph()->nodes[it]->links.clear();
    }
    deg->getDualGraph()->removeNodesDegree0();

//    deg->getDualGraph()->removeNodes(idNodesToRemove);
//    for(long i=0;i<linksToAdd.size();i++){
//        deg->getDualGraph()
//    }

}





std::vector<double> DualExtendedGraph::getPerimeterRegionsDual(DualExtendedGraph* deg){
    std::vector<double> result;
    result.resize(deg->getDualGraph()->nodes.size(),0.0);
    for(long i=0;i<deg->getDualGraph()->nodes.size();i++){
        for(long j=0;j<deg->getDualGraph()->nodes[i]->links.size();j++){
            result[i]+=deg->getPrimalGraph()->links[deg->getDualGraph()->nodes[i]->links[j]->id]->weight;
        }
    }
    return result;
}




void DualExtendedGraph::diffuseFromSegmentsToSegments_angular(DualExtendedGraph* deg, std::vector<double>& valuesEdges,std::vector<double>& result,double d0,double cutoffValue){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    DualExtendedGraph::setAngularWeightsLineGraph(deg);
    Grafo* G=deg->getLineGraph();
//    std::vector<double> diffusedValues;
    result.resize(valuesEdges.size(),0);
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    for(long i=0;i<valuesEdges.size();i++){
        if(valuesEdges[i]>0){
            double minValue=cutoffValue;
            double distanceLimit=sqrt(valuesEdges[i]/minValue-1)*d0;
            InterfaceDijkstra ID;
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY){
                    result[id]+=valuesEdges[i]/(1+distance*distance/d0/d0);
                }
            }
        }
    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}




void DualExtendedGraph::diffuseFromSegmentsToSegments_metric(DualExtendedGraph* deg, std::vector<double>& valuesEdges,std::vector<double>& result,double d0,double cutoffValue){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    DualExtendedGraph::setMetricWeightsLineGraph(deg);
    Grafo* G=deg->getLineGraph();
    //    std::vector<double> diffusedValues;
    result.resize(valuesEdges.size(),0);
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    for(long i=0;i<valuesEdges.size();i++){
        if(valuesEdges[i]>0){
            double minValue=cutoffValue;
            double distanceLimit=sqrt(valuesEdges[i]/minValue-1)*d0;
            InterfaceDijkstra ID;
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY){
                    result[id]+=valuesEdges[i]/(1+distance*distance/d0/d0);
                }
            }
        }
    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}







void DualExtendedGraph::calculateAreasClustersInParallel(DualExtendedGraph* deg,double percolationThreshold,std::vector<double>& areas,int numThreads){

    std::vector<long> colors;
    std::vector<double> sizes;
    DualExtendedGraph::metricPercolation(deg,percolationThreshold, colors, sizes);
    areas.clear();
//    if(areas.size()==0){

//    }

    long numClusters=0;
    std::vector<std::set<Point2d> > pointsPerCluster;

//    for(long i=0;i<colors.size();i++){
//        if(colors[i]!=-1){
//            if(pointsPerCluster[colors[i]].size()==0){
//                numClusters++;
//            }
////            idsNodesPerCluster[colors[i]].push_back(deg->getStructuralGraph()->nodes[i]->location);
//        }
//    }
    numClusters=sizes.size();// Should I take 1 away because of the -1 cluster, is this correct?
    pointsPerCluster.resize(numClusters,std::set<Point2d>());
    numClusters=0;
    for(long i=0;i<colors.size();i++){
        if(colors[i]!=-1){
            if(pointsPerCluster[colors[i]].size()==0){
                numClusters++;
            }
            pointsPerCluster[colors[i]].insert(deg->getStructuralGraph()->links[i]->A()->location);
            pointsPerCluster[colors[i]].insert(deg->getStructuralGraph()->links[i]->B()->location);
        }
    }
    areas.resize(numClusters,0);
    double numNodesPerThread=floor(numClusters/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {
//        long clusterId=it.first;

        long startId=i*numNodesPerThread;
        long endId=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endId=numClusters;
        }
        std::cout<<"creating thread"<<'\n';
        threads.push_back(std::thread(&GeometryGraph::calculateAreaSetOfPoints_preparationForParallel,std::ref(pointsPerCluster),startId,endId,std::ref(areas)));

    }

    for(auto& thread : threads)
    {
        thread.join();
    }

}




void DualExtendedGraph::calculateFractalDimensionClustersInParallel(DualExtendedGraph* deg,double percolationThreshold,std::vector<double>& fd,int numThreads){

    std::vector<long> colors;
    std::vector<double> sizes;
    DualExtendedGraph::metricPercolation(deg,percolationThreshold, colors, sizes);
    fd.clear();
    //    if(areas.size()==0){

    //    }

    long numClusters=0;
    std::vector<std::set<Point2d> > pointsPerCluster;

    //    for(long i=0;i<colors.size();i++){
    //        if(colors[i]!=-1){
    //            if(pointsPerCluster[colors[i]].size()==0){
    //                numClusters++;
    //            }
    ////            idsNodesPerCluster[colors[i]].push_back(deg->getStructuralGraph()->nodes[i]->location);
    //        }
    //    }
    numClusters=sizes.size();// Should I take 1 away because of the -1 cluster, is this correct?
    pointsPerCluster.resize(numClusters,std::set<Point2d>());
    numClusters=0;
    for(long i=0;i<colors.size();i++){
        if(colors[i]!=-1){
            if(pointsPerCluster[colors[i]].size()==0){
                numClusters++;
            }
            pointsPerCluster[colors[i]].insert(deg->getStructuralGraph()->links[i]->A()->location);
            pointsPerCluster[colors[i]].insert(deg->getStructuralGraph()->links[i]->B()->location);
        }
    }
    fd.resize(numClusters,0);
    double numNodesPerThread=floor(numClusters/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {
        //        long clusterId=it.first;

        long startId=i*numNodesPerThread;
        long endId=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endId=numClusters;
        }
        std::cout<<"creating thread"<<'\n';
        threads.push_back(std::thread(&FractalDimension::calculateFDSetOfPoints_preparationForParallel,std::ref(pointsPerCluster),startId,endId,std::ref(fd)));

    }

    for(auto& thread : threads)
    {
        thread.join();
    }

}

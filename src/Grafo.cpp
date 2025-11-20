//
//  Grafo.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "Grafo.h"

Grafo::Grafo(){
    reset();
}
Grafo::~Grafo(){
    reset();
}

void Grafo::reset(){
//    is3d=false;

    bidirectional=false;
    pseudoGraph=false;
    allowLoops=false;
    isPlanar=false;
    spatialGraph=true;
    acceptSeveralNodesByLocation=false;
    maxIdLinks=0;
    maxIdNodes=0;

    for(long i=links.size()-1;i>=0;i--){

        delete links[i];
        links[i]=NULL;
    }
    for(long i=nodes.size()-1;i>=0;i--){

        delete this->nodes[i];
        nodes[i]=NULL;
    }
    nodes.clear();
    links.clear();





    nodesByLocation.clear();
    severalNodesByLocation.clear();
//     if(numbersRepresentingNodes.size()>0){
//         for(long i=0;i<numbersRepresentingNodes.size();i++){
//             delete numbersRepresentingNodes[i];
//             numbersRepresentingNodes[i]=NULL;
//         }
//         numbersRepresentingNodes.clear();
//     }
// //    numbersRepresentingNodes.clear();
//    // inDijkstra.clear();
//    // inCutoff.clear();
//    // linksInCutoff.clear();


}

Grafo::Grafo(const Grafo& other){

    copyProperties(other);

    for(long i=0;i<other.nodes.size();i++){
//        if(i==604){
//            std::cout<<"checking"<<'\n';
//        }
        Nodo* node=addNode(other.nodes[i]->identifier,other.nodes[i]->originalID,other.nodes[i]->location.x,other.nodes[i]->location.y);
//        if(node==NULL){
//            std::cout<<"what is happening? "<<i<<'\n';
//        }
//        std::cout<<i<<" "<<node->id<<'\n';
//        node->nodeThatRepresents=other.nodes[i]->nodeThatRepresents;
//        node->nodeRepresentedBy=other.nodes[i]->nodeRepresentedBy;
        node->copyProperties(other.nodes[i]);
    }
    finishedAddingNodes();
    for(long i=0;i<other.links.size();i++){

        long id=addLink(other.links[i]->A()->id, other.links[i]->B()->id, other.links[i]->weight);
        if(id!=-1){
//            this->links[id]->linkRepresentedBy=other.links[id]->linkRepresentedBy;
//            this->links[id]->linkThatRepresents=other.links[id]->linkThatRepresents;
            this->links[id]->copyProperties(other.links[i]);
        }

    }


}

void Grafo::copyGraph(Grafo* other){
    copyProperties(other);

    for(long i=0;i<other->nodes.size();i++){
        //        if(i==604){
        //            std::cout<<"checking"<<'\n';
        //        }
        Nodo* node=addNode(other->nodes[i]->identifier,other->nodes[i]->originalID,other->nodes[i]->location.x,other->nodes[i]->location.y,true);
        //        if(node==NULL){
        //            std::cout<<"what is happening? "<<i<<'\n';
        //        }
        //        std::cout<<i<<" "<<node->id<<'\n';
        //        node->nodeThatRepresents=other.nodes[i]->nodeThatRepresents;
        //        node->nodeRepresentedBy=other.nodes[i]->nodeRepresentedBy;
        node->copyProperties(other->nodes[i]);
    }

    for(long i=0;i<other->links.size();i++){

        long id=addLink(other->links[i]->A()->id, other->links[i]->B()->id, other->links[i]->weight);
        if(id!=-1){
            //            this->links[id]->linkRepresentedBy=other.links[id]->linkRepresentedBy;
            //            this->links[id]->linkThatRepresents=other.links[id]->linkThatRepresents;
            this->links[id]->copyProperties(other->links[i]);
        }

    }
    // std::cout<<"Data not copied - need to implement the copy of data"<<'\n';
    finishedAddingNodes();
}
void Grafo::copyGraphForcingPlanarity(Grafo* other){
    copyProperties(other);

    for(long i=0;i<other->nodes.size();i++){
        //        if(i==604){
        //            std::cout<<"checking"<<'\n';
        //        }
        Nodo* node=addNode(other->nodes[i]->identifier,other->nodes[i]->originalID,other->nodes[i]->location.x,other->nodes[i]->location.y);//Here is the difference
        //        if(node==NULL){
        //            std::cout<<"what is happening? "<<i<<'\n';
        //        }
        //        std::cout<<i<<" "<<node->id<<'\n';
        //        node->nodeThatRepresents=other.nodes[i]->nodeThatRepresents;
        //        node->nodeRepresentedBy=other.nodes[i]->nodeRepresentedBy;
        node->copyProperties(other->nodes[i]);
    }

    for(long i=0;i<other->links.size();i++){

        long id=addLink(other->links[i]->A()->id, other->links[i]->B()->id, other->links[i]->weight);
        if(id!=-1){
            //            this->links[id]->linkRepresentedBy=other.links[id]->linkRepresentedBy;
            //            this->links[id]->linkThatRepresents=other.links[id]->linkThatRepresents;
            this->links[id]->copyProperties(other->links[i]);
        }

    }
    // std::cout<<"Data not copied - need to implement the copy of data"<<'\n';
    finishedAddingNodes();
}


void Grafo::removeNodesDegree0(){
    std::set<long> idsNodesToRemove;
    for(long i=0;i<nodes.size();i++){
        if(getDegree(nodes[i])>0||getDegreeIn(nodes[i])>0||getDegreeOut(nodes[i])>0){

        }else{
            idsNodesToRemove.insert(nodes[i]->id);
        }
    }
    removeNodes(idsNodesToRemove);
}

void Grafo::setAsDualGraph(){
    bidirectional=true;
    pseudoGraph=true;
    allowLoops=true;
    acceptSeveralNodesByLocation=true;
}

void Grafo::finishedAddingNodes(){
    nodesByLocation.clear();
    std::unordered_map<Point2d,Nodo*>().swap(nodesByLocation);
    severalNodesByLocation.clear();
    std::unordered_map<Point2d,std::vector<Nodo*> >().swap(severalNodesByLocation);
}

Nodo* Grafo::addNode(){
    Nodo* node=NULL;
    if(!spatialGraph){
        node=new Nodo();
        node->id=this->nodes.size();
        node->mass=1;
        std::stringstream ss;
        ss<<maxIdNodes;
        maxIdNodes++;
        node->originalID=maxIdNodes;
        node->identifier=ss.str();

        node->location=Point2d(0,0);
        this->nodes.push_back(node);
    }else{
        std::cout<<"Grafo::addNode(), Use only for non-spatial graphs";
    }
    return node;
}

Nodo* Grafo::addNode(Point2d location){

    Nodo* node=NULL;
    if(!acceptSeveralNodesByLocation){

        node=getNodeByLocation(location);
        if(node==NULL){
            node=new Nodo();
            node->id=this->nodes.size();
            node->mass=1;

            std::stringstream ss;
            ss<<maxIdNodes;
            maxIdNodes++;
            node->originalID=maxIdNodes;
            node->identifier=ss.str();
            node->location=location;
            this->nodes.push_back(node);
            setNodeByLocation(location,node);
        }
    }else{
        node=new Nodo();
        node->id=this->nodes.size();
        node->mass=1;
        std::stringstream ss;
        ss<<maxIdNodes;
        maxIdNodes++;
        node->originalID=maxIdNodes;
        node->identifier=ss.str();
        node->location=location;
        this->nodes.push_back(node);
        setNodeByLocation(location,node);
    }
    return node;
}

Nodo* Grafo::addNode(Point2d location,bool bypassCheckDuplicatedLocation){
    Nodo* node=NULL;
    if(!bypassCheckDuplicatedLocation){
        node=addNode(location);
    }else{
        node=new Nodo();
        node->id=this->nodes.size();
        node->mass=1;
        std::stringstream ss;
        ss<<maxIdNodes;
        maxIdNodes++;
        node->originalID=maxIdNodes;
        node->identifier=ss.str();
        node->location=location;
        this->nodes.push_back(node);

    }
    return node;
}

Nodo* Grafo::addNode(Point2d location,double mass){
    Nodo* node=NULL;
    if(acceptSeveralNodesByLocation){
        std::vector<Nodo*> nodesTemp=this->getNodesByLocation(location);
        bool exist=false;

        for(long i=0;i<nodesTemp.size();i++){
            if(nodesTemp[i]->mass==mass){
                exist=true;
                node=nodesTemp[i];
            }
        }
        if(!exist){
            node=addNode(location);
            node->mass=mass;
        }
    }else{
        node=addNode(location);
        node->mass=mass;
    }

    return node;
}
//Nodo* Grafo::addNode(long originalID,double x,double y){
//    std::stringstream ss;
//    ss<<originalID;
//    maxIdNodes++;
//    Nodo* node=addNode(ss.str(),x,y);
//    return node;
//}
//Nodo* Grafo::addNode(signed long long originalID,double x,double y){
//    std::stringstream ss;
//    ss<<originalID;
//    maxIdNodes++;
//    Nodo* node=addNode(ss.str(),x,y);
//    return node;
//}
Nodo* Grafo::addNode(long identifier,double x,double y){
//    std::string s=getStringOfLocation(Point2d(x,y));
//    Nodo* node=getNodeByLocation(Point2d(x,y));
//    if(node==NULL){
         Nodo* node=addNode(Point2d(x,y));
//        node->originalID=originalID;
    std::stringstream ssI;
    ssI<<identifier;
            node->identifier=ssI.str();
//        maxIdNodes++;
//    }
    return node;
}
Nodo* Grafo::addNode(long identifier,double x,double y,double mass){
//    std::string s=getStringOfLocation(Point2d(x,y));
//    Nodo* node=getNodeByLocation(Point2d(x,y));
//    if(node==NULL){
         Nodo* node=addNode(Point2d(x,y));
//        node->originalID=originalID;
    std::stringstream ssI;
    ssI<<identifier;
            node->identifier=ssI.str();
            node->mass=mass;
//        maxIdNodes++;
//    }
    return node;
}
Nodo* Grafo::addNode(long identifier,double x,double y,bool bypassCheckDuplicatedLocation){
    //    std::string s=getStringOfLocation(Point2d(x,y));
//    Nodo* node=getNodeByLocation(Point2d(x,y));
//    if(node==NULL){
         Nodo* node=addNode(Point2d(x,y),bypassCheckDuplicatedLocation);
    std::stringstream ssI;
    ssI<<identifier;
    node->identifier=ssI.str();
//        maxIdNodes++;
//    }
    return node;
}
Nodo* Grafo::addNode(double x,double y){
    //    std::string s=getStringOfLocation(Point2d(x,y));
    //    Nodo* node=getNodeByLocation(Point2d(x,y));
    //    if(node==NULL){
    Nodo* node=addNode(Point2d(x,y));
//    node->originalID=maxIdNodes;
//    node->identifier=identifier;
//    maxIdNodes++;
    //    }
    return node;
}
Nodo* Grafo::addNode(std::string identifier,double x,double y){
    //    std::string s=getStringOfLocation(Point2d(x,y));
    //    Nodo* node=getNodeByLocation(Point2d(x,y));
    //    if(node==NULL){
    Nodo* node=addNode(Point2d(x,y));
//    node->originalID=maxIdNodes;
    node->identifier=identifier;
//    maxIdNodes++;
    //    }
    return node;
}
Nodo* Grafo::addNode(std::string identifier,double x,double y,bool bypassCheckDuplicatedLocation){
    //    std::string s=getStringOfLocation(Point2d(x,y));
    //    Nodo* node=getNodeByLocation(Point2d(x,y));
    //    if(node==NULL){
    Nodo* node=addNode(Point2d(x,y),bypassCheckDuplicatedLocation);
//    node->originalID=maxIdNodes;
    node->identifier=identifier;
//    maxIdNodes++;
    //    }
    return node;
}
Nodo* Grafo::addNode(std::string identifier,long originalID,double x,double y,bool bypassCheckDuplicatedLocation){
    //    std::string s=getStringOfLocation(Point2d(x,y));
    //    Nodo* node=getNodeByLocation(Point2d(x,y));
    //    if(node==NULL){
    Nodo* node=addNode(Point2d(x,y),bypassCheckDuplicatedLocation);
        node->originalID=originalID;
    node->identifier=identifier;
//    maxIdNodes=Functions::max(originalID,maxIdNodes);
    //    maxIdNodes++;
    //    }
    return node;
}
Nodo* Grafo::addNodeAndCopyProperties(Nodo* nodeToCopyFrom){
    Nodo* node=addNode(nodeToCopyFrom->location,true);
    node->copyProperties(nodeToCopyFrom);
    return node;
}

void Grafo::removeNode(long id){
//    Nodo* nodeToRemove=this->nodes[id];
//    std::vector<Nodo*> newNodes;
//    newNodes.reserve(this->nodes.size()-1);

// removeLinks(std::set<long> idsLinksToRemove)
    std::set<long> idLinskToRemove;
    for(long i=0;i<this->nodes[id]->links.size();i++){
        idLinskToRemove.insert(this->nodes[id]->links[i]->id);
    }
    removeLinks(idLinskToRemove);

    if(id<nodes.size()-1){
        for(long i=id;i<this->nodes.size();i++){
    //        if(i<id){
    //            newNodes.push_back(this->nodes[i]);
    //        }else if (i>id){
                this->nodes[i]->id=this->nodes[i]->id-1;
    //            newNodes.push_back(this->nodes[i]);
    //        }
        }
    }

//    if(nodes[id]->nodeThatRepresents!=NULL){
//        if(nodes[id]->nodeThatRepresents->nodeRepresentedBy!=NULL){
//            nodes[id]->nodeThatRepresents->nodeRepresentedBy=NULL;
//        }
//        nodes[id]->nodeThatRepresents=NULL;
//    }
//    if(nodes[id]->nodeRepresentedBy!=NULL){
//        if(nodes[id]->nodeRepresentedBy->nodeThatRepresents!=NULL){
//            nodes[id]->nodeRepresentedBy->nodeThatRepresents=NULL;
//        }
//        nodes[id]->nodeThatRepresents=NULL;
//    }
    if(nodesByLocation.size()>0){
        nodesByLocation.erase(nodes[id]->location);
    }
    if(severalNodesByLocation.size()>0){
        for(long i=0;i<severalNodesByLocation[nodes[id]->location].size();i++){
            if(severalNodesByLocation[nodes[id]->location][i]->id==id){
                severalNodesByLocation[nodes[id]->location].erase(severalNodesByLocation[nodes[id]->location].begin()+i);
                break;
            }
        }
    }
    delete this->nodes[id];
    nodes[id]=NULL;
    nodes.erase(nodes.begin()+id);

//    this->nodes=newNodes;
}


void Grafo::removeNodes(std::set<Nodo*> setNodesToRemove){
    std::set<long> ids;
    for(auto it:setNodesToRemove){
        ids.insert(it->id);
    }
    removeNodes(ids);
}

void Grafo::removeNodes(std::set<long> idsNodesToRemove){
    if(idsNodesToRemove.size()>0){
        std::set<long> idLinskToRemove;
        for(auto& id:idsNodesToRemove){

            for(long i=0;i<this->nodes[id]->links.size();i++){
                idLinskToRemove.insert(this->nodes[id]->links[i]->id);
            }
        }
        removeLinks(idLinskToRemove);
        for(auto& id:idsNodesToRemove){

//            for(long i=0;i<this->nodes[id]->links.size();i++){
//                idLinskToRemove.insert(this->nodes[id]->links[i]->id);
//            }

            if(nodesByLocation.size()>0){
                nodesByLocation.erase(nodes[id]->location);
            }
            if(severalNodesByLocation.size()>0){
                for(long i=0;i<severalNodesByLocation[nodes[id]->location].size();i++){
                    if(severalNodesByLocation[nodes[id]->location][i]->id==id){
                        severalNodesByLocation[nodes[id]->location].erase(severalNodesByLocation[nodes[id]->location].begin()+i);
                        break;
                    }
                }
            }
            delete this->nodes[id];
            nodes[id]=NULL;
        }

        std::vector<Nodo*> newNodes;
        newNodes.reserve(nodes.size()-idsNodesToRemove.size());
    //    long currentId=0;
        for(long i=0;i<nodes.size();i++){
            if(nodes[i]!=NULL){
                nodes[i]->id=newNodes.size();
                newNodes.push_back(nodes[i]);
            }
        }
        newNodes.swap(nodes);
    //    newNodes.clear();
    //    std::vector<Nodo*>().swap(newNodes);
    }

}

void Grafo::checkIfLoops(Grafo* G){
    for(long i=0;i<G->links.size();i++){
        if(G->links[i]!=NULL&&G->links[i]->A()==G->links[i]->B()){
            std::cout<<"loop!!, id = "<<i<<'\n';
        }
    }
}


void Grafo::removeNode(Nodo* node){
    removeNode(node->id);
}
long Grafo::addLink(Link &link){
    long generatedId=-1;
    bool STOP=false;
    if(!allowLoops&&link.A()==link.B()){
        STOP=true;
    }
//    if(link.weight==0){
//        std::cout<<"how come?"<<'\n';
//    }
    bool existA=false;
    long id=-1;
    for(long i=0;i<link.A()->links.size();i++){
        if(link.A()->links[i]->getOtherNode(link.A())->id==link.B()->id){
            existA=true;
            id=link.A()->links[i]->id;
        }
    }

    bool existB=false;
    if(bidirectional){
        for(long i=0;i<link.B()->links.size();i++){
            if(link.B()->links[i]->getOtherNode(link.B())->id==link.A()->id){
                existB=true;
                id=link.B()->links[i]->id;
//                link.B()->links[i]->checkDirection(false);
            }
        }
    }else{
        for(long i=0;i<link.B()->getLinksThatReachMe(!bidirectional).size();i++){
            if(link.B()->getLinksThatReachMe(!bidirectional)[i]->getOtherNode(link.B())->id==link.A()->id){
                existB=true;
//                link.B()->getLinksThatReachMe(!bidirectional)[i]->id;
//                link.B()->getLinksThatReachMe(!bidirectional)[i]->checkDirection(false);
            }
        }
    }
    generatedId=id;

//    link.checkDirection(false);
    if(!STOP){
//        generatedId=id;
        if((!existA&&(!bidirectional||!existB))||pseudoGraph){

            Link* pLink=new Link();
            pLink->id=links.size();
            pLink->setA(link.A());
            pLink->setB(link.B());
            pLink->weight=link.weight;
            pLink->data=link.data;
            links.push_back(pLink);

            id=pLink->id;
            generatedId=id;
            std::stringstream ss;
            ss<<maxIdLinks;
            links[id]->originalID=maxIdLinks;
            maxIdLinks++;

            if(link.identifier==""){

                links[id]->identifier=ss.str();
            }else{
                links[id]->identifier=link.identifier;
//                maxIdLinks++;
            }

        }else{
            links[id]->weight=Functions::min(links[id]->weight,link.weight);
//            links[id]->checkDirection(false);
        }
        if(!existA||pseudoGraph){
            this->links[id]->A()->links.push_back(this->links[id]);

        }
        if(bidirectional&&(!existB||pseudoGraph)){
            this->links[id]->B()->links.push_back(this->links[id]);

        }else if (!bidirectional&&(!existB||pseudoGraph)){
            this->links[id]->B()->addLinkThatReachMe(links[id]);

        }

    }
    return generatedId;
}
long Grafo::addLink(long idA,long idB,double weight){
    Link link;
    link.setA(this->nodes[idA]);
    link.setB(this->nodes[idB]);
    link.weight=weight;
    long id=addLink(link);
    // if(id!=-1){
    //     std::stringstream ss;
    //     ss<<maxIdLinks;

    //     links[id]->originalID=maxIdLinks;
    //     maxIdLinks++;
    //     links[id]->identifier=ss.str();
    // }
    return id;

}
//long Grafo::addLink(long idA,long idB,double weight,long originalID){
//    Link link;
//    link.a=this->nodes[idA];
//    link.b=this->nodes[idB];
//    link.weight=weight;
//    long id=addLink(link);
//    if(id!=-1){
//        std::stringstream ss;
//        ss<<originalID;
//        links[id]->originalID=ss.str();
//        maxIdLinks++;
//    }
//    return id;
//
//}
//long Grafo::addLink(long idA,long idB,double weight,signed long long originalID){
//    Link link;
//    link.a=this->nodes[idA];
//    link.b=this->nodes[idB];
//    link.weight=weight;
//    long id=addLink(link);
//    if(id!=-1){
//        std::stringstream ss;
//        ss<<originalID;
//        links[id]->originalID=ss.str();
//        maxIdLinks++;
//    }
//    return id;
//
//}
long Grafo::addLink(long idA,long idB,double weight,std::string identifier){
    Link link;
    link.setA(this->nodes[idA]);
    link.setB(this->nodes[idB]);
    link.weight=weight;
    long id=addLink(link);
    if(id!=-1){
        // links[id]->originalID=maxIdLinks;
        links[id]->identifier=identifier;
        // maxIdLinks++;
    }
    return id;

}
// long Grafo::addLink(long idA,long idB,double weight,std::string identifier,long originalID){
//     Link link;
//     link.setA(this->nodes[idA]);
//     link.setB(this->nodes[idB]);
//     link.weight=weight;
//     long id=addLink(link);
//     if(id!=-1){
//         links[id]->originalID=originalID;
//         links[id]->identifier=identifier;
//         maxIdLinks=Functions::max(originalID+1,maxIdLinks);
// //        maxIdLinks++;
//     }
//     return id;

// }

long Grafo::addLinkAndCopyProperties(long idA,long idB,Link* linkToCopyFrom){
    //CAUTION: nodes needs to have been referenced previously
    long id=addLink(idA,idB,linkToCopyFrom->weight);
    if(id!=-1){
        this->links[id]->copyProperties(linkToCopyFrom);
    }
    return id;
}
void Grafo::removeLink(long id){

    removeLink(id, true);
}


void Grafo::removeLink(long id,bool correctIds){
//    links[id]->checkDirection(false);
  // std::cout<<"kjhkjhkjh"<<'\n';
    LinkPointerVector<Link> newLinkPointers;
    Nodo* nodeA=links[id]->A();

    newLinkPointers.reserve(nodeA->links.size()-1);

    for(long i=0;i<nodeA->links.size();i++){
        if(nodeA->links[i]->id!=id){
//            bool invert=nodeA->links.getLinkPointer(i).isInverted();
            newLinkPointers.push_back(nodeA->links[i]);
        }
    }
    // std::cout<<"oiuoiuoiu"<<'\n';
    links[id]->A()->links=newLinkPointers;
    newLinkPointers.clear();

    if(bidirectional){
      // std::cout<<"ijijjijij"<<'\n';
        Nodo* nodeB=links[id]->B();

        newLinkPointers.reserve(nodeB->links.size()-1);

        for(long i=0;i<nodeB->links.size();i++){

            if(nodeB->links[i]->id!=id){
//                bool invert=nodeB->links.getLinkPointer(i).isInverted();
                newLinkPointers.push_back(nodeB->links[i]);
//                nodeB->links[i]->checkDirection(false);
            }
        }
//        links[id]->checkDirection(false);
        links[id]->B()->links=newLinkPointers;
    }else{
      // std::cout<<"plplplplplpl"<<'\n';
        Nodo* nodeB=links[id]->B();
        std::vector<Link*> newLinksThatReachMe;
// std::cout<<"ytfytf"<<'\n';
        if (nodeB->links.size()-1>0){
          newLinksThatReachMe.reserve(nodeB->links.size()-1);
        }
// std::cout<<"uyguyguyg"<<'\n';
        for(long i=0;i<nodeB->getLinksThatReachMe(!bidirectional).size();i++){

            if(nodeB->getLinksThatReachMe(!bidirectional)[i]->id!=id){

                newLinksThatReachMe.push_back(nodeB->getLinksThatReachMe(!bidirectional)[i]);

            }
        }

        links[id]->B()->setLinksThatReachMe(newLinksThatReachMe);
    }
// std::cout<<"hgfhgfhgf"<<'\n';
    if(correctIds){
        if(id<links.size()-1){
            for(long i=id;i<this->links.size();i++){

                this->links[i]->id=this->links[i]->id-1;

            }
        }
    }


// std::cout<<"tretretre"<<'\n';
    delete links[id];
    links[id]=NULL;
    if(correctIds){
        links.erase(links.begin()+id);
    }

// std::cout<<"ewqewqewq"<<'\n';


}


void Grafo::correctIdsLinks(){
    long currentId=0;
    std::vector<Link*> newLinks;
    for(long i=0;i<this->links.size();i++){
        if(links[i]!=NULL){
            this->links[i]->id=currentId;
            currentId++;
            newLinks.push_back(this->links[i]);
        }

    }
    newLinks.swap(this->links);
}





void Grafo::removeLink(Link* link){
    removeLink(link->id);

}

void Grafo::removeLinks(std::set<long> idsLinksToRemove){
    if(idsLinksToRemove.size()>0){
        std::vector<Link*> linksToRemove;
        linksToRemove.reserve(idsLinksToRemove.size());
        for(auto& it:idsLinksToRemove){
            linksToRemove.push_back(links[it]);
        }
        removeLinks(linksToRemove);
    }
}

void Grafo::removeLinks(std::set<Link*> setLinksToRemove){
    if(setLinksToRemove.size()>0){
        std::vector<Link*> linksToRemove;
        linksToRemove.reserve(setLinksToRemove.size());
        for(auto& it:setLinksToRemove){
            linksToRemove.push_back(it);
        }
        removeLinks(linksToRemove);
    }
}

void Grafo::removeLinks(std::vector<Link*> linksToRemove){
    if(linksToRemove.size()>0){
        std::vector<long> idsToRemove;
        for(long i=0;i<linksToRemove.size();i++){
            idsToRemove.push_back(linksToRemove[i]->id);
        }
        idsToRemove=Functions::unique(idsToRemove);
        idsToRemove=Functions::orderValues(idsToRemove, true);

        for(long i=0;i<idsToRemove.size();i++){
            bool isItALoop=false;

            long id=idsToRemove[i];
            if(links[id]->A()==links[id]->B()){
                isItALoop=true;
            }
//            links[id]->checkDirection(false);
            LinkPointerVector<Link> newLinkPointers;
            Nodo* nodeA=links[id]->A();
            newLinkPointers.reserve(nodeA->links.size()-1);
            for(long i=0;i<nodeA->links.size();i++){
                if(nodeA->links[i]->id!=id){
//                    bool invert=nodeA->links.getLinkPointer(i).isInverted();
                    newLinkPointers.push_back(nodeA->links[i]);
                }
            }
            links[id]->A()->links=newLinkPointers;
            newLinkPointers.clear();

            if(bidirectional){
                if(!isItALoop){
                    Nodo nodeB=*links[id]->B();
                    newLinkPointers.reserve(nodeB.links.size()-1);
                    for(long i=0;i<nodeB.links.size();i++){

                        if(nodeB.links[i]->id!=id){
    //                        bool invert=nodeB.links.getLinkPointer(i).isInverted();
                            newLinkPointers.push_back(nodeB.links[i]);
    //                        nodeB.links[i]->checkDirection(false);
                        }
                    }
    //                links[id]->checkDirection(false);
                    links[id]->B()->links=newLinkPointers;
                }
            }
        }

        //    Link* linkToDelete=links[id];
        //    std::vector<Link*> newLinks;
        //    newLinks.reserve(this->links.size()-1);
        std::vector<Link*> newLinks;
        newLinks.reserve(links.size()-idsToRemove.size());
        if(idsToRemove.size()>0&&idsToRemove[0]<links.size()){

            long currentId=idsToRemove[0];
            if(currentId>0){
                for(long i=0;i<currentId;i++){
                    newLinks.push_back(links[i]);
                }
            }
            for(long j=0;j<idsToRemove.size()-1;j++){
                for(long i=idsToRemove[j]+1;i<idsToRemove[j+1];i++){
                    //        if(i<id){
                    //            newLinks.push_back(this->links[i]);
                    //        }else if (i>id){
                    this->links[i]->id=currentId;
                    newLinks.push_back(this->links[i]);
                    currentId++;
                    //            newLinks.push_back(this->links[i]);
                    //        }
                }
            }
            for(long i=idsToRemove[idsToRemove.size()-1]+1;i<links.size();i++){
                //        if(i<id){
                //            newLinks.push_back(this->links[i]);
                //        }else if (i>id){
                this->links[i]->id=currentId;
                 newLinks.push_back(this->links[i]);
                currentId++;
                //            newLinks.push_back(this->links[i]);
                //        }
            }
        }

        for(long i=0;i<idsToRemove.size();i++){

            long id=idsToRemove[i];
    //        if(links[id]->linkRepresentedBy!=NULL){
    //            if(links[id]->linkRepresentedBy->linkThatRepresents!=NULL){
    //                links[id]->linkRepresentedBy->linkThatRepresents=NULL;
    //            }
    //            links[id]->linkRepresentedBy=NULL;
    //
    //        }
    //        if(links[id]->linkThatRepresents!=NULL){
    //            if(links[id]->linkThatRepresents->linkRepresentedBy!=NULL){
    //                links[id]->linkThatRepresents->linkRepresentedBy=NULL;
    //            }
    //            links[id]->linkThatRepresents=NULL;
    //        }
            delete links[id];
            links[id]=NULL;
    //        links.erase(links.begin()+id);
            //    this->links=newLinks;
        }
         newLinks.swap(this->links);
    }

}

//long Grafo::getDegreeOut(Nodo* &a)
//{
//    return (a->links.size());
//}
//long Grafo::getDegreeIn(Nodo* &a)
//{
//
//    return(a->nodesThatReachMe.size());
//
//}
long Grafo::getDegree(Nodo* &a)
{
    return(a->getDegree());

}
long Grafo::getDegreeIn(Nodo* &a)
{
    return(a->getDegreeIn());

}
long Grafo::getDegreeOut(Nodo* &a)
{
    return(a->getDegreeOut());

}

Link* Grafo::getLink(long idA,long idB){
    Link* link=NULL;
    for(long i=0;i<nodes[idA]->links.size();i++){

        if(nodes[idA]->links[i]->getOtherNode(nodes[idA])->id==idB){
            link=nodes[idA]->links[i];
        }
    }
    return link;
}

long Grafo::getNumberNeighborsAsBidirectional(Nodo* node){
    if(!pseudoGraph&&bidirectional){
        return getDegree(node);
    }else if (pseudoGraph&&bidirectional){
        std::set<long> idNodes;
        for(long i=0;i<node->links.size();i++){
            idNodes.insert(node->links[i]->getOtherNode(node)->id);
        }
        return idNodes.size();
    }else if (pseudoGraph&&!bidirectional){
        std::set<long> idNodes;
        for(long i=0;i<node->links.size();i++){
            idNodes.insert(node->links[i]->getOtherNode(node)->id);
        }
        for(long i=0;i<node->getLinksThatReachMe(!bidirectional).size();i++){
            idNodes.insert(node->getLinksThatReachMe(!bidirectional)[i]->getOtherNode(node)->id);
        }
        return idNodes.size();
    }else{
        return node->links.size()+node->getLinksThatReachMe(!bidirectional).size();
    }
}

//long Graph::degreeOut_MEMB(Node* node){
//    long degree=0;
//    for(long i=0;i<node->transitions.size();i++){
//        if(!node->transitions[i]->b->isCovered){
//            degree++;
//        }
//    }
//    if(!node->isCovered){
//        degree++;
//    }
//    return degree;
//}







void Grafo::create(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,bool directed){
    G->bidirectional=!directed;
    std::unordered_map<long,long> idPerOriginalId;
    for(long i=0;i<std::get<0>(coordinates).size();i++){
        Nodo* node=G->addNode(std::get<0>(coordinates)[i],std::get<1>(coordinates)[i], std::get<2>(coordinates)[i]);
        idPerOriginalId[std::get<0>(coordinates)[i]]=node->id;
    }

    for(long i=0;i<std::get<0>(ncol).size();i++){
        long idA=idPerOriginalId[std::get<0>(ncol)[i]];
        long idB=idPerOriginalId[std::get<1>(ncol)[i]];

        // double x1=std::get<1>(coordinates)[idA];
        // double y1=std::get<2>(coordinates)[idA];
        // double x2=std::get<1>(coordinates)[idB];
        // double y2=std::get<2>(coordinates)[idB];

        // Nodo* node1=G->getNodeByLocation(Point2d(x1,y1));
        // Nodo* node2=G->getNodeByLocation(Point2d(x2,y2));

        G->addLink(idA,idB,std::get<2>(ncol)[i]);
    }
    G->finishedAddingNodes();

}



void Grafo::createPseudoGraph(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,bool directed){
    G->bidirectional=!directed;
    G->pseudoGraph=true;
    std::unordered_map<long,long> idPerOriginalId;
    for(long i=0;i<std::get<0>(coordinates).size();i++){
        Nodo* node=G->addNode(std::get<0>(coordinates)[i],std::get<1>(coordinates)[i], std::get<2>(coordinates)[i],true);
        idPerOriginalId[std::get<0>(coordinates)[i]]=node->id;
    }

    for(long i=0;i<std::get<0>(ncol).size();i++){
        long idA=idPerOriginalId[std::get<0>(ncol)[i]];
        long idB=idPerOriginalId[std::get<1>(ncol)[i]];

        // double x1=std::get<1>(coordinates)[idA];
        // double y1=std::get<2>(coordinates)[idA];
        // double x2=std::get<1>(coordinates)[idB];
        // double y2=std::get<2>(coordinates)[idB];

        // Nodo* node1=G->getNodeByLocation(Point2d(x1,y1));
        // Nodo* node2=G->getNodeByLocation(Point2d(x2,y2));

        G->addLink(idA,idB,std::get<2>(ncol)[i]);
    }
    G->finishedAddingNodes();

}


void Grafo::create(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,std::vector<double> masses,bool directed){
    G->bidirectional=!directed;
    std::unordered_map<long,long> idPerOriginalId;
    for(long i=0;i<std::get<0>(coordinates).size();i++){
        Nodo* node=G->addNode(std::get<0>(coordinates)[i],std::get<1>(coordinates)[i], std::get<2>(coordinates)[i],masses[i]);
        idPerOriginalId[std::get<0>(coordinates)[i]]=node->id;
    }

    for(long i=0;i<std::get<0>(ncol).size();i++){
        long idA=idPerOriginalId[std::get<0>(ncol)[i]];
        long idB=idPerOriginalId[std::get<1>(ncol)[i]];

        // double x1=std::get<1>(coordinates)[idA];
        // double y1=std::get<2>(coordinates)[idA];
        // double x2=std::get<1>(coordinates)[idB];
        // double y2=std::get<2>(coordinates)[idB];

        // Nodo* node1=G->getNodeByLocation(Point2d(x1,y1));
        // Nodo* node2=G->getNodeByLocation(Point2d(x2,y2));

        G->addLink(idA,idB,std::get<2>(ncol)[i]);
    }
    G->finishedAddingNodes();

}

void Grafo::create(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,std::vector<std::string> &originalIds,int type,bool directed){

    G->bidirectional=!directed;

    if(type==Grafo::TYPE_LINES){
        std::unordered_map<long,long> idPerOriginalId;
        for(long i=0;i<std::get<0>(coordinates).size();i++){
            Nodo* node=G->addNode(std::get<0>(coordinates)[i], std::get<1>(coordinates)[i], std::get<2>(coordinates)[i]);
            idPerOriginalId[std::get<0>(coordinates)[i]]=node->id;
        }

        for(long i=0;i<std::get<0>(ncol).size();i++){
            long idA=idPerOriginalId[std::get<0>(ncol)[i]];
            long idB=idPerOriginalId[std::get<1>(ncol)[i]];


            // double x1=std::get<1>(coordinates)[idA];
            // double y1=std::get<2>(coordinates)[idA];
            // double x2=std::get<1>(coordinates)[idB];
            // double y2=std::get<2>(coordinates)[idB];

            // Nodo* node1=G->getNodeByLocation(Point2d(x1,y1));
            // Nodo* node2=G->getNodeByLocation(Point2d(x2,y2));
            if(originalIds.size()>0){
                G->addLink(idA,idB,std::get<2>(ncol)[i],originalIds[i]);
            }else{
                G->addLink(idA,idB,std::get<2>(ncol)[i]);
            }

        }
        G->finishedAddingNodes();
    }else if(type==Grafo::TYPE_POINTS){
        for(long i=0;i<std::get<0>(coordinates).size();i++){
            if(originalIds.size()>0){
                Nodo* node=G->addNode(originalIds[i], std::get<1>(coordinates)[i], std::get<2>(coordinates)[i]);
            }else{
                Nodo* node=G->addNode(std::get<0>(coordinates)[i], std::get<1>(coordinates)[i], std::get<2>(coordinates)[i]);
            }

        }
        G->finishedAddingNodes();
    }

}


void Grafo::create(Grafo* G,std::vector<std::vector<long> > &ncol,std::vector<double> &weights,std::vector<long> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed){
    G->bidirectional=!directed;
    std::unordered_map<long,long> idPerOriginalId;
    for(long i=0;i<coordinates[0].size();i++){
        Nodo* node=G->addNode(idNodes[i], coordinates[0][i], coordinates[1][i]);
         idPerOriginalId[idNodes[i]]=node->id;
    }

    for(long i=0;i<ncol[0].size();i++){
//        long cidA=idPerOriginalId[ncol[0][i]];
//        long idB=idPerOriginalId[ncol[1][i]];

//        double x1=coordinates[0][idA];
//        double y1=coordinates[1][idA];
//        double x2=coordinates[0][idB];
//        double y2=coordinates[1][idB];



//        Nodo* node1=G->addNode(Point2d(x1,y1));
//        Nodo* node2=G->addNode(Point2d(x2,y2));

//        long id=G->addLink(node1->id,node2->id,weights[i]);
//        G->links[id]->originalID=id;
    }
    G->finishedAddingNodes();
}

void Grafo::create(Grafo* G,std::vector<std::vector<long> > &ncol,std::vector<double> &weights,std::vector<std::string> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed){
    G->bidirectional=!directed;
    std::unordered_map<std::string,long> idPerOriginalId;

    for(long i=0;i<coordinates[0].size();i++){
        Nodo* node=G->addNode(idNodes[i], coordinates[0][i], coordinates[1][i]);
        idPerOriginalId[idNodes[i]]=node->id;
    }

    for(long i=0;i<ncol[0].size();i++){
        std::stringstream ss;
        ss<<ncol[0][i];
//        long idA=idPerOriginalId[ss.str()];
        ss.str("");
        ss<<ncol[1][i];

//        long idB=idPerOriginalId[ss.str()];

//        double x1=coordinates[0][idA];
//        double y1=coordinates[1][idA];
//        double x2=coordinates[0][idB];
//        double y2=coordinates[1][idB];

//        Nodo* node1=G->addNode(Point2d(x1,y1));
//        Nodo* node2=G->addNode(Point2d(x2,y2));

//        long id=G->addLink(node1->id,node2->id,weights[i]);
//        G->links[id]->originalID=id;
    }
    G->finishedAddingNodes();
}

//static void create(Grafo* G,std::vector<std::vector<std::string> > &ncolOriginalIds,std::vector<double> &weights,std::vector<std::string> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed){
//    G->bidirectional=!directed;
//    std::unordered_map<std::string,long> idByOriginalId;
//    for(long i=0;i<coordinates[0].size();i++){
//        Nodo* node=G->addNode(idNodes[i], coordinates[0][i], coordinates[1][i]);
//        idByOriginalId[node->originalID]=node->id;
//    }
//
//    for(long i=0;i<ncolOriginalIds[0].size();i++){
//        double x1=coordinates[1][idByOriginalId[ncolOriginalIds[0][i]]];
//        double y1=coordinates[2][idByOriginalId[ncolOriginalIds[0][i]]];
//        double x2=coordinates[1][idByOriginalId[ncolOriginalIds[1][i]]];
//        double y2=coordinates[2][idByOriginalId[ncolOriginalIds[1][i]]];
//
//        Nodo* node1=G->addNode(Point2d(x1,y1));
//        Nodo* node2=G->addNode(Point2d(x2,y2));
//
//        long id=G->addLink(node1->id,node2->id,weights[i],id);
//    }
//    G->finishedAddingNodes();
//}
//static void create(Grafo* G,std::vector<std::string> &idLinks,std::vector<std::vector<std::string> > &ncolOriginalIds,std::vector<double> &weights,std::vector<std::string> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed);



Nodo* Grafo::commonNode(Link* l1,Link* l2){
    return l1->commonNode(l2);
}


//std::string Grafo::getStringOfLocation(Point2d location){
//    std::stringstream ss;
//    double tolerance=10000.0;
//    ss<<(double)(round(location.x*tolerance))/tolerance<<";"<<(double)(round(location.y*tolerance))/tolerance;
//    return ss.str();
//}

Nodo* Grafo::getNodeByLocation(Point2d location){

    if(nodesByLocation.size()==0){
        nodesByLocation.clear();
        for(long i=0;i<nodes.size();i++){
            setNodeByLocation(nodes[i]->location, nodes[i]);
        }
    }
//std::cout<<"point "<<location.x<<" "<<location.y<<'\n';
    Nodo* node=nodesByLocation[location];
    return node;
}
std::vector<Nodo*> Grafo::getNodesByLocation(Point2d location){

    if(severalNodesByLocation.size()==0){
        severalNodesByLocation.clear();
        for(long i=0;i<nodes.size();i++){
            setNodeByLocation(nodes[i]->location, nodes[i]);
        }
    }

    std::vector<Nodo*> nodes=severalNodesByLocation[location];
    return nodes;
}

void Grafo::setNodeByLocation(Point2d location,Nodo* node){
    if(!acceptSeveralNodesByLocation){
        nodesByLocation[location]=node;
    }else{
        severalNodesByLocation[location].push_back(node);
    }
}

void Grafo::getRegionOfALink(Grafo* G,Link* link,std::vector<long> &idNodes,std::vector<long> &idLinks,std::vector<bool> &invertedLinks,bool inverted,bool &correctResult){
    std::vector<long> numberOfTimesVisited;
    numberOfTimesVisited.resize(G->nodes.size());
    Nodo* nodeA=link->A();
    Nodo* nodeB=link->B();
    if(nodeA==nodeB){
        correctResult=false;
    }else{
        if(inverted){
            nodeA=link->B();
            nodeB=link->A();
        }
        std::vector<double> angles;
        bool STOP=false;
        Nodo* node=nodeA;
        Nodo* secondNode=nodeB;
        Nodo* thirdNode;
        angles.clear();
        long index=-1;
        for(long i=0;i<node->links.size();i++){
            if(node->links[i]->getOtherNode(node)==nodeB){
                index=i;
            }
        }
        idNodes.push_back(node->id);
        idLinks.push_back(link->id);
        invertedLinks.push_back(inverted);
        numberOfTimesVisited[node->id]++;
        while(!STOP){
            angles.clear();
            for(long i=0;i<secondNode->links.size();i++){
                if(secondNode->links[i]->getOtherNode(secondNode)!=node){
                    angles.push_back(Functions::getAngleRadians(node->location,secondNode->location,G->nodes[(secondNode->links[i]->getOtherNode(secondNode)->id)]->location));
                }else{
                    angles.push_back(2.0*M_PI);
                }
            }
            index=Functions::getLocationMinimum(angles);
            thirdNode=secondNode->links[index]->getOtherNode(secondNode);
            if(secondNode==nodeA&&thirdNode==nodeB){
                correctResult=true;
                STOP=true;
            }else if(numberOfTimesVisited[secondNode->id]>=100){
                STOP=true;
                correctResult=false;
            }else{
                numberOfTimesVisited[secondNode->id]++;
                idNodes.push_back(secondNode->id);
                idLinks.push_back(secondNode->links[index]->id);
                invertedLinks.push_back(secondNode==secondNode->links[index]->B());
                node=secondNode;
                secondNode=thirdNode;
            }
        }
        for(long i=0;i<idNodes.size();i++){
            numberOfTimesVisited[G->nodes[idNodes[i]]->id]=0;
        }
    }
}






void Grafo::constructDual(Grafo* G,Grafo* dual){
    // G->removeNodesDegree0();
    std::vector<long> idNodeDualA;
    std::vector<long> idNodeDualB;
    idNodeDualA.resize(G->links.size(),-1);
    idNodeDualB.resize(G->links.size(),-1);
    dual->setAsDualGraph();
    dual->pseudoGraph=true;
    dual->allowLoops=true;
    dual->bidirectional=true;
    dual->acceptSeveralNodesByLocation=true;
//    std::unordered_map<std::string, long> nodesDualByLocation;
    std::vector<long> transitionsToAddID;
    std::vector<long> transitionsToAddA;
    std::vector<long> transitionsToAddB;
    double maxArea=-INFINITY;
    long indexMax=-1;
    double minX=INFINITY;
    double minY=INFINITY;

    bool allNodesAreDegree2=true;
    for(long i=0;i<G->nodes.size();i++){
        if(G->nodes[i]->getDegree()!=2){
            allNodesAreDegree2=false;

        }
    }


    std::vector<long> idTransitionsToSetLater;
    for (long i=0;i<G->links.size();i++){
        bool correctResultA=true;
        bool correctResultB=true;
        long nodeDualAID=-1;
        long nodeDualBID=-1;
        if(idNodeDualA[G->links[i]->id]==-1||idNodeDualB[G->links[i]->id]==-1){
            if(idNodeDualA[G->links[i]->id]==-1){
//                G->links[i]->checkDirection(false);
                std::vector<long> idNodesA;
                std::vector<long> idTransitionsA;
                std::vector<bool> invertedTransitionsA;
                Grafo::getRegionOfALink(G,G->links[i],idNodesA,idTransitionsA,invertedTransitionsA,false,correctResultA);
                Point2d centroidA(0,0);
                double numberNodes=0;
                double areaA;
                std::vector<Point2d> points;
                points.reserve(idNodesA.size());
                for(long j=0;j<idNodesA.size();j++){
                    centroidA.x+=G->nodes[idNodesA[j]]->location.x;
                    centroidA.y+=G->nodes[idNodesA[j]]->location.y;
                    numberNodes++;
                    points.push_back(G->nodes[idNodesA[j]]->location);
                }

                areaA=Functions::area(points);
                if(allNodesAreDegree2){
                    areaA=areaA-.0001;
                    // std::cout<<"allNodesAreDegree2"<<'\n';
                }
                centroidA.x/=numberNodes;
                centroidA.y/=numberNodes;

                if(correctResultA){
//                    std::stringstream ss;
//                    ss<<round(centroidA.x*100)<<";"<<round(centroidA.y*100)<<";"<<round(areaA);
//                    if (nodesDualByLocation[ss.str()]==0){
                        Nodo* nodeTemp=dual->addNode(centroidA,areaA);
                        //                    nodeTemp->location=centroidA;
                        if(centroidA.x<minX){
                            minX=centroidA.x;
                        }
                        if(centroidA.y<minY){
                            minY=centroidA.y;
                        }
                        nodeDualAID=nodeTemp->id;
//                        nodesDualByLocation[ss.str()]=dual->nodes.size();
//                    }else{
//                        nodeDualAID=nodesDualByLocation[ss.str()]-1;
//                    }
                    if(areaA>=maxArea){
                        indexMax=nodeDualAID;
                        maxArea=areaA;
                    }
                    for(long k=0;k<idTransitionsA.size();k++){
                        if(!invertedTransitionsA[k]){
                            idNodeDualA[G->links[idTransitionsA[k]]->id]=nodeDualAID;
                        }else{
                            idNodeDualB[G->links[idTransitionsA[k]]->id]=nodeDualAID;
                        }
                    }

                }
            }else{
                nodeDualAID=idNodeDualA[G->links[i]->id];
                correctResultA=true;
            }
            if(idNodeDualB[G->links[i]->id]==-1){
                std::vector<long> idNodesB;
                std::vector<long> idTransitionsB;
                std::vector<bool> invertedTransitionsB;
//                G->links[i]->checkDirection(false);
                Grafo::getRegionOfALink(G,G->links[i],idNodesB,idTransitionsB,invertedTransitionsB,true,correctResultB);
                Point2d centroidB(0,0);
                long numberNodes=0;
                double areaB;
                std::vector<Point2d> points;

                points.reserve(idNodesB.size());
                for(long j=0;j<idNodesB.size();j++){
                    centroidB.x+=G->nodes[idNodesB[j]]->location.x;
                    centroidB.y+=G->nodes[idNodesB[j]]->location.y;
                    numberNodes++;
                    points.push_back(G->nodes[idNodesB[j]]->location);
                }
                centroidB.x/=numberNodes;
                centroidB.y/=numberNodes;
                areaB=Functions::area(points);
                if(allNodesAreDegree2){
                    areaB=areaB+.0001;
                }
                if(correctResultB) {
//                    std::stringstream ss;
//                    ss<<round(centroidB.x*100)<<";"<<round(centroidB.y*100)<<";"<<round(areaB);
//                    if (nodesDualByLocation[ss.str()]==0){
                        Nodo* nodeTemp=dual->addNode(centroidB,areaB);
                        //                    dual->nodes[dual->nodes.size()-1]->location=centroidB;
                        if(centroidB.x<minX){
                            minX=centroidB.x;
                        }
                        if(centroidB.y<minY){
                            minY=centroidB.y;
                        }
                        nodeDualBID=nodeTemp->id;
//                        nodesDualByLocation[ss.str()]=dual->nodes.size();
//                    }else{
//                        nodeDualBID=nodesDualByLocation[ss.str()]-1;
//                    }
                    if(areaB>=maxArea){
                        indexMax=nodeDualBID;
                        maxArea=areaB;
                    }
                    for(long k=0;k<idTransitionsB.size();k++){
                        if(!invertedTransitionsB[k]){
                            idNodeDualA[G->links[idTransitionsB[k]]->id]=nodeDualBID;
                        }else{
                            idNodeDualB[G->links[idTransitionsB[k]]->id]=nodeDualBID;
                        }
                    }

                }

            }else{
                 nodeDualBID=idNodeDualB[G->links[i]->id];
                correctResultB=true;
            }

//            std::stringstream ss;
//            ss<<round(centroidA.x*100)<<";"<<round(centroidA.y*100)<<";"<<round(areaA);
//            if(correctResultA&&correctResultB){
//                if (nodesDualByLocation[ss.str()]==0){
//                    Nodo* nodeTemp=dual->addNode(centroidA);
////                    nodeTemp->location=centroidA;
//                    if(centroidA.x<minX){
//                        minX=centroidA.x;
//                    }
//                    if(centroidA.y<minY){
//                        minY=centroidA.y;
//                    }
//                    nodeDualAID=nodeTemp->id;
//                    nodesDualByLocation[ss.str()]=dual->nodes.size();
//                }else{
//                    nodeDualAID=nodesDualByLocation[ss.str()]-1;
//                }
//                if(areaA>=maxArea){
//                    indexMax=nodeDualAID;
//                    maxArea=areaA;
//                }
//                ss.str("");
//                ss<<round(centroidB.x*100)<<";"<<round(centroidB.y*100)<<";"<<round(areaB);
//                if (nodesDualByLocation[ss.str()]==0){
//                    Nodo* nodeTemp=dual->addNode(centroidB);
////                    dual->nodes[dual->nodes.size()-1]->location=centroidB;
//                    if(centroidB.x<minX){
//                        minX=centroidB.x;
//                    }
//                    if(centroidB.y<minY){
//                        minY=centroidB.y;
//                    }
//                    nodeDualBID=nodeTemp->id;
//                    nodesDualByLocation[ss.str()]=dual->nodes.size();
//                }else{
//                    nodeDualBID=nodesDualByLocation[ss.str()]-1;
//                }
//                if(areaB>=maxArea){
//                    indexMax=nodeDualBID;
//                    maxArea=areaB;
//                }
//                for(long k=0;k<idTransitionsA.size();k++){
//                    if(!invertedTransitionsA[k]){
//                        idNodeDualA[G->links[idTransitionsA[k]]->id]=nodeDualAID;
//                    }else{
//                        idNodeDualB[G->links[idTransitionsA[k]]->id]=nodeDualAID;
//                    }
//                }
//                for(long k=0;k<idTransitionsB.size();k++){
//                    if(!invertedTransitionsB[k]){
//                        idNodeDualA[G->links[idTransitionsB[k]]->id]=nodeDualBID;
//                    }else{
//                        idNodeDualB[G->links[idTransitionsB[k]]->id]=nodeDualBID;
//                    }
//                }
//            }
        }else{
            nodeDualAID=idNodeDualA[G->links[i]->id];
            nodeDualBID=idNodeDualB[G->links[i]->id];
            correctResultA=true;
            correctResultB=true;
        }
        if(correctResultA&&correctResultB){
            transitionsToAddID.push_back(G->links[i]->id);
            nodeDualAID=idNodeDualA[G->links[i]->id];
            nodeDualBID=idNodeDualB[G->links[i]->id];
            transitionsToAddA.push_back(nodeDualAID);
            transitionsToAddB.push_back(nodeDualBID);
        }else{
            idTransitionsToSetLater.push_back(G->links[i]->id);
        }
    }
    for(long i=0;i<idTransitionsToSetLater.size();i++){
        long nodeDualAID=idNodeDualA[G->links[idTransitionsToSetLater[i]]->id];
        long nodeDualBID=idNodeDualB[G->links[idTransitionsToSetLater[i]]->id];
        transitionsToAddID.push_back(idTransitionsToSetLater[i]);
        transitionsToAddA.push_back(nodeDualAID);
        transitionsToAddB.push_back(nodeDualBID);
    }
    std::vector<long> order=Functions::getIndexesOfOrderedValues(transitionsToAddID, true);
    if(dual->nodes.size()>0){
        Point2d locationTemp=dual->nodes[0]->location;
        dual->nodes[0]->location=Point2d(minX-500,minY-500);
        dual->nodes[indexMax]->location=locationTemp;
        double massTemp=dual->nodes[0]->mass;
        dual->nodes[0]->mass=dual->nodes[indexMax]->mass;
        dual->nodes[indexMax]->mass=massTemp;
        for(long i=0;i<transitionsToAddID.size();i++){
            if(transitionsToAddA[order[i]]==0){
                transitionsToAddA[order[i]]=indexMax;
            }else if(transitionsToAddA[order[i]]==indexMax){
                transitionsToAddA[order[i]]=0;
            }
            if(transitionsToAddB[order[i]]==0){
                transitionsToAddB[order[i]]=indexMax;
            }else if(transitionsToAddB[order[i]]==indexMax){
                transitionsToAddB[order[i]]=0;
            }
            Link link;

            if(transitionsToAddA[order[i]]==-1){
                std::cout<<"weird"<<'\n';
                transitionsToAddA[order[i]]=0;
            }
            if(transitionsToAddB[order[i]]==-1){
                std::cout<<"weird"<<'\n';
                transitionsToAddB[order[i]]=0;
            }
            link.setA(dual->nodes[transitionsToAddA[order[i]]]);
            link.setB(dual->nodes[transitionsToAddB[order[i]]]);
            link.weight=Functions::getDistance(link.A()->location,link.B()->location);
            dual->addLink(link);

        }
    }

    dual->finishedAddingNodes();
}


void Grafo::constructLineGraph(Grafo* G,Grafo* lineGraph){
    lineGraph->copyProperties(G);
    for(long i=0; i<G->links.size();i++){
        Nodo* node=lineGraph->addNode(G->links[i]->originalID,(G->links[i]->A()->location.x+G->links[i]->B()->location.x)/2.0,(G->links[i]->A()->location.y+G->links[i]->B()->location.y)/2.0,true);
        node->mass=Functions::max(G->links[i]->A()->mass,G->links[i]->B()->mass);
    }
    if(G->bidirectional){
        for(long i=0;i<G->nodes.size();i++){
            for(long j=0;j<G->nodes[i]->links.size();j++){
                for(long k=0;k<G->nodes[i]->links.size();k++){
                    if(j!=k){
                        lineGraph->addLink(G->nodes[i]->links[j]->id,G->nodes[i]->links[k]->id,(G->nodes[i]->links[j]->weight+G->nodes[i]->links[k]->weight)/2.0);
                    }

                }
            }
        }
    }else{
        for(long i=0;i<G->links.size();i++){
            for(long j=0;j<G->links[i]->B()->links.size();j++){
                lineGraph->addLink(G->links[i]->id,G->links[i]->B()->links[j]->id,(G->links[i]->weight+G->links[i]->B()->links[j]->weight)/2.0);
            }
        }
    }
}



std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > Grafo::getCoordinates(Grafo* G){
//    internalRepresentation !!!
    std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;

    std::vector<long> ids;
    std::vector<double> xs;
    std::vector<double> ys;
    ids.reserve(G->nodes.size());
    xs.reserve(G->nodes.size());
    ys.reserve(G->nodes.size());
    for(long i=0;i<G->nodes.size();i++){

        ids.push_back(G->nodes[i]->id);
        xs.push_back(G->nodes[i]->location.x);
        ys.push_back(G->nodes[i]->location.y);


    }
    coordinates=make_tuple(ids,xs,ys);
    return coordinates;
}
std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > Grafo::getNCOL(Grafo* G){
    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol;
    std::vector<long> idA;
    std::vector<long> idB;
    std::vector<double> weight;
    idA.reserve(G->links.size());
    idB.reserve(G->links.size());
    weight.reserve(G->links.size());
    for(long i=0;i<G->links.size();i++){

        idA.push_back(G->links[i]->A()->id);
        idB.push_back(G->links[i]->B()->id);
        weight.push_back(G->links[i]->weight);



    }
    ncol=std::make_tuple(idA,idB,weight);
    return ncol;
}



void Grafo::getNodeColorsFromComponents(Grafo* G,Grafo* subGraphSeparated,std::vector<long> &colors,std::vector<double> &sizesLinks,long &maxColor,bool assignColorToIsolatedNodes){
    colors.clear();
    sizesLinks.clear();
    colors.resize(G->nodes.size(),-1);
    std::vector<bool> isVisited;
    maxColor=0;
    long color=0;
    isVisited.resize(subGraphSeparated->nodes.size(),false);
    std::vector<bool> isLinkCounted;
    isLinkCounted.resize(subGraphSeparated->links.size(),false);
    for(long i=0;i<subGraphSeparated->nodes.size();i++){
        if(colors[subGraphSeparated->nodes[i]->id]==-1){
            long sizeLinks=0;

            isVisited[i]=true;

            maxColor=color;
            std::queue<long> idsNodesToVisit;
            for(long j=0;j<subGraphSeparated->nodes[i]->links.size();j++){
                if(!isVisited[subGraphSeparated->nodes[i]->links[j]->getOtherNode(subGraphSeparated->nodes[i])->id]){
                    idsNodesToVisit.push(subGraphSeparated->nodes[i]->links[j]->getOtherNode(subGraphSeparated->nodes[i])->id);
                    isVisited[subGraphSeparated->nodes[i]->links[j]->getOtherNode(subGraphSeparated->nodes[i])->id]=true;
                    if(!isLinkCounted[subGraphSeparated->nodes[i]->links[j]->id]){
                        sizeLinks++;
                    }
                    isLinkCounted[subGraphSeparated->nodes[i]->links[j]->id]=true;
                }
            }
            if(!G->bidirectional){
                for(long j=0;j<subGraphSeparated->nodes[i]->getLinksThatReachMe(!G->bidirectional).size();j++){
                    if(!isVisited[subGraphSeparated->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]){
                        idsNodesToVisit.push(subGraphSeparated->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id);
                        isVisited[subGraphSeparated->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]=true;
                        if(!isLinkCounted[subGraphSeparated->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]){
                            sizeLinks++;
                        }
                        isLinkCounted[subGraphSeparated->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]=true;
                    }
                }
            }
            while(idsNodesToVisit.size()>0){
                long currentId=idsNodesToVisit.front();
                isVisited[currentId]=true;
                idsNodesToVisit.pop();


                for(long j=0;j<subGraphSeparated->nodes[currentId]->links.size();j++){
                    //                    long idTemp=separatedComponents->nodes[currentId].idsNeighbors[j];
                    if(!isVisited[subGraphSeparated->nodes[currentId]->links[j]->getOtherNode(subGraphSeparated->nodes[currentId])->id]){
                        idsNodesToVisit.push(subGraphSeparated->nodes[currentId]->links[j]->getOtherNode(subGraphSeparated->nodes[currentId])->id);
                        isVisited[subGraphSeparated->nodes[currentId]->links[j]->getOtherNode(subGraphSeparated->nodes[currentId])->id]=true;
                        if(!isLinkCounted[subGraphSeparated->nodes[currentId]->links[j]->id]){
                            sizeLinks++;
                        }
                        isLinkCounted[subGraphSeparated->nodes[currentId]->links[j]->id]=true;
                    }
                }
                if(!G->bidirectional){
                    for(long j=0;j<subGraphSeparated->nodes[currentId]->getLinksThatReachMe(!G->bidirectional).size();j++){
                        if(!isVisited[subGraphSeparated->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]){
                            idsNodesToVisit.push(subGraphSeparated->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id);
                            isVisited[subGraphSeparated->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]=true;
                            if(!isLinkCounted[subGraphSeparated->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]){
                                sizeLinks++;
                            }
                            isLinkCounted[subGraphSeparated->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]=true;
                        }
                    }
                }
                if(sizeLinks>0){
                    colors[subGraphSeparated->nodes[currentId]->id]=color;
                }
            }
            if(sizeLinks>0||assignColorToIsolatedNodes){
                colors[subGraphSeparated->nodes[i]->id]=color;

                sizesLinks.push_back(sizeLinks);
                color++;
            }


        }
    }


}
void Grafo::getLinkColorsFromNetworkPercolation(Grafo* G,double threshold,std::vector<long> &colors,std::vector<double> &sizesLinks,long &maxColor){
    colors.clear();
    sizesLinks.clear();
    colors.resize(G->links.size(),-1);
    std::vector<bool> isVisited;
    std::vector<bool> isLinkCounted;
    maxColor=0;
    long color=0;
    isVisited.resize(G->nodes.size(),false);
    isLinkCounted.resize(G->links.size(),false);
    for(long i=0;i<G->nodes.size();i++){
        if(!isVisited[G->nodes[i]->id]){
            long sizeLinks=0;

            isVisited[i]=true;

            maxColor=color;
            std::queue<long> idsNodesToVisit;
            for(long j=0;j<G->nodes[i]->links.size();j++){
                if(!isVisited[G->nodes[i]->links[j]->getOtherNode(G->nodes[i])->id]&&G->nodes[i]->links[j]->weight<=threshold){
                    idsNodesToVisit.push(G->nodes[i]->links[j]->getOtherNode(G->nodes[i])->id);
                    isVisited[G->nodes[i]->links[j]->getOtherNode(G->nodes[i])->id]=true;
                    if(!isLinkCounted[G->nodes[i]->links[j]->id]){
                        sizeLinks++;
                        colors[G->nodes[i]->links[j]->id]=color;
                    }
                    isLinkCounted[G->nodes[i]->links[j]->id]=true;
                }else if(G->nodes[i]->links[j]->weight<=threshold){
                    if(!isLinkCounted[G->nodes[i]->links[j]->id]){
                        sizeLinks++;
                        colors[G->nodes[i]->links[j]->id]=color;
                    }
                    isLinkCounted[G->nodes[i]->links[j]->id]=true;
                }
            }
            if(!G->bidirectional){
                for(long j=0;j<G->nodes[i]->getLinksThatReachMe(!G->bidirectional).size();j++){
                    if(!isVisited[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]&&G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->weight<=threshold){
                        idsNodesToVisit.push(G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id);
                        isVisited[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]=true;
                        if(!isLinkCounted[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]){
                            sizeLinks++;
                            colors[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]=color;
                        }
                        isLinkCounted[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]=true;
                    }else if(G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->weight<=threshold){
                        if(!isLinkCounted[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]){
                            sizeLinks++;
                            colors[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]=color;
                        }
                        isLinkCounted[G->nodes[i]->getLinksThatReachMe(!G->bidirectional)[j]->id]=true;
                    }
                }
            }
            while(idsNodesToVisit.size()>0){
                long currentId=idsNodesToVisit.front();
                isVisited[currentId]=true;
                idsNodesToVisit.pop();


                for(long j=0;j<G->nodes[currentId]->links.size();j++){
                    //                    long idTemp=separatedComponents->nodes[currentId].idsNeighbors[j];
                    if(!isVisited[G->nodes[currentId]->links[j]->getOtherNode(G->nodes[currentId])->id]&&G->nodes[currentId]->links[j]->weight<=threshold){
                        idsNodesToVisit.push(G->nodes[currentId]->links[j]->getOtherNode(G->nodes[currentId])->id);
                        isVisited[G->nodes[currentId]->links[j]->getOtherNode(G->nodes[currentId])->id]=true;
                        if(!isLinkCounted[G->nodes[currentId]->links[j]->id]){
                            sizeLinks++;
                            colors[G->nodes[currentId]->links[j]->id]=color;
                        }
                        isLinkCounted[G->nodes[currentId]->links[j]->id]=true;
                    }else if(G->nodes[currentId]->links[j]->weight<=threshold){
                        if(!isLinkCounted[G->nodes[currentId]->links[j]->id]){
                            sizeLinks++;
                            colors[G->nodes[currentId]->links[j]->id]=color;
                        }
                        isLinkCounted[G->nodes[currentId]->links[j]->id]=true;
                    }
                }
                if(!G->bidirectional){
                    for(long j=0;j<G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional).size();j++){
                        if(!isVisited[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]&&G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->weight<=threshold){
                            idsNodesToVisit.push(G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id);
                            isVisited[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->A()->id]=true;
                            if(!isLinkCounted[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]){
                                sizeLinks++;
                                colors[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]=color;
                            }
                            isLinkCounted[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]=true;
                        }else if(G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->weight<=threshold){
                            if(!isLinkCounted[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]){
                                sizeLinks++;
                                colors[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]=color;
                            }
                            isLinkCounted[G->nodes[currentId]->getLinksThatReachMe(!G->bidirectional)[j]->id]=true;
                        }
                    }
                }
//                if(sizeLinks>0){
//                    colors[G->nodes[currentId]->id]=color;
//                }
            }

            if(sizeLinks>0){

//                colors[G->nodes[i]->id]=color;
                sizesLinks.push_back(sizeLinks);
                color++;
            }


        }
    }
}

//void Grafo::getColorsFromNetworkPercolation(Grafo* G,double threshold,std::vector<long> &colors,std::vector<long> &sizes,long &maxColor,std::vector<long> orderWeights){
////    if(colors.size()>G->nodes.size()){
////        colors.clear();
////    }
////    if(colors.size()!=G->nodes.size()){
//    colors.clear();
//    sizes.clear();
//
////    }else{
////        for(long i=0;i<G->nodes.size();i++){
////            colors[i]=-1;
////        }
////    }
//    std::vector<bool> isVisited;
//    maxColor=0;
//    long color=0;
////    if(G->bidirectional){
////        isVisited.resize(G->links.size()*2,false);
////        colors.resize(G->links.size()*2,-1);
////    }else{
//        isVisited.resize(G->links.size(),false);
//        colors.resize(G->links.size(),-1);
////    }
//
////    std::vector<double> values;
////    values.reserve(G->links.size());
////    for(long g=0;g<G->links.size();g++){
////        values.push_back(G->links[g]->weight);
////    }
////    std::vector<long> orderWeights=Functions::getIndexesOfOrderedValues(values, true);
//
//    for(long g=0;g<G->links.size();g++){
////        long i=orderWeights[g];
//        long i=g;
//
//        if(colors[G->links[i]->id]==-1&&G->links[i]->weight<=threshold){
//            long size=0;
//            colors[G->links[i]->id]=color;
//            isVisited[i]=true;
//
//            maxColor=color;
//            std::queue<long> idsLinksToVisit;
//            std::queue<bool> inverted;
//            G->links[i]->checkDirection(false);
//            for(long j=0;j<G->links[i]->B()->links.size();j++){
//                if(G->links[i]->B()->links[j]->id!=G->links[i]->id){
//                    long idVisited=G->links[i]->B()->links[j]->id;
////                    if(G->links[i]->B()->links[j]->inverted==true){
////                        idVisited=idVisited+G->links.size();
////                    }
//                    if(!isVisited[idVisited]&&G->links[i]->B()->links[j]->weight<=threshold){
//                        idsLinksToVisit.push(G->links[i]->B()->links[j]->id);
//                        inverted.push(G->links[i]->B()->links[j]->inverted);
//                        isVisited[idVisited]=true;
//                        size++;
//                    }
//                }
//            }
//            while(idsLinksToVisit.size()>0){
//
//                bool currentInverted=inverted.front();
//                long currentId=idsLinksToVisit.front();
//                long idVisited=currentId;
////                if(currentInverted){
////                    idVisited=idVisited+G->links.size();
////                }
//                isVisited[idVisited]=true;
//                idsLinksToVisit.pop();
//                inverted.pop();
//                colors[idVisited]=color;
//
//                G->links[currentId]->checkDirection(currentInverted);
//
//                for(long j=0;j<G->links[currentId]->b->links.size();j++){
//                    if(G->links[currentId]->b->links[j]->id!=G->links[currentId]->id){
//                        G->links[currentId]->checkDirection(currentInverted);
//                        long idVisitedB=G->links[currentId]->b->links[j]->id;
////                        if(G->links[currentId]->b->links[j]->inverted==true){
////                            idVisitedB=idVisitedB+G->links.size();
////                        }
//
//                        if(!isVisited[idVisitedB]&&G->links[currentId]->b->links[j]->weight<=threshold){
//                            idsLinksToVisit.push(G->links[currentId]->b->links[j]->id);
//                            inverted.push(G->links[currentId]->b->links[j]->inverted);
//                            isVisited[idVisitedB]=true;
//                            size++;
//                        }
//                    }
//                    G->links[currentId]->checkDirection(currentInverted);
//                }
//            }
//            color++;
//            sizes.push_back(size);
//
//
//        }
//    }
////    if(G->bidirectional){
////        for(long i=0;i<G->links.size();i++){
////
////            if(colors[G->links[i]->id]==-1&&G->links[i]->weight<=threshold){
////                long size=0;
////                colors[G->links[i]->id]=color;
////                isVisited[i]=true;
////
////                maxColor=color;
////                std::queue<long> idsLinksToVisit;
////                std::queue<bool> inverted;
////                G->links[i]->checkDirection(true);
////                for(long j=0;j<G->links[i]->A()->links.size();j++){
////                    if(G->links[i]->A()->links[j]->id!=G->links[i]->id){
////                        long idVisited=G->links[i]->A()->links[j]->id;
////                        if(G->links[i]->A()->links[j]->inverted==true){
////                            idVisited=idVisited+G->links.size();
////                        }
////                        if(!isVisited[idVisited]&&G->links[i]->A()->links[j]->weight<=threshold){
////                            idsLinksToVisit.push(G->links[i]->A()->links[j]->id);
////                            inverted.push(G->links[i]->A()->links[j]->inverted);
////                            isVisited[idVisited]=true;
////                            size++;
////                        }
////                    }
////                }
////                while(idsLinksToVisit.size()>0){
////
////                    bool currentInverted=inverted.front();
////                    long currentId=idsLinksToVisit.front();
////                    long idVisited=currentId;
////                    if(currentInverted){
////                        idVisited=idVisited+G->links.size();
////                    }
////                    isVisited[idVisited]=true;
////                    idsLinksToVisit.pop();
////                    inverted.pop();
////                    colors[idVisited]=color;
////                    G->links[currentId]->checkDirection(currentInverted);
////                    for(long j=0;j<G->links[currentId]->b->links.size();j++){
////                        if(G->links[currentId]->b->links[j]->id!=G->links[i]->id){
////                            G->links[currentId]->checkDirection(currentInverted);
////                            long idVisitedB=G->links[currentId]->b->links[j]->id;
////                            if(G->links[currentId]->b->links[j]->inverted==true){
////                                idVisitedB=idVisitedB+G->links.size();
////                            }
////
////                            if(!isVisited[idVisitedB]&&G->links[currentId]->b->links[j]->weight<=threshold){
////                                idsLinksToVisit.push(G->links[currentId]->b->links[j]->id);
////                                inverted.push(G->links[currentId]->b->links[j]->inverted);
////                                isVisited[idVisitedB]=true;
////                                size++;
////                            }
////                        }
////                        G->links[currentId]->checkDirection(currentInverted);
////                    }
////                }
////                color++;
////                sizes.push_back(size);
////
////
////            }
////        }
////    }
//
//
//}


void Grafo::networkPercolation(Grafo* G,Grafo* result,double threshold){
    result->copyProperties(G);

    result->nodes.reserve(G->nodes.size());


    for(long i=0;i<G->nodes.size();i++){
        result->addNodeAndCopyProperties(G->nodes[i]);
    }

    for(long i=0;i<G->links.size();i++){
        if(G->links[i]->weight<=threshold){
//            Link link;
//            link.a=G->links[i]->a->nodeRepresentedBy;
//            link.b=G->links[i]->b->nodeRepresentedBy;
//            link.weight=G->links[i]->weight;
            result->addLinkAndCopyProperties(G->links[i]->A()->id,G->links[i]->B()->id,G->links[i]);
        }
    }
    result->finishedAddingNodes();

}


void Grafo::getComponents(Grafo* G,std::vector<Grafo> &components,long minSizeComponent){
//    Grafo percolated;
//    Grafo::networkPercolation(G, &percolated, INFINITY);
    // std::vector<long> colors;
    // std::vector<double> sizes;
    // long maxColor;
    // Grafo::getNodeColorsFromComponents(G,G, colors, sizes, maxColor,true);
    // std::vector<std::vector<Nodo*> > listOfListsNodes;
    // listOfListsNodes.resize(sizes.size());
    // for(long i=0;i<colors.size();i++){
    //     if(colors[i]!=-1){
    //         listOfListsNodes[colors[i]].push_back(G->nodes[i]);
    //     }
    // }
    // std::vector<long> ordered=Functions::getIndexesOfOrderedValues(sizes, false);
    // long numberComponents=0;
    // for(long i=0;i<sizes.size();i++){
    //     if(sizes[ordered[i]]>=minSizeComponent){
    //         numberComponents++;
    //     }else{
    //         break;
    //     }
    // }
    // components.resize(numberComponents,Grafo());
    // for(long i=0;i<numberComponents;i++){
    //     if(listOfListsNodes[ordered[i]].size()>=minSizeComponent){
    //
    //         Grafo::inducedSubgraph(G, &components[i], listOfListsNodes[ordered[i]]);
    //
    //     }
    // }
    std::vector<long> colors;
    std::vector<double> sizes;
//    void Grafo::getLinkColorsFromNetworkPercolation(Grafo* G,double threshold,std::vector<long> &colors,std::vector<long> &sizesLinks,long &maxColor);
    long maxColor;
    Grafo::getLinkColorsFromNetworkPercolation(G,INFINITY,colors,sizes,maxColor);

//    Grafo::getNodeColorsFromComponents(G, G, colors, sizes, maxColor,false);
    // std::vector<Grafo> components;
    Grafo::getComponentsFromColorsOfLinks(G, components, 0, colors, sizes);
}

void Grafo::transformColorsLinksIntoColorsNodes(Grafo* G,std::vector<long> &colorsLinks,std::vector<long> &colorsNodes){
    if(colorsNodes.size()==G->nodes.size()){
        std::fill(colorsNodes.begin(),colorsNodes.end(),-1);
    }else if(colorsNodes.size()==0){
        colorsNodes.resize(G->nodes.size(),-1);
    }else{
        colorsNodes.clear();
        colorsNodes.resize(G->nodes.size(),-1);
    }

    for(long i=0;i<G->links.size();i++){
        if(colorsLinks[i]!=-1){
            colorsNodes[G->links[i]->A()->id]=colorsLinks[i];
            colorsNodes[G->links[i]->B()->id]=colorsLinks[i];
        }
    }
}
void Grafo::transformValuesLinksIntoValuesNodes(Grafo* G,std::vector<double> &valuesLinks,std::vector<double> &valuesNodes){
    if(valuesNodes.size()==G->nodes.size()){
        std::fill(valuesNodes.begin(),valuesNodes.end(),-1);
    }else if(valuesNodes.size()==0){
        valuesNodes.resize(G->nodes.size(),-1);
    }else{
        valuesNodes.clear();
        valuesNodes.resize(G->nodes.size(),-1);
    }

    for(long i=0;i<G->links.size();i++){
        if(valuesLinks[i]!=-1){
            valuesNodes[G->links[i]->A()->id]=valuesLinks[i];
            valuesNodes[G->links[i]->B()->id]=valuesLinks[i];
        }
    }
}


void Grafo::transformColorsNodesIntoColorsLinks(Grafo* G,std::vector<long> &colorsNodes,std::vector<long> &colorsLinks){
    if(colorsLinks.size()==G->links.size()){
        std::fill(colorsLinks.begin(),colorsLinks.end(),-1);
    }else if(colorsLinks.size()==0){
        colorsLinks.resize(G->links.size(),-1);
    }else{
        colorsLinks.clear();
        colorsLinks.resize(G->links.size(),-1);
    }
    for(long i=0;i<G->nodes.size();i++){
        if(colorsNodes[i]!=-1){
            for(long j=0;j<G->nodes[i]->links.size();j++){
                if(colorsNodes[i]==colorsNodes[G->nodes[i]->links[j]->getOtherNode(G->nodes[i])->id]){
                    colorsLinks[G->nodes[i]->links[j]->id]=colorsNodes[i];
                }
            }
//            colorsNodes[G->links[i]->A()->id]=colorsLinks[i];
//            colorsNodes[G->links[i]->B()->id]=colorsLinks[i];
        }
    }
}

void Grafo::getComponentsFromColorsOfNodes(Grafo* G,std::vector<Grafo> &components,long minSizeComponent,std::vector<long> &colors,std::vector<double> &sizes){
    //    Grafo percolated;
    //    Grafo::networkPercolation(G, &percolated, INFINITY);

    std::vector<std::vector<Nodo*> > listOfListsNodes;
    listOfListsNodes.resize(sizes.size());
    for(long i=0;i<colors.size();i++){
        if(colors[i]!=-1){
            listOfListsNodes[colors[i]].push_back(G->nodes[i]);
        }
    }
    std::vector<long> ordered=Functions::getIndexesOfOrderedValues(sizes, false);
    long numberComponents=0;
    for(long i=0;i<sizes.size();i++){
        if(sizes[ordered[i]]>=minSizeComponent){
            numberComponents++;
        }else{
            break;
        }
    }
    components.resize(numberComponents,Grafo());
    for(long i=0;i<numberComponents;i++){
        if(listOfListsNodes[ordered[i]].size()>=minSizeComponent){

            Grafo::inducedSubgraph(G, &components[i], listOfListsNodes[ordered[i]]);

        }
    }

}

void Grafo::getComponentsFromColorsOfLinks(Grafo* G,std::vector<Grafo> &components,long minSizeComponent,std::vector<long> &colors,std::vector<double> &sizes){
    //    Grafo percolated;
    //    Grafo::networkPercolation(G, &percolated, INFINITY);

    std::vector<std::vector<Link*> > listOfListsLinks;
    listOfListsLinks.resize(sizes.size());
    for(long i=0;i<colors.size();i++){
        if(colors[i]!=-1){
            listOfListsLinks[colors[i]].push_back(G->links[i]);
        }
    }
    std::vector<long> ordered=Functions::getIndexesOfOrderedValues(sizes, false);
    long numberComponents=0;
    for(long i=0;i<sizes.size();i++){
        if(sizes[ordered[i]]>=minSizeComponent){
            numberComponents++;
        }else{
            break;
        }
    }
    components.resize(numberComponents,Grafo());
    for(long i=0;i<numberComponents;i++){
        if(listOfListsLinks[ordered[i]].size()>=minSizeComponent){

            Grafo::inducedSubgraphFromLinks(G, &components[i], listOfListsLinks[ordered[i]]);

        }
    }

}


void Grafo::getLargestComponent(Grafo* G,Grafo* LG){
//    Grafo percolated;
//    Grafo::networkPercolation(G, &percolated, INFINITY);
    std::vector<long> colors;
    std::vector<double> sizes;
//    void Grafo::getLinkColorsFromNetworkPercolation(Grafo* G,double threshold,std::vector<long> &colors,std::vector<long> &sizesLinks,long &maxColor);
    long maxColor;
    Grafo::getLinkColorsFromNetworkPercolation(G,INFINITY,colors,sizes,maxColor);

//    Grafo::getNodeColorsFromComponents(G, G, colors, sizes, maxColor,false);
    std::vector<Grafo> components;
    Grafo::getComponentsFromColorsOfLinks(G, components, 0, colors, sizes);
//    std::cout<<"number of components in getLargestComponent: "<<components.size()<<'\n';
    if(components.size()>0){
        LG->copyGraph(&components[0]);
    }

}

//void Grafo::getSubgraphsFromColors(Grafo* G,std::vector<Grafo> &subGraphs,std::vector<long> colors,std::vector<double> sizes,long minSizeComponent){
//    std::vector<std::vector<Nodo*> > listOfListsNodes;
//    listOfListsNodes.resize(sizes.size());
//    for(long i=0;i<colors.size();i++){
//        if(colors[i]!=-1){
//            listOfListsNodes[colors[i]].push_back(G->nodes[i]);
//        }
//    }
//    std::vector<long> ordered=Functions::getIndexesOfOrderedValues(sizes, false);
//    long numberComponents=0;
//    for(long i=0;i<sizes.size();i++){
//        if(sizes[ordered[i]]>=minSizeComponent){
//            numberComponents++;
//        }else{
//            break;
//        }
//    }
//    subGraphs.resize(numberComponents,Grafo());
//    for(long i=0;i<numberComponents;i++){
//        if(listOfListsNodes[ordered[i]].size()>=minSizeComponent){
//
//            Grafo::inducedSubgraph(G, &subGraphs[i], listOfListsNodes[ordered[i]]);
//
//        }
//    }
//
//}

void Grafo::copyProperties(Grafo* G){
//    is3d=G->is3d;
    pseudoGraph=G->pseudoGraph;
    bidirectional=G->bidirectional;
    allowLoops=G->allowLoops;
    isPlanar=G->isPlanar;
    spatialGraph=G->spatialGraph;
    acceptSeveralNodesByLocation=G->acceptSeveralNodesByLocation;
    maxIdNodes=G->maxIdNodes;
    maxIdLinks=G->maxIdLinks;

}

void Grafo::copyProperties(const Grafo& G){
//    is3d=G.is3d;
    pseudoGraph=G.pseudoGraph;
    bidirectional=G.bidirectional;
    allowLoops=G.allowLoops;
    isPlanar=G.isPlanar;
    spatialGraph=G.spatialGraph;
    acceptSeveralNodesByLocation=G.acceptSeveralNodesByLocation;
    maxIdNodes=G.maxIdNodes;
    maxIdLinks=G.maxIdLinks;

}

void Grafo::inducedSubgraph(Grafo* G,Grafo* subgraph,std::vector<Nodo*> &listNodes){
    std::set<long> idsNodes;
//    std::set<long> idsNodesTemp;

    subgraph->copyProperties(G);

    for(long i=0; i<listNodes.size(); i++){

        idsNodes.insert(listNodes[i]->id);
    }
    Grafo::inducedSubgraph(G,subgraph,idsNodes);
//    //    std::vector<long> idsNodesVector;
//    //    idsNodesVector.reserve(idsNodes.size());
//    //
//    //    for(auto& it:idsNodes){
//    //        idsNodesVector.push_back(it);
//    //    }
//
//    subgraph->nodes.reserve(idsNodes.size());
//
//    for(std::set<Number>::iterator it=idsNodes.begin();it!=idsNodes.end();it++){
//        Nodo* node=subgraph->addNodeAndCopyProperties(G->nodes[it->value]);
////        idsNodes->id=node->id;
//    }
//
//    for(auto& it:idsNodes){
//        Nodo* node=G->nodes[it.value];
//
//        for(long j=0;j<node->links.size(); j++)
//        {
//            Number searchNumber;
//            searchNumber.value=node->links[j]->b->id;
//            std::set<Number>::iterator it2=idsNodes.find(searchNumber);
//            if(it2!=idsNodes.end()){
//                if(!node->links[j]->inverted){
//                    subgraph->addLinkAndCopyProperties(it.id,(*it2).id,node->links[j]);
//                }else{
//                    subgraph->addLinkAndCopyProperties((*it2).id,it.id,node->links[j]);
//                }
//
//            }
//
//
//        }
//    }
//    subgraph->finishedAddingNodes();
}
void Grafo::inducedSubgraph(Grafo* G,Grafo* subgraph,std::vector<long> &idNodes){
    std::set<long> idsNodes_;
//    std::set<long> idsNodesTemp;

    subgraph->copyProperties(G);

    for(long i=0; i<idNodes.size(); i++){

        idsNodes_.insert(idNodes[i]);
    }
    Grafo::inducedSubgraph(G,subgraph,idsNodes_);
//    //    std::vector<long> idsNodesVector;
//    //    idsNodesVector.reserve(idsNodes.size());
//    //
//    //    for(auto& it:idsNodes){
//    //        idsNodesVector.push_back(it);
//    //    }
//
//    subgraph->nodes.reserve(idsNodes.size());
//
//    for(std::set<Number>::iterator it=idsNodes.begin();it!=idsNodes.end();it++){
//        Nodo* node=subgraph->addNodeAndCopyProperties(G->nodes[it->value]);
////        idsNodes->id=node->id;
//    }
//
//    for(auto& it:idsNodes){
//        Nodo* node=G->nodes[it.value];
//
//        for(long j=0;j<node->links.size(); j++)
//        {
//            Number searchNumber;
//            searchNumber.value=node->links[j]->b->id;
//            std::set<Number>::iterator it2=idsNodes.find(searchNumber);
//            if(it2!=idsNodes.end()){
//                if(!node->links[j]->inverted){
//                    subgraph->addLinkAndCopyProperties(it.id,(*it2).id,node->links[j]);
//                }else{
//                    subgraph->addLinkAndCopyProperties((*it2).id,it.id,node->links[j]);
//                }
//
//            }
//
//
//        }
//    }
//    subgraph->finishedAddingNodes();
}


void Grafo::inducedSubgraph(Grafo* G,Grafo* subgraph,std::set<long> &idsNodes){



    std::set<Number> idsNodesTemp;

    subgraph->copyProperties(G);
    long i=0;
    for(auto& it:idsNodes){
        Number number;
        number.value=it;
        number.id=idsNodesTemp.size();
        idsNodesTemp.insert(number);
        i++;
    }



    subgraph->nodes.reserve(idsNodesTemp.size());

    for(auto it:idsNodesTemp){
        subgraph->addNodeAndCopyProperties(G->nodes[it.value]);

    }

    for(auto& it:idsNodesTemp){
        Nodo* node=G->nodes[it.value];

        for(long j=0;j<node->links.size(); j++)
        {
            Number searchNumber;
            searchNumber.value=node->links[j]->getOtherNode(node)->id;
            std::set<Number>::iterator it2=idsNodesTemp.find(searchNumber);
            if(it2!=idsNodesTemp.end()){
                // if(!node->links[j]->inverted){
                    subgraph->addLinkAndCopyProperties(it.id,(*it2).id,node->links[j]);
                // }else{
                //     subgraph->addLinkAndCopyProperties((*it2).id,it.id,node->links[j]);
                // }

            }


        }
    }
    subgraph->finishedAddingNodes();
}

void Grafo::inducedSubgraphFromLinks(Grafo* G,Grafo* subgraph,std::vector<Link*> &listLinks){

    std::set<long> setLinks;
    for(long i=0;i<listLinks.size();i++){
        setLinks.insert(listLinks[i]->id);
        // listNodes.insert(listLinks[i]->b->id);
    }
    Grafo::inducedSubgraphFromLinks(G, subgraph, setLinks);



}

void Grafo::inducedSubgraphFromLinks(Grafo* G,Grafo* subgraph,std::vector<long> &idsLinks){
    std::set<long> listLinks;
    for(long i=0;i<idsLinks.size();i++){
        listLinks.insert(G->links[idsLinks[i]]->id);
        // listLinks.insert(G->links[idsLinks[i]]->b->id);
    }
    Grafo::inducedSubgraphFromLinks(G, subgraph, listLinks);
}
void Grafo::inducedSubgraphFromLinks(Grafo* G,Grafo* subgraph,std::set<long> &idsLinks){
     std::set<long> idsNodesTemp;

    subgraph->copyProperties(G);
//    long i=0;
    for(auto& it:idsLinks){
        // Number number;
        // number.value=it;
        // number.id=idsNodesTemp.size();
        idsNodesTemp.insert(G->links[it]->A()->id);
        idsNodesTemp.insert(G->links[it]->B()->id);
        // i++;
    }



    subgraph->nodes.reserve(idsNodesTemp.size());

    for(auto it:idsNodesTemp){
        subgraph->addNodeAndCopyProperties(G->nodes[it]);

    }

    for(auto& it:idsLinks){
        Nodo* a=subgraph->addNode(G->links[it]->A()->location);
        Nodo* b=subgraph->addNode(G->links[it]->B()->location);
        double weight=G->links[it]->weight;
        Link link;
        link.setA(a);
        link.setB(b);
        link.weight=weight;
        link.copyProperties(G->links[it]);
        subgraph->addLink(link);
    }
    subgraph->finishedAddingNodes();
}

//void Grafo::cleanDelaunay(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys,std::vector<std::vector<long> > &delaunay,std::vector<double> &weights,double tolerance){
//    std::vector<bool> accepted;
//
//    std::vector<long> idA,idB;
//    idA=delaunay[0];
//    idB=delaunay[1];
//    accepted.resize(idA.size(),true);
//    std::unordered_map<std::string,bool> acceptTransition;
//    Grafo G;
//    G.bidirectional=true;
//    for(long i=0;i<xs.size();i++){
//        Nodo* nodeTemp=G.addNode(Point2d(xs[i],ys[i]));
//        nodeTemp->originalID=ids[i];
////        nodeTemp->location=Point2d(xs[i],ys[i]);
//    }
//    for(long i=0;i<idA.size();i++){
//        Link link;
//        link.a=G.nodes[idA[i]];
//        link.b=G.nodes[idB[i]];
//        link.weight=Functions::getDistance(link.a->location, link.b->location);
//        G.addLink(link);
////        if(id!=-1){
////            std::stringstream ss;
////            ss<<G.links[id]->a->id<<";"<<G.links[id]->b->id;
////            acceptTransition[ss.str()]=true;
////            ss.str("");
////            ss<<G.links[id]->b->id<<";"<<G.links[id]->a->id;
////            acceptTransition[ss.str()]=true;
////        }
//    }
//
//    for(long i=0;i<G.nodes.size();i++){
//        for(long k=0;k<G.nodes[i]->links.size();k++){
////            Link link;
////            link.a=G.nodes[i]->links[k]->a;
////            link.b=G.nodes[i]->links[k]->b;
////            link.weight=G.nodes[i]->links[k]->weight;
//            for(long j=0;j<G.nodes[i]->links[k]->a->links.size();j++){
//                double angle=Functions::getAngle(G.nodes[i]->links[k]->a->links[j]->b->location,G.nodes[i]->links[k]->a->location, G.nodes[i]->links[k]->b->location);
//                if(Functions::abs(angle)>180-tolerance&&j!=k){
//                    if(G.nodes[i]->links[k]->weight<G.nodes[i]->links[k]->a->links[j]->weight){
//                        accepted[G.nodes[i]->links[k]->a->links[j]->id]=false;
////                        G.removeLink(G.nodes[i]->links[k]->a->links[j]->id);
////                        j=0;
////                        k=0;
////                        std::stringstream ss;
////                        ss<<link.a->links[j]->a->id<<";"<<link.a->links[j]->b->id;
////                        acceptTransition[ss.str()]=false;
////                        ss.str("");
////                        ss<<link.a->links[j]->b->id<<";"<<link.a->links[j]->a->id;
////                        acceptTransition[ss.str()]=false;
//
//                    }else{
////                        G.removeLink(G.nodes[i]->links[k]->id);
//                        accepted[G.nodes[i]->links[k]->id]=false;
////                        j=0;
////                        k=0;
////                        std::stringstream ss;
////                        ss<<link.a->id<<";"<<link.b->id;
////                        acceptTransition[ss.str()]=false;
////                        ss.str("");
////                        ss<<link.b->id<<";"<<link.a->id;
////                        acceptTransition[ss.str()]=false;
//                    }
//                }else{
//                }
//            }
//        }
//    }
//    idA.clear();
//    idB.clear();
//    for(long i=0;i<G.links.size();i++){
////        std::stringstream ss;
////        ss<<G.links[i]->a->id<<";"<<G.links[i]->b->id;
////        if(acceptTransition[ss.str()]){
//        if(accepted[G.links[i]->a->id]){
//            idA.push_back(G.links[i]->a->id);
//            idB.push_back(G.links[i]->b->id);
//            weights.push_back(G.links[i]->weight);
//        }
////        }
//    }
//    delaunay.clear();
//    delaunay.resize(2);
//    delaunay[0]=idA;
//    delaunay[1]=idB;
//    G.finishedAddingNodes();
//}



void Grafo::cleanDuplicatedLinks(Grafo* G,double tolerance,std::vector<long> &linksRemoved,bool keepTrackChanges){


    std::set<long> idLinksToRemove;
    for(long i=0;i<G->nodes.size();i++){
        for(long k=0;k<G->nodes[i]->links.size();k++){

            for(long j=0;j<G->nodes[i]->links.size();j++){
//                Nodo* node=G->nodes[i];
                double angle=Functions::getAngle(G->nodes[i]->links[j]->getOtherNode(G->nodes[i])->location,G->nodes[i]->location, G->nodes[i]->links[k]->getOtherNode(G->nodes[i])->location);
//                std::cout<<i<<" angle in clean duplicatedLinks "<<angle<<" "<<j<<" "<<k<<'\n';






                if(Functions::abs(angle)>180-tolerance&&j!=k){
                    if(G->nodes[i]->links[k]->weight<G->nodes[i]->links[j]->weight){
                        if(keepTrackChanges){
                            linksRemoved.push_back(G->nodes[i]->links[j]->originalID);
                        }
//                        G->removeLink(G->nodes[i]->links[j]->id,false);
//
//                        j--;
//                        k--;
                        idLinksToRemove.insert(G->nodes[i]->links[j]->id);
                    }else{
                        if(keepTrackChanges){
                            linksRemoved.push_back(G->nodes[i]->links[k]->originalID);
                        }
//                        G->removeLink(G->nodes[i]->links[k]->id,false);
//
//                        j--;
//                        k--;
                        idLinksToRemove.insert(G->nodes[i]->links[k]->id);

                    }
                }else{
                }
            }
        }
    }
//    std::cout<<"size ifLinksToRemove "<<idLinksToRemove.size()<<'\n';
    G->removeLinks(idLinksToRemove);
//    G->correctIdsLinks();

}







//int myints[]= {77,30,16,2,30,30};
//
//for(long i=0;i<6;i++){
//    Number number;
//    number.value=myints[i];
//    number.id=i;
//
//    linesIdsByYCoordinate.insert(number);
//}
//
//
//
//Number searchNumber;
//searchNumber.value=30;
//
//std::pair<It,It> ret = linesIdsByYCoordinate.equal_range(searchNumber);
//
//
//
//if(ret.first!=linesIdsByYCoordinate.begin()){
//    std::cout<<"predecessor "<<((std::prev(ret.first)))->value<<'\n';
//    }
//
//    std::cout<<"last element "<<((std::prev(ret.second)))->value<<'\n';
//
//
//    std::cout<<"numberElements "<<std::distance(ret.first,ret.second)<<'\n';
//
//    if(ret.second!=linesIdsByYCoordinate.end()){
//        std::cout<<"sucessor "<<((ret.second))->value<<'\n';
//    }
//
//
//    std::multiset<Number>::iterator itlow,itup;
//    searchNumber.value=25;
//    itlow = linesIdsByYCoordinate.lower_bound (searchNumber);
//    searchNumber.value=45;
//    itup = linesIdsByYCoordinate.upper_bound (searchNumber);
//
//    std::cout << "range contains:";
//    for (It it=itlow; it!=itup; ++it)
//    std::cout << ' ' << (it)->value;
//    std::cout << '\n';





void Grafo::forcePlanaritylineSweep(Grafo* G,std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > &pairsOldIdNewIds,bool keepTrackChanges){
    if(!G->isPlanar){
        typedef std::multiset<Number>::iterator It;
        typedef std::multiset<Number> BST;

        std::vector<std::vector<long> > idsIntersected;
        std::vector<Point2d> intersections;

        BST ys;

        Heap<Number*> events;

        std::vector<std::vector<Number*> > xsById;
        for(long i=0;i<G->links.size();i++){
            Nodo* nodeA;
            Nodo* nodeB;
            nodeA=G->links[i]->A();
            nodeB=G->links[i]->B();
            bool vertical=false;
            if(nodeA->location.x>nodeB->location.x){
//                G->links[i]->checkDirection(!G->links[i]->inverted);
                nodeA=G->links[i]->B();
                nodeB=G->links[i]->A();
            }else if(nodeA->location.x==nodeB->location.x){
                vertical=true;
            }

            std::vector<Number*> pair;
            pair.resize(2);

            Number* x1=new Number();


            x1->value=nodeA->location.x;
            x1->id=G->links[i]->id;
            if(!vertical){
                x1->qualifier=0;
            }else{
                x1->qualifier=2;
            }
            pair[0]=(x1);

            Number* x2=new Number();



            if(!vertical){
                x2->qualifier=1;
                x2->value=nodeB->location.x;
                x2->id=G->links[i]->id;
            }else{
                x2->qualifier=2;
            }
            pair[1]=x2;
            xsById.push_back(pair);

            events.push(x1);
            events.push(x2);

        }

        while(events.size()>0){
    //        std::cout<<"size of events: "<<events.size()<<'\n';
            Number* event=events.pop();
            if(event->id!=-1){
    //            std::cout<<"Event x: "<<event->value<<'\n';
                if(ys.size()==0){
                    Number y;
                    if(event->qualifier==0){
                        y.value=G->links[event->id]->A()->location.y;
                        y.id=G->links[event->id]->id;
                        ys.insert(y);
                    }else if (event->qualifier==1){

                    }else{

                    }

                }else{
                    Number y;
                    if(event->qualifier==0){
                        y.value=G->links[event->id]->A()->location.y;
                        y.id=G->links[event->id]->id;
                        ys.insert(y);


                        std::pair<It,It> range = ys.equal_range(y);

                        It predecessor;
                        It predecessorMin;
                        if(range.first!=ys.begin()){
                            predecessor=((std::prev(range.first)));
                            Number number=(*predecessor);
                            std::pair<It,It> rangePredecessor = ys.equal_range(number);
                            predecessorMin=rangePredecessor.first;
                        }else{
                            predecessorMin=ys.begin();
                        }

                        It succesor;
                        It succesorMax;
                        succesor=(range.second);


                        It succesorSuccesor;
                        if(succesor!=ys.end()){
                            Number number=(*succesor);
                            std::pair<It,It> rangeSuccesor = ys.equal_range(number);
                            succesorMax=std::prev(rangeSuccesor.second);
                            succesorSuccesor=std::next(succesorMax);
                        }else{
                            succesorSuccesor=succesor;
                        }

                        for (It it=predecessorMin; it!=succesorSuccesor; ++it){
                            if((*it).id!=y.id){
                                Nodo* nodeInCommon=G->links[y.id]->commonNode(G->links[(*it).id]);
                                if(nodeInCommon==NULL){
                                    Point2d intersection;
                                    bool valid;
                                    Functions::intersection(G->links[y.id]->A()->location, G->links[y.id]->B()->location, G->links[(*it).id]->A()->location, G->links[(*it).id]->B()->location, intersection, valid);
                                    if(valid){
                                        std::vector<long> idsInIntersection;
                                        idsInIntersection.push_back(y.id);
                                        idsInIntersection.push_back((*it).id);
                                        idsIntersected.push_back(idsInIntersection);
                                        intersections.push_back(intersection);
                                    }
                                }
                            }
                        }


                    }else if (event->qualifier==1){
                        Number yA;
                        yA.value=G->links[event->id]->A()->location.y;
                        yA.id=G->links[event->id]->id;
                        y.value=G->links[event->id]->B()->location.y;
                        y.id=G->links[event->id]->id;
                        std::pair<It,It> range = ys.equal_range(yA);
                        for (It it=range.first; it!=range.second; ++it){
                            if((*it).id==yA.id){
                                ys.erase(it);
                                break;

                            }
                        }

                        range = ys.equal_range(y);

                        It predecessor;
                        It predecessorMin;
                        if(range.first!=ys.begin()){
                            predecessor=((std::prev(range.first)));
                            Number number=(*predecessor);
                            std::pair<It,It> rangePredecessor = ys.equal_range(number);
                            predecessorMin=rangePredecessor.first;
                        }else{
                            predecessorMin=ys.begin();
                        }

                        It succesor;
                        It succesorMax;
                        succesor=(range.second);


                        It succesorSuccesor;
                        if(succesor!=ys.end()){
                            Number number=(*succesor);
                            std::pair<It,It> rangeSuccesor = ys.equal_range(number);
                            succesorMax=std::prev(rangeSuccesor.second);
                            succesorSuccesor=std::next(succesorMax);
                        }else{
                            succesorSuccesor=succesor;
                        }

                        for (It it=predecessorMin; it!=succesorSuccesor; ++it){
                            for (It it2=predecessorMin; it2!=succesorSuccesor; ++it2){
                                if((*it).id!=(*it2).id){
                                    Nodo* nodeInCommon=G->links[(*it2).id]->commonNode(G->links[(*it).id]);
                                    if(nodeInCommon==NULL){
                                        Point2d intersection;
                                        bool valid;
                                        Functions::intersection(G->links[(*it2).id]->A()->location, G->links[(*it2).id]->B()->location, G->links[(*it).id]->A()->location, G->links[(*it).id]->B()->location, intersection, valid);
                                        if(valid){
                                            std::vector<long> idsInIntersection;
                                            idsInIntersection.push_back((*it2).id);
                                            idsInIntersection.push_back((*it).id);
                                            idsIntersected.push_back(idsInIntersection);
                                            intersections.push_back(intersection);

                                        }
                                    }
                                }
                            }
                        }


                    }else{
                        //vertical line
                        Number yA;

                        yA.value=G->links[event->id]->A()->location.y;
                        yA.id=G->links[event->id]->id;
                        y.value=G->links[event->id]->B()->location.y;
                        y.id=G->links[event->id]->id;
                        std::pair<It,It> range = ys.equal_range(yA);
                        for (It it=range.first; it!=range.second; ++it){
                            if((*it).id==yA.id){
                                ys.erase(it);
                            }
                        }
                        It itA = ys.lower_bound (yA);
                        It itB = ys.upper_bound (y);
                        if(y.value>yA.value){
                            range=std::pair<It,It>(itA,itB);
                        }else{
                            range=std::pair<It,It>(itB,itA);
                        }
    //                    range = ys.equal_range(y);

                        It predecessor;
                        It predecessorMin;
                        if(range.first!=ys.begin()){
                            predecessor=((std::prev(range.first)));
                            Number number=(*predecessor);
                            std::pair<It,It> rangePredecessor = ys.equal_range(number);
                            predecessorMin=rangePredecessor.first;
                        }else{
                            predecessorMin=ys.begin();
                        }

                        It succesor;
                        It succesorMax;
                        succesor=(range.second);


                        It succesorSuccesor;
                        if(succesor!=ys.end()){
                            Number number=(*succesor);
                            std::pair<It,It> rangeSuccesor = ys.equal_range(number);
                            succesorMax=std::prev(rangeSuccesor.second);
                            succesorSuccesor=std::next(succesorMax);
                        }else{
                            succesorSuccesor=succesor;
                        }

                        for (It it=predecessorMin; it!=succesorSuccesor; ++it){
                            if((*it).id!=y.id){
                                Nodo* nodeInCommon=G->links[y.id]->commonNode(G->links[(*it).id]);
                                if(nodeInCommon==NULL){
                                    Point2d intersection;
                                    bool valid;
                                    Functions::intersection(G->links[y.id]->A()->location, G->links[y.id]->B()->location, G->links[(*it).id]->A()->location, G->links[(*it).id]->B()->location, intersection, valid);
                                    if(valid){
                                        std::vector<long> idsInIntersection;
                                        idsInIntersection.push_back(y.id);
                                        idsInIntersection.push_back((*it).id);
                                        idsIntersected.push_back(idsInIntersection);
                                        intersections.push_back(intersection);
                                    }
                                }
                            }
                        }

                    }





                }
            }

    //        delete event;
    //        event=NULL;
        }

        for(long i=0;i<xsById.size();i++){
            if(xsById[i][0]!=NULL){
                delete xsById[i][0];
                xsById[i][0]=NULL;
            }
            if(xsById[i][1]!=NULL){
                delete xsById[i][1];
                xsById[i][1]=NULL;
            }
        }

        Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
    }
    G->isPlanar=true;
}







void Grafo::forcePlanarityPlaneSweep(Grafo* G,int MEMORYorSPEED,std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > &pairsOldIdNewIds,bool keepTrackChanges){
    if(!G->isPlanar){
        std::vector<std::vector<long> > idsIntersected;
        std::vector<Point2d> intersections;
        long maxDegree=-std::numeric_limits<long>::max();
        long depthLimit=9;
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        maxDegree=2;

        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;

        for(long i=0;i<G->nodes.size();i++){
            if(G->nodes[i]->location.x>maxX){
                maxX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y>maxY){
                maxY=G->nodes[i]->location.y;
            }
            if(G->nodes[i]->location.x<minX){
                minX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y<minY){
                minY=G->nodes[i]->location.y;
            }
        }

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;
        std::deque<double> maxXs,minXs,maxYs,minYs;
    //    std::queue<long> numbers_DifferentLines;
        std::deque<long> depths;
        std::deque<std::vector<long> > idsLines;
        std::deque<std::vector<long> > idsNodes;
        std::deque<std::deque<int> > quadrantsToExplore;


        double a_maxX,a_maxY,a_minX,a_minY;
        long depth;


        a_maxX=maxX;
        a_maxY=maxY;
        a_minX=minX;
        a_minY=minY;
        maxXs.push_front(maxX);
        minXs.push_front(minX);
        maxYs.push_front(maxY);
        minYs.push_front(minY);
        std::vector<long> idsLinesTemp;
        std::vector<long> idsNodesTemp;
        std::deque<int> quadrantsToExploreTemp;
        for(long i=0;i<G->links.size();i++){
            idsLinesTemp.push_back(G->links[i]->id);
        }
        for(long i=0;i<G->nodes.size();i++){
            idsNodesTemp.push_back(G->nodes[i]->id);
        }
        for(int i=0;i<4;i++){
            quadrantsToExploreTemp.push_front(i);
        }
        idsLines.push_front(idsLinesTemp);
        idsNodes.push_front(idsNodesTemp);
        if(MEMORYorSPEED==MEMORY){
            quadrantsToExplore.push_front(quadrantsToExploreTemp);
        }
    //    numbers_DifferentLines.push(idsLinesTemp.size());
        depths.push_front(0);

        double gridSizeX=((maxX-minX));

        double gridSizeY=((maxY-minY));



        while (maxXs.size()>0){
            maxX=maxXs.front();
            maxY=maxYs.front();
            minX=minXs.front();
            minY=minYs.front();
            if(MEMORYorSPEED==MEMORY){
                quadrantsToExploreTemp=quadrantsToExplore.front();
            }

            idsLinesTemp=idsLines.front();
            idsNodesTemp=idsNodes.front();
    //        numLines=numbers_DifferentLines.front();
            depth=depths.front();

    //        std::cout<<depth<<'\n';
            int currentQuadrant = -1;
           if(MEMORYorSPEED==MEMORY){
                quadrantsToExplore.pop_front();
                currentQuadrant=quadrantsToExploreTemp.front();
                quadrantsToExploreTemp.pop_front();

                quadrantsToExplore.push_front(quadrantsToExploreTemp);
                if(quadrantsToExploreTemp.size()==0){
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
                    quadrantsToExplore.pop_front();
                }

            }else{
                maxXs.pop_front();
                maxYs.pop_front();
                minXs.pop_front();
                minYs.pop_front();

                idsLines.pop_front();
                idsNodes.pop_front();
                //        numbers_DifferentLines.pop();
                depths.pop_front();
    //            quadrantsToExplore.pop_front();
            }




            gridSizeX=((maxX-minX));

            gridSizeY=((maxY-minY));
            bool STOP=false;
            if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
                STOP=true;
            }
            if(!STOP&&((idsLinesTemp.size()>=2&&idsLinesTemp.size()<=maxDegree&&depth<=depthLimit)||(depth>depthLimit&&idsLinesTemp.size()>=2))){
               // checkIntersection;
                for(long i=0;i<idsLinesTemp.size()-1;i++){
                    for(long j=i+1;j<idsLinesTemp.size();j++){
                        long it=idsLinesTemp[i];
                        long it2=idsLinesTemp[j];
                        if(it!=it2){
    //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
                            Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
                            if(commonNode==NULL){
                                Point2d intersection;
                                bool valid;

                                Functions::intersection(G->links[it]->A()->location, G->links[it]->B()->location, G->links[it2]->A()->location, G->links[it2]->B()->location, intersection, valid);
                                if(valid){
                                    std::vector<long> idsIntersectedTemp;
                                    idsIntersectedTemp.reserve(2);
                                    idsIntersectedTemp.push_back(it);
                                    idsIntersectedTemp.push_back(it2);
                                    idsIntersected.push_back(idsIntersectedTemp);
                                    intersections.push_back(intersection);
    //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
                                }
                            }
                        }

                    }
                }


            }else if(!STOP&&idsLinesTemp.size()>=2){

                std::vector<std::vector<long> > idsLinesPerQuadrant;
                std::vector<std::vector<long> > idsNodesPerQuadrant;
    //            std::vector<long > numLinesPerQuadrant;
    //            numLinesPerQuadrant.resize(4,0);
                idsLinesPerQuadrant.resize(4,std::vector<long>());
                idsNodesPerQuadrant.resize(4,std::vector<long>());
                Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                for(long i=0;i<idsNodesTemp.size();i++){
                    long quadrant=Functions::getQuadrant(center, G->nodes[idsNodesTemp[i]]->location);

                    if((quadrant==currentQuadrant||MEMORYorSPEED==SPEED)&&Functions::inBoundaryOfASquare(center, G->nodes[idsNodesTemp[i]]->location, gridSizeX, gridSizeY)){
                        idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                    }
                }

                for(long i=0;i<idsLinesTemp.size();i++){
    //                for(long j=0;j<idsLinesTemp.size();j++){
                        long it=idsLinesTemp[i];

    //                if(depth==1&&it+1==336){
    //                    std::cout<<"check issue";
    //                }
                    std::vector<long> quadrants=Functions::getQuadrantsLine(center, G->links[it]->A()->location, G->links[it]->B()->location, gridSizeX, gridSizeY);
    //                if(quadrants.size()==0){
    //                    std::cout<<"wtf!"<<'\n';
    //                }
    //                if(quadrants.size()==0){
    //                    std::cout<<"Depth: "<<depth<<'\n';
    //                    std::cout<<"id: "<<it+1<<'\n';
    //                }

                    for(long j=0;j<quadrants.size();j++){
                        if(quadrants[j]==currentQuadrant||MEMORYorSPEED==SPEED){
                            idsLinesPerQuadrant[quadrants[j]].push_back(it);
                        }
    //                    numLinesPerQuadrant[itSet]++;
                    }
                }

                int startLoop=0;
                int endLoop=4;

                if(MEMORYorSPEED==MEMORY){
                    startLoop=currentQuadrant;
                    endLoop=currentQuadrant+1;
                }else if (MEMORYorSPEED==SPEED){
                    startLoop=0;
                    endLoop=4;
                }

                for(long i=startLoop;i<endLoop;i++){
    //            long i=currentQuadrant;{
                    double currentCol=i%2;
                    double currentRow=i/2;


    //                startingIndex=1;
                    double gridSizeX_temp=((maxX-minX)/2.0);
    //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                    double gridSizeY_temp=((maxY-minY)/2.0);
                    double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                    double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                    minXs.push_front(currentMinX);
                    minYs.push_front(currentMinY);
                    maxXs.push_front(currentMinX+gridSizeX_temp);
                    maxYs.push_front(currentMinY+gridSizeY_temp);
                    idsLines.push_front(idsLinesPerQuadrant[i]);
                    idsNodes.push_front(idsNodesPerQuadrant[i]);
    //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                    depths.push_front(depth+1);

                    if(MEMORYorSPEED==MEMORY){
                        std::deque<int> qTemp;
                        for(int i=0;i<4;i++){
                            qTemp.push_front(i);
                        }
                        quadrantsToExplore.push_front(qTemp);
                    }


    //                indexes.push(initialIndex);
                }
            }
        }

        Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
    }
    G->isPlanar=true;

}




void Grafo::intersectAGraphWithABoundary(Grafo* G,Grafo* boundary){
  std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
  bool keepTrackChanges=false;
  int MEMORYorSPEED=SPEED;
    // if(!G->isPlanar){
        std::vector<std::vector<long> > idsIntersected;
        std::vector<Point2d> intersections;
        long maxDegree=-std::numeric_limits<long>::max();
        long depthLimit=9;
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        maxDegree=2;

        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;

        for(long i=0;i<G->nodes.size();i++){
            if(G->nodes[i]->location.x>maxX){
                maxX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y>maxY){
                maxY=G->nodes[i]->location.y;
            }
            if(G->nodes[i]->location.x<minX){
                minX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y<minY){
                minY=G->nodes[i]->location.y;
            }
        }
        for(long i=0;i<boundary->nodes.size();i++){
            if(boundary->nodes[i]->location.x>maxX){
                maxX=boundary->nodes[i]->location.x;
            }
            if(boundary->nodes[i]->location.y>maxY){
                maxY=boundary->nodes[i]->location.y;
            }
            if(boundary->nodes[i]->location.x<minX){
                minX=boundary->nodes[i]->location.x;
            }
            if(boundary->nodes[i]->location.y<minY){
                minY=boundary->nodes[i]->location.y;
            }
        }

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;
        std::deque<double> maxXs,minXs,maxYs,minYs;
    //    std::queue<long> numbers_DifferentLines;
        std::deque<long> depths;
        std::deque<std::vector<long> > idsLines;
        std::deque<std::vector<long> > idsNodes;
        std::deque<std::deque<int> > quadrantsToExplore;


        double a_maxX,a_maxY,a_minX,a_minY;
        long depth;


        a_maxX=maxX;
        a_maxY=maxY;
        a_minX=minX;
        a_minY=minY;
        maxXs.push_front(maxX);
        minXs.push_front(minX);
        maxYs.push_front(maxY);
        minYs.push_front(minY);
        std::vector<long> idsLinesTemp;
        std::vector<long> idsNodesTemp;
        std::deque<int> quadrantsToExploreTemp;
        for(long i=0;i<G->links.size();i++){
            idsLinesTemp.push_back(G->links[i]->id);
        }
        for(long i=0;i<boundary->links.size();i++){
            idsLinesTemp.push_back(boundary->links[i]->id+G->links.size());
        }
        for(long i=0;i<G->nodes.size();i++){
            idsNodesTemp.push_back(G->nodes[i]->id);
        }
        for(long i=0;i<boundary->nodes.size();i++){
            idsNodesTemp.push_back(boundary->nodes[i]->id+G->nodes.size());
        }
        for(int i=0;i<4;i++){
            quadrantsToExploreTemp.push_front(i);
        }
        idsLines.push_front(idsLinesTemp);
        idsNodes.push_front(idsNodesTemp);
        if(MEMORYorSPEED==MEMORY){
            quadrantsToExplore.push_front(quadrantsToExploreTemp);
        }
    //    numbers_DifferentLines.push(idsLinesTemp.size());
        depths.push_front(0);

        double gridSizeX=((maxX-minX));

        double gridSizeY=((maxY-minY));



        while (maxXs.size()>0){
            maxX=maxXs.front();
            maxY=maxYs.front();
            minX=minXs.front();
            minY=minYs.front();
            if(MEMORYorSPEED==MEMORY){
                quadrantsToExploreTemp=quadrantsToExplore.front();
            }

            idsLinesTemp=idsLines.front();
            idsNodesTemp=idsNodes.front();
    //        numLines=numbers_DifferentLines.front();
            depth=depths.front();

    //        std::cout<<depth<<'\n';
            int currentQuadrant = -1;
           if(MEMORYorSPEED==MEMORY){
                quadrantsToExplore.pop_front();
                currentQuadrant=quadrantsToExploreTemp.front();
                quadrantsToExploreTemp.pop_front();

                quadrantsToExplore.push_front(quadrantsToExploreTemp);
                if(quadrantsToExploreTemp.size()==0){
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
                    quadrantsToExplore.pop_front();
                }

            }else{
                maxXs.pop_front();
                maxYs.pop_front();
                minXs.pop_front();
                minYs.pop_front();

                idsLines.pop_front();
                idsNodes.pop_front();
                //        numbers_DifferentLines.pop();
                depths.pop_front();
    //            quadrantsToExplore.pop_front();
            }




            gridSizeX=((maxX-minX));

            gridSizeY=((maxY-minY));
            bool STOP=false;
            bool linesFromBothGraphs=false;
            bool linesFromG=false;
            bool linesFromB=false;

            for(long i=0;i<idsLinesTemp.size();i++){
              if(idsLinesTemp[i]<G->links.size()){
                linesFromG=true;
              }else{
                linesFromB=true;
              }
            }
            if(linesFromB&&linesFromG){
              linesFromBothGraphs=true;
            }
            // if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
            if(!linesFromBothGraphs){
                STOP=true;
            }
            if(!STOP&&((idsLinesTemp.size()>=2&&idsLinesTemp.size()<=maxDegree&&depth<=depthLimit)||(depth>depthLimit&&idsLinesTemp.size()>=2))){
               // checkIntersection;
                for(long i=0;i<idsLinesTemp.size()-1;i++){
                    for(long j=i+1;j<idsLinesTemp.size();j++){
                        long it=idsLinesTemp[i];
                        long it2=idsLinesTemp[j];
                        if(it!=it2){
    //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
                            bool overLookIntersection=false;
                            if(it<G->links.size()&&it2<G->links.size()){
                                // Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
                                // if(commonNode==NULL){
                                //   overLookIntersection=false;
                                // }else{
                                //   overLookIntersection=true;
                                // }
                                overLookIntersection=true;
                            }
                            if(it>=G->links.size()&&it2>=G->links.size()){
                              overLookIntersection=true;
                            }
                            if(!overLookIntersection){
                              if(it<G->links.size()){
                                Nodo* a=boundary->links[it2-G->links.size()]->A();
                                Nodo* b=boundary->links[it2-G->links.size()]->B();
                                Nodo* ag=G->getNodeByLocation(a->location);
                                Nodo* bg=G->getNodeByLocation(b->location);
                                if(ag==NULL&&bg==NULL){
                                  overLookIntersection=false;
                                }else{
                                  overLookIntersection=true;
                                }
                              }else{
                                Nodo* a=boundary->links[it-G->links.size()]->A();
                                Nodo* b=boundary->links[it-G->links.size()]->B();
                                Nodo* ag=G->getNodeByLocation(a->location);
                                Nodo* bg=G->getNodeByLocation(b->location);
                                if(ag==NULL&&bg==NULL){
                                  overLookIntersection=false;
                                }else{
                                  overLookIntersection=true;
                                }
                              }
                            }

                            if(!overLookIntersection){
                                Link* linka;
                                Link* linkb;
                                if(it<G->links.size()){
                                  linka=G->links[it];
                                }else{
                                  linka=boundary->links[it-G->links.size()];
                                }
                                if(it2<G->links.size()){
                                  linkb=G->links[it2];
                                }else{
                                  linkb=boundary->links[it2-G->links.size()];
                                }
                                Point2d intersection;
                                bool valid;

                                Functions::intersection(linka->A()->location, linka->B()->location, linkb->A()->location, linkb->B()->location, intersection, valid);
                                // std::cout<<"is intersection valid "<<valid<<'\n';
                                if(valid){
                                    std::vector<long> idsIntersectedTemp;
                                    // idsIntersectedTemp.reserve(2);
                                    if(it<G->links.size()){
                                      idsIntersectedTemp.push_back(it);
                                    }
                                    if(it2<G->links.size()){
                                      idsIntersectedTemp.push_back(it2);
                                    }
                                    idsIntersected.push_back(idsIntersectedTemp);
                                    intersections.push_back(intersection);
    //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
                                }
                            }
                        }

                    }
                }


            }else if(!STOP&&idsLinesTemp.size()>=2){
              // std::cout<<"next level"<<'\n';

                std::vector<std::vector<long> > idsLinesPerQuadrant;
                std::vector<std::vector<long> > idsNodesPerQuadrant;
    //            std::vector<long > numLinesPerQuadrant;
    //            numLinesPerQuadrant.resize(4,0);
                idsLinesPerQuadrant.resize(4,std::vector<long>());
                idsNodesPerQuadrant.resize(4,std::vector<long>());
                Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                for(long i=0;i<idsNodesTemp.size();i++){
                    Nodo* node;
                    if(idsNodesTemp[i]>=G->nodes.size()){
                      node=boundary->nodes[idsNodesTemp[i]-G->nodes.size()];
                    }else{
                      node=G->nodes[idsNodesTemp[i]];
                    }
                    long quadrant=Functions::getQuadrant(center, node->location);

                    if((quadrant==currentQuadrant||MEMORYorSPEED==SPEED)&&Functions::inBoundaryOfASquare(center, node->location, gridSizeX, gridSizeY)){
                        idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                    }
                }

                for(long i=0;i<idsLinesTemp.size();i++){
    //                for(long j=0;j<idsLinesTemp.size();j++){
                        long it=idsLinesTemp[i];

    //                if(depth==1&&it+1==336){
    //                    std::cout<<"check issue";
    //                }
                    Nodo* a;
                    Nodo* b;
                    if(it>=G->links.size()){
                      a=boundary->links[it-G->links.size()]->A();
                      b=boundary->links[it-G->links.size()]->B();
                    }else{
                      a=G->links[it]->A();
                      b=G->links[it]->B();
                    }

                    std::vector<long> quadrants=Functions::getQuadrantsLine(center, a->location, b->location, gridSizeX, gridSizeY);
    //                if(quadrants.size()==0){
    //                    std::cout<<"wtf!"<<'\n';
    //                }
    //                if(quadrants.size()==0){
    //                    std::cout<<"Depth: "<<depth<<'\n';
    //                    std::cout<<"id: "<<it+1<<'\n';
    //                }

                    for(long j=0;j<quadrants.size();j++){
                        if(quadrants[j]==currentQuadrant||MEMORYorSPEED==SPEED){
                            idsLinesPerQuadrant[quadrants[j]].push_back(it);
                        }
    //                    numLinesPerQuadrant[itSet]++;
                    }
                }

                int startLoop=0;
                int endLoop=4;

                if(MEMORYorSPEED==MEMORY){
                    startLoop=currentQuadrant;
                    endLoop=currentQuadrant+1;
                }else if (MEMORYorSPEED==SPEED){
                    startLoop=0;
                    endLoop=4;
                }

                for(long i=startLoop;i<endLoop;i++){
    //            long i=currentQuadrant;{
                    double currentCol=i%2;
                    double currentRow=i/2;


    //                startingIndex=1;
                    double gridSizeX_temp=((maxX-minX)/2.0);
    //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                    double gridSizeY_temp=((maxY-minY)/2.0);
                    double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                    double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                    minXs.push_front(currentMinX);
                    minYs.push_front(currentMinY);
                    maxXs.push_front(currentMinX+gridSizeX_temp);
                    maxYs.push_front(currentMinY+gridSizeY_temp);
                    idsLines.push_front(idsLinesPerQuadrant[i]);
                    idsNodes.push_front(idsNodesPerQuadrant[i]);
    //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                    depths.push_front(depth+1);

                    if(MEMORYorSPEED==MEMORY){
                        std::deque<int> qTemp;
                        for(int i=0;i<4;i++){
                            qTemp.push_front(i);
                        }
                        quadrantsToExplore.push_front(qTemp);
                    }


    //                indexes.push(initialIndex);
                }
            }
        }

        Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);

    // }
    // G->isPlanar=true;

}




InterfaceIntersectionObject Grafo::intersectAGraphWithAnother(Grafo* G,Grafo* G2){
  Grafo* boundary=G2;
  std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
  bool keepTrackChanges=false;
  int MEMORYorSPEED=SPEED;
    // if(!G->isPlanar){
        std::vector<std::vector<long> > idsIntersected;
        std::vector<Point2d> intersections;
        long maxDegree=-std::numeric_limits<long>::max();
        long depthLimit=9;
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        maxDegree=2;

        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;

        for(long i=0;i<G->nodes.size();i++){
            if(G->nodes[i]->location.x>maxX){
                maxX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y>maxY){
                maxY=G->nodes[i]->location.y;
            }
            if(G->nodes[i]->location.x<minX){
                minX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y<minY){
                minY=G->nodes[i]->location.y;
            }
        }
        for(long i=0;i<boundary->nodes.size();i++){
            if(boundary->nodes[i]->location.x>maxX){
                maxX=boundary->nodes[i]->location.x;
            }
            if(boundary->nodes[i]->location.y>maxY){
                maxY=boundary->nodes[i]->location.y;
            }
            if(boundary->nodes[i]->location.x<minX){
                minX=boundary->nodes[i]->location.x;
            }
            if(boundary->nodes[i]->location.y<minY){
                minY=boundary->nodes[i]->location.y;
            }
        }

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;
        std::deque<double> maxXs,minXs,maxYs,minYs;
    //    std::queue<long> numbers_DifferentLines;
        std::deque<long> depths;
        std::deque<std::vector<long> > idsLines;
        std::deque<std::vector<long> > idsNodes;
        std::deque<std::deque<int> > quadrantsToExplore;


        double a_maxX,a_maxY,a_minX,a_minY;
        long depth;


        a_maxX=maxX;
        a_maxY=maxY;
        a_minX=minX;
        a_minY=minY;
        maxXs.push_front(maxX);
        minXs.push_front(minX);
        maxYs.push_front(maxY);
        minYs.push_front(minY);
        std::vector<long> idsLinesTemp;
        std::vector<long> idsNodesTemp;
        std::deque<int> quadrantsToExploreTemp;
        for(long i=0;i<G->links.size();i++){
            idsLinesTemp.push_back(G->links[i]->id);
        }
        for(long i=0;i<boundary->links.size();i++){
            idsLinesTemp.push_back(boundary->links[i]->id+G->links.size());
        }
        for(long i=0;i<G->nodes.size();i++){
            idsNodesTemp.push_back(G->nodes[i]->id);
        }
        for(long i=0;i<boundary->nodes.size();i++){
            idsNodesTemp.push_back(boundary->nodes[i]->id+G->nodes.size());
        }
        for(int i=0;i<4;i++){
            quadrantsToExploreTemp.push_front(i);
        }
        idsLines.push_front(idsLinesTemp);
        idsNodes.push_front(idsNodesTemp);
        if(MEMORYorSPEED==MEMORY){
            quadrantsToExplore.push_front(quadrantsToExploreTemp);
        }
    //    numbers_DifferentLines.push(idsLinesTemp.size());
        depths.push_front(0);

        double gridSizeX=((maxX-minX));

        double gridSizeY=((maxY-minY));



        while (maxXs.size()>0){
            maxX=maxXs.front();
            maxY=maxYs.front();
            minX=minXs.front();
            minY=minYs.front();
            if(MEMORYorSPEED==MEMORY){
                quadrantsToExploreTemp=quadrantsToExplore.front();
            }

            idsLinesTemp=idsLines.front();
            idsNodesTemp=idsNodes.front();
    //        numLines=numbers_DifferentLines.front();
            depth=depths.front();

    //        std::cout<<depth<<'\n';
            int currentQuadrant = -1;
           if(MEMORYorSPEED==MEMORY){
                quadrantsToExplore.pop_front();
                currentQuadrant=quadrantsToExploreTemp.front();
                quadrantsToExploreTemp.pop_front();

                quadrantsToExplore.push_front(quadrantsToExploreTemp);
                if(quadrantsToExploreTemp.size()==0){
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
                    quadrantsToExplore.pop_front();
                }

            }else{
                maxXs.pop_front();
                maxYs.pop_front();
                minXs.pop_front();
                minYs.pop_front();

                idsLines.pop_front();
                idsNodes.pop_front();
                //        numbers_DifferentLines.pop();
                depths.pop_front();
    //            quadrantsToExplore.pop_front();
            }




            gridSizeX=((maxX-minX));

            gridSizeY=((maxY-minY));
            bool STOP=false;
            bool linesFromBothGraphs=false;
            bool linesFromG=false;
            bool linesFromB=false;

            for(long i=0;i<idsLinesTemp.size();i++){
              if(idsLinesTemp[i]<G->links.size()){
                linesFromG=true;
              }else{
                linesFromB=true;
              }
            }
            if(linesFromB&&linesFromG){
              linesFromBothGraphs=true;
            }
            // if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
            if(!linesFromBothGraphs){
                STOP=true;
            }
            if(!STOP&&((idsLinesTemp.size()>=2&&idsLinesTemp.size()<=maxDegree&&depth<=depthLimit)||(depth>depthLimit&&idsLinesTemp.size()>=2))){
               // checkIntersection;
                for(long i=0;i<idsLinesTemp.size()-1;i++){
                    for(long j=i+1;j<idsLinesTemp.size();j++){
                        long it=idsLinesTemp[i];
                        long it2=idsLinesTemp[j];
                        if(it!=it2){
    //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
                            bool overLookIntersection=false;
                            if(it<G->links.size()&&it2<G->links.size()){
                                // Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
                                // if(commonNode==NULL){
                                //   overLookIntersection=false;
                                // }else{
                                //   overLookIntersection=true;
                                // }
                                overLookIntersection=true;
                            }
                            if(it>=G->links.size()&&it2>=G->links.size()){
                              overLookIntersection=true;
                            }
                            if(!overLookIntersection){
                              if(it<G->links.size()){
                                Nodo* a=boundary->links[it2-G->links.size()]->A();
                                Nodo* b=boundary->links[it2-G->links.size()]->B();
                                Nodo* ag=G->getNodeByLocation(a->location);
                                Nodo* bg=G->getNodeByLocation(b->location);
                                if(ag==NULL&&bg==NULL){
                                  overLookIntersection=false;
                                }else{
                                  overLookIntersection=true;
                                }
                              }else{
                                Nodo* a=boundary->links[it-G->links.size()]->A();
                                Nodo* b=boundary->links[it-G->links.size()]->B();
                                Nodo* ag=G->getNodeByLocation(a->location);
                                Nodo* bg=G->getNodeByLocation(b->location);
                                if(ag==NULL&&bg==NULL){
                                  overLookIntersection=false;
                                }else{
                                  overLookIntersection=true;
                                }
                              }
                            }

                            if(!overLookIntersection){
                                Link* linka;
                                Link* linkb;
                                if(it<G->links.size()){
                                  linka=G->links[it];
                                }else{
                                  linka=boundary->links[it-G->links.size()];
                                }
                                if(it2<G->links.size()){
                                  linkb=G->links[it2];
                                }else{
                                  linkb=boundary->links[it2-G->links.size()];
                                }
                                Point2d intersection;
                                bool valid;

                                Functions::intersection(linka->A()->location, linka->B()->location, linkb->A()->location, linkb->B()->location, intersection, valid);
                                // std::cout<<"is intersection valid "<<valid<<'\n';
                                if(valid){
                                    std::vector<long> idsIntersectedTemp;
                                    // idsIntersectedTemp.reserve(2);
                                    if(it<G->links.size()){
                                      idsIntersectedTemp.push_back(it);
                                    }
                                    if(it2<G->links.size()){
                                      idsIntersectedTemp.push_back(it2);
                                    }
                                    idsIntersected.push_back(idsIntersectedTemp);
                                    intersections.push_back(intersection);
    //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
                                }
                            }
                        }

                    }
                }


            }else if(!STOP&&idsLinesTemp.size()>=2){
              // std::cout<<"next level"<<'\n';

                std::vector<std::vector<long> > idsLinesPerQuadrant;
                std::vector<std::vector<long> > idsNodesPerQuadrant;
    //            std::vector<long > numLinesPerQuadrant;
    //            numLinesPerQuadrant.resize(4,0);
                idsLinesPerQuadrant.resize(4,std::vector<long>());
                idsNodesPerQuadrant.resize(4,std::vector<long>());
                Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                for(long i=0;i<idsNodesTemp.size();i++){
                    Nodo* node;
                    if(idsNodesTemp[i]>=G->nodes.size()){
                      node=boundary->nodes[idsNodesTemp[i]-G->nodes.size()];
                    }else{
                      node=G->nodes[idsNodesTemp[i]];
                    }
                    long quadrant=Functions::getQuadrant(center, node->location);

                    if((quadrant==currentQuadrant||MEMORYorSPEED==SPEED)&&Functions::inBoundaryOfASquare(center, node->location, gridSizeX, gridSizeY)){
                        idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                    }
                }

                for(long i=0;i<idsLinesTemp.size();i++){
    //                for(long j=0;j<idsLinesTemp.size();j++){
                        long it=idsLinesTemp[i];

    //                if(depth==1&&it+1==336){
    //                    std::cout<<"check issue";
    //                }
                    Nodo* a;
                    Nodo* b;
                    if(it>=G->links.size()){
                      a=boundary->links[it-G->links.size()]->A();
                      b=boundary->links[it-G->links.size()]->B();
                    }else{
                      a=G->links[it]->A();
                      b=G->links[it]->B();
                    }

                    std::vector<long> quadrants=Functions::getQuadrantsLine(center, a->location, b->location, gridSizeX, gridSizeY);
    //                if(quadrants.size()==0){
    //                    std::cout<<"wtf!"<<'\n';
    //                }
    //                if(quadrants.size()==0){
    //                    std::cout<<"Depth: "<<depth<<'\n';
    //                    std::cout<<"id: "<<it+1<<'\n';
    //                }

                    for(long j=0;j<quadrants.size();j++){
                        if(quadrants[j]==currentQuadrant||MEMORYorSPEED==SPEED){
                            idsLinesPerQuadrant[quadrants[j]].push_back(it);
                        }
    //                    numLinesPerQuadrant[itSet]++;
                    }
                }

                int startLoop=0;
                int endLoop=4;

                if(MEMORYorSPEED==MEMORY){
                    startLoop=currentQuadrant;
                    endLoop=currentQuadrant+1;
                }else if (MEMORYorSPEED==SPEED){
                    startLoop=0;
                    endLoop=4;
                }

                for(long i=startLoop;i<endLoop;i++){
    //            long i=currentQuadrant;{
                    double currentCol=i%2;
                    double currentRow=i/2;


    //                startingIndex=1;
                    double gridSizeX_temp=((maxX-minX)/2.0);
    //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                    double gridSizeY_temp=((maxY-minY)/2.0);
                    double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                    double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                    minXs.push_front(currentMinX);
                    minYs.push_front(currentMinY);
                    maxXs.push_front(currentMinX+gridSizeX_temp);
                    maxYs.push_front(currentMinY+gridSizeY_temp);
                    idsLines.push_front(idsLinesPerQuadrant[i]);
                    idsNodes.push_front(idsNodesPerQuadrant[i]);
    //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                    depths.push_front(depth+1);

                    if(MEMORYorSPEED==MEMORY){
                        std::deque<int> qTemp;
                        for(int i=0;i<4;i++){
                            qTemp.push_front(i);
                        }
                        quadrantsToExplore.push_front(qTemp);
                    }


    //                indexes.push(initialIndex);
                }
            }
        }

        // Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
        InterfaceIntersectionObject interfaceIntersectionObject;
        // interfaceIntersectionObject.G=G;
        interfaceIntersectionObject.idsIntersected=idsIntersected;
        interfaceIntersectionObject.intersections=intersections;
        // interfaceIntersectionObject.pairsOldIdNewIds=pairsOldIdNewIds;
        // interfaceIntersectionObject.keepTrackChanges=keepTrackChanges;
    // }
    // G->isPlanar=true;
    return interfaceIntersectionObject;
}





void Grafo::getLinkToWhichPointsBelongs(Grafo* G,std::vector<double>& xs,std::vector<double>& ys,std::vector<long>& idClosestLines){
    std::vector<long> idPoints;

        // std::vector<std::vector<long> > idsIntersected;
        // std::vector<Point2d> intersections;



        // long maxDegree=-std::numeric_limits<long>::max();
        long depthLimit=9;
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        // maxDegree=2;

        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;

        for(long i=0;i<G->nodes.size();i++){
            if(G->nodes[i]->location.x>maxX){
                maxX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y>maxY){
                maxY=G->nodes[i]->location.y;
            }
            if(G->nodes[i]->location.x<minX){
                minX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y<minY){
                minY=G->nodes[i]->location.y;
            }
        }
        idPoints.reserve(xs.size());

        for(long i=0;i<xs.size();i++){
            idPoints.push_back(i);
            if(xs[i]>maxX){
                maxX=xs[i];
            }
            if(ys[i]>maxY){
                maxY=ys[i];
            }
            if(xs[i]<minX){
                minX=xs[i];
            }
            if(ys[i]<minY){
                minY=ys[i];
            }
        }
        idClosestLines.resize(idPoints.size(),-1);
        std::deque<double> maxXs,minXs,maxYs,minYs;

        std::deque<long> depths;
        std::deque<std::vector<long> > idsLines;
        std::deque<std::vector<long> > idsNodes;
        std::deque<std::vector<long> > idsPointsInTree;
        std::deque<std::queue<int> > quadrantsToExplore;


        double a_maxX,a_maxY,a_minX,a_minY;
        long depth;


        a_maxX=maxX;
        a_maxY=maxY;
        a_minX=minX;
        a_minY=minY;
        maxXs.push_front(maxX);
        minXs.push_front(minX);
        maxYs.push_front(maxY);
        minYs.push_front(minY);
        std::vector<long> idsLinesTemp;
        // std::vector<long> idsNodesTemp;
        std::vector<long> idsPointsInTreeTemp;

        std::queue<int> quadrantsToExploreTemp;
        for(long i=0;i<G->links.size();i++){
            // idsLinesTemp.push_back(G->links[i]->id);
            idsLinesTemp.push_back(i);
        }
        for(long i=0;i<idPoints.size();i++){
            idsPointsInTreeTemp.push_back(idPoints[i]);
        }
        // for(long i=0;i<G->nodes.size();i++){
        //     idsNodesTemp.push_back(G->nodes[i]->id);
        // }
        for(int i=0;i<4;i++){
            quadrantsToExploreTemp.push(i);
        }
        idsLines.push_front(idsLinesTemp);
        // idsNodes.push_front(idsNodesTemp);
        idsPointsInTree.push_front(idsPointsInTreeTemp);


        depths.push_front(0);

        double gridSizeX=((maxX-minX));

        double gridSizeY=((maxY-minY));



        while (maxXs.size()>0){
            maxX=maxXs.front();
            maxY=maxYs.front();
            minX=minXs.front();
            minY=minYs.front();
            // if(MEMORYorSPEED==MEMORY){
            //     quadrantsToExploreTemp=quadrantsToExplore.front();
            // }

            idsLinesTemp=idsLines.front();
            // idsNodesTemp=idsNodes.front();
            idsPointsInTreeTemp=idsPointsInTree.front();
    //        numLines=numbers_DifferentLines.front();
            depth=depths.front();

    //        std::cout<<depth<<'\n';
            // int currentQuadrant = -1;
           // if(MEMORYorSPEED==MEMORY){
           //      quadrantsToExplore.pop_front();
           //      currentQuadrant=quadrantsToExploreTemp.front();
           //      quadrantsToExploreTemp.pop();

           //      quadrantsToExplore.push_front(quadrantsToExploreTemp);
           //      if(quadrantsToExploreTemp.size()==0){
           //          maxXs.pop_front();
           //          maxYs.pop_front();
           //          minXs.pop_front();
           //          minYs.pop_front();

           //          idsLines.pop_front();
           //          idsNodes.pop_front();
           //          //        numbers_DifferentLines.pop();
           //          depths.pop_front();
           //          quadrantsToExplore.pop_front();
           //      }

           //  }else{
                maxXs.pop_front();
                maxYs.pop_front();
                minXs.pop_front();
                minYs.pop_front();

                idsLines.pop_front();
                // idsNodes.pop_front();
                idsPointsInTree.pop_front();

                depths.pop_front();





            gridSizeX=((maxX-minX));

            gridSizeY=((maxY-minY));
            bool STOP=false;
            if(idsLinesTemp.size()<=0||idsPointsInTreeTemp.size()<=0){
                STOP=true;
            }
            if(!STOP&&((idsPointsInTreeTemp.size()==1&&depth<=depthLimit)||(depth>depthLimit))){
            //solve
                for(long i=0;i<idsPointsInTreeTemp.size();i++){
                        double minDistance=INFINITY;
                        for(long j=0;j<idsLinesTemp.size();j++){
                            long it=idsPointsInTreeTemp[i];
                            long it2=idsLinesTemp[j];
                            Point2d point(xs[it],ys[it]);
                            double distance=Geometry::distancePointToSegment(G->links[it2]->A()->location,G->links[it2]->B()->location,point);
                            // std::cout<<"distance2 "<<distance<<'\n';
                            if(distance<minDistance){
                                idClosestLines[it]=it2;
                                minDistance=distance;
                            }

                        }
                    }


            }else if(!STOP&&idsLinesTemp.size()>=2){

                std::vector<std::vector<long> > idsLinesPerQuadrant;
                std::vector<std::vector<long> > idsPointsPerQuadrant;

                idsLinesPerQuadrant.resize(4,std::vector<long>());
                idsPointsPerQuadrant.resize(4,std::vector<long>());
                Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                for(long i=0;i<idsPointsInTreeTemp.size();i++){
                    long quadrant=Functions::getQuadrant(center, Point2d(xs[idsPointsInTreeTemp[i]],ys[idsPointsInTreeTemp[i]]));

                    if(Functions::inBoundaryOfASquare(center, Point2d(xs[idsPointsInTreeTemp[i]],ys[idsPointsInTreeTemp[i]]), gridSizeX, gridSizeY)){
                        idsPointsPerQuadrant[quadrant].push_back(idsPointsInTreeTemp[i]);
                    }
                }

                for(long i=0;i<idsLinesTemp.size();i++){

                        long it=idsLinesTemp[i];


                    std::vector<long> quadrants=Functions::getQuadrantsLine(center, G->links[it]->A()->location, G->links[it]->B()->location, gridSizeX, gridSizeY);


                    for(long j=0;j<quadrants.size();j++){
                        // if(quadrants[j]==currentQuadrant||MEMORYorSPEED==SPEED){
                            idsLinesPerQuadrant[quadrants[j]].push_back(it);
                        // }
                    }
                }

                int startLoop=0;
                int endLoop=4;


                bool continueSubdivision=true;
                for(long i=startLoop;i<endLoop;i++){
                    if(idsPointsPerQuadrant[i].size()>0&&idsLinesPerQuadrant[i].size()==0){
                        continueSubdivision=false;
                    }
                }

                if(!continueSubdivision){

                    for(long i=0;i<idsPointsInTreeTemp.size();i++){
                        double minDistance=INFINITY;
                        for(long j=0;j<idsLinesTemp.size();j++){
                            long it=idsPointsInTreeTemp[i];
                            long it2=idsLinesTemp[j];
                            Point2d point(xs[it],ys[it]);
                            double distance=Geometry::distancePointToSegment(G->links[it2]->A()->location,G->links[it2]->B()->location,point);
                            // std::cout<<"distance2 "<<distance<<'\n';
                            if(distance<minDistance){
                                idClosestLines[it]=it2;
                                minDistance=distance;
                            }

                        }
                    }
                }else{




                    // if(MEMORYorSPEED==MEMORY){
                    //     startLoop=currentQuadrant;
                    //     endLoop=currentQuadrant+1;
                    // }else if (MEMORYorSPEED==SPEED){
                        startLoop=0;
                        endLoop=4;
                    // }

                    for(long i=startLoop;i<endLoop;i++){

                        double currentCol=i%2;
                        double currentRow=i/2;



                        double gridSizeX_temp=((maxX-minX)/2.0);

                        double gridSizeY_temp=((maxY-minY)/2.0);
                        double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                        double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                        minXs.push_front(currentMinX);
                        minYs.push_front(currentMinY);
                        maxXs.push_front(currentMinX+gridSizeX_temp);
                        maxYs.push_front(currentMinY+gridSizeY_temp);
                        idsLines.push_front(idsLinesPerQuadrant[i]);
                        idsPointsInTree.push_front(idsPointsPerQuadrant[i]);

                        depths.push_front(depth+1);

                        // if(MEMORYorSPEED==MEMORY){
                        //     std::queue<int> qTemp;
                        //     for(int i=0;i<4;i++){
                        //         qTemp.push(i);
                        //     }
                        //     quadrantsToExplore.push_front(qTemp);
                        // }



                    }
                }
            }
        }




}








void Grafo::addLinksFollowingIntersections(Grafo* G,std::vector<std::vector<long> > &idsIntersected,std::vector<Point2d> &intersections,std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > &pairsOldIdNewIds,bool keepTrackChanges){

//    std::cout<<"in addLinksFollowing intersections "<<idsIntersected.size()<<" "<<intersections.size()<<" "<<pairsOldIdNewIds.size()<<'\n';
// std::cout<<"intersection size "<<intersections.size()<<" idsIntersected size "<<idsIntersected.size()<<'\n';
// Grafo intersectionsGraph;
    if(intersections.size()>0){
        std::set<long> idLinksToRemove;
        std::set<long> idLinksToRemoveFinal;
        for(long i=0;i<intersections.size();i++){
          // intersectionsGraph.addNode(intersections[i]);
          // std::cout<<"intersections=rbind(intersections,data.frame(x="<<intersections[i].x<<",y="<<intersections[i].y<<"))"<<'\n';
    //        Nodo* checkNodeExists=G->getNodeByLocation(intersections[i]);
    //        if(checkNodeExists==NULL){
    //            G->addNode(intersections[i]);
            for(long j=0;j<idsIntersected[i].size();j++){
                long id1=idsIntersected[i][j];
                // long id2=idsIntersected[i][1];
                idLinksToRemove.insert(id1);
                // idLinksToRemove.insert(id2);

            idLinksToRemoveFinal.insert(id1);
          }
            // idLinksToRemoveFinal.insert(id2);
    //        }

        }

        // TextFile::saveCoordinates(&intersectionsGraph,"/home/carlos/intersections.txt");
//        std::set<long> idLinksToRemoveFinal;
        std::unordered_map<long,std::set<Point2d> > intersectionsPerId;




        for(long i=0;i<intersections.size();i++){

            // long id1=idsIntersected[i][0];
            // long id2=idsIntersected[i][1];
            for(long j=0;j<idsIntersected[i].size();j++){
                long id1=idsIntersected[i][j];

            Point2d intersection=intersections[i];

            intersectionsPerId[id1].insert(intersection);
          }
            // intersectionsPerId[id2].insert(intersection);
        }

        for(auto& it:idLinksToRemove){
            std::tuple<long,std::vector<long>,std::vector<double> > tuppleOldNew;
            std::vector<long> idsAdded;
            std::vector<double> percentages;
            long id=it;
//            pairOldNew.first=;

            std::vector<Point2d> intersectionsOfId;
            std::vector<double> distances;
//            long numberIntersectionsInThisId=0;
            for(auto& it2:intersectionsPerId[id]){

                Nodo* checkNodeExists=G->getNodeByLocation(it2);
                if(checkNodeExists==NULL||(checkNodeExists!=G->links[id]->A()&&checkNodeExists!=G->links[id]->B())){
//                    G->addNode(it2);
                    intersectionsOfId.push_back((it2));
                    double distance=Functions::getDistance(G->links[id]->A()->location, it2);
                    distances.push_back(distance);
//                    numberIntersectionsInThisId++;
                }
//                if(intersectionsOfId.size()>0){
//                    linksToRemove.push_back(G->links[id]);
//                }
            }
            if(intersectionsOfId.size()>0){

                std::vector<long> order=Functions::getIndexesOfOrderedValues(distances, true);

                Nodo* previousNode=G->links[id]->A();
                double Dx=Functions::getDistance(G->links[id]->A()->location,G->links[id]->B()->location);
                for(long j=0;j<order.size();j++){

                    Nodo* nodeTemp=G->addNode(intersectionsOfId[order[j]]);
                    // std::cout<<"id new node intersection "<<nodeTemp->id<<'\n';

                    double dx=Functions::getDistance(nodeTemp->location,previousNode->location);

                    double percentage=dx/Dx;
                    long idAdded=G->addLink(previousNode->id,nodeTemp->id,G->links[id]->weight*percentage,G->links[id]->identifier);
                    // std::cout<<"id new link "<<idAdded<<'\n';
                    if(keepTrackChanges){
                        idsAdded.push_back(G->links[idAdded]->originalID);
                        percentages.push_back(percentage);
                    }

                    if(idAdded==-1){
                        std::cout<<"error";
                    }
                    idLinksToRemoveFinal.erase(idAdded);

                    previousNode=nodeTemp;


                }
                double dx=Functions::getDistance(G->links[id]->B()->location,previousNode->location);

                double percentage=dx/Dx;
                long idAdded=G->addLink(previousNode->id,G->links[id]->B()->id,G->links[id]->weight*percentage,G->links[id]->identifier);
                if(keepTrackChanges){
                    percentages.push_back(percentage);
                    idsAdded.push_back(G->links[idAdded]->originalID);
                }
                if(idAdded==-1){
                    std::cout<<"error";
                }
                idLinksToRemoveFinal.erase(idAdded);
                if(keepTrackChanges){
                    tuppleOldNew=std::make_tuple(G->links[id]->originalID,idsAdded,percentages);
                    pairsOldIdNewIds.push_back(tuppleOldNew);
                }
            }else{
                idLinksToRemoveFinal.erase(id);
            }



        }
        // std::cout<<"number of links to remove "<<idLinksToRemoveFinal.size()<<'\n';
        if(idLinksToRemoveFinal.size()>0){
            G->removeLinks(idLinksToRemoveFinal);
        }else{
            // G->isPlanar=true;
        }
    }else{
        // G->isPlanar=true;
    }
    G->finishedAddingNodes();
//    std::cout<<"final number links "<<G->links.size()<<'\n';
}





void Grafo::removeSuperfluousNodes(Grafo* G,Grafo* result,std::vector<std::pair<std::vector<long>,long> > &pairsOldNew,double maxAngle,bool keepTrackChanges){
//    std::cout<<"checking loops before simplify "<<'\n';
//    Grafo::checkIfLoops(G);
    //TODO in some strange cases this leaves the graph not bidirectional (deletes too many or too little edges..) -> I have not seen this in this function, but because it is the same as buildStructuralGraph then it is supposed to happen also.
//    newIdsLinksByOldId.resize(G->links.size(),-1);
    result->copyGraph(G);
    // std::cout<<"aa"<<'\n';
    std::unordered_map<long,std::vector<long> > idsLinksCollapsedByNewId;
    std::vector<double> anglesToSimplify;
    long numberOfDeletedLinks=0;
    for(double i=1.0;i<=maxAngle;i+=maxAngle/3.0){
        anglesToSimplify.push_back(i);
    }
    // std::cout<<"aa"<<'\n';
    if(!result->pseudoGraph){
        for(long k=0;k<anglesToSimplify.size();k++){
            double angleToSimplify=anglesToSimplify[k];
            std::vector<Nodo*> passingNodes;
            for(long i=0;i<result->nodes.size();i++){
                if(result->getNumberNeighborsAsBidirectional(result->nodes[i])==2){
                  if (result->bidirectional){
                    passingNodes.push_back(result->nodes[i]);
                  }
                  if(!result->bidirectional){
                    if (result->nodes[i]->getLinksThatReachMe(!result->bidirectional).size()==1 && result->nodes[i]->getLinksThatReachMe(!result->bidirectional)[0]->getOtherNode(result->nodes[i])->id!=result->nodes[i]->links[0]->getOtherNode(result->nodes[i])->id){
                      passingNodes.push_back(result->nodes[i]);
                    }
                  }
                }
            }

            for(long i=0;i<passingNodes.size();i++){
                if(result->getNumberNeighborsAsBidirectional(passingNodes[i])==2){
                    Nodo* nodeA;
                    Nodo* nodeB;
                    Link* linkA;
                    Link* linkB;
                    if(!result->bidirectional){
                        // std::cout<<i<<'\n';
                        nodeA=passingNodes[i]->getLinksThatReachMe(!result->bidirectional)[0]->getOtherNode(passingNodes[i]);
                        // std::cout<<"AAAAAAAAAAAA"<<'\n';
                        linkA=passingNodes[i]->getLinksThatReachMe(!result->bidirectional)[0];
                        // std::cout<<"aabb"<<'\n';
                        nodeB=passingNodes[i]->links[0]->getOtherNode(passingNodes[i]);
                        // std::cout<<"aabb"<<'\n';
                        linkB=passingNodes[i]->links[0];
                        // std::cout<<"aabb"<<'\n';
                    }else{
                        // std::cout<<"cccc"<<'\n';
                        nodeA=passingNodes[i]->links[0]->getOtherNode(passingNodes[i]);
                        linkA=passingNodes[i]->links[0];
                        nodeB=passingNodes[i]->links[1]->getOtherNode(passingNodes[i]);
                        linkB=passingNodes[i]->links[1];
                    }
                    // std::cout<<"DDDDDDDDDDDD"<<'\n';
                    double angle=Functions::getAngle(nodeA->location, passingNodes[i]->location, nodeB->location);
                    if(Functions::abs(angle)<=angleToSimplify){

                        long newId=result->addLink(nodeA->id,nodeB->id,linkA->weight+linkB->weight,linkA->identifier);
                        //                std::cout<<"new ids "<<newId<<'\n';
                        if(keepTrackChanges){
                          // std::cout<<"hhhhhh"<<'\n';
                            if(linkA->id<G->links.size()){
                                numberOfDeletedLinks++;
                                idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkA->originalID);
                                for(long j=0;j<idsLinksCollapsedByNewId[linkA->originalID].size();j++){
                                    idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkA->originalID][j]);
                                }
                                idsLinksCollapsedByNewId.erase(linkA->originalID);
                            }else{

                                for(long j=0;j<idsLinksCollapsedByNewId[linkA->originalID].size();j++){
                                    idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkA->originalID][j]);
                                }
                                idsLinksCollapsedByNewId.erase(linkA->originalID);
    //                            idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkA->originalID);
                            }
                            if(linkB->id<G->links.size()){
                                numberOfDeletedLinks++;
                                idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkB->originalID);
                                for(long j=0;j<idsLinksCollapsedByNewId[linkB->originalID].size();j++){
                                    idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkB->originalID][j]);
                                }
                                idsLinksCollapsedByNewId.erase(linkB->originalID);
                            }else{
                                for(long j=0;j<idsLinksCollapsedByNewId[linkB->originalID].size();j++){
                                    idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkB->originalID][j]);
                                }
                                idsLinksCollapsedByNewId.erase(linkB->originalID);


    //                            idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkB->originalID);
                            }
                        }
                        // std::cout<<"kkkkkkkkk"<<'\n';
                        result->removeLink(linkA->id,false);
                        // std::cout<<"uhuhuhuh"<<'\n';
                        result->removeLink(linkB->id,false);
                        // std::cout<<"ioioioioi"<<'\n';
                        if(!result->bidirectional){
                          // std::cout<<"oooooooo"<<'\n';
                            bool isLinkABidirectional=false;
                            bool isLinkBBidirectional=false;
                            Link* newLinkA=NULL;
                            Link* newLinkB=NULL;
                            for(long j=0;j<nodeA->getLinksThatReachMe(!result->bidirectional).size();j++){
                                if(nodeA->getLinksThatReachMe(!result->bidirectional)[j]->getOtherNode(nodeA)==passingNodes[i]){
                                    isLinkABidirectional=true;
                                    newLinkA=nodeA->getLinksThatReachMe(!G->bidirectional)[j];
                                }
                            }
                            for(long j=0;j<nodeB->links.size();j++){
                                if(nodeB->links[j]->getOtherNode(nodeB)==passingNodes[i]){
                                    isLinkBBidirectional=true;
                                    newLinkB=nodeB->links[j];
                                }
                            }
                            // std::cout<<"ppppppppp"<<'\n';
                            if(isLinkABidirectional||isLinkBBidirectional){

                                long newId2=result->addLink(nodeB->id,nodeA->id,result->links[newId]->weight,newLinkA->identifier);
                                if(newLinkA!=NULL){
                                    if(keepTrackChanges){
                                        if(newLinkA->id<G->links.size()){
                                            numberOfDeletedLinks++;
                                            idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkA->originalID);
                                            for(long j=0;j<idsLinksCollapsedByNewId[newLinkA->originalID].size();j++){
                                                idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkA->originalID][j]);
                                            }
                                            idsLinksCollapsedByNewId.erase(newLinkA->originalID);
                                        }else{
                                            for(long j=0;j<idsLinksCollapsedByNewId[newLinkA->originalID].size();j++){
                                                idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkA->originalID][j]);
                                            }
                                            idsLinksCollapsedByNewId.erase(newLinkA->originalID);
    //                                        idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkA->originalID);
                                        }
                                    }
                                    // std::cout<<"wwwwwww"<<'\n';
                                    result->removeLink(newLinkA->id,false);
                                    // std::cout<<"yyyyyyyyy"<<'\n';
                                }
                                if(newLinkB!=NULL){
                                    if(keepTrackChanges){
                                        if(newLinkB->id<G->links.size()){
                                            numberOfDeletedLinks++;
                                            idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkB->originalID);
                                            for(long j=0;j<idsLinksCollapsedByNewId[newLinkB->originalID].size();j++){
                                                idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkB->originalID][j]);
                                            }
                                            idsLinksCollapsedByNewId.erase(newLinkB->originalID);
                                        }else{
                                            for(long j=0;j<idsLinksCollapsedByNewId[newLinkB->originalID].size();j++){
                                                idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkB->originalID][j]);
                                            }
                                            idsLinksCollapsedByNewId.erase(newLinkB->originalID);
    //                                        idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkB->originalID);
                                        }
                                    }
                                    // std::cout<<"iiiiiii"<<'\n';
                                    result->removeLink(newLinkB->id,false);
                                    // std::cout<<"rrrrrrrr"<<'\n';
                                }
                            }
                        }

                    }
                }
            }
        }
        // std::cout<<"aa"<<'\n';
        if(keepTrackChanges){
            for(auto it:idsLinksCollapsedByNewId){
                std::pair<std::vector<long>,long> pair;
                pair.second=it.first;

                for(long i=0;i<(it.second).size();i++){
                    pair.first.push_back(it.second[i]);
                    //                newIdsLinksByOldId[it.second[i]]=it.first-numberOfDeletedLinks;
                }
                if((it.second).size()>0){
                    pairsOldNew.push_back(pair);
                }
            }
        }
//        std::cout<<"checking loops before correcting ids "<<'\n';
//        Grafo::checkIfLoops(G);
      // std::cout<<"aa"<<'\n';
        result->correctIdsLinks();
        std::set<long> idsNodesToRemove;
        for(long i=0;i<result->nodes.size();i++){
            if(result->getNumberNeighborsAsBidirectional(result->nodes[i])==0){
                idsNodesToRemove.insert(i);
            }
        }
//        std::cout<<"checking loops before removing nodes "<<'\n';
//        Grafo::checkIfLoops(G);
        result->removeNodes(idsNodesToRemove);
//        std::cout<<"checking loops after removing nodes "<<'\n';
//        Grafo::checkIfLoops(G);
        result->finishedAddingNodes();
    }else{
        std::cout<<"Removing superfluous nodes for pseudographs is not yet implemented";
        result->copyGraph(G);
    }

}











void Grafo::removeNonStructuralNodes(Grafo* G,Grafo* result,std::vector<std::pair<std::vector<long>,long> > &pairsOldNew,bool keepTrackChanges){
    //TODO in some strange cases this leaves the graph not bidirectional (deletes too many or too little edges..)
//    pairsOldNew.resize(G->links.size());
    result->copyGraph(G);
    std::unordered_map<long,std::vector<long> > idsLinksCollapsedByNewId;
    std::vector<double> anglesToSimplify;
    long numberOfDeletedLinks=0;

    if(!result->pseudoGraph){

        std::vector<Nodo*> passingNodes;
        for(long i=0;i<result->nodes.size();i++){
            if(result->getNumberNeighborsAsBidirectional(result->nodes[i])==2&&result->nodes[i]->mass<=1){
              if (result->bidirectional){
                passingNodes.push_back(result->nodes[i]);
              }
              if(!result->bidirectional){
                if (result->nodes[i]->getLinksThatReachMe(!result->bidirectional).size()==1 && result->nodes[i]->getLinksThatReachMe(!result->bidirectional)[0]->getOtherNode(result->nodes[i])->id!=result->nodes[i]->links[0]->getOtherNode(result->nodes[i])->id){
                  passingNodes.push_back(result->nodes[i]);
                }
              }
            }
        }

        for(long i=0;i<result->links.size();i++){
            idsLinksCollapsedByNewId[result->links[i]->originalID].push_back(result->links[i]->originalID);

        }

        for(long i=0;i<passingNodes.size();i++){
            if(result->getNumberNeighborsAsBidirectional(passingNodes[i])==2){
                Nodo* nodeA;
                Nodo* nodeB;
                Link* linkA;
                Link* linkB;
                if(!result->bidirectional){
                    nodeA=passingNodes[i]->getLinksThatReachMe(!result->bidirectional)[0]->getOtherNode(passingNodes[i]);
                    linkA=passingNodes[i]->getLinksThatReachMe(!result->bidirectional)[0];
                    nodeB=passingNodes[i]->links[0]->getOtherNode(passingNodes[i]);
                    linkB=passingNodes[i]->links[0];
                }else{
                    nodeA=passingNodes[i]->links[0]->getOtherNode(passingNodes[i]);
                    linkA=passingNodes[i]->links[0];
                    nodeB=passingNodes[i]->links[1]->getOtherNode(passingNodes[i]);
                    linkB=passingNodes[i]->links[1];
                }



                long newId=result->addLink(nodeA->id,nodeB->id,linkA->weight+linkB->weight);
                if(newId!=-1){
                  // result->links[newId]->copyProperties(linkA);
                }
//                std::cout<<"new ids "<<newId<<'\n';
                if(newId!=-1){
                    if(keepTrackChanges){
                        // if(linkA->id<G->links.size()){
                        //     numberOfDeletedLinks++;
                        //     // idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkA->originalID);
                        //     for(long j=0;j<idsLinksCollapsedByNewId[linkA->originalID].size();j++){
                        //         idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkA->originalID][j]);
                        //     }
                        //     idsLinksCollapsedByNewId.erase(linkA->originalID);
                        // }else{

                            for(long j=0;j<idsLinksCollapsedByNewId[linkA->originalID].size();j++){
                                idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkA->originalID][j]);
                            }
                            idsLinksCollapsedByNewId.erase(linkA->originalID);
        //                    idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkA->originalID);
                        // }
                        // if(linkB->id<G->links.size()){
                        //     numberOfDeletedLinks++;
                        //     // idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkB->originalID);
                        //     for(long j=0;j<idsLinksCollapsedByNewId[linkB->originalID].size();j++){
                        //         idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkB->originalID][j]);
                        //     }
                        //     idsLinksCollapsedByNewId.erase(linkB->originalID);
                        // }else{
                            for(long j=0;j<idsLinksCollapsedByNewId[linkB->originalID].size();j++){
                                idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(idsLinksCollapsedByNewId[linkB->originalID][j]);
                            }
                            idsLinksCollapsedByNewId.erase(linkB->originalID);
        //                    idsLinksCollapsedByNewId[result->links[newId]->originalID].push_back(linkB->originalID);
                        // }
                    }
                }else{
                    std::cout<<"removenonstructuralnodes:: id is -1";
                }
                result->removeLink(linkA->id,false);
                result->removeLink(linkB->id,false);

                if(!result->bidirectional){
                    bool isLinkABidirectional=false;
                    bool isLinkBBidirectional=false;
                    Link* newLinkA=NULL;
                    Link* newLinkB=NULL;
                    for(long j=0;j<nodeA->getLinksThatReachMe(!result->bidirectional).size();j++){
                        if(nodeA->getLinksThatReachMe(!result->bidirectional)[j]->getOtherNode(nodeA)==passingNodes[i]){
                            isLinkABidirectional=true;
                            newLinkA=nodeA->getLinksThatReachMe(!G->bidirectional)[j];
                        }
                    }
                    for(long j=0;j<nodeB->links.size();j++){
                        if(nodeB->links[j]->getOtherNode(nodeB)==passingNodes[i]){
                            isLinkBBidirectional=true;
                            newLinkB=nodeB->links[j];
                        }
                    }
                    if(isLinkABidirectional||isLinkBBidirectional){

                        long newId2=result->addLink(nodeB->id,nodeA->id,result->links[newId]->weight);
                        if(newId2!=-1){
                          // result->links[newId2]->copyProperties(result->links[newId]);
                        }
                        if(newLinkA!=NULL){
                            if(newId2!=-1&&keepTrackChanges){
                                // if(newLinkA->id<G->links.size()){
                                //     numberOfDeletedLinks++;
                                //     idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkA->originalID);
                                //     for(long j=0;j<idsLinksCollapsedByNewId[newLinkA->originalID].size();j++){
                                //         idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkA->originalID][j]);

                                //     }
                                //     idsLinksCollapsedByNewId.erase(newLinkA->originalID);
                                // }else{
                                    for(long j=0;j<idsLinksCollapsedByNewId[newLinkA->originalID].size();j++){
                                        idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkA->originalID][j]);

                                    }
                                    idsLinksCollapsedByNewId.erase(newLinkA->originalID);
    //                                idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkA->originalID);
                                // }
                            }
                            result->removeLink(newLinkA->id,false);

                        }
                        if(newLinkB!=NULL){
                            if(newId2!=-1&&keepTrackChanges){
                                // if(newLinkB->id<G->links.size()){
                                //     numberOfDeletedLinks++;
                                //     idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkB->originalID);
                                //     for(long j=0;j<idsLinksCollapsedByNewId[newLinkB->originalID].size();j++){
                                //         idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkB->originalID][j]);

                                //     }
                                //     idsLinksCollapsedByNewId.erase(newLinkB->originalID);
                                // }else{
                                    for(long j=0;j<idsLinksCollapsedByNewId[newLinkB->originalID].size();j++){
                                        idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(idsLinksCollapsedByNewId[newLinkB->originalID][j]);

                                    }
                                    idsLinksCollapsedByNewId.erase(newLinkB->originalID);
    //                                idsLinksCollapsedByNewId[result->links[newId2]->originalID].push_back(newLinkB->originalID);
                                // }
                            }
                            result->removeLink(newLinkB->id,false);

                        }
                    }
                }
            }

        }
        if(keepTrackChanges){
            for(auto it:idsLinksCollapsedByNewId){
                std::pair<std::vector<long>,long> pair;
                pair.second=it.first;

                for(long i=0;i<(it.second).size();i++){
                    pair.first.push_back(it.second[i]);
    //                newIdsLinksByOldId[it.second[i]]=it.first-numberOfDeletedLinks;
                }
                if((it.second).size()>0){
                    pairsOldNew.push_back(pair);
                }
            }
        }
        result->correctIdsLinks();
        std::set<long> idsNodesToRemove;
        for(long i=0;i<result->nodes.size();i++){
            if(result->getNumberNeighborsAsBidirectional(result->nodes[i])==0){
                idsNodesToRemove.insert(i);
            }
        }
        result->removeNodes(idsNodesToRemove);
        result->finishedAddingNodes();
    }else{
        std::cout<<"Removing non-structural nodes for pseudographs is not yet implemented";
        result->copyGraph(G);
    }
}



















void Grafo::startCalculatingShortestPaths(Grafo* G,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff){
    if(numbersRepresentingNodes.size()==0){
        numbersRepresentingNodes.reserve(G->nodes.size());
        for(long i=0;i<G->nodes.size();i++){
            Number* number=new Number();
            number->value=INFINITY;
            number->id=G->nodes[i]->id;
            numbersRepresentingNodes.push_back(number);

        }
        inDijkstra.resize(G->nodes.size(),false);
        inCutoff.resize(G->nodes.size(),false);
    }


}

void Grafo::finishCalculatingShortestPaths(Grafo* G,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff){
    for(long i=0;i<numbersRepresentingNodes.size();i++){
        delete numbersRepresentingNodes[i];
        numbersRepresentingNodes[i]=NULL;
    }
    numbersRepresentingNodes.clear();
    inDijkstra.clear();
    inCutoff.clear();
}

void Grafo::calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result,double distanceLimit,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff)
{
    // Grafo::startCalculatingShortestPaths(G);
    if(result.size()==0){
        result.resize(G->nodes.size());
    }else{
        result.setMinDistance(nodeInit->id,0);
        if(!result.onlyCalculatingDistances()){
            result.setNumChildren(nodeInit->id, 0);
            result.setParentID(nodeInit->id, -1);
        }
    }
    result.idNodeInit=nodeInit->id;
    result.numberNodesInCutoff=0;
    Heap<Number*> nodesToCheckDijkstra=Heap<Number*>(true);

    result.setMinDistance(nodeInit->id,0.0);
    result.numberNodesInCutoff++;
    result.totalDistance=0;
    std::vector<long> idsNodesToReset;
    idsNodesToReset.push_back(nodeInit->id);
    nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeInit->id]);
    inDijkstra[nodeInit->id]=true;
    inCutoff[nodeInit->id]=true;
    std::set<long> idsBorderLinks;

    if(result.isBirdEyeCutoff()){
        distanceLimit=distanceLimit*distanceLimit;
    }


    while (nodesToCheckDijkstra.size() > 0)
    {
        Nodo* startNode =G->nodes[nodesToCheckDijkstra.pop()->id];
        inDijkstra[startNode->id]=false;
        if(startNode->links.size()>0)
        {
            for (long i = 0; i < startNode->links.size(); i++)
            {
                Link* linkTemp = (startNode->links[i]);
                if (linkTemp->A()==linkTemp->B())
                {
                    std::cout<<"loop!!! "<<linkTemp->id<<'\n';
                }

                Nodo* nodeB;

                if (linkTemp->getOtherNode(startNode)!=NULL)
                {
                    nodeB=linkTemp->getOtherNode(startNode);
                }
                else
                {
                    nodeB=(G->nodes[linkTemp->getOtherNode(startNode)->id]);
                }

                if(!inCutoff[nodeB->id]&&!inDijkstra[nodeB->id]){
                    result.setMinDistance(nodeB->id,INFINITY);
                    if(!result.onlyCalculatingDistances()){
                        result.setNumChildren(nodeB->id, 0);
                        result.setParentID(nodeB->id, -1);
                    }

                }

                double possibleDistance=linkTemp->weight + result.getMinDistance(startNode->id);
                double distanceCutoff=possibleDistance;
                if(result.isBirdEyeCutoff()){
                    distanceCutoff=Functions::getSquaredDistance(nodeInit->location, nodeB->location);
                }
                if ((possibleDistance < result.getMinDistance(nodeB->id))&& (distanceCutoff <= distanceLimit||distanceLimit==0))
                {

                    if (!inCutoff[nodeB->id])
                    {
                        inCutoff[nodeB->id]=true;
                        idsNodesToReset.push_back(nodeB->id);
                        result.numberNodesInCutoff++;
                        if(result.isMeasuringTotalDistances()){
                            result.totalDistance+=linkTemp->weight;
                        }
                    }
                    else
                    {
                        if(result.isMeasuringTotalDistances()){
                            result.totalDistance-=G->getLink(result.getParentID(nodeB->id), nodeB->id)->weight;
                            result.totalDistance+=linkTemp->weight;
                        }
                        result.decreaseNumChildren(result.getParentID(nodeB->id));
                    }
                    result.setParentID(nodeB->id, startNode->id);
                    result.increaseNumChildren(startNode->id);
                    double previousDistance=result.getMinDistance(nodeB->id);
                    result.setMinDistance(nodeB->id,possibleDistance);
                    if(possibleDistance>result.maxDistanceInSystem){
                      result.maxDistanceInSystem=possibleDistance;
                    }
                    numbersRepresentingNodes[nodeB->id]->value=result.getMinDistance(nodeB->id);
                    if (!inDijkstra[nodeB->id])
                    {
                        inDijkstra[nodeB->id]=true;
                        nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeB->id]);
                    }
                    else
                    {

                        nodesToCheckDijkstra.update(numbersRepresentingNodes[nodeB->id],previousDistance);
                    }
                }else if(distanceCutoff > distanceLimit&&distanceLimit>0){
                    if(result.includeBorderLinks()){
                        idsBorderLinks.insert(linkTemp->id);
                    }
                }
            }
        }
    }
    if(result.isMeasuringTotalDistances()){
        result.totalDistanceIncludingBorderLinks=result.totalDistance;
        if(result.includeBorderLinks()){
            for(auto& it:idsBorderLinks){
                double prevDistance=0;
                if(inCutoff[G->links[it]->A()->id]){
                    prevDistance=result.getMinDistance(G->links[it]->A()->id);
                }else{
                    prevDistance=result.getMinDistance(G->links[it]->B()->id);
                }
                result.totalDistanceIncludingBorderLinks+=distanceLimit-prevDistance;
            }
        }
    }
    for(long i=0;i<idsNodesToReset.size();i++){
        numbersRepresentingNodes[idsNodesToReset[i]]->value=INFINITY;
//        G->numbersRepresentingNodes[idsNodesToReset[i]]->indexInHeap.clear();
        numbersRepresentingNodes[idsNodesToReset[i]]->indexInHeap=-1;
        inCutoff[idsNodesToReset[i]]=false;
        inDijkstra[idsNodesToReset[i]]=false;
    }

    idsNodesToReset.swap(result.idsInCutoff);

}

void Grafo::calculateAStar_angleBased(Grafo* G,Nodo* &nodeInit,Nodo* nodeDestination,double angleAllowed,InterfaceDijkstra &result,double distanceLimit,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff)
{
    // Grafo::startCalculatingShortestPaths(G);
    if(result.size()==0){
        result.resize(G->nodes.size());
    }else{
        result.setMinDistance(nodeInit->id,0);
        if(!result.onlyCalculatingDistances()){
            result.setNumChildren(nodeInit->id, 0);
            result.setParentID(nodeInit->id, -1);
        }
    }
    result.idNodeInit=nodeInit->id;
    result.numberNodesInCutoff=0;
    Heap<Number*> nodesToCheckDijkstra=Heap<Number*>(true);

    result.setMinDistance(nodeInit->id,0.0);
    result.numberNodesInCutoff++;
    result.totalDistance=0;
    std::vector<long> idsNodesToReset;
    idsNodesToReset.push_back(nodeInit->id);
    nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeInit->id]);
    inDijkstra[nodeInit->id]=true;
    inCutoff[nodeInit->id]=true;
    std::set<long> idsBorderLinks;

    if(result.isBirdEyeCutoff()){
        distanceLimit=distanceLimit*distanceLimit;
    }


    while (nodesToCheckDijkstra.size() > 0)
    {
        Nodo* startNode =G->nodes[nodesToCheckDijkstra.pop()->id];
        inDijkstra[startNode->id]=false;
        if(startNode->links.size()>0)
        {
            for (long i = 0; i < startNode->links.size(); i++)
            {
                Link* linkTemp = (startNode->links[i]);
                if (linkTemp->A()==linkTemp->B())
                {
                    std::cout<<"loop!!! "<<linkTemp->id<<'\n';
                }

                Nodo* nodeB;

                if (linkTemp->getOtherNode(startNode)!=NULL)
                {
                    nodeB=linkTemp->getOtherNode(startNode);
                }
                else
                {
                    nodeB=(G->nodes[linkTemp->getOtherNode(startNode)->id]);
                }

                if(!inCutoff[nodeB->id]&&!inDijkstra[nodeB->id]){
                    result.setMinDistance(nodeB->id,INFINITY);
                    if(!result.onlyCalculatingDistances()){
                        result.setNumChildren(nodeB->id, 0);
                        result.setParentID(nodeB->id, -1);
                    }

                }

                double possibleDistance=linkTemp->weight + result.getMinDistance(startNode->id);
                double distanceCutoff=possibleDistance;
                if(result.isBirdEyeCutoff()){
                    distanceCutoff=Functions::getSquaredDistance(nodeInit->location, nodeB->location);
                }
                // double distanceFromCurrentNodeToDestination=Functions::getDistance(nodeB->location,nodeDestination->location);
                // double distanceFromInitNodeToCurrentNode=Functions::getDistance(nodeB->location,nodeInit->location);
                // double distanceFromInitNodeToDestination=Functions::getDistance(nodeDestination->location,nodeInit->location);
                double angleTwistAtCurrentNode=Functions::abs(Functions::getAngle(nodeInit->location,nodeB->location,nodeDestination->location));



                if ((possibleDistance < result.getMinDistance(nodeB->id))&& (distanceCutoff <= distanceLimit||distanceLimit==0)&&angleTwistAtCurrentNode<angleAllowed)
                {

                    if (!inCutoff[nodeB->id])
                    {
                        inCutoff[nodeB->id]=true;
                        idsNodesToReset.push_back(nodeB->id);
                        result.numberNodesInCutoff++;
                        if(result.isMeasuringTotalDistances()){
                            result.totalDistance+=linkTemp->weight;
                        }
                    }
                    else
                    {
                        if(result.isMeasuringTotalDistances()){
                            result.totalDistance-=G->getLink(result.getParentID(nodeB->id), nodeB->id)->weight;
                            result.totalDistance+=linkTemp->weight;
                        }
                        result.decreaseNumChildren(result.getParentID(nodeB->id));
                    }
                    result.setParentID(nodeB->id, startNode->id);
                    result.increaseNumChildren(startNode->id);
                    double previousDistance=result.getMinDistance(nodeB->id);
                    result.setMinDistance(nodeB->id,possibleDistance);
                    if(possibleDistance>result.maxDistanceInSystem){
                      result.maxDistanceInSystem=possibleDistance;
                    }
                    numbersRepresentingNodes[nodeB->id]->value=result.getMinDistance(nodeB->id);
                    if (!inDijkstra[nodeB->id])
                    {
                        inDijkstra[nodeB->id]=true;
                        nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeB->id]);
                    }
                    else
                    {

                        nodesToCheckDijkstra.update(numbersRepresentingNodes[nodeB->id],previousDistance);
                    }
                }else if(distanceCutoff > distanceLimit&&distanceLimit>0){
                    if(result.includeBorderLinks()){
                        idsBorderLinks.insert(linkTemp->id);
                    }
                }
            }
        }
    }
    if(result.isMeasuringTotalDistances()){
        result.totalDistanceIncludingBorderLinks=result.totalDistance;
        if(result.includeBorderLinks()){
            for(auto& it:idsBorderLinks){
                double prevDistance=0;
                if(inCutoff[G->links[it]->A()->id]){
                    prevDistance=result.getMinDistance(G->links[it]->A()->id);
                }else{
                    prevDistance=result.getMinDistance(G->links[it]->B()->id);
                }
                result.totalDistanceIncludingBorderLinks+=distanceLimit-prevDistance;
            }
        }
    }
    for(long i=0;i<idsNodesToReset.size();i++){
        numbersRepresentingNodes[idsNodesToReset[i]]->value=INFINITY;
//        G->numbersRepresentingNodes[idsNodesToReset[i]]->indexInHeap.clear();
        numbersRepresentingNodes[idsNodesToReset[i]]->indexInHeap=-1;
        inCutoff[idsNodesToReset[i]]=false;
        inDijkstra[idsNodesToReset[i]]=false;
    }

    idsNodesToReset.swap(result.idsInCutoff);

}


void Grafo::calculateDijkstra(Grafo* G,std::vector<double> &weights,Nodo* &nodeInit,InterfaceDijkstra &result,double distanceLimit,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff){
    // Grafo::startCalculatingShortestPaths(G);
    if(result.size()==0){
        result.resize(G->nodes.size());
    }else{
        result.setMinDistance(nodeInit->id,0);
        if(!result.onlyCalculatingDistances()){
            result.setNumChildren(nodeInit->id, 0);
            result.setParentID(nodeInit->id, -1);
        }
    }
    result.idNodeInit=nodeInit->id;
    result.numberNodesInCutoff=0;
    Heap<Number*> nodesToCheckDijkstra=Heap<Number*>(true);

    result.setMinDistance(nodeInit->id,0.0);
    result.numberNodesInCutoff++;
    std::vector<long> idsNodesToReset;
    idsNodesToReset.push_back(nodeInit->id);
    nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeInit->id]);
    inDijkstra[nodeInit->id]=true;
    inCutoff[nodeInit->id]=true;
    std::set<long> idsBorderLinks;
    if(result.isBirdEyeCutoff()){
        distanceLimit=distanceLimit*distanceLimit;
    }


    while (nodesToCheckDijkstra.size() > 0)
    {
        Nodo* startNode =G->nodes[nodesToCheckDijkstra.pop()->id];
        inDijkstra[startNode->id]=false;
        if(startNode->links.size()>0)
        {
            for (long i = 0; i < startNode->links.size(); i++)
            {
                Link* linkTemp = (startNode->links[i]);
                if (linkTemp->A()==linkTemp->B())
                {
                    std::cout<<"loop!!! "<<linkTemp->id<<'\n';
                }

                Nodo* nodeB;

                if (linkTemp->getOtherNode(startNode)!=NULL)
                {
                    nodeB=linkTemp->getOtherNode(startNode);
                }
                else
                {
                    nodeB=(G->nodes[linkTemp->getOtherNode(startNode)->id]);
                }

                if(!inCutoff[nodeB->id]&&!inDijkstra[nodeB->id]){
                    result.setMinDistance(nodeB->id,INFINITY);
                    if(!result.onlyCalculatingDistances()){
                        result.setNumChildren(nodeB->id, 0);
                        result.setParentID(nodeB->id, -1);
                    }

                }

                double possibleDistance=weights[linkTemp->id] + result.getMinDistance(startNode->id);
                double distanceCutoff=possibleDistance;
                if(result.isBirdEyeCutoff()){
                    distanceCutoff=Functions::getSquaredDistance(nodeInit->location, nodeB->location);
                }
                if ((possibleDistance < result.getMinDistance(nodeB->id))&& (distanceCutoff <= distanceLimit||distanceLimit==0))
                {

                    if (!inCutoff[nodeB->id])
                    {
                        inCutoff[nodeB->id]=true;
                        idsNodesToReset.push_back(nodeB->id);
                        result.numberNodesInCutoff++;
                        if(result.isMeasuringTotalDistances()){
                            result.totalDistance+=linkTemp->weight;
                        }
                        //                        nodesCutoff.push_back(nodeB);
                    }
                    else
                    {
                        if(result.isMeasuringTotalDistances()){
                            result.totalDistance-=G->getLink(result.getParentID(nodeB->id), nodeB->id)->weight;
                            result.totalDistance+=linkTemp->weight;
                        }
                        result.decreaseNumChildren(result.getParentID(nodeB->id));
                    }
                    result.setParentID(nodeB->id, startNode->id);
                    result.increaseNumChildren(startNode->id);
                    double previousDistance=result.getMinDistance(nodeB->id);
                    result.setMinDistance(nodeB->id,possibleDistance);
                    if(possibleDistance>result.maxDistanceInSystem){
                      result.maxDistanceInSystem=possibleDistance;
                    }
                    numbersRepresentingNodes[nodeB->id]->value=result.getMinDistance(nodeB->id);
                    if (!inDijkstra[nodeB->id])
                    {
                        inDijkstra[nodeB->id]=true;
                        nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeB->id]);
                    }
                    else
                    {

                        nodesToCheckDijkstra.update(numbersRepresentingNodes[nodeB->id],previousDistance);
                    }
                }else if(distanceCutoff > distanceLimit&&distanceLimit>0){
                    if(result.includeBorderLinks()){
                        idsBorderLinks.insert(linkTemp->id);
                    }
                }
            }
        }
    }
    if(result.isMeasuringTotalDistances()){
        result.totalDistanceIncludingBorderLinks=result.totalDistance;
        if(result.includeBorderLinks()){
            for(auto& it:idsBorderLinks){
                double prevDistance=0;
                if(inCutoff[G->links[it]->A()->id]){
                    prevDistance=result.getMinDistance(G->links[it]->A()->id);
                }else{
                    prevDistance=result.getMinDistance(G->links[it]->B()->id);
                }
                result.totalDistanceIncludingBorderLinks+=distanceLimit-prevDistance;
            }
        }
    }
    for(long i=0;i<idsNodesToReset.size();i++){
        numbersRepresentingNodes[idsNodesToReset[i]]->value=INFINITY;
//        G->numbersRepresentingNodes[idsNodesToReset[i]]->indexInHeap.clear();
        numbersRepresentingNodes[idsNodesToReset[i]]->indexInHeap=-1;
        inCutoff[idsNodesToReset[i]]=false;
        inDijkstra[idsNodesToReset[i]]=false;
    }
    idsNodesToReset.swap(result.idsInCutoff);

}

void Grafo::startMeasuringAroundACircle(Grafo* G,std::vector<bool>& inCutoff){
    if(inCutoff.size()==0){

//        G->linksInCutoff.resize(G->links.size(),false);
        inCutoff.resize(G->nodes.size(),false);
    }
}
void Grafo::finishMeasuringAroundACircle(Grafo* G,std::vector<bool>& inCutoff){
//    G->linksInCutoff.clear();
    inCutoff.clear();
}
void Grafo::takeMeasuresWithinACircle(Grafo* G,Nodo* nodeInit,InterfaceDijkstra &result,double radius,std::vector<bool>& inCutoff){
    result.percentagesOfOutsideNodes=0;
    double squaredRadius=radius*radius;
//    Grafo::startMeasuringAroundACircle(G);
    if(result.size()==0){
        result.resize(G->nodes.size());
    }else{
        result.setMinDistance(nodeInit->id,0);
        if(!result.onlyCalculatingDistances()){
            result.setNumChildren(nodeInit->id, 0);
            result.setParentID(nodeInit->id, -1);
        }
    }
    std::vector<long> idNodesInCutoff;
//    std::queue<long> idLinksInCutoff;
    idNodesInCutoff.push_back(nodeInit->id);
    std::queue<long> idNodesToCheck;
    idNodesToCheck.push(nodeInit->id);
    inCutoff[nodeInit->id]=true;
    result.numberNodesInCutoff=0;
    result.totalDistanceIncludingBorderLinks=0;
    result.totalDistance=0;
    result.numberNodesInCutoff++;
    result.setMinDistance(nodeInit->id, 0);
    while(idNodesToCheck.size()>0){
        long id=idNodesToCheck.front();
        idNodesToCheck.pop();
        for(long i=0;i<G->nodes[id]->links.size();i++){
            double distance=Functions::getSquaredDistance(nodeInit->location, G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->location);
            if(distance>Functions::getSquaredDistance(nodeInit->location, G->nodes[id]->location)){
                if(result.getParentID(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id)==-1){
                    result.setParentID(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id, G->nodes[id]->id);
                }else{
                    if(Functions::getSquaredDistance(nodeInit->location, G->nodes[id]->location)<Functions::getSquaredDistance(nodeInit->location, G->nodes[result.getParentID(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id)]->location)){
                        result.setParentID(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id, G->nodes[id]->id);
                    }
                }
            }else if(result.getParentID(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id)==-1){
                 result.setParentID(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id, G->nodes[id]->id);
            }
            if(!inCutoff[G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id]&&distance<=squaredRadius){
                idNodesToCheck.push(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id);
                idNodesInCutoff.push_back(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id);
                inCutoff[G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id]=true;
                result.setMinDistance(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id, distance);
                if(distance>result.maxDistanceInSystem){
                  result.maxDistanceInSystem=distance;
                }
                result.numberNodesInCutoff++;
            }else if(distance>squaredRadius){
                double realDistance=Functions::getDistance(nodeInit->location, G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->location);
                double realDistanceStartNode=Functions::getDistance(nodeInit->location, G->nodes[id]->location);
                double distanceIncluded=radius-realDistanceStartNode;
                result.percentagesOfOutsideNodes+=distanceIncluded/(realDistance-realDistanceStartNode);
            }
//            G->linksInCutoff[G->nodes[id]->links[i]->id]=true;
            if(G->bidirectional){
                if(distance>squaredRadius){
                    result.totalDistanceIncludingBorderLinks+=radius-Functions::getDistance(nodeInit->location, G->nodes[id]->location);
                }else{
                    result.totalDistance+=G->nodes[id]->links[i]->weight/2.0;
                    result.totalDistanceIncludingBorderLinks+=G->nodes[id]->links[i]->weight/2.0;
                }
            }else{
                if(distance>squaredRadius){
                    result.totalDistanceIncludingBorderLinks+=radius-Functions::getDistance(nodeInit->location, G->nodes[id]->location);
                }else{
                    if(G->getLink(G->nodes[id]->links[i]->getOtherNode(G->nodes[id])->id, G->nodes[id]->id)!=NULL){
                        result.totalDistance+=G->nodes[id]->links[i]->weight/2.0;
                        result.totalDistanceIncludingBorderLinks+=G->nodes[id]->links[i]->weight/2.0;
                    }else{
                        result.totalDistance+=G->nodes[id]->links[i]->weight;
                        result.totalDistanceIncludingBorderLinks+=G->nodes[id]->links[i]->weight;
                    }
                }
            }
//            idLinksInCutoff.push(G->nodes[id]->links[i]->id);
//            if(!G->linksInCutoff[G->nodes[id]->links[i]->id]){
//                G->linksInCutoff[G->nodes[id]->links[i]->id]=true;
//                if(distance>radius){
//                    result.totalDistanceIncludingBorderLinks+=radius-Functions::getDistance(nodeInit->location, G->nodes[id]->location);
//                }else{
//                    result.totalDistance+=G->nodes[id]->links[i]->weight;
//                    result.totalDistanceIncludingBorderLinks+=G->nodes[id]->links[i]->weight;
//                }
//                idLinksInCutoff.push(G->nodes[id]->links[i]->id);
//            }


        }
    }
//    while(idNodesInCutoff.size()>0){
    for(long i=0;i<idNodesInCutoff.size();i++){
        long id=idNodesInCutoff[i];
        inCutoff[id]=false;
        double squaredDistance=result.getMinDistance(idNodesInCutoff[i]);
        result.setMinDistance(idNodesInCutoff[i], sqrt(squaredDistance));
        if(sqrt(squaredDistance)>result.maxDistanceInSystem){
          result.maxDistanceInSystem=sqrt(squaredDistance);
        }
    }
    idNodesInCutoff.swap(result.idsInCutoff);
//    while(idLinksInCutoff.size()>0){
//        long id=idLinksInCutoff.front();
//        idLinksInCutoff.pop();
//        G->linksInCutoff[id]=false;
//    }
}

//void Grafo::calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result)
//{
//    result.idNodeInit=nodeInit->id;
//    Heap<Number*> nodesToCheckDijkstra=Heap<Number*>(true);
//    std::vector<Number*> numbersRepresentingNodes;
//    std::vector<bool> inDijkstra;
//    std::vector<bool> inCutoff;
//
//    result.resize(G->nodes.size());
//    result.setMinDistance(nodeInit->id,0.0);
//    inDijkstra.resize(G->nodes.size(),false);
//    inCutoff.resize(G->nodes.size(),false);
//    numbersRepresentingNodes.reserve(G->nodes.size());
//    for(long i=0;i<G->nodes.size();i++){
//        Number* number=new Number();
//        number->value=INFINITY;
//        number->id=G->nodes[i]->id;
//        numbersRepresentingNodes.push_back(number);
//
//    }
//
//
//
//    while (nodesToCheckDijkstra.size() > 0)
//    {
//        Nodo* startNode =G->nodes[nodesToCheckDijkstra.pop()->id];
//        inDijkstra[startNode->id]=false;
//        if(startNode->links.size()>0)
//        {
//            for (long i = 0; i < startNode->links.size(); i++)
//            {
//                Link* linkTemp = (startNode->links[i]);
//                if (linkTemp->a==linkTemp->b)
//                {
//                    std::cout<<"loop!!! "<<linkTemp->a<<'\n';
//                }
//
//                Nodo* nodeB;
//
//                if (linkTemp->b!=NULL)
//                {
//                    nodeB=linkTemp->b;
//                }
//                else
//                {
//                    nodeB=(G->nodes[linkTemp->b->id]);
//                }
//
//                double possibleDistance=linkTemp->weight + result.getMinDistance(startNode->id);
//                if (possibleDistance < result.getMinDistance(nodeB->id))
//                {
//                    if (!inCutoff[nodeB->id])
//                    {
//                       inCutoff[nodeB->id]=true;
////                        nodesCutoff.push_back(nodeB);
//                    }
//                    else
//                    {
//                        result.decreaseNumChildren(result.getParentID(nodeB->id));
//                    }
//                    result.setParentID(nodeB->id, startNode->id);
//                    result.increaseNumChildren(startNode->id);
//                    double previousDistance=result.getMinDistance(nodeB->id);
//                    result.setMinDistance(nodeB->id,possibleDistance);
//                    numbersRepresentingNodes[nodeB->id]->value=result.getMinDistance(nodeB->id);
//                    if (!inDijkstra[nodeB->id])
//                    {
//                        inDijkstra[nodeB->id]=true;
//                        nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeB->id]);
//                    }
//                    else
//                    {
//
//                        nodesToCheckDijkstra.update(numbersRepresentingNodes[nodeB->id],previousDistance);
//                    }
//                }
//            }
//        }
//    }
//    for(long i=0;i<numbersRepresentingNodes.size();i++){
//        delete numbersRepresentingNodes[i];
//        numbersRepresentingNodes[i]=NULL;
//    }
//}


//void Grafo::calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result,std::vector<Nodo*> &subsetNodes)
//{
//    result.idNodeInit=nodeInit->id;
//    Heap<Number*> nodesToCheckDijkstra=Heap<Number*>(true);
//    std::vector<Number*> numbersRepresentingNodes;
//    std::vector<bool> inDijkstra;
//    std::vector<bool> inCutoff;
//    std::vector<bool> acceptNode;
//    result.resize(G->nodes.size());
//    result.setMinDistance(nodeInit->id,0.0);
//    inDijkstra.resize(G->nodes.size(),false);
//    inCutoff.resize(G->nodes.size(),false);
//    acceptNode.resize(G->nodes.size(),false);
//    for(long i=0;i<subsetNodes.size();i++){
//        acceptNode[subsetNodes[i]->id]=true;
//    }
//    numbersRepresentingNodes.reserve(G->nodes.size());
//    for(long i=0;i<G->nodes.size();i++){
//        Number* number=new Number();
//        number->value=INFINITY;
//        number->id=G->nodes[i]->id;
//        numbersRepresentingNodes.push_back(number);
//
//    }
//
//
//
//    while (nodesToCheckDijkstra.size() > 0)
//    {
//        Nodo* startNode =G->nodes[nodesToCheckDijkstra.pop()->id];
//        inDijkstra[startNode->id]=false;
//        if(startNode->links.size()>0)
//        {
//            for (long i = 0; i < startNode->links.size(); i++)
//            {
//                Link* linkTemp = (startNode->links[i]);
//                if (linkTemp->a==linkTemp->b)
//                {
//                    std::cout<<"loop!!! "<<linkTemp->a<<'\n';
//                }
//
//                Nodo* nodeB;
//
//                if (linkTemp->b!=NULL)
//                {
//                    nodeB=linkTemp->b;
//                }
//                else
//                {
//                    nodeB=(G->nodes[linkTemp->b->id]);
//                }
//
//                double possibleDistance=linkTemp->weight + result.getMinDistance(startNode->id);
//                if (acceptNode[nodeB->id]&&(possibleDistance < result.getMinDistance(nodeB->id)))
////                    && (possibleDistance < distanceLimit||distanceLimit==0)
//                {
//                    if (!inCutoff[nodeB->id])
//                    {
//                        inCutoff[nodeB->id]=true;
//                        //                        nodesCutoff.push_back(nodeB);
//                    }
//                    else
//                    {
//                        result.decreaseNumChildren(result.getParentID(nodeB->id));
//                    }
//                    result.setParentID(nodeB->id, startNode->id);
//                    result.increaseNumChildren(startNode->id);
//                    double previousDistance=result.getMinDistance(nodeB->id);
//                    result.setMinDistance(nodeB->id,possibleDistance);
//                    numbersRepresentingNodes[nodeB->id]->value=result.getMinDistance(nodeB->id);                    if (!inDijkstra[nodeB->id])
//                    {
//                        inDijkstra[nodeB->id]=true;
//                        nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeB->id]);
//                    }
//                    else
//                    {
//
//                        nodesToCheckDijkstra.update(numbersRepresentingNodes[nodeB->id],previousDistance);
//                    }
//                }
//            }
//        }
//    }
//    for(long i=0;i<numbersRepresentingNodes.size();i++){
//        delete numbersRepresentingNodes[i];
//        numbersRepresentingNodes[i]=NULL;
//    }
//}
//
//
//void Grafo::calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result,double distanceLimit,std::vector<double> &weightsCutoff)
//{
//    result.idNodeInit=nodeInit->id;
//    std::vector<double> minDistancesCutoff;
//    Heap<Number*> nodesToCheckDijkstra=Heap<Number*>(true);
//    std::vector<Number*> numbersRepresentingNodes;
//    std::vector<bool> inDijkstra;
//    std::vector<bool> inCutoff;
//
//
//    result.resize(G->nodes.size());
//    result.setMinDistance(nodeInit->id,0.0);
//    minDistancesCutoff.resize(G->nodes.size(),INFINITY);
//    inDijkstra.resize(G->nodes.size(),false);
//    inCutoff.resize(G->nodes.size(),false);
//
//    numbersRepresentingNodes.reserve(G->nodes.size());
//    for(long i=0;i<G->nodes.size();i++){
//        Number* number=new Number();
//        number->value=INFINITY;
//        number->id=G->nodes[i]->id;
//        numbersRepresentingNodes.push_back(number);
//
//    }
//
//
//
//    while (nodesToCheckDijkstra.size() > 0)
//    {
//        Nodo* startNode =G->nodes[nodesToCheckDijkstra.pop()->id];
//        inDijkstra[startNode->id]=false;
//        if(startNode->links.size()>0)
//        {
//            for (long i = 0; i < startNode->links.size(); i++)
//            {
//                Link* linkTemp = (startNode->links[i]);
//                if (linkTemp->a==linkTemp->b)
//                {
//                    std::cout<<"loop!!! "<<linkTemp->a<<'\n';
//                }
//
//                Nodo* nodeB;
//
//                if (linkTemp->b!=NULL)
//                {
//                    nodeB=linkTemp->b;
//                }
//                else
//                {
//                    nodeB=(G->nodes[linkTemp->b->id]);
//                }
//
//                double possibleDistance=linkTemp->weight + result.getMinDistance(startNode->id);
//                double possibleDistanceCutoff=weightsCutoff[linkTemp->id] + minDistancesCutoff[startNode->id];
//                if ((possibleDistance < result.getMinDistance(nodeB->id))&& (possibleDistanceCutoff < distanceLimit||distanceLimit==0))
//                {
//                    if (!inCutoff[nodeB->id])
//                    {
//                        inCutoff[nodeB->id]=true;
//                        //                        nodesCutoff.push_back(nodeB);
//                    }
//                    else
//                    {
//                        result.decreaseNumChildren(result.getParentID(nodeB->id));
//                    }
//                    result.setParentID(nodeB->id, startNode->id);
//                    result.increaseNumChildren(startNode->id);
//                    double previousDistance=result.getMinDistance(nodeB->id);
//                    result.setMinDistance(nodeB->id,possibleDistance);
//                    numbersRepresentingNodes[nodeB->id]->value=result.getMinDistance(nodeB->id);
//                    minDistancesCutoff[nodeB->id]=possibleDistanceCutoff;
//                    if (!inDijkstra[nodeB->id])
//                    {
//                        inDijkstra[nodeB->id]=true;
//                        nodesToCheckDijkstra.push(numbersRepresentingNodes[nodeB->id]);
//                    }
//                    else
//                    {
//
//                        nodesToCheckDijkstra.update(numbersRepresentingNodes[nodeB->id],previousDistance);
//                    }
//                }
//            }
//        }
//    }
//    for(long i=0;i<numbersRepresentingNodes.size();i++){
//        delete numbersRepresentingNodes[i];
//        numbersRepresentingNodes[i]=NULL;
//    }
//}



//void Grafo::calculateCloseness(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &closeness){
//    if(closeness.size()==0){
//        closeness.resize(G->nodes.size(),0);
//    }
//    for (long i=0; i<minDistances.idsInCutoff.size(); i++)
//    {
//        double distance=minDistances.getMinDistance(minDistances.idsInCutoff[i]);
//        if(distance<INFINITY){
//            closeness[minDistances.idsInCutoff[i]]+=distance*G->nodes[minDistances.idsInCutoff[i]]->mass*G->nodes[minDistances.idNodeInit]->mass;
//        }
//    }
//}


void Grafo::calculateDistances_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &distances){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY){
                    distances[i]+=distance*G->nodes[id]->mass;
                }
            }
        }
    //    ID.reset();

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}



void Grafo::calculateCloseness(Grafo* G,double distanceLimit,std::vector<double> &closeness){
    int numThreads=8;
    closeness.clear();
    if(closeness.size()==0){
        closeness.resize(G->nodes.size(),0);
    }
     double numNodesPerThread=floor(G->nodes.size()/numThreads);

     std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&Grafo::calculateDistances_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(closeness)));

    }

    for(auto& thread : threads)
    {
        thread.join();
    }
    for(long i=0;i<closeness.size();i++){
        closeness[i]=G->nodes[i]->mass/closeness[i];
    }

}

void Grafo::calculateTotalDistancesFromEachNode(Grafo* G,double distanceLimit,std::vector<double> &distances){
    int numThreads=8;
    distances.clear();
    if(distances.size()==0){
        distances.resize(G->nodes.size(),0);
    }
     double numNodesPerThread=floor(G->nodes.size()/numThreads);

     std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&Grafo::calculateDistances_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(distances)));

    }

    for(auto& thread : threads)
    {
        thread.join();
    }
    for(long i=0;i<distances.size();i++){
        distances[i]=G->nodes[i]->mass*distances[i];
    }

}



void Grafo::calculateEfficiency_aux(Grafo* G,long startNode,long endNode,double distanceLimit,double &efficiency){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;

    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long j=0;j<ID.idsInCutoff.size();j++){
                double id=ID.idsInCutoff[j];
                double distance=ID.getMinDistance(id);
                if(distance<INFINITY&&i<id){
                    efficiency+=distance*G->nodes[i]->mass*G->nodes[id]->mass;
                }
            }
        }
//        ID.reset();

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}

void Grafo::calculateEfficiency(Grafo* G,double distanceLimit,double &efficiency){
    int numThreads=8;
    // efficiency.clear();
    // if(efficiency.size()==0){
    //     efficiency.resize(G->nodes.size(),0);
    // }
    // double efficiency
     double numNodesPerThread=floor(G->nodes.size()/numThreads);

     std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&Grafo::calculateEfficiency_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(efficiency)));

    }
    double n=(double)G->nodes.size();

    for(auto& thread : threads)
    {
        thread.join();
    }
    efficiency=1/efficiency*(2/(n*(n-1)));

}


void Grafo::calculateBetweenness(Grafo* G,double distanceLimit,std::vector<double> &betweenness){
    int numThreads=8;
    betweenness.clear();
    if(betweenness.size()==0){
        betweenness.resize(G->nodes.size(),0);
    }
    double numNodesPerThread=floor(G->nodes.size()/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&Grafo::calculateBetweenness_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(betweenness)));

    }
    for(auto& thread : threads)
    {
        thread.join();
    }
}
void Grafo::calculateEdgeBetweenness(Grafo* G,double distanceLimit,std::vector<double> &betweenness){
    int numThreads=8;
    betweenness.clear();
    if(betweenness.size()==0){
        betweenness.resize(G->links.size(),0);
    }
    double numNodesPerThread=floor(G->nodes.size()/numThreads);

    std::vector<std::thread> threads;
    for (int i=0; i<numThreads; i++)
    {

        long startNode=i*numNodesPerThread;
        long endNode=(i+1)*numNodesPerThread;
        if (i==numThreads-1)
        {
            endNode=G->nodes.size();
        }

        threads.push_back(std::thread(&Grafo::calculateEdgeBetweenness_aux,std::ref(G),startNode,endNode,distanceLimit,std::ref(betweenness)));

    }
    for(auto& thread : threads)
    {
        thread.join();
    }
}
void Grafo::calculateBetweenness_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &betweenness){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
//    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            Grafo::calculateBetweenness_singleNode(G, ID, betweenness);
            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}
void Grafo::calculateEdgeBetweenness_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &betweenness){
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;
    ID.prepareForBetweenness();
//    std::cout<<ID.onlyCalculatingDistances()<<'\n';
    for (long i=startNode; i<endNode; i++)
    {
        if(G->nodes[i]->mass>0){
            Grafo::calculateDijkstra(G,G->nodes[i],ID,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
            Grafo::calculateEdgeBetweenness_singleNode(G, ID, betweenness);
            ID.reset();
        }

    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
}
void Grafo::calculateBetweenness_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &betweenness){
    std::vector<double> valuesToPass;
//    bool fillingUpValuesToPass=false;
//    if(valuesToPass.size()==0){
//        fillingUpValuesToPass=true;
        valuesToPass.resize(G->nodes.size(),1);
//    }
    std::vector<double> originalValuesToPass;
    originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;

    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
//        if(fillingUpValuesToPass){
            valuesToPass[i]=G->nodes[i]->mass;
//        }
        originalValuesToPass[i]=valuesToPass[i];
    }
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

//    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
//            double valueToPass;
//            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                if(parent!=nodeInit){
                    betweenness[parent->id]=betweenness[parent->id]+((valuesToPass[node->id]))*nodeInit->mass;
    //                betweenness[node->id]=betweenness[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
    //                betweenness[node->id]=betweenness[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                }
                valuesToPass[parent->id]+=valuesToPass[node->id];

                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else{
                valuesToPass[parent->id]+=valuesToPass[node->id];

                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }
        }
//        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
//        {
//            valuesToPass[parent->id]+=valuesToPass[node->id];
//
//            numChildrenThatReachMe[parent->id]++;
//        }
    }
    valuesToPass.clear();


}


void Grafo::calculateEdgeBetweenness_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &edgeBetweenness){
    std::vector<double> valuesToPass;
//    bool fillingUpValuesToPass=false;
//    if(valuesToPass.size()==0){
//        fillingUpValuesToPass=true;
        valuesToPass.resize(G->nodes.size(),1);
//    }
    std::vector<double> originalValuesToPass;
    originalValuesToPass.resize(G->nodes.size(),0);
    Nodo* nodeInit=G->nodes[minDistances.idNodeInit];
    std::vector<Nodo*> leaves;

    for(long i=0;i<G->nodes.size();i++){
        if(minDistances.getMinDistance(i)<INFINITY){
            if(minDistances.getNumChildren(i)==0){
                leaves.push_back(G->nodes[i]);
            }

        }
//        if(fillingUpValuesToPass){
            valuesToPass[i]=G->nodes[i]->mass;
//        }
        originalValuesToPass[i]=valuesToPass[i];
    }
    std::vector<long> numChildrenThatReachMe;
    numChildrenThatReachMe.resize(G->nodes.size(),0);

//    valuesToPass.resize(G->nodes.size(),0);
    for (long i=0; i<leaves.size(); i++)
    {
        Nodo* node=leaves[i];
        Nodo* parent=G->nodes[minDistances.getParentID(leaves[i]->id)];
        // valuesToPass[parent->id]+=valuesToPass[node->id];
        bool STOP=false;
        while(!STOP&&minDistances.getParentID(node->id)!=-1)
        {
//            double valueToPass;
//            valueToPass=valuesToPass[node->id];
            if(minDistances.getNumChildren(parent->id)==numChildrenThatReachMe[parent->id]+1){
                numChildrenThatReachMe[parent->id]++;

                // if(parent!=nodeInit){
                    Link* currentLink=NULL;
                    for(long j=0;j<parent->links.size();j++){
                        if(parent->links[j]->getOtherNode(parent)==node){
                            currentLink=parent->links[j];
                        }
                    }
                    edgeBetweenness[currentLink->id]=edgeBetweenness[currentLink->id]+((valuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valueToPass+valuesToPass[node->id]-originalValuesToPass[node->id]))*nodeInit->mass;
    //                flows[node->id]=flows[node->id]+((valuesToPass[node->id]))*nodeInit->mass;
                // }
                valuesToPass[parent->id]+=valuesToPass[node->id];

                if(minDistances.getParentID(node->id)!=-1){
                    node=parent;
                    parent=G->nodes[minDistances.getParentID(node->id)];
                }
            }else{
                valuesToPass[parent->id]+=valuesToPass[node->id];
                Link* currentLink=NULL;
                for(long j=0;j<parent->links.size();j++){
                    if(parent->links[j]->getOtherNode(parent)==node){
                        currentLink=parent->links[j];
                    }
                }
                edgeBetweenness[currentLink->id]=edgeBetweenness[currentLink->id]+((valuesToPass[node->id]))*nodeInit->mass;
                numChildrenThatReachMe[parent->id]++;
                STOP=true;

            }
        }
//        if ((parent)!=NULL&&minDistances.getNumChildren(parent->id)>numChildrenThatReachMe[parent->id]+1)
//        {
//            valuesToPass[parent->id]+=valuesToPass[node->id];
//
//            numChildrenThatReachMe[parent->id]++;
//        }
    }
    valuesToPass.clear();


}




void Grafo::addLayerOfLinks(Grafo* G,Grafo* layer,double approximation){
    SparseMatrix approxLocations;

    for(long i=0;i<G->nodes.size();i++){

        Point2d approxLocation=Point2d(round(G->nodes[i]->location.x/approximation)*approximation,round(G->nodes[i]->location.y/approximation)*approximation);
        approxLocations.setId(approxLocation.x, approxLocation.y,G->nodes[i]->id);

    }
    for(long i=0;i<layer->links.size();i++){
        Nodo* nodeA=G->getNodeByLocation(layer->links[i]->A()->location);
        if (nodeA==NULL){
            Point2d approxLocation=Point2d(round(layer->links[i]->A()->location.x/approximation)*approximation,round(layer->links[i]->A()->location.y/approximation)*approximation);
            long id=approxLocations.getId(approxLocation.x, approxLocation.y);
            if(id!=-1){
                nodeA=G->nodes[id];
            }
        }
        Nodo* nodeB=G->getNodeByLocation(layer->links[i]->B()->location);
        if (nodeB==NULL){
            Point2d approxLocation=Point2d(round(layer->links[i]->B()->location.x/approximation)*approximation,round(layer->links[i]->B()->location.y/approximation)*approximation);
            long id=approxLocations.getId(approxLocation.x, approxLocation.y);
            if(id!=-1){
                nodeB=G->nodes[id];
            }
        }
        if(nodeA!=NULL&&nodeB!=NULL){
            G->addLink(nodeA->id, nodeB->id, layer->links[i]->weight);
        }
    }
    G->finishedAddingNodes();
}



double Grafo::calculateLocalClusteringCoefficient(Grafo* G,Nodo* node){
    double multiplier=1;
    if(G->bidirectional){
        multiplier=2;
    }
    std::vector<Nodo*> neighbourhood;
    neighbourhood.reserve(node->links.size());
    for(long i=0;i<node->links.size();i++){
        neighbourhood.push_back(node->links[i]->getOtherNode(node));
    }
    double k=(double)node->links.size();
    Grafo subgraph;
    inducedSubgraph(G,&subgraph,neighbourhood);
    double m=(double)subgraph.links.size();
    double c=multiplier*m/(k*(k-1));
    return c;
}


void Grafo::burnGraph(Grafo* G,Grafo* burnedGraph){
    burnedGraph->copyGraph(G);
    bool STOP=false;
    while(!STOP){
        STOP=true;
        std::vector<Nodo*> nodesDegree1;
        std::vector<bool> inserted;
        inserted.resize(burnedGraph->nodes.size(),false);
        std::set<long> idNodesToRemove;
        for(long i=0;i<burnedGraph->nodes.size();i++){
            if(burnedGraph->nodes[i]->getDegree()==1){
                nodesDegree1.push_back(burnedGraph->nodes[i]);
                STOP=false;
            }
        }
        for(long i=0;i<nodesDegree1.size();i++){
            idNodesToRemove.insert(nodesDegree1[i]->id);
            inserted[nodesDegree1[i]->id]=true;
            Nodo* otherNode=nodesDegree1[i]->links[0]->getOtherNode(nodesDegree1[i]);
            Link* thisLink=nodesDegree1[i]->links[0];
            while(otherNode->getDegree()==2&&!inserted[otherNode->id]){
            // while(otherNode->getDegree()==2){
                idNodesToRemove.insert(otherNode->id);
                inserted[otherNode->id]=true;
                // Link* otherLink;
                long index=0;
                if(otherNode->links[0]->id==thisLink->id){
                    index=1;
                }else{
                    index=0;
                }
                thisLink=otherNode->links[index];
                otherNode=otherNode->links[index]->getOtherNode(otherNode);

            }
            // if(otherNode->getDegree()!=2){
            //     std::cout<<"degree "<<otherNode->getDegree()<<'\n';
            // }else{
            //     std::cout<<"inserted is true"<<'\n';
            // }
        }
        burnedGraph->removeNodes(idNodesToRemove);
    }

}
void Grafo::burnGraph(Grafo* G){
    // burnedGraph->copyGraph(G);
    bool STOP=false;
    while(!STOP){
        STOP=true;
        std::vector<Nodo*> nodesDegree1;
        std::vector<bool> inserted;
        inserted.resize(G->nodes.size(),false);
        std::set<long> idNodesToRemove;
        for(long i=0;i<G->nodes.size();i++){
            if(G->nodes[i]->getDegree()==1){
                nodesDegree1.push_back(G->nodes[i]);
                STOP=false;
            }
        }
        for(long i=0;i<nodesDegree1.size();i++){
            idNodesToRemove.insert(nodesDegree1[i]->id);
            inserted[nodesDegree1[i]->id]=true;
            Nodo* otherNode=nodesDegree1[i]->links[0]->getOtherNode(nodesDegree1[i]);
            Link* thisLink=nodesDegree1[i]->links[0];
            while(otherNode->getDegree()==2&&!inserted[otherNode->id]){
            // while(otherNode->getDegree()==2){
                idNodesToRemove.insert(otherNode->id);
                inserted[otherNode->id]=true;
                // Link* otherLink;
                long index=0;
                if(otherNode->links[0]->id==thisLink->id){
                    index=1;
                }else{
                    index=0;
                }
                thisLink=otherNode->links[index];
                otherNode=otherNode->links[index]->getOtherNode(otherNode);

            }
            // if(otherNode->getDegree()!=2){
            //     std::cout<<"degree "<<otherNode->getDegree()<<'\n';
            // }else{
            //     std::cout<<"inserted is true"<<'\n';
            // }
        }
        G->removeNodes(idNodesToRemove);
    }

}

void Grafo::breakAcuteAnglesNodesDegree2(Grafo* G,double maxAngleAccepted){
    std::set<long> idNodesToRemove;
    for(long i=0;i<G->links.size();i++){
        Nodo* a=G->links[i]->A();
        Nodo* b=G->links[i]->B();
        long degree=b->getDegree();

        if(degree==2){
            Link* otherLink;
            long index=0;
            if(b->links[0]->id==G->links[i]->id){
                index=1;
            }else{
                index=0;
            }
            otherLink=b->links[index];

            double angle=Functions::getAngle(a->location,b->location,otherLink->getOtherNode(b)->location);
            if(angle>maxAngleAccepted){
                idNodesToRemove.insert(b->id);
            }
        }
        // if(G->bidirectional){
             a=G->links[i]->B();
             b=G->links[i]->A();
             degree=b->getDegree();

            if(degree==2){
                Link* otherLink;
                long index=0;
                if(b->links[0]->id==G->links[i]->id){
                    index=1;
                }else{
                    index=0;
                }
                otherLink=b->links[index];

                double angle=Functions::getAngle(a->location,b->location,otherLink->getOtherNode(b)->location);
                if(angle>maxAngleAccepted){
                    idNodesToRemove.insert(b->id);
                }
            }
        // }
        // double angle=Functions::calculate
    }
    G->removeNodes(idNodesToRemove);
}





void Grafo::createSuperGraphFromClustersFromColorsLinks(Grafo* originalGraph,Grafo* result,std::vector<long> &colorsLinks,bool useOriginalDistances){
//    std::unordered_map<unsigned long long,long> clusterIdPerNodeId;
//    std::unordered_map<std::string,Nodo*> nodesPerOriginalId;

//    std::vector<Point2d> locations;
    result->copyProperties(originalGraph);
    std::vector<long> colors;
    Grafo::transformColorsLinksIntoColorsNodes(originalGraph, colorsLinks, colors);
    std::unordered_map<long,std::vector<Nodo*> > nodesByColor;
    for(long i=0;i<colors.size();i++){
//        if(colors[i]!=-1){
            nodesByColor[colors[i]].push_back(originalGraph->nodes[i]);
//        }
    }

    std::vector<unsigned long long> newClusterIds;
    newClusterIds.resize(originalGraph->nodes.size(),-1);

    signed long long current_id=0;
    for(auto it:nodesByColor){
        if(it.first!=-1){
        //        Node nodeThatRepresentCluster;
            if(it.second.size()>0){
                double x=0;
                double y=0;
                double totalMass=0;
                for(long j=0;j<it.second.size();j++){
                    totalMass+=it.second[j]->mass;
                    //            long originalId=clusters[i].nodes[j].originalID;
    //                clusterIdPerNodeId[clusters[i].nodes[j].originalID]=i+1;

                    x+=it.second[j]->location.x;
                    y+=it.second[j]->location.y;
                    newClusterIds[it.second[j]->id]=current_id;

                }
                x/=(double)(it.second.size());
                y/=(double)(it.second.size());
                Point2d point(x,y);
                result->addNode(point);
                result->nodes[result->nodes.size()-1]->mass=totalMass;
                                result->nodes[result->nodes.size()-1]->originalID=it.first;
                current_id++;
//                locations.push_back(Point2d(x,y));

            }
        }else{
            for(long i=0;i<it.second.size();i++){
                result->addNode(it.second[i]->location);
                result->nodes[result->nodes.size()-1]->mass=it.second[i]->mass;
                                result->nodes[result->nodes.size()-1]->originalID=it.first;
//                locations.push_back(it.second[i]->location);
                newClusterIds[it.second[i]->id]=current_id;
                current_id++;
//                clusterIdPerNodeId[originalGraph->nodes[i].originalID]=result->nodes.size();
//                Grafo graphTemp;
//                graphTemp.addNode();
//                graphTemp.nodes[0].originalID=originalGraph->nodes[i].originalID;
//                graphTemp.nodes[0].nameRoad=originalGraph->nodes[i].nameRoad;
//                graphTemp.nodes[0].levelHierarchyRoad=originalGraph->nodes[i].levelHierarchyRoad;
//                graphTemp.nodes[0].location=originalGraph->nodes[i].location;
//                graphTemp.nodes[0].mass=originalGraph->nodes[i].mass;
//                clusters.push_back(graphTemp);
            }

        }
    }


    for(long i=0;i<originalGraph->links.size();i++){
        if(newClusterIds[originalGraph->links[i]->A()->id]!=newClusterIds[originalGraph->links[i]->B()->id]){
            double distance;
            if(useOriginalDistances){
                distance=originalGraph->links[i]->weight;
            }else{
                distance=Functions::getDistance(result->nodes[newClusterIds[originalGraph->links[i]->A()->id]]->location, result->nodes[newClusterIds[originalGraph->links[i]->B()->id]]->location);
            }

            result->addLink(newClusterIds[originalGraph->links[i]->A()->id], newClusterIds[originalGraph->links[i]->B()->id], distance);
        }
    }


    //    std::cout<<"a"<<'\n';
//    for(long i=0;i<originalGraph->nodes.size();i++){
////        nodesPerOriginalId[originalGraph->nodes[i]->originalID]=(originalGraph->nodes[i]);
//        if(clusterIdPerNodeId[originalGraph->nodes[i]->originalID]-1==-1){
//                    }
//    }
    //std::cout<<"b"<<'\n';
//    long numberOfTransitions=0;
//    for(long i=0;i<clusters.size();i++){
//        if(clusters[i].nodes.size()>0){
//            result->nodes[i].originalID=clusters[i].nodes[0].originalID;
//        }
//    }




//    long numberOfCollapsedNodes=0;
//    for(long i=0;i<clusters.size();i++){
//        //        result->nodes[i].originalID=clusters[i].nodes[0].originalID;
//        for(long j=0;j<clusters[i].nodes.size();j++){
//
//            Node* node=nodesPerOriginalId[clusters[i].nodes[j].originalID];
//            result->nodes[i].nodesCollapsed.push_back(node);
//            numberOfCollapsedNodes++;
//            for(long h=0;h<node->transitions.size();h++){
//                //                long originalId=otherNode->transitions[h].b->originalID;
//                long idOfNode=clusterIdPerNodeId[node->transitions[h]->a->originalID]-1;
//                long idOfOtherCluster=clusterIdPerNodeId[node->transitions[h]->b->originalID]-1;
//                if(idOfOtherCluster!=idOfNode){
//
//                    Transition trans;
//                    trans.a=&(result->nodes[idOfNode]);
//                    trans.a->location=locations[idOfNode];
//                    trans.b=&(result->nodes[idOfOtherCluster]);
//                    trans.b->location=locations[idOfOtherCluster];
//                    trans.weight=Functions::getDistance(trans.a->location, trans.b->location);
//                    trans.originalID=node->transitions[h]->originalID;
//                    trans.nameRoad=node->transitions[h]->nameRoad;
//                    trans.levelHierarchyRoad=node->transitions[h]->levelHierarchyRoad;
//                    std::vector<double> otherWeights;
//                    trans.otherWeights=otherWeights;
//                    if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
//                        result->addDirectedTransition(trans);
//                        numberOfTransitions++;
//                        result->nodes[idOfNode].transitions[result->nodes[idOfNode].transitions.size()-1]->transitionsCollapsed.push_back(node->transitions[h]);
//                    }else{
//                        result->nodes[idOfNode].transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->transitionsCollapsed.push_back(node->transitions[h]);
//                    }
//                }else{
//                    result->nodes[i].transitionsCollapsedIntoNode.push_back(node->transitions[h]);
//                }
//            }
//        }
//    }
    //    std::cout<<"c"<<'\n';


//    result->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
//    result->insertTopologicalWeights();
//    if(originalGraph->bidirectional){
//        result->transformToBidirectional();
//    }
    //    std::cout<<"d"<<'\n';
//    std::cout<<"number of transitions after generating superGraph of clusters "<<numberOfTransitions<<'\n';
//    std::cout<<"number of collapsed nodes "<<numberOfCollapsedNodes<<'\n';
}



void Grafo::createSuperGraphFromClustersFromColorsNodes(Grafo* originalGraph,Grafo* result,std::vector<long> &colorsNodes,bool useOriginalDistances){
//    std::unordered_map<unsigned long long,long> clusterIdPerNodeId;
//    std::unordered_map<std::string,Nodo*> nodesPerOriginalId;

//    std::vector<Point2d> locations;
    result->copyProperties(originalGraph);
    // std::vector<long> colors;
    // Grafo::transformColorsLinksIntoColorsNodes(originalGraph, colorsLinks, colors);
    std::unordered_map<signed long long,std::vector<Nodo*> > nodesByColor;
    for(long i=0;i<colorsNodes.size();i++){
//        if(colors[i]!=-1){
            nodesByColor[colorsNodes[i]].push_back(originalGraph->nodes[i]);
//        }
    }

    std::vector<unsigned long long> newClusterIds;
    newClusterIds.resize(originalGraph->nodes.size(),-1);

    signed long long current_id=0;
    for(auto it:nodesByColor){
        if(it.first!=-1){
        //        Node nodeThatRepresentCluster;
            if(it.second.size()>0){
                double x=0;
                double y=0;
                double totalMass=0;
                for(long j=0;j<it.second.size();j++){
                    totalMass+=it.second[j]->mass;
                    //            long originalId=clusters[i].nodes[j].originalID;
    //                clusterIdPerNodeId[clusters[i].nodes[j].originalID]=i+1;

                    x+=it.second[j]->location.x;
                    y+=it.second[j]->location.y;
                    newClusterIds[it.second[j]->id]=current_id;

                }
                x/=(double)(it.second.size());
                y/=(double)(it.second.size());
                Point2d point(x,y);
                result->addNode(point);
                result->nodes[result->nodes.size()-1]->mass=totalMass;
                result->nodes[result->nodes.size()-1]->originalID=it.first;
                current_id++;
//                locations.push_back(Point2d(x,y));

            }
        }else{
            for(long i=0;i<it.second.size();i++){
                result->addNode(it.second[i]->location);
                result->nodes[result->nodes.size()-1]->mass=it.second[i]->mass;
                result->nodes[result->nodes.size()-1]->originalID=it.first;
//                locations.push_back(it.second[i]->location);
                newClusterIds[it.second[i]->id]=current_id;
                current_id++;
//                clusterIdPerNodeId[originalGraph->nodes[i].originalID]=result->nodes.size();
//                Grafo graphTemp;
//                graphTemp.addNode();
//                graphTemp.nodes[0].originalID=originalGraph->nodes[i].originalID;
//                graphTemp.nodes[0].nameRoad=originalGraph->nodes[i].nameRoad;
//                graphTemp.nodes[0].levelHierarchyRoad=originalGraph->nodes[i].levelHierarchyRoad;
//                graphTemp.nodes[0].location=originalGraph->nodes[i].location;
//                graphTemp.nodes[0].mass=originalGraph->nodes[i].mass;
//                clusters.push_back(graphTemp);
            }

        }
    }


    for(long i=0;i<originalGraph->links.size();i++){
        if(newClusterIds[originalGraph->links[i]->A()->id]!=newClusterIds[originalGraph->links[i]->B()->id]){
            double distance;
            if(useOriginalDistances){
                distance=originalGraph->links[i]->weight;
            }else{
                distance=Functions::getDistance(result->nodes[newClusterIds[originalGraph->links[i]->A()->id]]->location, result->nodes[newClusterIds[originalGraph->links[i]->B()->id]]->location);
            }
            result->addLink(newClusterIds[originalGraph->links[i]->A()->id], newClusterIds[originalGraph->links[i]->B()->id], distance);
        }
    }


    //    std::cout<<"a"<<'\n';
//    for(long i=0;i<originalGraph->nodes.size();i++){
////        nodesPerOriginalId[originalGraph->nodes[i]->originalID]=(originalGraph->nodes[i]);
//        if(clusterIdPerNodeId[originalGraph->nodes[i]->originalID]-1==-1){
//                    }
//    }
    //std::cout<<"b"<<'\n';
//    long numberOfTransitions=0;
//    for(long i=0;i<clusters.size();i++){
//        if(clusters[i].nodes.size()>0){
//            result->nodes[i].originalID=clusters[i].nodes[0].originalID;
//        }
//    }




//    long numberOfCollapsedNodes=0;
//    for(long i=0;i<clusters.size();i++){
//        //        result->nodes[i].originalID=clusters[i].nodes[0].originalID;
//        for(long j=0;j<clusters[i].nodes.size();j++){
//
//            Node* node=nodesPerOriginalId[clusters[i].nodes[j].originalID];
//            result->nodes[i].nodesCollapsed.push_back(node);
//            numberOfCollapsedNodes++;
//            for(long h=0;h<node->transitions.size();h++){
//                //                long originalId=otherNode->transitions[h].b->originalID;
//                long idOfNode=clusterIdPerNodeId[node->transitions[h]->a->originalID]-1;
//                long idOfOtherCluster=clusterIdPerNodeId[node->transitions[h]->b->originalID]-1;
//                if(idOfOtherCluster!=idOfNode){
//
//                    Transition trans;
//                    trans.a=&(result->nodes[idOfNode]);
//                    trans.a->location=locations[idOfNode];
//                    trans.b=&(result->nodes[idOfOtherCluster]);
//                    trans.b->location=locations[idOfOtherCluster];
//                    trans.weight=Functions::getDistance(trans.a->location, trans.b->location);
//                    trans.originalID=node->transitions[h]->originalID;
//                    trans.nameRoad=node->transitions[h]->nameRoad;
//                    trans.levelHierarchyRoad=node->transitions[h]->levelHierarchyRoad;
//                    std::vector<double> otherWeights;
//                    trans.otherWeights=otherWeights;
//                    if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
//                        result->addDirectedTransition(trans);
//                        numberOfTransitions++;
//                        result->nodes[idOfNode].transitions[result->nodes[idOfNode].transitions.size()-1]->transitionsCollapsed.push_back(node->transitions[h]);
//                    }else{
//                        result->nodes[idOfNode].transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->transitionsCollapsed.push_back(node->transitions[h]);
//                    }
//                }else{
//                    result->nodes[i].transitionsCollapsedIntoNode.push_back(node->transitions[h]);
//                }
//            }
//        }
//    }
    //    std::cout<<"c"<<'\n';


//    result->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
//    result->insertTopologicalWeights();
//    if(originalGraph->bidirectional){
//        result->transformToBidirectional();
//    }
    //    std::cout<<"d"<<'\n';
//    std::cout<<"number of transitions after generating superGraph of clusters "<<numberOfTransitions<<'\n';
//    std::cout<<"number of collapsed nodes "<<numberOfCollapsedNodes<<'\n';
}


void Grafo::setNodeAsTemp(Nodo* node){
    node->identifier="temp";
    temporaryNodes.insert(node);
}
long Grafo::sizeOfTempLinks(){
    return temporaryLinks.size();
}

void Grafo::setLinkAsTemp(Link* link){
    link->identifier="temp";
    temporaryLinks.insert(link);
}
void Grafo::removeTemporaryLinks(Grafo* G){
    G->removeLinks(G->temporaryLinks);

}
void Grafo::removeTemporaryNodes(Grafo* G){
    G->removeNodes(G->temporaryNodes);

}


std::tuple<std::vector<double>, std::vector<double> > Grafo::getPointsEvenBreaks(Grafo* G,double breaksEach){
    std::vector<double> x;
    std::vector<double> y;
    x.reserve(G->nodes.size());
    y.reserve(G->nodes.size());
    for(long i=0;i<G->nodes.size();i++){
        if(G->nodes[i]->getDegree()!=2){
            x.push_back(G->nodes[i]->location.x);
            y.push_back(G->nodes[i]->location.y);
        }

    }
    for(long i=0;i<G->links.size();i++){
        double w=G->links[i]->weight;
        double breaks=w/breaksEach;
        double dx=G->links[i]->B()->location.x-G->links[i]->A()->location.x;
        double dy=G->links[i]->B()->location.y-G->links[i]->A()->location.y;
        dx/=w;
        dy/=w;
        for(double j=0.0;j<breaks;j++){

            x.push_back(G->links[i]->A()->location.x+dx*j*breaksEach);
            y.push_back(G->links[i]->A()->location.y+dy*j*breaksEach);

        }
    }
    std::tuple<std::vector<double>, std::vector<double> > result;
    result=std::make_tuple(x,y);
    return result;
}



void Grafo::getNormalisedGraphEvenBreaks(Grafo* G,Grafo* result,double breaksEach){
    // std::vector<double> x;
    // std::vector<double> y;
    // x.reserve(G->nodes.size());
    // y.reserve(G->nodes.size());
    result->copyProperties(G);
    result->allowLoops=false;
    // for(long i=0;i<G->nodes.size();i++){
    //     if(G->nodes[i]->getDegree()!=2){
    //         x.push_back(G->nodes[i]->location.x);
    //         y.push_back(G->nodes[i]->location.y);
    //     }
    //
    // }

    for(long i=0;i<G->links.size();i++){
        double w=G->links[i]->weight;
        double breaks=round(w/breaksEach);
        double dx=G->links[i]->B()->location.x-G->links[i]->A()->location.x;
        double dy=G->links[i]->B()->location.y-G->links[i]->A()->location.y;
        dx/=w;
        dy/=w;
        Nodo* previousNode=result->addNode(G->links[i]->A()->location);
        for(double j=0.0;j<breaks;j++){

            Nodo* node=result->addNode(Point2d(G->links[i]->A()->location.x+dx*j*breaksEach,G->links[i]->A()->location.y+dy*j*breaksEach));
            // if(j>0){
              result->addLink(previousNode->id,node->id,Functions::getDistance(previousNode->location,node->location));
            // }
            previousNode=node;
            // y.push_back();

        }
        Nodo* node=result->addNode(G->links[i]->B()->location);
        result->addLink(previousNode->id,node->id,Functions::getDistance(previousNode->location,node->location));
    }
    // std::tuple<std::vector<double>, std::vector<double> > result;
    // result=std::make_tuple(x,y);
    // return result;
}



void Grafo::continuityAnglesAndLengthAndLoop(Grafo* G, double maxDistance,std::vector<bool>& idLinksThatAreContinuousAndLoop){
    // Grafo* G=deg->getPrimalGraph();
    double toleranceAngle=30;
    double toleranceLength=50;
    idLinksThatAreContinuousAndLoop.clear();
    idLinksThatAreContinuousAndLoop.resize(G->links.size(),false);

    for(long i=0;i<G->links.size();i++){
        // if(!idLinksThatAreContinuousAndLoop[G->links[i]->id]){
        if(true){
            //direction 1
            std::set<long> idLinksAccepted;
            Nodo* originalNode=G->links[i]->A();
            idLinksAccepted.insert(G->links[i]->id);
            // std::cout<<"current i "<<i<<'\n';
            for(long j=0;j<G->links[i]->B()->links.size();j++){
                Nodo* secondaryNode=G->links[i]->B()->links[j]->getOtherNode(G->links[i]->B());
                double initialAngle=Functions::getAngle(G->links[i]->A()->location,G->links[i]->B()->location,secondaryNode->location);
                if(Functions::abs(initialAngle)<89){
                    double initialLength=G->links[i]->weight/2.0+G->links[i]->B()->links[j]->weight/2.0;
                    double currentDistance=Functions::getDistance(originalNode->location,secondaryNode->location);
                    bool STOP=false;
                    Link* currentLink=G->links[i]->B()->links[j];
                    Nodo* currentNode=G->links[i]->B();
                    Nodo* nextNode=G->links[i]->B()->links[j]->getOtherNode(G->links[i]->B());
                    idLinksAccepted.insert(currentLink->id);
                    // std::cout<<"initialAngle "<<initialAngle<<" initialLength "<<initialLength<<'\n';
                    while(currentDistance<maxDistance&&!STOP){
                        // std::cout<<"originalNode "<<originalNode<<" currentNode "<<currentNode<<" nextNode "<<nextNode<<" current Link "<<currentLink<<'\n';
                        double min=INFINITY;
                        long indexMin=-1;
                        Nodo* nextSecondaryNode=NULL;
                        for(long k=0;k<nextNode->links.size();k++){
                            secondaryNode=nextNode->links[k]->getOtherNode(nextNode);
                            double currentAngle=Functions::getAngle(currentNode->location,nextNode->location,secondaryNode->location);
                            double currentLength=currentLink->weight/2.0+nextNode->links[k]->weight/2.0;
                            // std::cout<<"initialAngle "<<initialAngle<<" initialLength "<<initialLength<<'\n';
                            // std::cout<<"currentAngle "<<currentAngle<<" currentLength "<<currentLength<<'\n';
                            if(Functions::abs(currentAngle)<89){
                                if(Functions::abs(currentAngle-initialAngle)<toleranceAngle&&Functions::abs(currentLength-initialLength)<toleranceLength){
                                    if(Functions::abs(currentAngle-initialAngle)<min){
                                        min=Functions::abs(currentAngle-initialAngle);
                                        indexMin=k;
                                        nextSecondaryNode=secondaryNode;
                                    }
                                    // if(Functions::abs(currentAngle-initialAngle)+Functions::abs(currentLength-initialLength)<min){
                                    //     min=Functions::abs(currentAngle-initialAngle)+Functions::abs(currentLength-initialLength);
                                    //     indexMin=k;
                                    //     nextSecondaryNode=secondaryNode;
                                    // }
                                }
                            }

                        }
                        // std::cout<<"indexmin "<<indexMin<<'\n';
                        if(indexMin==-1){
                            STOP=true;
                            idLinksAccepted.clear();
                        }else{
                            currentLink=nextNode->links[indexMin];
                            currentNode=nextNode;
                            nextNode=nextSecondaryNode;

                            if(currentLink==G->links[i]){
                                STOP=true;
                                idLinksAccepted.insert(currentLink->id);
                            }else if (idLinksAccepted.count(currentLink->id)){
                                // std::cout<<"it made a loop"<<'\n';
                                STOP=true;
                                idLinksAccepted.clear();
                            }else{
                                idLinksAccepted.insert(currentLink->id);
                            }

                            currentDistance=Functions::getDistance(originalNode->location,nextNode->location);
                            // std::cout<<"current distance "<<currentDistance<<'\n';
                            if(currentDistance>maxDistance){
                                STOP=true;
                                idLinksAccepted.clear();
                            }
                        }

    //                    double angleDifference;
                    }
                }else{
                    idLinksAccepted.clear();
                }
            }
            if(G->links[i]->B()->links.size()<2){
                idLinksAccepted.clear();
            }
            if(idLinksAccepted.size()>0){
                for(auto id:idLinksAccepted){
                    idLinksThatAreContinuousAndLoop[id]=true;
                }
            }
            //direction 2
        }
    }
}


// void Grafo::addLabelsLevelsToLinks(Grafo* G,std::vector<long>& labels){
//   for(long i=0;i<labels.size();i++){
//     if(labels[i]!=-1){
//       G->links[i]->labelsLevels.push_back(labels[i]);
//     }
//   }
// }

#include "Transition.h"

Transition::Transition()
{
    //ctor
//    a=a;
//    b=b;
//    Transition::weight=weight;
//    Transition::angularWeight=angularWeight;
//    Transition::metricWeight=metricWeight;
//    alreadyUsedDijkstra=false;
    idNodeDualA=-1;
    idNodeDualB=-1;
    numColor=-1;
    transitionThatRepresents=NULL;
    transitionRepresentedBy=NULL;
    firstAngleInPhaseTransition=INFINITY;
    widthDrawing=1;
    inverted=false;
    bidirectional=false;
    levelHierarchyRoad=std::numeric_limits<int>::infinity();
//     levelHierarchyRoad=-1;
    nameRoad="";
    isPath=false;
    a=NULL;
    idA=-1;
    b=NULL;
    idB=-1;
//    oppositeTransitionId=-1;
    id=-1;
    originalID=-1;
    usedInNetworkPercolation=false;
    transitionOfLineGraphFromNodeOfDegree2=false;
    inCutoff=false;
    numberTimesInPercolationThreshold=0;
    hierarchicalValues.clear();
//    ca=NULL;
//    cb=NULL;
}
void Transition::checkDirection(bool invert){
//    std::cout<<invert<<" "<<inverted;
    if (invert!=inverted){
//        Node* tempA=a;
//        a=b;
//        b=tempA;
//        std::cout<<" before swap "<<a->originalID<<" "<<b->originalID<<'\n';
        std::swap(a,b);
//        std::cout<<" after swap "<<a->originalID<<" "<<b->originalID<<'\n';
        inverted=!inverted;
        bidirectional=true;
    }
//    std::cout<<" no swap "<<a->originalID<<" "<<b->originalID<<'\n';
}
void Transition::setTransition(Node* a, Node* b,double weight,std::vector<double> otherWeights)
{
    this->a=a;
    this->b=b;
    this->weight=weight;
    this->otherWeights=otherWeights;
}

Transition::~Transition()
{
    //dtor
}
Transition* Transition::getSimetricTransition()
{
    long indexOfOtherTrans=b->indexOfTransitionsByIdOfDestination[a->originalID]-1;
    Transition* trans;
    
    if(indexOfOtherTrans!=-1){
//        if(bidirectional){
//            indexOfOtherTrans=b->indexOfTransitionsByIdOfDestination[a->originalID]-1
//        }
        trans=(b->transitions[indexOfOtherTrans]);
    }else{
        trans=NULL;
    }
    return trans;
}

//Transition* Transition::getCopy(){
//    Transition* trans=new Transition();
//    trans->transitionThatRepresents=this;
//    return trans;
//}

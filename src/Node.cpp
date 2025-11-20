#include "Node.h"
//#include "Math.h"
//#include<boost>
//#include <boost/smart_ptr/shared_ptr.hpp>
Node::Node()
{
//    if(numberDistances>1){
//        std::cout<<"jhjh"<<'\n';
//    }
//    if(numberDistances==0){
//        std::cout<<"jhjh"<<'\n';
//    }
    //ctor
//    MinHeap<Node> nodesToCheckDijkstra;
//    MinHeap<Node> Node::nodesCutoff;
    numberOfTimesVisited=0;
    diffusionValue=0;
    isCenter=false;
    isCovered=false;
    mass=1;
    probabilityInPath=1;
    alreadyCalculated=false;
    levelHierarchyRoad=std::numeric_limits<int>::infinity();
//    levelHierarchyRoad=-1;
    nameRoad="";
    dataVector.clear();
    averagedDataVector.clear();
    
    nodesRelated.clear();
    kShellValue=0;
        kShellValueFinal=0;
    nodesThatReachMe.clear();
    tripsGenerated=0;
    degree=0;
    degreeOut=0;
    degreeIn=0;
     degreeModifier=0;
    degreeModifierOut=0;
        degreeModifierIn=0;
    tripsReceived=0;
    id=-1;
    numColor=-1;
//    population=1;
    dMax=0;
    initialNodeOfDiameter=NULL;
    uppestRepresentative=NULL;
    nodeInOriginalGraph=NULL;
    transitionThatRepresents=NULL;
    inSubgraph=false;
    depthInRTree=0;
    upperLevel=-1;
    isFrontier=false;
    isFrontierOfDifferentLevel=false;
    this->valueToPass=1;
    this->numChildren=0;
    this->numChildrenThatReachedMe=0;
    
    nodeRepresentedBy=NULL;
    nodeThatRepresents=NULL;
    idEquivalentLowerVerticalNode=-1;
    idEquivalentUpperVerticalNode=-1;
//    this->transitionsAlreadyUsed=false;
    this->minDistance=INFINITY;
    inExternalNodes=false;
//    std::vector<double> minDistancesTemp(numberDistances,-1);
//    minOtherDistances=minDistancesTemp;
//    std::vector<Node*> parentOtherTemp(numberDistances);
//    otherParents=parentOtherTemp;
//    minOtherDistances.resize(numberDistances);
//    otherParents(numberDistances,NULL);
    minOtherDistances.clear();
    this->numberDistances=0;
    minOtherDistances.resize(numberDistances,INFINITY);
    numOtherChildren.resize(numberDistances,0);
    numOtherChildrenThatReachedMe.resize(numberDistances,0);
    valuesToPass.resize(numberDistances,1);
    originalValuesToPass.resize(numberDistances,1);
    originalValueToPass=1;
    otherParents.resize(numberDistances,NULL);
//	for (int i=0; i<numberDistances; i++) {
//		this->minOtherDistances.push_back(-1);
//		this->otherParents.push_back(NULL);
//	}
//	for (int i=0; i<numberDistances; i++) {
//		std::cout<<"size of parents "<<otherParents[i]<<'\n';
//	}
    hasParent=false;
    inDijkstra=false;
    inCluster=false;
    parent=NULL;
    inCutoff=false;
    inAStar=false;
    inVisitedNodes=false;
    indexOfTransitionsByIdOfDestination.clear();
//    minDistanceAStar=0;
//    parentAngular=NULL;


//    this->parent=new Node();
//    this->parentAngular=new Node();
//    this->parentMetric=new Node();
//    this->nodeThatRepresents=new Node();
}
//Node::Node(const Node &t){
//        Node* tempParent = new Node(*t.parent);
//        std::swap(tempParent, parent);
//        delete parent;
//        Node* tempParentAngular = new Node(*t.parentAngular);
//        std::swap(tempParentAngular, parentAngular);
//        delete parentAngular;
//        Node* tempParentMetric = new Node(*t.parentMetric);
//        std::swap(tempParentMetric, parentMetric);
//        delete parentMetric;
//        Node* tempNodeThatRepresents = new Node(*t.nodeThatRepresents);
//        std::swap(tempNodeThatRepresents, nodeThatRepresents);
//        delete nodeThatRepresents;
//
//}

// Node& Node::operator = (const Node &t){
//        Node* tempParent = new Node(*t.parent);
//        std::swap(tempParent, parent);
//        delete parent;
//        Node* tempParentAngular = new Node(*t.parentAngular);
//        std::swap(tempParentAngular, parentAngular);
//        delete parentAngular;
//        Node* tempParentMetric = new Node(*t.parentMetric);
//        std::swap(tempParentMetric, parentMetric);
//        delete parentMetric;
//        Node* tempNodeThatRepresents = new Node(*t.nodeThatRepresents);
//        std::swap(tempNodeThatRepresents, nodeThatRepresents);
//        delete nodeThatRepresents;
//        return *this;
//}

Node::~Node()
{
    //dtor
//    for(long i=0;i<otherParents.size();i++){
//        delete otherParents[i];
//    }

//        transitions.clear();
//        std::vector<Transition>().swap(transitions);
//        minOtherDistances.clear();
//        std::vector<double>().swap(minOtherDistances);
//        otherParents.clear();
//        std::vector<Node*>().swap(otherParents);

//        Node* tempParent;
//        std::swap(tempParent, parent);
////        delete parent;
//        Node* tempParentAngular;
//        std::swap(tempParentAngular, parentAngular);
////        delete parentAngular;
//        Node* tempParentMetric;
//        std::swap(tempParentMetric, parentMetric);
////        delete parentMetric;
//        Node* tempNodeThatRepresents;
//        std::swap(tempNodeThatRepresents, nodeThatRepresents);
////        delete nodeThatRepresents;


//    delete parent;
//    delete parentAngular;
//    delete parentMetric;
//    delete nodeThatRepresents;
}
//void Node::removeSon(Node* node){
//    for (int i=0;i<sons.size();i++){
//        if (sons[i]==&node){
//            sons.remove(i);
//            i--;
//        }
//    }
//}
void Node::setIndexInHeap(Node* &node,long index,long indexOfTheHeap){
    while(indexOfTheHeap>=node->indexInHeap.size()){
        node->indexInHeap.push_back(-1);
    }
    node->indexInHeap[indexOfTheHeap]=index;
}
long Node::getIndexInHeap( Node* &node,long indexOfTheHeap){
    return (node->indexInHeap[indexOfTheHeap]);
}
Node* Node::getCopy()
{
//    Node *node=new Node();
//    node->nodeThatRepresents=this;
//    return *node;
    Node* node=new Node();
//        std::cout<<"node "<<node<<'\n';
//std::cout<<"nodesToCheckDijkstra "<<nodesToCheckDijkstra.heap<<'\n';
//    boost::scoped_ptr<Node> node(new Node());
//    node.parent=new Node();
//    node.parentAngular=new Node();
//    node.parentMetric=new Node();
//    node.nodeThatRepresents=new Node();
    node->nodeThatRepresents=this;
    return node;

}

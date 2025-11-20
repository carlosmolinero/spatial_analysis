#include "Graph.h"


const int Graph::METRIC;
const int Graph::TOPOLOGICAL;
const int Graph::ANGULAR;
const int Graph::COMBINED_METRIC_ANGULAR;
const int Graph::COMBINED_METRIC_TOPOLOGICAL;
const int Graph::COMBINED_ANGULAR_TOPOLOGICAL;
const int Graph::COMBINED_SLOPE_GREENAREAS;
const int Graph::COGNITIVE;
const int Graph::SLOPE;
const int Graph::GREEN_AREAS_IMPEDANCE;
const int Graph::COMBINED_COGNITIVE_SLOPE_GREENAREAS;
const int Graph::COMBINED_COGNITIVE_GREENAREAS;
const int Graph::COMBINED_METRIC_COGNITIVE;
const int Graph::TIME_DISTANCE;
const int Graph::COMBINED_ANGULAR_COGNITIVE;
const int Graph::COMBINED_TIMEDISTANCE_COGNITIVE;
const int Graph::INFORMATIONAL;
const int Graph::POTENTIAL_FIELD;

const int Graph::COMBINED_ANGULAR_GREENAREAS;
const int Graph::COMBINED_SLOPE_ANGULAR;

Graph::Graph()
{
    degreesCalculated=false;
    useGaussianBetweenness=false;
    allowLoops=false;
    strictlyDirectional=false;
//    customize=false;
    bidirectional=false;
    pseudoGraph=false;
    calculateBetweenness=true;
    //ctor
    //    INF=std::numeric_limits<double>::infinity();
    calculateMainDistance=false;
    calculateOtherDistances=false;
    indexOfMainDistanceInOtherDistances=-1;
    avoidBacktrackingInLineGraph=false;
    
    //    diameterWeighted=0;
    //    diameterTopological=0;
    //    averageWeightedDistance=0;
    //    averageTopologicalDistance=0;
    //    topologicalLengthOfMetricDiameter=0;
    //    weightedLengthOfTopologicalDiameter=0;
    //    numberNodes=0;
    numberDistances=0;
    nodes.clear();
    id=-1;
    avoidBacktrackingInLineGraph=false;
    calculateTSL=false;
    //	currentIndexDistance=-1;
    
}

Graph::~Graph()
{
    //dtor
}

Graph::Graph(const Graph& other){
  
    const Graph* temp;
//        calculateBetweenness=true;
    temp=&other;
    copyGraph(temp, this,true);
    avoidBacktrackingInLineGraph=false;
    calculateTSL=false;
}

void Graph::prepareForCentralitiesCalculation()
{
    //    diameterWeighted=0;
    //    diameterTopological=0;
    //    averageWeightedDistance=0;
    //    averageTopologicalDistance=0;
    //    topologicalLengthOfMetricDiameter=0;
    //    weightedLengthOfTopologicalDiameter=0;
    //    numberNodes=0;
    
    betweenness.clear();
    closeness.clear();
    eccentricity.clear();
    for (int i=0; i<betweennessMeasures.size(); i++)
    {
        betweennessMeasures.clear();
        closenessMeasures.clear();
    }
    betweennessMeasures.clear();
    closenessMeasures.clear();
    
    nodeCount.clear();
    TSL.clear();
    for (long i=0; i<nodes.size(); i++)
    {
        betweenness.push_back(0);
        closeness.push_back(0);
        eccentricity.push_back(0);
        nodeCount.push_back(0);
        TSL.push_back(0);
    }
    for (int i=0; i<numberDistances; i++)
    {
        std::vector<double> betTemp;
        std::vector<double> closenessTemp;
        for (long j=0; j<nodes.size(); j++)
        {
            betTemp.push_back(0);
            closenessTemp.push_back(0);
        }
        betweennessMeasures.push_back(betTemp);
        closenessMeasures.push_back(closenessTemp);
    }
    
}



void Graph::calculationCentralities(Graph* graph,double radius,long startNode,long endNode,int threadNumber,int indexDistanceInOtherDistancesCutoff,int indexDistanceInOtherDistancesCalculation)
{
//    graph->prepareForCentralitiesCalculation();
    
    for(long i=0;i<graph->nodes.size();i++){
        for(long j=0;j<graph->nodes[i].transitions.size();j++){
            graph->nodes[i].transitions[j]->weight=graph->nodes[i].transitions[j]->otherWeights[indexDistanceInOtherDistancesCutoff];
        }
    }
    graph->indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCutoff;
    
    
    
    graph->calculateCentralities=true;
    graph->calculateDiffussion=false;
    graph->calculateGlobalProperties=false;
    
    graph->calculateMainDistance=false;
    graph->calculateTSL=false;
    graph->calculateOtherDistances=true;

//    std::cout<<"START"<<'\n';
    
    for (long i=startNode; i<endNode; i++)
    {
        if(i%1000==0){
            std::cout<<"Calculating centralities "<<i*100/(endNode-startNode)<< "%"<<'\n';
        }
        
        std::vector<Node*> listNodes;
        Node* nodeInit=&(graph->nodes[i]);
        std::vector<int> indexOfDistancesToCalculate;
        indexOfDistancesToCalculate.push_back(indexDistanceInOtherDistancesCalculation);
        
        graph->calculateShortestPathsSpeed(nodeInit,radius,indexOfDistancesToCalculate);
        
    }
    
    
    
    
    
//    std::cout<<"END"<<'\n';
}



void Graph::transformToBidirectional()
{
    bidirectional=true;
    signed long long maxOriginalId=0;
    long maxId=0;
    for(long i=0; i<nodes.size(); i++)
    {
        for(long j=0; j<nodes[i].transitions.size(); j++)
        {
            if(nodes[i].transitions[j]->originalID>maxOriginalId){
                maxOriginalId=nodes[i].transitions[j]->originalID;
            }
            if(nodes[i].transitions[j]->id>maxId){
                maxId=nodes[i].transitions[j]->id;
            }
        }
    }
    maxOriginalId++;
    maxId++;
    for(long i=0; i<nodes.size(); i++)
    {
        for(long j=0; j<nodes[i].transitions.size(); j++)
        {
            bool existOtherTransition=false;
            double weightOther=0;
            long indexOther=0;
//            for(long h=0; h<nodes[i].transitions[j].b->transitions.size(); h++)
//            {
            long indexOfOppositeTransition=nodes[i].transitions[j]->b->indexOfTransitionsByIdOfDestination[nodes[i].originalID]-1;
//                if (nodes[i].transitions[j].b->transitions[h].b==&nodes[i])
            if(indexOfOppositeTransition!=-1)
                {
//                    long indexOfOppositeTransitionInOtherDirection=nodes[i].transitions[indexOfOppositeTransition].b->indexOfTransitionsByIdOfDestination[nodes[i].originalID]-1;
                    existOtherTransition=true;
                    weightOther=nodes[i].transitions[j]->b->transitions[indexOfOppositeTransition]->weight;
                    indexOther=indexOfOppositeTransition;
//                    nodes[i].transitions[j].oppositeTransitionId=nodes[i].transitions[j].b->transitions[indexOfOppositeTransition].id;
//                    nodes[i].transitions[j].b->transitions[indexOfOppositeTransition].oppositeTransitionId=nodes[i].transitions[j].id;
                }
//            }
            if (!existOtherTransition)
            {
                Transition trans;
                trans.a=nodes[i].transitions[j]->b;
                trans.b=nodes[i].transitions[j]->a;
                trans.weight=nodes[i].transitions[j]->weight;
                trans.levelHierarchyRoad=nodes[i].transitions[j]->levelHierarchyRoad;
                trans.nameRoad=nodes[i].transitions[j]->nameRoad;
                trans.otherWeights=nodes[i].transitions[j]->otherWeights;
                trans.originalID=maxOriginalId;
                trans.id=maxId;
//                trans.oppositeTransitionId=nodes[i].transitions[j].id;
//                nodes[i].transitions[j].oppositeTransitionId=trans.id;
                
                maxOriginalId++;
                maxId++;
                addDirectedTransition(trans);
                
            }
            else
            {
                double min=std::min(weightOther,nodes[i].transitions[j]->weight);
                nodes[i].transitions[j]->b->transitions[indexOther]->weight=min;
                nodes[i].transitions[j]->weight=min;
                for(long h=0;h<nodes[i].transitions[j]->otherWeights.size();h++){
                    nodes[i].transitions[j]->otherWeights[h]=std::min(nodes[i].transitions[j]->otherWeights[h],nodes[i].transitions[j]->b->transitions[indexOfOppositeTransition]->otherWeights[h]);
                }
            }
        }
    }
}
void Graph::printNodes()
{
    for (long i=0; i<nodes.size(); i++)
    {
        std::cout<<nodes[i].id<<'\n';
    }
}
Node& Graph::addNode()
{
    Node node;
    node.id=this->nodes.size();
    node.originalID=node.id;
    this->nodes.push_back(node);
    //    numberNodes++;
    return (nodes[nodes.size()-1]);
}
bool Graph::compareByDistance(Node a,Node b)
{
    return (a.minDistance>b.minDistance);
}
bool Graph::compareByDistance(Node* &a,Node* &b)
{
    return (a->minDistance>b->minDistance);
}
bool Graph::compareByOtherDistances(Node* &a,Node* &b,int indexDistance)
{
    return (a->minOtherDistances[indexDistance]>b->minOtherDistances[indexDistance]);
}
bool Graph::compareByWeight(Transition* &a,Transition* &b)
{
    return (a->weight>b->weight);
}
bool Graph::compareByDistanceIsSmallerThan(Node* a,Node* b)
{
    return (a->minDistance<b->minDistance);
}
bool Graph::compareByDistanceAndHeuristic(Node* &a,Node* &b)
{
    return (a->minDistance+a->heuristicDistanceToGoal>b->minDistance+b->heuristicDistanceToGoal);
}
bool Graph::compareByWaterLevel(Node* a,Node* b)
{
    return (a->waterLevel.level>b->waterLevel.level);
}
bool Graph::compareByNumChildren(Node* a,Node* b)
{
    return (a->numChildren<b->numChildren);
}
bool Graph::compareByDegreeOut(Node* &a,Node* &b)
{
    return (getDegreeOut(a)>getDegreeOut(b));
}

bool Graph::compareByDegreeOutAndKShellValue(Node* &a,Node* &b)
{
    return (getDegreeOut(a)-a->kShellValue>getDegreeOut(b)-b->kShellValue);
}

//template<int index>

//bool Graph::compareByOtherDistance(Node* a,Node* b){
////    return ((a->minOtherDistances[index])>(b->minOtherDistances[index]));
//    return (a->minDistance>b->minDistance);
//}

bool Graph::compareById(Node a,Node b)
{
    return (a.id<b.id);
}


signed long long Graph::getOriginalId(Node* &a)
{
    return (a->originalID);
}
double Graph::getMinDistance(Node* &a)
{
    return (a->minDistance);
}
double Graph::getDegreeOut(Node* &a)
{
    return (a->transitions.size()+a->degreeModifierOut);
}
double Graph::getDegreeIn(Node* &a)
{

        return(a->nodesThatReachMe.size()+a->degreeModifierIn);
 
}
double Graph::getDegree(Node* &a)
{
    return(a->transitions.size()+a->degreeModifier);
    
}
double Graph::getMinOtherDistances( Node* &a,int indexDistance)
{
    return (a->minOtherDistances[indexDistance]);
}

//bool Graph::compareById(Transition* a,Transition* b){
//    return (a->id<b->id);
//}
double Graph::getDistance(Node* a)
{
    return a->minDistance;
}
double Graph::getId(Node* a)
{
    return a->nodeThatRepresents->id;
}
void Graph::addBidirectionalTransition(Node* a, Node* b,double weight, std::vector<double> otherWeights)
{
    Transition transition;
    transition.setTransition(a,b,weight,otherWeights);
    Transition transitionB;
    transitionB.setTransition(b,a,weight,otherWeights);
    addTransition(transition);
    addTransition(transitionB);
//    if (a->transitions.size()>2)
//    {
//        a->valueToPass=1;
//        a->valuesToPass.resize(numberDistances,1);
//    }
//    if (b->transitions.size()>2)
//    {
//        b->valueToPass=1;
//        b->valuesToPass.resize(numberDistances,1);
//    }
    //    transition.equivalentTransitionInOtherDirection=&transitionB;
    //    transitionB.equivalentTransitionInOtherDirection=&transition;
}
void Graph::addBidirectionalTransition(long aIndex, long bIndex,double weight, std::vector<double> otherWeights)
{
    Node* a=&(this->nodes[aIndex]);
    Node* b=&(this->nodes[bIndex]);
    Transition transition;
    transition.setTransition(a,b,weight,otherWeights);
    Transition transitionB;
    transitionB.setTransition(b,a,weight,otherWeights);
    addTransition(transition);
    addTransition(transitionB);
//    if (a->transitions.size()>2)
//    {
//        a->valueToPass=1;
//        a->valuesToPass.resize(numberDistances,1);
//    }
//    if (b->transitions.size()>2)
//    {
//        b->valueToPass=1;
//        b->valuesToPass.resize(numberDistances,1);
//    }
    //    transition.equivalentTransitionInOtherDirection=&transitionB;
    //    transitionB.equivalentTransitionInOtherDirection=&transition;
}
void Graph::addDirectedTransition(Node* a, Node* b,double weight, std::vector<double> otherWeights)
{
    Transition transition;
    transition.setTransition(a,b,weight,otherWeights);
    
    addTransition(transition);
    
//    if (a->transitions.size()>2)
//    {
//        a->valueToPass=1;
//        a->valuesToPass.resize(numberDistances,1);
//    }
    
    //    transition.equivalentTransitionInOtherDirection=&transitionB;
    //    transitionB.equivalentTransitionInOtherDirection=&transition;
}
void Graph::addDirectedTransition(Transition &trans)
{
 
    
    addTransition(trans);
    
//    if (trans.a->transitions.size()>2)
//    {
//        trans.a->valueToPass=1;
//        trans.a->valuesToPass.resize(numberDistances,1);
//    }
    
    //    transition.equivalentTransitionInOtherDirection=&transitionB;
    //    transitionB.equivalentTransitionInOtherDirection=&transition;
}
void Graph::addDirectedTransition(long aIndex, long bIndex,double weight, std::vector<double> otherWeights)
{
    Node* a=&(this->nodes[aIndex]);
    Node* b=&(this->nodes[bIndex]);
    Transition transition;
    transition.setTransition(a,b,weight,otherWeights);
    
    addTransition(transition);
    
//    if (a->transitions.size()>2)
//    {
//        a->valueToPass=1;
//        a->valuesToPass.resize(numberDistances,1);
//    }
    
    //    transition.equivalentTransitionInOtherDirection=&transitionB;
    //    transitionB.equivalentTransitionInOtherDirection=&transition;
}

void Graph::addTransition(Transition &trans)
{
    trans.id=this->transitions.size();
    if(allowLoops||trans.a!=trans.b){
        if(!pseudoGraph){
                long indexExistingTrans=-1;
        //    if(trans.b!=NULL)
        //    {
                indexExistingTrans=trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1;
        //    }
        //    else
        //    {
        //        indexExistingTrans=trans.a->indexOfTransitionsByIdOfDestination[trans.originalIdB]-1;
        //    }
            
//            if(indexExistingTrans!=-1)
            {
//                std::cout<<trans.a->id<<" "<<trans.b->id<<" "<<indexExistingTrans<<'\n';
//                 indexExistingTrans=trans.b->indexOfTransitionsByIdOfDestination[trans.a->originalID]-1;
            }
            
//            std::cout<<trans.a->originalID<<" "<<trans.b->originalID<<" "<<indexExistingTrans<<'\n';
            if(indexExistingTrans==-1)
            {
                
                if(!strictlyDirectional){
                    Transition* symmetricTrans=trans.getSimetricTransition();
//                    std::cout<<"symmetric trans "<<trans.a->originalID<<" "<<trans.b->originalID<<" "<<symmetricTrans<<'\n';
                    if(symmetricTrans==NULL||symmetricTrans->weight!=trans.weight){
                        long index=trans.a->transitions.size()+1;
                        transitions.push_back(trans);
                        Vector_elem<Transition> transPointer(transitions);
                        trans.a->transitions.push_back(transPointer);
                        trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
                        bool exist=false;
                        for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
                            if(trans.b->nodesThatReachMe[i]==trans.a){
                                exist=true;
                            }
                        }
                        if(!exist){
                            trans.b->nodesThatReachMe.push_back(trans.a);
                        }
                    }else{

                        Node* aSymmetric=symmetricTrans->a;
                        long index=trans.a->transitions.size()+1;
                        long indexMain=0;
                        
                        for(long i=0;i<aSymmetric->transitions.size();i++){
                            if(aSymmetric->transitions[i]==symmetricTrans){
                                indexMain=aSymmetric->transitions.getIndexInOriginalVector(i);
                            }
                        }
//                        std::cout<<indexMain<<" "<<aSymmetric->originalID<<" "<<trans.a->originalID<<'\n';
                        Vector_elem<Transition> transPointer(transitions,indexMain);
                        trans.a->transitions.push_back(transPointer);
                        trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
                        bool exist=false;
                        for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
                            if(trans.b->nodesThatReachMe[i]==trans.a){
                                exist=true;
                            }
                        }
                        if(!exist){
                            trans.b->nodesThatReachMe.push_back(trans.a);
                        }
                    }
                }else{
                    long index=trans.a->transitions.size()+1;
                    transitions.push_back(trans);
                    Vector_elem<Transition> transPointer(transitions);
                    trans.a->transitions.push_back(transPointer);
                    trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
                    bool exist=false;
                    for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
                        if(trans.b->nodesThatReachMe[i]==trans.a){
                            exist=true;
                        }
                    }
                    if(!exist){
                        trans.b->nodesThatReachMe.push_back(trans.a);
                    }
                }
            }
        }else{
            if(!strictlyDirectional){
                Transition* symmetricTrans=trans.getSimetricTransition();
                if(symmetricTrans==NULL||symmetricTrans->weight!=trans.weight){
                    
                    
                    long index=trans.a->transitions.size()+1;
                    transitions.push_back(trans);
                    Vector_elem<Transition> transPointer(transitions);
                    trans.a->transitions.push_back(transPointer);
                    trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
                    bool exist=false;
                    for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
                        if(trans.b->nodesThatReachMe[i]==trans.a){
                            exist=true;
                        }
                    }
                    if(!exist){
                        trans.b->nodesThatReachMe.push_back(trans.a);
                    }
                }else{
    //                long index=trans.a->transitions.size()+1;
    //                transitions.push_back(trans);
                    long index=trans.a->transitions.size()+1;
                    long indexMain=0;
                    Node* aSymmetric=symmetricTrans->a;
                    for(long i=0;i<aSymmetric->transitions.size();i++){
                        if(aSymmetric->transitions[i]==symmetricTrans){
                            indexMain=aSymmetric->transitions.getIndexInOriginalVector(i);
                        }
                    }
                    //TODO: indexMain fails when pseudoGraph because there are several transitions that are the same??
                    Vector_elem<Transition> transPointer(transitions,indexMain);
                    trans.a->transitions.push_back(transPointer);
                    trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
                    bool exist=false;
                    for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
                        if(trans.b->nodesThatReachMe[i]==trans.a){
                            exist=true;
                        }
                    }
                    if(!exist){
                        trans.b->nodesThatReachMe.push_back(trans.a);
                    }
                }
            }else{
                long index=trans.a->transitions.size()+1;
                transitions.push_back(trans);
                Vector_elem<Transition> transPointer(transitions);
                trans.a->transitions.push_back(transPointer);
                trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
                bool exist=false;
                for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
                    if(trans.b->nodesThatReachMe[i]==trans.a){
                        exist=true;
                    }
                }
                if(!exist){
                    trans.b->nodesThatReachMe.push_back(trans.a);
                }
            }
        }
    }
//    else
//    {
//        long index=trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1;
//        Transition* currentTrans=&(trans.a->transitions[index]);
//        double weight=min(trans.weight,currentTrans->weight);
//        currentTrans->weight=weight;
//        for(int i=0; i<min(trans.otherWeights.size(),currentTrans->otherWeights.size()); i++)
//        {
//            double weightTemp=min(trans.otherWeights[i],currentTrans->otherWeights[i]);
//            currentTrans->otherWeights[i]=weightTemp;
//        }
//        if(trans.b!=NULL)
//        {
//            currentTrans->b=trans.b;
//        }
//        
//    }
    
}




//void Graph::calculateShortestPaths(Node* nodeInit,double distanceLimit)
//{
//    //    std::cout<<"calculating shortest paths"<<'\n';
//    Node* startNode=nodeInit->getCopy();
//    BST<Node*> nodesCutoff;
//    MinHeap<Node*> nodesToCheckDijkstra;
//    nodesCutoff.add(startNode->nodeThatRepresents->id,startNode);
//    nodesToCheckDijkstra.push(startNode,&compareByDistance);
//    calculateDijkstra(nodeInit,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
//    nodesToCheckDijkstra.remove();
//    
//}




void Graph::calculateShortestPathsSpeed(Node* &nodeInit,double distanceLimit,std::vector<int> &setOfDistancesToCalculate)
{
    //    std::cout<<"calculating shortest paths"<<'\n';
    nodeInit->minDistance=0;
    Node* startNode=nodeInit;
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(startNode);
    startNode->inCutoff=true;
    nodesToCheckDijkstra.push(startNode);
    startNode->inDijkstra=true;
    startNode->minDistance=0;
    if(calculateMainDistance||distanceLimit!=0){
//        calculateMainDistance=true;
        calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
        if(calculateMainDistance&&calculateCentralities){
            makeCalculationsSpeed(startNode, nodesCutoff);
        }
        if(!calculateOtherDistances){
            
            for(long i=0; i<nodesCutoff.size(); i++)
            {
                //        if (nodes[i].minDistance>diamTemp){
                //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                //        }
//                if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                    nodesCutoff[i]->inCutoff=false;
                    
                    nodesCutoff[i]->inDijkstra=false;
                    nodesCutoff[i]->numChildren=0;
                    nodesCutoff[i]->numChildrenThatReachedMe=0;
                    nodesCutoff[i]->parent=NULL;
                    nodesCutoff[i]->minDistance=INFINITY;
                    nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
//                }
//                if (calculateOtherDistances)
//                {
//                    
//                    for (int j=0; j<numberDistances; j++)
//                    {
//                        nodesCutoff[i]->numOtherChildren[j]=0;
//                        nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
//                        nodesCutoff[i]->otherParents[j]=NULL;
//                        nodesCutoff[i]->minOtherDistances[j]=INFINITY;
//                        nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
//                    }
//                }
                
            }
        }
        
    }
    else if(distanceLimit==0){
        nodesCutoff.clear();
        for(long i=0;i<nodes.size();i++){
            nodes[i].inCutoff=true;
            nodesCutoff.push_back(&nodes[i]);
        }
    }
    
    if (this->calculateOtherDistances)
    {
        if(setOfDistancesToCalculate.size()==0){
            
            for (int indexDistance=0; indexDistance<numberDistances; indexDistance++)
            {
                setOfDistancesToCalculate.push_back(indexDistance);
            }
            
        }
        bool containsMetric=false;
        for(int i=0;i<setOfDistancesToCalculate.size();i++){
            if(setOfDistancesToCalculate[i]==getIndexesOfDistanceType(METRIC)[0]){
                containsMetric=true;
            }
        }
        bool calculateSpecialDistance=false;
        if(!containsMetric&&calculateSpecialDistance){
            setOfDistancesToCalculate.insert(setOfDistancesToCalculate.begin(), getIndexesOfDistanceType(METRIC)[0]);
        }
            for (int indexOfDistanceInSet=0; indexOfDistanceInSet<setOfDistancesToCalculate.size(); indexOfDistanceInSet++)
            {
                //			nodesToCheckDijkstra.clear();
                //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
                //			for (int i=0;i<orderedCutoff.size();i++){
                //				orderedCutoff[i]->inDijkstra=false;
                //			}
                //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
                //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
                
                
                if (setOfDistancesToCalculate[indexOfDistanceInSet]!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
                {
                    //                Node* startNode=(nodeInit);
                    //			this->currentIndexDistance=indexDistance;
                    //            int indexDistanceTemp=indexDistance;
                    CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],1);
                    nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,setOfDistancesToCalculate[indexOfDistanceInSet],1);
//                    nodesToCheckDijkstra.changeGetValueFunction(<#bool (*compare)(Node *, Node *, int)#>, <#double (*getValue)(Node *, int)#>, <#int indexInArray#>, <#int modeOfObjectComparison#>)
                    nodesToCheckDijkstra.push(startNode);
                    startNode->inDijkstra=true;
                    startNode->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
                    calculateDijkstraOtherDistanceSpeed(startNode,true,nodesToCheckDijkstra,setOfDistancesToCalculate[indexOfDistanceInSet]);
                    if (calculateGlobalProperties&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
//                    if(calculateGlobalProperties)
                    {
                        measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                    }
                    if (calculateCentralities&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
//                        if(calculateCentralities)
                    {
                        makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                    }
//                    else if (calculateCentralities&&calculateSpecialDistance){
//                        for(long h=0; h<nodesCutoff.size(); h++)
//                        {
//                            nodesCutoff[h]->specialDistance=nodesCutoff[h]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]];
//                        }
//                    }
//                    
                    for(long i=0; i<nodesCutoff.size(); i++)
                    {
                        //        if (nodes[i].minDistance>diamTemp){
                        //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                        //        }
                        if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                            nodesCutoff[i]->inCutoff=false;
                            
                            nodesCutoff[i]->inDijkstra=false;
                            nodesCutoff[i]->numChildren=0;
                            nodesCutoff[i]->numChildrenThatReachedMe=0;
                            nodesCutoff[i]->parent=NULL;
                            nodesCutoff[i]->minDistance=INFINITY;
                            nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                        }
                        if (calculateOtherDistances)
                        {
                            
                            for (int j=0; j<numberDistances; j++)
                            {
                                nodesCutoff[i]->numOtherChildren[j]=0;
                                nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                                nodesCutoff[i]->otherParents[j]=NULL;
                                nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                                nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
                            }
                        }
                        
                    }
                    if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                        nodesCutoff.clear();
                    }
                }else if (setOfDistancesToCalculate[indexOfDistanceInSet]==this->indexOfMainDistanceInOtherDistances){
                    for(long i=0;i<nodesCutoff.size();i++){
                        nodesCutoff[i]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->numChildren;
                        nodesCutoff[i]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->numChildrenThatReachedMe;
                        nodesCutoff[i]->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->parent;
                        nodesCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->minDistance;
                    }
                    if (calculateGlobalProperties&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
//                    if(calculateGlobalProperties)
                    {
                        measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                    }
                    if (calculateCentralities&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
//                    if(calculateCentralities)
                    {
                        makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                    }
//                    else if (calculateCentralities&&calculateSpecialDistance){
//                        for(long h=0; h<nodesCutoff.size(); h++)
//                        {
//                            nodesCutoff[h]->specialDistance=nodesCutoff[h]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]];
//                        }
//                    }
                    
                    for(long i=0; i<nodesCutoff.size(); i++)
                    {
                        //        if (nodes[i].minDistance>diamTemp){
                        //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                        //        }
                        if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                            nodesCutoff[i]->inCutoff=false;
                        
                            nodesCutoff[i]->inDijkstra=false;
                            nodesCutoff[i]->numChildren=0;
                            nodesCutoff[i]->numChildrenThatReachedMe=0;
                            nodesCutoff[i]->parent=NULL;
                            nodesCutoff[i]->minDistance=INFINITY;
                            nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                        }
                        if (calculateOtherDistances)
                        {
                            
                            for (int j=0; j<numberDistances; j++)
                            {
                                nodesCutoff[i]->numOtherChildren[j]=0;
                                nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                                nodesCutoff[i]->otherParents[j]=NULL;
                                nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                                nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
                            }
                        }
                        
                    }
                    if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                        nodesCutoff.clear();
                    }
                }
            }
        
        
    }

    nodesToCheckDijkstra.clear();

    
    
    nodesCutoff.clear();
    std::vector<Node*>().swap(nodesCutoff);
}








void Graph::calculateShortestPathsSpeedEuclideanCutoff(QTree* quadTree,Node* &nodeInit,double distanceLimit,std::vector<int> &setOfDistancesToCalculate)
{
//    //    std::cout<<"calculating shortest paths"<<'\n';
//    nodeInit->minDistance=0;
    Node* startNode=nodeInit;
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//    nodesCutoff.push_back(startNode);
//    startNode->inCutoff=true;
//    nodesToCheckDijkstra.push(startNode);
//    startNode->inDijkstra=true;
//    startNode->minDistance=0;
    if(calculateMainDistance||distanceLimit!=0){
        nodesCutoff=quadTree->getNodesInARange(nodeInit->location, distanceLimit);
        
    }
    else if(distanceLimit==0){
        nodesCutoff.clear();
        for(long i=0;i<nodes.size();i++){
            nodes[i].inCutoff=true;
            nodesCutoff.push_back(&nodes[i]);
        }
    }
    
    if (this->calculateOtherDistances)
    {
        if(setOfDistancesToCalculate.size()==0){
            
            for (int indexDistance=0; indexDistance<numberDistances; indexDistance++)
            {
                setOfDistancesToCalculate.push_back(indexDistance);
            }
            
        }
        bool containsMetric=false;
        for(int i=0;i<setOfDistancesToCalculate.size();i++){
            if(setOfDistancesToCalculate[i]==getIndexesOfDistanceType(METRIC)[0]){
                containsMetric=true;
            }
        }
        bool calculateSpecialDistance=false;
        if(!containsMetric&&calculateSpecialDistance){
            setOfDistancesToCalculate.insert(setOfDistancesToCalculate.begin(), getIndexesOfDistanceType(METRIC)[0]);
        }
        for (int indexOfDistanceInSet=0; indexOfDistanceInSet<setOfDistancesToCalculate.size(); indexOfDistanceInSet++)
        {
            //			nodesToCheckDijkstra.clear();
            //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
            //			for (int i=0;i<orderedCutoff.size();i++){
            //				orderedCutoff[i]->inDijkstra=false;
            //			}
            //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
            //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
            
            
            if (setOfDistancesToCalculate[indexOfDistanceInSet]!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
            {
                //                Node* startNode=(nodeInit);
                //			this->currentIndexDistance=indexDistance;
                //            int indexDistanceTemp=indexDistance;
                CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],1);
                nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,setOfDistancesToCalculate[indexOfDistanceInSet],1);
                //                    nodesToCheckDijkstra.changeGetValueFunction(<#bool (*compare)(Node *, Node *, int)#>, <#double (*getValue)(Node *, int)#>, <#int indexInArray#>, <#int modeOfObjectComparison#>)
                nodesToCheckDijkstra.push(startNode);
                startNode->inDijkstra=true;
                startNode->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
                calculateDijkstraOtherDistanceSpeed(startNode,true,nodesToCheckDijkstra,setOfDistancesToCalculate[indexOfDistanceInSet]);
                if (calculateGlobalProperties&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
                    //                    if(calculateGlobalProperties)
                {
                    measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                if (calculateCentralities&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
                    //                        if(calculateCentralities)
                {
                    makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                //                    else if (calculateCentralities&&calculateSpecialDistance){
                //                        for(long h=0; h<nodesCutoff.size(); h++)
                //                        {
                //                            nodesCutoff[h]->specialDistance=nodesCutoff[h]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]];
                //                        }
                //                    }
                //
                for(long i=0; i<nodesCutoff.size(); i++)
                {
                    //        if (nodes[i].minDistance>diamTemp){
                    //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                    //        }
                    if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                        nodesCutoff[i]->inCutoff=false;
                        
                        nodesCutoff[i]->inDijkstra=false;
                        nodesCutoff[i]->numChildren=0;
                        nodesCutoff[i]->numChildrenThatReachedMe=0;
                        nodesCutoff[i]->parent=NULL;
                        nodesCutoff[i]->minDistance=INFINITY;
                        nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                    }
                    if (calculateOtherDistances)
                    {
                        
                        for (int j=0; j<numberDistances; j++)
                        {
                            nodesCutoff[i]->numOtherChildren[j]=0;
                            nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                            nodesCutoff[i]->otherParents[j]=NULL;
                            nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                            nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
                        }
                    }
                    
                }
                if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                    nodesCutoff.clear();
                }
            }else if (setOfDistancesToCalculate[indexOfDistanceInSet]==this->indexOfMainDistanceInOtherDistances){
                for(long i=0;i<nodesCutoff.size();i++){
                    nodesCutoff[i]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->numChildren;
                    nodesCutoff[i]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->numChildrenThatReachedMe;
                    nodesCutoff[i]->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->parent;
                    nodesCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->minDistance;
                }
                if (calculateGlobalProperties&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
                    //                    if(calculateGlobalProperties)
                {
                    measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                if (calculateCentralities&&(setOfDistancesToCalculate[indexOfDistanceInSet]!=getIndexesOfDistanceType(METRIC)[0]||containsMetric))
                    //                    if(calculateCentralities)
                {
                    makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                //                    else if (calculateCentralities&&calculateSpecialDistance){
                //                        for(long h=0; h<nodesCutoff.size(); h++)
                //                        {
                //                            nodesCutoff[h]->specialDistance=nodesCutoff[h]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]];
                //                        }
                //                    }
                
                for(long i=0; i<nodesCutoff.size(); i++)
                {
                    //        if (nodes[i].minDistance>diamTemp){
                    //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                    //        }
                    if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                        nodesCutoff[i]->inCutoff=false;
                        
                        nodesCutoff[i]->inDijkstra=false;
                        nodesCutoff[i]->numChildren=0;
                        nodesCutoff[i]->numChildrenThatReachedMe=0;
                        nodesCutoff[i]->parent=NULL;
                        nodesCutoff[i]->minDistance=INFINITY;
                        nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                    }
                    if (calculateOtherDistances)
                    {
                        
                        for (int j=0; j<numberDistances; j++)
                        {
                            nodesCutoff[i]->numOtherChildren[j]=0;
                            nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                            nodesCutoff[i]->otherParents[j]=NULL;
                            nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                            nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
                        }
                    }
                    
                }
                if(indexOfDistanceInSet==setOfDistancesToCalculate.size()-1){
                    nodesCutoff.clear();
                }
            }
        }
        
        
    }
    
    nodesToCheckDijkstra.clear();
    
    
    
    nodesCutoff.clear();
    std::vector<Node*>().swap(nodesCutoff);
}










void Graph::calculateShortestPathsSpeedToSetOfDestinations(Node* &nodeInit,std::vector<Node*> setOfDestinations,double distanceLimit,std::vector<int> &setOfDistancesToCalculate)
{
    
    
    
    //    std::cout<<"calculating shortest paths"<<'\n';
    nodeInit->minDistance=0;
    Node* startNode=nodeInit;
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(startNode);
    startNode->inCutoff=true;
    nodesToCheckDijkstra.push(startNode);
    startNode->inDijkstra=true;
//    if(calculateMainDistance||distanceLimit!=0){
//        calculateMainDistance=true;
//        calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
//        
//    }else{
//        nodesCutoff.clear();
//        for(long i=0;i<nodes.size();i++){
//            nodes[i].inCutoff=true;
//            nodesCutoff.push_back(&nodes[i]);
//        }
//    }
    if (this->calculateOtherDistances)
    {
        if(setOfDistancesToCalculate.size()==0){
            for (int indexDistance=0; indexDistance<numberDistances; indexDistance++)
            {
                setOfDistancesToCalculate.push_back(indexDistance);
            }
            
        }
        for (int indexOfDistanceInSet=0; indexOfDistanceInSet<setOfDistancesToCalculate.size(); indexOfDistanceInSet++)
        {
            //			nodesToCheckDijkstra.clear();
            //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
            //			for (int i=0;i<orderedCutoff.size();i++){
            //				orderedCutoff[i]->inDijkstra=false;
            //			}
            //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
            //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
            
            
            if (setOfDistancesToCalculate[indexOfDistanceInSet]!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
            {
                //                Node* startNode=(nodeInit);
                //			this->currentIndexDistance=indexDistance;
                //            int indexDistanceTemp=indexDistance;
                CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],1);
                nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,setOfDistancesToCalculate[indexOfDistanceInSet],1);
                nodesToCheckDijkstra.push(startNode);
                startNode->inDijkstra=true;
                startNode->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
                calculateDijkstraSpeedOtherDistancesToSetOfNodes(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra,setOfDestinations,setOfDistancesToCalculate[indexOfDistanceInSet],false);
                if (calculateGlobalProperties)
                {
                    measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                if (calculateCentralities)
                {
                    makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                
                for(long i=0; i<nodesCutoff.size(); i++)
                {
                    //        if (nodes[i].minDistance>diamTemp){
                    //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                    //        }
                    nodesCutoff[i]->inCutoff=false;
                    nodesCutoff[i]->inDijkstra=false;
                    nodesCutoff[i]->numChildren=0;
                    nodesCutoff[i]->numChildrenThatReachedMe=0;
                    nodesCutoff[i]->parent=NULL;
                    nodesCutoff[i]->minDistance=INFINITY;
                    nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                    if (calculateOtherDistances)
                    {
                        
                        for (int j=0; j<numberDistances; j++)
                        {
                            nodesCutoff[i]->numOtherChildren[j]=0;
                            nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                            nodesCutoff[i]->otherParents[j]=NULL;
                            nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                            nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
                        }
                    }
                    
                }
                nodesCutoff.clear();
            }else if (setOfDistancesToCalculate[indexOfDistanceInSet]==this->indexOfMainDistanceInOtherDistances){
                for(long i=0;i<nodesCutoff.size();i++){
                    nodesCutoff[i]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->numChildren;
                    nodesCutoff[i]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->numChildrenThatReachedMe;
                    nodesCutoff[i]->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->parent;
                    nodesCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=nodesCutoff[i]->minDistance;
                }
                if (calculateGlobalProperties)
                {
                    measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                if (calculateCentralities)
                {
                    makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
                }
                
                for(long i=0; i<nodesCutoff.size(); i++)
                {
                    //        if (nodes[i].minDistance>diamTemp){
                    //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                    //        }
                    nodesCutoff[i]->inCutoff=false;
                    nodesCutoff[i]->inDijkstra=false;
                    nodesCutoff[i]->numChildren=0;
                    nodesCutoff[i]->numChildrenThatReachedMe=0;
                    nodesCutoff[i]->parent=NULL;
                    nodesCutoff[i]->minDistance=INFINITY;
                    nodesCutoff[i]->valueToPass= nodesCutoff[i]->originalValueToPass;
                    if (calculateOtherDistances)
                    {
                        
                        for (int j=0; j<numberDistances; j++)
                        {
                            nodesCutoff[i]->numOtherChildren[j]=0;
                            nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                            nodesCutoff[i]->otherParents[j]=NULL;
                            nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                            nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
                        }
                    }
                    
                }
                nodesCutoff.clear();
            }
        }
        
        
    }
    
    nodesToCheckDijkstra.clear();
    
    
    
    nodesCutoff.clear();
    std::vector<Node*>().swap(nodesCutoff);
    
    
    
    
    
    
    
    
    
    
    
    
    
//    //    std::cout<<"calculating shortest paths"<<'\n';
//    nodeInit->minDistance=0;
//    Node* startNode=nodeInit;
//    std::vector<Node*> nodesCutoff;
//    MinHeap<Node*> nodesToCheckDijkstra;
//    nodesCutoff.push_back(startNode);
//    startNode->inCutoff=true;
//    nodesToCheckDijkstra.push(startNode,&compareByDistance);
//    startNode->inDijkstra=true;
//    calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
//    if (this->calculateOtherDistances)
//    {
//        if(setOfDistancesToCalculate.size()==0){
//            for (int indexDistance=0; indexDistance<numberDistances; indexDistance++)
//            {
//                //			nodesToCheckDijkstra.clear();
//                //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
//                //			for (int i=0;i<orderedCutoff.size();i++){
//                //				orderedCutoff[i]->inDijkstra=false;
//                //			}
//                //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
//                //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
//                if (indexDistance!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
//                {
//                    //                Node* startNode=(nodeInit);
//                    //			this->currentIndexDistance=indexDistance;
//                    //            int indexDistanceTemp=indexDistance;
//                    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//                    nodesToCheckDijkstra.push(startNode,compare);
//                    calculateDijkstraSpeedOtherDistancesToSetOfNodes(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra,setOfDestinations,indexDistance);
//                }
//            }
//        }else{
//            for (int indexOfDistanceInSet=0; indexOfDistanceInSet<setOfDistancesToCalculate.size(); indexOfDistanceInSet++)
//            {
//                //			nodesToCheckDijkstra.clear();
//                //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
//                //			for (int i=0;i<orderedCutoff.size();i++){
//                //				orderedCutoff[i]->inDijkstra=false;
//                //			}
//                //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
//                //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
//                if (setOfDistancesToCalculate[indexOfDistanceInSet]!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
//                {
//                    //                Node* startNode=(nodeInit);
//                    //			this->currentIndexDistance=indexDistance;
//                    //            int indexDistanceTemp=indexDistance;
//                    CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],1);
//                    nodesToCheckDijkstra.push(startNode,compare);
//                    calculateDijkstraSpeedOtherDistancesToSetOfNodes(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra,setOfDestinations,setOfDistancesToCalculate[indexOfDistanceInSet]);
//                    //                    calculateDijkstraSpeedOtherDistancesToSetOfNodes(<#Node *&nodeInit#>, <#double distanceLimit#>, <#std::vector<Node *> &nodesCutoff#>, <#MinHeap<Node *> &nodesToCheckDijkstra#>, <#std::vector<Node *> setOfNodes#>, <#int indexDistance#>)
//                }
//            }
//        }
//        
//    }
//    if (calculateGlobalProperties)
//    {
//        measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate);
//    }
//    if (calculateCentralities)
//    {
//        makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate);
//    }
//    //std::cout<<nodesCutoff.size()<<'\n';
//    nodesToCheckDijkstra.remove();
//    //    for(long i=0;i<nodesCutoff.size();i++){
//    //        nodesCutoff[i]->inCutoff=false;
//    //        nodesCutoff[i]->inDijkstra=false;
//    //        nodesCutoff[i]->numChildren=0;
//    //        nodesCutoff[i]->numChildrenThatReachedMe=0;
//    //        nodesCutoff[i]->parent=NULL;
//    //        nodesCutoff[i]->minDistance=-INFINITY;
//    //        nodesCutoff[i]->valueToPass=1;
//    //        if (calculateOtherDistances){
//    //            for (int j=0;j<numberDistances;j++){
//    //                nodesCutoff[i]->numOtherChildren[j]=0;
//    //                nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
//    //                nodesCutoff[i]->otherParents[j]=NULL;
//    //                nodesCutoff[i]->minOtherDistances[j]=-1;
//    //                nodesCutoff[i]->valuesToPass[j]=1;
//    //            }
//    //        }
//    //
//    //    }
//    
//    for(long i=0; i<nodes.size(); i++)
//    {
//        //        if (nodes[i].minDistance>diamTemp){
//        //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
//        //        }
//        nodes[i].inCutoff=false;
//        nodes[i].inDijkstra=false;
//        nodes[i].numChildren=0;
//        nodes[i].numChildrenThatReachedMe=0;
//        nodes[i].parent=NULL;
//        nodes[i].minDistance=INFINITY;
//        nodes[i].valueToPass=1;
//        if (calculateOtherDistances)
//        {
//            
//            for (int j=0; j<numberDistances; j++)
//            {
//                nodes[i].numOtherChildren[j]=0;
//                nodes[i].numOtherChildrenThatReachedMe[j]=0;
//                nodes[i].otherParents[j]=NULL;
//                nodes[i].minOtherDistances[j]=INFINITY;
//                nodes[i].valuesToPass[j]=1;
//            }
//        }
//        
//    }
//    nodesCutoff.clear();
//    std::vector<Node*>().swap(nodesCutoff);
}
void Graph::calculateShortestPathsSpeedNoCutoff(Node* &nodeInit,std::vector<int> &setOfDistancesToCalculate)
{
    //    std::cout<<"calculating shortest paths"<<'\n';
    nodeInit->minDistance=0;
    Node* startNode=nodeInit;
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    //    for(long i=0; i<nodes.size(); i++)
    //    {
    //        nodesCutoff.push_back(&nodes[i]);
    //        nodes[i].inCutoff=true;
    //    }
    //    nodesCutoff.push_back(startNode);
    //    startNode->inCutoff=true;
    //    nodesToCheckDijkstra.push(startNode,&compareByDistance);
    //    startNode->inDijkstra=true;
    //    calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
    //    if (this->calculateOtherDistances)
    //    {
    
    //    std::cout<<"setOfDistancesToCalculate size "<<setOfDistancesToCalculate.size()<<'\n';
    for (int indexOfDistanceInSet=0; indexOfDistanceInSet<setOfDistancesToCalculate.size(); indexOfDistanceInSet++)
    {
        //			nodesToCheckDijkstra.clear();
        //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
        //			for (int i=0;i<orderedCutoff.size();i++){
        //				orderedCutoff[i]->inDijkstra=false;
        //			}
        //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
        //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
        //            if (setOfDistancesToCalculate[indexOfDistanceInSet]!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
        {
            //                Node* startNode=(nodeInit);
            //			this->currentIndexDistance=indexDistance;
            //            int indexDistanceTemp=indexDistance;
            CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],1);
            nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,setOfDistancesToCalculate[indexOfDistanceInSet],1);
            nodesToCheckDijkstra.push(startNode);
            startNode->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
            calculateDijkstraOtherDistanceSpeed(startNode,false,nodesToCheckDijkstra,setOfDistancesToCalculate[indexOfDistanceInSet]);
//            calculateDijkstraOtherDistanceSpeed
            for(long i=0; i<nodes.size(); i++){
                nodesCutoff.push_back(&nodes[i]);
            }
            if (calculateGlobalProperties)
            {
                measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
            }
            
            for(long i=0; i<nodes.size(); i++)
            {
                //        if (nodes[i].minDistance>diamTemp){
                //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                //        }
                nodes[i].inCutoff=false;
                nodes[i].inDijkstra=false;
                nodes[i].numChildren=0;
                nodes[i].numChildrenThatReachedMe=0;
                nodes[i].parent=NULL;
                nodes[i].minDistance=INFINITY;
                nodes[i].valueToPass=nodes[i].originalValueToPass;
                if (calculateOtherDistances)
                {
                    
                    for (int j=0; j<numberDistances; j++)
                    {
                        nodes[i].numOtherChildren[j]=0;
                        nodes[i].numOtherChildrenThatReachedMe[j]=0;
                        nodes[i].otherParents[j]=NULL;
                        nodes[i].minOtherDistances[j]=INFINITY;
                        nodes[i].valuesToPass[j]=nodes[i].originalValuesToPass[j];
                    }
                }
                
            }
        }
    }
    
    //    }
//    if (calculateGlobalProperties)
//    {
//        measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate);
//    }
    if (calculateCentralities)
    {
        makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate);
    }
    //std::cout<<nodesCutoff.size()<<'\n';
    nodesToCheckDijkstra.clear();
    //    for(long i=0;i<nodesCutoff.size();i++){
    //        nodesCutoff[i]->inCutoff=false;
    //        nodesCutoff[i]->inDijkstra=false;
    //        nodesCutoff[i]->numChildren=0;
    //        nodesCutoff[i]->numChildrenThatReachedMe=0;
    //        nodesCutoff[i]->parent=NULL;
    //        nodesCutoff[i]->minDistance=-INFINITY;
    //        nodesCutoff[i]->valueToPass=1;
    //        if (calculateOtherDistances){
    //            for (int j=0;j<numberDistances;j++){
    //                nodesCutoff[i]->numOtherChildren[j]=0;
    //                nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
    //                nodesCutoff[i]->otherParents[j]=NULL;
    //                nodesCutoff[i]->minOtherDistances[j]=-1;
    //                nodesCutoff[i]->valuesToPass[j]=1;
    //            }
    //        }
    //
    //    }
    for(long i=0; i<nodes.size(); i++)
    {
        //        if (nodes[i].minDistance>diamTemp){
        //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
        //        }
        nodes[i].inCutoff=false;
        nodes[i].inDijkstra=false;
        nodes[i].numChildren=0;
        nodes[i].numChildrenThatReachedMe=0;
        nodes[i].parent=NULL;
        nodes[i].minDistance=INFINITY;
        nodes[i].valueToPass=nodes[i].originalValueToPass;
        if (calculateOtherDistances)
        {
            
            for (int j=0; j<numberDistances; j++)
            {
                nodes[i].numOtherChildren[j]=0;
                nodes[i].numOtherChildrenThatReachedMe[j]=0;
                nodes[i].otherParents[j]=NULL;
                nodes[i].minOtherDistances[j]=INFINITY;
                nodes[i].valuesToPass[j]=nodes[i].originalValuesToPass[j];
            }
        }
        
    }
    nodesCutoff.clear();
    std::vector<Node*>().swap(nodesCutoff);
}
void Graph::calculateShortestPathsSpeedNoCutoffToSetOfDestinations(Node* &nodeInit,std::vector<Node*> setOfDestinations,std::vector<int> &setOfDistancesToCalculate)
{
    //    std::cout<<"calculating shortest paths"<<'\n';
    nodeInit->minDistance=0;
    Node* startNode=nodeInit;
    std::vector<Node*> nodesCutoff;
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    //    for(long i=0; i<nodes.size(); i++)
    //    {
    //        nodesCutoff.push_back(&nodes[i]);
    //        nodes[i].inCutoff=true;
    //    }
    //    nodesCutoff.push_back(startNode);
    //    startNode->inCutoff=true;
    //    nodesToCheckDijkstra.push(startNode,&compareByDistance);
    //    startNode->inDijkstra=true;
    //    calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
    //    if (this->calculateOtherDistances)
    //    {
    
    //    std::cout<<"setOfDistancesToCalculate size "<<setOfDistancesToCalculate.size()<<'\n';
    for (int indexOfDistanceInSet=0; indexOfDistanceInSet<setOfDistancesToCalculate.size(); indexOfDistanceInSet++)
    {
        //			nodesToCheckDijkstra.clear();
        //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
        //			for (int i=0;i<orderedCutoff.size();i++){
        //				orderedCutoff[i]->inDijkstra=false;
        //			}
        //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
        //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
        //            if (setOfDistancesToCalculate[indexOfDistanceInSet]!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance)
        {
            //                Node* startNode=(nodeInit);
            //			this->currentIndexDistance=indexDistance;
            //            int indexDistanceTemp=indexDistance;
            CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],1);
            nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,setOfDistancesToCalculate[indexOfDistanceInSet],1);
            nodesToCheckDijkstra.push(startNode);
            startNode->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
            //            calculateDijkstraOtherDistanceSpeed(startNode,false,nodesToCheckDijkstra,setOfDistancesToCalculate[indexOfDistanceInSet]);
            calculateDijkstraSpeedOtherDistancesToSetOfNodes(startNode,0,nodesCutoff,nodesToCheckDijkstra,setOfDestinations,setOfDistancesToCalculate[indexOfDistanceInSet],false);
            
            if (calculateGlobalProperties)
            {
//                std::cout<<"idStartNode "<<startNode->id<<'\n';
                measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate,indexOfDistanceInSet);
            }
            
            for(long i=0; i<nodes.size(); i++)
            {
                //        if (nodes[i].minDistance>diamTemp){
                //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
                //        }
                nodes[i].inCutoff=false;
                nodes[i].inDijkstra=false;
                nodes[i].numChildren=0;
                nodes[i].numChildrenThatReachedMe=0;
                nodes[i].parent=NULL;
                nodes[i].minDistance=INFINITY;
                nodes[i].valueToPass=nodes[i].originalValueToPass;
                if (calculateOtherDistances)
                {
                    
                    for (int j=0; j<numberDistances; j++)
                    {
                        nodes[i].numOtherChildren[j]=0;
                        nodes[i].numOtherChildrenThatReachedMe[j]=0;
                        nodes[i].otherParents[j]=NULL;
                        nodes[i].minOtherDistances[j]=INFINITY;
                        nodes[i].valuesToPass[j]=nodes[i].originalValuesToPass[j];
                    }
                }
                
            }
//            nodesCutoff.clear();
//            std::vector<Node*>().swap(nodesCutoff);
        }
    }
    
    //    }
//    if (calculateGlobalProperties)
//    {
//        measureGlobalProperties(nodesCutoff,setOfDistancesToCalculate);
//    }
    if (calculateCentralities)
    {
        makeCalculationsSpeed(startNode,nodesCutoff,setOfDistancesToCalculate);
    }
    //std::cout<<nodesCutoff.size()<<'\n';
    nodesToCheckDijkstra.clear();
    //    for(long i=0;i<nodesCutoff.size();i++){
    //        nodesCutoff[i]->inCutoff=false;
    //        nodesCutoff[i]->inDijkstra=false;
    //        nodesCutoff[i]->numChildren=0;
    //        nodesCutoff[i]->numChildrenThatReachedMe=0;
    //        nodesCutoff[i]->parent=NULL;
    //        nodesCutoff[i]->minDistance=-INFINITY;
    //        nodesCutoff[i]->valueToPass=1;
    //        if (calculateOtherDistances){
    //            for (int j=0;j<numberDistances;j++){
    //                nodesCutoff[i]->numOtherChildren[j]=0;
    //                nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
    //                nodesCutoff[i]->otherParents[j]=NULL;
    //                nodesCutoff[i]->minOtherDistances[j]=-1;
    //                nodesCutoff[i]->valuesToPass[j]=1;
    //            }
    //        }
    //
    //    }
    
    for(long i=0; i<nodes.size(); i++)
    {
        //        if (nodes[i].minDistance>diamTemp){
        //            std::cout<<i<<" \""<<nodeInit->originalID<<"\" \""<<nodes[i].originalID<<"\" "<<nodes[i].minDistance<<'\n';
        //        }
        nodes[i].inCutoff=false;
        nodes[i].inDijkstra=false;
        nodes[i].numChildren=0;
        nodes[i].numChildrenThatReachedMe=0;
        nodes[i].parent=NULL;
        nodes[i].minDistance=INFINITY;
        nodes[i].valueToPass=nodes[i].originalValueToPass;
        if (calculateOtherDistances)
        {
            
            for (int j=0; j<numberDistances; j++)
            {
                nodes[i].numOtherChildren[j]=0;
                nodes[i].numOtherChildrenThatReachedMe[j]=0;
                nodes[i].otherParents[j]=NULL;
                nodes[i].minOtherDistances[j]=INFINITY;
                nodes[i].valuesToPass[j]=nodes[i].originalValuesToPass[j];
            }
        }
        
    }
    nodesCutoff.clear();
    std::vector<Node*>().swap(nodesCutoff);
}
void Graph::getRTreeInducedSubgraphAndReturnFrontierTransitions(Graph* subgraph,std::vector<Node*> &listNodes,std::vector<Transition> &frontierTransitions)
{
    subgraph->numberDistances=numberDistances;
    BST<Node*> nodesById;
    
    for(long i=0; i<listNodes.size(); i++)
    {
        
        subgraph->addNode();
        //        std::vector<Node>* nodesTemp=&(subgraph->nodes);
        //        nodesById.add(listNodes[i]->id,&((subgraph->nodes)[i]));
        //
        //        subgraph->nodes[i].nodeThatRepresents=listNodes[i];
        //        listNodes[i]->nodeThatRepresents=&(subgraph->nodes[i]);
    }
    subgraph->resizeInitialParametersToNumDistances();
    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    for(long i=0; i<listNodes.size(); i++)
    {
        
        //        subgraph->addNode();
        //        std::vector<Node>* nodesTemp=&(subgraph->nodes);
        nodesById.add(listNodes[i]->originalID,&((subgraph->nodes)[i]));
        //        Node** pointerToFirst=listNodes.data();
        subgraph->nodes[i].nodeThatRepresents=&(*listNodes[i]);
        subgraph->nodes[i].location=listNodes[i]->location;
        subgraph->nodes[i].idEquivalentLowerVerticalNode=listNodes[i]->idEquivalentLowerVerticalNode;
        subgraph->nodes[i].idEquivalentUpperVerticalNode=listNodes[i]->idEquivalentUpperVerticalNode;
        subgraph->nodes[i].depthInRTree=listNodes[i]->depthInRTree;
        subgraph->nodes[i].originalID=listNodes[i]->originalID;
        subgraph->nodes[i].nodeInOriginalGraph=listNodes[i]->nodeInOriginalGraph;
        (*listNodes[i]).nodeRepresentedBy=&((subgraph->nodes[i]));
    }
    for(long i=0; i<listNodes.size(); i++)
    {
        Node a=(subgraph->nodes[i]);
        for(long j=0; j<listNodes[i]->transitions.size(); j++)
        {
            
            Node* nodeTemp;
            if (listNodes[i]->transitions[j]->b!=NULL)
            {
                nodeTemp=(nodesById.get(listNodes[i]->transitions[j]->b->originalID));
            }
            else
            {
                nodeTemp=(nodesById.get(listNodes[i]->transitions[j]->idB));
            }
            if(nodeTemp!=NULL)
            {
                //                Node b=(subgraph->nodes)[nodeTemp->id];
                //                Transition transition;
                //                transition.setTransition(&(subgraph->nodes[i]),&(subgraph->nodes[nodeTemp->id]),listNodes[i]->transitions[j].weight,listNodes[i]->transitions[j].otherWeights);
                //                subgraph->nodes[i].transitions.push_back(transition);
                //                if (subgraph->nodes[i].transitions.size()>2){
                ////                    subgraph->nodes[i].valueToPass=1;
                ////                    subgraph->nodes[i].valuesToPass.resize(numberDistances,1);
                //
                //                }
                Transition trans;
                trans.a=listNodes[i]->transitions[j]->a->nodeRepresentedBy;
                trans.b=listNodes[i]->transitions[j]->b->nodeRepresentedBy;
                trans.weight=listNodes[i]->transitions[j]->weight;
                trans.otherWeights=listNodes[i]->transitions[j]->otherWeights;
                subgraph->addTransition(trans);
                
            }
            else
            {
                //                Transition trans;
                //                trans.a=listNodes[i]->transitions[j].a;
                //                trans.b=listNodes[i]->transitions[j].b;
                //                trans.weight=listNodes[i]->transitions[j].weight;
                //                trans.otherWeights=listNodes[i]->transitions[j].otherWeights;
                //                frontierTransitions.push_back(trans);
                frontierTransitions.push_back(*(listNodes[i]->transitions[j]));
                
            }
            
        }
    }
    
    
}

void Graph::getInducedSubgraph(Graph* subgraph,std::vector<Node*> &listNodes)
{
    
    std::unordered_map<signed long long,int> nodesById;
    subgraph->numberDistances=numberDistances;
    subgraph->pseudoGraph=pseudoGraph;
    subgraph->bidirectional=bidirectional;
    //    subgraph->indexOfMainDistanceInOtherDistances=indexOfMainDistanceInOtherDistances;
    //    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    
    for(long i=0; i<listNodes.size(); i++)
    {
//        std::cout<<"graph->getInducedSubgraph "<<listNodes[i]->originalID<<'\n';
        if(nodesById[listNodes[i]->originalID]!=2){
            nodesById[listNodes[i]->originalID]=2;
            subgraph->addNode();
        }else{
            listNodes.erase(listNodes.begin()+i);
            i--;
        }
        //        std::vector<Node>* nodesTemp=&(subgraph->nodes);
        //        nodesById.add(listNodes[i]->id,&((subgraph->nodes)[i]));
        //
        //        subgraph->nodes[i].nodeThatRepresents=listNodes[i];
        //        listNodes[i]->nodeThatRepresents=&(subgraph->nodes[i]);
    }
    subgraph->resizeInitialParametersToNumDistances();
    subgraph->indexOfMainDistanceInOtherDistances=indexOfMainDistanceInOtherDistances;
    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    for(long i=0; i<listNodes.size(); i++)
    {
        
        //        subgraph->addNode();
        //        std::vector<Node>* nodesTemp=&(subgraph->nodes);
        subgraph->nodes[i].mass=listNodes[i]->mass;
        subgraph->nodes[i].location=listNodes[i]->location;
        subgraph->nodes[i].nameRoad=listNodes[i]->nameRoad;
        subgraph->nodes[i].levelHierarchyRoad=listNodes[i]->levelHierarchyRoad;
        subgraph->nodes[i].originalID=listNodes[i]->originalID;
        subgraph->nodes[i].nodeInOriginalGraph=listNodes[i]->nodeInOriginalGraph;
        //        subgraph->nodes[i].nodeThatRepresents=&(*listNodes[i]);
        listNodes[i]->nodeRepresentedBy=&((subgraph->nodes[i]));
        subgraph->nodes[i].nodeThatRepresents=listNodes[i];
        subgraph->nodes[i].numberDistances=listNodes[i]->numberDistances;
        //        listNodes[i]->nodeThatRepresents=&(subgraph->nodes[i]);
        subgraph->nodes[i].transitionThatRepresents=listNodes[i]->transitionThatRepresents;
    }
    for(long i=0; i<listNodes.size(); i++)
    {
        //        Node a=(subgraph->nodes[i]);
        for(long j=0; j<listNodes[i]->transitions.size(); j++)
        {
            
            
            
//            Node* nodeTemp=(nodesById.get(listNodes[i]->transitions[j].b->originalID));
            if(nodesById[listNodes[i]->transitions[j]->b->originalID]==2)
            {
//                Node b=(subgraph->nodes)[nodeTemp->id];
                Transition transition;
                //                transition.setTransition(&(subgraph->nodes[i]),&(subgraph->nodes[nodeTemp->id]),listNodes[i]->transitions[j].weight,listNodes[i]->transitions[j].otherWeights);
                transition.a=listNodes[i]->nodeRepresentedBy;
                transition.transitionThatRepresents=listNodes[i]->transitions[j];
                transition.b=listNodes[i]->transitions[j]->b->nodeRepresentedBy;
                transition.weight=listNodes[i]->transitions[j]->weight;
                transition.nameRoad=listNodes[i]->transitions[j]->nameRoad;
                transition.levelHierarchyRoad=listNodes[i]->transitions[j]->levelHierarchyRoad;
                transition.otherWeights=listNodes[i]->transitions[j]->otherWeights;
                transition.originalID=listNodes[i]->transitions[j]->originalID;
                subgraph->addTransition(transition);
                //                transition.a->transitions.push_back(transition);
//                if (subgraph->nodes[i].transitions.size()>2)
//                {
//                    subgraph->nodes[i].valueToPass=1;
//                    subgraph->nodes[i].valuesToPass.resize(numberDistances,1);
//                }
                
            }
            else
            {
//                std::cout<<"transition falls out of set"<<'\n';
                
                //                std::vector<Node*> nodesTemp=nodesById.getAll();
                //                std::vector<long> ids;
                //                for(int h=0;h<listNodes.size();h++){
                //                    ids.push_back(listNodes[h]->id);
                //                }
                //                long idTemp=listNodes[i]->transitions[j].b->id;
                //                std::cout<<listNodes[i]->transitions[j].b->id<<'\n';
            }
            
        }
    }
    for(long i=0;i<subgraph->transitions.size();i++){
        subgraph->transitions[i].transitionThatRepresents->transitionRepresentedBy=&subgraph->transitions[i];
    }
    
    //    if (listNodes.size()>1){
    ////        std::cout<<"hello 1 "<<'\n';
    //        for(long h=0;h<subgraph->nodes.size();h++){
    ////            std::cout<<"hello 2 "<<i<<'\n';
    //            if ((subgraph->nodes[h].transitions.size())==0){
    //                std::cout<<"ERROR"<<'\n';
    //            }
    //        }
    //    }
    
    //    return subgraph;
}

void Graph::getInducedSubgraphIncludingExternalTransitions(Graph* subgraph,std::vector<Node*> &listNodesOriginal)
{
    std::vector<Node*> listNodes;
    for(long i=0;i<listNodesOriginal.size();i++){
        listNodes.push_back(listNodesOriginal[i]);
    }
    std::unordered_map<signed long long,int> nodesById;
    subgraph->numberDistances=numberDistances;
    subgraph->pseudoGraph=pseudoGraph;
    subgraph->bidirectional=bidirectional;
    //    subgraph->indexOfMainDistanceInOtherDistances=indexOfMainDistanceInOtherDistances;
    //    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    
    for(long i=0; i<listNodes.size(); i++)
    {
        //        std::cout<<"graph->getInducedSubgraph "<<listNodes[i]->originalID<<'\n';
        if(nodesById[listNodes[i]->originalID]!=2){
            nodesById[listNodes[i]->originalID]=2;
            subgraph->addNode();
        }else{
            listNodes.erase(listNodes.begin()+i);
            i--;
        }
        //        std::vector<Node>* nodesTemp=&(subgraph->nodes);
        //        nodesById.add(listNodes[i]->id,&((subgraph->nodes)[i]));
        //
        //        subgraph->nodes[i].nodeThatRepresents=listNodes[i];
        //        listNodes[i]->nodeThatRepresents=&(subgraph->nodes[i]);
    }
    for(long i=0; i<listNodes.size(); i++)
    {
        for(long j=0;j<listNodes[i]->transitions.size();j++){
            if(nodesById[listNodes[i]->transitions[j]->b->originalID]!=2&&nodesById[listNodes[i]->transitions[j]->b->originalID]!=1&&nodesById[listNodes[i]->transitions[j]->a->originalID]==2){
                nodesById[listNodes[i]->transitions[j]->b->originalID]=1;
                listNodes.push_back(listNodes[i]->transitions[j]->b);
                subgraph->addNode();
            }
        }
    }
    subgraph->resizeInitialParametersToNumDistances();
    subgraph->indexOfMainDistanceInOtherDistances=indexOfMainDistanceInOtherDistances;
    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    for(long i=0; i<listNodes.size(); i++)
    {
        
        //        subgraph->addNode();
        //        std::vector<Node>* nodesTemp=&(subgraph->nodes);
        subgraph->nodes[i].mass=listNodes[i]->mass;
        subgraph->nodes[i].location=listNodes[i]->location;
        subgraph->nodes[i].nameRoad=listNodes[i]->nameRoad;
        subgraph->nodes[i].levelHierarchyRoad=listNodes[i]->levelHierarchyRoad;
        subgraph->nodes[i].originalID=listNodes[i]->originalID;
        subgraph->nodes[i].nodeInOriginalGraph=listNodes[i]->nodeInOriginalGraph;
        //        subgraph->nodes[i].nodeThatRepresents=&(*listNodes[i]);
        listNodes[i]->nodeRepresentedBy=&((subgraph->nodes[i]));
        subgraph->nodes[i].nodeThatRepresents=listNodes[i];
        subgraph->nodes[i].numberDistances=listNodes[i]->numberDistances;
        //        listNodes[i]->nodeThatRepresents=&(subgraph->nodes[i]);
        subgraph->nodes[i].transitionThatRepresents=listNodes[i]->transitionThatRepresents;
    }
    for(long i=0; i<listNodes.size(); i++)
    {
        //        Node a=(subgraph->nodes[i]);
        for(long j=0; j<listNodes[i]->transitions.size(); j++)
        {
            
            
            
            //            Node* nodeTemp=(nodesById.get(listNodes[i]->transitions[j].b->originalID));
            if(nodesById[listNodes[i]->transitions[j]->b->originalID]==2||(nodesById[listNodes[i]->transitions[j]->b->originalID]==1&&nodesById[listNodes[i]->transitions[j]->a->originalID]==2)||(nodesById[listNodes[i]->transitions[j]->a->originalID]==1&&nodesById[listNodes[i]->transitions[j]->b->originalID]==2))
            {
                //                Node b=(subgraph->nodes)[nodeTemp->id];
                Transition transition;
                //                transition.setTransition(&(subgraph->nodes[i]),&(subgraph->nodes[nodeTemp->id]),listNodes[i]->transitions[j].weight,listNodes[i]->transitions[j].otherWeights);
                transition.a=listNodes[i]->nodeRepresentedBy;
                /////TRANSITION THAT REPRESENTS!!!!!!!
                transition.transitionThatRepresents=listNodes[i]->transitions[j];
//                listNodes[i]->transitions[j]->transitionRepresentedBy=
                transition.b=listNodes[i]->transitions[j]->b->nodeRepresentedBy;
                transition.weight=listNodes[i]->transitions[j]->weight;
                transition.nameRoad=listNodes[i]->transitions[j]->nameRoad;
                transition.levelHierarchyRoad=listNodes[i]->transitions[j]->levelHierarchyRoad;
                transition.otherWeights=listNodes[i]->transitions[j]->otherWeights;
                transition.originalID=listNodes[i]->transitions[j]->originalID;
                subgraph->addTransition(transition);
                //                transition.a->transitions.push_back(transition);
                //                if (subgraph->nodes[i].transitions.size()>2)
                //                {
                //                    subgraph->nodes[i].valueToPass=1;
                //                    subgraph->nodes[i].valuesToPass.resize(numberDistances,1);
                //                }
                
            }
//            else
//            {
                //                std::cout<<"transition falls out of set"<<'\n';
                
                //                std::vector<Node*> nodesTemp=nodesById.getAll();
                //                std::vector<long> ids;
                //                for(int h=0;h<listNodes.size();h++){
                //                    ids.push_back(listNodes[h]->id);
                //                }
                //                long idTemp=listNodes[i]->transitions[j].b->id;
                //                std::cout<<listNodes[i]->transitions[j].b->id<<'\n';
//            }
            
        }
    }
    for(long i=0;i<subgraph->transitions.size();i++){
        subgraph->transitions[i].transitionThatRepresents->transitionRepresentedBy=&subgraph->transitions[i];
    }
    
    //    if (listNodes.size()>1){
    ////        std::cout<<"hello 1 "<<'\n';
    //        for(long h=0;h<subgraph->nodes.size();h++){
    ////            std::cout<<"hello 2 "<<i<<'\n';
    //            if ((subgraph->nodes[h].transitions.size())==0){
    //                std::cout<<"ERROR"<<'\n';
    //            }
    //        }
    //    }
    
    //    return subgraph;
}
void Graph::getInducedSubgraph(Graph* subgraph,std::vector<Transition*> &transitions)
{
    subgraph->numberDistances=numberDistances;
    subgraph->pseudoGraph=pseudoGraph;
    
    std::vector<Node*> listNodes;
    for(long i=0; i<transitions.size(); i++)
    {
        if(!transitions[i]->a->inSubgraph)
        {
            subgraph->addNode();
            listNodes.push_back(transitions[i]->a);
            transitions[i]->a->inSubgraph=true;
        }
        if(!transitions[i]->b->inSubgraph)
        {
            subgraph->addNode();
            listNodes.push_back(transitions[i]->b);
            transitions[i]->b->inSubgraph=true;
        }
    }
    subgraph->resizeInitialParametersToNumDistances();
    subgraph->indexOfMainDistanceInOtherDistances=indexOfMainDistanceInOtherDistances;
    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    //    subgraph->indexOfDistancesByDistanceType=indexOfDistancesByDistanceType;
    for(long i=0; i<listNodes.size(); i++)
    {
        subgraph->nodes[i].mass=listNodes[i]->mass;
        listNodes[i]->nodeRepresentedBy=&(subgraph->nodes[i]);
        subgraph->nodes[i].nodeThatRepresents=listNodes[i];
        subgraph->nodes[i].originalID=listNodes[i]->originalID;
        subgraph->nodes[i].nameRoad=listNodes[i]->nameRoad;
        subgraph->nodes[i].levelHierarchyRoad=listNodes[i]->levelHierarchyRoad;
        subgraph->nodes[i].nodeInOriginalGraph=listNodes[i];
        subgraph->nodes[i].location=listNodes[i]->location;
                subgraph->nodes[i].transitionThatRepresents=listNodes[i]->transitionThatRepresents;
        if(listNodes[i]->nodeInOriginalGraph==NULL)
        {
            listNodes[i]->nodeInOriginalGraph=listNodes[i];
        }
        else
        {
            listNodes[i]->nodeInOriginalGraph=listNodes[i]->nodeInOriginalGraph;
        }
        
    }
    for(long i=0; i<transitions.size(); i++)
    {
        Transition trans;
        trans.a=transitions[i]->a->nodeRepresentedBy;
        trans.b=transitions[i]->b->nodeRepresentedBy;
        trans.transitionThatRepresents=transitions[i];
        
//        cout<<trans.a<<" "<<&subgraph->nodes[trans.a->id]<<'\n';
        //        std::cout<<"node Temp id "<<trans.a->id<<'\n';
        //        std::cout<<"node Temp id "<<trans.b->id<<'\n';
        trans.weight=transitions[i]->weight;
        trans.otherWeights=transitions[i]->otherWeights;
        trans.nameRoad=transitions[i]->nameRoad;
        trans.levelHierarchyRoad=transitions[i]->levelHierarchyRoad;
        trans.originalID=transitions[i]->originalID;
        subgraph->addTransition(trans);
        transitions[i]->a->inSubgraph=false;
        transitions[i]->b->inSubgraph=false;
        
    }
    for(long i=0;i<subgraph->transitions.size();i++){
        subgraph->transitions[i].transitionThatRepresents->transitionRepresentedBy=&subgraph->transitions[i];
    }
//    for(long i=0; i<listNodes.size(); i++)
//    {
//        listNodes[i]->inSubgraph=false;
//    }
    
}

void Graph::calculateCutoffSpeed(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff)
{
    //    std::cout<<"calculating shortest paths"<<'\n';
    
    Node* startNode=nodeInit;
    
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(startNode);
    startNode->inCutoff=true;
    nodesToCheckDijkstra.push(startNode);
    startNode->inDijkstra=true;
    startNode->minDistance=0;
    calculateOtherDistances=false;
    calculateMainDistance=true;
    calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
    //    if (this->calculateOtherDistances){
    //		for (int indexDistance=0; indexDistance<numberDistances; indexDistance++) {
    //            //			nodesToCheckDijkstra.clear();
    //            //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
    //            //			for (int i=0;i<orderedCutoff.size();i++){
    //            //				orderedCutoff[i]->inDijkstra=false;
    //            //			}
    //            //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
    //            //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
    //            if (indexDistance!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance){
    //                Node* startNode=(nodeInit);
    //                //			this->currentIndexDistance=indexDistance;
    //                //            int indexDistanceTemp=indexDistance;
    //                CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
    //                nodesToCheckDijkstra.push(startNode,compare);
    //                calculateDijkstraOtherDistanceSpeed(nodeInit,nodesCutoff,nodesToCheckDijkstra,indexDistance);
    //            }
    //		}
    //
    //    }
    
    
    //    makeCalculationsSpeed(nodeInit,nodesCutoff);
    //std::cout<<nodesCutoff.size()<<'\n';
    nodesToCheckDijkstra.clear();
    //    return nodesCutoff;
    for(long i=0; i<nodesCutoff.size(); i++)
    {
        nodesCutoff[i]->inCutoff=false;
        nodesCutoff[i]->inDijkstra=false;
        nodesCutoff[i]->numChildren=0;
        nodesCutoff[i]->numChildrenThatReachedMe=0;
        nodesCutoff[i]->parent=NULL;
        nodesCutoff[i]->minDistance=INFINITY;
        nodesCutoff[i]->valueToPass=nodesCutoff[i]->originalValueToPass;
        if (calculateOtherDistances)
        {
            for (int j=0; j<numberDistances; j++)
            {
                nodesCutoff[i]->numOtherChildren[j]=0;
                nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                nodesCutoff[i]->otherParents[j]=NULL;
                nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                nodesCutoff[i]->valuesToPass[j]=nodesCutoff[i]->originalValuesToPass[j];
            }
        }
        
    }
    
}

std::vector<double> Graph::calculateDistancesFrom(Node* startNode){
    std::vector<Node*> nodesCutoff;
//    Node* startNode=nodeInit;
    
    std::vector<double> distances;
    
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(startNode);
    startNode->inCutoff=true;
    nodesToCheckDijkstra.push(startNode);
    startNode->inDijkstra=true;
    startNode->minDistance=0;
    calculateOtherDistances=false;
    calculateDijkstraSpeed(startNode,0,nodesCutoff,nodesToCheckDijkstra);
    //    if (this->calculateOtherDistances){
    //		for (int indexDistance=0; indexDistance<numberDistances; indexDistance++) {
    //            //			nodesToCheckDijkstra.clear();
    //            //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
    //            //			for (int i=0;i<orderedCutoff.size();i++){
    //            //				orderedCutoff[i]->inDijkstra=false;
    //            //			}
    //            //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
    //            //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
    //            if (indexDistance!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance){
    //                Node* startNode=(nodeInit);
    //                //			this->currentIndexDistance=indexDistance;
    //                //            int indexDistanceTemp=indexDistance;
    //                CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
    //                nodesToCheckDijkstra.push(startNode,compare);
    //                calculateDijkstraOtherDistanceSpeed(nodeInit,nodesCutoff,nodesToCheckDijkstra,indexDistance);
    //            }
    //		}
    //
    //    }
    
    
    //    makeCalculationsSpeed(nodeInit,nodesCutoff);
    //std::cout<<nodesCutoff.size()<<'\n';
    nodesToCheckDijkstra.clear();
    //    return nodesCutoff;
    for(long i=0; i<nodes.size(); i++)
    {
        
        distances.push_back(nodes[i].minDistance);
        nodes[i].inCutoff=false;
        nodes[i].inDijkstra=false;
        nodes[i].numChildren=0;
        nodes[i].numChildrenThatReachedMe=0;
        nodes[i].parent=NULL;
        nodes[i].minDistance=INFINITY;
        nodes[i].valueToPass=nodes[i].originalValueToPass;
        if (calculateOtherDistances)
        {
            for (int j=0; j<numberDistances; j++)
            {
                nodes[i].numOtherChildren[j]=0;
                nodes[i].numOtherChildrenThatReachedMe[j]=0;
                nodes[i].otherParents[j]=NULL;
                nodes[i].minOtherDistances[j]=INFINITY;
                nodes[i].valuesToPass[j]=nodes[i].originalValuesToPass[j];
            }
        }
        
    }
    return distances;
}

std::vector<double> Graph::calculateDistancesFrom(Node* startNode,double distanceLimit){
    std::vector<Node*> nodesCutoff;
//    Node* startNode=nodeInit;
    
    std::vector<double> distances;
    
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(startNode);
    startNode->inCutoff=true;
    nodesToCheckDijkstra.push(startNode);
    startNode->inDijkstra=true;
    startNode->minDistance=0;
    calculateOtherDistances=false;
    calculateMainDistance=true;
    calculateDijkstraSpeed(startNode,distanceLimit,nodesCutoff,nodesToCheckDijkstra);
    //    if (this->calculateOtherDistances){
    //		for (int indexDistance=0; indexDistance<numberDistances; indexDistance++) {
    //            //			nodesToCheckDijkstra.clear();
    //            //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
    //            //			for (int i=0;i<orderedCutoff.size();i++){
    //            //				orderedCutoff[i]->inDijkstra=false;
    //            //			}
    //            //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
    //            //std::cout<<this->indexOfMainDistanceInOtherDistances<<'\n';
    //            if (indexDistance!=this->indexOfMainDistanceInOtherDistances||!this->calculateMainDistance){
    //                Node* startNode=(nodeInit);
    //                //			this->currentIndexDistance=indexDistance;
    //                //            int indexDistanceTemp=indexDistance;
    //                CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
    //                nodesToCheckDijkstra.push(startNode,compare);
    //                calculateDijkstraOtherDistanceSpeed(nodeInit,nodesCutoff,nodesToCheckDijkstra,indexDistance);
    //            }
    //		}
    //
    //    }
    
    
    //    makeCalculationsSpeed(nodeInit,nodesCutoff);
    //std::cout<<nodesCutoff.size()<<'\n';
    nodesToCheckDijkstra.clear();
    //    return nodesCutoff;
    for(long i=0; i<nodes.size(); i++)
    {
        
        distances.push_back(nodes[i].minDistance);
        nodes[i].inCutoff=false;
        nodes[i].inDijkstra=false;
        nodes[i].numChildren=0;
        nodes[i].numChildrenThatReachedMe=0;
        nodes[i].parent=NULL;
        nodes[i].minDistance=INFINITY;
        nodes[i].valueToPass=nodes[i].originalValueToPass;
        if (calculateOtherDistances)
        {
            for (int j=0; j<numberDistances; j++)
            {
                nodes[i].numOtherChildren[j]=0;
                nodes[i].numOtherChildrenThatReachedMe[j]=0;
                nodes[i].otherParents[j]=NULL;
                nodes[i].minOtherDistances[j]=INFINITY;
                nodes[i].valuesToPass[j]=nodes[i].originalValuesToPass[j];
            }
        }
        
    }
    return distances;
}


void Graph::generateFuzzyNetworkPercolation(double multiplier,double exponent,std::vector<Graph> &clusters)
{
    
    //from primal graph
    static const int STATIC=0;
    static const int ADAPTATIVE=1;
    int mode=STATIC;
    MinHeap<Transition*> transitionsToGetMinWeight;
    
    for(long i=0; i<nodes.size(); i++)
    {
        for(long j=0; j<nodes[i].transitions.size(); j++)
        {
            Transition* trans=(nodes[i].transitions[j]);
            transitionsToGetMinWeight.push(trans, &compareByWeight);
        }
    }
    
    
    long numClusters=0;
    
    
    while(transitionsToGetMinWeight.size()>0)
    {
        
        
        Transition* minTrans=transitionsToGetMinWeight.pop(&compareByWeight);
        if(!minTrans->usedInNetworkPercolation)
        {
            std::vector<Transition*> transitionsInCluster;
            std::vector<long> idsNodesToContinueCluster;
            std::vector<Node*> cluster;
            
            long idNode=minTrans->a->id;
            idsNodesToContinueCluster.push_back(idNode);
            
            double referenceDistance;
            referenceDistance=minTrans->weight;
            
            while(idsNodesToContinueCluster.size()>0)
            {
                idNode=idsNodesToContinueCluster[idsNodesToContinueCluster.size()-1];
                idsNodesToContinueCluster.pop_back();
                if(!nodes[idNode].inCluster)
                {
                    cluster.push_back(&nodes[idNode]);
                    //                    minTrans->a->inCluster=true;
                    nodes[idNode].inCluster=true;
                }
                
                if(nodes[idNode].transitions.size()>0)
                {
                    
                    
                    for(long i=0; i<nodes[idNode].transitions.size(); i++)
                    {
                        
                        Transition* trans=(nodes[idNode].transitions[i]);
                        
                        if(trans->a!=trans->b&&!trans->usedInNetworkPercolation&&(trans->weight)<=multiplier*pow(referenceDistance,(exponent)))
                        {
                            if(!trans->b->inCluster)
                            {
                                cluster.push_back(trans->b);
                                idsNodesToContinueCluster.push_back(trans->b->id);
                                trans->b->inCluster=true;
                                
                            }
                            trans->b->inCluster=true;
                            trans->usedInNetworkPercolation=true;
                            transitionsInCluster.push_back((nodes[idNode].transitions[i]));
                            trans->getSimetricTransition()->usedInNetworkPercolation=true;
                            
                            
                            
                            if(mode==ADAPTATIVE)
                            {
                                //                                        referenceDistance=nodes[idNode].transitions[i].weight;
                            }
                        }
                        
                    }
                }
                
            }
            if(cluster.size()>2)
            {
                
            }
            if(transitionsInCluster.size()>0)
            {
                numClusters++;
                
                if(numClusters==128)
                {
                    std::cout<<"hello???"<<'\n';
                }
                
                
                
                
//                ArchivoTexto textFile;
                std::stringstream nameSS1;
                nameSS1<<"/Users/carlos/Documents/results/clustersFromFuzzyPercolation/"<<"dynamicNetworkPercolation_UK_3_25_x25_clusters"<<".txt";
                
                std::string name1=nameSS1.str();
                std::vector<std::string> values;
                double TSL=0;
                Graph subGraph;
                std::stringstream valuesSS1;
                valuesSS1<<"numCluster"<<","<<"referenceDistance"<<","<<"idA"<<","<<"idB"<<","<<"weight"<<","<<"xA"<<","<<"yA"<<","<<"xB"<<","<<"yB";
                std::string valuesS1=valuesSS1.str();
                //values.push_back(valuesS1);
                for(long i=0; i<transitionsInCluster.size(); i++)
                {
                    //                    cluster.push_back(&nodes[idNode]);
                    TSL+=transitionsInCluster[i]->weight;
                    std::stringstream valuesSS;
                    //                    valuesSS<<numClusters<<" "<<transitionsInCluster[i]->a->id<<" "<<transitionsInCluster[i]->b->id<<" "<<transitionsInCluster[i]->weight<<" "<<std::to_string(transitionsInCluster[i]->a->location.x)<<" "<<std::to_string(transitionsInCluster[i]->a->location.y)<<" "<<std::to_string(transitionsInCluster
                    valuesSS<<numClusters<<","<<referenceDistance<<","<<transitionsInCluster[i]->a->id<<","<<transitionsInCluster[i]->b->id<<","<<transitionsInCluster[i]->weight<<","<<std::to_string(transitionsInCluster[i]->a->location.x)<<","<<std::to_string(transitionsInCluster[i]->a->location.y)<<","<<std::to_string(transitionsInCluster                                                                                                                                                                                                                                                                                                         [i]->b->location.x)<<","<<std::to_string(transitionsInCluster[i]->b->location.y);
                    std::string valuesS=valuesSS.str();
                    values.push_back(valuesS);
                    
                }
                this->getInducedSubgraph(&subGraph, cluster);
                //                clusters.push_back(subGraph);
                
                
                //                std::cout<<"saving file"<<'\n';
                TextFile::writeToFile(name1, values, true);
                //                textFile.writeNCOLPlusCoordinatesFile(&subGraph, name1);
            }
            for(long i=0; i<cluster.size(); i++)
            {
                cluster[i]->inCluster=false;
            }
            transitionsInCluster.clear();
            cluster.clear();
            idsNodesToContinueCluster.clear();
            
        }
    }
    
    
}
void Graph::generateNetworkPercolation(double distanceLimit,std::vector<Graph> &clusters,bool saveResultClusters,bool returnClusters,std::string nameOfFolderForFiles,long minClusterSize,bool probabilistic)
{
    bool save=saveResultClusters;
    //    bool returnClusters=false;
    //from primal graph
    static const int STATIC=0;
    static const int ADAPTATIVE=1;
    int mode=STATIC;
//    MinHeap<Transition*> transitionsToGetMinWeight;
    std::list<Transition*> transitionsToGetMinWeight;
    
    for(long i=0; i<nodes.size(); i++)
    {
        for(long j=0; j<nodes[i].transitions.size(); j++)
        {
            Transition* trans=(nodes[i].transitions[j]);
//            transitionsToGetMinWeight.push(trans, &compareByWeight);
            transitionsToGetMinWeight.push_front(trans);
        }
    }
    
    
    long numClusters=0;
    
    
    while(transitionsToGetMinWeight.size()>0)
    {
        
        
//        Transition* minTrans=transitionsToGetMinWeight.pop(&compareByWeight);
        Transition* minTrans=transitionsToGetMinWeight.front();
        transitionsToGetMinWeight.pop_front();
        
//        if(minTrans->weight>distanceLimit&&!probabilistic)
//        {
//            break;
//        }
        if(!minTrans->usedInNetworkPercolation)
        {
            std::vector<Transition*> transitionsInCluster;
            std::vector<long> idsNodesToContinueCluster;
            std::vector<Node*> externalNodes;
            
            
            long idNode=minTrans->a->id;
            idsNodesToContinueCluster.push_back(idNode);
            
            //            double referenceDistance;
            //            referenceDistance=minTrans->weight;
            
            while(idsNodesToContinueCluster.size()>0)
            {
                idNode=idsNodesToContinueCluster[idsNodesToContinueCluster.size()-1];
                idsNodesToContinueCluster.pop_back();
                if(!nodes[idNode].inCluster)
                {
                    //                    externalNodes.push_back(&nodes[idNode]);
                    //                    minTrans->a->inCluster=true;
                    nodes[idNode].inCluster=true;
                }
                
                if(nodes[idNode].transitions.size()>0)
                {
                    
                    long numTransAdded=0;
                    for(long i=0; i<nodes[idNode].transitions.size(); i++)
                    {
                        
                        Transition* trans=(nodes[idNode].transitions[i]);
                        double B=3;
                        double probability=1-1/(1+exp(-B*(trans->weight-distanceLimit)));
                        double value=Functions::runiform(0,1);
                        bool valid;
                        if(!probabilistic){
                            if((trans->weight)<=distanceLimit){
                                valid=true;
                            }else{
                                valid=false;
                            }
                        }else{
                            if(value<=probability){
                                
                                valid=true;
                            }else{
                                valid=false;
                            }
                        }
                        
                        
                        if(trans->a!=trans->b&&!trans->usedInNetworkPercolation&&valid)
                        {
                            if(!trans->b->inCluster)
                            {
                                //                                cluster.push_back(trans->b);
                                idsNodesToContinueCluster.push_back(trans->b->id);
                                trans->b->inCluster=true;
                                
//                                trans->getSimetricTransition()->usedInNetworkPercolation=true;
                            }
                            numTransAdded++;
                            trans->usedInNetworkPercolation=true;
                            transitionsInCluster.push_back((nodes[idNode].transitions[i]));
                            
//
                            
                            
                            
                            if(mode==ADAPTATIVE)
                            {
                                //                                        referenceDistance=nodes[idNode].transitions[i].weight;
                            }
                        }
                        
                    }
                    if(numTransAdded==0&&!nodes[idNode].inExternalNodes)
                    {
                        externalNodes.push_back(&nodes[idNode]);
                        nodes[idNode].inExternalNodes=true;
                    }
                }
                
            }
            Graph subGraph;
            if(transitionsInCluster.size()>0)
            {
                
                
                //                if(numClusters==128){
                //                    std::cout<<"hello???"<<'\n';
                //                }
                double totalMass=0;
                if(save||returnClusters)
                {
                    
                    this->getInducedSubgraph(&subGraph, transitionsInCluster);
                    for(long k=0;k<subGraph.nodes.size();k++){
                        totalMass+=subGraph.nodes[k].mass;
                    }
                    if(totalMass>=minClusterSize){
                        numClusters++;
                    }
                    
                    
                    //                    std::cout<<"temp subgraph size "<<subGraph.nodes.size();
                }
                if(returnClusters&&totalMass>=minClusterSize)
                {
                    subGraph.id=numClusters;
                    
                    clusters.push_back(subGraph);
                    //                    if(clusters.size()==1){
                    ////                        std::cout<<"en function "<<&(clusters[0])<<'\n';
                    //                    }
                }
                
                if(save&&totalMass>=minClusterSize)
                {
//                    ArchivoTexto textFile;
                    std::stringstream nameSS1;
                    nameSS1<<nameOfFolderForFiles<<"clustered_network_dc"<<distanceLimit<<".txt";
                    
                    std::string name1=nameSS1.str();
                    std::vector<std::string> values;
                    double TSL=0;
                    std::stringstream valuesSS1;
                    valuesSS1<<"numCluster"<<","<<"numNodes"<<","<<"idA"<<","<<"idB"<<","<<"weight";
                    std::string valuesS1=valuesSS1.str();
                    //  values.push_back(valuesS1);
                    
                    for(long i=0; i<transitionsInCluster.size(); i++)
                    {
                        //                    cluster.push_back(&nodes[idNode]);
                        TSL+=transitionsInCluster[i]->weight;
                        std::stringstream valuesSS;
                        //                    valuesSS<<numClusters<<" "<<transitionsInCluster[i]->a->id<<" "<<transitionsInCluster[i]->b->id<<" "<<transitionsInCluster[i]->weight<<" "<<std::to_string(transitionsInCluster[i]->a->location.x)<<" "<<std::to_string(transitionsInCluster[i]->a->location.y)<<" "<<std::to_string(transitionsInCluster
                        valuesSS<<numClusters<<","<<subGraph.nodes.size()<<","<<transitionsInCluster[i]->a->originalID<<","<<transitionsInCluster[i]->b->originalID<<","<<transitionsInCluster[i]->weight;
                        std::string valuesS=valuesSS.str();
                        values.push_back(valuesS);
                        
                    }
                    
                    
                    
                    //                std::cout<<"saving file"<<'\n';
                    TextFile::writeToFile(name1, values, true);
                }
                
                //                //                textFile.writeNCOLPlusCoordinatesFile(&subGraph, name1);
            }
            
            
            
            
            ////////////calculatediameter
            //            if(calculateDiameter&&subGraph.nodes.size()>600)
            //            {
            //                std::vector<Transition> originsDestinationsTemp;
            //                subGraph.calculateDiameter(false,false,false,externalNodes,originsDestinationsTemp,true,&metricHeuristic);
            //                originsDestinationsTemp.clear();
            //                std::cout<<"diameter of cluster calculated "<<"id: "<<numClusters<<" sizeCluster: "<<subGraph.nodes.size()<<" sizeExternalNodes: "<<externalNodes.size()<<" diameter: "<<subGraph.diameterWeighted<<'\n';
            //            }
            
            
            for(long i=0; i<externalNodes.size(); i++)
            {
                externalNodes[i]->inExternalNodes=false;
            }
            transitionsInCluster.clear();
            externalNodes.clear();
            idsNodesToContinueCluster.clear();
            
        }
    }
    for(long i=0; i<nodes.size(); i++)
    {
        nodes[i].inCluster=false;
        for(long j=0; j<nodes[i].transitions.size(); j++)
        {
            Transition* trans=(nodes[i].transitions[j]);
            trans->usedInNetworkPercolation=false;
        }
    }
    
    
}
void Graph::getConnectedComponents(Graph* graph,std::vector<Graph> &clusters){

    generateNetworkPercolation(INFINITY, clusters, false, true, "", 0,false);
  

}
void Graph::getGiantComponent(Graph* graph,Graph* giantComponent){
    std::vector<Graph> clusters;
    generateNetworkPercolation(INFINITY, clusters, false, true, "", 0,false);
    long indexGiantComponent=-1;
    long maxNumberNodes=0;
    for(long i=0;i<clusters.size();i++){
        if(maxNumberNodes<clusters[i].nodes.size()){
            maxNumberNodes=clusters[i].nodes.size();
            indexGiantComponent=i;
        }
    }
    std::vector<Node*> nodesOfGiantCluster;
    for(long i=0;i<clusters[indexGiantComponent].nodes.size();i++){
        nodesOfGiantCluster.push_back(clusters[indexGiantComponent].nodes[i].nodeThatRepresents);
    }
    graph->getInducedSubgraph(giantComponent,nodesOfGiantCluster);
    
//    copyGraph(&clusters[indexGiantComponent], giantComponent,true);
}
double Graph::calculateFractalDimension(std::vector<Point2d> &results){
//    std::vector<Point2d> results;

    
//               for(long i=0;i<transitions.size();i++){
//                transitions[i].weight=1;
//            }
//            this->setTypeOfMainDistanceAndInsertIntoDistances(Graph::TOPOLOGICAL);
    
    
    
    std::vector<Graph> modules;
    for(long lb=2;lb<10;lb++){
//        std::cout<<lb<<'\n';
        modules.clear();
        this->calculateColorsWithMEMB(this, lb, this->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]);
        this->calculateClustersFromColors(this,modules);
        results.push_back(Point2d(lb,modules.size()));
        
    }

    LinearRegression linearRegression;
    linearRegression.calculate(results);
    fractalDimension=linearRegression.slope;
    return fractalDimension;
//    return fractalDimension;
    
}

double Graph::calculateModularityFromColors(Graph* graph,std::vector<Graph> &clusters,long type){
    double modularity=0;
    if(type==0){//NEWMANN
        
        double m=0;
//        if(graph->strictlyDirectional){
//            m=graph->transitions.size();
//        }else{
//            if(graph->bidirectional){
//                m=graph->transitions.size()*2;
//            }else{
//                m=0;//I leave it undefined and calculate it later;
//            }
//        }
        
        
        
        for(long i=0;i<graph->nodes.size();i++){
            for (long j=0;j<graph->nodes[i].transitions.size();j++){
                m++;

            }
        }
        for(long h=0;h<clusters.size();h++){
            double positiveModularity=0;
            double negativeModularity=0;
            for(long i=0;i<clusters[h].nodes.size();i++){
                Node* realNodeA=clusters[h].nodes[i].nodeThatRepresents;
                for(long j=0;j<clusters[h].nodes.size();j++){
                    Node* realNodeB=clusters[h].nodes[i].nodeThatRepresents;
                    if(realNodeA->indexOfTransitionsByIdOfDestination[realNodeB->originalID]!=-1){
                        positiveModularity++;
                    }
                    negativeModularity+=graph->getDegreeOut(realNodeA)*graph->getDegreeIn(realNodeB)/(2*m);
                    
                }
                
            }
            modularity+=(positiveModularity-negativeModularity)/(2*m);
        }
        
        
        
    }else{//MAKSE
        if(clusters.size()>1){
            double L_in=0;
            double L_out=0;
            double m=0;
            
            for(long h=0;h<clusters.size();h++){
                for(long i=0;i<clusters[h].nodes.size();i++){
                    Node* realNode=clusters[h].nodes[i].nodeThatRepresents;
                    for (long j=0;j<realNode->transitions.size();j++){
                        m++;
                        if(realNode->transitions[j]->a->numColor==realNode->transitions[j]->b->numColor){
                            L_in++;
                        }else{
                            L_out++;
                        }
                    }
                }
                modularity+=1/((double)(clusters.size()))*(L_in/L_out);
            }
        }
    }
    
    return modularity;
}
double Graph::calculateLocalClustering(Graph* graph,Node* node){
    double localClustering=0;
    std::vector<Node*> neighborhood;
    neighborhood.push_back(node);
    for(long i=0;i<node->transitions.size();i++){
        neighborhood.push_back(node->transitions[i]->b);
    }
    for(long i=0;i<node->nodesThatReachMe.size();i++){
        neighborhood.push_back(node->nodesThatReachMe[i]);
    }
    Graph subgraph;
    graph->getInducedSubgraph(&subgraph, neighborhood);
    double m=0;
    for(long i=0;i<subgraph.nodes.size();i++){
        Node* nodeTemp=&subgraph.nodes[i];
        m+=nodeTemp->transitions.size();
    }
    double n=subgraph.nodes.size();
    if(graph->bidirectional){
        localClustering=2*m/(n*(n-1));
    }else{
        localClustering=m/(n*(n-1));
    }
    return localClustering;
}

double Graph::calculateAveragedLocalClustering(Graph* graph){
    double averagedLocalClustering=0;
    for(long i=0;i<graph->nodes.size();i++){
        averagedLocalClustering+=calculateLocalClustering(graph,&graph->nodes[i]);
    }
    averagedLocalClustering/=(double)(graph->nodes.size());
    return averagedLocalClustering;
}

void Graph::generateRandomGraphFromRewiring(Graph* originalGraph,Graph* randomGraph,double p){
    for(long i=0;i<originalGraph->nodes.size();i++){
        randomGraph->addNode();
    }
    std::vector<Node*> starts;
    std::vector<Node*> ends;
    for(long i=0;i<originalGraph->nodes.size();i++){
        //        kReachableGraph->addNode();
        randomGraph->nodes[i].numColor=originalGraph->nodes[i].numColor;
//        kReachableGraph->nodes[i].isCovered=originalGraph->nodes[i].isCovered;
//        kReachableGraph->nodes[i].isCenter=nodes[i].isCenter;
        randomGraph->nodes[i].originalID=originalGraph->nodes[i].originalID;
        randomGraph->nodes[i].nodeThatRepresents=&originalGraph->nodes[i];
        originalGraph->nodes[i].nodeRepresentedBy=&randomGraph->nodes[i];
        
    }
    double totalNumberOfTransitionsToRewire=ceil((double)(originalGraph->transitions.size())*p);
    
    std::vector<double> randomValues;
//    std::vector<double> randomValues2;
    
    for(long i=0;i<originalGraph->transitions.size();i++){
        double random=Functions::runiform(0, 1);
        randomValues.push_back(random);
//        random=Functions::runiform(0, 1);
//        randomValues2.push_back(random);
    }
    
    
    std::vector<long> indexesRandom=Functions::getIndexesOfOrderedValues(randomValues, true);
//    std::vector<long> indexesRandom2=Functions::getIndexesOfOrderedValues(randomValues, true);
    
    for(long i=0;i<(totalNumberOfTransitionsToRewire);i++){
//        starts.push_back(originalGraph->transitions[i].a);
//        ends.push_back(originalGraph->transitions[i].b);
        Transition* trans1=&originalGraph->transitions[indexesRandom[i]];
//        Transition* trans2=&originalGraph->transitions[indexesRandom[i+1]];
                starts.push_back(trans1->a->nodeRepresentedBy);
                ends.push_back(trans1->b->nodeRepresentedBy);
//        Transition trans;
//        trans.a=trans1->a->nodeRepresentedBy;
//        trans.b=trans2->b->nodeRepresentedBy;
//        randomGraph->addTransition(trans);
        if(trans1->bidirectional){
            starts.push_back(trans1->b->nodeRepresentedBy);
            ends.push_back(trans1->a->nodeRepresentedBy);
//            Transition transB;
//            transB.a=trans1->b->nodeRepresentedBy;
//            transB.b=trans2->a->nodeRepresentedBy;
//            randomGraph->addTransition(trans);
        }
    }
   
    
    for(long i=(totalNumberOfTransitionsToRewire);i<originalGraph->transitions.size();i++){
        Transition* trans1=&originalGraph->transitions[indexesRandom[i]];
        Transition trans;
        trans.a=trans1->a->nodeRepresentedBy;
        trans.b=trans1->b->nodeRepresentedBy;
        randomGraph->addTransition(trans);
    }
    std::vector<double> randomValuesSub;
    //    std::vector<double> randomValues2;
    
    for(long i=0;i<starts.size();i++){
        double random=Functions::runiform(0, 1);
        randomValuesSub.push_back(random);
        //        random=Functions::runiform(0, 1);
        //        randomValues2.push_back(random);
    }
    std::vector<long> indexesRandomSub=Functions::getIndexesOfOrderedValues(randomValuesSub, true);
    
    for(long i=0;i<starts.size();i++){
        Transition trans;
        trans.a=starts[indexesRandomSub[i]];
        trans.b=ends[i];
        randomGraph->addTransition(trans);
    }
    
}


void Graph::assignColorsFromClusters(Graph* graph,std::vector<Graph> &clusters){
    for(long i=0;i<clusters.size();i++){
        for(long j=0;j<clusters[i].nodes.size();j++){
            clusters[i].nodes[j].nodeThatRepresents->numColor=i;
        }
    }
}



void Graph::calculateClustersFromColors(Graph* graph,std::vector<Graph> &clusters){
    std::vector<Node*> nodesOfCluster;
    std::vector<double> values;
    for(long i=0; i<graph->nodes.size(); i++)
    {
        values.push_back(graph->nodes[i].numColor);
    }
    std::vector<long> orderNumColors=Functions::getIndexesOfOrderedValues(values, true);
    double previousNumColor=values[orderNumColors[0]];
    for(long i=0;i<values.size();i++){
        Node* node=&graph->nodes[orderNumColors[i]];
        double numColor=node->numColor;
//        std::cout<<previousNumColor<<" "<<numColor<<" "<<clusters.size()<<'\n';
        

//        if(!nodes[i].inCluster){
//            std::vector<Node*> nodesToContinueCluster;
//            
//            nodesToContinueCluster.push_back(&nodes[i]);
//            
//            Node* currentNode;
//            while(nodesToContinueCluster.size()>0){
//                currentNode=nodesToContinueCluster.back();
//                nodesToContinueCluster.pop_back();
//                nodesOfCluster.push_back(currentNode);
//                currentNode->inCluster=true;
//                bool nodesAdded=true;
//                while(nodesAdded){
//                    nodesAdded=false;
//                    for(long j=0;j<nodes[i].transitions.size();j++){
//                        if(!nodes[i].transitions[j]->b->inCluster){
//                            if(nodes[i].transitions[j]->b->numColor==nodes[i].numColor){
////                                nodesOfCluster.push_back(nodes[i].transitions[j].b);
//                                nodesToContinueCluster.push_back(nodes[i].transitions[j]->b);
//                                nodes[i].transitions[j]->b->inCluster=true;
//                                nodesAdded=true;
//                            }
//                        }
//                    }
//                }
//            }
        if(previousNumColor!=numColor){
            Graph cluster;
            graph->getInducedSubgraph(&cluster, nodesOfCluster);
//            if (returnClusters){
                clusters.push_back(cluster);
//            }
            nodesOfCluster.clear();
            nodesOfCluster.push_back(node);
            previousNumColor=numColor;
        }else{
            
            nodesOfCluster.push_back(node);
        }
    }
    Graph cluster;
    graph->getInducedSubgraph(&cluster, nodesOfCluster);

    clusters.push_back(cluster);
//        nodes[i].inCluster=false;
    
    
}
//void Graph::calculateClusterUsingNetworkPercolation(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff) {
//
//    if (!nodeInit->inCluster){
//        std::vector<Node*> nodesYetToCalculate;
//        nodesCutoff.push_back(nodeInit);
//        nodeInit->inCluster=true;
//        for(int i=0;i<nodeInit->transitions.size();i++){
//
//            if (nodeInit->transitions[i].b->transitions.size()>2){
//                if (nodeInit->transitions[i].weight<distanceLimit&&!(nodeInit->transitions[i].b->inCluster)&&!(nodeInit->transitions[i].b->inDijkstra)){
//                    nodesCutoff.push_back(nodeInit->transitions[i].b);
//                    nodeInit->transitions[i].b->inDijkstra=true;
//                    if (!nodeInit->transitions[i].b->inDijkstra){
//                        nodesYetToCalculate.push_back(nodeInit->transitions[i].b);
//                    }
//                }
//            }else{
//                bool end=false;
//                Node* nodePrevious=nodeInit;
//
//                double totalLengthPath=nodeInit->transitions[i].weight;
//                Node* nodeTemp=nodeInit->transitions[i].b;
//
//                std::vector<Node*> nodesOfPath;
//                nodesOfPath.push_back(nodeTemp);
//                int indexOtherTransition=-1;
//                for (int j=0;j<nodeTemp->transitions.size();j++){
//                    if (nodeTemp->transitions[j].b!=nodePrevious){
//                        indexOtherTransition=j;
//                    }
//                }
//                bool valid=true;
//                if(nodeTemp->transitions.size()<2){
//                    end=true;
//                }
//                while(valid&&!end&&nodeTemp->transitions[indexOtherTransition].b->transitions.size()==2){
//                    if (totalLengthPath>distanceLimit){
//                        valid=false;
//                    }
//                    nodePrevious=nodeTemp;
//                    totalLengthPath+=nodePrevious->transitions[indexOtherTransition].weight;
//                    nodeTemp=nodeTemp->transitions[indexOtherTransition].b;
//                    nodesOfPath.push_back(nodeTemp);
//
//                    if(nodeTemp->transitions.size()<2){
//                        end=true;
//                    }else{
//                        indexOtherTransition=-1;
//                    }
//                    if(!end){
//                        for (int j=0;j<nodeTemp->transitions.size();j++){
//                            if (nodeTemp->transitions[j].b!=nodePrevious){
//                                indexOtherTransition=j;
//                            }
//                        }
//                    }
//                }
//                if (!end){
//                    totalLengthPath+=nodeTemp->transitions[indexOtherTransition].weight;
//                }
//                if (totalLengthPath>distanceLimit){
//                    valid=false;
//                }
//                if (valid){
//                    if (!end&&!nodeTemp->transitions[indexOtherTransition].b->inDijkstra&&!nodeTemp->transitions[indexOtherTransition].b->inCluster){
//                        nodesYetToCalculate.push_back(nodeTemp->transitions[indexOtherTransition].b);
//                    }
//                    for (int j=0;j<nodesOfPath.size();j++){
//                        nodesCutoff.push_back(nodesOfPath[j]);
//                        nodesOfPath[j]->inDijkstra=true;
//                        nodesOfPath[j]->inCluster=true;
//
//                    }
//                    if (!end){
//                        nodesCutoff.push_back(nodeTemp->transitions[indexOtherTransition].b);
//                    }
//                }
//            }
//        }
//
//
//        while (nodesYetToCalculate.size()>0){
//            Node* node=nodesYetToCalculate[nodesYetToCalculate.size()-1];
//            node->inCluster=true;
////            node->inDijkstra=false;
//            nodesYetToCalculate.pop_back();
//            nodesCutoff.push_back(node);
//            for(int i=0;i<node->transitions.size();i++){
//                if (node->transitions[i].b->transitions.size()>2){
//                    if (node->transitions[i].weight<distanceLimit&&!(node->transitions[i].b->inCluster)&&!(node->transitions[i].b->inDijkstra)){
//                        nodesCutoff.push_back(node->transitions[i].b);
//                        node->transitions[i].b->inDijkstra=true;
//                        nodesYetToCalculate.push_back(node->transitions[i].b);
//                    }
//                }else{
//                    Node* nodePrevious=node;
//
//                    double totalLengthPath=node->transitions[i].weight;
//                    Node* nodeTemp=node->transitions[i].b;
//                    std::vector<Node*> nodesOfPath;
//                    nodesOfPath.push_back(nodeTemp);
//                    int indexOtherTransition=-1;
//                    for (int j=0;j<nodeTemp->transitions.size();j++){
//                        if (nodeTemp->transitions[j].b!=nodePrevious){
//                            indexOtherTransition=j;
//                        }
//                    }
//                    bool valid=true;
//                    bool end=false;
//                    if(nodeTemp->transitions.size()<2){
//                        end=true;
//                    }
//                    while(valid&&!end&&nodeTemp->transitions[indexOtherTransition].b->transitions.size()==2){
//                        if (totalLengthPath>distanceLimit){
//                            valid=false;
//                        }
//                        nodePrevious=nodeTemp;
//                        totalLengthPath+=nodePrevious->transitions[indexOtherTransition].weight;
//                        nodeTemp=nodeTemp->transitions[indexOtherTransition].b;
//                        nodesOfPath.push_back(nodeTemp);
//
//                        if(nodeTemp->transitions.size()==1){
//                            end=true;
//                        }else{
//                            indexOtherTransition=-1;
//                        }
//                        if(!end){
//                            for (int j=0;j<nodeTemp->transitions.size();j++){
//                                if (nodeTemp->transitions[j].b!=nodePrevious){
//                                    indexOtherTransition=j;
//                                }
//                            }
//                        }
//                    }
//                    if (!end){
//                        totalLengthPath+=nodeTemp->transitions[indexOtherTransition].weight;
//                    }
//                    if (totalLengthPath>distanceLimit){
//                        valid=false;
//                    }
//                    if (valid){
//                        if (!end&&!nodeTemp->transitions[indexOtherTransition].b->inDijkstra&&!nodeTemp->transitions[indexOtherTransition].b->inCluster){
//                            nodesYetToCalculate.push_back(nodeTemp->transitions[indexOtherTransition].b);
//                        }
//                        for (int j=0;j<nodesOfPath.size();j++){
//                            nodesCutoff.push_back(nodesOfPath[j]);
//                            nodesOfPath[j]->inDijkstra=true;
//                             nodesOfPath[j]->inCluster=true;
//
//                        }
//                        if (!end){
//                            nodesCutoff.push_back(nodeTemp->transitions[indexOtherTransition].b);
//                        }
//                    }
//                }
//            }
//
//        }
//    }
//
//}
//void Graph::calculateDijkstra(Node* &nodeInit,double distanceLimit,BST<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra)
//{
//    
//    nodesToCheckDijkstra.heap[0]->minDistance=0;
//    
//    while (nodesToCheckDijkstra.size() > 0)
//    {
//        
//        Node* startNode = (nodesToCheckDijkstra.pop());
//        startNode->inDijkstra=false;
//        
//        
//        for (long i = 0; i < startNode->nodeThatRepresents->transitions.size(); i++)
//        {
//            Transition* trans = &(startNode->nodeThatRepresents->transitions[i]);
//            //                if (!trans.alreadyUsedDijkstra){
//            //                    trans.alreadyUsedDijkstra=true;
//            //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
//            //                    bool addToDijkstra = false;
//            
//            //                Node* nodeB;
//            
//            bool nodeBSet=false;
//            
//            bool alreadyInCutoff=false;
//            Node* nodeB=nodesCutoff.get(trans->b->id);
//            
//            if (nodeB!=NULL)
//            {
//                
//                alreadyInCutoff=true;
//                
//                nodeBSet=true;
//            }
//            
//            
//            double possibleDistance=trans->weight + startNode->minDistance;
//            
//            if ((!nodeBSet||(possibleDistance) < nodeB->minDistance)&& (possibleDistance < distanceLimit||distanceLimit==0))
//            {
//                if (!nodeBSet)
//                {
//                    
//                    nodeB=trans->b->getCopy();
//                    nodesCutoff.add(nodeB->nodeThatRepresents->id,nodeB);
//                }
//                else
//                {
//                    nodeB->parent->numChildren--;
//                }
//                nodeB->parent=startNode;
//                startNode->numChildren++;
//                
//                nodeB->minDistance=possibleDistance;
//                //                        addToDijkstra=true;
//                //                        if (!alreadyInCutoff){
//                //
//                //
//                //                        }
//                
//                if (!nodeB->inDijkstra)
//                {
//                    nodesToCheckDijkstra.push(nodeB);
//                    nodeB->inDijkstra=true;
//                }
//                else
//                {
////                    if(nodeB->minDistance<nodesToCheckDijkstra.getMin(&compareByDistance)->minDistance){
//                        nodesToCheckDijkstra.modify(nodeB);
////                    }
//                }
//                
//            }
//            //                 if (nodeB->minAngularDistance==-1||(trans.angularWeight + startNode->minAngularDistance) < nodeB->minAngularDistance) {
//            //
//            //                    nodeB->parentAngular=startNode;
//            //
//            //                    nodeB->minAngularDistance=trans.angularWeight + startNode->minAngularDistance;
//            //                    addToDijkstra=true;
//            //
//            //                }
//            //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
//            //
//            //                    nodeB->parentMetric=startNode;
//            //
//            //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
//            //                    addToDijkstra=true;
//            //
//            //                }
//            
//            //                    if (addToDijkstra ) {
//            //
//            //                    }else {
//            ////                        if (!alreadyInCutoff&&nodeB!=NULL){
//            ////
//            ////                            delete nodeB;
//            ////                        }
//            //                    }
//            //                }
//            
//        }
//        
//    }
//    if (this->calculateOtherDistances)
//    {
//        for (int indexDistance=0; indexDistance<numberDistances; indexDistance++)
//        {
//            //			nodesToCheckDijkstra.clear();
//            //			std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
//            //			for (int i=0;i<orderedCutoff.size();i++){
//            //				orderedCutoff[i]->inDijkstra=false;
//            //			}
//            //			std::cout<<"currently calculating distance "<<indexDistance<<'\n';
//            Node* startNode=nodesCutoff.get(nodeInit->id);
//            //			this->currentIndexDistance=indexDistance;
//            //            int indexDistanceTemp=indexDistance;
//            CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//            nodesToCheckDijkstra.push(startNode,compare);
//            calculateDijkstraOtherDistance(nodeInit,nodesCutoff,nodesToCheckDijkstra,indexDistance);
//            
//        }
//        
//    }
//    
//    
//    makeCalculations(nodeInit,nodesCutoff);
//}
void Graph::calculateDijkstraSpeed(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra)
{
    
//    nodesToCheckDijkstra.heap[0]->minDistance=0;
    
    while (nodesToCheckDijkstra.size() > 0)
    {
        //                Node* possibleNode=nodesToCheckDijkstra.pop(&compareByDistance);
        //        long idTemp=(possibleNode->id);
        
        //        Node* startNode = &(this->nodes[idTemp]);
        Node* startNode =nodesToCheckDijkstra.pop();
        startNode->inDijkstra=false;
        if(startNode->transitions.size()>0)
        {
            
            for (long i = 0; i < startNode->transitions.size(); i++)
            {
                Transition* trans = (startNode->transitions[i]);
                if (trans->a==trans->b)
                {
                    std::cout<<"loop!!! "<<trans->a<<'\n';
                }
                if(trans->weight==INFINITY)
                {
                    //                    std::cout<<"INFINITY!!"<<'\n';
                    
                }
                //                if (!trans.alreadyUsedDijkstra){
                //                    trans.alreadyUsedDijkstra=true;
                //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
                //                    bool addToDijkstra = false;
                
                Node* nodeB;
                
                bool nodeBSet=false;
                
                //                    bool alreadyInCutoff=false;
                if (trans->b!=NULL)
                {
                    nodeB=trans->b;
                }
                else
                {
                    nodeB=&(nodes[trans->idB]);
                }
                //                    idTemp=possibleNode->id;
                //                    Node* nodeB=&(this->nodes[idTemp]);
                
                if (nodeB->inCutoff)
                {
                    
                    //                        alreadyInCutoff=true;
                    
                    nodeBSet=true;
                }
                bool nullBecauseOfBacktracking=false;
                if(avoidBacktrackingInLineGraph){
                    Transition* previousTrans=NULL;
                    if(startNode->parent!=NULL){
                        for(long g=0;g<startNode->parent->transitions.size();g++){
                            if(startNode==startNode->parent->transitions[g]->b){
                                previousTrans=startNode->parent->transitions[g];
                            }
                        }
                        if(previousTrans->nodeInGraphAfterLineGraphGeneration==trans->nodeInGraphAfterLineGraphGeneration){
                            nullBecauseOfBacktracking=true;
                        }
                    }
                }
                
                double possibleDistance=trans->weight + startNode->minDistance;
                
                if (!nullBecauseOfBacktracking&&(nodeB->minDistance==INFINITY||(possibleDistance) < nodeB->minDistance)&& (possibleDistance < distanceLimit||distanceLimit==0))
                {
                    if (!nodeBSet)
                    {
                        
                        //                            nodeB=trans->b->getCopy();
                        nodeB->inCutoff=true;
                        nodesCutoff.push_back(nodeB);
                    }
                    else
                    {
                        nodeB->parent->numChildren--;
                    }
                    nodeB->parent=startNode;
                    startNode->numChildren++;
                    double previousDistance=nodeB->minDistance;
                    nodeB->minDistance=possibleDistance;
                    //                        addToDijkstra=true;
                    //                        if (!alreadyInCutoff){
                    //
                    //
                    //                        }
                    
                    if (!nodeB->inDijkstra)
                    {
                        nodeB->inDijkstra=true;
                        nodesToCheckDijkstra.push(nodeB);
                        
                    }
                    else
                    {
//                        if(nodeB->minDistance<nodesToCheckDijkstra.getMin(&compareByDistance)->minDistance){
                        nodesToCheckDijkstra.update(nodeB,previousDistance);
//                        }
                    }
                    
                }
                //                 if (nodeB->minAngularDistance==-1||(trans.angularWeight + startNode->minAngularDistance) < nodeB->minAngularDistance) {
                //
                //                    nodeB->parentAngular=startNode;
                //
                //                    nodeB->minAngularDistance=trans.angularWeight + startNode->minAngularDistance;
                //                    addToDijkstra=true;
                //
                //                }
                //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
                //
                //                    nodeB->parentMetric=startNode;
                //
                //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
                //                    addToDijkstra=true;
                //
                //                }
                
                //                    if (addToDijkstra ) {
                //
                //                    }else {
                ////                        if (!alreadyInCutoff&&nodeB!=NULL){
                ////
                ////                            delete nodeB;
                ////                        }
                //                    }
                //                }
                
            }
        }
        
    }
    
    
}
void Graph::calculateAllShortestPathsToANodeUsingModificationDijkstra(Node* &nodeInit,Node* nodeDestination,Heap<Node*> &nodesToCheckDijkstra)
{
    
    
//    std::cout<<"_______________________________"<<'\n';
//    std::cout<<"nodeInit "<<nodeInit->originalID<<'\n';
//    ,double distanceLimit,std::vector<Node*> &nodesCutoff
    double distanceLimit=0;
    bool reached=false;
//    nodesToCheckDijkstra.heap[0]->minDistance=0;
    
    while (nodesToCheckDijkstra.size() > 0)
    {
        //                Node* possibleNode=nodesToCheckDijkstra.pop(&compareByDistance);
        //        long idTemp=(possibleNode->id);
        
        //        Node* startNode = &(this->nodes[idTemp]);
        if (reached){
            distanceLimit=nodeDestination->minDistance;
        }
        
//        for(long u=0;u<nodesToCheckDijkstra.heap.size();u++){
//            std::cout<<"dijkstra "<<nodesToCheckDijkstra.heap[u]->originalID<<'\n';
//        }
        Node* startNode =nodesToCheckDijkstra.pop();
        startNode->inDijkstra=false;
//        for(long u=0;u<nodesToCheckDijkstra.heap.size();u++){
//            std::cout<<"dijkstraB "<<nodesToCheckDijkstra.heap[u]->originalID<<'\n';
//        }
//                    std::cout<<"startNode "<<startNode->originalID<<'\n';
        if(startNode->transitions.size()>0)
        {
            
            for (long i = 0; i < startNode->transitions.size(); i++)
            {
                Transition* trans = (startNode->transitions[i]);
                if (trans->a==trans->b)
                {
                    std::cout<<"loop!!!"<<'\n';
                }
                if(trans->weight==INFINITY)
                {
                    //                    std::cout<<"INFINITY!!"<<'\n';
                    
                }
                //                if (!trans.alreadyUsedDijkstra){
                //                    trans.alreadyUsedDijkstra=true;
                //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
                //                    bool addToDijkstra = false;
                
                Node* nodeB;
                
                bool nodeBSet=false;
                
                //                    bool alreadyInCutoff=false;
                if (trans->b!=NULL)
                {
                    nodeB=trans->b;
//                    std::cout<<"nodeB "<<nodeB->originalID<<'\n';
                }
                else
                {
                    nodeB=&(nodes[trans->idB]);
                }
                //                    idTemp=possibleNode->id;
                //                    Node* nodeB=&(this->nodes[idTemp]);
                
                if (nodeB->inCutoff)
                {
                    
                    //                        alreadyInCutoff=true;
                    
                    nodeBSet=true;
                }
//                bool nullBecauseOfBacktracking=false;
//                if(avoidBacktrackingInLineGraph){
//                    Transition previousTrans;
//                    if(startNode->parent!=NULL){
//                        for(long g=0;g<startNode->parent->transitions.size();g++){
//                            if(startNode==startNode->parent->transitions[g].b){
//                                previousTrans=startNode->parent->transitions[g];
//                            }
//                        }
//                        if(previousTrans.IDofNodeInGraphAfterLineGraphGeneration==trans->IDofNodeInGraphAfterLineGraphGeneration){
//                            nullBecauseOfBacktracking=true;
//                        }
//                    }
//                }
                
                double possibleDistance=trans->weight + startNode->minDistance;
                
//                long id=nodeB->originalID;
//                std::cout<<"start Node "<<startNode->originalID<<'\n';
//                std::cout<<id<<" "<<nodeB->minDistance<<" "<<possibleDistance<< " "<<nodeB->inDijkstra<<'\n';
                
                if ((nodeB->minDistance==INFINITY||(possibleDistance) <= nodeB->minDistance)&& (possibleDistance <= distanceLimit||distanceLimit==0))
                {
//                    bool distanceIsLess=false;
                    double previousDistance=nodeB->minDistance;
                    if(possibleDistance == nodeB->minDistance){
                        nodeB->parents.push_back(startNode);
                        nodeB->minDistance=possibleDistance;
//                        std::cout<<"addingParent "<<startNode->originalID<<'\n';
                        
                    }else if (possibleDistance < nodeB->minDistance){
//                        distanceIsLess=true;
//                        std::cout<<"parentsSize "<<nodeB->parents.size()<<'\n';
                        for(long h=0;h<nodeB->parents.size();h++){
                            nodeB->parents[h]->numChildren--;
                        }
                        nodeB->parents.clear();
                        nodeB->parents.push_back(startNode);
                        
                        nodeB->minDistance=possibleDistance;
                        if (!nodeB->inDijkstra)
                        {
                            //                        std::cout<<"adding "<<nodeB->originalID<<" to dijkstra"<<'\n';
                            nodeB->inDijkstra=true;
                            nodesToCheckDijkstra.push(nodeB);
                            
                        }else
                        {
                            //                        if(nodeB->minDistance<nodesToCheckDijkstra.getMin(&compareByDistance)->minDistance){
                            nodesToCheckDijkstra.update(nodeB,previousDistance);
                            //                        }
                        }
                        
//                                                std::cout<<"clearParent+addingParent "<<startNode->originalID<<'\n';
//                        nodeB->parent->numChildren--;
                    }
                    if(nodeB==nodeDestination&&nodeDestination!=NULL){
                        reached=true;
                    }
                    startNode->numChildren++;
                    
                    
                    //                        addToDijkstra=true;
                    //                        if (!alreadyInCutoff){
                    //
                    //
                    //                        }
                    
                    
                    
                    
                }
                //                 if (nodeB->minAngularDistance==-1||(trans.angularWeight + startNode->minAngularDistance) < nodeB->minAngularDistance) {
                //
                //                    nodeB->parentAngular=startNode;
                //
                //                    nodeB->minAngularDistance=trans.angularWeight + startNode->minAngularDistance;
                //                    addToDijkstra=true;
                //
                //                }
                //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
                //
                //                    nodeB->parentMetric=startNode;
                //
                //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
                //                    addToDijkstra=true;
                //
                //                }
                
                //                    if (addToDijkstra ) {
                //
                //                    }else {
                ////                        if (!alreadyInCutoff&&nodeB!=NULL){
                ////
                ////                            delete nodeB;
                ////                        }
                //                    }
                //                }
                
            }
        }
        
    }
    
    
}
//void Graph::calculateDijkstraOtherDistance(Node* &nodeInit,BST<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra, int indexDistance)
//{
//    //std::cout<<"making calculations";
//    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//    nodesToCheckDijkstra.heap[0]->minOtherDistances[indexDistance]=0;
//    //I have to define this minCurrentDistance although is redundant because of passing the function of compareOtherDistance
//    //	nodesToCheckDijkstra.heap[0]->minCurrentDistance=0;
//    
//    while (nodesToCheckDijkstra.size() > 0)
//    {
//        
//        Node* startNode = (nodesToCheckDijkstra.pop(compare));
//        startNode->inDijkstra=false;
//        
//        
//        for (long i = 0; i < startNode->nodeThatRepresents->transitions.size(); i++)
//        {
//            Transition* trans = &(startNode->nodeThatRepresents->transitions[i]);
//            //                if (!trans.alreadyUsedDijkstra){
//            //                    trans.alreadyUsedDijkstra=true;
//            //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
//            //                    bool addToDijkstra = false;
//            
//            //                Node* nodeB;
//            
//            //                bool nodeBSet=false;
//            
//            //                bool alreadyInCutoff=false;
//            Node* nodeB=nodesCutoff.get(trans->b->id);
//            
//            if (nodeB!=NULL)
//            {
//                
//                //                    alreadyInCutoff=true;
//                
//                //                    nodeBSet=true;
//                
//                
//                
//                
//                //                    if (nodeB->minDistance==-1||(trans.weight + startNode->minDistance) < nodeB->minDistance) {
//                //
//                //                        nodeB->parent=startNode;
//                //
//                //                        nodeB->minDistance=trans.weight + startNode->minDistance;
//                //                        addToDijkstra=true;
//                //
//                //                    }
//                double  possibleDistance=trans->otherWeights[indexDistance] + startNode->minOtherDistances[indexDistance];
//                if (nodeB->minOtherDistances[indexDistance]==INFINITY||(possibleDistance) < nodeB->minOtherDistances[indexDistance])
//                {
//                    if (nodeB->otherParents[indexDistance]!=NULL)
//                    {
//                        nodeB->otherParents[indexDistance]->numOtherChildren[indexDistance]--;
//                    }
//                    nodeB->otherParents[indexDistance]=startNode;
//                    startNode->numOtherChildren[indexDistance]++;
//                    
//                    
//                    nodeB->minOtherDistances[indexDistance]=possibleDistance;
//                    //						nodeB->minCurrentDistance=nodeB->minOtherDistances[indexDistance];
//                    //                            addToDijkstra=true;
//                    if (!nodeB->inDijkstra)
//                    {
//                        //                                CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//                        nodesToCheckDijkstra.push(nodeB,compare);
//                        nodeB->inDijkstra=true;
//                    }
//                    else
//                    {
////                        if(nodeB->minOtherDistances[indexDistance]<nodesToCheckDijkstra.getMin(compare)->minOtherDistances[indexDistance]){
//                            nodesToCheckDijkstra.buildHeap(compare);
////                        }
//                    }
//                }
//                //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
//                //
//                //                    nodeB->parentMetric=startNode;
//                //
//                //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
//                //                    addToDijkstra=true;
//                //
//                //                }
//                
//                //                        if (addToDijkstra) {
//                //    //                        if (!alreadyInCutoff){
//                //    //                            nodesCutoff.add(nodeB->nodeThatRepresents->id,nodeB);
//                //    //
//                //    //                        }
//                //
//                //
//                //                        }else{
//                //
//                //    //                        if (!alreadyInCutoff){
//                //    //
//                //    //                            delete nodeB;
//                //    //                        }
//                //                        }
//            }
//            
//        }
//        //            }
//        
//        
//    }
//    
//    
//}

void Graph::calculateDijkstraOtherDistanceSpeed(Node* &nodeInit,bool useCutoff,Heap<Node*> &nodesToCheckDijkstra, int indexDistance)
{
    //std::cout<<"making calculations";
    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//    nodesToCheckDijkstra.heap[0]->minOtherDistances[indexDistance]=0;
    //I have to define this minCurrentDistance although is redundant because of passing the function of compareOtherDistance
    //	nodesToCheckDijkstra.heap[0]->minCurrentDistance=0;
    
    while (nodesToCheckDijkstra.size() > 0)
    {
        
        Node* startNode = (nodesToCheckDijkstra.pop());
        startNode->inDijkstra=false;
        
        
        for (long i = 0; i < startNode->transitions.size(); i++)
        {
            Transition* trans = (startNode->transitions[i]);
            //                if (!trans.alreadyUsedDijkstra){
            //                    trans.alreadyUsedDijkstra=true;
            //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
            //                    bool addToDijkstra = false;
            
            //                Node* nodeB;
            
            //                bool nodeBSet=false;
            
            //                bool alreadyInCutoff=false;
            Node* nodeB=trans->b;
            
            if (nodeB->inCutoff||!useCutoff)
            {
                
                //                    alreadyInCutoff=true;
                
                //                    nodeBSet=true;
                
                
                
                
                //                    if (nodeB->minDistance==-1||(trans.weight + startNode->minDistance) < nodeB->minDistance) {
                //
                //                        nodeB->parent=startNode;
                //
                //                        nodeB->minDistance=trans.weight + startNode->minDistance;
                //                        addToDijkstra=true;
                //
                //                    }
                bool nullBecauseOfBacktracking=false;
                if(avoidBacktrackingInLineGraph){
                    Transition* previousTrans=NULL;
                    if(startNode->otherParents[indexDistance]!=NULL){
                        for(long g=0;g<startNode->otherParents[indexDistance]->transitions.size();g++){
                            if(startNode==startNode->otherParents[indexDistance]->transitions[g]->b){
                                previousTrans=startNode->otherParents[indexDistance]->transitions[g];
                            }
                        }
                        if(previousTrans->nodeInGraphAfterLineGraphGeneration==trans->nodeInGraphAfterLineGraphGeneration){
                            nullBecauseOfBacktracking=true;
                        }
                    }
                }
                double  possibleDistance=trans->otherWeights[indexDistance] + startNode->minOtherDistances[indexDistance];
                if (!nullBecauseOfBacktracking&&(nodeB->minOtherDistances[indexDistance]==INFINITY||(possibleDistance) < nodeB->minOtherDistances[indexDistance]))
                {
                    double previousDistance=nodeB->minOtherDistances[indexDistance];
                    if (nodeB->otherParents[indexDistance]!=NULL)
                    {
                        nodeB->otherParents[indexDistance]->numOtherChildren[indexDistance]--;
                    }
                    nodeB->otherParents[indexDistance]=startNode;
                    startNode->numOtherChildren[indexDistance]++;
                    
                    
                    nodeB->minOtherDistances[indexDistance]=possibleDistance;
                    //						nodeB->minCurrentDistance=nodeB->minOtherDistances[indexDistance];
                    //                            addToDijkstra=true;
                    if (!nodeB->inDijkstra)
                    {
                        //                                CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
                        nodesToCheckDijkstra.push(nodeB);
                        nodeB->inDijkstra=true;
                    }
                    else
                    {
//                         if(nodeB->minOtherDistances[indexDistance]<nodesToCheckDijkstra.getMin(compare)->minOtherDistances[indexDistance]){
                             nodesToCheckDijkstra.update(nodeB,previousDistance);
//                         }
                    }
                }
                //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
                //
                //                    nodeB->parentMetric=startNode;
                //
                //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
                //                    addToDijkstra=true;
                //
                //                }
                
                //                        if (addToDijkstra) {
                //    //                        if (!alreadyInCutoff){
                //    //                            nodesCutoff.add(nodeB->nodeThatRepresents->id,nodeB);
                //    //
                //    //                        }
                //
                //
                //                        }else{
                //
                //    //                        if (!alreadyInCutoff){
                //    //
                //    //                            delete nodeB;
                //    //                        }
                //                        }
            }
            
        }
        //            }
        
        
    }
    
    
}


//void Graph::makeCalculations(Node* &nodeInit,BST<Node*> &nodesCutoff)
//{
//    
//    //std::cout<<"geh";
//    std::vector<Node*> orderedCutoff=nodesCutoff.getAll();
//    double closenessTemp=0;
//    double TSLtemp=0;
//    double nodeCountTemp=orderedCutoff.size();
//    for (long i=0; i<orderedCutoff.size(); i++)
//    {
//        TSLtemp=TSLtemp+metricLengths[orderedCutoff[i]->nodeThatRepresents->id];
//    }
//    if (calculateMainDistance)
//    {
//        
//        for (long i=0; i<orderedCutoff.size(); i++)
//        {
//            if(orderedCutoff[i]->minDistance<INFINITY){
//                closenessTemp=closenessTemp+orderedCutoff[i]->minDistance;
//            }
//        }
//        
//        
//    }
//    std::vector<double> closenessTempOtherDistance;
//    if (calculateOtherDistances)
//    {
//        for (int j=0; j<numberDistances; j++)
//        {
//            closenessTempOtherDistance.push_back(0);
//            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
//            {
//                for (long i=0; i<orderedCutoff.size(); i++)
//                {
//                    if(orderedCutoff[i]->minOtherDistances[j]<INFINITY){
//                        closenessTempOtherDistance[j]=closenessTempOtherDistance[j]+orderedCutoff[i]->minOtherDistances[j];
//                    }
//                }
//            }
//            else
//            {
//                closenessTempOtherDistance[j]=closenessTemp;
//            }
//        }
//    }
//    
//    
//    this->nodeCount[nodeInit->id]=nodeCountTemp;
//    this->TSL[nodeInit->id]=TSLtemp;
//    this->closeness[nodeInit->id]=closenessTemp;
//    if (calculateOtherDistances)
//    {
//        for (int j=0; j<numberDistances; j++)
//        {
//            this->closenessMeasures[j][nodeInit->id]=closenessTempOtherDistance[j];
//        }
//    }
//    
//    //    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,2);
//    
//    std::vector<Node*> leaves;
//    if (calculateMainDistance)
//    {
//        std::sort(orderedCutoff.begin(),orderedCutoff.end(),&compareByNumChildren);
//        //              std::cout<<'\n';
//        //    for(int i=0;i<orderedCutoff.size();i++){
//        //        std::cout<<orderedCutoff[i]->numChildren;
//        //    }
//        
//        int i=0;
//        while(orderedCutoff[i]->numChildren==0&&i<orderedCutoff.size())
//        {
//            leaves.push_back(orderedCutoff[i]);
//            i++;
//        }
//        //    std::cout<<leaves.size()<<'\n';
//        for (long i=0; i<leaves.size(); i++)
//        {
//            Node* node=leaves[i];
////            node->valueToPass=1;
//            
//            this->betweenness[node->nodeThatRepresents->id]=this->betweenness[node->nodeThatRepresents->id]+node->valueToPass;
//            //            long valueToPass;
//            while((node->parent)!=NULL&&node->parent->numChildren==node->parent->numChildrenThatReachedMe+1)
//            {
//                double valueToPass=node->valueToPass+node->parent->valueToPass;
//                node=(node->parent);
//                node->valueToPass=valueToPass;
//                node->numChildrenThatReachedMe++;
//                if (node->nodeThatRepresents->id<0||node->nodeThatRepresents->id>=(betweenness.size()))
//                {
//                    std::cout<<"problema";
//                }
//                this->betweenness[node->nodeThatRepresents->id]=this->betweenness[node->nodeThatRepresents->id]+valueToPass;
//                
//            }
//            if ((node->parent)!=NULL&&node->parent->numChildren>node->parent->numChildrenThatReachedMe+1)
//            {
//                double valueToPass=node->valueToPass+node->parent->valueToPass;
//                //					node=(node->parent);
//                node->parent->valueToPass=valueToPass;
//                node->parent->numChildrenThatReachedMe++;
//                
//            }
//            //		   else if (node->parent==NULL){
//            //               std::cout<<leaves.size()<<'\n';
//            //		   }
//            
//        }
//    }
//    if (calculateOtherDistances)
//    {
//        for (int j=0; j<numberDistances; j++)
//        {
//            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
//            {
//                leaves.clear();
//                CompareFunc<Node*> compare=CompareFunc<Node*> (j,2);
//                std::sort(orderedCutoff.begin(),orderedCutoff.end(),compare);
//                std::vector<Node*> leaves;
//                int i=0;
//                while(orderedCutoff[i]->numOtherChildren[j]==0&&i<orderedCutoff.size())
//                {
//                    leaves.push_back(orderedCutoff[i]);
//                    i++;
//                }
//                
//                for (long i=0; i<leaves.size(); i++)
//                {
//                    Node* node=leaves[i];
////                    node->valuesToPass[j]=1;
//                    this->betweennessMeasures[j][node->nodeThatRepresents->id]=this->betweennessMeasures[j][node->nodeThatRepresents->id]+node->valuesToPass[j];
//                    
//                    while((node->otherParents[j])!=NULL&&node->otherParents[j]->numOtherChildren[j]==node->otherParents[j]->numOtherChildrenThatReachedMe[j]+1)
//                    {
//                        double valueToPass=node->valuesToPass[j]+node->otherParents[j]->valuesToPass[j];
//                        node=(node->otherParents[j]);
//                        //						if (node->otherParents[j]==NULL){
//                        //							std::cout<<"null";
//                        //						}
//                        node->valuesToPass[j]=valueToPass;
//                        node->numOtherChildrenThatReachedMe[j]++;
//                        if (node->nodeThatRepresents->id<0||node->nodeThatRepresents->id>=(betweennessMeasures[j].size()))
//                        {
//                            std::cout<<"problema";
//                        }
//                        this->betweennessMeasures[j][node->nodeThatRepresents->id]=this->betweennessMeasures[j][node->nodeThatRepresents->id]+valueToPass;
//                        
//                    }
//                    if ((node->otherParents[j])!=NULL&&node->otherParents[j]->numOtherChildren[j]>node->otherParents[j]->numOtherChildrenThatReachedMe[j]+1)
//                    {
//                        double valueToPass=node->valuesToPass[j]+node->otherParents[j]->valuesToPass[j];
//                        //					node=(node->parent);
//                        node->otherParents[j]->valuesToPass[j]=valueToPass;
//                        node->otherParents[j]->numOtherChildrenThatReachedMe[j]++;
//                        
//                    }
//                    
//                }
//            }
//            else
//            {
//                for (long i=0; i<betweenness.size(); i++)
//                {
//                    
//                    this->betweennessMeasures[j][i]=this->betweenness[i];
//                    
//                }
//            }
//        }
//    }
//    
//    
//    
//    for(long i=0; i<orderedCutoff.size(); i++)
//    {
//        delete orderedCutoff[i];
//    }
//    
//    orderedCutoff.clear();
//    std::vector<Node*>().swap(orderedCutoff);
//    
//    
//}
void Graph::measureGlobalProperties(std::vector<Node*>  &orderedCutoff,std::vector<int> setOfDistancesToCalculate)
{
    
    
    for(int j=0;j<setOfDistancesToCalculate.size();j++){
        for(int h=0;h<indexOfDistancesByDistanceType[setOfDistancesToCalculate[j]].size();h++){
            double totalDistanceTemp=0;
            
            for (long i=0; i<orderedCutoff.size(); i++)
            {
                
                totalDistanceTemp+=orderedCutoff[i]->minOtherDistances[indexOfDistancesByDistanceType[setOfDistancesToCalculate[j]][h]];
                
                
                if (orderedCutoff[i]->minOtherDistances[getIndexesOfDistanceType(setOfDistancesToCalculate[j])[h]]>diameters[getIndexesOfDistanceType(setOfDistancesToCalculate[j])[h]])
                {
                    diameters[getIndexesOfDistanceType(setOfDistancesToCalculate[j])[h]]=orderedCutoff[i]->minOtherDistances[getIndexesOfDistanceType(setOfDistancesToCalculate[j])[h]];
                    
                }
                
                
                
                
                
            }
            if (orderedCutoff.size()>0)
            {
                
                totalLengths[indexOfDistancesByDistanceType[setOfDistancesToCalculate[j]][h]]+=totalDistanceTemp/(double)(orderedCutoff.size());
                
                
            }
        }
    }
    
}
void Graph::measureGlobalProperties(std::vector<Node*>  &orderedCutoff,std::vector<int> setOfDistancesToCalculate,int indexDistanceInSet)
{
    
    
//    for(int j=0;j<setOfDistancesToCalculate.size();j++){
//        for(int h=0;h<indexOfDistancesByDistanceType[setOfDistancesToCalculate[indexDistanceInSet]].size();h++){
//    int h=
//    {
            double totalDistanceTemp=0;
            
            for (long i=0; i<orderedCutoff.size(); i++)
            {
                
                totalDistanceTemp+=orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexDistanceInSet]];
                
                
                if (orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexDistanceInSet]]<INFINITY&&orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexDistanceInSet]]>diameters[setOfDistancesToCalculate[indexDistanceInSet]])
                {
                    diameters[setOfDistancesToCalculate[indexDistanceInSet]]=orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexDistanceInSet]];
//                    std::cout<<"idDestination "<<orderedCutoff[i]->id<<'\n';
                }
                
                
                
                
                
            }
            if (orderedCutoff.size()>0)
            {
                
                totalLengths[setOfDistancesToCalculate[indexDistanceInSet]]+=totalDistanceTemp/(double)(orderedCutoff.size());
                
                
            }
//        }
//    }
    
}
void Graph::makeCalculationsSpeed(Node* &nodeInit,std::vector<Node*>  &orderedCutoff)
{
    
    //std::cout<<"geh";
    
    //    std::vector<Node*> orderedCutoff=nodesCutoff;
    double closenessTemp=0;
    double TSLtemp=0;
    double nodeCountTemp=orderedCutoff.size();
    if (calculateTSL)
    {
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            TSLtemp=TSLtemp+metricLengths[orderedCutoff[i]->id];
        }
         this->TSL[nodeInit->id]=TSLtemp;
    }
    
    if (calculateMainDistance)
    {
        
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            closenessTemp=closenessTemp+orderedCutoff[i]->minDistance*orderedCutoff[i]->mass*nodeInit->mass;
        }
        
        
    }
    
    //    if (orderedCutoff.size()<10){
    //        for(int i=0;i<orderedCutoff.size();i++){
    //            cout<<orderedCutoff[i]->originalID;
    //        }
    //    }
    std::vector<double> closenessTempOtherDistance;
    if (calculateOtherDistances)
    {
        for (int j=0; j<numberDistances; j++)
        {
            closenessTempOtherDistance.push_back(0);
            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
            {
                for (long i=0; i<orderedCutoff.size(); i++)
                {
                    //                    if(orderedCutoff[i]->transitions.size()>2||orderedCutoff[i]->numChildren==0){
                    if(orderedCutoff[i]->minOtherDistances[j]<INFINITY){
                        closenessTempOtherDistance[j]=closenessTempOtherDistance[j]+orderedCutoff[i]->minOtherDistances[j]*orderedCutoff[i]->mass*nodeInit->mass;
                    }
                    //                    }
                }
            }
            else
            {
                closenessTempOtherDistance[j]=closenessTemp;
            }
        }
    }
    
    
    this->nodeCount[nodeInit->id]=nodeCountTemp;
  
    this->closeness[nodeInit->id]=closenessTemp;
    if (calculateOtherDistances)
    {
        for (int j=0; j<numberDistances; j++)
        {
            this->closenessMeasures[j][nodeInit->id]=closenessTempOtherDistance[j];
        }
    }
    
    //    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,2);
    //////////////////////////////////////////////
    std::vector<Node*> leaves;
    if (calculateMainDistance&&calculateBetweenness)
    {
        std::sort(orderedCutoff.begin(),orderedCutoff.end(),&compareByNumChildren);
        //              std::cout<<'\n';
        //    for(int i=0;i<orderedCutoff.size();i++){
        //        std::cout<<orderedCutoff[i]->numChildren;
        //    }
        
        int i=0;
        while(i<orderedCutoff.size()&&orderedCutoff[i]->numChildren==0)
        {
            leaves.push_back(orderedCutoff[i]);
            i++;
        }
        //    std::cout<<leaves.size()<<'\n';
//        for (long i=0; i<leaves.size(); i++)
//        {
//            Node* node=leaves[i];
////            node->valueToPass=1;
//            this->betweenness[node->id]=this->betweenness[node->id]+node->valueToPass;
//            //            long valueToPass;
//            while((node->parent)!=NULL&&node->parent->numChildren==node->parent->numChildrenThatReachedMe+1)
//            {
//                double valueToPass=node->valueToPass+node->parent->valueToPass;
//                node=(node->parent);
//                node->valueToPass=valueToPass;
//                node->numChildrenThatReachedMe++;
//                //					if (node->id<0||node->id>=(betweenness.size())){
//                //						std::cout<<"problema";
//                //					}
//                this->betweenness[node->id]=this->betweenness[node->id]+valueToPass*nodeInit->population;
//                
//            }
//            if ((node->parent)!=NULL&&node->parent->numChildren>node->parent->numChildrenThatReachedMe+1)
//            {
//                double valueToPass=node->valueToPass+node->parent->valueToPass;
//                //					node=(node->parent);
//                node->parent->valueToPass=valueToPass;
//                node->parent->numChildrenThatReachedMe++;
//                
//            }
//            //		   else if (node->parent==NULL){
//            //               std::cout<<leaves.size()<<'\n';
//            //		   }
//            
//        }
        
        for (long i=0; i<leaves.size(); i++)
        {
            Node* node=leaves[i];
            
            
            while((node->parent)!=NULL&&node->parent->numChildren==node->parent->numChildrenThatReachedMe+1)
            {
                double valueToPass=0;
                
                valueToPass=node->valueToPass;
                
                node=(node->parent);
                
                
                node->numChildrenThatReachedMe++;
                if (node->id<0)
                {
                    std::cout<<"problema";
                }
                if(node!=nodeInit){
                    this->betweenness[node->id]=this->betweenness[node->id]+((valueToPass+node->valueToPass-node->originalValueToPass))*nodeInit->mass;
//                    std::cout<<"id: "<<node->originalID<<" bet "<<this->betweennessMeasures[j][node->id]<<" "<<node->originalValuesToPass[j]<<'\n';
                }
                node->valueToPass=valueToPass+node->valueToPass;
                
            }
            if ((node->parent)!=NULL&&node->parent->numChildren>node->parent->numChildrenThatReachedMe+1)
            {
                double valueToPass=node->valueToPass+node->parent->valueToPass;
                
                node->parent->valueToPass=valueToPass;
                node->parent->numChildrenThatReachedMe++;
                
            }
            
        }
    }
    if (calculateOtherDistances&&calculateBetweenness)
    {
        for (int j=0; j<numberDistances; j++)
        {
            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
            {
                leaves.clear();
                CompareFunc<Node*> compare=CompareFunc<Node*> (j,2);
                std::sort(orderedCutoff.begin(),orderedCutoff.end(),compare);
                std::vector<Node*> leaves;
                int i=0;
                while(i<orderedCutoff.size()&&orderedCutoff[i]->numOtherChildren[j]==0)
                {
                    leaves.push_back(orderedCutoff[i]);
                    i++;
                }
                
                for (long i=0; i<leaves.size(); i++)
                {
                    Node* node=leaves[i];
                    
                    
                    while((node->otherParents[j])!=NULL&&node->otherParents[j]->numOtherChildren[j]==node->otherParents[j]->numOtherChildrenThatReachedMe[j]+1)
                    {
                        double valueToPass=0;
                        
                        valueToPass=node->valuesToPass[j];
                        
                        node=(node->otherParents[j]);
                        
                        
                        node->numOtherChildrenThatReachedMe[j]++;
                        if (node->id<0||node->id>=(betweennessMeasures[j].size()))
                        {
                            std::cout<<"problema";
                        }
                        if(node!=nodeInit){
                            this->betweennessMeasures[j][node->id]=this->betweennessMeasures[j][node->id]+((valueToPass+node->valuesToPass[j]-node->originalValuesToPass[j]))*nodeInit->mass;
//                            std::cout<<"id: "<<node->originalID<<" bet "<<this->betweennessMeasures[j][node->id]<<" "<<node->originalValuesToPass[j]<<'\n';
                        }
                        node->valuesToPass[j]=valueToPass+node->valuesToPass[j];
                        
                    }
                    if ((node->otherParents[j])!=NULL&&node->otherParents[j]->numOtherChildren[j]>node->otherParents[j]->numOtherChildrenThatReachedMe[j]+1)
                    {
                        double valueToPass=node->valuesToPass[j]+node->otherParents[j]->valuesToPass[j];
                        
                        node->otherParents[j]->valuesToPass[j]=valueToPass;
                        node->otherParents[j]->numOtherChildrenThatReachedMe[j]++;
                        
                    }
                    
                }
            }
            else
            {
                for (long i=0; i<betweenness.size(); i++)
                {
                    
                    this->betweennessMeasures[j][i]=this->betweenness[i];
                    
                }
            }
        }
    }
    
    
    
    //    for(long i=0;i<orderedCutoff.size();i++){
    //            delete orderedCutoff[i];
    //    }
    
    
}


void Graph::makeCalculationsSpeed(Node* &nodeInit,std::vector<Node*>  &orderedCutoff,std::vector<int> &setOfDistancesToCalculate,int indexOfDistanceInSet)
{
    double TSLtemp=0;
    double nodeCountTemp=orderedCutoff.size();
    this->nodeCount[nodeInit->id]=nodeCountTemp;
    if (calculateTSL)
    {
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            TSLtemp=TSLtemp+metricLengths[orderedCutoff[i]->id];
        }
         this->TSL[nodeInit->id]=TSLtemp;
    }
 
    std::vector<double> closenessTempOtherDistance;
//    if (calculateOtherDistances)
//    {
//        for (int j=0; j<setOfDistancesToCalculate.size(); j++)
//    int j=indexOfDistanceInSet;
        {
            closenessTempOtherDistance.push_back(0);
//            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
//            {
                for (long i=0; i<orderedCutoff.size(); i++)
                {
                    if(orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]<INFINITY){
                        closenessTempOtherDistance[0]=closenessTempOtherDistance[0]+orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]]*orderedCutoff[i]->mass*nodeInit->mass;
                    }

                }
//            }
//            else
//            {
//                closenessTempOtherDistance[j]=closenessTemp;
//            }
        }
//    }
    
    
   
//    if (calculateOtherDistances)
//    {
//        for (int j=0; j<setOfDistancesToCalculate.size(); j++)
        {
            this->closenessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][nodeInit->id]=closenessTempOtherDistance[0];
        }
//    }

    if(customize.useGeneratedAndAttractedTrips){
        
        
        double sumTrips=1;
        sumTrips=0;
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            double tripsAttracted=0;
            double euclideanDistance=Functions::getDistance(nodeInit->location, orderedCutoff[i]->location);
            
            for(long h=0;h<orderedCutoff[i]->customizedAttractedTrips.size();h++){
                double value=customize.applyDistributionDistancesByMode(orderedCutoff[i]->customizedAttractedTrips[h][0], euclideanDistance);
                tripsAttracted+=value*orderedCutoff[i]->customizedAttractedTrips[h][1];
            }
            sumTrips+=tripsAttracted;
//            double tripsGenerated=nodeInit->customizedGeneratedTrips[0][1];
            //            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=tripsAttracted;
//            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=(tripsAttracted+1)*tripsGenerated;
        }
        if(sumTrips==0){
            sumTrips=1;
        }
        if(sumTrips>0){
        
        
            for (long i=0; i<orderedCutoff.size(); i++)
            {
                double tripsAttracted=0;
                double euclideanDistance=Functions::getDistance(nodeInit->location, orderedCutoff[i]->location);
               
                for(long h=0;h<orderedCutoff[i]->customizedAttractedTrips.size();h++){
                    double value=customize.applyDistributionDistancesByMode(orderedCutoff[i]->customizedAttractedTrips[h][0], euclideanDistance);

                    tripsAttracted+=value*orderedCutoff[i]->customizedAttractedTrips[h][1];
//                    std::cout<<"value "<<value<<" distance "<<euclideanDistance<<" trips attracted "<<orderedCutoff[i]->customizedAttractedTrips[h][1]<<" type "<<orderedCutoff[i]->customizedAttractedTrips[h][0]<<'\n';
                }
                double tripsGenerated=0;
                if(nodeInit->customizedGeneratedTrips.size()>0){
                 tripsGenerated=nodeInit->customizedGeneratedTrips[0][1];
                }
                
//                if(tripsGenerated>0){
//                    tripsGenerated=1;
//                }
//                if(tripsAttracted>0){
//                    tripsAttracted=1;
//                }
                
//                tripsAttracted=1;
//                tripsGenerated=1;
                
                
    //            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=tripsAttracted;
                orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=((tripsAttracted)/sumTrips)*tripsGenerated+nodeInit->tripsReceivedFromNodeByID[orderedCutoff[i]->originalID];
                
//                std::cout<<orderedCutoff[i]->originalID<<"->"<<nodeInit->originalID<<" trips received from node "<<nodeInit->tripsReceivedFromNodeByID[orderedCutoff[i]->originalID]<<'\n';
                orderedCutoff[i]->originalValuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=((tripsAttracted)/sumTrips)*tripsGenerated+nodeInit->tripsReceivedFromNodeByID[orderedCutoff[i]->originalID];
            }
        }else{
            for (long i=0; i<orderedCutoff.size(); i++)
            {
                orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=0;
            }
        }
        
        
       
    }else if(customize.useDistributionDistances){
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            double euclideanDistance=Functions::getDistance(nodeInit->location, orderedCutoff[i]->location);
            double value=customize.applyDistributionDistancesByMode(1, euclideanDistance);
            orderedCutoff[i]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]*=value;
        }
    }

    std::vector<Node*> leaves;

//    if (calculateOtherDistances)
//    {
//        for (int j=0; j<setOfDistancesToCalculate.size(); j++)
        {
//            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
//            {
                leaves.clear();
                CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[indexOfDistanceInSet],2);
                std::sort(orderedCutoff.begin(),orderedCutoff.end(),compare);
                std::vector<Node*> leaves;
            
                int i=0;
                while(i<orderedCutoff.size()&&orderedCutoff[i]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]==0)
                {
                    
                    leaves.push_back(orderedCutoff[i]);
                    i++;
                }
                
                for (long i=0; i<leaves.size(); i++)
                {
                    Node* node=leaves[i];

                    
                    while((node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]])!=NULL&&node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]==node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]+1)
                    {
                        double valueToPass=0;

                        valueToPass=node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]];

                        
                        if (node->id<0||node->id>=(betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]].size()))
                        {
                            std::cout<<"problema";
                        }
                        Node* parent=node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]];
                        if(parent!=nodeInit){
                            double d0=1;
                            
//                            double distanceNetworkNode=node->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]];
//                            double distanceNetworkParent=parent->minOtherDistances[setOfDistancesToCalculate[indexOfDistanceInSet]];
                            double euclideanDistanceNode=Functions::getDistance(node->location, nodeInit->location);
                            double euclideanDistanceParent=Functions::getDistance(node->location, nodeInit->location);
                            
                            double gaussianDistanceNode;
                     
                            double gaussianDistanceParent;
                
                            //I AM CURRENTLY NOT USING THE GAUSSIAN BETWEENNESS
                            if(useGaussianBetweenness){
                                gaussianDistanceNode=1/(1+pow(euclideanDistanceNode/d0,2));
                                gaussianDistanceParent=1/(1+pow(euclideanDistanceParent/d0,2));

                            }else{
                                gaussianDistanceNode=1;
                                gaussianDistanceParent=1;
                            }
                            
                            this->betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][parent->id]=this->betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][parent->id]+(gaussianDistanceNode*(valueToPass)+gaussianDistanceParent*(parent->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]-parent->originalValuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]))*nodeInit->mass;
//                            std::cout<<"id: "<<node->originalID<<" bet "<<this->betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][node->id]<<" "<<node->originalValuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]<<'\n';
                        }
                        node=(node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]);
                        
                        
                        node->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]++;
                        node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=valueToPass+node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]];
                        
                    }
                    if ((node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]])!=NULL&&node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]>node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]+1)
                    {
                        double valueToPass=node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]+node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]];

                        node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=valueToPass;
                        node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]++;
                        
                    }
                    
                }

        }

    
    

    
}

void Graph::makeCalculationsSpeed(Node* &nodeInit,std::vector<Node*>  &orderedCutoff,std::vector<int> &setOfDistancesToCalculate)
{
    double TSLtemp=0;
    double nodeCountTemp=orderedCutoff.size();
    this->nodeCount[nodeInit->id]=nodeCountTemp;
    if (calculateTSL)
    {
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            TSLtemp=TSLtemp+metricLengths[orderedCutoff[i]->id];
        }
         this->TSL[nodeInit->id]=TSLtemp;
    }
    
    std::vector<double> closenessTempOtherDistance;
    //    if (calculateOtherDistances)
    //    {
            for (int j=0; j<setOfDistancesToCalculate.size(); j++)
//    int j=indexOfDistanceInSet;
    {
        closenessTempOtherDistance.push_back(0);
        //            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
        //            {
        for (long i=0; i<orderedCutoff.size(); i++)
        {
            if(orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[j]]<INFINITY){
                closenessTempOtherDistance[j]=closenessTempOtherDistance[j]+orderedCutoff[i]->minOtherDistances[setOfDistancesToCalculate[j]]*orderedCutoff[i]->mass*nodeInit->mass;
            }
            
        }
        //            }
        //            else
        //            {
        //                closenessTempOtherDistance[j]=closenessTemp;
        //            }
    }
    //    }
    
    
    
    //    if (calculateOtherDistances)
    //    {
            for (int j=0; j<setOfDistancesToCalculate.size(); j++)
    {
        this->closenessMeasures[setOfDistancesToCalculate[j]][nodeInit->id]=closenessTempOtherDistance[j];
    }
    //    }
    
    
    std::vector<Node*> leaves;
    
    //    if (calculateOtherDistances)
    //    {
            for (int j=0; j<setOfDistancesToCalculate.size(); j++)
    {
        //            if (j!=this->indexOfMainDistanceInOtherDistances||!calculateMainDistance)
        //            {
        leaves.clear();
        CompareFunc<Node*> compare=CompareFunc<Node*> (setOfDistancesToCalculate[j],2);
        std::sort(orderedCutoff.begin(),orderedCutoff.end(),compare);
        std::vector<Node*> leaves;
        int i=0;
        while(i<orderedCutoff.size()&&orderedCutoff[i]->numOtherChildren[setOfDistancesToCalculate[j]]==0)
        {
            leaves.push_back(orderedCutoff[i]);
            i++;
        }
        
//        for (long i=0; i<leaves.size(); i++)
//        {
//            Node* node=leaves[i];
////            node->valuesToPass[setOfDistancesToCalculate[j]]=1;
//            this->betweennessMeasures[setOfDistancesToCalculate[j]][node->id]=this->betweennessMeasures[setOfDistancesToCalculate[j]][node->id]+node->valuesToPass[setOfDistancesToCalculate[j]];
//            double valueToPassTemp=node->valuesToPass[setOfDistancesToCalculate[j]];
//            
//            while((node->otherParents[setOfDistancesToCalculate[j]])!=NULL&&node->otherParents[setOfDistancesToCalculate[j]]->numOtherChildren[setOfDistancesToCalculate[j]]==node->otherParents[setOfDistancesToCalculate[j]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[j]]+1)
//            {
//                double valueToPass=0;
//                valueToPass=node->valuesToPass[setOfDistancesToCalculate[j]]+node->otherParents[setOfDistancesToCalculate[j]]->valuesToPass[setOfDistancesToCalculate[j]]+valueToPassTemp;
//                valueToPassTemp=0;
//                node=(node->otherParents[setOfDistancesToCalculate[j]]);
//                //						if (node->otherParents[j]==NULL){
//                //							std::cout<<"null";
//                //						}
//                node->valuesToPass[setOfDistancesToCalculate[j]]=valueToPass;
//                node->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[j]]++;
//                if (node->id<0||node->id>=(betweennessMeasures[setOfDistancesToCalculate[j]].size()))
//                {
//                    std::cout<<"problema";
//                }
//                this->betweennessMeasures[setOfDistancesToCalculate[j]][node->id]=this->betweennessMeasures[setOfDistancesToCalculate[j]][node->id]+valueToPass*nodeInit->population;
//                
//            }
//            if ((node->otherParents[setOfDistancesToCalculate[j]])!=NULL&&node->otherParents[setOfDistancesToCalculate[j]]->numOtherChildren[setOfDistancesToCalculate[j]]>node->otherParents[setOfDistancesToCalculate[j]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[j]]+1)
//            {
//                double valueToPass=node->valuesToPass[setOfDistancesToCalculate[j]]+node->otherParents[setOfDistancesToCalculate[j]]->valuesToPass[setOfDistancesToCalculate[j]];
//                //					node=(node->parent);
//                node->otherParents[setOfDistancesToCalculate[j]]->valuesToPass[setOfDistancesToCalculate[j]]=valueToPass;
//                node->otherParents[setOfDistancesToCalculate[j]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[j]]++;
//                
//            }
//            
//        }
        
        for (long i=0; i<leaves.size(); i++)
        {
            Node* node=leaves[i];
            int indexOfDistanceInSet=j;
            
            while((node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]])!=NULL&&node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]==node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]+1)
            {
                double valueToPass=0;
                
                valueToPass=node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]];
                
                node=(node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]);
                
                
                node->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]++;
                if (node->id<0||node->id>=(betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]].size()))
                {
                    std::cout<<"problema";
                }
                if(node!=nodeInit){
                    this->betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][node->id]=this->betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][node->id]+((valueToPass+node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]-node->originalValuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]))*nodeInit->mass;
//                    std::cout<<"id: "<<node->originalID<<" bet "<<this->betweennessMeasures[setOfDistancesToCalculate[indexOfDistanceInSet]][node->id]<<" "<<node->originalValuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]<<'\n';
                }
                node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=valueToPass+node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]];
                
            }
            if ((node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]])!=NULL&&node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildren[setOfDistancesToCalculate[indexOfDistanceInSet]]>node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]+1)
            {
                double valueToPass=node->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]+node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]];
                
                node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->valuesToPass[setOfDistancesToCalculate[indexOfDistanceInSet]]=valueToPass;
                node->otherParents[setOfDistancesToCalculate[indexOfDistanceInSet]]->numOtherChildrenThatReachedMe[setOfDistancesToCalculate[indexOfDistanceInSet]]++;
                
            }
            
        }
        
        
        //            }
        //            else
        //            {
        //                for (long i=0; i<betweenness.size(); i++)
        //                {
        //
        //                    this->betweennessMeasures[j][i]=this->betweenness[i];
        //
        //                }
        //            }
    }
    //    }
    
    
    
    
}

void Graph::calculateDiffusionAlgorithm(int indexDistance,long startNode,long endNode)
{
    double maxWeight=0.0;
    double tick=.2;
    //    for (long i=0;i<nodes.size();i++){
    //        for(long j=0;j<nodes[i].transitions.size();j++){
    //            if (nodes[i].transitions[j].otherWeights[indexDistance]>maxWeight){
    //                maxWeight=log(nodes[i].transitions[j].otherWeights[indexDistance]+1);
    //            }
    //        }
    //    }
    maxWeight=1.0;
    double leak=0.1;
    double fluidity=1.0;
    double exponent=-.75;
    double limit=0.0001;
    std::vector<Node*> nodesWithWater;
    for(long i=startNode; i<endNode; i++)
    {
        nodes[i].inNodesWithWater=true;
        nodes[i].waterLevel.level=1;
        nodesWithWater.push_back(&nodes[i]);
    }
    while(nodesWithWater.size()>0)
    {
        Node* node=nodesWithWater[nodesWithWater.size()-1];
        if (node->waterLevel.level<=limit)
        {
            nodesWithWater.pop_back();
            node->inNodesWithWater=false;
        }
        else
        {
            
            double waterToPass=std::min(tick,node->waterLevel.level)-leak;
            node->waterLevel.flow+=waterToPass;
            double capacity=0.0;
            for(long j=0; j<node->transitions.size(); j++)
            {
                capacity+=pow(fluidity*node->transitions[j]->otherWeights[indexDistance]/maxWeight,exponent);
            }
            if (waterToPass>capacity)
            {
                //                node->waterLevel.spilled+=waterToPass-capacity;
                //                node->waterLevel.level+=waterToPass-capacity;
                //                waterToPass=capacity;
            }
            //            waterToPass=std::max(waterToPass,capacity);
            for(long j=0; j<node->transitions.size(); j++)
            {
                double capacityTemp=pow(fluidity*node->transitions[j]->otherWeights[indexDistance]/maxWeight,exponent);
                //                std::max(0,1);
                double value=std::max((waterToPass*capacityTemp/capacity),0.0);
                node->transitions[j]->b->waterLevel.level+=value;
                if (!node->transitions[j]->b->inNodesWithWater)
                {
                    nodesWithWater.push_back(node->transitions[j]->b);
                    node->transitions[j]->b->inNodesWithWater=true;
                }
            }
            node->waterLevel.level-=waterToPass;
        }
    }
    
}
void Graph::calculateDiffusionAlgorithmAux(int indexDistance)
{
    
}

void Graph::AStar(Node* a,Node* b,std::vector<Node*> &visitedNodes,double (*function)(Node*,Node*))
{
    if (a==b)
    {
        visitedNodes.push_back(a);
        visitedNodes.push_back(b);
        a->minDistance=0;
        b->minDistance=0;
        return;
    }
    //    visitedNodes.push_back(a);
    visitedNodes.push_back(b);
    //    BST<Node*> pathNodesById;
    double currentPathWeight=0;
    MinHeap<Node*> bestNodes;
    
    Node* node=a;
    node->minDistance=0;
    double heuristicDistanceToGoal=function(node,b);
    node->heuristicDistanceToGoal=heuristicDistanceToGoal;
    bestNodes.push(node, &compareByDistanceAndHeuristic);
    bool reached=false;
    bool insertInBestNodes;
    
    while(bestNodes.size()>0)
    {
        
        
        node=bestNodes.pop(&compareByDistanceAndHeuristic);
        
        node->inAStar=false;
        if (!node->inVisitedNodes)
        {
            node->inVisitedNodes=true;
            visitedNodes.push_back(node);
        }
        if (node->minDistance+node->heuristicDistanceToGoal<b->minDistance)
        {
            
            currentPathWeight=node->minDistance;
            if (node!=b)
            {
                for(int i=0; i<node->transitions.size(); i++)
                {
                    
                    Node* nodeTemp=node->transitions[i]->b;
                    if (nodeTemp==NULL)
                    {
                        nodeTemp=&(this->nodes[node->transitions[i]->idB]);
                    }
                    
                    if (!nodeTemp->inVisitedNodes)
                    {
                        nodeTemp->inVisitedNodes=true;
                        visitedNodes.push_back(nodeTemp);
                    }
                    
                    //                    if (node->transitions[i].weight==INFINITY){
                    //                        std::cout<<"mal hecha la transicion horizontal en Graph::"<<'\n';
                    //                    }
                    double possiblePathWeight=currentPathWeight+node->transitions[i]->weight;
                    
                    
                    insertInBestNodes=false;
//                    std::cout<<"in astar in graph "<<nodeTemp->minDistance<<" "<<possiblePathWeight<<'\n';
                    
                    if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance)
                    {
                        nodeTemp->minDistance=possiblePathWeight;
                        nodeTemp->parent=node;
                        insertInBestNodes=true;
                        
                    }
                    
                    if (!nodeTemp->inAStar&&insertInBestNodes)
                    {
                        //                        if (!nodeTemp->inDijkstra){
                        double heuristicDistanceToGoal=function(nodeTemp,b);
                        nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                        nodeTemp->inAStar=true;
                        bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
                        
                        
                    }
                    else if (insertInBestNodes)
                    {
                        bestNodes.buildHeap(&compareByDistanceAndHeuristic);
                    }
                    if (nodeTemp==b)
                    {
                        reached=true;
                    }
                    
                }
            }
        }
        
    }
    
    
}


double Graph::AStar(Node* a,Node* b,double (*function)(Node*,Node*))
{
    double distanceResult=INFINITY;
    std::vector<Node*> visitedNodes;
    if (a==b)
    {
        
        return 0;
    }
    //    visitedNodes.push_back(a);
    visitedNodes.push_back(b);
    //    BST<Node*> pathNodesById;
    double currentPathWeight=0;
    MinHeap<Node*> bestNodes;
    
    Node* node=a;
    node->minDistance=0;
    double heuristicDistanceToGoal=function(node,b);
    node->heuristicDistanceToGoal=heuristicDistanceToGoal;
    bestNodes.push(node, &compareByDistanceAndHeuristic);
    bool reached=false;
    bool insertInBestNodes;
    
    while(bestNodes.size()>0)
    {
        
        
        node=bestNodes.pop(&compareByDistanceAndHeuristic);
        
        node->inAStar=false;
        if (!node->inVisitedNodes)
        {
            node->inVisitedNodes=true;
            visitedNodes.push_back(node);
        }
        if (node->minDistance+node->heuristicDistanceToGoal<b->minDistance)
        {
            
            currentPathWeight=node->minDistance;
            if (node!=b)
            {
                for(int i=0; i<node->transitions.size(); i++)
                {
                    
                    Node* nodeTemp=node->transitions[i]->b;
                    if (nodeTemp==NULL)
                    {
                        nodeTemp=&(this->nodes[node->transitions[i]->idB]);
                    }
                    
                    if (!nodeTemp->inVisitedNodes)
                    {
                        nodeTemp->inVisitedNodes=true;
                        visitedNodes.push_back(nodeTemp);
                    }
                    
                    //                    if (node->transitions[i].weight==INFINITY){
                    //                        std::cout<<"mal hecha la transicion horizontal en Graph::"<<'\n';
                    //                    }
                    double possiblePathWeight=currentPathWeight+node->transitions[i]->weight;
                    
                    
                    insertInBestNodes=false;
                    
                    if (nodeTemp->minDistance==INFINITY||possiblePathWeight<=nodeTemp->minDistance)
                    {
                        nodeTemp->minDistance=possiblePathWeight;
                        nodeTemp->parent=node;
                        insertInBestNodes=true;
                        
                    }
                    
                    if (!nodeTemp->inAStar&&insertInBestNodes)
                    {
                        //                        if (!nodeTemp->inDijkstra){
                        double heuristicDistanceToGoal=function(nodeTemp,b);
                        nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                        nodeTemp->inAStar=true;
                        bestNodes.push(nodeTemp, &Graph::compareByDistanceAndHeuristic);
                        
                        
                    }
                    else if (insertInBestNodes)
                    {
                        bestNodes.buildHeap(&compareByDistanceAndHeuristic);
                    }
                    if (nodeTemp==b)
                    {
                        reached=true;
                    }
                    
                }
            }
        }
        
    }
    distanceResult=b->minDistance;
    for(long h=0; h<visitedNodes.size(); h++)
    {
        
        visitedNodes[h]->minDistance=INFINITY;
        visitedNodes[h]->inAStar=false;
        visitedNodes[h]->inVisitedNodes=false;
        visitedNodes[h]->parent=NULL;
        
    }
    visitedNodes.clear();
    return distanceResult;
}


std::vector<double> Graph::AStarOtherWeights(Node* a,Node* b,std::vector<int> setOfDistancesToCalculate,double (*function)(Node*,Node*))
{
    //    double distanceResult=INFINITY;
    std::vector<double> results;
    
    
    if (a==b)
    {
        for(long i=0; i<numberDistances; i++)
        {
            results.push_back(0);
        }
        return results;
    }
    //    visitedNodes.push_back(a);
    for(long i=0; i<setOfDistancesToCalculate.size(); i++)
    {
        CompareFunc<Node*> compare=CompareFunc<Node*> ((int)setOfDistancesToCalculate[i],CompareFunc<Node*>::BY_DISTANCE_AND_HEURISTIC);
        
        std::vector<Node*> visitedNodes;
        visitedNodes.push_back(b);
        //    BST<Node*> pathNodesById;
        double currentPathWeight=0;
        MinHeap<Node*> bestNodes;
        
        Node* node=a;
        node->minOtherDistances[setOfDistancesToCalculate[i]]=0;
        double heuristicDistanceToGoal=function(node,b);
        node->heuristicDistanceToGoal=heuristicDistanceToGoal;
        bestNodes.push(node, compare);
        bool reached=false;
        bool insertInBestNodes;
        
        while(bestNodes.size()>0)
        {
            
            
            node=bestNodes.pop(compare);
            
            node->inAStar=false;
            if (!node->inVisitedNodes)
            {
                node->inVisitedNodes=true;
                visitedNodes.push_back(node);
            }
            if (node->minOtherDistances[setOfDistancesToCalculate[i]]+node->heuristicDistanceToGoal<b->minOtherDistances[setOfDistancesToCalculate[i]])
            {
                
                currentPathWeight=node->minOtherDistances[setOfDistancesToCalculate[i]];
                if (node!=b)
                {
                    for(int j=0; j<node->transitions.size(); j++)
                    {
                        
                        Node* nodeTemp=node->transitions[j]->b;
                        if (nodeTemp==NULL)
                        {
                            nodeTemp=&(this->nodes[node->transitions[j]->idB]);
                        }
                        
                        if (!nodeTemp->inVisitedNodes)
                        {
                            nodeTemp->inVisitedNodes=true;
                            visitedNodes.push_back(nodeTemp);
                        }
                        
                        //                        if (node->transitions[i].otherWeights[i]==INFINITY){
                        //                            std::cout<<"mal hecha la transicion horizontal en Graph::"<<'\n';
                        //                        }
                        double possiblePathWeight=currentPathWeight+node->transitions[j]->otherWeights[setOfDistancesToCalculate[i]];
                        
                        
                        insertInBestNodes=false;
                        
                        if (nodeTemp->minOtherDistances[setOfDistancesToCalculate[i]]==INFINITY||possiblePathWeight<=nodeTemp->minOtherDistances[setOfDistancesToCalculate[i]])
                        {
                            nodeTemp->minOtherDistances[setOfDistancesToCalculate[i]]=possiblePathWeight;
                            nodeTemp->otherParents[setOfDistancesToCalculate[i]]=node;
                            insertInBestNodes=true;
                            
                        }
                        
                        if (!nodeTemp->inAStar&&insertInBestNodes)
                        {
                            //                        if (!nodeTemp->inDijkstra){
                            double heuristicDistanceToGoal=function(nodeTemp,b);
                            nodeTemp->heuristicDistanceToGoal=heuristicDistanceToGoal;
                            nodeTemp->inAStar=true;
                            bestNodes.push(nodeTemp, compare);
                            
                            
                        }
                        else if (insertInBestNodes)
                        {
                            bestNodes.buildHeap(compare);
                        }
                        if (nodeTemp==b)
                        {
                            reached=true;
                        }
                        
                    }
                }
            }
            
        }
        results.push_back(b->minOtherDistances[setOfDistancesToCalculate[i]]);
        for(long h=0; h<visitedNodes.size(); h++)
        {
            
            visitedNodes[h]->minOtherDistances[setOfDistancesToCalculate[i]]=INFINITY;
            visitedNodes[h]->inAStar=false;
            visitedNodes[h]->inVisitedNodes=false;
            visitedNodes[h]->otherParents[setOfDistancesToCalculate[i]]=NULL;
            
        }
        visitedNodes.clear();
    }
    return results;
}

void Graph::calculateDijkstraSpeedToSetOfNodes(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra,std::vector<Node*> setOfNodes)
{
    
//    nodesToCheckDijkstra.heap[0]->minDistance=0;
    
    if(setOfNodes.size()==1&&setOfNodes[0]==nodeInit){
        
    }else{
    
        Heap<Node*> setOfNodesInOrder (Heap<Node*>::MAX,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true,1);
        BST<long> originalIds;
        for(long i=0; i<setOfNodes.size(); i++)
        {
            setOfNodesInOrder.push(setOfNodes[i]);
            originalIds.add(setOfNodes[i]->originalID,setOfNodes[i]->originalID);
        }
        
        while (nodesToCheckDijkstra.size() > 0)
        {
            //                Node* possibleNode=nodesToCheckDijkstra.pop(&compareByDistance);
            //        long idTemp=(possibleNode->id);
            
            //        Node* startNode = &(this->nodes[idTemp]);
            Node* startNode =nodesToCheckDijkstra.pop();
            startNode->inDijkstra=false;
            
            
            for (long i = 0; i < startNode->transitions.size(); i++)
            {
                Transition* trans = (startNode->transitions[i]);
                if (trans->a==trans->b)
                {
                    std::cout<<"loop!!!"<<'\n';
                }
                if(trans->weight==INFINITY)
                {
                    //                    std::cout<<"INFINITY!!"<<'\n';
                    
                }
                //                if (!trans.alreadyUsedDijkstra){
                //                    trans.alreadyUsedDijkstra=true;
                //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
                //                    bool addToDijkstra = false;
                
                Node* nodeB;
                
                bool nodeBSet=false;
                
                //                    bool alreadyInCutoff=false;
                if (trans->b!=NULL)
                {
                    nodeB=trans->b;
                }
                else
                {
                    nodeB=&(nodes[trans->idB]);
                }
                //                    idTemp=possibleNode->id;
                //                    Node* nodeB=&(this->nodes[idTemp]);
                
                if (nodeB->inCutoff)
                {
                    
                    //                        alreadyInCutoff=true;
                    
                    nodeBSet=true;
                }
                
                bool nullBecauseOfBacktracking=false;
    //            if(avoidBacktrackingInLineGraph){
    //                Transition* previousTrans=NULL;
    //                if(startNode->parent!=NULL){
    //                    for(long g=0;g<startNode->parent->transitions.size();g++){
    //                        if(startNode==startNode->parent->transitions[g]->b){
    //                            previousTrans=startNode->parent->transitions[g];
    //                        }
    //                    }
    //                    if(previousTrans->nodeInGraphAfterLineGraphGeneration==trans->nodeInGraphAfterLineGraphGeneration){
    //                        nullBecauseOfBacktracking=true;
    //                    }
    //                }
    //            }
                double possibleDistance=trans->weight + startNode->minDistance;
                
                if (!nullBecauseOfBacktracking&&(nodeB->minDistance==INFINITY||(possibleDistance) < nodeB->minDistance)&& (possibleDistance < distanceLimit||distanceLimit==0))
                {
                    double previousDistance=nodeB->minDistance;
                    if (!nodeBSet)
                    {
                        
                        //                            nodeB=trans->b->getCopy();
                        nodeB->inCutoff=true;
                        nodesCutoff.push_back(nodeB);
                    }
                    else
                    {
                        nodeB->parent->numChildren--;
                    }
                    nodeB->parent=startNode;
                    startNode->numChildren++;
                    
                    nodeB->minDistance=possibleDistance;
                    
                    if(originalIds.exist(nodeB->originalID))
                    {
                        //                            originalIds.get(nodeB->originalID)
                        setOfNodesInOrder.update(nodeB,previousDistance);
                        distanceLimit=setOfNodesInOrder.getRoot()->minDistance;
                        if (distanceLimit==INFINITY)
                        {
                            distanceLimit=0;
                        }else{
    //                        std::cout<<"distance limit "<<distanceLimit<<'\n';
                        }
                    }
                    //                        addToDijkstra=true;
                    //                        if (!alreadyInCutoff){
                    //
                    //
                    //                        }
                    
                    if (!nodeB->inDijkstra)
                    {
                        nodeB->inDijkstra=true;
                        nodesToCheckDijkstra.push(nodeB);
                        
                    }
                    else
                    {
                        nodesToCheckDijkstra.update(nodeB,previousDistance);
                    }
                    
                }
                //                 if (nodeB->minAngularDistance==-1||(trans.angularWeight + startNode->minAngularDistance) < nodeB->minAngularDistance) {
                //
                //                    nodeB->parentAngular=startNode;
                //
                //                    nodeB->minAngularDistance=trans.angularWeight + startNode->minAngularDistance;
                //                    addToDijkstra=true;
                //
                //                }
                //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
                //
                //                    nodeB->parentMetric=startNode;
                //
                //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
                //                    addToDijkstra=true;
                //
                //                }
                
                //                    if (addToDijkstra ) {
                //
                //                    }else {
                ////                        if (!alreadyInCutoff&&nodeB!=NULL){
                ////
                ////                            delete nodeB;
                ////                        }
                //                    }
                //                }
                
            }
            
        }
    }
    
}


void Graph::calculateDijkstraSpeedOtherDistancesToSetOfNodes(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra,std::vector<Node*> setOfNodes,int indexDistance,bool followCutoff)
{
    Heap<Node*> setOfNodesInOrder (Heap<Node*>::MAX,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    std::unordered_map<signed long long,signed long long> originalIds;
    CompareFunc<Node*> compare2=CompareFunc<Node*> (indexDistance,CompareFunc<Node*>::BYDISTANCE_INVERTED);
    for(long i=0; i<setOfNodes.size(); i++)
    {
        setOfNodesInOrder.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,indexDistance,CompareFunc<Node*>::BYDISTANCE_INVERTED);
        setOfNodesInOrder.push(setOfNodes[i]);
        originalIds[setOfNodes[i]->originalID]=setOfNodes[i]->originalID+1;
    }
    //    for(long i=0;i<numberDistances;i++){
    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//    nodesToCheckDijkstra.heap[0]->minOtherDistances[indexDistance]=0;
    
    
    
    while (nodesToCheckDijkstra.size() > 0)
    {
        //                Node* possibleNode=nodesToCheckDijkstra.pop(&compareByDistance);
        //        long idTemp=(possibleNode->id);
        
        //        Node* startNode = &(this->nodes[idTemp]);
        Node* startNode =nodesToCheckDijkstra.pop();
        startNode->inDijkstra=false;
        
        
        for (long i = 0; i < startNode->transitions.size(); i++)
        {
            Transition* trans = (startNode->transitions[i]);
            if (trans->a==trans->b)
            {
                std::cout<<"loop!!!"<<'\n';
            }
            if(trans->otherWeights[indexDistance]==INFINITY)
            {
                //                    std::cout<<"INFINITY!!"<<'\n';
                
            }
            //                if (!trans.alreadyUsedDijkstra){
            //                    trans.alreadyUsedDijkstra=true;
            //                    trans.equivalentTransitionInOtherDirection->alreadyUsedDijkstra=true;
            //                    bool addToDijkstra = false;
            
            Node* nodeB;
            
            bool nodeBSet=false;
            
            //                    bool alreadyInCutoff=false;
            if (trans->b!=NULL)
            {
                nodeB=trans->b;
            }
            else
            {
                nodeB=&(nodes[trans->idB]);
            }
            //                    idTemp=possibleNode->id;
            //                    Node* nodeB=&(this->nodes[idTemp]);
            
            if (nodeB->inCutoff)
            {
                
                //                        alreadyInCutoff=true;
                
                nodeBSet=true;
            }
            bool nullBecauseOfBacktracking=false;
            if(avoidBacktrackingInLineGraph){
                Transition* previousTrans=NULL;
                if(startNode->otherParents[indexDistance]!=NULL){
                    for(long g=0;g<startNode->otherParents[indexDistance]->transitions.size();g++){
                        if(startNode==startNode->otherParents[indexDistance]->transitions[g]->b){
                            previousTrans=startNode->otherParents[indexDistance]->transitions[g];
                        }
                    }
                    if(previousTrans->nodeInGraphAfterLineGraphGeneration==trans->nodeInGraphAfterLineGraphGeneration){
                        nullBecauseOfBacktracking=true;
                    }
                }
            }
            
            bool continueCalculation=true;
            if(followCutoff){
                if(!nodeB->inCutoff){
                    continueCalculation=false;
                }
            }
            double possibleDistance=trans->otherWeights[indexDistance] + startNode->minOtherDistances[indexDistance];
            
            if ((!nullBecauseOfBacktracking&&(nodeB->minOtherDistances[indexDistance]==INFINITY||(possibleDistance) < nodeB->minOtherDistances[indexDistance])&& (possibleDistance < distanceLimit||distanceLimit==0))&&continueCalculation)
            {
                double previousDistance=nodeB->minOtherDistances[indexDistance];
                if (!nodeBSet)
                {
                    
                    //                            nodeB=trans->b->getCopy();
                    nodeB->inCutoff=true;
                    nodesCutoff.push_back(nodeB);
                }
                if(nodeB->otherParents[indexDistance]!=NULL)
                {
                    nodeB->otherParents[indexDistance]->numChildren--;
                }
                nodeB->otherParents[indexDistance]=startNode;
                startNode->numChildren++;
                
                nodeB->minOtherDistances[indexDistance]=possibleDistance;
                
                if(originalIds[nodeB->originalID]-1!=-1)
                {
                    //                            originalIds.get(nodeB->originalID)
                    setOfNodesInOrder.update(nodeB,previousDistance);
                    double distanceLimitTemp;
                    if(setOfNodes.size()>0){
                        distanceLimitTemp=setOfNodesInOrder.getRoot()->minOtherDistances[indexDistance];
                    }else{
                        distanceLimitTemp=INFINITY;
                    }
                    if (distanceLimitTemp<INFINITY)
                    {
                        distanceLimit=distanceLimitTemp;
                    }
                }
                //                        addToDijkstra=true;
                //                        if (!alreadyInCutoff){
                //
                //
                //                        }
                
                if (!nodeB->inDijkstra)
                {
                    nodeB->inDijkstra=true;
                    nodesToCheckDijkstra.push(nodeB);
                    
                }
                else
                {
//                    if(nodeB->minOtherDistances[indexDistance]<nodesToCheckDijkstra.getMin(compare)->minOtherDistances[indexDistance]){
                        nodesToCheckDijkstra.update(nodeB,previousDistance);
//                    }
                }
                
            }
            //                 if (nodeB->minAngularDistance==-1||(trans.angularWeight + startNode->minAngularDistance) < nodeB->minAngularDistance) {
            //
            //                    nodeB->parentAngular=startNode;
            //
            //                    nodeB->minAngularDistance=trans.angularWeight + startNode->minAngularDistance;
            //                    addToDijkstra=true;
            //
            //                }
            //                if (nodeB->minMetricDistance==-1||(trans.metricWeight + startNode->minMetricDistance) < nodeB->minMetricDistance) {
            //
            //                    nodeB->parentMetric=startNode;
            //
            //                    nodeB->minMetricDistance=trans.metricWeight + startNode->minMetricDistance;
            //                    addToDijkstra=true;
            //
            //                }
            
            //                    if (addToDijkstra ) {
            //
            //                    }else {
            ////                        if (!alreadyInCutoff&&nodeB!=NULL){
            ////
            ////                            delete nodeB;
            ////                        }
            //                    }
            //                }
            
        }
        
    }
    //    }
    
    
}
void Graph::calculateDijkstraAllToAll(Graph* graph,std::vector<int> setOfDistancesToCalculate,long startNode,long endNode,double cutoffRadius, bool calculateMainDistance,bool calculateOtherDistances,bool calculateCentralities, bool calculateGlobalProperties,bool calculateDiffussion,std::vector<Node*> setOfDestinations)
{
    //    Graph* graph=this;
    //    graph->init();
    
    graph->calculateMainDistance=calculateMainDistance;
    graph->calculateOtherDistances=calculateOtherDistances;
    graph->calculateCentralities=calculateCentralities;
    graph->calculateGlobalProperties=calculateGlobalProperties;
    graph->calculateDiffussion=calculateDiffussion;
    //    graph->totalLengths[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
    //    graph->totalLengths[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=0;
    //    graph->diameters[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
    //    graph->diameters[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=0;
    //    for(int i=0;i<indexDistancesToCalculate.size();i++){
    //        if (indexAlpha==indexDistancesToCalculate[i]){
    //            graph->indexOfMainDistanceInOtherDistances=i;
    //            graph->calculateMainDistance=true;
    //        }
    //    }
    //    std::cout<<"START"<<'\n';
    
    if (graph->calculateCentralities||graph->calculateGlobalProperties)
    {
        for (long i=startNode; i<endNode; i++)
        {
            Node* nodeInit=&(graph->nodes[i]);
            if(setOfDestinations.size()==0){
                if(cutoffRadius!=0){
                    
                    graph->calculateShortestPathsSpeed(nodeInit,cutoffRadius,setOfDistancesToCalculate);
                }else{
                    graph->calculateShortestPathsSpeedNoCutoff(nodeInit,setOfDistancesToCalculate);
                }
            }else{
                if(cutoffRadius!=0){
                    
                    graph->calculateShortestPathsSpeedToSetOfDestinations(nodeInit,setOfDestinations,cutoffRadius,setOfDistancesToCalculate);
                    //                    calculateShortestPathsSpeedToSetOfDestinations(<#Node *&nodeInit#>, <#std::vector<Node *> setOfDestinations#>, <#double distanceLimit#>, <#std::vector<int> &setOfDistancesToCalculate#>)
                }else{
                    //                     graph->calculateShortestPathsSpeedToSetOfDestinations(nodeInit,setOfDestinations,0,setOfDistancesToCalculate);
                    graph->calculateShortestPathsSpeedNoCutoffToSetOfDestinations(nodeInit,setOfDestinations,setOfDistancesToCalculate);
                }
            }
            
        }
        //        for (long i=startNode; i<endNode; i++)
        //        {
        ////            if(graph->nodes[i].minOtherDistances.size()>0){
        //                graph->totalLengths[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]+=graph->nodes[i].minOtherDistances[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
        ////            }
        //            std::cout<<"tamano asdf "<<graph->nodes[i].minOtherDistances[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]<<'\n';
        //            graph->totalLengths[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]+=graph->nodes[i].minOtherDistances[graph->getIndexesOfDistanceType(Graph::METRIC)[0]];
        //        }
        //
        //        graph->averageLengths[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=graph->totalLengths[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]/(double)(endNode-startNode);
        //       graph->averageLengths[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]=graph->totalLengths[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]/(double)(endNode-startNode);
    }
    if (graph->calculateDiffussion)
    {
        graph->calculateDiffusionAlgorithm(5,startNode,endNode);
    }
    //    std::cout<<"END"<<'\n';
}



void Graph::calculateDiameterUsingMainDistance(bool precise,std::vector<Node*> &externalNodes,std::vector<Transition> &originDestinationPairs){
    for(long j=0;j<this->nodes.size();j++){
        
        Node* startNode=&this->nodes[j];
        std::vector<Node*> nodesCutoff;
        Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        nodesCutoff.push_back(startNode);
        startNode->inCutoff=true;
        nodesToCheckDijkstra.push(startNode);
        startNode->inDijkstra=true;
        startNode->minDistance=0;
        
        calculateDijkstraSpeed(startNode,0,nodesCutoff,nodesToCheckDijkstra);
        
        for(long i=0; i<nodesCutoff.size(); i++)
        {
            if(nodesCutoff[i]->minDistance>diameters[indexOfMainDistanceInOtherDistances]&&nodesCutoff[i]->minDistance<INFINITY){
                diameters[indexOfMainDistanceInOtherDistances]=nodesCutoff[i]->minDistance;
            }
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




void Graph::calculateDiameter(int typeOfDistance,bool parallel,bool calculateCentralitiesSimultaneously, bool precise,std::vector<Node*> &externalNodes,std::vector<Transition> &originDestinationPairs, bool withHeuristic,double (*function)(Node*,Node*))
{
    std::vector<int> setOfDistancesToCalculate=indexOfDistancesByDistanceType[typeOfDistance];
    calculateCentralities=calculateCentralitiesSimultaneously;
    //    int start = getMilliCount();
    std::vector<Graph> graphs;
    //    if(calculatediameter){
    //    double cutoffRadius=0;
    //    }
    calculateGlobalProperties=true;
    //    Graph mainGraph=*this;
    //  bool parallel=false;
    int numThreads=8;
    if (!parallel)
    {
        numThreads=0;
    }
    if(parallel)
    {
        for (int i=0; i<numThreads; i++)
        {
            Graph graph;
            graphs.push_back(graph);
        }
        
        for (int i=0; i<numThreads; i++)
        {
            graphs[i].resetGraph();
            copyGraph(this,&graphs[i],false);
            //            graphs[i].transformToBidirectional();
            
        }
        //        std::cout<<"graph copied"<<'\n';
    }
    
    
    
    
    if(!precise&&withHeuristic)
    {
        if(!parallel){
            for(long i=0; i<externalNodes.size(); i++)
            {
                for(long j=i; j<externalNodes.size(); j++)
                {
                    
                    Transition trans;
                    trans.a=externalNodes[i];
                    trans.b=externalNodes[j];
                    originDestinationPairs.push_back(trans);
                    
                }
            }
            
            for(long i=0; i<originDestinationPairs.size(); i++)
            {
                
                std::vector<double> results=AStarOtherWeights(originDestinationPairs[i].a,originDestinationPairs[i].b,setOfDistancesToCalculate,function);
                for(int j=0;j<setOfDistancesToCalculate.size();j++){
                    
                    if(diameters[indexOfDistancesByDistanceType[typeOfDistance][j]]<results[indexOfDistancesByDistanceType[typeOfDistance][j]]&&results[indexOfDistancesByDistanceType[typeOfDistance][j]]<INFINITY)
                    {
                        diameters[indexOfDistancesByDistanceType[typeOfDistance][j]]=results[indexOfDistancesByDistanceType[typeOfDistance][j]];
                        
                    }
                }
                
                
            }
        }else{
            std::vector<std::thread> threads;
            double numNodesPerThread=floor(originDestinationPairs.size()/numThreads);
            std::vector<Node*> setOfDestinations;
            for (int i=0; i<numThreads; i++)
            {
                
                long startNode=i*numNodesPerThread;
                long endNode=(i+1)*numNodesPerThread;
                if (i==numThreads-1)
                {
                    endNode=originDestinationPairs.size();
                }
                
                
                threads.push_back(std::thread(&Graph::toParallelizeCalculatingAStar,&graphs[i],&graphs[i],originDestinationPairs,startNode,endNode, typeOfDistance, function));
                
                
            }
            
            for(auto& thread : threads)
            {
                thread.join();
            }
        }
        
    }
    
    if(!precise&&!withHeuristic)
    {
        //        std::vector<Transition> originDestinationPairs;
        BST<Node*> uniqueNodesBST;
        
        for(long i=0; i<originDestinationPairs.size(); i++)
        {
            
            //                            if (!uniqueNodesBST.exist(originDestinationPairs[i].a->id)){
            uniqueNodesBST.add(originDestinationPairs[i].a->id,originDestinationPairs[i].a);
            
            
            //                            }else{
            //                            }
        }
        std::vector<Node*> uniqueNodes=uniqueNodesBST.getAll();
        //                     for(long i=0;i<uniqueNodes.size();i++){
        //
        //                     }
        
        //        std::cout<<"size unique nodes "<<uniqueNodes.size()<<'\n';
        //        calculateOtherDistances=true;
        //        diameters[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=0;
        if(!parallel){
            for(long i=0; i<uniqueNodes.size(); i++)
            {
                BST<Node*> uniqueNodesDestinations;
                for(long j=0; j<originDestinationPairs.size(); j++)
                {
                    if (originDestinationPairs[j].a==uniqueNodes[i])
                    {
                        uniqueNodesDestinations.add(originDestinationPairs[j].b->id,originDestinationPairs[j].b);
                    }
                }
                
                std::vector<Node*>uniqueDestinations=uniqueNodesDestinations.getAll();
                
                calculateDijkstraAllToAll(this,setOfDistancesToCalculate,uniqueNodes[i]->id,uniqueNodes[i]->id+1,0,true,true,calculateCentralitiesSimultaneously, true,false,uniqueDestinations);
                
                
                uniqueNodesDestinations.deleteAll();
            }
        }else{
            std::vector<std::thread> threads;
            double numNodesPerThread=floor(uniqueNodes.size()/numThreads);
            std::vector<Node*> setOfDestinations;
            for (int i=0; i<numThreads; i++)
            {
                
                long startNode=i*numNodesPerThread;
                long endNode=(i+1)*numNodesPerThread;
                if (i==numThreads-1)
                {
                    endNode=uniqueNodes.size();
                }
                std::vector<Node*> uniqueNodesTemp;
                for(long j=startNode;j<endNode;j++){
//                    std::cout<<"id de los nodos que meto "<<uniqueNodes[j]->id<<'\n';
                    uniqueNodesTemp.push_back(&graphs[i].nodes[uniqueNodes[j]->id]);
                }
                threads.push_back(std::thread(&Graph::toParallelizeCalculatingDiskstraToSetOfDestinations,&graphs[i],&graphs[i],uniqueNodesTemp,originDestinationPairs,setOfDistancesToCalculate,calculateCentralitiesSimultaneously));
                
                
            }
            
            for(auto& thread : threads)
            {
                thread.join();
            }
            //            toParallelizeCalculatingDiskstraToSetOfDestinations(<#std::vector<Node *> uniqueNodes#>, <#std::vector<Transition> originDestinationPairs#>, <#std::vector<int> setOfDistancesToCalculate#>, <#bool calculateCentralitiesSimultaneously#>)
        }
        //                    milliSecondsElapsed = getMilliSpan(start);
        //        std::cout<<"diameter topo calculated"<<'\n';
    }
    if(precise&&!withHeuristic)
    {
        //        int start = getMilliCount();
        if(parallel)
        {
            std::vector<std::thread> threads;
            double numNodesPerThread=floor(nodes.size()/numThreads);
            std::vector<Node*> setOfDestinations;
            for (int i=0; i<numThreads; i++)
            {
                
                long startNode=i*numNodesPerThread;
                long endNode=(i+1)*numNodesPerThread;
                if (i==numThreads-1)
                {
                    endNode=nodes.size();
                }
                
                threads.push_back(std::thread(&Graph::calculateDijkstraAllToAll,&(graphs[i]),&(graphs[i]),setOfDistancesToCalculate,startNode,endNode,0,false,true,calculateCentralitiesSimultaneously, true,false,setOfDestinations));
                //calculateDijkstraAllToAll(<#Graph *graph#>, <#std::vector<int> setOfDistancesToCalculate#>, <#long startNode#>, <#long endNode#>, <#double cutoffRadius#>, <#bool calculateMainDistance#>, <#bool calculateOtherDistances#>, <#bool calculateCentralities#>, <#bool calculateGlobalProperties#>, <#bool calculateDiffussion#>, <#std::vector<Node *> setOfDestinations#>)
                
            }
            
            for(auto& thread : threads)
            {
                thread.join();
            }
        }
        else
        {
//            Graph lineGraph;
//            lineGraph.strictlyDirectional=true;
//            this->createLineGraph(this,&lineGraph);
//            
//            Graph skeleton;
//            std::vector<Graph> clusters;
//            lineGraph.generateAngularPercolation(&lineGraph, 50, clusters, 0, false);
//            std::vector<double> values;
//            for(long j=0;j<clusters.size();j++){
//                values.push_back(clusters[j].nodes.size());
//            }
//            std::vector<long> orderClusters=Functions::getIndexesOfOrderedValues(values, false);
//            
//            for(long j=0;j<setOfDistancesToCalculate.size();j++){
//                std::vector<int> setOfDistancesTemp;
//                setOfDistancesTemp.push_back(clusters[orderClusters[0]].getIndexesOfDistanceType(typeOfDistance)[j]);
//                for(long i=0;i<clusters[orderClusters[0]].transitions.size();i++){
//                    clusters[orderClusters[0]].transitions[i].weight=clusters[orderClusters[0]].transitions[i].otherWeights[clusters[orderClusters[0]].getIndexesOfDistanceType(typeOfDistance)[j]];
//                }
//                clusters[orderClusters[0]].transformToBidirectional();
//                long startNode=0;
//                long endNode=clusters[orderClusters[0]].nodes.size();
//                std::vector<Node*> setOfDestinations;
//                
//                clusters[orderClusters[0]].calculateDijkstraAllToAll(&clusters[orderClusters[0]],setOfDistancesTemp,startNode,endNode,0,false,true,calculateCentralitiesSimultaneously, true,false,setOfDestinations);
//
//                this->diameters[this->getIndexesOfDistanceType(typeOfDistance)[j]]=clusters[orderClusters[0]].diameters[clusters[orderClusters[0]].getIndexesOfDistanceType(typeOfDistance)[j]];
//            }
                long startNode=0;
                long endNode=nodes.size();
                std::vector<Node*> setOfDestinations;
                
                calculateDijkstraAllToAll(this,setOfDistancesToCalculate,startNode,endNode,0,false,true,calculateCentralitiesSimultaneously, true,false,setOfDestinations);
            
            
            

            
            
        }
        
        //                    milliSecondsElapsed = getMilliSpan(start);
    }
    if (calculateCentralities)
    {
        if (parallel)
        {
            for(int i=0; i<graphs.size(); i++)
            {
                for(int j=0; j<nodes.size(); j++)
                {
                    //                    if (calculateCentralities)
                    {
                        nodeCount[j]+=graphs[i].nodeCount[j];
                        TSL[j]+=graphs[i].TSL[j];
                        betweenness[j]+=graphs[i].betweenness[j];
                        closeness[j]+=graphs[i].closeness[j];
                        for (int h=0; h<numberDistances; h++)
                        {
                            betweennessMeasures[h][j]+=graphs[i].betweennessMeasures[h][j];
                            closenessMeasures[h][j]+=graphs[i].closenessMeasures[h][j];
                        }
                    }
                    if (calculateDiffussion)
                    {
                        nodes[j].waterLevel.flow+=graphs[i].nodes[j].waterLevel.flow;
                    }
                }
            }
        }
        
        
    }
    if (calculateGlobalProperties)
    {
        if (parallel)
        {
            for(int i=0; i<graphs.size(); i++)
            {
                if (i==0)
                {
                    diameters[getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    diameters[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    averageLengths[getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    averageLengths[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    
   
                    
                }
                else
                {
                    if (graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]]>diameters[getIndexesOfDistanceType(Graph::METRIC)[0]])
                    {
                        diameters[getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    }
                    if (graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]>diameters[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]])
                    {
                        diameters[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    }
                    averageLengths[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]+=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    averageLengths[getIndexesOfDistanceType(Graph::METRIC)[0]]+=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                }
            }
            averageLengths[getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]/=(double)(numThreads);
            averageLengths[getIndexesOfDistanceType(Graph::METRIC)[0]]/=(double)(numThreads);
        }
        
        
    }
}

//
//void Graph::parallelize(...){
//     va_list args;
////    va_start(args, fmt);
////    std::cout<<args;
//        std::cout<<"size of args "<<
//
//}


double Graph::metricHeuristic(Node* node,Node* b)
{
    double heuristicDistanceToGoal=sqrt((b->location.x-node->location.x)*(b->location.x-node->location.x)+(b->location.y-node->location.y)*(b->location.y-node->location.y));
    return heuristicDistanceToGoal;
}

void Graph::copyGraph(const Graph* graphOrigin,Graph* graphDestination,bool substitute)
{
    graphDestination->customize=graphOrigin->customize;
    graphDestination->id=graphOrigin->id;
    
    
    graphDestination->strictlyDirectional=graphOrigin->strictlyDirectional;
    graphDestination->bidirectional=graphOrigin->bidirectional;
    graphDestination->pseudoGraph=graphOrigin->pseudoGraph;
    graphDestination->calculateBetweenness=graphOrigin->calculateBetweenness;
    graphDestination->avoidBacktrackingInLineGraph=graphOrigin->avoidBacktrackingInLineGraph;
    graphDestination->nodes.clear();
    graphDestination->calculateCentralities=graphOrigin->calculateCentralities;
    graphDestination->calculateGlobalProperties=graphOrigin->calculateGlobalProperties;
    graphDestination->calculateMainDistance=graphOrigin->calculateMainDistance;
    graphDestination->calculateOtherDistances=graphOrigin->calculateOtherDistances;
    graphDestination->calculateDiffussion=graphOrigin->calculateDiffussion;
    graphDestination->numberDistances=graphOrigin->numberDistances;
    for(long i=0; i<graphOrigin->nodes.size(); i++)
    {
        graphDestination->addNode();
    }
    graphDestination->resizeInitialParametersToNumDistances();
    //    graphDestination->indexOfMainDistanceInOtherDistances=graphOrigin->indexOfMainDistanceInOtherDistances;
    //    graphDestination->indexOfDistancesByDistanceType=graphOrigin->indexOfDistancesByDistanceType;
    for(int i=0;i<numberDistances;i++){
        graphDestination->diameters[i]=graphOrigin->diameters[i];
        graphDestination->totalLengths[i]=graphOrigin->totalLengths[i];
        graphDestination->averageLengths[i]=graphOrigin->averageLengths[i];
    }
    graphDestination->indexOfMainDistanceInOtherDistances=graphOrigin->indexOfMainDistanceInOtherDistances;
    graphDestination->indexOfDistancesByDistanceType=graphOrigin->indexOfDistancesByDistanceType;
    //    graphDestination->indexOfDistancesByDistanceType=graphOrigin->indexOfDistancesByDistanceType;
    
    for(long i=0; i<graphOrigin->nodes.size(); i++)
    {
        graphDestination->nodes[i].location=Point2d(graphOrigin->nodes[i].location.x,graphOrigin->nodes[i].location.y);
        graphDestination->nodes[i].mass=graphOrigin->nodes[i].mass;
        graphDestination->nodes[i].nodeThatRepresents=graphOrigin->nodes[i].nodeThatRepresents;
        graphDestination->nodes[i].nodeRepresentedBy=graphOrigin->nodes[i].nodeRepresentedBy;
        graphDestination->nodes[i].levelHierarchyRoad=graphOrigin->nodes[i].levelHierarchyRoad;
        graphDestination->nodes[i].nameRoad=graphOrigin->nodes[i].nameRoad;
        if(substitute){
            if(graphDestination->nodes[i].nodeThatRepresents!=NULL){
                graphDestination->nodes[i].nodeThatRepresents->nodeRepresentedBy=&graphDestination->nodes[i];
            }
            if(graphDestination->nodes[i].nodeRepresentedBy!=NULL){
                graphDestination->nodes[i].nodeRepresentedBy->nodeThatRepresents=&graphDestination->nodes[i];
            }
        }
        
        graphDestination->nodes[i].originalID=graphOrigin->nodes[i].originalID;
//        graphDestination->nodes[i].indexOfTransitionsByIdOfDestination=graphOrigin->nodes[i].indexOfTransitionsByIdOfDestination;
        graphDestination->nodes[i].transitionThatRepresents=graphOrigin->nodes[i].transitionThatRepresents;
    }
    
    
    for(long i=0; i<graphOrigin->nodes.size(); i++)
    {
        for (long j=0; j<graphOrigin->nodes[i].transitions.size(); j++)
        {
            Transition trans;
            trans.transitionThatRepresents=graphOrigin->nodes[i].transitions[j]->transitionThatRepresents;
            
            trans.firstAngleInPhaseTransition=graphOrigin->nodes[i].transitions[j]->firstAngleInPhaseTransition;
            trans.levelHierarchyRoad=graphOrigin->nodes[i].transitions[j]->levelHierarchyRoad;
            trans.nameRoad=graphOrigin->nodes[i].transitions[j]->nameRoad;
            trans.a=&(graphDestination->nodes[graphOrigin->nodes[i].transitions[j]->a->id]);
            trans.b=&(graphDestination->nodes[graphOrigin->nodes[i].transitions[j]->b->id]);
            trans.weight=graphOrigin->nodes[i].transitions[j]->weight;
            trans.originalID=graphOrigin->nodes[i].transitions[j]->originalID;
            trans.otherWeights=graphOrigin->nodes[i].transitions[j]->otherWeights;
            
            //            trans.a->transitions.push_back(trans);
            graphDestination->addTransition(trans);
        }
//        for (long j=0; j<graphOrigin->nodes[i].transitionsThatReachMe.size(); j++)
//        {
//            Transition trans;
//            trans.a=&(graphDestination->nodes[graphOrigin->nodes[i].transitionsThatReachMe[j]->a->id]);
//            trans.b=&(graphDestination->nodes[graphOrigin->nodes[i].transitionsThatReachMe[j]->b->id]);
//            trans.weight=graphOrigin->nodes[i].transitionsThatReachMe[j]->weight;
//            trans.otherWeights=graphOrigin->nodes[i].transitionsThatReachMe[j]->otherWeights;
//            
//            //            trans.a->transitions.push_back(trans);
//            graphDestination->nodes[i].transitionsThatReachMe.push_back(trans);
//        }
        
    }
    if(substitute){
        for(long i=0; i<graphDestination->nodes.size(); i++)
        {
            for (long j=0; j<graphDestination->nodes[i].transitions.size(); j++)
            {
                graphDestination->nodes[i].transitions[j]->transitionThatRepresents->transitionRepresentedBy=graphDestination->nodes[i].transitions[j];
            }
        }
    }
}
void Graph::insertTopologicalWeights(){
    int indexDistance=numberDistances;
    indexOfDistancesByDistanceType[Graph::TOPOLOGICAL].push_back(indexDistance);
    this->numberDistances++;
    totalLengths.push_back(0);
    averageLengths.push_back(0);
    diameters.push_back(0);
    for(long i=0;i<nodes.size();i++){
        pushNewDistance(&nodes[i]);
        for(long j=0;j<nodes[i].transitions.size();j++){
            nodes[i].transitions[j]->otherWeights.push_back(1);
            
        }
    }
}
void Graph::setTypeOfMainDistanceAndInsertIntoDistances(int distanceType){
    int indexDistance=numberDistances;
    indexOfDistancesByDistanceType[distanceType].push_back(indexDistance);
    this->numberDistances++;
    indexOfMainDistanceInOtherDistances=indexDistance;
    totalLengths.push_back(0);
    averageLengths.push_back(0);
    diameters.push_back(0);
    for(long i=0;i<nodes.size();i++){
        pushNewDistance(&nodes[i]);
    }
    for(long i=0;i<transitions.size();i++){
//        for(long j=0;j<transitions[i].size();j++){
            transitions[i].otherWeights.push_back(transitions[i].weight);
            
//        }
    }
}

void Graph::changeWeightsTo(Graph* graph,int indexDistance){
    for(long i=0;i<graph->transitions.size();i++){
        graph->transitions[i].weight=transitions[i].otherWeights[indexDistance];
    }
    indexOfMainDistanceInOtherDistances=indexDistance;
}

void Graph::setTypeOfMainDistance(int distanceType,int indexOfDistanceWhenSeveralDistancesOfSameType){
//    int indexDistance=numberDistances;
//    indexOfDistancesByDistanceType[distanceType].push_back(indexDistance);
//    this->numberDistances++;
    indexOfMainDistanceInOtherDistances=getIndexesOfDistanceType(distanceType)[indexOfDistanceWhenSeveralDistancesOfSameType];
//    totalLengths.push_back(0);
//    averageLengths.push_back(0);
//    diameters.push_back(0);
//    for(long i=0;i<nodes.size();i++){
//        pushNewDistance(&nodes[i]);
//    }
//    for(long i=0;i<transitions.size();i++){
//        //        for(long j=0;j<transitions[i].size();j++){
//        transitions[i].otherWeights.push_back(transitions[i].weight);
//        
//        //        }
//    }
}

void Graph::pushNewDistance(Node* node){
    //    this->numberDistances++;
    //    for(long i=0;i<nodes.size();i++){
    node->minOtherDistances.push_back(INFINITY);
    node->numOtherChildren.push_back(0);
    node->numOtherChildrenThatReachedMe.push_back(0);
    node->valuesToPass.push_back(1);
    node->originalValuesToPass.push_back(1);
    node->otherParents.push_back(NULL);
    //    }
}

void Graph::pushNewDistance(){
   
    this->numberDistances++;
    totalLengths.push_back(0);
    averageLengths.push_back(0);
    diameters.push_back(0);
    for(long i=0;i<nodes.size();i++){
        nodes[i].minOtherDistances.push_back(INFINITY);
        nodes[i].numOtherChildren.push_back(0);
        nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        nodes[i].valuesToPass.push_back(1);
                nodes[i].originalValuesToPass.push_back(1);
        nodes[i].otherParents.push_back(NULL);
    }
}
void Graph::pushNewDistance(int distanceType){
    int indexDistance=numberDistances;
    indexOfDistancesByDistanceType[distanceType].push_back(indexDistance);
    this->numberDistances++;
    totalLengths.push_back(0);
    averageLengths.push_back(0);
    diameters.push_back(0);
    for(long i=0;i<nodes.size();i++){
        nodes[i].minOtherDistances.push_back(INFINITY);
        nodes[i].numOtherChildren.push_back(0);
        nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        nodes[i].valuesToPass.push_back(1);
          nodes[i].originalValuesToPass.push_back(1);
        nodes[i].otherParents.push_back(NULL);
    }
}

void Graph::resizeInitialParametersToNumDistances(){
    //    this->numberDistances++;
    totalLengths.resize(numberDistances,0);
    averageLengths.resize(numberDistances,0);
    diameters.resize(numberDistances,0);
    nodeCount.resize(numberDistances,0);
    for(long i=0;i<nodes.size();i++){
        nodes[i].minOtherDistances.resize(numberDistances,INFINITY);
        nodes[i].numOtherChildren.resize(numberDistances,0);
        nodes[i].numOtherChildrenThatReachedMe.resize(numberDistances,0);
        nodes[i].valuesToPass.resize(numberDistances,0);
                nodes[i].originalValuesToPass.resize(numberDistances,0);
        nodes[i].otherParents.resize(numberDistances,NULL);
    }
    
    
}


std::vector<int> Graph::getIndexesOfDistanceType(int distanceType){
    return indexOfDistancesByDistanceType[distanceType];
}
void Graph::toParallelizeCalculatingDiskstraToSetOfDestinations(Graph* graph,std::vector<Node*> uniqueNodes,std::vector<Transition> originDestinationPairs,std::vector<int> setOfDistancesToCalculate,bool calculateCentralitiesSimultaneously){
    
//    std::cout<<"size of unique Nodes "<<uniqueNodes.size()<<'\n';
//    std::cout<<"size of originsDestinaitons "<<originDestinationPairs.size()<<'\n';
    for(long i=0; i<uniqueNodes.size(); i++)
    {
        BST<Node*> uniqueNodesDestinations;
        for(long j=0; j<originDestinationPairs.size(); j++)
        {
            if (originDestinationPairs[j].a->id==uniqueNodes[i]->id)
            {
                uniqueNodesDestinations.add(originDestinationPairs[j].b->id,&graph->nodes[originDestinationPairs[j].b->id]);
            }
        }
        
        std::vector<Node*> uniqueDestinations=uniqueNodesDestinations.getAll();
        
        calculateDijkstraAllToAll(graph,setOfDistancesToCalculate,uniqueNodes[i]->id,uniqueNodes[i]->id+1,0,true,true,calculateCentralitiesSimultaneously, true,false,uniqueDestinations);
        
        uniqueNodesDestinations.deleteAll();
    }
}

void Graph::toParallelizeCalculatingAStar(Graph* graph,std::vector<Transition> originDestinationPairs,long startNode,long endNode,int typeOfDistance,double (*function)(Node*,Node*)){
    
    
    for(long i=startNode; i<endNode; i++)
    {
        
        std::vector<double> results=graph->AStarOtherWeights(originDestinationPairs[i].a,originDestinationPairs[i].b,graph->indexOfDistancesByDistanceType[typeOfDistance],function);
        for(int j=0;j<graph->indexOfDistancesByDistanceType[typeOfDistance].size();j++){
            
            if(graph->diameters[graph->indexOfDistancesByDistanceType[typeOfDistance][j]]<results[graph->indexOfDistancesByDistanceType[typeOfDistance][j]]&&results[graph->indexOfDistancesByDistanceType[typeOfDistance][j]]<INFINITY)
            {
                graph->diameters[graph->indexOfDistancesByDistanceType[typeOfDistance][j]]=results[graph->indexOfDistancesByDistanceType[typeOfDistance][j]];
                
            }
        }
        
        
    }
}


void Graph:: resetGraph(){
    nodes.clear();
    transitions.clear();
    numberDistances=0;
    indexOfDistancesByDistanceType.clear();
    indexOfMainDistanceInOtherDistances=-1;
    
    resizeInitialParametersToNumDistances();
}


void Graph::removeNodesFromGraph(Graph* graph,Graph& newGraph,double percentageOfNodesToRemove){
    std::vector<Node*> nodesToRemain;
    for(long i=0;i<graph->nodes.size();i++){
        nodesToRemain.push_back(&graph->nodes[i]);
    }
    for(long i=0;i<graph->nodes.size()/100*percentageOfNodesToRemove;i++){
        long randomIndex=rand()%nodesToRemain.size();
        std::swap(nodesToRemain[randomIndex], nodesToRemain.back());
        //        Node* nodeToRemove=nodesToRemain.back();
        nodesToRemain.pop_back();
    }
    //    Graph subgraph;
    graph->getInducedSubgraph(&newGraph, nodesToRemain);
    //    graph->nodes=subgraph.nodes;
}

void Graph::removeNodesFromGraph(Graph* graph,std::vector<Node*> nodesToRemove){
    
    for(long h=0;h<nodesToRemove.size();h++){
        Node* node=nodesToRemove[h];
//        graph->nodes.erase(graph->nodes.begin()+node->id);
        node->transitions.clear();
        if(node->nodesThatReachMe.size()>0){
            for(long i=0;i<node->nodesThatReachMe.size();i++){
                for (long j=0;j<node->nodesThatReachMe[i]->transitions.size();j++){
                    if(node->nodesThatReachMe[i]->transitions[j]->b==node){
//                        node->nodesThatReachMe[i]->transitions.erase(node->nodesThatReachMe[i]->transitions.begin()+j);
                        
                        j--;
                    }
                }
                
            }
        }
    }
//    for(long i=0;i<graph->nodes.size();i++){
//        graph->nodes[i].id=i;
//    }
  
}

void Graph::removeNode(Graph* graph,Node* node){
//    graph->nodes.erase(graph->nodes.begin()+node->id);
    node->transitions.clear();

    if(node->nodesThatReachMe.size()>0){
        for(long i=0;i<node->nodesThatReachMe.size();i++){
            for (long j=0;j<node->nodesThatReachMe[i]->transitions.size();j++){
                if(node->nodesThatReachMe[i]->transitions[j]->b==node){
//                    node->nodesThatReachMe[i]->transitions.erase(node->nodesThatReachMe[i]->transitions.begin()+j);
                    j--;
                }
            }

        }
    }
//    for(long i=node->id;i<graph->nodes.size();i++){
//        graph->nodes[i].id=graph->nodes[i].id-1;
//    }

}


void Graph::colorInvertedKReachableGraph(Graph* originalGraph,Graph* inverseOfKReachableGraph){
//    std::queue<Node*> connectedNodes;
//    std::queue<Node*> unConnectedNodes;
//    Node* initNode=&kReachableGraph->nodes[0];
//    connectedNodes.push(initNode);
//    while(connectedNodes.size()>0){
    for(long h=0;h<inverseOfKReachableGraph->nodes.size();h++){
        Node* currentNodeInKReachable=&inverseOfKReachableGraph->nodes[h];
//        connectedNodes.pop();
        if(currentNodeInKReachable->numColor==-1){
        
//        for (long i=0;i<kReachableGraph->nodes.size();i++){
//            BST<long> colorsOfNeighbors;
            std::unordered_map<long,long> countscolorsOfRealNeighbors;
            std::unordered_map<long,long> colorsOfNeighbors;
            long maxCountsOfColor=0;
            long predominantColor=-1;
            for(long j=0;j<currentNodeInKReachable->transitions.size();j++){
//                if(currentNodeInKReachable->transitions[j]->b->numColor!=-1){
                    colorsOfNeighbors[currentNodeInKReachable->transitions[j]->b->numColor]++;
//                }
//                if(currentNodeInKReachable->transitions[j]->b->numColor==-1){
//                    connectedNodes.push(currentNodeInKReachable->transitions[j]->b);
//                }
            }
            
            
            for(long j=0;j<currentNodeInKReachable->nodeThatRepresents->transitions.size();j++){
                if(currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor!=-1){
                    countscolorsOfRealNeighbors[currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor]=countscolorsOfRealNeighbors[currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor]+1;
                    if(countscolorsOfRealNeighbors[currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor]>maxCountsOfColor){
                        if(colorsOfNeighbors[currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor]==0){
                            maxCountsOfColor=countscolorsOfRealNeighbors[currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor];
                            predominantColor=currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor;
                        }
                    }
                }
//                if(currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy->numColor==-1){
//                    unConnectedNodes.push(currentNodeInKReachable->nodeThatRepresents->transitions[j]->b->nodeRepresentedBy);
//                }
            }
            if (predominantColor==-1){
                long possibleColor=0;
                bool colorChosen=false;
                while(!colorChosen){
//                    std::cout<<colorsOfNeighbors[possibleColor]<<'\n';
                    if(colorsOfNeighbors[possibleColor]==0){
                        colorChosen=true;
                        predominantColor=possibleColor;
                    }else{
                        possibleColor++;
                    }
                }
            }
            currentNodeInKReachable->numColor=predominantColor;
            currentNodeInKReachable->nodeThatRepresents->numColor=predominantColor;
            
//        }
        }
        
//        if (connectedNodes.size()==0&&unConnectedNodes.size()!=0){
//            connectedNodes.push(unConnectedNodes.front());
//            unConnectedNodes.pop();
//        }
        
        
    }
    
}




//void Graph::calculateColorsWithMEMB_approximation(Graph* graph,double distance,int indexDistance){
//    Heap<Node*> extendedDegrees (Heap<Node*>::MAX,&Graph::compareByDegreeOut,&Graph::getDegreeOut,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//    std::vector<Node*> centers;
//    Graph kReachableGraph;
//    if (indexDistance!=indexOfMainDistanceInOtherDistances){
//        for(long i=0;i<graph->transitions.size();i++){
//            graph->transitions[i].weight=transitions[i].otherWeights[indexDistance];
//        }
//    }
//    graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
//    
//    for(long i=0;i<kReachableGraph.nodes.size();i++){
//        Node* node=&kReachableGraph.nodes[i];
//        extendedDegrees.push(node);
//    }
//    long numberUncoveredNodes=kReachableGraph.nodes.size();
//    long numColor=0;
//    while(numberUncoveredNodes>0&&extendedDegrees.size()>0){
//        Node* node=extendedDegrees.pop();
////        std::cout<<numberUncoveredNodes<<" "<<kReachableGraph.getDegree(node)<<'\n';
//        
//        if(!node->isCovered){
//            centers.push_back(node);
//            if (!node->isCovered){
//                numberUncoveredNodes--;
//            }
//            node->isCenter=true;
//            node->isCovered=true;
//            node->numColor=numColor;
////            node->nodeThatRepresents->isCovered=true;
////            node->nodeThatRepresents->isCenter=true;
//            node->nodeThatRepresents->numColor=numColor;
//            
//            
//            
//            for(long j=0;j<node->transitions.size();j++){
//                if (!node->transitions[j]->b->isCovered){
//                    numberUncoveredNodes--;
//                    node->transitions[j]->b->isCovered=true;
////                    node->transitions[j]->b->nodeThatRepresents->isCovered=true;
//                }
//                //                double previousValue=kReachableGraph.getDegree(node);
//                ////                node->transitions[j]->b->degreeModifier--;
//                //                if(!node->transitions[j]->b->isCenter){
//                //                    long degreeModifierTemp=0;
//                ////                    for(long h=0;h<node->transitions[j]->b->transitions.size();h++){
//                ////                        if(node->transitions[j]->b->transitions[h]->b->isCovered){
//                ////                            degreeModifierTemp++;
//                ////                        }
//                ////                    }
//                //                    degreeModifierTemp=distance/(node->transitions[j]->b->minDistance);
//                //                    node->transitions[j]->b->degreeModifier-=degreeModifierTemp;
//                //                    extendedDegrees.update(node->transitions[j]->b, previousValue);
//                //                }
//            }
//            
//    //        extendedDegrees.clear();
//    //        kReachableGraph.resetGraph();
//    //        graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
//            
////            for(long i=0;i<kReachableGraph.nodes.size();i++){
////                Node* node=&kReachableGraph.nodes[i];
////                if(kReachableGraph.getDegree(node)>0){
////                    extendedDegrees.push(node);
////                }
////            }
//            
//            numColor++;
//        }
//        
//    }
//    
//    
////    for(long i=0;i<graph->nodes.size();i++){
////        graph->nodes[i].isCovered=false;
////    }
////    kReachableGraph.resetGraph();
////    graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
//    
//    
//    Graph finalGraph;
//    for(long i=0;i<kReachableGraph.nodes.size();i++){
//        finalGraph.addNode();
//        //        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
//        //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
//    }
//    
//    
//    
//    for(long i=0;i<graph->nodes.size();i++){
//        //        kReachableGraph->addNode();
//        finalGraph.nodes[i].originalID=kReachableGraph.nodes[i].originalID;
//        finalGraph.nodes[i].nodeThatRepresents=&kReachableGraph.nodes[i];
//        kReachableGraph.nodes[i].nodeRepresentedBy=&finalGraph.nodes[i];
//    }
//    for(long i=0;i<kReachableGraph.nodes.size();i++){
//        Node* node=&kReachableGraph.nodes[i];
//        if(!node->isCenter){
//            double min=INFINITY;
//            Transition* transitionChosen=NULL;
//            std::vector<Transition*> possibleTransitions;
//            for(long j=0;j<node->transitions.size();j++){
//                //                std::vector<Transition*> transitionsToCenters;
//                
//                if(node->transitions[j]->b->isCenter){
//                    if(node->transitions[j]->weight<=min){
//                        min=node->transitions[j]->weight;
//                        possibleTransitions.push_back(node->transitions[j]);
////                        transitionChosen=node->transitions[j];
//                    }
//                    //                    transitionsToCenters.push_back(node->transitions[j]);
//                }
//            }
//            double minNumColor=INFINITY;
//            for (long j=0;j<possibleTransitions.size();j++){
//                if(possibleTransitions[j]->b->numColor<minNumColor){
//                    minNumColor=possibleTransitions[j]->b->numColor;
////                    possibleTransitions.push_back(node->transitions[j]);
//                    transitionChosen=possibleTransitions[j];
//                }
//                
//            }
//            Transition trans;
//            trans.a=transitionChosen->b->nodeRepresentedBy;
//            trans.b=node->nodeRepresentedBy;
//            trans.weight=transitionChosen->weight;
//            trans.otherWeights=transitionChosen->otherWeights;
//            finalGraph.addTransition(trans);
//            node->numColor=transitionChosen->b->numColor;
//            node->nodeThatRepresents->numColor=node->numColor;
//        }
//    }
////    for(long i=0;i<finalGraph.nodes.size();i++){
////        double numColor=finalGraph.nodes[i].numColor;
////        Graph cluster;
////        std::vector<Node*> nodesInCluster;
////        Node* node=&finalGraph.nodes[i];
////        if(node->transitions.size()>0){
////            nodesInCluster.push_back(node->nodeThatRepresents->nodeThatRepresents);
////        }
////        for(long j=0;j<node->transitions.size();j++){
////            nodesInCluster.push_back(node->transitions[j]->b->nodeThatRepresents->nodeThatRepresents);
////        }
////        graph->getInducedSubgraph(&cluster, nodesInCluster);
////        if(cluster.transitions.size()>0){
////            clusters.push_back(cluster);
////        }
//        
//        
////    }
//    
//    
//        //            lines.clear();
////        std::vector<std::string> lines;
////        for(long i=0;i<kReachableGraph.transitions.size();i++){
////    
////            std::stringstream line;
////            line<<kReachableGraph.transitions[i].a->originalID<<" "<<kReachableGraph.transitions[i].b->originalID<<" "<<kReachableGraph.transitions[i].a->numColor<<" "<<kReachableGraph.transitions[i].b->numColor;
////            lines.push_back(line.str());
////            //            }
////        }
////        TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/kReachableLondon.txt", lines, false);
////    
////    
////    
////    
////        lines.clear();
////        for(long i=0;i<graph->transitions.size();i++){
////            //            for(long j=0;j<modules[i].transitions.size();j++){
////            std::stringstream line;
////            line<<graph->transitions[i].a->originalID<<" "<<graph->transitions[i].b->originalID<<" "<<graph->transitions[i].a->numColor<<" "<<graph->transitions[i].b->numColor;
////            lines.push_back(line.str());
////            //            }
////        }
////        TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clusterLondon.txt", lines, false);
//    
//    for(long i=0;i<graph->nodes.size();i++){
//        graph->nodes[i].isCovered=false;
//        graph->nodes[i].isCenter=false;
//        graph->nodes[i].degreeModifierOut=0;
//        
//    }
//    if (indexDistance!=indexOfMainDistanceInOtherDistances){
//        for(long i=0;i<graph->transitions.size();i++){
//            graph->transitions[i].weight=transitions[i].otherWeights[indexOfMainDistanceInOtherDistances];
//        }
//    }
//    
//    
//    
//}




void Graph::calculateColorsWithMEMB_approximation(Graph* graph,double distance,int indexDistance){
    //    Heap<Node*> extendedDegrees (Heap<Node*>::MAX,&Graph::compareByDegree,&Graph::getDegree,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    std::vector<Node*> centers;
    Graph kReachableGraph;
    for(long i=0;i<graph->transitions.size();i++){
        graph->transitions[i].weight=transitions[i].otherWeights[indexDistance];
    }
    graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
    //    Graph kReachableForCalculation;
    //    graph->recalculateKReachableGraph(&kReachableGraph, &kReachableForCalculation, distance, indexDistance);
    
    //    for(long i=0;i<kReachableGraph.nodes.size();i++){
    //        Node* node=&kReachableGraph.nodes[i];
    //        extendedDegrees.push(node);
    //    }
    long numberUncoveredNodes=kReachableGraph.nodes.size();
    long numColor=1;
    Node* node=NULL;
    std::vector<Node*> possibleCenters;
    long max=-INFINITY;
    for(long f=0;f<kReachableGraph.nodes.size();f++){
        Node* nodeTemp=&kReachableGraph.nodes[f];
        if(!nodeTemp->isCenter){
            long degree=getDegreeOut(nodeTemp);
            if(degree>=max){
                if(degree>max){
                    possibleCenters.clear();
                }
                max=degree;
                possibleCenters.push_back(nodeTemp);
            }
        }
    }
    long index=(long)(Functions::random(0, possibleCenters.size(), true));
    node=possibleCenters[index];
    while(numberUncoveredNodes>0){
        //        Node* node=extendedDegrees.pop();
        
        //        std::cout<<numberUncoveredNodes<<" "<<kReachableGraph.getDegree(node)<<'\n';
        
        //        if(!node->isCovered){
        centers.push_back(node);
        //            node->degreeModifierOut-=1;
        if (!node->isCovered){
            numberUncoveredNodes--;
        }
        node->isCenter=true;
        node->isCovered=true;
        node->numColor=numColor;
        node->nodeThatRepresents->isCovered=true;
        node->nodeThatRepresents->isCenter=true;
        node->nodeThatRepresents->numColor=numColor;
        
        
        
        for(long j=0;j<node->transitions.size();j++){
            if (!node->transitions[j]->b->isCovered){
                numberUncoveredNodes--;
                
                node->transitions[j]->b->isCovered=true;
                node->transitions[j]->b->nodeThatRepresents->isCovered=true;
                node->transitions[j]->b->diffusionValue-=exp(-pow((node->transitions[j]->weight),2.0)/(2.0*pow((distance/3.0),2.0)));
//
                
                
                
                //                    node->transitions[j]->b->degreeModifierOut-=1;
                
            }
            
//            double multiplier=exp(-pow((node->transitions[j]->weight),2.0)/(2.0*pow((distance/3.0),2.0)));
//                            if(multiplier>.1){
            Node* b=node->transitions[j]->b;
//            if (!b->isCenter){
                for(long k=0;k<b->transitions.size();k++){
                    if(!b->transitions[k]->b->isCenter){
                        b->transitions[k]->b->diffusionValue-=exp(-pow((b->transitions[k]->weight),2.0)/(2.0*pow((distance/3.0),2.0)));
                    }
                    if (!b->isCenter){
                        b->diffusionValue-=1;
                    }
                }
//            }
//                            }
            
            //                double previousValue=kReachableGraph.getDegree(node);
            ////                node->transitions[j]->b->degreeModifier--;
            //                if(!node->transitions[j]->b->isCenter){
            //                    long degreeModifierTemp=0;
            ////                    for(long h=0;h<node->transitions[j]->b->transitions.size();h++){
            ////                        if(node->transitions[j]->b->transitions[h]->b->isCovered){
            ////                            degreeModifierTemp++;
            ////                        }
            ////                    }
            //                    degreeModifierTemp=distance/(node->transitions[j]->b->minDistance);
            //                    node->transitions[j]->b->degreeModifier-=degreeModifierTemp;
            //                    extendedDegrees.update(node->transitions[j]->b, previousValue);
            //                }
        }
        
        //            extendedDegrees.clear();
        //            kReachableGraph.resetGraph();
        //            graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
        
        //        kReachableForCalculation.resetGraph();
        //         graph->recalculateKReachableGraph(&kReachableForCalculation, &kReachableForCalculation, distance, indexDistance);
        
        double max=-INFINITY;
//        std::vector<Node*> possibleCenters;
        possibleCenters.clear();
        for(long f=0;f<kReachableGraph.nodes.size();f++){
            Node* nodeTemp=&kReachableGraph.nodes[f];
            long diffusionValue=nodeTemp->diffusionValue;
            if(!nodeTemp->isCenter){
//                long degree=degreeOut_MEMB(nodeTemp);
                if(diffusionValue>=max){
                    if(diffusionValue>max){
                        possibleCenters.clear();
                    }
                    max=diffusionValue;
                    possibleCenters.push_back(nodeTemp);
                }
            }
        }
        long index=(long)(Functions::random(0, possibleCenters.size(), true));
        node=possibleCenters[index];
        
        //            for(long i=0;i<kReachableGraph.nodes.size();i++){
        //                Node* node=&kReachableGraph.nodes[i];
        //                if(kReachableGraph.getDegree(node)>0){
        //                    extendedDegrees.push(node);
        //                }
        //            }
        
        numColor++;
        //        }
        
    }
    
    
    //    for(long i=0;i<graph->nodes.size();i++){
    //        graph->nodes[i].isCovered=false;
    //        graph->nodes[i].degreeModifierOut=0;
    //    }
    //    kReachableGraph.resetGraph();
    //    graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
    
    
    //    Graph finalGraph;
    //    for(long i=0;i<kReachableGraph.nodes.size();i++){
    //        finalGraph.addNode();
    //        //        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
    //        //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
    //    }
    
    
    
    //    for(long i=0;i<kReachableGraph.nodes.size();i++){
    //        //        kReachableGraph->addNode();
    //        finalGraph.nodes[i].originalID=kReachableGraph.nodes[i].originalID;
    //        finalGraph.nodes[i].nodeThatRepresents=&kReachableGraph.nodes[i];
    //        kReachableGraph.nodes[i].nodeRepresentedBy=&finalGraph.nodes[i];
    //    }
    
    
    
    
    
    
    
    
    
    for(long i=0;i<kReachableGraph.nodes.size();i++){
        Node* node=&kReachableGraph.nodes[i];
        if(!node->isCenter){
            double min=INFINITY;
            //            Transition* transitionChosen=NULL;
            std::vector<Node*> possibleCenters;
            
            for(long j=0;j<node->transitions.size();j++){
                //                std::vector<Transition*> transitionsToCenters;
                
                if(node->transitions[j]->b->isCenter){
                    if(node->transitions[j]->weight<=min){
                        if(node->transitions[j]->weight<min){
                            possibleCenters.clear();
                        }
                        min=node->transitions[j]->weight;
                        possibleCenters.push_back(node->transitions[j]->b);
                        //                        transitionChosen=node->transitions[j];
                    }
                    //                    transitionsToCenters.push_back(node->transitions[j]);
                }
            }
            double minNumColor=INFINITY;
            //            Node* centerChosen=NULL;
            for (long j=0;j<possibleCenters.size();j++){
                if(possibleCenters[j]->numColor<minNumColor){
                    //                    centerChosen=possibleCenters[j];
                    minNumColor=possibleCenters[j]->numColor;
                    //                    possibleTransitions.push_back(node->transitions[j]);
                    //                    transitionChosen=possibleTransitions[j];
                }
                
            }
            possibleCenters.clear();
            //            Transition trans;
            //            trans.a=transitionChosen->b->nodeRepresentedBy;
            //            trans.b=node->nodeRepresentedBy;
            //            trans.weight=transitionChosen->weight;
            //            trans.otherWeights=transitionChosen->otherWeights;
            //            finalGraph.addTransition(trans);
            node->numColor=minNumColor;
            node->nodeThatRepresents->numColor=minNumColor;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    //    for(long i=0;i<finalGraph.nodes.size();i++){
    //        Graph cluster;
    //        std::vector<Node*> nodesInCluster;
    //         Node* node=&finalGraph.nodes[i];
    //        if(node->transitions.size()>0){
    //            nodesInCluster.push_back(node->nodeThatRepresents->nodeThatRepresents);
    //        }
    //        for(long j=0;j<node->transitions.size();j++){
    //            nodesInCluster.push_back(node->transitions[j]->b->nodeThatRepresents->nodeThatRepresents);
    //        }
    //        graph->getInducedSubgraph(&cluster, nodesInCluster);
    //        clusters.push_back(cluster);
    //
    //
    //    }
    for(long i=0;i<graph->nodes.size();i++){
        graph->nodes[i].isCovered=false;
        graph->nodes[i].isCenter=false;
        graph->nodes[i].degreeModifierOut=0;
        
    }
    
    //    //            lines.clear();
    //    std::vector<std::string> lines;
    //    for(long i=0;i<kReachableGraph.transitions.size();i++){
    //
    //        std::stringstream line;
    //        line<<kReachableGraph.transitions[i].a->originalID<<" "<<kReachableGraph.transitions[i].b->originalID<<" "<<kReachableGraph.transitions[i].a->numColor<<" "<<kReachableGraph.transitions[i].b->numColor;
    //        lines.push_back(line.str());
    //        //            }
    //    }
    //    TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/kReachableLondon.txt", lines, false);
    //
    //
    //
    //
    //    lines.clear();
    //    for(long i=0;i<graph->transitions.size();i++){
    //        //            for(long j=0;j<modules[i].transitions.size();j++){
    //        std::stringstream line;
    //        line<<graph->transitions[i].a->originalID<<" "<<graph->transitions[i].b->originalID<<" "<<graph->transitions[i].a->numColor<<" "<<graph->transitions[i].b->numColor;
    //        lines.push_back(line.str());
    //        //            }
    //    }
    //    TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clusterLondon.txt", lines, false);
    
    
    
    
    
    
}





long Graph::degreeOut_MEMB(Node* node){
    long degree=0;
    for(long i=0;i<node->transitions.size();i++){
        if(!node->transitions[i]->b->isCovered){
            degree++;
        }
    }
    if(!node->isCovered){
        degree++;
    }
    return degree;
}





void Graph::calculateColorsWithMEMB(Graph* graph,double distance,int indexDistance){
//    Heap<Node*> extendedDegrees (Heap<Node*>::MAX,&Graph::compareByDegree,&Graph::getDegree,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    std::vector<Node*> centers;
    Graph kReachableGraph;
    for(long i=0;i<graph->transitions.size();i++){
        graph->transitions[i].weight=transitions[i].otherWeights[indexDistance];
    }
    graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
//    Graph kReachableForCalculation;
//    graph->recalculateKReachableGraph(&kReachableGraph, &kReachableForCalculation, distance, indexDistance);
    
//    for(long i=0;i<kReachableGraph.nodes.size();i++){
//        Node* node=&kReachableGraph.nodes[i];
//        extendedDegrees.push(node);
//    }
    long numberUncoveredNodes=kReachableGraph.nodes.size();
    long numColor=1;
    Node* node=NULL;
    std::vector<Node*> possibleCenters;
    long max=-INFINITY;
    for(long f=0;f<kReachableGraph.nodes.size();f++){
        Node* nodeTemp=&kReachableGraph.nodes[f];
        if(!nodeTemp->isCenter){
            long degree=getDegreeOut(nodeTemp);
//            std::cout<<"first pass "<<nodeTemp->originalID<<" "<<degree<<'\n';
            if(degree>=max){
                if(degree>max){
                    possibleCenters.clear();
                }
                max=degree;
                possibleCenters.push_back(nodeTemp);
            }
        }
    }
    long index=(long)(Functions::random(0, possibleCenters.size(), true));
    node=possibleCenters[index];
    
    while(numberUncoveredNodes>0){
//        Node* node=extendedDegrees.pop();
        
//        std::cout<<numberUncoveredNodes<<" "<<kReachableGraph.getDegree(node)<<'\n';
        
//        if(!node->isCovered){
            centers.push_back(node);
//            node->degreeModifierOut-=1;
            if (!node->isCovered){
                numberUncoveredNodes--;
            }
            node->isCenter=true;
            node->isCovered=true;
            node->numColor=numColor;
            node->nodeThatRepresents->isCovered=true;
            node->nodeThatRepresents->isCenter=true;
            node->nodeThatRepresents->numColor=numColor;
            
            
            
            for(long j=0;j<node->transitions.size();j++){
                if (!node->transitions[j]->b->isCovered){
                    numberUncoveredNodes--;
                
                    node->transitions[j]->b->isCovered=true;
                    node->transitions[j]->b->nodeThatRepresents->isCovered=true;
//                    node->transitions[j]->b->degreeModifierOut-=1;
                
                }
//                double previousValue=kReachableGraph.getDegree(node);
////                node->transitions[j]->b->degreeModifier--;
//                if(!node->transitions[j]->b->isCenter){
//                    long degreeModifierTemp=0;
////                    for(long h=0;h<node->transitions[j]->b->transitions.size();h++){
////                        if(node->transitions[j]->b->transitions[h]->b->isCovered){
////                            degreeModifierTemp++;
////                        }
////                    }
//                    degreeModifierTemp=distance/(node->transitions[j]->b->minDistance);
//                    node->transitions[j]->b->degreeModifier-=degreeModifierTemp;
//                    extendedDegrees.update(node->transitions[j]->b, previousValue);
//                }
            }
        
//            extendedDegrees.clear();
//            kReachableGraph.resetGraph();
        
//            graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
        
//        kReachableForCalculation.resetGraph();
//         graph->recalculateKReachableGraph(&kReachableForCalculation, &kReachableForCalculation, distance, indexDistance);
//        std::vector<Node*> possibleCenters;
        long max=-INFINITY;
        possibleCenters.clear();
        for(long f=0;f<kReachableGraph.nodes.size();f++){
            Node* nodeTemp=&kReachableGraph.nodes[f];
            if(!nodeTemp->isCenter){
                long degree=degreeOut_MEMB(nodeTemp);
//                std::cout<<nodeTemp->originalID<<" "<<degree<<'\n';
                if(degree>=max){
                    if(degree>max){
                        possibleCenters.clear();
                    }
                    max=degree;
                    possibleCenters.push_back(nodeTemp);
                }
            }
        }
//        std::cout<<"__________"<<'\n';
        long index=(long)(Functions::random(0, possibleCenters.size(), true));
        node=possibleCenters[index];
        
//            for(long i=0;i<kReachableGraph.nodes.size();i++){
//                Node* node=&kReachableGraph.nodes[i];
//                if(kReachableGraph.getDegree(node)>0){
//                    extendedDegrees.push(node);
//                }
//            }
        
            numColor++;
//        }
    
    }
    
    
//    for(long i=0;i<graph->nodes.size();i++){
//        graph->nodes[i].isCovered=false;
//        graph->nodes[i].degreeModifierOut=0;
//    }
//    kReachableGraph.resetGraph();
//    graph->generateKReachableGraph(&kReachableGraph, distance, indexDistance);
    
    
//    Graph finalGraph;
//    for(long i=0;i<kReachableGraph.nodes.size();i++){
//        finalGraph.addNode();
//        //        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
//        //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
//    }
    
    
    
//    for(long i=0;i<kReachableGraph.nodes.size();i++){
//        //        kReachableGraph->addNode();
//        finalGraph.nodes[i].originalID=kReachableGraph.nodes[i].originalID;
//        finalGraph.nodes[i].nodeThatRepresents=&kReachableGraph.nodes[i];
//        kReachableGraph.nodes[i].nodeRepresentedBy=&finalGraph.nodes[i];
//    }
    
    
    
    
    
    
    
    
    
    for(long i=0;i<kReachableGraph.nodes.size();i++){
        Node* node=&kReachableGraph.nodes[i];
        if(!node->isCenter){
            long min=INFINITY;
//            Transition* transitionChosen=NULL;
//            std::vector<Node*> possibleCenters;
            possibleCenters.clear();
            for(long j=0;j<node->transitions.size();j++){
                //                std::vector<Transition*> transitionsToCenters;
                
                if(node->transitions[j]->b->isCenter){
                    if(node->transitions[j]->weight<=min){
                        if(node->transitions[j]->weight<min){
                            possibleCenters.clear();
                        }
                        min=node->transitions[j]->weight;
                        possibleCenters.push_back(node->transitions[j]->b);
                        //                        transitionChosen=node->transitions[j];
                    }
                    //                    transitionsToCenters.push_back(node->transitions[j]);
                }
            }
            long minNumColor=INFINITY;
//            Node* centerChosen=NULL;
            
            for (long j=0;j<possibleCenters.size();j++){
                if(possibleCenters[j]->numColor<minNumColor){
//                    centerChosen=possibleCenters[j];
                    minNumColor=possibleCenters[j]->numColor;
                    //                    possibleTransitions.push_back(node->transitions[j]);
//                    transitionChosen=possibleTransitions[j];
                }
                
            }
            possibleCenters.clear();
//            Transition trans;
//            trans.a=transitionChosen->b->nodeRepresentedBy;
//            trans.b=node->nodeRepresentedBy;
//            trans.weight=transitionChosen->weight;
//            trans.otherWeights=transitionChosen->otherWeights;
//            finalGraph.addTransition(trans);
            node->numColor=minNumColor;
            node->nodeThatRepresents->numColor=minNumColor;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
//    for(long i=0;i<finalGraph.nodes.size();i++){
//        Graph cluster;
//        std::vector<Node*> nodesInCluster;
//         Node* node=&finalGraph.nodes[i];
//        if(node->transitions.size()>0){
//            nodesInCluster.push_back(node->nodeThatRepresents->nodeThatRepresents);
//        }
//        for(long j=0;j<node->transitions.size();j++){
//            nodesInCluster.push_back(node->transitions[j]->b->nodeThatRepresents->nodeThatRepresents);
//        }
//        graph->getInducedSubgraph(&cluster, nodesInCluster);
//        clusters.push_back(cluster);
//        
//        
//    }
    for(long i=0;i<graph->nodes.size();i++){
        graph->nodes[i].isCovered=false;
        graph->nodes[i].isCenter=false;
        graph->nodes[i].degreeModifierOut=0;
        
    }
    
//    //            lines.clear();
//    std::vector<std::string> lines;
//    for(long i=0;i<kReachableGraph.transitions.size();i++){
//        
//        std::stringstream line;
//        line<<kReachableGraph.transitions[i].a->originalID<<" "<<kReachableGraph.transitions[i].b->originalID<<" "<<kReachableGraph.transitions[i].a->numColor<<" "<<kReachableGraph.transitions[i].b->numColor;
//        lines.push_back(line.str());
//        //            }
//    }
//    TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/kReachableLondon.txt", lines, false);
//    
//    
//    
//    
//    lines.clear();
//    for(long i=0;i<graph->transitions.size();i++){
//        //            for(long j=0;j<modules[i].transitions.size();j++){
//        std::stringstream line;
//        line<<graph->transitions[i].a->originalID<<" "<<graph->transitions[i].b->originalID<<" "<<graph->transitions[i].a->numColor<<" "<<graph->transitions[i].b->numColor;
//        lines.push_back(line.str());
//        //            }
//    }
//    TextFile::writeToFile("/Users/carlos/Documents/results/clustersFromPercolation/UK/modules/clusterLondon.txt", lines, false);

    
    
    
    
    
}

void Graph::generateKReachableGraph(Graph* kReachableGraph, double distance, int indexDistance){
    if(indexDistance!=indexOfMainDistanceInOtherDistances){
        for(long i=0;i<transitions.size();i++){
            transitions[i].weight=transitions[i].otherWeights[indexDistance];
        }
    }
//    indexOfMainDistanceInOtherDistances=indexDistance;
    for(long i=0;i<nodes.size();i++){
        kReachableGraph->addNode();
        //        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
        //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
    }
    for(long i=0;i<nodes.size();i++){
        //        kReachableGraph->addNode();
        kReachableGraph->nodes[i].numColor=nodes[i].numColor;
        kReachableGraph->nodes[i].isCovered=nodes[i].isCovered;
//        if(!kReachableGraph->nodes[i].isCovered){
//            kReachableGraph->nodes[i].degreeModifierOut=1;
//        }else{
//            kReachableGraph->nodes[i].degreeModifierOut=0;
//        }
        kReachableGraph->nodes[i].isCenter=nodes[i].isCenter;
        kReachableGraph->nodes[i].originalID=nodes[i].originalID;
        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
        kReachableGraph->nodes[i].location=nodes[i].location;
        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
    }
    for(long h=0;h<nodes.size();h++){
        Node* nodeInit=&(nodes[h]);
//        if(!nodeInit->isCovered){
    //        nodeInit->minDistance=0;
            Node* startNode=nodeInit;
            std::vector<Node*> nodesCutoff;
            //        std::vector<Node*> nodesAtDistanceK;
            Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
            nodesCutoff.push_back(startNode);
            startNode->inCutoff=true;
            //        CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
            //        nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,indexDistance,1);
            nodesToCheckDijkstra.push(startNode);
            startNode->inDijkstra=true;
            startNode->minDistance=0;
            //        generateKReachableGraphAux(this, nodesToCheckDijkstra, nodesCutoff, nodesAtDistanceK, distance, indexDistance);
            calculateDijkstraSpeed(startNode,distance,nodesCutoff,nodesToCheckDijkstra);
            
             for(long i=0;i<nodesCutoff.size();i++){
    //        for (long i=0;i<nodes.size();i++){
    //            if(!nodes[i].inCutoff){
//                 if(!nodesCutoff[i]->isCovered){
                    Transition trans;
                    trans.a=nodeInit->nodeRepresentedBy;
                    trans.b=nodesCutoff[i]->nodeRepresentedBy;
                    trans.weight=nodesCutoff[i]->minDistance;
                    kReachableGraph->addTransition(trans);
                    nodesCutoff[i]->nodeRepresentedBy->diffusionValue+=exp(-pow((nodesCutoff[i]->minDistance),2.0)/(2.0*pow((distance/3.0),2.0)));
//                 std::cout<<"diffusion added = "<<exp(-pow((nodesCutoff[i]->minDistance),2.0)/(2.0*pow((distance/3.0),2.0)))<<" "<<nodesCutoff[i]->minDistance<<" "<<distance<<" "<<nodesCutoff[i]->diffusionValue<<'\n';
//                }
                    //                nodes[j].minOtherDistances[indexDistance]=INFINITY;
    //            }else{
                    //        }
                    //        for(long i=0;i<nodesCutoff.size();i++){
                    nodesCutoff[i]->inCutoff=false;
                    nodesCutoff[i]->inDijkstra=false;
                    nodesCutoff[i]->numChildren=0;
                    nodesCutoff[i]->numChildrenThatReachedMe=0;
                    nodesCutoff[i]->parent=NULL;
                    nodesCutoff[i]->minDistance=INFINITY;
                    nodesCutoff[i]->valueToPass=nodes[i].originalValueToPass;
                    //            if (calculateOtherDistances){
                    //                for (int j=0;j<numberDistances;j++){
                    //                    nodesCutoff[i]->numOtherChildren[j]=0;
                    //                    nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
                    //                    nodesCutoff[i]->otherParents[j]=NULL;
                    //                    nodesCutoff[i]->minOtherDistances[j]=INFINITY;
                    //                    nodesCutoff[i]->valuesToPass[j]= nodesCutoff[i]->originalValuesToPass[j];
                    //                }
                    //            }
                    
    //            }
            }
            nodesToCheckDijkstra.clear();
            nodesCutoff.clear();
//        }
        
        //        nodesAtDistanceK.clear();
        
        
    }
    if(bidirectional){
        kReachableGraph->transformToBidirectional();
    }
    if(indexDistance!=indexOfMainDistanceInOtherDistances){
        for(long i=0;i<transitions.size();i++){
            transitions[i].weight=transitions[i].otherWeights[indexOfMainDistanceInOtherDistances];
        }
    }
    
}


//void Graph::recalculateKReachableGraph(Graph* originalKReachableGraph,Graph* kReachableGraph, double distance, int indexDistance){
////    for(long i=0;i<transitions.size();i++){
////        transitions[i].weight=transitions[i].otherWeights[indexDistance];
////    }
////    indexOfMainDistanceInOtherDistances=indexDistance;
//    if(originalKReachableGraph!=kReachableGraph){
//        for(long i=0;i<nodes.size();i++){
//            kReachableGraph->addNode();
//            //        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
//            //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
//        }
//    
//        for(long i=0;i<nodes.size();i++){
//            //        kReachableGraph->addNode();
//            kReachableGraph->nodes[i].numColor=nodes[i].numColor;
//            kReachableGraph->nodes[i].isCovered=nodes[i].isCovered;
//            if(!kReachableGraph->nodes[i].isCovered){
//                kReachableGraph->nodes[i].degreeModifierOut=1;
//            }else{
//                kReachableGraph->nodes[i].degreeModifierOut=0;
//            }
//            kReachableGraph->nodes[i].isCenter=nodes[i].isCenter;
//            kReachableGraph->nodes[i].originalID=nodes[i].originalID;
//            kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
//    //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
//        }
//    }else{
//        for(long i=0;i<nodes.size();i++){
//            //        kReachableGraph->addNode();
////            kReachableGraph->nodes[i].numColor=nodes[i].numColor;
////            kReachableGraph->nodes[i].isCovered=nodes[i].isCovered;
//            if(!kReachableGraph->nodes[i].isCovered){
//                kReachableGraph->nodes[i].degreeModifierOut=1;
//            }else{
//                kReachableGraph->nodes[i].degreeModifierOut=0;
//            }
////            kReachableGraph->nodes[i].isCenter=nodes[i].isCenter;
////            kReachableGraph->nodes[i].originalID=nodes[i].originalID;
////            kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
//            //        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
//        }
//    }
//    
//    
//    for(long h=0;h<originalKReachableGraph->nodes.size();h++){
//        
//        if(originalKReachableGraph==kReachableGraph){
//            std::vector<Vector_elem<Transition> > transitionsTemp;
////            std::vector<long> indexOfTransToKeep;
//            for(long g=0;g<originalKReachableGraph->nodes[h].transitions.size();g++){
//                if(!originalKReachableGraph->nodes[h].transitions[g]->b->nodeThatRepresents->isCovered){
////                    indexOfTransToKeep.push_back(g);
//                    Vector_elem<Transition> vectorTransition=originalKReachableGraph->nodes[h].transitions.getObject(g);
//                    transitionsTemp.push_back(vectorTransition);
//                }
//            }
//            kReachableGraph->nodes[h].transitions.clear();
//            for(long g=0;g<transitionsTemp.size();g++){
//                kReachableGraph->nodes[h].transitions.push_back(transitionsTemp[g]);
//            }
//        }else{
//        
//            for(long g=0;g<originalKReachableGraph->nodes[h].transitions.size();g++){
//                if(!originalKReachableGraph->nodes[h].transitions[g]->b->nodeThatRepresents->isCovered){
//                    Transition trans;
//                    trans.a=&kReachableGraph->nodes[originalKReachableGraph->nodes[h].id];
//                    trans.b=&kReachableGraph->nodes[originalKReachableGraph->nodes[h].transitions[g]->b->id];
//                    trans.weight=originalKReachableGraph->nodes[h].transitions[g]->weight;
//                    kReachableGraph->addTransition(trans);
//                }
//            }
//        }
////        Node* nodeInit=&(nodes[h]);
////        //        if(!nodeInit->isCovered){
////        //        nodeInit->minDistance=0;
////        Node* startNode=nodeInit;
////        std::vector<Node*> nodesCutoff;
////        //        std::vector<Node*> nodesAtDistanceK;
////        Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
////        nodesCutoff.push_back(startNode);
////        startNode->inCutoff=true;
////        //        CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
////        //        nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,indexDistance,1);
////        nodesToCheckDijkstra.push(startNode);
////        startNode->inDijkstra=true;
////        startNode->minDistance=0;
////        //        generateKReachableGraphAux(this, nodesToCheckDijkstra, nodesCutoff, nodesAtDistanceK, distance, indexDistance);
////        calculateDijkstraSpeed(startNode,distance,nodesCutoff,nodesToCheckDijkstra);
////        
////        for(long i=0;i<nodesCutoff.size();i++){
////            //        for (long i=0;i<nodes.size();i++){
////            //            if(!nodes[i].inCutoff){
////            if(!nodesCutoff[i]->isCovered){
////                Transition trans;
////                trans.a=nodeInit->nodeRepresentedBy;
////                trans.b=nodesCutoff[i]->nodeRepresentedBy;
////                trans.weight=nodesCutoff[i]->minDistance;
////                kReachableGraph->addTransition(trans);
////            }
////            //                nodes[j].minOtherDistances[indexDistance]=INFINITY;
////            //            }else{
////            //        }
////            //        for(long i=0;i<nodesCutoff.size();i++){
////            nodesCutoff[i]->inCutoff=false;
////            nodesCutoff[i]->inDijkstra=false;
////            nodesCutoff[i]->numChildren=0;
////            nodesCutoff[i]->numChildrenThatReachedMe=0;
////            nodesCutoff[i]->parent=NULL;
////            nodesCutoff[i]->minDistance=INFINITY;
////            nodesCutoff[i]->valueToPass=nodes[i].originalValueToPass;
////            //            if (calculateOtherDistances){
////            //                for (int j=0;j<numberDistances;j++){
////            //                    nodesCutoff[i]->numOtherChildren[j]=0;
////            //                    nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
////            //                    nodesCutoff[i]->otherParents[j]=NULL;
////            //                    nodesCutoff[i]->minOtherDistances[j]=INFINITY;
////            //                    nodesCutoff[i]->valuesToPass[j]= nodesCutoff[i]->originalValuesToPass[j];
////            //                }
////            //            }
////            
////            //            }
////        }
////        nodesToCheckDijkstra.clear();
////        nodesCutoff.clear();
////        //        }
////        
////        //        nodesAtDistanceK.clear();
//        
//        
//    }
//    
//}




void Graph::generateInverseOfKReachableGraph(Graph* inverseOfKReachableGraph, double distance, int indexDistance){
    for(long i=0;i<transitions.size();i++){
        transitions[i].weight=transitions[i].otherWeights[indexDistance];
    }
    indexOfMainDistanceInOtherDistances=indexDistance;
    for(long i=0;i<nodes.size();i++){
        inverseOfKReachableGraph->addNode();
//        kReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
//        nodes[i].nodeRepresentedBy=&kReachableGraph->nodes[i];
    }
    for(long i=0;i<nodes.size();i++){
//        kReachableGraph->addNode();
        inverseOfKReachableGraph->nodes[i].originalID=nodes[i].originalID;
        inverseOfKReachableGraph->nodes[i].nodeThatRepresents=&nodes[i];
        nodes[i].nodeRepresentedBy=&inverseOfKReachableGraph->nodes[i];
    }
    for(long h=0;h<nodes.size();h++){
        Node* nodeInit=&(nodes[h]);
        nodeInit->minOtherDistances[indexDistance]=0;
        Node* startNode=nodeInit;
        std::vector<Node*> nodesCutoff;
//        std::vector<Node*> nodesAtDistanceK;
        Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        nodesCutoff.push_back(startNode);
        startNode->inCutoff=true;
//        CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
//        nodesToCheckDijkstra.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances,indexDistance,1);
        nodesToCheckDijkstra.push(startNode);
        startNode->inDijkstra=true;
        startNode->minDistance=0;
//        generateKReachableGraphAux(this, nodesToCheckDijkstra, nodesCutoff, nodesAtDistanceK, distance, indexDistance);
        calculateDijkstraSpeed(startNode,distance,nodesCutoff,nodesToCheckDijkstra);
        
        
        for (long i=0;i<nodes.size();i++){
            if(!nodes[i].inCutoff){
                Transition trans;
                trans.a=nodeInit->nodeRepresentedBy;
                trans.b=nodes[i].nodeRepresentedBy;
                trans.weight=nodes[i].minDistance;
                inverseOfKReachableGraph->addTransition(trans);
//                nodes[j].minOtherDistances[indexDistance]=INFINITY;
            }else{
    //        }
    //        for(long i=0;i<nodesCutoff.size();i++){
                nodes[i].inCutoff=false;
                nodes[i].inDijkstra=false;
                nodes[i].numChildren=0;
                nodes[i].numChildrenThatReachedMe=0;
                nodes[i].parent=NULL;
                nodes[i].minDistance=INFINITY;
                nodes[i].valueToPass=nodes[i].originalValueToPass;
    //            if (calculateOtherDistances){
    //                for (int j=0;j<numberDistances;j++){
    //                    nodesCutoff[i]->numOtherChildren[j]=0;
    //                    nodesCutoff[i]->numOtherChildrenThatReachedMe[j]=0;
    //                    nodesCutoff[i]->otherParents[j]=NULL;
    //                    nodesCutoff[i]->minOtherDistances[j]=INFINITY;
    //                    nodesCutoff[i]->valuesToPass[j]= nodesCutoff[i]->originalValuesToPass[j];
    //                }
    //            }
        
            }
        }
        nodesToCheckDijkstra.clear();
        nodesCutoff.clear();
        
//        nodesAtDistanceK.clear();
        
        
    }
    
}
//void Graph::generateKReachableGraphAux(Graph* graph,Heap<Node*> &nodesToCheckDijkstra,std::vector<Node*> &nodesCutoff, std::vector<Node*> &nodesAtDistanceK, double distanceLimit, int indexDistance){
//    
//    CompareFunc<Node*> compare=CompareFunc<Node*> (indexDistance,1);
////    nodesToCheckDijkstra.heap[0]->minOtherDistances[indexDistance]=0;
//    
//    
//    while (nodesToCheckDijkstra.size() > 0)
//    {
//        
//        Node* startNode = (nodesToCheckDijkstra.pop());
//        startNode->inDijkstra=false;
//        
//        
//        for (long i = 0; i < startNode->transitions.size(); i++)
//        {
//            Transition* trans = (startNode->transitions[i]);
//            
//            
//            Node* nodeB;
//            
//            bool nodeBSet=false;
//            
//            if (trans->b!=NULL)
//            {
//                nodeB=trans->b;
//            }
//            else
//            {
//                nodeB=&(nodes[trans->idB]);
//            }
//            
//            if (nodeB->inCutoff)
//            {
//                nodeBSet=true;
//            }
//
//            
//            
//            
//            
//            
//            
//            
//            
//            
//            if (nodeB!=NULL)
//            {
//                
//                
//                double  possibleDistance=trans->otherWeights[indexDistance] + startNode->minOtherDistances[indexDistance];
//                if ((possibleDistance < distanceLimit||distanceLimit==0)&&(nodeB->minOtherDistances[indexDistance]==INFINITY||(possibleDistance) < nodeB->minOtherDistances[indexDistance]))
//                {
//                    double previousDistance=nodeB->minOtherDistances[indexDistance];
//                    if (!nodeBSet)
//                    {
//                        nodeB->inCutoff=true;
//                        nodesCutoff.push_back(nodeB);
//                    }
//                    else
//                    {
//                        nodeB->otherParents[indexDistance]->numOtherChildren[indexDistance]--;
//                    }
//                    nodeB->otherParents[indexDistance]=startNode;
//                    startNode->numOtherChildren[indexDistance]++;
//                    
//                    
//                    nodeB->minOtherDistances[indexDistance]=possibleDistance;
//                    
//                    if (!nodeB->inDijkstra)
//                    {
//                        
//                        nodesToCheckDijkstra.push(nodeB);
//                        nodeB->inDijkstra=true;
//                    }
//                    else
//                    {
////                        if(nodeB->minOtherDistances[indexDistance]<nodesToCheckDijkstra.getMin(compare)->minOtherDistances[indexDistance]){
//                            nodesToCheckDijkstra.update(nodeB,previousDistance);
////                        }
//                    }
//                }else if (possibleDistance >= distanceLimit){
//                    nodeB->minOtherDistances[indexDistance]=possibleDistance;
//                    
//                }
//                
//            }
//            
//        }
//        
//        
//    }
//}


void Graph::createLineGraph(Graph* graphOrigin, Graph* lineGraph){
    long idTransitions=0;
    bool alreadyExistIds=false;

    for(long i=0;i<graphOrigin->transitions.size();i++){
//        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
            if(graphOrigin->transitions[i].originalID!=-1){
                alreadyExistIds=true;
            }else{
                graphOrigin->transitions[i].originalID=idTransitions;
//                idTransitions++;
            
            }
//            graphOrigin->transitions[i].id=graphOrigin->transitions[i].originalID;
        graphOrigin->transitions[i].id=idTransitions;
        idTransitions++;
//            for(long h=0; h<nodes[i].transitions[j].b->transitions.size(); h++)
//            {
//                if (nodes[i].transitions[j].b->transitions[h].b==&nodes[i])
//                {
//                    nodes[i].transitions[j].oppositeTransitionId=nodes[i].transitions[j].b->transitions[h].id;
//                    nodes[i].transitions[j].b->transitions[h].oppositeTransitionId=nodes[i].transitions[j].id;
//                }
//            }
            
        
            lineGraph->addNode();
//        }
    }
    int indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[METRIC].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->indexOfMainDistanceInOtherDistances=indexDistance;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[TOPOLOGICAL].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[ANGULAR].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[COGNITIVE].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[POTENTIAL_FIELD].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
   

    long idTransitionsLineGraph=0;
    
  
    long numTransitions=0;
//    std::cout<<"numTransitions originalGraph "<<graphOrigin->transitions.size()<<'\n';;
//        std::cout<<"numNodes lineGraph "<<lineGraph->nodes.size()<<'\n';;
    for(long i=0;i<graphOrigin->transitions.size();i++){
//    for(long i=0;i<graphOrigin->nodes.size();i++){
//        
//        
//        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
//                        long idNodeA=graphOrigin->nodes[i].transitions[j]->id;
            long idNodeA=graphOrigin->transitions[i].id;
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            
            double x=(graphOrigin->transitions[i].a->location.x+graphOrigin->transitions[i].b->location.x)/2;
            double y=(graphOrigin->transitions[i].a->location.y+graphOrigin->transitions[i].b->location.y)/2;
            lineGraph->nodes[idNodeA].location=Point2d(x,y);
//            lineGraph->nodes[idNodeA].transitionThatRepresents=&(graphOrigin->transitions[i]);
            lineGraph->nodes[idNodeA].transitionThatRepresents=&(graphOrigin->transitions[i]);
            graphOrigin->transitions[i].nodeOfLineGraphThatRepresentsThis=&(lineGraph->nodes[idNodeA]);
            lineGraph->nodes[idNodeA].originalID=graphOrigin->transitions[i].originalID;
//        std::cout<<"setting transitions in createlinegraph "<<i<<'\n';;
//        }
    }
    
    for(long i=0;i<graphOrigin->nodes.size();i++){

        
        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
//            long idNodeA=graphOrigin->nodes[i].transitions[j].id;
            Node* nodeA=&graphOrigin->nodes[i];
            
            Transition* transA=graphOrigin->nodes[i].transitions[j];
            Node* nodeB=transA->b;
            Transition* transB;

            for(long h=0;h<nodeB->transitions.size();h++){
                transB=nodeB->transitions[h];
                Node* nodeC=transB->b;
//                if(&(graphOrigin->nodes[i].transitions[j].b->transitions[h])!=graphOrigin->nodes[i].transitions[j].getSimetricTransition()){
                    long idNodeA=transA->id;
                    long idNodeB=transB->id;
                    if(idNodeA!=idNodeB||lineGraph->allowLoops){
//                if(true){
                        Transition trans;
                        numTransitions++;
                        trans.id=idTransitionsLineGraph;
//                        trans.originalID=idTransitionsLineGraph;
                        trans.a=&lineGraph->nodes[idNodeA];
                        trans.b=&lineGraph->nodes[idNodeB];
                        
                        
//                        std::cout<<"in create linegraph "<<trans.a->id<<" "<<trans.b->id<<'\n';
//                        std::cout<<"in create linegraph "<<trans.a->originalID<<" "<<trans.b->originalID<<'\n';
                    
                        trans.weight=transA->weight/2+transB->weight/2;
                        trans.otherWeights.push_back(trans.weight);
                        trans.otherWeights.push_back(1);
                        
                      
                        
                        double angle=Functions::getAngularDistance(nodeA->location,nodeB->location,nodeC->location);

                        
                        
                
                        trans.otherWeights.push_back(angle);
                        
                        
                        double cognitiveWeight;

                        
                        cognitiveWeight=pow((pow(((1/(1+pow(exp(-(angle/180*14-7)),1)))),1)),1)*180;
                        
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                        if(cognitiveWeight>180){
                            cognitiveWeight=180;
                        }

                        
                        trans.otherWeights.push_back(cognitiveWeight);
                        if(graphOrigin->getIndexesOfDistanceType(Graph::POTENTIAL_FIELD).size()>0){
                            double potentialWeight=(transA->otherWeights[graphOrigin->getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]]/2+transB->otherWeights[graphOrigin->getIndexesOfDistanceType(Graph::POTENTIAL_FIELD)[0]])/2;
                            trans.otherWeights.push_back(potentialWeight);
                        }else{
                            trans.otherWeights.push_back(1);
                        }
                        
        //                 trans.nodeInGraphAfterLineGraphGeneration=graphOrigin->nodes[i].transitions[j].b;
                    
                        if(graphOrigin->bidirectional==true&&graphOrigin->strictlyDirectional==true){
                        
                            if(graphOrigin->nodes[i].transitions[j]->b->transitions[h]->b==&graphOrigin->nodes[i]){
                                trans.weight=0;
                                for(long g=0;g<trans.otherWeights.size();g++){
                                    trans.otherWeights[g]=0;
                                }
                            }
                        }
                    
                        lineGraph->addDirectedTransition(trans);
                    
                   

                        idTransitionsLineGraph++;
    //                }
                    }

            }
        }
        
    }
//    if(graphOrigin->bidirectional){
//        lineGraph->transformToBidirectional();
//    }
//    std::cout<<"numInsertionsInTransitions lineGraph "<<numTransitions<<'\n';
//        std::cout<<"numTransitions lineGraph "<<lineGraph->transitions.size()<<'\n';

    
}



void Graph::createInformationalLineGraph(Graph* graphOrigin, Graph* lineGraph){
    long idTransitions=0;
//    bool alreadyExistIds=false;
    
    for(long i=0;i<graphOrigin->transitions.size();i++){
        //        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
        if(graphOrigin->transitions[i].originalID!=-1){
//            alreadyExistIds=true;
        }else{
            graphOrigin->transitions[i].originalID=idTransitions;
//            idTransitions++;
            
        }
//        graphOrigin->transitions[i].id=graphOrigin->transitions[i].originalID;
        graphOrigin->transitions[i].id=idTransitions;
        idTransitions++;
        
        //            for(long h=0; h<nodes[i].transitions[j].b->transitions.size(); h++)
        //            {
        //                if (nodes[i].transitions[j].b->transitions[h].b==&nodes[i])
        //                {
        //                    nodes[i].transitions[j].oppositeTransitionId=nodes[i].transitions[j].b->transitions[h].id;
        //                    nodes[i].transitions[j].b->transitions[h].oppositeTransitionId=nodes[i].transitions[j].id;
        //                }
        //            }
        
        
        lineGraph->addNode();
        //        }
    }
    int indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[METRIC].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->indexOfMainDistanceInOtherDistances=indexDistance;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
   
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[TOPOLOGICAL].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[ANGULAR].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[COGNITIVE].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[INFORMATIONAL].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    long idTransitionsLineGraph=0;
    
    
    long numTransitions=0;
    
    for(long i=0;i<graphOrigin->nodes.size();i++){
        
        
        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
            long idNodeA=graphOrigin->nodes[i].transitions[j]->id;
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            pushNewDistance(&lineGraph->nodes[idNodeA]);
            
            double x=(graphOrigin->nodes[i].transitions[j]->a->location.x+graphOrigin->nodes[i].transitions[j]->b->location.x)/2;
            double y=(graphOrigin->nodes[i].transitions[j]->a->location.y+graphOrigin->nodes[i].transitions[j]->b->location.y)/2;
            lineGraph->nodes[idNodeA].location=Point2d(x,y);
            lineGraph->nodes[idNodeA].nameRoad=graphOrigin->nodes[i].transitions[j]->nameRoad;
            lineGraph->nodes[idNodeA].levelHierarchyRoad=graphOrigin->nodes[i].transitions[j]->levelHierarchyRoad;
            
            lineGraph->nodes[idNodeA].transitionThatRepresents=(graphOrigin->nodes[i].transitions[j]);
            graphOrigin->nodes[i].transitions[j]->nodeOfLineGraphThatRepresentsThis=&(lineGraph->nodes[idNodeA]);
            lineGraph->nodes[idNodeA].originalID=graphOrigin->nodes[i].transitions[j]->originalID;
        }
    }
    
    for(long i=0;i<graphOrigin->nodes.size();i++){
        
        
        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
            //            long idNodeA=graphOrigin->nodes[i].transitions[j].id;
            double angleMin=INFINITY;
            long indexSmallestAngle=-1;
            for(long h=0;h<graphOrigin->nodes[i].transitions[j]->b->transitions.size();h++){
                double angle=Functions::getAngularDistance(graphOrigin->nodes[i].location,graphOrigin->nodes[i].transitions[j]->b->location,graphOrigin->nodes[i].transitions[j]->b->transitions[h]->b->location);
                if(angle<angleMin){
                    angleMin=angle;
                    indexSmallestAngle=h;
                }
            }
            for(long h=0;h<graphOrigin->nodes[i].transitions[j]->b->transitions.size();h++){
                //                if(&(graphOrigin->nodes[i].transitions[j].b->transitions[h])!=graphOrigin->nodes[i].transitions[j].getSimetricTransition()){
                long idNodeA=graphOrigin->nodes[i].transitions[j]->id;
                long idNodeB=graphOrigin->nodes[i].transitions[j]->b->transitions[h]->id;
                if(idNodeA!=idNodeB||lineGraph->allowLoops){
                    Transition trans;
                    numTransitions++;
                    trans.id=idTransitionsLineGraph;
                    trans.originalID=idTransitionsLineGraph;
                    trans.a=&lineGraph->nodes[idNodeA];
                    trans.b=&lineGraph->nodes[idNodeB];
                    trans.weight=graphOrigin->nodes[i].transitions[j]->weight/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->weight/2;
                    trans.otherWeights.push_back(trans.weight);
                    trans.otherWeights.push_back(1);
                    double angle=Functions::getAngularDistance(graphOrigin->nodes[i].location,graphOrigin->nodes[i].transitions[j]->b->location,graphOrigin->nodes[i].transitions[j]->b->transitions[h]->b->location);
                    
                    
                    
                    
                    trans.otherWeights.push_back(angle);
                    
                    
                    double cognitiveWeight;
                    
                    
                    cognitiveWeight=pow((pow(((1/(1+pow(exp(-(angle/180*14-7)),1)))),1)),1)*180;
                    
                    if(cognitiveWeight<0){
                        cognitiveWeight=0;
                    }
                    if(cognitiveWeight>180){
                        cognitiveWeight=180;
                    }
                    
                    
                    trans.otherWeights.push_back(cognitiveWeight);
                    
                    double informationalWeight=1;
                    if(trans.a->levelHierarchyRoad<4&&trans.b->levelHierarchyRoad<4){
                        if (trans.a->nameRoad==trans.b->nameRoad){
                            informationalWeight=0;
                        }
                    }
                    if(trans.a->levelHierarchyRoad==4&&trans.b->levelHierarchyRoad==4){
                        if (h==indexSmallestAngle&&angle<90){
                            informationalWeight=0;
                            
                        }
                    }
                    trans.otherWeights.push_back(informationalWeight);
                    
                    
                    
                    //                 trans.nodeInGraphAfterLineGraphGeneration=graphOrigin->nodes[i].transitions[j].b;
                    
                    if(graphOrigin->bidirectional==true){
                    
                        if(graphOrigin->nodes[i].transitions[j]->b->transitions[h]->b==&graphOrigin->nodes[i]){
                            trans.weight=0;
                            for(long g=0;g<trans.otherWeights.size();g++){
                                trans.otherWeights[g]=0;
                            }
                        }
                    }
                    
                    
                    lineGraph->addDirectedTransition(trans);
                    
                    idTransitionsLineGraph++;
                    //                }
                }
            }
        }
        
    }
    //    if(graphOrigin->bidirectional){
    //        lineGraph->transformToBidirectional();
    //    }
    
    
    hierarchicalBreakOfNetwork(graphOrigin,lineGraph);
    
    std::cout<<"numTransitions lineGraph "<<numTransitions<<'\n';
    
    
}





void Graph::hierarchicalBreakOfNetwork(Graph* graph,Graph* lineGraph){
    
    for(long i=0;i<graph->nodes.size();i++){
        std::unordered_map<std::string,vector<Transition*> > pairedStreets;
        std::vector<Transition*> pairedStreetsLowLevel;
                std::vector<Transition*> symetricPairedStreetsLowLevel;
        std::vector<Node*> nodes;
        std::unordered_map<unsigned long long,long> nodesInVicinity;
        bool existHighHierarchicalContinuation=false;
        for(long j=0;j<graph->nodes[i].transitions.size();j++){

            if(graph->nodes[i].transitions[j]->levelHierarchyRoad<4){
                pairedStreets[graph->nodes[i].transitions[j]->nameRoad].push_back(graph->nodes[i].transitions[j]);
                if(pairedStreets[graph->nodes[i].transitions[j]->nameRoad].size()>=2){
                    existHighHierarchicalContinuation=true;
                }
            }else{
                pairedStreetsLowLevel.push_back(graph->nodes[i].transitions[j]);
            }
            
            
        }
        if(existHighHierarchicalContinuation){
            for (long j=0;j<pairedStreetsLowLevel.size();j++){
                Transition* trans=pairedStreetsLowLevel[j]->getSimetricTransition();
                nodes.push_back(trans->nodeOfLineGraphThatRepresentsThis);
                nodesInVicinity[trans->nodeOfLineGraphThatRepresentsThis->originalID]=2;
                nodes.push_back(pairedStreetsLowLevel[j]->nodeOfLineGraphThatRepresentsThis);
                nodesInVicinity[pairedStreetsLowLevel[j]->nodeOfLineGraphThatRepresentsThis->originalID]=2;
            }
            
            for(long j=0;j<nodes.size();j++){
                for(long h=0;h<nodes[j]->transitions.size();h++){
                    if(nodesInVicinity[nodes[j]->transitions[h]->b->originalID]==2){
                        Transition* trans=nodes[j]->transitionThatRepresents;
                        Transition* symetricTrans=trans->getSimetricTransition();
                        Node* symetricNode=symetricTrans->nodeOfLineGraphThatRepresentsThis;
                        if(nodes[j]->transitions[h]->b!=symetricNode){
                            nodes[j]->transitions[h]->otherWeights[lineGraph->getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]]=1;
                        }else{
//                            std::cout<<"sym. "<<nodes[j]->transitions[h].otherWeights[lineGraph->getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]];
                        }
                    }
                }
            }
        }
        
    }

    
//    for(long i=0;i<graph->nodes.size();i++){
//        if(graph->nodes[i].levelHierarchyRoad<4){
//            std::unordered_map<signed long long,long> nodesByOriginalId;
//            for(long j=0;j<graph->nodes[i].transitions.size();j++){
//                nodesByOriginalId[graph->nodes[i].transitions[j].b->originalID]=2;
//            }
//            
//            for(long j=0;j<graph->nodes[i].transitions.size();j++){
//                if(graph->nodes[i].transitions[j].b->levelHierarchyRoad==4){
//                    for(long h=0;h<graph->nodes[i].transitions[j].b->transitions.size();h++){
//                        if(nodesByOriginalId[graph->nodes[i].transitions[j].b->transitions[h].b->originalID]==2){
//                            if(graph->nodes[i].transitions[j].b->transitions[h].b->levelHierarchyRoad==4){
//                                graph->nodes[i].transitions[j].b->levelHierarchyRoad=(graph->nodes[i].transitions[j].b->levelHierarchyRoad+graph->nodes[i].levelHierarchyRoad)/2;
//                                graph->nodes[i].transitions[j].b->transitions[h].b->levelHierarchyRoad=(graph->nodes[i].transitions[j].b->transitions[h].b->levelHierarchyRoad+graph->nodes[i].levelHierarchyRoad)/2;
//                                graph->nodes[i].transitions[j].b->transitions[h].otherWeights[graph->getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]]=1;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
    
    
//    for(long i=0;i<graph->nodes.size();i++){
//        if(graph->nodes[i].levelHierarchyRoad<4){
//            int currentHierarchicalLevel=graph->nodes[i].levelHierarchyRoad;
//            std::unordered_map<signed long long,long> nodesByOriginalId;
//            for(long j=0;j<graph->nodes[i].transitions.size();j++){
//                nodesByOriginalId[graph->nodes[i].transitions[j].b->originalID]=2;
//            }
//            
//            for(long j=0;j<graph->nodes[i].transitions.size();j++){
//                if(graph->nodes[i].transitions[j].b->levelHierarchyRoad<currentHierarchicalLevel){
//                    for(long h=0;h<graph->nodes[i].transitions[j].b->transitions.size();h++){
//                        if(nodesByOriginalId[graph->nodes[i].transitions[j].b->transitions[h].b->originalID]==2){
//                            if(graph->nodes[i].transitions[j].b->transitions[h].otherWeights[graph->getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]]==0){
//                                graph->nodes[i].transitions[j].b->levelHierarchyRoad=(graph->nodes[i].transitions[j].b->levelHierarchyRoad+graph->nodes[i].levelHierarchyRoad)/2;
//                                graph->nodes[i].transitions[j].b->transitions[h].b->levelHierarchyRoad=(graph->nodes[i].transitions[j].b->transitions[h].b->levelHierarchyRoad+graph->nodes[i].levelHierarchyRoad)/2;
//                                graph->nodes[i].transitions[j].b->transitions[h].otherWeights[graph->getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]]=1;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
}






void Graph::createLineGraphMelbourne(Graph* graphOrigin, Graph* lineGraph){
    long idTransitions=0;
//    std::unordered_map<signed long long,Transition*> transitionsOfLineGraphByID;
//    for(long i=0;i<graphOrigin->nodes.size();i++){
//        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
    
    for(long i=0;i<graphOrigin->transitions.size();i++){
//        std::cout<<"Graph -> createlinegraphMelbourne originalID transitions A "<<graphOrigin->transitions[i].originalID<<'\n';
        if(graphOrigin->transitions[i].originalID!=-1){
//            alreadyExistIds=true;
        }else{
            graphOrigin->transitions[i].originalID=idTransitions;
            
        }
//        std::cout<<"Graph -> createlinegraphMelbourne originalID transitions B "<<graphOrigin->transitions[i].originalID<<'\n';
            graphOrigin->transitions[i].id=idTransitions;
            idTransitions++;
            lineGraph->addNode();
//        }
    }
    int indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[METRIC].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->indexOfMainDistanceInOtherDistances=indexDistance;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[TOPOLOGICAL].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[ANGULAR].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
          lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[COGNITIVE].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
          lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[GREEN_AREAS_IMPEDANCE].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
          lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[TIME_DISTANCE].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
          lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
    indexDistance=lineGraph->numberDistances;
    lineGraph->indexOfDistancesByDistanceType[SLOPE].push_back(indexDistance);
    lineGraph->numberDistances++;
    lineGraph->totalLengths.push_back(0);
    lineGraph->averageLengths.push_back(0);
    lineGraph->diameters.push_back(0);
    for(long i=0;i<lineGraph->nodes.size();i++){
        lineGraph->nodes[i].minOtherDistances.push_back(INFINITY);
        lineGraph->nodes[i].numOtherChildren.push_back(0);
        lineGraph->nodes[i].numOtherChildrenThatReachedMe.push_back(0);
        lineGraph->nodes[i].valuesToPass.push_back(1);
        lineGraph->nodes[i].originalValuesToPass.push_back(1);
        lineGraph->nodes[i].otherParents.push_back(NULL);
    }
    
//    long idTransitionsLineGraph=0;
    
//    double maxLogLengths=0;
//    
//    double maxLengths=0;
//    double maxTimeDistance=0;
//    double maxLogTimeDistance=0;
    


    for(long i=0;i<graphOrigin->nodes.size();i++){
        //        std::vector<Node*> nodesTermination;
        
        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
            
            long idNodeA=graphOrigin->nodes[i].transitions[j]->id;
//            std::cout<<"graph ->createlinegraphMelbourne ->transition that represents "<<lineGraph->nodes[idNodeA].transitionThatRepresents<<'\n';
//            if(lineGraph->nodes[idNodeA].transitionThatRepresents==NULL){
                pushNewDistance(&lineGraph->nodes[idNodeA]);
                pushNewDistance(&lineGraph->nodes[idNodeA]);
                pushNewDistance(&lineGraph->nodes[idNodeA]);
                pushNewDistance(&lineGraph->nodes[idNodeA]);
                pushNewDistance(&lineGraph->nodes[idNodeA]);
                pushNewDistance(&lineGraph->nodes[idNodeA]);
                pushNewDistance(&lineGraph->nodes[idNodeA]);
            
                double x=(graphOrigin->nodes[i].transitions[j]->a->location.x+graphOrigin->nodes[i].transitions[j]->b->location.x)/2;
                double y=(graphOrigin->nodes[i].transitions[j]->a->location.y+graphOrigin->nodes[i].transitions[j]->b->location.y)/2;
                lineGraph->nodes[idNodeA].location=Point2d(x,y);
                lineGraph->nodes[idNodeA].transitionThatRepresents=(graphOrigin->nodes[i].transitions[j]);
                graphOrigin->nodes[i].transitions[j]->nodeOfLineGraphThatRepresentsThis=&(lineGraph->nodes[idNodeA]);
//                std::cout<<"Graph -> createlinegraphMelbourne originalID transitions C "<<graphOrigin->nodes[i].transitions[j]->originalID<<'\n';
                lineGraph->nodes[idNodeA].originalID=graphOrigin->nodes[i].transitions[j]->originalID;
               
//                for(long h=0;h<graphOrigin->nodes[i].transitions[j]->b->transitions.size();h++){
//                    double length=graphOrigin->nodes[i].transitions[j]->weight/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->weight/2;
//    //                double greenAreasWeight=graphOrigin->nodes[i].transitions[j].otherWeights[graphOrigin->getIndexesOfDistanceType(GREEN_AREAS_IMPEDANCE)[0]]/2+graphOrigin->nodes[i].transitions[j].b->transitions[h].otherWeights[graphOrigin->getIndexesOfDistanceType(GREEN_AREAS_IMPEDANCE)[0]]/2;
//                    double timeDistanceWeight=graphOrigin->nodes[i].transitions[j]->otherWeights[graphOrigin->getIndexesOfDistanceType(TIME_DISTANCE)[0]]/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->otherWeights[graphOrigin->getIndexesOfDistanceType(TIME_DISTANCE)[0]]/2;
//                    if(log(length+1)>maxLogLengths){
//                        maxLogLengths=log(length+1);
//                    }
//                    if((length)>maxLengths){
//                        maxLengths=(length);
//                    }
//                    if(timeDistanceWeight>maxTimeDistance){
//                        maxTimeDistance=timeDistanceWeight;
//                    }
//                    if(log(timeDistanceWeight+1)>maxLogTimeDistance){
//                        maxLogTimeDistance=log(timeDistanceWeight+1);
//                    }
//                }
//            }
        }
    }
    
    
    for(long i=0;i<graphOrigin->nodes.size();i++){
//        std::vector<Node*> nodesTermination;
        
        for(long j=0;j<graphOrigin->nodes[i].transitions.size();j++){
            long idNodeA=graphOrigin->nodes[i].transitions[j]->id;
//            pushNewDistance(&lineGraph->nodes[idNodeA]);
//            pushNewDistance(&lineGraph->nodes[idNodeA]);
//            pushNewDistance(&lineGraph->nodes[idNodeA]);
//            pushNewDistance(&lineGraph->nodes[idNodeA]);
//            pushNewDistance(&lineGraph->nodes[idNodeA]);
//            pushNewDistance(&lineGraph->nodes[idNodeA]);
//
//            double x=(graphOrigin->nodes[i].transitions[j].a->location.x+graphOrigin->nodes[i].transitions[j].b->location.x)/2;
//            double y=(graphOrigin->nodes[i].transitions[j].a->location.y+graphOrigin->nodes[i].transitions[j].b->location.y)/2;
//            lineGraph->nodes[idNodeA].location=Point2d(x,y);
//                        lineGraph->nodes[idNodeA].transitionThatRepresents=&(graphOrigin->nodes[i].transitions[j]);
//            graphOrigin->nodes[i].transitions[j].nodeOfLineGraphThatRepresentsThis=&(lineGraph->nodes[idNodeA]);
//            lineGraph->nodes[idNodeA].originalID=graphOrigin->nodes[i].transitions[j].originalID;
//            nodesTermination.push_back(graphOrigin->nodes[i].transitions[j].b);
            for(long h=0;h<graphOrigin->nodes[i].transitions[j]->b->transitions.size();h++){
                
                long idNodeB=graphOrigin->nodes[i].transitions[j]->b->transitions[h]->id;
                
                if(idNodeA!=idNodeB||lineGraph->allowLoops){
                    Transition trans;
    //                if(graphOrigin->nodes[i].transitions[j].b->transitions.size()+graphOrigin->nodes[i].transitions[j].b->inDegree<=2){
    //                    trans.transitionOfLineGraphFromNodeOfDegree2=true;
    //                }else if(graphOrigin->nodes[i].transitions[j].b->transitions.size()==2){
    //                    if(Functions::getAngularDistance(graphOrigin->nodes[i].transitions[j].b->transitions[0].b->location, graphOrigin->nodes[i].transitions[j].b->transitions[0].a->location, graphOrigin->nodes[i].transitions[j].b->transitions[1].b->location)<30){
    //                         trans.transitionOfLineGraphFromNodeOfDegree2=true;
    //                    }
    //                }
//                    if(graphOrigin->nodes[i].transitions[j]->b->degree<=2){
//                         trans.transitionOfLineGraphFromNodeOfDegree2=true;
//                    }
                    trans.a=&lineGraph->nodes[idNodeA];
                    trans.b=&lineGraph->nodes[idNodeB];
                    trans.weight=graphOrigin->nodes[i].transitions[j]->weight/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->weight/2;
                    trans.otherWeights.push_back(trans.weight);
                    trans.otherWeights.push_back(1);
                    double angle=Functions::getAngularDistance(graphOrigin->nodes[i].location,graphOrigin->nodes[i].transitions[j]->b->location,graphOrigin->nodes[i].transitions[j]->b->transitions[h]->b->location);
                    double greenAreasWeight=graphOrigin->nodes[i].transitions[j]->otherWeights[graphOrigin->getIndexesOfDistanceType(GREEN_AREAS_IMPEDANCE)[0]]/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->otherWeights[graphOrigin->getIndexesOfDistanceType(GREEN_AREAS_IMPEDANCE)[0]]/2;
                    double timeDistanceWeight=graphOrigin->nodes[i].transitions[j]->otherWeights[graphOrigin->getIndexesOfDistanceType(TIME_DISTANCE)[0]]/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->otherWeights[graphOrigin->getIndexesOfDistanceType(TIME_DISTANCE)[0]]/2;
                    double timeDistanceBasedInSlope=graphOrigin->nodes[i].transitions[j]->otherWeights[graphOrigin->getIndexesOfDistanceType(SLOPE)[0]]/2+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->otherWeights[graphOrigin->getIndexesOfDistanceType(SLOPE)[0]]/2;
                    
                    
                    double angleTransformed=angle/180*12-6;
    //                angle=angle*log(trans.weight+1)/maxLogLengths;
                    double angleModified=pow(((1/(1+exp(-angleTransformed)))),1)*180;
    //                double lengthTransformed=log(timeDistanceWeight+1)/maxLogTimeDistance*12-6;
    //                double multiplierLengths=pow(((1/(1+exp(-lengthTransformed)))),.25);
    //                double multiplierLengths=(lengthTransformed+6)/12;
                    angleModified=angle;
    //                                angleModified=angleModified*multiplierLengths;
                    
                    
                    //this is angulardistance
                    trans.otherWeights.push_back(angleModified);
                    
                    
                    
                    double modifierCognitive=graphOrigin->nodes[i].transitions[j]->otherWeights[graphOrigin->getIndexesOfDistanceType(COGNITIVE)[0]]+graphOrigin->nodes[i].transitions[j]->b->transitions[h]->otherWeights[graphOrigin->getIndexesOfDistanceType(COGNITIVE)[0]];
                    double cognitiveWeight;
                    double multiplierCognitive=1;
    //                double minMultiplierCognitive=0.2;
    //                double removeFromMultiplierCognitive=0.1;
    //                double bonus=0.2;
                    
                    if(modifierCognitive==0){
    //                    cognitiveWeight=angle*.5;
                        
                            cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),2.5)*180;
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                        multiplierCognitive=0.1;

                    }else if(modifierCognitive==1){
                        //                    cognitiveWeight=angle*.5;
                        
                        cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),2.25)*180;
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                        multiplierCognitive=0.15;
                        
                    }else if(modifierCognitive==2){
                        //                    cognitiveWeight=angle*.5;
                        
                        cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),1.75)*180;
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                         multiplierCognitive=0.2;
                        
                    }else if(modifierCognitive==3){
                        //                    cognitiveWeight=angle*.5;
                        
                        cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),2.25)*180;
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                         multiplierCognitive=0.225;
                        
                    }else if(modifierCognitive==4){
                        //                    cognitiveWeight=angle*.5;
                        
                        cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),2)*180;
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                         multiplierCognitive=0.25;
                        
                    }else if(modifierCognitive==6){
                        //                    cognitiveWeight=angle*.5;
                        
                        cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),2)*180;
                        if(cognitiveWeight<0){
                            cognitiveWeight=0;
                        }
                         multiplierCognitive=0.3;
                        
                    }else if (modifierCognitive==7){
                        multiplierCognitive=0.05;
                    }
                    else if (modifierCognitive==8){
                        multiplierCognitive=0.05;
                    }
                    else if (modifierCognitive==10){
                        multiplierCognitive=0.15;
                    }
                    else if (modifierCognitive==14){
                        multiplierCognitive=0.0;
                    }
                    else if (modifierCognitive==17){
                        multiplierCognitive=0.1;
                    }
                    else if (modifierCognitive==18){
                        multiplierCognitive=0.15;
                    }
                    else if (modifierCognitive==20){
                        multiplierCognitive=0.2;
                    }
                    else if (modifierCognitive==24){
                        multiplierCognitive=0.05;
                    }
                    else if (modifierCognitive==34){
                        multiplierCognitive=0.2;
                    }
                    else{
                        cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),1)*180;
    //                    cognitiveWeight=angle;
                         multiplierCognitive=1;
                    }
    //                cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),1)*180*((1-multiplierCognitive)*pow(((1/(1+exp(-angleTransformed)))),1)+multiplierCognitive);
                    double coefficient=1;
                    
                    if(trans.transitionOfLineGraphFromNodeOfDegree2){
    //                    multiplierCognitive=1;
                    }
                    
                    
                    angle=angle*((1-multiplierCognitive)*pow(((1/(1+exp(-(-(angle/180*14-7)))))),1)+multiplierCognitive);
                    
                    
                    
                    
                    
    //                angle=angle*multiplierCognitive;
                    if(angle<=90){
    //                    cognitiveWeight=(pow(((1/(1+exp(-(angle/90*12*.75-6))))),1)*90)*multiplierCognitive;
    //                    cognitiveWeight=(pow(((1/(1+exp(-(angle/90*12*coefficient-6))))),1)*90)*((1-multiplierCognitive)*pow(((1/(1+exp(-angleTransformed)))),2)+multiplierCognitive);
                        cognitiveWeight=(pow(((1/(1+exp(-(angle/90*12*coefficient-6))))),1)*90);
                    }else{
    //                    cognitiveWeight=(((pow(((1/(1+exp(-((angle-90)/90*12*.75-6*.75))))),1)+1)*90))*multiplierCognitive;
    //                     cognitiveWeight=(((pow(((1/(1+exp(-((angle-90)/90*12*coefficient-6))))),1)+1)*90))*((1-multiplierCognitive)*pow(((1/(1+exp(-angleTransformed)))),2)+multiplierCognitive);
                        cognitiveWeight=(((pow(((1/(1+exp(-((angle-90)/90*12*coefficient-6))))),1)+1)*90));

                    }
                    cognitiveWeight=pow((pow(((1/(1+pow(exp(-(angle/180*14-7)),1)))),1)),1)*180;
                    
                    if(cognitiveWeight<0){
                        cognitiveWeight=0;
                    }
                    if(cognitiveWeight>180){
                        cognitiveWeight=180;
                    }
    //                cognitiveWeight=pow(((1/(1+exp(-angleTransformed)))),4)*180;
    //                cognitiveWeight=cognitiveWeight*multiplierLengths;

                    trans.otherWeights.push_back(cognitiveWeight);
                    
    //                double greenAreasWeight=graphOrigin->nodes[i].transitions[j].otherWeights[graphOrigin->getIndexesOfDistanceType(GREEN_AREAS_IMPEDANCE)[0]]/2+graphOrigin->nodes[i].transitions[j].b->transitions[h].otherWeights[graphOrigin->getIndexesOfDistanceType(GREEN_AREAS_IMPEDANCE)[0]]/2;
    //                double timeDistanceWeight=graphOrigin->nodes[i].transitions[j].otherWeights[graphOrigin->getIndexesOfDistanceType(TIME_DISTANCE)[0]]/2+graphOrigin->nodes[i].transitions[j].b->transitions[h].otherWeights[graphOrigin->getIndexesOfDistanceType(TIME_DISTANCE)[0]]/2;
                    
                    trans.otherWeights.push_back(greenAreasWeight);
                    trans.nodeInGraphAfterLineGraphGeneration=graphOrigin->nodes[i].transitions[j]->b;
                    
                    
                    trans.otherWeights.push_back(timeDistanceWeight);
                    trans.otherWeights.push_back(timeDistanceBasedInSlope);
                    if(graphOrigin->bidirectional==true){
                    
                        if(graphOrigin->nodes[i].transitions[j]->b->transitions[h]->b==&graphOrigin->nodes[i]){
    //                        std::cout<<graphOrigin->nodes[i].transitions[j].weight<<"--"<<graphOrigin->nodes[i].transitions[j].b->transitions[h].weight<<'\n';
                            trans.weight=0;
                            for(long g=0;g<trans.otherWeights.size();g++){
                                trans.otherWeights[g]=0;
                            }
                        }
                    }
                    lineGraph->addDirectedTransition(trans);
                    }
//                transitionsOfLineGraphByID[trans.originalID]=&trans;
//                idTransitionsLineGraph++;
//                std::cout<<idTransitionsLineGraph<<'\n';
            }
        }
        
    }
//    for(long i=0;i<lineGraph->nodes.size();i++){
//        if(lineGraph->nodes[i].transitions.size()==1){
//            int indexCognitive=lineGraph->getIndexesOfDistanceType(Graph::COGNITIVE)[0];
//            Transition trans;
//            trans=lineGraph->nodes[i].transitions[0];
//            double multiplierCognitive=0;
//            double previousWeight=trans.otherWeights[indexCognitive];
//            trans.otherWeights[indexCognitive]=trans.otherWeights[indexCognitive]*((1-multiplierCognitive)*pow(((1/(1+exp(-(trans.otherWeights[indexCognitive]/180*12-6))))),1)+multiplierCognitive);
//            double posteriorWeight=trans.otherWeights[indexCognitive];
//
//        }
//    }
    
}
void Graph::calculateKShellAlgorithm(Graph* graph){
//    Graph graphCopy;
//    copyGraph(graph, &graphCopy);
//    std::unordered_map<signed long long,Node*> nodesOriginalGraphByID;
//    std::unordered_map<signed long long,Node*> nodesCopiedGraphByID;
    MinHeap<Node*> nodesByDegree;

    for(long i=0;i<graph->nodes.size();i++){
//        nodesOriginalGraphByID[graph->nodes[i].originalID]=&(graph->nodes[i]);
//        nodesCopiedGraphByID[graphCopy.nodes[i].originalID]=&(graphCopy.nodes[i]);
//        while(nodesByDegree.size()<graphCopy.nodes[i].transitions.size()+1){
//            std::vector<Node*> vector;
//            nodesByDegree.push_back(vector);
//        }
//        nodesByDegree[graphCopy.nodes[i].transitions.size()].push_back(&(graphCopy.nodes[i]));
        Node* node=&(graph->nodes[i]);
        nodesByDegree.push(node, &compareByDegreeOutAndKShellValue);
        
    }
    long kShellValue=nodesByDegree.getMin(&compareByDegreeOutAndKShellValue)->transitions.size();
//    Graph graphCopy;
//    copyGraph(graph, &graphCopy);
//    for(long i=0;i<nodesByDegree.size();i++){
std::vector<Node*> nodesToRemove;
        while(nodesByDegree.size()>0){
            Node* node=nodesByDegree.pop(&compareByDegreeOutAndKShellValue);
            
            if(node->transitions.size()<=kShellValue){
                nodesToRemove.push_back(node);
                node->kShellValueFinal=kShellValue;
            }else{
//                Graph newGraph;
                removeNodesFromGraph(graph, nodesToRemove);
                nodesByDegree.buildHeap(&compareByDegreeOutAndKShellValue);
//                graphCopy.resetGraph();
//                copyGraph(&newGraph, &graphCopy);
                nodesToRemove.clear();
//                nodesByDegree.clear();
//                for(long i=0;i<graphCopy.nodes.size();i++){
//                    Node* node=&(graphCopy.nodes[i]);
//                    nodesByDegree.push(node, &compareByDegree);
//                }
                Node* min=nodesByDegree.getMin(&compareByDegreeOutAndKShellValue);
                if(min->transitions.size()>kShellValue){
                    kShellValue++;
                }
            }
//            if(node->transitions.size()-node->kShellValue>kShellValue){
//                kShellValue++;
//            }
//            node->kShellValueFinal=(int)(node->transitions.size()-node->kShellValue);
////            std::cout<<node->transitions.size()<<" / "<<node->idNodesThatReachMe.size()<<" / "<<node->kShellValueFinal<<'\n';
//            for(long i=0;i<node->idNodesThatReachMe.size();i++){
//                graph->nodes[node->idNodesThatReachMe[i]].kShellValue++;
//            }
//            nodesByDegree.buildHeap(&compareByDegree);
////            graphCopy.removeNode(&graphCopy, node);
////            nodesByDegree.heap.clear();
////            for(long i=0;i<graphCopy.nodes.size();i++){
////              
////                Node* node=&(graphCopy.nodes[i]);
////                nodesByDegree.push(node, &compareByDegree);
////                
////            }
           
        }
    
//        }
//    }
    
}
//
void Graph::generateSpatialPercolation(Graph* graph,double distanceLimit,std::vector<Graph> &clusters){
    double INF=std::numeric_limits<double>::infinity();
    double maxX=-INF;
    double maxY=-INF;
    double minX=INF;
    double minY=INF;

    QTree quadTree;
    Graph graphOfCloseness;
    for(long i=0;i<graph->nodes.size();i++){
        graphOfCloseness.addNode();
        if (graph->nodes[i].location.x>=maxX)
        {
            maxX=graph->nodes[i].location.x+1;
        }
        if (graph->nodes[i].location.y>=maxY)
        {
            maxY=graph->nodes[i].location.y+1;
        }
        if (graph->nodes[i].location.x<=minX)
        {
            minX=graph->nodes[i].location.x-1;
        }
        if (graph->nodes[i].location.y<=minY)
        {
            minY=graph->nodes[i].location.y-1;
        }
    }
    quadTree.generateCornersOfMainCluster(minX,maxX,minY,maxY);
    
    for(long i=0;i<graph->nodes.size();i++){
        graphOfCloseness.nodes[i].location=graph->nodes[i].location;
        graphOfCloseness.nodes[i].mass=graph->nodes[i].mass;
        graphOfCloseness.nodes[i].originalID=graph->nodes[i].originalID;
        graphOfCloseness.nodes[i].nodeThatRepresents=&(graph->nodes[i]);
        
    }
    for(long i=0;i<graphOfCloseness.nodes.size();i++){
        Node* node=&graphOfCloseness.nodes[i];
        quadTree.mainCluster.addNode(node);
    }
    
    for(long i=0;i<graphOfCloseness.nodes.size();i++){
        double width=distanceLimit;
        std::vector<Node*> nodesClose;
        std::vector<Node*> nodesInRange=quadTree.getNodesInARange(graphOfCloseness.nodes[i].location.x-width, graphOfCloseness.nodes[i].location.x+width, graphOfCloseness.nodes[i].location.y-width, graphOfCloseness.nodes[i].location.y+width);
        for(long j=0;j<nodesInRange.size();j++){
            double distance=Functions::getDistance(graph->nodes[i].location, nodesInRange[j]->location);
            if(distance<distanceLimit){
                Transition trans;
                trans.a=&graphOfCloseness.nodes[i];
                trans.b=nodesInRange[j];
                trans.weight=distance;
                graphOfCloseness.addDirectedTransition(trans);
            }
        }
        
    }
    std::vector<Graph> clustersTemp;
    graphOfCloseness.generateNetworkPercolation(distanceLimit, clustersTemp, false, true, "", 0,false);
    
//    std::unordered_map<unsigned long long,Node*> nodesByOriginalId;
//    for(long i=0;i<graph->nodes.size();i++){
//        nodesByOriginalId[graph->nodes[i].originalID]=&(graph->nodes[i]);
//    }
    
    for(long i=0;i<clustersTemp.size();i++){
        std::vector<Node*> nodesInCluster;
        for(long j=0;j<clustersTemp[i].nodes.size();j++){
//            nodesInCluster.push_back(nodesByOriginalId[clustersTemp[i].nodes[j].originalID]);
             nodesInCluster.push_back(clustersTemp[i].nodes[j].nodeThatRepresents);
        }
        Graph clusterNew;
        graph->getInducedSubgraph(&clusterNew, nodesInCluster);
        clusters.push_back(clusterNew);
        
    }
    



}

void Graph::generateSuperGraphFromClusters(std::vector<Graph> &clusters,Graph* originalGraph,Graph* result){
    std::unordered_map<unsigned long long,long> clusterIdPerNodeId;
    std::unordered_map<unsigned long long,Node*> nodesPerOriginalId;
    
    std::vector<Point2d> locations;
    for(long i=0;i<clusters.size();i++){
//        Node nodeThatRepresentCluster;
        if(clusters[i].nodes.size()>0){
            double x=0;
            double y=0;
            double totalMass=0;
            for(long j=0;j<clusters[i].nodes.size();j++){
                totalMass+=clusters[i].nodes[j].mass;
    //            long originalId=clusters[i].nodes[j].originalID;
                clusterIdPerNodeId[clusters[i].nodes[j].originalID]=i+1;
                
                x+=clusters[i].nodes[j].location.x;
                y+=clusters[i].nodes[j].location.y;
            }
            x/=(double)(clusters[i].nodes.size());
            y/=(double)(clusters[i].nodes.size());
            
            result->addNode();
            result->nodes[result->nodes.size()-1].mass=totalMass;
            locations.push_back(Point2d(x,y));
        }
    }
//    std::cout<<"a"<<'\n';
    for(long i=0;i<originalGraph->nodes.size();i++){
        nodesPerOriginalId[originalGraph->nodes[i].originalID]=&(originalGraph->nodes[i]);
        if(clusterIdPerNodeId[originalGraph->nodes[i].originalID]-1==-1){
            result->addNode();
            result->nodes[result->nodes.size()-1].mass=originalGraph->nodes[i].mass;
            locations.push_back(originalGraph->nodes[i].location);
            clusterIdPerNodeId[originalGraph->nodes[i].originalID]=result->nodes.size();
            Graph graphTemp;
            graphTemp.addNode();
            graphTemp.nodes[0].originalID=originalGraph->nodes[i].originalID;
            graphTemp.nodes[0].nameRoad=originalGraph->nodes[i].nameRoad;
            graphTemp.nodes[0].levelHierarchyRoad=originalGraph->nodes[i].levelHierarchyRoad;
            graphTemp.nodes[0].location=originalGraph->nodes[i].location;
            graphTemp.nodes[0].mass=originalGraph->nodes[i].mass;
            clusters.push_back(graphTemp);
        }
    }
//std::cout<<"b"<<'\n';
    long numberOfTransitions=0;
    for(long i=0;i<clusters.size();i++){
         if(clusters[i].nodes.size()>0){
             result->nodes[i].originalID=clusters[i].nodes[0].originalID;
         }
    }
    long numberOfCollapsedNodes=0;
    for(long i=0;i<clusters.size();i++){
//        result->nodes[i].originalID=clusters[i].nodes[0].originalID;
        for(long j=0;j<clusters[i].nodes.size();j++){
            
            Node* node=nodesPerOriginalId[clusters[i].nodes[j].originalID];
            result->nodes[i].nodesCollapsed.push_back(node);
            numberOfCollapsedNodes++;
            for(long h=0;h<node->transitions.size();h++){
//                long originalId=otherNode->transitions[h].b->originalID;
                long idOfNode=clusterIdPerNodeId[node->transitions[h]->a->originalID]-1;
                long idOfOtherCluster=clusterIdPerNodeId[node->transitions[h]->b->originalID]-1;
                if(idOfOtherCluster!=idOfNode){
                    
                    Transition trans;
                    trans.a=&(result->nodes[idOfNode]);
                    trans.a->location=locations[idOfNode];
                    trans.b=&(result->nodes[idOfOtherCluster]);
                    trans.b->location=locations[idOfOtherCluster];
                    trans.weight=Functions::getDistance(trans.a->location, trans.b->location);
                    trans.originalID=node->transitions[h]->originalID;
                    trans.nameRoad=node->transitions[h]->nameRoad;
                    trans.levelHierarchyRoad=node->transitions[h]->levelHierarchyRoad;
                    std::vector<double> otherWeights;
                    trans.otherWeights=otherWeights;
                    if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
                        result->addDirectedTransition(trans);
                        numberOfTransitions++;
                        result->nodes[idOfNode].transitions[result->nodes[idOfNode].transitions.size()-1]->transitionsCollapsed.push_back(node->transitions[h]);
                    }else{
                        result->nodes[idOfNode].transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->transitionsCollapsed.push_back(node->transitions[h]);
                    }
                }else{
                    result->nodes[i].transitionsCollapsedIntoNode.push_back(node->transitions[h]);
                }
            }
        }
    }
//    std::cout<<"c"<<'\n';
    result->setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
    result->insertTopologicalWeights();
    if(originalGraph->bidirectional){
        result->transformToBidirectional();
    }
//    std::cout<<"d"<<'\n';
    cout<<"number of transitions after generating superGraph of clusters "<<numberOfTransitions<<'\n';
     cout<<"number of collapsed nodes "<<numberOfCollapsedNodes<<'\n';
}

void Graph::collapseNodesOfDegree2(){
    for(long i=0;i<nodes.size();i++){
        long transOut=nodes[i].transitions.size();
//        long transIn=nodes[i].nodesThatReachMe.size();
        Node* node=&nodes[i];
        if(bidirectional){
            if (transOut==2){
                Node* a=nodes[i].transitions[0]->b;
                Node* b=nodes[i].transitions[1]->b;
                long index=a->indexOfTransitionsByIdOfDestination[node->originalID];
                a->transitions[index]->b=b;
                a->indexOfTransitionsByIdOfDestination[node->originalID]=0;
                
                
            }
        }else{
            
        }
        
    }
}

void Graph::insertGraphIntoQTree(QTree* quadTree){
    double maxX=-INFINITY;
    double minX=INFINITY;
    double maxY=-INFINITY;
    double minY=INFINITY;
    for(long i=0;i<nodes.size();i++){

        if (nodes[i].location.x>=maxX)
        {
            maxX=nodes[i].location.x+1;
        }
        if (nodes[i].location.y>=maxY)
        {
            maxY=nodes[i].location.y+1;
        }
        if (nodes[i].location.x<=minX)
        {
            minX=nodes[i].location.x-1;
        }
        if (nodes[i].location.y<=minY)
        {
            minY=nodes[i].location.y-1;
        }
    }
    quadTree->generateCornersOfMainCluster(minX,maxX,minY,maxY);


    for(long i=0;i<nodes.size();i++){
        Node* node=&nodes[i];
        quadTree->mainCluster.addNode(node);
    }
}


void Graph::generateAngularPercolation(Graph* graph,double angleLimit,std::vector<Graph> &clusters,double minClusterSize,bool probabilistic){
    Graph lineGraph;
    lineGraph.strictlyDirectional=true;
//    std::vector<Graph> clustersTemp;
    graph->createLineGraph(graph,&lineGraph);
    for(long i=0;i<lineGraph.transitions.size();i++){
        lineGraph.transitions[i].weight=lineGraph.transitions[i].otherWeights[lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
    }
    lineGraph.generateNetworkPercolation(angleLimit, clusters, false, true, "", minClusterSize,probabilistic);
    
//    std::vector<Node> nodes;
//    Heap<Node*> heap(Heap<Node*>::MAX,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//    for(long i=0;i<clustersTemp.size();i++){
//        Node node;
//        node.minDistance=clustersTemp[i].nodes.size();
//        node.id=i;
//        nodes.push_back(node);
//  
//    }
//    for(long i=0;i<nodes.size();i++){
//        Node* node=&nodes[i];
//        heap.push(node);
//    }
//    long index=0;
//    while(heap.size()>0&&(index<numberClustersToReturn||numberClustersToReturn==0)){
//        long indexMax=heap.pop()->id;
//        
//        if(returnClustersFromOriginalGraph){
//            Graph giantCluster;
//            std::vector<Transition*> transitions;
//            for(long i=0;i<clustersTemp[indexMax].nodes.size();i++){
//                transitions.push_back(clustersTemp[indexMax].nodes[i].transitionThatRepresents);
//            }
//            
//            graph->getInducedSubgraph(&giantCluster, transitions);
//            clusters.push_back(giantCluster);
//        }else{
//            clusters.push_back(clustersTemp[indexMax]);
//        }
//        
//        index++;
//    }
    

    
    
    
}

void Graph::generateAngularPercolation(Graph* graph,Graph* lineGraph,double angleLimit,std::vector<Graph> &clusters,double minClusterSize,bool probabilistic){
//    Graph lineGraph;
//    lineGraph.strictlyDirectional=true;
//    std::vector<Graph> clustersTemp;
//    graph->createLineGraph(graph,&lineGraph);
    for(long i=0;i<lineGraph->transitions.size();i++){
        lineGraph->transitions[i].weight=lineGraph->transitions[i].otherWeights[lineGraph->getIndexesOfDistanceType(Graph::ANGULAR)[0]];
    }
    lineGraph->generateNetworkPercolation(angleLimit, clusters, false, true, "", minClusterSize,probabilistic);
    
//    std::vector<Node> nodes;
//    Heap<Node*> heap(Heap<Node*>::MAX,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//    for(long i=0;i<clustersTemp.size();i++){
//        Node node;
//        node.minDistance=clustersTemp[i].nodes.size();
//        node.id=i;
//        nodes.push_back(node);
//        
//    }
//    for(long i=0;i<nodes.size();i++){
//        Node* node=&nodes[i];
//        heap.push(node);
//    }
//    long index=0;
//    while(heap.size()>0&&(index<numberClustersToReturn||numberClustersToReturn==0)){
//        long indexMax=heap.pop()->id;
//        
//        if(returnClustersFromOriginalGraph){
//            Graph giantCluster;
//            std::vector<Transition*> transitions;
//            for(long i=0;i<clustersTemp[indexMax].nodes.size();i++){
//                transitions.push_back(clustersTemp[indexMax].nodes[i].transitionThatRepresents);
//            }
//            
//            graph->getInducedSubgraph(&giantCluster, transitions);
//            clusters.push_back(giantCluster);
//        }else{
//            clusters.push_back(clustersTemp[indexMax]);
//        }
//        
//        index++;
//    }
    
    
    
    
    
}


void Graph::orderClustersByMass(std::vector<Graph>& clusters){
    std::vector<Graph> clustersTemp;
    std::vector<Node> nodes;
    Heap<Node*> heap(Heap<Node*>::MAX,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    for(long i=0;i<clusters.size();i++){
        Node node;
        node.minDistance=clusters[i].nodes.size();
        node.id=i;
        nodes.push_back(node);
        
    }
    for(long i=0;i<nodes.size();i++){
        Node* node=&nodes[i];
        heap.push(node);
    }

    while(heap.size()>0){
        long indexMax=heap.pop()->id;
        clustersTemp.push_back(clusters[indexMax]);
    }
    clusters.clear();
    for(long i=0;i<clustersTemp.size();i++){
        clusters.push_back(clustersTemp[i]);
    }
}





Point2d Graph::calculateCentroid(std::vector<Node> &nodes){
    Point2d centroid;
    centroid.x=0.0;
    centroid.y=0.0;
    double totalMass=0.0;
    for(long i=0;i<nodes.size();i++){
        if(nodes[i].mass>0){
            centroid.x+=nodes[i].location.x*nodes[i].mass;
            centroid.y+=nodes[i].location.y*nodes[i].mass;
            
            totalMass+=nodes[i].mass;
        }
    }
    centroid.x/=totalMass;
    centroid.y/=totalMass;
    
    
    return centroid;
    
}



double Graph::calculateSquaredGyrationRadius(Graph* graph){
    Point2d centroid=calculateCentroid(graph->nodes);
//    std::cout<<"centroid "<<centroid.x<<" "<<centroid.y<<'\n';
    double totalDistanceFromCentroid=0;
    double totalMass=0;
    for(long i=0;i<graph->nodes.size();i++){
        totalMass+=graph->nodes[i].mass;
        totalDistanceFromCentroid+=pow(Functions::getDistance(centroid, graph->nodes[i].location),2.0);
        
    }
    double rg=1.0/totalMass*totalDistanceFromCentroid;
//    std::cout<<"radius gyration "<<totalMass<<" "<<totalDistanceFromCentroid<<" "<<rg<<'\n';
    return rg;
    
}

double Graph::calculateTotalDistance(Graph* graph,Node* nodeInit){
    std::vector<Node*> nodesCutoff;
    nodeInit->minDistance=0;
    
    
    Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
    nodesCutoff.push_back(nodeInit);
    nodeInit->inCutoff=true;
    nodesToCheckDijkstra.push(nodeInit);
    nodeInit->inDijkstra=true;
    
    
    graph->calculateDijkstraSpeed(nodeInit,0,nodesCutoff,nodesToCheckDijkstra);
    double max=-INFINITY;
    double totalDistance=0;
    for(long i=0; i<nodesCutoff.size(); i++)
    {
        totalDistance+=nodesCutoff[i]->minDistance;
        if(nodesCutoff[i]->minDistance>max){
            max=nodesCutoff[i]->minDistance;
            
        }
    }
    graph->eccentricity[nodeInit->id]=max;
    
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
    return totalDistance;
}

double Graph::calculateSquaredGyrationRadiusInGraphSpace(Graph* subGraph,Graph* fullGraph,QTree* quadTree){
//    Point2d centroid=calculateCentroid(subGraph->nodes);
////
//    QTree quadTreeTemp;
//    subGraph->insertGraphIntoQTree(&quadTreeTemp);
//    Node* current=quadTreeTemp.getClosestNode(centroid);
    
//    subGraph->prepareForCentralitiesCalculation();
//    
//
//    bool continueLooking=true;
//    while(continueLooking)
//    {
//        
//        double totalDistance;
//        if(subGraph->closeness[current->id]==0){
//            totalDistance=calculateTotalDistance(subGraph, current);
//            subGraph->closeness[current->id]=totalDistance;
//            
//        }else{
//            totalDistance=subGraph->closeness[current->id];
//        }
//        std::vector<double> otherTotalDistances;
//        for(long i=0;i<current->transitions.size();i++){
//            double totalDistanceTemp;
//            if(subGraph->closeness[current->transitions[i]->b->id]==0){
//                totalDistanceTemp=calculateTotalDistance(subGraph,  current->transitions[i]->b);
//                subGraph->closeness[current->transitions[i]->b->id]=totalDistanceTemp;
//                
//            }else{
//                totalDistanceTemp=subGraph->closeness[current->transitions[i]->b->id];
//            }
//            otherTotalDistances.push_back(totalDistanceTemp);
//        }
//        double min=totalDistance;
////        long indexMin=-1;
//        for(long i=0;i<otherTotalDistances.size();i++){
//            if(otherTotalDistances[i]<min&&otherTotalDistances[i]>0){
//                current=current->transitions[i]->b;
//                min=otherTotalDistances[i];
//            }
//        }
//        if(min==totalDistance){
//            continueLooking=false;
//        }
//        
//    }


//    double totalDistanceFromCentroid=0;
    std::vector<Node*> nodesOfSubgraphInFullGraph;
    double totalMass=0;
    for(long i=0;i<subGraph->nodes.size();i++){
        totalMass+=subGraph->nodes[i].mass;
        nodesOfSubgraphInFullGraph.push_back(subGraph->nodes[i].nodeThatRepresents);
//        totalDistanceFromCentroid+=pow(graph->nodes[i].minDistance,2.0);
        
    }
    
//    QTree quadTree;
//    fullGraph->insertGraphIntoQTree(&quadTree);
//    Node* current=quadTree->getClosestNode(centroid);
    
    
    double totalSquaredDistance=0;
    
    
    for(long g=0;g<subGraph->nodes.size();g++){
        Node* current=&subGraph->nodes[g];
        std::vector<Node*> nodesCutoff;
        Node* nodeInit=current;
        nodeInit->minDistance=0;
        
        
        Heap<Node*> nodesToCheckDijkstra (Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        nodesCutoff.push_back(nodeInit);
        nodeInit->inCutoff=true;
        nodesToCheckDijkstra.push(nodeInit);
        nodeInit->inDijkstra=true;
        
    //    fullGraph->calculateDijkstraSpeedToSetOfNodes(<#Node *&nodeInit#>, <#double distanceLimit#>, <#std::vector<Node *> &nodesCutoff#>, <#Heap<Node *> &nodesToCheckDijkstra#>, <#std::vector<Node *> setOfNodes#>)
     
//        fullGraph->calculateDijkstraSpeedToSetOfNodes(nodeInit,0,nodesCutoff,nodesToCheckDijkstra,nodesOfSubgraphInFullGraph);
        subGraph->calculateDijkstraSpeed(nodeInit,0,nodesCutoff,nodesToCheckDijkstra);
    
    //    (nodeInit,subGraph->eccentricity[current->id],nodesCutoff,nodesToCheckDijkstra);
        
        for(long i=0; i<subGraph->nodes.size(); i++)
        {
            if(subGraph->nodes[i].minDistance<INFINITY){
                totalSquaredDistance+=pow(subGraph->nodes[i].minDistance,2);
            }
//            if(subGraph->nodes[i].minDistance<INFINITY){
//                
//                totalSquaredDistance+=pow(subGraph->nodes[i].minDistance,2);
////                std::cout<<"minDistance "<<subGraph->nodes[i].minDistance<<'\n';
//            }
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
    nodesToCheckDijkstra.clear();
    nodesCutoff.clear();
    }
//    std::cout<<"totalSquaredDistance "<<totalSquaredDistance<<'\n';
    
    double rg=0;
    if(totalMass>2){
        rg=totalSquaredDistance/(2*pow(totalMass,2));
    }    //    std::cout<<"radius gyration "<<totalMass<<" "<<totalDistanceFromCentroid<<" "<<rg<<'\n';
    
    
 
    
    return rg;
    
}



std::vector<Transition> Graph::getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(Graph* graph){
        std::vector<Transition> result;
    
    
        double INF=std::numeric_limits<double>::infinity();
        double maxX=-INF;
        double maxY=-INF;
        double minX=INF;
        double minY=INF;
        for(int i=0; i<graph->nodes.size(); i++)
        {
            if (graph->nodes[i].location.x>=maxX)
            {
                maxX=graph->nodes[i].location.x+1;
            }
            if (graph->nodes[i].location.y>=maxY)
            {
                maxY=graph->nodes[i].location.y+1;
            }
            if (graph->nodes[i].location.x<=minX)
            {
                minX=graph->nodes[i].location.x-1;
            }
            if (graph->nodes[i].location.y<=minY)
            {
                minY=graph->nodes[i].location.y-1;
            }
        }
    
    std::vector<Node*> nodes;
    for(long i=0;i<graph->nodes.size();i++){
        nodes.push_back(&graph->nodes[i]);
    }
    QTree qTree;
    result=qTree.getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(minX,maxX,minY,maxY,nodes);
    
    
    return result;
}














void Graph::getRegionOfATransition(Graph* G,Transition* trans,std::vector<long> &idNodes,std::vector<long> &idTransitions,std::vector<bool> &invertedTransitions,bool inverted,bool &correctResult){
   
//    std::vector<long> result;
//    std::vector<Node*> nodes;
    Node* nodeA=trans->a;
    Node* nodeB=trans->b;
    if(nodeA==nodeB){
        correctResult=false;
    }else{

        if(inverted==true){
    //        Node* nodeTemp=nodeA;
            nodeA=trans->b;
            nodeB=trans->a;
        }
        
       
        
        //    std::vector<long> otherNodes;
        std::vector<double> angles;
        //    std::vector<Transition*> transitions;
        bool STOP=false;
        Node* node=nodeA;
        Node* secondNode=nodeB;
        Node* thirdNode;
        
        angles.clear();
        long index=-1;
        // long index=node.indexOfTransitionsByIdOfDestination[nodeIdB-1];
        for(long i=0;i<node->transitions.size();i++){
            //      otherNodes.push_back(node.transitions[i]->b->id);
            // angles.push_back(Functions::getAngle(node.location,G->nodes[(node.transitions[i]->b->id)].location));
            if(node->transitions[i]->b==nodeB){
                index=i;
            }
        }
        
        // secondNode=G->nodes[(node.transitions[index]->b->id)];
        idNodes.push_back(node->id);
        idTransitions.push_back(trans->id);
        invertedTransitions.push_back(trans->inverted);
        node->numberOfTimesVisited++;
        
    //    long counter=0;
        while(!STOP){
    //        counter++;
            angles.clear();
            
            for(long i=0;i<secondNode->transitions.size();i++){
                //      otherNodes.push_back(secondNode.transitions[i]->b->id);
                if(secondNode->transitions[i]->b!=node){
                    angles.push_back(Functions::getAngleRadians(node->location,secondNode->location,G->nodes[(secondNode->transitions[i]->b->id)].location));
                }else{
                    angles.push_back(2.0*M_PI);
                }
            }
            index=Functions::getLocationMinimum(angles);
            thirdNode=secondNode->transitions[index]->b;
            if(secondNode==nodeA&&thirdNode==nodeB){
                correctResult=true;
                STOP=true;
            }else if(secondNode->numberOfTimesVisited>=100){
                //        if(counter>50){
                STOP=true;
                
                    correctResult=false;
                
            }else{
                secondNode->numberOfTimesVisited++;
                idNodes.push_back(secondNode->id);
                idTransitions.push_back(secondNode->transitions[index]->id);
                invertedTransitions.push_back(secondNode->transitions[index]->inverted);
                node=secondNode;
                secondNode=thirdNode;
            }
//            secondNode->transitions[index]->inCutoff=true;
            
            
        }
//        if(nodeB->numberOfTimesVisited>getDegree(nodeB)-1){
//            correctResult=false;
//        }
//        nodes.reserve(idNodes.size());
//          std::vector<Node*> nodes;
        for(long i=0;i<idNodes.size();i++){
//            if(!G->nodes[idNodes[i]].inCutoff){
//                nodes.push_back(&G->nodes[idNodes[i]]);
//                G->nodes[idNodes[i]].inCutoff=true;
//            }
            G->nodes[idNodes[i]].numberOfTimesVisited=0;
        }
//        for(long i=0;i<nodes.size();i++){
//            nodes[i]->inCutoff=false;
//        }
//        Graph subG;
//        G->getInducedSubgraph(&subG,nodes);
//        Node* NodeATemp=&subG.nodes[0];
//        Node* nodeBTemp=&subG.nodes[1];
//        //        if(trans->id==51){
//        //            std::cout<<trans->id<<" "<<nodeA->originalID<<" "<<NodeATemp->originalID<<" "<<nodeB->originalID<<" "<<nodeBTemp->originalID<<" "<<getDegree(NodeATemp)<<" "<<getDegree(nodeBTemp)<<'\n';
//        //        }
//        if(getDegree(NodeATemp)==1||getDegree(nodeBTemp)==1){
//            correctResult=false;
//            //            std::cout<<trans->id<<" "<<nodeA->originalID<<" "<<NodeATemp->originalID<<" "<<nodeB->originalID<<" "<<nodeBTemp->originalID<<'\n';
//        }
        
//        Graph burnedGraph;
//        Graph::burnGraph(&subG, &burnedGraph);
//        bool containsA=false;
//        bool containsB=false;
//        for(long i=0;i<burnedGraph.nodes.size();i++){
//            if(burnedGraph.nodes[i].originalID==nodeA->originalID){
//                containsA=true;
//            }
//            if(burnedGraph.nodes[i].originalID==nodeB->originalID){
//                containsB=true;
//            }
//        }
//        if(!(containsA&&containsB)){
//            correctResult=false;
//        }
       
        
    }
//    return (result);
}



void Graph::constructDual(Graph* G,Graph* dual){
    dual->pseudoGraph=true;
    dual->allowLoops=true;
    dual->bidirectional=true;
    dual->strictlyDirectional=false;
//    Graph* dual=new Graph();
    std::unordered_map<std::string, long> nodesDualByLocation;
//    std::vector<long> correspondancesIdsTransitions1;
//    std::vector<long> correspondancesIdsTransitions2;
    std::vector<long> transitionsToAddID;
    std::vector<long> transitionsToAddA;
    std::vector<long> transitionsToAddB;
    // std::vector<long [3]> transitionsToAdd;
    double maxArea=-INFINITY;
    long indexMax=-1;
    double minX=INFINITY;
    double minY=INFINITY;
    std::vector<long> idTransitionsToSetLater;
    for (long i=0;i<G->transitions.size();i++){
//        if(G->transitions[i].inverted){
//            inverted=!inverted;
//        }
        bool correctResultA=true;
        bool correctResultB=true;
        long nodeDualAID=-1;
        long nodeDualBID=-1;
        if(G->transitions[i].idNodeDualA==-1||G->transitions[i].idNodeDualB==-1){
            G->transitions[i].checkDirection(false);

            std::vector<long> idNodesA;
            std::vector<long> idTransitionsA;
            std::vector<bool> invertedTransitionsA;
            
            Graph::getRegionOfATransition(G,&G->transitions[i],idNodesA,idTransitionsA,invertedTransitionsA,false,correctResultA);
    //        if(i==177){
    //            std::cout<<i;
    //        }
            
            Point2d centroidA(0,0);
            double numberNodes=0;
            double areaA;
            std::vector<Point2d> points;
            points.reserve(idNodesA.size());
            for(long j=0;j<idNodesA.size();j++){
    //            Transition transition=G->transitions[regionA[j]];
    //            
    //            Node* nodeA=transition.a;
    //            Node* nodeB=transition.b;
    ////            bool correctOrder=false;
    //            if(j==0&&regionA.size()>1){
    //                if(nodeB==G->transitions[regionA[j+1]].a||nodeB==G->transitions[regionA[j+1]].b){
    ////                    correctOrder=true;
    //                    
    //                }else{
    //                    nodeA=transition.b;
    //                    nodeB=transition.a;
    //                }
    //            }
    //            
    //            
    //            
    //            if(!nodeA->inCutoff){
                
                    centroidA.x+=G->nodes[idNodesA[j]].location.x;
                    centroidA.y+=G->nodes[idNodesA[j]].location.y;
                    numberNodes++;
                    points.push_back(G->nodes[idNodesA[j]].location);
    //            }
    //            if(!nodeB->inCutoff){
    //                centroidA.y+=nodeB->location.y;
    //                centroidA.x+=nodeB->location.x;
    //                numberNodes++;
    //                points.push_back(nodeB->location);
                
    //            }
    //            nodeA->inCutoff=true;
    //            nodeB->inCutoff=true;
            }
            areaA=Functions::area(points);
            centroidA.x/=numberNodes;
            centroidA.y/=numberNodes;
    //        for(long j=0;j<regionA.size();j++){
    //            Transition transition=G->transitions[regionA[j]];
    //            Node* nodeA=transition.a;
    //            Node* nodeB=transition.b;
    //            nodeA->inCutoff=false;
    //            nodeB->inCutoff=false;
    //        }
            std::vector<long> idNodesB;
            std::vector<long> idTransitionsB;
            std::vector<bool> invertedTransitionsB;
            G->transitions[i].checkDirection(false);
            Graph::getRegionOfATransition(G,&G->transitions[i],idNodesB,idTransitionsB,invertedTransitionsB,true,correctResultB);

            
            Point2d centroidB(0,0);
            numberNodes=0;
            double areaB;
            points.clear();
            points.reserve(idNodesB.size());
            for(long j=0;j<idNodesB.size();j++){
//                Transition transition=G->transitions[regionB[j]];
//                Node* nodeA=transition.a;
//                Node* nodeB=transition.b;
//                if(j==0&&regionB.size()>1){
//                    if(nodeB==G->transitions[regionB[j+1]].a||nodeB==G->transitions[regionB[j+1]].b){
//                        //                    correctOrder=true;
//                        
//                    }else{
//                        nodeA=transition.b;
//                        nodeB=transition.a;
//                    }
//                }
//                
//                if(!nodeA->inCutoff){
                
                    centroidB.x+=G->nodes[idNodesB[j]].location.x;
                    centroidB.y+=G->nodes[idNodesB[j]].location.y;
                    numberNodes++;
                    points.push_back(G->nodes[idNodesB[j]].location);
//                }
//                if(!nodeB->inCutoff){
//                    centroidB.y+=nodeB->location.y;
//                    centroidB.x+=nodeB->location.x;
//                    numberNodes++;
//                    points.push_back(nodeB->location);
//                    
//                }
//                nodeA->inCutoff=true;
//                nodeB->inCutoff=true;
            }
            centroidB.x/=numberNodes;
            centroidB.y/=numberNodes;
            areaB=Functions::area(points);
            points.clear();
//            for(long j=0;j<regionB.size();j++){
//                Transition transition=G->transitions[regionB[j]];
//                Node* nodeA=transition.a;
//                Node* nodeB=transition.b;
//                nodeA->inCutoff=false;
//                nodeB->inCutoff=false;
//            }
            
            std::stringstream ss;
            ss<<round(centroidA.x*100)<<";"<<round(centroidA.y*100)<<";"<<round(areaA);
            
            
            
            
            
            if(correctResultA&&correctResultB){
                if (nodesDualByLocation[ss.str()]==0){
                    dual->addNode();
                    dual->nodes[dual->nodes.size()-1].location=centroidA;
                    if(centroidA.x<minX){
                        minX=centroidA.x;
                    }
                    if(centroidA.y<minY){
                        minY=centroidA.y;
                    }
                    nodeDualAID=dual->nodes.size()-1;
                    nodesDualByLocation[ss.str()]=dual->nodes.size();
                    
                }else{
                    nodeDualAID=nodesDualByLocation[ss.str()]-1;
                }
                if(areaA>=maxArea){
                    indexMax=nodeDualAID;
                    maxArea=areaA;
                }
                ss.str("");
                ss<<round(centroidB.x*100)<<";"<<round(centroidB.y*100)<<";"<<round(areaB);
                if (nodesDualByLocation[ss.str()]==0){
                    dual->addNode();
                    dual->nodes[dual->nodes.size()-1].location=centroidB;
                    if(centroidB.x<minX){
                        minX=centroidB.x;
                    }
                    if(centroidB.y<minY){
                        minY=centroidB.y;
                    }
                    nodeDualBID=dual->nodes.size()-1;
                    nodesDualByLocation[ss.str()]=dual->nodes.size();
                    
                }else{
                    nodeDualBID=nodesDualByLocation[ss.str()]-1;
                }
                if(areaB>=maxArea){
                    indexMax=nodeDualBID;
                    maxArea=areaB;
                }
                
                for(long k=0;k<idTransitionsA.size();k++){
                    if(!invertedTransitionsA[k]){
                        G->transitions[idTransitionsA[k]].idNodeDualA=nodeDualAID;
                    }else{
                        G->transitions[idTransitionsA[k]].idNodeDualB=nodeDualAID;
                    }
                }
                for(long k=0;k<idTransitionsB.size();k++){
                    if(!invertedTransitionsB[k]){
                        G->transitions[idTransitionsB[k]].idNodeDualA=nodeDualBID;
                    }else{
                        G->transitions[idTransitionsB[k]].idNodeDualB=nodeDualBID;
                    }
                }
                
            }
//            if(i+1==227){
//                std::cout<<"stop"<<'\n';
//            }
//            std::cout<<(i+1)<<'\n';
        }else{
//            std::cout<<"no need to calculate "<<(i+1)<<" "<<G->transitions[i].id<<" "<<G->transitions[i].idNodeDualA<<" "<<G->transitions[i].idNodeDualB<<'\n';
            nodeDualAID=G->transitions[i].idNodeDualA;
            nodeDualBID=G->transitions[i].idNodeDualB;
            correctResultA=true;
            correctResultB=true;
        }
        // long transitionToAdd[3];
        if(correctResultA&&correctResultB){
//            std::cout<<"inserting "<<(i+1)<<" "<<G->transitions[i].id<<" "<<G->transitions[i].idNodeDualA<<" "<<nodeDualAID<<" "<<G->transitions[i].idNodeDualB<<" "<<nodeDualBID<<'\n';
            transitionsToAddID.push_back(G->transitions[i].id);
            transitionsToAddA.push_back(nodeDualAID);
            transitionsToAddB.push_back(nodeDualBID);
        }else{
//            std::cout<<"tosetlater "<<(i+1)<<" "<<G->transitions[i].id<<'\n';
            idTransitionsToSetLater.push_back(G->transitions[i].id);
        }
        // transitionsToAdd.push_back(transitionToAdd);
        
    }
    for(long i=0;i<idTransitionsToSetLater.size();i++){
       
        long nodeDualAID=G->transitions[idTransitionsToSetLater[i]].idNodeDualA;
        long nodeDualBID=G->transitions[idTransitionsToSetLater[i]].idNodeDualB;
//         std::cout<<"to set later, inserting "<<(idTransitionsToSetLater[i]+1)<<" "<<G->transitions[idTransitionsToSetLater[i]].id<<" "<<G->transitions[idTransitionsToSetLater[i]].idNodeDualA<<" "<<nodeDualAID<<" "<<G->transitions[idTransitionsToSetLater[i]].idNodeDualB<<" "<<nodeDualBID<<'\n';
        transitionsToAddID.push_back(idTransitionsToSetLater[i]);
        transitionsToAddA.push_back(nodeDualAID);
        transitionsToAddB.push_back(nodeDualBID);
    }
    
    std::vector<long> order=Functions::getIndexesOfOrderedValues(transitionsToAddID, true);
    
//    correspondancesIdsTransitions1.resize(transitionsToAddID.size());
//    correspondancesIdsTransitions2.resize(transitionsToAddID.size());
    
    Point2d locationTemp=dual->nodes[0].location;
    dual->nodes[0].location=Point2d(minX-500,minY-500);
    dual->nodes[indexMax].location=locationTemp;
    
    for(long i=0;i<transitionsToAddID.size();i++){
//        std::cout<<transitionsToAddID[order[i]]<<'\n';
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
        Transition trans;
        trans.id=i;
        if(transitionsToAddA[order[i]]==-1){
//            std::cout<<transitionsToAddID[order[i]]<< " "<<(order[i]+1)<<",";
            transitionsToAddA[order[i]]=0;
        }
        if(transitionsToAddB[order[i]]==-1){
//            std::cout<<transitionsToAddID[order[i]]<< " "<<(order[i]+1)<<",";
            transitionsToAddB[order[i]]=0;
        }
        trans.a=&dual->nodes[transitionsToAddA[order[i]]];
        trans.b=&dual->nodes[transitionsToAddB[order[i]]];
        trans.weight=Functions::getDistance(trans.a->location,trans.b->location);
        
        long index=trans.a->transitions.size()+1;
        dual->transitions.push_back(trans);
        Vector_elem<Transition> transPointer(dual->transitions);
        trans.a->transitions.push_back(transPointer);
        trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
        bool exist=false;
        for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
            if(trans.b->nodesThatReachMe[i]==trans.a){
                exist=true;
            }
        }
        if(!exist){
            trans.b->nodesThatReachMe.push_back(trans.a);
        }
        Vector_elem<Transition> transPointerInverted(dual->transitions,dual->transitions.size()-1);
//        transPointer.invert=true;
        trans.b->transitions.push_back(transPointerInverted);
        trans.b->indexOfTransitionsByIdOfDestination[trans.a->originalID]=index;
        exist=false;
        for(long i=0;i<trans.a->nodesThatReachMe.size();i++){
            if(trans.a->nodesThatReachMe[i]==trans.b){
                exist=true;
            }
        }
        if(!exist){
            trans.a->nodesThatReachMe.push_back(trans.b);
        }

        
//        std::cout<<trans.a->id<<" "<<trans.b->id<<" "<<trans.weight<<'\n';
//        dual->addDirectedTransition(trans);
        //    long correspondance[2];
//        correspondancesIdsTransitions1[i]=transitionsToAddID[i];
//        correspondancesIdsTransitions2[i]=i;
        // correspondancesIdsTransitions.push_back(correspondance);
    }
//    for(long i=0;i<dual->transitions.size();i++){
//        std::cout<<dual->transitions[i].id<<'\n';
//    }
//    dual->transformToBidirectional();
    for(long i=0;i<G->transitions.size();i++){
        G->transitions[i].idNodeDualA=-1;
        G->transitions[i].idNodeDualB=-1;
    }
//    Rcpp::XPtr< Graph > p(dual,true) ;
//    List list(2);
//    list[0]=p;
//    List list_df(2);
//    list_df[0]=wrap(correspondancesIdsTransitions1);
//    list_df[1]=wrap(correspondancesIdsTransitions2);
//    // list[2]=(degreeOut);
//    
//    CharacterVector namevec;
//    namevec.push_back("idOriginalTransition");
//    namevec.push_back("idDualTransition");
//    // namevec.push_back("degreeIn");
//    
//    list_df.attr("names") = namevec;
//    DataFrame df(list_df);
//    list[1]=df;
//    return list;
}

void Graph::correctGeometryOfDual(Graph* G,Graph* dual,Graph* result,std::vector<long>& correspondanceID_originalGraph,std::vector<long>& correspondanceID_result){
    result->pseudoGraph=true;
    result->allowLoops=true;
//    Graph geometryDual;
    long maxIdNodes=dual->nodes.size()-1;
    for(long i=0;i<dual->nodes.size();i++){
        result->addNode();
        result->nodes[i].location=dual->nodes[i].location;
    }
    for(long i=0;i<G->transitions.size();i++){
        result->addNode();
        result->nodes[i+maxIdNodes+1].location=Point2d((G->transitions[i].a->location.x+G->transitions[i].b->location.x)/2,(G->transitions[i].a->location.y+G->transitions[i].b->location.y)/2);
        result->nodes[i+maxIdNodes+1].mass=0;
    }
    long idTrans=0;
    for(long i=0;i<dual->transitions.size();i++){
        correspondanceID_originalGraph.push_back(i);
        correspondanceID_result.push_back(idTrans);
        
        Transition trans1;
        trans1.a=&result->nodes[dual->transitions[i].a->id];
        trans1.b=&result->nodes[i+maxIdNodes+1];
        trans1.weight=Functions::getDistance(trans1.a->location, trans1.b->location);
        correspondanceID_originalGraph.push_back(i);
        correspondanceID_result.push_back(idTrans);
        trans1.id=idTrans;
        idTrans++;
        Transition trans2;
        trans2.a=trans1.b;
        trans2.b=&result->nodes[dual->transitions[i].b->id];
        trans2.weight=Functions::getDistance(trans2.a->location, trans2.b->location);
        trans2.id=idTrans;
        idTrans++;
//        result->addDirectedTransition(trans1);
//        result->addDirectedTransition(trans2);
        Transition trans=trans1;
        long index=trans.a->transitions.size()+1;
        result->transitions.push_back(trans);
        Vector_elem<Transition> transPointer(result->transitions);
        trans.a->transitions.push_back(transPointer);
        trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
        bool exist=false;
        for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
            if(trans.b->nodesThatReachMe[i]==trans.a){
                exist=true;
            }
        }
        if(!exist){
            trans.b->nodesThatReachMe.push_back(trans.a);
        }
        
        trans=trans2;
        index=trans.a->transitions.size()+1;
        result->transitions.push_back(trans);
        Vector_elem<Transition> transPointer2(result->transitions);
        trans.a->transitions.push_back(transPointer2);
        trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]=index;
        exist=false;
        for(long i=0;i<trans.b->nodesThatReachMe.size();i++){
            if(trans.b->nodesThatReachMe[i]==trans.a){
                exist=true;
            }
        }
        if(!exist){
            trans.b->nodesThatReachMe.push_back(trans.a);
        }
    }
    result->transformToBidirectional();
//    geometryDual.transformToBidirectional();
//    std::vector<Node*> nodes;
//    nodes.resize(geometryDual.nodes.size()-1);
//    for(long i=1;i<geometryDual.nodes.size();i++){
//        nodes[i-1]=&geometryDual.nodes[i];
//    }
//    geometryDual.getInducedSubgraph(result, nodes);
    
    
}

void Graph::removeExternalNodeDual(Graph* G,Graph* dual,Graph* result,std::vector<long> &correspondanceID_originalGraph,std::vector<long>& correspondanceID_result){
//    Graph geometryDual;
//    long maxIdNodes=dual->nodes.size()-2;
    for(long i=1;i<dual->nodes.size();i++){
        result->addNode();
        result->nodes[i-1].location=dual->nodes[i].location;
    }
    
//    for(long i=0;i<G->transitions.size();i++){
//        result->addNode();
//        result->nodes[i+maxIdNodes+1].location=Point2d((G->transitions[i].a->location.x+G->transitions[i].b->location.x)/2,(G->transitions[i].a->location.y+G->transitions[i].b->location.y)/2);
//    }
    long numTrans=0;
    for(long i=0;i<dual->transitions.size();i++){
        if(dual->transitions[i].a->id!=0&&dual->transitions[i].b->id!=0){
            
            Transition trans2;
            trans2.a=&result->nodes[dual->transitions[i].a->id];
    //        trans1.b=&result->nodes[i+maxIdNodes+1];
    //        trans1.weight=Functions::getDistance(trans1.a->location, trans1.b->location);
    //        Transition trans2;
    //        trans2.a=trans1.b;
            trans2.b=&result->nodes[dual->transitions[i].b->id];
            trans2.weight=Functions::getDistance(trans2.a->location, trans2.b->location);
    //        result->addDirectedTransition(trans1);
            result->addDirectedTransition(trans2);
            correspondanceID_originalGraph.push_back(i);
            correspondanceID_result.push_back(numTrans);
            numTrans++;
            
        }
    }
    result->transformToBidirectional();
//    std::vector<Node*> nodes;
//    nodes.resize(geometryDual.nodes.size()-1);
//    for(long i=1;i<geometryDual.nodes.size();i++){
//        nodes[i-1]=&geometryDual.nodes[i];
//    }
//    geometryDual.getInducedSubgraph(result, nodes);
    
    
}

void Graph::cleanDelaunay(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys,std::vector<std::vector<long> > &delaunay,std::vector<double> &weights,double tolerance){
//    std::unordered_map<long, bool> existsId;
    std::vector<long> idA,idB;
    idA=delaunay[0];
    idB=delaunay[1];
    std::unordered_map<std::string,bool> acceptTransition;
    Graph G;
    for(long i=0;i<xs.size();i++){
        G.addNode();
        G.nodes[i].originalID=ids[i];
        G.nodes[i].location=Point2d(xs[i],ys[i]);
    }
    for(long i=0;i<idA.size();i++){
        Transition trans;
        trans.a=&G.nodes[idA[i]];
        trans.b=&G.nodes[idB[i]];
        trans.weight=Functions::getDistance(trans.a->location, trans.b->location);
//        double angle=Functions::getAngle(trans.a->location, trans.b->location);
//        bool accept=true;
//        for(long j=0;j<trans.a->transitions.size();j++){
//            double angle=Functions::getAngle(trans.a->transitions[j]->b->location,trans.a->location, trans.b->location);
//            if(Functions::abs(angle)>180-tolerance){
//                std::cout<<"not accepting transition"<<'\n';
//                accept=false;
//                if(trans.weight<trans.a->transitions[j]->weight){
//                    trans.a->transitions[j]->weight=trans.weight;
//                    trans.a->transitions[j]->b=trans.b;
//                }
//            }
//        }
//        if(accept){
            G.addDirectedTransition(trans);
//        }
        std::stringstream ss;
        ss<<trans.a->id<<";"<<trans.b->id;
        acceptTransition[ss.str()]=true;
        ss.str("");
        ss<<trans.b->id<<";"<<trans.a->id;
        acceptTransition[ss.str()]=true;
    }
    G.transformToBidirectional();
//    Graph g2;
//    for(long i=0;i<xs.size();i++){
//        g2.addNode();
//        g2.nodes[i].originalID=ids[i];
//        g2.nodes[i].location=Point2d(xs[i],ys[i]);
//    }
    
    for(long i=0;i<G.nodes.size();i++){
        for(long k=0;k<G.nodes[i].transitions.size();k++){
            Transition trans;
            trans.a=G.nodes[i].transitions[k]->a;
            trans.b=G.nodes[i].transitions[k]->b;
            trans.weight=G.nodes[i].transitions[k]->weight;
            //        double angle=Functions::getAngle(trans.a->location, trans.b->location);
//            bool accept=true;
            for(long j=0;j<trans.a->transitions.size();j++){
                double angle=Functions::getAngle(trans.a->transitions[j]->b->location,trans.a->location, trans.b->location);
                if(Functions::abs(angle)>180-tolerance&&j!=k){
//                    std::cout<<"not accepting transition"<<'\n';
//                    accept=false;
                    if(trans.weight<trans.a->transitions[j]->weight){
//                        trans.a->transitions[j]->weight=trans.weight;
//                        trans.a->transitions[j]->b=trans.b;
                        std::stringstream ss;
                        ss<<trans.a->transitions[j]->a->id<<";"<<trans.a->transitions[j]->b->id;
                        acceptTransition[ss.str()]=false;
                        ss.str("");
                        ss<<trans.a->transitions[j]->b->id<<";"<<trans.a->transitions[j]->a->id;
                        acceptTransition[ss.str()]=false;
                        
//                        ss.str("");
//                        ss<<trans.a->id<<";"<<trans.b->id;
//                        acceptTransition[ss.str()]=true;
//                        ss.str("");
//                        ss<<trans.b->id<<";"<<trans.a->id;
//                        acceptTransition[ss.str()]=true;
                    }else{
                        std::stringstream ss;
                        ss<<trans.a->id<<";"<<trans.b->id;
                        acceptTransition[ss.str()]=false;
                        ss.str("");
                        ss<<trans.b->id<<";"<<trans.a->id;
                        acceptTransition[ss.str()]=false;
                        
//                        ss.str("");
//                        ss<<trans.a->transitions[j]->a->id<<";"<<trans.a->transitions[j]->b->id;
//                        acceptTransition[ss.str()]=true;
//                        ss.str("");
//                        ss<<trans.a->transitions[j]->b->id<<";"<<trans.a->transitions[j]->a->id;
//                        acceptTransition[ss.str()]=true;
                    }
                }else{
//                    std::stringstream ss;
//                    ss<<trans.a->id<<";"<<trans.b->id;
//                    acceptTransition[ss.str()]=true;
//                    ss.str("");
//                    ss<<trans.b->id<<";"<<trans.a->id;
//                    acceptTransition[ss.str()]=true;
                }
            }
//            if(accept){
//                G.addDirectedTransition(trans);
//            }
        }
    }
//    std::vector<std::vector<long> > result;
    idA.clear();
    idB.clear();
//    idA.resize(G.transitions.size());
//    idB.resize(G.transitions.size());
//    weights.resize(G.transitions.size());
    for(long i=0;i<G.transitions.size();i++){
        std::stringstream ss;
        ss<<G.transitions[i].a->id<<";"<<G.transitions[i].b->id;
        if(acceptTransition[ss.str()]){
            idA.push_back(G.transitions[i].a->originalID);
            idB.push_back(G.transitions[i].b->originalID);
            weights.push_back(G.transitions[i].weight);
        }
    }
    delaunay.clear();
    delaunay.resize(2);
    delaunay[0]=idA;
    delaunay[1]=idB;
//    result.resize(2);
//    result[0]=idA;
//    result[1]=idB;
//    
//    return result;
    
}









void Graph::calculateDegrees(Graph* G){
    
    for(long i=0;i<G->nodes.size();i++){
        Node* node=&G->nodes[i];
        G->nodes[i].degree=Graph::getDegree(node);
        G->nodes[i].degreeIn=Graph::getDegreeIn(node);
        G->nodes[i].degreeOut=Graph::getDegreeOut(node);
    }
    G->degreesCalculated=true;
}


std::vector<long> Graph::getNeighboursIDs(Graph* G,long nodeID){
    //using internal igraph representation of nodes (to avoid that the name is larger than a long)
    
    std::vector<long> result;
    Node node=G->nodes[nodeID];
    for(long i=0;i<node.transitions.size();i++){
        result.push_back(node.transitions[i]->b->id);
    }
    return (result);
    
}

std::vector<Transition*> Graph::findPathDegree2(Graph* G,long nodeID){
    if(!G->degreesCalculated){
        Graph::calculateDegrees(G);
    }
    std::vector<long> neighboursIDs=Graph::getNeighboursIDs(G,nodeID);
    std::vector<Transition*> path;
    //  path.push_back(&G->nodes[nodeID]);
    //side 1
    
    
    if(G->bidirectional){
        bool STOP=false;
        Node* neighbour=&G->nodes[neighboursIDs[0]];
        neighbour->inCutoff=true;
        path.push_back(G->nodes[nodeID].transitions[0]);
        if(neighbour->degree!=2){
            STOP=true;
        }
        std::vector<long> neighboursIDs_internal;
        long counter=0;
        while(!STOP){
            
            if(counter>G->nodes.size()){
                STOP=true;
            }
            counter++;
            neighboursIDs_internal.clear();
            neighboursIDs_internal=Graph::getNeighboursIDs(G,neighbour->id);
            //      if(neighboursIDs.size()>1){
            long id=-1;
            long index=0;
            for(long i=0;i<neighboursIDs_internal.size();i++){
                if(neighboursIDs_internal[i]!=path[path.size()-1]->b->id){
                    //                       neighbour=&G->nodes[neighboursIDs_internal[i]];
                    id=neighboursIDs_internal[i];
                    index=i;
                }
            }
            if(id!=-1){
                path.push_back(neighbour->transitions[index]);
                neighbour=&G->nodes[id];
                
                if(neighbour->degree!=2){
                    STOP=true;
                }else{
                    neighbour->inCutoff=true;
                }
            }else{
                STOP=true;
            }
            //      }
            //      else{
            //          if(neighboursIDs.size()==0){
            //              STOP=true;
            //          }
            ////          else if(neighboursIDs.size()==1){
            ////              neighbour=G->nodes[neighboursIDs[0]];
            ////              nodesInPath.push_back(neighbour);
            ////              STOP=true;
            ////          }
            //      }
        }
        //side 2
        if(neighboursIDs.size()>1){
            bool STOP=false;
            Node* neighbour=&G->nodes[neighboursIDs[1]];
            neighbour->inCutoff=true;
            path.push_back(G->nodes[nodeID].transitions[1]);
            if(neighbour->degree!=2){
                STOP=true;
            }
            //           std::vector<long> neighboursIDs_internal
            counter=0;
            while(!STOP){
                if(counter>G->nodes.size()){
                    STOP=true;
                }
                counter++;
                neighboursIDs_internal.clear();
                neighboursIDs_internal=Graph::getNeighboursIDs(G,neighbour->id);
                //      if(neighboursIDs.size()>1){
                long id=-1;
                long index=0;
                for(long i=0;i<neighboursIDs_internal.size();i++){
                    if(neighboursIDs_internal[i]!=path[path.size()-1]->b->id){
                        //                       neighbour=&G->nodes[neighboursIDs_internal[i]];
                        id=neighboursIDs_internal[i];
                        index=i;
                    }
                }
                if(id!=-1){
                    path.push_back(neighbour->transitions[index]);
                    neighbour=&G->nodes[id];
                    
                    if(neighbour->degree!=2){
                        STOP=true;
                    }else{
                        neighbour->inCutoff=true;
                    }
                }else{
                    STOP=true;
                }
                //      }
                //      else{
                //          if(neighboursIDs.size()==0){
                //              STOP=true;
                //          }
                ////          else if(neighboursIDs.size()==1){
                ////              neighbour=G->nodes[neighboursIDs[0]];
                ////              nodesInPath.push_back(neighbour);
                ////              STOP=true;
                ////          }
                //      }
            }
        }
    }
    return path;
}



void Graph::burnGraph(Graph* G,Graph* burnedGraph){
    if(!G->degreesCalculated){
        Graph::calculateDegrees(G);
    }
    //  NumericVector idA;
    //  NumericVector idB;
    //  NumericVector weights;
    std::vector<Node*> otherNodes;
    for(long i=0;i<G->nodes.size();i++){
        if (G->nodes[i].degree==1&&!G->nodes[i].inCutoff){
            Graph::findPathDegree2(G,G->nodes[i].id);
        }
    }
    for(long i=0;i<G->nodes.size();i++){
        if (!G->nodes[i].inCutoff){
            Node* node=&G->nodes[i];
            otherNodes.push_back(node);
        }
    }
    for(long i=0;i<G->nodes.size();i++){
        G->nodes[i].inCutoff=false;
    }
//    Graph subGraph;
    G->getInducedSubgraph(burnedGraph,otherNodes);
//    Rcpp::XPtr< Graph > p(subGraph,true) ;
//    return (subGraph);
}
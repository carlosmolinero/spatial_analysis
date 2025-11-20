#ifndef NODE_H
#define NODE_H
//#include <string>
#include <vector>
#include "MinHeap.h"
#include "WaterDrop.h"

class Transition;
#include "Transition.h"
#include "Point2d.h"
//class ClusterRTree;
//#include "ClusterRTree.h"
#include <unordered_map>
#include "Vector_elem.h"
#include "Vector_ve.h"

class Node
{
public:
    long numberOfTimesVisited;
    double diffusionValue;
    bool isCenter;
    bool isCovered;
    double mass;
    double probabilityInPath;
    bool alreadyCalculated;
    std::string nameRoad;
    double levelHierarchyRoad;
    std::vector<double> dataVector;
    std::vector<double> averagedDataVector;
    long clusterOfPercolationToWhichItBelongs;
    std::vector<long> indexInHeap;
    std::vector<std::vector<double> > customizedGeneratedTrips;
    std::vector<std::vector<double> > customizedAttractedTrips;
    std::vector<Node*> nodesRelated;
    long kShellValue;
    long kShellValueFinal;
    std::vector<Node*> nodesCollapsed;
    std::vector<Transition*> transitionsCollapsedIntoNode;
    
    std::unordered_map<long,double> treeCoordinates;
    
    Transition* transitionThatRepresents;
    long degree;
    long degreeOut;
    long degreeIn;
    long degreeModifierOut;
        long degreeModifierIn;
    long degreeModifier;
//    double specialDistance;
    double tripsGenerated;
    double tripsReceived;
    std::unordered_map<signed long long,double> tripsReceivedFromNodeByID;
    long  numColor;
    double dMax;
    Node* initialNodeOfDiameter;
    std::unordered_map<signed long long,long> indexOfTransitionsByIdOfDestination;
    bool inSubgraph;
    bool inExternalNodes;
    Point2d location;
    Node();
    WaterDrop waterLevel;
    virtual ~Node();
    Vector_ve<Transition> transitions;
    std::vector<Node*> nodesThatReachMe;
    std::vector<Transition> verticalPathsTowardsUpperLevel;
    std::vector<Transition> verticalPathsTowardsLowerLevel;
    std::vector<Transition> horizontalPaths;

//		double minCurrentDistance;
    double minDistance;
//    double minDistanceAStar;
    std::vector<Node*> otherParents;
    int numberDistances;
//		Node* otherParents[];
    std::vector<double> minOtherDistances;
    std::vector<int> numOtherChildren;
    std::vector<int> numOtherChildrenThatReachedMe;
    std::vector<double> valuesToPass;
    std::vector<double> originalValuesToPass;
//        double minOtherDistances[];
    Node* parent;
    std::vector<Node*> parents;
    long id;
    double nodeCount;
//        double TSL;
//        double totalDepth;
//		std::vector<double> totalDepthOthers;
//        double betweenness;
//        std::vector<double> betweennessOthers;

//        bool transitionsAlreadyUsed;


//        bool considerForDistance;
//        bool considerForOtherDistances;

    Node* nodeThatRepresents;
    Node* nodeRepresentedBy;
    long idEquivalentUpperVerticalNode;
    long idEquivalentLowerVerticalNode;
    Node* getCopy();
    bool hasParent;
    bool inDijkstra;
    bool inAStar;
    bool inVisitedNodes;
    bool inCluster;
    bool inNodesWithWater;
    bool isFrontier;
    bool isFrontierOfDifferentLevel;
//    double population;
    double valueToPass;
    double originalValueToPass;
    int numChildren;
    int numChildrenThatReachedMe;
    bool inCutoff;
    unsigned long long originalID;
    int depthInRTree;
    int depthInQTree;
    long upperLevel;
//        bool isFrontierNode;
//        ClusterRTree* cluster;
    double heuristicDistanceToGoal;
    Node* uppestRepresentative;
    Node* nodeInOriginalGraph;
    static void setIndexInHeap(Node* &node,long index,long indexOfTheHeap);
    static long getIndexInHeap( Node* &node,long indexOfTheHeap);


protected:
private:
};

#endif // NODE_H

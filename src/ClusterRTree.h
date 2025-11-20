#ifndef CLUSTERRTREE_H
#define CLUSTERRTREE_H
//class Graph;
#include "Graph.h"
#include "Point2d.h"
//class RTree;
//#include "RTree.h"
//#include "TransitionCluster.h"
#include"SparseMatrix.h"
#include "Matrix.h"
//#include "Timer.h"

class CoordinatesTransition
{
private:
public:
    Node* node;
    long idTrans;
//    Transition trans;
    bool fixB=true;
    long idB;

};
class ClusterRTree
{
public:
//    Timer timer;
    static const int A_STAR=0;
    static const int TREE_DISTANCE=1;
    static const int MIXED=2;
    std::vector<ClusterRTree*> clustersById;
    void setClustersToCalculateDistances(std::vector<Transition> &originDestinationPairs);
    void setClustersToConstructBackwards(std::vector<Transition> &originDestinationPairs);
    bool distancesCalculated;
    bool inCalculateDistances;
    bool inConstruction;
    double calculateDistance(Node* a,Node* b);
    void completeConnectionsOfLevel(std::vector<ClusterRTree*> &nextLevel,std::vector<ClusterRTree*> &leavesInUpperLevels);
//    SparseMatrix* matrixDistances;
//    SparseMatrix matrixDistancesCluster;
//    Matrix* matrixDistances;
    bool completedBackwardsProcess;
//    void insertDistance(double value,long col,long row,long module);
//    double getDistance (long col,long row,long module);
//    BST<TransitionCluster*> transitionsById;
    BST<ClusterRTree*> externalLeavesById;
    MinHeap<ClusterRTree*> externalClustersByDepth;
    double findDistanceRecursive(Node* a, Node* b);
    long idTransitions;
//        std::vector<TransitionCluster> transitionsNorth;
//            std::vector<TransitionCluster> transitionsWest;
//            std::vector<TransitionCluster> transitionsEast;
//            std::vector<TransitionCluster> transitionsSouth;
    bool northIsExternal;
    bool westIsExternal;
    bool eastIsExternal;
    bool southIsExternal;
    ClusterRTree* externalCluster;
    long id;
    long idClusters;
    BST<ClusterRTree*> leavesById;
    MinHeap<ClusterRTree*> clustersByDepth;
    ClusterRTree();
    Point2d corners[2];
    virtual ~ClusterRTree();
    std::vector<Node*> nodesInCluster;
    std::vector<Node*> frontierNodes;
    std::vector<Transition> externalTransitions;
    BST<Transition*> subDiameters;
    std::vector<CoordinatesTransition> externalTransitionsToSolveLater;
    std::vector<CoordinatesTransition> externalTransitionsToInsertNodeRepresentedBy;
    void divide();
    void addNode(Node* &node);
    void addExternalNode(Node* &node);
    Graph* graph;
    Graph* graphTemp;
    Graph* originalGraph;
//        Graph augmentedGraph;
    std::vector<ClusterRTree> sons;
    ClusterRTree* parent;
    bool isLeave;
    long maxNumberNodes;
    int depth;

    ClusterRTree* getSonThatCorrespondToNode(Node* &node);
    double widthClusterSons;
    double heightClusterSons;
    double numVertDivisions;
    double numHorDivisions;
    void generateRTreeGraph(Graph* mainGraph,std::vector<Transition> &originDestinationPairs,int mode);
    void generateRTreeGraphAux(Graph* mainGraph);
    bool graphCreated;
    void handleGraphGeneration(Graph* graph);
    void handleGraphGenerationAux();
    void handleGraphGenerationBackwards(std::vector<ClusterRTree*> &nextLevel,int mode);
    void handleGraphGenerationBackwardsAux(int mode);
//        void calculateDiameter();
    void fixHorizontalTransitions(std::vector<ClusterRTree*> clusters);
    void fixExternalTransitions(ClusterRTree* cluster);
    ClusterRTree* mainCluster;
    ClusterRTree* getClusterOfNode(Node* a);
    ClusterRTree* getDeepestClusterOfNode(Node* a);

    ClusterRTree* getCommonLevelOfTwoNodes(Node* a,Node* b);
//      ClusterRTree* getCommonUpperLevelOfTwoNodes(Node* a,Node* b);
//    long getHighestLevelOfNode(Node* a);
    void prepareVerticalTransitionsAndShortcuts();
    static bool compareByDepth(ClusterRTree* &a, ClusterRTree* &b);
//        RTree* rTree;
protected:
private:
    void calculateDistanceNodeInLeaveCluster(Node* a);
};

#endif // CLUSTERRTREE_H

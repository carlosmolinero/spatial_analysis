#ifndef CLUSTERQTree_H
#define CLUSTERQTree_H
//class Graph;
//#include "Graph.h"
#include "Point2d.h"
//class QTree;
//#include "QTree.h"
#include "TransitionCluster.h"
#include"SparseMatrix.h"
#include "Matrix.h"
#include "BST.h"
//#include "Timer.h"

//class CoordinatesTransition
//{
//private:
//public:
//    Node* node;
//    long idTrans;
////    Transition trans;
//    bool fixB=true;
//    long idB;
//
//};
class ClusterQTree
{
public:
//    Timer timer;
    static const int A_STAR=0;
    static const int TREE_DISTANCE=1;
    static const int MIXED=2;
    std::vector<ClusterQTree*> clustersById;

    bool distancesCalculated;
    bool inCalculateDistances;
    bool inConstruction;
    double calculateDistance(Node* a,Node* b);

//    SparseMatrix* matrixDistances;
//    SparseMatrix matrixDistancesCluster;
//    Matrix* matrixDistances;
    bool completedBackwardsProcess;
//    void insertDistance(double value,long col,long row,long module);
//    double getDistance (long col,long row,long module);
//    BST<TransitionCluster*> transitionsById;
    BST<ClusterQTree*> externalLeavesById;
    MinHeap<ClusterQTree*> externalClustersByDepth;

    long idTransitions;
        std::vector<TransitionCluster> transitionsNorth;
            std::vector<TransitionCluster> transitionsWest;
            std::vector<TransitionCluster> transitionsEast;
            std::vector<TransitionCluster> transitionsSouth;
    bool northIsExternal;
    bool westIsExternal;
    bool eastIsExternal;
    bool southIsExternal;
    ClusterQTree* externalCluster;
    long id;
    long idClusters;
    BST<ClusterQTree*> leavesById;
    MinHeap<ClusterQTree*> clustersByDepth;
    ClusterQTree();
    Point2d corners[2];
    virtual ~ClusterQTree();
    std::vector<Node*> nodesInCluster;
    std::vector<Node*> frontierNodes;
    std::vector<Transition> externalTransitions;
    BST<Transition*> subDiameters;
//    std::vector<CoordinatesTransition> externalTransitionsToSolveLater;
//    std::vector<CoordinatesTransition> externalTransitionsToInsertNodeRepresentedBy;
    void divide();
    void addNode(Node* &node);
    void addExternalNode(Node* &node);
//    Graph* graph;
//    Graph* graphTemp;
//    Graph* originalGraph;
//        Graph augmentedGraph;
    std::vector<ClusterQTree> sons;
    ClusterQTree* parent;
    bool isLeave;
    long maxNumberNodes;
    int depth;

    ClusterQTree* getSonThatCorrespondToNode(Node* &node);
    double widthClusterSons;
    double heightClusterSons;
    double numVertDivisions;
    double numHorDivisions;

    bool graphCreated;

//        void calculateDiameter();

    void fixExternalTransitions(ClusterQTree* cluster);
    ClusterQTree* mainCluster;
    ClusterQTree* getClusterOfNode(Node* a);
    ClusterQTree* getDeepestClusterOfNode(Node* a);

    ClusterQTree* getCommonLevelOfTwoNodes(Node* a,Node* b);
//      ClusterQTree* getCommonUpperLevelOfTwoNodes(Node* a,Node* b);
//    long getHighestLevelOfNode(Node* a);

    static bool compareByDepth(ClusterQTree* &a, ClusterQTree* &b);
//        QTree* QTree;
protected:
private:
    void calculateDistanceNodeInLeaveCluster(Node* a);
};

#endif // CLUSTERQTree_H

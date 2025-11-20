#ifndef RTREE_H
#define RTREE_H

#include "ClusterRTree.h"
#include "SparseMatrix.h"
#include "Matrix.h"
#include "BST.h"

class RTree
{
public:

    int mode;
    static const int A_STAR=0;
    static const int TREE_DISTANCE=1;

    RTree(int mode);
        RTree();
    double calculateAllToAllDistances();
    virtual ~RTree();
//    SparseMatrix matrixDistances;

//    Matrix matrixDistances;
//    void insertDistance(double value,long col,long row,long module);
//    double getDistance (long col,long row,long module);
//    void generateSpatialPercolation(Graph* graph,double distanceLimit);
    void generateRTreeGraph(Graph* mainGraph,std::vector<Transition> &originDestinationPairs);
    void generateCornersOfMainCluster(Graph* mainGraph);
    ClusterRTree mainCluster;
    ClusterRTree externalCluster;
    long maxNumberNodes;
    ClusterRTree* insertNode(Node* node);
    ClusterRTree* getDeepestClusterOfNode(Node* a);
    ClusterRTree* getClusterOfNode(Node* a);
    ClusterRTree* getCommonParent(ClusterRTree* a,ClusterRTree* b);
    ClusterRTree* getCommonLevelOfTwoNodes(Node* a,Node*b);
    double AStar(Node* a,Node* b,bool save);
    ClusterRTree* getCommonUpperLevelOfTwoNodes(Node* a,Node* b);
    long getHighestLevelOfNode(Node* a);
    Node* getHighestRepresentativeOfNode(Node* a);
    double calculateDiameter();
    std::vector<double> calculateDistances(std::vector<Transition> &originDestinationPairs);
    std::vector<Transition> getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(Graph* graph);
    std::vector<ClusterRTree*> getClustersInARange(double minX,double minY,double maxX,double maxY);
    std::vector<Node*> getNodesOfClusters(std::vector<ClusterRTree*> clusters);
    std::vector<Node*> getNodesInARange(double minX,double minY,double maxX,double maxY);
protected:
private:
//        MinHeap<ClusterRTree*> clustersByLevel;
    bool isDeeperThan(ClusterRTree* a,ClusterRTree* b);
};

#endif // RTREE_H

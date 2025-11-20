#ifndef QTree_H
#define QTree_H

#include "ClusterQTree.h"
#include "SparseMatrix.h"
#include "Matrix.h"
#include "Functions.h"
//#include "Graph.h"

class QTree
{
public:

    int mode;
    static const int A_STAR=0;
    static const int TREE_DISTANCE=1;

    QTree(int mode);
    QTree();

    virtual ~QTree();
//    SparseMatrix matrixDistances;

//    Matrix matrixDistances;
//    void insertDistance(double value,long col,long row,long module);
//    double getDistance (long col,long row,long module);
//    void generateSpatialPercolation(Graph* graph,double distanceLimit);

    void generateCornersOfMainCluster(double minX,double maxX,double minY,double maxY);
    ClusterQTree mainCluster;
    ClusterQTree externalCluster;
//    long maxNumberNodes;
//    ClusterQTree* insertNode(Node* node);
    ClusterQTree* getDeepestClusterOfNode(Node* a);
    ClusterQTree* getClusterOfNode(Node* a);
    ClusterQTree* getCommonParent(ClusterQTree* a,ClusterQTree* b);
    ClusterQTree* getCommonLevelOfTwoNodes(Node* a,Node*b);
    double AStar(Node* a,Node* b,bool save);
//    ClusterQTree* getCommonUpperLevelOfTwoNodes(Node* a,Node* b);



    std::vector<Transition> getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(double minX,double maxX,double minY,double maxY,std::vector<Node*> &nodesOfGraph);
    std::vector<ClusterQTree*> getClustersInARange(double minX,double minY,double maxX,double maxY);
    std::vector<Node*> getNodesOfClusters(std::vector<ClusterQTree*> clusters);
    std::vector<Node*> getNodesInARange(double minX,double minY,double maxX,double maxY);
    std::vector<Node*> getNodesInARange(Point2d center,double radius);
    Node* getClosestNode(Point2d point);
     Node* getClosestNode(Node* nodeInit);
//    void insertGraph(Graph* graph);
protected:
private:
//        MinHeap<ClusterQTree*> clustersByLevel;
    bool isDeeperThan(ClusterQTree* a,ClusterQTree* b);
};

#endif // QTree_H

#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>
//class Node;
#include "Node.h"
#include "Transition.h"
#include <algorithm>
//#include "MinHeap.h"
#include "TextFile.h"
//#include "BST.h"
#include "CompareFunc.h"
#include <math.h>
#include <thread>
#include "Configuration.h"
#include <queue>
#include "LinearRegression.h"
#include "Functions.h"
#include "QTree.h"
//class Customize;
#include "Customize.h"
#include "Heap.h"
#include "Functor.h"
#include "PotentialField.h"



//class RTree;
//#include "RTree.h"

//class ClusterRTree;
//#include "ClusterRTree.h"
class Graph
{
public:
//        double INF;
    std::vector<double> calculateDistancesFrom(Node* nodeInit);
    std::vector<double> calculateDistancesFrom(Node* nodeInit,double distanceLimit);
    void changeWeightsTo(Graph* graph,int indexDistance);
    bool degreesCalculated;
    bool useGaussianBetweenness;
    bool allowLoops;
    bool strictlyDirectional;
    std::vector<Transition> transitions;
    void insertGraphIntoQTree(QTree* quadTree);
    void hierarchicalBreakOfNetwork(Graph* graph,Graph* lineGraph);
    void collapseNodesOfDegree2();
    Customize customize;
    bool pseudoGraph;
    bool bidirectional;
    bool calculateBetweenness;
    void removeNodesFromGraph(Graph* graph,std::vector<Node*> nodesToRemove);
    void generateSuperGraphFromClusters(std::vector<Graph> &clusters,Graph* originalGraph,Graph* result);
    void getGiantComponent(Graph* graph,Graph* giantComponent);
    void getConnectedComponents(Graph* graph,std::vector<Graph> &clusters);
    void generateSpatialPercolation(Graph* graph,double distanceLimit,std::vector<Graph> &clusters);
    void generateAngularPercolation(Graph* graph,double angleLimit,std::vector<Graph> &clusters,double minClusterSize,bool probabilistic);
    void generateAngularPercolation(Graph* graph,Graph* lineGraph,double angleLimit,std::vector<Graph> &clusters,double minClusterSize,bool probabilistic);
    void removeNode(Graph* graph,Node* node);
    bool avoidBacktrackingInLineGraph;
    
    double fractalDimension;
    static const int METRIC=0;
    static const int TOPOLOGICAL=1;
    static const int ANGULAR=2;
    static const int COMBINED_METRIC_ANGULAR=3;
    static const int COMBINED_METRIC_TOPOLOGICAL=4;
    static const int COMBINED_ANGULAR_TOPOLOGICAL=5;
    static const int COMBINED_SLOPE_GREENAREAS=6;
    static const int COGNITIVE=7;
    static const int SLOPE=8;
    static const int GREEN_AREAS_IMPEDANCE=9;
    static const int COMBINED_COGNITIVE_SLOPE_GREENAREAS=10;
    static const int COMBINED_METRIC_COGNITIVE=11;
    static const int TIME_DISTANCE=12;
     static const int COMBINED_COGNITIVE_GREENAREAS=13;
    static const int COMBINED_ANGULAR_GREENAREAS=14;
    static const int COMBINED_ANGULAR_COGNITIVE=15;
    static const int COMBINED_TIMEDISTANCE_COGNITIVE=16;
    static const int INFORMATIONAL=17;
    static const int POTENTIAL_FIELD=18;
        static const int BETWEENNESS_WEIGHT=19;
    static const int COMBINED_SLOPE_ANGULAR=20;
    
    
    void calculationCentralities(Graph* graph,double radius,long startNode,long endNode,int threadNumber,int indexDistanceInOtherDistancesCutoff,int indexDistanceInOtherDistancesCalculation);
    void removeNodesFromGraph(Graph* graph,Graph& newGraph,double percentageOfNodesToRemove);
    void assignColorsFromClusters(Graph* graph,std::vector<Graph> &clusters);
    void calculateClustersFromColors(Graph* graph,std::vector<Graph> &clusters);
    void colorInvertedKReachableGraph(Graph* originalGraph,Graph* inverseOfKReachableGraph);
    void generateKReachableGraph(Graph* kReachableGraph, double distance, int indexDistance);
//    void recalculateKReachableGraph(Graph* originalKReachableGraph,Graph* kReachableGraph, double distance, int indexDistance);
    void generateInverseOfKReachableGraph(Graph* inverseOfKReachableGraph, double distance, int indexDistance);
    void calculateColorsWithMEMB(Graph* graph,double distance,int indexDistance);
    void calculateColorsWithMEMB_approximation(Graph* graph,double distance,int indexDistance);
    double calculateModularityFromColors(Graph* graph,std::vector<Graph> &clusters,long type);
    double calculateLocalClustering(Graph* graph,Node* node);
    double calculateAveragedLocalClustering(Graph* graph);
    double calculateFractalDimension(std::vector<Point2d> &results);
    void generateRandomGraphFromRewiring(Graph* originalGraph,Graph* randomGraph,double p);
    
    long id;
    Graph();
    virtual ~Graph();
    Graph(const Graph& other);
     void toParallelizeCalculatingDiskstraToSetOfDestinations(Graph* graph,std::vector<Node*> uniqueNodes,std::vector<Transition> originDestinationPairs,std::vector<int> setOfDistancesToCalculate,bool calculateCentralitiesSimultaneously);
     void toParallelizeCalculatingAStar(Graph* graph,std::vector<Transition> originDestinationPairs,long startNode,long endNode,int typeOfDistance,double (*function)(Node*,Node*));
    void insertTopologicalWeights();
    
    void pushNewDistance(int indexDistance);
    void pushNewDistance(Node* node);
    void resetGraph();
    void resizeInitialParametersToNumDistances();
    void setTypeOfMainDistanceAndInsertIntoDistances(int distanceType);
    void setTypeOfMainDistance(int distanceType,int indexOfDistanceWhenSeveralDistancesOfSameType);
    std::vector<int> getIndexesOfDistanceType(int distanceType);
    std::unordered_map<int,std::vector<int>> indexOfDistancesByDistanceType;
    std::vector<Node> nodes;
    void calculateDijkstraAllToAll(Graph* graph,std::vector<int> setOfDistancesToCalculate,long startNode,long endNode,double cutoffRadius, bool calculateMainDistance,bool calculateOtherDistances,bool calculateCentralities, bool calculateGlobalProperties,bool calculateDiffussion,std::vector<Node*> setOfDestinations);
//        void parallelize(...);
//		int currentIndexDistance;
    void calculateDiameter(int typeOfDistance,bool parallel,bool calculateCentralitiesSimultaneously, bool precise,std::vector<Node*> &externalNodes,std::vector<Transition> &originDestinationPairs, bool withHeuristic,double (*function)(Node*,Node*));
    void calculateDiameterUsingMainDistance(bool precise,std::vector<Node*> &externalNodes,std::vector<Transition> &originDestinationPairs);
    int indexOfMainDistanceInOtherDistances;
    Node& addNode();
    void addBidirectionalTransition(Node* a, Node* b,double weight, std::vector<double> otherWeights);
    void addBidirectionalTransition(long aIndex, long bIndex,double weight,std::vector<double> otherWeights);
    void addDirectedTransition(Node* a, Node* b,double weight, std::vector<double> otherWeights);
    void addDirectedTransition(Transition &trans);
    void addDirectedTransition(long aIndex, long bIndex,double weight,std::vector<double> otherWeights);
   
//    void calculateShortestPaths(Node* nodoInit,double distanceLimit);
    
//    void prepareGeneratedRoundTrips(Node* &nodeInit,double distanceLimit,std::vector<int> &setOfDistancesToCalculate);
    void calculateShortestPathsSpeed(Node* &nodoInit,double distanceLimit,std::vector<int> &setOfDistancesToCalculate);
    void calculateShortestPathsSpeedEuclideanCutoff(QTree* quadTree,Node* &nodoInit,double distanceLimit,std::vector<int> &setOfDistancesToCalculate);
    void calculateShortestPathsSpeedToSetOfDestinations(Node* &nodoInit,std::vector<Node*> setOfDestinations,double distanceLimit,std::vector<int> &setOfDistancesToCalculate);
    void calculateShortestPathsSpeedNoCutoff(Node* &nodoInit,std::vector<int> &setOfDistancesToCalculate);
    void calculateShortestPathsSpeedNoCutoffToSetOfDestinations(Node* &nodoInit,std::vector<Node*> setOfDestinations,std::vector<int> &setOfDistancesToCalculate);
    void calculateDiffusionAlgorithm(int indexDistance,long startNode,long endNode);
//        double alpha;
    bool calculateOtherDistances;
    bool calculateMainDistance;
    std::vector<double> betweenness;
    std::vector<double> closeness;
    std::vector<double> eccentricity;
    std::vector<std::vector<double> > betweennessMeasures;
    std::vector<std::vector<double> > closenessMeasures;
    std::vector<double> nodeCount;
    std::vector<double> TSL;
//    double totalSegmentLengthOfGraph;
    int numberDistances;
    void copyGraph(const Graph* graphOrigin,Graph* graphDestination,bool substitute);
//    double diameterWeighted;
//    double diameterTopological;
//    double averageWeightedDistance;
//    double averageTopologicalDistance;
//    double topologicalLengthOfMetricDiameter;
//    double weightedLengthOfTopologicalDiameter;
//    double numberNodes;
    std::vector<double> diameters;
    std::vector<double> totalLengths;
    std::vector<double> averageLengths;
    static double metricHeuristic(Node* currentNode,Node* nodeDestination);

    std::vector<double> metricLengths;
    void prepareForCentralitiesCalculation();
    void printNodes();
    bool calculateCentralities;
    bool calculateGlobalProperties;
    bool calculateTSL;
    bool calculateDiffussion;
    void calculateCutoffSpeed(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff);
    void generateNetworkPercolation(double distanceLimit,std::vector<Graph> &clusters,bool saveResultClusters,bool returnClusters,std::string nameOfFolderForFiles,long minClusterSize,bool probabilistic);
    void generateFuzzyNetworkPercolation(double multiplier,double exponent,std::vector<Graph> &clusters) ;
    void getInducedSubgraph(Graph* subgraph,std::vector<Node*> &listNodes);
    void getInducedSubgraphIncludingExternalTransitions(Graph* subgraph,std::vector<Node*> &listNodes);
    void getInducedSubgraph(Graph* subgraph,std::vector<Transition*> &transitions);
    void getRTreeInducedSubgraphAndReturnFrontierTransitions(Graph* subgraph,std::vector<Node*> &listNodes,std::vector<Transition> &frontierTransitions);
//    void removeNodeAndTransitions(long idNode);
    void AStar(Node* a,Node* b,std::vector<Node*> &visitedNodes,double (*function)(Node*,Node*));
    double AStar(Node* a,Node* b,double (*function)(Node*,Node*));
    std::vector<double> AStarOtherWeights(Node* a,Node* b,std::vector<int> setOfDistancesToCalculate,double (*function)(Node*,Node*));
    void calculateDijkstraSpeed(Node* &nodoInit,double distanceLimit,std::vector<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra);
    void calculateDijkstraSpeedToSetOfNodes(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra,std::vector<Node*> setOfNodes) ;
    void calculateDijkstraSpeedOtherDistancesToSetOfNodes(Node* &nodeInit,double distanceLimit,std::vector<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra,std::vector<Node*> setOfNodes,int indexDistance,bool followCutoff) ;
    static bool compareByDistanceAndHeuristic(Node* &a,Node* &b);
    static bool compareByDistance(Node* &a,Node* &b);
    static bool compareByOtherDistances(Node* &a,Node* &b,int indexDistance);
    static bool compareByWeight(Transition* &a,Transition* &b);
//        int indexDistanceForCutoff;
    void transformToBidirectional();
//    double totalTopologicalSize=0;
//    double totalMetricLength=0;
    void createLineGraph(Graph* graphOrigin, Graph* lineGraph);
    void createInformationalLineGraph(Graph* graphOrigin, Graph* lineGraph);
     void createLineGraphMelbourne(Graph* graphOrigin, Graph* lineGraph);
    void calculateAllShortestPathsToANodeUsingModificationDijkstra(Node* &nodeInit,Node* nodeDestination,Heap<Node*> &nodesToCheckDijkstra);
    void calculateKShellAlgorithm(Graph* graph);
    
    static signed long long getOriginalId( Node* &a);
    static double getMinDistance( Node* &a);
    static double getDegreeOut(Node* &a);
    static long degreeOut_MEMB(Node* node);
    static double getDegreeIn(Node* &a);
    static double getDegree(Node* &a);
    static double getMinOtherDistances( Node* &a,int indexDistance);
      void orderClustersByMass(std::vector<Graph>& clusters);
    
    
    static double calculateSquaredGyrationRadius(Graph* graph);
    static double calculateSquaredGyrationRadiusInGraphSpace(Graph* subGraph,Graph* fullGraph,QTree* quadTree);
    
    static Point2d calculateCentroid(std::vector<Node> &nodes);
    
    static double calculateTotalDistance(Graph* graph,Node* nodeInit);
    
        static std::vector<Transition> getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(Graph* graph);
    
    static void getRegionOfATransition(Graph* G,Transition* trans,std::vector<long> &idNodes,std::vector<long> &idTransitions,std::vector<bool> &invertedTransitions,bool inverted,bool &correctResult);
    static void constructDual(Graph* G,Graph* dual);
    static void correctGeometryOfDual(Graph* G,Graph* dual,Graph* result,std::vector<long> &correspondanceID_originalGraph,std::vector<long> &correspondanceID_result);
    static void removeExternalNodeDual(Graph* G,Graph* dual,Graph* result,std::vector<long> &correspondanceID_originalGraph,std::vector<long> &correspondanceID_result);
    static void cleanDelaunay(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys,std::vector<std::vector<long> > &delaunay,std::vector<double> &weights,double tolerance);
    static void calculateDegrees(Graph* G);
    static std::vector<long> getNeighboursIDs(Graph* G,long nodeID);
    static std::vector<Transition*> findPathDegree2(Graph* G,long nodeID);
    static void burnGraph(Graph* G,Graph* burnedGraph);
protected:
private:
    void pushNewDistance();
     void addTransition(Transition &trans);
//    void generateKReachableGraphAux(Graph* kReachableGraph,Heap<Node*> &nodesToCheckDijkstra,std::vector<Node*> &nodesCutoff, std::vector<Node*> &nodesAtDistanceK, double distanceLimit, int indexDistance);
    static double getDistance(Node* a);
    static double getId(Node* a);
    static bool compareByDistance(Node a,Node b);
    static bool compareByDistanceIsSmallerThan(Node* a,Node* b);
    static bool compareByNumChildren(Node* a,Node* b);
    static bool compareByDegreeOut(Node* &a,Node* &b);
    static bool compareByDegreeOutAndKShellValue(Node* &a,Node* &b);


    static bool compareByWaterLevel(Node* a,Node* b);

//        template<int index>
//        static bool compareByOtherDistance(Node* a,Node* b);
//    static bool compareByOtherDistanceAndHeuristic(Node* a,Node* b);
    bool compareById(Node a,Node b);
//        bool compareById(Transition* a,Transition* b);
//    void calculateDijkstra(Node* &nodoInit,double distanceLimit,BST<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra);
//        void calculateDijkstraSpeed(Node* &nodoInit,double distanceLimit,std::vector<Node*> &nodesCutoff,MinHeap<Node*> &nodesToCheckDijkstra);
//    void calculateDijkstraOtherDistance(Node* &nodeInit,BST<Node*> &nodesCutoff,Heap<Node*> &nodesToCheckDijkstra,int indexDistance);
    void calculateDijkstraOtherDistanceSpeed(Node* &nodeInit,bool useCutoff,Heap<Node*> &nodesToCheckDijkstra,int indexDistance);
//    void makeCalculations(Node* &nodoInit,BST<Node*> &nodesCutoff);
    void makeCalculationsSpeed(Node* &nodoInit,std::vector<Node*> &orderedCutoff);
     void makeCalculationsSpeed(Node* &nodoInit,std::vector<Node*> &orderedCutoff,std::vector<int> &setOfDistancesToCalculate,int indexOfDistanceInSet);
     void makeCalculationsSpeed(Node* &nodoInit,std::vector<Node*> &orderedCutoff,std::vector<int> &setOfDistancesToCalculate);
    void calculateDiffusionAlgorithmAux(int indexDistance);
    void measureGlobalProperties(std::vector<Node*>  &orderedCutoff,std::vector<int> setOfDistancesToCalculate);
    void measureGlobalProperties(std::vector<Node*>  &orderedCutoff,std::vector<int> setOfDistancesToCalculate,int indexDistanceInSet);

  
    
    


};

#endif // GRAPH_H

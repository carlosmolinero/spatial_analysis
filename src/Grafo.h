//
//  Grafo.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 27/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef hashPoint2d
#define hashPoint2d
#include "Point2d.h"

#include <limits>
namespace std{
template <>
struct hash<Point2d > {
public:
    size_t operator()(Point2d point) const throw() {

        return hash<double>()(point.x) ^ hash<double>()(point.y);

    }
};
template <>
struct hash<Number > {
public:
    size_t operator()(Number n) const throw() {

        return hash<double>()(n.value);

    }
};
}
#endif



#ifndef __SpatialAnalysis__Grafo__
#define __SpatialAnalysis__Grafo__

#include <stdio.h>
#include <vector>
#include "Nodo.h"
#include "Link.h"
#include <sstream>
#include "Functions.h"
#include "LinkPointer.h"
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include "SparseMatrix.h"
#include "InterfaceDijkstra.h"
#include <unordered_set>
#include "Geometry.h"
#include <thread>
class TextFile;
#include "TextFile.h"
#include "InterfaceIntersectionObject.h"
// #include "ShapeFile.h"





class Grafo{
public:
    static const int TYPE_POINTS=0;
    static const int TYPE_LINES=1;

    static const int PLANARITY_LINESWEEP=0;
    static const int PLANARITY_PLANESWEEP=1;
    static const int MEMORY=0;
    static const int SPEED=1;

    std::vector<Nodo*> nodes;
    std::vector<Link*> links;

    bool bidirectional;
    bool pseudoGraph;
    bool allowLoops;
    bool isPlanar;
    bool spatialGraph;
    // bool is3d;// is planar and is 3d is not the same, is 3d means that there are several nodes in the same location

    Grafo();

    Grafo(const Grafo& other);

    void copyGraph(Grafo* other);
    void copyGraphForcingPlanarity(Grafo* other);

    ~Grafo();
    void reset();
    void setAsDualGraph();
    void finishedAddingNodes();
    Nodo* addNode();
//    Nodo* addNode(double x,double y);
    Nodo* addNode(Point2d location);
    Nodo* addNode(Point2d location,bool bypassCheckDuplicatedLocation);
    Nodo* addNode(Point2d location,double mass);
    Nodo* addNode(std::string identifier,long originalID,double x,double y,bool bypassCheckDuplicatedLocation);
    Nodo* addNode(double x,double y);
    Nodo* addNode(long identifier,double x,double y);
    Nodo* addNode(long identifier,double x,double y,double mass);
    Nodo* addNode(long identifier,double x,double y,bool bypassCheckDuplicatedLocation);
    Nodo* addNode(std::string identifier,double x,double y);
    Nodo* addNode(std::string identifier,double x,double y,bool bypassCheckDuplicatedLocation);
    Nodo* addNodeAndCopyProperties(Nodo* nodeToCopyFrom);
    void removeNode(long id);
    void removeNode(Nodo* node);
    void removeNodes(std::set<long> idsNodesToRemove);
    void removeNodes(std::set<Nodo*> setNodesToRemove);
    long addLink(Link &link);
    long addLink(long idA,long idB,double weight);
//    long addLink(long idA,long idB,double weight,long originalID);
    long addLink(long idA,long idB,double weight,std::string identifier);
    // long addLink(long idA,long idB,double weight,std::string identifier,long originalID);
    long addLinkAndCopyProperties(long idA,long idB,Link* linkToCopyFrom);
    void removeLink(long id);
    void removeLink(Link* link);
    void removeLinks(std::vector<Link*> linksToRemove);
    void removeLinks(std::set<long> idsLinksToRemove);
    void removeLinks(std::set<Link*> setLinksToRemove);
    void removeLink(long id,bool correctIds);
    void correctIdsLinks();

    void removeNodesDegree0();

    Link* getLink(long idA,long idB);

    long getNumberNeighborsAsBidirectional(Nodo* node);

    Nodo* getNodeByLocation(Point2d location);
    std::vector<Nodo*> getNodesByLocation(Point2d location);

    static long getDegree(Nodo* &a);
    long getDegreeIn(Nodo* &a);
    long getDegreeOut(Nodo* &a);

    static Nodo* commonNode(Link* l1,Link* l2);

    void copyProperties(Grafo* G);
    void copyProperties(const Grafo& G);

    static void create(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,bool directed);
    static void createPseudoGraph(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,bool directed);
    static void create(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,std::vector<double> masses,bool directed);
    static void create(Grafo* G,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,std::vector<std::string> &originalIds,int type,bool directed);
    static void create(Grafo* G,std::vector<std::vector<long> > &ncolIDs,std::vector<double> &weights,std::vector<long> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed);
    static void create(Grafo* G,std::vector<std::vector<long> > &ncolIDs,std::vector<double> &weights,std::vector<std::string> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed);
//    static void create(Grafo* G,std::vector<std::vector<std::string> > &ncolOriginalIds,std::vector<double> &weights,std::vector<std::string> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed);
//    static void create(Grafo* G,std::vector<std::string> &idLinks,std::vector<std::vector<std::string> > &ncolOriginalIds,std::vector<double> &weights,std::vector<std::string> &idNodes,std::vector<std::vector<double> > &coordinates,bool directed);
    static void getRegionOfALink(Grafo* G,Link* link,std::vector<long> &idNodes,std::vector<long> &idLinks,std::vector<bool> &invertedLinks,bool inverted,bool &correctResult);
    static void constructDual(Grafo* G,Grafo* dual);
    static void constructLineGraph(Grafo* G,Grafo* lineGraph);

    static std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > getCoordinates(Grafo* G);
    static std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > getNCOL(Grafo* G);
    static void getNodeColorsFromComponents(Grafo* G,Grafo* subGraphSeparated,std::vector<long> &colors,std::vector<double> &sizes,long &maxColor,bool assignColorToIsolatedNodes);
    static void getLinkColorsFromNetworkPercolation(Grafo* G,double threshold,std::vector<long> &colors,std::vector<double> &sizes,long &maxColor);
    static void networkPercolation(Grafo* G,Grafo* result,double threshold);

    static void inducedSubgraphFromLinks(Grafo* G,Grafo* subgraph,std::vector<Link*> &listLinks);
    static void inducedSubgraph(Grafo* G,Grafo* subgraph,std::vector<Nodo*> &listNodes);
    static void inducedSubgraph(Grafo* G,Grafo* subgraph,std::vector<long> &idNodes);
    static void inducedSubgraph(Grafo* G,Grafo* subgraph,std::set<long> &idsNodes);
    static void inducedSubgraphFromLinks(Grafo* G,Grafo* subgraph,std::vector<long> &idsLinks);
        static void inducedSubgraphFromLinks(Grafo* G,Grafo* subgraph,std::set<long> &idsLinks);

    static void getComponents(Grafo* G,std::vector<Grafo> &components,long minSizeComponent);
    static void transformColorsLinksIntoColorsNodes(Grafo* G,std::vector<long> &colorsLinks,std::vector<long> &colorsNodes);
    static void transformValuesLinksIntoValuesNodes(Grafo* G,std::vector<double> &valuesLinks,std::vector<double> &valuesNodes);
    static void transformColorsNodesIntoColorsLinks(Grafo* G,std::vector<long> &colorsNodes,std::vector<long> &colorsLinks);
    static void getComponentsFromColorsOfNodes(Grafo* G,std::vector<Grafo> &components,long minSizeComponent,std::vector<long> &colors,std::vector<double> &sizes);
    static void getComponentsFromColorsOfLinks(Grafo* G,std::vector<Grafo> &components,long minSizeComponent,std::vector<long> &colors,std::vector<double> &sizes);

//    static void cleanDelaunay(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys,std::vector<std::vector<long> > &delaunay,std::vector<double> &weights,double tolerance);
    static void forcePlanarityPlaneSweep(Grafo* G,int MEMORYorSPEED,std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > &pairsOldIdNewIds,bool keepTrackChanges);
    static void intersectAGraphWithABoundary(Grafo* G,Grafo* boundary);
    static InterfaceIntersectionObject intersectAGraphWithAnother(Grafo* G,Grafo* G2);
    static void forcePlanaritylineSweep(Grafo* G,std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > &pairsOldIdNewIds,bool keepTrackChanges);

    static void getLinkToWhichPointsBelongs(Grafo* G,std::vector<double>& xs,std::vector<double>& ys,std::vector<long>& idClosestLines);

    static void addLinksFollowingIntersections(Grafo* G,std::vector<std::vector<long> > &idsIntersected,std::vector<Point2d> &intersections,std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > &pairsOldIdNewIds,bool keepTrackChanges);

    static void removeSuperfluousNodes(Grafo* G,Grafo* result,std::vector<std::pair<std::vector<long>,long> > &pairsOldNew,double maxAngle,bool keepTrackChanges);
    static void removeNonStructuralNodes(Grafo* G,Grafo* result,std::vector<std::pair<std::vector<long>,long> > &pairsOldNew,bool keepTrackChanges);
    static void cleanDuplicatedLinks(Grafo* G,double tolerance,std::vector<long> &linksRemoved,bool keepTrackChanges);

//    static void getSubgraphsFromColors(Grafo* G,std::vector<Grafo> &subGraphs,std::vector<long> colors,std::vector<long> sizes,long minSizeComponent);

    static void getLargestComponent(Grafo* G,Grafo* LG);

//    static void calculateShortestPaths(Grafo* G,std::vector<InterfaceDijkstra> &result,double distanceLimit);
    static void startCalculatingShortestPaths(Grafo* G,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff);
    static void finishCalculatingShortestPaths(Grafo* G,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff);
    static void startMeasuringAroundACircle(Grafo* G,std::vector<bool>& inCutoff);
    static void finishMeasuringAroundACircle(Grafo* G,std::vector<bool>& inCutoff);
    // static void addLabelsLevelsToLinks(Grafo* G,std::vector<long>& labels);
//        static void calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result);
        static void calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result,double distanceLimit,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff);
    static void calculateDijkstra(Grafo* G,std::vector<double> &weights,Nodo* &nodeInit,InterfaceDijkstra &result,double distanceLimit,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff);
    static void calculateAStar_angleBased(Grafo* G,Nodo* &nodeInit,Nodo* nodeDestination,double angleAllowed,InterfaceDijkstra &result,double distanceLimit,std::vector<Number*>& numbersRepresentingNodes,std::vector<bool>& inDijkstra,std::vector<bool>& inCutoff);
    static void takeMeasuresWithinACircle(Grafo* G,Nodo* nodeInit,InterfaceDijkstra &result,double radius,std::vector<bool>& inCutoff);
    static void calculateBetweenness(Grafo* G,double distanceLimit,std::vector<double> &betweenness);
    static void calculateEdgeBetweenness(Grafo* G,double distanceLimit,std::vector<double> &betweenness);
//        static void calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result,std::vector<Nodo*> &subsetNodes);
//        static void calculateDijkstra(Grafo* G,Nodo* &nodeInit,InterfaceDijkstra &result,double distanceLimit,std::vector<double> &weightsCutoff);

//    static void calculateCloseness(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &closeness);

static void calculateCloseness(Grafo* G,double distanceLimit,std::vector<double> &closeness);
static void calculateTotalDistancesFromEachNode(Grafo* G,double distanceLimit,std::vector<double> &distances);

static void calculateEfficiency(Grafo* G,double distanceLimit,double &efficiency);
    static void addLayerOfLinks(Grafo* G,Grafo* layer,double approximation);
    static double calculateLocalClusteringCoefficient(Grafo* G,Nodo* node);
    static void burnGraph(Grafo* G,Grafo* burnedGraph);
    static void burnGraph(Grafo* G);
    static void breakAcuteAnglesNodesDegree2(Grafo* G,double maxAngleAccepted);
    static void createSuperGraphFromClustersFromColorsLinks(Grafo* originalGraph,Grafo* result,std::vector<long> &colorsLinks,bool useOriginalDistances);
    static void createSuperGraphFromClustersFromColorsNodes(Grafo* originalGraph,Grafo* result,std::vector<long> &colorsNodes,bool useOriginalDistances);
    static void removeTemporaryLinks(Grafo* G);
    static void removeTemporaryNodes(Grafo* G);
    static void checkIfLoops(Grafo* G);
    long sizeOfTempLinks();
     void setNodeAsTemp(Nodo* node);
     void setLinkAsTemp(Link* link);
     static std::tuple<std::vector<double>, std::vector<double> > getPointsEvenBreaks(Grafo* G,double breaksEach);
     static void getNormalisedGraphEvenBreaks(Grafo* G,Grafo* result,double breaksEach);
     static void continuityAnglesAndLengthAndLoop(Grafo* G, double maxDistance,std::vector<bool>& idLinksThatAreContinuousAndLoop);
     static void calculateEdgeBetweenness_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &betweenness);

private:
    long maxIdLinks;
    long maxIdNodes;
    std::unordered_map<Point2d,Nodo*> nodesByLocation;
    std::unordered_map<Point2d,std::vector<Nodo*> > severalNodesByLocation;
//    std::vector<bool> linksInCutoff;
//    std::string getStringOfLocation(Point2d location);
    void setNodeByLocation(Point2d location,Nodo* node);
    bool acceptSeveralNodesByLocation;
//    bool addingNodesStatus;
    std::set<Link*> temporaryLinks;
    std::set<Nodo*> temporaryNodes;
    static void calculateDistances_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &distances);
        // static void calculateCloseness_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &closeness);
        static void calculateBetweenness_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &betweenness);
        static void calculateBetweenness_aux(Grafo* G,long startNode,long endNode,double distanceLimit,std::vector<double> &betweenness);
        static void calculateEdgeBetweenness_singleNode(Grafo* G,InterfaceDijkstra &minDistances,std::vector<double> &betweenness);

        static void calculateEfficiency_aux(Grafo* G,long startNode,long endNode,double distanceLimit,double &efficiency);


};

#endif /* defined(__SpatialAnalysis__Grafo__) */

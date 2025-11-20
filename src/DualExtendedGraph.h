//
//  DualExtendedGraph.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 28/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__DualExtendedGraph__
#define __SpatialAnalysis__DualExtendedGraph__

#include <stdio.h>
#include "Grafo.h"
#include "Data.h"
#include "CriticalExponentsPercolation.h"
#include "FractalDimension.h"
#include "TextFile.h"
#include "GeometryGraph.h"
#include "Point3d.h"
class DualExtendedGraph{
public:
    static const int METRIC=0;
    static const int ANGULAR=1;


    DualExtendedGraph();
   ~DualExtendedGraph();

    void reset();
//    static void addPrimal(DualExtendedGraph* deg,Grafo* G);
    static void addPrimal(DualExtendedGraph* deg,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,bool directed);
    static void addPrimal(DualExtendedGraph* deg,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >  &coordinates,std::vector<double> masses,bool directed);
    static void addPrimal(DualExtendedGraph* deg,std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  &ncol,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > &coordinates,std::vector<std::string> &originalIds,int type,bool directed);
    static void addPrimal(DualExtendedGraph* deg,Grafo* G);
    static void addAnotherGraph(DualExtendedGraph* deg,Grafo* otherGraph,bool finishAddingGraphs);
    static void addAnotherDEG(DualExtendedGraph* deg,DualExtendedGraph* otherDEG,bool finishAddingGraphs);
    static void simplify(DualExtendedGraph* deg);
    static void simplify(DualExtendedGraph* deg,double angle);
    static void useOnlyLargestConnectedComponent(DualExtendedGraph* deg);
    static void buildStructuralGraph(DualExtendedGraph* deg);
    // static void buildStructuralGraph(DualExtendedGraph* deg,bool directed);

    static void buildBidirectionalGraph(DualExtendedGraph* deg);

    static void createDual(DualExtendedGraph* deg,Grafo* originalGraph,Grafo* dual);
    static void createLineGraph(DualExtendedGraph* deg);

    static void constructPlanarGraph(DualExtendedGraph* deg,int mode);


    static void forcePlanarityPrimal(DualExtendedGraph* deg,int mode);
    static void unPlanarizeUsingIntersectionPointsAndOriginalIdsOfLinks(DualExtendedGraph* deg,Grafo* intersectionPoints);
    static void intersectionContinuityNegotiationPrimal(DualExtendedGraph* deg,Nodo* node,std::vector<std::vector<long> >& idLinksPerPairs);
    static void cleanDuplicatedLinks(DualExtendedGraph* deg,double angularDistanceToConsiderEqual);

    static void metricPercolation(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes);
        static void metricPercolation_sizeUsingMassesNodes(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes);

    static void angularPercolation(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes);
    static void dualPercolation(DualExtendedGraph* deg,double threshold,std::vector<long> &colors,std::vector<double> &sizes);
    static void setDistanceDual_HuMoments(DualExtendedGraph* deg);
    static void setDistanceDual_difArea(DualExtendedGraph* deg);
    static void setDistanceDual_avArea(DualExtendedGraph* deg);
    static void setDistanceDual_minArea(DualExtendedGraph* deg);
    static void setDistanceDual_avNeighborhoodArea(DualExtendedGraph* deg);
    static void setDistanceDual_difNeighborhoodArea(DualExtendedGraph* deg);
    static void setDistancePrimal_minLengthNeighbours(DualExtendedGraph* deg);

    static void setPrimalAsPlanar(DualExtendedGraph* deg);
    static void setPrimalAsSimplified(DualExtendedGraph* deg);

    static void setPrimalAsStructuralGraph(DualExtendedGraph* deg);
    static void unSetPrimalAsStructuralGraph(DualExtendedGraph* deg);
    static bool isPrimalStructural(DualExtendedGraph* deg);
    Grafo* getStructuralGraph();
    Grafo* getPrimalGraph();
    Grafo* getDualGraph();
    Grafo* getLineGraph();
    Grafo* getPlanarGraph();
    Grafo* getDualPlanarGraph();
    Data* getData();
    static void setAngularWeightsLineGraph(DualExtendedGraph* deg);
    static void setMetricWeightsLineGraph(DualExtendedGraph* deg);
    static std::vector<double> getAngularWeightsLineGraph(DualExtendedGraph* deg);
    // static void setMetricWeightsLineGraph(DualExtendedGraph* deg);
    static void setWeightsLineGraphFromData(DualExtendedGraph* deg,std::string weightType);
    static void calculateCompleteMetricPercolation(DualExtendedGraph* deg,std::string folderNameOut);
    static void calculateCompleteWeightStructuralGraphPercolation(DualExtendedGraph* deg,std::string folderNameOut);
    static void calculateCompleteAngularPercolation(DualExtendedGraph* deg,double definition,CriticalExponentsPercolation &cep,bool calculatePhaseTransition);
    static std::pair<double,double> detectPhaseTransitionAngularPercolation(DualExtendedGraph* deg,double definition);
    static void measureCriticalExponentsAngularPercolation(DualExtendedGraph* deg,CriticalExponentsPercolation &cep);
    static double getEntropyFromAngularPercolation(DualExtendedGraph* deg,double angle);
    static double getEntropyFromMetricPercolation(DualExtendedGraph* deg,double threshold);
    static double getEntropyFromDualPercolation(DualExtendedGraph* deg,double threshold);
    static void calculateHierarchicalIndexAngular(DualExtendedGraph* deg,double definition,std::vector<double> &HI);
    static void calculateHierarchicalIndexAngularUsingMetricweightsAsMass(DualExtendedGraph* deg,double definition,std::vector<double> &HI);
    static void calculateHierarchicalIndexMetric(DualExtendedGraph* deg,double definition,std::vector<double> &HI);
        static void calculateHierarchicalIndexMetricUsingMassesNodes(DualExtendedGraph* deg,double definition,std::vector<double> &HI);
        static void calculateHierarchicalIndexMetricUsingMassesNodes(DualExtendedGraph* deg,double definition,std::vector<double> &HI,std::vector<double>& thresholdsToUse);
    static void calculateHierarchicalIndexMetricUsingMassesNodesAsMeasureOfStructure(DualExtendedGraph* deg,double definition,std::vector<double> &strengthConnection);
    static void calculateHierarchicalIndexMetric_basedInDensityOfNodesThatRepresentAGrid_UsingMassesNodes(DualExtendedGraph* deg,double definition,std::vector<double> &HI,double widthSquareGrid);
    static void calculateHierarchicalIndexDual(DualExtendedGraph* deg,double definition,std::vector<double> &HI);
    static std::vector<double> getSpeedsForStructuralGraph(DualExtendedGraph* deg,std::vector<double> &HIangular,std::vector<double> &HImetric);
    // static std::vector<double> getHImetricInPrimal(DualExtendedGraph* deg,std::vector<double> &HImetricStructural);
    static std::vector<double> calculateThresholdFromEntropyDistribution(std::vector<double> initialPs,std::vector<double> entropies);
    bool keepTrackDifferencesBetweenPrimalAndStructural;
    static std::vector<double> getThresholdsForMetricPercolation(DualExtendedGraph* deg,double definition);
    static std::tuple<std::vector<double>,std::vector<double> > getThresholdsAndEntropyForMetricPercolation(DualExtendedGraph* deg,double definition);
        static std::tuple<std::vector<double>,std::vector<double> > getThresholdsAndEntropyForMetricPercolation_UsingMassNodes(DualExtendedGraph* deg,double definition);

    static void createHierarchicalTreeMetric(DualExtendedGraph* deg,Grafo* tree,std::vector<double>& thresholds,std::vector<long>& colorsNodesStructuralGraph,std::vector<double>& massesTreeNodes,std::vector<long>& depths,double minMassCluster);
    static void removeLoopsOfDualInPrimal(DualExtendedGraph* deg);
    static std::vector<double> calculateCoefficientsAngularDeviationPerMetricLengthForAllRegions(DualExtendedGraph* deg);
    static void detectRoundabouts(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel);
    static void detectRoundabouts(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,double minAngle, double maxAngle, double maxDistance,bool useSegmentDistance,double minCoef,double maxCoef);
    static void joinTwoAdjacentNodesOfTheDual(DualExtendedGraph* deg,Link* link);
    static void assignRoundaboutsToMainDualGraph(DualExtendedGraph* deg,std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,std::vector<long>& idsRoundaboutsAtNodesDualLevel);
    static void detectEntryPointsToRoundabouts(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel,std::vector<long>& idsEntriesToRoundaboutsPrimalLevel);
    static void detectEntryPointsToRoundabouts(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel);
    static void hyperConnectRoundabouts(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel);
    static void connectRoundaboutToItsCenter(DualExtendedGraph* deg, std::vector<long>& idsRoundaboutsAtNodesPrimalLevel);
    static std::vector<long> getIdsOfLinksOfPrimalNotTemp(DualExtendedGraph* deg);
    static void calculateAngularBetweenness(DualExtendedGraph* deg,double angularLimit,std::vector<double>& betweenness);
    static void calculateMetricEdgeBetweenness(DualExtendedGraph* deg,double distanceLimit,std::vector<double>& betweenness);

   void softReset();
static void removeTempObjects(DualExtendedGraph* deg);

static void collapseRoundabouts(DualExtendedGraph* deg);
static void setRoundaboutsRemoved(DualExtendedGraph* deg,bool roundaboutsRemoved);
static void collapseDoubleLanes(DualExtendedGraph* deg,Grafo* result);
// static void collapseDoubleLanesB(DualExtendedGraph* deg,Grafo* result);
static void collapseNodesDual(DualExtendedGraph* deg, std::set<long>& idNodesToCollapse);
static std::vector<double> getPerimeterRegionsDual(DualExtendedGraph* deg);
    static void diffuseFromSegmentsToSegments_angular(DualExtendedGraph* deg, std::vector<double>& valuesEdges,std::vector<double>& result,double d0,double cutoffValue);
        static void diffuseFromSegmentsToSegments_metric(DualExtendedGraph* deg, std::vector<double>& valuesEdges,std::vector<double>& result,double d0,double cutoffValue);
    static void calculateAreasClustersInParallel(DualExtendedGraph* deg,double percolationThreshold,std::vector<double>& areas,int numThreads);
    static void calculateFractalDimensionClustersInParallel(DualExtendedGraph* deg,double percolationThreshold,std::vector<double>& fd,int numThreads);

private:
//    std::vector<long> idsLinksStructuralGraphOrderedByIdsLinksPrimalGraph;
    std::vector<std::vector<long> > idsLinksPrimalByIdsLinksStructural;
    bool isSimplified;
    bool structuralGraphConstructed;
    bool primalIsStructuralGraph;
    bool primalIsBidirectional;
    bool lineGraphConstructed;
    bool dualGraphConstructed;
    bool dualPlanarGraphConstructed;
    int currentWeightsInLineGraph;
    bool isPlanarGraphConstructed;
    bool roundaboutsRemoved;



    Grafo primalGraph;
    Grafo primalPlanarGraph;
    Grafo structuralGraph;
    Grafo primalBidirectionalGraph;
    Grafo dualGraph;
    Grafo dualPlanarGraph;
    Grafo lineGraph;
    Data dataLinksPrimal;
};

#endif /* defined(__SpatialAnalysis__DualExtendedGraph__) */

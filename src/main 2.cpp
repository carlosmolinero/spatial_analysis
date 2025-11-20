

#include"ArchivoTexto.h"
#include<vector>
#include"Graph.h"
//#include "omp.h"
#include <thread>
#include <sstream>
#include<math.h>
#include "RTree.h"
#include <sys/timeb.h>
#include <map>
#include "Timer.h"
#include "Configuration.h"
#include "Singleton.h"
#include <queue>
#include "LinearRegression.h"
#include "Customize.h"
#include "Heap.h"
//========================================================================
Timer timer;
std::vector<std::vector<double> > combinedDistances;
std::vector<std::vector<double> > combinedDistancesToCalculate;
std::vector<int> indexDistancesToCalculate;

static const int CALCULATE_DIJKSTRA_PARALLEL_ALLTOALL=0;
static const int CALCULATE_QTREE=1;
static const int CALCULATE_ASTAR_METRIC_AND_DIJKSTRA_TOPO=2;
static const int CALCULATE_DIJKSTRA_STOPCRITERIA=3;
static const int CALCULATE_ASTAR=4;
static const int CALCULATE_DIKSTRA_FROMUNIQUENODES=5;

static const int CALCULATE_NETWORK_PERCOLATION=6;

static const int CALCULATE_FUZZY_NETWORK_PERCOLATION=7;
static const int CALCULATE_DIAMETER=8;
static const int REMOVE_NODES_FROM_GRAPH_EXTRACT_CLUSTERS_AND_CALCULATE_DIAMETER=9;
static const int CALCULATE_FRACTAL_DIMENSION=10;
static const int CALCULATE_DIAMETER_TEST=11;

static const int CALCULATE_CENTRALITIES=12;
static const int CALCULATE_ANGULAR_NETWORK_PERCOLATION=13;
static const int CALCULATE_K_SHELL_VALUES=14;
static const int CALCULATE_CLOSENESS_THROUGH_SHORTESTINFORMATIONAL_ROUTE=15;//review algorithm//delete
static const int ANALYZE_ANGULARPERCOLATION=16;
static const int SIMPLIFY_GRAPH=17;
static const int GENERATE_TREE_FROM_CLUSTERS=18;
static const int REMOVE_NODES_FROM_GRAPH_EXTRACT_CLUSTERS_USING_SPATIAL_PERCOLATION=19;//not finished
static const int GENERATE_TREE_FROM_CLUSTERS_METHOD_B=20;
static const int GENERATE_TREE_FROM_CLUSTERS_METHOD_C=21;
static const int CALCULATE_CLOSENESS_THROUGH_SHORTESTINFORMATIONAL_ROUTE_B=22;

static const int APROX=0;
static const int PRECISE=1;

int modeCalculation=CALCULATE_CENTRALITIES;
int typeOfCalculation=APROX;
//time_t timerInit;
//time_t timerEnd;
static const int TEST=-1;
static const int IMPORT_PRIMALGRAPH_SEVERAL=0;
static const int IMPORT_PRIMALGRAPH_SINGLE=2;
static const int IMPORT_PRIMALGRAPH_CLUSTERS=3;
static const int IMPORT_LINEGRAPH=1;
static const int IMPORT_PRIMALGRAPH_AND_GENERATE_LINEGRAPH=4;
static const int IMPORT_PRIMALGRAPH_AND_INFORMATIONALGRAPH=5;

int formatFile=IMPORT_PRIMALGRAPH_AND_GENERATE_LINEGRAPH;



int getMilliCount()
{
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

int getMilliSpan(int nTimeStart)
{
    int nSpan = getMilliCount() - nTimeStart;
    if(nSpan < 0)
        nSpan += 0x100000 * 1000;
    return nSpan;
}
void setGraph(Graph* graph, int numberVertex,std::vector<double> &metricLengths)
{
    
    
    
    
    
    graph->numberDistances=(int)(combinedDistancesToCalculate.size());
    for (long i=0; i<numberVertex; i++)
    {
        graph->addNode();
        graph->metricLengths.push_back(metricLengths[i]);
    }
    //    graph.printNodes();
    graph->calculateCentralities=true;
    graph->calculateGlobalProperties=false;
    graph->calculateDiffussion=false;
    graph->calculateTSL=true;
    std::cout<<"num. distances "<<combinedDistancesToCalculate.size()<<'\n';
    
    
    
}
void resetWeights(Graph* graph,int indexAlpha,std::vector<double> &initVertex,std::vector<double> &endVertex)
{
    std::vector<double> combinedWeights;
    combinedWeights=combinedDistances[indexAlpha];
    
    for (long i=0; i<graph->nodes.size(); i++)
    {
        graph->nodes[i].transitions.clear();
    }
    for (long i=0; i<initVertex.size(); i++)
    {
        std::vector<double> otherWeights;
        otherWeights.clear();
        for (long j=0; j<combinedDistancesToCalculate.size(); j++)
        {
            otherWeights.push_back(combinedDistancesToCalculate[j][i]);
        }
        graph->addBidirectionalTransition(initVertex[i]-1,endVertex[i]-1,combinedWeights[i],otherWeights);
    }
}

void importPrimalGraph(Graph* graph, std::string nameOfFile)
{
    graph->numberDistances=0;
    graph->calculateCentralities=true;
    graph->calculateDiffussion=false;
    graph->calculateTSL=true;
    ArchivoTexto textFile;
    textFile.parseNCOLWithCoordinates(nameOfFile, graph,",",true);
    
}
void copyGraph(Graph* graphOrigin,Graph* graphDestination)
{
    graphDestination->nodes.clear();
    graphDestination->numberDistances=graphOrigin->numberDistances;
    for(long i=0; i<graphOrigin->nodes.size(); i++)
    {
        graphDestination->addNode();
    }
    for(long i=0; i<graphOrigin->nodes.size(); i++)
    {
        graphDestination->nodes[i].location=Point2d(graphOrigin->nodes[i].location.x,graphOrigin->nodes[i].location.y);
        graphDestination->nodes[i].originalID=graphOrigin->nodes[i].originalID;
        for (long j=0; j<graphOrigin->nodes[i].transitions.size(); j++)
        {
            long idA=graphOrigin->nodes[i].transitions[j]->a->id;
            long idB=graphOrigin->nodes[i].transitions[j]->b->id;
            
            //            graphDestination->nodes[idB].originalID=graphOrigin->nodes[i].transitions[j].b->originalID;
            
            //            graphDestination->nodes[idA].location=Point2d(graphOrigin->nodes[i].location.x,graphOrigin->nodes[i].location.y);
            //            std::cout<<idA<<" "<<idB<<" "<<i<<" "<<j<<'\n';
            
            graphDestination->addDirectedTransition(idA, idB, graphOrigin->nodes[i].transitions[j]->weight,graphOrigin->nodes[i].transitions[j]->otherWeights);
        }
        
    }
}

void saveFiles(Graph* graph,int indexAlpha,double metricRadius)
{
    ArchivoTexto textFile;
    std::cout<<"SAVING FILES"<<'\n';
    std::stringstream nameSS;
    nameSS<<"/Users/carlos/Documents/results/meridianDataSetUKSimplified_tryNoDegree2_indexAlpha_"<<indexAlpha<<"_radius_"<<metricRadius<<".txt";
    std::string name=nameSS.str();
    
    std::stringstream headerSS;
    if (graph->calculateCentralities)
    {
        headerSS<<"nodeCount"<<" "<<"TSL"<<" "<<"TD"<<" ";
        for (int j=0; j<combinedDistancesToCalculate.size(); j++)
        {
            headerSS<<"TD"<<j<<" ";
        }
        headerSS<<"betweenness"<<" ";
        for (int j=0; j<combinedDistancesToCalculate.size(); j++)
        {
            headerSS<<"betweenness"<<j;
            if (j<combinedDistancesToCalculate.size()-1)
            {
                headerSS<<" ";
            }
        }
    }
    if (graph->calculateDiffussion&&graph->calculateCentralities)
    {
        headerSS<<" ";
    }
    if (graph->calculateDiffussion)
    {
        headerSS<<"flow";
    }
    std::string header=headerSS.str();
    
    std::stringstream valuesSS;
    
    std::string values;
    std::vector<std::string> finalAnalysis;
    finalAnalysis.push_back(header);
    
    
    for(long i=0; i<graph->nodes.size(); i++)
    {
        valuesSS.clear();
        valuesSS.str("");
        if (graph->calculateCentralities)
        {
            valuesSS<<graph->nodeCount[i]<<" "<<graph->TSL[i]<<" "<<graph->closeness[i]<<" ";
            for (int j=0; j<combinedDistancesToCalculate.size(); j++)
            {
                valuesSS<<graph->closenessMeasures[j][i]<<" ";
            }
            valuesSS<<graph->betweenness[i]<<" ";
            for (int j=0; j<combinedDistancesToCalculate.size(); j++)
            {
                valuesSS<<graph->betweennessMeasures[j][i];
                if (j<combinedDistancesToCalculate.size()-1)
                {
                    valuesSS<<" ";
                }
            }
        }
        if (graph->calculateDiffussion&&graph->calculateCentralities)
        {
            valuesSS<<" ";
        }
        if (graph->calculateDiffussion)
        {
            valuesSS<<graph->nodes[i].waterLevel.flow;
        }
        values=valuesSS.str();
        finalAnalysis.push_back(values);
    }
    textFile.writeToFile(name,finalAnalysis,false);
}
void saveFiles(Graph* graph,std::string nameFile,int indexAlpha,double metricRadius,long vertexNumber,bool saveHeader)
{
    ArchivoTexto textFile;
    //    std::cout<<"SAVING FILES"<<'\n';
    std::vector<std::string> finalAnalysis;
    std::stringstream nameSS;
    nameSS<<"/Users/carlos/Documents/results/"<<nameFile<<"_indexAlpha_"<<indexAlpha<<"_radius_"<<metricRadius<<".txt";
    
    std::string name=nameSS.str();
    std::cout<<"saving file "<<name<<'\n';
    if (saveHeader)
    {
        std::stringstream headerSS;
        if (graph->calculateCentralities)
        {
            headerSS<<"nodeId"<<" "<<"nodeThatRepresents"<<" "<<"nodeCount"<<" "<<"TSL"<<" "<<"TD"<<" ";
            if (graph->calculateOtherDistances)
            {
                for (int j=0; j<combinedDistancesToCalculate.size(); j++)
                {
                    headerSS<<"TD"<<j<<" ";
                }
            }
            headerSS<<"betweenness";
            if (graph->calculateOtherDistances)
            {
                headerSS<<" ";
                for (int j=0; j<combinedDistancesToCalculate.size(); j++)
                {
                    headerSS<<"betweenness"<<j;
                    if (j<combinedDistancesToCalculate.size()-1)
                    {
                        headerSS<<" ";
                    }
                }
            }
        }
        if (graph->calculateDiffussion&&graph->calculateCentralities)
        {
            headerSS<<" ";
        }
        if (graph->calculateDiffussion)
        {
            headerSS<<"flow";
        }
        std::string header=headerSS.str();
        finalAnalysis.push_back(header);
    }
    std::stringstream valuesSS;
    
    std::string values;
    
    
    
    
    for(long i=0; i<graph->nodes.size(); i++)
    {
        valuesSS.clear();
        valuesSS.str("");
        if (graph->calculateCentralities)
        {
            valuesSS<<vertexNumber<<" "<<graph->nodes[i].nodeThatRepresents->id<<" "<<graph->nodeCount[i]<<" "<<graph->TSL[i]<<" "<<graph->closeness[i]<<" ";
            if (graph->calculateOtherDistances)
            {
                for (int j=0; j<combinedDistancesToCalculate.size(); j++)
                {
                    valuesSS<<graph->closenessMeasures[j][i]<<" ";
                }
            }
            valuesSS<<graph->betweenness[i];
            if (graph->calculateOtherDistances)
            {
                valuesSS<<" ";
                for (int j=0; j<combinedDistancesToCalculate.size(); j++)
                {
                    valuesSS<<graph->betweennessMeasures[j][i];
                    if (j<combinedDistancesToCalculate.size()-1)
                    {
                        valuesSS<<" ";
                    }
                }
            }
        }
        if (graph->calculateDiffussion&&graph->calculateCentralities)
        {
            valuesSS<<" ";
        }
        if (graph->calculateDiffussion)
        {
            valuesSS<<graph->nodes[i].waterLevel.flow;
        }
        values=valuesSS.str();
        finalAnalysis.push_back(values);
    }
    textFile.writeToFile(name,finalAnalysis,true);
}

void saveFilesCluster(Graph* graph,std::string nameFile,int indexAlpha,double metricRadius,long vertexNumber,bool saveHeader,long numCluster)
{
    ArchivoTexto textFile;
    //    std::cout<<"SAVING FILES"<<'\n';
    std::vector<std::string> finalAnalysis;
    std::stringstream nameSS;
    nameSS<<"/Users/carlos/Documents/apps/results/"<<nameFile<<"_indexAlpha_"<<indexAlpha<<"_radius_"<<metricRadius<<".txt";
    std::string name=nameSS.str();
    if (saveHeader)
    {
        std::stringstream headerSS;
        //        if (graph->calculateCentralities){
        headerSS<<"cluster"<<" "<<"nodeThatRepresents";
        //            <<" "<<"nodeCount"<<" "<<"TSL"<<" "<<"TD"<<" ";
        //            if (graph->calculateOtherDistances){
        //                for (int j=0;j<combinedDistancesToCalculate.size();j++){
        //                    headerSS<<"TD"<<j<<" ";
        //                }
        //            }
        //            headerSS<<"betweenness";
        //            if (graph->calculateOtherDistances){
        //                headerSS<<" ";
        //                for (int j=0;j<combinedDistancesToCalculate.size();j++){
        //                    headerSS<<"betweenness"<<j;
        //                    if (j<combinedDistancesToCalculate.size()-1){
        //                        headerSS<<" ";
        //                    }
        //                }
        //            }
        //        }
        //        if (graph->calculateDiffussion&&graph->calculateCentralities){
        //            headerSS<<" ";
        //        }
        //        if (graph->calculateDiffussion){
        //            headerSS<<"flow";
        //        }
        std::string header=headerSS.str();
        finalAnalysis.push_back(header);
    }
    std::stringstream valuesSS;
    
    std::string values;
    
    
    
    
    for(long i=0; i<graph->nodes.size(); i++)
    {
        valuesSS.clear();
        valuesSS.str("");
        //        if (graph->calculateCentralities){
        valuesSS<<numCluster<<" "<<graph->nodes[i].nodeThatRepresents->id;
        //            <<" "<<graph->nodeCount[i]<<" "<<graph->TSL[i]<<" "<<graph->closeness[i]<<" ";
        //            if (graph->calculateOtherDistances){
        //                for (int j=0;j<combinedDistancesToCalculate.size();j++){
        //                    valuesSS<<graph->closenessMeasures[j][i]<<" ";
        //                }
        //            }
        //            valuesSS<<graph->betweenness[i];
        //            if (graph->calculateOtherDistances){
        //                valuesSS<<" ";
        //                for (int j=0;j<combinedDistancesToCalculate.size();j++){
        //                    valuesSS<<graph->betweennessMeasures[j][i];
        //                    if (j<combinedDistancesToCalculate.size()-1){
        //                        valuesSS<<" ";
        //                    }
        //                }
        //            }
        //        }
        //        if (graph->calculateDiffussion&&graph->calculateCentralities){
        //            valuesSS<<" ";
        //        }
        //        if (graph->calculateDiffussion){
        //            valuesSS<<graph->nodes[i].waterLevel.flow;
        //        }
        values=valuesSS.str();
        finalAnalysis.push_back(values);
    }
    textFile.writeToFile(name,finalAnalysis,true);
}
void saveFilesGlobalProperties(Graph* graph,std::string nameFile,int numCluster,bool saveHeader)
{
    ArchivoTexto textFile;
    //    std::cout<<"SAVING FILES"<<'\n';
    std::vector<std::string> finalAnalysis;
    std::stringstream nameSS;
    //    nameSS<<"/Users/carlos/Documents/apps/results/"<<nameFile<<".txt";
    std::string name=nameFile;
    //    if (numCluster==0){
    //        saveHeader=true;
    //    }else{
    //        saveHeader=false;
    //    }
    if (saveHeader)
    {
        std::stringstream headerSS;
        headerSS<<"clusterID"<<" "<<"numberNodes"<<" "<<"diameterMetric"<<" "<<"averageLengthMetric"<<" "<<"diameterTopological"<<" "<<"averageTopologicalLength";
        //        if (graph->calculateCentralities){
        //
        //            if (graph->calculateOtherDistances){
        //                for (int j=0;j<combinedDistancesToCalculate.size();j++){
        //                    headerSS<<"TD"<<j<<" ";
        //                }
        //            }
        //            headerSS<<"betweenness";
        //            if (graph->calculateOtherDistances){
        //                headerSS<<" ";
        //                for (int j=0;j<combinedDistancesToCalculate.size();j++){
        //                    headerSS<<"betweenness"<<j;
        //                    if (j<combinedDistancesToCalculate.size()-1){
        //                        headerSS<<" ";
        //                    }
        //                }
        //            }
        //        }
        //        if (graph->calculateDiffussion&&graph->calculateCentralities){
        //            headerSS<<" ";
        //        }
        //        if (graph->calculateDiffussion){
        //            headerSS<<"flow";
        //        }
        std::string header=headerSS.str();
        finalAnalysis.push_back(header);
    }
    std::stringstream valuesSS;
    
    std::string values;
    valuesSS.clear();
    valuesSS.str("");
    valuesSS<<numCluster<<" "<<graph->nodes.size()<<" "<<graph->diameters[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<graph->averageLengths[graph->getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<graph->diameters[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<" "<<graph->averageLengths[graph->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
    values=valuesSS.str();
    finalAnalysis.push_back(values);
    
    
    
    textFile.writeToFile(name,finalAnalysis,true);
}








//void calculate(Graph* graph,double combinedRadius,int indexAlpha, std::vector<double> initVertex,std::vector<double> endVertex,long startNode,long endNode)
//{
//    resetWeights(graph, indexAlpha,initVertex,endVertex);
//
//
//    graph->init();
//    graph->indexOfMainDistanceInOtherDistances=-1;
//    graph->calculateMainDistance=false;
//    graph->calculateOtherDistances=true;
//    for(int i=0; i<indexDistancesToCalculate.size(); i++)
//    {
//        if (indexAlpha==indexDistancesToCalculate[i])
//        {
//            graph->indexOfMainDistanceInOtherDistances=i;
//            graph->calculateMainDistance=true;
//        }
//    }
//    std::cout<<"START"<<'\n';
//
//    if (graph->calculateCentralities)
//    {
//        for (long i=startNode; i<endNode; i++)
//        {
//            Node* nodeInit=&(graph->nodes[i]);
//            graph->calculateShortestPathsSpeed(nodeInit,combinedRadius);
//        }
//    }
//    if (graph->calculateDiffussion)
//    {
//        graph->calculateDiffusionAlgorithm(5,startNode,endNode);
//    }
//    std::cout<<"END"<<'\n';
//}

//void calculateGraphFromCluster(Graph* graph,double combinedRadius,long startNode,long endNode)
//{
////    resetWeights(graph, indexAlpha,initVertex,endVertex);
////    bool saveHeader=true;
//
//    graph->init();
//    graph->indexOfMainDistanceInOtherDistances=-1;
//    graph->calculateMainDistance=true;
//    graph->calculateOtherDistances=true;
//    graph->calculateCentralities=false;
//    graph->calculateGlobalProperties=true;
//    graph->calculateDiffussion=false;
//    graph->totalTopologicalSize=0;
//    graph->totalMetricLength=0;
//    graph->diameterWeighted=0;
////    for(int i=0;i<indexDistancesToCalculate.size();i++){
////        if (indexAlpha==indexDistancesToCalculate[i]){
////            graph->indexOfMainDistanceInOtherDistances=i;
////            graph->calculateMainDistance=true;
////        }
////    }
//    std::cout<<"START"<<'\n';
//
//    if (graph->calculateCentralities||graph->calculateGlobalProperties)
//    {
//        for (long i=startNode; i<endNode; i++)
//        {
//            Node* nodeInit=&(graph->nodes[i]);
//            graph->calculateShortestPathsSpeed(nodeInit,combinedRadius);
//        }
//        for (long i=startNode; i<endNode; i++)
//        {
////            graph->totalTopologicalSize+=graph->topologicalSize;
////            graph->totalMetricLength+=graph->nodes[i].minDistance;
//        }
//
//        graph->averageTopologicalDistance=graph->totalTopologicalSize/(double)(endNode-startNode);
//        graph->averageWeightedDistance=graph->totalMetricLength/(double)(endNode-startNode);
//    }
//    if (graph->calculateDiffussion)
//    {
//        graph->calculateDiffusionAlgorithm(5,startNode,endNode);
//    }
//    std::cout<<"END"<<'\n';
//}
void calculateSubgraphsAndCentralities(Graph* graph,double combinedRadius,int indexAlpha, std::vector<double> initVertex,std::vector<double> endVertex,long startNode,long endNode,int threadNumber)
{
    resetWeights(graph, indexAlpha,initVertex,endVertex);
    bool saveHeader=true;
    
    graph->prepareForCentralitiesCalculation();
    graph->indexOfMainDistanceInOtherDistances=-1;
    graph->calculateMainDistance=true;
    graph->calculateOtherDistances=false;
    for(int i=0; i<indexDistancesToCalculate.size(); i++)
    {
        if (indexAlpha==indexDistancesToCalculate[i])
        {
            graph->indexOfMainDistanceInOtherDistances=i;
            graph->calculateMainDistance=true;
        }
    }
    std::cout<<"START"<<'\n';
    
    //    if (graph->calculateCentralities){
    for (long i=startNode; i<endNode; i++)
    {
        std::vector<Node*> listNodes;
        Node* nodeInit=&(graph->nodes[i]);
        graph->calculateCutoffSpeed(nodeInit, combinedRadius,listNodes);
        //            Graph realSubgraph;
        //            Graph* subgraph=&realSubgraph;
        Graph* subgraph=new Graph();
        subgraph->numberDistances=(int)(combinedDistancesToCalculate.size());
        graph->getInducedSubgraph(subgraph,listNodes);
        
        //            resetWeights(&subgraph, indexAlpha,initVertex,endVertex);
        subgraph->calculateCentralities=true;
        subgraph->calculateDiffussion=false;
        subgraph->calculateTSL=true;
        
        subgraph->prepareForCentralitiesCalculation();
        subgraph->indexOfMainDistanceInOtherDistances=-1;
        subgraph->calculateMainDistance=true;
        subgraph->calculateOtherDistances=false;
        for(int j=0; j<indexDistancesToCalculate.size(); j++)
        {
            if (indexAlpha==indexDistancesToCalculate[j])
            {
                subgraph->indexOfMainDistanceInOtherDistances=j;
                subgraph->calculateMainDistance=true;
            }
        }
        if (subgraph->nodes.size()>1)
        {
            //            for(long j=0;j<subgraph->nodes.size();j++){
            int j=0;
            Node* nodeTemp=&(subgraph->nodes[j]);
            std::vector<int> setOfDistancesToCalculate=subgraph->indexOfDistancesByDistanceType[Graph::METRIC];
            subgraph->calculateShortestPathsSpeed(nodeTemp,0,setOfDistancesToCalculate);
            //                Node* nodeTemp=&(subgraph->nodes[0]);
            //                            subgraph->calculateShortestPathsSpeed(nodeTemp,combinedRadius);
            //            }
        }
        listNodes.clear();
        std::stringstream nameSS;
        nameSS<<"subgraph"<<threadNumber;
        std::string name=nameSS.str();
        
        
        saveFiles(subgraph, name, indexAlpha, combinedRadius,i,saveHeader);
        if(saveHeader)
        {
            saveHeader=false;
        }
        delete subgraph;
        //            subgraph.nodes.clear();
    }
    //    }
    std::cout<<"END"<<'\n';
}
void calculateSubgraphsAndCentralities(Graph* graph,double radius,long startNode,long endNode,int threadNumber,int indexDistanceInOtherDistancesCutoff,int indexDistanceInOtherDistancesCalculation)
{
    //    resetWeights(graph, indexAlpha,initVertex,endVertex);
    
    for(long i=0;i<graph->nodes.size();i++){
        for(long j=0;j<graph->nodes[i].transitions.size();j++){
            graph->nodes[i].transitions[j]->weight=graph->nodes[i].transitions[j]->otherWeights[indexDistanceInOtherDistancesCutoff];
        }
    }
    
    bool saveHeader=true;
    
    graph->prepareForCentralitiesCalculation();
    graph->calculateCentralities=false;
    graph->calculateDiffussion=false;
    graph->calculateGlobalProperties=false;
    graph->indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCutoff;
    graph->calculateMainDistance=true;
    graph->calculateTSL=false;
    graph->calculateOtherDistances=false;
    //    for(int i=0; i<indexDistancesToCalculate.size(); i++)
    //    {
    //        if (indexAlpha==indexDistancesToCalculate[i])
    //        {
    //            graph->indexOfMainDistanceInOtherDistances=i;
    //            graph->calculateMainDistance=true;
    //        }
    //    }
    std::cout<<"START"<<'\n';
    
    //    if (graph->calculateCentralities){
    for (long i=startNode; i<endNode; i++)
    {
        if(i%1000==0){
            std::cout<<""<<i*100/(endNode-startNode)<< "%"<<'\n';
        }
        //        std::cout<<'\n';
        std::vector<Node*> listNodes;
        Node* nodeInit=&(graph->nodes[i]);
        graph->calculateCutoffSpeed(nodeInit, radius,listNodes);
        //            Graph realSubgraph;
        //            Graph* subgraph=&realSubgraph;
        Graph subgraph;
        //        subgraph.resetGraph();
        //        subgraph->numberDistances=(int)(combinedDistancesToCalculate.size());
        graph->getInducedSubgraph(&subgraph,listNodes);
        
        subgraph.calculateTSL=false;
        //            resetWeights(&subgraph, indexAlpha,initVertex,endVertex);
        subgraph.calculateCentralities=true;
        subgraph.calculateDiffussion=false;
        subgraph.calculateGlobalProperties=false;
        //        subgraph->calculateTSL=true;
        
        subgraph.prepareForCentralitiesCalculation();
        //        subgraph.indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCalculation;
        //        for(long h=0;h<subgraph->nodes.size();h++){
        //            for(long j=0;j<subgraph->nodes[h].transitions.size();j++){
        //                subgraph->nodes[h].transitions[j].weight=subgraph->nodes[h].transitions[j].otherWeights[indexDistanceInOtherDistancesCalculation];
        //            }
        //        }
        subgraph.calculateMainDistance=false;
        subgraph.calculateOtherDistances=true;
        //        for(int j=0; j<indexDistancesToCalculate.size(); j++)
        //        {
        //            if (indexAlpha==indexDistancesToCalculate[j])
        //            {
        //                subgraph->indexOfMainDistanceInOtherDistances=j;
        //                subgraph->calculateMainDistance=true;
        //            }
        //        }
        Node* nodeTemp=nodeInit->nodeRepresentedBy;
        if (subgraph.nodes.size()>1)
        {
            //            for(long j=0;j<subgraph->nodes.size();j++){
            //            int j=0;
            
            std::vector<int> indexOfDistancesToCalculate;
            indexOfDistancesToCalculate.push_back(indexDistanceInOtherDistancesCalculation);
            //            std::vector<int> setOfDistancesToCalculate=subgraph->indexOfDistancesByDistanceType[Graph::METRIC];
            subgraph.calculateShortestPathsSpeed(nodeTemp,0,indexOfDistancesToCalculate);
            //                Node* nodeTemp=&(subgraph->nodes[0]);
            //                            subgraph->calculateShortestPathsSpeed(nodeTemp,combinedRadius);
            //            }
        }
        listNodes.clear();
        std::stringstream nameSS;
        nameSS<<"subgraph"<<threadNumber;
        std::string name=nameSS.str();
        for(long h=0;h<subgraph.nodes.size();h++){
            graph->betweennessMeasures[indexDistanceInOtherDistancesCalculation][subgraph.nodes[h].nodeThatRepresents->id]+=subgraph.betweennessMeasures[indexDistanceInOtherDistancesCalculation][subgraph.nodes[h].id];
            
        }
        //        graph->betweenness[nodeInit->id]=subgraph->betweennessMeasures[indexDistanceInOtherDistancesCalculation][nodeTemp->id];
        graph->closenessMeasures[indexDistanceInOtherDistancesCalculation][nodeInit->id]=subgraph.closenessMeasures[indexDistanceInOtherDistancesCalculation][nodeTemp->id];
        
        
        //        saveFiles(subgraph, name, indexAlpha, combinedRadius,i,saveHeader);
        
        if(saveHeader)
        {
            saveHeader=false;
        }
        //        delete subgraph;
        //            subgraph.nodes.clear();
    }
    //    }
    
    
    
    
    std::cout<<"END"<<'\n';
}
void calculateCentralities(Graph* graph,double radius,long startNode,long endNode,int threadNumber,int indexDistanceInOtherDistancesCutoff,int indexDistanceInOtherDistancesCalculation)
{
    
    
    for(long i=0;i<graph->nodes.size();i++){
        for(long j=0;j<graph->nodes[i].transitions.size();j++){
            graph->nodes[i].transitions[j]->weight=graph->nodes[i].transitions[j]->otherWeights[indexDistanceInOtherDistancesCutoff];
        }
    }
    graph->indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCutoff;
    
    
    graph->prepareForCentralitiesCalculation();
    graph->calculateCentralities=true;
    graph->calculateDiffussion=false;
    graph->calculateGlobalProperties=false;
    
    graph->calculateMainDistance=false;
    graph->calculateTSL=false;
    graph->calculateOtherDistances=true;
    graph->prepareForCentralitiesCalculation();
    std::cout<<"START"<<'\n';
    
    for (long i=startNode; i<endNode; i++)
    {
        if(i%1000==0){
            std::cout<<""<<i*100/(endNode-startNode)<< "%"<<'\n';
        }
        
        std::vector<Node*> listNodes;
        Node* nodeInit=&(graph->nodes[i]);
        std::vector<int> indexOfDistancesToCalculate;
        indexOfDistancesToCalculate.push_back(indexDistanceInOtherDistancesCalculation);
        
        graph->calculateShortestPathsSpeed(nodeInit,radius,indexOfDistancesToCalculate);
        
    }
    
    
    
    
    
    std::cout<<"END"<<'\n';
}




void calculateCentralitiesEuclideanCutoff(Graph* graph,QTree* quadTree,double radius,long startNode,long endNode,int threadNumber,int indexDistanceInOtherDistancesCutoff,int indexDistanceInOtherDistancesCalculation)
{
    
    
    for(long i=0;i<graph->nodes.size();i++){
        for(long j=0;j<graph->nodes[i].transitions.size();j++){
            graph->nodes[i].transitions[j]->weight=graph->nodes[i].transitions[j]->otherWeights[indexDistanceInOtherDistancesCutoff];
        }
    }
    graph->indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCutoff;
    
    
    graph->prepareForCentralitiesCalculation();
    graph->calculateCentralities=true;
    graph->calculateDiffussion=false;
    graph->calculateGlobalProperties=false;
    
    graph->calculateMainDistance=false;
    graph->calculateTSL=false;
    graph->calculateOtherDistances=true;
    graph->prepareForCentralitiesCalculation();
    std::cout<<"START"<<'\n';
    
    for (long i=startNode; i<endNode; i++)
    {
        if(i%1000==0){
            std::cout<<""<<i*100/(endNode-startNode)<< "%"<<'\n';
        }
        
        std::vector<Node*> listNodes;
        Node* nodeInit=&(graph->nodes[i]);
        std::vector<int> indexOfDistancesToCalculate;
        indexOfDistancesToCalculate.push_back(indexDistanceInOtherDistancesCalculation);
        
        graph->calculateShortestPathsSpeedEuclideanCutoff(quadTree,nodeInit,radius,indexOfDistancesToCalculate);
        
    }
    
    
    
    
    
    std::cout<<"END"<<'\n';
}




void calculateFuzzyNetworkPercolationAndCentralities(Graph* graph)
{
    //    resetWeights(graph, indexAlpha,initVertex,endVertex);
    //    bool saveHeader=true;
    
    //    graph->init();
    graph->indexOfMainDistanceInOtherDistances=-1;
    graph->calculateMainDistance=true;
    graph->calculateOtherDistances=false;
    
    std::cout<<"START"<<'\n';
    
    //    if (graph->calculateCentralities){
    std::vector<Graph> clusters;
    graph->calculateClustersUsingFuzzyNetworkPercolation(25,3.25, clusters);
    //rural/urban=25,3.25
    //inner city=50,1.25
    for (long i=0; clusters.size(); i++)
    {
        
        Graph* subgraph=&(clusters[i]);
        subgraph->numberDistances=(int)(combinedDistancesToCalculate.size());
        
        
        //            resetWeights(&subgraph, indexAlpha,initVertex,endVertex);
        subgraph->calculateCentralities=true;
        subgraph->calculateDiffussion=false;
        subgraph->calculateTSL=false;
        
        //        subgraph->init();
        subgraph->indexOfMainDistanceInOtherDistances=-1;
        subgraph->calculateMainDistance=true;
        subgraph->calculateOtherDistances=false;
        
        if (subgraph->nodes.size()>2)
        {
            for(long j=0; j<subgraph->nodes.size(); j++)
            {
                //            int j=0;
                Node* nodeTemp=&(subgraph->nodes[j]);
                std::vector<int> setOfDistancesToCalculate=subgraph->indexOfDistancesByDistanceType[Graph::METRIC];
                subgraph->calculateShortestPathsSpeed(nodeTemp,0,setOfDistancesToCalculate);
                //                Node* nodeTemp=&(subgraph->nodes[0]);
                //                            subgraph->calculateShortestPathsSpeed(nodeTemp,combinedRadius);
            }
        }
        
        std::stringstream nameSS;
        nameSS<<"/Users/Documents/results/clustersFromFuzzyPercolation/subgraph_network520_GlobalProperties.txt";
        std::string name=nameSS.str();
        double totalCloseness=0;
        double totalBetweenness=0;
        long numTransitions=0;
        //        double totalDegree=0;
        double TSL=0;
        for(long j=0; j<subgraph->nodes.size(); j++)
        {
            totalBetweenness+=subgraph->betweenness[j];
            totalCloseness+=subgraph->betweenness[j];
            numTransitions+=subgraph->nodes[j].transitions.size();
            //            totalDegree
            
            for(long h=0; h<subgraph->nodes[j].transitions.size(); h++)
            {
                TSL+=subgraph->nodes[j].transitions[h]->weight;
            }
            
        }
        
        //        saveFiles(subgraph, name, 0, 0,i,saveHeader);
        std::vector<std::string> values;
        ArchivoTexto textFile;
        std::stringstream valuesSS;
        if(i==0)
        {
            std::stringstream headerSS;
            headerSS<<"numCluster,numberNodes,numberTrans,TSL,closeness,betweenness";
            std::string header=headerSS.str();
            values.push_back(header);
        }
        valuesSS<<i<<","<<subgraph->nodes.size()<<","<<numTransitions<<","<<TSL<<","<<totalCloseness<<","<<totalBetweenness;
        std::string value=valuesSS.str();
        values.push_back(value);
        textFile.writeToFile(name, values, true);
        //        if(saveHeader){
        //            saveHeader=false;
        //        }
        //            subgraph.nodes.clear();
    }
    //    }
    std::cout<<"END"<<'\n';
}


//bool compareStringsOfClusters(std::vector<string> a,std::vector<string> b){
//    ArchivoTexto textFile;
//    std::vector<string> wordsA=textFile.extractWords(a[0], ",");
//    std::vector<string> wordsB=textFile.extractWords(b[0], ",");
//    const char * input;
//    input=wordsA[1].c_str();
//    long sizeA=atol(input);
//    input=wordsB[1].c_str();
//    long sizeB=atol(input);
//    return sizeA<sizeB;
//}

void calculateNetworkPercolation(Graph* graph,double distanceLimit,bool saveFilesClusters,bool returnClusters,std::string nameFolderForFiles,long minClusterSizeForSaving)
{
    //    resetWeights(graph, indexAlpha,initVertex,endVertex);
    //    bool saveHeader=true;
    
    //    graph->init();
    graph->indexOfMainDistanceInOtherDistances=-1;
    graph->calculateMainDistance=false;
    graph->calculateOtherDistances=false;
    //    for(int i=0;i<indexDistancesToCalculate.size();i++){
    //        if (indexAlpha==indexDistancesToCalculate[i]){
    //            graph->indexOfMainDistanceInOtherDistances=i;
    //            graph->calculateMainDistance=true;
    //        }
    //    }
    std::cout<<"START"<<'\n';
    
    
    std::vector<Graph> clusters;
    graph->calculateClusterUsingNetworkPercolation(distanceLimit,clusters,saveFilesClusters,returnClusters,nameFolderForFiles,minClusterSizeForSaving);
    //    for(long i=0;i<clusters.size();i++){
    //        std::stringstream nameSS;
    //        nameSS<<"/Users/Documents/results/clustersFromPercolation/UK/network_dc100n"<<i<<".txt";
    //        std::string name=nameSS.str();
    //        ArchivoTexto textFile;
    //        textFile.writeNCOLPlusCoordinatesFile(&clusters[i], name);
    //    }
    
    
    std::cout<<"END"<<'\n';
    //    return clusters;
}

void calculateAngularNetworkPercolation(Graph* graph,std::vector<Graph> &clusters, double distanceLimit,bool saveFilesClusters,bool returnClusters,std::string nameFolderForFiles,long minClusterSizeForSaving)
{
    //    resetWeights(graph, indexAlpha,initVertex,endVertex);
    //    bool saveHeader=true;
    
    //    graph->init();
    //    graph->indexOfMainDistanceInOtherDistances=-1;
    graph->calculateMainDistance=false;
    graph->calculateOtherDistances=false;
    //    for(int i=0;i<indexDistancesToCalculate.size();i++){
    //        if (indexAlpha==indexDistancesToCalculate[i]){
    //            graph->indexOfMainDistanceInOtherDistances=i;
    //            graph->calculateMainDistance=true;
    //        }
    //    }
    std::cout<<"START clustering, distance="<<distanceLimit<<'\n';
    
    
    
    //    std::vector<Graph> clusters;
    graph->calculateClusterUsingNetworkPercolation(distanceLimit,clusters,false,true,nameFolderForFiles,minClusterSizeForSaving);
    std::stringstream nameFile;
    nameFile<<nameFolderForFiles<<"angularNetworkPercolation_d"<<(distanceLimit)<<".txt";
    if(saveFilesClusters){
        
        std::vector<std::string> values;
        values.push_back("idCluster sizeCluster idNodeOrigin idNodeDestination weight");
        for(long i=0;i<clusters.size();i++){
            if(clusters[i].nodes.size()>=minClusterSizeForSaving){
                for(long j=0;j<clusters[i].nodes.size();j++){
                    std::stringstream value;
                    Transition* trans;
                    trans=clusters[i].nodes[j].transitionThatRepresents;
                    value<<i<<" "<<clusters[i].nodes.size()<<" "<<trans->a->originalID<<" "<<trans->b->originalID<<" "<<trans->weight;
                    values.push_back(value.str());
                }
            }
            
        }
        ArchivoTexto textFile;
        textFile.writeToFile(nameFile.str(), values, false);
        values.clear();
        
    }
    if(!returnClusters){
        clusters.clear();
    }
    
    //    for(long i=0;i<clusters.size();i++){
    //        std::stringstream nameSS;
    //        nameSS<<"/Users/Documents/results/clustersFromPercolation/UK/network_dc100n"<<i<<".txt";
    //        std::string name=nameSS.str();
    //        ArchivoTexto textFile;
    //        textFile.writeNCOLPlusCoordinatesFile(&clusters[i], name);
    //    }
    
    
    std::cout<<"END"<<'\n';
    //    return clusters;
}


//void calculateSubgraphs(Graph* graph,double combinedRadius,int indexAlpha, std::vector<double> initVertex,std::vector<double> endVertex,long startNode,long endNode){
//    resetWeights(graph, indexAlpha,initVertex,endVertex);
//
//
//    graph->init();
//    graph->indexOfMainDistanceInOtherDistances=-1;
//    graph->calculateMainDistance=false;
//    graph->calculateOtherDistances=true;
//    for(int i=0;i<indexDistancesToCalculate.size();i++){
//        if (indexAlpha==indexDistancesToCalculate[i]){
//            graph->indexOfMainDistanceInOtherDistances=i;
//            graph->calculateMainDistance=true;
//        }
//    }
//    std::cout<<"START"<<'\n';
//
//    if (graph->calculateCentralities){
//        for (long i=startNode;i<endNode;i++){
//            graph->calculateShortestPathsSpeed(&(graph->nodes[i]),combinedRadius);
//        }
//    }
//    if (graph->calculateDiffussion){
//        graph->calculateDiffusionAlgorithm(5,startNode,endNode);
//    }
//    std::cout<<"END"<<'\n';
//}




int main( int argc,char *argv[])
{
    /*
     1st argument: folder
     2nd argument: subfolderIn
     3rd argument: subfolderOut
     4th argument: subfolderLocationCoordinatesFile
     5rth argument: nameOfClustersFile (without distance)
     5th argument: nameOfFileCoordinates
     6th argument: separatorClustersFile
     7th argument: separatorCoordinates
     8th argument: startDistance
     9th argument: endDistance
     10th argument: separationBetweenDistances
     11th argument: minClusterSize
     */
    std::cout<<"number of arguments "<<argc<<'\n';
    for(int i=0;i<argc;i++){
        std::cout<<"argv["<<i<<"]= \""<<argv[i]<<"\""<<'\n';
    }
    //    Configuration::setFolder("C:/Users/Carlos/Documents/_TRABAJO/CASA/");
    if (argc>1){
        Configuration::setFolder(argv[1]);
        //        std::cout<<Configuration::folder();
        Configuration::setSubFolderIn(argv[2]);
        //        std::cout<<Configuration::folderIn();
        Configuration::setSubFolderOut(argv[3]);
        //        std::cout<<Configuration::folderOut();
    }else{
        Configuration::setFolder("/Users/carlos/Documents/");
        
        
        
        
        if(modeCalculation==CALCULATE_CENTRALITIES&&formatFile==IMPORT_PRIMALGRAPH_AND_GENERATE_LINEGRAPH){
            
//            Configuration::setSubFolderIn("data/GIS/Melbourne/example/");
//            Configuration::setSubFolderOut("results/CyclistAnalysis/example/");
                Configuration::setSubFolderIn("data/GIS/Melbourne/");
                Configuration::setSubFolderOut("results/CyclistAnalysis/");
        }else if(formatFile==IMPORT_PRIMALGRAPH_AND_INFORMATIONALGRAPH){
                    Configuration::setSubFolderIn("data/informationalGraphs/");
                    Configuration::setSubFolderOut("results/informationalGraphs/");
        }else{
//                            Configuration::setSubFolderIn("data/GIS/UK/");
//                            Configuration::setSubFolderOut("results/clustersFromPercolation/UK/cities/");
            Configuration::setSubFolderIn("data/GIS/EU/");
            Configuration::setSubFolderOut("results/clustersFromPercolation/EU/");

            
        }
        
//                Configuration::setSubFolderIn("data/GIS/UK/");
//                Configuration::setSubFolderOut("results/clustersFromPercolation/UK/cities/");
        
//                        Configuration::setSubFolderOut("results/clustersFromPercolation/UK/clusteredHierarchical/completeData/");
//          Configuration::setSubFolderOut("results/clustersFromPercolation/UK/");
        

        
    }
    std::cout<<"START OF PROGRAM"<<'\n';
    
    
    
    
    Timer timer;
    timer.active=false;
    
    
    
    //    timer.start(std::to_string(modeCalculation));
    ArchivoTexto textFile;
    //    textFile.parseCompleteClusterNetworkAndExportToSingleFiles();
    //    std::cout<<"FinishedTransformingFile"<<'\n';
    std::vector<Graph> graphs;
    Graph mainGraph;
    
    //    mainGraph.parallelize(1,'a',"asdf");
    
    
    bool parallel=false;
    int numThreads=8;
    if (!parallel)
    {
        numThreads=0;
    }
    for (int i=0; i<numThreads; i++)
    {
        Graph graph;
        graphs.push_back(graph);
    }
    
    
    std::vector<double> radiiCutoff;
    std::vector<double> proportions;
    for(int j=1; j<11; j++)
    {
        radiiCutoff.push_back(j*10000);
    }
    
    if(formatFile==TEST){
        timer.active=true;
//        timer.start("initHeap new");
        
//        timer.stop();
        
        long totalSize=3000;
        long secondarySize=100;
        std::vector<Node> nodes;
//        timer.start("insertNodes first time");
        for(long i=0;i<totalSize;i++){
            Node a;
            a.originalID=i;
            a.minDistance=rand()%1000;
            nodes.push_back(a);
            
        }
//        timer.stop();
        timer.start("old heap type");
        MinHeap<Node*> heapb;
        for(long i=0;i<nodes.size();i++){
            Node* a=&nodes[i];
            heapb.push(a,&Graph::compareByDistance);
//            if(rand()%10<2){
//                a->minDistance=rand()%1000;
//                
//                heapb.buildHeap(&Graph::compareByDistance);
//            }
        }
        for(long i=0;i<secondarySize;i++){
            Node* a=&nodes[i];
            //            double old=a->minDistance;
            a->minDistance=rand()%1000;
            
            heapb.buildHeap(&Graph::compareByDistance);
        }
//                heap.print(true);
        timer.stop();
        
        timer.start("old heap type II");
        MinHeap<Node*> heapc;
        for(long i=0;i<nodes.size();i++){
            Node* a=&nodes[i];
            heapc.push(a,&Graph::compareByDistance);
//            if(rand()%10<2){
//                a->minDistance=rand()%1000;
//                
//                heapc.buildHeap(&Graph::compareByDistance);
//            }
        }
        for(long i=0;i<secondarySize;i++){
            Node* a=&nodes[i];
            //            double old=a->minDistance;
            a->minDistance=rand()%1000;
            
            heapc.buildHeap(&Graph::compareByDistance);
        }
        //        heap.print(true);
        timer.stop();
        
        
//        heap.print(true);
//        heap.print(true,&Graph::compareByDistance);
        
//        for(long i=0;i<timer.getTimes().size();i++){
//            std::cout<<timer.getTimes()[i]<<'\n';
//        }
//        timer.start("initHeap old");
//        
//        timer.stop();
        
//        timer.start("insertNodes second time");
        nodes.clear();
        for(long i=0;i<totalSize;i++){
            Node a;
            a.originalID=i;
            a.minOtherDistances.push_back(rand()%1000);
            a.minDistance=rand()%1000;
            nodes.push_back(a);
            
        }
//        timer.stop();
        
        
        timer.start("new heap type");
        Heap<Node*> heap(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        heap.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances, 0, 1);
        for(long i=0;i<nodes.size();i++){
            Node* a=&nodes[i];
            heap.push(a);
//            if(rand()%10<2){
//                double old=a->minDistance;
//                a->minDistance=rand()%1000;
//                
//                heap.update(a,old);
//            }
        }
        
        for(long i=0;i<secondarySize;i++){
            Node* a=&nodes[i];
            double old=a->minOtherDistances[0];
            a->minOtherDistances[0]=rand()%1000;
            
            heap.update(a,old);
        }
        timer.stop();
        heap.print(true);
        timer.start("new heap type II");
        Heap<Node*> heapd(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
        for(long i=0;i<nodes.size();i++){
            Node* a=&nodes[i];
            heapd.push(a);
//            if(rand()%10<2){
//                double old=a->minDistance;
//                a->minDistance=rand()%1000;
//                
//                heapd.update(a,old);
//            }
        }
        for(long i=0;i<secondarySize;i++){
            Node* a=&nodes[i];
            double old=a->minDistance;
            a->minDistance=rand()%1000;
            
            heapd.update(a,old);
        }
        timer.start("new heap type imitating old");
        Heap<Node*> heape(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,false);
                heape.changeGetValueFunction(&Graph::compareByOtherDistances,&Graph::getMinOtherDistances, 0, 1);
        for(long i=0;i<nodes.size();i++){
            Node* a=&nodes[i];
            heape.push(a);
//            if(rand()%10<2){
//                double old=a->minDistance;
//                a->minDistance=rand()%1000;
//                
//                heape.update(a,old);
//            }
        }
        for(long i=0;i<secondarySize;i++){
            Node* a=&nodes[i];
            double old=a->minDistance;
            a->minDistance=rand()%1000;
            
            heape.update(a,old);
        }
        timer.start("new heap type imitating old II");
        Heap<Node*> heapf(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,false);
        for(long i=0;i<nodes.size();i++){
            Node* a=&nodes[i];
            heapf.push(a);
//            if(rand()%10<2){
//                double old=a->minDistance;
//                a->minDistance=rand()%1000;
//                
//                heapf.update(a,old);
//            }
        }
        for(long i=0;i<secondarySize;i++){
            Node* a=&nodes[i];
            double old=a->minDistance;
            a->minDistance=rand()%1000;
            
            heapf.update(a,old);
        }
        //
        timer.stop();
//        while(heapb.size()>0){
//            Node* a=heapb.pop(&Graph::compareByDistance);
//            std::cout<<"heapB "<<a->minDistance<<'\n';
//        }
        for(long i=0;i<timer.getTimes().size();i++){
            std::cout<<timer.getTimes()[i]<<'\n';
        }
        
    }
    if(formatFile==IMPORT_PRIMALGRAPH_AND_INFORMATIONALGRAPH){
        
        ArchivoTexto textFile;
        std::stringstream nameGraph;
        
        std::stringstream nameDualGraph;
        std::stringstream nameCoordinatesFile;
        long startNode=0;
        long endNode=1;
        bool fromBeginningToEnd=false;
        std::string cityName;
        
        
        if (argc>4){
            //                std::cout<<argv[4];
            nameGraph<<Configuration::folderIn()<<argv[4];
            nameDualGraph<<Configuration::folderIn()<<argv[5];
            nameCoordinatesFile<<Configuration::folderIn()<<argv[5];
            startNode=atol(argv[6]);
            endNode=atol(argv[7]);
            cityName=argv[8];
            if(startNode==0&&endNode==0){
                fromBeginningToEnd=true;
            }
            
        }else{
            fromBeginningToEnd=true;
//            nameGraph<<Configuration::folderIn()<<"sample/sample1.net";
//            nameDualGraph<<Configuration::folderIn()<<"sample/sample2.net";
            
            
//            nameGraph<<Configuration::folderIn()<<"london/lndM25_Complete_segmentsWithNames.txt";
//            nameCoordinatesFile<<Configuration::folderIn()<<"london/lndM25_Complete_coordinates.txt";
            
                        nameGraph<<Configuration::folderIn()<<"london/london_segmentsWithNames.txt";
                        nameCoordinatesFile<<Configuration::folderIn()<<"london/london_coordinates.txt";
            
//            nameGraph<<Configuration::folderIn()<<"london/londonDEL_segmentsWithNames.txt";
//            nameCoordinatesFile<<Configuration::folderIn()<<"london/lndM25_coordinates.txt";
            
            
//            nameGraph<<Configuration::folderIn()<<"london/lndM25_B_segmentsWithNames.txt";
//            nameCoordinatesFile<<Configuration::folderIn()<<"london/lndM25_B_coordinates.txt";
            
//            nameGraph<<Configuration::folderIn()<<"ERPG/erpg_segmentsWithNames.txt";
//            nameCoordinatesFile<<Configuration::folderIn()<<"ERPG/erpg_coordinates.txt";
            
//            nameGraph<<Configuration::folderIn()<<"chicago/Chicago_segmentsWithNames.txt";
//            nameCoordinatesFile<<Configuration::folderIn()<<"chicago/Chicago_coordinates.txt";
            
//            nameGraph<<Configuration::folderIn()<<"chicago/ChicagoMST_segmentsWithNames.txt";
//                        nameCoordinatesFile<<Configuration::folderIn()<<"chicago/Chicago_coordinates.txt";
            
//            nameGraph<<Configuration::folderIn()<<"london/gridDEL_segmentsWithNames.txt";
//            nameCoordinatesFile<<Configuration::folderIn()<<"london/gridDEL_coordinates.txt";
            
//            nameGraph<<Configuration::folderIn()<<"london/ld_primal.net";
//            nameDualGraph<<Configuration::folderIn()<<"london/ld_dual.net";
            
//                        nameGraph<<Configuration::folderIn()<<"MST/MSTDEL_London.net";
//                        nameDualGraph<<Configuration::folderIn()<<"MST/MSTDEL_London_dual.net";
            
            cityName="london_";
            
            
        }
        Graph primalGraph;
        Graph lineGraph;
        
        
        
        
        
       
        
        if(modeCalculation==CALCULATE_CLOSENESS_THROUGH_SHORTESTINFORMATIONAL_ROUTE){
             Graph dualInformationalGraph;
        primalGraph.pseudoGraph=false;
        dualInformationalGraph.pseudoGraph=false;
        
//        textFile.parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/ncol.txt", "/Users/carlos/Documents/coordinates.txt", &primalGraph, " ", " ", false, false);
//        primalGraph.transformToBidirectional();
        textFile.parsePajekGraphAndInformationalDual(nameGraph.str(), nameDualGraph.str(), &primalGraph,&lineGraph, &dualInformationalGraph);
       
     
        
//        std::vector<Graph> clusters;
////        Graph newPrimalTemp;
//
//        
//        Graph giantComponent;
//        
//        primalGraph.getGiantComponent(&primalGraph, &giantComponent);
////
////        giantComponent.generateSpatialPercolation(&giantComponent, 10, clusters);
////        Graph newPrimal;
////        
////        newPrimal.pseudoGraph=false;
////        giantComponent.generateSuperGraphFromClusters(clusters, &giantComponent,&newPrimal);
//
//        Graph lineGraphTemp;
//        lineGraph.resetGraph();
//        giantComponent.createLineGraph(&giantComponent, &lineGraph);
////        giantComponent.createLineGraph(&giantComponent, &lineGraphTemp);
////        std::vector<Graph> clusters;
////        lineGraphTemp.generateSpatialPercolation(&lineGraphTemp, 5, clusters);
////        lineGraphTemp.generateSuperGraphFromClusters(clusters, &lineGraphTemp,&lineGraph);
//        
////        lineGraph.transformToBidirectional();
//        for(long i=0;i<lineGraph.nodes.size();i++){
//            for(long j=0;j<lineGraph.nodes[i].transitions.size();j++){
//                lineGraph.nodes[i].transitions[j].otherWeights[lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=lineGraph.nodes[i].transitions[j].weight;
//                lineGraph.nodes[i].transitions[j].weight=lineGraph.nodes[i].transitions[j].otherWeights[lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
//            }
//        }
//        std::vector<Graph> angularClusters;
//        lineGraph.calculateClusterUsingNetworkPercolation(40, angularClusters, false, true, "", 0);
//        dualInformationalGraph.resetGraph();
//        dualInformationalGraph.pseudoGraph=true;
//        lineGraph.generateSuperGraphFromClusters(angularClusters,&lineGraph, &dualInformationalGraph);
//        
//        for(long i=0;i<dualInformationalGraph.nodes.size();i++){
//            for(long j=0;j<dualInformationalGraph.nodes[i].nodesCollapsed.size();j++){
//                dualInformationalGraph.nodes[i].nodesRelated.push_back(dualInformationalGraph.nodes[i].nodesCollapsed[j]);
////                dualInformationalGraph.nodes[i].nodesCollapsed[j]->nodesRelated.push_back(&dualInformationalGraph.nodes[i]);
//                
//            }
//            for(long j=0;j<dualInformationalGraph.nodes[i].transitions.size();j++){
//                dualInformationalGraph.nodes[i].transitions[j].weight=1;
//            }
//        }
//        
//        for(long i=0;i<lineGraph.nodes.size();i++){
//            for(long j=0;j<lineGraph.nodes[i].transitions.size();j++){
//                //                lineGraph.nodes[i].transitions[j].otherWeights[lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=lineGraph.nodes[i].transitions[j].weight;
//                lineGraph.nodes[i].transitions[j].weight=lineGraph.nodes[i].transitions[j].otherWeights[lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0]];
//            }
//        }
//        
//        
//        
//                    std::stringstream fileName;
//                    fileName<< Configuration::folderOut()<<cityName<<"dual.txt";
//        
//                    textFile.writeNCOLPlusCoordinatesFile(&dualInformationalGraph,fileName.str());
//        
////        std::stringstream fileName;
//        fileName.str("");
//        fileName<< Configuration::folderOut()<<cityName<<"lineGraph.txt";
//        
//        textFile.writeNCOLPlusCoordinatesFile(&lineGraph,fileName.str());
//        
//        
////        fileName.str("");
////        fileName<< Configuration::folderOut()<<cityName<<"giantComponent.txt";
////        
////        textFile.writeNCOLPlusCoordinatesFile(&giantComponent,fileName.str());
////        
////        
////        fileName.str("");
////        fileName<< Configuration::folderOut()<<cityName<<"newPrimal.txt";
////        
////        textFile.writeNCOLPlusCoordinatesFile(&newPrimal,fileName.str());
//        
//        
//        
//       
//        
//        
//        
        
        
        
        if(fromBeginningToEnd){
            startNode=0;
            endNode=dualInformationalGraph.nodes.size();
            //                    endNode=1;
        }
        
        
        
            timer.active=false;
            timer.start("Calculate informational graph");
       

            lineGraph.prepareForCentralitiesCalculation();
            for(long i=startNode;i<endNode;i++){
                
                
                Node* nodeInit=&(dualInformationalGraph.nodes[i]);
//                if(nodeInit->transitions.size()>0){
                if(true){

                    Node* nodeEnd=NULL;
                    Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,false);
//                    nodesToCheckDijkstra.updatable=false;
                    nodeInit->minDistance=0;
                    nodesToCheckDijkstra.push(nodeInit);
                    nodeInit->inDijkstra=true;
                    
                    dualInformationalGraph.calculateAllShortestPathsToANodeUsingModificationDijkstra(nodeInit, nodeEnd, nodesToCheckDijkstra);
                    for(long j=0;j<dualInformationalGraph.nodes.size();j++){
     
//                        if(dualInformationalGraph.nodes[j].transitions.size()>0){
                        if(true){
                            std::vector<Node*> nodesSubgraph;
                            std::vector<Node*> nodesDestination;
                            std::vector<Node*> nodesOfResultingGraph;
                            std::vector<Node*> pathInDualInformational;
                            if(i!=j){
//                                cout<<"i!=j"<<'\n';

                                Node* current;
                                current=&(dualInformationalGraph.nodes[j]);

                                std::vector<Node*> possibleParents;
                                nodesDestination.clear();

                                nodesOfResultingGraph.clear();
                                
                                for(long h=0;h<current->nodesRelated.size();h++){
                                    

                                    nodesDestination.push_back(current->nodesRelated[h]);
             
                                    
                                }
                                
                                
                                nodesSubgraph.clear();
                                while(current!=NULL){
                                    if(j==521){
//                                        cout<<"stop"<<'\n';
                                    }
                                    pathInDualInformational.push_back(current);
                                    //                                std::cout<<current->originalID<<'\n';
                                    for(long d=0;d<current->nodesRelated.size();d++){
                                        if(!current->nodesRelated[d]->inCluster){
                                            if(j==521){
//                                                cout<<current->nodesRelated[d]->originalID<<'\n';
                                            }
                                            nodesSubgraph.push_back(current->nodesRelated[d]);
                                            current->nodesRelated[d]->inCluster=true;
                                        }
                                    }

                                    for(long h=0;h<current->parents.size();h++){
                                        if(!current->parents[h]->inCutoff){
                                            possibleParents.push_back(current->parents[h]);
                                            nodesOfResultingGraph.push_back(current->parents[h]);
                                            current->parents[h]->inCutoff=true;
                                        }else{

                                        }
        
                                        
                                        
                                    }
                                    if(possibleParents.size()>0){
                                        current=possibleParents.back();
                                        possibleParents.pop_back();
                                    }else{
                                        current=NULL;
                                    }
                                    
                                }

                                
                            }else{
//                                cout<<"i==j - aqui seria logico no tener transiciones, no?"<<'\n';
                                Node* current;
                                current=&(dualInformationalGraph.nodes[j]);
                                for(long h=0;h<current->nodesRelated.size();h++){
                                    

                                    if(!current->nodesRelated[h]->inCluster){
                                        
                                        nodesDestination.push_back(current->nodesRelated[h]);
                                        nodesSubgraph.push_back(current->nodesRelated[h]);
                                        current->nodesRelated[h]->inCluster=true;
                                    }

                                    
                                }
                            }
                            
                            Graph subGraphCutoff;
                            
                            subGraphCutoff.resetGraph();

                            lineGraph.getInducedSubgraph(&subGraphCutoff, nodesSubgraph);
                            subGraphCutoff.prepareForCentralitiesCalculation();
                            subGraphCutoff.calculateCentralities=false;
                            subGraphCutoff.calculateMainDistance=true;
                            subGraphCutoff.calculateBetweenness=false;
                            subGraphCutoff.calculateOtherDistances=false;
                            
//                            fileName.str("");
//                            fileName<< Configuration::folderOut()<<cityName<<i<<" "<<j<<"subGraph.txt";
//                            
//                            textFile.writeNCOLPlusCoordinatesFile(&subGraphCutoff,fileName.str());

                            
                            std::vector<int> setOfDistancesToCalculate;
                            if(subGraphCutoff.nodes.size()>0){
                                for(long h=0;h<nodeInit->nodesRelated.size();h++){
                                    Node* node=nodeInit->nodesRelated[h]->nodeRepresentedBy;
//                                    cout<<"size of nodeInit->nodesRelated"<<nodeInit->nodesRelated.size()<<" "<<"current "<<h<<'\n';
                                    if(node!=NULL&&node->transitions.size()>0){
                                        Heap<Node*> nodesToCheckDijkstraB(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                                        
                                        node->minDistance=0;
                                        nodesToCheckDijkstraB.push(node);
                                        node->inDijkstra=true;
                                        
                                        std::vector<Node*> nodesCutoff;
                                        nodesCutoff.push_back(node);
                                        node->inCutoff=true;
                                        
                                        subGraphCutoff.calculateDijkstraSpeed(node, 0, nodesCutoff, nodesToCheckDijkstraB);
                                        
                                        
                                        for(long g=0;g<nodesDestination.size();g++){
                                            if(nodesDestination[g]->nodeRepresentedBy->minDistance<INFINITY){
                                                lineGraph.closeness[nodeInit->nodesRelated[h]->id]=lineGraph.closeness[nodeInit->nodesRelated[h]->id]+nodesDestination[g]->nodeRepresentedBy->minDistance;
                                            }
                                        }
                                        for(long g=0; g<nodesCutoff.size(); g++)
                                        {
                                            
                                            nodesCutoff[g]->inCutoff=false;
                                            nodesCutoff[g]->inDijkstra=false;
                                            nodesCutoff[g]->numChildren=0;
                                            nodesCutoff[g]->numChildrenThatReachedMe=0;
                                            nodesCutoff[g]->parent=NULL;
                                            nodesCutoff[g]->minDistance=INFINITY;
                                            nodesCutoff[g]->valueToPass= nodesCutoff[g]->originalValueToPass;
                                            
                                            
                                        }
                
                                    }else{
                                        if(node==NULL){
                                            cout<<"node is NULL"<<'\n';
                                        }else{
//                                            cout<<"node.transitions.size()==0 "<<'\n';
                                        }
                                    }
                                }
                            }
                
                            for(long h=0;h<subGraphCutoff.nodes.size();h++){
                                subGraphCutoff.nodes[h].nodeThatRepresents->inCluster=false;
                                subGraphCutoff.nodes[h].nodeThatRepresents->nodeRepresentedBy=NULL;
                            }
           
                            for(long h=0;h<pathInDualInformational.size();h++){
                                pathInDualInformational[h]->inCutoff=false;
                                
                            }
                            nodesOfResultingGraph.clear();
                            pathInDualInformational.clear();
                        
                        }
                        
                    }
                    //CLEAN EVERYTHING
                    
                    for(long h=0; h<dualInformationalGraph.nodes.size(); h++)
                    {

                        dualInformationalGraph.nodes[h].inCutoff=false;
                        
                        dualInformationalGraph.nodes[h].inDijkstra=false;
                        dualInformationalGraph.nodes[h].numChildren=0;
                        dualInformationalGraph.nodes[h].numChildrenThatReachedMe=0;
                        dualInformationalGraph.nodes[h].parent=NULL;
                        dualInformationalGraph.nodes[h].parents.clear();
                        dualInformationalGraph.nodes[h].minDistance=INFINITY;
                        dualInformationalGraph.nodes[h].valueToPass= dualInformationalGraph.nodes[h].originalValueToPass;

                        
                    }
                }
            }
            
            //            std::stringstream fileName;
            //            fileName<< Configuration::folderOut()<<"testLG.txt";
            //
            //            textFile.writeNCOLPlusCoordinatesFile(&lineGraph,fileName.str());
            
            std::vector<std::string> values;
            values.push_back("idNodeOrigin idNodeDestination xNodeOrigin yNodeOrigin xNodeDestination yNodeDestination closeness");
            
            for(long j=0;j<lineGraph.nodes.size();j++){
                std::stringstream value;
                Transition* trans;
                trans=lineGraph.nodes[j].transitionThatRepresents;
                value<<trans->a->originalID<<" "<<trans->b->originalID<<" "<<trans->a->location.x<<" "<<trans->a->location.y<<" "<<trans->b->location.x<<" "<<trans->b->location.y<<" "<< lineGraph.closeness[lineGraph.nodes[j].id];
                values.push_back(value.str());
            }
            

            std::stringstream nameFile;
            nameFile<<Configuration::folderOut()<<cityName<<" "<<startNode<<" "<<endNode<<".txt";
            textFile.writeToFile(nameFile.str(), values, false);
            values.clear();
            
            timer.stop();
            for(long i=0;i<timer.getTimes().size();i++){
                std::cout<<timer.getTimes()[i]<<'\n';
            }
        }
        if(modeCalculation==CALCULATE_CLOSENESS_THROUGH_SHORTESTINFORMATIONAL_ROUTE_B){
            
            
            
            
            
            
            
            textFile.parseNCOLWithNamesEdgesAndSeparateCoordinatesFile(nameGraph.str(), nameCoordinatesFile.str(), &primalGraph, " ", " ", true);
            primalGraph.transformToBidirectional();
            
            primalGraph.createInformationalLineGraph(&primalGraph, &lineGraph);
            
            
            
            if(fromBeginningToEnd){
                startNode=0;
                endNode=lineGraph.nodes.size();
                //                    endNode=1;
            }
            
            
            
            timer.active=false;
            timer.start("Calculate informational graph");
            std::stringstream fileName;
            
            lineGraph.prepareForCentralitiesCalculation();
            for(long i=startNode;i<endNode;i++){
                Node* nodeInit=&(lineGraph.nodes[i]);
                for(long j=0;j<nodeInit->transitions.size();j++){
                    nodeInit->transitions[j]->weight=nodeInit->transitions[j]->otherWeights[lineGraph.getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]];
                }
            }
            lineGraph.indexOfMainDistanceInOtherDistances=lineGraph.getIndexesOfDistanceType(Graph::INFORMATIONAL)[0];
//            lineGraph.transformToBidirectional();
            for(long i=startNode;i<endNode;i++){
                std::cout<<"Node calculating "<<i<<" out of "<<endNode<<'\n';
                
                Node* nodeInit=&(lineGraph.nodes[i]);
                //                if(nodeInit->transitions.size()>0){
                
                
                Node* nodeEnd=NULL;
                Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,false);
                //                    nodesToCheckDijkstra.updatable=false;
                nodeInit->minDistance=0;
                nodesToCheckDijkstra.push(nodeInit);
                nodeInit->inDijkstra=true;
                
                lineGraph.calculateAllShortestPathsToANodeUsingModificationDijkstra(nodeInit, nodeEnd, nodesToCheckDijkstra);
                for(long j=0;j<lineGraph.nodes.size();j++){
//                    if(j%500==0){
//                        std::cout<<"---------- Node calculating "<<j<<"/"<<i<<" out of "<<endNode<<'\n';
//                    }
                    std::vector<Node*> nodesCutoff;
                    
                    Node* current;
                    
                    current=&(lineGraph.nodes[j]);
                    if(!current->alreadyCalculated){
//                        current->inCutoff=true;
                        lineGraph.nodes[i].inCutoff=true;
//                        nodesCutoff.push_back(current);
                        nodesCutoff.push_back(&lineGraph.nodes[i]);
                        std::vector<Node*> possibleParents;
                        
                        
                        
                        
                        while(current!=NULL){
                            if(!current->inCutoff){
                                nodesCutoff.push_back(current);
                                current->inCutoff=true;
                            }
                            
                            for(long h=0;h<current->parents.size();h++){
                                if(!current->parents[h]->inCutoff){
                                    possibleParents.push_back(current->parents[h]);
//                                    if(!current->inCutoff){
                                        nodesCutoff.push_back(current->parents[h]);
                                        current->parents[h]->inCutoff=true;
//                                    }
                                    
//                                    current->parents[h]->inCutoff=true;
                                }else{
                                    
                                }
                                
                                
                                
                            }
                            if(possibleParents.size()>0){
                                current=possibleParents.back();
                                possibleParents.pop_back();
                            }else{
                                current=NULL;
                            }
                            
                        }
                        
                        
                        
                        
                        
                        Heap<Node*> nodesToCheckDijkstraB(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                        int indexDistanceMetric=lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0];
                        nodesToCheckDijkstraB.changeGetValueFunction(Graph::compareByOtherDistances,Graph::getMinOtherDistances ,indexDistanceMetric, CompareFunc<Node*>::BYDISTANCE);
                        nodeInit->minOtherDistances[indexDistanceMetric]=0;
                        nodesToCheckDijkstraB.push(nodeInit);
                        nodeInit->inDijkstra=true;
                        
                        
                        std::vector<Node *> setOfNodes;
//                        setOfNodes.push_back(&lineGraph.nodes[j]);
                        lineGraph.calculateDijkstraSpeedOtherDistancesToSetOfNodes(nodeInit, 0, nodesCutoff, nodesToCheckDijkstraB,setOfNodes , indexDistanceMetric,true);
                        
                        
                        for(long g=0;g<nodesCutoff.size();g++){
                            if(nodesCutoff[g]->minOtherDistances[indexDistanceMetric]<INFINITY&&!nodesCutoff[g]->alreadyCalculated){
                                nodesCutoff[g]->alreadyCalculated=true;
                                lineGraph.closeness[nodeInit->id]+=nodesCutoff[g]->minOtherDistances[indexDistanceMetric];
                            }
                        }
                        

//                            if(lineGraph.nodes[j].minOtherDistances[indexDistanceMetric]<INFINITY){
//
//                                lineGraph.closeness[nodeInit->id]+=lineGraph.nodes[j].minOtherDistances[indexDistanceMetric];
//                            }
                        for(long g=0; g<nodesCutoff.size(); g++)
                        {
                            
                            nodesCutoff[g]->inCutoff=false;
                            nodesCutoff[g]->inDijkstra=false;
                            nodesCutoff[g]->numOtherChildren[indexDistanceMetric]=0;
                            nodesCutoff[g]->numOtherChildrenThatReachedMe[indexDistanceMetric]=0;
                            nodesCutoff[g]->otherParents[indexDistanceMetric]=NULL;
                            nodesCutoff[g]->minOtherDistances[indexDistanceMetric]=INFINITY;
                            nodesCutoff[g]->valueToPass= nodesCutoff[g]->originalValueToPass;
                            
                            
                        }
                        nodesCutoff.clear();
                        
                        
                        
                        //                            for(long h=0;h<subGraphCutoff.nodes.size();h++){
                        //                                subGraphCutoff.nodes[h].nodeThatRepresents->inCluster=false;
                        //                                subGraphCutoff.nodes[h].nodeThatRepresents->nodeRepresentedBy=NULL;
                        //                            }
                        //
                        //                            for(long h=0;h<pathInDualInformational.size();h++){
                        //                                pathInDualInformational[h]->inCutoff=false;
                        //
                        //                            }
                        //                            nodesOfResultingGraph.clear();
                        //                            pathInDualInformational.clear();
                    }
                    
                }
                
                
                //CLEAN EVERYTHING
                
                for(long h=0; h<lineGraph.nodes.size(); h++)
                {
                    
                    lineGraph.nodes[h].inCutoff=false;
                    lineGraph.nodes[h].alreadyCalculated=false;
                    lineGraph.nodes[h].inDijkstra=false;
                    lineGraph.nodes[h].numChildren=0;
                    lineGraph.nodes[h].numChildrenThatReachedMe=0;
                    
                    lineGraph.nodes[h].parent=NULL;
                    lineGraph.nodes[h].parents.clear();
                    lineGraph.nodes[h].minDistance=INFINITY;
                    lineGraph.nodes[h].valueToPass= lineGraph.nodes[h].originalValueToPass;
                    
                    
                }
            }
            
            
            //            std::stringstream fileName;
            //            fileName<< Configuration::folderOut()<<"testLG.txt";
            //
            //            textFile.writeNCOLPlusCoordinatesFile(&lineGraph,fileName.str());
            
            std::vector<std::string> values;
            values.push_back("idNodeOrigin idNodeDestination closeness");
            
            for(long j=0;j<lineGraph.nodes.size();j++){
                std::stringstream value;
                Transition* trans;
                trans=lineGraph.nodes[j].transitionThatRepresents;
                value<<trans->a->originalID<<" "<<trans->b->originalID<<" "<< lineGraph.closeness[lineGraph.nodes[j].id];
                values.push_back(value.str());
            }
            
            
            std::stringstream nameFile;
            nameFile<<Configuration::folderOut()<<cityName<<" "<<startNode<<" "<<endNode<<".txt";
            textFile.writeToFile(nameFile.str(), values, false);
            values.clear();
            
            timer.stop();
            for(long i=0;i<timer.getTimes().size();i++){
                std::cout<<timer.getTimes()[i]<<'\n';
            }
        }
        
        
        
        if(modeCalculation==CALCULATE_CENTRALITIES){
            
            textFile.parseNCOLWithNamesEdgesAndSeparateCoordinatesFile(nameGraph.str(), nameCoordinatesFile.str(), &primalGraph, " ", " ", true);
            primalGraph.transformToBidirectional();
            
            primalGraph.createLineGraph(&primalGraph, &lineGraph);
            
            
            
            if(fromBeginningToEnd){
                startNode=0;
                endNode=lineGraph.nodes.size();
                //                    endNode=1;
            }
            
            
            
            timer.active=false;
            timer.start("Calculate informational graph");
            std::stringstream fileName;
            
            lineGraph.prepareForCentralitiesCalculation();
            
            for(long i=startNode;i<endNode;i++){
                if(i%100==0){
                std::cout<<i<<"/"<<endNode<<'\n';
                }
                std::vector<Node*> nodesCutoff;
                Node* nodeInit=&lineGraph.nodes[i];
            
                Heap<Node*> nodesToCheckDijkstraB(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//                int indexDistanceMetric=lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0];
//                nodesToCheckDijkstraB.changeGetValueFunction(Graph::compareByOtherDistances,Graph::getMinOtherDistances ,indexDistanceMetric, CompareFunc<Node*>::BYDISTANCE);
                nodeInit->minDistance=0;
                nodesToCheckDijkstraB.push(nodeInit);
                nodeInit->inDijkstra=true;
                nodesCutoff.push_back(nodeInit);
                nodeInit->inCutoff=true;
                
                
                std::vector<Node *> setOfNodes;
                //                        setOfNodes.push_back(&lineGraph.nodes[j]);
                lineGraph.calculateDijkstraSpeed(nodeInit, 0, nodesCutoff, nodesToCheckDijkstraB);
                
                
                for(long g=0;g<nodesCutoff.size();g++){
                    if(nodesCutoff[g]->minDistance<INFINITY){
//                        nodesCutoff[g]->alreadyCalculated=true;
                        lineGraph.closeness[nodeInit->id]+=nodesCutoff[g]->minDistance;
                    }
                }
                
                
                //                            if(lineGraph.nodes[j].minOtherDistances[indexDistanceMetric]<INFINITY){
                //
                //                                lineGraph.closeness[nodeInit->id]+=lineGraph.nodes[j].minOtherDistances[indexDistanceMetric];
                //                            }
                for(long g=0; g<nodesCutoff.size(); g++)
                {
                    
                    nodesCutoff[g]->inCutoff=false;
                    nodesCutoff[g]->inDijkstra=false;
                    nodesCutoff[g]->numChildren=0;
                    nodesCutoff[g]->numChildrenThatReachedMe=0;
                    nodesCutoff[g]->parent=NULL;
                    nodesCutoff[g]->minDistance=INFINITY;
                    nodesCutoff[g]->valueToPass= nodesCutoff[g]->originalValueToPass;
                    
                    
                }
                nodesCutoff.clear();
            }
            std::vector<std::string> values;
            values.push_back("idNodeOrigin idNodeDestination closeness");
            
            for(long j=0;j<lineGraph.nodes.size();j++){
                std::stringstream value;
                Transition* trans;
                trans=lineGraph.nodes[j].transitionThatRepresents;
                value<<trans->a->originalID<<" "<<trans->b->originalID<<" "<< lineGraph.closeness[lineGraph.nodes[j].id];
                values.push_back(value.str());
            }
            
            
            std::stringstream nameFile;
            nameFile<<Configuration::folderOut()<<cityName<<" "<<startNode<<" "<<endNode<<".txt";
            textFile.writeToFile(nameFile.str(), values, false);
            values.clear();
        }
        
        
        
        if(modeCalculation==SIMPLIFY_GRAPH){
            textFile.parseNCOLWithNamesEdgesAndSeparateCoordinatesFile(nameGraph.str(), nameCoordinatesFile.str(), &mainGraph, " ", " ", true);
//            textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true, true);
            mainGraph.transformToBidirectional();
            mainGraph.createInformationalLineGraph(&mainGraph, &lineGraph);
            for(long i=0;i<lineGraph.nodes.size();i++){
                Node* nodeInit=&(lineGraph.nodes[i]);
                for(long j=0;j<nodeInit->transitions.size();j++){
                    nodeInit->transitions[j]->weight=nodeInit->transitions[j]->otherWeights[lineGraph.getIndexesOfDistanceType(Graph::INFORMATIONAL)[0]];
                }
            }
            
            textFile.writeNCOLPlusCoordinatesFile(&lineGraph, "/Users/carlos/Documents/informationalLineGraph.txt");
            
            
            
            lineGraph.indexOfMainDistanceInOtherDistances=lineGraph.getIndexesOfDistanceType(Graph::INFORMATIONAL)[0];
            std::vector<Graph> clusters;
            lineGraph.calculateClusterUsingNetworkPercolation(0.5, clusters, false, true, "", 0);
            //                    mainGraph.calculateClusterUsingNetworkPercolation(25, clusters, false, true, "", 1);
            Graph simplifiedGraph;
            lineGraph.generateSuperGraphFromClusters(clusters,&lineGraph, &simplifiedGraph);
            
            
            std::cout<<"numberNodes original "<<mainGraph.nodes.size()<<" lineGraph "<<lineGraph.nodes.size()<<" simplified "<<simplifiedGraph.nodes.size()<<'\n';
            
            
            ArchivoTexto textFile;
            std::stringstream nameFile;
            nameFile<<Configuration::folderOut()<<cityName<<"dualCollapsedGraph.txt";
            textFile.writeNCOLPlusCoordinatesFile_PlusNamesAndHierarchicalLevel(&simplifiedGraph, nameFile.str());
            
            nameFile.str("");
            nameFile<<Configuration::folderOut()<<cityName<<"primalGraph_idTransitions.txt";
            textFile.writeNCOLPlusCoordinatesFile_PlusIdTransitions(&mainGraph, nameFile.str());
            
            std::vector<std::string> collapsedNodes;
            std::vector<std::string> collapsedTransitions;
            std::vector<std::string> collapsedTransitionsInNodes;
            long numberOfCollapsedNodes=0;
            for(long i=0;i<simplifiedGraph.nodes.size();i++){
                for(long j=0;j<simplifiedGraph.nodes[i].nodesCollapsed.size();j++){
                    std::stringstream line;
                    line<<simplifiedGraph.nodes[i].originalID<<" "<<simplifiedGraph.nodes[i].nodesCollapsed[j]->originalID;
                    collapsedNodes.push_back(line.str());
                    numberOfCollapsedNodes++;
                }
                for(long j=0;j<simplifiedGraph.nodes[i].transitionsCollapsedIntoNode.size();j++){
                    std::stringstream line;
                    line<<simplifiedGraph.nodes[i].originalID<<" "<<simplifiedGraph.nodes[i].transitionsCollapsedIntoNode[j]->originalID;
                    collapsedTransitionsInNodes.push_back(line.str());
                }
                for(long j=0;j<simplifiedGraph.nodes[i].transitions.size();j++){
                    for(long h=0;h<simplifiedGraph.nodes[i].transitions[j]->transitionsCollapsed.size();h++){
                        std::stringstream line;
                        line<<simplifiedGraph.nodes[i].transitions[j]->originalID<<" "<<simplifiedGraph.nodes[i].transitions[j]->transitionsCollapsed[h]->originalID;
                        collapsedTransitions.push_back(line.str());
                    }
                }
            }
            
            std::cout<<"numberOfCollapsedNodes in saving "<<numberOfCollapsedNodes<<'\n';
            nameFile.str("");
            nameFile<<Configuration::folderOut()<<cityName<<"collapsedNodes.txt";
            textFile.writeToFile(nameFile.str(), collapsedNodes, false);
            
            nameFile.str("");
            nameFile<<Configuration::folderOut()<<cityName<<"collapsedTransitions.txt";
            textFile.writeToFile(nameFile.str(), collapsedTransitions, false);
            
            nameFile.str("");
            nameFile<<Configuration::folderOut()<<cityName<<"collapsedTransitionsIntoNodes.txt";
            textFile.writeToFile(nameFile.str(), collapsedTransitionsInNodes, false);
        }
        
        
        
    }
    

    if (formatFile==IMPORT_PRIMALGRAPH_AND_GENERATE_LINEGRAPH)
    {
        
        std::stringstream nameSS,nameCoordinatesSS;
        //            nameSS<<"/Users/cavargasru/Documents/mechanicity/erez/networks/n0600/network_dc100n"<<numCluster<<".txt";
        //            nameSS<<"/Users/carlos/Documents/data/mechanicity/EU/n0600/network_dc310n"<<numCluster<<".txt";
        //            nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/network_dc100n"<<numCluster<<".txt";
        //            nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/exampleGraph.txt";
        //            nameSS<<folder<<"data/mechanicity/EU/n0600/network_dc280n"<<numCluster<<".txt";
        std::string separatorNCOL=" ";
        std::string separatorCoordinates=" ";
        double startDistance=60;
        double endDistance=65;
        long minClusterSize=50000;
        double separationBetweenDistances=5;
        
        if (argc>4){
            //                std::cout<<argv[4];
            nameSS<<Configuration::folderIn()<<argv[4];
            nameCoordinatesSS<<Configuration::folderIn()<<argv[5];
            separatorNCOL=argv[6];
            separatorCoordinates=argv[7];
            startDistance=stod(argv[8]);
            endDistance=stod(argv[9]);
            separationBetweenDistances=stod(argv[10]);
            minClusterSize=atol(argv[11]);
        }else{
            //            nameSS<<Configuration::folderIn()<<"melbourneNCOLPure"<<".txt";
            //            nameCoordinatesSS<<Configuration::folderIn()<<"pointsFinal"<<".txt";
            
                        nameSS<<Configuration::folderIn()<<"melbourneNCOLPure"<<".txt";
                        nameCoordinatesSS<<Configuration::folderIn()<<"pointsFinal"<<".txt";
            
            
//            nameSS<<Configuration::folderIn()<<"ncol"<<".txt";
//            nameCoordinatesSS<<Configuration::folderIn()<<"coordinates"<<".txt";
            
            //
//            nameSS<<Configuration::folderIn()<<"UK_ncol"<<".txt";
//            nameCoordinatesSS<<Configuration::folderIn()<<"UK_coordinates"<<".txt";
        }
        float initPercentageNodes=0;
        float topPercentageNodes=0.5;
        long separationBetweenPercentages=1;
        long initRepetitions=0;
        long endRepetitions=1;
        if (argc>12){
            initPercentageNodes=atol(argv[12]);
            topPercentageNodes=atol(argv[13]);
            separationBetweenPercentages=atol(argv[14]);
            initRepetitions=atol(argv[15]);
            endRepetitions=atol(argv[16]);
        }
        
        //            nameSS<<Configuration::folder()<<"data/GIS/UK/uk_ncolCoordinates"<<".txt";
        
        std::string name=nameSS.str();
        mainGraph.resetGraph();
        //            mainGraph.numberNodes=0;
        
        //            textFile.parseNCOLWithCoordinates(ncolsTextLines[numClusterTemp],&mainGraph,",");
        
        //            mainGraph.transformToBidirectional();
        
        
        ArchivoTexto textFile;
        
        
        if(modeCalculation==CALCULATE_CENTRALITIES){
            
            bool testing=true;
//            mainGraph.strictlyDirectional=true;
            textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true,true);
            
            //            importPrimalGraph(&mainGraph, name);
            mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
            mainGraph.insertTopologicalWeights();
            
            mainGraph.calculateGlobalProperties=true;
            mainGraph.calculateCentralities=false;
            mainGraph.calculateOtherDistances=false;
            std::stringstream nameWeights;
            nameWeights<<Configuration::folderIn()<<"weightsGreenAreas.txt";
            
            textFile.addWeightsToGraph(&mainGraph, nameWeights.str(), " ", true, Graph::GREEN_AREAS_IMPEDANCE);
            
            nameWeights.str("");
            nameWeights<<Configuration::folderIn()<<"modifierCognitiveDistance.txt";
            
            textFile.addWeightsToGraph(&mainGraph, nameWeights.str(), " ", true, Graph::COGNITIVE);
            
            nameWeights.str("");
            nameWeights<<Configuration::folderIn()<<"weightTimeDistance.txt";
            
            textFile.addWeightsToGraph(&mainGraph, nameWeights.str(), " ", true, Graph::TIME_DISTANCE);
            
            
            
            nameWeights.str("");
            nameWeights<<Configuration::folderIn()<<"pointsDegrees.txt";
            
            
            textFile.includeOriginalDegreeOfNodes(&mainGraph, nameWeights.str(), " ", true);
            
            std::cout<<"graph imported, numberNodes= "<<mainGraph.nodes.size()<<'\n';
            
//                    mainGraph.transformToBidirectional();
//            mainGraph.bidirectional=true;
            
            Graph lineGraph;
            mainGraph.createLineGraphMelbourne(&mainGraph, &lineGraph);
            
            
            std::cout<<"lineGraph generated, numberNodes= "<<lineGraph.nodes.size()<<'\n';
            lineGraph.avoidBacktrackingInLineGraph=true;
            std::vector<double> max;
            //
            for(long j=0;j<lineGraph.nodes.size();j++){
                for(long h=0;h<lineGraph.nodes[j].transitions.size();h++){
                    for(int i=0;i<lineGraph.nodes[j].transitions[h]->otherWeights.size();i++){
                        if(i>=max.size()){
                            max.push_back(lineGraph.nodes[j].transitions[h]->otherWeights[i]);
                        }else{
                            if(max[i]<lineGraph.nodes[j].transitions[h]->otherWeights[i]){
                                max[i]=lineGraph.nodes[j].transitions[h]->otherWeights[i];
                            }
                        }
                    }
                }
            }
            std::cout<<"max. calculated "<<'\n';
            std::vector<Node*> externalNodesTemp;
            std::vector<Transition> originDestinationsPairs;
            
            RTree rTree(RTree::A_STAR);
            
            originDestinationsPairs=rTree.getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&lineGraph);
            
//            originDestinationsPairs.clear();
//            
//            Transition transTmp;
//            transTmp.a=&lineGraph.nodes[572784];
//            transTmp.b=&lineGraph.nodes[1252687];
//            originDestinationsPairs.push_back(transTmp);
            

             if(!testing){
                 lineGraph.calculateDiameter(Graph::METRIC,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
             }
            double originalMetricDiameter=1;
            if(!testing){
                originalMetricDiameter=lineGraph.diameters[lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0]];
            }
            std::cout<<"metric diameter calculated "<<originalMetricDiameter<<'\n';
            
            int firstDistance=lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0];
            int secondDistance=lineGraph.getIndexesOfDistanceType(Graph::COGNITIVE)[0];
            int typeDistanceCombined=Graph::COMBINED_METRIC_COGNITIVE;
            
            for(double alpha=0;alpha<1.05;alpha+=.1){
                lineGraph.pushNewDistance(typeDistanceCombined);
                for(long i=0;i<lineGraph.nodes.size();i++){
                    for(long j=0;j<lineGraph.nodes[i].transitions.size();j++){
                        //                    int indexMetric=lineGraph.getIndexesOfDistanceType(Graph::METRIC)[0];
                        //                    int indexAngular=lineGraph.getIndexesOfDistanceType(Graph::COGNITIVE)[0];
                        //                    int indexCombined=lineGraph.getIndexesOfDistanceType(Graph::COMBINED_METRIC_COGNITIVE)[alpha*10];
                        
                        //
                        double combined=alpha*lineGraph.nodes[i].transitions[j]->otherWeights[firstDistance]/max[firstDistance]+(1-alpha)*lineGraph.nodes[i].transitions[j]->otherWeights[secondDistance]/max[secondDistance];
                        //                    double combined=alpha*lineGraph.nodes[i].transitions[j].otherWeights[firstDistance]+(1-alpha)*lineGraph.nodes[i].transitions[j].otherWeights[secondDistance];
                        lineGraph.nodes[i].transitions[j]->otherWeights.push_back(combined);
                        
                    }
                }
                std::cout<<"combined distance "<<alpha<<". generated "<<'\n';
            }
            if(!testing){
                lineGraph.calculateDiameter(typeDistanceCombined,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                std::cout<<"diameters combined calculated "<<'\n';
                //        for(int i=0;i<14;i++){
                //            std::cout<<"diameters "<<i<<" : "<<lineGraph.diameters[i]<<'\n';
                //        }
                std::vector<double> proportions;
                for(int h=0;h<lineGraph.getIndexesOfDistanceType(typeDistanceCombined).size();h++){
                    proportions.push_back(lineGraph.diameters[lineGraph.getIndexesOfDistanceType(typeDistanceCombined)[h]]/originalMetricDiameter);
                }
            }
            std::cout<<"proportions calculated "<<'\n';
            lineGraph.customize=false;
            nameWeights.str("");
            nameWeights<<Configuration::folderIn()<<"tripsGeneratedByUse.txt";
            if(lineGraph.customize){
             textFile.includeTripsGeneratedByType(&mainGraph,&lineGraph, nameWeights.str(), " ", true);
            }
            
            
            
            
//            textFile.includeValuesToPassBetweenness(&lineGraph, nameWeights.str(), " ", true);
            
            
            
            
            
            //            nameWeights.str("");
            //            nameWeights<<Configuration::folderIn()<<"population.txt";
            //            textFile.includePopulation(&lineGraph, nameWeights.str(), " ", true);
            //            std::cout<<"population included"<<'\n';
            //            for(long i=0;i<lineGraph.nodes.size();i++){
            //                lineGraph.nodes[i].tripsGenerated=lineGraph.nodes[i].population;
            //                lineGraph.nodes[i].tripsReceived=lineGraph.nodes[i].valueToPass;
            //            }
            //            std::cout<<"diameters and max calculated, metric= "<<lineGraph.diameters[lineGraph.getIndexesOfDistanceType(lineGraph.METRIC)[0]]<<" angular= "<<lineGraph.diameters[lineGraph.getIndexesOfDistanceType(lineGraph.ANGULAR)[0]]<<'\n';
            
            
            
            double metricRadius=5000;
            int indexDistanceCutOff=0;
            int indexDistanceCalculation=0;
            double radius;
            if(testing){
                radius=0.20;
//                radius=metricRadius/max[firstDistance];
//                radius=0;
            }else{
                radius=metricRadius*proportions[indexDistanceCutOff];
            }
            //        radius=0;
            std::cout<<"radius "<<radius<<'\n';
            //        int indexAlpha=0;
            long startNode=0;
            long endNode=lineGraph.nodes.size();
            //                long endNode=101;
            int threadNumber=0;
            int indexDistanceInOtherDistancesCutoff=lineGraph.getIndexesOfDistanceType(typeDistanceCombined)[indexDistanceCutOff];
            
            
            int indexDistanceInOtherDistancesCalculation=lineGraph.getIndexesOfDistanceType(typeDistanceCombined)[indexDistanceCalculation];
            //        calculateSubgraphsAndCentralities(&lineGraph,radius,startNode,endNode,threadNumber,indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
            std::vector<int> setOfDistancesToCalculate;
            setOfDistancesToCalculate.push_back(indexDistanceCalculation);
            for(long i=startNode;i<endNode;i++){
                for(long j=0;j<lineGraph.nodes[i].transitions.size();j++){
                    lineGraph.nodes[i].transitions[j]->weight=lineGraph.nodes[i].transitions[j]->otherWeights[indexDistanceInOtherDistancesCutoff];
                }
            }
            lineGraph.indexOfMainDistanceInOtherDistances=indexDistanceInOtherDistancesCutoff;
            
            QTree quadTree;
            lineGraph.insertGraphIntoQTree(&quadTree);
            if(lineGraph.customize){
                
                
                for(long i=startNode;i<endNode;i++){
                    Node* nodeInit=&lineGraph.nodes[i];
                    if(i%1000==0){
                        std::cout<<"preparing trips "<<i*100/(endNode-startNode)<< "%"<<'\n';
                    }
//                    std::cout<<"id of node "<<nodeInit->originalID<<'\n';
                    Customize::prepareGeneratedRoundTrips(&lineGraph,&quadTree,nodeInit, radius);
                }
            }
            
            
            
//            calculateCentralitiesEuclideanCutoff(&lineGraph,&quadTree,metricRadius,startNode,endNode,threadNumber,indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
            calculateCentralities(&lineGraph,radius,startNode,endNode,threadNumber,indexDistanceInOtherDistancesCutoff,indexDistanceInOtherDistancesCalculation);
            
            
            
            std::vector<std::string> values;
            for(long i=0;i<lineGraph.nodes.size();i++){
                std::stringstream strstr;
                Node* nodeTemp=&lineGraph.nodes[i];
                strstr<<nodeTemp->originalID<<" "<<lineGraph.closenessMeasures[lineGraph.getIndexesOfDistanceType(typeDistanceCombined)[indexDistanceCalculation]][nodeTemp->id]<<" "<<lineGraph.betweennessMeasures[lineGraph.getIndexesOfDistanceType(typeDistanceCombined)[indexDistanceCalculation]][nodeTemp->id];
                values.push_back(strstr.str());
            }
            //        ArchivoTexto textFile;
            std::stringstream nameSSFileCalculationCentralities;
            nameSSFileCalculationCentralities<<Configuration::folderOut()<<"calculationCentralitiesMelbourne_"<<typeDistanceCombined<<"_"<<metricRadius<<"_"<<indexDistanceCutOff<<" "<<indexDistanceCalculation<<".txt";
            
            textFile.writeToFile(nameSSFileCalculationCentralities.str(), values, false);
            values.clear();
            
            
            
            
            std::cout<<"centralities calculated "<<'\n';
        }
        if(modeCalculation==CALCULATE_ANGULAR_NETWORK_PERCOLATION)
        {
            textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true,false);
            
            //            importPrimalGraph(&mainGraph, name);
            mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
            mainGraph.insertTopologicalWeights();
            
            mainGraph.calculateGlobalProperties=true;
            mainGraph.calculateCentralities=false;
            mainGraph.calculateOtherDistances=false;
            mainGraph.transformToBidirectional();
            std::cout<<"graph imported, numberNodes= "<<mainGraph.nodes.size()<<'\n';
            Graph lineGraph;
            mainGraph.createLineGraph(&mainGraph, &lineGraph);
            
            
            std::cout<<"lineGraph generated, numberNodes= "<<lineGraph.nodes.size()<<'\n';
            
            for(long i=0;i<lineGraph.nodes.size();i++){
                for(long h=0;h<lineGraph.nodes[i].transitions.size();h++){
                    lineGraph.nodes[i].transitions[h]->weight=lineGraph.nodes[i].transitions[h]->otherWeights[lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
                }
            }
            
            lineGraph.indexOfMainDistanceInOtherDistances=lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0];
            
            std::cout<<"... starting calculation, startDistance: "<<startDistance<<" , endDistance: "<<endDistance<<" , separationBetweendistances: "<<separationBetweenDistances<<'\n';
            for(double i=startDistance; i<endDistance; i+=separationBetweenDistances)
            {
                std::vector<Graph> clusters;
                calculateAngularNetworkPercolation(&lineGraph,clusters,i,true,false,Configuration::folderOut(),minClusterSize);
                //                        calculateNetworkPercolation(<#Graph *graph#>, <#double distanceLimit#>, <#bool saveFilesClusters#>, <#bool returnClusters#>, <#std::string nameFolderForFiles#>, <#long minClusterSizeForSaving#>)
            }
            //                    mainGraph.calculateCentralities=false;
            //                    mainGraph.calculateGlobalProperties=true;
            
            
        }
        if(modeCalculation==ANALYZE_ANGULARPERCOLATION)
        {
            textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true,false);
            //            textFile.parseNCOLWithCoordinates(name, &mainGraph, separatorNCOL, true);
            //            importPrimalGraph(&mainGraph, name);
            mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
            mainGraph.insertTopologicalWeights();
            
            mainGraph.calculateGlobalProperties=true;
            mainGraph.calculateCentralities=false;
            mainGraph.calculateOtherDistances=false;
            mainGraph.transformToBidirectional();
            std::cout<<"graph imported, numberNodes= "<<mainGraph.nodes.size()<<'\n';
            Graph lineGraph;
            mainGraph.createLineGraph(&mainGraph, &lineGraph);
            
            
            std::cout<<"lineGraph generated, numberNodes= "<<lineGraph.nodes.size()<<'\n';
            for(long i=0;i<lineGraph.nodes.size();i++){
                for(long h=0;h<lineGraph.nodes[i].transitions.size();h++){
                    lineGraph.nodes[i].transitions[h]->weight=lineGraph.nodes[i].transitions[h]->otherWeights[lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0]];
                }
            }
            lineGraph.indexOfMainDistanceInOtherDistances=lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0];
            std::cout<<"... preparing nodes"<<'\n';
            std::unordered_map<unsigned long long,Node*> nodesOfLineGraphByOriginalId;
            for(long i=0;i<lineGraph.nodes.size();i++){
                nodesOfLineGraphByOriginalId[lineGraph.nodes[i].originalID]=&(lineGraph.nodes[i]);
            }
            std::cout<<"finished preparing nodes"<<'\n';
            std::cout<<"... starting calculation, startDistance: "<<startDistance<<" , endDistance: "<<endDistance<<" , separationBetweendistances: "<<separationBetweenDistances<<'\n';
            for(double i=startDistance; i<endDistance; i+=separationBetweenDistances)
            {
                std::vector<Graph> clusters;
                calculateAngularNetworkPercolation(&lineGraph,clusters,i,true,true,Configuration::folderOut(),minClusterSize);
                //                calculateAngularNetworkPercolation(<#Graph *graph#>, <#std::vector<Graph> &clusters#>, <#double distanceLimit#>, <#bool saveFilesClusters#>, <#bool returnClusters#>, <#std::string nameFolderForFiles#>, <#long minClusterSizeForSaving#>)
                std::vector<std::string> valuesToRecord;
                std::cout<<"Network percolation finished, threshold "<<i<<" , number of clusters generated: "<<clusters.size()<<'\n';
                for(long j=0;j<clusters.size();j++){
                    //                    double length=0;
                    long massEdges=clusters[j].nodes.size();
                    std::vector<Transition*> transitionsOfCluster;
                    double length=0;
                    for(long h=0;h<clusters[j].nodes.size();h++){
                        Node* node=nodesOfLineGraphByOriginalId[clusters[j].nodes[h].originalID];
                        transitionsOfCluster.push_back(node->transitionThatRepresents);
                        length+=node->transitionThatRepresents->weight;
                    }
                    Graph subGraphOfPrimal;
                    mainGraph.getInducedSubgraph(&subGraphOfPrimal, transitionsOfCluster);
                    //                    std::cout<<"subGraph "<<j<<" / "<<clusters.size()<<" of primal recovered, number of nodes: "<<subGraphOfPrimal.nodes.size()<<'\n';
                    long mass=subGraphOfPrimal.nodes.size();
                    
                    clusters[j].nodes.clear();
                    subGraphOfPrimal.nodes.clear();
                    std::stringstream value;
                    value<<j<<" "<<mass<<" "<<massEdges<<" "<<length;
                    valuesToRecord.push_back(value.str());
                    
                }
                ArchivoTexto textFile;
                std::stringstream nameFile;
                nameFile<<Configuration::folderOut()<<"masses_d"<<i<<".txt";
                textFile.writeToFile(nameFile.str(), valuesToRecord, false);
                
                //                        calculateNetworkPercolation(<#Graph *graph#>, <#double distanceLimit#>, <#bool saveFilesClusters#>, <#bool returnClusters#>, <#std::string nameFolderForFiles#>, <#long minClusterSizeForSaving#>)
            }
            //                    mainGraph.calculateCentralities=false;
            //                    mainGraph.calculateGlobalProperties=true;
            
            
        }
        
    }
    if (formatFile==IMPORT_LINEGRAPH)
    {
        //        std::cout<<"LOADING FILES"<<'\n';
        //        std::vector<double> numberVertex=textFile.parseSimpleNumericFile("/Users/carlos/Documents/data/graphs/meridianDataSetLineGraph/meridianDataSetUKSimplifiedgraphNumberVertex.csv");
        //        std::vector<double> initVertex=textFile.parseSimpleNumericFile("/Users/carlos/Documents/data/graphs/meridianDataSetLineGraph/meridianDataSetUKSimplifiedgraphInitVertex.csv");
        //        std::vector<double> endVertex=textFile.parseSimpleNumericFile("/Users/carlos/Documents/data/graphs/meridianDataSetLineGraph/meridianDataSetUKSimplifiedgraphEndVertex.csv");
        //        std::vector<double> angularWeights=textFile.parseSimpleNumericFile("/Users/carlos/Documents/data/graphs/meridianDataSetLineGraph/meridianDataSetUKSimplifiedangularWeights.csv");
        //        std::vector<double> metricWeights=textFile.parseSimpleNumericFile("/Users/carlos/Documents/data/graphs/meridianDataSetLineGraph/meridianDataSetUKSimplifiedmetricWeights.csv");
        //        std::vector<double> metricLengths=textFile.parseSimpleNumericFile("/Users/carlos/Documents/data/graphs/meridianDataSetLineGraph/meridianDataSetUKSimplifiedmetricLengths.csv");
        //        std::cout<<"GENERATING GRAPH"<<'\n';
        //        double maxAngularDistance=0;
        //        double maxMetricDistance=0;
        //        for (long i=0; i<angularWeights.size(); i++)
        //        {
        //            if (angularWeights[i]>maxAngularDistance)
        //            {
        //                maxAngularDistance=angularWeights[i];
        //            }
        //            if (metricWeights[i]>maxMetricDistance)
        //            {
        //                maxMetricDistance=metricWeights[i];
        //            }
        //        }
        //        for (double indexAlpha=0; indexAlpha<11; indexAlpha++)
        //        {
        //            double alpha=indexAlpha/10;
        //            std::vector<double> combinedWeights;
        //            for (long i=0; i<angularWeights.size(); i++)
        //            {
        //                double combinedDistance=alpha*(angularWeights[i]/maxAngularDistance)+(1-alpha)*(metricWeights[i]/maxMetricDistance);
        //                combinedWeights.push_back(combinedDistance);
        //            }
        //            //		std::cout<<combinedWeights.size();
        //            combinedDistances.push_back(combinedWeights);
        //            //		if (indexAlpha==0||indexAlpha==5||indexAlpha==10){
        //            //        if (indexAlpha!=0&&indexAlpha!=5&&indexAlpha!=10){
        //            //        if (indexAlpha==6){
        //            indexDistancesToCalculate.push_back(indexAlpha);
        //            combinedDistancesToCalculate.push_back(combinedWeights);
        //            //		}
        //        }
        //        setGraph(&mainGraph,numberVertex[0],metricLengths);
        //
        //        for (int i=0; i<numThreads; i++)
        //        {
        //            setGraph(&graphs[i],numberVertex[0],metricLengths);
        //        }
        //
        //
        //
        //        proportions.push_back(.0001501746);
        //        proportions.push_back(.0001506685);
        //        proportions.push_back(.0001476175);
        //        proportions.push_back(.000148044);
        //        proportions.push_back(.0001475307);
        //        proportions.push_back(.0001447458);
        //        proportions.push_back(.0001419608);
        //        proportions.push_back(.0001391759);
        //        proportions.push_back(.0001389397);
        //        proportions.push_back(.0001391831);
        //        proportions.push_back(.0001392159);
        //        for (int indexRadius=0; indexRadius<10; indexRadius++)
        //        {
        //
        //            for (double indexAlpha=0; indexAlpha<11; indexAlpha+=8)
        //            {
        //                double metricRadius=radiiCutoff[indexRadius];
        //                double combinedRadius=metricRadius*proportions[indexAlpha];
        //                double alpha=indexAlpha/10;
        //                //            graph.alpha=alpha;
        //                std::cout<<"alpha "<<alpha<<'\n';
        //                std::cout<<"combinedRadius "<<combinedRadius<<'\n';
        //                std::cout<<"metricRadius "<<metricRadius<<'\n';
        //                std::vector<std::thread> threads;
        //
        //                double numNodesPerThread=floor(mainGraph.nodes.size()/numThreads);
        //                for (int i=0; i<numThreads; i++)
        //                {
        //
        //                    long startNode=i*numNodesPerThread;
        //                    long endNode=(i+1)*numNodesPerThread;
        //                    if (i==numThreads-1)
        //                    {
        //                        endNode=mainGraph.nodes.size();
        //                    }
        //                    //                    threads.push_back(std::thread(calculateSubgraphsFromPercolation,&graphs[i],combinedRadius,indexAlpha,initVertex,endVertex,startNode,endNode,i));
        //                    threads.push_back(std::thread(calculateSubgraphsAndCentralities,&graphs[i],combinedRadius,indexAlpha,initVertex,endVertex,startNode,endNode,i));
        //
        //                }
        //
        //                //    cout<<values.size(); std::cout<<"GENERATING GRAPH"<<'\n';
        //                //    for (int i=0;i<values.size();i++){
        //                //        cout<<"values"<<values[i];
        //                //    }
        //                //ArchivoTexto textFile;
        //
        //                for(auto& thread : threads)
        //                {
        //                    thread.join();
        //                }
        //
        //                //            mainGraph.init();
        //                //            for(int i=0;i<graphs.size();i++){
        //                //                for(int j=0;j<mainGraph.nodes.size();j++){
        //                //                    if (mainGraph.calculateCentralities){
        //                //                        mainGraph.nodeCount[j]+=graphs[i].nodeCount[j];
        //                //                        mainGraph.TSL[j]+=graphs[i].TSL[j];
        //                //                        mainGraph.betweenness[j]+=graphs[i].betweenness[j];
        //                //                        mainGraph.closeness[j]+=graphs[i].closeness[j];
        //                //                        for (int h=0;h<combinedDistancesToCalculate.size();h++){
        //                //                            mainGraph.betweennessMeasures[h][j]+=graphs[i].betweennessMeasures[h][j];
        //                //                            mainGraph.closenessMeasures[h][j]+=graphs[i].closenessMeasures[h][j];
        //                //                        }
        //                //                    }
        //                //                    if (mainGraph.calculateDiffussion){
        //                //                        mainGraph.nodes[j].waterLevel.flow+=graphs[i].nodes[j].waterLevel.flow;
        //                //                    }
        //                //                }
        //                //            }
        //                //            saveFiles(&mainGraph,indexAlpha,metricRadius);
        //
        //            }
        //        }
        //        numberVertex.clear();
        //        initVertex.clear();
        //        endVertex.clear();
        //        angularWeights.clear();
        //        metricWeights.clear();
    }
    else if (formatFile==IMPORT_PRIMALGRAPH_SEVERAL)
    {
        for (int numCluster=1; numCluster<2; numCluster++)
        {
            std::stringstream nameSS;
            nameSS<<Configuration::folder()<<"data/mechanicity/clusteredGraph/ncolWithCoordinates/network_dc100n"<<numCluster<<".txt";
            std::string name=nameSS.str();
            ArchivoTexto textFile;
            mainGraph.resetGraph();
            //            mainGraph.numberNodes=0;
            
            textFile.parseNCOLWithCoordinates(name,&mainGraph," ",false);
            mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
            mainGraph.insertTopologicalWeights();
            mainGraph.transformToBidirectional();
            std::cout<<"Finished parsing cluster"<<'\n';
            if(modeCalculation==CALCULATE_DIAMETER)
            {
                
                
                std::vector<Node*> externalNodesTemp;
                std::vector<Transition> originDestinationsPairs;
                //                if(mainGraph.nodes.size()>250000){
                if(typeOfCalculation==APROX){
                    std::cout<<"Graph too big, using aproximation"<<'\n';
                    std::stringstream aproxSS;
                    aproxSS<<"Aproximation "<<mainGraph.nodes.size()<<" ";
                    
                    timer.start(aproxSS.str());
                    RTree rTree(RTree::A_STAR);
                    originDestinationsPairs=rTree.getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&mainGraph);
                    std::cout<<"Origin Destinations generated"<<'\n';
                    mainGraph.calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::WITH_HEURISTIC,&Graph::metricHeuristic);
                    mainGraph.calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                    timer.stop();
                }else{
                    std::stringstream preciseSS;
                    preciseSS<<"Precise "<<mainGraph.nodes.size()<<" ";
                    timer.start(preciseSS.str());
                    std::cout<<"Calculating using precise dijkstra all to all"<<'\n';
                    mainGraph.calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                    mainGraph.calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                    timer.stop();
                }
                
                
            }
            std::cout<<numCluster<<"/"<<2<<" numNodes "<<mainGraph.nodes.size()<<" diameterMetric: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
            
        }
    }
    else if (formatFile==IMPORT_PRIMALGRAPH_CLUSTERS)
    {
        std::stringstream nameSS;
        //        nameSS<<Configuration::folder()<<"results/clustersFromPercolation/UK/clustersWithCorrectedIDs/clustered_network_dc";
        nameSS<<Configuration::folder()<<"results/angularNetworkPercolation/UK/clustersWithCorrectedIds/clustered_network_dc";
        std::stringstream nameCoordinatesSS;
        nameCoordinatesSS<<Configuration::folder()<<"data/GIS/UK/UK_coordinates.txt";
        std::string separatorClusterFile=",";
        std::string separatorCoordinates=" ";
        long startDistance=5;
        long endDistance=180;
        long minClusterSize=2;
        long separationBetweenDistances=5;
        if (argc>4){
            nameSS.str(std::string());
            nameSS<<Configuration::folderIn()<<argv[5];
            Configuration::setSubFolderCoordinatesFile(argv[4]);
            Configuration::setCoordinatesFileName(argv[6]);
            nameCoordinatesSS.str(std::string());
            nameCoordinatesSS<<Configuration::coordinatesFile();
            separatorClusterFile=argv[7];
            separatorCoordinates=argv[8];
            startDistance=stod(argv[9]);
            endDistance=stod(argv[10]);
            separationBetweenDistances=stod(argv[11]);
            minClusterSize=atol(argv[12]);
        }
        textFile.readCoordinatesNodes(nameCoordinatesSS.str(), separatorCoordinates);
        for(long distanceClustering=startDistance;distanceClustering<endDistance;distanceClustering+=separationBetweenDistances){
            //        long distanceClustering=210;{
            
            std::stringstream nameSS2;
            nameSS2<<nameSS.str()<<distanceClustering<<".txt";
            std::string name=nameSS2.str();
            ArchivoTexto textFile;
            std::vector<std::vector<std::string>> ncolsTextLines=textFile.importFileClusters(name,separatorClusterFile,minClusterSize);
            
            
            
            //            std::priority_queue<std::vector<std::string>,std::vector<std::vector<std::string>>,&compareStringsOfClusters> orderedClustersBySize;
            
            
            
            
            
            
            
            
            
            std::cout<<"START"<<'\n';
            std::vector<std::string> resultsAprox;
            std::vector<std::string> resultsPrecise;
            //        if(timer.getTimes().size()>0)
            //        {
            //        std::cout<<timer.getTimes()[0]<<'\n';
            //            std::stringstream timesSS;
            //            std::stringstream nameTimesSS;
            //            nameTimesSS<<Configuration::folder()<<"results/clustersFromPercolation/clustersWithCorrectedIDs/results_network_dc"<<distanceClustering<<"_times.txt";
            //            std::string name2=nameSS2.str();
            //            timer.saveToFile(name2);
            //        }
            
            if(modeCalculation==CALCULATE_DIAMETER)
            {
                std::stringstream resultsAproxSS;
                resultsAproxSS<<"clusterId"<<" "<<"numNodes"<<" "<<"diameterMetric"<<" "<<"diameterTopological";
                resultsAprox.clear();
                resultsAprox.push_back(resultsAproxSS.str());
                //                }else{
                
                
                
                std::stringstream nameAproxSS;
                nameAproxSS<<Configuration::folderOut()<<"results_diameterCalculationAprox_"<<distanceClustering<<".txt";
                textFile.writeToFile(nameAproxSS.str(), resultsAprox, true);
            }
            
            if(modeCalculation==CALCULATE_K_SHELL_VALUES){
                mainGraph.resetGraph();
                //            mainGraph.numberNodes=0;
                
                textFile.parseNCOLWithCoordinatesAndId(ncolsTextLines[0],&mainGraph,separatorClusterFile);
                mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
                mainGraph.insertTopologicalWeights();
                mainGraph.transformToBidirectional();
                std::cout<<"Finished parsing cluster, numNodes: "<<mainGraph.nodes.size()<<'\n';
                ncolsTextLines.clear();
                
                
                std::vector<Graph> clusters;
                mainGraph.generateSpatialPercolation(&mainGraph, 200, clusters);
                
                Graph simplifiedGraph;
                mainGraph.generateSuperGraphFromClusters(clusters,&mainGraph, &simplifiedGraph);
                
                
                
                
                std::cout<<"network simplified, number of nodes: "<<simplifiedGraph.nodes.size()<<'\n';
                
                
                
                //                simplifiedGraph.createLineGraph(&simplifiedGraph, &lineGraph);
                
                Graph lineGraph;
                simplifiedGraph.createLineGraph(&simplifiedGraph, &lineGraph);
                
                lineGraph.calculateKShellAlgorithm(&lineGraph);
                //                lineGraph.transformToBidirectional();
                
                
                ArchivoTexto textFile;
                //                mainGraph.calculateFractalDimension();
                std::stringstream nameFileSS;
                nameFileSS<<Configuration::folderOut()<<"results_KShellValues"<<distanceClustering<<".txt";
                resultsAprox.clear();
                
                
                
                
                //                ArchivoTexto textFile;
                std::stringstream nameSS1;
                
                //                nameSS1<<Configuration::folderOut()<<"clustered_partial_network_dc"<<distance<<".txt";
                
                std::string name1=nameSS1.str();
                std::vector<std::string> values;
                
                std::stringstream valuesSS1;
                valuesSS1<<"idA"<<" "<<"idB"<<" "<<"weight"<<" xNodeOrigin yNodeOrigin xNodeDestination yNodeDestination kShellValue";
                std::string valuesS1=valuesSS1.str();
                values.push_back(valuesS1);
                for(long j=0; j<simplifiedGraph.nodes.size(); j++){
                    for(long i=0; i<simplifiedGraph.nodes[j].transitions.size(); i++)
                    {
                        //                        if(mainGraph.nodes[j].transitions[i].a->kShellValueFinal>1&&mainGraph.nodes[j].transitions[i].b->kShellValueFinal>1){
                        double kValue=(double)(simplifiedGraph.nodes[j].transitions[i]->nodeOfLineGraphThatRepresentsThis->kShellValueFinal);
                        std::stringstream valuesSS;
                        valuesSS<<simplifiedGraph.nodes[j].transitions[i]->a->originalID<<" "<<simplifiedGraph.nodes[j].transitions[i]->b->originalID<<" "<<simplifiedGraph.nodes[j].transitions[i]->weight<<" "<<simplifiedGraph.nodes[j].transitions[i]->a->location.x<<" "<<simplifiedGraph.nodes[j].transitions[i]->a->location.y<<" "<<simplifiedGraph.nodes[j].transitions[i]->b->location.x<<" "<<simplifiedGraph.nodes[j].transitions[i]->b->location.y<<" "<<kValue;
                        std::string valuesS=valuesSS.str();
                        values.push_back(valuesS);
                        
                        
                        
                        //                    double kValue=(double)(lineGraph.nodes[j].kShellValueFinal);
                        //                    std::stringstream valuesSS;
                        //                    valuesSS<<lineGraph.nodes[j].transitionThatRepresents->a->originalID<<" "<<lineGraph.nodes[j].transitionThatRepresents->b->originalID<<" "<<lineGraph.nodes[j].transitionThatRepresents->weight<<" "<<lineGraph.nodes[j].transitionThatRepresents->a->location.x<<" "<<lineGraph.nodes[j].transitionThatRepresents->a->location.y<<" "<<lineGraph.nodes[j].transitionThatRepresents->b->location.x<<" "<<lineGraph.nodes[j].transitionThatRepresents->b->location.y<<" "<<kValue;
                        //                    std::string valuesS=valuesSS.str();
                        //                    values.push_back(valuesS);
                        //                        }
                        
                    }
                }
                textFile.writeToFile(nameFileSS.str(), values, false);
                
            }
            
            for (int numClusterTemp=0; numClusterTemp<ncolsTextLines.size(); numClusterTemp++)
                
            {
                
                mainGraph.resetGraph();
                //            mainGraph.numberNodes=0;
                
                textFile.parseNCOLWithCoordinatesAndId(ncolsTextLines[numClusterTemp],&mainGraph,separatorClusterFile);
                mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
                mainGraph.insertTopologicalWeights();
                mainGraph.transformToBidirectional();
                std::cout<<"Finished parsing cluster, numNodes: "<<mainGraph.nodes.size()<<'\n';
                
                if (modeCalculation==CALCULATE_FRACTAL_DIMENSION){
                    ArchivoTexto textFile;
                    mainGraph.calculateFractalDimension();
                    std::stringstream nameFileSS;
                    nameFileSS<<Configuration::folderOut()<<"results_FractalDimension_Renormalization"<<distanceClustering<<".txt";
                    resultsAprox.clear();
                    std::stringstream resultSS;
                    resultSS<<mainGraph.nodes.size()<<" "<<mainGraph.fractalDimension;
                    resultsAprox.push_back(resultSS.str());
                    textFile.writeToFile(nameFileSS.str(), resultsAprox, true);
                    //                    std::cout<<resultSS.str();
                }
                
                if(modeCalculation==CALCULATE_DIAMETER)
                {
                    if(mainGraph.nodes.size()>minClusterSize){
                        std::vector<std::string> times;
                        std::vector<Node*> externalNodesTemp;
                        std::vector<Transition> originDestinationsPairs;
                        ArchivoTexto textFileAprox;
                        ArchivoTexto textFilePrecise;
                        //                if(mainGraph.nodes.size()>250000){
                        //                if(true){
                        //                std::cout<<"Graph too big, using aproximation"<<'\n';
                        
                        
                        if(typeOfCalculation==APROX){
                            
                            std::stringstream aproxSS;
                            aproxSS<<"Aproximation "<<mainGraph.nodes.size()<<" ";
                            
                            timer.start(aproxSS.str());
                            RTree rTree(RTree::A_STAR);
                            originDestinationsPairs=rTree.getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&mainGraph);
                            //                std::cout<<"Origin Destinations generated"<<'\n';
                            mainGraph.calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            mainGraph.calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            //                mainGraph.calculateDiameter(<#int typeOfDistance#>, <#bool parallel#>, <#bool calculateCentralitiesSimultaneously#>, <#bool precise#>, <#std::vector<Node *> &externalNodes#>, <#std::vector<Transition> &originDestinationPairs#>, <#bool withHeuristic#>, <#double (*function)(Node *, Node *)#>)
                           timer.stop();
                            //                        if(timer.active){
                            //                            times.clear();
                            //                            times.push_back(time);
                            //                            textFile.writeToFile(nameTimesSS.str(), times, true);
                            //                        }
                            std::stringstream resultsAproxSS;
                            resultsAproxSS<<(numClusterTemp+1)<<" "<<mainGraph.nodes.size()<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                            resultsAprox.clear();
                            resultsAprox.push_back(resultsAproxSS.str());
                            //                }else{
                            
                            
                            std::stringstream nameAproxSS;
                            nameAproxSS<<Configuration::folderOut()<<"results_diameterCalculationAprox_"<<distanceClustering<<".txt";
                            textFileAprox.writeToFile(nameAproxSS.str(), resultsAprox, true);
                            
                            std::cout<<"Aprox "<<(numClusterTemp+1)<<"/"<<ncolsTextLines.size()<<" numNodes "<<mainGraph.nodes.size()<<" diameterMetric: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
                        }
                        
                        if(typeOfCalculation==PRECISE){
                            
                            
                            std::stringstream preciseSS;
                            preciseSS<<"Precise "<<mainGraph.nodes.size()<<" ";
                            timer.start(preciseSS.str());
                            //                std::cout<<"Calculating using precise dijkstra all to all"<<'\n';
                            mainGraph.calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            mainGraph.calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            timer.stop();
                            //                        if(timer.active){
                            //                            times.clear();
                            //                            times.push_back(time);
                            //                            textFile.writeToFile(nameTimesSS.str(), times, true);
                            //                        }
                            std::stringstream resultsPreciseSS;
                            resultsPreciseSS<<numClusterTemp<<" "<<mainGraph.nodes.size()<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                            resultsPrecise.clear();
                            resultsPrecise.push_back(resultsPreciseSS.str());
                            std::stringstream namePreciseSS;
                            namePreciseSS<<Configuration::folderOut()<<"results_diameterCalculationPrecise_"<<distanceClustering<<".txt";
                            textFilePrecise.writeToFile(namePreciseSS.str(), resultsPrecise, true);
                            //                }
                            
                            std::cout<<"Precise "<<numClusterTemp<<"/"<<ncolsTextLines.size()<<" numNodes "<<mainGraph.nodes.size()<<" diameterMetric: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
                        }
                    }
                }
                
                
                if(modeCalculation==CALCULATE_DIAMETER_TEST)
                {
                    if(mainGraph.nodes.size()>minClusterSize){
                        std::vector<std::string> times;
                        std::vector<Node*> externalNodesTemp;
                        std::vector<Transition> originDestinationsPairs;
                        ArchivoTexto textFileAprox;
                        ArchivoTexto textFilePrecise;
                        //                if(mainGraph.nodes.size()>250000){
                        //                if(true){
                        //                std::cout<<"Graph too big, using aproximation"<<'\n';
                        
                        
                        if(typeOfCalculation==APROX){
                            
                            std::stringstream aproxSS;
                            aproxSS<<"Aproximation "<<mainGraph.nodes.size()<<" ";
                            
                            timer.start(aproxSS.str());
                            RTree rTree(RTree::A_STAR);
                            originDestinationsPairs=rTree.getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&mainGraph);
                            //                std::cout<<"Origin Destinations generated"<<'\n';
                            mainGraph.calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            double diameterInParallel=mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]];
                            mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
                            mainGraph.calculateDiameter(Graph::METRIC,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            double diameterInSerial=mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]];
                            //                            mainGraph.calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            //                mainGraph.calculateDiameter(<#int typeOfDistance#>, <#bool parallel#>, <#bool calculateCentralitiesSimultaneously#>, <#bool precise#>, <#std::vector<Node *> &externalNodes#>, <#std::vector<Transition> &originDestinationPairs#>, <#bool withHeuristic#>, <#double (*function)(Node *, Node *)#>)
                            timer.stop();
                            //                        if(timer.active){
                            //                            times.clear();
                            //                            times.push_back(time);
                            //                            textFile.writeToFile(nameTimesSS.str(), times, true);
                            //                        }
                            std::stringstream resultsAproxSS;
                            resultsAproxSS<<mainGraph.id<<" "<<mainGraph.nodes.size()<<" "<<diameterInParallel<<" "<<diameterInSerial;
                            std::cout<<"Comparison between parallel and serial "<<diameterInParallel<<" "<<diameterInSerial<<'\n';
                            resultsAprox.clear();
                            resultsAprox.push_back(resultsAproxSS.str());
                            //                }else{
                            
                            
                            std::stringstream nameAproxSS;
                            nameAproxSS<<Configuration::folderOut()<<"results_diameterCalculationAprox_Test"<<distanceClustering<<".txt";
                            textFileAprox.writeToFile(nameAproxSS.str(), resultsAprox, true);
                            
                            std::cout<<"Aprox "<<mainGraph.id<<"/"<<ncolsTextLines.size()<<" numNodes "<<mainGraph.nodes.size()<<" diameterMetric: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
                        }
                        
                        if(typeOfCalculation==PRECISE){
                            
                            
                            //                            std::stringstream preciseSS;
                            //                            preciseSS<<"Precise "<<mainGraph.nodes.size()<<" ";
                            //                            timer.start(preciseSS.str());
                            //                            //                std::cout<<"Calculating using precise dijkstra all to all"<<'\n';
                            //                            mainGraph.calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            //                            mainGraph.calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                            //                            std::string time=timer.stop();
                            //                            //                        if(timer.active){
                            //                            //                            times.clear();
                            //                            //                            times.push_back(time);
                            //                            //                            textFile.writeToFile(nameTimesSS.str(), times, true);
                            //                            //                        }
                            //                            std::stringstream resultsPreciseSS;
                            //                            resultsPreciseSS<<numClusterTemp<<" "<<mainGraph.nodes.size()<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                            //                            resultsPrecise.clear();
                            //                            resultsPrecise.push_back(resultsPreciseSS.str());
                            //                            std::stringstream namePreciseSS;
                            //                            namePreciseSS<<Configuration::folderOut()<<"results_diameterCalculationPrecise_"<<distanceClustering<<".txt";
                            //                            textFilePrecise.writeToFile(namePreciseSS.str(), resultsPrecise, true);
                            //                            //                }
                            //
                            //                            std::cout<<"Precise "<<numClusterTemp<<"/"<<ncolsTextLines.size()<<" numNodes "<<mainGraph.nodes.size()<<" diameterMetric: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
                        }
                    }
                }
                
                
                
                else if (modeCalculation==CALCULATE_QTREE)
                {
                    std::stringstream nameTimesSS;
                    nameTimesSS<<Configuration::folder()<<"results/clustersFromPercolation/results_network_dc"<<distanceClustering<<"_timesQTree.txt";
                    //            int start = getMilliCount();
                    timer.start("QTree");
                    RTree rTree(RTree::TREE_DISTANCE);
                    
                    //                    originDestinationPairs.clear();
                    //                    rTree.mainCluster.
                    rTree.generateCornersOfMainCluster(&mainGraph);
                    //                    std::cout<<"QTree created"<<'\n';
                    for(int i=0; i<mainGraph.nodes.size(); i++)
                    {
                        Node* node=&(mainGraph.nodes[i]);
                        rTree.mainCluster.addNode(node);
                    }
                    //                    std::cout<<"nodes added"<<'\n';
                    
                    
                    
                    
                    std::vector<Transition> originDestinationPairs;
                    //
                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    //            std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    //
                    //            for(long i=0; i<clustersExternalLeaves.size(); i++)
                    //            {
                    //                for(long j=0; j<clustersExternalLeaves.size(); j++)
                    //                {
                    //                    if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
                    //                    {
                    //                        Transition trans;
                    //                        trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                    //                        trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                    //                        originDestinationPairs.push_back(trans);
                    //                    }
                    //
                    //                }
                    //            }
                    
                    
                    
                    //TODO turn this on if you want it to work
                    //                    rTree.generateRTreeGraph(mainGraph,originDestinationPairs);
                    
                    
                    
                    
                    //                    std::cout<<"extended graph generated"<<'\n';
                    
                    //                    long i=10;
                    
                    
                    
                    
                    
                    
                    //                    for(long i=0;i<mainGraph.nodes.size();i++){
                    //                        for(long j=0;j<mainGraph.nodes.size();j++){
                    //                            if (i!=j){
                    //                                Node& a=mainGraph.nodes[i];
                    //                                Node& b=mainGraph.nodes[j];
                    //                                ClusterRTree* clusterCommonLevel=rTree.getCommonLevelOfTwoNodes(&a, &b);
                    //                                double distance=rTree.AStar(&a,&b);
                    ////                                if (distance>=4195){
                    //                                    std::cout<<distance<<", "<<clusterCommonLevel->depth<<" "<<a.originalID<<" "<<b.originalID<<'\n';
                    ////                                }
                    //                                if (distance>mainGraph.diameterWeighted){
                    //                                    mainGraph.diameterWeighted=distance;
                    //                                }
                    //                            }
                    //                        }
                    //                    }
                    //                    std::cout<<"AStar calculated"<<'\n';
                    
                    
                    //            std::vector<double> distances=rTree.calculateDistances(originDestinationPairs);
                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=rTree.calculateAllToAllDistances();
                    //            mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
                    //
                    //            for(long i=0; i<distances.size(); i++)
                    //            {
                    //                //                            std::cout<<"distances "<<distances[i]<<" < "<<mainGraph.diameterWeighted<<'\n';
                    //                if(mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<distances[i]&&distances[i]<INFINITY)
                    //                {
                    //                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=distances[i];
                    //                }
                    //            }
                    std::stringstream resultsPreciseSS;
                    resultsPreciseSS<<numClusterTemp<<" "<<mainGraph.nodes.size()<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    resultsPrecise.clear();
                    resultsPrecise.push_back(resultsPreciseSS.str());
                    std::stringstream namePreciseSS;
                    namePreciseSS<<Configuration::folder()<<"results/clustersFromPercolation/results_valuesPrecise_"<<distanceClustering<<"QTree.txt";
                    ArchivoTexto textFilePrecise;
                    textFilePrecise.writeToFile(namePreciseSS.str(), resultsPrecise, true);
                    
                    //                    mainGraph.diameterWeighted=rTree.calculateDiameter();
                    
                    
                    //                    mainGraph.diameterWeighted=rTree.calculateAllToAllDistances();
                    //            milliSecondsElapsed = getMilliSpan(start);
                    
                    
                    
                    
                    //                    timesSS<<mainGraph.nodes.size()<<" "<<milliSecondsElapsed<<'\n';
                    
                    //                    std::string timeCalculation=timesSS.str();
                    //                    std::vector<std::string> times;
                    //                    times.push_back(timeCalculation);
                    //                    textFile.writeToFile("/Users/carlos/Documents/results/results_network_dc100_times.txt", times, true);
                    
                    timer.stop();
                    std::vector<std::string> times;
                    times.clear();
//                    times.push_back(time);
                    textFile.writeToFile(nameTimesSS.str(), times, true);
                    //            if(rTree.mainCluster.timer.active)
                    //            {
                    //                ArchivoTexto textFile;
                    //                std::stringstream nameSS;
                    //                nameSS<<Configuration::folder()<<"results/individual_times.txt";
                    //                std::string name=nameSS.str();
                    //                textFile.writeToFile(name, rTree.mainCluster.timer.getTimes(), true);
                    //                //                        textFile.writeToFile("C:/Users/Carlos/Documents/_TRABAJO/CASA/results/individual_times.txt", rTree.mainCluster.timer.getTimes(), true);
                    //            }
                    
                    //                    std:cout<<"diameter calculated "<<mainGraph.diameterWeighted<<'\n';
                    //                    rTree.mainCluster.sons.clear();
                    //                    rTree.mainCluster.originalGraph->nodes.clear();
                    //                    rTree.mainCluster.graph.nodes.clear();
                    ////                    rTree.mainCluster.graph.
                    //                    rTree.mainCluster.graphTemp.nodes.clear();
                    //                    rTree.mainCluster.clustersByDepth.clear();
                    
                    //                    mainGraph.init();
                    
                    std::cout<<"diameter calculated"<<'\n';
                }
            }
        }
        
        std::cout<<"END"<<'\n';
        
    }
    else if (formatFile==IMPORT_PRIMALGRAPH_SINGLE)
    {
        
        //                std::string folder="/Users/carlos/Documents/";
        //        for (int numCluster=373; numCluster<374; numCluster++)
        int numCluster=0;
        
        {
            //London 373
            std::stringstream nameSS,nameCoordinatesSS;
            //            nameSS<<"/Users/cavargasru/Documents/mechanicity/erez/networks/n0600/network_dc100n"<<numCluster<<".txt";
            //            nameSS<<"/Users/carlos/Documents/data/mechanicity/EU/n0600/network_dc310n"<<numCluster<<".txt";
            //            nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/network_dc100n"<<numCluster<<".txt";
            //            nameSS<<"/Users/carlos/Documents/data/mechanicity/clusteredGraph/ncolWithCoordinates/exampleGraph.txt";
            //            nameSS<<folder<<"data/mechanicity/EU/n0600/network_dc280n"<<numCluster<<".txt";
            std::string separatorNCOL=" ";
            std::string separatorCoordinates=" ";
            long startDistance=1;
            long endDistance=450;
            long minClusterSize=50;
            long separationBetweenDistances=1;
            
            if (argc>4){
                //                std::cout<<argv[4];
                nameSS<<Configuration::folderIn()<<argv[4];
                nameCoordinatesSS<<Configuration::folderIn()<<argv[5];
                separatorNCOL=argv[6];
                separatorCoordinates=argv[7];
                startDistance=stod(argv[8]);
                endDistance=stod(argv[9]);
                separationBetweenDistances=stod(argv[10]);
                minClusterSize=atol(argv[11]);
            }else{
                
//                nameSS<<Configuration::folderIn()<<"melbourneNCOLPure"<<".txt";
//                nameCoordinatesSS<<Configuration::folderIn()<<"pointsFinal"<<".txt";
                
//                nameSS<<Configuration::folderIn()<<"cities/londonNCOL"<<".txt";
//                                                nameCoordinatesSS<<Configuration::folderIn()<<"cities/londonCoordinates.txt";
                
//                                nameSS<<Configuration::folderIn()<<"UK_ncol"<<".txt";
//                                nameCoordinatesSS<<Configuration::folderIn()<<"UK_coordinates"<<".txt";
                
                nameSS<<Configuration::folderIn()<<"EU_ncol"<<".txt";
                                                nameCoordinatesSS<<Configuration::folderIn()<<"eu_coordinates"<<".txt";
                
                
//                nameSS<<"/Users/carlos/Documents/results/angularNetworkPercolation/UK/clustersWithCorrectedIds/ncolGiantCluster60.txt";
//                nameCoordinatesSS<<"/Users/carlos/Documents/results/angularNetworkPercolation/UK/clustersWithCorrectedIds/coordinatesGianCluster60.txt";
            }
            float initPercentageNodes=10;
            float topPercentageNodes=15;
            long separationBetweenPercentages=10;
            long initRepetitions=0;
            long endRepetitions=1;
            if (argc>12){
                initPercentageNodes=atol(argv[12]);
                topPercentageNodes=atol(argv[13]);
                separationBetweenPercentages=atol(argv[14]);
                initRepetitions=atol(argv[15]);
                endRepetitions=atol(argv[16]);
            }
            
            //            nameSS<<Configuration::folder()<<"data/GIS/UK/uk_ncolCoordinates"<<".txt";
            
            std::string name=nameSS.str();
            mainGraph.resetGraph();
            //            mainGraph.numberNodes=0;
            
            //            textFile.parseNCOLWithCoordinates(ncolsTextLines[numClusterTemp],&mainGraph,",");
            
            //            mainGraph.transformToBidirectional();
            
            
            ArchivoTexto textFile;
            
            
            //                    double numNodesPerThread=floor(mainGraph.nodes.size()/numThreads);
            //                    for (int i=0;i<numThreads;i++){
            //
            //                        long startNode=i*numNodesPerThread;
            //                        long endNode=(i+1)*numNodesPerThread;
            //                        if (i==numThreads-1){
            //                            endNode=mainGraph.nodes.size();
            //                        }
            //    //                    threads.push_back(std::thread(calculateGraphFromCluster,&graphs[i],combinedRadius,startNode,endNode,i));
            //                        threads.push_back(std::thread(calculateGraphFromCluster,&graphs[i],0,startNode,endNode,i));
            //
            //                    }
            //                RTree rTree;
            //                rTree.generateCornersOfMainCluster(mainGraph);
            //                std::cout<<"QTree created"<<'\n';
            //                for(int i=0;i<mainGraph.nodes.size();i++){
            //                    Node* node=&(mainGraph.nodes[i]);
            //                    rTree.mainCluster.addNode(node);
            //                }
            //                std::cout<<"nodes added"<<'\n';
            //                rTree.generateRTreeGraph(graphs[0]);
            //                std::cout<<"extended graph generated"<<'\n';
            
            
            //                for(long i=0;i<mainGraph.nodes.size();i++){
            //                    for(long j=0;j<mainGraph.nodes.size();j++){
            //                        if (i!=j){
            //                            Node* a=&mainGraph.nodes[i];
            //                            Node* b=&mainGraph.nodes[j];
            //                            ClusterRTree* clusterCommonLevel=rTree.getCommonLevelOfTwoNodes(a, b);
            //                            rTree.AStar(a,b,clusterCommonLevel);
            //                            std::cout<<b->minDistance<<", ";
            //                            if (b->minDistance>mainGraph.diameterWeighted){
            //                                mainGraph.diameterWeighted=b->minDistance;
            //                            }
            //                        }
            //
            //                    }
            
            //                }
            //                std::cout<<"AStar calculated"<<'\n';
            int milliSecondsElapsed=0;
            
            if(modeCalculation==SIMPLIFY_GRAPH){
                textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true, true);
                std::vector<Graph> clusters;
                mainGraph.generateSpatialPercolation(&mainGraph, 25, clusters);
                //                    mainGraph.calculateClusterUsingNetworkPercolation(25, clusters, false, true, "", 1);
                Graph simplifiedGraph;
                mainGraph.generateSuperGraphFromClusters(clusters,&mainGraph, &simplifiedGraph);
                ArchivoTexto textFile;
                std::stringstream nameFile;
                nameFile<<Configuration::folderOut()<<"simplifiedGraph.txt";
                textFile.writeNCOLPlusCoordinatesFile(&simplifiedGraph, nameFile.str());
                std::vector<std::string> collapsedNodes;
                std::vector<std::string> collapsedTransitions;
                std::vector<std::string> collapsedTransitionsInNodes;
                for(long i=0;i<simplifiedGraph.nodes.size();i++){
                    for(long j=0;j<simplifiedGraph.nodes[i].nodesCollapsed.size();j++){
                        std::stringstream line;
                        line<<simplifiedGraph.nodes[i].originalID<<" "<<simplifiedGraph.nodes[i].nodesCollapsed[j]->originalID;
                        collapsedNodes.push_back(line.str());
                    }
                    for(long j=0;j<simplifiedGraph.nodes[i].transitionsCollapsedIntoNode.size();j++){
                        std::stringstream line;
                        line<<simplifiedGraph.nodes[i].originalID<<" "<<simplifiedGraph.nodes[i].transitionsCollapsedIntoNode[j]->originalID;
                        collapsedTransitionsInNodes.push_back(line.str());
                    }
                    for(long j=0;j<simplifiedGraph.nodes[i].transitions.size();j++){
                        for(long h=0;h<simplifiedGraph.nodes[i].transitions[j]->transitionsCollapsed.size();h++){
                            std::stringstream line;
                            line<<simplifiedGraph.nodes[i].transitions[j]->originalID<<" "<<simplifiedGraph.nodes[i].transitions[j]->transitionsCollapsed[h]->originalID;
                            collapsedTransitions.push_back(line.str());
                        }
                    }
                }
                nameFile.str("");
                nameFile<<Configuration::folderOut()<<"collapsedNodes.txt";
                textFile.writeToFile(nameFile.str(), collapsedNodes, false);
                
                nameFile.str("");
                nameFile<<Configuration::folderOut()<<"collapsedTransitions.txt";
                textFile.writeToFile(nameFile.str(), collapsedTransitions, false);
                
                nameFile.str("");
                nameFile<<Configuration::folderOut()<<"collapsedTransitionsIntoNodes.txt";
                textFile.writeToFile(nameFile.str(), collapsedTransitionsInNodes, false);
            }else{
                textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true,false);
                
                //            importPrimalGraph(&mainGraph, name);
                mainGraph.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
                mainGraph.insertTopologicalWeights();
                
                mainGraph.calculateGlobalProperties=true;
                mainGraph.calculateCentralities=false;
                mainGraph.calculateOtherDistances=false;
                //        for (double indexAlpha=0;indexAlpha<11;indexAlpha++){
                //            double alpha=indexAlpha/10;
                //            std::vector<double> combinedWeights;
                //            for (long i=0;i<angularWeights.size();i++){
                //                double combinedDistance=alpha*(angularWeights[i]/maxAngularDistance)+(1-alpha)*(metricWeights[i]/maxMetricDistance);
                //            std::vector<double> combinedWeights;
                //            combinedWeights.resize(mainGraph.nodes.size(),1);
                //            }
                //		std::cout<<combinedWeights.size();
                //            combinedDistances.push_back(combinedWeights);
                //		if (indexAlpha==0||indexAlpha==5||indexAlpha==10){
                //        if (indexAlpha!=0&&indexAlpha!=5&&indexAlpha!=10){
                //        if (indexAlpha==6){
                //            indexDistancesToCalculate.push_back(indexAlpha);
                //            combinedDistancesToCalculate.push_back(combinedWeights);
                //		}
                //        }
                mainGraph.transformToBidirectional();
                std::cout<<"graph imported, numberNodes= "<<mainGraph.nodes.size()<<'\n';
                if(parallel)
                {
                    for (int i=0; i<numThreads; i++)
                    {
                        graphs[i].nodes.clear();
                        copyGraph(&mainGraph,&graphs[i]);
                        
                        
                    }
                    std::cout<<"graph copied"<<'\n';
                }
                
                for (int i=0; i<numThreads; i++)
                {
                    graphs[i].calculateGlobalProperties=true;
                    graphs[i].calculateCentralities=false;
                    graphs[i].calculateOtherDistances=false;
                    
                    
                }
                
                
                proportions.push_back(1);
                for (int indexRadius=0; indexRadius<1; indexRadius++)
                {
                    
                    
                    std::vector<std::thread> threads;
                }
                if (modeCalculation==GENERATE_TREE_FROM_CLUSTERS){
                    
//                    textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true, false);
//                    mainGraph.transformToBidirectional();
                    //                std::unordered_map<signed long long,long> previousCluster;
                    std::unordered_map<signed long long,long> currentCluster;
                    std::vector<std::string> ncolPairs;
                    std::vector<std::string> masses;
                    std::vector<std::vector<signed long long> > nodesBelongingToClusters;
                    std::unordered_map<signed long long,long> nodesByOriginalId;
                    
//                    for(long i=0;i<mainGraph.nodes.size();i++){
//                        std::vector<long long> pair;
//                        pair.push_back(mainGraph.nodes[i].originalID);
//                        pair.push_back(-1);
//                        nodesBelongingToClusters.push_back(pair);
//                        nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
//                    }
//                    
//                    
//                    //
//                    long uniqueId=0;
//                    for(int distance=50;distance<=5000;distance+=50){
//                        //                    std::unordered_map<long,signed long long> correspondancesBetweenRealIdsAndUniqueIds;
//                        std::vector<Graph> clusters;
//                        mainGraph.calculateClusterUsingNetworkPercolation(distance, clusters, false, true, "", 75);
//                        
//                        //                    std::vector<std::string> masses;
//                        
//                        
//                        for (long i=0;i<clusters.size();i++){
//                            
//                            clusters[i].id=uniqueId;
//                            std::stringstream mass;
//                            mass<<distance<<" "<<uniqueId<<" "<<clusters[i].nodes.size();
//                            masses.push_back(mass.str());
//                            uniqueId++;
//                            for(long j=0;j<clusters[i].nodes.size();j++){
//                                long index=nodesByOriginalId[clusters[i].nodes[j].originalID];
//                                long value=nodesBelongingToClusters[index][1];
//                                if(value==-1){
//                                    nodesBelongingToClusters[index][1]=clusters[i].id;
//                                }
//                                if(currentCluster[clusters[i].nodes[j].originalID]!=0){
//                                    std::stringstream pair;
//                                    pair<<(clusters[i].id)<<" "<<(currentCluster[clusters[i].nodes[j].originalID]-1)<<" "<<"1";
//                                    ncolPairs.push_back(pair.str());
//                                    currentCluster[clusters[i].nodes[j].originalID]=0;
//                                    
//                                }
//                                
//                            }
//                            
//                        }
//                        for (long i=0;i<clusters.size();i++){
//                            
//                            currentCluster[clusters[i].nodes[0].originalID]=clusters[i].id+1;
//                            
//                        }
//                        
//                    }
//                    std::vector<std::string> belongingOfNodes;
//                    for(long i=0;i<nodesBelongingToClusters.size();i++){
//                        std::stringstream value;
//                        value<<nodesBelongingToClusters[i][0]<<" "<<nodesBelongingToClusters[i][1];
//                        belongingOfNodes.push_back(value.str());
//                    }
//                    std::stringstream textFileOut;
//                    textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
//                    textFile.writeToFile(textFileOut.str(), ncolPairs, false);
//                    textFileOut.str("");
//                    textFileOut<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
//                    textFile.writeToFile(textFileOut.str(), masses, false);
//                    textFileOut.str("");
//                    textFileOut<<Configuration::folderOut()<<"clusterOfEachNode.txt";
//                    textFile.writeToFile(textFileOut.str(), belongingOfNodes, false);
                    bool generateTree=false;
                    std::unordered_map<long,long> massesOfClustersByOriginalId;
                    if(generateTree){
                        
                        for(long i=0;i<mainGraph.nodes.size();i++){
                            std::vector<signed long long> pair;
                            pair.push_back(mainGraph.nodes[i].originalID);
                            pair.push_back(-1);
                            nodesBelongingToClusters.push_back(pair);
                            nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
                        }
                        
                        long uniqueId=0;
                        
                        std::vector<long> setOfDistances;
                        for(long distance=50;distance<=5000;distance+=50){
                            setOfDistances.push_back(distance);
                        }
//                        setOfDistances.push_back(3550);
//                        setOfDistances.push_back(3600);
//                        setOfDistances.push_back(3650);
//                        setOfDistances.push_back(3700);
//                                                setOfDistances.push_back(4600);
//                                                setOfDistances.push_back(4650);
//                                                setOfDistances.push_back(4800);
//                                                setOfDistances.push_back(4850);
//                                                setOfDistances.push_back(5000);
                        
                        
                        for(long proxyDistance=0;proxyDistance<setOfDistances.size();proxyDistance++){
                            long distance=setOfDistances[proxyDistance];
                            //                    std::unordered_map<long,signed long long> correspondancesBetweenRealIdsAndUniqueIds;
                            std::vector<Graph> clusters;
                            mainGraph.calculateClusterUsingNetworkPercolation(distance, clusters, false, true, "", 50);
                            
                            //                    std::vector<std::string> masses;
                            
                            
                            for (long i=0;i<clusters.size();i++){
                                
                                clusters[i].id=uniqueId;
                                std::stringstream mass;
                                mass<<distance<<" "<<uniqueId<<" "<<clusters[i].nodes.size();
                                massesOfClustersByOriginalId[uniqueId]=clusters[i].nodes.size();
                                masses.push_back(mass.str());
                                uniqueId++;
                                for(long j=0;j<clusters[i].nodes.size();j++){
                                    long index=nodesByOriginalId[clusters[i].nodes[j].originalID];
                                    long value=nodesBelongingToClusters[index][1];
                                    if(value==-1){
                                        nodesBelongingToClusters[index][1]=clusters[i].id;
                                    }
                                    if(currentCluster[clusters[i].nodes[j].originalID]!=0){
                                        std::stringstream pair;
                                        pair<<(clusters[i].id)<<" "<<(currentCluster[clusters[i].nodes[j].originalID]-1)<<" "<<"1";
                                        ncolPairs.push_back(pair.str());
                                        currentCluster[clusters[i].nodes[j].originalID]=0;
                                        
                                    }
                                    
                                }
                                
                            }
                            for (long i=0;i<clusters.size();i++){
                                
                                currentCluster[clusters[i].nodes[0].originalID]=clusters[i].id+1;
                                
                            }
                            
                        }
                        std::vector<std::string> belongingOfNodes;
                        for(long i=0;i<nodesBelongingToClusters.size();i++){
                            std::stringstream value;
                            value<<nodesBelongingToClusters[i][0]<<" "<<nodesBelongingToClusters[i][1];
                            belongingOfNodes.push_back(value.str());
                        }
                        std::stringstream textFileOut;
                        textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
                        textFile.writeToFile(textFileOut.str(), ncolPairs, false);
                        textFileOut.str("");
                        textFileOut<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
                        textFile.writeToFile(textFileOut.str(), masses, false);
                        textFileOut.str("");
                        textFileOut<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                        textFile.writeToFile(textFileOut.str(), belongingOfNodes, false);
                    }else{
                        std::stringstream fileName;
                        fileName<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                        textFile.loadPairsFileOfNodeIdAndClusterId(nodesBelongingToClusters, fileName.str(), " ", false);
                        for(long i=0;i<mainGraph.nodes.size();i++){
                            nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
                        }
                        fileName.str("");
                        fileName<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
                        textFile.loadMassesPercolation(&massesOfClustersByOriginalId, fileName.str(), " ", false);

                        
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
//                }
//                if(modeCalculation==CREATE_COORDINATES_FROM_TREE){
                    
                    Graph tree;
                    std::stringstream textFileOut;
                    textFileOut.str("");
                    textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
                    textFile.parseNCOL(textFileOut.str(), &tree, " ", false);
                    
                    
                    Graph giantComponent;
                    tree.getGiantComponent(&tree, &giantComponent);
                    Node* root=NULL;
                    for(long i=0;i<giantComponent.nodes.size();i++){
                        if(giantComponent.nodes[i].nodesThatReachMe.size()==0){
                            root=&(giantComponent.nodes[i]);
                        }
                    }
                    
                        std::vector<Node*> nodesCutoff;
                        Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//                        Node* nodeTemp=root;
                        root->minDistance=0;
                        nodesCutoff.push_back(root);
                        
                        nodesToCheckDijkstra.push(root);
                        
                        giantComponent.calculateDijkstraSpeed(root, 0, nodesCutoff,nodesToCheckDijkstra);
                        long maxDepth=0;
                        for(long i=0;i<giantComponent.nodes.size();i++){
                            if(maxDepth<giantComponent.nodes[i].minDistance){
                                maxDepth=giantComponent.nodes[i].minDistance;
                            }
                        }
//                    std::vector<long> wTnodeInit;
//                    std::vector<long> wTnodeEnd;
//                    std::vector<double> wTweight;
                    
                        for(long i=0;i<giantComponent.nodes.size();i++){
                            Node* currentNode=&(giantComponent.nodes[i]);
//                            double delta=0.00001;
                            while(currentNode->parent!=NULL){
//                                long idParent=currentNode->parent->originalID;
//                                long idCluster=currentNode->originalID;
//                                long massParent=massesOfClustersByOriginalId[idParent];
//                                long massCluster=massesOfClustersByOriginalId[idCluster];
                                double topoWeight=(log(maxDepth-giantComponent.nodes[i].minDistance+1)/log(maxDepth+1));
                                topoWeight=0;
//                                double weight=(1-(double)(massCluster)/(double)(massParent))*(double)(log(maxDepth-currentNode->minDistance+1))+topoWeight;
//                                 double weight=(1-((double)(massCluster)/(double)(massParent)))+delta;
                                double weight=1;
//                                std::cout<<"idParent"<<idParent<<" idCluster "<<idCluster<<" massParent "<<massParent<<" massCluster "<<massCluster<<" weight "<<weight<<'\n';
                                giantComponent.nodes[i].treeCoordinates[currentNode->id]=weight;
//                                giantComponent.nodes[i].treeCoordinates[currentNode->parent->id]=1;
//                                giantComponent.nodes[i].treeCoordinates[currentNode->parent->id]=(giantComponent.nodes[i].minDistance+1);
//                                giantComponent.nodes[i].treeCoordinates[currentNode->parent->id]=(maxDepth-giantComponent.nodes[i].minDistance+1);
//                                giantComponent.nodes[i].treeCoordinates[currentNode->id]=log(maxDepth-currentNode->minDistance+1);
//                                giantComponent.nodes[i].treeCoordinates[currentNode->parent->id]=pow((maxDepth-giantComponent.nodes[i].minDistance+1),.5);
                                currentNode=currentNode->parent;
                            }
//                            giantComponent.nodes[i].treeCoordinates[currentNode->id]=0+delta;
                             giantComponent.nodes[i].treeCoordinates[currentNode->id]=1;
//                            giantComponent.nodes[i].treeCoordinates[currentNode->id]=log(maxDepth-currentNode->minDistance+1);
//                             giantComponent.nodes[i].treeCoordinates[giantComponent.nodes.size()]=(maxDepth-giantComponent.nodes[i].minDistance);
                            
                        }
                    
                    
                        for(long h=0; h<nodesCutoff.size(); h++)
                        {
                            
                            nodesCutoff[h]->minDistance=INFINITY;
                            nodesCutoff[h]->inDijkstra=false;
                            nodesCutoff[h]->inCutoff=false;
                            nodesCutoff[h]->numOtherChildren.clear();
                            nodesCutoff[h]->parent=NULL;
                            
                        }
                        nodesCutoff.clear();
                        nodesToCheckDijkstra.clear();
                    
                    
                    
                    //AGGREGATE_BY_CONSTITUENCIES                    
                    //"~/Dropbox/CASA/data/GIS/UK/GB_ParlConst_2010/UK_Intersections_ParConst.csv"
                    std::vector<Graph> constituencies;
                    std::stringstream fileName;
//                    fileName<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                    fileName<<"/Users/carlos/Dropbox/CASA/data/GIS/UK/GB_ParlConst_2010/UK_intersections_nodes_constituencies.txt";
                    
                    textFile.loadClassificationOfNodes(&mainGraph, fileName.str(), constituencies, " ", true);
                    
                    std::unordered_map<long,std::vector<long> > coordinatesPerIdConstituency;
                    std::unordered_map<unsigned long long, Node*> nodesOfGiantComponentByOriginalId;
                    for(long j=0;j<giantComponent.nodes.size();j++){
                        nodesOfGiantComponentByOriginalId[giantComponent.nodes[j].originalID]=&giantComponent.nodes[j];
                    }
                    
                    
                    
                    
                    bool useCommunities=false;
                    if(useCommunities){
                        std::vector<Graph> communityClusters;
                        
                        fileName.str("");
                        fileName<<"/Users/carlos/Dropbox/CASA/results/clustersFromPercolation/clusteredHierarchical/completeData/resultCommunity.txt";
                        
                        textFile.loadClassificationOfNodes(&giantComponent, fileName.str(), communityClusters, " ", true);
                        
                        
                        for(long i=0;i<communityClusters.size();i++){
                            std::unordered_map<long,double> coordinates;
//                            long totalNumberOfNodesInCommunity=communityClusters[i].nodes.size();
                            std::unordered_map<long,long> numberOfNodesPerClusterInCommunity;
                            double numNodes=0;
                            for(long j=0;j<communityClusters[i].nodes.size();j++){
    //                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
    //                            Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
    //                            long idCluster=communityClusters.id;
    //                            numberOfNodesPerClusterInConstituency[idCluster]++;
                                
                                
                                if(coordinates.size()==0){
                                    Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                                    if(node!=NULL){
                                        coordinates=node->treeCoordinates;
                                        numNodes++;
                                    }
                                }else{
                                    Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                                    if(node!=NULL){
                                        coordinates=Functions::sum(coordinates,node->treeCoordinates);
                                        numNodes++;
                                    }
                                }
                                
                            }
                            coordinates=Functions::div(coordinates,(double)numNodes);
                            
                            for(long j=0;j<communityClusters[i].nodes.size();j++){
                                Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                                if(node!=NULL){
                                    node->treeCoordinates=coordinates;
                                }
                            }
                            
                        }
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    std::unordered_map<long,std::unordered_map<long,double> > coordinatesOfConstituencies;
                    for(long i=0;i<constituencies.size();i++){
                        long totalNumberOfNodesInConstituency=constituencies[i].nodes.size();
                        std::unordered_map<long,long> numberOfNodesPerClusterInConstituency;
                        for(long j=0;j<constituencies[i].nodes.size();j++){
                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
                            long idCluster=nodesBelongingToClusters[index][1];
                            numberOfNodesPerClusterInConstituency[idCluster]++;
                            
                        }
                        std::unordered_map<long,double> coordinatesOfConstituency;
//                        for ( auto it = numberOfNodesPerClusterInConstituency.begin(); it != numberOfNodesPerClusterInConstituency.end(); ++it ){
//                            long idCluster=it->first;
//                            //                            double numberOfNodes=(double)(it->second)/(double)(totalNumberOfNodesInConstituency);
//                            double numberOfNodes=(double)(it->second);
//                            if(nodesOfGiantComponentByOriginalId[idCluster]!=NULL){
//                                totalNumberOfNodesInConstituency+=numberOfNodes;
//                            }
//                        }
                        
                        
                        for ( auto it = numberOfNodesPerClusterInConstituency.begin(); it != numberOfNodesPerClusterInConstituency.end(); ++it ){
                            long idCluster=it->first;
                            double numberOfNodes=(double)(it->second)/(double)(totalNumberOfNodesInConstituency);
//                            double numberOfNodes=(double)(it->second);
                            if(nodesOfGiantComponentByOriginalId[idCluster]!=NULL){
                                for(auto itB=nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.begin();itB!=nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.end();++itB){
//                                    coordinatesOfConstituency[itB->first]=(double)(itB->second)*numberOfNodes/(double)numberOfNodesPerClusterInConstituency.size()+coordinatesOfConstituency[itB->first];
//                                    std::cout<<"______________________________________"<<'\n';
//                                    std::cout<<"constituencies[i].id "<<constituencies[i].id<<'\n';
//                                    std::cout<<"idCluster "<<idCluster<<'\n';
//                                    std::cout<<"coordinatesOfConstituency[itB->first] "<<coordinatesOfConstituency[itB->first]<<'\n';
//                                    std::cout<<"nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.size() "<<nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.size()<<'\n';
//                                    std::cout<<"itB->second "<<itB->second<<'\n';
//                                    std::cout<<"numberOfNodes "<<numberOfNodes<<'\n';
//                                    std::cout<<"numberOfNodesPerClusterInConstituency.size() "<<numberOfNodesPerClusterInConstituency.size()<<'\n';
//                                    std::cout<<"totalNumberOfNodesInConstituency "<<totalNumberOfNodesInConstituency<<'\n';
//                                    double previous=coordinatesOfConstituency[itB->first];
                                    double previous=coordinatesOfConstituencies[constituencies[i].id][itB->first];
//                                    coordinatesOfConstituency[itB->first]=(double)(itB->second)*numberOfNodes+previous;
                                    coordinatesOfConstituencies[constituencies[i].id][itB->first]=(double)(itB->second)*numberOfNodes+previous;
                                }
                            }
                            
                            
                            
                         
                        }
//                        std::stringstream result;
//                        result<<constituencies[i].id<<" ";
//                        
//                        for(long j=0;j<giantComponent.nodes.size();j++){
//                            result<<(coordinatesOfConstituency[j]);
//                            if(j<giantComponent.nodes.size()){
//                                result<<" ";
//                            }
//                        }
//                        
//                        std::vector<std::string> resultVector;
//                        resultVector.push_back(result.str());
//                        fileName.str("");
//                        fileName<<Configuration::folderOut()<<"coordinatesOfConstituencies.txt";
//                        textFile.writeToFile(fileName.str(), resultVector, true);
                    }
                    std::vector<Node> nodesThatSimulateIdsConstituencies;
                    for(long i=0;i<constituencies.size();i++){
                        Node node;
                        node.minDistance=constituencies[i].id;
                        nodesThatSimulateIdsConstituencies.push_back(node);
                        
                    }
                    Matrix distanceMatrix;
                    Heap<Node*> idsConstituenciesForOrdering(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                    for(long i=0;i<constituencies.size();i++){
                        Node* node=&nodesThatSimulateIdsConstituencies[i];
                        idsConstituenciesForOrdering.push(node);
                    }
                    std::vector<Node*> orderedIdsConstituencies;
                    while(idsConstituenciesForOrdering.size()>0){
                        Node* node=idsConstituenciesForOrdering.pop();
                        orderedIdsConstituencies.push_back(node);
                    }
                    for(long i=0;i<orderedIdsConstituencies.size();i++){
                        long idA=orderedIdsConstituencies[i]->minDistance;
                        std::stringstream result;
                        bool toBeSavedA=true;
                        if(coordinatesOfConstituencies[idA].size()==0){
                            toBeSavedA=false;
                        }
                        if(toBeSavedA){
                            result<<orderedIdsConstituencies[i]->minDistance<<" ";
                            
                            for(long j=0;j<orderedIdsConstituencies.size();j++){
                                bool toBeSavedB=true;
                                long idB=orderedIdsConstituencies[j]->minDistance;
                                if(coordinatesOfConstituencies[idB].size()==0){
                                    toBeSavedB=false;
                                }
                                if(toBeSavedB){
                                    double distance=Functions::getManhattanDistance(coordinatesOfConstituencies[idA], coordinatesOfConstituencies[idB]);
                                //                            distanceMatrix.set(distance, idA, idB);
                               
                                    result<<distance<<" ";
                                }
                                
                            }
                            std::vector<std::string> resultVector;
                            resultVector.push_back(result.str());
                            fileName.str("");
                            fileName<<Configuration::folderOut()<<"distanceMatrixOfConstituenciesTD.txt";
                            
                            textFile.writeToFile(fileName.str(), resultVector, true);
                        }
                    }

                    
                }
                if (modeCalculation==GENERATE_TREE_FROM_CLUSTERS_METHOD_B){
                    
                    //                    textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true, false);
                    //                    mainGraph.transformToBidirectional();
                    //                std::unordered_map<signed long long,long> previousCluster;
                    std::unordered_map<signed long long,long> currentCluster;
                    std::vector<std::string> ncolPairs;
                    std::vector<std::string> masses;
                    std::vector<std::vector<signed long long> > nodesBelongingToClusters;
                    std::unordered_map<signed long long,long> nodesByOriginalId;
                    
                   
                    
                    
                    //
                    long uniqueId=0;
                    bool generateTree=false;

                    
                    if(generateTree){
                        
                        for(long i=0;i<mainGraph.nodes.size();i++){
                            std::vector<signed long long> pair;
                            pair.push_back(mainGraph.nodes[i].originalID);
                            pair.push_back(-1);
                            nodesBelongingToClusters.push_back(pair);
                            nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
                        }
                        
                        
                        for(int distance=50;distance<=5000;distance+=50){
                            //                    std::unordered_map<long,signed long long> correspondancesBetweenRealIdsAndUniqueIds;
                            std::vector<Graph> clusters;
                            mainGraph.calculateClusterUsingNetworkPercolation(distance, clusters, false, true, "", 75);
                            
                            //                    std::vector<std::string> masses;
                            
                            
                            for (long i=0;i<clusters.size();i++){
                                
                                clusters[i].id=uniqueId;
                                std::stringstream mass;
                                mass<<distance<<" "<<uniqueId<<" "<<clusters[i].nodes.size();
                                masses.push_back(mass.str());
                                uniqueId++;
                                for(long j=0;j<clusters[i].nodes.size();j++){
                                    long index=nodesByOriginalId[clusters[i].nodes[j].originalID];
                                    long value=nodesBelongingToClusters[index][1];
                                    if(value==-1){
                                        nodesBelongingToClusters[index][1]=clusters[i].id;
                                    }
                                    if(currentCluster[clusters[i].nodes[j].originalID]!=0){
                                        std::stringstream pair;
                                        pair<<(clusters[i].id)<<" "<<(currentCluster[clusters[i].nodes[j].originalID]-1)<<" "<<"1";
                                        ncolPairs.push_back(pair.str());
                                        currentCluster[clusters[i].nodes[j].originalID]=0;
                                        
                                    }
                                    
                                }
                                
                            }
                            for (long i=0;i<clusters.size();i++){
                                
                                currentCluster[clusters[i].nodes[0].originalID]=clusters[i].id+1;
                                
                            }
                            
                        }
                        std::vector<std::string> belongingOfNodes;
                        for(long i=0;i<nodesBelongingToClusters.size();i++){
                            std::stringstream value;
                            value<<nodesBelongingToClusters[i][0]<<" "<<nodesBelongingToClusters[i][1];
                            belongingOfNodes.push_back(value.str());
                        }
                        std::stringstream textFileOut;
                        textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
                        textFile.writeToFile(textFileOut.str(), ncolPairs, false);
                        textFileOut.str("");
                        textFileOut<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
                        textFile.writeToFile(textFileOut.str(), masses, false);
                        textFileOut.str("");
                        textFileOut<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                        textFile.writeToFile(textFileOut.str(), belongingOfNodes, false);
                    }else{
                        std::stringstream fileName;
                        fileName<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                        textFile.loadPairsFileOfNodeIdAndClusterId(nodesBelongingToClusters, fileName.str(), " ", false);
                        for(long i=0;i<mainGraph.nodes.size();i++){
                            nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
                        }
                        
                        
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    //                }
                    //                if(modeCalculation==CREATE_COORDINATES_FROM_TREE){
                    
                    Graph tree;
//                    textFileOut.str("");
                    std::stringstream textFileOut;
                    textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
                    textFile.parseNCOL(textFileOut.str(), &tree, " ", false);
                    
                    
                    Graph giantComponent;
                    tree.getGiantComponent(&tree, &giantComponent);
                    Node* root=NULL;
                    for(long i=0;i<giantComponent.nodes.size();i++){
                        if(giantComponent.nodes[i].nodesThatReachMe.size()==0){
                            root=&(giantComponent.nodes[i]);
                        }
                    }
                    
                    std::vector<Node*> nodesCutoff;
                    Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                    //                        Node* nodeTemp=root;
                    root->minDistance=0;
                    nodesCutoff.push_back(root);
                    
                    nodesToCheckDijkstra.push(root);
                    
                    giantComponent.calculateDijkstraSpeed(root, 0, nodesCutoff,nodesToCheckDijkstra);
                    
                    
                    
                    
                    
                    
                    
                   
                    
                    
                    
                    
                    
                    
                    
                    
                    std::vector<Graph> constituencies;
                    std::stringstream fileName;
                    fileName<<"/Users/carlos/Dropbox/CASA/data/GIS/UK/GB_ParlConst_2010/UK_intersections_nodes_constituencies.txt";
                    
                    textFile.loadClassificationOfNodes(&mainGraph, fileName.str(), constituencies, " ", true);
                    
                    fileName.str("");
                    fileName<<"/Users/carlos/Dropbox/CASA/data/socialData/UK/elections/normalizedVotes.txt";
                    std::unordered_map<long, std::vector<double> > votes;
                    textFile.loadVectorWithIds(&votes, fileName.str(), " ", true);
                    
                    for(long i=0;i<constituencies.size();i++){
                        for(long j=0;j<constituencies[i].nodes.size();j++){
                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
                            Node* node=&mainGraph.nodes[index];
                            node->dataVector=votes[constituencies[i].id];
                            
                        }
                    }
                    
                    long maxDepth=0;
                    for(long h=0; h<nodesCutoff.size(); h++)
                    {
                        if(nodesCutoff[h]->minDistance>maxDepth){
                            maxDepth=nodesCutoff[h]->minDistance;
                        }
                    }
                    
                    std::unordered_map<unsigned long long, Node*> nodesOfGiantComponentByOriginalId;
                    for(long j=0;j<giantComponent.nodes.size();j++){
                        nodesOfGiantComponentByOriginalId[giantComponent.nodes[j].originalID]=&giantComponent.nodes[j];
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    bool useCommunities=false;
                    std::unordered_map<long,long> communityClusterIdByPercolationClusterId;
                    if(useCommunities){
                        std::vector<Graph> communityClusters;
                        
                        fileName.str("");
                        fileName<<"/Users/carlos/Dropbox/CASA/results/clustersFromPercolation/clusteredHierarchical/completeData/resultCommunityLPW.txt";
                        
                        textFile.loadClassificationOfNodes(&giantComponent, fileName.str(), communityClusters, " ", true);
                        
                        
                        for(long i=0;i<communityClusters.size();i++){
                            
                            
                            
                            
                            
//                            std::unordered_map<long,double> coordinates;
//                            //                            long totalNumberOfNodesInCommunity=communityClusters[i].nodes.size();
//                            std::unordered_map<long,long> numberOfNodesPerClusterInCommunity;
//                            double numNodes=0;
                            for(long j=0;j<communityClusters[i].nodes.size();j++){
                                
                                communityClusterIdByPercolationClusterId[communityClusters[i].nodes[j].originalID]=communityClusters[i].id;
                                
                                
//                                //                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
//                                //                            Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
//                                //                            long idCluster=communityClusters.id;
//                                //                            numberOfNodesPerClusterInConstituency[idCluster]++;
//                                
//                                
//                                if(coordinates.size()==0){
//                                    Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
//                                    if(node!=NULL){
//                                        coordinates=node->treeCoordinates;
//                                        numNodes++;
//                                    }
//                                }else{
//                                    Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
//                                    if(node!=NULL){
//                                        coordinates=Functions::sum(coordinates,node->treeCoordinates);
//                                        numNodes++;
//                                    }
//                                }
//                                
                            }
//                            coordinates=Functions::div(coordinates,(double)numNodes);
//                            
//                            for(long j=0;j<communityClusters[i].nodes.size();j++){
//                                Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
//                                if(node!=NULL){
//                                    node->treeCoordinates=coordinates;
//                                }
//                            }
                            
                        }
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    for(long depth=0;depth<maxDepth+1;depth++)
//                    {
//                    long depth=99;
                    {
                        std::unordered_map<long,std::vector<Node*> > nodesByPercolationCluster;
                        for(long h=0;h<nodesBelongingToClusters.size();h++){
                            long indexOfNodeInMainGraph=nodesByOriginalId[nodesBelongingToClusters[h][0]];
                            long clusterIdOfPercolation=nodesBelongingToClusters[h][1];

                            Node* currentNode=nodesOfGiantComponentByOriginalId[clusterIdOfPercolation];
                            if(currentNode!=NULL){
                                while(currentNode->minDistance>depth){
                                    currentNode=currentNode->parent;
                                }
                                if(!useCommunities){
                                    nodesByPercolationCluster[currentNode->originalID].push_back(&mainGraph.nodes[indexOfNodeInMainGraph]);
                                }else{
                                    nodesByPercolationCluster[communityClusterIdByPercolationClusterId[currentNode->originalID]].push_back(&mainGraph.nodes[indexOfNodeInMainGraph]);
                                }
                            }

                        }
                        for(auto it=nodesByPercolationCluster.begin();it!=nodesByPercolationCluster.end();++it){
                            std::vector<double> averagedVotes;
                            long numberNodes=0;
                            for(long h=0;h<it->second.size();h++){
                                if(it->second[h]->dataVector.size()>0){
                                    for(long g=0;g<it->second[h]->dataVector.size();g++){
                                        double value=it->second[h]->dataVector[g];
                                        if(averagedVotes.size()<it->second[h]->dataVector.size()){
                                            averagedVotes.push_back(value);
                                        }else{
                                            averagedVotes[g]+=value;
                                        }
                                    }
                                    numberNodes++;
                                }
                               
                            }
                            for(long h=0;h<averagedVotes.size();h++){
                                averagedVotes[h]/=(double)(numberNodes);
                            }
                            for(long h=0;h<it->second.size();h++){
                                it->second[h]->averagedDataVector=averagedVotes;
                            }
                        }
                        for(long i=0;i<constituencies.size();i++){
                            std::vector<double> averagedVotes;
                            long numberNodes=0;
                            for(long j=0;j<constituencies[i].nodes.size();j++){
                                
                                long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
                                Node* node=&mainGraph.nodes[index];
                                if(node->averagedDataVector.size()>0){
                                    for(long g=0;g<node->averagedDataVector.size();g++){
                                        double value=node->averagedDataVector[g];
                                        if(averagedVotes.size()<node->averagedDataVector.size()){
                                            averagedVotes.push_back(value);
                                        }else{
                                            averagedVotes[g]+=value;
                                        }
                                        
                                    }
                                    numberNodes++;
                                }
                                
                                
                            }
                            if(averagedVotes.size()>0){
                                std::stringstream result;
                                result<<constituencies[i].id<<" ";
                                for(long h=0;h<averagedVotes.size();h++){
                                    averagedVotes[h]/=(double)(numberNodes);
                                    result<<averagedVotes[h]<<" ";
                                }
                                fileName.str("");
                                if(!useCommunities){
                                    fileName<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/clusteredHierarchical/fixedAveragedVotingBehavior/averagedVotingVectorFromPercolationThreshold"<<depth<<".txt";
                                }else{
                                    fileName<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/clusteredHierarchical/fixedAveragedVotingBehavior/averagedVotingVectorFromPercolationThreshold_Communities"<<depth<<".txt";
                                }
                                std::vector<std::string> resultVector;
                                resultVector.push_back(result.str());
                                textFile.writeToFile(fileName.str(), resultVector, true);
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
//                    for(long i=0;i<giantComponent.nodes.size();i++){
//                        Node* currentNode=&(giantComponent.nodes[i]);
//                        giantComponent.nodes[i].treeCoordinates[currentNode->id]=1;
//                        while(currentNode->parent!=NULL){
//                            giantComponent.nodes[i].treeCoordinates[currentNode->parent->id]=1;
//                            currentNode=currentNode->parent;
//                        }
//                    }
                    
                    
                    for(long h=0; h<nodesCutoff.size(); h++)
                    {
                        
                        nodesCutoff[h]->minDistance=INFINITY;
                        nodesCutoff[h]->inDijkstra=false;
                        nodesCutoff[h]->inCutoff=false;
                        nodesCutoff[h]->numOtherChildren.clear();
                        nodesCutoff[h]->parent=NULL;
                        
                    }
                    nodesCutoff.clear();
                    nodesToCheckDijkstra.clear();
                    
                    
                    
                    //AGGREGATE_BY_CONSTITUENCIES
                    //"~/Dropbox/CASA/data/GIS/UK/GB_ParlConst_2010/UK_Intersections_ParConst.csv"
                  
                    
//                    std::unordered_map<long,std::vector<long> > coordinatesPerIdConstituency;
//                    std::unordered_map<unsigned long long, Node*> nodesOfGiantComponentByOriginalId;
//                    for(long j=0;j<giantComponent.nodes.size();j++){
//                        nodesOfGiantComponentByOriginalId[giantComponent.nodes[j].originalID]=&giantComponent.nodes[j];
//                    }
//                    std::unordered_map<long,std::unordered_map<long,double> > coordinatesOfConstituencies;
//                    for(long i=0;i<constituencies.size();i++){
//                        long totalNumberOfNodesInConstituency=0;
//                        std::unordered_map<long,long> numberOfNodesPerClusterInConstituency;
//                        for(long j=0;j<constituencies[i].nodes.size();j++){
//                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
//                            long idCluster=nodesBelongingToClusters[index][1];
//                            numberOfNodesPerClusterInConstituency[idCluster]++;
//                            
//                        }
//                        std::unordered_map<long,double> coordinatesOfConstituency;
//                        for ( auto it = numberOfNodesPerClusterInConstituency.begin(); it != numberOfNodesPerClusterInConstituency.end(); ++it ){
//                            long idCluster=it->first;
//                            //                            double numberOfNodes=(double)(it->second)/(double)(totalNumberOfNodesInConstituency);
//                            double numberOfNodes=(double)(it->second);
//                            if(nodesOfGiantComponentByOriginalId[idCluster]!=NULL){
//                                totalNumberOfNodesInConstituency+=numberOfNodes;
//                            }
//                        }
//                        
//                        
//                        for ( auto it = numberOfNodesPerClusterInConstituency.begin(); it != numberOfNodesPerClusterInConstituency.end(); ++it ){
//                            long idCluster=it->first;
//                            double numberOfNodes=(double)(it->second)/(double)(totalNumberOfNodesInConstituency);
//                            //                            double numberOfNodes=(double)(it->second);
//                            if(nodesOfGiantComponentByOriginalId[idCluster]!=NULL){
//                                for(auto itB=nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.begin();itB!=nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.end();++itB){
//                                    //                                    coordinatesOfConstituency[itB->first]=(double)(itB->second)*numberOfNodes/(double)numberOfNodesPerClusterInConstituency.size()+coordinatesOfConstituency[itB->first];
//                                    //                                    std::cout<<"______________________________________"<<'\n';
//                                    //                                    std::cout<<"constituencies[i].id "<<constituencies[i].id<<'\n';
//                                    //                                    std::cout<<"idCluster "<<idCluster<<'\n';
//                                    //                                    std::cout<<"coordinatesOfConstituency[itB->first] "<<coordinatesOfConstituency[itB->first]<<'\n';
//                                    //                                    std::cout<<"nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.size() "<<nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.size()<<'\n';
//                                    //                                    std::cout<<"itB->second "<<itB->second<<'\n';
//                                    //                                    std::cout<<"numberOfNodes "<<numberOfNodes<<'\n';
//                                    //                                    std::cout<<"numberOfNodesPerClusterInConstituency.size() "<<numberOfNodesPerClusterInConstituency.size()<<'\n';
//                                    //                                    std::cout<<"totalNumberOfNodesInConstituency "<<totalNumberOfNodesInConstituency<<'\n';
//                                    double previous=coordinatesOfConstituency[itB->first];
//                                    //                                    coordinatesOfConstituency[itB->first]=(double)(itB->second)*numberOfNodes+previous;
//                                    coordinatesOfConstituencies[constituencies[i].id][it->first]=(double)(itB->second)*numberOfNodes+previous;
//                                }
//                            }
//                            
//                            
//                            
//                            
//                        }
//                        //                        std::stringstream result;
//                        //                        result<<constituencies[i].id<<" ";
//                        //
//                        //                        for(long j=0;j<giantComponent.nodes.size();j++){
//                        //                            result<<(coordinatesOfConstituency[j]);
//                        //                            if(j<giantComponent.nodes.size()){
//                        //                                result<<" ";
//                        //                            }
//                        //                        }
//                        //
//                        //                        std::vector<std::string> resultVector;
//                        //                        resultVector.push_back(result.str());
//                        //                        fileName.str("");
//                        //                        fileName<<Configuration::folderOut()<<"coordinatesOfConstituencies.txt";
//                        //                        textFile.writeToFile(fileName.str(), resultVector, true);
//                    }
//                    std::vector<Node> nodesThatSimulateIdsConstituencies;
//                    for(long i=0;i<constituencies.size();i++){
//                        Node node;
//                        node.minDistance=constituencies[i].id;
//                        nodesThatSimulateIdsConstituencies.push_back(node);
//                        
//                    }
//                    Matrix distanceMatrix;
//                    Heap<Node*> idsConstituenciesForOrdering(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
//                    for(long i=0;i<constituencies.size();i++){
//                        Node* node=&nodesThatSimulateIdsConstituencies[i];
//                        idsConstituenciesForOrdering.push(node);
//                    }
//                    std::vector<Node*> orderedIdsConstituencies;
//                    while(idsConstituenciesForOrdering.size()>0){
//                        Node* node=idsConstituenciesForOrdering.pop();
//                        orderedIdsConstituencies.push_back(node);
//                    }
//                    for(long i=0;i<orderedIdsConstituencies.size();i++){
//                        long idA=orderedIdsConstituencies[i]->minDistance;
//                        std::stringstream result;
//                        result<<orderedIdsConstituencies[i]->minDistance<<" ";
//                        
//                        for(long j=0;j<orderedIdsConstituencies.size();j++){
//                            long idB=orderedIdsConstituencies[j]->minDistance;
//                            double distance=Functions::getManhattanDistance(coordinatesOfConstituencies[idA], coordinatesOfConstituencies[idB]);
//                            //                            distanceMatrix.set(distance, idA, idB);
//                            result<<distance<<" ";
//                            
//                        }
//                        std::vector<std::string> resultVector;
//                        resultVector.push_back(result.str());
//                        fileName.str("");
//                        fileName<<Configuration::folderOut()<<"distanceMatrixOfConstituencies.txt";
//                        textFile.writeToFile(fileName.str(), resultVector, true);
//                    }
                    
                    
                }
                
                if (modeCalculation==GENERATE_TREE_FROM_CLUSTERS_METHOD_C){
                    
                    //                    textFile.parseNCOLandSeparateCoordinatesFile(name, nameCoordinatesSS.str(), &mainGraph, separatorNCOL, separatorCoordinates, true, false);
                    //                    mainGraph.transformToBidirectional();
                    //                std::unordered_map<signed long long,long> previousCluster;
                    std::unordered_map<signed long long,long> currentCluster;
                    std::vector<std::string> ncolPairs;
                    std::vector<std::string> masses;
                    std::vector<std::vector<signed long long> > nodesBelongingToClusters;
                    std::unordered_map<signed long long,long> nodesByOriginalId;
                    
                    
                    
                    
                    //
                    long uniqueId=0;
                    bool generateTree=false;
                    std::unordered_map<long,long> massesOfClustersByOriginalId;
                    
                    if(generateTree){
                        
                        for(long i=0;i<mainGraph.nodes.size();i++){
                            std::vector<signed long long> pair;
                            pair.push_back(mainGraph.nodes[i].originalID);
                            pair.push_back(-1);
                            nodesBelongingToClusters.push_back(pair);
                            nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
                        }
                        
                        
                        std::vector<long> setOfDistances;
//                        for(long distance=50;distance<=5000;distance+=50){
//                            setOfDistances.push_back(distance);
//                        }
                                                setOfDistances.push_back(300);
                                                setOfDistances.push_back(450);
                        setOfDistances.push_back(800);
//                        setOfDistances.push_back(600);
                                                setOfDistances.push_back(900);
//                                                setOfDistances.push_back(900);
                                                                        setOfDistances.push_back(1400);
                                                                        setOfDistances.push_back(5000);
                        //                                                setOfDistances.push_back(4800);
                        //                                                setOfDistances.push_back(4850);
                        //                                                setOfDistances.push_back(5000);
                        
                        
                        for(long proxyDistance=0;proxyDistance<setOfDistances.size();proxyDistance++){
                            long distance=setOfDistances[proxyDistance];
                            //                    std::unordered_map<long,signed long long> correspondancesBetweenRealIdsAndUniqueIds;
                            std::vector<Graph> clusters;
                            mainGraph.calculateClusterUsingNetworkPercolation(distance, clusters, false, true, "", 75);
                            
                            //                    std::vector<std::string> masses;
                            
                            
                            for (long i=0;i<clusters.size();i++){
                                
                                clusters[i].id=uniqueId;
                                std::stringstream mass;
                                mass<<distance<<" "<<uniqueId<<" "<<clusters[i].nodes.size();
                                masses.push_back(mass.str());
                                uniqueId++;
                                for(long j=0;j<clusters[i].nodes.size();j++){
                                    long index=nodesByOriginalId[clusters[i].nodes[j].originalID];
                                    long value=nodesBelongingToClusters[index][1];
                                    if(value==-1){
                                        nodesBelongingToClusters[index][1]=clusters[i].id;
                                    }
                                    if(currentCluster[clusters[i].nodes[j].originalID]!=0){
                                        std::stringstream pair;
                                        pair<<(clusters[i].id)<<" "<<(currentCluster[clusters[i].nodes[j].originalID]-1)<<" "<<"1";
                                        ncolPairs.push_back(pair.str());
                                        currentCluster[clusters[i].nodes[j].originalID]=0;
                                        
                                    }
                                    
                                }
                                
                            }
                            for (long i=0;i<clusters.size();i++){
                                
                                currentCluster[clusters[i].nodes[0].originalID]=clusters[i].id+1;
                                
                            }
                            
                        }
                        std::vector<std::string> belongingOfNodes;
                        for(long i=0;i<nodesBelongingToClusters.size();i++){
                            std::stringstream value;
                            value<<nodesBelongingToClusters[i][0]<<" "<<nodesBelongingToClusters[i][1];
                            belongingOfNodes.push_back(value.str());
                        }
                        std::stringstream textFileOut;
                        textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
                        textFile.writeToFile(textFileOut.str(), ncolPairs, false);
                        textFileOut.str("");
                        textFileOut<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
                        textFile.writeToFile(textFileOut.str(), masses, false);
                        textFileOut.str("");
                        textFileOut<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                        textFile.writeToFile(textFileOut.str(), belongingOfNodes, false);
                    }else{
                        std::stringstream fileName;
                        fileName<<Configuration::folderOut()<<"clusterOfEachNode.txt";
                        textFile.loadPairsFileOfNodeIdAndClusterId(nodesBelongingToClusters, fileName.str(), " ", false);
                        for(long i=0;i<mainGraph.nodes.size();i++){
                            nodesByOriginalId[mainGraph.nodes[i].originalID]=i;
                        }
                        fileName.str("");
                        fileName<<Configuration::folderOut()<<"massesClustersFromPercolation.txt";
                        textFile.loadMassesPercolation(&massesOfClustersByOriginalId, fileName.str(), " ", false);
                        
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    //                }
                    //                if(modeCalculation==CREATE_COORDINATES_FROM_TREE){
                    
                    Graph tree;
                    //                    textFileOut.str("");
                    std::stringstream textFileOut;
                    textFileOut<<Configuration::folderOut()<<"ncolTreeFromPercolation.txt";
                    textFile.parseNCOL(textFileOut.str(), &tree, " ", false);
                    
                    
                    Graph giantComponent;
                    tree.getGiantComponent(&tree, &giantComponent);
                    Node* root=NULL;
                    for(long i=0;i<giantComponent.nodes.size();i++){
                        if(giantComponent.nodes[i].nodesThatReachMe.size()==0){
                            root=&(giantComponent.nodes[i]);
                        }
                    }
                    
                    std::vector<Node*> nodesCutoff;
                    Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                    //                        Node* nodeTemp=root;
                    root->minDistance=0;
                    nodesCutoff.push_back(root);
                    
                    nodesToCheckDijkstra.push(root);
                    
                    giantComponent.calculateDijkstraSpeed(root, 0, nodesCutoff,nodesToCheckDijkstra);
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    std::vector<Graph> constituencies;
                    std::stringstream fileName;
                    fileName<<"/Users/carlos/Dropbox/CASA/data/GIS/UK/GB_ParlConst_2010/UK_intersections_nodes_constituencies.txt";
                    
                    textFile.loadClassificationOfNodes(&mainGraph, fileName.str(), constituencies, " ", true);
                    
                    fileName.str("");
                    fileName<<"/Users/carlos/Dropbox/CASA/data/socialData/UK/elections/normalizedVotes.txt";
                    std::unordered_map<long, std::vector<double> > votes;
                    textFile.loadVectorWithIds(&votes, fileName.str(), " ", true);
                    
                    for(long i=0;i<constituencies.size();i++){
                        for(long j=0;j<constituencies[i].nodes.size();j++){
                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
                            Node* node=&mainGraph.nodes[index];
                            node->dataVector=votes[constituencies[i].id];
                            
                        }
                    }
                    
                    long maxDepth=0;
                    for(long h=0; h<nodesCutoff.size(); h++)
                    {
                        if(nodesCutoff[h]->minDistance>maxDepth){
                            maxDepth=nodesCutoff[h]->minDistance;
                        }
                    }
                    
                    std::unordered_map<unsigned long long, Node*> nodesOfGiantComponentByOriginalId;
                    for(long j=0;j<giantComponent.nodes.size();j++){
                        nodesOfGiantComponentByOriginalId[giantComponent.nodes[j].originalID]=&giantComponent.nodes[j];
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    bool useCommunities=false;
//                    long maxNumberClusters=0;
                    std::unordered_map<long,long> communityClusterIdByPercolationClusterId;
                    if(useCommunities){
                        std::vector<Graph> communityClusters;
                        
                        fileName.str("");
                        fileName<<"/Users/carlos/Dropbox/CASA/results/clustersFromPercolation/clusteredHierarchical/completeData/resultCommunityIMW.txt";
                        
                        textFile.loadClassificationOfNodes(&giantComponent, fileName.str(), communityClusters, " ", true);
//                        maxNumberClusters=communityClusters.size();
                        
                        for(long i=0;i<communityClusters.size();i++){
//                            communityClusters[i].id=i;
                            
                            
                            
                            
                            //                            std::unordered_map<long,double> coordinates;
                            //                            //                            long totalNumberOfNodesInCommunity=communityClusters[i].nodes.size();
                            //                            std::unordered_map<long,long> numberOfNodesPerClusterInCommunity;
                            //                            double numNodes=0;
                            for(long j=0;j<communityClusters[i].nodes.size();j++){
                                
                                communityClusterIdByPercolationClusterId[communityClusters[i].nodes[j].originalID]=communityClusters[i].id;
                                
                                
                                //                                //                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
                                //                                //                            Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                                //                                //                            long idCluster=communityClusters.id;
                                //                                //                            numberOfNodesPerClusterInConstituency[idCluster]++;
                                //
                                //
                                //                                if(coordinates.size()==0){
                                //                                    Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                                //                                    if(node!=NULL){
                                //                                        coordinates=node->treeCoordinates;
                                //                                        numNodes++;
                                //                                    }
                                //                                }else{
                                //                                    Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                                //                                    if(node!=NULL){
                                //                                        coordinates=Functions::sum(coordinates,node->treeCoordinates);
                                //                                        numNodes++;
                                //                                    }
                                //                                }
                                //
                            }
                            //                            coordinates=Functions::div(coordinates,(double)numNodes);
                            //
                            //                            for(long j=0;j<communityClusters[i].nodes.size();j++){
                            //                                Node* node=nodesOfGiantComponentByOriginalId[communityClusters[i].nodes[j].originalID];
                            //                                if(node!=NULL){
                            //                                    node->treeCoordinates=coordinates;
                            //                                }
                            //                            }
                            
                        }
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
//                                        for(long depth=0;depth<maxDepth+1;depth++)
//                    {
                    long depth=99;
                    {
                        std::unordered_map<unsigned long long,long > clusterIdByNodeOriginalID;
                        for(long h=0;h<nodesBelongingToClusters.size();h++){
                            long indexOfNodeInMainGraph=nodesByOriginalId[nodesBelongingToClusters[h][0]];
                            long clusterIdOfPercolation=nodesBelongingToClusters[h][1];
                            
                            Node* currentNode=nodesOfGiantComponentByOriginalId[clusterIdOfPercolation];
                            
                            if(currentNode!=NULL){
                                while(currentNode->minDistance>depth){
                                    currentNode=currentNode->parent;
                                }
                                if(!useCommunities){
                                    clusterIdByNodeOriginalID[mainGraph.nodes[indexOfNodeInMainGraph].originalID]=currentNode->originalID;
                                }else{
                                    clusterIdByNodeOriginalID[mainGraph.nodes[indexOfNodeInMainGraph].originalID]=communityClusterIdByPercolationClusterId[currentNode->originalID];
//                                    nodesByPercolationCluster[communityClusterIdByPercolationClusterId[currentNode->originalID]].push_back(&mainGraph.nodes[indexOfNodeInMainGraph]);
                                }
                            }
                            
                        }
//                        for(auto it=nodesByPercolationCluster.begin();it!=nodesByPercolationCluster.end();++it){
//                            std::vector<double> averagedVotes;
//                            long numberNodes=0;
//                            for(long h=0;h<it->second.size();h++){
//                                if(it->second[h]->dataVector.size()>0){
//                                    for(long g=0;g<it->second[h]->dataVector.size();g++){
//                                        double value=it->second[h]->dataVector[g];
//                                        if(averagedVotes.size()<it->second[h]->dataVector.size()){
//                                            averagedVotes.push_back(value);
//                                        }else{
//                                            averagedVotes[g]+=value;
//                                        }
//                                    }
//                                    numberNodes++;
//                                }
//                                
//                            }
//                            for(long h=0;h<averagedVotes.size();h++){
//                                averagedVotes[h]/=(double)(numberNodes);
//                            }
//                            for(long h=0;h<it->second.size();h++){
//                                it->second[h]->averagedDataVector=averagedVotes;
//                            }
//                        }
                        std::unordered_map<long,unordered_map<long,double> > numberOfNodesByClusterIdPerConstituencyId;
                        for(long i=0;i<constituencies.size();i++){
                            

                            for(long j=0;j<constituencies[i].nodes.size();j++){
                                long id=clusterIdByNodeOriginalID[constituencies[i].nodes[j].originalID];
                                numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id][id]+=1;

                                Node* currentNode=nodesOfGiantComponentByOriginalId[id];
                                if(currentNode!=NULL){
                                    while(currentNode->parent!=NULL){
                                        long idParent=currentNode->parent->originalID;

                                        numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id][idParent]+=1;
                                        currentNode=currentNode->parent;
                                       
                                    }
                                }

                                
                                
                            }
                            
                            
                            
                            
                            
                            
                            
//                            for(long j=0;j<constituencies[i].nodes.size();j++){
//                                long id=clusterIdByNodeOriginalID[constituencies[i].nodes[j].originalID];
//                                
//                                
//                                Node* currentNode=nodesOfGiantComponentByOriginalId[id];
//                                numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id][currentNode->minDistance]+=1;
//                                if(currentNode!=NULL){
//                                    while(currentNode->parent!=NULL){
//                                        long idParent=currentNode->parent->originalID;
//                                        currentNode=currentNode->parent;
//                                        numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id][currentNode->minDistance]+=1;
//                                        
//                                        
//                                    }
//                                }
//                                
//                                
//                                
//                            }
                            
                            
                            
//                            for(long j=0;j<constituencies[i].nodes.size();j++){
//                                long id=clusterIdByNodeOriginalID[constituencies[i].nodes[j].originalID];
                            
                            //normalizing.....
                            
//                                numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id]=Functions::div(numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id],(double)constituencies[i].nodes.size());
//                                numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id]=Functions::norm(numberOfNodesByClusterIdPerConstituencyId[constituencies[i].id]);
                            
                            
                            
                            
//                            }
                            
                            
                            
                            
//                            if(averagedVotes.size()>0){
//                                std::stringstream result;
//                                result<<constituencies[i].id<<" ";
//                                for(long h=0;h<averagedVotes.size();h++){
//                                    averagedVotes[h]/=(double)(numberNodes);
//                                    result<<averagedVotes[h]<<" ";
//                                }
//                                fileName.str("");
//                                if(!useCommunities){
//                                    fileName<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/clusteredHierarchical/fixedAveragedVotingBehavior/averagedVotingVectorFromPercolationThreshold"<<depth<<".txt";
//                                }else{
//                                    fileName<<"/Users/carlos/Documents/results/clustersFromPercolation/UK/clusteredHierarchical/fixedAveragedVotingBehavior/averagedVotingVectorFromPercolationThreshold_Communities"<<depth<<".txt";
//                                }
//                                std::vector<std::string> resultVector;
//                                resultVector.push_back(result.str());
//                                textFile.writeToFile(fileName.str(), resultVector, true);
//                            }
                        }
                        std::vector<Node> nodesThatSimulateIdsConstituencies;
                        for(long i=0;i<constituencies.size();i++){
                            Node node;
                            node.minDistance=constituencies[i].id;
                            nodesThatSimulateIdsConstituencies.push_back(node);
                            
                        }
//                        Matrix distanceMatrix;
                        Heap<Node*> idsConstituenciesForOrdering(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                        for(long i=0;i<constituencies.size();i++){
                            Node* node=&nodesThatSimulateIdsConstituencies[i];
                            idsConstituenciesForOrdering.push(node);
                        }
                        std::vector<Node*> orderedIdsConstituencies;
                        while(idsConstituenciesForOrdering.size()>0){
                            Node* node=idsConstituenciesForOrdering.pop();
                            orderedIdsConstituencies.push_back(node);
                        }
                        for(long i=0;i<orderedIdsConstituencies.size();i++){
                            long idA=orderedIdsConstituencies[i]->minDistance;
                            std::stringstream result;
                            bool toBeSavedA=true;
                            if(numberOfNodesByClusterIdPerConstituencyId[idA].size()==0){
                                toBeSavedA=false;
                            }
                            if(toBeSavedA){
                                result<<orderedIdsConstituencies[i]->minDistance<<" ";
                                
                                for(long j=0;j<orderedIdsConstituencies.size();j++){
                                    bool toBeSavedB=true;
                                    long idB=orderedIdsConstituencies[j]->minDistance;
                                    if(numberOfNodesByClusterIdPerConstituencyId[idB].size()==0){
                                        toBeSavedB=false;
                                    }
                                    if(toBeSavedB){
                                        double distance=Functions::getChiSquaredDistance(numberOfNodesByClusterIdPerConstituencyId[idA], numberOfNodesByClusterIdPerConstituencyId[idB]);
                                        //                            distanceMatrix.set(distance, idA, idB);
                                        
                                        result<<distance<<" ";
                                    }
                                    
                                }
                                std::vector<std::string> resultVector;
                                resultVector.push_back(result.str());
                                fileName.str("");
                                fileName<<Configuration::folderOut()<<"distanceMatrixOfConstituenciesNoTDChiSquared_"<<depth<<".txt";
                                
                                textFile.writeToFile(fileName.str(), resultVector, true);
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    //                    for(long i=0;i<giantComponent.nodes.size();i++){
                    //                        Node* currentNode=&(giantComponent.nodes[i]);
                    //                        giantComponent.nodes[i].treeCoordinates[currentNode->id]=1;
                    //                        while(currentNode->parent!=NULL){
                    //                            giantComponent.nodes[i].treeCoordinates[currentNode->parent->id]=1;
                    //                            currentNode=currentNode->parent;
                    //                        }
                    //                    }
                    
                    
                    for(long h=0; h<nodesCutoff.size(); h++)
                    {
                        
                        nodesCutoff[h]->minDistance=INFINITY;
                        nodesCutoff[h]->inDijkstra=false;
                        nodesCutoff[h]->inCutoff=false;
                        nodesCutoff[h]->numOtherChildren.clear();
                        nodesCutoff[h]->parent=NULL;
                        
                    }
                    nodesCutoff.clear();
                    nodesToCheckDijkstra.clear();
                    
                    
                    
                    //AGGREGATE_BY_CONSTITUENCIES
                    //"~/Dropbox/CASA/data/GIS/UK/GB_ParlConst_2010/UK_Intersections_ParConst.csv"
                    
                    
                    //                    std::unordered_map<long,std::vector<long> > coordinatesPerIdConstituency;
                    //                    std::unordered_map<unsigned long long, Node*> nodesOfGiantComponentByOriginalId;
                    //                    for(long j=0;j<giantComponent.nodes.size();j++){
                    //                        nodesOfGiantComponentByOriginalId[giantComponent.nodes[j].originalID]=&giantComponent.nodes[j];
                    //                    }
                    //                    std::unordered_map<long,std::unordered_map<long,double> > coordinatesOfConstituencies;
                    //                    for(long i=0;i<constituencies.size();i++){
                    //                        long totalNumberOfNodesInConstituency=0;
                    //                        std::unordered_map<long,long> numberOfNodesPerClusterInConstituency;
                    //                        for(long j=0;j<constituencies[i].nodes.size();j++){
                    //                            long index=nodesByOriginalId[constituencies[i].nodes[j].originalID];
                    //                            long idCluster=nodesBelongingToClusters[index][1];
                    //                            numberOfNodesPerClusterInConstituency[idCluster]++;
                    //
                    //                        }
                    //                        std::unordered_map<long,double> coordinatesOfConstituency;
                    //                        for ( auto it = numberOfNodesPerClusterInConstituency.begin(); it != numberOfNodesPerClusterInConstituency.end(); ++it ){
                    //                            long idCluster=it->first;
                    //                            //                            double numberOfNodes=(double)(it->second)/(double)(totalNumberOfNodesInConstituency);
                    //                            double numberOfNodes=(double)(it->second);
                    //                            if(nodesOfGiantComponentByOriginalId[idCluster]!=NULL){
                    //                                totalNumberOfNodesInConstituency+=numberOfNodes;
                    //                            }
                    //                        }
                    //
                    //
                    //                        for ( auto it = numberOfNodesPerClusterInConstituency.begin(); it != numberOfNodesPerClusterInConstituency.end(); ++it ){
                    //                            long idCluster=it->first;
                    //                            double numberOfNodes=(double)(it->second)/(double)(totalNumberOfNodesInConstituency);
                    //                            //                            double numberOfNodes=(double)(it->second);
                    //                            if(nodesOfGiantComponentByOriginalId[idCluster]!=NULL){
                    //                                for(auto itB=nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.begin();itB!=nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.end();++itB){
                    //                                    //                                    coordinatesOfConstituency[itB->first]=(double)(itB->second)*numberOfNodes/(double)numberOfNodesPerClusterInConstituency.size()+coordinatesOfConstituency[itB->first];
                    //                                    //                                    std::cout<<"______________________________________"<<'\n';
                    //                                    //                                    std::cout<<"constituencies[i].id "<<constituencies[i].id<<'\n';
                    //                                    //                                    std::cout<<"idCluster "<<idCluster<<'\n';
                    //                                    //                                    std::cout<<"coordinatesOfConstituency[itB->first] "<<coordinatesOfConstituency[itB->first]<<'\n';
                    //                                    //                                    std::cout<<"nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.size() "<<nodesOfGiantComponentByOriginalId[idCluster]->treeCoordinates.size()<<'\n';
                    //                                    //                                    std::cout<<"itB->second "<<itB->second<<'\n';
                    //                                    //                                    std::cout<<"numberOfNodes "<<numberOfNodes<<'\n';
                    //                                    //                                    std::cout<<"numberOfNodesPerClusterInConstituency.size() "<<numberOfNodesPerClusterInConstituency.size()<<'\n';
                    //                                    //                                    std::cout<<"totalNumberOfNodesInConstituency "<<totalNumberOfNodesInConstituency<<'\n';
                    //                                    double previous=coordinatesOfConstituency[itB->first];
                    //                                    //                                    coordinatesOfConstituency[itB->first]=(double)(itB->second)*numberOfNodes+previous;
                    //                                    coordinatesOfConstituencies[constituencies[i].id][it->first]=(double)(itB->second)*numberOfNodes+previous;
                    //                                }
                    //                            }
                    //
                    //
                    //
                    //
                    //                        }
                    //                        //                        std::stringstream result;
                    //                        //                        result<<constituencies[i].id<<" ";
                    //                        //
                    //                        //                        for(long j=0;j<giantComponent.nodes.size();j++){
                    //                        //                            result<<(coordinatesOfConstituency[j]);
                    //                        //                            if(j<giantComponent.nodes.size()){
                    //                        //                                result<<" ";
                    //                        //                            }
                    //                        //                        }
                    //                        //
                    //                        //                        std::vector<std::string> resultVector;
                    //                        //                        resultVector.push_back(result.str());
                    //                        //                        fileName.str("");
                    //                        //                        fileName<<Configuration::folderOut()<<"coordinatesOfConstituencies.txt";
                    //                        //                        textFile.writeToFile(fileName.str(), resultVector, true);
                    //                    }
                    //                    std::vector<Node> nodesThatSimulateIdsConstituencies;
                    //                    for(long i=0;i<constituencies.size();i++){
                    //                        Node node;
                    //                        node.minDistance=constituencies[i].id;
                    //                        nodesThatSimulateIdsConstituencies.push_back(node);
                    //                        
                    //                    }
                    //                    Matrix distanceMatrix;
                    //                    Heap<Node*> idsConstituenciesForOrdering(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                    //                    for(long i=0;i<constituencies.size();i++){
                    //                        Node* node=&nodesThatSimulateIdsConstituencies[i];
                    //                        idsConstituenciesForOrdering.push(node);
                    //                    }
                    //                    std::vector<Node*> orderedIdsConstituencies;
                    //                    while(idsConstituenciesForOrdering.size()>0){
                    //                        Node* node=idsConstituenciesForOrdering.pop();
                    //                        orderedIdsConstituencies.push_back(node);
                    //                    }
                    //                    for(long i=0;i<orderedIdsConstituencies.size();i++){
                    //                        long idA=orderedIdsConstituencies[i]->minDistance;
                    //                        std::stringstream result;
                    //                        result<<orderedIdsConstituencies[i]->minDistance<<" ";
                    //                        
                    //                        for(long j=0;j<orderedIdsConstituencies.size();j++){
                    //                            long idB=orderedIdsConstituencies[j]->minDistance;
                    //                            double distance=Functions::getManhattanDistance(coordinatesOfConstituencies[idA], coordinatesOfConstituencies[idB]);
                    //                            //                            distanceMatrix.set(distance, idA, idB);
                    //                            result<<distance<<" ";
                    //                            
                    //                        }
                    //                        std::vector<std::string> resultVector;
                    //                        resultVector.push_back(result.str());
                    //                        fileName.str("");
                    //                        fileName<<Configuration::folderOut()<<"distanceMatrixOfConstituencies.txt";
                    //                        textFile.writeToFile(fileName.str(), resultVector, true);
                    //                    }
                    
                    
                }
                if (modeCalculation==REMOVE_NODES_FROM_GRAPH_EXTRACT_CLUSTERS_AND_CALCULATE_DIAMETER){
                    //                    std::cout<<"START0"<<'\n';
                    Graph currentGraph;
                    mainGraph.copyGraph(&mainGraph, &currentGraph,false);
                    for(long distance=startDistance; distance<endDistance; distance+=separationBetweenDistances)
                    {
                        //                        std::cout<<"START1 "<<initPercentageNodes<<" "<<topPercentageNodes<<" "<<separationBetweenPercentages<<'\n';
                        Graph newGraph;
                        for(float percentageOfRemovedNodes=initPercentageNodes;percentageOfRemovedNodes<topPercentageNodes;percentageOfRemovedNodes+=separationBetweenPercentages){
                            std::vector<double> fractalDimensions;
                            //                            std::cout<<"START2"<<'\n';
                            for(long repetitions=initRepetitions;repetitions<endRepetitions;repetitions++){
                                
                                newGraph.resetGraph();
                                currentGraph.removeNodesFromGraph(&currentGraph,newGraph, percentageOfRemovedNodes);
                                
                                std::vector<Graph> clusters;
                                
                                newGraph.calculateClusterUsingNetworkPercolation(distance,clusters,false,true,"",minClusterSize);
                                //                        std::cout<<"en main "<<&(clusters[0])<<'\n';
                                //                        std::vector<Graph> clusters=calculateNetworkPercolation(&mainGraph,distance,false,false,true);
                                
                                
                                
                                double minClusterSizeForSaving=minClusterSize;
                                bool save;
                                if(repetitions==initRepetitions){
                                    save=true;
                                }else{
                                    save=false;
                                }
                                for(long numCluster=0;numCluster<clusters.size();numCluster++){
                                    if(save&&clusters[numCluster].nodes.size()>minClusterSizeForSaving)
                                    {
                                        ArchivoTexto textFile;
                                        std::stringstream nameSS1;
                                        
                                        nameSS1<<Configuration::folderOut()<<"clustered_partial_network_dc"<<distance<<".txt";
                                        
                                        std::string name1=nameSS1.str();
                                        std::vector<std::string> values;
                                        double TSL=0;
                                        std::stringstream valuesSS1;
                                        valuesSS1<<"numCluster"<<","<<"numNodes"<<","<<"idA"<<","<<"idB"<<","<<"weight";
                                        std::string valuesS1=valuesSS1.str();
                                        //  values.push_back(valuesS1);
                                        for(long j=0; j<clusters[numCluster].nodes.size(); j++)
                                        {
                                            for(long i=0; i<clusters[numCluster].nodes[j].transitions.size(); i++)
                                            {
                                                //                    cluster.push_back(&nodes[idNode]);
                                                TSL+=clusters[numCluster].nodes[j].transitions[i]->weight;
                                                std::stringstream valuesSS;
                                                //                    valuesSS<<numClusters<<" "<<transitionsInCluster[i]->a->id<<" "<<transitionsInCluster[i]->b->id<<" "<<transitionsInCluster[i]->weight<<" "<<std::to_string(transitionsInCluster[i]->a->location.x)<<" "<<std::to_string(transitionsInCluster[i]->a->location.y)<<" "<<std::to_string(transitionsInCluster
                                                valuesSS<<numCluster<<","<<clusters[numCluster].nodes.size()<<","<<clusters[numCluster].nodes[j].transitions[i]->a->originalID<<","<<clusters[numCluster].nodes[j].transitions[i]->b->originalID<<","<<clusters[numCluster].nodes[j].transitions[i]->weight<<","<<clusters[numCluster].nodes[j].transitions[i]->a->location.x<<","<<clusters[numCluster].nodes[j].transitions[i]->a->location.y<<","<<clusters[numCluster].nodes[j].transitions[i]->b->location.x<<","<<clusters[numCluster].nodes[j].transitions[i]->b->location.y;
                                                std::string valuesS=valuesSS.str();
                                                values.push_back(valuesS);
                                                
                                            }
                                        }
                                        
                                        textFile.writeToFile(name1, values, true);
                                    }
                                }
                                
                                
                                std::cout<<"START"<<'\n';
                                std::vector<std::string> resultsAprox;
                                std::vector<std::string> resultsPrecise;
                                //        if(timer.getTimes().size()>0)
                                //        {
                                //        std::cout<<timer.getTimes()[0]<<'\n';
                                //            std::stringstream timesSS;
                                //                                std::stringstream nameTimesSS;
                                //                                nameTimesSS<<Configuration::folder()<<"results/clustersFromPercolation/clustersWithCorrectedIDs/results_network_dc"<<distance<<"_times.txt";
                                //            std::string name2=nameSS2.str();
                                //            timer.saveToFile(name2);
                                //        }
                                
                                
                                std::stringstream resultsAproxSS;
                                resultsAproxSS<<"clusterId"<<" "<<"numNodes"<<" "<<"diameterMetric"<<" "<<"diameterTopological";
                                resultsAprox.clear();
                                resultsAprox.push_back(resultsAproxSS.str());
                                //                }else{
                                
                                
                                std::stringstream nameAproxSS;
                                nameAproxSS<<Configuration::folderOut()<<"results_diameterCalculationAprox_dc"<<distance<<"per"<<percentageOfRemovedNodes<<"rep"<<repetitions<<".txt";
                                textFile.writeToFile(nameAproxSS.str(), resultsAprox, true);
                                
                                std::vector<Point2d> pointsForCorrelation;
                                
                                for (int numClusterTemp=0; numClusterTemp<clusters.size(); numClusterTemp++)
                                    
                                {
                                    
                                    Graph* cluster=&(clusters[numClusterTemp]);
                                    if(cluster->nodes.size()>minClusterSize){
                                        cluster->transformToBidirectional();
                                        //                                cluster.resetGraph();
                                        //            mainGraph.numberNodes=0;
                                        
                                        //                        textFile.parseNCOLWithCoordinatesAndId(ncolsTextLines[numClusterTemp],&mainGraph,",");
                                        //                                cluster.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
                                        //                                cluster.insertTopologicalWeights();
                                        //                                cluster.transformToBidirectional();
                                        //                                    std::cout<<"Finished parsing cluster, numNodes: "<<cluster->nodes.size()<<'\n';
                                        
                                        std::vector<std::string> times;
                                        std::vector<Node*> externalNodesTemp;
                                        std::vector<Transition> originDestinationsPairs;
                                        ArchivoTexto textFileAprox;
                                        ArchivoTexto textFilePrecise;
                                        //                if(mainGraph.nodes.size()>250000){
                                        //                if(true){
                                        //                std::cout<<"Graph too big, using aproximation"<<'\n';
                                        
                                        
                                        if(typeOfCalculation==APROX){
                                            
                                            std::stringstream aproxSS;
                                            aproxSS<<"Aproximation "<<cluster->nodes.size()<<" ";
                                            
                                            timer.start(aproxSS.str());
                                            RTree rTree(RTree::A_STAR);
                                            originDestinationsPairs=rTree.getOriginDestinationsPairsOfExternalNodesForAproxDiameterCalculation(&clusters[numClusterTemp]);
                                            //                std::cout<<"Origin Destinations generated"<<'\n';
                                            cluster->calculateDiameter(Graph::METRIC,Configuration::NON_PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                                            //                                                                                    cluster->calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::NON_PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                                            //                mainGraph.calculateDiameter(<#int typeOfDistance#>, <#bool parallel#>, <#bool calculateCentralitiesSimultaneously#>, <#bool precise#>, <#std::vector<Node *> &externalNodes#>, <#std::vector<Transition> &originDestinationPairs#>, <#bool withHeuristic#>, <#double (*function)(Node *, Node *)#>)
                                            timer.stop();
                                            //                                            if(timer.active){
                                            //                                                times.clear();
                                            //                                                times.push_back(time);
                                            //                                                textFile.writeToFile(nameTimesSS.str(), times, true);
                                            //                                            }
                                            std::stringstream resultsAproxSS;
                                            resultsAproxSS<<numClusterTemp<<" "<<cluster->nodes.size()<<" "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                                            resultsAprox.clear();
                                            resultsAprox.push_back(resultsAproxSS.str());
                                            //                                        //                }else{
                                            //
                                            //
                                            //                                        std::stringstream nameAproxSS;
                                            //                                        nameAproxSS<<Configuration::folder()<<"results/clustersFromPercolation/UK/diameters/results_diameterCalculationAprox_"<<distance<<".txt";
                                            textFileAprox.writeToFile(nameAproxSS.str(), resultsAprox, true);
                                            
                                            //                                        std::cout<<"Aprox "<<cluster->id<<"/"<<clusters.size()<<" numNodes "<<cluster->nodes.size()<<" diameterMetric: "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
                                        }
                                        
                                        if(typeOfCalculation==PRECISE){
                                            
                                            
                                            std::stringstream preciseSS;
                                            preciseSS<<"Precise "<<cluster->nodes.size()<<" ";
                                            timer.start(preciseSS.str());
                                            //                std::cout<<"Calculating using precise dijkstra all to all"<<'\n';
                                            cluster->calculateDiameter(Graph::METRIC,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                                            //                                        cluster->calculateDiameter(Graph::TOPOLOGICAL,Configuration::PARALLEL,Configuration::NO_CALCULATE_CENTRALITIES,Configuration::PRECISE,externalNodesTemp,originDestinationsPairs,Configuration::NO_WITH_HEURISTIC,&Graph::metricHeuristic);
                                            timer.stop();
                                            //                                            if(timer.active){
                                            //                                                times.clear();
                                            //                                                times.push_back(time);
                                            //                                                textFile.writeToFile(nameTimesSS.str(), times, true);
                                            //                                            }
                                            std::stringstream resultsPreciseSS;
                                            resultsPreciseSS<<numClusterTemp<<" "<<cluster->nodes.size()<<" "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::METRIC)[0]]<<" "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                                            resultsPrecise.clear();
                                            resultsPrecise.push_back(resultsPreciseSS.str());
                                            std::stringstream namePreciseSS;
                                            namePreciseSS<<Configuration::folder()<<"results/clustersFromPercolation/diameters/results_diameterCalculationPrecise_"<<distance<<".txt";
                                            textFilePrecise.writeToFile(namePreciseSS.str(), resultsPrecise, true);
                                            //                }
                                            
                                            std::cout<<"Precise "<<numClusterTemp<<"/"<<clusters.size()<<" numNodes "<<cluster->nodes.size()<<" diameterMetric: "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::METRIC)[0]]<<" diameterTopological: "<<cluster->diameters[cluster->getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<<'\n';
                                        }
                                        pointsForCorrelation.push_back(Point2d(log(cluster->diameters[cluster->getIndexesOfDistanceType(Graph::METRIC)[0]]),log((double)(cluster->nodes.size()))));
                                        
                                    }
                                }
                                LinearRegression linearRegression;
                                linearRegression.calculate(pointsForCorrelation);
                                fractalDimensions.push_back(linearRegression.slope);
                                std::cout<<"--------------------> fractal dimension "<<linearRegression.slope<<'\n';
                                pointsForCorrelation.clear();
                            }
                            
                            
                            
                            std::stringstream nameFractalDimensionSS;
                            nameFractalDimensionSS<<Configuration::folderOut()<<"fractalDimensionRepetitions"<<distance<<"removedPercentage"<<percentageOfRemovedNodes<<".txt";
                            //                        std::cout<<"name of file fractal dimension "<<nameFractalDimensionSS.str()<<'\n';
                            textFile.writeToFile(nameFractalDimensionSS.str(), fractalDimensions, false);
                            bool all0=true;
                            for(int i=0;i<fractalDimensions.size();i++){
                                if(fractalDimensions[i]!=0){
                                    all0=false;
                                }
                            }
                            if(all0){
                                percentageOfRemovedNodes=100;
                            }
                            fractalDimensions.clear();
                        }
                        //                        currentGraph.copyGraph(&newGraph, &currentGraph);
                    }
                }
                if (modeCalculation==REMOVE_NODES_FROM_GRAPH_EXTRACT_CLUSTERS_USING_SPATIAL_PERCOLATION){
                    //                    std::cout<<"START0"<<'\n';
                    Graph currentGraph;
                    mainGraph.copyGraph(&mainGraph, &currentGraph,false);
                    for(long distance=startDistance; distance<endDistance; distance+=separationBetweenDistances)
                    {

                        Graph newGraph;
//                        std::vector<Graph> clusters;
                        for(float percentageOfRemovedNodes=initPercentageNodes;percentageOfRemovedNodes<topPercentageNodes;percentageOfRemovedNodes+=separationBetweenPercentages){
                            std::vector<double> fractalDimensions;
                            //                            std::cout<<"START2"<<'\n';
                            for(long repetitions=initRepetitions;repetitions<endRepetitions;repetitions++){
                                
                                newGraph.resetGraph();
                                currentGraph.removeNodesFromGraph(&currentGraph,newGraph, percentageOfRemovedNodes);
                                
//                                clusters.clear();
                                

                                
//                                newGraph.generateSpatialPercolation(&newGraph, distance, clusters);
                                double minX=INFINITY;
                                double minY=INFINITY;
                                double maxX=0;
                                double maxY=0;
                                SparseMatrix matrix;
                                
                                for(long i=0;i<newGraph.nodes.size();i++){
                                    newGraph.nodes[i].location.x=round(newGraph.nodes[i].location.x/distance);
                                    newGraph.nodes[i].location.y=round(newGraph.nodes[i].location.y/distance);
                                    currentGraph.nodes[i].location.x=round(currentGraph.nodes[i].location.x/distance)*distance;
                                    currentGraph.nodes[i].location.y=round(currentGraph.nodes[i].location.y/distance)*distance;
                                    if(newGraph.nodes[i].location.x<minX){
                                        minX=newGraph.nodes[i].location.x;
                                    }
                                    if(newGraph.nodes[i].location.y<minY){
                                        minY=newGraph.nodes[i].location.y;
                                    }
                                    if(newGraph.nodes[i].location.x>maxX){
                                        maxX=newGraph.nodes[i].location.x;
                                    }
                                    if(newGraph.nodes[i].location.y>maxY){
                                        maxY=newGraph.nodes[i].location.y;
                                    }
                                    
                                }
                                long moduleMatrix=(maxX-minX)/distance;
                                matrix.module=moduleMatrix;
                                for(long i=0;i<newGraph.nodes.size();i++){
                                    long coordX=(newGraph.nodes[i].location.x-minX)/distance;
                                    long coordY=(newGraph.nodes[i].location.y-minY)/distance;
                                    matrix.add(&newGraph.nodes[i], coordX, coordY);
                                }
                                
                                long numCluster=0;
                               
                                

                                
                                
                                double minClusterSizeForSaving=minClusterSize;
                                bool save;

                                save=true;
                                
                                
                                for(auto it = matrix.nodes.begin(); it != matrix.nodes.end(); ++it ){
                                    if(save&&it->second.size()>minClusterSizeForSaving)
                                    {
                                        ArchivoTexto textFile;
                                        std::stringstream nameSS1;
                                        
                                        nameSS1<<Configuration::folderOut()<<"clustered_partial_network_dc"<<distance<<".txt";
                                        
                                        std::string name1=nameSS1.str();
                                        std::vector<std::string> values;
                                        //                                        double TSL=0;
                                        std::stringstream valuesSS1;
                                        valuesSS1<<"numCluster"<<","<<"numNodes"<<","<<"idA"<<","<<"idB"<<","<<"weight";
                                        std::string valuesS1=valuesSS1.str();
                                        
                                        for(long j=0; j<it->second.size(); j++)
                                        {
                                            std::stringstream valuesSS;
                                            valuesSS<<numCluster<<","<<it->second.size()<<","<<it->second[j]->originalID;
                                            
                                            values.push_back(valuesSS.str());
                                            
                                            
                                        }
                                        
                                        textFile.writeToFile(name1, values, true);
                                    }
                                }
                                
                                
                                
                                
//
//                                for(long numCluster=0;numCluster<clusters.size();numCluster++){
//                                    if(save&&clusters[numCluster].nodes.size()>minClusterSizeForSaving)
//                                    {
//                                        ArchivoTexto textFile;
//                                        std::stringstream nameSS1;
//                                        
//                                        nameSS1<<Configuration::folderOut()<<"clustered_partial_network_dc"<<distance<<".txt";
//                                        
//                                        std::string name1=nameSS1.str();
//                                        std::vector<std::string> values;
////                                        double TSL=0;
//                                        std::stringstream valuesSS1;
//                                        valuesSS1<<"numCluster"<<","<<"numNodes"<<","<<"idA"<<","<<"idB"<<","<<"weight";
//                                        std::string valuesS1=valuesSS1.str();
//
//                                        for(long j=0; j<clusters[numCluster].nodes.size(); j++)
//                                        {
//                                            std::stringstream valuesSS;
//                                            valuesSS<<numCluster<<","<<clusters[numCluster].nodes.size()<<","<<clusters[numCluster].nodes[j].originalID;
//
//                                            values.push_back(valuesSS.str());
//                                            
//
//                                        }
//                                        
//                                        textFile.writeToFile(name1, values, true);
//                                    }
//                                }
                                
                                

                            }

                        }
//                        currentGraph.resetGraph();
//                        currentGraph.generateSuperGraphFromClusters(clusters, &currentGraph);

                    }
                }
                if(modeCalculation==CALCULATE_NETWORK_PERCOLATION)
                {
                    for(long i=startDistance; i<endDistance; i+=separationBetweenDistances)
                    {
                        calculateNetworkPercolation(&mainGraph,i,true,false,Configuration::folderOut(),minClusterSize);
                        //                        calculateNetworkPercolation(<#Graph *graph#>, <#double distanceLimit#>, <#bool saveFilesClusters#>, <#bool returnClusters#>, <#std::string nameFolderForFiles#>, <#long minClusterSizeForSaving#>)
                    }
                    //                    mainGraph.calculateCentralities=false;
                    //                    mainGraph.calculateGlobalProperties=true;
                    
                    
                }
                else if(modeCalculation==CALCULATE_FUZZY_NETWORK_PERCOLATION)
                {
                    
                    calculateFuzzyNetworkPercolationAndCentralities(&mainGraph);
                    mainGraph.calculateCentralities=false;
                    mainGraph.calculateGlobalProperties=false;
                    
                    
                }
                else if (modeCalculation==CALCULATE_DIJKSTRA_PARALLEL_ALLTOALL)
                {
                    //                    int start = getMilliCount();
                    //                    double numNodesPerThread=floor(mainGraph.nodes.size()/numThreads);
                    //                    for (int i=0; i<numThreads; i++)
                    //                    {
                    //
                    //                        long startNode=i*numNodesPerThread;
                    //                        long endNode=(i+1)*numNodesPerThread;
                    //                        if (i==numThreads-1)
                    //                        {
                    //                            endNode=mainGraph.nodes.size();
                    //                        }
                    //                        //                    threads.push_back(std::thread(calculateGraphFromCluster,&graphs[i],combinedRadius,startNode,endNode,i));
                    //                        //                    calculateGraphFromCluster(&mainGraph, 0, 0, mainGraph.nodes.size());
                    //                        threads.push_back(std::thread(calculateGraphFromCluster,&graphs[i],0,startNode,endNode));
                    //
                    //                    }
                    //
                    //                    for(auto& thread : threads)
                    //                    {
                    //                        thread.join();
                    //                    }
                    //
                    //                    milliSecondsElapsed = getMilliSpan(start);
                }
                else if (modeCalculation==CALCULATE_QTREE)
                {
                    
                    int start = getMilliCount();
                    
                    RTree rTree(RTree::A_STAR);
                    
                    //                    originDestinationPairs.clear();
                    //                    rTree.mainCluster.
                    rTree.generateCornersOfMainCluster(&mainGraph);
                    //                    std::cout<<"QTree created"<<'\n';
                    for(int i=0; i<mainGraph.nodes.size(); i++)
                    {
                        Node* node=&(mainGraph.nodes[i]);
                        rTree.mainCluster.addNode(node);
                    }
                    //                    std::cout<<"nodes added"<<'\n';
                    
                    
                    
                    
                    std::vector<Transition> originDestinationPairs;
                    //
                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    
                    for(long i=0; i<clustersExternalLeaves.size(); i++)
                    {
                        for(long j=0; j<clustersExternalLeaves.size(); j++)
                        {
                            if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
                            {
                                Transition trans;
                                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                                originDestinationPairs.push_back(trans);
                            }
                            
                        }
                    }
                    
                    //TODO turn this on if you want it to work
                    //                    rTree.generateRTreeGraph(mainGraph,originDestinationPairs);
                    //                    std::cout<<"extended graph generated"<<'\n';
                    
                    //                    long i=10;
                    
                    
                    
                    
                    
                    
                    //                    for(long i=0;i<mainGraph.nodes.size();i++){
                    //                        for(long j=0;j<mainGraph.nodes.size();j++){
                    //                            if (i!=j){
                    //                                Node& a=mainGraph.nodes[i];
                    //                                Node& b=mainGraph.nodes[j];
                    //                                ClusterRTree* clusterCommonLevel=rTree.getCommonLevelOfTwoNodes(&a, &b);
                    //                                double distance=rTree.AStar(&a,&b);
                    ////                                if (distance>=4195){
                    //                                    std::cout<<distance<<", "<<clusterCommonLevel->depth<<" "<<a.originalID<<" "<<b.originalID<<'\n';
                    ////                                }
                    //                                if (distance>mainGraph.diameterWeighted){
                    //                                    mainGraph.diameterWeighted=distance;
                    //                                }
                    //                            }
                    //                        }
                    //                    }
                    //                    std::cout<<"AStar calculated"<<'\n';
                    
                    
                    std::vector<double> distances=rTree.calculateDistances(originDestinationPairs);
                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
                    
                    for(long i=0; i<distances.size(); i++)
                    {
                        //                            std::cout<<"distances "<<distances[i]<<" < "<<mainGraph.diameterWeighted<<'\n';
                        if(mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<distances[i]&&distances[i]<INFINITY)
                        {
                            mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=distances[i];
                        }
                    }
                    
                    
                    //                    mainGraph.diameterWeighted=rTree.calculateDiameter();
                    
                    
                    //                    mainGraph.diameterWeighted=rTree.calculateAllToAllDistances();
                    milliSecondsElapsed = getMilliSpan(start);
                    
                    
                    
                    
                    //                    timesSS<<mainGraph.nodes.size()<<" "<<milliSecondsElapsed<<'\n';
                    
                    //                    std::string timeCalculation=timesSS.str();
                    //                    std::vector<std::string> times;
                    //                    times.push_back(timeCalculation);
                    //                    textFile.writeToFile("/Users/carlos/Documents/results/results_network_dc100_times.txt", times, true);
                    
                    
                    //                    if(rTree.mainCluster.timer.active)
                    //                    {
                    //                        ArchivoTexto textFile;
                    //                        std::stringstream nameSS;
                    //                        nameSS<<Configuration::folder()<<"results/individual_times.txt";
                    //                        std::string name=nameSS.str();
                    //                        textFile.writeToFile(name, rTree.mainCluster.timer.getTimes(), true);
                    //                        //                        textFile.writeToFile("C:/Users/Carlos/Documents/_TRABAJO/CASA/results/individual_times.txt", rTree.mainCluster.timer.getTimes(), true);
                    //                    }
                    
                    //                    std:cout<<"diameter calculated "<<mainGraph.diameterWeighted<<'\n';
                    //                    rTree.mainCluster.sons.clear();
                    //                    rTree.mainCluster.originalGraph->nodes.clear();
                    //                    rTree.mainCluster.graph.nodes.clear();
                    ////                    rTree.mainCluster.graph.
                    //                    rTree.mainCluster.graphTemp.nodes.clear();
                    //                    rTree.mainCluster.clustersByDepth.clear();
                    
                    //                    mainGraph.init();
                    
                    std::cout<<"diameter calculated"<<'\n';
                }
                else if (modeCalculation==CALCULATE_ASTAR)
                {
                    
                    int start = getMilliCount();
                    RTree rTree(RTree::A_STAR);
                    
                    //                    originDestinationPairs.clear();
                    //                    rTree.mainCluster.
                    rTree.generateCornersOfMainCluster(&mainGraph);
                    //                    std::cout<<"QTree created"<<'\n';
                    for(int i=0; i<mainGraph.nodes.size(); i++)
                    {
                        Node* node=&(mainGraph.nodes[i]);
                        rTree.mainCluster.addNode(node);
                    }
                    std::vector<Transition> originDestinationPairs;
                    
                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    
                    for(long i=0; i<clustersExternalLeaves.size(); i++)
                    {
                        for(long j=i+1; j<clustersExternalLeaves.size(); j++)
                        {
                            
                            if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
                            {
                                Transition trans;
                                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                                originDestinationPairs.push_back(trans);
                            }
                            
                        }
                    }
                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
                    for(long i=0; i<originDestinationPairs.size(); i++)
                    {
                        
                        double distance=mainGraph.AStar(originDestinationPairs[i].a,originDestinationPairs[i].b,&Graph::metricHeuristic);
                        
                        if(mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<distance&&distance<INFINITY)
                        {
                            mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=distance;
                        }
                        //                        std::vector<double> topologicalDistance=mainGraph.AStarOtherWeights(originDestinationPairs[i].a,originDestinationPairs[i].b);
                        //                        if(mainGraph.diameterTopological<topologicalDistance[0]&&topologicalDistance[0]<INFINITY){
                        //                            mainGraph.diameterTopological=topologicalDistance[0];
                        //                        }
                        
                    }
                    
                    milliSecondsElapsed = getMilliSpan(start);
                    std::cout<<"diameter metric calculated"<<'\n';
                }
                else if (modeCalculation==CALCULATE_DIKSTRA_FROMUNIQUENODES)
                {
                    int start = getMilliCount();
                    RTree rTree(RTree::A_STAR);
                    
                    //                    originDestinationPairs.clear();
                    //                    rTree.mainCluster.
                    rTree.generateCornersOfMainCluster(&mainGraph);
                    //                    std::cout<<"QTree created"<<'\n';
                    for(int i=0; i<mainGraph.nodes.size(); i++)
                    {
                        Node* node=&(mainGraph.nodes[i]);
                        rTree.mainCluster.addNode(node);
                    }
                    std::vector<Transition> originDestinationPairs;
                    
                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    
                    for(long i=0; i<clustersExternalLeaves.size(); i++)
                    {
                        for(long j=0; j<clustersExternalLeaves.size(); j++)
                        {
                            if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
                            {
                                Transition trans;
                                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                                originDestinationPairs.push_back(trans);
                            }
                            
                        }
                    }
                    BST<Node*> uniqueNodesBST;
                    
                    for(long i=0; i<originDestinationPairs.size(); i++)
                    {
                        //                            if (!uniqueNodesBST.exist(originDestinationPairs[i].a->id)){
                        uniqueNodesBST.add(originDestinationPairs[i].a->id,originDestinationPairs[i].a);
                        //                            }else{
                        //                            }
                    }
                    std::vector<Node*> uniqueNodes=uniqueNodesBST.getAll();
                    mainGraph.calculateOtherDistances=false;
                    for(long i=0; i<uniqueNodes.size(); i++)
                    {
                        std::vector<Node*> nodesCutoff;
                        Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                        Node* nodeTemp=uniqueNodes[i];
                        nodeTemp->minDistance=0;
                        nodesCutoff.push_back(nodeTemp);
                        
                        nodesToCheckDijkstra.push(nodeTemp);
                        
                        mainGraph.calculateDijkstraSpeed(nodeTemp, 0, nodesCutoff,nodesToCheckDijkstra);
                        
                        
                        for(long h=0; h<nodesCutoff.size(); h++)
                        {
                            
                            nodesCutoff[h]->minDistance=INFINITY;
                            nodesCutoff[h]->inDijkstra=false;
                            nodesCutoff[h]->inCutoff=false;
                            nodesCutoff[h]->numOtherChildren.clear();
                            nodesCutoff[h]->parent=NULL;
                            
                        }
                        nodesCutoff.clear();
                        nodesToCheckDijkstra.clear();
                    }
                    milliSecondsElapsed = getMilliSpan(start);
                    std::cout<<"diameter topological calculated"<<'\n';
                }
                else if(modeCalculation==CALCULATE_DIJKSTRA_STOPCRITERIA)
                {
                    int start = getMilliCount();
                    RTree rTree(RTree::A_STAR);
                    
                    //                    originDestinationPairs.clear();
                    //                    rTree.mainCluster.
                    rTree.generateCornersOfMainCluster(&mainGraph);
                    //                    std::cout<<"QTree created"<<'\n';
                    for(int i=0; i<mainGraph.nodes.size(); i++)
                    {
                        Node* node=&(mainGraph.nodes[i]);
                        rTree.mainCluster.addNode(node);
                    }
                    std::vector<Transition> originDestinationPairs;
                    
                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    
                    for(long i=0; i<clustersExternalLeaves.size(); i++)
                    {
                        for(long j=0; j<clustersExternalLeaves.size(); j++)
                        {
                            if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
                            {
                                Transition trans;
                                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                                originDestinationPairs.push_back(trans);
                            }
                            
                        }
                    }
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
                    
                    std::cout<<"size unique nodes "<<uniqueNodes.size()<<'\n';
                    mainGraph.calculateOtherDistances=true;
                    for(long i=0; i<uniqueNodes.size(); i++)
                    {
                        BST<Node*> uniqueNodesDestinations;
                        for(long j=0; j<originDestinationPairs.size(); j++)
                        {
                            if (originDestinationPairs[j].a==uniqueNodes[i])
                            {
                                uniqueNodesDestinations.add(originDestinationPairs[i].b->id,originDestinationPairs[i].b);
                            }
                        }
                        
                        std::vector<Node*>uniqueDestinations=uniqueNodesDestinations.getAll();
                        std::vector<Node*> nodesCutoff;
                        Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                        Node* nodeTemp=uniqueNodes[i];
                        nodeTemp->minDistance=0;
                        nodesCutoff.push_back(nodeTemp);
                        
                        nodesToCheckDijkstra.push(nodeTemp);
                        
                        mainGraph.calculateDijkstraSpeedToSetOfNodes(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra,uniqueDestinations);
                        
                        
                        for(long h=0; h<nodesCutoff.size(); h++)
                        {
                            
                            nodesCutoff[h]->minDistance=INFINITY;
                            nodesCutoff[h]->inDijkstra=false;
                            nodesCutoff[h]->inCutoff=false;
                            nodesCutoff[h]->numOtherChildren.clear();
                            nodesCutoff[h]->parent=NULL;
                            
                        }
                        nodesCutoff.clear();
                        nodesToCheckDijkstra.clear();
                        uniqueNodesDestinations.deleteAll();
                    }
                    milliSecondsElapsed = getMilliSpan(start);
                    std::cout<<"diameter calculated"<<'\n';
                }
                else if (modeCalculation==CALCULATE_ASTAR_METRIC_AND_DIJKSTRA_TOPO)
                {
                    int start = getMilliCount();
                    RTree rTree(RTree::A_STAR);
                    
                    //                    originDestinationPairs.clear();
                    //                    rTree.mainCluster.
                    rTree.generateCornersOfMainCluster(&mainGraph);
                    //                    std::cout<<"QTree created"<<'\n';
                    for(int i=0; i<mainGraph.nodes.size(); i++)
                    {
                        Node* node=&(mainGraph.nodes[i]);
                        rTree.mainCluster.addNode(node);
                    }
                    std::vector<Transition> originDestinationPairs;
                    
                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    
                    for(long i=0; i<clustersExternalLeaves.size(); i++)
                    {
                        for(long j=i+1; j<clustersExternalLeaves.size(); j++)
                        {
                            
                            if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0)
                            {
                                Transition trans;
                                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                                originDestinationPairs.push_back(trans);
                            }
                            
                        }
                    }
                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
                    for(long i=0; i<originDestinationPairs.size(); i++)
                    {
                        
                        double distance=mainGraph.AStar(originDestinationPairs[i].a,originDestinationPairs[i].b,&Graph::metricHeuristic);
                        
                        if(mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]<distance&&distance<INFINITY)
                        {
                            mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=distance;
                        }
                        //                        std::vector<double> topologicalDistance=mainGraph.AStarOtherWeights(originDestinationPairs[i].a,originDestinationPairs[i].b);
                        //                        if(mainGraph.diameterTopological<topologicalDistance[0]&&topologicalDistance[0]<INFINITY){
                        //                            mainGraph.diameterTopological=topologicalDistance[0];
                        //                        }
                        
                    }
                    
                    milliSecondsElapsed = getMilliSpan(start);
                    std::cout<<"diameter metric calculated"<<'\n';
                    //                    int start = getMilliCount();
                    //                    RTree rTree(RTree::A_STAR);
                    //
                    //                    //                    originDestinationPairs.clear();
                    //                    //                    rTree.mainCluster.
                    //                    rTree.generateCornersOfMainCluster(mainGraph);
                    //                    //                    std::cout<<"QTree created"<<'\n';
                    //                    for(int i=0;i<mainGraph.nodes.size();i++){
                    //                        Node* node=&(mainGraph.nodes[i]);
                    //                        rTree.mainCluster.addNode(node);
                    //                    }
                    //                    std::vector<Transition> originDestinationPairs;
                    //
                    //                    //                    long numberTimes=mainGraph.nodes.size()/25;
                    //                    std::vector<ClusterRTree*> clustersExternalLeaves=rTree.mainCluster.externalLeavesById.getAll();
                    //
                    //                    for(long i=0;i<clustersExternalLeaves.size();i++){
                    //                        for(long j=0;j<clustersExternalLeaves.size();j++){
                    //                            if(clustersExternalLeaves[i]->nodesInCluster.size()>0&&clustersExternalLeaves[j]->nodesInCluster.size()>0){
                    //                                Transition trans;
                    //                                trans.a=clustersExternalLeaves[i]->nodesInCluster[0];
                    //                                trans.b=clustersExternalLeaves[j]->nodesInCluster[0];
                    //                                originDestinationPairs.push_back(trans);
                    //                            }
                    //
                    //                        }
                    //                    }
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
                    
                    std::cout<<"size unique nodes "<<uniqueNodes.size()<<'\n';
                    mainGraph.calculateOtherDistances=true;
                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=0;
                    for(long i=0; i<uniqueNodes.size(); i++)
                    {
                        BST<Node*> uniqueNodesDestinations;
                        for(long j=0; j<originDestinationPairs.size(); j++)
                        {
                            if (originDestinationPairs[j].a==uniqueNodes[i])
                            {
                                uniqueNodesDestinations.add(originDestinationPairs[i].b->id,originDestinationPairs[i].b);
                            }
                        }
                        
                        std::vector<Node*>uniqueDestinations=uniqueNodesDestinations.getAll();
                        std::vector<Node*> nodesCutoff;
                        Heap<Node*> nodesToCheckDijkstra(Heap<Node*>::MIN,&Graph::compareByDistance,&Graph::getMinDistance,&Node::setIndexInHeap, &Node::getIndexInHeap,true);
                        Node* nodeTemp=uniqueNodes[i];
                        nodeTemp->minDistance=0;
                        nodesCutoff.push_back(nodeTemp);
                        
                        nodesToCheckDijkstra.push(nodeTemp);
                        
                        mainGraph.calculateDijkstraSpeedOtherDistancesToSetOfNodes(nodeTemp, 0, nodesCutoff, nodesToCheckDijkstra,uniqueDestinations,0,false);
                        
                        
                        for(long h=0; h<nodesCutoff.size(); h++)
                        {
                            if(mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]<nodesCutoff[h]->minOtherDistances[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]])
                            {
                                mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=nodesCutoff[h]->minOtherDistances[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                            }
                            nodesCutoff[h]->minOtherDistances[0]=INFINITY;
                            nodesCutoff[h]->inDijkstra=false;
                            nodesCutoff[h]->inCutoff=false;
                            nodesCutoff[h]->numOtherChildren.clear();
                            nodesCutoff[h]->otherParents[0]=NULL;
                            
                        }
                        nodesCutoff.clear();
                        nodesToCheckDijkstra.clear();
                        uniqueNodesDestinations.deleteAll();
                    }
                    milliSecondsElapsed = getMilliSpan(start);
                    std::cout<<"diameter topo calculated"<<'\n';
                    
                }
                //                mainGraph.init();
                if (mainGraph.calculateCentralities)
                {
                    if (parallel)
                    {
                        for(int i=0; i<graphs.size(); i++)
                        {
                            for(int j=0; j<mainGraph.nodes.size(); j++)
                            {
                                if (mainGraph.calculateCentralities)
                                {
                                    mainGraph.nodeCount[j]+=graphs[i].nodeCount[j];
                                    mainGraph.TSL[j]+=graphs[i].TSL[j];
                                    mainGraph.betweenness[j]+=graphs[i].betweenness[j];
                                    mainGraph.closeness[j]+=graphs[i].closeness[j];
                                    for (int h=0; h<combinedDistancesToCalculate.size(); h++)
                                    {
                                        mainGraph.betweennessMeasures[h][j]+=graphs[i].betweennessMeasures[h][j];
                                        mainGraph.closenessMeasures[h][j]+=graphs[i].closenessMeasures[h][j];
                                    }
                                }
                                if (mainGraph.calculateDiffussion)
                                {
                                    mainGraph.nodes[j].waterLevel.flow+=graphs[i].nodes[j].waterLevel.flow;
                                }
                            }
                        }
                    }
                    saveFiles(&mainGraph,0,numCluster);
                    
                }
                if (mainGraph.calculateGlobalProperties)
                {
                    //                    if (parallel)
                    //                    {
                    //                        for(int i=0; i<graphs.size(); i++)
                    //                        {
                    //                            if (i==0)
                    //                            {
                    //                                mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    //                                mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    //                                //                                mainGraph.numberNodes=graphs[i].numberNodes;
                    //                                mainGraph.averageLengths[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    //                                mainGraph.averageLengths[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    //                                //
                    //                                //                                mainGraph.topologicalLengthOfMetricDiameter=graphs[i].topologicalLengthOfMetricDiameter;
                    //                                //                                mainGraph.weightedLengthOfTopologicalDiameter=graphs[i].weightedLengthOfTopologicalDiameter;
                    //
                    //                            }
                    //                            else
                    //                            {
                    //                                if (graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]]>mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]])
                    //                                {
                    //                                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    //                                    //                                    mainGraph.topologicalLengthOfMetricDiameter=graphs[i].topologicalLengthOfMetricDiameter;
                    //                                }
                    //                                if (graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]>mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]])
                    //                                {
                    //                                    mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=graphs[i].diameters[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    //                                    //                                    mainGraph.weightedLengthOfTopologicalDiameter=graphs[i].weightedLengthOfTopologicalDiameter;
                    //                                }
                    //                                mainGraph.averageLengths[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]+=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]];
                    //                                mainGraph.averageLengths[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]+=graphs[i].averageLengths[graphs[i].getIndexesOfDistanceType(Graph::METRIC)[0]];
                    //                            }
                    //                        }
                    //                        mainGraph.averageLengths[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]/=(double)(numThreads);
                    //                        mainGraph.averageLengths[mainGraph.getIndexesOfDistanceType(Graph::TOPOLOGICAL)[0]]/=(double)(numThreads);
                    //                    }
                    //                    bool saveHeader=true;
                    //                    if (numCluster>1)
                    //                    {
                    //                        saveHeader=false;
                    //                    }
                    //                    
                    //                    std::stringstream nameSS;
                    //                    nameSS<<Configuration::folder()<<"results/results_network_dc210.txt";
                    //                    std::string name=nameSS.str();
                    //                    //                    saveFilesGlobalProperties(&mainGraph,"/Users/carlos/Documents/results/results_network_dc100.txt",numCluster,saveHeader);
                    //                    saveFilesGlobalProperties(&mainGraph,name,numCluster,saveHeader);
                    //                    //                    saveFilesGlobalProperties(&mainGraph,"/Users/carlos/Documents/apps/results/EU/results_network_dc310.txt",numCluster,saveHeader);
                    //                    //                    saveFilesGlobalProperties(&mainGraph,"/Users/cavargasru/Documents/mechanicity/erez/networks/n0600_d/results_network_dc100.txt",numCluster,saveHeader);
                    //                    
                    //                    
                    //                    
                    //                    
                    //                    ArchivoTexto textFile;
                    //                    std::stringstream timesSS;
                    //                    
                    //                    timesSS<<mainGraph.nodes.size()<<" "<<milliSecondsElapsed<<'\n';
                    //                    
                    //                    std::string timeCalculation=timesSS.str();
                    //                    std::vector<std::string> times;
                    //                    times.push_back(timeCalculation);
                    //                    //                    textFile.writeToFile("/Users/carlos/Documents/results/results_network_dc100_times.txt", times, true);
                    //                    std::stringstream nameSS2;
                    //                    nameSS2<<Configuration::folder()<<"results/results_network_dc100_times.txt";
                    //                    std::string name2=nameSS2.str();
                    //                    textFile.writeToFile(name2, times, true);
                    //                    
                }
                //                mainGraph.nodes.clear();
                //                //                mainGraph.numberNodes=0;
                //                mainGraph.diameters[mainGraph.getIndexesOfDistanceType(Graph::METRIC)[0]]=0;
                //                std::cout<<"-------------------"<<'\n';
            }
            
        }
    }
    
    //    std::cout<<"GETTING NUMBER OF THREADS"<<'\n';
    //	int nProcessors=omp_get_max_threads();
    //    omp_set_num_threads(nProcessors);
    //    std::cout<<"NUMBER OF THREADS "<<nProcessors<<'\n';
    ////////////////////////////////////////////////////
    //    for (int indexRadius=0;indexRadius<radiiCutoff.size();indexRadius++){
    
    
    
    
    
    //    timer.stop();
    //    if(timer.getTimes().size()>0)
    //    {
    ////        std::cout<<timer.getTimes()[0]<<'\n';
    //         std::stringstream timesSS;
    //        std::stringstream nameSS2;
    //        nameSS2<<Configuration::folder()<<"results/clustersFromPercolation/results_network_dc210_times.txt";
    //        std::string name2=nameSS2.str();
    //        timer.saveToFile(name2);
    //    }
    
    
    std::cout<<"END OF PROGRAM"<<'\n';
    
    
}



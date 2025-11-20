#pragma once
#include <fstream> //ifstream, ofstream
#include <string> //string, getline()
//#include "ArrayList.h"
//#include "Linea.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
//class Graph;
//#include "Graph.h"
#include <sstream>
class Grafo;
#include "Grafo.h"
#include "Data.h"
//#include "DualExtendedGraph.h"
#include "Configuration.h"
//#include <Point2d.h>
class TextFile
{
public:
//    ArchivoTexto();
//    virtual ~ArchivoTexto();

//        void parseDXF3d(string name,ArrayList<Linea> * lineas3d);
    static std::vector<double> parseSimpleNumericFile(std::string name);
//    static void parsePajekGraphAndInformationalDual(std::string nameGraphFile,std::string nameDualFile,Graph* graph,Graph* lineGraph,Graph* dualGraph);
//    static void parseNCOLWithCoordinates(std::string name,Graph* graph,std::string separator,bool header);
//    static void parseNCOL(std::string name,Graph* graph,std::string separator,bool header);
//    static void parseNCOLandSeparateCoordinatesFile(std::string nameNCOLFile,std::string nameCoordinatesFile,Graph* graph,std::string separatorNCOL,std::string separatorCoordinates,bool header,bool includeIDTransitions);
//    static void parseNCOLWithNamesEdgesAndSeparateCoordinatesFile(std::string nameNCOLFile,std::string nameCoordinatesFile,Graph* graph,std::string separatorNCOL,std::string separatorCoordinates,bool header);
//    static void parseNCOLWithCoordinates(std::vector<std::string> lines,Graph* graph,std::string separator);
//        static void parseNCOLWithCoordinatesAndId(std::vector<std::string> lines,Graph* graph,std::string separator);
//        void parseCompleteClusterNetworkAndExportToSingleFiles();

    static void readCoordinatesNodes(std::string name,std::string separator);
//    static void addWeightsToGraph(Graph* graph,std::string nameOfFile,std::string separator,bool header,int distanceType);
//        static void includeValuesToPassBetweenness(Graph* graph,std::string nameOfFile,std::string separator,bool header);
//    static void includeMasses(Graph* graph,std::string nameOfFile,std::string separator,bool header);
//    static void includeOriginalDegreeOfNodes(Graph* graph,std::string nameOfFile,std::string separator,bool header);
//    static void includeTripsGeneratedByType(Graph* primalGraph,Graph* lineGraph,std::string nameOfFile,std::string separator,bool header);
//    static std::ifstream file;
    static std::vector<std::string> extractWords(std::string line, std::string separator);
//    static void writeNCOLFile(Graph* graph,std::string fileName);
//    static void writeNCOLFileAndSeparateCoordinatesFile(Graph* graph,std::string fileNameNCOL,std::string fileNameCoordinates,std::string separatorNCOL,std::string separatorCoordinates);
//    static void writeNCOLPlusCoordinatesFile(Graph* graph,std::string fileName);
//    static void writeNCOLPlusCoordinatesFile_PlusNamesAndHierarchicalLevel(Graph* graph,std::string fileName);
//    static void writeNCOLPlusCoordinatesFile_PlusIdTransitions(Graph* graph,std::string fileName);
//    void writeNCOLPlusCoordinatesAndValuesFile(Graph* graph,std::string fileName,std::vector<double> values);
//    static void writeNCOLPlusCoordinatesForQTreeFile(Graph* graph,std::string fileName);
    static std::vector<std::vector<std::string>> importFileClusters(std::string name,std::string separator,long minClusterSize);

//    static void loadClassificationOfNodes(Graph* graph,std::string nameOfFile,std::vector<Graph> &clusters,std::string separator,bool header);

    static void loadVectorWithIds(std::unordered_map<long,std::vector<double> >* result,std::string nameOfFile,std::string separator,bool header);
    static void loadPairsFileOfNodeIdAndClusterId(std::vector<std::vector<signed long long> > &pairs,std::string nameOfFile,std::string separator,bool header);
//    static void loadBetweenness(Graph* graph,long indexOfDistance,std::string nameOfFile,std::string separator,bool header);
    static void loadMassesPercolation(std::unordered_map<long,long>* result,std::string nameOfFile,std::string separator,bool header);
    static void loadPointLocationsAndValue(std::string name,std::vector<Point2d> &points,std::vector<double> &values,bool header,std::string separator);





    /////////////////////
    static bool open (std::string name,std::ifstream &file);
    static void close(std::ifstream &file);
    static std::string getLine(std::ifstream &file);
    static void writeToFile(std::string name,std::vector<double> values,bool append);
    static void writeToFile(std::string name,std::vector<long> values,bool append);
    static void writeToFile(std::string name,std::vector<std::string> values,bool append);
    static void loadData(std::vector<std::string> &ids,std::vector<std::string> &columnNames,std::vector<std::vector<double> > &values,std::string nameOfFile,std::string separator,bool header);
    static void createLineString(Grafo* G,std::string fileName,bool append);
    static std::vector<std::string> getLineString(Grafo* G,std::string fileName,bool append);
    static void parseNCOLandSeparateCoordinatesFile(Grafo* graph,bool directional,std::string nameNCOLFile,std::string nameCoordinatesFile,std::string separatorNCOL,std::string separatorCoordinates,bool header);
    static void parseNCOLandSeparateCoordinatesFile(Grafo* graph,bool directional,std::string nameNCOLFile,std::string nameCoordinatesFile,std::string separatorNCOL,std::string separatorCoordinates,bool header,bool bypassChekingNodes);
//    static void parseNCOLandSeparateCoordinatesFile(Grafo* G,bool directional,std::string nameNCOLFile,std::string nameCoordinatesFile,std::string separatorNCOL,std::string separatorCoordinates,bool header);
    static void saveNCOL(Grafo* G,std::string nameFile);
    static void saveCoordinates(Grafo* G,std::string nameFile);

protected:
private:
};

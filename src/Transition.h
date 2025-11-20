#ifndef TRANSITION_H
#define TRANSITION_H
//#include <Node.h>
#include <vector>
#include <cstddef>

class Node;
#include "Node.h"
//class ClusterRTree;
class Transition
{
public:
    long numColor;
    Transition* transitionThatRepresents;
    Transition* transitionRepresentedBy;
    double firstAngleInPhaseTransition;
    double widthDrawing;
    void checkDirection(bool invert);
    bool inverted;
    bool bidirectional;
    std::string nameRoad;
    double levelHierarchyRoad;
    std::vector<double> hierarchicalValues;
    double numberTimesInPercolationThreshold;
    std::vector<Transition*> transitionsCollapsed;
    bool inCutoff;
    bool transitionOfLineGraphFromNodeOfDegree2;
    Node* nodeOfLineGraphThatRepresentsThis;
    Node* nodeInGraphAfterLineGraphGeneration;
    Transition* getSimetricTransition();
    bool usedInNetworkPercolation;
    long id;
//    long oppositeTransitionId;// refers to id
    Transition();
    virtual ~Transition();
    void setTransition(Node* a, Node* b,double weight,std::vector<double> otherWeights);
    Node* a;
    Node* b;
    long idA;
    long idB;
    signed long long originalIdB;
    signed long long originalID;
//    ClusterRTree* ca;
//    ClusterRTree* cb;
//    Point2d locationA;
//    Point2d locationB;
    std::vector<double> otherWeights;
    double weight;
    
    long idNodeDualA;
    long idNodeDualB;
    
//        Transition* transitionThatRepresents;
//        Transition* getCopy();
//        long id;
//        bool alreadyUsedDijkstra;
//        Transition* equivalentTransitionInOtherDirection;
    bool isPath;
//    std::vector<Transition*> transitionsThatFormThePath;
protected:
private:
};

#endif // TRANSITION_H

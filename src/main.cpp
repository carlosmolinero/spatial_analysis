////
////  main.cpp
////  harmonicCities
////
////  Created by Carlos Molinero on 04/06/2015.
////  Copyright (c) 2015 Carlos Molinero. All rights reserved.
////
//
//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}

//#ifndef hashPoint2d
//#define hashPoint2d
//#include "Point2d.h"
//template <>
//struct std::__1::hash<Point2d > {
//public:
//    size_t operator()(Point2d point) const throw() {
//        //        return hash<double>()(round(point.x*Point2d::PRECISION)/Point2d::PRECISION) ^ hash<double>()(round(point.y*Point2d::PRECISION)/Point2d::PRECISION);
//        return hash<double>()(point.x) ^ hash<double>()(point.y);
//
//    }
//};
//#endif

#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//#include "Programs.h"
#include "Singleton.h"

//#include "Graph.h"
#include "Windows.h"
//#include "InterfaceCityGeneration.h"
//#include "Network.h"
#include "ShapeFile.h"
//#include "LargeGraph.h"
#include "Grafo.h"
#include "DualExtendedGraph.h"
#include "Geometry.h"
#include <unordered_map>
#include "CriticalExponentsPercolation.h"
#include "LinearRegression.h"
#include "Configuration.h"
#include "GeometryGraph.h"
#include "InterfaceCityGeneration.h"
#include "GenerativeProcedures.h"
#include "SpatialInteraction.h"
#include "RoadNetworkGeneration.h"

double width=930;
long counter=0;
//InterfaceCityGeneration interfaceCityGeneration;
//bool constructRoads;
//bool calculateCities;
//bool migrate;
//Graph graph;
//double definitionRoadNetwork=3;

#define DEG2RAD 3.14159/180.0























void line(float x1,float y1,float x2,float y2)
{
    glLineWidth(.5);
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    //    double random=rand()%100;
    glVertex2i(x2,y2);
    glEnd();

    //    glEnableClientState(GL_VERTEX_ARRAY);
    //    glEnableClientState(GL_COLOR_ARRAY);
    //
    //    float width=2;
    //
    //    float para_vertex[]=
    //    {
    //        x1,y1,
    //        x2,y2,
    //        x1+width/2,y1,
    //        x2+width/2,y2,
    //        x1+width,y1,
    //        x2+width,y2
    //
    ////        50,270,
    ////        100,30,
    ////        54,270,
    ////        104,30,
    ////        58,270,
    ////        108,30
    //    };
    //    float para_color[]=
    //    {
    //        1,1,1,    //white
    //        1,1,1,
    //        1,0,0,    //red
    //        1,0,0,
    //        1,1,1,    //white
    //        1,1,1
    //    };
    //    glVertexPointer(2, GL_FLOAT, 0, para_vertex);
    //    glColorPointer(3, GL_FLOAT, 0, para_color);
    //    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    //    glDisableClientState(GL_VERTEX_ARRAY);
    //    glDisableClientState(GL_COLOR_ARRAY);

}

void line(float x1,float y1,float x2,float y2,float width)
{
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    //    double random=rand()%100;
    glVertex2i(x2,y2);
    glEnd();

    //    glEnableClientState(GL_VERTEX_ARRAY);
    //    glEnableClientState(GL_COLOR_ARRAY);
    //
    //    float width=2;
    //
    //    float para_vertex[]=
    //    {
    //        x1,y1,
    //        x2,y2,
    //        x1+width/2,y1,
    //        x2+width/2,y2,
    //        x1+width,y1,
    //        x2+width,y2
    //
    ////        50,270,
    ////        100,30,
    ////        54,270,
    ////        104,30,
    ////        58,270,
    ////        108,30
    //    };
    //    float para_color[]=
    //    {
    //        1,1,1,    //white
    //        1,1,1,
    //        1,0,0,    //red
    //        1,0,0,
    //        1,1,1,    //white
    //        1,1,1
    //    };
    //    glVertexPointer(2, GL_FLOAT, 0, para_vertex);
    //    glColorPointer(3, GL_FLOAT, 0, para_color);
    //    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    //    glDisableClientState(GL_VERTEX_ARRAY);
    //    glDisableClientState(GL_COLOR_ARRAY);

}

void ellipse(double x, double y,float xradius, float yradius)
{
    int i;

    glBegin(GL_LINE_LOOP);

    for(i=0;i<360;i++)
    {
        float degInRad = i*DEG2RAD;
        glVertex2f(cos(degInRad)*xradius+x,sin(degInRad)*yradius+y);
    }

    glEnd();
}
void setColor(float r,float g,float b){
    glColor3f(r/255,g/255,b/255);
}

void setColor(float r,float g,float b,float alpha){
    glColor4f(r/255,g/255,b/255,alpha/255);
}
void setColor(VectorNDim color){
    if(color.values.size()==4){
        glColor4f(color[0]/255,color[1]/255,color[2]/255,color[3]/255);
    }
    if(color.values.size()==3){
        glColor3f(color[0]/255,color[1]/255,color[2]/255);
    }
}
void setColor(VectorNDim color,double alpha){
    if(color.values.size()==4){
        glColor4f(color[0]/255,color[1]/255,color[2]/255,color[3]/255);
    }
    if(color.values.size()==3){
        glColor4f(color[0]/255,color[1]/255,color[2]/255,alpha/255);
    }
}

void point(double x, double y,double radius){
    //        glEnable(GL_POINT_SMOOTH);
    //        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(radius*2);
    glBegin( GL_POINTS);
    glVertex2d(x,y);
    glEnd();
}
void filledCircle(double x, double y,double radius){



    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
                   x + (radius * cos(i *  twicePi / triangleAmount)),
                   y + (radius * sin(i * twicePi / triangleAmount))
                   );
    }
    glEnd();
}

void filledRectangle(double x1,double y1,double x2,double y2){
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glVertex2f(x1, y1);    // x, y
    glVertex2f( x1, y2);
    glVertex2f( x2,  y2);
    glVertex2f(x2, y1);
    glEnd();
}

void rectangle(double x1,double y1,double x2,double y2){
    line(x1,y1,x1,y2);
    line(x1,y2,x2,y2);
    line(x2,y2,x2,y1);
    line(x2,y1,x1,y1);

}
void text(std::string quote,Point2d location,int size){

    //    int lenghOfQuote = (int)quote.length();
    //    glPushMatrix();
    //    glTranslatef(location.x, location.y, 0.0);
    //    //        char* text=(char*)quote.c_str();
    //    char charArray[2000];
    //    double sizeD=(double)(size);
    //    glScalef(sizeD/100,sizeD/100,sizeD/100);
    //    strcpy(charArray, quote.c_str());
    //    for (long i = 0; i < lenghOfQuote; i++)
    //    {
    //        glutStrokeCharacter(GLUT_STROKE_ROMAN,charArray[i]);
    ////                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, charArray[i]);
    //    }
    //    //    glutBitmapString(GLUT_BITMAP_HELVETICA_10,text);
    //    glPopMatrix();


    int lenghOfQuote = (int)quote.length();
    //    glPushMatrix();
    //    glTranslatef(location.x, location.y, 0.0);
    char* text=(char*)quote.c_str();
    //    char charArray[2000];
    //    double sizeD=(double)(size);
    //    glScalef(sizeD/100,sizeD/100,sizeD/100);
    //    strcpy(charArray, quote.c_str());
    //    int len, i;

    glRasterPos2f(location.x,location.y);
    //    len = (int) strlen(string);
    //    for (i = 0; i < len; i++) {
    //        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    //    }
    for (long i = 0; i < lenghOfQuote; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,text[i]);
        //                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, charArray[i]);
    }
    //    glutBitmapString(GLUT_BITMAP_HELVETICA_10,text);
    //    glPopMatrix();



}






void MouseAction(int the_button, int button_state, int x, int y){

    if (the_button==GLUT_LEFT_BUTTON && button_state==GLUT_UP){


        //        std::cout<<"size of window "<<glutGet(GLUT_WINDOW_WIDTH)<<" "<<glutGet(GLUT_WINDOW_HEIGHT)<<'\n';
        //        double scaleTempX=width/glutGet(GLUT_WINDOW_WIDTH)*2;
        //        double scaleTempY=width/glutGet(GLUT_WINDOW_HEIGHT);
        //        nodeInitForPath=quadTreeGenerated.getClosestNode(Point2d(x*scaleTempX,(glutGet(GLUT_WINDOW_HEIGHT)-y)*scaleTempY));


    }
    if (the_button==GLUT_RIGHT_BUTTON && button_state==GLUT_UP){
        //        double scaleTempX=width/glutGet(GLUT_WINDOW_WIDTH)*2;
        //        double scaleTempY=width/glutGet(GLUT_WINDOW_HEIGHT);
        //
        //        Node* node=quadTreeGenerated.getClosestNode(Point2d(x*scaleTempX,(glutGet(GLUT_WINDOW_HEIGHT)-y)*scaleTempY));
        //        pathOfGeneratedGraph.resetGraph();
        //        pathOfOriginalGraph.resetGraph();
        //        std::cout<<"first chosen node "<<nodeInitForPath<<" "<<x<<" "<<y<<'\n';
        //        std::cout<<"second chosen node "<<node<<" "<<x<<" "<<y<<'\n';
        //        if(nodeInitForPath!=NULL&&node!=NULL){
        //            imitate(&mainGraph, &minRealGraph,&realShortestPath, nodeInitForPath, node, &pathOfGeneratedGraph, &pathOfOriginalGraph);
        //        }

    }
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'a':
            // call a function
            //            Singleton<Windows>::instance().decreaseCurrent();

            break;
        case 'd':
            // call a function
            //            Singleton<Windows>::instance().increaseCurrent();
            break;
        case 'c':
            // call a function
            //            Singleton<Windows>::instance().increaseCurrent();
            //            constructRoads=true;
            //            definitionRoadNetwork=4;
            break;
        case 'x':
            // call a function
            //            Singleton<Windows>::instance().increaseCurrent();
            //            constructRoads=true;
            //            definitionRoadNetwork=2;
            break;
        case 'v':
            // call a function
            //            Singleton<Windows>::instance().increaseCurrent();
            //            calculateCities=true;
            //            migrate=false;
            break;
        case 'b':
            // call a function
            //            Singleton<Windows>::instance().increaseCurrent();
            //            calculateCities=false;
            //            migrate=true;

            break;
        default:
            break;
    }
    //    glutPostRedisplay(); /* this redraws the scene without                         waiting for the display callback so that any changes appear                          instantly */
}


















































void renderScene(void){


    if(counter>=INFINITY/10){
        counter=0;
    }




    bool draw=(counter%10==0);

    if(draw){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    //    if(constructRoads){
    //
    //        graph.resetGraph();
    //        for(long i=0;i<interfaceCityGeneration.metropolises.size();i++){
    //            double mass=interfaceCityGeneration.metropolises[i].calculateSize(&interfaceCityGeneration);
    //            if(mass>0){
    //                graph.addNode();
    //                graph.nodes[graph.nodes.size()-1].location=interfaceCityGeneration.metropolises[i].calculateCentroid(&interfaceCityGeneration);
    //                graph.nodes[graph.nodes.size()-1].mass=mass;
    //            }
    //
    //        }
    //        Programs::createRoadNetwork(graph,Functions::max(1,5*counter/1500),definitionRoadNetwork);
    //        Graph lineGraph;
    //        graph.createLineGraph(&graph, &lineGraph);
    //        Network::calculateEdgeBetweennessOfCitiesAndUseItAsWidthTransition(&lineGraph, lineGraph.getIndexesOfDistanceType(Graph::ANGULAR)[0], 1, true);
    //        constructRoads=false;
    //        calculateCities=false;
    //
    //    }else if(calculateCities){
    //        Singleton<Windows>::instance().get(0)->deleteTemporary();
    //        VectorNDim color;
    //        color.values.push_back(0);
    //        color.values.push_back(0);
    //        color.values.push_back(0);
    //        color.values.push_back(200);
    //        Programs::loopGenerateCities(&interfaceCityGeneration,counter,draw);
    ////        Programs::migrate(&interfaceCityGeneration, .1);
    //
    ////        Singleton<Windows>::instance().get(0)->drawGraphEdges(&graph, color);
    //
    //    }else if(migrate){
    //        //        Singleton<Windows>::instance().get(0)->deleteTemporary();
    //        //        VectorNDim color;
    //        //        color.values.push_back(0);
    //        //        color.values.push_back(0);
    //        //        color.values.push_back(0);
    //        //        color.values.push_back(200);
    ////        Programs::loopGenerateCities(&interfaceCityGeneration,counter,draw);
    //        Programs::migrate(&interfaceCityGeneration, .1);
    //
    //        //        Singleton<Windows>::instance().get(0)->drawGraphEdges(&graph, color);
    //
    //    }else{
    //        VectorNDim color;
    //        color.values.push_back(0);
    //        color.values.push_back(0);
    //        color.values.push_back(0);
    //        color.values.push_back(200);
    //        Singleton<Windows>::instance().get(0)->deleteTemporary();
    ////        Singleton<Windows>::instance().get(0)->drawGraphEdges(&graph, color);
    //        Singleton<Windows>::instance().get(0)->drawPotentialField(&interfaceCityGeneration.cityField,true,false,true);
    //
    //    }


    //
    //
    //
    //    ///DRAW POTENTIAL FIELDS
    //    //    for(long i=0;i<potentialField.clusters.size();i++){
    //    //        setColor(getColor((potentialField.clusters[i].value),(potentialField.min),(potentialField.max)),50);
    //    //        filledRectangle(potentialField.clusters[i].corner1.x, potentialField.clusters[i].corner1.y, potentialField.clusters[i].corner2.x, potentialField.clusters[i].corner2.y);
    //    //    }
    //    //    glPushMatrix();
    //    //    glTranslatef(930, 0, 0.0);
    //    //
    //    //    for(long i=0;i<potentialField.clusters.size();i++){
    //    //
    //    //        setColor(getColor((potentialField.clusters[i].value),(potentialField.min),(potentialField.max)),50);
    //    //        filledRectangle(potentialField.clusters[i].corner1.x, potentialField.clusters[i].corner1.y, potentialField.clusters[i].corner2.x, potentialField.clusters[i].corner2.y);
    //    //    }
    //    //    glPopMatrix();
    //    ////////////////////////////////////
    //

    if(draw){

        for(long i=0;i<Singleton<Windows>::instance().size();i++){
            DrawingObject* object=Singleton<Windows>::instance().get(i)->getTemporaryObject();
            while(object!=NULL){
                double displacementX=Singleton<Windows>::instance().get(i)->startWindowX;
                double displacementY=Singleton<Windows>::instance().get(i)->startWindowY;
                double scale=Singleton<Windows>::instance().get(i)->scale;
                if(object->type==DrawingObject::POINT){
                    setColor(object->colorFill);
                    point((object->center.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->center.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY, object->radius*scale);
                }
                if(object->type==DrawingObject::CIRCLE_FILLED){
                    setColor(object->colorFill);
                    filledCircle((object->center.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->center.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY, object->radius*scale);
                }
                if(object->type==DrawingObject::RECTANGLE_FILLED){
                    setColor(object->colorFill);
                    filledRectangle((object->corner1.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->corner1.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY, (object->corner2.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->corner2.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY);

                }
                if(object->type==DrawingObject::LINE){
                    setColor(object->colorLine);
                    line((object->start.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->start.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY, (object->end.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->end.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY, object->widthLine*scale);
                }
                if(object->type==DrawingObject::TEXT){
                    setColor(object->colorLine);
                    text(object->text, Point2d((object->start.x+Singleton<Windows>::instance().get(i)->startX)*scale+displacementX, (object->start.y+Singleton<Windows>::instance().get(i)->startY)*scale+displacementY), object->size);
                }
                object=Singleton<Windows>::instance().get(i)->getTemporaryObject();
            }
            setColor(150,150,150);
            filledRectangle(Singleton<Windows>::instance().get(i)->startWindowX, Singleton<Windows>::instance().get(i)->startWindowY+Singleton<Windows>::instance().get(i)->heightWindowY, Singleton<Windows>::instance().get(i)->startWindowX+Singleton<Windows>::instance().get(i)->widthWindowX, Singleton<Windows>::instance().get(i)->startWindowY+Singleton<Windows>::instance().get(i)->heightWindowY+20);
            setColor(0,0,0);
            rectangle(Singleton<Windows>::instance().get(i)->startWindowX, Singleton<Windows>::instance().get(i)->startWindowY+Singleton<Windows>::instance().get(i)->heightWindowY, Singleton<Windows>::instance().get(i)->startWindowX+Singleton<Windows>::instance().get(i)->widthWindowX, Singleton<Windows>::instance().get(i)->startWindowY+Singleton<Windows>::instance().get(i)->heightWindowY+20);
            setColor(250,250,250);
            text(Singleton<Windows>::instance().getTitle(i), Point2d(Singleton<Windows>::instance().get(i)->startWindowX+5, Singleton<Windows>::instance().get(i)->startWindowY+Singleton<Windows>::instance().get(i)->heightWindowY+5), 10);
            setColor(0,0,0);
            rectangle(Singleton<Windows>::instance().get(i)->startWindowX, Singleton<Windows>::instance().get(i)->startWindowY, Singleton<Windows>::instance().get(i)->startWindowX+Singleton<Windows>::instance().get(i)->widthWindowX, Singleton<Windows>::instance().get(i)->startWindowY+Singleton<Windows>::instance().get(i)->heightWindowY);
        }
    }


    glFlush();
    counter++;


}


void init(void)
{

    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
    glutInitWindowSize (width*2,width);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Percolation");




    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND ); glClearColor(1.0, 1.0, 1.0,0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width*2, 0, width);
    glutMouseFunc(MouseAction);
    glutKeyboardFunc(keyboard);




}



int main(int argc,char** argv)

{
    double minX=548573;
    double minY=239939;
    //    double widthKm=75*1000;





    //            Graph uk;
    //            std::cout<<"IMPORTING FILE UK"<<'\n';
    //            TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", &minRealGraph, ",", " ", true, false);
    //
    //
    //
    //        QTree quadTreeUKReal;
    //        std::cout<<"INSERT INTO QUADTREE WHOLE UK"<<'\n';
    //        uk.insertGraphIntoQTree(&quadTreeUKReal);
    //
    //        std::vector<Node*> nodesInRangeUK=quadTreeUKReal.getNodesInARange(minX, minY, minX+widthKm, minY+widthKm);
    //        std::cout<<"GET INDUCED SUBGRAPH"<<'\n';
    //        uk.getInducedSubgraph(&subArea, nodesInRangeUK);
    //        std::cout<<"SAVE SUBGRAPH"<<'\n';
    //
    //        TextFile::writeNCOLPlusCoordinatesFile(&subArea, "/Users/carlos/Documents/results/harmonicCities/uk_subArea.txt");

    //        std::cout<<"GENERATE PERCOLATION"<<'\n';
    //
    //        std::vector<Graph> clusters;
    //        uk.generateNetworkPercolation(600,clusters , false, true, "", minSizeCity);
    //        Graph superGraph;
    //        std::cout<<"GENERATE SUPERGRAPH"<<'\n';
    //        uk.generateSuperGraphFromClusters(clusters, &uk, &superGraph);
    //
    //        QTree quadTreeUK;
    //        std::cout<<"INSERT INTO QUADTREE"<<'\n';
    //        superGraph.insertGraphIntoQTree(&quadTreeUK);
    //
    //
    //        std::cout<<"SELECT NODES"<<'\n';
    //        std::vector<Node*> nodesInRange=quadTreeUK.getNodesInARange(minX, minY, minX+widthKm, minY+widthKm);
    //        std::cout<<"GET INDUCED SUBGRAPH"<<'\n';
    //        superGraph.getInducedSubgraph(&realGraph, nodesInRange);
    //        std::cout<<"SAVE SUBGRAPH"<<'\n';
    //        TextFile::writeNCOLPlusCoordinatesFile(&realGraph, "/Users/carlos/Documents/results/harmonicCities/uk_subgraph.txt");

    //        std::vector<std::string> originalIdsAndMasses;
    //        for(long i=0;i<realGraph.nodes.size();i++){
    //            std::stringstream data;
    //            data<<realGraph.nodes[i].originalID<<" "<<realGraph.nodes[i].mass;
    //            originalIdsAndMasses.push_back(data.str());
    //        }
    //
    //        TextFile::writeToFile("/Users/carlos/Documents/results/harmonicCities/masses.txt", originalIdsAndMasses, false);








    if (argc>1){
        Configuration::setFolder(argv[1]);
        Configuration::setSubFolderIn(argv[2]);
        Configuration::setSubFolderOut(argv[3]);
    }

    std::stringstream nameSS,nameCoordinatesSS;
    std::string separatorNCOL=" ";
    std::string separatorCoordinates=" ";
    double startAngle,endAngle,separationAngles;

    if (argc>4){
        nameSS<<Configuration::folderIn()<<argv[4];
        nameCoordinatesSS<<Configuration::folderIn()<<argv[5];
        separatorNCOL=argv[6];
        separatorCoordinates=argv[7];
        startAngle=std::stod(argv[8]);
        endAngle=std::stod(argv[9]);
        separationAngles=std::stod(argv[10]);
        //
        //        Programs::performAngularNetworkPercolationLegion(nameSS.str(),nameCoordinatesSS.str(),separatorNCOL,separatorCoordinates,startAngle,endAngle,separationAngles);
    }else{


        //
//                std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string>,int > result;
//        ////
//                        result=ShapeFile::readShapeFile("/Users/carlos/Dropbox/CASA/zzz_/","sampleUK","27700","27700");
//        //        result=ShapeFile::readShapeFile("/Users/carlos/Dropbox/CASA/zzz_/","testSmallMadridArea","4326","3857");
//                DualExtendedGraph deg;
//                DualExtendedGraph::addPrimal(&deg,std::get<0>(result),std::get<1>(result),false);
//                DualExtendedGraph::simplify(&deg);
//                DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);
//        std::vector<long> colors;
//        std::vector<long> sizes;
//        DualExtendedGraph::metricPercolation(&deg, 300, colors,  sizes);
////        Grafo supergraph;






        std::string folder="/Users/carlos/Documents/zzz_/";
        std::string nameNoExtension="lines";





        //                std::string folder="/Users/carlos/Dropbox/CASA/zzz_/";
        //                std::string nameNoExtension="sampleFromUK";


        //        "4326","3857"

               std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string>, int > result;

        result=ShapeFile::readShapeFile(folder,nameNoExtension,"54009","54009");
        Grafo G;
        Grafo::create(&G,std::get<0>(result),std::get<1>(result),false);
        result=ShapeFile::readShapeFile(folder,"linesHULL","54009","54009");
        Grafo hull;
        Grafo::create(&hull,std::get<0>(result),std::get<1>(result),false);
        double diameter=0;
        InterfaceDijkstra djks;
        if(hull.nodes.size()>2){


            std::vector<Number*> numbersRepresentingNodes;
            std::vector<bool> inDijkstra;
            std::vector<bool> inCutoff;
            Grafo::startCalculatingShortestPaths(&G,numbersRepresentingNodes,inDijkstra,inCutoff);
            double distanceLimit=0;
            // for(long i=0;i<G->nodes.size();i++){
            for(long i=0;i<hull.nodes.size();i++){

                long nodeID=G.getNodeByLocation(hull.nodes[i]->location)->id;
                std::cout<<nodeID<<'\n';
                if(nodeID!=-1){
                    std::cout<<"number of links departing from node "<<G.nodes[nodeID]->links.size()<<'\n';
                    Grafo::calculateDijkstra(&G,G.nodes[nodeID],djks,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
                    for(long j=0;j<G.nodes.size();j++){
                        if(std::isfinite(djks.getMinDistance(j))&&djks.getMinDistance(j)>diameter){
                            diameter=djks.getMinDistance(j);
                        }
                    }
                }

            }
            std::cout<<"finished calculating distances"<<'\n';
            // std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
            // Grafo::calculateCloseness(G,result,closeness);
            // result.reset();
            // }
            // std::cout<<"finished"<<'\n';
            Grafo::finishCalculatingShortestPaths(&G,numbersRepresentingNodes,inDijkstra,inCutoff);
            std::cout<<"finished whole process "<<diameter<<'\n';
        }
        std::cout<<"hasta aqui"<<'\n';
        std::cout<<"hasta aqui 2"<<'\n';




















        Grafo cities;
//        Grafo::createSuperGraphFromClustersFromColorsLinks(deg.getPrimalGraph(), &cities, colors);

        TextFile::parseNCOLandSeparateCoordinatesFile(&cities, false, "/Users/carlos/Dropbox/CASA/collaborations/alberto/ncolCities.txt", "/Users/carlos/Dropbox/CASA/collaborations/alberto/coordsCities.txt", " "," ", true);
        std::vector<double> masses=TextFile::parseSimpleNumericFile("/Users/carlos/Dropbox/CASA/collaborations/alberto/massesCities.txt");
        for(long i=0;i<masses.size();i++){
            cities.nodes[i]->mass=masses[i];
        }



        //        Grafo cg;
        //        DualExtendedGraph::collapseDoubleLanes(&deg, &cg);

        //        std::vector<long> idRoundabouts;
        //        DualExtendedGraph::detectRoundabouts(&deg, idRoundabouts);
        //        std::tuple<std::vector<double>, std::vector<double> > points= Grafo::getPointsEvenBreaks(deg.getPrimalGraph(),10);
        //        std::vector<double> gridSizes;
        //        for(double i=0;i<5;i++){
        //            gridSizes.push_back(pow(2,i));
        //        }
        //        double fd=FractalDimension::calculateBoxCounting(deg.getStructuralGraph());
        //        std::vector<std::vector<double> > pointsFD=FractalDimension::calculateBoxCounting_getPoints(std::get<0>(points), std::get<1>(points), gridSizes, .25);
        //        Fxy::createFunction(pointsFD[0], pointsFD[1]);
        //        std::vector<double> data;
        //        for(long i=0;i<10;i++){
        //            data.push_back(Functions::rnorm(0, 1));
        //        }
        //        Distribution::createDistribution(data);
        //                double ent=Entropy::calculateEntropy(data);



        //        std::vector<double> gammas;
        //        std::vector<double> epsilons;
        //        std::vector<double> Ns;
        //        std::vector<double> areas;
        //        std::vector<double> tsls;
        //        std::vector<double> Hs;
        //        std::vector<double> Has;
        //        std::vector<double> Nareas;
        //
        //        std::vector<double> EFAs;
        //        std::vector<double> EFDs;
        //        std::vector<double> FCs;
        //
        //
        //
        ////        for(long i=0;i<thresholds.size();i++){
        //
        //            double threshold=100;
        //            std::cout<<"Threshold "<<threshold<<'\n';
        //            std::vector<long> colors;
        //            std::vector<long> sizes;
        //
        //            DualExtendedGraph::metricPercolation(&deg,threshold,colors,sizes);
        //            std::vector<long> indexes=Functions::getIndexesOfOrderedValues(sizes,false);
        //            std::vector<long> idsLinksLargestCluster;
        //            for(long j=0;j<colors.size();j++){
        //                if(colors[j]==indexes[0]){
        //                    idsLinksLargestCluster.push_back(j);
        //                }
        //            }
        //            Grafo sg;
        //            Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), &sg, idsLinksLargestCluster);
        //            Grafo boundary;
        //            GeometryGraph::createBoundaryGraph(&sg, &boundary, 0);
        //            Grafo G;
        //            // Grafo* boundary=new Grafo();
        //            // GeometryGraph::createBoundaryGraph(G, boundary, 0);
        //            GeometryGraph::getSubgraphWithinABoundary(deg.getPrimalGraph(), &boundary, &G);
        //
        //
        //        for(long i=0;i<20;i++){
        //        double fd=FractalDimension::calculateBoxCounting(&G);
        //        std::cout<<fd<<'\n';
        //        }

























        //
//                DualExtendedGraph deg;
//                Grafo G;
//                TextFile::parseNCOLandSeparateCoordinatesFile(&G, false, "/Users/carlos/Dropbox/CASA/data/graphsFromImages/bottomWingInsectNCOL.txt", "/Users/carlos/Dropbox/CASA/data/graphsFromImages/bottomWingInsectCoordinates.txt", " ", " ", true);
//        ////                DualExtendedGraph::addPrimal(&deg,std::get<0>(result),std::get<1>(result),false);
//                                DualExtendedGraph::addPrimal(&deg,&G);
//        std::vector<double> HI;
////        DualExtendedGraph::calculateAreasClustersInParallel(&deg, 20, areas, 2);
//        DualExtendedGraph::calculateHierarchicalIndexMetric_basedInDensityOfNodesThatRepresentAGrid_UsingMassesNodes(&deg, 20, HI, .25);
        //                DualExtendedGraph::simplify(&deg);
        //                DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP );
        //        std::vector<long> colors;
        //        std::vector<long> colorsNodes;
        //        std::vector<long> sizes;
        //        DualExtendedGraph::angularPercolation(&deg, 52.5753, colors, sizes);
        //        Grafo::transformColorsLinksIntoColorsNodes(deg.getLineGraph(), colors, colorsNodes);
        //        std::set<long> idsLinks;
        //        std::vector<long> indexOrderSize=Functions::getIndexesOfOrderedValues(sizes, false);
        //        long colorLargestCluster=indexOrderSize[0];
        //        for(long i=0;i<deg.getPlanarGraph()->links.size();i++){
        //            if(colorsNodes[i]==colorLargestCluster){
        //                idsLinks.insert(i);
        //            }
        //        }
        //        Grafo subG;
        //        Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), &subG, idsLinks);
        //        DualExtendedGraph degsubG;
        //        DualExtendedGraph::addPrimal(&degsubG, &subG);
        //        Grafo dual;
        //        for(long i=0;i<degsubG.getDualGraph()->nodes.size();i++){
        //            std::cout<<degsubG.getDualGraph()->nodes[i]->mass<<'\n';
        //        }










        //                std::vector<long> roundaboutsIdsAtNodes;
        //
        //                DualExtendedGraph::detectRoundabouts(&deg,roundaboutsIdsAtNodes,.1,65,200,false,0,200);
















        std::vector<std::string > lines;

        std::stringstream name;
        //        name<<"/Users/carlos/Dropbox/CASA/collaborations/alberto/results/experiments_fd_c"<<".txt";
        name<<"/Users/carlos/Dropbox/CASA/collaborations/alberto/results/experiments_final_k"<<".txt";
        // lines.push_back("experiment alpha robustnessLength robustnessNumLinks totalTimeDistance tsl numIntersections flowPerMeter intersectionsPerMeter numberTripsGenerated numLinks");
        //               lines.push_back("experiment alpha realBetAv realBetTot realBetEntr realNumLinks realNumInt betAv betTot betEntr numLinks numIntersections");
//        lines.push_back("experiment alphas robustnessLengths robustnessNumLinks tsl sumDegrees sumDegreesComplexity numIntersectionsDegLarger2 numIntersections betAv betTot betEntr EntrAreas totalArea numAreas closenessTot closenessAvPerIntersection closenessAvPerCity closenessTotNoMass closenessAvNoMass");
                lines.push_back("experiment alphas robustnessLengths robustnessNumLinks tsl flowPerCar distancePerCar intersectionsPerCar outoingTrips fractalDimension");
        //                lines.push_back("experiment alpha fractalDimension");
//        TextFile::writeToFile(name.str(),lines, false);
        lines.clear();
        for(long j=0;j<3000;j++){
            std::cout<<"*****************  experiment "<<j<<'\n';
            double speed=1;//km/h
            double metersAtThisSpeedIn2seconds=speed*1000/3600*2;
            double c=1/(((5+metersAtThisSpeedIn2seconds)*3600.0)/(1000.0*speed));

            //            std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double> > resultsExperiments=RoadNetworkGeneration::experiments_optimizeAlpha(1, c,.15,4,8);
            //                        std::tuple<std::vector<double>,std::vector<double> > resultsExperiments=RoadNetworkGeneration::experiments_measureFractalDimension(1, c,.15,4,8);
            //           std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>  > resultsExperiments=RoadNetworkGeneration::experiments_measureEntropy(1, c,.15,4,8);
            //                       std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>    > resultsExperiments=RoadNetworkGeneration::experiments_calculateFlows(1, c,.15,4,8);

//            std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double> ,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>     > resultsExperiments=RoadNetworkGeneration::experiments_final(1, c,.15,4,8);
            std::tuple<std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>  ,std::vector<double>   > resultsExperiments=RoadNetworkGeneration::experiments_final_C(&cities);





            for(long i=0;i<std::get<0>(resultsExperiments).size();i++){
                std::stringstream ss;
                //                ss<<j<<" "<<std::get<0>(resultsExperiments)[i]<<" "<<std::get<1>(resultsExperiments)[i]<<" "<<std::get<2>(resultsExperiments)[i]<<" "<<std::get<3>(resultsExperiments)[i]<<" "<<std::get<4>(resultsExperiments)[i]<<" "<<std::get<5>(resultsExperiments)[i]<<" "<<std::get<6>(resultsExperiments)[i]<<" "<<std::get<7>(resultsExperiments)[i]<<" "<<std::get<8>(resultsExperiments)[i]<<" "<<std::get<9>(resultsExperiments)[i];
                //                                ss<<j<<" "<<std::get<0>(resultsExperiments)[i]<<" "<<std::get<1>(resultsExperiments)[i];
//                ss<<j<<" "<<std::to_string(std::get<0>(resultsExperiments)[i])<<" "<<std::to_string(std::get<1>(resultsExperiments)[i])<<" "<<std::to_string(std::get<2>(resultsExperiments)[i])<<" "<<std::to_string(std::get<3>(resultsExperiments)[i])<<" "<<std::to_string(std::get<4>(resultsExperiments)[i])<<" "<<std::to_string(std::get<5>(resultsExperiments)[i])<<" "<<std::to_string(std::get<6>(resultsExperiments)[i])<<" "<<std::to_string(std::get<7>(resultsExperiments)[i])<<" "<<std::to_string(std::get<8>(resultsExperiments)[i])<<" "<<std::to_string(std::get<9>(resultsExperiments)[i])<<" "<<std::to_string(std::get<10>(resultsExperiments)[i])<<" "<<std::to_string(std::get<11>(resultsExperiments)[i])<<" "<<std::to_string(std::get<12>(resultsExperiments)[i])<<" "<<std::to_string(std::get<13>(resultsExperiments)[i])<<" "<<std::to_string(std::get<14>(resultsExperiments)[i])<<" "<<std::to_string(std::get<15>(resultsExperiments)[i])<<" "<<std::to_string(std::get<16>(resultsExperiments)[i])<<" "<<std::to_string(std::get<17>(resultsExperiments)[i])<<" "<<std::to_string(std::get<18>(resultsExperiments)[i]);
                 ss<<j<<" "<<std::to_string(std::get<0>(resultsExperiments)[i])<<" "<<std::to_string(std::get<1>(resultsExperiments)[i])<<" "<<std::to_string(std::get<2>(resultsExperiments)[i])<<" "<<std::to_string(std::get<3>(resultsExperiments)[i])<<" "<<std::to_string(std::get<4>(resultsExperiments)[i])<<" "<<std::to_string(std::get<5>(resultsExperiments)[i])<<" "<<std::to_string(std::get<6>(resultsExperiments)[i])<<" "<<std::to_string(std::get<7>(resultsExperiments)[i])<<" "<<std::to_string(std::get<8>(resultsExperiments)[i])<<" "<<std::to_string(std::get<9>(resultsExperiments)[i]);
                lines.push_back(ss.str());
            }
            TextFile::writeToFile(name.str(),lines, true);
            lines.clear();


        }
        std::cout<<"FINISHED experiments"<<'\n';


















        //        Programs::simplifyNetwork(&loadedGraph);
        //        Programs::analyseHierarchyUsingDerivativePercolation(&loadedGraph);




        //                DualExtendedGraph deg;
        //

        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_ncol.txt", "/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_coordinates.txt", " ", " ", true);


        folder="/Users/carlos/Documents/data/GIS/EU/countries/Spain/cities/Barcelona/";
        nameNoExtension="Barcelona";

        //                std::string folder="/Users/carlos/Dropbox/CASA/zzz_/";
        //                std::string nameNoExtension="sampleFromUK";


        //        "4326","3857"

        //        std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string>,int > result;
        //        result=ShapeFile::readShapeFile(<#std::string folder#>, <#std::string nameNoExtension#>, <#std::string EPSG_in#>, <#std::string EPSG_out#>);
        //        result=ShapeFile::readShapeFile(folder,nameNoExtension,"3857","3857");


        //        for(long i=0;i<100;i++){
        //            std::cout<<std::get<2>(result)[i]<<'\n';
        //        }

        //        DualExtendedGraph::addPrimal(&deg,std::get<0>(result),std::get<1>(result),false);
        //        result=ShapeFile::readShapeFile("/Users/carlos/Documents/data/GIS/UK/OpenData/","RoadNodesUK","27700","27700");
        //
        //        Grafo G;
        //        Grafo::create(&G, std::get<0>(result),std::get<1>(result),false);

        //        DualExtendedGraph::simplify(&deg);
        //        DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP );
        //        DualExtendedGraph::unPlanarizeUsingIntersectionPointsAndOriginalIdsOfLinks(&deg,&G);

        //        std::vector<long> roundaboutsIdsAtNodes;

        //        DualExtendedGraph::detectEntryPointsToRoundabouts(&deg,roundaboutsIdsAtNodes);
        //        DualExtendedGraph::hyperConnectRoundabouts(&deg,roundaboutsIdsAtNodes);
        //        DualExtendedGraph::detectRoundabouts(&deg,roundaboutsIdsAtNodes);
        //        std::cout<<"calculating closeness "<<'\n';
        //        std::cout<<"checking loops before closeness "<<'\n';
        //        Grafo::checkIfLoops(deg.getPrimalGraph());
        //        std::vector<double> cl;
        //        Grafo::calculateCloseness(deg.getPrimalGraph(), 1000, cl);
        //        std::vector<long> colors;
        //        std::vector<long> sizes;
        //        DualExtendedGraph::metricPercolation(&deg, 200, colors,sizes);

        //        DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
        //        std::vector<double> HI;
        //        DualExtendedGraph::calculateHierarchicalIndexMetric(&deg, 100, HI);

        //        std::vector<long> idsRoundaboutsAtNodesPrimalLevel;
        //        DualExtendedGraph::detectRoundabouts(&deg,idsRoundaboutsAtNodesPrimalLevel);
        //        Grafo burnedGraph;
        //        Grafo::burnGraph(deg.getPrimalGraph(), &burnedGraph);









        //        Grafo flights;
        //        Grafo::create(&flights, result.first, result.second, false);
        //         Grafo europeanBorders;
        //                Grafo::create(&europeanBorders, result.first, result.second, false);


        //        folder="/Users/carlos/Dropbox/CASA/data/GIS/EU/countries/Spain/cities/Madrid/";
        //        nameNoExtension="MadridAndSurroundings";

        //        folder="/Users/carlos/Documents/data/GIS/UK/UK_simplified/";
        //        nameNoExtension="UK_simplified";
        //       std::pair<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > > result=ShapeFile::readShapeFile(folder,nameNoExtension,"27700","27700");


        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Dropbox/CASA/data/fractals/gridNCOL.txt", "/Users/carlos/Dropbox/CASA/data/fractals/gridCoordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Dropbox/CASA/data/fractals/largeGrid_ncol.txt", "/Users/carlos/Dropbox/CASA/data/fractals/largeGrid_coordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Dropbox/CASA/data/fractals/sierpienskyCarpetNCOL.txt", "/Users/carlos/Dropbox/CASA/data/fractals/sierpienskyCarpetCoordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/data/GIS/UK/UK_ncol.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", ",", " ", true);
        //         TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/results/angularNetworkPercolation/UK/subAreaUK_pointsix/subAreaUK_pointsix.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/results/angularNetworkPercolation/UK/subAreaUK_pointeight/subAreaUK_pointeight.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/results/angularNetworkPercolation/UK/subAreaUK_half/subAreaUK_half.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/results/angularNetworkPercolation/UK/subAreaUK_third/subAreaUK_third.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", " ", " ", true);
        //        TextFile::parseNCOLandSeparateCoordinatesFile(deg.getPrimalGraph(),false,"/Users/carlos/Documents/results/angularNetworkPercolation/UK/subAreaUK_fourth/subAreaUK_fourth.txt", "/Users/carlos/Documents/data/GIS/UK/UK_coordinates.txt", " ", " ", true);


        //
        //        std::vector<double> qs;
        //
        //        for(long i=-10;i<=10;i++){
        //            qs.push_back(i);
        //        }
        //        InterfaceMultiFractalAnalysis ima;
        //
        //        ima=FractalDimension::MultifractalAnalysis_boxCounting(deg.getPrimalGraph(), qs);
        //
        //
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"D"<<qs[i]<<"="<<std::to_string(ima.Dqs[i])<<'\n';
        //        }
        // std::vector<double> HI_angular;
        // DualExtendedGraph::calculateHierarchicalIndexAngular(&deg, 20, HI_angular);





        //        Grafo tree;
        //  std::vector<long> colorsNodes;
        //  DualExtendedGraph::createHierarchicalTreeMetric(&deg,&tree,colorsNodes);





        //    ShapeFile::close();
        //        std::cout<<"coordinates"<<'\n';
        //
        //        for(long i=0;i<result[0].size();i++){
        //            std::cout<<"coords "<<result[0][i][0]<<" "<<result[0][i][1]<<" "<<result[0][i][2]<<" "<<'\n';
        //        }
        //
        //        std::cout<<"ncol"<<'\n';
        //
        //        for(long i=0;i<result[1].size();i++){
        //            std::cout<<"ncolValues "<<result[1][i][0]<<" "<<result[1][i][1]<<" "<<result[1][i][2]<<" "<<'\n';
        //        }


        //        std::vector<std::vector<double> >  result_=FractalDimension::generateSetOfPointsInvertedBoxCounting( 1.4, 10000, 0, 10000, 0, 1000, 50);









        //        Graph G;
        //
        ////        G.strictlyDirectional=true;
        //        TextFile::parseNCOLandSeparateCoordinatesFile("/Users/carlos/Documents/results/fractalCities/FCncol.txt", "/Users/carlos/Documents/results/fractalCities/FCcoordinates.txt", &G, " ", " ", true, false);
        //        G.setTypeOfMainDistanceAndInsertIntoDistances(Graph::METRIC);
        //        G.transformToBidirectional();
        //
        ////        Grafo G;
        ////        Grafo::create(&G, result[0], result[1], false);
        //

        //        deg.primal.bidirectional=true;
        //        for(long i=0;i<G.nodes.size();i++){
        //            deg.primal.addNode();
        //            deg.primal.nodes[deg.primal.nodes.size()-1]->location=G.nodes[i].location;
        //        }
        //        for(long i=0;i<G.transitions.size();i++){
        //            deg.primal.addLink(G.transitions[i].a->id,G.transitions[i].b->id,G.transitions[i].weight);
        //        }
        //        DualExtendedGraph::addPrimal(&deg,result[0], result[1]);









        //            typedef std::multiset<Number>::iterator It;
        //        typedef std::multiset<Number> Multiset;
        //
        //        Multiset linesIdsByYCoordinate;
        //        int myints[]= {77,30,16,2,30,30};
        //
        //        for(long i=0;i<6;i++){
        //            Number number;
        //            number.value=myints[i];
        //            number.id=i;
        //
        //            linesIdsByYCoordinate.insert(number);
        //        }
        //
        //
        //
        //        Number searchNumber;
        //        searchNumber.value=25;
        //
        //        std::pair<It,It> ret = linesIdsByYCoordinate.equal_range(searchNumber);
        //
        //
        //
        //        if(ret.first!=linesIdsByYCoordinate.begin()){
        //            std::cout<<"predecessor "<<((std::prev(ret.first)))->value<<'\n';
        //        }
        //
        //            std::cout<<"last element "<<((std::prev(ret.second)))->value<<'\n';
        //
        //
        //        std::cout<<"numberElements "<<std::distance(ret.first,ret.second)<<'\n';
        //
        //        if(ret.second!=linesIdsByYCoordinate.end()){
        //            std::cout<<"sucessor "<<((ret.second))->value<<'\n';
        //        }
        //
        //
        //        std::multiset<Number>::iterator itlow,itup;
        //        searchNumber.value=25;
        //        itlow = linesIdsByYCoordinate.lower_bound (searchNumber);
        //        searchNumber.value=25;
        //        itup = linesIdsByYCoordinate.upper_bound (searchNumber);
        //
        //                std::cout << "range contains:";
        //                for (It it=itlow; it!=itup; ++it)
        //                    std::cout << ' ' << (it)->value;
        //                std::cout << '\n';






        //        DualExtendedGraph::simplify(&deg);
        //        Grafo::forcePlanaritylineSweep(&deg.primal);
        //        DualExtendedGraph deg2;
        //        DualExtendedGraph::addPrimal(&deg2,result[0], result[1],false);
        //        Grafo::forcePlanarityPlaneSweep(&deg2.primal, Grafo::SPEED);

        //        DualExtendedGraph::forcePlanarityPrimal(&deg, Grafo::PLANARITY_LINESWEEP);
        //        std::string distanceName="metric";
        //        std::vector<double> data=deg.dataLinksPrimal.getData(deg.primal.links,distanceName);
        //        for(long i=0;i<deg.primal.links.size();i++){
        //            if(deg.primal.links[i]->weight!=data[i]){
        //
        //                std::cout<<"distance "<<Functions::getDistance(deg.primal.links[i]->a->location,deg.primal.links[i]->b->location)<<" in links "<<deg.primal.links[i]->weight<<" in data "<<data[i]<<'\n';
        //            }
        //        }

        //        DualExtendedGraph::simplify(&deg);

        //
        //        DualExtendedGraph::setPrimalAsPlanar(&deg);
        //        DualExtendedGraph::setPrimalAsSimplified(&deg);
        //        DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
        //         DualExtendedGraph::useOnlyLargestConnectedComponent(&deg);


        //        DualExtendedGraph::forcePlanarityPrimal(&deg, Grafo::PLANARITY_PLANESWEEP);

        //                TextFile::saveCoordinates(deg.getPrimalGraph(), "/Users/carlos/Dropbox/CASA/data/fractals/largeGrid_coordinates.txt");
        //        std::cout<<"number links primal "<<deg.getPrimalGraph()->links.size()<<'\n';
        //                TextFile::saveNCOL(deg.getPrimalGraph(), "/Users/carlos/Dropbox/CASA/data/fractals/largeGrid_ncol.txt");







        //        DualExtendedGraph::useOnlyLargestConnectedComponent(&deg);
        //        CriticalExponentsPercolation cep;
        //        deg.getPrimalGraph()->removeNodesDegree0();





        //        std::vector<double> qs;
        //        for(long i=-10;i<10;i++){
        //            qs.push_back(i);
        //        }
        //        InterfaceMultiFractalAnalysis ima;
        //        ima=FractalDimension::MultifractalAnalysis(deg.getPrimalGraph(),qs);
        ////        ima=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg.getPrimalGraph(),qs);
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"D"<<qs[i]<<"="<<std::to_string(ima.Dqs[i])<<'\n';
        //        }
        ////
        //        std::cout<<'\n';
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"df=rbind(df,data.frame(q="<<qs[i]<<",Dq="<<std::to_string(ima.Dqs[i])<<"))"<<'\n';
        //        }
        //
        //        std::vector<double> xs,ys;
        //        xs.reserve(deg.getPrimalGraph()->nodes.size());
        //        ys.reserve(deg.getPrimalGraph()->nodes.size());
        //        for(long i=0;i<deg.getPrimalGraph()->nodes.size();i++){
        //            xs.push_back(deg.getPrimalGraph()->nodes[i]->location.x);
        //            ys.push_back(deg.getPrimalGraph()->nodes[i]->location.y);
        //        }
        //        std::vector<std::vector<double> > points=FractalDimension::calculateBoxCounting_getPoints(xs, ys, 5000, 50, 0);
        //        std::cout<<'\n';
        //        for(long i=0;i<points[0].size();i++){
        //            std::cout<<"df=rbind(df,data.frame(x="<<points[0][i]<<",y="<<points[1][i]<<"))"<<'\n';
        //        }







        //        DualExtendedGraph::createLineGraph(&deg);
        ////        deg.getPrimalGraph()->reset();
        //        DualExtendedGraph degB;
        //        DualExtendedGraph::addPrimal(&degB, deg.getLineGraph());
        ////        deg.getLineGraph()->reset();
        //
        //        DualExtendedGraph::createLineGraph(&degB);
        //        TextFile::saveCoordinates(degB.getLineGraph(), "/Users/carlos/Documents/results/angularNetworkPercolation/UK/LGLGs/UK5_LGLG_coordinates.txt");
        //        TextFile::saveNCOL(degB.getLineGraph(), "/Users/carlos/Documents/results/angularNetworkPercolation/UK/LGLGs/UK5_LGLG_ncol.txt");















        //        ima=FractalDimension::MultifractalAnalysis(deg.getPrimalGraph(),qs);
        //                ima=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg.getPrimalGraph(),qs);
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"D"<<qs[i]<<"="<<std::to_string(ima.Dqs[i])<<'\n';
        //        }
        //
        //        std::cout<<'\n';
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"df=rbind(df,data.frame(q="<<qs[i]<<",Dq="<<std::to_string(ima.Dqs[i])<<"))"<<'\n';
        //        }


        //        DualExtendedGraph::measureCriticalExponentsAngularPercolation(&deg, cep);

        //        DualExtendedGraph::createLineGraph(&deg);
        //        cep.mass=deg->getLineGraph()->links.size();
        //        std::cout<<"M = "<<std::to_string(cep.mass)<<'\n';
        //        Grafo Lg;
        //        Grafo::constructLineGraph(deg.getLineGraph(),&Lg);
        //    double fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg->getPrimalGraph());
        //    double fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg->getLineGraph(),InterfaceDijkstra::EUCLIDEAN);


        //        Grafo delaunayComplete;
        //        auto coordinatesComplete=Grafo::getCoordinates(deg.getPrimalGraph());
        //        auto ncolDelaunayComplete=Geometry::delaunay(std::get<0>(coordinatesComplete), std::get<1>(coordinatesComplete), std::get<2>(coordinatesComplete));
        //        Grafo::create(&delaunayComplete, ncolDelaunayComplete, coordinatesComplete, false);
        //        std::vector<std::string> linksRemoved;
        //        double D2,D0;
        ////        Grafo::cleanDuplicatedLinks(&delaunayComplete, 10, linksRemoved, false);
        //        //        double fractalDimension=FractalDimension::calculateCapacityDimension(&components[0]);
        //        D2=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg.getPrimalGraph(), InterfaceDijkstra::EUCLIDEAN,2);
        ////        std::cout<<std::to_string(fractalDimension)<<'\n';
        //        std::cout<<"D2="<<std::to_string(D2)<<'\n';
        //        D0=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg.getPrimalGraph(), InterfaceDijkstra::EUCLIDEAN,0);
        //        std::cout<<"D0="<<std::to_string(D0)<<'\n';
        //        double D1=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg.getPrimalGraph(), InterfaceDijkstra::EUCLIDEAN,1);
        //        std::cout<<"D1="<<std::to_string(D1)<<'\n';


        //        std::vector<Grafo> separatedComponents;
        //        Grafo::getComponents(deg.getStructuralGraph(), separatedComponents, 0);
        //        deg.getPrimalGraph()->reset();
        //        deg.getStructuralGraph()->reset();
        //
        //        DualExtendedGraph degSpeeds;
        //
        //        for(long i=0;i<separatedComponents.size();i++){
        //            if(separatedComponents[i].nodes.size()>10000){
        //
        //                DualExtendedGraph degTemp;
        //                DualExtendedGraph::addPrimal(&degTemp,&separatedComponents[i]);
        //                separatedComponents[i].reset();
        //                DualExtendedGraph::setPrimalAsPlanar(&degTemp);
        //                DualExtendedGraph::setPrimalAsSimplified(&degTemp);
        //                DualExtendedGraph::setPrimalAsStructuralGraph(&degTemp);
        //                std::vector<double> HIA;
        //                std::vector<double> HIM;
        //
        //                DualExtendedGraph::calculateHierarchicalIndexAngular(&degTemp, 100, HIA);
        //                degTemp.getLineGraph()->reset();
        //                DualExtendedGraph::calculateHierarchicalIndexMetric(&degTemp, 100, HIM);
        //
        //                std::vector<double> speeds;
        //                speeds.resize(HIA.size());
        //
        //                for(long i=0;i<HIA.size();i++){
        //
        //                    speeds[i]=(1/((2-HIA[i])+HIM[i]))*120;
        //                    degTemp.getPrimalGraph()->links[i]->weight=degTemp.getPrimalGraph()->links[i]->weight/1000/speeds[i]*60;
        //                }
        //
        //
        //                DualExtendedGraph::addAnotherGraph(&degSpeeds, degTemp.getPrimalGraph(),false);
        //                separatedComponents[i].reset();
        //            }
        //
        //
        //        }
        //        degSpeeds.getPrimalGraph()->finishedAddingNodes();
        //
        //
        //
        //

        //        for(long i=0;i<flights.links.size();i++){
        //            flights.links[i]->weight=flights.links[i]->weight/(900*1000/60);
        //        }

        //        Grafo::addLayerOfLinks(deg.getPrimalGraph(), &flights, 1000);

        //        TextFile::saveCoordinates(deg.getPrimalGraph(), "/Users/carlos/Documents/results/clustersFromPercolation/EU_timeBased_withFlights/validGraph/EU_coordinates.txt");
        //        TextFile::saveNCOL(deg.getPrimalGraph(), "/Users/carlos/Documents/results/clustersFromPercolation/EU_timeBased_withFlights/validGraph/EU_ncol.txt");

        //        DualExtendedGraph::setPrimalAsPlanar(&deg);
        //        DualExtendedGraph::setPrimalAsSimplified(&deg);
        //        DualExtendedGraph::setPrimalAsStructuralGraph(&deg);
        //
        //        DualExtendedGraph::calculateCompleteMetricPercolation(&deg, "/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/clusters/");

        //        Grafo boundary;
        //
        //        std::cout<<"number nodes europe brders "<<europeanBorders.nodes.size()<<'\n';
        //        GeometryGraph::createBoundaryGraph(&europeanBorders, &boundary, 25000000000);
        //        std::cout<<" and in the boundary "<<boundary.nodes.size()<<'\n';
        //
        //        std::set<long> nodesInBoundary=GeometryGraph::nodesInPolygon(deg.getPrimalGraph(), &boundary);
        //
        //        Grafo validEuropeanRoads;
        //
        //        Grafo::inducedSubgraph(deg.getPrimalGraph(), &validEuropeanRoads, nodesInBoundary);
        //
        //        TextFile::saveCoordinates(&validEuropeanRoads,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_original_coordinates.txt");
        //        TextFile::saveNCOL(&validEuropeanRoads,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_original_ncol.txt");
        //
        //        deg.getPrimalGraph()->reset();
        //        DualExtendedGraph::addPrimal(&deg,&validEuropeanRoads);
        //        validEuropeanRoads.reset();
        //
        //
        //
        //
        //        DualExtendedGraph::forcePlanarityPrimal(&deg, Grafo::PLANARITY_PLANESWEEP);
        //
        //        TextFile::saveCoordinates(deg.getPrimalGraph(),"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_coordinates.txt");
        //        TextFile::saveNCOL(deg.getPrimalGraph(),"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_ncol.txt");

        //        DualExtendedGraph::setPrimalAsPlanar(&deg);
        //
        //        OGRCoordinateTransformation* poCT=ShapeFile::prepareToTransformCoordinates("3035", "4326");
        //        for(long i=0;i<deg.getPrimalGraph()->links.size();i++){
        //            double distance=Functions::getDistance(deg.getPrimalGraph()->links[i]->A()->location, deg.getPrimalGraph()->links[i]->B()->location);
        //            double multiplier=Functions::max(1.0,deg.getPrimalGraph()->links[i]->weight/distance);
        //            Point2d lonlatA=ShapeFile::transformCoordinates(deg.getPrimalGraph()->links[i]->A()->location, poCT);
        //            Point2d lonlatB=ShapeFile::transformCoordinates(deg.getPrimalGraph()->links[i]->B()->location, poCT);
        //            deg.getPrimalGraph()->links[i]->weight=ShapeFile::calculateDistanceLatLon(lonlatA,lonlatB)*multiplier;
        //        }
        //
        //
        //
        //        TextFile::saveCoordinates(&europeanBorders,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/europeanBordersCountries_coordinates.txt");
        //        TextFile::saveNCOL(&europeanBorders,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/europeanBordersCountries_ncol.txt");
        //
        //        TextFile::saveCoordinates(deg.getPrimalGraph(),"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_SphericalDistances_coordinates.txt");
        //        TextFile::saveNCOL(deg.getPrimalGraph(),"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_SphericalDistances_ncol.txt");
        //
        //        DualExtendedGraph::buildStructuralGraph(&deg, false);
        ////
        //        TextFile::saveCoordinates(deg.getStructuralGraph(),"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_structural_coordinates.txt");
        //        TextFile::saveNCOL(deg.getStructuralGraph(),"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/EU_planar_structural_ncol.txt");
        //
        //        DualExtendedGraph::calculateCompleteMetricPercolation(&deg, "/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/clusters/");




        //        TextFile::createLineString(&boundary,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/subset/boundaryEurope.txt",false);
        //       TextFile::createLineString(&europeanBorders,"/Users/carlos/Documents/results/clustersFromPercolation/EU_planar/validGraph/subset/countriesEurope.txt",false);








        //        DualExtendedGraph::calculateCompleteWeightStructuralGraphPercolation(&deg, "/Users/carlos/Documents/results/clustersFromPercolation/EU_timeBased/clusters/");

        //                std::cout<<"Phase transition "<<std::get<0>(phaseTransition)<<" "<<std::get<1>(phaseTransition)<<'\n';




        //        degB.reset();
        //
        //
        //                std::vector<long> colors;
        //                std::vector<long> colorsNodes;
        //                std::vector<long> sizes;
        //                DualExtendedGraph::angularPercolation(&deg,46,colors,sizes);
        //                Grafo::transformColorsLinksIntoColorsNodes(deg.getLineGraph(), colors, colorsNodes);
        //
        //                std::vector<Grafo> components;
        //
        //                Grafo::getComponentsFromColorsOfLinks(deg.getPrimalGraph(),components,0,colorsNodes,sizes);
        //
        //        ima=FractalDimension::MultifractalAnalysis(&components[0], qs);
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"D"<<qs[i]<<"="<<std::to_string(ima.Dqs[i])<<'\n';
        //        }
        //        std::cout<<'\n';
        //        for(long i=0;i<ima.Dqs.size();i++){
        //            std::cout<<"df=rbind(df,data.frame(q="<<qs[i]<<",Dq="<<std::to_string(ima.Dqs[i])<<"))"<<'\n';
        //        }




        //        DualExtendedGraph::addPrimal(&degB, &components[0]);
        //        DualExtendedGraph::createLineGraph(&degB);
        //        DualExtendedGraph degC;
        //        DualExtendedGraph::addPrimal(&degC, degB.getLineGraph());
        //        DualExtendedGraph::createLineGraph(&degC);
        //        TextFile::saveCoordinates(degC.getLineGraph(), "/Users/carlos/Documents/results/angularNetworkPercolation/UK/LGLGs/UK0_skeleton_LGLG_coordinates.txt");
        //        TextFile::saveNCOL(degC.getLineGraph(), "/Users/carlos/Documents/results/angularNetworkPercolation/UK/LGLGs/UK0_skeleton_LGLG_ncol.txt");
        //
        //        TextFile::createLineString(degB.getPrimalGraph(),  "/Users/carlos/Documents/results/angularNetworkPercolation/UK/LGLGs/UK0_skeleton_lineString.txt", false);
        //







        //                TextFile::saveCoordinates(&components[0],"/Users/carlos/Documents/data/GIS/UK/skeletonCoordinates.txt");
        //                TextFile::saveNCOL(&components[0],"/Users/carlos/Documents/data/GIS/UK/skeletonNCOL.txt");


        ////        FractalDimension fd;
        //
        ////        TextFile::saveCoordinates(deg.getPrimalGraph(),"/Users/carlos/Documents/zzz_/networksForRoberto/network_fourth.txt");
        ////        std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates=Grafo::getCoordinates(deg.getPrimalGraph());
        //        double fractalDimension;
        ////         fractalDimension=fd.calculateBoxCounting(std::get<1>(coordinates), std::get<2>(coordinates), 1200, 800, 10);

        //        std::cout<<"link size "<<deg.getStructuralGraph()->links.size();
        //        DualExtendedGraph::useOnlyLargestConnectedComponent(&deg);
        //                std::cout<<"link size "<<deg.getStructuralGraph()->links.size();
        //        DualExtendedGraph::createLineGraph(&deg);
        ////        Grafo Lg;
        ////        Grafo::constructLineGraph(deg.getLineGraph(),&Lg);



        //        DualExtendedGraph degLG;
        //        DualExtendedGraph::addPrimal(&degLG,deg.getLineGraph());
        //        DualExtendedGraph::setPrimalAsPlanar(&degLG);
        //        DualExtendedGraph::setPrimalAsSimplified(&degLG);
        //        DualExtendedGraph::setPrimalAsStructuralGraph(&degLG);
        //        DualExtendedGraph::createLineGraph(&degLG);


        //
        ////        fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(deg.getPrimalGraph());
        ////fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(&Lg);



        // double definition=100;
        // deg.keepTrackDifferencesBetweenPrimalAndStructural=true;
        // std::vector<double> HImetric;
        // std::vector<double> HIangular;
        //
        // DualExtendedGraph::calculateHierarchicalIndexMetric(&deg,definition, HImetric);
        // DualExtendedGraph::calculateHierarchicalIndexAngular(&deg,definition, HIangular);
        // for(long i=0;i<10;i++){
        // std::cout<<deg.getPrimalGraph()->links[i]->originalID<<" "<<deg.getLineGraph()->nodes[i]->originalID<<'\n';
        // }
        // std::vector<double> speeds=DualExtendedGraph::getSpeedsForStructuralGraph(&deg,HIangular, HImetric);
        // std::vector<double> HImetricNorm=Functions::normalize(HImetric);
        // std::vector<double> HIangularNorm=Functions::normalize(HIangular);
        //
        // std::vector<double> speedsNormalized=Functions::normalize(speeds);
        //
        //
        // std::vector<double> HItime;
        // DualExtendedGraph degB;
        // DualExtendedGraph::addPrimal(&degB, deg.getStructuralGraph());
        // for(long i=0;i<degB.getPrimalGraph()->links.size();i++){
        //
        //     //            speeds[i]=(1/((2-HIangular[i])+HImetric[i]));
        //     //                    degTemp.getPrimalGraph()->links[i]->weight=degTemp.getPrimalGraph()->links[i]->weight/1000/speeds[i]*60;
        //     degB.getPrimalGraph()->links[i]->weight=deg.getPrimalGraph()->links[i]->weight/1000/(speedsNormalized[i]*90+30)*60;
        // }
        // DualExtendedGraph::setPrimalAsPlanar(&degB);
        // DualExtendedGraph::setPrimalAsSimplified(&degB);
        // DualExtendedGraph::setPrimalAsStructuralGraph(&degB);
        //
        // DualExtendedGraph::calculateHierarchicalIndexMetric(&degB,definition, HItime);




        //        std::vector<double> HII;
        //        DualExtendedGraph degC;
        //
        //
        //        for(long i=0;i<deg.getStructuralGraph()->links.size();i++){
        //
        //            //            speeds[i]=(1/((2-HIangular[i])+HImetric[i]));
        //            //                    degTemp.getPrimalGraph()->links[i]->weight=degTemp.getPrimalGraph()->links[i]->weight/1000/speeds[i]*60;
        //            deg.getStructuralGraph()->links[i]->weight=1-Functions::max(HImetric[i],HIangular[i]);
        //        }
        //
        ////        std::vector<double> HItime;
        ////        DualExtendedGraph degB;
        //        DualExtendedGraph::addPrimal(&degC, deg.getStructuralGraph());
        //        DualExtendedGraph::setPrimalAsPlanar(&degC);
        //        DualExtendedGraph::setPrimalAsSimplified(&degC);
        //        DualExtendedGraph::setPrimalAsStructuralGraph(&degC);
        //
        //        DualExtendedGraph::calculateHierarchicalIndexMetric(&degC,definition, HII);


















        //        std::cout<<HImetric.size()<<" "<<HIangular.size()<<" "<<HItime.size()<<'\n';
        //
        //        for(long i=0;i<10;i++){
        //            std::cout<<deg.getStructuralGraph()->links[i]->originalID<<" "<<degB.getStructuralGraph()->links[i]->originalID<<'\n';
        //        }

        //        std::vector<std::string> lines;
        // lines.reserve(deg.getStructuralGraph()->links.size());
        // for(long i=0;i<deg.getStructuralGraph()->links.size();i++){
        //     std::stringstream ss;
        //     ss<<deg.getStructuralGraph()->links[i]->A()->id<<" "<<deg.getPrimalGraph()->links[i]->B()->id<<" "<<HImetric[i]<<" "<<HItime[i]<<" "<<(speedsNormalized[i]*90+30);
        //     lines.push_back(ss.str());
        // }
        //                TextFile::writeToFile("/Users/carlos/Documents/results/cityGrowth/resultsHierarchyMeasurement/HImetric.txt", HImetric, false);
        //                TextFile::writeToFile("/Users/carlos/Documents/results/cityGrowth/resultsHierarchyMeasurement/HIangular.txt", HIangular, false);
        // TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/HI.txt", lines, false);


        //         TextFile::saveCoordinates(deg.getStructuralGraph(), "/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/UK_coordinates_structural.txt");
        //         TextFile::saveNCOL(deg.getStructuralGraph(), "/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/UK_ncol_structural.txt");
        //
        //         TextFile::saveCoordinates(deg.getPrimalGraph(), "/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/UK_coordinates_primal.txt");
        //         TextFile::saveNCOL(deg.getPrimalGraph(), "/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/UK_ncol_primal.txt");
        //
        //         TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/HIangular.txt", HIangular, false);
        //         TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/HImetricOfStructuralGraph.txt", HImetric, false);
        // //        std::vector<double> HImetricPrimal=DualExtendedGraph::getHImetricInPrimal(&deg, HImetric);


        //        std::vector<long> colors;
        //        std::vector<long> sizes;
        //        DualExtendedGraph::metricPercolation(&deg, 300, colors, sizes);
        //
        //
        //
        //
        //
        //        std::stringstream ss;
        //        std::vector<Grafo> cities;
        //        Grafo::getComponentsFromColorsOfLinks(deg.getStructuralGraph(),cities,1800,colors,sizes);
        //        // std::vector<long> colorsCities;
        //        // colorsCities.resize(deg.getStructuralGraph()->nodes.size(),-1);
        //        // std::vector<long> sizesCities;
        ////        std::vector<long> orderSizes=Functions::getIndexesOfOrderedValues(sizes,false);
        //        lines.clear();
        //        std::unordered_map<std::string,long> idNodesStructuralGraphByOriginalId;
        //        for(long i=0;i<deg.getStructuralGraph().nodes.size();i++){
        //          idNodesStructuralGraphByOriginalId[deg.getStructuralGraph().nodes[i]->originalID]=i;
        //        }
        //
        //        for(long i=0;i<cities.size();i++){
        //            if(cities[i].nodes.size()>3){
        //                Grafo realGraphCity;
        //                Grafo boundary;
        //                GeometryGraph::createBoundaryGraph(&cities[i], &boundary, 0);
        //                GeometryGraph::getSubgraphWithinABoundary(deg.getStructuralGraph(), &boundary, &realGraphCity);
        //                long n=realGraphCity.nodes.size();
        //                long m=realGraphCity.links.size();
        //                Grafo dualCity;
        //                Grafo::constructDual(&realGraphCity, &dualCity);
        //                double totalArea=0;
        //                double perimeter=0;
        //                double totalLengthLinks=0;
        //                for(long j=0;j<realGraphCity.links.size();j++){
        //                    totalLengthLinks+=realGraphCity.links[j]->weight;
        //                }
        //                // for(long j=0;j<realGraphCity.nodes.size();j++){
        //                //     colorsCities[idNodesStructuralGraphByOriginalId[realGraphCity.nodes[j]->originalID]]=i;
        //                // }
        //                // sizesCities.push_back(realGraphCity.nodes.size());
        //                double numberRegions=dualCity.nodes.size()-1;
        //                double sumAreasRegions=0.0;
        ////                double numberRegions=0;
        //                double averageAreaRegions=0;
        //                for(long j=0;j<dualCity.nodes.size();j++){
        //                    std::vector<Link*> linksOfDualRegion;
        //                    Grafo dualRegionLimits;
        //                    for(long h=0;h<dualCity.nodes[j]->links.size();h++){
        //                        linksOfDualRegion.push_back(realGraphCity.links[dualCity.nodes[j]->links[h]->id]);
        //                    }
        //                    Grafo::inducedSubgraph(&realGraphCity, &dualRegionLimits, linksOfDualRegion);
        //                    if(j==0){
        //                        totalArea=GeometryGraph::calculateAreaPolygon(&dualRegionLimits);
        //                        for(long h=0;h<linksOfDualRegion.size();h++){
        //                            perimeter+=linksOfDualRegion[h]->weight;
        //                        }
        //                    }else{
        //                        sumAreasRegions+=GeometryGraph::calculateAreaPolygon(&dualRegionLimits);
        //                        numberRegions++;
        //                    }
        //                }
        //                averageAreaRegions=sumAreasRegions/numberRegions;
        //                std::stringstream lineTemp;
        //                lineTemp<<i<<" "<<n<<" "<<m<<" "<<totalArea<<" "<<averageAreaRegions<<" "<<numberRegions<<" "<<perimeter<<" "<<totalLengthLinks;
        //                lines.push_back(lineTemp.str());
        //
        //            }else{
        //                break;
        //            }
        //
        //        }
        //        TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/infoCities.txt", lines, false);
        // TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/colorsCities.txt", colorsCities, false);
        // TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/sizesCities.txt", sizesCities, false);



        // std::vector<double> HImetricPrimal=DualExtendedGraph::getHImetricInPrimal(&deg, HImetric);
        // TextFile::writeToFile("/Users/carlos/Dropbox/CASA/results/cityGrowth/newResults/HImetricOfPrimalGraph.txt", HImetricPrimal, false);
        //        auto coordinates=Grafo::getCoordinates(deg.getPrimalGraph());
        //
        //
        //        double widthOfAPoint=150;
        //
        //
        //        auto points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 600, 400, widthOfAPoint);
        //
        //        std::vector<std::string> lines;
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD.txt", lines, false);







        //        InterfaceCityGeneration interface;
        //        GenerativeProcedures::generateInitialCities(&interface,10,5);
        //        for(long i=0;i<1;i++){
        //            GenerativeProcedures::loopGenerateCities(&interface,0,1000);
        //        }





        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 400, 300, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_350.txt", lines, false);
        //
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 600, 500, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_550.txt", lines, false);
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 700, 600, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_650.txt", lines, false);
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 800, 700, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_750.txt", lines, false);
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 900, 800, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_850.txt", lines, false);




        //
        //        std::cout<<"fractal dimension complete system "<<fractalDimension<<'\n';
        //
        //        //
        //



        //        std::cout<<deg.getLineGraph()->links.size()<<'\n';
        //        std::pair<double,double> phaseTransition=DualExtendedGraph::detectPhaseTransitionAngularPercolation(&deg, .001);
        //        std::vector<long> colors;
        //        std::vector<long> sizes;
        //        DualExtendedGraph::angularPercolation(&deg,std::get<0>(phaseTransition)+.001,colors,sizes);
        //        std::vector<Grafo> components;
        //        Grafo::getComponentsFromColorsOfLinks(deg.getLineGraph(),components,0,colors,sizes);
        //        std::vector<long> orderSizes=Functions::getIndexesOfOrderedValues(sizes,false);
        //        std::cout<<sizes[orderSizes[0]]<<'\n';
        //
        //        Grafo Lg_subgraph;
        //        Grafo::constructLineGraph(&components[0],&Lg_subgraph);
        //
        //        coordinates=Grafo::getCoordinates(&Lg_subgraph);
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 600,400, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_skeleton.txt", lines, false);





        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 400,300, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_skeleton_350.txt", lines, false);
        //
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 600,500, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_skeleton_550.txt", lines, false);
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 700,600, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_skeleton_650.txt", lines, false);
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 800,700, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_skeleton_750.txt", lines, false);
        //
        //        points=FractalDimension::calculateBoxCounting_getPoints(std::get<1>(coordinates), std::get<2>(coordinates), 900,800, widthOfAPoint);
        //
        //        lines.clear();
        //        for(long i=0;i<points[0].size();i++){
        //            std::stringstream ss;
        //            ss<<points[0][i]<<" "<<points[1][i];
        //            lines.push_back(ss.str());
        //        }
        //
        //        TextFile::writeToFile("/Users/carlos/Documents/zzz_/pointsFD_skeleton_850.txt", lines, false);


        //
        ////        Grafo LG=components[orderSizes[0]];
        ////        coordinates=Grafo::getCoordinates(&components[orderSizes[0]]);
        ////        fractalDimension=fd.calculateBoxCounting(std::get<1>(coordinates), std::get<2>(coordinates), 1200, 800, 10);
        ////        Grafo Lg_subgraph;
        ////        Grafo::constructLineGraph(&components[0],&Lg_subgraph);
        ////        fractalDimension=fd.calculateCorrelationDimension(&Lg_subgraph,InterfaceDijkstra::TOPOLOGICAL);
        //        components[0].removeNodesDegree0();
        //        fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(&components[0]);
        ////        fractalDimension=FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(&Lg_subgraph);
        //
        //                std::cout<<"fractal dimension cluster at percolation threshold "<<fractalDimension<<'\n';
        ////        double phaseTransition=DualExtendedGraph::detectPhaseTransitionAngularPercolation(&deg, .001);
        ////        DualExtendedGraph::calculateCompleteAngularPercolation(&deg,180);
        ////        double phaseTransition=DualExtendedGraph::detectPhaseTransitionAngularPercolation(&deg, .001);
        ////        std::cout<<"angle phase transition "<<phaseTransition<<'\n';
        ////        DualExtendedGraph::simplify(&deg);
        //
        ////        data=deg.dataLinksPrimal.getData(deg.primal.links,distanceName);
        ////        for(long i=0;i<deg.primal.links.size();i++){
        ////            if(deg.primal.links[i]->weight!=data[i]){
        ////
        ////                std::cout<<"distance "<<Functions::getDistance(deg.primal.links[i]->a->location,deg.primal.links[i]->b->location)<<" in links "<<deg.primal.links[i]->weight<<" in data "<<data[i]<<'\n';
        ////            }
        ////        }
        //
        ////        DualExtendedGraph::metricPercolation(&deg, 250, colors, sizes);
        ////        DualExtendedGraph::createDual(&deg);
        ////        DualExtendedGraph::createDual(&deg);





        //        std::vector<std::vector<long> > delaunay=Geometry::delaunay(result[1][1], result[1][2]);
        //        std::vector<double> weights;
        //        std::vector<long> ids;
        //        ids.reserve(result[1][0].size());
        //        for(long i=0;i<result[1][0].size();i++){
        //            ids.push_back(result[1][0][i]);
        //        }
        //        Grafo::cleanDelaunay(ids, result[1][1], result[1][2], delaunay, weights, 45);
        //        std::vector<long> idNodes;
        //        idNodes.reserve(result[1][0].size());
        //        std::vector<double> xs,ys;
        //        xs.reserve(result[1][0].size());
        //        ys.reserve(result[1][0].size());
        //
        //        for(long i=0;i<result[1][0].size();i++){
        //            idNodes.push_back(result[1][0][i]);
        //            xs.push_back(result[1][1][i]);
        //            ys.push_back(result[1][2][i]);
        //        }
        //        std::vector<std::vector<double> > coordinates;
        //        coordinates.push_back(xs);
        //        coordinates.push_back(ys);
        //        DualExtendedGraph::createDual(&deg, delaunay,weights,idNodes,coordinates);





        //        std::vector<double> idA;
        //        std::vector<double> idB;
        //        idA.reserve(weights.size());
        //        idB.reserve(weights.size());
        //        for(long i=0;i<weights.size();i++){
        //            idA.push_back(round(delaunay[0][i]));
        //            idB.push_back(round(delaunay[1][i]));
        //        }
        //        std::vector<std::vector<double> > delaunayNcol;
        //        delaunayNcol.reserve(3);
        //        delaunayNcol.push_back(idA);
        //        delaunayNcol.push_back(idB);
        //        delaunayNcol.push_back(weights);




        //        Graph::constructDual(&G, &dual);
        //        TextFile::writeNCOLFile(&dual, "/Users/carlos/Documents/results/fractalCities/FC_DUALncol.txt");
        //        TextFile::writeNCOLFileAndSeparateCoordinatesFile(&dual, "/Users/carlos/Documents/results/fractalCities/FC_DUALncol.txt", "/Users/carlos/Documents/results/fractalCities/FC_DUALcoordinates.txt", " ", " ");
        //        Graph geometricDual;
        //        std::vector<long> correspondanceID_originalGraph;
        //        std::vector<long> correspondanceID_result;
        //        Graph::correctGeometryOfDual(&G,&dual, &geometricDual, correspondanceID_originalGraph, correspondanceID_result);
        //        std::vector<Graph> clusters;
        //        G.generateNetworkPercolation(100, clusters, false, true, "", 0, false);
        //
        //        Graph sg;
        //        G.generateSuperGraphFromClusters(clusters, &G, &sg);
        //        Network net;
        //        net.generateRoadNetworkBetweenNodes(&sg, 100, 10);
        //        Graph result;
        //        Programs::percolateAndCreateRoadNetwork(&G,&result , 100, 100, 10);

        std::cout<<"FINISHED";

        //        LargeGraph g;
        //        LargeGraph::create(&g, result[0], result[1], false);
        //
        //        LargeGraph::removeNodesDegree2(&g);
        //
        //        LargeGraph r;
        //        LargeGraph::networkPercolation(&g, &r, 170);
        //
        //        std::vector<long> colors;
        //        std::vector<long> sizes;
        //        long maxColor;
        //        LargeGraph::getColorsFromComponents(&g, &r,  colors,sizes,maxColor);










        //        std::vector<double> values;
        //        values.push_back(0);
        //        values.push_back(23);
        //        values.push_back(45);
        //        values.push_back(68);
        //        values.push_back(79);
        //        values.push_back(180);
        //
        //        std::vector<double> positions;
        //        positions.push_back(0);
        //        positions.push_back(23);
        //        positions.push_back(45);
        //        positions.push_back(68);
        //        positions.push_back(79);
        //        positions.push_back(180);
        //
        //        long indexValue=Functions::findPositionValue(values, 46);
        //        std::cout<<"position value "<<indexValue;
        //
        //        std::vector<double> derivative;
        //        derivative=Functions::derivative(values, positions);
        //
        //         std::cout<<"position value "<<derivative[1];




        //        Programs::performMetricNetworkPercolation();
        //        Programs::calculateHierarchicalIndexPercolation();
        //        Programs::createRoadNetwork(graph);
        //        Programs::calculateRenormalisedGraph();

        //        Programs::generateCities(&interfaceCityGeneration);
        //        constructRoads=false;
        //        calculateCities=true;
        //        Programs::expandValuesThroughNetwork();

        //        Programs::calculateNumberIntersectionsCloseToIntersections();










        //        Configuration::setSubFolderIn("data/GIS/Melbourne/");
        //        Configuration::setSubFolderOut("results/CyclistAnalysis/");
        //        std::stringstream nameSS,nameCoordinatesSS;
        //        std::string separatorNCOL=" ";
        //        std::string separatorCoordinates=" ";
        //        double startDistance=60;
        //        double endDistance=65;
        //        long minClusterSize=50000;
        //        double separationBetweenDistances=5;
        //        if (argc>4){
        //            //                std::cout<<argv[4];
        //            nameSS<<Configuration::folderIn()<<argv[4];
        //            nameCoordinatesSS<<Configuration::folderIn()<<argv[5];
        //            separatorNCOL=argv[6];
        //            separatorCoordinates=argv[7];
        //            startDistance=stod(argv[8]);
        //            endDistance=stod(argv[9]);
        //            separationBetweenDistances=stod(argv[10]);
        //            minClusterSize=atol(argv[11]);
        //        }else{
        //            nameSS<<Configuration::folderIn()<<"melbourneNCOLPure"<<".txt";
        //            nameCoordinatesSS<<Configuration::folderIn()<<"pointsFinal"<<".txt";
        //        }
        //        float initPercentageNodes=0;
        //        float topPercentageNodes=0.5;
        //        long separationBetweenPercentages=1;
        //        long initRepetitions=0;
        //        long endRepetitions=1;
        //        if (argc>12){
        //            initPercentageNodes=atol(argv[12]);
        //            topPercentageNodes=atol(argv[13]);
        //            separationBetweenPercentages=atol(argv[14]);
        //            initRepetitions=atol(argv[15]);
        //            endRepetitions=atol(argv[16]);
        //        }

















    }





    //    glutInit(&argc, argv);
    init();
    //    glutDisplayFunc(renderScene);
    //    glutIdleFunc(renderScene);
    //
    //    glutMainLoop();
    return 0;
}

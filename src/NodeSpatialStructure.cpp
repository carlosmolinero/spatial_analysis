//
//  NodeSpatialStructure.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 16/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "NodeSpatialStructure.h"

void NodeSpatialStructure::create(std::vector<Nodo*> &nodes,double definition){
  this->definition=definition;
  for(long i=0;i<nodes.size();i++){
    Point2d simplifiedLocation=Point2d(std::floor(nodes[i]->location.x/definition)*definition,std::floor(nodes[i]->location.y/definition)*definition);
    matrix[simplifiedLocation].insert(nodes[i]);
  }
}
void NodeSpatialStructure::create(Grafo* G,double definition){
  // for(long i=0;i<G->nodes.size();i++){
  //
  // }
  this->definition=definition;
  for(long i=0;i<G->nodes.size();i++){
    Point2d simplifiedLocation=Point2d(std::floor(G->nodes[i]->location.x/definition)*definition,std::floor(G->nodes[i]->location.y/definition)*definition);
    matrix[simplifiedLocation].insert(G->nodes[i]);
  }
}
std::vector<Nodo*> NodeSpatialStructure::getNodesAround(Nodo* node,double distance){
    double minx=std::floor((node->location.x-distance)/definition-1.0)*definition;
    double maxx=std::floor((node->location.x+distance)/definition+1.0)*definition;
    double miny=std::floor((node->location.y-distance)/definition-1.0)*definition;
    double maxy=std::floor((node->location.y+distance)/definition+1.0)*definition;
    std::vector<Nodo*> nodesAround;
    for(double i=minx;i<=maxx;i+=definition){
      for(double j=miny;j<=maxy;j+=definition){
            Point2d simplifiedLocation=Point2d(i,j);
            for(auto it:matrix[simplifiedLocation]){
              if(Functions::getDistance(it->location,node->location)<=distance&&it!=node){
                nodesAround.push_back(it);
              }
            }
      }
    }

    // Point2d simplifiedLocation=Point2d(std::floor(G->nodes[i]->location.x/definition)*definition,std::floor(G->nodes[i]->location.y/definition)*definition);
    // matrix[simplifiedLocation].insert(G->nodes[i]);

    return nodesAround;
}
long NodeSpatialStructure::getIdClosestNodeInOtherGraph(Nodo* node,Grafo* og,double definition){
    if(matrix.size()==0){
      create(og,definition);
    }
    // double minx=std::floor((node->location.x-distance)/definition-1.0)*definition;
    // double maxx=std::floor((node->location.x+distance)/definition+1.0)*definition;
    // double miny=std::floor((node->location.y-distance)/definition-1.0)*definition;
    // double maxy=std::floor((node->location.y+distance)/definition+1.0)*definition;

    Point2d a=Point2d(std::floor(node->location.x/definition)*definition,std::floor(node->location.y/definition)*definition);
    std::vector<Nodo*> nodesAround;
    long id=-1;
    if(matrix[a].size()>0){
      double mind=INFINITY;

      for(auto it:matrix[a]){
        if(Functions::getDistance(it->location,node->location)<mind){
          mind=Functions::getDistance(it->location,node->location);
          id=it->id;
        }
      }

    }else{
      // std::vector<Nodo*> nodesAround;
      double w=2.0;
      while(nodesAround.size()==0){


        for(double i=a.x-w*definition;i<=a.x+w*definition;i+=definition){
          for(double j=a.y-w*definition;j<=a.y+w*definition;j+=definition){
                Point2d simplifiedLocation=Point2d(i,j);
                for(auto it:matrix[simplifiedLocation]){
                  // if(Functions::getDistance(it->location,node->location)<=distance&&it!=node){
                    nodesAround.push_back(it);
                  // }
                }
          }
        }
        w++;
      }
      double mind=INFINITY;
      for(long i=0;i<nodesAround.size();++i){
        if(Functions::getDistance(nodesAround[i]->location,node->location)<mind){
          mind=Functions::getDistance(nodesAround[i]->location,node->location);
          id=nodesAround[i]->id;
        }
      }


    }

    // Point2d simplifiedLocation=Point2d(std::floor(G->nodes[i]->location.x/definition)*definition,std::floor(G->nodes[i]->location.y/definition)*definition);
    // matrix[simplifiedLocation].insert(G->nodes[i]);

    return id;
}



std::vector<Nodo*> NodeSpatialStructure::getNodesAround(Point2d location,double distance){
    double minx=std::floor((location.x-distance)/definition-1.0)*definition;
    double maxx=std::floor((location.x+distance)/definition+1.0)*definition;
    double miny=std::floor((location.y-distance)/definition-1.0)*definition;
    double maxy=std::floor((location.y+distance)/definition+1.0)*definition;
    std::vector<Nodo*> nodesAround;
    for(double i=minx;i<=maxx;i+=definition){
      for(double j=miny;j<=maxy;j+=definition){
            Point2d simplifiedLocation=Point2d(i,j);
            for(auto it:matrix[simplifiedLocation]){
              if(Functions::getDistance(it->location,location)<=distance){
                nodesAround.push_back(it);
              }
            }
      }
    }

    // Point2d simplifiedLocation=Point2d(std::floor(G->nodes[i]->location.x/definition)*definition,std::floor(G->nodes[i]->location.y/definition)*definition);
    // matrix[simplifiedLocation].insert(G->nodes[i]);

    return nodesAround;
}

void NodeSpatialStructure::moveNode(Nodo* node, Point2d finalPosition){
  double xSimplified=std::floor((node->location.x)/definition)*definition;
  double xSimplifiedNew=std::floor((finalPosition.x)/definition)*definition;
  double ySimplified=std::floor((node->location.y)/definition)*definition;
  double ySimplifiedNew=std::floor((finalPosition.y)/definition)*definition;
  if(xSimplified!=xSimplifiedNew||ySimplified!=ySimplifiedNew){
    matrix[Point2d(xSimplified,ySimplified)].erase(node);
    matrix[Point2d(xSimplifiedNew,ySimplifiedNew)].insert(node);

  }
  node->location=finalPosition;

}
// void NodeSpatialStructure::create(std::vector<Nodo*> &nodes){
//     double definition=250;
//     std::unordered_map<Point2d, std::vector<Number> > matrix;
//     for(long i=0;i<nodes.size();i++){
//         Number number;
//         number.value=nodes[i]->mass;
//         number.id=nodes[i]->id;
//         Point2d simplifiedLocation=Point2d(round(nodes[i]->location.x/definition),round(nodes[i]->location.y/definition));
//         matrix[simplifiedLocation].push_back(number);
//
//     }
//     for(auto& it:matrix){
//
//     }
//
// //    double maxX=-INFINITY;
// //    double maxY=-INFINITY;
// //    double minX=INFINITY;
// //    double minY=INFINITY;
// //
// //    for(long i=0;i<nodes.size();i++){
// //        if(nodes[i]->location.x>maxX){
// //            maxX=nodes[i]->location.x;
// //        }
// //        if(nodes[i]->location.y>maxY){
// //            maxY=nodes[i]->location.y;
// //        }
// //        if(nodes[i]->location.x<minX){
// //            minX=nodes[i]->location.x;
// //        }
// //        if(nodes[i]->location.y<minY){
// //            minY=nodes[i]->location.y;
// //        }
// //    }
// //    double widthX=maxX-minX;
// //    double widthY=maxY-minY;
//
//
// }

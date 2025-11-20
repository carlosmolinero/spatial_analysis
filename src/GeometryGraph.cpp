//
//  GeometryGraph.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 10/05/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "GeometryGraph.h"


void GeometryGraph::createBoundaryGraph(Grafo* G,Grafo* boundaryGraph,double alpha){

  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates=Grafo::getCoordinates(G);
  // for(long i=0;i<std::get<0>(coordinates).size();i++){
  //   std::get<0>(coordinates)[i]=i;
  // }
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > boundary=Geometry::calculateAlphaShape(std::get<0>(coordinates),std::get<1>(coordinates),std::get<2>(coordinates),alpha);
  Grafo temp;
  temp.bidirectional=true;
  Grafo::create(&temp,boundary,coordinates,false);
  // Grafo LG;
  Grafo boundaryGraphT;
  Grafo::getLargestComponent(&temp,&boundaryGraphT);
  DualExtendedGraph deg;
  DualExtendedGraph::addPrimal(&deg,&boundaryGraphT);
  DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);

  Grafo* dual=deg.getDualGraph();
  // Grafo
  // Grafo::constructDual   (&LG,&dual);
  // // std::cout<<"Size of the dual of the boundary, nodes: "<<dual.nodes.size()<<'\n';
  std::vector<Link*> links;
  if(dual->nodes.size()>0){
    for(long i=0;i<dual->nodes[0]->links.size();i++){
      links.push_back(boundaryGraphT.links[dual->nodes[0]->links[i]->id]);
    }
  }
  Grafo::inducedSubgraphFromLinks(&boundaryGraphT, boundaryGraph,links);
  // std::cout<<"Size of the boundary, nodes: "<<boundaryGraph->nodes.size()<<", links: "<<boundaryGraph->links.size()<<'\n';

}



void GeometryGraph::createBoundaryGraphUsingDelanuay(Grafo* G,Grafo* boundaryGraph,double multiplierOfMeanWeightToDetermineWhichLinksStay) {
    std::vector<long> ids;
    std::vector<double> xs;
    std::vector<double> ys;
    for(long i=0;i<G->nodes.size();i++){
        ids.push_back(i);
        xs.push_back(G->nodes[i]->location.x);
        ys.push_back(G->nodes[i]->location.y);
    }
    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > result_=Geometry::delaunay(ids,xs,ys);
//    double averWeight=0;
//    for(long i=0;i<std::get<2>(result_).size();i++){
//        averWeight+=std::get<2>(result_)[i];
//    }
//    averWeight/=(double)(std::get<2>(result_).size());
//    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol;
//    std::vector<long> idAsLinks;
//    std::vector<long> idBsLinks;
//    std::vector<double> weights;
//    for(long i=0;i<std::get<2>(result_).size();i++){
//        if(std::get<2>(result_)[i]<averWeight*multiplierOfMeanWeightToDetermineWhichLinksStay){
//            idAsLinks.push_back(std::get<0>(result_)[i]);
//            idBsLinks.push_back(std::get<1>(result_)[i]);
//            weights.push_back(std::get<2>(result_)[i]);
//        }
//    }
//    ncol=std::make_tuple(idAsLinks,idBsLinks,weights);
    DualExtendedGraph deg;
    std::tuple<std::vector<long>, std::vector<double>, std::vector<double> > coordinates;
    coordinates=std::make_tuple(ids,xs,ys);
    DualExtendedGraph::addPrimal(&deg, result_,coordinates , false);
    DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);

    Grafo* dual=deg.getDualGraph();

    std::vector<Link*> links;
    if(dual->nodes.size()>0){
        for(long i=0;i<dual->nodes[0]->links.size();i++){
            links.push_back(deg.getPrimalGraph()->links[dual->nodes[0]->links[i]->id]);
        }
    }
    Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), boundaryGraph,links);

}





std::set<long> GeometryGraph::nodesInPolygon(Grafo* G,Grafo* polygon){
  std::set<long> idNodesInPolygon;
  //    if(!G->isPlanar){
  typedef std::multiset<Number>::iterator It;

  std::set<long> idLinesActive;


  Heap<Number*> events;

  std::vector<std::vector<Number*> > xsById;


  double maxX=-INFINITY;
  double minX=INFINITY;
  double maxY=-INFINITY;
  double minY=INFINITY;

  for(long i=0;i<polygon->links.size();i++){
    Nodo* nodeA;
    Nodo* nodeB;
    nodeA=polygon->links[i]->A();
    nodeB=polygon->links[i]->B();
    bool vertical=false;
    if(nodeA->location.x>maxX){
      maxX=nodeA->location.x;
    }
    if(nodeA->location.x<minX){
      minX=nodeA->location.x;
    }
    if(nodeA->location.y>maxY){
      maxY=nodeA->location.y;
    }
    if(nodeA->location.y<minY){
      minY=nodeA->location.y;
    }
    if(nodeB->location.x>maxX){
      maxX=nodeB->location.x;
    }
    if(nodeB->location.x<minX){
      minX=nodeB->location.x;
    }
    if(nodeB->location.y>maxY){
      maxY=nodeB->location.y;
    }
    if(nodeB->location.y<minY){
      minY=nodeB->location.y;
    }
    if(nodeA->location.x>nodeB->location.x){
//      polygon->links[i]->checkDirection(!polygon->links[i]->inverted);
      nodeA=polygon->links[i]->B();
      nodeB=polygon->links[i]->A();
    }else if(nodeA->location.x==nodeB->location.x){
      vertical=true;
    }
    if(!vertical){
      std::vector<Number*> pair;
      pair.resize(2);

      Number* x1=new Number();


      x1->value=nodeA->location.x;
      x1->id=polygon->links[i]->id;
      x1->qualifier=0;

      pair[0]=(x1);

      Number* x2=new Number();





      x2->value=nodeB->location.x;
      x2->id=polygon->links[i]->id;
      x2->qualifier=1;

      pair[1]=x2;
      xsById.push_back(pair);

      events.push(x1);
      events.push(x2);
    }

  }

//    std::cout<<minX<<","<<minY<<" "<<maxX<<","<<maxY<<'\n';

  for(long i=0;i<G->nodes.size();i++){
    if(G->nodes[i]->location.x>=minX&&G->nodes[i]->location.x<=maxX&&G->nodes[i]->location.y>=minY&&G->nodes[i]->location.y<=maxY){
//        std::cout<<"points("<<G->nodes[i]->location.x<<","<<G->nodes[i]->location.y<<")"<<'\n';
      std::vector<Number*> pair;
      pair.resize(2);

      Number* x1=new Number();


      x1->value=G->nodes[i]->location.x;
      x1->id=G->nodes[i]->id;
      x1->qualifier=3;
      pair[0]=(x1);






      pair[1]=NULL;
      xsById.push_back(pair);

      events.push(x1);
    }

  }

  while(events.size()>0){
    std::vector<Number*> eventsTempLines;
    std::vector<Number*> eventsTempPoints;
    Number* event=events.pop();
    if(event->qualifier<2){
      eventsTempLines.push_back(event);
    }else{
      eventsTempPoints.push_back(event);
    }
    //        eventsTemp.push_back(event);
    while(events.getRoot()!=NULL&&events.getRoot()->value==event->value){
      event=events.pop();
      if(event->qualifier<2){
        eventsTempLines.push_back(event);
      }else{
        eventsTempPoints.push_back(event);
      }
    }
    for(long i=0;i<eventsTempLines.size();i++){
      event=eventsTempLines[i];
      if(event->id!=-1){

        if(idLinesActive.size()==0){

          if(event->qualifier==0){
            idLinesActive.insert(event->id);
          }

        }else{

          if(event->qualifier==0){
            idLinesActive.insert(event->id);

          }else if (event->qualifier==1){
            idLinesActive.erase(event->id);

          }
        }
      }
    }
    for(long i=0;i<eventsTempPoints.size();i++){
      event=eventsTempPoints[i];
      if(event->id!=-1){
        long numberIntersections=0;
        for(auto& it:idLinesActive){
          Link* link=polygon->links[it];
          Nodo* node=G->nodes[event->id];
          Point2d start,end;
          if(link->A()->location.x<link->B()->location.x){
            start=link->A()->location;
            end=link->B()->location;
          }else{
            end=link->A()->location;
            start=link->B()->location;
          }
          Point2d intersectionY;
            double dax=Functions::abs(node->location.x-start.x);
          double y;
            double dx=Functions::abs(end.x-start.x);
          double percentage=dax/dx;
          y=start.y+percentage*(end.y-start.y);
          //                            x=node->location.x;
          //                            intersectionY=Point2d(x,y);
          if(y>node->location.y){
            numberIntersections++;
          }

        }
        //                        std::cout<<" asdf "<<idLinesActive.size()<<" "<<numberIntersections<<'\n';
//          std::cout<<numberIntersections<<'\n';
        if((long)(numberIntersections)%2!=0&&numberIntersections>0){
//            std::cout<<"in"<<'\n';
          idNodesInPolygon.insert(event->id);
        }

      }

    }



  }






  for(long i=0;i<xsById.size();i++){
    if(xsById[i][0]!=NULL){
      delete xsById[i][0];
      xsById[i][0]=NULL;
    }
    if(xsById[i][1]!=NULL){
      delete xsById[i][1];
      xsById[i][1]=NULL;
    }
  }


  //    }
  return idNodesInPolygon;

}




void GeometryGraph::getSubgraphWithinABoundary(Grafo* G,Grafo* boundary,Grafo* result){
  Grafo G2;
  G2.copyGraph(G);
  // std::vector<std::tuple<long,std::vector<long>,std::vector<double> > > pairsOldIdNewIds;
  Grafo::intersectAGraphWithABoundary(&G2,boundary);

  std::set<long> idNodesInBoundary=nodesInPolygon(&G2,boundary);

// DualExtendedGraph deg;
// DualExtendedGraph::addPrimal(&deg,boundary);
// std::vector<long> idNodesInTheFrontier;
//   for(auto it:idNodesInBoundary){
//     for(long i=0;i<G->nodes[it]->links.size();i++){
//       if(idNodesInBoundary.count(G->nodes[it]->links[i]->getOtherNode(G->nodes[it])->id)==0){
//         Nodo* a=deg.getPrimalGraph()->addNode(G->nodes[it]->links[i]->A()->location);
//         Nodo* b=deg.getPrimalGraph()->addNode(G->nodes[it]->links[i]->B()->location);
//         deg.getPrimalGraph()->addLink(a->id,b->id,G->nodes[it]->links[i]->weight);
//         idNodesInTheFrontier.push_back(it);
//       }
//     }
//   }
//   std::vector<Link*> linksToAddLater;
//   DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);
//   for(long i=0;i<idNodesInTheFrontier.size();i++){
//     long id=idNodesInTheFrontier[i];
//     Nodo* nodeInDEG=deg.getPrimalGraph()->getNodeByLocation(G->nodes[id]->location);
//     for(long j=0;j<nodeInDEG->links.size();j++){
//         linksToAddLater.push_back(nodeInDEG->links[j]);
//     }
//
//   }
  // //  Grafo::inducedSubgraph(G, result, idNodesInBoundary);

      std::set<Number> idsNodesTemp;

      result->copyProperties(&G2);
      long i=0;
      for(auto& it:idNodesInBoundary){
          Number number;
          number.value=it;
          number.id=idsNodesTemp.size();
          idsNodesTemp.insert(number);
          i++;
      }



      result->nodes.reserve(idsNodesTemp.size());

      for(auto it:idsNodesTemp){
          result->addNodeAndCopyProperties(G2.nodes[it.value]);

      }

      for(auto& it:idsNodesTemp){
          Nodo* node=G2.nodes[it.value];

          for(long j=0;j<node->links.size(); j++)
          {
              Number searchNumber;
              searchNumber.value=node->links[j]->getOtherNode(node)->id;
              std::set<Number>::iterator it2=idsNodesTemp.find(searchNumber);
              if(it2!=idsNodesTemp.end()){
                  // if(!node->links[j]->inverted){
                      result->addLinkAndCopyProperties(it.id,(*it2).id,node->links[j]);
                  // }else{
                  //     result->addLinkAndCopyProperties((*it2).id,it.id,node->links[j]);
                  // }

              }


          }
      }
      // for(long i=0;i<linksToAddLater.size();i++){
      //   Nodo* a=result->addNode(linksToAddLater[i]->A()->location);
      //   Nodo* b=result->addNode(linksToAddLater[i]->B()->location);
      //   result->addLink(a->id,b->id,linksToAddLater[i]->weight);
      //
      // }
      result->finishedAddingNodes();
}






double GeometryGraph::calculateAproxDiameterGraph(Grafo *G){
  double alpha=INFINITY;
  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates=Grafo::getCoordinates(G);
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > boundary=Geometry::calculateAlphaShape(std::get<0>(coordinates),std::get<1>(coordinates),std::get<2>(coordinates),alpha);
  std::unordered_set<long> setIds;
  for(long i=0;i<std::get<0>(boundary).size();i++){
    setIds.insert(std::get<0>(boundary)[i]);
    setIds.insert(std::get<1>(boundary)[i]);

  }
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
  Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  InterfaceDijkstra result;
  double diameter=0.0;
  for (auto it=setIds.begin(); it!=setIds.end(); ++it){
    Grafo::calculateDijkstra(G, G->nodes[*it], result, 0,numbersRepresentingNodes,inDijkstra,inCutoff);

    for(long j=0;j<result.size();j++){
      if(result.getMinDistance(j)<INFINITY&&result.getMinDistance(j)>diameter){
        diameter=result.getMinDistance(j);
      }
    }
  }

  Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);

  return diameter;


}



double GeometryGraph::calculateAreaPolygon(Grafo* polygons){

//  polygon->links[0]->checkDirection(false);
  std::vector<Grafo> components;
  Grafo::getComponents(polygons,components,3);
  double totalArea=0;
  for(long i=0;i<components.size();i++){
    Grafo* polygon=&components[i];
    std::vector<long> idNodesA;
    std::vector<long> idTransitionsA;
    std::vector<bool> invertedTransitionsA;
    bool correctResultA;
    Grafo::getRegionOfALink(polygon,polygon->links[0],idNodesA,idTransitionsA,invertedTransitionsA,false,correctResultA);
    // std::cout<<correctResultA<<'\n';
    Point2d centroidA(0,0);
    double numberNodes=0;
    double areaA;
    std::vector<Point2d> points;
    points.reserve(idNodesA.size());
    for(long j=0;j<idNodesA.size();j++){
      // std::cout<<idNodesA[j]<<'\n';
      centroidA.x+=polygon->nodes[idNodesA[j]]->location.x;
      centroidA.y+=polygon->nodes[idNodesA[j]]->location.y;
      numberNodes++;
      points.push_back(polygon->nodes[idNodesA[j]]->location);
    }
    areaA=Functions::area(points);
    totalArea+=areaA;
  }
  return totalArea;
}



std::vector<double> GeometryGraph::calculateHuMoments(Grafo* region){
  double width=10;

  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<region->nodes.size();i++){
    if(region->nodes[i]->location.x>maxX){
      maxX=region->nodes[i]->location.x;

    }
    if(region->nodes[i]->location.y>maxY){
      maxY=region->nodes[i]->location.y;

    }
    if(region->nodes[i]->location.x<minX){
      minX=region->nodes[i]->location.x;

    }
    if(region->nodes[i]->location.y<minY){
      minY=region->nodes[i]->location.y;

    }
  }


  Grafo grid;
  for(long i=0;i<ceil((maxX-minX)/width);i++){
    for(long j=0;j<ceil((maxY-minY)/width);j++){
      grid.addNode(minX+width*i,minY+width*j);
    }
  }

  std::set<long> nodesInPolygon=GeometryGraph::nodesInPolygon(&grid,region);
  std::vector<double> p,q;
  p.push_back(0.0);
  q.push_back(0.0);



  p.push_back(0.0);
  q.push_back(1.0);

  p.push_back(1.0);
  q.push_back(0.0);

  p.push_back(1.0);
  q.push_back(1.0);

  p.push_back(2.0);
  q.push_back(0.0);

  p.push_back(0.0);
  q.push_back(2.0);

   p.push_back(2.0);
  q.push_back(1.0);

  p.push_back(1.0);
  q.push_back(2.0);





  p.push_back(3.0);
  q.push_back(0.0);

  p.push_back(0.0);
  q.push_back(3.0);
  std::vector<double> rawMoments;
  rawMoments.resize(10,0.0);
  for(long i=0;i<p.size();i++){
    for(auto it:nodesInPolygon){
      rawMoments[i]+=pow(grid.nodes[it]->location.x,p[i])*pow(grid.nodes[it]->location.y,q[i])*width*width;
    }
  }
  double xmean=rawMoments[2]/rawMoments[0];
  double ymean=rawMoments[1]/rawMoments[0];
  std::vector<double> centralMoments;
  centralMoments.resize(10,0.0);
  centralMoments[0]=rawMoments[0];
  centralMoments[1]=0.0;
  centralMoments[2]=0.0;
  centralMoments[3]=rawMoments[3]-xmean*rawMoments[1];
  centralMoments[4]=rawMoments[4]-xmean*rawMoments[2];
  centralMoments[5]=rawMoments[5]-ymean*rawMoments[1];
  centralMoments[6]=rawMoments[6]-2*xmean*rawMoments[3]-ymean*rawMoments[4]+2*xmean*xmean*rawMoments[1];
  centralMoments[7]=rawMoments[7]-2*ymean*rawMoments[3]-xmean*rawMoments[5]+2*ymean*ymean*rawMoments[2];
  centralMoments[8]=rawMoments[8]-3*xmean*rawMoments[4]+2*xmean*xmean*rawMoments[2];
  centralMoments[9]=rawMoments[9]-3*ymean*rawMoments[5]+2*ymean*ymean*rawMoments[1];

  std::vector<double> scaleInvariants;
  scaleInvariants.resize(10,0.0);

  for(long i=0;i<p.size();i++){
    scaleInvariants[i]=centralMoments[i]/pow(centralMoments[0],1.0+(p[i]+q[i])/2.0);
  }

  // std::vector<double> scaleInvariants;
  // scaleInvariants.resize(10,0.0);
  //
  // for(long i=0;i<p.size();i++){
  //   scaleInvariants[i]=centralMoments[i]/pow(centralMoments[0],1.0+(p[i]+q[i])/2.0);
  // }
  std::vector<double> HuMoments;
  HuMoments.resize(8,0.0);
  HuMoments[0]=centralMoments[4]+centralMoments[5];
  HuMoments[1]=pow(centralMoments[4]-centralMoments[5],2.0)+4*pow(centralMoments[3],2.0);
  HuMoments[2]=pow(centralMoments[8]-centralMoments[7],2.0)+pow(3*centralMoments[6]-centralMoments[9],2.0);
  HuMoments[3]=pow(centralMoments[8]+centralMoments[7],2.0)+pow(centralMoments[7]+centralMoments[9],2.0);
  HuMoments[4]=(centralMoments[8]-3*centralMoments[7])*(centralMoments[8]+centralMoments[7])*(pow(centralMoments[8]+centralMoments[7],2.0)-3*pow(centralMoments[6]+centralMoments[9],2.0))+(3*centralMoments[6]-centralMoments[9])*(centralMoments[6]+centralMoments[9])*(3*pow(centralMoments[8]+centralMoments[7],2.0)-pow(centralMoments[6]+centralMoments[9],2.0));
  HuMoments[5]=(centralMoments[4]-centralMoments[5])*(pow(centralMoments[8]+centralMoments[7],2.0)-pow(centralMoments[6]+centralMoments[9],2.0))+4*centralMoments[3]*(centralMoments[8]+centralMoments[7])*(centralMoments[6]+centralMoments[9]);
  HuMoments[6]=(3*centralMoments[6]-centralMoments[9])*(centralMoments[8]+centralMoments[7])*(pow(centralMoments[8]+centralMoments[7],2.0)-3*(centralMoments[6]+centralMoments[9],2.0))-(centralMoments[8]-3*centralMoments[7])*(centralMoments[6]+centralMoments[9])*(3*pow(centralMoments[8]+centralMoments[7],2.0)-pow(centralMoments[6]+centralMoments[9],2.0));
  HuMoments[7]=centralMoments[3]*(pow(centralMoments[8]+centralMoments[7],2.0)-pow(centralMoments[9]+centralMoments[6],2.0))-(centralMoments[4]-centralMoments[5])*(centralMoments[8]+centralMoments[7])*(centralMoments[9]+centralMoments[6]);

  return HuMoments;
}











double GeometryGraph::calculateAreaSetOfPoints(std::set<Point2d>& points){
    Grafo G;
    for(auto it:points){
        G.addNode(it);
    }
    Grafo boundary;

    GeometryGraph::createBoundaryGraphUsingDelanuay(&G, &boundary, 3);
    double area=0;
    if(boundary.links.size()>3){
        area=GeometryGraph::calculateAreaPolygon(&boundary);
    }else{
//        std::cout<<"no boundary, size of points "<<points.size()<<'\n';
    }
    return area;

}







void GeometryGraph::calculateAreaSetOfPoints_preparationForParallel(std::vector<std::set<Point2d> >& pointsPerIdCluster,long startIndex,long endIndex,std::vector<double>& areas){
    for(long i=startIndex;i<endIndex;i++){
        areas[i]=GeometryGraph::calculateAreaSetOfPoints(pointsPerIdCluster[i]);
    }
}



// std::tuple<std::vector<long>,std::vector<long> > getNodesFromOtherGraphClosestToNodes(Grafo* G,Grafo OG,double lengthSquareSpatialIndex){
//     std::unordered_map<
//     for(long i=0;i<OG->nodes.size();++i){
//
//     }
//
//
// }

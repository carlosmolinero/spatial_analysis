// [[Rcpp::plugins(cpp11)]]
#include <Rcpp.h>
#include <unordered_set>
#include <vector>

#include "SpatialAnalysis/SpatialAnalysis/Functions.h"
#include "SpatialAnalysis/SpatialAnalysis/ShapeFile.h"

#include "SpatialAnalysis/SpatialAnalysis/FractalDimension.h"
#include "SpatialAnalysis/SpatialAnalysis/Geometry.h"
#include "SpatialAnalysis/SpatialAnalysis/GeometryGraph.h"
#include "SpatialAnalysis/SpatialAnalysis/DualExtendedGraph.h"
#include "SpatialAnalysis/SpatialAnalysis/Grafo.h"
#include "SpatialAnalysis/SpatialAnalysis/OSM.h"
#include <stdio.h>
#include <sstream>
#include <queue>
#include <string>
#include <tuple>
#include "SpatialAnalysis/SpatialAnalysis/InterfaceCityGeneration.h"
#include "SpatialAnalysis/SpatialAnalysis/InterfaceMultiFractalAnalysis.h"
#include "SpatialAnalysis/SpatialAnalysis/GenerativeProcedures.h"
#include "SpatialAnalysis/SpatialAnalysis/CriticalExponentsPercolation.h"
#include "SpatialAnalysis/SpatialAnalysis/InterfaceDijkstra.h"
#include "SpatialAnalysis/SpatialAnalysis/SpatialInteraction.h"
#include <iterator>
#include <utility>
#include "SpatialAnalysis/SpatialAnalysis/Entropy.h"
#include "SpatialAnalysis/SpatialAnalysis/Fxy.h"
#include "SpatialAnalysis/SpatialAnalysis/Distribution.h"
#include "SpatialAnalysis/SpatialAnalysis/NodeSpatialStructure.h"
#include "SpatialAnalysis/SpatialAnalysis/InterfaceIntersectionObject.h"
#include "SpatialAnalysis/SpatialAnalysis/ExtrudedGraph.h"
#include "SpatialAnalysis/SpatialAnalysis/Point3d.h"
#include "SpatialAnalysis/SpatialAnalysis/Tree.h"

using namespace Rcpp;

template <>
struct std::hash<std::vector<long> > {
public:
    size_t operator()(std::vector<long> n) const throw() {
        size_t value=hash<long>() (n[0]);
        for(long i=1;i<n.size();i++){
          value=value^hash<long>() (n[i]);
        }
        return value;

    }
};

template <>
struct std::hash<std::vector<double> > {
public:
    size_t operator()(std::vector<double> n) const throw() {
        size_t value=hash<double>() (n[0]);
        for(long i=1;i<n.size();i++){
          value=value^hash<double>() (n[i]);
        }
        return value;

    }
};

RCPP_EXPOSED_CLASS(Grafo)
RCPP_EXPOSED_CLASS(DualExtendedGraph)
RCPP_EXPOSED_CLASS(InterfaceCityGeneration)
RCPP_EXPOSED_CLASS(InterfaceMultiFractalAnalysis)

void out(std::string text){
  std::cout<<text<<'\n';
}

void out(long number){
  std::stringstream ss;
  ss<<number;
  std::cout<<ss.str()<<'\n';
}


// [[Rcpp::export]]
void deleteDEG(XPtr<DualExtendedGraph> deg){
  deg->reset();
  deg.release();
  // delete (DualExtendedGraph*)(deg);
}

// [[Rcpp::export]]
void deleteGraph(XPtr<Grafo> G){
  G->reset();
  G.release();
  // delete (Grafo*) ();
}



// [[Rcpp::export]]
XPtr< DualExtendedGraph > createDEG(DataFrame ncol,DataFrame coordinates,bool directed){
  NumericVector ids=as<NumericVector>(coordinates[0]);
  NumericVector x=as<NumericVector>(coordinates[1]);
  NumericVector y=as<NumericVector>(coordinates[2]);
  NumericVector idA=as<NumericVector>(ncol[0]);
  NumericVector idB=as<NumericVector>(ncol[1]);
  NumericVector weights=as<NumericVector>(ncol[2]);




  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);

 //  for(long i=0;i<idA_.size();i++){
 //    idA_[i]=idA_[i]-1;
 //    idB_[i]=idB_[i]-1;
 //  }
 //  for(long i=0;i<ids_.size();i++){
 //   ids_[i]--;
 // }
 std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
 std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;

 coordinates_=std::make_tuple(ids_,x_,y_);


 ncol_=std::make_tuple(idA_,idB_,weights_);


 DualExtendedGraph* deg=new DualExtendedGraph();
 DualExtendedGraph::addPrimal(deg,ncol_,coordinates_,directed);

 Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;
 return (p);
}


// [[Rcpp::export]]
XPtr< Grafo > createGraph(DataFrame ncol,DataFrame coordinates,bool directed){
  NumericVector ids=as<NumericVector>(coordinates[0]);
  NumericVector x=as<NumericVector>(coordinates[1]);
  NumericVector y=as<NumericVector>(coordinates[2]);
  NumericVector idA=as<NumericVector>(ncol[0]);
  NumericVector idB=as<NumericVector>(ncol[1]);
  NumericVector weights=as<NumericVector>(ncol[2]);




  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);

 //  for(long i=0;i<idA_.size();i++){
 //    idA_[i]=idA_[i]-1;
 //    idB_[i]=idB_[i]-1;
 //  }
 //  for(long i=0;i<ids_.size();i++){
 //   ids_[i]--;
 // }
 std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
 std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;

 coordinates_=std::make_tuple(ids_,x_,y_);


 ncol_=std::make_tuple(idA_,idB_,weights_);


 Grafo* G=new Grafo();
 Grafo::create(G,ncol_,coordinates_,directed);

 Rcpp::XPtr< Grafo > p(G,true) ;
 return (p);
}




// [[Rcpp::export]]
XPtr< Grafo > createPseudoGraph(DataFrame ncol,DataFrame coordinates,bool directed){
  NumericVector ids=as<NumericVector>(coordinates[0]);
  NumericVector x=as<NumericVector>(coordinates[1]);
  NumericVector y=as<NumericVector>(coordinates[2]);
  NumericVector idA=as<NumericVector>(ncol[0]);
  NumericVector idB=as<NumericVector>(ncol[1]);
  NumericVector weights=as<NumericVector>(ncol[2]);




  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);

 //  for(long i=0;i<idA_.size();i++){
 //    idA_[i]=idA_[i]-1;
 //    idB_[i]=idB_[i]-1;
 //  }
 //  for(long i=0;i<ids_.size();i++){
 //   ids_[i]--;
 // }
 std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
 std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;

 coordinates_=std::make_tuple(ids_,x_,y_);


 ncol_=std::make_tuple(idA_,idB_,weights_);


 Grafo* G=new Grafo();
 // G->pseudoGraph=true;
 Grafo::createPseudoGraph(G,ncol_,coordinates_,directed);

 Rcpp::XPtr< Grafo > p(G,true) ;
 return (p);
}




// [[Rcpp::export]]
XPtr< DualExtendedGraph > createDEG_mass(DataFrame ncol,DataFrame coordinates,NumericVector masses,bool directed){
  NumericVector ids=as<NumericVector>(coordinates[0]);
  NumericVector x=as<NumericVector>(coordinates[1]);
  NumericVector y=as<NumericVector>(coordinates[2]);
  NumericVector idA=as<NumericVector>(ncol[0]);
  NumericVector idB=as<NumericVector>(ncol[1]);
  NumericVector weights=as<NumericVector>(ncol[2]);




  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);

 //  for(long i=0;i<idA_.size();i++){
 //    idA_[i]=idA_[i]-1;
 //    idB_[i]=idB_[i]-1;
 //  }
 //  for(long i=0;i<ids_.size();i++){
 //   ids_[i]--;
 // }
 std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
 std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;

 coordinates_=std::make_tuple(ids_,x_,y_);


 ncol_=std::make_tuple(idA_,idB_,weights_);


 DualExtendedGraph* deg=new DualExtendedGraph();
 std::vector<double> masses_=as<std::vector<double> > (masses);
 DualExtendedGraph::addPrimal(deg,ncol_,coordinates_,masses_,directed);

 Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;
 return (p);
}

// [[Rcpp::export]]
XPtr< DualExtendedGraph > createDEGFromFile(String ncolFileName,String coordinatesFileName,String separatorNCOL,String separatorCoordinates,bool directed){
  // NumericVector ids=as<NumericVector>(coordinates[0]);
  // NumericVector x=as<NumericVector>(coordinates[1]);
  // NumericVector y=as<NumericVector>(coordinates[2]);
  // NumericVector idA=as<NumericVector>(ncol[0]);
  // NumericVector idB=as<NumericVector>(ncol[1]);
  // NumericVector weights=as<NumericVector>(ncol[2]);
  //
  //
  //
  //
  // std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  // std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  // std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  // std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  // std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  // std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);
  //
  // for(long i=0;i<idA_.size();i++){
  //   idA_[i]=idA_[i]-1;
  //   idB_[i]=idB_[i]-1;
  // }
  // for(long i=0;i<ids_.size();i++){
  //   ids_[i]--;
  // }
  // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
  // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;
  //
  // coordinates_=std::make_tuple(ids_,x_,y_);
  //
  //
  // ncol_=std::make_tuple(idA_,idB_,weights_);


  DualExtendedGraph* deg=new DualExtendedGraph();

  TextFile::parseNCOLandSeparateCoordinatesFile(deg->getPrimalGraph(),directed,ncolFileName, coordinatesFileName, separatorNCOL, separatorCoordinates, true);
  // DualExtendedGraph::addPrimal(deg,ncol_,coordinates_,directed);

  // DualExtendedGraph::setPrimalAsPlanar(deg);
  // DualExtendedGraph::setPrimalAsSimplified(deg);
  // DualExtendedGraph::setPrimalAsStructuralGraph(deg);
  // DualExtendedGraph::useOnlyLargestConnectedComponent(deg);

  Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;
  return (p);
}


// [[Rcpp::export]]
XPtr< DualExtendedGraph > createDEG_FromGraph(XPtr<Grafo> G){
  // NumericVector ids=as<NumericVector>(coordinates[0]);
  // NumericVector x=as<NumericVector>(coordinates[1]);
  // NumericVector y=as<NumericVector>(coordinates[2]);
  // NumericVector idA=as<NumericVector>(ncol[0]);
  // NumericVector idB=as<NumericVector>(ncol[1]);
  // NumericVector weights=as<NumericVector>(ncol[2]);
  //
  //
  //
  //
  // std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  // std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  // std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  // std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  // std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  // std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);
  //
  // for(long i=0;i<idA_.size();i++){
  //   idA_[i]=idA_[i]-1;
  //   idB_[i]=idB_[i]-1;
  // }
  // for(long i=0;i<ids_.size();i++){
  //   ids_[i]--;
  // }
  // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
  // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;
  //
  // coordinates_=std::make_tuple(ids_,x_,y_);
  //
  //
  // ncol_=std::make_tuple(idA_,idB_,weights_);


  DualExtendedGraph* deg=new DualExtendedGraph();

  // TextFile::parseNCOLandSeparateCoordinatesFile(deg->getPrimalGraph(),directed,ncolFileName, coordinatesFileName, separatorNCOL, separatorCoordinates, true);
  DualExtendedGraph::addPrimal(deg,G);

  // DualExtendedGraph::setPrimalAsPlanar(deg);
  // DualExtendedGraph::setPrimalAsSimplified(deg);
  // DualExtendedGraph::setPrimalAsStructuralGraph(deg);
  // DualExtendedGraph::useOnlyLargestConnectedComponent(deg);

  Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;
  return (p);
}

// [[Rcpp::export]]
XPtr< Grafo > getLargestComponent(XPtr< Grafo > G){
  Grafo* LCC=new Grafo();
  Grafo::getLargestComponent(G,LCC);
   Rcpp::XPtr< Grafo > p(LCC,true) ;
  return (p);
}



// [[Rcpp::export]]
void addAnotherGraph(XPtr< DualExtendedGraph > deg,XPtr< Grafo > G){
DualExtendedGraph::addAnotherGraph(deg,G,true);
}
// [[Rcpp::export]]
void addAnotherDEG(XPtr< DualExtendedGraph > deg,XPtr< DualExtendedGraph > otherDEG){
DualExtendedGraph::addAnotherDEG(deg,otherDEG,true);
}

// [[Rcpp::export]]
void setPrimalAsPseudoGraph(XPtr< DualExtendedGraph > deg){
  deg->getPrimalGraph()->pseudoGraph=true;
}

// [[Rcpp::export]]
void allowLoops(XPtr< DualExtendedGraph > deg){
  deg->getPrimalGraph()->allowLoops=true;
}

// [[Rcpp::export]]
void setPrimalAsStructuralGraph(XPtr< DualExtendedGraph > deg){
  // NumericVector ids=as<NumericVector>(coordinates[0]);
  // NumericVector x=as<NumericVector>(coordinates[1]);
  // NumericVector y=as<NumericVector>(coordinates[2]);
  // NumericVector idA=as<NumericVector>(ncol[0]);
  // NumericVector idB=as<NumericVector>(ncol[1]);
  // NumericVector weights=as<NumericVector>(ncol[2]);
  //
  //
  //
  //
  // std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  // std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  // std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  // std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  // std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  // std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);
  //
  // for(long i=0;i<idA_.size();i++){
  //   idA_[i]=idA_[i]-1;
  //   idB_[i]=idB_[i]-1;
  // }
  // for(long i=0;i<ids_.size();i++){
  //   ids_[i]--;
  // }
  // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
  // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol_;
  //
  // coordinates_=std::make_tuple(ids_,x_,y_);
  //
  //
  // ncol_=std::make_tuple(idA_,idB_,weights_);


  // DualExtendedGraph* deg=new DualExtendedGraph();

  // TextFile::parseNCOLandSeparateCoordinatesFile(deg->getPrimalGraph(),directed,ncolFileName, coordinatesFileName, separatorNCOL, separatorCoordinates, true);
  // DualExtendedGraph::addPrimal(deg,ncol_,coordinates_,directed);

  DualExtendedGraph::setPrimalAsPlanar(deg);
  DualExtendedGraph::setPrimalAsSimplified(deg);
  DualExtendedGraph::setPrimalAsStructuralGraph(deg);
  // DualExtendedGraph::useOnlyLargestConnectedComponent(deg);

  // Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;
  // return (deg);
}

// [[Rcpp::export]]
XPtr< DualExtendedGraph > readShapeFileIntoDEG(String folder,String nameNoExtension,String EPSG_in,String EPSG_out,bool directed){

  out("reading shapeFile");

  std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >,std::vector<std::string>, int  > result=ShapeFile::readShapeFile(folder,nameNoExtension,EPSG_in,EPSG_out);


  out("create Graph");
  DualExtendedGraph* deg=new DualExtendedGraph();
  DualExtendedGraph::addPrimal(deg,std::get<0>(result), std::get<1>(result),std::get<2>(result),std::get<3>(result),directed);
  Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;

    // Rcpp::XPtr< Graph > G=_createGraph(result[0],result[1],directed);

  return (p);

}

// [[Rcpp::export]]
XPtr< Grafo > readShapeFileIntoGraph(String folder,String nameNoExtension,String EPSG_in,String EPSG_out,bool directed){

  out("reading shapeFile");

  std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >,std::vector<std::string> ,int > result=ShapeFile::readShapeFile(folder,nameNoExtension,EPSG_in,EPSG_out);


  out("create Graph");
  Grafo* G=new Grafo();
  Grafo::create(G,std::get<0>(result), std::get<1>(result),std::get<2>(result),std::get<3>(result),directed);
  Rcpp::XPtr< Grafo > p(G,true) ;

    // Rcpp::XPtr< Graph > G=_createGraph(result[0],result[1],directed);

  return (p);

}

// [[Rcpp::export]]
void unPlanarizeUsingIntersectionPointsAndOriginalIdsOfLinks(XPtr< DualExtendedGraph > deg,XPtr< Grafo > intersectionPoints){
  DualExtendedGraph::unPlanarizeUsingIntersectionPointsAndOriginalIdsOfLinks(deg,intersectionPoints);
}


// [[Rcpp::export]]
DataFrame readAttributesShapeFile(String folder,String nameNoExtension){

  out("reading shapeFile");

  // std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >,std::vector<std::string>  > result=ShapeFile::readShapeFile(folder,nameNoExtension,EPSG_in,EPSG_out);
std::tuple<std::vector<std::string>, std::vector<std::vector<std::string> > > table=ShapeFile::readAttributeShapefile(folder,nameNoExtension);

  // out("create Graph");
  // DualExtendedGraph* deg=new DualExtendedGraph();
  // DualExtendedGraph::addPrimal(deg,std::get<0>(result), std::get<1>(result),std::get<2>(result),directed);
  // Rcpp::XPtr< DualExtendedGraph > p(deg,true) ;


  long numberObjectsDataFrame=std::get<0>(table).size();
  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(std::get<1>(table)[i]));
  }

  CharacterVector namevec;
  for(long i=0;i<numberObjectsDataFrame;i++){
    namevec.push_back(std::get<0>(table)[i]);
  }




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
    // Rcpp::XPtr< Graph > G=_createGraph(result[0],result[1],directed);



}




// [[Rcpp::export]]
void forcePlanarityPrimal(XPtr< DualExtendedGraph > deg){
  DualExtendedGraph::forcePlanarityPrimal(deg,1);
}

//// [[Rcpp::export]]
//void createDual(XPtr< DualExtendedGraph > deg){
//  DualExtendedGraph::createDualOfPrimal(deg);
//}

// [[Rcpp::export]]
void simplifyPrimal(XPtr< DualExtendedGraph > deg){
  DualExtendedGraph::simplify(deg);
}


// [[Rcpp::export]]
DataFrame getCoordinatesDual(XPtr< DualExtendedGraph > deg){

  NumericVector id(deg->getDualGraph()->nodes.size());
  NumericVector x(deg->getDualGraph()->nodes.size());
  NumericVector y(deg->getDualGraph()->nodes.size());


  for(long j=0;j<deg->getDualGraph()->nodes.size();j++){
    id[j]=(deg->getDualGraph()->nodes[j]->id);
    x[j]=(deg->getDualGraph()->nodes[j]->location.x);
    y[j]=(deg->getDualGraph()->nodes[j]->location.y);
  }

  List list(3);
  list[0]=(id);
  list[1]=(x);
  list[2]=(y);

  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("x");
  namevec.push_back("y");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}

// [[Rcpp::export]]
DataFrame getCoordinatesStructural(XPtr< DualExtendedGraph > deg){

  NumericVector id(deg->getStructuralGraph()->nodes.size());
  NumericVector x(deg->getStructuralGraph()->nodes.size());
  NumericVector y(deg->getStructuralGraph()->nodes.size());


  for(long j=0;j<deg->getStructuralGraph()->nodes.size();j++){
    id[j]=(deg->getStructuralGraph()->nodes[j]->id);
    x[j]=(deg->getStructuralGraph()->nodes[j]->location.x);
    y[j]=(deg->getStructuralGraph()->nodes[j]->location.y);
  }

  List list(3);
  list[0]=(id);
  list[1]=(x);
  list[2]=(y);

  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("x");
  namevec.push_back("y");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}
// [[Rcpp::export]]
DataFrame getCoordinatesPrimal(XPtr< DualExtendedGraph > deg){

  NumericVector id(deg->getPrimalGraph()->nodes.size());
  NumericVector x(deg->getPrimalGraph()->nodes.size());
  NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    id[j]=(deg->getPrimalGraph()->nodes[j]->id);
    x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  List list(3);
  list[0]=(id);
  list[1]=(x);
  list[2]=(y);

  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("x");
  namevec.push_back("y");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}


// [[Rcpp::export]]
NumericVector getMassesNodesPrimal(XPtr< DualExtendedGraph > deg){

  NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    masses[j]=deg->getPrimalGraph()->nodes[j]->mass;
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  return masses;
}

// [[Rcpp::export]]
NumericVector getMassesUpperLevelNodesPrimal(XPtr< DualExtendedGraph > deg){

  NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    masses[j]=deg->getPrimalGraph()->nodes[j]->mass_upperLevel;
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  return masses;
}


// [[Rcpp::export]]
NumericVector getEquivalentAreaNodesPrimal(XPtr< DualExtendedGraph > deg){

  NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    masses[j]=deg->getPrimalGraph()->nodes[j]->equivalentArea;
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  return masses;
}

// [[Rcpp::export]]
NumericVector getMassesNodesDual(XPtr< DualExtendedGraph > deg){

  NumericVector masses(deg->getDualGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getDualGraph()->nodes.size();j++){
    masses[j]=deg->getDualGraph()->nodes[j]->mass;
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  return masses;
}

// [[Rcpp::export]]
NumericVector getPerimeterRegionsDual(XPtr<DualExtendedGraph> deg){
  return wrap(DualExtendedGraph::getPerimeterRegionsDual(deg));
}

// [[Rcpp::export]]
void setWeightsPrimal(XPtr< DualExtendedGraph > deg,NumericVector weights){

  // NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->links.size();j++){
    deg->getPrimalGraph()->links[j]->weight=weights[j];
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }
  deg->softReset();

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  // return masses;
}

// [[Rcpp::export]]
NumericVector getWeightsPrimal(XPtr< DualExtendedGraph > deg){

  // NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());

  NumericVector weights(deg->getPrimalGraph()->links.size());
  for(long j=0;j<deg->getPrimalGraph()->links.size();j++){
    weights[j]=deg->getPrimalGraph()->links[j]->weight;
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }
  // deg->softReset();
  return weights;

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  // return masses;
}


// [[Rcpp::export]]
void setMassesNodesPrimal(XPtr< DualExtendedGraph > deg,NumericVector masses){

  // NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    deg->getPrimalGraph()->nodes[j]->mass=masses[j];
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  // return masses;
}
// [[Rcpp::export]]
void setMassesUpperLevelNodesPrimal(XPtr< DualExtendedGraph > deg,NumericVector masses){

  // NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    deg->getPrimalGraph()->nodes[j]->mass_upperLevel=masses[j];
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  // return masses;
}
// [[Rcpp::export]]
void setEquivalentAreasNodesPrimal(XPtr< DualExtendedGraph > deg,NumericVector areas){

  // NumericVector masses(deg->getPrimalGraph()->nodes.size());
  // NumericVector x(deg->getPrimalGraph()->nodes.size());
  // NumericVector y(deg->getPrimalGraph()->nodes.size());


  for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
    deg->getPrimalGraph()->nodes[j]->equivalentArea=areas[j];
    // x[j]=(deg->getPrimalGraph()->nodes[j]->location.x);
    // y[j]=(deg->getPrimalGraph()->nodes[j]->location.y);
  }

  // List list(3);
  // list[0]=(id);
  // list[1]=(x);
  // list[2]=(y);

  // CharacterVector namevec;
  // namevec.push_back("id");
  // namevec.push_back("x");
  // namevec.push_back("y");
  // list.attr("names") = namevec;
  // DataFrame df(list);

  // return masses;
}
// [[Rcpp::export]]
NumericVector getMassesNodes(XPtr< Grafo > G){

  NumericVector masses(G->nodes.size());
  // NumericVector masses;


  for(long j=0;j<G->nodes.size();j++){
    masses[j]=(G->nodes[j]->mass);

  }



  return masses;
}

// [[Rcpp::export]]
void setMassesNodes(XPtr< Grafo > G,NumericVector masses){


  for(long j=0;j<G->nodes.size();j++){
    G->nodes[j]->mass=masses[j];

  }


}

// [[Rcpp::export]]
DataFrame getCoordinates(XPtr< Grafo > G){

  NumericVector id(G->nodes.size());
  NumericVector x(G->nodes.size());
  NumericVector y(G->nodes.size());


  for(long j=0;j<G->nodes.size();j++){
    id[j]=(G->nodes[j]->id);
    x[j]=(G->nodes[j]->location.x);
    y[j]=(G->nodes[j]->location.y);
  }

  List list(3);
  list[0]=(id);
  list[1]=(x);
  list[2]=(y);

  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("x");
  namevec.push_back("y");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}
// [[Rcpp::export]]
DataFrame getNCOL(XPtr< Grafo > G){

  NumericVector idA(G->links.size());
  NumericVector idB(G->links.size());
  NumericVector weights(G->links.size());


  for(long j=0;j<G->links.size();j++){
    idA[j]=(G->links[j]->A()->id);
    idB[j]=(G->links[j]->B()->id);
    weights[j]=(G->links[j]->weight);
  }

  List list(3);
  list[0]=(idA);
  list[1]=(idB);
  list[2]=(weights);

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}

// [[Rcpp::export]]
DataFrame getNCOLPrimal(XPtr< DualExtendedGraph > deg){

  NumericVector idA(deg->getPrimalGraph()->links.size());
  NumericVector idB(deg->getPrimalGraph()->links.size());
  NumericVector weights(deg->getPrimalGraph()->links.size());


  for(long j=0;j<deg->getPrimalGraph()->links.size();j++){
    idA[j]=(deg->getPrimalGraph()->links[j]->A()->id);
    idB[j]=(deg->getPrimalGraph()->links[j]->B()->id);
    weights[j]=(deg->getPrimalGraph()->links[j]->weight);
  }

  List list(3);
  list[0]=(idA);
  list[1]=(idB);
  list[2]=(weights);

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}

// [[Rcpp::export]]
NumericVector getOriginalIdsLinksPrimal(XPtr< DualExtendedGraph > deg){
  NumericVector originalIds(deg->getPrimalGraph()->links.size());
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    originalIds[i]=(deg->getPrimalGraph()->links[i]->originalID);
  }
  return originalIds;
}

// [[Rcpp::export]]
NumericVector getOriginalIdsLinks(XPtr< Grafo > G){
  NumericVector originalIds(G->links.size());
  for(long i=0;i<G->links.size();i++){
    originalIds[i]=(G->links[i]->originalID);
  }
  return originalIds;
}



// [[Rcpp::export]]
StringVector getIdentifiersNodesPrimal(XPtr< DualExtendedGraph > deg){
  StringVector identifiers(deg->getPrimalGraph()->nodes.size());
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    identifiers[i]=(deg->getPrimalGraph()->nodes[i]->identifier);
  }
  return identifiers;
}

// [[Rcpp::export]]
StringVector getIdentifiersLinksPrimal(XPtr< DualExtendedGraph > deg){
  StringVector identifiers(deg->getPrimalGraph()->links.size());
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    identifiers[i]=(deg->getPrimalGraph()->links[i]->identifier);
  }
  return identifiers;
}




// [[Rcpp::export]]
NumericVector getOriginalIdsNodesPrimal(XPtr< DualExtendedGraph > deg){
  NumericVector originalIds(deg->getPrimalGraph()->nodes.size());
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    originalIds[i]=(deg->getPrimalGraph()->nodes[i]->originalID);
  }
  return originalIds;
}

// [[Rcpp::export]]
void setOriginalIdsNodesPrimal(XPtr<DualExtendedGraph> deg,NumericVector originalIds){
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    deg->getPrimalGraph()->nodes[i]->originalID=originalIds[i];
  }
}


// [[Rcpp::export]]
StringVector getIdentifiersNodes(XPtr< Grafo > G){
  StringVector originalIds(G->nodes.size());
  for(long i=0;i<G->nodes.size();i++){
    originalIds[i]=(G->nodes[i]->identifier);
  }
  return originalIds;
}

// [[Rcpp::export]]
NumericVector getOriginalIdsNodes(XPtr< Grafo > G){
  NumericVector originalIds(G->nodes.size());
  for(long i=0;i<G->nodes.size();i++){
    originalIds[i]=(G->nodes[i]->originalID);
  }
  return originalIds;
}

// [[Rcpp::export]]
DataFrame getNCOLStructural(XPtr< DualExtendedGraph > deg){

  NumericVector idA(deg->getStructuralGraph()->links.size());
  NumericVector idB(deg->getStructuralGraph()->links.size());
  NumericVector weights(deg->getStructuralGraph()->links.size());


  for(long j=0;j<deg->getStructuralGraph()->links.size();j++){
    idA[j]=(deg->getStructuralGraph()->links[j]->A()->id);
    idB[j]=(deg->getStructuralGraph()->links[j]->B()->id);
    weights[j]=(deg->getStructuralGraph()->links[j]->weight);
  }

  List list(3);
  list[0]=(idA);
  list[1]=(idB);
  list[2]=(weights);

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}
// [[Rcpp::export]]
DataFrame getNCOLDual(XPtr< DualExtendedGraph > deg){

  NumericVector idA(deg->getDualGraph()->links.size());
  NumericVector idB(deg->getDualGraph()->links.size());
  NumericVector weights(deg->getDualGraph()->links.size());


  for(long j=0;j<deg->getDualGraph()->links.size();j++){
    idA[j]=(deg->getDualGraph()->links[j]->A()->id);
    idB[j]=(deg->getDualGraph()->links[j]->B()->id);
    weights[j]=(deg->getDualGraph()->links[j]->weight);
  }

  List list(3);
  list[0]=(idA);
  list[1]=(idB);
  list[2]=(weights);

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);

  return df;
}


// // [[Rcpp::export]]
// double calculateBoxCounting(NumericVector xs,NumericVector ys,double max,double min,double widthPoint){
//   std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
//   std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
//   double result=FractalDimension::calculateBoxCounting(xs_,ys_,max,min,widthPoint);
//   return result;
// }

// // [[Rcpp::export]]
// DataFrame  calculateBoxCounting_getPoints(NumericVector xs,NumericVector ys,NumericVector gridSizes,double widthPoint){
//   std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
//   std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
//   std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);
//   std::vector<std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(xs_,ys_,gridSizes_,widthPoint);
//   List list(2);
//   list[0]=(wrap(result_[0]));
//   list[1]=(wrap(result_[1]));
// //    list[2]=(weights);

//   CharacterVector namevec;
//   namevec.push_back("xs");
//   namevec.push_back("ys");
// //    namevec.push_back("weight");
//   list.attr("names") = namevec;
//   DataFrame df(list);
//   return df;
// }

// [[Rcpp::export]]
DataFrame  calculateBoxCounting_getPoints(XPtr<Grafo> G,long depthLimit){
  // std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  // std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  // std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);
  // std::vector<std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(xs_,ys_,gridSizes_,widthPoint);
  // List list(2);
  // list[0]=(wrap(result_[0]));
  // list[1]=(wrap(result_[1]));

  std::tuple<std::vector<double>,std::vector<double> > result_=FractalDimension::boxCountingPlaneSweep(G,depthLimit);
//    list[2]=(weights);
 List list(2);
  list[0]=wrap(std::get<0>(result_));
  list[1]=wrap(std::get<1>(result_));
  CharacterVector namevec;
  namevec.push_back("xs");
  namevec.push_back("ys");
//    namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

// [[Rcpp::export]]
DataFrame  calculateBoxCounting_getPoints_check(XPtr<Grafo> G,long depthLimit){
  // std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  // std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  // std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);
  // std::vector<std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(xs_,ys_,gridSizes_,widthPoint);
  // List list(2);
  // list[0]=(wrap(result_[0]));
  // list[1]=(wrap(result_[1]));

  std::tuple<std::vector<double>,std::vector<double> > result_=FractalDimension::boxCountingCheckPlaneSweep(G,depthLimit);
//    list[2]=(weights);
 List list(2);
  list[0]=wrap(std::get<0>(result_));
  list[1]=wrap(std::get<1>(result_));
  CharacterVector namevec;
  namevec.push_back("xs");
  namevec.push_back("ys");
//    namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}
// [[Rcpp::export]]
DataFrame  calculateBoxCounting_getPoints_usingPointsFromGraph(XPtr<Grafo> G,long depthLimit){
  // std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  // std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  // std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);


 double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;
        Point2d centroid(0,0);
        for(long i=0;i<G->nodes.size();i++){
            centroid.x+=G->nodes[i]->location.x;
            centroid.y+=G->nodes[i]->location.y;
            if(G->nodes[i]->location.x>maxX){
                maxX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y>maxY){
                maxY=G->nodes[i]->location.y;
            }
            if(G->nodes[i]->location.x<minX){
                minX=G->nodes[i]->location.x;
            }
            if(G->nodes[i]->location.y<minY){
                minY=G->nodes[i]->location.y;
            }
        }

        centroid.x/=(double)(G->nodes.size());
        centroid.y/=(double)(G->nodes.size());


        double radius=0;
        radius=Functions::max(Functions::max(maxX-centroid.x,centroid.x-minX),Functions::max(maxY-centroid.y,centroid.y-minY));

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;
    // long depthLimit=10;
std::vector<double> sizeGridPerLevel;
        for(long j=0;j<depthLimit;j++){
                sizeGridPerLevel.push_back((2*radius)/pow(2,j));
            }

double subdivision=(2*radius)/pow(2.0,16.0);
                std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(G,subdivision);
std::vector<double> x;
    std::vector<double> y;


  std::vector<std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(std::get<0>(points),std::get<1>(points),sizeGridPerLevel,(2*radius)/pow(2.0,16.0));
  List list(2);
  list[0]=(wrap(result_[0]));
  list[1]=(wrap(result_[1]));
// std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint
  // std::tuple<std::vector<double>,std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(G,depthLimit);
//    list[2]=(weights);
 // List list(2);
 //  list[0]=wrap(std::get<0>(result_));
 //  list[1]=wrap(std::get<1>(result_));
  CharacterVector namevec;
  namevec.push_back("xs");
  namevec.push_back("ys");
//    namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

// [[Rcpp::export]]
DataFrame  calculateBoxCounting_getPoints_usingPoints(NumericVector xs,NumericVector ys,NumericVector gridSizes,double widthPoint){
  std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);
  std::vector<std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(xs_,ys_,gridSizes_,widthPoint);
  List list(2);
  list[0]=(wrap(result_[0]));
  list[1]=(wrap(result_[1]));
// std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint
  // std::tuple<std::vector<double>,std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(G,depthLimit);
//    list[2]=(weights);
 // List list(2);
 //  list[0]=wrap(std::get<0>(result_));
 //  list[1]=wrap(std::get<1>(result_));
  CharacterVector namevec;
  namevec.push_back("xs");
  namevec.push_back("ys");
//    namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


// [[Rcpp::export]]
DataFrame  calculateBoxCounting_getPoints_mixScales(XPtr<Grafo> G,double depthLimit){
  // std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  // std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  // std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);


//  double maxX=-INFINITY;
//         double minX=INFINITY;
//         double maxY=-INFINITY;
//         double minY=INFINITY;
//         Point2d centroid(0,0);
//         for(long i=0;i<G->nodes.size();i++){
//             centroid.x+=G->nodes[i]->location.x;
//             centroid.y+=G->nodes[i]->location.y;
//             if(G->nodes[i]->location.x>maxX){
//                 maxX=G->nodes[i]->location.x;
//             }
//             if(G->nodes[i]->location.y>maxY){
//                 maxY=G->nodes[i]->location.y;
//             }
//             if(G->nodes[i]->location.x<minX){
//                 minX=G->nodes[i]->location.x;
//             }
//             if(G->nodes[i]->location.y<minY){
//                 minY=G->nodes[i]->location.y;
//             }
//         }

//         centroid.x/=(double)(G->nodes.size());
//         centroid.y/=(double)(G->nodes.size());


//         double radius=0;
//         radius=Functions::max(Functions::max(maxX-centroid.x,centroid.x-minX),Functions::max(maxY-centroid.y,centroid.y-minY));

//     //    std::vector<double> xs_result;
//     //    std::vector<double> ys_result;
//     long depthLimit=10;
// std::vector<double> sizeGridPerLevel;
//         for(long j=0;j<depthLimit;j++){
//                 sizeGridPerLevel.push_back((2*radius)/pow(2,j));
//             }

// double subdivision=(2*radius)/pow(2.0,16.0);
//                 std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(G,subdivision);
// std::vector<double> x;
//     std::vector<double> y;


//   std::vector<std::vector<double> > result_=FractalDimension::calculateBoxCounting_getPoints(std::get<0>(points),std::get<1>(points),sizeGridPerLevel,(2*radius)/pow(2.0,16.0));
//   List list(2);
//   list[0]=(wrap(result_[0]));
//   list[1]=(wrap(result_[1]));
// std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint
  std::tuple<std::vector<double>,std::vector<double> > result_=FractalDimension::boxCountingPlaneSweep_mixScales(G,depthLimit);

 List list(2);
  list[0]=wrap(std::get<0>(result_));
  list[1]=wrap(std::get<1>(result_));
  CharacterVector namevec;
  namevec.push_back("xs");
  namevec.push_back("ys");
//    namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



// [[Rcpp::export]]
double calculateBoxCounting(XPtr<Grafo> G){
  return FractalDimension::calculateBoxCounting(G);
}

// // [[Rcpp::export]]
// double calculateNumberOccupiedBoxes(XPtr<Grafo> grafo,double roundingFactor,double displacementX,double displacementY){
//   Grafo G;
//   G.copyGraph(grafo);
//   double minX=INFINITY;
//   double minY=INFINITY;
//   double maxX=-INFINITY;
//   double maxY=-INFINITY;
//   for(long i=0;i<G.nodes.size();i++){
//     if(G.nodes[i]->location.x>maxX){
//         maxX=G.nodes[i]->location.x;
//     }
//     if(G.nodes[i]->location.y>maxY){
//         maxY=G.nodes[i]->location.y;
//     }
//     if(G.nodes[i]->location.x<minX){
//         minX=G.nodes[i]->location.x;
//     }
//     if(G.nodes[i]->location.y<minY){
//         minY=G.nodes[i]->location.y;
//     }
//   }
//   // double centeringGridX=-(std::floor((minX-displacementX)/roundingFactor)*roundingFactor-minX);
//   // double centeringGridY=-(std::floor((minY-displacementY)/roundingFactor)*roundingFactor-minY);
//
//   // double x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
//   // double y=std::floor((minY-displacementY)/roundingFactor)*roundingFactor+centeringGridY;
//   double x=
//   Grafo squareSubdivision;
//   squareSubdivision.bidirectional=true;
//   while (x<maxX){
//
//     Nodo* a=squareSubdivision.addNode(Point2d(x,y-10));
//     Nodo* b=squareSubdivision.addNode(Point2d(x,maxY+10));
//     squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     // a=squareSubdivision.addNode(Point2d(x+roundingFactor/100,y-10));
//     // b=squareSubdivision.addNode(Point2d(x+roundingFactor/100,maxY+10));
//     // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     // a=squareSubdivision.addNode(Point2d(x-roundingFactor/100,y-10));
//     // b=squareSubdivision.addNode(Point2d(x-roundingFactor/100,maxY+10));
//     // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     x+=roundingFactor;
//   }
//   x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
//   while (y<maxY){
//
//     Nodo* a=squareSubdivision.addNode(Point2d(x-10,y));
//     Nodo* b=squareSubdivision.addNode(Point2d(maxX+10,y));
//     squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     // a=squareSubdivision.addNode(Point2d(x-10,y+roundingFactor/100));
//     // b=squareSubdivision.addNode(Point2d(maxX+10,y+roundingFactor/100));
//     // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     // a=squareSubdivision.addNode(Point2d(x-10,y-roundingFaOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesOccupiedBoxesctor/100));
//     // b=squareSubdivision.addNode(Point2d(maxX+10,y-roundingFactor/100));
//     // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
//     y+=roundingFactor;
//   }
//   Grafo::intersectAGraphWithABoundary(&G,&squareSubdivision);
//
//   long numberOccupiedBoxes=0;
//   SparseMatrix matrix;
//   for(long i=0;i<G.nodes.size();i++){
//     double epsilon=Functions::min(1.0/100000.0,roundingFactor/100.0);
//     double x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor)*roundingFactor+minX;
//     double y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor)*roundingFactor+minY;
//     double x1=std::floor((G.nodes[i]->location.x-minX-epsilon)/roundingFactor)*roundingFactor+minX;
//     double y1=std::floor((G.nodes[i]->location.y-minY-epsilon)/roundingFactor)*roundingFactor+minY;
//     double x2=std::floor((G.nodes[i]->location.x-minX+epsilon)/roundingFactor)*roundingFactor+minX;
//     double y2=std::floor((G.nodes[i]->location.y-minY+epsilon)/roundingFactor)*roundingFactor+minY;
//     std::vector<double> xSec;
//     std::vector<double> ySec;
//     xSec.push_back(x);
//     ySec.push_back(y);
//     // matrix[Point2d(x,y)].push_back(i);
//
//     // bool addSecondaryLocation=false;
//
//     // if(x+roundingFactor/2.0>786092&&x+roundingFactor/2.0<786093&&y+roundingFactor/2.0>6002344.34&&y+roundingFactor/2.0<6002352){
//     // // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
//     //   std::cout<<"texting "<<x<<","<<y<<" "<<G.nodes[i]->location.x<<","<<G.nodes[i]->location.y<<" dif: "<<(x-G.nodes[i]->location.x)<<","<<(y-G.nodes[i]->location.y)<<'\n';
//     // }
//     if(x!=x1){
//       // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
//       xSec.push_back(x1);
//       // addSecondaryLocation=true;
//     }
//     if(x!=x2){
//       // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
//       xSec.push_back(x2);
//       // addSecondaryLocation=true;
//     }
//     if(y!=y1){
//       // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
//       ySec.push_back(y1);
//       // addSecondaryLocation=true;
//     }
//     if(y!=y2){
//       // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
//       ySec.push_back(y2);
//       // addSecondaryLocation=true;
//     }
//     // if(Functions::abs(x+roundingFactor-G.nodes[i]->location.x)<epsilon){
//     //   x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor+1)*roundingFactor+minX;
//     //   addSecondaryLocation=true;
//     // }
//     // if(Functions::abs(y+roundingFactor-G.nodes[i]->location.y)<epsilon){
//     //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor+1)*roundingFactor+minY;
//     //   addSecondaryLocation=true;
//     // }
//     // if(Functions::abs(y-G.nodes[i]->location.y)<epsilon){
//     //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor-1)*roundingFactor+minY;
//     //   addSecondaryLocation=true;
//     // }
//     // if(addSecondaryLocation){
//       // std::cout<<"adding secondary location"<<'\n';
//       for(long j=0;j<xSec.size();j++){
//         for(long k=0;k<ySec.size();k++){
//           x=xSec[j];
//           y=ySec[k];
//           double originalValue=matrix.getValue(x,y);
//           matrix.setValue(x,y,originalValue+1);
//           if(originalValue==0){
//             numberOccupiedBoxes++;
//           }
//         }
//       }
//     // if((G.nodes[i]->location.x-displacementX)>=x+roundingFactor/10.0&&(G.nodes[i]->location.x-displacementX)<=(x+roundingFactor)-roundingFactor/10.0&&(G.nodes[i]->location.y-displacementY)>=y+roundingFactor/10.0&&(G.nodes[i]->location.y-displacementY)<=(y+roundingFactor)-roundingFactor/10.0){
//
//     // }
//     // double epsilon=.01;
//     // bool addSecondaryLocation=false;
//     // if(Functions::abs(x-G.nodes[i]->location.x-displacementX)<epsilon){
//     //   x=std::floor((G.nodes[i]->location.x-displacementX)/roundingFactor-1)*roundingFactor;
//     //   addSecondaryLocation=true;
//     // }
//     // if(Functions::abs(y-G.nodes[i]->location.y-displacementY)<epsilon){
//     //   y=std::floor((G.nodes[i]->location.y-displacementY)/roundingFactor-1)*roundingFactor;
//     //   addSecondaryLocation=true;
//     // }
//     // if(addSecondaryLocation){
//     //   originalValue=matrix.getValue(x,y);
//     //   matrix.setValue(x,y,originalValue+1);
//     //   if(originalValue==0){
//     //     numberOccupiedBoxes++;
//     //   }
//     // }
//   }
//   return numberOccupiedBoxes;
//
//
//
//   // std::unordered_map<Point2d, std::vector<long> > matrix;
//   // double av=0;
//   // double num=0;
//   // for(long i=0;i<G.nodes.size();i++){
//   //   double x=std::floor((G.nodes[i]->location.x-displacementX)/roundingFactor)*roundingFactor;
//   //   double y=std::floor((G.nodes[i]->location.y-displacementY)/roundingFactor)*roundingFactor;
//   //
//   //   matrix[Point2d(x,y)].push_back(i);
//   //   double epsilon=.01;
//   //   bool addSecondaryLocation=false;
//   //   if(Functions::abs(x-G.nodes[i]->location.x-displacementX)<epsilon){
//   //     x=std::floor((G.nodes[i]->location.x-displacementX)/roundingFactor-1)*roundingFactor;
//   //     addSecondaryLocation=true;
//   //   }
//   //   if(Functions::abs(y-G.nodes[i]->location.y-displacementY)<epsilon){
//   //     y=std::floor((G.nodes[i]->location.y-displacementY)/roundingFactor-1)*roundingFactor;
//   //     addSecondaryLocation=true;
//   //   }
//   //   if(addSecondaryLocation){
//   //     matrix[Point2d(x,y)].push_back(i);
//   //   }
//   //
//   //
//   //
//   //
//   // }
//   // std::vector<double> lengths;
//   // for(auto it:matrix){
//   //   Grafo boundary;
//   //   boundary.bidirectional=true;
//   //   double border=10.0;
//   //   Nodo* a=boundary.addNode(Point2d(it.first.x+roundingFactor/border+displacementX,it.first.y+roundingFactor/border+displacementY));
//   //   Nodo* b=boundary.addNode(Point2d(it.first.x+roundingFactor-roundingFactor/border+displacementX,it.first.y+roundingFactor/border+displacementY));
//   //   Nodo* c=boundary.addNode(Point2d(it.first.x+roundingFactor-roundingFactor/border+displacementX,it.first.y+roundingFactor-roundingFactor/border+displacementY));
//   //   Nodo* d=boundary.addNode(Point2d(it.first.x+roundingFactor/border+displacementX,it.first.y+roundingFactor-roundingFactor/border+displacementY));
//   //   boundary.addLink(a->id,b->id,roundingFactor-2*roundingFactor/border);
//   //   boundary.addLink(b->id,c->id,roundingFactor-2*roundingFactor/border);
//   //   boundary.addLink(c->id,d->id,roundingFactor-2*roundingFactor/border);
//   //   boundary.addLink(d->id,a->id,roundingFactor-2*roundingFactor/border);
//   //   //
//   //   //
//   //   Grafo sg;
//   //   // GeometryGraph::getSubgraphWithinABoundary(G,&boundary,&sg);
//   //   Grafo::inducedSubgraph(&G,&sg,it.second);
//   //   Grafo ssg;
//   //   GeometryGraph::getSubgraphWithinABoundary(&sg,&boundary,&ssg);
//   //   double l=0;
//   //   for(long i=0;i<ssg.links.size();i++){
//   //     l+=ssg.links[i]->weight;
//   //   }
//   //   if(l>0){
//   //     numberOccupiedBoxes++;
//   //   }
//   //   // lengths.push_back(l);
//   //   av+=l;
//   //   num++;
//   // }
//   // av/=num;
//   //
//   // return numberOccupiedBoxes;
//
// }
// [[Rcpp::export]]
double calculateNumberOccupiedBoxesFromPixelsGraph(XPtr<Grafo> pixelG,double widthPixel,double roundingFactor){

  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;

  for(long i=0;i<pixelG->nodes.size();i++){
    if(pixelG->nodes[i]->location.x>maxX){
      maxX=pixelG->nodes[i]->location.x;
    }
    if(pixelG->nodes[i]->location.y>maxY){
      maxY=pixelG->nodes[i]->location.y;
    }
    if(pixelG->nodes[i]->location.x<minX){
      minX=pixelG->nodes[i]->location.x;
    }
    if(pixelG->nodes[i]->location.y<minY){
      minY=pixelG->nodes[i]->location.y;
    }
  }
  long numberOccupiedBoxes=0;
  SparseMatrix matrix;
  // double centeringGridX=-(std::floor((minX-displacementX)/roundingFactor)*roundingFactor-minX);
  // double centeringGridY=-(std::floor((minY-displacementY)/roundingFactor)*roundingFactor-minY);
  // centeringGridX=0;
  // centeringGridY=0;
  // displacementX+=minXGrid;
  // displacementY+=minYGrid;

  for(long i=0;i<pixelG->nodes.size();i++){
    double xTemp=(pixelG->nodes[i]->location.x)-minX+widthPixel/2.0;
    double yTemp=(pixelG->nodes[i]->location.y)-minY+widthPixel/2.0;
    // double x=std::floor(xTemp/roundingFactor)*roundingFactor+minX;
    // double y=std::floor(yTemp/roundingFactor)*roundingFactor+minY;
    double x=std::floor(xTemp/roundingFactor);
    double y=std::floor(yTemp/roundingFactor);

    // if((pixelG->nodes[i]->location.x-displacementX)>=x+roundingFactor/10.0&&(pixelG->nodes[i]->location.x-displacementX)<=(x+roundingFactor)-roundingFactor/10.0&&(pixelG->nodes[i]->location.y-displacementY)>=y+roundingFactor/10.0&&(pixelG->nodes[i]->location.y-displacementY)<=(y+roundingFactor)-roundingFactor/10.0){
    if(pixelG->nodes[i]->location.x<maxX&&pixelG->nodes[i]->location.y<maxY){//quitar el maximo para evitar que se salga de los bordes del maximo
      double originalValue=matrix.getValue(x,y);
      matrix.setValue(x,y,originalValue+pixelG->nodes[i]->mass);
      if(originalValue==0){
        // std::cout<<roundingFactor<<" "<<x<<","<<y<<'\n';
        numberOccupiedBoxes++;
      }
    }
    // }

  }
  return numberOccupiedBoxes;




}

// [[Rcpp::export]]
NumericVector calculateLengthPerBoxFromPixelGraph(XPtr<Grafo> pixelG,double widthPixel,double roundingFactor){

  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<pixelG->nodes.size();i++){
    if(pixelG->nodes[i]->location.x>maxX){
      maxX=pixelG->nodes[i]->location.x;
    }
    if(pixelG->nodes[i]->location.y>maxY){
      maxY=pixelG->nodes[i]->location.y;
    }
    if(pixelG->nodes[i]->location.x<minX){
      minX=pixelG->nodes[i]->location.x;
    }
    if(pixelG->nodes[i]->location.y<minY){
      minY=pixelG->nodes[i]->location.y;
    }
  }
  long numberOccupiedBoxes=0;
  SparseMatrix matrix;
  // double centeringGridX=-(std::floor((minX-displacementX)/roundingFactor)*roundingFactor-minX);
  // double centeringGridY=-(std::floor((minY-displacementY)/roundingFactor)*roundingFactor-minY);
  // centeringGridX=0;
  // centeringGridY=0;
  // displacementX+=minXGrid;
  // displacementY+=minYGrid;

  for(long i=0;i<pixelG->nodes.size();i++){
    double xTemp=(pixelG->nodes[i]->location.x)-minX+widthPixel/2.0;
    double yTemp=(pixelG->nodes[i]->location.y)-minY+widthPixel/2.0;
    // double x=std::floor(xTemp/roundingFactor)*roundingFactor+minX;
    // double y=std::floor(yTemp/roundingFactor)*roundingFactor+minY;
    double x=std::floor(xTemp/roundingFactor);
    double y=std::floor(yTemp/roundingFactor);

    // if((pixelG->nodes[i]->location.x-displacementX)>=x+roundingFactor/10.0&&(pixelG->nodes[i]->location.x-displacementX)<=(x+roundingFactor)-roundingFactor/10.0&&(pixelG->nodes[i]->location.y-displacementY)>=y+roundingFactor/10.0&&(pixelG->nodes[i]->location.y-displacementY)<=(y+roundingFactor)-roundingFactor/10.0){

    if(pixelG->nodes[i]->location.x<maxX&&pixelG->nodes[i]->location.y<maxY){//quitar el maximo para evitar que se salga de los bordes del maximo
      double originalValue=matrix.getValue(x,y);
      matrix.setValue(x,y,originalValue+pixelG->nodes[i]->mass);
      if(originalValue==0){
        // std::cout<<roundingFactor<<" "<<x<<","<<y<<'\n';
        numberOccupiedBoxes++;
      }
    }
    // }

  }
  std::vector<double> lengths;
  lengths.reserve(matrix.size());
  for(auto it:matrix.cells){
    lengths.push_back(it.second.value);
  }
  return wrap(lengths);




}

// [[Rcpp::export]]
XPtr<Grafo> createPixelGraph (XPtr<Grafo> grafo,double lengthSidePixel,double displacementX,double displacementY){
  double roundingFactor=lengthSidePixel;
  Grafo* pixelGraph=new Grafo();
  Grafo G;
  G.copyGraph(grafo);
  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<G.nodes.size();i++){
    if(G.nodes[i]->location.x>maxX){
      maxX=G.nodes[i]->location.x;
    }
    if(G.nodes[i]->location.y>maxY){
      maxY=G.nodes[i]->location.y;
    }
    if(G.nodes[i]->location.x<minX){
      minX=G.nodes[i]->location.x;
    }
    if(G.nodes[i]->location.y<minY){
      minY=G.nodes[i]->location.y;
    }
  }
  // double centeringGridX=(std::floor((minX)/roundingFactor)*roundingFactor-minX);
  // double centeringGridY=(std::floor((minY)/roundingFactor)*roundingFactor-minY);
  // double x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
  // double y=std::floor((minY-displacementY)/roundingFactor)*roundingFactor+centeringGridY;
  double x=minX;
  double y=minY;
  Grafo squareSubdivision;
  squareSubdivision.bidirectional=true;
  while (x<=maxX){

    Nodo* a=squareSubdivision.addNode(Point2d(x+displacementX,minY-10+displacementY));
    Nodo* b=squareSubdivision.addNode(Point2d(x+displacementX,maxY+10+displacementY));
    squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x+roundingFactor/100,y-10));
    // b=squareSubdivision.addNode(Point2d(x+roundingFactor/100,maxY+10));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-roundingFactor/100,y-10));
    // b=squareSubdivision.addNode(Point2d(x-roundingFactor/100,maxY+10));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    x+=roundingFactor;
  }
  // x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
  // x=minX;
  while (y<=maxY){

    Nodo* a=squareSubdivision.addNode(Point2d(minX-10+displacementX,y+displacementY));
    Nodo* b=squareSubdivision.addNode(Point2d(maxX+10+displacementX,y+displacementY));
    squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-10,y+roundingFactor/100));
    // b=squareSubdivision.addNode(Point2d(maxX+10,y+roundingFactor/100));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-10,y-roundingFactor/100));
    // b=squareSubdivision.addNode(Point2d(maxX+10,y-roundingFactor/100));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    y+=roundingFactor;
  }
  Grafo::intersectAGraphWithABoundary(&G,&squareSubdivision);
  std::unordered_map<Point2d, std::vector<long> > matrix;
  double av=0;
  double num=0;
  for(long i=0;i<G.nodes.size();i++){
    double epsilon=Functions::min(1.0/100000.0,roundingFactor/100.0);
    double x=std::floor((G.nodes[i]->location.x-minX-displacementX)/roundingFactor)*roundingFactor+minX;
    double y=std::floor((G.nodes[i]->location.y-minY-displacementY)/roundingFactor)*roundingFactor+minY;
    double x1=std::floor((G.nodes[i]->location.x-minX-epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
    double y1=std::floor((G.nodes[i]->location.y-minY-epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
    double x2=std::floor((G.nodes[i]->location.x-minX+epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
    double y2=std::floor((G.nodes[i]->location.y-minY+epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
    std::vector<double> xSec;
    std::vector<double> ySec;
    xSec.push_back(x);
    ySec.push_back(y);
    // matrix[Point2d(x,y)].push_back(i);

    // bool addSecondaryLocation=false;

    // if(x+roundingFactor/2.0>786092&&x+roundingFactor/2.0<786093&&y+roundingFactor/2.0>6002344.34&&y+roundingFactor/2.0<6002352){
    // // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
    //   std::cout<<"texting "<<x<<","<<y<<" "<<G.nodes[i]->location.x<<","<<G.nodes[i]->location.y<<" dif: "<<(x-G.nodes[i]->location.x)<<","<<(y-G.nodes[i]->location.y)<<'\n';
    // }
    if(x!=x1){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      xSec.push_back(x1);
      // addSecondaryLocation=true;
    }
    if(x!=x2){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      xSec.push_back(x2);
      // addSecondaryLocation=true;
    }
    if(y!=y1){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      ySec.push_back(y1);
      // addSecondaryLocation=true;
    }
    if(y!=y2){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      ySec.push_back(y2);
      // addSecondaryLocation=true;
    }
    // if(Functions::abs(x+roundingFactor-G.nodes[i]->location.x)<epsilon){
    //   x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor+1)*roundingFactor+minX;
    //   addSecondaryLocation=true;
    // }
    // if(Functions::abs(y+roundingFactor-G.nodes[i]->location.y)<epsilon){
    //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor+1)*roundingFactor+minY;
    //   addSecondaryLocation=true;
    // }
    // if(Functions::abs(y-G.nodes[i]->location.y)<epsilon){
    //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor-1)*roundingFactor+minY;
    //   addSecondaryLocation=true;
    // }
    // if(addSecondaryLocation){
      // std::cout<<"adding secondary location"<<'\n';
      for(long j=0;j<xSec.size();j++){
        for(long k=0;k<ySec.size();k++){
          matrix[Point2d(xSec[j],ySec[k])].push_back(i);
        }
      }

    // }

  }
  std::vector<double> lengths;
  // double maxx=-INFINITY;
  // double maxy=-INFINITY;
  // for(auto it:matrix){
  //   if(it.first.x>maxx){
  //     maxx=it.first.x;
  //   }
  //   if(it.first.y>maxy){
  //     maxy=it.first.y;
  //   }
  // }
  for(auto it:matrix){
    // Grafo boundary;
    // boundary.bidirectional=true;
    // Nodo* a=boundary.addNode(Point2d(it.first.x+displacementX,it.first.y+displacementY));
    // Nodo* b=boundary.addNode(Point2d(it.first.x+displacementX+roundingFactor,it.first.y+displacementY));
    // Nodo* c=boundary.addNode(Point2d(it.first.x+displacementX+roundingFactor,it.first.y+displacementY+roundingFactor));
    // Nodo* d=boundary.addNode(Point2d(it.first.x+displacementX,it.first.y+displacementY+roundingFactor));
    // boundary.addLink(a->id,b->id,roundingFactor);
    // boundary.addLink(b->id,c->id,roundingFactor);
    // boundary.addLink(c->id,d->id,roundingFactor);
    // boundary.addLink(d->id,a->id,roundingFactor);
    //
    //
    Grafo sg;
    // GeometryGraph::getSubgraphWithinABoundary(G,&boundary,&sg);
    Grafo::inducedSubgraph(&G,&sg,it.second);
    double l=0;
    for(long i=0;i<sg.links.size();i++){
      l+=sg.links[i]->weight;
    }

    double x=it.first.x+roundingFactor/2.0;
    double y=it.first.y+roundingFactor/2.0;
    // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
    //   std::cout<<"textingB "<<x<<","<<y<<" "<<it.first.x<<","<<it.first.y<<" "<<l<<" "<<sg.nodes.size()<<" "<<sg.links.size()<<'\n';
    // }
    // double x=it.first.x;
    // double y=it.first.y;
    // if(it.first.x<maxx&&it.first.y<maxy&&l>0){
    if(l>0){
      Nodo* node=pixelGraph->addNode(Point2d(x,y));
      node->mass=l;
    }
    // }

    // lengths.push_back(l);
    av+=l;
    num++;
  }
  av/=num;

  // return av;
  Rcpp::XPtr<Grafo> p(pixelGraph,true);
  return p;
  // Distribution dis=Distribution::createDistribution(lengths);

  // return (Distribution::getMode(&dis));

}


























// [[Rcpp::export]]
DataFrame calculateMonteCarloFractalDimension (XPtr<Grafo> grafo,XPtr<Grafo> boundary,double lengthSidePixel,double minSize,double maxSize){
  bool quick=true;
  double displacementX=0;
  double displacementY=0;
  // double minSide=INFINITY;
  // for(long i=0;i<sideBoxes.size();i++){
  //   if(sideBoxes[i]<minSide){
  //     minSide=sideBoxes[i];
  //   }
  // }
  // double lengthSidePixel=minSide/4.0;
  double roundingFactor=lengthSidePixel;
  Grafo* pixelGraph=new Grafo();
  Grafo G;
  G.copyGraph(grafo);
  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<G.nodes.size();i++){
    if(G.nodes[i]->location.x>maxX){
      maxX=G.nodes[i]->location.x;
    }
    if(G.nodes[i]->location.y>maxY){
      maxY=G.nodes[i]->location.y;
    }
    if(G.nodes[i]->location.x<minX){
      minX=G.nodes[i]->location.x;
    }
    if(G.nodes[i]->location.y<minY){
      minY=G.nodes[i]->location.y;
    }
  }


  Grafo boundaryGrid;
  SparseMatrix boundaryMatrix;
  for(double x=minX;x<=maxX;x+=lengthSidePixel){
    for(double y=minY;y<=maxY;y+=lengthSidePixel){
      boundaryGrid.addNode(Point2d(x,y));
    }

  }
  Grafo withinBoundary;
  GeometryGraph::getSubgraphWithinABoundary(&boundaryGrid,boundary,&withinBoundary);

for(long i=0;i<withinBoundary.nodes.size();i++){
  double x=withinBoundary.nodes[i]->location.x;
  double y=withinBoundary.nodes[i]->location.y;
  boundaryMatrix.setValue(x,y,1);
}


  // double centeringGridX=(std::floor((minX)/roundingFactor)*roundingFactor-minX);
  // double centeringGridY=(std::floor((minY)/roundingFactor)*roundingFactor-minY);
  // double x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
  // double y=std::floor((minY-displacementY)/roundingFactor)*roundingFactor+centeringGridY;
  double x=minX;
  double y=minY;
  Grafo squareSubdivision;
  squareSubdivision.bidirectional=true;
  while (x<=maxX){

    Nodo* a=squareSubdivision.addNode(Point2d(x+displacementX,minY-10+displacementY));
    Nodo* b=squareSubdivision.addNode(Point2d(x+displacementX,maxY+10+displacementY));
    squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x+roundingFactor/100,y-10));
    // b=squareSubdivision.addNode(Point2d(x+roundingFactor/100,maxY+10));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-roundingFactor/100,y-10));
    // b=squareSubdivision.addNode(Point2d(x-roundingFactor/100,maxY+10));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    x+=roundingFactor;
  }
  // x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
  // x=minX;
  while (y<=maxY){

    Nodo* a=squareSubdivision.addNode(Point2d(minX-10+displacementX,y+displacementY));
    Nodo* b=squareSubdivision.addNode(Point2d(maxX+10+displacementX,y+displacementY));
    squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-10,y+roundingFactor/100));
    // b=squareSubdivision.addNode(Point2d(maxX+10,y+roundingFactor/100));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-10,y-roundingFactor/100));
    // b=squareSubdivision.addNode(Point2d(maxX+10,y-roundingFactor/100));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    y+=roundingFactor;
  }
  Grafo::intersectAGraphWithABoundary(&G,&squareSubdivision);
  std::unordered_map<Point2d, std::vector<long> > matrix;
  double av=0;
  double num=0;
  for(long i=0;i<G.nodes.size();i++){
    double epsilon=Functions::min(1.0/100000.0,roundingFactor/100.0);
    double x=std::floor((G.nodes[i]->location.x-minX-displacementX)/roundingFactor)*roundingFactor+minX;
    double y=std::floor((G.nodes[i]->location.y-minY-displacementY)/roundingFactor)*roundingFactor+minY;
    double x1=std::floor((G.nodes[i]->location.x-minX-epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
    double y1=std::floor((G.nodes[i]->location.y-minY-epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
    double x2=std::floor((G.nodes[i]->location.x-minX+epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
    double y2=std::floor((G.nodes[i]->location.y-minY+epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
    std::vector<double> xSec;
    std::vector<double> ySec;
    xSec.push_back(x);
    ySec.push_back(y);
    // matrix[Point2d(x,y)].push_back(i);

    // bool addSecondaryLocation=false;

    // if(x+roundingFactor/2.0>786092&&x+roundingFactor/2.0<786093&&y+roundingFactor/2.0>6002344.34&&y+roundingFactor/2.0<6002352){
    // // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
    //   std::cout<<"texting "<<x<<","<<y<<" "<<G.nodes[i]->location.x<<","<<G.nodes[i]->location.y<<" dif: "<<(x-G.nodes[i]->location.x)<<","<<(y-G.nodes[i]->location.y)<<'\n';
    // }
    if(x!=x1){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      xSec.push_back(x1);
      // addSecondaryLocation=true;
    }
    if(x!=x2){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      xSec.push_back(x2);
      // addSecondaryLocation=true;
    }
    if(y!=y1){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      ySec.push_back(y1);
      // addSecondaryLocation=true;
    }
    if(y!=y2){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      ySec.push_back(y2);
      // addSecondaryLocation=true;
    }
    // if(Functions::abs(x+roundingFactor-G.nodes[i]->location.x)<epsilon){
    //   x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor+1)*roundingFactor+minX;
    //   addSecondaryLocation=true;
    // }
    // if(Functions::abs(y+roundingFactor-G.nodes[i]->location.y)<epsilon){
    //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor+1)*roundingFactor+minY;
    //   addSecondaryLocation=true;
    // }
    // if(Functions::abs(y-G.nodes[i]->location.y)<epsilon){
    //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor-1)*roundingFactor+minY;
    //   addSecondaryLocation=true;
    // }
    // if(addSecondaryLocation){
      // std::cout<<"adding secondary location"<<'\n';
      for(long j=0;j<xSec.size();j++){
        for(long k=0;k<ySec.size();k++){
          matrix[Point2d(xSec[j],ySec[k])].push_back(i);
        }
      }

    // }

  }
  std::vector<double> lengths;
  // double maxx=-INFINITY;
  // double maxy=-INFINITY;
  // for(auto it:matrix){
  //   if(it.first.x>maxx){
  //     maxx=it.first.x;
  //   }
  //   if(it.first.y>maxy){
  //     maxy=it.first.y;
  //   }
  // }
  SparseMatrix finalMatrix;
  for(auto it:matrix){
    // Grafo boundary;
    // boundary.bidirectional=true;
    // Nodo* a=boundary.addNode(Point2d(it.first.x+displacementX,it.first.y+displacementY));
    // Nodo* b=boundary.addNode(Point2d(it.first.x+displacementX+roundingFactor,it.first.y+displacementY));
    // Nodo* c=boundary.addNode(Point2d(it.first.x+displacementX+roundingFactor,it.first.y+displacementY+roundingFactor));
    // Nodo* d=boundary.addNode(Point2d(it.first.x+displacementX,it.first.y+displacementY+roundingFactor));
    // boundary.addLink(a->id,b->id,roundingFactor);
    // boundary.addLink(b->id,c->id,roundingFactor);
    // boundary.addLink(c->id,d->id,roundingFactor);
    // boundary.addLink(d->id,a->id,roundingFactor);
    //
    //
    Grafo sg;
    // GeometryGraph::getSubgraphWithinABoundary(G,&boundary,&sg);
    Grafo::inducedSubgraph(&G,&sg,it.second);
    double l=0;
    for(long i=0;i<sg.links.size();i++){
      l+=sg.links[i]->weight;
    }

    double x=it.first.x;
    double y=it.first.y;
    // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
    //   std::cout<<"textingB "<<x<<","<<y<<" "<<it.first.x<<","<<it.first.y<<" "<<l<<" "<<sg.nodes.size()<<" "<<sg.links.size()<<'\n';
    // }
    // double x=it.first.x;
    // double y=it.first.y;
    // if(it.first.x<maxx&&it.first.y<maxy&&l>0){
    if(l>0){
      // Nodo* node=pixelGraph->addNode(Point2d(x,y));
      // node->mass=l;
      finalMatrix.setValue(x,y,l);
      num++;

    }
    // }

    // lengths.push_back(l);
    // av+=l;
    // num++;
  }

  std::vector<double> result;
  std::vector<double> sizes;
  std::vector<double> numberBoxes;
  std::vector<double> avLengthInside;

  SparseMatrix summaryLengths;
  SparseMatrix summaryArea;
  // result.push_back((double)(num)/(double)(withinBoundary.nodes.size()));
  // sizes.push_back(lengthSidePixel);
long j=0;
double size=lengthSidePixel;
bool first=true;
  // for(long j=0;j<numberLevels;j+=1){
  while(size<=maxSize){
    if(size>=minSize){
      std::cout<<"Calculating size "<<size<<'\n';
    num=0;
    double totalNumForAverage=0;
    double avLengths=0;
    for(long i=0;i<withinBoundary.nodes.size();i++){
      double x=withinBoundary.nodes[i]->location.x;
      double y=withinBoundary.nodes[i]->location.y;
      double totalL=0;
      double boundaryNum=0;
      if(quick){
      if(first){
        for(long k=-j;k<=j;k++){
          for(long l=-j;l<=j;l++){
            boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
            totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
          }
        }

      }else{
        boundaryNum+=summaryArea.getValue(x,y);
        totalL+=summaryLengths.getValue(x,y);

        // for(long k=-j;k<=j;k++){
        long k=-j;
          for(long l=-j;l<=j;l++){
            boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
            totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
          }
        // }
        // for(long k=-j;k<=j;k++){
        k=j;
          for(long l=-j;l<=j;l++){
            boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
            totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
          }
        // }
        long l=-j;
        for(long k=-j+1;k<j;k++){
        // k=-j;
          // for(long l=-j;l<=j;l++){
            boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
            totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
          // }
        }
        l=j;
        for(long k=-j+1;k<j;k++){
        // k=-j;
          // for(long l=-j;l<=j;l++){
            boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
            totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
          // }
        }
      }

        summaryArea.setValue(x,y,boundaryNum);
        summaryLengths.setValue(x,y,totalL);
      }else{
        for(long k=-j;k<=j;k++){
        // long k=-j;
          for(long l=-j;l<=j;l++){
            boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
            totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
          }
        }
      }

      double proportionIn=boundaryNum/(pow((double)(j)*2.0+1,2));
        if(totalL>0&&proportionIn>.5){
           num++;
           totalNumForAverage+=proportionIn;
           avLengths+=totalL;
        }
        // avLengths+=totalL/(pow((double)(j)*2.0+1,2))*boundaryNum;
    }
    result.push_back((double)(num)/(double)(withinBoundary.nodes.size()));
    // avLengthInside.push_back((double)(avLengths)/(double)(withinBoundary.nodes.size()));
    avLengthInside.push_back((double)(avLengths)/(double)(totalNumForAverage));
    sizes.push_back(lengthSidePixel+lengthSidePixel*(double)(j)*2.0);
    numberBoxes.push_back((double)(withinBoundary.nodes.size()));
  }
  if(size>=minSize){
    first=false;
  }
    j++;
    size=lengthSidePixel+lengthSidePixel*(double)(j)*2.0;

  }

  // av/=num;

  // return av;
  // Rcpp::XPtr<Grafo> p(pixelGraph,true);
  // return p;
  // Distribution dis=Distribution::createDistribution(lengths);

  // return (Distribution::getMode(&dis));




    List list(4);
    NumericVector numberBoxes_=wrap(numberBoxes);
    NumericVector sizes_=wrap(sizes);
    NumericVector result_=wrap(result);
    NumericVector avL_=wrap(avLengthInside);



  //    for(size_t i=0;i<numberObjectsDataFrame;i++){
  //        list[i]=(wrap(std::get<i>(result_)));
  //    }
  list[0]=sizes_;
  list[1]=numberBoxes_;
    list[2]=result_;
    list[3]=avL_;

    // list[2]=weight;

    CharacterVector namevec;
    namevec.push_back("sizesBox");
    namevec.push_back("numberBoxes");
    namevec.push_back("percentageOccupied");
    namevec.push_back("averageLengthInBox");

    // namevec.push_back("weight");


    list.attr("names") = namevec;
    DataFrame df(list);
    return df;
}







// [[Rcpp::export]]
DataFrame calculateSandBox_MonteCarloFractalDimension (XPtr<Grafo> grafo,XPtr<Grafo> boundary,double lengthSidePixel,double xCentroid,double yCentroid,double maxDistance){
  bool quick=true;
  double displacementX=0;
  double displacementY=0;
  // double minSide=INFINITY;
  // for(long i=0;i<sideBoxes.size();i++){
  //   if(sideBoxes[i]<minSide){
  //     minSide=sideBoxes[i];
  //   }
  // }
  // double lengthSidePixel=minSide/4.0;
  double roundingFactor=lengthSidePixel;
  Grafo* pixelGraph=new Grafo();
  Grafo G;
  G.copyGraph(grafo);
  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<G.nodes.size();i++){
    if(G.nodes[i]->location.x>maxX){
      maxX=G.nodes[i]->location.x;
    }
    if(G.nodes[i]->location.y>maxY){
      maxY=G.nodes[i]->location.y;
    }
    if(G.nodes[i]->location.x<minX){
      minX=G.nodes[i]->location.x;
    }
    if(G.nodes[i]->location.y<minY){
      minY=G.nodes[i]->location.y;
    }
  }


  Grafo boundaryGrid;
  SparseMatrix boundaryMatrix;
  for(double x=minX;x<=maxX;x+=lengthSidePixel){
    for(double y=minY;y<=maxY;y+=lengthSidePixel){
      boundaryGrid.addNode(Point2d(x,y));
    }

  }
  Grafo withinBoundary;
  GeometryGraph::getSubgraphWithinABoundary(&boundaryGrid,boundary,&withinBoundary);

for(long i=0;i<withinBoundary.nodes.size();i++){
  double x=withinBoundary.nodes[i]->location.x;
  double y=withinBoundary.nodes[i]->location.y;
  boundaryMatrix.setValue(x,y,lengthSidePixel*lengthSidePixel);
}


  // double centeringGridX=(std::floor((minX)/roundingFactor)*roundingFactor-minX);
  // double centeringGridY=(std::floor((minY)/roundingFactor)*roundingFactor-minY);
  // double x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
  // double y=std::floor((minY-displacementY)/roundingFactor)*roundingFactor+centeringGridY;
  double x=minX;
  double y=minY;
  Grafo squareSubdivision;
  squareSubdivision.bidirectional=true;
  while (x<=maxX){

    Nodo* a=squareSubdivision.addNode(Point2d(x+displacementX,minY-10+displacementY));
    Nodo* b=squareSubdivision.addNode(Point2d(x+displacementX,maxY+10+displacementY));
    squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x+roundingFactor/100,y-10));
    // b=squareSubdivision.addNode(Point2d(x+roundingFactor/100,maxY+10));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-roundingFactor/100,y-10));
    // b=squareSubdivision.addNode(Point2d(x-roundingFactor/100,maxY+10));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    x+=roundingFactor;
  }
  // x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
  // x=minX;
  while (y<=maxY){

    Nodo* a=squareSubdivision.addNode(Point2d(minX-10+displacementX,y+displacementY));
    Nodo* b=squareSubdivision.addNode(Point2d(maxX+10+displacementX,y+displacementY));
    squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-10,y+roundingFactor/100));
    // b=squareSubdivision.addNode(Point2d(maxX+10,y+roundingFactor/100));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    // a=squareSubdivision.addNode(Point2d(x-10,y-roundingFactor/100));
    // b=squareSubdivision.addNode(Point2d(maxX+10,y-roundingFactor/100));
    // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
    y+=roundingFactor;
  }
  Grafo::intersectAGraphWithABoundary(&G,&squareSubdivision);
  std::unordered_map<Point2d, std::vector<long> > matrix;
  double av=0;
  double num=0;
  for(long i=0;i<G.nodes.size();i++){
    double epsilon=Functions::min(1.0/100000.0,roundingFactor/100.0);
    double x=std::floor((G.nodes[i]->location.x-minX-displacementX)/roundingFactor)*roundingFactor+minX;
    double y=std::floor((G.nodes[i]->location.y-minY-displacementY)/roundingFactor)*roundingFactor+minY;
    double x1=std::floor((G.nodes[i]->location.x-minX-epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
    double y1=std::floor((G.nodes[i]->location.y-minY-epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
    double x2=std::floor((G.nodes[i]->location.x-minX+epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
    double y2=std::floor((G.nodes[i]->location.y-minY+epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
    std::vector<double> xSec;
    std::vector<double> ySec;
    xSec.push_back(x);
    ySec.push_back(y);
    // matrix[Point2d(x,y)].push_back(i);

    // bool addSecondaryLocation=false;

    // if(x+roundingFactor/2.0>786092&&x+roundingFactor/2.0<786093&&y+roundingFactor/2.0>6002344.34&&y+roundingFactor/2.0<6002352){
    // // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
    //   std::cout<<"texting "<<x<<","<<y<<" "<<G.nodes[i]->location.x<<","<<G.nodes[i]->location.y<<" dif: "<<(x-G.nodes[i]->location.x)<<","<<(y-G.nodes[i]->location.y)<<'\n';
    // }
    if(x!=x1){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      xSec.push_back(x1);
      // addSecondaryLocation=true;
    }
    if(x!=x2){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      xSec.push_back(x2);
      // addSecondaryLocation=true;
    }
    if(y!=y1){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      ySec.push_back(y1);
      // addSecondaryLocation=true;
    }
    if(y!=y2){
      // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
      ySec.push_back(y2);
      // addSecondaryLocation=true;
    }
    // if(Functions::abs(x+roundingFactor-G.nodes[i]->location.x)<epsilon){
    //   x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor+1)*roundingFactor+minX;
    //   addSecondaryLocation=true;
    // }
    // if(Functions::abs(y+roundingFactor-G.nodes[i]->location.y)<epsilon){
    //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor+1)*roundingFactor+minY;
    //   addSecondaryLocation=true;
    // }
    // if(Functions::abs(y-G.nodes[i]->location.y)<epsilon){
    //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor-1)*roundingFactor+minY;
    //   addSecondaryLocation=true;
    // }
    // if(addSecondaryLocation){
      // std::cout<<"adding secondary location"<<'\n';
      for(long j=0;j<xSec.size();j++){
        for(long k=0;k<ySec.size();k++){
          matrix[Point2d(xSec[j],ySec[k])].push_back(i);
        }
      }

    // }

  }
  // std::vector<double> lengths;
  // double maxx=-INFINITY;
  // double maxy=-INFINITY;
  // for(auto it:matrix){
  //   if(it.first.x>maxx){
  //     maxx=it.first.x;
  //   }
  //   if(it.first.y>maxy){
  //     maxy=it.first.y;
  //   }
  // }
  SparseMatrix finalMatrix;
  Point2d centroid;
  double totalLength=0;
  for(auto it:matrix){
    // Grafo boundary;
    // boundary.bidirectional=true;
    // Nodo* a=boundary.addNode(Point2d(it.first.x+displacementX,it.first.y+displacementY));
    // Nodo* b=boundary.addNode(Point2d(it.first.x+displacementX+roundingFactor,it.first.y+displacementY));
    // Nodo* c=boundary.addNode(Point2d(it.first.x+displacementX+roundingFactor,it.first.y+displacementY+roundingFactor));
    // Nodo* d=boundary.addNode(Point2d(it.first.x+displacementX,it.first.y+displacementY+roundingFactor));
    // boundary.addLink(a->id,b->id,roundingFactor);
    // boundary.addLink(b->id,c->id,roundingFactor);
    // boundary.addLink(c->id,d->id,roundingFactor);
    // boundary.addLink(d->id,a->id,roundingFactor);
    //
    //
    Grafo sg;
    // GeometryGraph::getSubgraphWithinABoundary(G,&boundary,&sg);
    Grafo::inducedSubgraph(&G,&sg,it.second);
    double l=0;
    for(long i=0;i<sg.links.size();i++){
      l+=sg.links[i]->weight;
    }

    double x=it.first.x;
    double y=it.first.y;
    // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
    //   std::cout<<"textingB "<<x<<","<<y<<" "<<it.first.x<<","<<it.first.y<<" "<<l<<" "<<sg.nodes.size()<<" "<<sg.links.size()<<'\n';
    // }
    // double x=it.first.x;
    // double y=it.first.y;
    // if(it.first.x<maxx&&it.first.y<maxy&&l>0){
    if(l>0){
      // Nodo* node=pixelGraph->addNode(Point2d(x,y));
      // node->mass=l;
      finalMatrix.setValue(x,y,l);
      num++;
      centroid.x+=x*pow(l,5.0);
      centroid.y+=y*pow(l,5.0);
      totalLength+=pow(l,5.0);
    }
    // }

    // lengths.push_back(l);
    // av+=l;
    // num++;
  }
centroid.x/=totalLength;
centroid.y/=totalLength;

centroid.x=std::floor((centroid.x-minX-displacementX)/roundingFactor)*roundingFactor+minX;
centroid.y=std::floor((centroid.y-minY-displacementY)/roundingFactor)*roundingFactor+minY;

std::cout<<"centroidX "<<centroid.x<<" centroidY "<<centroid.y<<'\n';

centroid.x=xCentroid;
centroid.y=yCentroid;





std::vector<double> distancesG;
std::vector<double> distancesB;
std::vector<double> lengths;
std::vector<double> A2;



for(auto it:finalMatrix.cells){
  double distance=Functions::getDistance(it.first,centroid);
  distancesG.push_back(distance);
  lengths.push_back(it.second.value);
}
for(auto it:boundaryMatrix.cells){
  double distance=Functions::getDistance(it.first,centroid);
  distancesB.push_back(distance);
  A2.push_back(it.second.value);
}

long indexA=0;
long indexB=0;

double Lt=0;
double A2t=0;
std::vector<double> distances;
std::vector<double> Ls;
std::vector<double> correctionFactorAreaWithin;
// std::vector<double> A2s;

std::vector<long> orderA=Functions::getIndexesOfOrderedValues(distancesG,true);
std::vector<long> orderB=Functions::getIndexesOfOrderedValues(distancesB,true);
std::vector<double> orderedDistancesA=Functions::orderVectorUsingAnotherVectorWithPositions(distancesG,orderA);
std::vector<double> orderedLengths=Functions::orderVectorUsingAnotherVectorWithPositions(lengths,orderA);
std::vector<double> orderedDistancesB=Functions::orderVectorUsingAnotherVectorWithPositions(distancesB,orderB);
std::vector<double> orderedA2=Functions::orderVectorUsingAnotherVectorWithPositions(A2,orderB);


double distance=orderedDistancesA[indexA];
// while(indexB<orderedDistancesB.size()&&distance>=orderedDistancesB[indexB]){
//   A2t+=orderedA2[indexB];
//   indexB++;
// }
while(indexA<orderedDistancesA.size()&&(distance<maxDistance||maxDistance==0)){

  // A2t+=orderedA2[indexB];
  double distanceNew=orderedDistancesA[indexA];


  if(distanceNew>distance){

    distances.push_back(distance);
    distance=distanceNew;
    while(indexB<orderedDistancesB.size()&&distance>=orderedDistancesB[indexB]){

      A2t+=orderedA2[indexB];
      indexB++;
    }
    Ls.push_back(Lt);
    correctionFactorAreaWithin.push_back(M_PI*distance*distance/A2t);
  }

    Lt+=orderedLengths[indexA];

// }else{

// }
  indexA++;

  // A2s.push_back(A2t);
}











//
//   std::vector<double> result;
//   std::vector<double> sizes;
//   std::vector<double> numberBoxes;
//   std::vector<double> avLengthInside;
//
//   SparseMatrix summaryLengths;
//   SparseMatrix summaryArea;
//   // result.push_back((double)(num)/(double)(withinBoundary.nodes.size()));
//   // sizes.push_back(lengthSidePixel);
// long j=0;
// double size=lengthSidePixel;
// bool first=true;
//   // for(long j=0;j<numberLevels;j+=1){
//   while(size<=maxSize){
//     if(size>=minSize){
//       std::cout<<"Calculating size "<<size<<'\n';
//     num=0;
//
//     double avLengths=0;
//     for(long i=0;i<withinBoundary.nodes.size();i++){
//       double x=withinBoundary.nodes[i]->location.x;
//       double y=withinBoundary.nodes[i]->location.y;
//       double totalL=0;
//       double boundaryNum=0;
//       if(quick){
//       if(first){
//         for(long k=-j;k<=j;k++){
//           for(long l=-j;l<=j;l++){
//             boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//             totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//           }
//         }
//
//       }else{
//         boundaryNum+=summaryArea.getValue(x,y);
//         totalL+=summaryLengths.getValue(x,y);
//
//         // for(long k=-j;k<=j;k++){
//         long k=-j;
//           for(long l=-j;l<=j;l++){
//             boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//             totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//           }
//         // }
//         // for(long k=-j;k<=j;k++){
//         k=j;
//           for(long l=-j;l<=j;l++){
//             boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//             totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//           }
//         // }
//         long l=-j;
//         for(long k=-j+1;k<j;k++){
//         // k=-j;
//           // for(long l=-j;l<=j;l++){
//             boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//             totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//           // }
//         }
//         l=j;
//         for(long k=-j+1;k<j;k++){
//         // k=-j;
//           // for(long l=-j;l<=j;l++){
//             boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//             totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//           // }
//         }
//       }
//
//         summaryArea.setValue(x,y,boundaryNum);
//         summaryLengths.setValue(x,y,totalL);
//       }else{
//         for(long k=-j;k<=j;k++){
//         // long k=-j;
//           for(long l=-j;l<=j;l++){
//             boundaryNum+=boundaryMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//             totalL+=finalMatrix.getValue(x+k*lengthSidePixel,y+l*lengthSidePixel);
//           }
//         }
//       }
//         if(totalL>0){
//            num++;
//            avLengths+=totalL/(pow((double)(j)*2.0+1,2))*boundaryNum;
//         }
//         // avLengths+=totalL/(pow((double)(j)*2.0+1,2))*boundaryNum;
//     }
//     result.push_back((double)(num)/(double)(withinBoundary.nodes.size()));
//     // avLengthInside.push_back((double)(avLengths)/(double)(withinBoundary.nodes.size()));
//     avLengthInside.push_back((double)(avLengths)/(double)(num));
//     sizes.push_back(lengthSidePixel+lengthSidePixel*(double)(j)*2.0);
//     numberBoxes.push_back((double)(withinBoundary.nodes.size()));
//   }
//   if(size>=minSize){
//     first=false;
//   }
//     j++;
//     size=lengthSidePixel+lengthSidePixel*(double)(j)*2.0;
//
//   }
//
//   // av/=num;
//
//   // return av;
//   // Rcpp::XPtr<Grafo> p(pixelGraph,true);
//   // return p;
//   // Distribution dis=Distribution::createDistribution(lengths);
//
//   // return (Distribution::getMode(&dis));




    List list(3);
    NumericVector lengths_=wrap(Ls);
    NumericVector distances_=wrap(distances);
    NumericVector correctionFactorAreaWithin_=wrap(correctionFactorAreaWithin);
    // NumericVector result_=wrap(result);
    // NumericVector avL_=wrap(avLengthInside);



  //    for(size_t i=0;i<numberObjectsDataFrame;i++){
  //        list[i]=(wrap(std::get<i>(result_)));
  //    }
  list[0]=distances_;
  list[1]=lengths_;
    list[2]=correctionFactorAreaWithin_;
    // list[3]=avL_;

    // list[2]=weight;

    CharacterVector namevec;
    namevec.push_back("distances");
    namevec.push_back("lengthWithin");
    namevec.push_back("correctionFactorAreaWithin");
    // namevec.push_back("averageLengthInBox");

    // namevec.push_back("weight");


    list.attr("names") = namevec;
    DataFrame df(list);
    return df;
}








































// [[Rcpp::export]]
DataFrame  calculateAlphaShape(NumericVector ids,NumericVector xs,NumericVector ys,double alpha){
  std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
//    std::vector<std::vector<double> > result_;
  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > result_;
  result_=Geometry::calculateAlphaShape(ids_,xs_,ys_,alpha);

  long numberObjectsDataFrame=3;

  List list(numberObjectsDataFrame);
  NumericVector idA=wrap(std::get<0>(result_));
  NumericVector idB=wrap(std::get<1>(result_));
  NumericVector weight=wrap(std::get<2>(result_));
//    for(size_t i=0;i<numberObjectsDataFrame;i++){
//        list[i]=(wrap(std::get<i>(result_)));
//    }
  list[0]=idA;
  list[1]=idB;
  list[2]=weight;

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


// [[Rcpp::export]]
XPtr< Grafo > createSuperGraphFromClustersFromColorsLinks(XPtr<DualExtendedGraph> deg,NumericVector idLinksClusters,bool useOriginalDistances){
  Grafo* sG=new Grafo();
  std::vector<long> idClusters_=as<std::vector<long> >(idLinksClusters);
  Grafo::createSuperGraphFromClustersFromColorsLinks(deg->getPrimalGraph(),sG,idClusters_,useOriginalDistances);

  Rcpp::XPtr< Grafo > p(sG,true) ;
  return (p);

}

// [[Rcpp::export]]
XPtr< Grafo > createSuperGraphFromClustersFromColorsNodes(XPtr<DualExtendedGraph> deg,NumericVector idNodesClusters,bool useOriginalDistances){
  Grafo* sG=new Grafo();
  std::vector<long> idClusters_=as<std::vector<long> >(idNodesClusters);
  Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),sG,idClusters_,useOriginalDistances);

  Rcpp::XPtr< Grafo > p(sG,true) ;
  return (p);

}


// [[Rcpp::export]]
DataFrame metricPercolation(XPtr< DualExtendedGraph >  deg,double threshold,long minClusterSize){


  std::vector<long> colors;
  std::vector<double> sizes;
//    long maxColor;
  // std::cout<<"is primal structural? "<<DualExtendedGraph::isPrimalStructural(deg)<<'\n';
  DualExtendedGraph::metricPercolation(deg,threshold,colors,sizes);
  out("Finished getting colors");
  std::vector<double> idA,idB,weights,colors_,sizes_;

  idA.resize(deg->getPrimalGraph()->links.size());
  idB.resize(deg->getPrimalGraph()->links.size());
  weights.resize(deg->getPrimalGraph()->links.size());
  colors_.resize(deg->getPrimalGraph()->links.size());
  sizes_.resize(deg->getPrimalGraph()->links.size());


  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){

    idA[i]=deg->getPrimalGraph()->links[i]->A()->id;
    idB[i]=deg->getPrimalGraph()->links[i]->B()->id;
    weights[i]=deg->getPrimalGraph()->links[i]->weight;
            // colors_[i]=colors[deg->getStructuralGraph()->links[i]->a->id];
            // if(colors[deg->getStructuralGraph()->links[i]->a->id]>=0){
            //   sizes_[i]=sizes[colors[deg->getStructuralGraph()->links[i]->a->id]];
            // }else{
            //   sizes_[i]=0;
            // }
    colors_[i]=colors[i];
    if(colors[i]>=0){
      sizes_[i]=sizes[colors[i]];
    }else{
      sizes_[i]=0;
    }




  }

  std::vector<std::vector<double> > result;
  result.resize(5);
  result[0]=idA;
  result[1]=idB;
  result[2]=weights;
  result[3]=colors_;
  result[4]=sizes_;





  long numberObjectsDataFrame=5;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  namevec.push_back("idCluster");
  namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}




// [[Rcpp::export]]
DataFrame metricPercolation_sizeUsingMassesNodes(XPtr< DualExtendedGraph >  deg,double threshold,long minClusterSize){


  std::vector<long> colors;
  std::vector<double> sizes;
//    long maxColor;
  // std::cout<<"is primal structural? "<<DualExtendedGraph::isPrimalStructural(deg)<<'\n';
  DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,threshold,colors,sizes);
  out("Finished getting colors");
  std::vector<double> idA,idB,weights,colors_,sizes_;

  idA.resize(deg->getPrimalGraph()->links.size());
  idB.resize(deg->getPrimalGraph()->links.size());
  weights.resize(deg->getPrimalGraph()->links.size());
  colors_.resize(deg->getPrimalGraph()->links.size());
  sizes_.resize(deg->getPrimalGraph()->links.size());


  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){

    idA[i]=deg->getPrimalGraph()->links[i]->A()->id;
    idB[i]=deg->getPrimalGraph()->links[i]->B()->id;
    weights[i]=deg->getPrimalGraph()->links[i]->weight;
            // colors_[i]=colors[deg->getStructuralGraph()->links[i]->a->id];
            // if(colors[deg->getStructuralGraph()->links[i]->a->id]>=0){
            //   sizes_[i]=sizes[colors[deg->getStructuralGraph()->links[i]->a->id]];
            // }else{
            //   sizes_[i]=0;
            // }
    colors_[i]=colors[i];
    if(colors[i]>=0){
      sizes_[i]=sizes[colors[i]];
    }else{
      sizes_[i]=0;
    }




  }

  std::vector<std::vector<double> > result;
  result.resize(5);
  result[0]=idA;
  result[1]=idB;
  result[2]=weights;
  result[3]=colors_;
  result[4]=sizes_;





  long numberObjectsDataFrame=5;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  namevec.push_back("idCluster");
  namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



// [[Rcpp::export]]
void setWeightsDual_HuMoments(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistanceDual_HuMoments(deg);
}

// [[Rcpp::export]]
void setWeightsDual_difArea(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistanceDual_difArea(deg);
}

// [[Rcpp::export]]
void setWeightsDual_avArea(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistanceDual_avArea(deg);
}

// [[Rcpp::export]]
void setWeightsDual_avNeighborhoodArea(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistanceDual_avNeighborhoodArea(deg);
}

// [[Rcpp::export]]
void setWeightsDual_difNeighborhoodArea(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistanceDual_difNeighborhoodArea(deg);
}

// [[Rcpp::export]]
void setWeightsDual_minArea(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistanceDual_minArea(deg);
}


// [[Rcpp::export]]
void setDistancePrimal_minLengthNeighbours(XPtr< DualExtendedGraph >  deg){
  DualExtendedGraph::setDistancePrimal_minLengthNeighbours(deg);
}

// [[Rcpp::export]]
void averageWeightsPrimalWithNeighbours(XPtr< DualExtendedGraph >  deg){
  // DualExtendedGraph::setDistancePrimal_minLengthNeighbours(deg);
  std::vector<double> weights;
  weights.resize(deg->getPrimalGraph()->links.size(),0);
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    Nodo* a=deg->getPrimalGraph()->links[i]->A();
    Nodo* b=deg->getPrimalGraph()->links[i]->B();
    double weight=deg->getPrimalGraph()->links[i]->weight;
    double counter=1.0;
    for(long j=0;j<a->links.size();j++){
      if(a->links[j]->id!=deg->getPrimalGraph()->links[i]->id){
        counter++;
        weight+=a->links[j]->weight;
      }

    }
    for(long j=0;j<b->links.size();j++){
      if(b->links[j]->id!=deg->getPrimalGraph()->links[i]->id){
        counter++;
        weight+=b->links[j]->weight;
      }

    }
    weights[i]=weight/counter;
  }
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    deg->getPrimalGraph()->links[i]->weight=weights[i];
  }

}

// [[Rcpp::export]]
void averageWeightsPrimalWithNeighboursWeighted(XPtr< DualExtendedGraph >  deg){

  // DualExtendedGraph::setDistancePrimal_minLengthNeighbours(deg);
  std::vector<double> weights;
  weights.resize(deg->getPrimalGraph()->links.size(),0);
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    Nodo* a=deg->getPrimalGraph()->links[i]->A();
    Nodo* b=deg->getPrimalGraph()->links[i]->B();
    double distance=Functions::getDistance(a->location,b->location);
    double weight=deg->getPrimalGraph()->links[i]->weight*distance;
    double counter=distance;
    for(long j=0;j<a->links.size();j++){
      if(a->links[j]->id!=deg->getPrimalGraph()->links[i]->id){
        distance=Functions::getDistance(a->links[j]->A()->location,a->links[j]->B()->location);
        counter+=distance;
        weight+=a->links[j]->weight*distance;
      }

    }
    for(long j=0;j<b->links.size();j++){
      if(b->links[j]->id!=deg->getPrimalGraph()->links[i]->id){
        distance=Functions::getDistance(b->links[j]->A()->location,b->links[j]->B()->location);
        counter+=distance;
        weight+=b->links[j]->weight*distance;
      }

    }
    weights[i]=weight/counter;
  }
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    deg->getPrimalGraph()->links[i]->weight=weights[i];
  }

}


// [[Rcpp::export]]
DataFrame dualPercolation(XPtr< DualExtendedGraph >  deg,double threshold,long minClusterSize){


  std::vector<long> colors;
  std::vector<double> sizes;
//    long maxColor;
  // std::cout<<"is primal structural? "<<DualExtendedGraph::isPrimalStructural(deg)<<'\n';
  DualExtendedGraph::dualPercolation(deg,threshold,colors,sizes);
  out("Finished getting colors");
  std::vector<double> idA,idB,weights,colors_,sizes_;

  idA.resize(deg->getPrimalGraph()->links.size());
  idB.resize(deg->getPrimalGraph()->links.size());
  weights.resize(deg->getPrimalGraph()->links.size());
  colors_.resize(deg->getPrimalGraph()->links.size());
  sizes_.resize(deg->getPrimalGraph()->links.size());


  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){

    idA[i]=deg->getPrimalGraph()->links[i]->A()->id;
    idB[i]=deg->getPrimalGraph()->links[i]->B()->id;
    weights[i]=deg->getPrimalGraph()->links[i]->weight;
            // colors_[i]=colors[deg->getStructuralGraph()->links[i]->a->id];
            // if(colors[deg->getStructuralGraph()->links[i]->a->id]>=0){
            //   sizes_[i]=sizes[colors[deg->getStructuralGraph()->links[i]->a->id]];
            // }else{
            //   sizes_[i]=0;
            // }
    colors_[i]=colors[i];
    if(colors[i]>=0){
      sizes_[i]=sizes[colors[i]];
    }else{
      sizes_[i]=0;
    }




  }

  std::vector<std::vector<double> > result;
  result.resize(5);
  result[0]=idA;
  result[1]=idB;
  result[2]=weights;
  result[3]=colors_;
  result[4]=sizes_;





  long numberObjectsDataFrame=5;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  namevec.push_back("idCluster");
  namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

// [[Rcpp::export]]
double getEntropyFromAngularPercolation(XPtr< DualExtendedGraph >  deg,double angle){
  double entropy=DualExtendedGraph::getEntropyFromAngularPercolation(deg,angle);
  return entropy;
}

// [[Rcpp::export]]
DataFrame angularPercolation(XPtr< DualExtendedGraph >  deg,double threshold,long minClusterSize){


  std::vector<long> colors;
  std::vector<double> sizes;
//    long maxColor;
  DualExtendedGraph::angularPercolation(deg,threshold,colors,sizes);
  out("Finished getting colors");
  std::vector<double> idA,idB,weights,colors_,sizes_;

  std::vector<long> colorsNodesOfLineGraph;
  Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(),colors,colorsNodesOfLineGraph);

  idA.resize(deg->getPrimalGraph()->links.size());
  idB.resize(deg->getPrimalGraph()->links.size());
  weights.resize(deg->getPrimalGraph()->links.size());
  colors_.resize(deg->getPrimalGraph()->links.size());
  sizes_.resize(deg->getPrimalGraph()->links.size());


  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){

    idA[i]=deg->getPrimalGraph()->links[i]->A()->id;
    idB[i]=deg->getPrimalGraph()->links[i]->B()->id;
    weights[i]=deg->getPrimalGraph()->links[i]->weight;
            // colors_[i]=colors[deg->getStructuralGraph()->links[i]->a->id];
            // if(colors[deg->getStructuralGraph()->links[i]->a->id]>=0){
            //   sizes_[i]=sizes[colors[deg->getStructuralGraph()->links[i]->a->id]];
            // }else{
            //   sizes_[i]=0;
            // }
    colors_[i]=colorsNodesOfLineGraph[i];
    if(colorsNodesOfLineGraph[i]>=0){
      sizes_[i]=sizes[colorsNodesOfLineGraph[i]];
    }else{
      sizes_[i]=0;
    }




  }

  std::vector<std::vector<double> > result;
  result.resize(5);
  result[0]=idA;
  result[1]=idB;
  result[2]=weights;
  result[3]=colors_;
  result[4]=sizes_;





  long numberObjectsDataFrame=5;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  namevec.push_back("idCluster");
  namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


// [[Rcpp::export]]
NumericVector getSetOfTheoreticalCities(double expectedPop,double a,double b,double c){

 // std::vector<double> as;
 //  std::vector<double> bs;
 //  std::vector<double> cs;
 //  std::vector<double> maxSs;
 //  std::vector<double> Ns;
  NumericVector cities;

  // for(double a=minA;a<=maxA;a+=(maxA-minA)/definition){

    // for(double b=minB;b<=maxB;b+=(maxB-minB)/definition){
      // for(double c=minC;c<=maxC;c+=(maxC-minC)/definition){
        std::cout<<"a "<<a<<" b "<<b<<" c "<<c<<'\n';
        // for(long repetitions=0;repetitions<numRepetitions;repetitions++){
          double maxS=0;
          double pop=0;
          double N=0;

          while(pop<expectedPop){
            N++;
            double city=Functions::sampleDagumDistribution(a,b,c);
            cities.push_back(city);
            pop=pop+city;
            if(city>maxS){
              maxS=city;
            }
          }
          // as.push_back(a);
          // bs.push_back(b);
          // cs.push_back(c);
          // maxSs.push_back(maxS);
          // Ns.push_back(N);
        // }
      // }
    // }
  // }

  // long numberObjec


// tsDataFrame=5;

  // List list(5);
  // list[0]=as;
  // list[1]=bs;
  // list[2]=cs;
  // list[3]=maxSs;
  // list[4]=Ns;
  // // for(long i=0;i<numberObjectsDataFrame;i++){
  // //   list[i]=(wrap(result[i]));
  // // }

  // CharacterVector namevec;
  // namevec.push_back("a");
  // namevec.push_back("b");
  // namevec.push_back("c");
  // namevec.push_back("maxS");
  // namevec.push_back("N");
  // // namevec.push_back("weight");
  // // namevec.push_back("idCluster");
  // // namevec.push_back("size");


  // list.attr("names") = namevec;
  // DataFrame df(list);
  // return df;
          return cities;
}


// [[Rcpp::export]]
DataFrame getNandMaxSSetOfTheoreticalCities(double expectedPop,double a,double b,double c,long numRepetitions){

 std::vector<double> as;
  std::vector<double> bs;
  std::vector<double> cs;
  std::vector<double> maxSs;
  std::vector<double> Ns;


  // for(double a=minA;a<=maxA;a+=(maxA-minA)/definition){

    // for(double b=minB;b<=maxB;b+=(maxB-minB)/definition){
      // for(double c=minC;c<=maxC;c+=(maxC-minC)/definition){
        std::cout<<"a "<<a<<" b "<<b<<" c "<<c<<'\n';
        for(long repetitions=0;repetitions<numRepetitions;repetitions++){
          double maxS=0;
          double pop=0;
          double N=0;

          while(pop<expectedPop){
            N++;
            double city=Functions::sampleDagumDistribution(a,b,c);
            pop=pop+city;
            if(city>maxS){
              maxS=city;
            }
          }
          as.push_back(a);
          bs.push_back(b);
          cs.push_back(c);
          maxSs.push_back(maxS);
          Ns.push_back(N);
        }
      // }
    // }
  // }

  // long numberObjec


// tsDataFrame=5;

  List list(5);
  list[0]=as;
  list[1]=bs;
  list[2]=cs;
  list[3]=maxSs;
  list[4]=Ns;
  // for(long i=0;i<numberObjectsDataFrame;i++){
  //   list[i]=(wrap(result[i]));
  // }

  CharacterVector namevec;
  namevec.push_back("a");
  namevec.push_back("b");
  namevec.push_back("c");
  namevec.push_back("maxS");
  namevec.push_back("N");
  // namevec.push_back("weight");
  // namevec.push_back("idCluster");
  // namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

// [[Rcpp::export]]
DataFrame getSpectrumNandMaxSSetOfTheoreticalCities(double expectedPop,double minA,double maxA,double minB,double maxB,double minC,double maxC,double definition,double numRepetitions){
  std::vector<double> as;
  std::vector<double> bs;
  std::vector<double> cs;
  std::vector<double> maxSs;
  std::vector<double> Ns;


  for(double a=minA;a<=maxA;a+=(maxA-minA)/definition){

    for(double b=minB;b<=maxB;b+=(maxB-minB)/definition){
      for(double c=minC;c<=maxC;c+=(maxC-minC)/definition){
        std::cout<<"a "<<a<<" b "<<b<<" c "<<c<<'\n';
        for(long repetitions=0;repetitions<numRepetitions;repetitions++){
          double maxS=0;
          double pop=0;
          double N=0;

          while(pop<expectedPop){
            N++;
            double city=Functions::sampleDagumDistribution(a,b,c);
            pop=pop+city;
            if(city>maxS){
              maxS=city;
            }
          }
          as.push_back(a);
          bs.push_back(b);
          cs.push_back(c);
          maxSs.push_back(maxS);
          Ns.push_back(N);
        }
      }
    }
  }

  // long numberObjec


// tsDataFrame=5;

  List list(5);
  list[0]=as;
  list[1]=bs;
  list[2]=cs;
  list[3]=maxSs;
  list[4]=Ns;
  // for(long i=0;i<numberObjectsDataFrame;i++){
  //   list[i]=(wrap(result[i]));
  // }

  CharacterVector namevec;
  namevec.push_back("a");
  namevec.push_back("b");
  namevec.push_back("c");
  namevec.push_back("maxS");
  namevec.push_back("N");
  // namevec.push_back("weight");
  // namevec.push_back("idCluster");
  // namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}






// // [[Rcpp::export]]
// double createPointsGridWithProbabilityAndCalculateFractalDimension(double spacing,long numCol,long numRow,double p){

//   std::vector<double> xsTemp,ysTemp,xs,ys;
//   std::vector<Point2d> points;
//   long numPoints=0;
//   xsTemp.resize(numCol*numRow);
//   ysTemp.resize(numCol*numRow);
// //std::stringstream ss;
// //    long numNode=0;
//   for(long i=0;i<numCol;i++){
//     for(long j=0;j<numRow;j++){

//       if(Functions::runiform(0.0,1.0)<=p){
//         xsTemp[numPoints]=(double)(i)*spacing+Functions::runiform(-spacing/5,spacing/5);
//         ysTemp[numPoints]=(double)(j)*spacing+Functions::runiform(-spacing/5,spacing/5);
//         numPoints++;

//       }
//     }
//   }
//   xs.resize(numPoints);
//   ys.resize(numPoints);

// //  ss<<numPoints/((double)(numCol*numRow)*p);
// //    out(ss.str());
//   for(long i=0;i<numPoints;i++){
//     xs[i]=xsTemp[i];
//     ys[i]=ysTemp[i];
//   }
//   double result_=FractalDimension::calculateBoxCounting(xs,ys,500,100,25);
// //    List list(2);
// //    list[0]=(wrap(result_[0]));
// //    list[1]=(wrap(result_[1]));
// //    //    list[2]=(weights);
// //
// //    CharacterVector namevec;
// //    namevec.push_back("xs");
// //    namevec.push_back("ys");
// //    //    namevec.push_back("weight");
// //    list.attr("names") = namevec;
// //    DataFrame df(list);
// //    return df;
//   return result_;

// }

// [[Rcpp::export]]
DataFrame generateSetOfFractalPoints(double gamma,double maxX,double minX,double maxY,double minY,double max,double min,bool regular,bool random){

  std::vector<std::vector<double> >  result_=FractalDimension::generateSetOfPointsInvertedBoxCounting( gamma, maxX, minX, maxY, minY, max, min,regular,random);




  List list(2);
  list[0]=(wrap(result_[0]));
  list[1]=(wrap(result_[1]));
    //    list[2]=(weights);

  CharacterVector namevec;
  namevec.push_back("xs");
  namevec.push_back("ys");
    //    namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


// [[Rcpp::export]]
DataFrame createDelaunayTriangulation(NumericVector ids,NumericVector xs,NumericVector ys,double tolerance){
  std::vector<double> xs_=Rcpp::as<std::vector<double> > (xs);
  std::vector<double> ys_=Rcpp::as<std::vector<double> > (ys);
  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);

  std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  result_=Geometry::delaunay( ids_,xs_,ys_);
//    std::vector<double> weights;

  Grafo G;

  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
  coordinates=std::make_tuple(ids_,xs_,ys_);
  Grafo::create(&G,result_,coordinates,false);
  std::vector<long> linksRemoved;
  Grafo::cleanDuplicatedLinks(&G,tolerance,linksRemoved,false);


  auto finalNCOL=Grafo::getNCOL(&G);
//    auto finalCoordinates=Grafo::getCoordinates(&G);


  List list(3);
  list[0]=(wrap(std::get<0>(finalNCOL)));
  list[1]=(wrap(std::get<1>(finalNCOL)));
  list[2]=(wrap(std::get<2>(finalNCOL)));


  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

// [[Rcpp::export]]
DataFrame cleanNCOL(DataFrame ncol,DataFrame coordinates,double tolerance){
  NumericVector ids=as<NumericVector>(coordinates[0]);
  NumericVector x=as<NumericVector>(coordinates[1]);
  NumericVector y=as<NumericVector>(coordinates[2]);
  NumericVector idA=as<NumericVector>(ncol[0]);
  NumericVector idB=as<NumericVector>(ncol[1]);
  NumericVector weights=as<NumericVector>(ncol[2]);




  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  std::vector<double> xs_=Rcpp::as<std::vector<double> > (x);
  std::vector<double> ys_=Rcpp::as<std::vector<double> > (y);
  std::vector<long> idA_=Rcpp::as<std::vector<long> > (idA);
  std::vector<long> idB_=Rcpp::as<std::vector<long> > (idB);
  std::vector<double> weights_=Rcpp::as<std::vector<double> > (weights);

  Grafo G;
  auto ncol_=std::make_tuple(idA_,idB_,weights_);
  std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates_;
  coordinates_=std::make_tuple(ids_,xs_,ys_);
  Grafo::create(&G,ncol_,coordinates_,false);
  std::vector<long> linksRemoved;
  Grafo::cleanDuplicatedLinks(&G,tolerance,linksRemoved,false);


  auto finalNCOL=Grafo::getNCOL(&G);
//    auto finalCoordinates=Grafo::getCoordinates(&G);


  List list(3);
  list[0]=(wrap(std::get<0>(finalNCOL)));
  list[1]=(wrap(std::get<1>(finalNCOL)));
  list[2]=(wrap(std::get<2>(finalNCOL)));


  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}

// [[Rcpp::export]]
NumericVector getNodesInsidePolygonPrimal(XPtr<DualExtendedGraph> deg, XPtr<Grafo> polygon){
  //border boundary limit inside region
  std::set<long> validIds;
  validIds=GeometryGraph::nodesInPolygon(deg->getPrimalGraph(),polygon);
  NumericVector ids(validIds.size());
  long i=0;
  for(auto id:validIds){
    ids[i]=id;
    // ids[i]++;
    i++;
  }
  return ids;
}
// [[Rcpp::export]]
NumericVector getNodesInsidePolygon(XPtr<Grafo> G, XPtr<Grafo> polygon){
  //border boundary limit inside region
  std::set<long> validIds;
  validIds=GeometryGraph::nodesInPolygon(G,polygon);
  NumericVector ids(validIds.size());
  long i=0;
  for(auto id:validIds){
    ids[i]=id;
    // ids[i]++;
    i++;
  }
  return ids;
}


// [[Rcpp::export]]
DataFrame calculateCompleteAngularPercolation(XPtr< DualExtendedGraph > deg,double definition,bool calculatePhaseTransition){
  // double definition=10;
  CriticalExponentsPercolation cep;
  // bool calculatePhaseTransition=false;
  DualExtendedGraph::calculateCompleteAngularPercolation(deg,definition,cep,calculatePhaseTransition);



  List list(5);
  list[0]=(wrap(cep.angles));
  list[1]=(wrap(cep.probabilities));
  list[2]=(wrap(cep.massesGC));
  list[3]=(wrap(cep.averageClusterSize));
  list[4]=(wrap(cep.entropies));


  CharacterVector namevec;
  namevec.push_back("angles");
  namevec.push_back("probabilities");
  namevec.push_back("massesGC");
  namevec.push_back("averageClusterSize");
  namevec.push_back("entropies");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



//// [[Rcpp::export]]
//void setPrimalAsStructuralGraph(XPtr< DualExtendedGraph > deg){
//  DualExtendedGraph::setPrimalAsStructuralGraph(deg);
//}

// [[Rcpp::export]]
void saveBoundariesMetricPercolation(XPtr< DualExtendedGraph > deg,double threshold,String fileName,long minSize,double alpha){
  //saveBorders
  std::vector<long> colors;
  std::vector<double> sizes;
  DualExtendedGraph::metricPercolation(deg,threshold,colors,sizes);
  std::vector<Grafo> subgraphs;
  Grafo::getComponentsFromColorsOfLinks(deg->getStructuralGraph(),subgraphs,minSize,colors,sizes);
  std::cout<<"Number of components: "<<subgraphs.size()<<'\n';
  for(long i=0;i<subgraphs.size();i++){
    // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates=Grafo::getCoordinates(&subgraphs[i]);
    // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > boundary=Geometry::calculateAlphaShape(std::get<0>(coordinates),std::get<1>(coordinates),std::get<2>(coordinates),alpha);
    Grafo boundaryGraph;
    // Grafo::create(&boundaryGraph,boundary,coordinates,false);
    // std::cout<<"Size of boundary: "<<i<<": "<<boundaryGraph.nodes.size()<<" , "<<boundaryGraph.links.size()<<'\n';
    // Grafo LG;
    // Grafo::getLargestComponent(&boundaryGraph,&LG);
    // std::cout<<"Size of boundary: "<<i<<": "<<LG.nodes.size()<<'\n';
    GeometryGraph::createBoundaryGraph(&subgraphs[i],&boundaryGraph,alpha);
    TextFile::createLineString(&boundaryGraph,fileName,true);
  }
}




// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexMetricPercolation(XPtr< DualExtendedGraph > deg){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexMetric(deg,100,HI);
  // std::vector<double> HI=DualExtendedGraph::getHImetricInPrimal(deg,HI_temp);
  return wrap(HI);
}


// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexMetricPercolationUsingMassesNodes(XPtr< DualExtendedGraph > deg){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexMetricUsingMassesNodes(deg,100,HI);
  // std::vector<double> HI=DualExtendedGraph::getHImetricInPrimal(deg,HI_temp);
  return wrap(HI);
}

// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexMetricPercolationUsingMassesNodes_presetThresholds(XPtr< DualExtendedGraph > deg,NumericVector thresholds ){
  std::vector<double> HI;
  std::vector<double> thresholds_=Rcpp::as<std::vector<double> > (thresholds);
  // std::vector<double> entropies_=Rcpp::as<std::vector<double> >(entropies);
  DualExtendedGraph::calculateHierarchicalIndexMetricUsingMassesNodes(deg,100,HI,thresholds_);
  // std::vector<double> HI=DualExtendedGraph::getHImetricInPrimal(deg,HI_temp);
  return wrap(HI);
}

// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexMetricUsingMassesNodesAsMeasureOfStructure(XPtr< DualExtendedGraph > deg){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexMetricUsingMassesNodesAsMeasureOfStructure(deg,100,HI);
  // std::vector<double> HI=DualExtendedGraph::getHImetricInPrimal(deg,HI_temp);
  return wrap(HI);
}

// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexMetric_basedInDensityOfNodesThatRepresentAGrid_UsingMassesNodes(XPtr< DualExtendedGraph > deg,double widthSquareGrid){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexMetric_basedInDensityOfNodesThatRepresentAGrid_UsingMassesNodes(deg,100,HI,widthSquareGrid);
  // std::vector<double> HI=DualExtendedGraph::getHImetricInPrimal(deg,HI_temp);
  return wrap(HI);
}


// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexDualPercolation(XPtr< DualExtendedGraph > deg){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexDual(deg,100,HI);
  // std::vector<double> HI=DualExtendedGraph::getHImetricInPrimal(deg,HI_temp);
  return wrap(HI);
}

// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexAngularPercolation(XPtr< DualExtendedGraph > deg){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexAngular(deg,100,HI);

  return wrap(HI);
}

// [[Rcpp::export]]
NumericVector calculateHierarchicalIndexAngularPercolationUsingMetricWeightsAsMass(XPtr< DualExtendedGraph > deg,double definition){
  std::vector<double> HI;
  DualExtendedGraph::calculateHierarchicalIndexAngularUsingMetricweightsAsMass(deg,definition,HI);

  return wrap(HI);
}


// [[Rcpp::export]]
XPtr<Grafo> getGraphWithinBoundaryOfAnotherGraph(XPtr< DualExtendedGraph > deg,XPtr< Grafo > G){
    Grafo* realGraphCity=new Grafo();
    Grafo boundary;
    GeometryGraph::createBoundaryGraph(G, &boundary, 0);
    GeometryGraph::getSubgraphWithinABoundary(deg->getPrimalGraph(), &boundary, realGraphCity);
    Rcpp::XPtr< Grafo > p(realGraphCity,true) ;
    return (p);
}
// [[Rcpp::export]]
XPtr<Grafo> getBoundaryGraph(XPtr< Grafo > G){
    // Grafo* realGraphCity=new Grafo();
    Grafo* boundary=new Grafo();
    GeometryGraph::createBoundaryGraph(G, boundary, 0);
    // GeometryGraph::getSubgraphWithinABoundary(deg->getPrimalGraph(), &boundary, realGraphCity);
    Rcpp::XPtr< Grafo > p(boundary,true) ;
    return (p);
}

// [[Rcpp::export]]
XPtr<Grafo> getGraphWithinBoundaryPrimal(XPtr< DualExtendedGraph > deg,XPtr<Grafo> boundary){
    Grafo* realGraphCity=new Grafo();
    // Grafo* boundary=new Grafo();
    // GeometryGraph::createBoundaryGraph(G, boundary, 0);
    GeometryGraph::getSubgraphWithinABoundary(deg->getPrimalGraph(), boundary, realGraphCity);
    Rcpp::XPtr< Grafo > p(realGraphCity,true) ;
    return (p);
}


// [[Rcpp::export]]
XPtr<Grafo> getGraphWithinBoundary(XPtr< Grafo > G,XPtr<Grafo> boundary){
    Grafo* realGraphCity=new Grafo();
    // Grafo* boundary=new Grafo();
    // GeometryGraph::createBoundaryGraph(G, boundary, 0);
    GeometryGraph::getSubgraphWithinABoundary(G, boundary, realGraphCity);
    Rcpp::XPtr< Grafo > p(realGraphCity,true) ;
    return (p);
}

// [[Rcpp::export]]
DataFrame getColorsAndSizesClustersCompleteWithinABoundary(XPtr< DualExtendedGraph > deg,double threshold,long minSize){
  std::vector<long> colors;
  std::vector<double> sizes;
  DualExtendedGraph::metricPercolation(deg,threshold,colors,sizes);
  std::vector<Grafo> cities;
  Grafo::getComponentsFromColorsOfLinks(deg->getStructuralGraph(),cities,minSize,colors,sizes);
  std::cout<<"Number of cities: "<<cities.size()<<'\n';
  std::unordered_map<long,long> idNodesStructuralGraphByOriginalId;
  for(long i=0;i<deg->getStructuralGraph()->nodes.size();i++){
    idNodesStructuralGraphByOriginalId[deg->getStructuralGraph()->nodes[i]->originalID]=i;
  }
  std::vector<long> colorsCities;
  colorsCities.resize(deg->getStructuralGraph()->nodes.size(),-1);
  std::vector<double> sizesCities;
  sizesCities.resize(deg->getStructuralGraph()->nodes.size(),0);
  for(long i=0;i<cities.size();i++){
    // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates=Grafo::getCoordinates(&subgraphs[i]);
    // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > boundary=Geometry::calculateAlphaShape(std::get<0>(coordinates),std::get<1>(coordinates),std::get<2>(coordinates),alpha);
    // Grafo boundaryGraph;
    // Grafo::create(&boundaryGraph,boundary,coordinates,false);
    // std::cout<<"Size of boundary: "<<i<<": "<<boundaryGraph.nodes.size()<<" , "<<boundaryGraph.links.size()<<'\n';
    // Grafo LG;
    // Grafo::getLargestComponent(&boundaryGraph,&LG);
    // std::cout<<"Size of boundary: "<<i<<": "<<LG.nodes.size()<<'\n';
    std::cout<<"Calculating city "<<i<<", number nodes "<<cities[i].nodes.size()<<'\n';
    Grafo realGraphCity;
    Grafo boundary;
    GeometryGraph::createBoundaryGraph(&cities[i], &boundary, 0);
    GeometryGraph::getSubgraphWithinABoundary(deg->getStructuralGraph(), &boundary, &realGraphCity);
    for(long j=0;j<realGraphCity.nodes.size();j++){
      long idTemp=idNodesStructuralGraphByOriginalId[realGraphCity.nodes[j]->originalID];
      colorsCities[idTemp]=i;
      sizesCities[idTemp]=realGraphCity.links.size();
    }

  }
  // return wrap(colorsCities);

  List list(2);
  list[0]=(wrap(colorsCities));
  list[1]=(wrap(sizesCities));



  CharacterVector namevec;
  namevec.push_back("idCities");
  namevec.push_back("sizeCluster");
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}







// [[Rcpp::export]]
DataFrame getMeasurementsFromClustersCompleteWithinABoundary(XPtr< DualExtendedGraph > deg,double threshold,long minSize){
  std::vector<long> colors;
  std::vector<double> sizes;
  DualExtendedGraph::metricPercolation(deg,threshold,colors,sizes);
  std::vector<Grafo> cities;
  Grafo::getComponentsFromColorsOfLinks(deg->getStructuralGraph(),cities,minSize,colors,sizes);

  // std::vector<long> colorsCities;
  // colorsCities.resize(deg.getStructuralGraph()->nodes.size(),-1);
  // std::vector<double> sizesCities;
//        std::vector<long> orderSizes=Functions::getIndexesOfOrderedValues(sizes,false);
  // lines.clear();
  // std::unordered_map<std::string,long> idNodesStructuralGraphByOriginalId;
  // for(long i=0;i<deg.getStructuralGraph().nodes.size();i++){
  //   idNodesStructuralGraphByOriginalId[deg->getStructuralGraph().nodes[i]->originalID]=i;
  // }

  std::vector<long> n_v,m_v,numberRegions_v;
  std::vector<double> totalArea_v,averageAreaRegions_v,averageLengthLinks_v,perimeter_v,totalLengthLinks_v,averageLocalClusteringCoefDual_v,averageLocalClusteringCoefPrimal_v,averageDegreeDual_v,averageDegreePrimal_v;

  n_v.reserve(cities.size());
  m_v.reserve(cities.size());
  numberRegions_v.reserve(cities.size());
  totalArea_v.reserve(cities.size());
  averageAreaRegions_v.reserve(cities.size());
  averageLengthLinks_v.reserve(cities.size());
  totalLengthLinks_v.reserve(cities.size());
  perimeter_v.reserve(cities.size());
  averageLocalClusteringCoefDual_v.reserve(cities.size());
  averageLocalClusteringCoefPrimal_v.reserve(cities.size());
  averageDegreePrimal_v.reserve(cities.size());
  averageDegreeDual_v.reserve(cities.size());

  for(long i=0;i<cities.size();i++){
    if(cities[i].links.size()>0){
      std::cout<<"Calculating cluster "<<i<<" / "<<cities.size()<<'\n';
      Grafo realGraphCity;
      Grafo boundary;
      GeometryGraph::createBoundaryGraph(&cities[i], &boundary, 0);
      GeometryGraph::getSubgraphWithinABoundary(deg->getStructuralGraph(), &boundary, &realGraphCity);
      std::cout<<".. real cluster within boundary obtained "<<'\n';
      long n=realGraphCity.nodes.size();
      long m=realGraphCity.links.size();
      Grafo dualCity;
      Grafo::constructDual(&realGraphCity, &dualCity);
      std::cout<<".. dual graph constructed "<<'\n';
      double totalArea=0;
      double perimeter=0;
      double totalLengthLinks=0;
      for(long j=0;j<realGraphCity.links.size();j++){
        totalLengthLinks+=realGraphCity.links[j]->weight;
      }
      double clusteringCoefficientPrimal=0.0;
      double avDegreePrimal=0.0;
      for(long j=0;j<realGraphCity.nodes.size();j++){
              // clusteringCoefficientPrimal+=Grafo::calculateLocalClusteringCoefficient(&realGraphCity,realGraphCity.nodes[j]);
        avDegreePrimal+=realGraphCity.nodes[j]->links.size();
      }
          // for(long j=0;j<realGraphCity.nodes.size();j++){
          //     colorsCities[idNodesStructuralGraphByOriginalId[realGraphCity.nodes[j]->originalID]]=i;
          // }
          // sizesCities.push_back(realGraphCity.nodes.size());
      double numberRegions=dualCity.nodes.size()-1;
      double sumAreasRegions=0.0;
//                double numberRegions=0;
      double averageAreaRegions=0;
      double clusteringCoefficientDual=0.0;
      double avDegreeDual=0.0;

      std::cout<<".. measurements primal finished "<<'\n';
      for(long j=0;j<dualCity.nodes.size();j++){
        avDegreeDual+=dualCity.nodes[j]->links.size();
              // clusteringCoefficientDual+=Grafo::calculateLocalClusteringCoefficient(&dualCity,dualCity.nodes[j]);
        std::vector<Link*> linksOfDualRegion;
        Grafo dualRegionLimits;
        for(long h=0;h<dualCity.nodes[j]->links.size();h++){
          linksOfDualRegion.push_back(realGraphCity.links[dualCity.nodes[j]->links[h]->id]);
        }
        Grafo::inducedSubgraphFromLinks(&realGraphCity, &dualRegionLimits, linksOfDualRegion);
        if(j==0){
          totalArea=GeometryGraph::calculateAreaPolygon(&dualRegionLimits);
          for(long h=0;h<linksOfDualRegion.size();h++){
            perimeter+=linksOfDualRegion[h]->weight;
          }
        }else{
          sumAreasRegions+=GeometryGraph::calculateAreaPolygon(&dualRegionLimits);
          numberRegions++;
        }
      }
      std::cout<<".. measurements dual finished "<<'\n';
      averageAreaRegions=sumAreasRegions/numberRegions;

      n_v.push_back(n);
      m_v.push_back(m);
      totalArea_v.push_back(totalArea);
      averageAreaRegions_v.push_back(averageAreaRegions);
      averageLengthLinks_v.push_back((double)totalLengthLinks/(double)m);
      numberRegions_v.push_back(numberRegions);
      perimeter_v.push_back(perimeter);
      totalLengthLinks_v.push_back(totalLengthLinks);
      averageLocalClusteringCoefDual_v.push_back(clusteringCoefficientDual/(double)dualCity.nodes.size());
      averageLocalClusteringCoefPrimal_v.push_back(clusteringCoefficientPrimal/(double)n);
      averageDegreePrimal_v.push_back(avDegreePrimal/n);
      averageDegreeDual_v.push_back(avDegreeDual/(double)dualCity.nodes.size());

          // std::stringstream lineTemp;
          // lineTemp<<i<<" "<<n<<" "<<m<<" "<<totalArea<<" "<<averageAreaRegions<<" "<<numberRegions<<" "<<perimeter<<" "<<totalLengthLinks;
          // lines.push_back(lineTemp.str());

    }else{
      break;
    }

  }

  List list(12);
  list[0]=(wrap(n_v));
  list[1]=(wrap(m_v));
  list[2]=(wrap(totalArea_v));
  list[3]=(wrap(averageAreaRegions_v));
  list[4]=(wrap(averageLengthLinks_v));
  list[5]=(wrap(numberRegions_v));
  list[6]=(wrap(perimeter_v));
  list[7]=(wrap(totalLengthLinks_v));
  list[8]=(wrap(averageLocalClusteringCoefDual_v));
  list[9]=(wrap(averageLocalClusteringCoefPrimal_v));
  list[10]=(wrap(averageDegreePrimal_v));
  list[11]=(wrap(averageDegreeDual_v));



  CharacterVector namevec;
  namevec.push_back("n");
  namevec.push_back("m");
  namevec.push_back("totalArea");
  namevec.push_back("averageAreaRegions");
  namevec.push_back("averageLengthLinks");
  namevec.push_back("numberRegions");
  namevec.push_back("perimeter");
  namevec.push_back("totalLengthLinks");
  namevec.push_back("averageClusteringCoefficientDual");
  namevec.push_back("averageClusteringCoefficientPrimal");
  namevec.push_back("avDegreePrimal");
  namevec.push_back("avDegreeDual");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}



// [[Rcpp::export]]
DataFrame fractalNoise(long xInit,long yInit,long w,long h,double zoom,double expansionFactor,double p,double octaves,int noiseKey,bool ridged){


  std::vector<std::vector<double> >  matrix=GenerativeProcedures::fractal_noise(xInit,yInit,w,h,zoom,expansionFactor,p,octaves,noiseKey,ridged);




  List list(3);
  list[0]=wrap(matrix[0]);
  list[1]=wrap(matrix[1]);
  list[2]=wrap(matrix[2]);





  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");
  namevec.push_back("z");



  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}












//// [[Rcpp::export]]
//void calculateMultifractalDimension(XPtr<Grafo> G){
//
//
//
//    std::vector<double> qs;
//  for(long i=-10;i<=10;i++){
//    qs.push_back(i);
//  }
//    InterfaceMultiFractalAnalysis ima=FractalDimension::MultifractalAnalysis_box(G, qs);
//     for(long i=0;i<ima.Dqs.size();i++){
//         std::cout<<"D"<<qs[i]<<"="<<std::to_string(ima.Dqs[i])<<'\n';
//     }
//     std::cout<<'\n';
//     for(long i=0;i<ima.Dqs.size();i++){
//         std::cout<<"df=rbind(df,data.frame(q="<<qs[i]<<",Dq="<<std::to_string(ima.Dqs[i])<<"))"<<'\n';
//     }
//
//
//  // List list(3);
//  // list[0]=wrap(matrix[0]);
//  // list[1]=wrap(matrix[1]);
//  // list[2]=wrap(matrix[2]);
//
//
//
//
//
//  // CharacterVector namevec;
//  // namevec.push_back("x");
//  // namevec.push_back("y");
//  // namevec.push_back("z");
//
//
//
//  // list.attr("names") = namevec;
//  // DataFrame df(list);
//  // return df;
//
//}


// [[Rcpp::export]]
void calculateMultifractalDimension_primal_DEG(XPtr<DualExtendedGraph> deg,String method,NumericVector gridSizes){

  std::vector<double> gridSizes_=Rcpp::as<std::vector<double> > (gridSizes);
  std::vector<double> qs;

  for(long i=-10;i<=10;i++){
    qs.push_back(i);
  }
  InterfaceMultiFractalAnalysis ima;
  if(method=="sandBox"){
    ima=FractalDimension::MultifractalAnalysis_sandBox(deg->getPrimalGraph(), qs);
  }else if(method=="boxCounting"){
    ima=FractalDimension::MultifractalAnalysis_boxCounting(deg->getPrimalGraph(), qs,gridSizes_);
  }
  for(long i=0;i<ima.Dqs.size();i++){
   std::cout<<"D"<<qs[i]<<"="<<std::to_string(ima.Dqs[i])<<'\n';
 }
     // std::cout<<'\n';
     // for(long i=0;i<ima.Dqs.size();i++){
     //     std::cout<<"df=rbind(df,data.frame(q="<<qs[i]<<",Dq="<<std::to_string(ima.Dqs[i])<<"))"<<'\n';
     // }


  // List list(3);
  // list[0]=wrap(matrix[0]);
  // list[1]=wrap(matrix[1]);
  // list[2]=wrap(matrix[2]);





  // CharacterVector namevec;
  // namevec.push_back("x");
  // namevec.push_back("y");
  // namevec.push_back("z");



  // list.attr("names") = namevec;
  // DataFrame df(list);
  // return df;

}




// [[Rcpp::export]]
double detectPhaseTransitionAngularPercolation(XPtr< DualExtendedGraph > deg){
  std::pair<double,double> result=DualExtendedGraph::detectPhaseTransitionAngularPercolation(deg,.0001);
  return result.first;
    // result.first=anglePhaseTransition;
    // result.second=probabilityPhaseTransition;

}



// // [[Rcpp::export]]
// NumericVector getProbabilities(NumericVector weights){
//   NumericVector p(weights.size());
//   for(long i=0;i<weights.size();i++){
//     p[i]=(double)(i)/(double)(weights.size());
//   }
//   return p;
//
// }

// [[Rcpp::export]]
DataFrame getProbabilities(NumericVector completeWeights,NumericVector actualSetOfThresholds){
  NumericVector p(actualSetOfThresholds.size());
std::vector<double> values=Rcpp::as<std::vector<double> > (completeWeights);
  std::vector<double> orderedWeights=Functions::orderValues(values,true);
  std::vector<double> values2=Rcpp::as<std::vector<double> > (actualSetOfThresholds);
  std::vector<double> orderedThresholds=Functions::orderValues(values2,true);
  long index=0;
  for(long i=0;i<orderedThresholds.size();i++){
    // for(long i=0;i<weights.size();i++){
    while(orderedWeights[index]<orderedThresholds[i]&&index<orderedThresholds.size()){
      index++;
    }
    p[i]=(double)(index)/(double)(orderedWeights.size());
    // }
  }

  List list(2);
  list[0]=wrap(orderedThresholds);
  list[1]=p;









  CharacterVector namevec;
  namevec.push_back("threshold");
  namevec.push_back("p");






  list.attr("names") = namevec;
  DataFrame df(list);
  return df;


}


// [[Rcpp::export]]
NumericVector getAngularWeights(XPtr< DualExtendedGraph > deg){
  std::vector<double> angles=DualExtendedGraph::getAngularWeightsLineGraph(deg);
  return wrap(angles);
}


// [[Rcpp::export]]
NumericVector getThresholdsFromEntropyMetricPercolation(XPtr< DualExtendedGraph > deg,double definition,double minThreshold){
  double max=-INFINITY;
  std::vector<double> thresholds;
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    if(deg->getPrimalGraph()->links[i]->weight>max){
      max=deg->getPrimalGraph()->links[i]->weight;
    }
  }
  std::vector<double> x;
  std::vector<double> y;
  // std::vector<double> entropies;


  for(double i=minThreshold;i<max;i+=(max-minThreshold)/definition){
    // thresholdsTemp.push_back(i);
    y.push_back(DualExtendedGraph::getEntropyFromMetricPercolation(deg,i));
    x.push_back(i);
  }
  Fxy f;
  Fxy::insertData(&f,x,y);
  Fxy integral=Fxy::getIntegral(&f);
  Fxy::interpolateDataInY(&integral,definition);
  for(long i=0;i<integral.x.size();i++){
    thresholds.push_back(integral.x[i]);
  }
  return wrap(thresholds);

}

// [[Rcpp::export]]
NumericVector getThresholdsFromEntropyDualPercolation(XPtr< DualExtendedGraph > deg,double definition){
  double max=-INFINITY;
  double minThreshold=INFINITY;
  std::vector<double> thresholds;
  for(long i=0;i<deg->getDualGraph()->links.size();i++){
    if(deg->getDualGraph()->links[i]->weight>max){
      max=deg->getDualGraph()->links[i]->weight;

    }
    if(deg->getDualGraph()->links[i]->weight<minThreshold){
      minThreshold=deg->getDualGraph()->links[i]->weight;
    }
  }
  std::vector<double> x;
  std::vector<double> y;
  // std::vector<double> entropies;


  for(double i=minThreshold;i<max;i+=(max-minThreshold)/definition){
    // thresholdsTemp.push_back(i);
    y.push_back(DualExtendedGraph::getEntropyFromDualPercolation(deg,i));
    x.push_back(i);
  }
  Fxy f;
  Fxy::insertData(&f,x,y);
  Fxy integral=Fxy::getIntegral(&f);
  Fxy::interpolateDataInY(&integral,definition);
  for(long i=0;i<integral.x.size();i++){
    thresholds.push_back(integral.x[i]);
  }
  return wrap(thresholds);

}


// [[Rcpp::export]]
double getEntropyFromMetricPercolation(XPtr<DualExtendedGraph> deg,double threshold){
  double H=DualExtendedGraph::getEntropyFromMetricPercolation(deg,threshold);
  return H;
}


// [[Rcpp::export]]
List getHierarchicalTreeMetric(XPtr< DualExtendedGraph > deg,double definition,double minThreshold,double minMassCluster){
  Grafo* tree=new Grafo();
  std::vector<long> colorsNodes;
  std::vector<double> massesTreeNodes;
  std::vector<double> thresholds;
  std::vector<long> depths;
  double max=-INFINITY;
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    if(deg->getPrimalGraph()->links[i]->weight>max){
      max=deg->getPrimalGraph()->links[i]->weight;
    }
  }
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> entropies;

std::tuple<std::vector<double>,std::vector<double> > tAndH;
  tAndH=DualExtendedGraph::getThresholdsAndEntropyForMetricPercolation_UsingMassNodes(deg,definition);
  thresholds=std::get<0>(tAndH);
  // for(double i=minThreshold;i<max;i+=(max-minThreshold)/definition){
  //   // thresholdsTemp.push_back(i);
  //   y.push_back(DualExtendedGraph::getEntropyFromMetricPercolation(deg,i));
  //   x.push_back(i);
  // }
  // Fxy f;
  // Fxy::insertData(&f,x,y);
  // Fxy integral=Fxy::getIntegral(&f);
  // Fxy::interpolateDataInY(&integral,definition);
  // for(long i=0;i<integral.x.size();i++){
  //   thresholds.push_back(integral.x[i]);
  // }




  DualExtendedGraph::createHierarchicalTreeMetric(deg,tree,thresholds,colorsNodes,massesTreeNodes,depths,minMassCluster);
  Rcpp::XPtr< Grafo > p(tree,true) ;


  List list(5);
  list[0]=p;
  list[1]=wrap(colorsNodes);
  list[2]=wrap(massesTreeNodes);
  list[3]=wrap(thresholds);
  list[4]=wrap(depths);





  CharacterVector namevec;
  namevec.push_back("tree_graph");
  namevec.push_back("clustersNodesStructuralGraph");
  namevec.push_back("massesTreeNodes");
  namevec.push_back("thresholds");
  namevec.push_back("depths");




  list.attr("names") = namevec;
  return list;
  // DataFrame df(list);
  // return df;

}


// [[Rcpp::export]]
List getHierarchicalTreeMetric_presetThresholds(XPtr< DualExtendedGraph > deg,NumericVector thresholds,double minMassCluster){
  Grafo* tree=new Grafo();
  std::vector<long> colorsNodes;
  std::vector<double> massesTreeNodes;
  std::vector<double> thresholds_=Rcpp::as<std::vector<double> >(thresholds);
  std::vector<long> depths;
  double max=-INFINITY;
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    if(deg->getPrimalGraph()->links[i]->weight>max){
      max=deg->getPrimalGraph()->links[i]->weight;
    }
  }
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> entropies;

// std::tuple<std::vector<double>,std::vector<double> > tAndH;
//   tAndH=DualExtendedGraph::getThresholdsAndEntropyForMetricPercolation_UsingMassNodes(deg,definition);
//   thresholds=std::get<0>(tAndH);
  // for(double i=minThreshold;i<max;i+=(max-minThreshold)/definition){
  //   // thresholdsTemp.push_back(i);
  //   y.push_back(DualExtendedGraph::getEntropyFromMetricPercolation(deg,i));
  //   x.push_back(i);
  // }
  // Fxy f;
  // Fxy::insertData(&f,x,y);
  // Fxy integral=Fxy::getIntegral(&f);
  // Fxy::interpolateDataInY(&integral,definition);
  // for(long i=0;i<integral.x.size();i++){
  //   thresholds.push_back(integral.x[i]);
  // }




  DualExtendedGraph::createHierarchicalTreeMetric(deg,tree,thresholds_,colorsNodes,massesTreeNodes,depths, minMassCluster);
  Rcpp::XPtr< Grafo > p(tree,true) ;


  List list(5);
  list[0]=p;
  list[1]=wrap(colorsNodes);
  list[2]=wrap(massesTreeNodes);
  list[3]=wrap(thresholds);
  list[4]=wrap(depths);





  CharacterVector namevec;
  namevec.push_back("tree_graph");
  namevec.push_back("clustersNodesStructuralGraph");
  namevec.push_back("massesTreeNodes");
  namevec.push_back("thresholds");
  namevec.push_back("depths");




  list.attr("names") = namevec;
  return list;
  // DataFrame df(list);
  // return df;

}




// // [[Rcpp::export]]
// NumericVector getParentsInHierarchicalMetricTreeUpToADepth(XPtr< Grafo > tree,NumericVector currentClusters,std::vector<long> depths,long referenceDepth){
//
//   NumericVector newClusters(currentClusters.size());
//   for(long i=0;i<currentClusters.size();i++){
//     if(depths[currentClusters[i]]>referenceDepth){
//       long cluster=currentClusters[i];
//       while(depths[cluster]>referenceDepth){
//         Nodo* node=tree->nodes[cluster];
//         std::vector<Link*> linksThatReachMe=node->getLinksThatReachMe(true);
//         Nodo* parentNode=NULL;
//         if(linksThatReachMe.size()>0){
//           parentNode=linksThatReachMe[0]->A();
//         }
//         newClusters[i]=parentNode->id;
//         cluster=parentNode->id;
//       }
//     }else{
//       newClusters[i]=currentClusters[i];
//     }
//   }
//   return newClusters;
//
// }

// [[Rcpp::export]]
NumericVector getAllParents(XPtr< Grafo > tree,long node){
  NumericVector parents;
  if(node<tree->nodes.size()){
//    long parent=node;
    std::vector<Link*> linksThatReachMe=tree->nodes[node]->getLinksThatReachMe(true);
    while(linksThatReachMe.size()>0){
      long parent=linksThatReachMe[0]->A()->id;
      // std::cout<<"parent "<<parent<<'\n';
      linksThatReachMe=tree->nodes[parent]->getLinksThatReachMe(true);
      parents.push_back(parent);

    }
    return parents;
  }else {
    return NumericVector(0);
  }


}

// [[Rcpp::export]]
long getParent(XPtr< Grafo > tree,long node){
  NumericVector parents;
  if(node<tree->nodes.size()){
    // long parent=node;
    std::vector<Link*> linksThatReachMe=tree->nodes[node]->getLinksThatReachMe(true);
    if(linksThatReachMe.size()>0){
      long parent=linksThatReachMe[0]->A()->id;
      // std::cout<<"parent "<<parent<<'\n';
      // linksThatReachMe=tree->nodes[parent]->getLinksThatReachMe(true);
      // parents.push_back(parent);
      return parent;
    }
    else return -1;

  }else {
    return -1;
  }


}

// [[Rcpp::export]]
NumericVector getSonsInHierarchicalMetricTree(XPtr< Grafo > tree,long node){

  if(node<tree->nodes.size()){
    NumericVector sons(tree->nodes[node]->links.size());
    for(long i=0;i<tree->nodes[node]->links.size();i++){
      sons[i]=tree->nodes[node]->links[i]->B()->id;
    }
    return sons;
  }else {
    return NumericVector(0);
  }


}

// [[Rcpp::export]]
NumericVector getSonsAllLevelsInHierarchicalMetricTree(XPtr< Grafo > tree,long node){

  NumericVector sons;
  std::vector<long> sonsToCheck;
  sons=getSonsInHierarchicalMetricTree(tree,node);
  for(long i=0;i<sons.size();i++){
    sonsToCheck.push_back(sons[i]);
  }
  while(sonsToCheck.size()>0){
    NumericVector sonsTemp=getSonsInHierarchicalMetricTree(tree,sonsToCheck[sonsToCheck.size()-1]);
    sonsToCheck.pop_back();
    for(long i=0;i<sonsTemp.size();i++){
      sonsToCheck.push_back(sonsTemp[i]);
      sons.push_back(sonsTemp[i]);
    }
  }
  return sons;

}




// [[Rcpp::export]]
NumericVector getLeavesSonsOfANode(XPtr< Grafo > tree,long node){

  NumericVector sons;
  std::vector<long> sonsToCheck;
  sons=getSonsInHierarchicalMetricTree(tree,node);
  for(long i=0;i<sons.size();i++){
    sonsToCheck.push_back(sons[i]);
  }
  while(sonsToCheck.size()>0){
    NumericVector sonsTemp=getSonsInHierarchicalMetricTree(tree,sonsToCheck[sonsToCheck.size()-1]);
    sonsToCheck.pop_back();
    for(long i=0;i<sonsTemp.size();i++){
      sonsToCheck.push_back(sonsTemp[i]);
      NumericVector sonsTempTemp=getSonsInHierarchicalMetricTree(tree,sonsTemp[i]);
      if(sonsTempTemp.size()==0){
        sons.push_back(sonsTemp[i]);
      }
    }
  }
  return sons;

}


// [[Rcpp::export]]
DataFrame calculateCentroidsOfClusters(DataFrame coordinates, NumericVector masses, NumericVector clusters){
  NumericVector ids=as<NumericVector>(coordinates[0]);
  NumericVector x=as<NumericVector>(coordinates[1]);
  NumericVector y=as<NumericVector>(coordinates[2]);
  std::set<long> differentClusters;
  for(long i=0;i<clusters.size();i++){
    if(clusters[i]!=-1){
      differentClusters.insert(clusters[i]);
    }
  }
  long numClusters=differentClusters.size();
  NumericVector xs(numClusters,0.0);
  NumericVector ys(numClusters,0.0);
  NumericVector massCluster(numClusters,0.0);
  NumericVector ids_(numClusters,0.0);


  for(long i=0;i<clusters.size();i++){
    if(clusters[i]!=-1){
      xs[clusters[i]]+=x[i]*masses[i];
      ys[clusters[i]]+=y[i]*masses[i];
      massCluster[clusters[i]]+=masses[i];
      ids_[clusters[i]]=clusters[i];
    }
  }
  for(long i=0;i<numClusters;i++){
    xs[i]/=massCluster[i];
    ys[i]/=massCluster[i];
  }

  List list(4);
  list[0]=ids_;
  list[1]=xs;
  list[2]=ys;
  list[3]=massCluster;






  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("x");
  namevec.push_back("y");
  namevec.push_back("mass");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;



}


// [[Rcpp::export]]
XPtr<Grafo> getPrimalGraph(XPtr<DualExtendedGraph> deg){
  Grafo* G=new Grafo();
  G->copyGraph(deg->getPrimalGraph());
  Rcpp::XPtr<Grafo> p(G,true);
  return p;
}
// [[Rcpp::export]]
XPtr<Grafo> getStructuralGraph(XPtr<DualExtendedGraph> deg){
  Grafo* G=new Grafo();
  G->copyGraph(deg->getStructuralGraph());
  Rcpp::XPtr<Grafo> p(G,true);
  return p;
}
// [[Rcpp::export]]
XPtr<Grafo> getLineGraph(XPtr<DualExtendedGraph> deg){
  Grafo* G=new Grafo();
  G->copyGraph(deg->getLineGraph());
  Rcpp::XPtr<Grafo> p(G,true);
  return p;
}
// [[Rcpp::export]]
XPtr<Grafo> getDualGraph(XPtr<DualExtendedGraph> deg){
  Grafo* G=new Grafo();
  G->copyGraph(deg->getDualGraph());
  Rcpp::XPtr<Grafo> p(G,true);
  return p;
}


// [[Rcpp::export]]
NumericVector getLinksWherePointsAre(XPtr< Grafo > G, DataFrame coordinates){


    // NumericVector ids=as<NumericVector>(coordinates[0]);
  std::vector<double> xs=as<std::vector<double> >(coordinates[0]);
  std::vector<double> ys=as<std::vector<double> >(coordinates[1]);

    // std::cout<<xs.size()<<'\n';

  std::vector<long> idClosestLines;
  Grafo::getLinkToWhichPointsBelongs(G,xs,ys,idClosestLines);


  return (wrap(idClosestLines));



}



//// [[Rcpp::export]]
//NumericVector calculateBetweenness(XPtr< Grafo > G, double distanceLimit,NumericVector massesNodes){
//  InterfaceDijkstra result;
//  result.prepareForBetweenness();
//  Grafo::startCalculatingShortestPaths(G);
//  Grafo::calculateDijkstra(G,G->nodes[0],result,distanceLimit);
//  std::vector<double> betweenness;
//  std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
//  Grafo::calculateBetweenness(G,result,betweenness,valuesToPass);
//  std::cout<<"finished"<<'\n';
//  std::vector<double> asdf;
//  Grafo::finishCalculatingShortestPaths(G);
//  return wrap(asdf);
//}







//// [[Rcpp::export]]
//NumericVector calculateClosenessA(XPtr< Grafo > G, double distanceLimit){
//  InterfaceDijkstra result;
//  // result.prepareForBetweenness();
//  std::vector<double> closeness;
//  Grafo::startCalculatingShortestPaths(G);
//  for(long i=0;i<G->nodes.size();i++){
//    Grafo::calculateDijkstra(G,G->nodes[i],result,distanceLimit);
//
//    // std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
//    Grafo::calculateCloseness(G,result,closeness);
//    result.reset();
//    // result.reset();
//  }
//  std::cout<<"finished"<<'\n';
//  Grafo::finishCalculatingShortestPaths(G);
//
//  return wrap(closeness);
//}




// [[Rcpp::export]]
NumericVector calculateCloseness(XPtr< Grafo > G, double distanceLimit){

  std::vector<double> closeness;

    Grafo::calculateCloseness(G,distanceLimit,closeness);


  return wrap(closeness);
}

// [[Rcpp::export]]
NumericVector calculateTotalDistancesFromEachNode(XPtr< Grafo > G, double distanceLimit){

  std::vector<double> distances;

    Grafo::calculateTotalDistancesFromEachNode(G,distanceLimit,distances);


  return wrap(distances);
}



// [[Rcpp::export]]
double calculateEfficiency(XPtr< Grafo > G, double distanceLimit){

  double efficiency;

    Grafo::calculateEfficiency(G,distanceLimit,efficiency);


  return efficiency;
}

// [[Rcpp::export]]
NumericVector calculateBetweenness(XPtr< Grafo > G, double distanceLimit){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  std::vector<double> betweenness;

    Grafo::calculateBetweenness(G,distanceLimit,betweenness);


  return wrap(betweenness);
}

// [[Rcpp::export]]
NumericVector calculateAngularBetweenness(XPtr< DualExtendedGraph > deg, double angularLimit){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  std::vector<double> betweenness;

    DualExtendedGraph::calculateAngularBetweenness(deg,angularLimit,betweenness);


  return wrap(betweenness);
}
// [[Rcpp::export]]
NumericVector calculateMetricEdgeBetweenness(XPtr< DualExtendedGraph > deg, double distanceLimit){
  // std::vector<double> valuesToPass;
  // valuesToPass.resize(G->nodes.size(),1);
  std::vector<double> betweenness;

    DualExtendedGraph::calculateMetricEdgeBetweenness(deg,distanceLimit,betweenness);


  return wrap(betweenness);
}


// [[Rcpp::export]]
NumericVector getShortestPaths_MinDistancesFromANode(XPtr< Grafo > G, long nodeID,double distanceLimit){
  InterfaceDijkstra result;
  // result.prepareForBetweenness();
  std::vector<double> closeness;
  std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
  Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  // for(long i=0;i<G->nodes.size();i++){
  Grafo::calculateDijkstra(G,G->nodes[nodeID],result,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);

    // std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
    // Grafo::calculateCloseness(G,result,closeness);
    // result.reset();
  // }
  // std::cout<<"finished"<<'\n';
 Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
   std::vector<double> distances;
   distances.reserve(G->nodes.size());
   for(long i=0;i<G->nodes.size();i++){
     distances.push_back(result.getMinDistance(i));
   }

  return wrap(distances);
}


// [[Rcpp::export]]
XPtr<Grafo> getShortestPaths_getPaths(XPtr< Grafo > G, long nodeID,double distanceLimit){
  InterfaceDijkstra result;
  result.prepareForBetweenness();
  std::vector<double> closeness;
  std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
  Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  // for(long i=0;i<G->nodes.size();i++){
  Grafo::calculateDijkstra(G,G->nodes[nodeID],result,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);

    // std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
    // Grafo::calculateCloseness(G,result,closeness);
    // result.reset();
  // }
  // std::cout<<"finished"<<'\n';

 Grafo* paths=new Grafo();
 for(long i=0;i<G->nodes.size();i++){
   paths->addNode(G->nodes[i]->location);
 }
   // std::vector<double> distances;
   // distances.reserve(G->nodes.size());
   for(long i=0;i<G->nodes.size();i++){
     long idParent=result.getParentID(G->nodes[i]->id);
     if(idParent!=-1){
       Link* link=G->getLink(idParent,G->nodes[i]->id);
       paths->addLink(idParent,G->nodes[i]->id,link->weight);
     }
     // distances.push_back(result.getMinDistance(i));
   }
Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  // return wrap(distances);
  Rcpp::XPtr<Grafo> p(paths,true);
  return p;
}


// [[Rcpp::export]]
XPtr<Grafo> getShortestPaths_getPathsToANode(XPtr< Grafo > G, long nodeID,long destinationID,double distanceLimit){
  InterfaceDijkstra result;
  result.prepareForBetweenness();
  std::vector<double> closeness;
  std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
  Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  // for(long i=0;i<G->nodes.size();i++){
  Grafo::calculateDijkstra(G,G->nodes[nodeID],result,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);

    // std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
    // Grafo::calculateCloseness(G,result,closeness);
    // result.reset();
  // }
  // std::cout<<"finished"<<'\n';

 Grafo* paths=new Grafo();
 for(long i=0;i<G->nodes.size();i++){
   paths->addNode(G->nodes[i]->location);
 }
   // std::vector<double> distances;
   // distances.reserve(G->nodes.size());
   // for(long i=0;i<G->nodes.size();i++){
   long idParent=destinationID;
   while (idParent!=-1){
     long prev=idParent;
     idParent=result.getParentID(prev);
     if(idParent!=-1){
       Link* link=G->getLink(idParent,prev);
       paths->addLink(idParent,prev,link->weight);
     }
     // distances.push_back(result.getMinDistance(i));
   }
Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  // return wrap(distances);
  Rcpp::XPtr<Grafo> p(paths,true);
  return p;
}




// [[Rcpp::export]]
NumericVector diffuse(XPtr<DualExtendedGraph> deg, long idSegment, std::vector<double> &HIangular,double initialQuantityWater, double tolerance){
  std::vector<double> quantitiesOfWater;
  quantitiesOfWater.resize(deg->getLineGraph()->nodes.size(),0);
  quantitiesOfWater[idSegment]=initialQuantityWater;
  std::vector<double> result;
  result.resize(deg->getLineGraph()->nodes.size(),0);
  result[idSegment]=initialQuantityWater;
  std::queue<Nodo*> nodesToExpand;
  nodesToExpand.push(deg->getLineGraph()->nodes[idSegment]);
  while(nodesToExpand.size()>0){
    Nodo* current=nodesToExpand.front();
    nodesToExpand.pop();
    double water=quantitiesOfWater[current->id];
    quantitiesOfWater[current->id]=0;
    double totalHI=0;
    for(long i=0;i<current->links.size();i++){
      totalHI+=HIangular[current->links[i]->getOtherNode(current)->id];
    }
    for(long i=0;i<current->links.size();i++){
      quantitiesOfWater[current->links[i]->getOtherNode(current)->id]+=water*HIangular[current->links[i]->getOtherNode(current)->id]/totalHI;
      result[current->links[i]->getOtherNode(current)->id]+=water*HIangular[current->links[i]->getOtherNode(current)->id]/totalHI;
      if(quantitiesOfWater[current->links[i]->getOtherNode(current)->id]>tolerance){
        nodesToExpand.push(current->links[i]->getOtherNode(current));
      }
    }
  }
  return wrap(result);
}


// [[Rcpp::export]]
XPtr<Grafo> getBurnedGraphFromPrimal(XPtr<DualExtendedGraph> deg){
  Grafo* burnedGraph=new Grafo();
  Grafo::burnGraph(deg->getPrimalGraph(),burnedGraph);

 Rcpp::XPtr< Grafo > p(burnedGraph,true) ;
 return (p);

}

// [[Rcpp::export]]
void burnPrimalGraph(XPtr<DualExtendedGraph> deg){
  Grafo burnedGraph;
  Grafo::burnGraph(deg->getPrimalGraph(),&burnedGraph);
  deg->reset();
  DualExtendedGraph::addPrimal(deg,&burnedGraph);


}

// [[Rcpp::export]]
XPtr<Grafo> getBurnedGraph(XPtr<Grafo> G){
  Grafo* burnedGraph=new Grafo();
  Grafo::burnGraph(G,burnedGraph);

 Rcpp::XPtr< Grafo > p(burnedGraph,true) ;
 return (p);

}

// [[Rcpp::export]]
XPtr<Grafo> inducedSubgraphFromPrimalUsingLinks(XPtr<DualExtendedGraph> deg,NumericVector indexLinks){
  std::vector<long> ids=as<std::vector<long> > (indexLinks);
  for(long i=0;i<ids.size();i++){
    ids[i]-=1;
  }
  Grafo* subGraph=new Grafo();
  Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),subGraph,ids);

 Rcpp::XPtr< Grafo > p(subGraph,true) ;
 return (p);

}

// [[Rcpp::export]]
XPtr<Grafo> inducedSubgraphUsingNodes(XPtr<Grafo> G,NumericVector idsNodes){
  std::vector<long> ids=as<std::vector<long> > (idsNodes);
  std::set<long> idsInSet;
  for(long i=0;i<ids.size();i++){
    idsInSet.insert(ids[i]);
  }
  Grafo* subGraph=new Grafo();
  Grafo::inducedSubgraph(G,subGraph,idsInSet);

 Rcpp::XPtr< Grafo > p(subGraph,true) ;
 return (p);

}

// [[Rcpp::export]]
NumericVector getDegreesPrimal(XPtr<DualExtendedGraph> deg){
  NumericVector degrees(deg->getPrimalGraph()->nodes.size());
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    degrees[i]=(deg->getPrimalGraph()->nodes[i]->getDegree());
  }
  return degrees;

}

// [[Rcpp::export]]
NumericVector getDegreesDual(XPtr<DualExtendedGraph> deg){
  NumericVector degrees(deg->getDualGraph()->nodes.size());
  for(long i=0;i<deg->getDualGraph()->nodes.size();i++){
    degrees[i]=(deg->getDualGraph()->nodes[i]->getDegree());
  }
  return degrees;

}

// [[Rcpp::export]]
NumericVector getDegrees(XPtr<Grafo> G){
  NumericVector degrees(G->nodes.size());
  for(long i=0;i<G->nodes.size();i++){
    degrees[i]=(G->nodes[i]->getDegree());
  }
  return degrees;

}
// [[Rcpp::export]]
NumericVector getDegreesOut(XPtr<Grafo> G){
  NumericVector degrees(G->nodes.size());
  for(long i=0;i<G->nodes.size();i++){
    degrees[i]=(G->nodes[i]->getDegreeOut());
  }
  return degrees;

}
//// [[Rcpp::export]]
//void constructDual(XPtr<DualExtendedGraph> deg){
//  DualExtendedGraph::createDual(deg);
//
//}


// [[Rcpp::export]]
void breakAcuteAnglesNodesDegree2(XPtr<Grafo> G,double maxAngleAccepted){
  Grafo::breakAcuteAnglesNodesDegree2(G,maxAngleAccepted);

}

// [[Rcpp::export]]
void breakAcuteAnglesNodesDegree2InPrimal(XPtr<DualExtendedGraph> deg,double maxAngleAccepted){
  Grafo::breakAcuteAnglesNodesDegree2(deg->getPrimalGraph(),maxAngleAccepted);

}


// [[Rcpp::export]]
void removeLoopsOfDualInPrimal(XPtr<DualExtendedGraph> deg){
  DualExtendedGraph::removeLoopsOfDualInPrimal(deg);
}

// [[Rcpp::export]]
void removeNodesOfDegree0FromPrimal(XPtr<DualExtendedGraph> deg){
  deg->getPrimalGraph()->removeNodesDegree0();
}

// [[Rcpp::export]]
void removeNodesOfDegree0(XPtr<Grafo> G){
  G->removeNodesDegree0();
}

// [[Rcpp::export]]
NumericVector calculateCoefficientsAngularDeviationPerMetricLengthForAllRegions(XPtr<DualExtendedGraph> deg){
  return wrap(DualExtendedGraph::calculateCoefficientsAngularDeviationPerMetricLengthForAllRegions(deg));

}




// [[Rcpp::export]]
Rcpp::XPtr<DualExtendedGraph> detectBoundaries(XPtr<DualExtendedGraph> deg,NumericVector idClusters,double alpha){
  //o detect borders, detectBorders

  std::vector<long> idClusters_=as<std::vector<long> > (idClusters);
  DualExtendedGraph* degResult=new DualExtendedGraph();

  bool starting=true;
  std::set<long> idUniqueClusters;
  for(long i=0;i<idClusters_.size();i++){
    if(idClusters_[i]!=-1){
      idUniqueClusters.insert(idClusters_[i]);
    }
  }

for(auto id:idUniqueClusters){
  Grafo sG;
  std::set<long> idLinks;
  for(long i=0;i<idClusters_.size();i++){
    if(idClusters_[i]==id){
      idLinks.insert(i);
    }
  }

  Grafo::inducedSubgraphFromLinks(deg->getPrimalGraph(),&sG,idLinks);
  Grafo boundaryGraph;
  GeometryGraph::createBoundaryGraph(&sG,&boundaryGraph,alpha);
  if(starting){
    DualExtendedGraph::addPrimal(degResult,&boundaryGraph);
    starting=false;
  }else{
      DualExtendedGraph::addAnotherGraph(degResult,&boundaryGraph,false);
  }
}
  degResult->getPrimalGraph()->finishedAddingNodes();
    Rcpp::XPtr<DualExtendedGraph> p(degResult,true) ;
  return p;
}

// [[Rcpp::export]]
NumericVector detectRoundAbouts(XPtr<DualExtendedGraph> deg){
  std::vector<long> roundaboutsIdsAtNodes;
  DualExtendedGraph::detectRoundabouts(deg,roundaboutsIdsAtNodes);
  NumericVector idsR=wrap(roundaboutsIdsAtNodes);
  return idsR;
}

// [[Rcpp::export]]
NumericVector detectRoundAboutsChangeCoefs(XPtr<DualExtendedGraph> deg,double minAngle, double maxAngle, double maxDistance,bool useSegmentDistance,double minCoef,double maxCoef){
  std::vector<long> roundaboutsIdsAtNodes;
  DualExtendedGraph::detectRoundabouts(deg,roundaboutsIdsAtNodes,minAngle,maxAngle,maxDistance,useSegmentDistance,minCoef,maxCoef);
  NumericVector idsR=wrap(roundaboutsIdsAtNodes);
  return idsR;
}

// [[Rcpp::export]]
NumericVector detectEntryPointsRoundAbouts(XPtr<DualExtendedGraph> deg,NumericVector roundaboutsIdsAtNodes){
  std::vector<long> roundaboutsEntriesIdsAtNodes;
  std::vector<long> vectorRoundaboutsIds=as<std::vector<long> > (roundaboutsIdsAtNodes);
  DualExtendedGraph::detectEntryPointsToRoundabouts(deg,vectorRoundaboutsIds,roundaboutsEntriesIdsAtNodes);
  return wrap(roundaboutsEntriesIdsAtNodes);
}
// [[Rcpp::export]]
void hyperConnectRoundabouts(XPtr<DualExtendedGraph> deg,bool approximate){
  std::vector<long> roundaboutsIdsAtNodes;
   DualExtendedGraph::detectRoundabouts(deg,roundaboutsIdsAtNodes);
   // DualExtendedGraph::detectEntryPointsToRoundabouts(deg,roundaboutsIdsAtNodes);
   if(!approximate){
      DualExtendedGraph::hyperConnectRoundabouts(deg,roundaboutsIdsAtNodes);
    }else{
      DualExtendedGraph::connectRoundaboutToItsCenter(deg,roundaboutsIdsAtNodes);
    }

  // return wrap(roundaboutsEntriesIdsAtNodes);
}
// [[Rcpp::export]]
NumericVector getIdsOfLinksOfPrimalNotTemp(XPtr<DualExtendedGraph> deg){
  return (wrap(DualExtendedGraph::getIdsOfLinksOfPrimalNotTemp(deg)));
}

// [[Rcpp::export]]
DataFrame getPointsEvenBreaks(XPtr<Grafo> G,double breaksEach){
  std::tuple<std::vector<double>, std::vector<double> > result= Grafo::getPointsEvenBreaks(G,breaksEach);
  List list(2);
  list[0]=std::get<0>(result);
  list[1]=std::get<1>(result);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


// [[Rcpp::export]]
double entropyAreas(NumericVector areas){
  std::vector<double> areas_=as<std::vector<double> > (areas);
  return Entropy::calculateEntropyAreas(areas_);
}

// [[Rcpp::export]]
double entropy(NumericVector data){
  std::vector<double> data_=as<std::vector<double> > (data);
  double H=Entropy::calculateEntropy(data_);
  return H;
}

// [[Rcpp::export]]
DataFrame getDistribution(NumericVector data){
  std::vector<double> data_=as<std::vector<double> > (data);
  Distribution dis=Distribution::createDistribution(data_);
  List list(2);
  list[0]=wrap(dis.f.x);
  list[1]=wrap(dis.f.y);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
  // return Entropy::calculateEntropy(data_);
}

// [[Rcpp::export]]
DataFrame getFunction(NumericVector x,NumericVector y){
  std::vector<double> x_=as<std::vector<double> > (x);
  std::vector<double> y_=as<std::vector<double> > (y);
  Fxy f=Fxy::createFunction(x_,y_);
  List list(2);
  list[0]=wrap(f.x);
  list[1]=wrap(f.y);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
  // return Entropy::calculateEntropy(data_);
}

// [[Rcpp::export]]
DataFrame getFunctionApproximate(NumericVector x,NumericVector y){
  std::vector<double> x_=as<std::vector<double> > (x);
  std::vector<double> y_=as<std::vector<double> > (y);
  Fxy f=Fxy::createFunction(x_,y_);
  Fxy::approximate(&f);
  List list(2);
  list[0]=wrap(f.x);
  list[1]=wrap(f.y);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
  // return Entropy::calculateEntropy(data_);
}

// [[Rcpp::export]]
DataFrame interpolateFunctionEvenBreaksInY(NumericVector x,NumericVector y,double numberBreaks){
  std::vector<double> x_=as<std::vector<double> > (x);
  std::vector<double> y_=as<std::vector<double> > (y);
  Fxy f=Fxy::createFunction(x_,y_);
  Fxy::interpolateDataInY(&f,numberBreaks);
  List list(2);
  list[0]=wrap(f.x);
  list[1]=wrap(f.y);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
  // return Entropy::calculateEntropy(data_);
}


// [[Rcpp::export]]
DataFrame getDerivative(NumericVector x,NumericVector y){
  std::vector<double> x_=as<std::vector<double> > (x);
  std::vector<double> y_=as<std::vector<double> > (y);
  Fxy f=Fxy::createFunction(x_,y_);
  Fxy d=Fxy::getDerivative(&f);
  List list(2);
  list[0]=wrap(d.x);
  list[1]=wrap(d.y);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
  // return Entropy::calculateEntropy(data_);
}
// [[Rcpp::export]]
DataFrame getIntegral(NumericVector x,NumericVector y){
  std::vector<double> x_=as<std::vector<double> > (x);
  std::vector<double> y_=as<std::vector<double> > (y);
  Fxy f=Fxy::createFunction(x_,y_);
  Fxy i=Fxy::getIntegral(&f);
  List list(2);
  list[0]=wrap(i.x);
  list[1]=wrap(i.y);

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");

  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
  // return Entropy::calculateEntropy(data_);
}

// [[Rcpp::export]]
double getMomentDistribution(NumericVector data,double n){
  std::vector<double> data_=as<std::vector<double> > (data);
  Distribution dis=Distribution::createDistribution(data_);
  double moment=Distribution::getMoment(&dis,n);
  return moment;
  // return Entropy::calculateEntropy(data_);
}

// [[Rcpp::export]]
void collapseRoundabouts(XPtr<DualExtendedGraph> deg){
  std::cout<<"This collapses the roundabout to a single point, use hyperConnectRoundabouts if you prefer to superconnect them without modifying the underlying graph";
  DualExtendedGraph::collapseRoundabouts(deg);

}


// [[Rcpp::export]]
XPtr< Grafo > collapseDoubleLanes(XPtr<DualExtendedGraph> deg){
  Grafo* G=new Grafo();
  DualExtendedGraph::collapseDoubleLanes(deg,G);
  Rcpp::XPtr< Grafo > p(G,true) ;
  return (p);
}
// [[Rcpp::export]]
XPtr< Grafo > collapseDoubleLanesFake(XPtr<DualExtendedGraph> deg){

  std::cout<<"I have forgotten what this function does, it seems to be irrelevant and removable";
DualExtendedGraph::simplify(deg);
    DualExtendedGraph::forcePlanarityPrimal(deg,Grafo::PLANARITY_PLANESWEEP);
    Grafo* dual=deg->getDualGraph();
    std::set<long> idLinksToRemoveA;
    for(long i=0;i<dual->links.size();i++){
        if(dual->links[i]->A()==dual->links[i]->B()){
            idLinksToRemoveA.insert(i);
        }
    }
    deg->getPrimalGraph()->removeLinks(idLinksToRemoveA);
    Grafo largestComponent;
    Grafo::getLargestComponent(deg->getPrimalGraph(),&largestComponent);

    deg->reset();
    // deg->softReset();
    DualExtendedGraph::addPrimal(deg,&largestComponent);
    Rcpp::XPtr< Grafo > p(deg->getPrimalGraph(),true) ;
 return (p);

}


// [[Rcpp::export]]
NumericVector diffuseFromSegmentsToSegments_angular(XPtr<DualExtendedGraph> deg,NumericVector valuesEdges,double d0,double cutoffValue){
std::vector<double> result;
std::vector<double> valuesEdges_=as<std::vector<double> >(valuesEdges);
 DualExtendedGraph::diffuseFromSegmentsToSegments_angular(deg,valuesEdges_,result,d0,cutoffValue);
 NumericVector result_=wrap(result);
 return result_;

}

// [[Rcpp::export]]
NumericVector diffuseFromSegmentsToSegments_metric(XPtr<DualExtendedGraph> deg,NumericVector valuesEdges,double d0,double cutoffValue){
std::vector<double> result;
std::vector<double> valuesEdges_=as<std::vector<double> >(valuesEdges);
 DualExtendedGraph::diffuseFromSegmentsToSegments_metric(deg,valuesEdges_,result,d0,cutoffValue);
 NumericVector result_=wrap(result);
 return result_;

}












// [[Rcpp::export]]
DataFrame readGeoASCII(String nameFile,double minValue){
  std::string separator=" ";
  std::cout<<"This code is using manually inserted values, recheck to make it general"<<'\n';
  std::ifstream file;
    bool abierto=TextFile::open(nameFile,file);
    std::vector<double> values;
    std::vector<double> xs;
    std::vector<double> ys;
    separator=" ";
    if (abierto)
    {
//        cout<<"dentro de leer";
        std::string linea;
        linea=TextFile::getLine(file);//skipping the names of variables
        linea=TextFile::getLine(file);//skipping the names of variables
        linea=TextFile::getLine(file);//skipping the names of variables
        linea=TextFile::getLine(file);//skipping the names of variables
        linea=TextFile::getLine(file);//skipping the names of variables
        linea=TextFile::getLine(file);//skipping the names of variables
        long ncols=141969;
        long nrows=60829;
        double xllcorner=-17619594.547443531454;
        double yllcorner=-6484970.538131510839;
        double cellsize=250;
        double xcurrent=xllcorner+cellsize/2.0;
        double ycurrent=yllcorner+cellsize/2.0+cellsize*nrows;
        long lineNum=0;
        xs.reserve(ncols*nrows);
        ys.reserve(ncols*nrows);
        values.reserve(ncols*nrows);
        while(!file.eof())
        {
            linea=TextFile::getLine(file);
            lineNum++;
            // if (linea.length()>0)
            // {
            //     const char * input;
            //     input=linea.c_str();
            //     double value=atof(input);
            //     values.push_back(value);
            // }
            std::vector<std::string> words=TextFile::extractWords(linea, separator);
            for(long i=0;i<words.size();i++){
                const char * input;
                input=words[i].c_str();
                double value=atof(input);
                if(value>=minValue){
                  xs.push_back(xcurrent);
                  ys.push_back(ycurrent);
                  values.push_back(value);
                }
                xcurrent+=cellsize;
            }
            ycurrent-=cellsize;
            xcurrent=xllcorner+cellsize/2.0;
            std::cout<<lineNum<<" / "<<nrows<<" size points found:"<<values.size()<<'\n';
        }

        TextFile::close(file);
    }
    List list(3);

    list[0]=(wrap(xs));
    list[1]=(wrap(ys));
    list[2]=(wrap(values));


  CharacterVector namevec;
  // for(long i=0;i<numberObjectsDataFrame;i++){
    namevec.push_back("x");
    namevec.push_back("y");
    namevec.push_back("value");
  // }




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}


// [[Rcpp::export]]
NumericVector transformClustersLinksToClustersNodes_Primal(XPtr<DualExtendedGraph> deg,NumericVector originalClustersOfEdges_R){
  std::vector<long> originalClustersOfEdges=Rcpp::as<std::vector<long> > (originalClustersOfEdges_R);
  std::vector<long> originalClustersNodes;
  originalClustersNodes.resize(deg->getPrimalGraph()->nodes.size(),-1);
  // std::cout<<originalClustersOfEdges.size()<<" "<<deg->getStructuralGraph()->links.size()<<" "<<originalClustersNodes.size()<<'\n';
  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
    // std::cout<<deg->getStructuralGraph()->links[i]->A()->id<<" "<<deg->getStructuralGraph()->links[i]->B()->id<<'\n';
    // std::cout<<i<<" ";
    originalClustersNodes[deg->getPrimalGraph()->links[i]->A()->id]=Functions::max(originalClustersNodes[deg->getPrimalGraph()->links[i]->A()->id],originalClustersOfEdges[i]);
    originalClustersNodes[deg->getPrimalGraph()->links[i]->B()->id]=Functions::max(originalClustersNodes[deg->getPrimalGraph()->links[i]->B()->id],originalClustersOfEdges[i]);
  }

// std::cout<<"A"<<'\n';


  return (wrap(originalClustersNodes));

}



// // [[Rcpp::export]]
// NumericVector transformClustersLinksToClustersNodes_Structural(XPtr<DualExtendedGraph> deg,NumericVector originalClustersOfEdges_R){
//   std::vector<long> originalClustersOfEdges=Rcpp::as<std::vector<long> > (originalClustersOfEdges_R);
//   std::vector<long> originalClustersNodes;
//   originalClustersNodes.resize(deg->getStructuralGraph()->nodes.size(),-1);
//   // std::cout<<originalClustersOfEdges.size()<<" "<<deg->getStructuralGraph()->links.size()<<" "<<originalClustersNodes.size()<<'\n';
//   for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
//     // std::cout<<deg->getStructuralGraph()->links[i]->A()->id<<" "<<deg->getStructuralGraph()->links[i]->B()->id<<'\n';
//     // std::cout<<i<<" ";
//     originalClustersNodes[deg->getStructuralGraph()->links[i]->A()->id]=Functions::max(originalClustersNodes[deg->getStructuralGraph()->links[i]->A()->id],originalClustersOfEdges[i]);
//     originalClustersNodes[deg->getStructuralGraph()->links[i]->B()->id]=Functions::max(originalClustersNodes[deg->getStructuralGraph()->links[i]->B()->id],originalClustersOfEdges[i]);
//   }

// // std::cout<<"A"<<'\n';


//   return (wrap(originalClustersNodes));

// }



// [[Rcpp::export]]
NumericVector transformClustersNodesToClustersLinks_Primal(XPtr<DualExtendedGraph> deg,NumericVector originalClustersNodes){
  std::vector<long> originalClustersOfEdges;
  originalClustersOfEdges.resize(deg->getStructuralGraph()->links.size(),-1);
  // std::cout<<originalClustersOfEdges.size()<<" "<<deg->getStructuralGraph()->links.size()<<" "<<originalClustersNodes.size()<<'\n';
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    // std::cout<<deg->getStructuralGraph()->links[i]->A()->id<<" "<<deg->getStructuralGraph()->links[i]->B()->id<<'\n';
    // std::cout<<i<<" ";
    for(long j=0;j<deg->getPrimalGraph()->nodes[i]->links.size();j++){
      if(originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->A()->id]==originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->B()->id]){
        originalClustersOfEdges[deg->getPrimalGraph()->nodes[i]->links[j]->id]=originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->A()->id];
      }else{
        originalClustersOfEdges[deg->getPrimalGraph()->nodes[i]->links[j]->id]=-1;
      }
    }
    // originalClustersNodes[deg->getStructuralGraph()->links[i]->A()->id]=Functions::max(originalClustersNodes[deg->getStructuralGraph()->links[i]->A()->id],originalClustersOfEdges[i]);
    // originalClustersNodes[deg->getStructuralGraph()->links[i]->B()->id]=Functions::max(originalClustersNodes[deg->getStructuralGraph()->links[i]->B()->id],originalClustersOfEdges[i]);
  }

// std::cout<<"A"<<'\n';


  return (wrap(originalClustersOfEdges));

}

// // [[Rcpp::export]]
// NumericVector transformClustersNodesToClustersLinks_Structural(XPtr<DualExtendedGraph> deg,NumericVector originalClustersNodes){
//   std::vector<long> originalClustersOfEdges;
//   originalClustersOfEdges.resize(deg->getStructuralGraph()->links.size(),-1);
//   // std::cout<<originalClustersOfEdges.size()<<" "<<deg->getStructuralGraph()->links.size()<<" "<<originalClustersNodes.size()<<'\n';
//   for(long i=0;i<deg->getStructuralGraph()->nodes.size();i++){
//     // std::cout<<deg->getStructuralGraph()->links[i]->A()->id<<" "<<deg->getStructuralGraph()->links[i]->B()->id<<'\n';
//     // std::cout<<i<<" ";
//     for(long j=0;j<deg->getStructuralGraph()->nodes[i]->links.size();j++){
//       if(originalClustersNodes[deg->getStructuralGraph()->nodes[i]->links[j]->A()->id]==originalClustersNodes[deg->getStructuralGraph()->nodes[i]->links[j]->B()->id]){
//         originalClustersOfEdges[deg->getStructuralGraph()->nodes[i]->links[j]->id]=originalClustersNodes[deg->getStructuralGraph()->nodes[i]->links[j]->A()->id];
//       }else{
//         originalClustersOfEdges[deg->getStructuralGraph()->nodes[i]->links[j]->id]=-1;
//       }
//     }
//     // originalClustersNodes[deg->getStructuralGraph()->links[i]->A()->id]=Functions::max(originalClustersNodes[deg->getStructuralGraph()->links[i]->A()->id],originalClustersOfEdges[i]);
//     // originalClustersNodes[deg->getStructuralGraph()->links[i]->B()->id]=Functions::max(originalClustersNodes[deg->getStructuralGraph()->links[i]->B()->id],originalClustersOfEdges[i]);
//   }

// // std::cout<<"A"<<'\n';


//   return (wrap(originalClustersOfEdges));

// }


// [[Rcpp::export]]
NumericVector expandClustersNotInPercolation(XPtr<DualExtendedGraph> deg,NumericVector originalClusterNodes_R,double distancePercolation,double maxSlopePopulation){

  // std::vector<long> originalClustersOfEdges=Rcpp::as<std::vector<long> > (originalClustersOfEdges_R);
  std::vector<long> originalClustersNodes=Rcpp::as<std::vector<long> > (originalClusterNodes_R);
  // originalClustersNodes.resize(deg->getPrimalGraph()->nodes.size(),-1);


  std::unordered_set<Nodo*> nodesToExpand;
  std::unordered_set<Nodo*> nodesToExpandLater;
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    long cluster=originalClustersNodes[i];
    if(cluster<0){
      // bool atLeastOneIsInCluster=false;
      std::vector<long> possibleOtherClusters;
      double max=-INFINITY;
      long indexMax=-1;
      for(long j=0;j<deg->getPrimalGraph()->nodes[i]->links.size();j++){
        if(deg->getPrimalGraph()->nodes[i]->links[j]->weight<=distancePercolation){
          double slope=Functions::abs(deg->getPrimalGraph()->nodes[i]->mass-deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass)/deg->getPrimalGraph()->nodes[i]->links[j]->weight;
          if(slope<=maxSlopePopulation){
            if(originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->id]>=0){
              // atLeastOneIsInCluster=true;
              possibleOtherClusters.push_back(originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->id]);
              if(deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass>max){
                max=deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass;
                indexMax=possibleOtherClusters.size()-1;
              }
              // if(Functions::abs(deg->getStructuralGraph()->nodes[i]->links[j]->A()->mass-))
            }
          }
        }
      }

      if(possibleOtherClusters.size()>0){
        // originalClustersNodes[i]=possibleOtherClusters[indexMax];
        nodesToExpand.insert(deg->getPrimalGraph()->nodes[i]);
      }else{
        nodesToExpandLater.insert(deg->getPrimalGraph()->nodes[i]);
      }
      possibleOtherClusters.clear();
    }

  }
  // std::cout<<"B"<<'\n';
  // std::cout<<nodesToExpand.size()<<" "<<nodesToExpandLater.size()<<'\n';

  // std::unordered_set<Nodo*> nodesToExpand;
  bool atLeastOneNodeAdded=false;
  while(nodesToExpand.size()>0){
    Nodo* node=*nodesToExpand.begin();
    nodesToExpand.erase(nodesToExpand.begin());
    long i=node->id;
    long cluster=originalClustersNodes[i];
    if(cluster<0){
      // bool atLeastOneIsInCluster=false;
      std::vector<long> possibleOtherClusters;
      double max=-INFINITY;
      long indexMax=-1;
      for(long j=0;j<node->links.size();j++){
        if(node->links[j]->weight<=distancePercolation){
          double slope=Functions::abs(deg->getPrimalGraph()->nodes[i]->mass-deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass)/deg->getPrimalGraph()->nodes[i]->links[j]->weight;
          if(slope<=maxSlopePopulation){
            if(originalClustersNodes[node->links[j]->getOtherNode(node)->id]>=0){
                // atLeastOneIsInCluster=true;
                      possibleOtherClusters.push_back(originalClustersNodes[node->links[j]->getOtherNode(node)->id]);
              if(node->links[j]->getOtherNode(node)->mass>max){
                max=node->links[j]->getOtherNode(node)->mass;
                indexMax=possibleOtherClusters.size()-1;
              }
              // if(Functions::abs(deg->getStructuralGraph()->nodes[i]->links[j]->A()->mass-))
            }
          }
        }
      }
      if(possibleOtherClusters.size()==1){
        originalClustersNodes[i]=possibleOtherClusters[0];
        atLeastOneNodeAdded=true;
      }else if(possibleOtherClusters.size()>1){
        originalClustersNodes[i]=possibleOtherClusters[indexMax];
        atLeastOneNodeAdded=true;
      }else{
        // nodesToExpand.insert(deg->getStructuralGraph()->nodes[i]);
      }
      possibleOtherClusters.clear();
    }
    std::unordered_set<Nodo*> nodesToExpandLaterB;
    if(nodesToExpand.size()==0){
      // std::cout<<"C"<<'\n';
      if(!atLeastOneNodeAdded){
        break;
      }
      atLeastOneNodeAdded=false;
      for(auto it:nodesToExpandLater){
          Nodo* node=it;
          long i=node->id;
          // nodesToExpandLater.erase(it);
          long cluster=originalClustersNodes[i];
          if(cluster<0){
            // bool atLeastOneIsInCluster=false;
            std::vector<long> possibleOtherClusters;
            double max=-INFINITY;
            long indexMax=-1;
            for(long j=0;j<deg->getPrimalGraph()->nodes[i]->links.size();j++){
              if(deg->getPrimalGraph()->nodes[i]->links[j]->weight<=distancePercolation){
                double slope=Functions::abs(deg->getPrimalGraph()->nodes[i]->mass-deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass)/deg->getPrimalGraph()->nodes[i]->links[j]->weight;
              if(slope<=maxSlopePopulation){
                 if(originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->id]>=0){
              // atLeastOneIsInCluster=true;
                    possibleOtherClusters.push_back(originalClustersNodes[deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->id]);
                    if(deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass>max){
                      max=deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->mass;
                      indexMax=possibleOtherClusters.size()-1;
                    }
                    // if(Functions::abs(deg->getStructuralGraph()->nodes[i]->links[j]->A()->mass-))
                  }
                }
              }
            }
            if(possibleOtherClusters.size()==1){
              // originalClustersNodes[i]=possibleOtherClusters[0];
              nodesToExpand.insert(deg->getPrimalGraph()->nodes[i]);
            }else if(possibleOtherClusters.size()>1){
              // originalClustersNodes[i]=possibleOtherClusters[indexMax];
              nodesToExpand.insert(deg->getPrimalGraph()->nodes[i]);
            }else{
              nodesToExpandLaterB.insert(deg->getPrimalGraph()->nodes[i]);
            }
          }

      }
      // std::cout<<"D"<<'\n';
      std::swap(nodesToExpandLater,nodesToExpandLaterB);
    }
  }


  return (wrap(originalClustersNodes));

}







// [[Rcpp::export]]
DataFrame percolationBasedOnVariationOfDensityOrMinimumSize(XPtr<DualExtendedGraph> deg,double distancePercolation,double massThreshold,double maxSlopePopulation){

  std::vector<long> originalClustersNodes;
  originalClustersNodes.resize(deg->getStructuralGraph()->nodes.size(),-1);

  std::vector<double> originalWeights;
  originalWeights.reserve(deg->getStructuralGraph()->links.size());
  for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
    originalWeights.push_back(deg->getStructuralGraph()->links[i]->weight);
  }
  // std::cout<<originalClustersOfEdges.size()<<" "<<deg->getStructuralGraph()->links.size()<<" "<<originalClustersNodes.size()<<'\n';
  for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
    double slope=Functions::abs(deg->getStructuralGraph()->links[i]->A()->mass-deg->getStructuralGraph()->links[i]->B()->mass)/originalWeights[i];
    double weightedSlope=(slope+1)/deg->getStructuralGraph()->links[i]->A()->mass/deg->getStructuralGraph()->links[i]->B()->mass;
    // if(originalWeights[i]<=distancePercolation&&Functions::min(deg->getStructuralGraph()->links[i]->A()->mass,deg->getStructuralGraph()->links[i]->B()->mass)>massThreshold){
    //   deg->getStructuralGraph()->links[i]->weight=1;
    // }else if (originalWeights[i]<=distancePercolation&&slope<=maxSlopePopulation){
    //   deg->getStructuralGraph()->links[i]->weight=1;
    // }else{
    //   deg->getStructuralGraph()->links[i]->weight=10;
    // }
    if(originalWeights[i]<=distancePercolation&&slope<weightedSlope){
      // deg->getStructuralGraph()->links[i]->weight=1;
    // }else if (originalWeights[i]<=distancePercolation&&slope<=maxSlopePopulation){
      deg->getStructuralGraph()->links[i]->weight=1;
    }else{
      deg->getStructuralGraph()->links[i]->weight=10;
    }

  }


  std::vector<long> colors;
  std::vector<double> sizes;
//    long maxColor;
  // std::cout<<"is primal structural? "<<DualExtendedGraph::isPrimalStructural(deg)<<'\n';
  DualExtendedGraph::metricPercolation(deg,2,colors,sizes);
  out("Finished getting colors");
  std::vector<double> idA,idB,weights,colors_,sizes_;


for(long i=0;i<deg->getStructuralGraph()->links.size();i++){
    deg->getStructuralGraph()->links[i]->weight=originalWeights[i];
  }


  idA.resize(deg->getPrimalGraph()->links.size());
  idB.resize(deg->getPrimalGraph()->links.size());
  weights.resize(deg->getPrimalGraph()->links.size());
  colors_.resize(deg->getPrimalGraph()->links.size());
  sizes_.resize(deg->getPrimalGraph()->links.size());


  for(long i=0;i<deg->getPrimalGraph()->links.size();i++){

    idA[i]=deg->getPrimalGraph()->links[i]->A()->id;
    idB[i]=deg->getPrimalGraph()->links[i]->B()->id;
    weights[i]=deg->getPrimalGraph()->links[i]->weight;
            // colors_[i]=colors[deg->getStructuralGraph()->links[i]->a->id];
            // if(colors[deg->getStructuralGraph()->links[i]->a->id]>=0){
            //   sizes_[i]=sizes[colors[deg->getStructuralGraph()->links[i]->a->id]];
            // }else{
            //   sizes_[i]=0;
            // }
    colors_[i]=colors[i];
    if(colors[i]>=0){
      sizes_[i]=sizes[colors[i]];
    }else{
      sizes_[i]=0;
    }




  }

  std::vector<std::vector<double> > result;
  result.resize(5);
  result[0]=idA;
  result[1]=idB;
  result[2]=weights;
  result[3]=colors_;
  result[4]=sizes_;





  long numberObjectsDataFrame=5;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("idA");
  namevec.push_back("idB");
  namevec.push_back("weight");
  namevec.push_back("idCluster");
  namevec.push_back("size");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;



}






// [[Rcpp::export]]
DataFrame projectPeopleToNodes(XPtr<DualExtendedGraph> deg,double widthPixel,double scale){
double totalMass=0;
for(long i=0;i<deg->getStructuralGraph()->nodes.size();i++){
  totalMass+=deg->getStructuralGraph()->nodes[i]->mass;
}

std::vector<double> ids;
std::vector<double> xs;
std::vector<double> ys;

ids.reserve(totalMass/scale);
xs.reserve(totalMass/scale);
ys.reserve(totalMass/scale);

for(long i=0;i<deg->getStructuralGraph()->nodes.size();i++){
    double mass=deg->getStructuralGraph()->nodes[i]->mass;
    double nn=mass/scale;
    double xO=deg->getStructuralGraph()->nodes[i]->location.x;
    double yO=deg->getStructuralGraph()->nodes[i]->location.y;
    for(long j=0;j<nn;j++){
      double x=Functions::runiform(xO-widthPixel/2.0,xO+widthPixel/2.0);
      double y=Functions::runiform(yO-widthPixel/2.0,yO+widthPixel/2.0);
      ids.push_back(ids.size());
      xs.push_back(x);
      ys.push_back(y);
    }
  }



  std::vector<std::vector<double> > result;
  result.resize(3);
  result[0]=ids;
  result[1]=xs;
  result[2]=ys;





  long numberObjectsDataFrame=3;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("id");
  namevec.push_back("x");
  namevec.push_back("y");


  list.attr("names") = namevec;
  DataFrame df(list);
  return df;



}



// [[Rcpp::export]]
NumericVector passMeanHIToNodes(XPtr<DualExtendedGraph> deg,NumericVector hi){
std::vector<double> hiNodes;
hiNodes.reserve(deg->getStructuralGraph()->nodes.size());
for(long i=0;i<deg->getStructuralGraph()->nodes.size();i++){
  double hiTemp=0;
  for(long j=0;j<deg->getStructuralGraph()->nodes[i]->links.size();j++){
    hiTemp+=hi[deg->getStructuralGraph()->nodes[i]->links[j]->id];
  }
  hiTemp/=(double)(deg->getStructuralGraph()->nodes[i]->links.size());
  hiNodes.push_back(hiTemp);
}
return (wrap(hiNodes));
}

// [[Rcpp::export]]
NumericVector passMaxHIToNodes(XPtr<DualExtendedGraph> deg,NumericVector hi){
std::vector<double> hiNodes;
hiNodes.reserve(deg->getStructuralGraph()->nodes.size());
for(long i=0;i<deg->getStructuralGraph()->nodes.size();i++){
  double hiTemp=0;
  for(long j=0;j<deg->getStructuralGraph()->nodes[i]->links.size();j++){
    hiTemp=Functions::max(hiTemp,hi[deg->getStructuralGraph()->nodes[i]->links[j]->id]);
  }
  // hiTemp/=(double)(deg->getStructuralGraph()->nodes[i]->links.size());
  hiNodes.push_back(hiTemp);
}
return (wrap(hiNodes));
}


// [[Rcpp::export]]
double calculateAreaPolygon(XPtr<Grafo> G){
  double area=GeometryGraph::calculateAreaPolygon(G);
  return area;
}




// [[Rcpp::export]]
NumericVector calculateAreaOcuppiedByClusters(XPtr<DualExtendedGraph> deg,double limitPercolation){
  std::vector<double> areas;
  DualExtendedGraph::calculateAreasClustersInParallel(deg,limitPercolation,areas,4);
  return wrap(areas);
}


// [[Rcpp::export]]
NumericVector calculateFractalDimensionOcuppiedByClusters(XPtr<DualExtendedGraph> deg,double limitPercolation){
  std::vector<double> fd;
  DualExtendedGraph::calculateFractalDimensionClustersInParallel(deg,limitPercolation,fd,4);
  return wrap(fd);
}









// [[Rcpp::export]]
DataFrame getThresholdsAndEntropyForMetricPercolation(XPtr<DualExtendedGraph> deg,long definition){
  // std::vector<double> fd;
  std::tuple<std::vector<double>,std::vector<double> > result_=DualExtendedGraph::getThresholdsAndEntropyForMetricPercolation(deg,definition);
  // return wrap(fd);


  std::vector<std::vector<double> > result;
  result.resize(2);
  result[0]=std::get<0>(result_);
  result[1]=std::get<1>(result_);
  // result[2]=ys;





  long numberObjectsDataFrame=2;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("threshold");
  namevec.push_back("entropy");



  list.attr("names") = namevec;
  DataFrame df(list);
  return df;


}





// [[Rcpp::export]]
DataFrame getThresholdsAndEntropyForMetricPercolation_UsingMassNodes(XPtr<DualExtendedGraph> deg){
  // std::vector<double> fd;
  std::tuple<std::vector<double>,std::vector<double> > result_=DualExtendedGraph::getThresholdsAndEntropyForMetricPercolation_UsingMassNodes(deg,100);
  // return wrap(fd);


  std::vector<std::vector<double> > result;
  result.resize(2);
  result[0]=std::get<0>(result_);
  result[1]=std::get<1>(result_);
  // result[2]=ys;





  long numberObjectsDataFrame=2;

  List list(numberObjectsDataFrame);
  for(long i=0;i<numberObjectsDataFrame;i++){
    list[i]=(wrap(result[i]));
  }

  CharacterVector namevec;
  namevec.push_back("threshold");
  namevec.push_back("entropy");



  list.attr("names") = namevec;
  DataFrame df(list);
  return df;


}




// // [[Rcpp::export]]
// XPtr<Grafo> compressCitiesUsingStructure(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){
//   std::vector<double> masses;
//   masses.reserve(deg->getPrimalGraph()->nodes.size());
//   std::vector<long> idClusters;
//   idClusters.reserve(deg->getPrimalGraph()->nodes.size());
//   for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
//     masses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
//     idClusters.push_back(i);
//   }
//   std::vector<long> orderedIndexes=Functions::getIndexesOfOrderedValues(masses,true);
//   long numberCities=deg->getPrimalGraph()->nodes.size();
//   std::vector<bool> linkCollapsed;
//   linkCollapsed.resize(deg->getPrimalGraph()->links.size(),false);


//   long current=0;
//   while(numberCities>100&current<orderedIndexes.size()){
//     double max=-INFINITY;
//     long indexMax=-1;
//     Nodo* node=deg->getPrimalGraph()->nodes[orderedIndexes[current]];
//     for(long i=0;i<node->links.size();i++){
//       if(!linkCollapsed[node->links[i]->id]){
//         if(structureWeights[node->links[i]->id]>max){
//           max=structureWeights[node->links[i]->id];
//           indexMax=i;
//         }
//       }
//     }
//     if(indexMax!=-1){
//       long newCluster=idClusters[node->links[indexMax]->getOtherNode(node)->id];
//       linkCollapsed[node->links[indexMax]->id]=true;
//       if(idClusters[node->id]!=newCluster){
//         numberCities--;
//       }
//       idClusters[node->id]=newCluster;


//     }
//     current++;

//   }
//   // Grafo* G=new Grafo();
//    Grafo* G=new Grafo();
//  // Grafo::create(G,ncol_,coordinates_,directed);
//    Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),G,idClusters,true);

//  Rcpp::XPtr< Grafo > p(G,true) ;
//  return p;

// }



// [[Rcpp::export]]
NumericVector compressCitiesUsingStructure(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){
  // XPtr<Grafo>  compressCitiesUsingStructure(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){
  std::vector<double> masses;
  masses.reserve(deg->getPrimalGraph()->nodes.size());
  std::vector<long> idClusters;
  idClusters.reserve(deg->getPrimalGraph()->nodes.size());
  std::unordered_map<long,std::set<long> > idNodesPerIdCluster;
  std::unordered_map<long,double> massesPerCluster;
  std::unordered_map<long,Point2d> weightedCoordinatesPerCluster;
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    masses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
    idClusters.push_back(i);
    idNodesPerIdCluster[i].insert(i);
    weightedCoordinatesPerCluster[i].x=deg->getPrimalGraph()->nodes[i]->location.x*deg->getPrimalGraph()->nodes[i]->mass;
    weightedCoordinatesPerCluster[i].y=deg->getPrimalGraph()->nodes[i]->location.y*deg->getPrimalGraph()->nodes[i]->mass;
    massesPerCluster[i]=deg->getPrimalGraph()->nodes[i]->mass;
  }
  std::vector<long> orderedIndexes=Functions::getIndexesOfOrderedValues(masses,true);
  long numberCities=deg->getPrimalGraph()->nodes.size();
  std::vector<bool> linkCollapsed;
  linkCollapsed.resize(deg->getPrimalGraph()->links.size(),false);



  long current=0;
  while(current<orderedIndexes.size()){
    double max=-INFINITY;
    long indexMax=-1;
    Nodo* node=deg->getPrimalGraph()->nodes[orderedIndexes[current]];
    for(long i=0;i<node->links.size();i++){
      // if(!linkCollapsed[node->links[i]->id]){
        long newCluster=idClusters[node->links[i]->getOtherNode(node)->id];
        Point2d centroidNewCluster;
        centroidNewCluster.x=weightedCoordinatesPerCluster[newCluster].x/massesPerCluster[newCluster];
        centroidNewCluster.y=weightedCoordinatesPerCluster[newCluster].y/massesPerCluster[newCluster];
        long oldCluster=idClusters[node->id];
        Point2d centroidOldCluster;
        centroidOldCluster.x=weightedCoordinatesPerCluster[oldCluster].x/massesPerCluster[oldCluster];
        centroidOldCluster.y=weightedCoordinatesPerCluster[oldCluster].y/massesPerCluster[oldCluster];
        double distance=Functions::getDistance(centroidOldCluster,centroidNewCluster);

        // if(structureWeights[node->links[i]->id]>max&&oldCluster!=newCluster){
        if(structureWeights[node->links[i]->id]>max){
          max=structureWeights[node->links[i]->id];
          indexMax=i;
        }
      // }
    }
    if(indexMax!=-1){
      long newCluster=idClusters[node->links[indexMax]->getOtherNode(node)->id];
      linkCollapsed[node->links[indexMax]->id]=true;
      long oldCluster=idClusters[node->id];
      if(oldCluster!=newCluster){
        numberCities--;
      //   std::cout<<numberCities<<'\n';
      }
      for(auto it:idNodesPerIdCluster[oldCluster]){
        idClusters[it]=newCluster;
        idNodesPerIdCluster[newCluster].insert(it);
        massesPerCluster[newCluster]+=masses[it];
        weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
        weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      }
      weightedCoordinatesPerCluster[oldCluster].x=0;
      weightedCoordinatesPerCluster[oldCluster].y=0;
      massesPerCluster[oldCluster]=0;
      idNodesPerIdCluster[oldCluster].clear();
      // idClusters[node->id]=newCluster;
      // std::vector<long> uniqueIds=Functions::unique(idClusters);
      // numberCities=uniqueIds.size();


    }
    current++;

  }

 //   Grafo* G=new Grafo();

 //   Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),G,idClusters,true);

 // Rcpp::XPtr< Grafo > p(G,true) ;
 // return p;

 return wrap(idClusters);

}






// double compressCitiesUsingStructure_stopLowerNormalisedEntropy_getMaxEntropy(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){
//   // XPtr<Grafo>  compressCitiesUsingStructure(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){
//   std::vector<double> masses;
//   masses.reserve(deg->getPrimalGraph()->nodes.size());
//   std::vector<long> idClusters;
//   idClusters.reserve(deg->getPrimalGraph()->nodes.size());
//   std::unordered_map<long,std::set<long> > idNodesPerIdCluster;
//   std::unordered_map<long,double> massesPerCluster;
//   std::unordered_map<long,Point2d> weightedCoordinatesPerCluster;
//   std::vector<double> massesLinks;
//   massesLinks.reserve(structureWeights.size());
//   // std::cout<<"A"<<'\n';
//   for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
//     masses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
//     idClusters.push_back(i);
//     idNodesPerIdCluster[i].insert(i);
//     weightedCoordinatesPerCluster[i].x=deg->getPrimalGraph()->nodes[i]->location.x*deg->getPrimalGraph()->nodes[i]->mass;
//     weightedCoordinatesPerCluster[i].y=deg->getPrimalGraph()->nodes[i]->location.y*deg->getPrimalGraph()->nodes[i]->mass;
//     massesPerCluster[i]=deg->getPrimalGraph()->nodes[i]->mass;
//   }
//   // std::cout<<"B"<<'\n';
//   for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
//     double weight=structureWeights[i];
//     double massA=deg->getPrimalGraph()->links[i]->A()->mass;
//     double massB=deg->getPrimalGraph()->links[i]->B()->mass;
//     massesLinks.push_back(weight/massA/massB);
//   }
//   // std::cout<<"C"<<'\n';

//   std::tuple<double,double> entropyInit_pair=Entropy::calculateDiscreteEntropyAreas(masses);
//   double entropyInit_norm=std::get<0>(entropyInit_pair)/log(std::get<1>(entropyInit_pair));

//   std::vector<long> orderedIndexes=Functions::getIndexesOfOrderedValues(massesLinks,false);
//   // long numberCities=deg->getPrimalGraph()->nodes.size();
//   // std::vector<bool> linkCollapsed;
//   // linkCollapsed.resize(deg->getPrimalGraph()->links.size(),false);


//   std::tuple<double,double> entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(masses);
//   double entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));
//   long current=0;

//   // std::cout<< entropyInit_norm<<'\n';
//   double maxEnt=-INFINITY;
//   while(entropyCurrent_norm>=entropyInit_norm&&current<orderedIndexes.size()){
//     // std::cout<< entropyInit_norm<<" <= "<<entropyCurrent_norm<<'\n';
//     if(entropyCurrent_norm>maxEnt){
//       maxEnt=entropyCurrent_norm;
//     }
//     // double max=-INFINITY;
//     // long indexMax=-1;
//     Link* link=deg->getPrimalGraph()->links[orderedIndexes[current]];
//     Nodo* nodeA=link->A();
//     Nodo* nodeB=link->B();
//     long newCluster;
//     long oldCluster;
//     Nodo* node;
//     if(nodeA->mass>nodeB->mass){
//       newCluster=idClusters[nodeA->id];
//       node=nodeB;
//       oldCluster=idClusters[nodeB->id];
//     }else{
//       newCluster=idClusters[nodeB->id];
//       node=nodeA;
//       oldCluster=idClusters[nodeA->id];
//     }
//     // for(long i=0;i<node->links.size();i++){
//     //   // if(!linkCollapsed[node->links[i]->id]){
//     //     long newCluster=idClusters[node->links[i]->getOtherNode(node)->id];
//     //     Point2d centroidNewCluster;
//     //     centroidNewCluster.x=weightedCoordinatesPerCluster[newCluster].x/massesPerCluster[newCluster];
//     //     centroidNewCluster.y=weightedCoordinatesPerCluster[newCluster].y/massesPerCluster[newCluster];
//     //     long oldCluster=idClusters[node->id];
//     //     Point2d centroidOldCluster;
//     //     centroidOldCluster.x=weightedCoordinatesPerCluster[oldCluster].x/massesPerCluster[oldCluster];
//     //     centroidOldCluster.y=weightedCoordinatesPerCluster[oldCluster].y/massesPerCluster[oldCluster];
//     //     double distance=Functions::getDistance(centroidOldCluster,centroidNewCluster);

//     //     // if(structureWeights[node->links[i]->id]>max&&oldCluster!=newCluster){
//     //     if(structureWeights[node->links[i]->id]>max){
//     //       max=structureWeights[node->links[i]->id];
//     //       indexMax=i;
//     //     }
//     //   // }
//     // }
//     // if(indexMax!=-1){
//     // long newCluster=idClusters[node->links[indexMax]->getOtherNode(node)->id];
//     // linkCollapsed[node->links[indexMax]->id]=true;
//     // long oldCluster=idClusters[node->id];
//     // if(oldCluster!=newCluster){
//     //   numberCities--;
//     // //   std::cout<<numberCities<<'\n';
//     // }
//     for(auto it:idNodesPerIdCluster[oldCluster]){
//       idClusters[it]=newCluster;
//       idNodesPerIdCluster[newCluster].insert(it);
//       massesPerCluster[newCluster]+=masses[it];
//       weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
//       weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

//     }
//     weightedCoordinatesPerCluster[oldCluster].x=0;
//     weightedCoordinatesPerCluster[oldCluster].y=0;
//     massesPerCluster[oldCluster]=0;
//     idNodesPerIdCluster[oldCluster].clear();

//     std::vector<double> massesCurrent;
//     massesCurrent.reserve(massesPerCluster.size());
//     for(auto it:massesPerCluster){
//       massesCurrent.push_back(it.second);
//     }

//     entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(massesCurrent);
//     entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

//     // idClusters[node->id]=newCluster;
//     // std::vector<long> uniqueIds=Functions::unique(idClusters);
//     // numberCities=uniqueIds.size();


//     // }
//     current++;

//   }

//   //   Grafo* G=new Grafo();

//   //   Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),G,idClusters,true);

//   // Rcpp::XPtr< Grafo > p(G,true) ;
//   // return p;

//   return maxEnt;

// }








// [[Rcpp::export]]
NumericVector compressCitiesUsingStructure_stopLowerNormalisedEntropy(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){
  // XPtr<Grafo>  compressCitiesUsingStructure(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){

double widthBin=1;

  std::vector<double> masses;
  masses.reserve(deg->getPrimalGraph()->nodes.size());
  std::vector<long> idClusters;
  idClusters.reserve(deg->getPrimalGraph()->nodes.size());
  std::unordered_map<long,std::set<long> > idNodesPerIdCluster;
  // std::unordered_map<long,double> massesPerCluster;
  // std::unordered_map<long,Point2d> weightedCoordinatesPerCluster;
std::vector<double> massesLinks;
massesLinks.reserve(structureWeights.size());
// std::unordered_map<long,long> idsPerIdCluster;
std::vector<double> currentMasses;
currentMasses.reserve(deg->getPrimalGraph()->nodes.size());
std::unordered_map<double,long> n_perMass;
std::unordered_map<double,long> mass_PerMass;
double n=0;
double totalMass=0;

// double maxEnt=compressCitiesUsingStructure_stopLowerNormalisedEntropy_getMaxEntropy(deg,structureWeights);
// std::cout<<"A"<<'\n';
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){

    masses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
    long currentNOfThisMass=n_perMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)];
    if(currentNOfThisMass==0){
      n++;
    }
    n_perMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)]++;
    idClusters.push_back(i);
    idNodesPerIdCluster[i].insert(i);
    // weightedCoordinatesPerCluster[i].x=deg->getPrimalGraph()->nodes[i]->location.x*deg->getPrimalGraph()->nodes[i]->mass;
    // weightedCoordinatesPerCluster[i].y=deg->getPrimalGraph()->nodes[i]->location.y*deg->getPrimalGraph()->nodes[i]->mass;
    // massesPerCluster[i]=deg->getPrimalGraph()->nodes[i]->mass;
    currentMasses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
    mass_PerMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)]+=deg->getPrimalGraph()->nodes[i]->mass;
    totalMass+=deg->getPrimalGraph()->nodes[i]->mass;
  }
// std::cout<<"B"<<'\n';
for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
  double weight=structureWeights[i];
  double massA=deg->getPrimalGraph()->links[i]->A()->mass;
  double massB=deg->getPrimalGraph()->links[i]->B()->mass;
  // massesLinks.push_back(weight/Functions::min(massA,massB));
  // massesLinks.push_back(weight);
  massesLinks.push_back(weight*Functions::max(massA,massB));
  // massesLinks.push_back(Functions::max(massA,massB));
  // massesLinks.push_back(Functions::runiform(0,100));

}
// std::cout<<"C"<<'\n';

  std::tuple<double,double> entropyInit_pair=Entropy::calculateDiscreteEntropyAreas(masses);
  double entropyInit_norm=std::get<0>(entropyInit_pair)/log(std::get<1>(entropyInit_pair));

  std::vector<long> orderedIndexes=Functions::getIndexesOfOrderedValues(massesLinks,false);
  // long numberCities=deg->getPrimalGraph()->nodes.size();
  // std::vector<bool> linkCollapsed;
  // linkCollapsed.resize(deg->getPrimalGraph()->links.size(),false);


  std::tuple<double,double> entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(masses);
  double entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));
  long current=0;
double entropy=std::get<0>(entropyCurrent_pair);
n=std::get<1>(entropyCurrent_pair);
  // std::cout<< entropyInit_norm<<'\n';
  bool stop=false;
  while(!stop&&current<orderedIndexes.size()){
    if(entropyCurrent_norm>=entropyInit_norm){
      // stop=true;
    }else{
      // stop=true;
    }
    if(current>1000){
      // stop=true;
    }
    // std::cout<< entropyInit_norm<<" <= "<<entropyCurrent_norm<<'\n';
    // double max=-INFINITY;
    // long indexMax=-1;
    Link* link=deg->getPrimalGraph()->links[orderedIndexes[current]];
    Nodo* nodeA=link->A();
    Nodo* nodeB=link->B();
    long newCluster;
    long oldCluster;
    Nodo* node;
    if(currentMasses[idClusters[nodeA->id]]>currentMasses[idClusters[nodeB->id]]){
      newCluster=idClusters[nodeA->id];
      node=nodeB;
      oldCluster=idClusters[nodeB->id];
    }else{
      newCluster=idClusters[nodeB->id];
      node=nodeA;
      oldCluster=idClusters[nodeA->id];
    }

    if(oldCluster!=newCluster){
    // for(long i=0;i<node->links.size();i++){
    //   // if(!linkCollapsed[node->links[i]->id]){
    //     long newCluster=idClusters[node->links[i]->getOtherNode(node)->id];
    //     Point2d centroidNewCluster;
    //     centroidNewCluster.x=weightedCoordinatesPerCluster[newCluster].x/massesPerCluster[newCluster];
    //     centroidNewCluster.y=weightedCoordinatesPerCluster[newCluster].y/massesPerCluster[newCluster];
    //     long oldCluster=idClusters[node->id];
    //     Point2d centroidOldCluster;
    //     centroidOldCluster.x=weightedCoordinatesPerCluster[oldCluster].x/massesPerCluster[oldCluster];
    //     centroidOldCluster.y=weightedCoordinatesPerCluster[oldCluster].y/massesPerCluster[oldCluster];
    //     double distance=Functions::getDistance(centroidOldCluster,centroidNewCluster);

    //     // if(structureWeights[node->links[i]->id]>max&&oldCluster!=newCluster){
    //     if(structureWeights[node->links[i]->id]>max){
    //       max=structureWeights[node->links[i]->id];
    //       indexMax=i;
    //     }
    //   // }
    // }
    // if(indexMax!=-1){
      // long newCluster=idClusters[node->links[indexMax]->getOtherNode(node)->id];
      // linkCollapsed[node->links[indexMax]->id]=true;
      // long oldCluster=idClusters[node->id];
      // if(oldCluster!=newCluster){
      //   numberCities--;
      // //   std::cout<<numberCities<<'\n';
      // }

      // std::vector<long> idsForRecovery;
      // idsForRecovery.reserve(idNodesPerIdCluster[oldCluster].size());






    // double massToAdd=0;
      // for(auto it:idNodesPerIdCluster[oldCluster]){
      //   // idsForRecovery.push_back(it);
      //   // idClusters[it]=newCluster;
      //   // idNodesPerIdCluster[newCluster].insert(it);
      //   massToAdd+=masses[it];
      //   // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
      //   // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      // }
      double pNew_prev=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      double pSum_prev=mass_PerMass[std::floor((currentMasses[newCluster]+currentMasses[oldCluster])/widthBin)]/totalMass;
      double pOld_prev=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;

double massA=currentMasses[newCluster];
double massB=currentMasses[oldCluster];
      mass_PerMass[std::floor(massA/widthBin)]-=massA;
      mass_PerMass[std::floor(massB/widthBin)]-=massB;
      if(mass_PerMass[std::floor((massA)/widthBin)]<0){
        std::cout<<"A "<<mass_PerMass[std::floor((massA)/widthBin)]<<" "<<massA<<" "<<std::floor((massA)/widthBin)<<'\n';
        mass_PerMass[std::floor((massA)/widthBin)]=0;
      }
      if(mass_PerMass[std::floor((massB)/widthBin)]<0){
        std::cout<<"B "<<mass_PerMass[std::floor((massB)/widthBin)]<<'\n';
        mass_PerMass[std::floor((massB)/widthBin)]=0;
      }
      mass_PerMass[std::floor((massA+massB)/widthBin)]+=massA+massB;

      double pNew_post=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      double pSum_post=mass_PerMass[std::floor((currentMasses[newCluster]/widthBin)+currentMasses[oldCluster])]/totalMass;
      double pOld_post=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;
      // double pOld_prev2=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;

      // n--;
      long currentNOfNewClusterMass=n_perMass[std::floor(currentMasses[newCluster]/widthBin)];
      long currentNOfOldClusterMass=n_perMass[std::floor(currentMasses[oldCluster]/widthBin)];
      long n_prev=n;

    if(currentNOfNewClusterMass==1){
      n--;
    }
    if(currentNOfOldClusterMass==1){
      n--;
    }
    n_perMass[std::floor(currentMasses[newCluster]/widthBin)]--;
    currentMasses[newCluster]+=currentMasses[oldCluster];
      // weightedCoordinatesPerCluster[oldCluster].x=0;
      // weightedCoordinatesPerCluster[oldCluster].y=0;


if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==0){
      n++;
    }
    n_perMass[std::floor(currentMasses[newCluster]/widthBin)]++;
    n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]--;
    currentMasses[oldCluster]=0;
    // double pNew_post=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      // double pOld_post=currentMasses[oldCluster]/totalMass;
    // double pOld_post=0;
      // idNodesPerIdCluster[oldCluster].clear();

      // std::vector<double> massesCurrent;
      // massesCurrent.reserve(massesPerCluster.size());
      // for(auto it:massesPerCluster){
      //   massesCurrent.push_back(it.second);
      // }
      double prev_entropy=entropy;
      double prev_entropy_norm=entropyCurrent_norm;


      entropy=-entropy;
      double entNewPrev=pNew_prev*log(pNew_prev);
      double entSumPrev=pSum_prev*log(pSum_prev);
      double entOldPrev=pOld_prev*log(pOld_prev);
      if(pNew_prev<=0){
        entNewPrev=0;
        // std::cout<<"weirdA"<<'\n';
      }
      if(pSum_prev<=0){
        entSumPrev=0;
        // std::cout<<"weirdA"<<'\n';
      }
      if(pOld_prev<=0){
        entOldPrev=0;
        // std::cout<<"weirdB"<<'\n';
      }
      entropy-=entNewPrev+entOldPrev+entSumPrev;
      double entNewPost=pNew_post*log(pNew_post);
      double entSumPost=pSum_post*log(pSum_post);
      double entOldPost=pOld_post*log(pOld_post);
      if(pNew_post<=0){
        entNewPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      if(pSum_post<=0){
        entSumPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      if(pOld_post<=0){
        entOldPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      entropy+=entNewPost+entOldPost+entSumPost;
      entropy=-entropy;
      entropyCurrent_norm=entropy/log(n);


      // entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(currentMasses);
      // // std::cout<<pNew_prev<<" "<<pNew_post<<" "<<pOld_prev<<" "<<pOld_post<<'\n';
      // // if(Functions::abs(entropy-std::get<0>(entropyCurrent_pair))>.00001||n!=std::get<1>(entropyCurrent_pair)){
      //   // std::cout<<current<<" expected "<<entropy<<" "<<n<<" real "<<std::get<0>(entropyCurrent_pair)<<" "<<std::get<1>(entropyCurrent_pair)<<'\n';
      //   // stop=true;
      // // }
      // entropy=std::get<0>(entropyCurrent_pair);
      // n=std::get<1>(entropyCurrent_pair);
      // entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

      if((prev_entropy_norm-entropyCurrent_norm)>0){
        n_perMass[std::floor(currentMasses[newCluster]/widthBin)]--;
        if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==0){
          n--;
        }
        for(auto it:idNodesPerIdCluster[oldCluster]){

          // idClusters[it]=oldCluster;
          // auto it2=idNodesPerIdCluster[newCluster].find(it);
          // idNodesPerIdCluster[new]
          // idNodesClusters[oldCluster].insert(idsForRecovery[j]);
          currentMasses[newCluster]-=masses[it];
          currentMasses[oldCluster]+=masses[it];
          // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
          // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];
        }

        mass_PerMass[std::floor(massA/widthBin)]+=massA;
      mass_PerMass[std::floor(massB/widthBin)]+=massB;
      mass_PerMass[std::floor((massA+massB)/widthBin)]-=massA+massB;
      if(mass_PerMass[std::floor((massA+massB)/widthBin)]<0){
        std::cout<<mass_PerMass[std::floor((massA+massB)/widthBin)]<<'\n';
        mass_PerMass[std::floor((massA+massB)/widthBin)]=0;
      }

        n_perMass[std::floor(currentMasses[newCluster]/widthBin)]++;
        n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]++;
        if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==1){
          n++;
        }
        if(n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]==1){
          n++;
        }
        n=n_prev;
        // n++;
        entropy=prev_entropy;
        entropyCurrent_norm=entropy/log(n);
        // entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(currentMasses);

        // entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

      }else{
        // currentMasses[oldCluster]=0;
        for(auto it:idNodesPerIdCluster[oldCluster]){
        // idsForRecovery.push_back(it);
        idClusters[it]=newCluster;
        idNodesPerIdCluster[newCluster].insert(it);
        // currentMasses[newCluster]+=masses[it];
        // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
        // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      }
        idNodesPerIdCluster[oldCluster].clear();
      }

      // idClusters[node->id]=newCluster;
      // std::vector<long> uniqueIds=Functions::unique(idClusters);
      // numberCities=uniqueIds.size();

}
    // }
    current++;

  }

 //   Grafo* G=new Grafo();

 //   Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),G,idClusters,true);

 // Rcpp::XPtr< Grafo > p(G,true) ;
 // return p;

 return wrap(idClusters);

}









void compressCitiesUsingStructure_stopLowerNormalisedEntropy_hillClimbForGA(XPtr<DualExtendedGraph> deg,std::vector<double>& ADN){
  // XPtr<Grafo>  compressCitiesUsingStructure(XPtr<DualExtendedGraph> deg,NumericVector structureWeights){

// double widthBin=141;

  std::vector<double> masses;
  masses.reserve(deg->getPrimalGraph()->nodes.size());
  std::vector<long> idClusters;
  idClusters.reserve(deg->getPrimalGraph()->nodes.size());
  std::unordered_map<long,std::set<long> > idNodesPerIdCluster;
  // std::unordered_map<long,double> massesPerCluster;
  // std::unordered_map<long,Point2d> weightedCoordinatesPerCluster;
std::vector<double> massesLinks;
massesLinks.reserve(deg->getPrimalGraph()->links.size());
// std::unordered_map<long,long> idsPerIdCluster;
std::vector<double> currentMasses;
currentMasses.reserve(deg->getPrimalGraph()->nodes.size());
std::unordered_map<double,long> n_perMass;
std::unordered_map<double,long> mass_PerMass;
double n=0;
double totalMass=0;
double maxSample=0;
double minSample=INFINITY;
double nTemp=deg->getPrimalGraph()->nodes.size();
for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
  if(maxSample<deg->getPrimalGraph()->nodes[i]->mass){
    maxSample=deg->getPrimalGraph()->nodes[i]->mass;
  }
  if(minSample>deg->getPrimalGraph()->nodes[i]->mass){
    minSample=deg->getPrimalGraph()->nodes[i]->mass;
  }
}
double widthBin=(maxSample-minSample)/sqrt(nTemp);

DualExtendedGraph::setPrimalAsStructuralGraph(deg);


// for(long j=0;j<numberLinks;j++){
//     deg->getPrimalGraph()->links[j]->weight=ADN;
//   }
//   std::vector<long> colors;
//   std::vector<double> sizes;
//   DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,0.5,colors,sizes);

//   long numClusters=sizes.size();
//   long current=numClusters;
//    std::vector<long> colorsNodes;
//   Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
//   std::vector<double> sizesNodes;
//   for(long i=0;i<colorsNodes.size();i++){
//     if(colorsNodes[i]==-1){
//       colorsNodes[i]=current;
//       current++;
//     }
//   }





// double maxEnt=compressCitiesUsingStructure_stopLowerNormalisedEntropy_getMaxEntropy(deg,structureWeights);
// std::cout<<"A"<<'\n';
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){

    masses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
    long currentNOfThisMass=n_perMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)];
    if(currentNOfThisMass==0){
      n++;
    }
    n_perMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)]++;
    idClusters.push_back(i);
    idNodesPerIdCluster[i].insert(i);
    // weightedCoordinatesPerCluster[i].x=deg->getPrimalGraph()->nodes[i]->location.x*deg->getPrimalGraph()->nodes[i]->mass;
    // weightedCoordinatesPerCluster[i].y=deg->getPrimalGraph()->nodes[i]->location.y*deg->getPrimalGraph()->nodes[i]->mass;
    // massesPerCluster[i]=deg->getPrimalGraph()->nodes[i]->mass;
    currentMasses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
    mass_PerMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)]+=deg->getPrimalGraph()->nodes[i]->mass;
    totalMass+=deg->getPrimalGraph()->nodes[i]->mass;
  }
  // widthBin=sqrt(n);
  // n=0;
  // totalMass=0;
  // for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
  //
  //   masses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
  //   long currentNOfThisMass=n_perMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)];
  //   if(currentNOfThisMass==0){
  //     n++;
  //   }
  //   n_perMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)]++;
  //   idClusters.push_back(i);
  //   idNodesPerIdCluster[i].insert(i);
  //   // weightedCoordinatesPerCluster[i].x=deg->getPrimalGraph()->nodes[i]->location.x*deg->getPrimalGraph()->nodes[i]->mass;
  //   // weightedCoordinatesPerCluster[i].y=deg->getPrimalGraph()->nodes[i]->location.y*deg->getPrimalGraph()->nodes[i]->mass;
  //   // massesPerCluster[i]=deg->getPrimalGraph()->nodes[i]->mass;
  //   currentMasses.push_back(deg->getPrimalGraph()->nodes[i]->mass);
  //   mass_PerMass[std::floor(deg->getPrimalGraph()->nodes[i]->mass/widthBin)]+=deg->getPrimalGraph()->nodes[i]->mass;
  //   totalMass+=deg->getPrimalGraph()->nodes[i]->mass;
  // }
// std::cout<<"B"<<'\n';
for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
  // double weight=structureWeights[i];
  double massA=deg->getPrimalGraph()->links[i]->A()->mass;
  double massB=deg->getPrimalGraph()->links[i]->B()->mass;
  // massesLinks.push_back(1.0/Functions::min(massA,massB));
  // massesLinks.push_back(weight);
  // massesLinks.push_back(weight*Functions::max(massA,massB));
  // massesLinks.push_back(Functions::max(massA,massB));
  massesLinks.push_back(Functions::runiform(0,100));

}
// std::cout<<"C"<<'\n';

  std::tuple<double,double> entropyInit_pair=Entropy::calculateDiscreteEntropyAreas(masses);
  double entropyInit_norm=std::get<0>(entropyInit_pair)/log(std::get<1>(entropyInit_pair));

  std::vector<long> orderedIndexes=Functions::getIndexesOfOrderedValues(massesLinks,false);
  // long numberCities=deg->getPrimalGraph()->nodes.size();
  // std::vector<bool> linkCollapsed;
  // linkCollapsed.resize(deg->getPrimalGraph()->links.size(),false);


  std::tuple<double,double> entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(masses);
  double entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));
  long current=0;
double entropy=std::get<0>(entropyCurrent_pair);
n=std::get<1>(entropyCurrent_pair);
  // std::cout<< entropyInit_norm<<'\n';
  bool stop=false;






  while(!stop&&current<orderedIndexes.size()){
    if(entropyCurrent_norm>=entropyInit_norm){
      // stop=true;
    }else{
      // stop=true;
    }
    if(current>1000){
      // stop=true;
    }
    // std::cout<< entropyInit_norm<<" <= "<<entropyCurrent_norm<<'\n';
    // double max=-INFINITY;
    // long indexMax=-1;

    if(ADN[orderedIndexes[current]]<.5){
    Link* link=deg->getPrimalGraph()->links[orderedIndexes[current]];
    Nodo* nodeA=link->A();
    Nodo* nodeB=link->B();
    long newCluster;
    long oldCluster;
    Nodo* node;
    if(currentMasses[idClusters[nodeA->id]]>currentMasses[idClusters[nodeB->id]]){
      newCluster=idClusters[nodeA->id];
      node=nodeB;
      oldCluster=idClusters[nodeB->id];
    }else{
      newCluster=idClusters[nodeB->id];
      node=nodeA;
      oldCluster=idClusters[nodeA->id];
    }

    if(oldCluster!=newCluster){
    // for(long i=0;i<node->links.size();i++){
    //   // if(!linkCollapsed[node->links[i]->id]){
    //     long newCluster=idClusters[node->links[i]->getOtherNode(node)->id];
    //     Point2d centroidNewCluster;
    //     centroidNewCluster.x=weightedCoordinatesPerCluster[newCluster].x/massesPerCluster[newCluster];
    //     centroidNewCluster.y=weightedCoordinatesPerCluster[newCluster].y/massesPerCluster[newCluster];
    //     long oldCluster=idClusters[node->id];
    //     Point2d centroidOldCluster;
    //     centroidOldCluster.x=weightedCoordinatesPerCluster[oldCluster].x/massesPerCluster[oldCluster];
    //     centroidOldCluster.y=weightedCoordinatesPerCluster[oldCluster].y/massesPerCluster[oldCluster];
    //     double distance=Functions::getDistance(centroidOldCluster,centroidNewCluster);

    //     // if(structureWeights[node->links[i]->id]>max&&oldCluster!=newCluster){
    //     if(structureWeights[node->links[i]->id]>max){
    //       max=structureWeights[node->links[i]->id];
    //       indexMax=i;
    //     }
    //   // }
    // }
    // if(indexMax!=-1){
      // long newCluster=idClusters[node->links[indexMax]->getOtherNode(node)->id];
      // linkCollapsed[node->links[indexMax]->id]=true;
      // long oldCluster=idClusters[node->id];
      // if(oldCluster!=newCluster){
      //   numberCities--;
      // //   std::cout<<numberCities<<'\n';
      // }

      // std::vector<long> idsForRecovery;
      // idsForRecovery.reserve(idNodesPerIdCluster[oldCluster].size());






    // double massToAdd=0;
      // for(auto it:idNodesPerIdCluster[oldCluster]){
      //   // idsForRecovery.push_back(it);
      //   // idClusters[it]=newCluster;
      //   // idNodesPerIdCluster[newCluster].insert(it);
      //   massToAdd+=masses[it];
      //   // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
      //   // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      // }
      double pNew_prev=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      double pSum_prev=mass_PerMass[std::floor((currentMasses[newCluster]+currentMasses[oldCluster])/widthBin)]/totalMass;
      double pOld_prev=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;

double massA=currentMasses[newCluster];
double massB=currentMasses[oldCluster];
      mass_PerMass[std::floor(massA/widthBin)]-=massA;
      mass_PerMass[std::floor(massB/widthBin)]-=massB;
      if(mass_PerMass[std::floor((massA)/widthBin)]<0){
        // std::cout<<"A "<<mass_PerMass[std::floor((massA)/widthBin)]<<" "<<massA<<" "<<std::floor((massA)/widthBin)<<'\n';
        mass_PerMass[std::floor((massA)/widthBin)]=0;
      }
      if(mass_PerMass[std::floor((massB)/widthBin)]<0){
        // std::cout<<"B "<<mass_PerMass[std::floor((massB)/widthBin)]<<'\n';
        mass_PerMass[std::floor((massB)/widthBin)]=0;
      }
      mass_PerMass[std::floor((massA+massB)/widthBin)]+=massA+massB;

      double pNew_post=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      double pSum_post=mass_PerMass[std::floor((currentMasses[newCluster]/widthBin)+currentMasses[oldCluster])]/totalMass;
      double pOld_post=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;
      // double pOld_prev2=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;

      // n--;
      long currentNOfNewClusterMass=n_perMass[std::floor(currentMasses[newCluster]/widthBin)];
      long currentNOfOldClusterMass=n_perMass[std::floor(currentMasses[oldCluster]/widthBin)];
      long n_prev=n;

    if(currentNOfNewClusterMass==1){
      n--;
    }
    if(currentNOfOldClusterMass==1){
      n--;
    }
    n_perMass[std::floor(currentMasses[newCluster]/widthBin)]--;
    currentMasses[newCluster]+=currentMasses[oldCluster];
      // weightedCoordinatesPerCluster[oldCluster].x=0;
      // weightedCoordinatesPerCluster[oldCluster].y=0;


if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==0){
      n++;
    }
    n_perMass[std::floor(currentMasses[newCluster]/widthBin)]++;
    n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]--;
    currentMasses[oldCluster]=0;
    // double pNew_post=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      // double pOld_post=currentMasses[oldCluster]/totalMass;
    // double pOld_post=0;
      // idNodesPerIdCluster[oldCluster].clear();

      // std::vector<double> massesCurrent;
      // massesCurrent.reserve(massesPerCluster.size());
      // for(auto it:massesPerCluster){
      //   massesCurrent.push_back(it.second);
      // }
      double prev_entropy=entropy;
      double prev_entropy_norm=entropyCurrent_norm;


      entropy=-entropy;
      double entNewPrev=pNew_prev*log(pNew_prev);
      double entSumPrev=pSum_prev*log(pSum_prev);
      double entOldPrev=pOld_prev*log(pOld_prev);
      if(pNew_prev<=0){
        entNewPrev=0;
        // std::cout<<"weirdA"<<'\n';
      }
      if(pSum_prev<=0){
        entSumPrev=0;
        // std::cout<<"weirdA"<<'\n';
      }
      if(pOld_prev<=0){
        entOldPrev=0;
        // std::cout<<"weirdB"<<'\n';
      }
      entropy-=entNewPrev+entOldPrev+entSumPrev;
      double entNewPost=pNew_post*log(pNew_post);
      double entSumPost=pSum_post*log(pSum_post);
      double entOldPost=pOld_post*log(pOld_post);
      if(pNew_post<=0){
        entNewPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      if(pSum_post<=0){
        entSumPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      if(pOld_post<=0){
        entOldPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      entropy+=entNewPost+entOldPost+entSumPost;
      entropy=-entropy;
      entropyCurrent_norm=entropy/log(n);


      // entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(currentMasses);
      // // std::cout<<pNew_prev<<" "<<pNew_post<<" "<<pOld_prev<<" "<<pOld_post<<'\n';
      // // if(Functions::abs(entropy-std::get<0>(entropyCurrent_pair))>.00001||n!=std::get<1>(entropyCurrent_pair)){
      //   // std::cout<<current<<" expected "<<entropy<<" "<<n<<" real "<<std::get<0>(entropyCurrent_pair)<<" "<<std::get<1>(entropyCurrent_pair)<<'\n';
      //   // stop=true;
      // // }
      // entropy=std::get<0>(entropyCurrent_pair);
      // n=std::get<1>(entropyCurrent_pair);
      // entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

      if(false){
        n_perMass[std::floor(currentMasses[newCluster]/widthBin)]--;
        if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==0){
          n--;
        }
        for(auto it:idNodesPerIdCluster[oldCluster]){

          // idClusters[it]=oldCluster;
          // auto it2=idNodesPerIdCluster[newCluster].find(it);
          // idNodesPerIdCluster[new]
          // idNodesClusters[oldCluster].insert(idsForRecovery[j]);
          currentMasses[newCluster]-=masses[it];
          currentMasses[oldCluster]+=masses[it];
          // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
          // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];
        }

        mass_PerMass[std::floor(massA/widthBin)]+=massA;
      mass_PerMass[std::floor(massB/widthBin)]+=massB;
      mass_PerMass[std::floor((massA+massB)/widthBin)]-=massA+massB;
      if(mass_PerMass[std::floor((massA+massB)/widthBin)]<0){
        std::cout<<mass_PerMass[std::floor((massA+massB)/widthBin)]<<'\n';
        mass_PerMass[std::floor((massA+massB)/widthBin)]=0;
      }

        n_perMass[std::floor(currentMasses[newCluster]/widthBin)]++;
        n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]++;
        if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==1){
          n++;
        }
        if(n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]==1){
          n++;
        }
        n=n_prev;
        // n++;
        entropy=prev_entropy;
        entropyCurrent_norm=entropy/log(n);
        // entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(currentMasses);

        // entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

      }else{
        // currentMasses[oldCluster]=0;
        for(auto it:idNodesPerIdCluster[oldCluster]){
        // idsForRecovery.push_back(it);
        idClusters[it]=newCluster;
        idNodesPerIdCluster[newCluster].insert(it);
        // currentMasses[newCluster]+=masses[it];
        // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
        // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      }
        idNodesPerIdCluster[oldCluster].clear();
      }

      // idClusters[node->id]=newCluster;
      // std::vector<long> uniqueIds=Functions::unique(idClusters);
      // numberCities=uniqueIds.size();
    }

}
    // }
    current++;

  }

current=0;
while(!stop&&current<orderedIndexes.size()){
    if(entropyCurrent_norm>=entropyInit_norm){
      // stop=true;
    }else{
      // stop=true;
    }
    if(current>1000){
      // stop=true;
    }
    // std::cout<< entropyInit_norm<<" <= "<<entropyCurrent_norm<<'\n';
    // double max=-INFINITY;
    // long indexMax=-1;
    Link* link=deg->getPrimalGraph()->links[orderedIndexes[current]];
    Nodo* nodeA=link->A();
    Nodo* nodeB=link->B();
    long newCluster;
    long oldCluster;
    Nodo* node;
    if(currentMasses[idClusters[nodeA->id]]>currentMasses[idClusters[nodeB->id]]){
      newCluster=idClusters[nodeA->id];
      node=nodeB;
      oldCluster=idClusters[nodeB->id];
    }else{
      newCluster=idClusters[nodeB->id];
      node=nodeA;
      oldCluster=idClusters[nodeA->id];
    }

    if(oldCluster!=newCluster){
    // for(long i=0;i<node->links.size();i++){
    //   // if(!linkCollapsed[node->links[i]->id]){
    //     long newCluster=idClusters[node->links[i]->getOtherNode(node)->id];
    //     Point2d centroidNewCluster;
    //     centroidNewCluster.x=weightedCoordinatesPerCluster[newCluster].x/massesPerCluster[newCluster];
    //     centroidNewCluster.y=weightedCoordinatesPerCluster[newCluster].y/massesPerCluster[newCluster];
    //     long oldCluster=idClusters[node->id];
    //     Point2d centroidOldCluster;
    //     centroidOldCluster.x=weightedCoordinatesPerCluster[oldCluster].x/massesPerCluster[oldCluster];
    //     centroidOldCluster.y=weightedCoordinatesPerCluster[oldCluster].y/massesPerCluster[oldCluster];
    //     double distance=Functions::getDistance(centroidOldCluster,centroidNewCluster);

    //     // if(structureWeights[node->links[i]->id]>max&&oldCluster!=newCluster){
    //     if(structureWeights[node->links[i]->id]>max){
    //       max=structureWeights[node->links[i]->id];
    //       indexMax=i;
    //     }
    //   // }
    // }
    // if(indexMax!=-1){
      // long newCluster=idClusters[node->links[indexMax]->getOtherNode(node)->id];
      // linkCollapsed[node->links[indexMax]->id]=true;
      // long oldCluster=idClusters[node->id];
      // if(oldCluster!=newCluster){
      //   numberCities--;
      // //   std::cout<<numberCities<<'\n';
      // }

      // std::vector<long> idsForRecovery;
      // idsForRecovery.reserve(idNodesPerIdCluster[oldCluster].size());






    // double massToAdd=0;
      // for(auto it:idNodesPerIdCluster[oldCluster]){
      //   // idsForRecovery.push_back(it);
      //   // idClusters[it]=newCluster;
      //   // idNodesPerIdCluster[newCluster].insert(it);
      //   massToAdd+=masses[it];
      //   // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
      //   // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      // }
      double pNew_prev=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      double pSum_prev=mass_PerMass[std::floor((currentMasses[newCluster]+currentMasses[oldCluster])/widthBin)]/totalMass;
      double pOld_prev=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;

double massA=currentMasses[newCluster];
double massB=currentMasses[oldCluster];
      mass_PerMass[std::floor(massA/widthBin)]-=massA;
      mass_PerMass[std::floor(massB/widthBin)]-=massB;
      if(mass_PerMass[std::floor((massA)/widthBin)]<0){
        // std::cout<<"A "<<mass_PerMass[std::floor((massA)/widthBin)]<<" "<<massA<<" "<<std::floor((massA)/widthBin)<<'\n';
        mass_PerMass[std::floor((massA)/widthBin)]=0;
      }
      if(mass_PerMass[std::floor((massB)/widthBin)]<0){
        // std::cout<<"B "<<mass_PerMass[std::floor((massB)/widthBin)]<<'\n';
        mass_PerMass[std::floor((massB)/widthBin)]=0;
      }
      mass_PerMass[std::floor((massA+massB)/widthBin)]+=massA+massB;

      double pNew_post=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      double pSum_post=mass_PerMass[std::floor((currentMasses[newCluster]/widthBin)+currentMasses[oldCluster])]/totalMass;
      double pOld_post=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;
      // double pOld_prev2=mass_PerMass[std::floor(currentMasses[oldCluster]/widthBin)]/totalMass;

      // n--;
      long currentNOfNewClusterMass=n_perMass[std::floor(currentMasses[newCluster]/widthBin)];
      long currentNOfOldClusterMass=n_perMass[std::floor(currentMasses[oldCluster]/widthBin)];
      long n_prev=n;

    if(currentNOfNewClusterMass==1){
      n--;
    }
    if(currentNOfOldClusterMass==1){
      n--;
    }
    n_perMass[std::floor(currentMasses[newCluster]/widthBin)]--;
    currentMasses[newCluster]+=currentMasses[oldCluster];
      // weightedCoordinatesPerCluster[oldCluster].x=0;
      // weightedCoordinatesPerCluster[oldCluster].y=0;


if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==0){
      n++;
    }
    n_perMass[std::floor(currentMasses[newCluster]/widthBin)]++;
    n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]--;
    currentMasses[oldCluster]=0;
    // double pNew_post=mass_PerMass[std::floor(currentMasses[newCluster]/widthBin)]/totalMass;
      // double pOld_post=currentMasses[oldCluster]/totalMass;
    // double pOld_post=0;
      // idNodesPerIdCluster[oldCluster].clear();

      // std::vector<double> massesCurrent;
      // massesCurrent.reserve(massesPerCluster.size());
      // for(auto it:massesPerCluster){
      //   massesCurrent.push_back(it.second);
      // }
      double prev_entropy=entropy;
      double prev_entropy_norm=entropyCurrent_norm;


      entropy=-entropy;
      double entNewPrev=pNew_prev*log(pNew_prev);
      double entSumPrev=pSum_prev*log(pSum_prev);
      double entOldPrev=pOld_prev*log(pOld_prev);
      if(pNew_prev<=0){
        entNewPrev=0;
        // std::cout<<"weirdA"<<'\n';
      }
      if(pSum_prev<=0){
        entSumPrev=0;
        // std::cout<<"weirdA"<<'\n';
      }
      if(pOld_prev<=0){
        entOldPrev=0;
        // std::cout<<"weirdB"<<'\n';
      }
      entropy-=entNewPrev+entOldPrev+entSumPrev;
      double entNewPost=pNew_post*log(pNew_post);
      double entSumPost=pSum_post*log(pSum_post);
      double entOldPost=pOld_post*log(pOld_post);
      if(pNew_post<=0){
        entNewPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      if(pSum_post<=0){
        entSumPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      if(pOld_post<=0){
        entOldPost=0;
        // std::cout<<"weirdC"<<'\n';
      }
      entropy+=entNewPost+entOldPost+entSumPost;
      entropy=-entropy;
      entropyCurrent_norm=entropy/log(n);


      // entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(currentMasses);
      // // std::cout<<pNew_prev<<" "<<pNew_post<<" "<<pOld_prev<<" "<<pOld_post<<'\n';
      // // if(Functions::abs(entropy-std::get<0>(entropyCurrent_pair))>.00001||n!=std::get<1>(entropyCurrent_pair)){
      //   // std::cout<<current<<" expected "<<entropy<<" "<<n<<" real "<<std::get<0>(entropyCurrent_pair)<<" "<<std::get<1>(entropyCurrent_pair)<<'\n';
      //   // stop=true;
      // // }
      // entropy=std::get<0>(entropyCurrent_pair);
      // n=std::get<1>(entropyCurrent_pair);
      // entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

      if((prev_entropy_norm-entropyCurrent_norm)>0){
        ADN[orderedIndexes[current]]=1;
        n_perMass[std::floor(currentMasses[newCluster]/widthBin)]--;
        if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==0){
          n--;
        }
        for(auto it:idNodesPerIdCluster[oldCluster]){

          // idClusters[it]=oldCluster;
          // auto it2=idNodesPerIdCluster[newCluster].find(it);
          // idNodesPerIdCluster[new]
          // idNodesClusters[oldCluster].insert(idsForRecovery[j]);
          currentMasses[newCluster]-=masses[it];
          currentMasses[oldCluster]+=masses[it];
          // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
          // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];
        }

        mass_PerMass[std::floor(massA/widthBin)]+=massA;
      mass_PerMass[std::floor(massB/widthBin)]+=massB;
      mass_PerMass[std::floor((massA+massB)/widthBin)]-=massA+massB;
      if(mass_PerMass[std::floor((massA+massB)/widthBin)]<0){
        std::cout<<mass_PerMass[std::floor((massA+massB)/widthBin)]<<'\n';
        mass_PerMass[std::floor((massA+massB)/widthBin)]=0;
      }

        n_perMass[std::floor(currentMasses[newCluster]/widthBin)]++;
        n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]++;
        if(n_perMass[std::floor(currentMasses[newCluster]/widthBin)]==1){
          n++;
        }
        if(n_perMass[std::floor(currentMasses[oldCluster]/widthBin)]==1){
          n++;
        }
        n=n_prev;
        // n++;
        entropy=prev_entropy;
        entropyCurrent_norm=entropy/log(n);
        // entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(currentMasses);

        // entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));

      }else{
        ADN[orderedIndexes[current]]=0;
        // currentMasses[oldCluster]=0;
        for(auto it:idNodesPerIdCluster[oldCluster]){
        // idsForRecovery.push_back(it);
        idClusters[it]=newCluster;
        idNodesPerIdCluster[newCluster].insert(it);
        // currentMasses[newCluster]+=masses[it];
        // weightedCoordinatesPerCluster[newCluster].x+=deg->getPrimalGraph()->nodes[it]->location.x*masses[it];
        // weightedCoordinatesPerCluster[newCluster].y+=deg->getPrimalGraph()->nodes[it]->location.y*masses[it];

      }
        idNodesPerIdCluster[oldCluster].clear();
      }

      // idClusters[node->id]=newCluster;
      // std::vector<long> uniqueIds=Functions::unique(idClusters);
      // numberCities=uniqueIds.size();

}
    // }
    current++;

  }














 //   Grafo* G=new Grafo();

 //   Grafo::createSuperGraphFromClustersFromColorsNodes(deg->getPrimalGraph(),G,idClusters,true);

 // Rcpp::XPtr< Grafo > p(G,true) ;
 // return p;

 // return wrap(idClusters);

}








// [[Rcpp::export]]
NumericVector compressCitiesUsingStructure_usingGA(XPtr<DualExtendedGraph> deg,NumericVector structure,double probModification,double probModStruct,long numGen){
  long nIH=20;
  DualExtendedGraph::setPrimalAsStructuralGraph(deg);
  std::vector<double> bestADN;
  double fitnessBest=0;

  std::vector<std::vector<double> > ADNs;
  std::vector<std::vector<double> > ADNs_copy;
  std::vector<double> fitness;
  long numberLinks=deg->getPrimalGraph()->links.size();
  std::vector<double> initialWeights;
  initialWeights.reserve(numberLinks);
  double maxOfMins=0;
  double maxInvStructure=0;
  for(long j=0;j<numberLinks;j++){
    initialWeights.push_back(deg->getPrimalGraph()->links[j]->weight);
    if(maxOfMins<Functions::min(deg->getPrimalGraph()->links[j]->A()->mass,deg->getPrimalGraph()->links[j]->B()->mass)){
      maxOfMins=Functions::min(deg->getPrimalGraph()->links[j]->A()->mass,deg->getPrimalGraph()->links[j]->B()->mass);
    }
    if(maxInvStructure<structure[j]){
      maxInvStructure=structure[j];
    }
  }
  ADNs.resize(nIH*2,std::vector<double>() );
  fitness.resize(nIH*2,0);
  for(long i=0;i<nIH*2;i++){
    ADNs[i].resize(numberLinks,1);
  }
  bestADN.resize(numberLinks,1);
  ADNs_copy.resize(nIH*2,std::vector<double>() );
  // fitness.resize(nIH*2,0);
  for(long i=0;i<nIH*2;i++){
    ADNs_copy[i].resize(numberLinks,1);
  }
  long indexBest=-1;
  // double probModification=.1;//.005
  long generation=0;


  while(generation<numGen){

    for(long i=0;i<nIH;i++){

      long id2=std::floor(Functions::runiform(0,nIH));
      id2=0;
      if(i==1&&generation%1==0){
          // compressCitiesUsingStructure_stopLowerNormalisedEntropy_hillClimbForGA(deg,ADNs[i]);
        }
      for(long j=0;j<numberLinks;j++){
        if(probModification>Functions::runiform(0,1)&&i!=0){
          // if(ADNs[i][j]==0){
          // // if(Functions::runiform(0,1)<.75){
          //   ADNs[i][j]=1;
          // }else{
          //   ADNs[i][j]=0;
          // }

            if(ADNs[i][j]==0){
            // if(Functions::runiform(0,1)<.75){
              ADNs[i][j]=1;
            }else{
              ADNs[i][j]=0;
            }

        }
        if(probModStruct>Functions::runiform(0,1)&&i!=0){
          double minMasses=Functions::min(deg->getPrimalGraph()->links[j]->A()->mass,deg->getPrimalGraph()->links[j]->B()->mass);
          if(minMasses/maxOfMins<Functions::runiform(0,1)){
          // if((structure[j])/maxInvStructure*minMasses/maxOfMins<Functions::runiform(0,1)){
          // if((structure[j])/maxInvStructure<Functions::runiform(0,1)){
            ADNs[i][j]=0;
          }else{
            ADNs[i][j]=1;
            // if(ADNs[i][j]==0){
            // // if(Functions::runiform(0,1)<.75){
            //   ADNs[i][j]=1;
            // }else{
            //   ADNs[i][j]=0;
            // }
          }
        }




        if(Functions::runiform(0,1)<.5){
          ADNs[i+nIH][j]=ADNs[i][j];
        }else{
          ADNs[i+nIH][j]=bestADN[j];
        }
        deg->getPrimalGraph()->links[j]->weight=ADNs[i][j];
      }
      std::vector<long> colors;
      std::vector<double> sizes;

      DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,0.5,colors,sizes);
      // out("Finished getting colors");
      std::vector<long> colorsNodes;
      Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
      // std::vector<double> sizesNodes;
      for(long h=0;h<colorsNodes.size();h++){
        if(colorsNodes[h]==-1){
          sizes.push_back(deg->getPrimalGraph()->nodes[h]->mass);
        }
      }
      std::tuple<double,double> entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(sizes);
      double entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));
      fitness[i]=entropyCurrent_norm;
      if(!std::isfinite(fitness[i])){
        fitness[i]=0;
      }
      // std::cout<<i<<" "<<std::get<0>(entropyCurrent_pair)<<" "<<std::get<1>(entropyCurrent_pair)<<'\n';

    }
    for(long i=nIH;i<nIH*2;i++){
      for(long j=0;j<numberLinks;j++){
        deg->getPrimalGraph()->links[j]->weight=ADNs[i][j];
      }
      std::vector<long> colors;
      std::vector<double> sizes;

      DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,0.5,colors,sizes);
      // out("Finished getting colors");
      std::vector<long> colorsNodes;
      Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
      // std::vector<double> sizesNodes;
      for(long h=0;h<colorsNodes.size();h++){
        if(colorsNodes[h]==-1){
          sizes.push_back(deg->getPrimalGraph()->nodes[h]->mass);
        }
      }
      std::tuple<double,double> entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(sizes);
      double entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));
      fitness[i]=entropyCurrent_norm;
      if(!std::isfinite(fitness[i])){
        fitness[i]=0;
      }

    }

    std::vector<long> orderIndex=Functions::getIndexesOfOrderedValues(fitness,false);
    // indexBest=orderIndex[0];
    std::cout<<"Generation: "<<generation<<" ,fitness: "<<fitness[orderIndex[0]]<<'\n';
    for(long i=0;i<nIH;i++){
      std::swap(ADNs_copy[i],ADNs[orderIndex[i]]);
    }
    std::swap(ADNs_copy,ADNs);


    for(long i=0;i<nIH;i++){
      for(long j=0;j<numberLinks;j++){
        deg->getPrimalGraph()->links[j]->weight=ADNs[i][j];
      }
      std::vector<long> colors;
      std::vector<double> sizes;

      DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,0.5,colors,sizes);
      // out("Finished getting colors");
      std::vector<long> colorsNodes;
      Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
      // std::vector<double> sizesNodes;
      for(long h=0;h<colorsNodes.size();h++){
        if(colorsNodes[h]==-1){
          sizes.push_back(deg->getPrimalGraph()->nodes[h]->mass);
        }
      }
      std::tuple<double,double> entropyCurrent_pair=Entropy::calculateDiscreteEntropyAreas(sizes);
      double entropyCurrent_norm=std::get<0>(entropyCurrent_pair)/log(std::get<1>(entropyCurrent_pair));
      fitness[i]=entropyCurrent_norm;
      std::cout<<i<<" "<<fitness[i]<<" "<<std::get<0>(entropyCurrent_pair)<<" "<<std::get<1>(entropyCurrent_pair)<<'\n';
    }
    if(fitness[0]>fitnessBest){
      fitnessBest=fitness[0];
      for(long h=0;h<numberLinks;h++){
        bestADN[h]=ADNs[0][h];
      }
    }
    if(fitness[0]<.995*fitnessBest){
      // fitnessBest=fitness[0];
      for(long h=0;h<numberLinks;h++){
        ADNs[0][h]=bestADN[h];
      }
    }

    generation++;
  }

  // std::vector<long> orderIndex=Functions::getIndexesOfOrderedValues(fitness,false);
  for(long j=0;j<numberLinks;j++){
    deg->getPrimalGraph()->links[j]->weight=bestADN[j];
  }
  std::vector<long> colors;
  std::vector<double> sizes;
  DualExtendedGraph::metricPercolation_sizeUsingMassesNodes(deg,0.5,colors,sizes);
  for(long j=0;j<numberLinks;j++){
    deg->getPrimalGraph()->links[j]->weight=initialWeights[j];
  }
  long numClusters=sizes.size();
  long current=numClusters;
   std::vector<long> colorsNodes;
  Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),colors,colorsNodes);
  std::vector<double> sizesNodes;
  for(long i=0;i<colorsNodes.size();i++){
    if(colorsNodes[i]==-1){
      colorsNodes[i]=current;
      current++;
    }
  }
  return wrap(colorsNodes);

}



// [[Rcpp::export]]
DataFrame projectCoordinates(DataFrame coordinates,String EPSG_in,String EPSG_out){
   OGRCoordinateTransformation* poCT=ShapeFile::prepareToTransformCoordinates(EPSG_in,EPSG_out);
   NumericVector ids=as<NumericVector>(coordinates[0]);
   NumericVector x=as<NumericVector>(coordinates[1]);
   NumericVector y=as<NumericVector>(coordinates[2]);

   std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
   std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
   std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
   std::vector<double> xR;
   std::vector<double> yR;
   xR.resize(x_.size(),0);
   yR.resize(x_.size(),0);
   for(long i=0;i<ids_.size();i++){
     Point2d point=ShapeFile::transformCoordinates(Point2d(x_[i],y_[i]),poCT);
     xR[i]=point.x;
     yR[i]=point.y;
   }

   List list(3);
   // for(long i=0;i<numberObjectsDataFrame;i++){
     list[0]=(wrap(ids_));
     list[1]=(wrap(xR));
     list[2]=(wrap(yR));
   // }

   CharacterVector namevec;
   // for(long i=0;i<numberObjectsDataFrame;i++){
     namevec.push_back("id");
     namevec.push_back("x");
     namevec.push_back("y");
   // }




   list.attr("names") = namevec;
   DataFrame df(list);
   return df;
}





// [[Rcpp::export]]
void changeProjectionGraph(XPtr<Grafo> G,String EPSG_in,String EPSG_out){
   OGRCoordinateTransformation* poCT=ShapeFile::prepareToTransformCoordinates(EPSG_in,EPSG_out);
   for(long i=0;i<G->nodes.size();i++){
     Point2d point=ShapeFile::transformCoordinates(G->nodes[i]->location,poCT);
     G->nodes[i]->location=point;
   }

}

// [[Rcpp::export]]
void changeProjectionDEG(XPtr<DualExtendedGraph> deg,String EPSG_in,String EPSG_out){
   OGRCoordinateTransformation* poCT=ShapeFile::prepareToTransformCoordinates(EPSG_in,EPSG_out);
   for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
     Point2d point=ShapeFile::transformCoordinates(deg->getPrimalGraph()->nodes[i]->location,poCT);
     deg->getPrimalGraph()->nodes[i]->location=point;
   }
   deg->softReset();
}

// [[Rcpp::export]]
XPtr<Grafo> generateBoundaryFromPixelGraph(XPtr<Grafo> city,double sizePixel){
  double rounding=sizePixel;
  Grafo* G=new Grafo();
  G->bidirectional=true;
  G->pseudoGraph=false;
  G->allowLoops=false;
  G->isPlanar=true;
  G->spatialGraph=true;
  // bool allowLoops;
  // bool isPlanar;
  // bool spatialGraph;
  SparseMatrix matrix;
  for(long i=0;i<city->nodes.size();i++){
    // double rounding=10.0;
    // double xr=std::round(city->nodes[i]->location.x/rounding)*rounding;
    // double yr=std::round(city->nodes[i]->location.y/rounding)*rounding;

    double x=city->nodes[i]->location.x;
    double y=city->nodes[i]->location.y;
    double xr=x;
    double yr=y;
    Nodo* id1;
      if(matrix.getId(xr-(rounding/2.0),yr-(rounding/2.0))==-1){
        id1=G->addNode(Point2d(x-(rounding/2.0),y-(rounding/2.0)));
        matrix.setId(xr-(rounding/2.0),yr-(rounding/2.0),id1->id);
      }else{
        id1=G->nodes[matrix.getId(xr-(rounding/2.0),yr-(rounding/2.0))];
      }
      Nodo* id2;
        if(matrix.getId(xr-(rounding/2.0),yr+(rounding/2.0))==-1){
          id2=G->addNode(Point2d(x-(rounding/2.0),y+(rounding/2.0)));
          matrix.setId(xr-(rounding/2.0),yr+(rounding/2.0),id2->id);
        }else{
          id2=G->nodes[matrix.getId(xr-(rounding/2.0),yr+(rounding/2.0))];
        }
        Nodo* id3;
          if(matrix.getId(xr+(rounding/2.0),yr+(rounding/2.0))==-1){
            id3=G->addNode(Point2d(x+(rounding/2.0),y+(rounding/2.0)));
            matrix.setId(xr+(rounding/2.0),yr+(rounding/2.0),id3->id);
          }else{
            id3=G->nodes[matrix.getId(xr+(rounding/2.0),yr+(rounding/2.0))];
          }
          Nodo* id4;
            if(matrix.getId(xr+(rounding/2.0),yr-(rounding/2.0))==-1){
              id4=G->addNode(Point2d(x+(rounding/2.0),y-(rounding/2.0)));
              matrix.setId(xr+(rounding/2.0),yr-(rounding/2.0),id4->id);
            }else{
              id4=G->nodes[matrix.getId(xr+(rounding/2.0),yr-(rounding/2.0))];
            }
      // Nodo* id4=G->addNode(Point2d(x+125,y-125));
      G->addLink(id1->id,id2->id,rounding);
      G->addLink(id2->id,id3->id,rounding);
      G->addLink(id3->id,id4->id,rounding);
      G->addLink(id4->id,id1->id,rounding);
  }
  G->finishedAddingNodes();
  // std::vector<long> linksToKeep;
  // for(long i=0;i<G->links.size();i++){
  //     if(G->links[i]->A()->links.size()<4&&G->links[i]->B()->links.size()<4){
  //       linksToKeep.push_back(i);
  //     }
  // }
  Grafo* boundary=new Grafo();
  // Grafo boundaryTemp;
  // Grafo::inducedSubgraphFromLinks(G,&boundaryTemp,linksToKeep);
  // Grafo LG;
  // Grafo::getLargestComponent(&boundaryTemp,&LG);
  DualExtendedGraph deg;
  DualExtendedGraph::addPrimal(&deg,G);
  Grafo* dual=deg.getDualGraph();

  std::vector<Link*> links;
  if(dual->nodes.size()>0){
      for(long i=0;i<dual->nodes[0]->links.size();i++){
          links.push_back(deg.getPrimalGraph()->links[dual->nodes[0]->links[i]->id]);
      }
  }
  Grafo bt;
  Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), &bt,links);
  Grafo::getLargestComponent(&bt,boundary);
  delete G;
  Rcpp::XPtr<Grafo> p(boundary,true);
  return p;
}


// [[Rcpp::export]]
XPtr<Grafo> generateBoundaryFromGriddedPopulation(XPtr<Grafo> city){
  double rounding=1;
  Grafo* G=new Grafo();
  G->bidirectional=true;
  G->pseudoGraph=false;
  G->allowLoops=false;
  G->isPlanar=true;
  G->spatialGraph=true;
  // bool allowLoops;
  // bool isPlanar;
  // bool spatialGraph;
  SparseMatrix matrix;
  for(long i=0;i<city->nodes.size();i++){
    // double rounding=10.0;
    double xr=std::round(city->nodes[i]->location.x/rounding)*rounding;
    double yr=std::round(city->nodes[i]->location.y/rounding)*rounding;

    double x=city->nodes[i]->location.x;
    double y=city->nodes[i]->location.y;
    Nodo* id1;
      if(matrix.getId(xr-125,yr-125)==-1){
        id1=G->addNode(Point2d(x-125,y-125));
        matrix.setId(xr-125,yr-125,id1->id);
      }else{
        id1=G->nodes[matrix.getId(xr-125,yr-125)];
      }
      Nodo* id2;
        if(matrix.getId(xr-125,yr+125)==-1){
          id2=G->addNode(Point2d(x-125,y+125));
          matrix.setId(xr-125,yr+125,id2->id);
        }else{
          id2=G->nodes[matrix.getId(xr-125,yr+125)];
        }
        Nodo* id3;
          if(matrix.getId(xr+125,yr+125)==-1){
            id3=G->addNode(Point2d(x+125,y+125));
            matrix.setId(xr+125,yr+125,id3->id);
          }else{
            id3=G->nodes[matrix.getId(xr+125,yr+125)];
          }
          Nodo* id4;
            if(matrix.getId(xr+125,yr-125)==-1){
              id4=G->addNode(Point2d(x+125,y-125));
              matrix.setId(xr+125,yr-125,id4->id);
            }else{
              id4=G->nodes[matrix.getId(xr+125,yr-125)];
            }
      // Nodo* id4=G->addNode(Point2d(x+125,y-(rounding/2.0)));
      G->addLink(id1->id,id2->id,250);
      G->addLink(id2->id,id3->id,250);
      G->addLink(id3->id,id4->id,250);
      G->addLink(id4->id,id1->id,250);
  }
  G->finishedAddingNodes();
  // std::vector<long> linksToKeep;
  // for(long i=0;i<G->links.size();i++){
  //     if(G->links[i]->A()->links.size()<4&&G->links[i]->B()->links.size()<4){
  //       linksToKeep.push_back(i);
  //     }
  // }
  Grafo* boundary=new Grafo();
  // Grafo boundaryTemp;
  // Grafo::inducedSubgraphFromLinks(G,&boundaryTemp,linksToKeep);
  // Grafo LG;
  // Grafo::getLargestComponent(&boundaryTemp,&LG);
  DualExtendedGraph deg;
  DualExtendedGraph::addPrimal(&deg,G);
  Grafo* dual=deg.getDualGraph();

  std::vector<Link*> links;
  if(dual->nodes.size()>0){
      for(long i=0;i<dual->nodes[0]->links.size();i++){
          links.push_back(deg.getPrimalGraph()->links[dual->nodes[0]->links[i]->id]);
      }
  }
  // Grafo bt;
  // Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), &bt,links);
  // Grafo::getLargestComponent(&bt,boundary);
  Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), boundary,links);
  delete G;
  Rcpp::XPtr<Grafo> p(boundary,true);
  return p;
}




Grafo* generateBoundaryFromGriddedObject_cpp(Grafo* city,double lengthPixel){
  double rounding=1.0;
  Grafo* G=new Grafo();
  G->bidirectional=true;
  G->pseudoGraph=false;
  G->allowLoops=false;
  G->isPlanar=true;
  G->spatialGraph=true;
  // bool allowLoops;
  // bool isPlanar;
  // bool spatialGraph;
  // std::cout<<"n nodes in city "<<city->nodes.size()<<'\n';
  SparseMatrix matrix;
  for(long i=0;i<city->nodes.size();i++){
    // double rounding=10.0;
    double xr=std::round(city->nodes[i]->location.x/rounding)*rounding;
    double yr=std::round(city->nodes[i]->location.y/rounding)*rounding;

    double x=city->nodes[i]->location.x;
    double y=city->nodes[i]->location.y;
    Nodo* id1;
      if(matrix.getId(xr-lengthPixel/2.0,yr-lengthPixel/2.0)==-1){
        id1=G->addNode(Point2d(x-lengthPixel/2.0,y-lengthPixel/2.0));
        matrix.setId(xr-lengthPixel/2.0,yr-lengthPixel/2.0,id1->id);
      }else{
        id1=G->nodes[matrix.getId(xr-lengthPixel/2.0,yr-lengthPixel/2.0)];
      }
      Nodo* id2;
        if(matrix.getId(xr-lengthPixel/2.0,yr+lengthPixel/2.0)==-1){
          id2=G->addNode(Point2d(x-lengthPixel/2.0,y+lengthPixel/2.0));
          matrix.setId(xr-lengthPixel/2.0,yr+lengthPixel/2.0,id2->id);
        }else{
          id2=G->nodes[matrix.getId(xr-lengthPixel/2.0,yr+lengthPixel/2.0)];
        }
        Nodo* id3;
          if(matrix.getId(xr+lengthPixel/2.0,yr+lengthPixel/2.0)==-1){
            id3=G->addNode(Point2d(x+lengthPixel/2.0,y+lengthPixel/2.0));
            matrix.setId(xr+lengthPixel/2.0,yr+lengthPixel/2.0,id3->id);
          }else{
            id3=G->nodes[matrix.getId(xr+lengthPixel/2.0,yr+lengthPixel/2.0)];
          }
          Nodo* id4;
            if(matrix.getId(xr+lengthPixel/2.0,yr-lengthPixel/2.0)==-1){
              id4=G->addNode(Point2d(x+lengthPixel/2.0,y-lengthPixel/2.0));
              matrix.setId(xr+lengthPixel/2.0,yr-lengthPixel/2.0,id4->id);
            }else{
              id4=G->nodes[matrix.getId(xr+lengthPixel/2.0,yr-lengthPixel/2.0)];
            }
      // Nodo* id4=G->addNode(Point2d(x+lengthPixel/2.0,y-(rounding/2.0)));
      G->addLink(id1->id,id2->id,lengthPixel);
      G->addLink(id2->id,id3->id,lengthPixel);
      G->addLink(id3->id,id4->id,lengthPixel);
      G->addLink(id4->id,id1->id,lengthPixel);
  }
  G->finishedAddingNodes();
  // std::vector<long> linksToKeep;
  // for(long i=0;i<G->links.size();i++){
  //     if(G->links[i]->A()->links.size()<4&&G->links[i]->B()->links.size()<4){
  //       linksToKeep.push_back(i);
  //     }
  // }



  Grafo* boundary=new Grafo();
  // Grafo boundaryTemp;
  // Grafo::inducedSubgraphFromLinks(G,&boundaryTemp,linksToKeep);
  // Grafo LG;
  // Grafo::getLargestComponent(&boundaryTemp,&LG);
  DualExtendedGraph deg;
  DualExtendedGraph::addPrimal(&deg,G);
  Grafo* dual=deg.getDualGraph();

  std::vector<Link*> links;
  if(dual->nodes.size()>0){
      for(long i=0;i<dual->nodes[0]->links.size();i++){
          links.push_back(deg.getPrimalGraph()->links[dual->nodes[0]->links[i]->id]);
      }
  }
  // Grafo bt;
  // Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), &bt,links);
  // Grafo::getLargestComponent(&bt,boundary);

  Grafo::inducedSubgraphFromLinks(deg.getPrimalGraph(), boundary,links);
  delete G;
  // Rcpp::XPtr<Grafo> p(boundary,true);
  return boundary;
}






// [[Rcpp::export]]
XPtr<Grafo> generateBoundaryFromGriddedObject(XPtr<Grafo> city,double lengthPixel){
  Grafo* boundary=generateBoundaryFromGriddedObject_cpp(city,lengthPixel);
  Rcpp::XPtr<Grafo> p(boundary,true);
  return p;
}



// [[Rcpp::export]]
DataFrame measureNumberEndPointsWithinACircle(XPtr<Grafo> city,double xCenter,double yCenter,double radius){

double r=radius;
DualExtendedGraph deg;
DualExtendedGraph::addPrimal(&deg,city);
DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);
long N1=deg.getPrimalGraph()->nodes.size();
Grafo circle;
circle.bidirectional=false;
circle.pseudoGraph=false;
circle.allowLoops=false;
circle.isPlanar=true;

double definition=1.0;
long numberNodes=(long)(2.0*3.1416*r/definition);
double angleBetweenNodesRadians=2.0*3.1416/(double)(numberNodes);
double lengthCircle=0;
for(long i=0;i<numberNodes;i++){
  circle.addNode(Point2d(std::cos(angleBetweenNodesRadians*i)*r+xCenter,std::sin(angleBetweenNodesRadians*i)*r+yCenter));
  if(i>0){
    circle.addLink(i-1,i,Functions::getDistance(circle.nodes[i]->location,circle.nodes[i-1]->location));
    lengthCircle+=Functions::getDistance(circle.nodes[i]->location,circle.nodes[i-1]->location);
  }
  if(i==numberNodes-1){
    circle.addLink(i,0,Functions::getDistance(circle.nodes[i]->location,circle.nodes[0]->location));
    lengthCircle+=Functions::getDistance(circle.nodes[i]->location,circle.nodes[0]->location);
  }
}

long Ncircle=numberNodes;
DualExtendedGraph::addAnotherGraph(&deg,&circle,true);
long N2=deg.getPrimalGraph()->nodes.size();
// Grafo* G=DualExtendedGraph::getPrimalGraph(&deg);
long numberCoincidentNodes=N1+Ncircle-N2;
DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);
long N3=deg.getPrimalGraph()->nodes.size();
// return(N3-N2+numberCoincidentNodes);
long n=N3-N2+numberCoincidentNodes;

std::vector<long> idsNodes;
for(long i=0;i<deg.getPrimalGraph()->nodes.size();i++){
  if(Functions::getDistance(deg.getPrimalGraph()->nodes[i]->location,Point2d(xCenter,yCenter))<=r+1){//+1 only to absorb any errors possible
        idsNodes.push_back(i);
  }
}
Grafo subgraph;
Grafo::inducedSubgraph(deg.getPrimalGraph(),&subgraph,idsNodes);
double l=0;
for(long i=0;i<subgraph.links.size();i++){
  l+=subgraph.links[i]->weight;
}
l-=lengthCircle;

List list(3);
// for(long i=0;i<numberObjectsDataFrame;i++){
  list[0]=(r);
  list[1]=(n);
  list[2]=(l);
// }

CharacterVector namevec;
// for(long i=0;i<numberObjectsDataFrame;i++){
  namevec.push_back("r");
  namevec.push_back("n");
  namevec.push_back("l");
// }




list.attr("names") = namevec;
DataFrame df(list);
return df;
}







// [[Rcpp::export]]
DataFrame measureNumberEndPointsWithinADistanceThroughTheNetwork(XPtr<Grafo> city,double xCenter,double yCenter,double distance){


double r=distance;
DualExtendedGraph deg;
DualExtendedGraph::addPrimal(&deg,city);
DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);
double minD=INFINITY;
long indexNode=-1;
for(long i=0;i<deg.getPrimalGraph()->nodes.size();i++){
  deg.getPrimalGraph()->nodes[i]->mass=1;//just to make sure that min of betweenness is 1
  if(Functions::getDistance(Point2d(xCenter,yCenter),deg.getPrimalGraph()->nodes[i]->location)<minD){
    indexNode=i;
    minD=Functions::getDistance(Point2d(xCenter,yCenter),deg.getPrimalGraph()->nodes[i]->location);
  }
}
std::vector<double> betweenness;
betweenness.resize(deg.getPrimalGraph()->links.size(),0);
Grafo::calculateEdgeBetweenness_aux(deg.getPrimalGraph(),indexNode,indexNode+1,r,betweenness);
long n=0;
double l=0;
for(long i=0;i<deg.getPrimalGraph()->links.size();i++){
  if(betweenness[i]>=1){
    l+=deg.getPrimalGraph()->links[i]->weight;
    if(betweenness[i]==1){
      n++;
    }
  }
}

//
// long N1=deg.getPrimalGraph()->nodes.size();
// Grafo circle;
// circle.bidirectional=false;
// circle.pseudoGraph=false;
// circle.allowLoops=false;
// circle.isPlanar=true;
//
// double definition=1.0;
// long numberNodes=(long)(2.0*3.1416*r/definition);
// double angleBetweenNodesRadians=2.0*3.1416/(double)(numberNodes);
// double lengthCircle=0;
// for(long i=0;i<numberNodes;i++){
//   circle.addNode(Point2d(std::cos(angleBetweenNodesRadians*i)*r+xCenter,std::sin(angleBetweenNodesRadians*i)*r+yCenter));
//   if(i>0){
//     circle.addLink(i-1,i,Functions::getDistance(circle.nodes[i]->location,circle.nodes[i-1]->location));
//     lengthCircle+=Functions::getDistance(circle.nodes[i]->location,circle.nodes[i-1]->location);
//   }
//   if(i==numberNodes-1){
//     circle.addLink(i,0,Functions::getDistance(circle.nodes[i]->location,circle.nodes[0]->location));
//     lengthCircle+=Functions::getDistance(circle.nodes[i]->location,circle.nodes[0]->location);
//   }
// }
//
// long Ncircle=numberNodes;
// DualExtendedGraph::addAnotherGraph(&deg,&circle,true);
// long N2=deg.getPrimalGraph()->nodes.size();
// // Grafo* G=DualExtendedGraph::getPrimalGraph(&deg);
// long numberCoincidentNodes=N1+Ncircle-N2;
// DualExtendedGraph::forcePlanarityPrimal(&deg,Grafo::PLANARITY_PLANESWEEP);
// long N3=deg.getPrimalGraph()->nodes.size();
// // return(N3-N2+numberCoincidentNodes);
// long n=N3-N2+numberCoincidentNodes;
//
// std::vector<long> idsNodes;
// for(long i=0;i<deg.getPrimalGraph()->nodes.size();i++){
//   if(Functions::getDistance(deg.getPrimalGraph()->nodes[i]->location,Point2d(xCenter,yCenter))<=r+1){//+1 only to absorb any errors possible
//         idsNodes.push_back(i);
//   }
// }
// Grafo subgraph;
// Grafo::inducedSubgraph(deg.getPrimalGraph(),&subgraph,idsNodes);
// double l=0;
// for(long i=0;i<subgraph.links.size();i++){
//   l+=subgraph.links[i]->weight;
// }
// l-=lengthCircle;

List list(3);
// for(long i=0;i<numberObjectsDataFrame;i++){
  list[0]=(r);
  list[1]=(n);
  list[2]=(l);
// }

CharacterVector namevec;
// for(long i=0;i<numberObjectsDataFrame;i++){
  namevec.push_back("r");
  namevec.push_back("n");
  namevec.push_back("l");
// }




list.attr("names") = namevec;
DataFrame df(list);
return df;
}
















// // [[Rcpp::export]]
// void calculatePlanarDistanceAndUseItAsWeightsGraph(XPtr< Grafo > G){
//   for(long i=0;i<G->links.size();i++){
//     G->links[i]->weight=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
//   }
//
// }
//
// // [[Rcpp::export]]
// void calculateLatLonDistanceAndUseItAsWeightsGraph(XPtr< Grafo > G){
//   for(long i=0;i<G->links.size();i++){
//     G->links[i]->weight=ShapeFile::calculateDistanceLatLon(G->links[i]->A()->location,G->links[i]->B()->location);
//   }
// }

// // [[Rcpp::export]]
// double calculateHaversineDistance(double x0,double y0,double x1,double y1){
//   // for(long i=0;i<G->links.size();i++){
//     double distance=ShapeFile::calculateDistanceLatLon(Point2d(x0,y0),Point2d(x1,y1));
//     return distance;
//   // }
// }


// [[Rcpp::export]]
XPtr<Grafo> loadOSMRoads(String filename,bool directed){
  Grafo* G=new Grafo();
  OSM::loadRoads(filename,G,directed);
  Rcpp::XPtr<Grafo> p(G,true);
  return p;
}

// [[Rcpp::export]]
XPtr<DualExtendedGraph> loadOSMRoadsAndData_asDEG(String filename,bool directed){
  DualExtendedGraph* deg=new DualExtendedGraph();
  OSM::loadRoadsAndDataRoads(filename,deg,directed);
  Rcpp::XPtr<DualExtendedGraph> p(deg,true);
  return p;
}

// [[Rcpp::export]]
XPtr<Grafo> loadOSMRivers(String filename,bool directed){
  Grafo* G=new Grafo();
  OSM::loadRivers(filename,G,directed);
  Rcpp::XPtr<Grafo> p(G,true);
  return p;
}

// [[Rcpp::export]]
DataFrame loadOSMResidentialBuildingLevels(String filename){
  std::tuple<std::vector<double>,std::vector<double>,std::vector<double> > result;
  result=OSM::loadResidentialBuildingLevels(filename);



    List list(3);
    list[0]=(wrap(std::get<0>(result)));
    list[1]=(wrap(std::get<1>(result)));
    list[2]=(wrap(std::get<2>(result)));


    CharacterVector namevec;

      namevec.push_back("x");
      namevec.push_back("y");
      namevec.push_back("levels");





    list.attr("names") = namevec;
    DataFrame df(list);
    return df;
      // Rcpp::XPtr< Graph
  // return wrap(levels);
}

// [[Rcpp::export]]
List loadOSMResidentialBuildings(String filename){
  // std::tuple<std::vector<std::vector<Point2d> >,std::vector<double> > result;
  std::vector<ExtrudedGraph> buildings;
  buildings=OSM::loadResidentialBuildings(filename);

  // NumericVector xs(std::get<1>(result).size());
  // NumericVector ys(std::get<1>(result).size());
    // List list(2);
    List Gs(buildings.size());
    NumericVector numberLevels(buildings.size());
        NumericVector heights(buildings.size());
    CharacterVector buildingType(buildings.size());
    NumericVector xCentroid(buildings.size());
    NumericVector yCentroid(buildings.size());
    for(long i=0;i<buildings.size();i++){
      // std::cout<<"Building "<<i<<" from "<<buildings.size()<<'\n';
      Grafo* G=new Grafo();
      G->copyGraph(&buildings[i].G);
      Rcpp::XPtr<Grafo> p(G,true);
      Gs[i]=(p);
      numberLevels[i]=(buildings[i].numberLevels);
      buildingType[i]=(buildings[i].note);
      heights[i]=(buildings[i].totalHeight);
      xCentroid[i]=(buildings[i].centroid.x);
      yCentroid[i]=(buildings[i].centroid.y);

    }

    List list(6);
    list[0]=((Gs));
    list[1]=(numberLevels);
    list[2]=(heights);
    list[3]=(buildingType);
    list[4]=(xCentroid);
    list[5]=(yCentroid);
    // list[2]=(wrap(std::get<2>(result)));



    CharacterVector namevec;

      namevec.push_back("grafos");
      namevec.push_back("levels");
      namevec.push_back("heights");
      namevec.push_back("type");
      namevec.push_back("xCentroid");
      namevec.push_back("yCentroid");





    list.attr("names") = namevec;
    return list;
    // DataFrame df(list);
    // return df;
      // Rcpp::XPtr< Graph
  // return wrap(levels);
}

// [[Rcpp::export]]
List loadOSMBuildings(String filename){
  // std::tuple<std::vector<std::vector<Point2d> >,std::vector<double> > result;
  std::vector<ExtrudedGraph> buildings;
  buildings=OSM::loadBuildings(filename);

  // NumericVector xs(std::get<1>(result).size());
  // NumericVector ys(std::get<1>(result).size());
    // List list(2);
    List Gs(buildings.size());
    NumericVector numberLevels(buildings.size());
        NumericVector heights(buildings.size());
    CharacterVector buildingType(buildings.size());
    NumericVector xCentroid(buildings.size());
    NumericVector yCentroid(buildings.size());
    for(long i=0;i<buildings.size();i++){
      std::cout<<"Building "<<i<<" from "<<buildings.size()<<'\n';
      Grafo* G=new Grafo();
      G->copyGraph(&buildings[i].G);
      Rcpp::XPtr<Grafo> p(G,true);
      Gs[i]=(p);
      numberLevels[i]=(buildings[i].numberLevels);
      buildingType[i]=(buildings[i].note);
      heights[i]=(buildings[i].totalHeight);
      xCentroid[i]=(buildings[i].centroid.x);
      yCentroid[i]=(buildings[i].centroid.y);

    }

    List list(6);
    list[0]=((Gs));
    list[1]=(numberLevels);
    list[2]=(heights);
    list[3]=(buildingType);
    list[4]=(xCentroid);
    list[5]=(yCentroid);
    // list[2]=(wrap(std::get<2>(result)));



    CharacterVector namevec;

      namevec.push_back("grafos");
      namevec.push_back("levels");
      namevec.push_back("heights");
      namevec.push_back("type");
      namevec.push_back("xCentroid");
      namevec.push_back("yCentroid");





    list.attr("names") = namevec;
    return list;
    // DataFrame df(list);
    // return df;
      // Rcpp::XPtr< Graph
  // return wrap(levels);
}



// [[Rcpp::export]]
XPtr<Grafo> createCircleGraph(NumericVector center,double radius,double definition){
  Grafo* circle= new Grafo();
  circle->bidirectional=false;
  circle->pseudoGraph=false;
  circle->allowLoops=false;
  circle->isPlanar=true;
  double xCenter=center[0];
  double yCenter=center[1];
  double r=radius;
  // double definition=1.0;
  long numberNodes=(long)(2.0*3.1416*r/definition);
  double angleBetweenNodesRadians=2.0*3.1416/(double)(numberNodes);
  double lengthCircle=0;
  for(long i=0;i<numberNodes;i++){
    circle->addNode(Point2d(std::cos(angleBetweenNodesRadians*i)*r+xCenter,std::sin(angleBetweenNodesRadians*i)*r+yCenter));
    if(i>0){
      circle->addLink(i-1,i,Functions::getDistance(circle->nodes[i]->location,circle->nodes[i-1]->location));
      lengthCircle+=Functions::getDistance(circle->nodes[i]->location,circle->nodes[i-1]->location);
    }
    if(i==numberNodes-1){
      circle->addLink(i,0,Functions::getDistance(circle->nodes[i]->location,circle->nodes[0]->location));
      lengthCircle+=Functions::getDistance(circle->nodes[i]->location,circle->nodes[0]->location);
    }
  }
    Rcpp::XPtr<Grafo> p(circle,true);
  return p;
}


// [[Rcpp::export]]
List splitWorldPopulationByLatLon_inputInEpsg4326(DataFrame coordsEPSG4326){


  NumericVector ids=as<NumericVector>(coordsEPSG4326[0]);
  NumericVector x=as<NumericVector>(coordsEPSG4326[1]);
  NumericVector y=as<NumericVector>(coordsEPSG4326[2]);
  NumericVector numberPeople=as<NumericVector>(coordsEPSG4326[3]);

  // SparseMatrix matrix;
  std::unordered_map<Point2d, std::vector<long> > matrix;

  std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
  std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
  std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
  std::vector<double> numberPeople_=Rcpp::as<std::vector<double> > (numberPeople);

  for(long i=0;i<ids_.size();i++){
    matrix[Point2d(std::floor(x_[i]),std::floor(y_[i]))].push_back(i);
  }

  List result(matrix.size());
  long index=0;
  for(auto it:matrix){
    std::vector<long> idt;
    std::vector<double> xt;
    std::vector<double> yt;
    std::vector<double> npt;
    idt.reserve(it.second.size());
    xt.reserve(it.second.size());
    yt.reserve(it.second.size());
    npt.reserve(it.second.size());
    for(long i=0;i<it.second.size();i++){
      idt.push_back(ids_[it.second[i]]);
      xt.push_back(x_[it.second[i]]);
      yt.push_back(y_[it.second[i]]);
      npt.push_back(numberPeople_[it.second[i]]);
    }
    List list(4);
    // for(long i=0;i<numberObjectsDataFrame;i++){
      list[0]=(idt);
      list[1]=(xt);
      list[2]=(yt);
      list[3]=(npt);
    // }

    CharacterVector namevec;
    // for(long i=0;i<numberObjectsDataFrame;i++){
      namevec.push_back("id");
      namevec.push_back("x");
      namevec.push_back("y");
      namevec.push_back("numberPeople");
    // }




    list.attr("names") = namevec;
    DataFrame df(list);
    result[index]=df;
    index++;
  }





  return result;
  }


  // [[Rcpp::export]]
  List splitGraphIntoSquares_returnsIdsNodesInAList(XPtr<Grafo> G, double sizeSquares,double displacementX,double displacementY){
// G->copyGraph(Grafo);

    // NumericVector ids=as<NumericVector>(coordsEPSG4326[0]);
    // NumericVector x=as<NumericVector>(coordsEPSG4326[1]);
    // NumericVector y=as<NumericVector>(coordsEPSG4326[2]);
    // NumericVector numberPeople=as<NumericVector>(coordsEPSG4326[3]);
    //
    // // SparseMatrix matrix;
    double minX=INFINITY;
    double minY=INFINITY;
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    for(long i=0;i<G->nodes.size();i++){
      if(G->nodes[i]->location.x>maxX){
          maxX=G->nodes[i]->location.x;
      }
      if(G->nodes[i]->location.y>maxY){
          maxY=G->nodes[i]->location.y;
      }
      if(G->nodes[i]->location.x<minX){
          minX=G->nodes[i]->location.x;
      }
      if(G->nodes[i]->location.y<minY){
          minY=G->nodes[i]->location.y;
      }
    }
    double roundingFactor=sizeSquares;
    // double centeringGridX=-(std::floor((minX-displacementX)/roundingFactor)*roundingFactor-minX);
    // double centeringGridY=-(std::floor((minY-displacementY)/roundingFactor)*roundingFactor-minY);
    // double x=std::floor((minX-displacementX)/sizeSquares)*sizeSquares+centeringGridX;
    // double y=std::floor((minY-displacementY)/sizeSquares)*sizeSquares+centeringGridY;
    double x=minX;
    double y=minY;
    Grafo squareSubdivision;

    squareSubdivision.bidirectional=true;
    while (x<maxX){

      Nodo* a=squareSubdivision.addNode(Point2d(x+displacementX,y-10+displacementY));
      Nodo* b=squareSubdivision.addNode(Point2d(x+displacementX,maxY+10+displacementY));
      squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
      // a=squareSubdivision.addNode(Point2d(x+roundingFactor/100,y-10));
      // b=squareSubdivision.addNode(Point2d(x+roundingFactor/100,maxY+10));
      // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
      // a=squareSubdivision.addNode(Point2d(x-roundingFactor/100,y-10));
      // b=squareSubdivision.addNode(Point2d(x-roundingFactor/100,maxY+10));
      // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
      x+=roundingFactor;
    }
    // x=std::floor((minX-displacementX)/roundingFactor)*roundingFactor+centeringGridX;
    x=minX;
    while (y<maxY){

      Nodo* a=squareSubdivision.addNode(Point2d(x-10+displacementX,y+displacementY));
      Nodo* b=squareSubdivision.addNode(Point2d(maxX+10+displacementX,y+displacementY));
      squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
      // a=squareSubdivision.addNode(Point2d(x-10,y+roundingFactor/100));
      // b=squareSubdivision.addNode(Point2d(maxX+10,y+roundingFactor/100));
      // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
      // a=squareSubdivision.addNode(Point2d(x-10,y-roundingFactor/100));
      // b=squareSubdivision.addNode(Point2d(maxX+10,y-roundingFactor/100));
      // squareSubdivision.addLink(a->id,b->id,Functions::getDistance(a->location,b->location));
      y+=roundingFactor;
    }
    Grafo::intersectAGraphWithABoundary(G,&squareSubdivision);
     std::unordered_map<Point2d, std::vector<long> > matrix;
    //
    // std::vector<long> ids_=Rcpp::as<std::vector<long> > (ids);
    // std::vector<double> x_=Rcpp::as<std::vector<double> > (x);
    // std::vector<double> y_=Rcpp::as<std::vector<double> > (y);
    // std::vector<double> numberPeople_=Rcpp::as<std::vector<double> > (numberPeople);

    for(long i=0;i<G->nodes.size();i++){
      double epsilon=Functions::min(1.0/100000.0,roundingFactor/100.0);
      double x=std::floor((G->nodes[i]->location.x-minX-displacementX)/roundingFactor)*roundingFactor+minX;
      double y=std::floor((G->nodes[i]->location.y-minY-displacementY)/roundingFactor)*roundingFactor+minY;
      double x1=std::floor((G->nodes[i]->location.x-minX-epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
      double y1=std::floor((G->nodes[i]->location.y-minY-epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
      double x2=std::floor((G->nodes[i]->location.x-minX+epsilon-displacementX)/roundingFactor)*roundingFactor+minX;
      double y2=std::floor((G->nodes[i]->location.y-minY+epsilon-displacementY)/roundingFactor)*roundingFactor+minY;
      std::vector<double> xSec;
      std::vector<double> ySec;
      xSec.push_back(x);
      ySec.push_back(y);
      // matrix[Point2d(x,y)].push_back(i);

      // bool addSecondaryLocation=false;

      // if(x+roundingFactor/2.0>786092&&x+roundingFactor/2.0<786093&&y+roundingFactor/2.0>6002344.34&&y+roundingFactor/2.0<6002352){
      // // if(x>786092&&x<786093&&y>6002344.34&&y<6002352){
      //   std::cout<<"texting "<<x<<","<<y<<" "<<G.nodes[i]->location.x<<","<<G.nodes[i]->location.y<<" dif: "<<(x-G.nodes[i]->location.x)<<","<<(y-G.nodes[i]->location.y)<<'\n';
      // }
      if(x!=x1){
        // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
        xSec.push_back(x1);
        // addSecondaryLocation=true;
      }
      if(x!=x2){
        // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
        xSec.push_back(x2);
        // addSecondaryLocation=true;
      }
      if(y!=y1){
        // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
        ySec.push_back(y1);
        // addSecondaryLocation=true;
      }
      if(y!=y2){
        // x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor-1)*roundingFactor+minX;
        ySec.push_back(y2);
        // addSecondaryLocation=true;
      }
      // if(Functions::abs(x+roundingFactor-G.nodes[i]->location.x)<epsilon){
      //   x=std::floor((G.nodes[i]->location.x-minX)/roundingFactor+1)*roundingFactor+minX;
      //   addSecondaryLocation=true;
      // }
      // if(Functions::abs(y+roundingFactor-G.nodes[i]->location.y)<epsilon){
      //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor+1)*roundingFactor+minY;
      //   addSecondaryLocation=true;
      // }
      // if(Functions::abs(y-G.nodes[i]->location.y)<epsilon){
      //   y=std::floor((G.nodes[i]->location.y-minY)/roundingFactor-1)*roundingFactor+minY;
      //   addSecondaryLocation=true;
      // }
      // if(addSecondaryLocation){
        // std::cout<<"adding secondary location"<<'\n';
        for(long j=0;j<xSec.size();j++){
          for(long k=0;k<ySec.size();k++){
            matrix[Point2d(xSec[j],ySec[k])].push_back(i);
          }
        }
    }

    List result(matrix.size());
    long index=0;
    for(auto it:matrix){

      List list(1);
      // for(long i=0;i<numberObjectsDataFrame;i++){
        list[0]=(it.second);

      // }

      CharacterVector namevec;
      // for(long i=0;i<numberObjectsDataFrame;i++){
        namevec.push_back("id");

      // }




      list.attr("names") = namevec;
      DataFrame df(list);
      result[index]=df;
      index++;
    }





    return result;
    }








  // [[Rcpp::export]]
  XPtr<Grafo> getNormalisedGraphEvenBreaks(XPtr<Grafo> G,double breaksEach){
    Grafo* result= new Grafo();
  Grafo::getNormalisedGraphEvenBreaks(G,result,breaksEach);
      Rcpp::XPtr<Grafo> p(result,true);
    return p;
  }











        // [[Rcpp::export]]
        XPtr<Grafo> createDLA(NumericVector xs,NumericVector ys,long numberNodes,double meanStep,double neighborhoodSize,double speedTime,double randomComponent01,double randomConnectivity01,long numberNodesDirectional,long numberNodesBeforeChangingDirection,double widthDirection,double centered){
          double initWidth=neighborhoodSize*5;

          Grafo* result= new Grafo();
          result->bidirectional=true;
          // double step=1;
          double minx=INFINITY;
          double maxx=-INFINITY;
          double miny=INFINITY;
          double maxy=-INFINITY;
          // SparseMatrix matrix;
          std::unordered_map<Point2d, std::vector<long> > matrix;
          for(long i=0;i<xs.size();i++){
            double x=xs[i];
            double y=ys[i];
            // matrix.setValue(x,y,1);
            Nodo* node=result->addNode(x,y);
            matrix[Point2d(std::round(x),std::round(y))].push_back(node->id);
            if(x>maxx){
              maxx=x;
            }
            if(x<minx){
              minx=x;
            }
            if(y<miny){
              miny=y;
            }
            if(y>maxy){
              maxy=y;
            }
          }
          double direction=Functions::runiform(0,2*M_PI);
          for(long i=0;i<numberNodes;i++){
            double angle=Functions::runiform(0,2*M_PI);
            if(i<numberNodesDirectional){
              // angle=Functions::runiform(direction-widthDirection,direction+widthDirection);

              angle=direction;
              // if(Functions::runiform(0,1)<.5){
              //   angle=-angle;
              // }
            }
            direction+=Functions::runiform(-widthDirection,widthDirection);
            if(i%numberNodesBeforeChangingDirection==0){
              direction=Functions::runiform(0,2*M_PI);
            }
            initWidth=Functions::max(maxx-minx,maxy-miny)+100;
            double xc=initWidth*cos(angle)+(minx+maxx)/2.0;
            double yc=initWidth*sin(angle)+(miny+maxy)/2.0;
            // xc=Functions::runiform(minx-50,maxx+50);
            // yc=Functions::runiform(miny-50,maxy+50);
            // std::vector<double> distancesToCenters;
            double minDistance=INFINITY;
            long indexMinDistance=-1;
            for(long j=0;j<xs.size();j++){// [[Rcpp::export]]
              double distance=Functions::getDistance(Point2d(xs[j],ys[j]),Point2d(xc,yc));
              // distancesToCenters.push_back(distance);
              if(distance<minDistance){
                minDistance=distance;
                indexMinDistance=j;
              }

            }
            double xv=xs[indexMinDistance]-xc;
            double yv=ys[indexMinDistance]-yc;
            bool moving=true;
            double timeAlife=1;
            while(moving){

              double step=Functions::runiform(meanStep/2.0,meanStep);
              bool nextTo=false;
              // std::vector<long> idTemp;
              // if(matrix.getValue(std::round((xc+step*xv/sqrt(xv*xv+yv*yv))),std::round((yc+step*yv/sqrt(xv*xv+yv*yv))))>0){
              //   nextTo=true;
              // idTemp=matrix.getId(std::round((xc+step*xv/sqrt(xv*xv+yv*yv))),std::round((yc+step*yv/sqrt(xv*xv+yv*yv))));
              // }
              double xTemp=std::round(xc);
              double yTemp=std::round(yc);

              // for(long j=xTemp-1;j<=xTemp+1;j++){
              //   for(long k=yTemp-1;k<=yTemp+1;k++){
              double j=xTemp;
              double k=yTemp;
              if(matrix[Point2d(j,k)].size()>Functions::runiform(0,randomConnectivity01)*neighborhoodSize){
                nextTo=true;
                // idTemp.push_back(matrix.getId(j,k));
              }
              //   }
              // }
              if(nextTo){
                moving=false;
                if(xc>maxx){
                  maxx=xc;
                }
                if(xc<minx){
                  minx=xc;
                }
                if(yc<miny){
                  miny=yc;
                }
                if(yc>maxy){
                  maxy=yc;
                }
                Nodo* node=result->addNode((xc),(yc));
                // Nodo* node=result->addNode(xTemp,yTemp);
                if(randomConnectivity01>0){
                  for(long j=0;j<matrix[Point2d(xTemp,yTemp)].size();j++){
                    result->addLink(node->id,matrix[Point2d(xTemp,yTemp)][j],1);

                  }
                }else{
                      result->addLink(node->id,matrix[Point2d(xTemp,yTemp)][0],1);
                }
                for(long j=xTemp-neighborhoodSize;j<=xTemp+neighborhoodSize;j++){
                  for(long k=yTemp-neighborhoodSize;k<=yTemp+neighborhoodSize;k++){
                    // if(matrix.getValue(j,k)>0){
                      // nextTo=true;
                      // idTemp.push_back(matrix.getId(j,k));
                      matrix[Point2d(j,k)].push_back(node->id);
                      // matrix.setValue(j,k,1);
                    // }
                  }
                }

                if(Functions::getDistance(Point2d(0,0),Point2d(xc,yc))*3>initWidth){
                  initWidth=Functions::getDistance(Point2d(0,0),Point2d(xc,yc))*3.0;
                }

              }
              // step=1.0;
              timeAlife+=speedTime;
              double min=Functions::min(-randomComponent01,Functions::max(-1.1,-2/timeAlife));
              xc+=step*xv/sqrt(xv*xv+yv*yv)*Functions::runiform(min,1);
              yc+=step*yv/sqrt(xv*xv+yv*yv)*Functions::runiform(min,1);
               minDistance=INFINITY;
               indexMinDistance=-1;
              for(long j=0;j<xs.size();j++){// [[Rcpp::export]]
                double distance=Functions::getDistance(Point2d(xs[j],ys[j]),Point2d(xc,yc));
                // distancesToCenters.push_back(distance);
                if(distance<minDistance){
                  minDistance=distance;
                  indexMinDistance=j;
                }

              }
              if(centered){
               xv=xs[indexMinDistance]-xc;
               yv=ys[indexMinDistance]-yc;
             }else{
               Point2d randomLocation=result->nodes[std::floor(Functions::runiform(0,result->nodes.size()-1))]->location;
               xv=randomLocation.x-xc;
               yv=randomLocation.y-yc;
             }
              // xv=x-xc;
              // yv=y-yc;
              // std::cout<<"x "<<xc<<" , y "<<yc<<'\n';
            }
          }


          Rcpp::XPtr<Grafo> p(result,true);
          return p;
        }




        // [[Rcpp::export]]
        List createLSystem(double centerX,double centerY,long maxNumberNodes,double widthAngle,bool treeLike,double exponent,long maxBranching){

          Grafo* result= new Grafo();
          result->bidirectional=false;

          Nodo* node=result->addNode(Point2d(centerX,centerY));
          std::queue<Nodo*> lastNodes;
          std::queue<double> anglesPrev;
          std::queue<double> lengthsPrev;
          std::queue<double> weightsPrev;
          lastNodes.push(node);
          anglesPrev.push(M_PI/2);

          weightsPrev.push(maxNumberNodes);
          lengthsPrev.push(maxNumberNodes);

          bool first=true;
          std::vector<double> levels;

          // for(long i=0;i<numberRepetitions;i++){
          while(lastNodes.size()>0){
            // for(long k=0;k<lastNodes.size();k++){

              double anglePrev=anglesPrev.front();
              anglesPrev.pop();
              Nodo* nodePrev=lastNodes.front();
              lastNodes.pop();
              double lengthPrev=lengthsPrev.front();
              lengthsPrev.pop();
              double weightPrev=weightsPrev.front();
              weightsPrev.pop();
              // levels.push_back(weightPrev);
              long numberSons=std::floor(Functions::runiform(1,maxBranching));
              if(weightPrev<1.0){
                numberSons=0;
              }
              if(first&&treeLike){
                // first=false;
                numberSons=1;
              }

              std::vector<double> anglesDifCurrent;
              double maxAnglesDif=-INFINITY;
              double sumAnglesDif=0;
              for(long j=0;j<numberSons;j++){
                double w=Functions::min(widthAngle/(1.5*weightPrev/maxNumberNodes),widthAngle);
                // double w=M_PI/6.0;
                double random=Functions::runiform(-w,w);
                if(numberSons==1){
                  // random/=Functions::max(sqrt(weightPrev),5.0);
                  random/=2.5;
                }
                double angle=random+anglePrev;
                // if(numberSons==1){
                //    angle=Functions::rnorm(anglePrev,M_PI/40.0);
                // }
                // double angle=Functions::rnorm(anglePrev,w);
                double angleDif=Functions::abs(angle-M_PI/2.0);
                angleDif=Functions::abs(angle-anglePrev);
                anglesDifCurrent.push_back(angleDif);
                sumAnglesDif+=angleDif;
                if(maxAnglesDif<angleDif){
                  maxAnglesDif=angleDif;
                }
                // double length=lengthPrev*Functions::runiform(1.0-widthRandomLengthDown,1.0+widthRandomLengthUp)*weightPrev/maxNumberNodes;
                // double length=lengthPrev*log(weightPrev/(double)(maxNumberNodes)+1.0);
                double length=pow(weightPrev,exponent);
                // std::cout<<length<<'\n';
                if(first&&treeLike){
                  first=false;
                  angle=anglePrev;
                }

                Point2d location=Point2d(nodePrev->location.x+length*cos(angle),nodePrev->location.y+length*sin(angle));
                Nodo* currentNode=result->addNode(location);
                result->addLink(currentNode->id,nodePrev->id,length);
                // levels.push_back(levelPrev);
                lastNodes.push(currentNode);
                anglesPrev.push(angle);
                lengthsPrev.push(length);


              // }
            }
            if(anglesDifCurrent.size()>0){
              std::vector<double> invertedAnglesDif;
              double sumInvertedAnglesDif=0;

              for(long j=0;j<anglesDifCurrent.size();j++){
                invertedAnglesDif.push_back(maxAnglesDif-anglesDifCurrent[j]);
                sumInvertedAnglesDif+=maxAnglesDif-anglesDifCurrent[j];
              }
              if(anglesDifCurrent.size()==1){
                weightsPrev.push(weightPrev);
                levels.push_back(weightPrev);
              }else{
                for(long j=0;j<anglesDifCurrent.size();j++){
                  weightsPrev.push(weightPrev*(1.0-anglesDifCurrent[j]/sumAnglesDif));
                  levels.push_back(weightPrev*(1.0-anglesDifCurrent[j]/sumAnglesDif));
                }
              }
            }
          }


          Rcpp::XPtr<Grafo> p(result,true);
          List list(2);
          list[0]=p;
          list[1]=wrap(levels);

          return list;
          // return p;
        }


        // [[Rcpp::export]]
        void pushAndPullAwayNodesUsingLinks(XPtr<Grafo> G,double cutoffLength,long numberSteps,double strength){
          double maxStep=strength/100.0;
          for(long step=0;step<numberSteps;step++){
            for(long i=0;i<G->links.size();i++){
                double ax=G->links[i]->A()->location.x;
                double ay=G->links[i]->A()->location.y;
                double bx=G->links[i]->B()->location.x;
                double by=G->links[i]->B()->location.y;

                double vx=bx-ax;
                double vy=by-ay;

                vx/=sqrt(vx*vx+vy*vy);
                vy/=sqrt(vx*vx+vy*vy);

                double w=G->links[i]->weight;

                double m=Functions::min(maxStep,(cutoffLength-w)*strength);
                // double s=strength;
                ax-=m*vx;
                bx+=m*vx;
                ay-=m*vy;
                by+=m*vy;

                vx=bx-ax;
                vy=by-ay;



                if(sqrt(vx*vx+vy*vy)>0){
                  G->links[i]->A()->location.x=ax;
                  G->links[i]->A()->location.y=ay;
                  G->links[i]->B()->location.x=bx;
                  G->links[i]->B()->location.y=by;
                  G->links[i]->weight=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
                }

            }
          }

        }




                // [[Rcpp::export]]
                void pushAndPullAwayNodesUsingForceAlgorithm(XPtr<Grafo> G,long numberSteps,double strengthRepulsion,double strengthAttraction,double distanceInteraction,double cutoffLength){
                  double maxStep=distanceInteraction/100.0;
                  NodeSpatialStructure NST;
                  NST.create(G,distanceInteraction/3.0);
                  std::cout<<"Nodes inserted into spatial structure"<<'\n';
                  for(long step=0;step<numberSteps;step++){
                    std::cout<<"STEP "<<step<<'\n';
                    if(strengthRepulsion>0){
                    for(long i=0;i<G->nodes.size();i++){
                      Nodo* node=G->nodes[i];
                      std::vector<Nodo*> nodesClose=NST.getNodesAround(node,distanceInteraction);
                      double ax=node->location.x;
                      double ay=node->location.y;
                      // std::cout<<"number nodes around "<<nodesClose.size()<<'\n';
                      for(long k=0;k<nodesClose.size();k++){
                        // if(nodesClose[k]!=node)
                        double bx=nodesClose[k]->location.x;
                        double by=nodesClose[k]->location.y;

                        double vx=bx-ax;
                        double vy=by-ay;

                        vx/=sqrt(vx*vx+vy*vy);
                        vy/=sqrt(vx*vx+vy*vy);

                        double w=Functions::getDistance(node->location,nodesClose[k]->location);
                        if(w>0){
                          double m=Functions::min(strengthRepulsion/w/w,maxStep);
                          // double s=strength;
                          // ax-=m*vx;
                          bx+=m*vx;
                          // ay-=m*vy;
                          by+=m*vy;
                        }else{
                          double m=maxStep;
                          // double s=strength;
                          // ax-=m*vx;
                          bx+=m;
                          // ay-=m*vy;
                          by+=m;
                        }
                        NST.moveNode(nodesClose[k],Point2d(bx,by));


                      }
                      // node->location.x=ax;
                      // node->location.y=ay;

                    }
                  }
                  if(strengthAttraction>0){
                    for(long i=0;i<G->links.size();i++){
                        double ax=G->links[i]->A()->location.x;
                        double ay=G->links[i]->A()->location.y;
                        double bx=G->links[i]->B()->location.x;
                        double by=G->links[i]->B()->location.y;

                        double vx=bx-ax;
                        double vy=by-ay;

                        vx/=sqrt(vx*vx+vy*vy);
                        vy/=sqrt(vx*vx+vy*vy);

                        double w=G->links[i]->weight;
                        // double cutoffLength=distanceInteraction/2.0;
                        double m=-Functions::min(maxStep,Functions::max(w-cutoffLength,0.0)*strengthAttraction);
                        // double s=strength;
                        ax-=m*vx;
                        bx+=m*vx;
                        ay-=m*vy;
                        by+=m*vy;

                        vx=bx-ax;
                        vy=by-ay;



                        if(sqrt(vx*vx+vy*vy)>0){
                          NST.moveNode(G->links[i]->A(),Point2d(ax,ay));
                          NST.moveNode(G->links[i]->B(),Point2d(bx,by));
                          // G->links[i]->A()->location.x=ax;
                          // G->links[i]->A()->location.y=ay;
                          // G->links[i]->B()->location.x=bx;
                          // G->links[i]->B()->location.y=by;
                          G->links[i]->weight=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
                        }

                    }
                  }
                }

                }



                // [[Rcpp::export]]
                List createRandomWalk(long numberSteps,double w,double h,double strengthTendencyTowardsCenter){

                  Grafo* result= new Grafo();
                  result->bidirectional=true;

                  std::vector<double> speeds;

                  // double v=10;
                  // double a=-2;
                  result->addNode(Point2d(0,0));
                  double x=0;
                  double y=0;
                  for(long i=0;i<numberSteps;i++){
                    double vx=Functions::runiform(-w,w);
                    double vy=Functions::runiform(-h,h);
                    double rx=0-x;
                    double ry=0-y;
                    rx/=sqrt(rx*rx+ry*ry);
                    ry/=sqrt(rx*rx+ry*ry);
                    double s=strengthTendencyTowardsCenter;
                    if(sqrt(rx*rx+ry*ry)>0){
                    x+=vx+rx*s;
                    y+=vy+ry*s;
                  }else{
                    x+=vx;
                    y+=vy;
                  }
                    result->addNode(Point2d(x,y));

                  }



                  Rcpp::XPtr<Grafo> p(result,true);
                  // return p;
                  List list(2);
                  list[0]=p;
                  list[1]=speeds;
                  return list;
                }




    // [[Rcpp::export]]
    NumericVector getNumNodesAround(XPtr<Grafo> G,double distanceInteraction){
      // double maxStep=distanceInteraction/100.0;
      NodeSpatialStructure NST;
      NST.create(G,distanceInteraction/3.0);
      std::cout<<"Nodes inserted into spatial structure"<<'\n';
      // for(long step=0;step<numberSteps;step++){
        // std::cout<<"STEP "<<step<<'\n';
        // if(strengthRepulsion>0){
        std::vector<double> numNodesClose;
        for(long i=0;i<G->nodes.size();i++){
          Nodo* node=G->nodes[i];
          std::vector<Nodo*> nodesClose=NST.getNodesAround(node,distanceInteraction);
          numNodesClose.push_back(nodesClose.size());
        }
      // }
      return (wrap(numNodesClose));
    }


    // [[Rcpp::export]]
    void intersectAGraphWithAnother(XPtr<Grafo> G,XPtr<Grafo> other){
        Grafo::intersectAGraphWithABoundary(G,other);
    }

    // [[Rcpp::export]]
    void setMassAsAverageMassOfNeighbours(XPtr<Grafo> G,NumericVector idsNodes){
        // Grafo::intersectAGraphWithABoundary(G,other);
        for(long i=0;i<idsNodes.size();i++){
          Nodo* node=G->nodes[idsNodes[i]];
          double mass=0;
          for(long j=0;j<node->links.size();j++){
            mass+=node->links[j]->getOtherNode(node)->mass;
          }
          mass/=(double)(node->links.size());
          node->mass=mass;
        }
    }

    // [[Rcpp::export]]
    DataFrame getIntersectionsOfGraphWithAnother(XPtr<Grafo> G,XPtr<Grafo> G2){
      InterfaceIntersectionObject interface;
      interface=Grafo::intersectAGraphWithAnother(G,G2);
      // std::cout<<interface.intersections[0].x<<" "<<interface.intersections[0].y;
      std::vector<double> xs;
      std::vector<double> ys;
      std::vector<long> idsIntersected;

      xs.resize(interface.intersections.size(),0);
      ys.resize(interface.intersections.size(),0);
      idsIntersected.resize(interface.idsIntersected.size(),0);
      for(long i=0;i<interface.intersections.size();i++){
        xs[i]=interface.intersections[i].x;
        ys[i]=interface.intersections[i].y;
        idsIntersected[i]=interface.idsIntersected[i][0];
      }
      List list(3);
      list[0]=wrap(xs);
      list[1]=wrap(ys);
      list[2]=wrap(idsIntersected);
      CharacterVector namevec;
      // // for(long i=0;i<numberObjectsDataFrame;i++){
        namevec.push_back("x");
        namevec.push_back("y");
        namevec.push_back("idsIntersected");
      // // }




      list.attr("names") = namevec;
      DataFrame df(list);

      return df;
      //
      // return list;
    }

    // [[Rcpp::export]]
    NumericVector collapseCitiesUsingRiversReturnNewClusters(XPtr<DualExtendedGraph> deg,XPtr<DualExtendedGraph> riversDEG,NumericVector currentClustersCities,String method){

        std::vector<long> currentClustersCitiesNodes;
        std::vector<long> clustersLinks=Rcpp::as<std::vector<long> >(currentClustersCities);
        Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),clustersLinks,currentClustersCitiesNodes);

        std::vector<long> idsLinksConnecting2Cities;
        Grafo* G=getPrimalGraph(deg);
        NumericVector newClusters(G->links.size(),-1);
        std::unordered_map<long,std::vector<long> > idLinksPerClusterId;

        if(method!="intersections"){
          NodeSpatialStructure NST;
          NST.create(getPrimalGraph(riversDEG),1000);
          for(long i=0;i<G->links.size();i++){
            newClusters[i]=currentClustersCities[i];
            idLinksPerClusterId[currentClustersCities[i]].push_back(i);
            Nodo* a=G->links[i]->A();
            Nodo* b=G->links[i]->B();
            if (currentClustersCitiesNodes[a->id]!=-1&&currentClustersCitiesNodes[b->id]!=-1&&currentClustersCitiesNodes[a->id]!=currentClustersCitiesNodes[b->id]){
              double lengthLink=Functions::getDistance(a->location,b->location);
              std::vector<Nodo*> nodesAroundA=NST.getNodesAround(a->location,lengthLink);
              std::vector<Nodo*> nodesAroundB=NST.getNodesAround(b->location,lengthLink);
              if(lengthLink<5000&&(nodesAroundA.size()>0||nodesAroundB.size()>0)){
                idsLinksConnecting2Cities.push_back(i);
              }
            }
          }
        }else{
          InterfaceIntersectionObject interface=Grafo::intersectAGraphWithAnother(G,riversDEG->getPrimalGraph());
          for(long i=0;i<G->links.size();i++){
            newClusters[i]=currentClustersCities[i];
            idLinksPerClusterId[currentClustersCities[i]].push_back(i);
          }
          for(long i=0;i<interface.idsIntersected.size();i++){
            long id=interface.idsIntersected[i][0];
            Nodo* a=G->links[id]->A();
            Nodo* b=G->links[id]->B();
            if (currentClustersCitiesNodes[a->id]!=-1&&currentClustersCitiesNodes[b->id]!=-1&&currentClustersCitiesNodes[a->id]!=currentClustersCitiesNodes[b->id]){
              idsLinksConnecting2Cities.push_back(id);
            }
          }


        }
        for(long i=0;i<idsLinksConnecting2Cities.size();i++){
          Nodo* a=G->links[idsLinksConnecting2Cities[i]]->A();
          Nodo* b=G->links[idsLinksConnecting2Cities[i]]->B();
          long idA=currentClustersCitiesNodes[a->id];
          long idB=currentClustersCitiesNodes[b->id];
          if(idA!=idB){
            for(long j=0;j<idLinksPerClusterId[idB].size();j++){
              newClusters[idLinksPerClusterId[idB][j]]=idA;
              currentClustersCitiesNodes[G->links[idLinksPerClusterId[idB][j]]->A()->id]=idA;
              currentClustersCitiesNodes[G->links[idLinksPerClusterId[idB][j]]->B()->id]=idA;
              idLinksPerClusterId[idA].push_back(idLinksPerClusterId[idB][j]);
            }
            // std::swap(idLinksPerClusterId[idB],std::vector<long>());
            idLinksPerClusterId[idB].clear();
          }
        }
        return((newClusters));

    }
    // [[Rcpp::export]]
    NumericVector collapseCitiesUsingIntersectionsWithRiversReturnNewClusters(XPtr<DualExtendedGraph> deg,NumericVector currentClustersCities,NumericVector idsIntersectedLinks){

        std::vector<long> currentClustersCitiesNodes;
        std::vector<long> clustersLinks=Rcpp::as<std::vector<long> >(currentClustersCities);
        Grafo::transformColorsLinksIntoColorsNodes(deg->getPrimalGraph(),clustersLinks,currentClustersCitiesNodes);
        // NodeSpatialStructure NST;
        // NST.create(getPrimalGraph(riversDEG),1000);
        std::vector<long> idsLinksConnecting2Cities;
        Grafo* G=getPrimalGraph(deg);
        NumericVector newClusters(G->links.size(),-1);
        std::unordered_map<long,std::vector<long> > idLinksPerClusterId;

        // if(method!="intersections"){
        //   for(long i=0;i<G->links.size();i++){
        //     newClusters[i]=currentClustersCities[i];
        //     idLinksPerClusterId[currentClustersCities[i]].push_back(i);
        //     Nodo* a=G->links[i]->A();
        //     Nodo* b=G->links[i]->B();
        //     if (currentClustersCitiesNodes[a->id]!=-1&&currentClustersCitiesNodes[b->id]!=-1&&currentClustersCitiesNodes[a->id]!=currentClustersCitiesNodes[b->id]){
        //       double lengthLink=Functions::getDistance(a->location,b->location);
        //       std::vector<Nodo*> nodesAroundA=NST.getNodesAround(a->location,lengthLink);
        //       std::vector<Nodo*> nodesAroundB=NST.getNodesAround(b->location,lengthLink);
        //       if(lengthLink<5000&&(nodesAroundA.size()>0||nodesAroundB.size()>0)){
        //         idsLinksConnecting2Cities.push_back(i);
        //       }
        //     }
        //   }
        // }else{
          // InterfaceIntersectionObject interface=Grafo::intersectAGraphWithAnother(G,riversDEG->getPrimalGraph());
          for(long i=0;i<G->links.size();i++){
            newClusters[i]=currentClustersCities[i];
            idLinksPerClusterId[currentClustersCities[i]].push_back(i);
          }
          for(long i=0;i<idsIntersectedLinks.size();i++){
            long id=idsIntersectedLinks[i];
            Nodo* a=G->links[id]->A();
            Nodo* b=G->links[id]->B();
            if (currentClustersCitiesNodes[a->id]!=-1&&currentClustersCitiesNodes[b->id]!=-1&&currentClustersCitiesNodes[a->id]!=currentClustersCitiesNodes[b->id]){
              idsLinksConnecting2Cities.push_back(id);
            }
          }


        // }
        for(long i=0;i<idsLinksConnecting2Cities.size();i++){
          Nodo* a=G->links[idsLinksConnecting2Cities[i]]->A();
          Nodo* b=G->links[idsLinksConnecting2Cities[i]]->B();
          long idA=currentClustersCitiesNodes[a->id];
          long idB=currentClustersCitiesNodes[b->id];
          if(idA!=idB){
            for(long j=0;j<idLinksPerClusterId[idB].size();j++){
              newClusters[idLinksPerClusterId[idB][j]]=idA;
              currentClustersCitiesNodes[G->links[idLinksPerClusterId[idB][j]]->A()->id]=idA;
              currentClustersCitiesNodes[G->links[idLinksPerClusterId[idB][j]]->B()->id]=idA;
              idLinksPerClusterId[idA].push_back(idLinksPerClusterId[idB][j]);
            }
            // std::swap(idLinksPerClusterId[idB],std::vector<long>());
            idLinksPerClusterId[idB].clear();
          }
        }
        return((newClusters));

    }



    // [[Rcpp::export]]
    double getApproxDiameterCityByRotatingBoundary(XPtr<Grafo> boundary){
       double maxX=-INFINITY;
       double minX=INFINITY;
       double maxY=-INFINITY;
       double minY=INFINITY;
       Point2d centroid(0,0);
       for(long i=0;i<boundary->nodes.size();i++){
           centroid.x+=boundary->nodes[i]->location.x;
           centroid.y+=boundary->nodes[i]->location.y;
           if(boundary->nodes[i]->location.x>maxX){
               maxX=boundary->nodes[i]->location.x;
           }
           if(boundary->nodes[i]->location.y>maxY){
               maxY=boundary->nodes[i]->location.y;
           }
           if(boundary->nodes[i]->location.x<minX){
               minX=boundary->nodes[i]->location.x;
           }
           if(boundary->nodes[i]->location.y<minY){
               minY=boundary->nodes[i]->location.y;
           }
       }

       centroid.x/=(double)(boundary->nodes.size());
       centroid.y/=(double)(boundary->nodes.size());

       double diameter=0;

      for(double angle=0.0;angle<M_PI;angle+=M_PI/50.0){
        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;
        for(long i=0;i<boundary->nodes.size();i++){
          double initialAngle=Functions::getAngleRadians(centroid,boundary->nodes[i]->location);
          double distance=Functions::getDistance(centroid,boundary->nodes[i]->location);
          double newx=centroid.x+cos(initialAngle+angle)*distance;
          double newy=centroid.y+sin(initialAngle+angle)*distance;

          if(newx>maxX){
              maxX=newx;
          }
          if(newy>maxY){
              maxY=newy;
          }
          if(newx<minX){
              minX=newx;
          }
          if(newy<minY){
              minY=newy;
          }

        }
        diameter=Functions::max(diameter,Functions::max(maxX-minX,maxY-minY));

      }
      return diameter;
    }


    // [[Rcpp::export]]
    double getDiameterCityUsingConvexHull(XPtr<Grafo> G,XPtr<Grafo> hull){
      // std::vector<long> identifiers;
      // identifiers.resize(hull->nodes.size(),-1);
      // std::unordered_map<std::string,long> idsByIdentifier;
      // for(long i=0;i<G->nodes.size();i++){
      //
      // }
      // for(long i=0;i<hull->nodes.size();i++){
      //   identifiers[i]=stol(hull->nodes[i]->identifier);
      // }

      double diameter=0;
      InterfaceDijkstra result;
      if(hull->nodes.size()>2){


      std::vector<Number*> numbersRepresentingNodes;
        std::vector<bool> inDijkstra;
        std::vector<bool> inCutoff;
      Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
      double distanceLimit=0;
      // for(long i=0;i<G->nodes.size();i++){
      for(long i=0;i<hull->nodes.size();i++){

      long nodeID=G->getNodeByLocation(hull->nodes[i]->location)->id;
      // std::cout<<nodeID<<'\n';
      if(nodeID!=-1){
        // std::cout<<"number of links departing from node "<<G->nodes[nodeID]->links.size()<<'\n';
      Grafo::calculateDijkstra(G,G->nodes[nodeID],result,distanceLimit,numbersRepresentingNodes,inDijkstra,inCutoff);
        for(long j=0;j<G->nodes.size();j++){
          if(std::isfinite(result.getMinDistance(j))&&result.getMinDistance(j)>diameter){
            diameter=result.getMinDistance(j);
          }
        }
      }

      }
// std::cout<<"finished calculating distances"<<'\n';
        // std::vector<double> valuesToPass=as<std::vector<double> > (massesNodes);
        // Grafo::calculateCloseness(G,result,closeness);
        // result.reset();
      // }
      // std::cout<<"finished"<<'\n';
     Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
   }

     return diameter;
    }











    // [[Rcpp::export]]
    DataFrame multiplyPoints (NumericVector x,NumericVector y,NumericVector values,double originalSpacing,double definition){
        // NumericVector newX(x.size()*definition*definition);
        // NumericVector newY(y.size()*definition*definition);
        // NumericVector newValues(values.size()*definition*definition);

        NumericVector newX(x.size()*definition);
        NumericVector newY(y.size()*definition);
        NumericVector newValues(values.size()*definition);

        double sep=originalSpacing/(definition);
        double angleSep=2*M_PI/(definition);
        long counter=0;
        for(long i=0;i<x.size();i++){
          for(long j=0;j<(definition);j++){
            // for(long h=0;h<(definition);h++){
              // newX[counter]=x[i]-originalSpacing/2.0+sep*j+sep/2.0;
              // newY[counter]=y[i]-originalSpacing/2.0+sep*h+sep/2.0;
              // newValues[counter]=values[i]/definition/definition;
              newX[counter]=x[i]+cos(angleSep*j)*originalSpacing*2/3/2;
              newY[counter]=y[i]+sin(angleSep*j)*originalSpacing*2/3/2;
              // newX[counter]=x[i]-originalSpacing/2.0+Functions::runiform(0,originalSpacing);
              // newY[counter]=y[i]-originalSpacing/2.0+Functions::runiform(0,originalSpacing);
              newValues[counter]=values[i]/definition;
              counter++;
            // }
          }
        }
        // for(long i=0;i<y.size();i++){
        //   for(long j=1;j<11;j++){
        //     newX[i]=x[i]-originalSpacing+sep*j;
        //   }
        // }


                List list(3);
                list[0]=wrap(newX);
                list[1]=wrap(newY);
                list[2]=wrap(newValues);
                // list[3]=wrap(zsInOrder);
                // list[4]=wrap(sizesInOrder);
                CharacterVector namevec;
                // // for(long i=0;i<numberObjectsDataFrame;i++){
                // namevec.push_back("id");
                  namevec.push_back("x");
                  namevec.push_back("y");
                  // namevec.push_back("z");
                  namevec.push_back("values");
                // // }




                list.attr("names") = namevec;
                DataFrame df(list);

                return df;
    }



    double calculateAreaUsingGriddedPoints_cpp (Grafo* boundary,double lengthSidePixel){
      bool quick=true;
      double displacementX=0;
      double displacementY=0;
      // double minSide=INFINITY;
      // for(long i=0;i<sideBoxes.size();i++){
      //   if(sideBoxes[i]<minSide){
      //     minSide=sideBoxes[i];
      //   }
      // }
      // double lengthSidePixel=minSide/4.0;
      double roundingFactor=lengthSidePixel;

      double minX=INFINITY;
      double minY=INFINITY;
      double maxX=-INFINITY;
      double maxY=-INFINITY;
      for(long i=0;i<boundary->nodes.size();i++){
        if(boundary->nodes[i]->location.x>maxX){
          maxX=boundary->nodes[i]->location.x;
        }
        if(boundary->nodes[i]->location.y>maxY){
          maxY=boundary->nodes[i]->location.y;
        }
        if(boundary->nodes[i]->location.x<minX){
          minX=boundary->nodes[i]->location.x;
        }
        if(boundary->nodes[i]->location.y<minY){
          minY=boundary->nodes[i]->location.y;
        }
      }


      Grafo boundaryGrid;
      SparseMatrix boundaryMatrix;
      for(double x=minX;x<=maxX;x+=lengthSidePixel){
        for(double y=minY;y<=maxY;y+=lengthSidePixel){
          boundaryGrid.addNode(Point2d(x,y));
        }

      }
      Grafo withinBoundary;
      GeometryGraph::getSubgraphWithinABoundary(&boundaryGrid,boundary,&withinBoundary);

      return (double)(withinBoundary.nodes.size())*lengthSidePixel*lengthSidePixel;
    }




        // [[Rcpp::export]]
        double calculateAreaUsingGriddedPoints (XPtr<Grafo> boundary,double lengthSidePixel){
          return (calculateAreaUsingGriddedPoints(boundary,lengthSidePixel));
        }
















        // [[Rcpp::export]]
        NumericVector assignEachNodeToAClusterUsingHI_hillClimbing (XPtr<DualExtendedGraph> deg,NumericVector z,double minZ,double tolerance){
          Grafo* G=getPrimalGraph(deg);
          std::vector<long> clusters;
          // clusters.reserve(G->nodes.size());
          clusters.resize(G->nodes.size(),-1);
          // for(long i=0;i<G->nodes.size();i++){
          //   clusters.push_back(i);
          // }
          std::vector<double> hi_=Rcpp::as<std::vector<double> >(z);
          std::vector<long> order=Functions::getIndexesOfOrderedValues(hi_,false);
          std::vector<bool> used;
          used.resize(z.size(),false);
          std::deque<long> idNodesToExpand;
          idNodesToExpand.push_back(order[0]);
          long maxClusters=0;
          long numberToExpand=z.size();
          long numberExpanded=0;
          // for(long i=0;i<order.size();i++){
          long i=0;
          while(i<z.size()){

          while(idNodesToExpand.size()>0){
              // long index=order[i];

              long index=idNodesToExpand.front();
              idNodesToExpand.pop_front();
              if(!used[index]){
                used[index]=true;
                numberExpanded++;
                double hic=hi_[index];
                for(long j=0;j<G->nodes[index]->links.size();j++){
                  if(hic-hi_[G->nodes[index]->links[j]->getOtherNode(G->nodes[index])->id]>-tolerance&&hi_[G->nodes[index]->links[j]->getOtherNode(G->nodes[index])->id]>=minZ){
                    if(clusters[index]==-1){
                      clusters[index]=maxClusters;
                      maxClusters++;
                    }
                    if(clusters[G->nodes[index]->links[j]->getOtherNode(G->nodes[index])->id]==-1){
                      clusters[G->nodes[index]->links[j]->getOtherNode(G->nodes[index])->id]=clusters[index];
                    }
                    idNodesToExpand.push_back(G->nodes[index]->links[j]->getOtherNode(G->nodes[index])->id);
                  }
                }
              }
            }

            // while(used[i]&&i<z.size()-1){
                i++;
            // }
            if(i<z.size()){
              idNodesToExpand.push_front(order[i]);
            }


          }
          return (wrap(clusters));
        }






        // [[Rcpp::export]]
        NumericVector getDistancesOfLinks (XPtr<Grafo> G){
          std::vector<double> distances;
          distances.resize(G->links.size(),0);
          for(long i=0;i<G->links.size();i++){
            double distance=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
            distances[i]=distance;
          }
          return wrap(distances);


        }

        // [[Rcpp::export]]
        NumericVector getDistancesOfLinksPrimal (XPtr<DualExtendedGraph> deg){
          std::vector<double> distances;
          distances.resize(deg->getPrimalGraph()->links.size(),0);
          for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
            double distance=Functions::getDistance(deg->getPrimalGraph()->links[i]->A()->location,deg->getPrimalGraph()->links[i]->B()->location);
            distances[i]=distance;
          }
          return wrap(distances);


        }
        // [[Rcpp::export]]
        NumericVector getDistancesOfLinksPrimal_latLon (XPtr<DualExtendedGraph> deg){
          std::vector<double> distances;
          distances.resize(deg->getPrimalGraph()->links.size(),0);
          for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
            double distance=ShapeFile::calculateDistanceLatLon(deg->getPrimalGraph()->links[i]->A()->location.x,deg->getPrimalGraph()->links[i]->A()->location.y,deg->getPrimalGraph()->links[i]->B()->location.x,deg->getPrimalGraph()->links[i]->B()->location.y);
            distances[i]=distance;
          }
          return wrap(distances);


        }

        // [[Rcpp::export]]
        void setMetricWeights (XPtr<Grafo> G){
          std::vector<double> distances;
          // distances.resize(G->links.size(),0);
          for(long i=0;i<G->links.size();i++){
            double distance=Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
            G->links[i]->weight=distance;
            // distances[i]=distance;
          }
          // return wrap(distances);


        }
        // [[Rcpp::export]]
        void setMetricWeightsPrimal (XPtr<DualExtendedGraph> deg){
          std::vector<double> distances;
          // distances.resize(G->links.size(),0);
          for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
            double distance=Functions::getDistance(deg->getPrimalGraph()->links[i]->A()->location,deg->getPrimalGraph()->links[i]->B()->location);
            deg->getPrimalGraph()->links[i]->weight=distance;
            // distances[i]=distance;
          }
          // return wrap(distances);


        }

        // [[Rcpp::export]]
        NumericVector getDistancesLatLon(NumericVector lon1,NumericVector lat1,NumericVector lon2,NumericVector lat2){//haversine formula
          std::vector<double> distances;
          distances.reserve(lon1.size());
          for(long i=0;i<lon1.size();i++){
            distances.push_back(ShapeFile::calculateDistanceLatLon(lon1[i],lat1[i],lon2[i],lat2[i]));
          }
          return(wrap(distances));
        }


        // [[Rcpp::export]]
        void setMetricWeightsLatLon (XPtr<Grafo> G){
          std::vector<double> distances;
          // distances.resize(G->links.size(),0);
          for(long i=0;i<G->links.size();i++){
            double distance=ShapeFile::calculateDistanceLatLon(G->links[i]->A()->location.x,G->links[i]->A()->location.y,G->links[i]->B()->location.x,G->links[i]->B()->location.y);
            // Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
            G->links[i]->weight=distance;
            // distances[i]=distance;
          }
          // return wrap(distances);


        }
        // [[Rcpp::export]]
        void setMetricWeightsLatLon_Primal (XPtr<DualExtendedGraph> deg){
          std::vector<double> distances;
          // distances.resize(G->links.size(),0);
          for(long i=0;i<deg->getPrimalGraph()->links.size();i++){
            double distance=ShapeFile::calculateDistanceLatLon(deg->getPrimalGraph()->links[i]->A()->location.x,deg->getPrimalGraph()->links[i]->A()->location.y,deg->getPrimalGraph()->links[i]->B()->location.x,deg->getPrimalGraph()->links[i]->B()->location.y);
            // Functions::getDistance(G->links[i]->A()->location,G->links[i]->B()->location);
            deg->getPrimalGraph()->links[i]->weight=distance;
            // distances[i]=distance;
          }
          // return wrap(distances);


        }




        // [[Rcpp::export]]
        NumericVector soften3d(XPtr<DualExtendedGraph> deg,NumericVector z,NumericVector moduleDerivative){
          // std::vector<double> distances;
          // distances.resize(deg->getPrimalGraph()->links.size(),0);
          double maxHeight=-INFINITY;
          double minHeight=INFINITY;
          double maxDerivative=-INFINITY;
          double minDerivative=INFINITY;
          for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
            if(z[i]>maxHeight){
              maxHeight=z[i];
            }
            if(z[i]<minHeight){
              minHeight=z[i];
            }
            if(maxDerivative<moduleDerivative[i]){
              maxDerivative=moduleDerivative[i];
            }
            if(minDerivative>moduleDerivative[i]){
              minDerivative=moduleDerivative[i];
            }
          }
          NumericVector z_(z.size());
          for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
            z_[i]=z[i];
            // double meanHeightNeighbours=0;
            // for(long j=0;j<deg->getPrimalGraph()->nodes[i]->links.size();j++){
            //   meanHeightNeighbours+=z[deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->id]/(double)(deg->getPrimalGraph()->nodes[i]->links.size());
            // }
            double num=0;
            for(long j=0;j<deg->getPrimalGraph()->nodes[i]->links.size();j++){
              long otherIndex=deg->getPrimalGraph()->nodes[i]->links[j]->getOtherNode(deg->getPrimalGraph()->nodes[i])->id;
              // if((z[i]-minHeight)/(maxHeight-minHeight)>Functions::runiform(0,1)){
                z_[i]+=z[otherIndex]*(moduleDerivative[i]-minDerivative)/(maxDerivative-minDerivative);
                num+=(moduleDerivative[i]-minDerivative)/(maxDerivative-minDerivative);
              // }else{
              //   z_[i]+=z[i]*.99;
              //   num++;
              // }
            }
            if(num>0){
              z_[i]/=(double)(num+1.0);
            }
          }
          return z_;


        }




  // [[Rcpp::export]]
  DataFrame loadOSMAmenities(String filename){
    // std::vector<double> xs;
    // std::vector<double> ys;
    // std::vector<std::string> types;


    // // [[Rcpp::export]]
    // XPtr<Grafo> loadOSMRoads(String filename,bool directed){
    //   Grafo* G=new Grafo();
    std::tuple<std::vector<double>,std::vector<double>,std::vector<std::string> > result;
    result=OSM::loadAmenities(filename);
    // OSM::loadAmenities(filename);

  //   Rcpp::XPtr<Grafo> p(G,true);
  //   return p;
  // }





    List list(3);
    list[0]=wrap(std::get<0>(result));
    list[1]=wrap(std::get<1>(result));
    list[2]=wrap(std::get<2>(result));

    // list[3]=wrap(zsInOrder);
    // list[4]=wrap(sizesInOrder);
    CharacterVector namevec;
    // // for(long i=0;i<numberObjectsDataFrame;i++){
    // namevec.push_back("id");
      namevec.push_back("x");
      namevec.push_back("y");
      namevec.push_back("type");
      // namevec.push_back("sizes");
    // // }




    list.attr("names") = namevec;
    DataFrame df(list);

    return df;
  }


  // [[Rcpp::export]]
  DataFrame getIndexNodesClosestToNodesInOtherGraph(XPtr<Grafo>  G,XPtr<Grafo> og,double definition){
    NodeSpatialStructure nsp;
    nsp.create(og,definition);

    NumericVector ids;
    NumericVector idsOG;

    for(long i=0;i<G->nodes.size();++i){
      ids.push_back(G->nodes[i]->originalID);
      idsOG.push_back(nsp.getIdClosestNodeInOtherGraph(G->nodes[i],og,definition));

    }



    List list(2);
    list[0]=ids;
    list[1]=idsOG;
    // list[2]=wrap(std::get<2>(result));

    // list[3]=wrap(zsInOrder);
    // list[4]=wrap(sizesInOrder);
    CharacterVector namevec;
    // // for(long i=0;i<numberObjectsDataFrame;i++){
    // namevec.push_back("id");
      namevec.push_back("id");
      namevec.push_back("indexInOtherGraph");
      // namevec.push_back("type");
      // namevec.push_back("sizes");
    // // }




    list.attr("names") = namevec;
    DataFrame df(list);

    return df;
  }

// [[Rcpp::export]]
long calculateTopologicalDistancesInATreeBetweenTwoNodes(XPtr<Grafo> tree,long idA,long idB){
  return(Tree::calculateTopologicalDistancesInATreeBetweenTwoNodes(tree,idA,idB));
}


// [[Rcpp::export]]
NumericMatrix getDistanceMatrixOfATree(XPtr<Grafo> tree) {
  int n = tree->nodes.size();
  NumericMatrix d = no_init_matrix(n, n);

  for(int i=0; i<n;i++){
    for(int j=i+1; j<n;j++){
      d(i,j)=Tree::calculateTopologicalDistancesInATreeBetweenTwoNodes(tree,tree->nodes[i]->id,tree->nodes[j]->id);
      d(j,i)=d(i,j);
    }

    d(i,i)=0;

  }
  return d;
}



// [[Rcpp::export]]
long percolationOnALattice_sizeGC(double p,long radius,int k,int d){
      // std::unordered_map<long,double>& map;
      // double size=radius*radius*probability;
      // for(long i=0;i<size;i++){
      //   map[]
      // }
      long numToExplore=1;
      if(p==0){
        numToExplore=0;
      }
      long size=0;
      bool ft=true;
      if(p<1){
      while(numToExplore>0){
        numToExplore--;
        size++;
        if(ft){
        for(int j=0;j<k;j++){
          if(Functions::runiform(0,1)<=p){
            numToExplore++;
          }
        }
        ft=false;
      }else{
        for(int j=0;j<(k-1);j++){
          if(Functions::runiform(0,1)<=p){
            numToExplore++;
          }
        }
      }
      if(size>=pow(radius,d)){
        numToExplore=0;
      }
      }
    }else{
      size=pow(radius,d);
    }
    return size;
}


// [[Rcpp::export]]
DataFrame percolationTypical2dGrid(double p,long radius){
      std::unordered_map<long,double> map;
      long cols=radius;
      long rows=radius;
      double numOcc=0;
      // double numGiant=0;
      double total=radius*radius;
      Grafo* G=new Grafo();
      G->bidirectional=true;

      long id=0;
      for(long i=0;i<cols;i++){
        for(long j=0;j<rows;j++){
          long index=i*cols+j;
          if(Functions::runiform(0,1)<=p){
            map[index]=id;
            id++;
            G->addNode(Point2d(i,j));
            double idOther=Functions::getValueAt(map,i*cols+(j-1),-1);
            if(idOther!=-1){
              G->addLink(id-1,idOther,1);
            }
            idOther=Functions::getValueAt(map,i*cols+(j+1),-1);
            if(idOther!=-1){
              G->addLink(id-1,idOther,1);
            }
            idOther=Functions::getValueAt(map,(i-1)*cols+(j),-1);
            if(idOther!=-1){
              G->addLink(id-1,idOther,1);
            }
            idOther=Functions::getValueAt(map,(i+1)*cols+(j),-1);
            if(idOther!=-1){
              G->addLink(id-1,idOther,1);
            }
            numOcc++;
          }
        }
      }
      double areaGiant=0;
      long numGiant=0;
      long numSecond=0;
      long numThird=0;
      long numFourth=0;
      long numComponents=0;
      long areaGiantTight=0;
      if(numOcc>0){

      map.clear();
      std::vector<Grafo> components;
      Grafo::getComponents(G,components,0);
      numComponents=components.size();
      // long maxSize=0;
      std::vector<long> sizes;
      sizes.reserve(components.size());
      long indexMax=-1;
      long maxSize=0;
      for(long i=0;i<components.size();i++){
        sizes.push_back(components[i].nodes.size());
        if(maxSize<components[i].nodes.size()){
          maxSize=components[i].nodes.size();
          indexMax=i;
        }
      }
      Grafo* boundary;

      if(indexMax>=0&&components[indexMax].nodes.size()>0){
      boundary=generateBoundaryFromGriddedObject_cpp(&components[indexMax],1);
      areaGiantTight=calculateAreaUsingGriddedPoints_cpp(boundary,1);
        double minx=INFINITY;
        double maxx=-INFINITY;
        double miny=INFINITY;
        double maxy=-INFINITY;

        for(long i=0;i<components[indexMax].nodes.size();i++){
          if(components[indexMax].nodes[i]->location.x<minx){
            minx=components[indexMax].nodes[i]->location.x;
          }
          if(components[indexMax].nodes[i]->location.x>maxx){
            maxx=components[indexMax].nodes[i]->location.x;
          }
          if(components[indexMax].nodes[i]->location.y<miny){
            miny=components[indexMax].nodes[i]->location.y;
          }
          if(components[indexMax].nodes[i]->location.y>maxy){
            maxy=components[indexMax].nodes[i]->location.y;
          }

        }
        areaGiant=(maxx-minx+1)*(maxy-miny+1);

      }
      // delete boundary;
      delete G;
      // asdf

      // std::vector<long> orderedSizes;
      // static std::vector<double> orderValues(std::vector<double>& values,bool minToMax);
      Functions::orderValues(sizes,false);

      if(sizes.size()>0){
        numGiant=sizes[0];
      }

      if(sizes.size()>1){
        numSecond=sizes[1];
      }

      if(sizes.size()>2){
        numThird=sizes[2];
      }

      if(sizes.size()>3){
        numFourth=sizes[3];
      }
    }
      List list(8);
      list[0]=numOcc;
      list[1]=numGiant;
      list[2]=numSecond;
      list[3]=numThird;
      list[4]=numFourth;
      list[5]=numComponents;
      list[6]=areaGiant;
      list[7]=areaGiantTight;
      // list[2]=wrap(std::get<2>(result));

      // list[3]=wrap(zsInOrder);
      // list[4]=wrap(sizesInOrder);
      CharacterVector namevec;
      // // for(long i=0;i<numberObjectsDataFrame;i++){
      // namevec.push_back("id");
        namevec.push_back("nSitesOccupied");
        namevec.push_back("sizeGiant");
        namevec.push_back("sizeSecond");
        namevec.push_back("sizeThird");
        namevec.push_back("sizeFourth");
        namevec.push_back("numClusters");
        namevec.push_back("areaGiantCluster");
        namevec.push_back("areaGiantClusterTight");
        // namevec.push_back("type");
        // namevec.push_back("sizes");
      // // }




      list.attr("names") = namevec;
      DataFrame df(list);

      return df;

}



// [[Rcpp::export]]
DataFrame createTriangularGrid(double minx,double maxx,double miny,double maxy,double sep){
  // std::tuple<std::vector<double>, std::vector<double> > result= Grafo::getPointsEvenBreaks(G,breaksEach);
  std::vector<double> xs;
  std::vector<double> ys;
  for(double i=0;i<(maxx-minx)/sep;i++){
    for(double j=0;j<(maxy-miny)/sep;j++){
      if((long)(j)%2==0){
        xs.push_back(i*sep+minx);
      }else{
        xs.push_back((i+.5)*sep+minx);
      }
      ys.push_back(j*sep+miny);
    }
  }
  List list(2);
  list[0]=xs;
  list[1]=ys;

  CharacterVector namevec;
  namevec.push_back("x");
  namevec.push_back("y");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



// [[Rcpp::export]]
DataFrame calculatePopInEachSupermarket(DataFrame population,DataFrame supermarkets,DataFrame popsup,double exponent){
  // std::tuple<std::vector<double>, std::vector<double> > result= Grafo::getPointsEvenBreaks(G,breaksEach);
  NumericVector idsPop=as<NumericVector>(population[0]);
  NumericVector pops=as<NumericVector>(population[3]);
  NumericVector idsSup=as<NumericVector>(supermarkets[0]);
  NumericVector idA=as<NumericVector>(popsup[0]);
  NumericVector idB=as<NumericVector>(popsup[1]);
  NumericVector d=as<NumericVector>(popsup[2]);

  std::vector<double> popInSup;
  popInSup.resize(idsSup.size(),0.0);


  long i=0;
  while(i<idA.size()){
    long idPop=idA[i];
    std::cout<<idPop<<'\n';
    std::deque<long> idsSupTemp;
    std::deque<double> distances;
    std::deque<double> probs;
    double n=0;
    while(idA[i]==idPop){
      long idBi=idB[i];
      idsSupTemp.push_back(idBi);
      if(d[i]>=100){
        double di=d[i];
        distances.push_back(di);
      }else{
        distances.push_back(100.0);
      }
      n++;
      i++;
    }
    double probTotal=0.0;
    for(long j=0;j<distances.size();j++){
      double prob=1.0/pow(distances.at(j),exponent);
      // double prob=1.0*exp(-exponent*distances.at(j)/1000.0);
      // double prob=2.888701081/(distances.at(j)*distances.at(j));
      probs.push_back(prob);
      probTotal+=prob;
    }
    double pop=pops[idPop];
    for(long j=0;j<distances.size();j++){
      popInSup[idsSupTemp[j]]+=probs[j]/probTotal*pop;
    }
  }





  List list(2);
  list[0]=idsSup;
  list[1]=popInSup;

  CharacterVector namevec;
  namevec.push_back("idSup");
  namevec.push_back("pop");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}




// [[Rcpp::export]]
DataFrame calculatePopThatGoesToEachSupermarket(DataFrame population,DataFrame supermarkets,DataFrame popsup,double exponent){
  // std::tuple<std::vector<double>, std::vector<double> > result= Grafo::getPointsEvenBreaks(G,breaksEach);
  NumericVector idsPop=as<NumericVector>(population[0]);
  NumericVector pops=as<NumericVector>(population[3]);
  NumericVector idsSup=as<NumericVector>(supermarkets[0]);
  NumericVector idA=as<NumericVector>(popsup[0]);
  NumericVector idB=as<NumericVector>(popsup[1]);
  NumericVector d=as<NumericVector>(popsup[2]);

  std::vector<double> popToSup;
  popToSup.resize(idA.size(),0.0);


  long i=0;
  while(i<idA.size()){
    long idPop=idA[i];
    std::cout<<idPop<<'\n';
    std::deque<long> idsSupTemp;
    std::deque<double> distances;
    std::deque<double> probs;
    double n=0;
    while(idA[i]==idPop){
      long idBi=idB[i];
      idsSupTemp.push_back(idBi);
      if(d[i]>=100){
        double di=d[i];
        distances.push_back(di);
      }else{
        distances.push_back(100.0);
      }
      n++;
      i++;
    }
    double probTotal=0.0;
    for(long j=0;j<distances.size();j++){
      double prob=1.0/pow(distances.at(j),exponent);
      // double prob=1.0*exp(-exponent*distances.at(j)/1000.0);
      // double prob=2.888701081/(distances.at(j)*distances.at(j));
      probs.push_back(prob);
      probTotal+=prob;
    }
    double pop=pops[idPop];
    for(long j=0;j<distances.size();j++){
      popToSup[i-n+j]=probs[j]/probTotal*pop;
    }
  }





  List list(3);
  list[0]=idA;
  list[1]=idB;
  list[2]=popToSup;

  CharacterVector namevec;
  namevec.push_back("idPop");
  namevec.push_back("idSup");
  namevec.push_back("numPeople");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}



// [[Rcpp::export]]
DataFrame calculatePopThatGoesToEachSupermarketUsingDistricts(DataFrame population,DataFrame supermarkets,DataFrame popsup,double exponent){
  // std::tuple<std::vector<double>, std::vector<double> > result= Grafo::getPointsEvenBreaks(G,breaksEach);
  NumericVector idsPop=as<NumericVector>(population[0]);
  NumericVector idsDistricts=as<NumericVector>(population[5]);
  NumericVector pops=as<NumericVector>(population[3]);
  NumericVector idsSup=as<NumericVector>(supermarkets[0]);
  NumericVector idA=as<NumericVector>(popsup[0]);
  NumericVector idB=as<NumericVector>(popsup[1]);
  NumericVector d=as<NumericVector>(popsup[2]);

  std::unordered_map<long,std::unordered_map<long,double> > districtToSup;
  // popToSup.resize(idA.size(),0.0);


  long i=0;
  while(i<idA.size()){
    long idPop=idA[i];
    std::cout<<idPop<<'\n';
    std::deque<long> idsSupTemp;
    std::deque<double> distances;
    std::deque<double> probs;
    double n=0;
    while(idA[i]==idPop){
      long idBi=idB[i];
      idsSupTemp.push_back(idBi);
      if(d[i]>=100){
        double di=d[i];
        distances.push_back(di);
      }else{
        distances.push_back(100.0);
      }
      n++;
      i++;
    }
    double probTotal=0.0;
    for(long j=0;j<distances.size();j++){
      double prob=1.0/pow(distances.at(j),exponent);
      // double prob=1.0*exp(-exponent*distances.at(j)/1000.0);
      // double prob=2.888701081/(distances.at(j)*distances.at(j));
      probs.push_back(prob);
      probTotal+=prob;
    }
    double pop=pops[idPop];
    if(pop>1.0){
      bool stop=false;
      if(distances.size()==1){
        stop=true;
      }
      // long indexMaxDistance=-1;
      // double maxDistance=-99999999;
      //   for(long j=0;j<distances.size();j++){
      //     if(distances[j]>maxDistance){
      //       maxDistance=distances[j];
      //       indexMaxDistance=j;
      //     }
      //
      //   }
      while(!stop){
        stop=true;
        long indexMaxDistance=-1;
        double maxDistance=-99999999;
        for(long j=0;j<distances.size();j++){
          if(distances[j]>maxDistance&&probs[j]>0.0){
            maxDistance=distances[j];
            indexMaxDistance=j;
          }
          // probs[j]=0.0;
        }
        if(probs[indexMaxDistance]/probTotal*pop<1.0){
          probTotal-=probs[indexMaxDistance];
          probs[indexMaxDistance]=0.0;
          stop=false;
        }
        // double probsTotalB=0.0;
        // for(long j=0;j<distances.size();j++){
        //   if(probs[j]/probTotal*pop<1&&probs[j]>0&&j!=indexMaxDistance){
        //     probs[j]=0;
        //     stop=false;
        //   }
        //   probsTotalB+=probs[j];
        // }
        // probTotal=probsTotalB;
      }
    }else{
      long indexMinDistance=-1;
      double minDistance=99999999;
        for(long j=0;j<distances.size();j++){
          if(distances[j]<minDistance){
            minDistance=distances[j];
            indexMinDistance=j;
          }
          probs[j]=0.0;
        }
        probs[indexMinDistance]=1.0;
        probTotal=1.0;
    }

    for(long j=0;j<distances.size();j++){
      if(probs[j]/probTotal*pop>0.0){
        districtToSup[idsDistricts[idPop]][idB[i-n+j]]+=probs[j]/probTotal*pop;
      }
    }
  }


  std::vector<long> idDistrictsFinal;
  std::vector<long> idSupsFinal;
  std::vector<double> numPeopleFinal;

  for(auto idD:districtToSup){
    for(auto idS:idD.second){
      idDistrictsFinal.push_back(idD.first);
      idSupsFinal.push_back(idS.first);
      numPeopleFinal.push_back(idS.second);
    }
  }


  List list(3);
  list[0]=idDistrictsFinal;
  list[1]=idSupsFinal;
  list[2]=numPeopleFinal;

  CharacterVector namevec;
  namevec.push_back("idDistrict");
  namevec.push_back("idSup");
  namevec.push_back("numPeople");




  list.attr("names") = namevec;
  DataFrame df(list);
  return df;
}








// [[Rcpp::export]]
NumericVector calculateSatisfactionLevel(NumericVector tipReal,NumericVector dMiles, NumericVector tolls){
  NumericVector ss(tipReal.size(),0);
  double d0=(20-4.591091337)/2.87372457;
  for(long i=0;i<tipReal.size();i++){
    int closestS=-5;
    double closestV=INFINITY;
    for(int s=-4;s<=2;s++){
        double v=dMiles[i]*(.575+s*.15)+(1.15+s*.3);
        if(tolls[i]>0){

          if(dMiles[i]>d0){
            v=v-(dMiles[i]-d0)*.14;
          }
        }
        if(Functions::abs(tipReal[i]-v)<closestV){
          closestV=Functions::abs(tipReal[i]-v);
          closestS=s;
        }
    }
    ss[i]=closestS;
  }
  return ss;
}




// [[Rcpp::export]]
DataFrame locateSimilarPointsInAStereographicImage(DataFrame im,double maxDistance,double subdivider){
  NumericVector r=as<NumericVector>(im[2]);
  NumericVector g=as<NumericVector>(im[3]);
  NumericVector b=as<NumericVector>(im[4]);
  NumericVector xs=as<NumericVector>(im[0]);
  NumericVector ys=as<NumericVector>(im[1]);

NumericVector ir(r.size(),0.0);
NumericVector ig(r.size(),0.0);
NumericVector ib(r.size(),0.0);
NumericVector Sr(r.size(),0.0);
NumericVector Sg(r.size(),0.0);
NumericVector Sb(r.size(),0.0);
NumericVector Fr(r.size(),0.0);
NumericVector Fg(r.size(),0.0);
NumericVector Fb(r.size(),0.0);

  // std::vector<Point2d,long> points;
  std::unordered_map<Point2d, std::deque<long> > matrix;
  // double maxDistance=20.0;
  // double subdivider=maxDistance;
  double cl=0;
  double rl=0;

  for(long i=0;i<xs.size();i++){
    double x=xs[i];
    double y=ys[i];
    cl=Functions::max(cl,x);
    rl=Functions::max(rl,y);
    matrix[Point2d(std::floor(x/subdivider)*subdivider,std::floor(y/subdivider)*subdivider)].push_back(i);
  }

  for(double xc=0;xc<std::floor(cl/subdivider)*subdivider;xc+=subdivider){
    for(double yc=0;yc<floor(rl/subdivider)*subdivider;yc+=subdivider){
      std::deque<long> pointsAround;
      double w=Functions::max(1.0,std::ceil(maxDistance/subdivider));
      double xmin=Functions::max(0.0,xc-w*subdivider);
      double xmax=Functions::min(cl,xc+w*subdivider);
      double ymin=Functions::max(0.0,yc-w*subdivider);
      double ymax=Functions::min(rl,yc+w*subdivider);
      for(long xcB=xmin;xcB<=xmax;xcB+=subdivider){
        for(long ycB=ymin;ycB<=ymax;ycB+=subdivider){
          for(long i=0;i<matrix[Point2d(xcB,ycB)].size();i++){
            pointsAround.push_back(matrix[Point2d(xcB,ycB)].at(i));
          }
        }
      }

      for(long i=0;i<matrix[Point2d(xc,yc)].size();i++){
        std::vector<double> statesr;
        std::vector<double> nsr;
        nsr.resize(maxDistance,0);
        statesr.resize(maxDistance,0);
        std::vector<double> statesb;
        std::vector<double> nsb;
        nsb.resize(maxDistance,0);
        statesb.resize(maxDistance,0);
        std::vector<double> statesg;
        std::vector<double> nsg;
        nsg.resize(maxDistance,0);
        statesg.resize(maxDistance,0);
        double totalR=0;
        double totalG=0;
        double totalB=0;
        for(long j=0;j<pointsAround.size();j++){
          double d=Functions::getDistance(Point2d(xs[matrix[Point2d(xc,yc)].at(i)],ys[matrix[Point2d(xc,yc)].at(i)]),Point2d(xs[pointsAround.at(j)],ys[pointsAround.at(j)]));
          if(d<maxDistance){
            statesr[std::floor(d)]+=r[pointsAround.at(j)];
            nsr[std::floor(d)]++;
            totalR+=r[pointsAround.at(j)];
            statesg[std::floor(d)]+=g[pointsAround.at(j)];
            nsg[std::floor(d)]++;
            totalG+=g[pointsAround.at(j)];
            statesb[std::floor(d)]+=b[pointsAround.at(j)];
            nsb[std::floor(d)]++;
            totalB+=b[pointsAround.at(j)];


            double massR=r[pointsAround.at(j)];
            double massG=g[pointsAround.at(j)];
            double massB=b[pointsAround.at(j)];
            ir[matrix[Point2d(xc,yc)].at(i)]+=massR/(1+d)/(1+d);
            ib[matrix[Point2d(xc,yc)].at(i)]+=massB/(1+d)/(1+d);
            ig[matrix[Point2d(xc,yc)].at(i)]+=massG/(1+d)/(1+d);

            Fr[matrix[Point2d(xc,yc)].at(i)]+=(1.0-massR)/(2.0*M_PI*d+1);
            Fb[matrix[Point2d(xc,yc)].at(i)]+=(1.0-massB)/(2.0*M_PI*d+1);
            Fg[matrix[Point2d(xc,yc)].at(i)]+=(1.0-massG)/(2.0*M_PI*d+1);
          }
        }
        totalR=0;
        totalG=0;
        totalB=0;
        for(long j=0;j<statesr.size();j++){
          if(nsr[j]>0){
          statesr[j]/=nsr[j];
          totalR+=statesr[j];
        }
        if(nsb[j]>0){
          statesb[j]/=nsb[j];
          totalB+=statesb[j];
        }
        if(nsg[j]>0){
          statesg[j]/=nsg[j];
          totalG+=statesg[j];
        }
        }
        for(long j=0;j<statesr.size();j++){
            if(statesr[j]>0){
              double pr=statesr[j]/totalR;
              Sr[matrix[Point2d(xc,yc)].at(i)]+=-pr*log(pr);
            }
            if(statesg[j]>0){
              double pg=statesg[j]/totalG;
              Sg[matrix[Point2d(xc,yc)].at(i)]+=-pg*log(pg);
            }
            if(statesb[j]>0){
              double pb=statesb[j]/totalB;
              Sb[matrix[Point2d(xc,yc)].at(i)]+=-pb*log(pb);
            }
        }

      }
    }
  }



    // long numberObjectsDataFrame=std::get<0>(table).size();
    List list(11);
    list[0]=xs;
    list[1]=ys;
    list[2]=ir;
    list[3]=ig;
    list[4]=ib;
    list[5]=Sr;
    list[6]=Sg;
    list[7]=Sb;
    list[8]=Fr;
    list[9]=Fg;
    list[10]=Fb;

    // for(long i=0;i<numberObjectsDataFrame;i++){
    //   list[i]=(wrap(std::get<1>(table)[i]));
    // }

    CharacterVector namevec;
    // for(long i=0;i<numberObjectsDataFrame;i++){
      namevec.push_back("xs");
      namevec.push_back("ys");
      namevec.push_back("intertiaRed");
      namevec.push_back("intertiaGreen");
      namevec.push_back("intertiaBlue");
      namevec.push_back("Sred");
      namevec.push_back("Sgreen");
      namevec.push_back("Sblue");
      namevec.push_back("Fred");
      namevec.push_back("Fgreen");
      namevec.push_back("Fblue");
    // }




    list.attr("names") = namevec;
    DataFrame df(list);
    return df;

  // return ss;
}








// [[Rcpp::export]]
DataFrame getAllTagsFromLinkPrimal(XPtr<DualExtendedGraph>  deg,long idLink){


CharacterVector keys;
CharacterVector values;



    for(auto tag:deg->getPrimalGraph()->links[idLink]->data){
      keys.push_back(tag.first);
      values.push_back(tag.second);
    }

    // long numberObjectsDataFrame=std::get<0>(table).size();
    List list(2);
    list[0]=keys;
    list[1]=values;


    // for(long i=0;i<numberObjectsDataFrame;i++){
    //   list[i]=(wrap(std::get<1>(table)[i]));
    // }

    CharacterVector namevec;
    // for(long i=0;i<numberObjectsDataFrame;i++){
      namevec.push_back("keys");
      namevec.push_back("values");

    // }




    list.attr("names") = namevec;
    DataFrame df(list);
    return df;

  // return ss;
}



// [[Rcpp::export]]
DataFrame getAllTagsFromLink(XPtr<Grafo>  G,long idLink){


CharacterVector keys;
CharacterVector values;



    for(auto tag:G->links[idLink]->data){
      keys.push_back(tag.first);
      values.push_back(tag.second);
    }

    // long numberObjectsDataFrame=std::get<0>(table).size();
    List list(2);
    list[0]=keys;
    list[1]=values;


    // for(long i=0;i<numberObjectsDataFrame;i++){
    //   list[i]=(wrap(std::get<1>(table)[i]));
    // }

    CharacterVector namevec;
    // for(long i=0;i<numberObjectsDataFrame;i++){
      namevec.push_back("keys");
      namevec.push_back("values");

    // }




    list.attr("names") = namevec;
    DataFrame df(list);
    return df;

  // return ss;
}


// [[Rcpp::export]]
CharacterVector getTagFromAllLinks(XPtr<Grafo>  G,std::string nameTag){



// CharacterVector keys;
CharacterVector values(G->links.size());


    for (long i=0;i<G->links.size();i++){
    // for(auto tag:G->links[idLink]->data){
      // keys.push_back(tag.first);
      values[i]=(G->links[i]->data[nameTag]);
    }

    // long numberObjectsDataFrame=std::get<0>(table).size();
    // List list(2);
    // list[0]=keys;
    // list[1]=values;
    //
    //
    // // for(long i=0;i<numberObjectsDataFrame;i++){
    // //   list[i]=(wrap(std::get<1>(table)[i]));
    // // }
    //
    // CharacterVector namevec;
    // // for(long i=0;i<numberObjectsDataFrame;i++){
    //   namevec.push_back("keys");
    //   namevec.push_back("values");
    //
    // // }
    //
    //
    //
    //
    // list.attr("names") = namevec;
    // DataFrame df(list);
    // return df;
    return values;
  // return ss;
}




// [[Rcpp::export]]
void setMultiplierNForSpatialInteraction(double multiplier){
  SpatialInteraction::setMultiplierN(multiplier);
  // std::cout<<"multiplier N in spatial interaction: "<<SpatialInteraction::multiplierN<<'\n';
}




// [[Rcpp::export]]
void softResetDEG(XPtr<DualExtendedGraph> deg){
  deg->softReset();
  // std::cout<<"multiplier N in spatial interaction: "<<SpatialInteraction::multiplierN<<'\n';
}




// [[Rcpp::export]]
XPtr<std::vector<DualExtendedGraph*> > getSeveralSubsystems(XPtr< DualExtendedGraph > deg,NumericVector proportionsBox,NumericVector numbersSubsystems){
  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    if(deg->getPrimalGraph()->nodes[i]->location.x<minX){
      minX=deg->getPrimalGraph()->nodes[i]->location.x;
    }
    if(deg->getPrimalGraph()->nodes[i]->location.x>maxX){
      maxX=deg->getPrimalGraph()->nodes[i]->location.x;
    }
    if(deg->getPrimalGraph()->nodes[i]->location.y<minY){
      minY=deg->getPrimalGraph()->nodes[i]->location.y;
    }
    if(deg->getPrimalGraph()->nodes[i]->location.y>maxY){
      maxY=deg->getPrimalGraph()->nodes[i]->location.y;
    }

  }
  std::vector<DualExtendedGraph*>* degs=new std::vector<DualExtendedGraph*>();


  for(long h=0;h<proportionsBox.size();h++){
    double proportionBox=proportionsBox[h];
    long numberSubsystems=numbersSubsystems[h];
    double width=(maxX-minX)*proportionBox;
    double height=(maxY-minY)*proportionBox;
    for(long i=0;i<numberSubsystems;i++){
      double initX=Functions::runiform(minX,(maxX-width));
      double initY=Functions::runiform(minY,(maxY-height));
      std::vector<Nodo*> nodes;
      for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
        if(deg->getPrimalGraph()->nodes[j]->location.x>initX&&deg->getPrimalGraph()->nodes[j]->location.x<initX+width&&deg->getPrimalGraph()->nodes[j]->location.y>initY&&deg->getPrimalGraph()->nodes[j]->location.y<initY+height){
          nodes.push_back(deg->getPrimalGraph()->nodes[j]);
        }
      }
    // out(nodes.size()); 
      Grafo G;
      Grafo::inducedSubgraph(deg->getPrimalGraph(),&G,nodes);
    // out("subgraph generated");
      DualExtendedGraph* degNew=new DualExtendedGraph();

    // out("new pointer");
      DualExtendedGraph::addPrimal(degNew,&G);
      DualExtendedGraph::setPrimalAsStructuralGraph(degNew);
    // out("add primal");
      degs->push_back(degNew);
    // out(degs->at(i)->getPrimalGraph()->nodes.size());

    }

  }

  
  Rcpp::XPtr<std::vector<DualExtendedGraph*> > p(degs,true) ;
  return p;

}



// [[Rcpp::export]]
DataFrame calculateAngularPercolationSeveralSubsystemsSeveralAngles(XPtr< DualExtendedGraph > deg,DataFrame subSystems,NumericVector angles){


  NumericVector fractalDimension_=as<NumericVector>(subSystems[0]);
  NumericVector Ms_=as<NumericVector>(subSystems[1]);
  NumericVector Ls_=as<NumericVector>(subSystems[2]);
  NumericVector initXs_=as<NumericVector>(subSystems[3]);
  NumericVector initYs_=as<NumericVector>(subSystems[4]);
  NumericVector widths_=as<NumericVector>(subSystems[5]);
  NumericVector heights_=as<NumericVector>(subSystems[6]);

  NumericVector massesGC_=as<NumericVector>(subSystems[7]);
  NumericVector averageMasses8_=as<NumericVector>(subSystems[8]);

  long numberSubsystems=fractalDimension_.size();
  long numberAngles=angles.size();
  long totalNumberSystems=numberSubsystems*numberAngles;

  NumericVector fractalDimension(totalNumberSystems);
  NumericVector Ms(totalNumberSystems);
  NumericVector Ls(totalNumberSystems);
  NumericVector initXs(totalNumberSystems);
  NumericVector initYs(totalNumberSystems);
  NumericVector widths(totalNumberSystems);
  NumericVector heights(totalNumberSystems);

  NumericVector massesGC(totalNumberSystems);
  NumericVector averageMasses(totalNumberSystems);

  NumericVector angles_(totalNumberSystems);
  NumericVector ps_(totalNumberSystems);

  NumericVector angularWeights=getAngularWeights(deg);
  NumericVector ps=as<NumericVector>(getProbabilities(angularWeights,angles)[1]);




  long index=0;

  for(long i=0;i<numberSubsystems;i++){
    double initX=initXs_[i];
    double initY=initYs_[i];
    double width=widths_[i];
    double height=heights_[i];
    std::vector<Nodo*> nodes;
    for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
      if(deg->getPrimalGraph()->nodes[j]->location.x>initX&&deg->getPrimalGraph()->nodes[j]->location.x<initX+width&&deg->getPrimalGraph()->nodes[j]->location.y>initY&&deg->getPrimalGraph()->nodes[j]->location.y<initY+height){
        nodes.push_back(deg->getPrimalGraph()->nodes[j]);
      }
    }
    // out(nodes.size()); 
    Grafo G;
    Grafo::inducedSubgraph(deg->getPrimalGraph(),&G,nodes);
    // out("subgraph generated");
    DualExtendedGraph degNew;

    // out("new pointer");
    DualExtendedGraph::addPrimal(&degNew,&G);
    DualExtendedGraph::setPrimalAsStructuralGraph(&degNew);
    



    for(long j=0;j<numberAngles;j++){
      double angle=angles[j];
      std::vector<long> colors;
      std::vector<long> colorsNodes;
      std::vector<long> sizes;
      DualExtendedGraph::angularPercolation(&degNew,angle, colors, sizes);
      // Grafo::transformColorsLinksIntoColorsNodes(degNew.getLineGraph(), colors, colorsNodes);
      std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
      double massGiantCluster=0.0;
      if(sizes.size()>0){
        massGiantCluster=sizes[indexesOrderClusters[0]];
      }
      double averageClusterSize;
      double quadraticSum=0.0;
      double linearSum=0.0;
      for(long j=0;j<sizes.size();j++){
        quadraticSum+=sizes[j]*sizes[j];
        linearSum+=sizes[j];
      }
      averageClusterSize=quadraticSum/linearSum;
      massesGC[index]=massGiantCluster;
      averageMasses[index]=averageClusterSize;


      fractalDimension[index]=fractalDimension_[i];
      Ms[index]=Ms_[i];
      Ls[index]=Ls_[i];
      initXs[index]=initXs_[i];
      initYs[index]=initYs_[i];
      widths[index]=widths_[i];
      heights[index]=heights_[i];
      angles_[index]=angle;
      ps_[index]=ps[j];



      index++;
    }

    // out("add primal");
    // degs->push_back(degNew);
    // out(degs->at(i)->getPrimalGraph()->nodes.size());

  }



  
  // Rcpp::XPtr<std::vector<DualExtendedGraph*> > p(degs,true) ;
  // return p;

  List list(11);
  list[0]=fractalDimension;
  list[1]=Ms;
  list[2]=Ls;
  list[3]=initXs;
  list[4]=initYs;
  list[5]=widths;
  list[6]=heights;
  list[7]=massesGC;
  list[8]=averageMasses;
  list[9]=angles_;
  list[10]=ps_;


  
  




  CharacterVector namevec;
  namevec.push_back("fractalDimension");
  namevec.push_back("M");
  namevec.push_back("L");
  namevec.push_back("initXs");
  namevec.push_back("initYs");
  namevec.push_back("widths");
  namevec.push_back("heights");
  namevec.push_back("massesGC");
  namevec.push_back("averageMasses");
  namevec.push_back("angle");
  namevec.push_back("p");




  
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}


// [[Rcpp::export]]
DataFrame getDimensionsSeveralDEGs(XPtr<std::vector<DualExtendedGraph*> > degs){
  // out(degs->at(0)->getPrimalGraph()->nodes.size());
  // out(degs->at(0)->getPrimalGraph()->links.size());
  // out(degs->at(0)->getLineGraph()->nodes.size());
  // out(degs->at(0)->getLineGraph()->links.size());
  NumericVector fractalDimension(degs->size());
  NumericVector Ms(degs->size());
  NumericVector Ls(degs->size());
  std::vector<double> gridSizes;
  gridSizes.push_back(2000);
  gridSizes.push_back(3000);
  gridSizes.push_back(4000);

  for(long i=0;i<degs->size();i++){
//    DualExtendedGraph* deg=degs->at(i);
    std::vector<double> xs;
    std::vector<double> ys;
    xs.reserve(degs->at(i)->getLineGraph()->links.size());
    ys.reserve(degs->at(i)->getLineGraph()->links.size());

    for(long j=0;j<degs->at(i)->getLineGraph()->links.size();j++){
      double xA=degs->at(i)->getLineGraph()->links[j]->A()->location.x;
      double xB=degs->at(i)->getLineGraph()->links[j]->B()->location.x;
      double yA=degs->at(i)->getLineGraph()->links[j]->A()->location.y;
      double yB=degs->at(i)->getLineGraph()->links[j]->B()->location.y;
      xs.push_back((xA+xB)/2.0);
      ys.push_back((yA+yB)/2.0);
      
    }
    double d=FractalDimension::calculateBoxCounting(xs,ys,gridSizes,1.0);
    double M=degs->at(i)->getLineGraph()->links.size();
    double L=pow(M,1/d);
    fractalDimension[i]=d;
    Ms[i]=M;
    Ls[i]=L;
    

  }

  List list(3);
  list[0]=fractalDimension;
  list[1]=Ms;
  list[2]=Ls;
  
  




  CharacterVector namevec;
  namevec.push_back("fractalDimension");
  namevec.push_back("M");
  namevec.push_back("L");



  
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}

// [[Rcpp::export]]
DataFrame angularPercolationOneThreshold(XPtr<std::vector<DualExtendedGraph*> > degs, double angle){

  NumericVector massesGC(degs->size());
  NumericVector averageMasses(degs->size());
  for(long i=0;i<degs->size();i++){
    DualExtendedGraph* deg=degs->at(i);
    std::vector<long> colors;
    std::vector<long> colorsNodes;
    std::vector<long> sizes;
    DualExtendedGraph::angularPercolation(deg,angle, colors, sizes);
    Grafo::transformColorsLinksIntoColorsNodes(deg->getLineGraph(), colors, colorsNodes);
    std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
    double massGiantCluster=sizes[indexesOrderClusters[0]];
    double averageClusterSize;
    double quadraticSum=0.0;
    double linearSum=0.0;
    for(long j=0;j<sizes.size();j++){
      quadraticSum+=sizes[j]*sizes[j];
      linearSum+=sizes[j];
    }
    averageClusterSize=quadraticSum/linearSum;
    massesGC[i]=massGiantCluster;
    averageMasses[i]=averageClusterSize;
    

  }

  List list(2);
  list[0]=massesGC;
  list[1]=averageMasses;
  
  




  CharacterVector namevec;
  namevec.push_back("massGC");
  namevec.push_back("averageMass");



  
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}




// [[Rcpp::export]]
DataFrame calculateAngularPercolationSeveralSubsystems(XPtr< DualExtendedGraph > deg,NumericVector proportionsBox,NumericVector numbersSubsystems,double angle){
  double minX=INFINITY;
  double minY=INFINITY;
  double maxX=-INFINITY;
  double maxY=-INFINITY;
  for(long i=0;i<deg->getPrimalGraph()->nodes.size();i++){
    if(deg->getPrimalGraph()->nodes[i]->location.x<minX){
      minX=deg->getPrimalGraph()->nodes[i]->location.x;
    }
    if(deg->getPrimalGraph()->nodes[i]->location.x>maxX){
      maxX=deg->getPrimalGraph()->nodes[i]->location.x;
    }
    if(deg->getPrimalGraph()->nodes[i]->location.y<minY){
      minY=deg->getPrimalGraph()->nodes[i]->location.y;
    }
    if(deg->getPrimalGraph()->nodes[i]->location.y>maxY){
      maxY=deg->getPrimalGraph()->nodes[i]->location.y;
    }

  }
// std::vector<DualExtendedGraph*>* degs=new std::vector<DualExtendedGraph*>();
  long totalNumberSystems=0;
  for(long i=0;i<numbersSubsystems.size();i++){
    totalNumberSystems+=numbersSubsystems[i];
  }

  NumericVector fractalDimension(totalNumberSystems);
  NumericVector Ms(totalNumberSystems);
  NumericVector Ls(totalNumberSystems);
  NumericVector initXs(totalNumberSystems);
  NumericVector initYs(totalNumberSystems);
  NumericVector widths(totalNumberSystems);
  NumericVector heights(totalNumberSystems);

  NumericVector massesGC(totalNumberSystems);
  NumericVector averageMasses(totalNumberSystems);
  std::vector<double> gridSizes;
  gridSizes.push_back(2000);
  gridSizes.push_back(2500);
  gridSizes.push_back(3000);
  long index=0;
  for(long h=0;h<proportionsBox.size();h++){
    double proportionBox=proportionsBox[h];
    long numberSubsystems=numbersSubsystems[h];
    double width=(maxX-minX)*proportionBox;
    double height=(maxY-minY)*proportionBox;
    for(long i=0;i<numberSubsystems;i++){
      double initX=Functions::runiform(minX,(maxX-width));
      double initY=Functions::runiform(minY,(maxY-height));
      std::vector<Nodo*> nodes;
      for(long j=0;j<deg->getPrimalGraph()->nodes.size();j++){
        if(deg->getPrimalGraph()->nodes[j]->location.x>initX&&deg->getPrimalGraph()->nodes[j]->location.x<initX+width&&deg->getPrimalGraph()->nodes[j]->location.y>initY&&deg->getPrimalGraph()->nodes[j]->location.y<initY+height){
          nodes.push_back(deg->getPrimalGraph()->nodes[j]);
        }
      }
    // out(nodes.size()); 
      Grafo G;
      Grafo::inducedSubgraph(deg->getPrimalGraph(),&G,nodes);
    // out("subgraph generated");
      DualExtendedGraph degNew;

    // out("new pointer");
      DualExtendedGraph::addPrimal(&degNew,&G);
      DualExtendedGraph::setPrimalAsStructuralGraph(&degNew);
      std::vector<double> xs;
      std::vector<double> ys;
      xs.reserve(degNew.getLineGraph()->links.size());
      ys.reserve(degNew.getLineGraph()->links.size());

      for(long j=0;j<degNew.getLineGraph()->links.size();j++){
        double xA=degNew.getLineGraph()->links[j]->A()->location.x;
        double xB=degNew.getLineGraph()->links[j]->B()->location.x;
        double yA=degNew.getLineGraph()->links[j]->A()->location.y;
        double yB=degNew.getLineGraph()->links[j]->B()->location.y;
        xs.push_back((xA+xB)/2.0);
        ys.push_back((yA+yB)/2.0);

      }
      double d=FractalDimension::calculateBoxCounting(xs,ys,gridSizes,1.0);
      double M=degNew.getLineGraph()->links.size();
      double L=pow(M,1/d);
      fractalDimension[index]=d;
      Ms[index]=M;
      Ls[index]=L;
      initXs[index]=initX;
      initYs[index]=initY;
      widths[index]=width;
      heights[index]=height;




      std::vector<long> colors;
      std::vector<long> colorsNodes;
      std::vector<long> sizes;
      DualExtendedGraph::angularPercolation(&degNew,angle, colors, sizes);
    // Grafo::transformColorsLinksIntoColorsNodes(degNew.getLineGraph(), colors, colorsNodes);
      std::vector<long> indexesOrderClusters=Functions::getIndexesOfOrderedValues(sizes, false);
      double massGiantCluster=0.0;
      if(sizes.size()>0){
        massGiantCluster=sizes[indexesOrderClusters[0]];
      }
      double averageClusterSize;
      double quadraticSum=0.0;
      double linearSum=0.0;
      for(long j=0;j<sizes.size();j++){
        quadraticSum+=sizes[j]*sizes[j];
        linearSum+=sizes[j];
      }
      averageClusterSize=quadraticSum/linearSum;
      massesGC[index]=massGiantCluster;
      averageMasses[index]=averageClusterSize;

      index++;

    // out("add primal");
    // degs->push_back(degNew);
    // out(degs->at(i)->getPrimalGraph()->nodes.size());

    }

  }

  
  // Rcpp::XPtr<std::vector<DualExtendedGraph*> > p(degs,true) ;
  // return p;

  List list(9);
  list[0]=fractalDimension;
  list[1]=Ms;
  list[2]=Ls;
  list[3]=initXs;
  list[4]=initYs;
  list[5]=widths;
  list[6]=heights;
  list[7]=massesGC;
  list[8]=averageMasses;


  
  




  CharacterVector namevec;
  namevec.push_back("fractalDimension");
  namevec.push_back("M");
  namevec.push_back("L");
  namevec.push_back("initXs");
  namevec.push_back("initYs");
  namevec.push_back("widths");
  namevec.push_back("heights");
  namevec.push_back("massesGC");
  namevec.push_back("averageMasses");




  
  list.attr("names") = namevec;
  DataFrame df(list);
  return df;

}


//
//  FractalDimension.cpp
//  harmonicCities
//
//  Created by Carlos Molinero on 12/06/2015.
//  Copyright (c) 2015 Carlos Molinero. All rights reserved.
//

#include "FractalDimension.h"

FractalDimension::FractalDimension(){

}

//double FractalDimension::calculateFractalDimensionGyrationRadius(Graph &graph){
//    std::vector<double> x;
//    std::vector<double> y;
//
//    Point2d centroid;
//    double totalMass;
//
//    LinearRegression linearRegression;
//    QTree quadTree;
//    centroid=Graph::calculateCentroid(graph.nodes);
//
////    if(!quadTreeCalculated){
//        graph.insertGraphIntoQTree(&quadTree);
////        quadTreeCalculated=true;
////    }
//    double radius=10.0;
//    double inc_radius=2.0;
//    x.clear();
//    y.clear();
//    bool stop=false;
//
//    double previousMass=0.0;
//    while (!stop){
//        std::vector<Node*> nodesInRange=quadTree.getNodesInARange(centroid, radius);
//
//        double mass=0.0;
//        for(long i=0;i<nodesInRange.size();i++){
//            if(nodesInRange[i]->mass>1){
//            mass+=nodesInRange[i]->mass;
//            }
//        }
//        if(mass>0){
//            x.push_back(log(radius));
//            y.push_back(log((mass-previousMass)));
//        }
//        if(mass>=totalMass-1){
//            stop=true;
//        }
//        previousMass=mass;
//        radius*=inc_radius;
//
//
//    }
//
//    LinearRegression::compute(x,y);
//    return linearRegression.slope;
//}


double FractalDimension::calculateBoxCounting(Grafo* G){
//    DualExtendedGraph deg;
//    DualExtendedGraph::addPrimal(&deg,G);
//    Grafo* g=deg.getStructuralGraph();

        // std::vector<std::tuple<long, std::vector<long>, std::vector<double> > > pairsOldIdNewIds;
        // Grafo::forcePlanarityPlaneSweep(g, Grafo::SPEED, pairsOldIdNewIds, false);

        // std::vector<double> weights;
        // weights.resize(g->links.size(),0);
        // for(long j=0;j<g->links.size();j++){
        //     weights[j]=g->links[j]->weight;
        // }
        // std::vector<double> orderedWeights=Functions::orderValues(weights,true);
        // double median=orderedWeights[orderedWeights.size()/2];

        // std::vector<double> gridSizes;

        // double maxX=-INFINITY;
        // double minX=INFINITY;
        // double maxY=-INFINITY;
        // double minY=INFINITY;
        // for(long i=0;i<G->nodes.size();i++){
        //     if(G->nodes[i]->location.x>maxX){
        //         maxX=G->nodes[i]->location.x;
        //     }
        //     if(G->nodes[i]->location.x<minX){
        //         minX=G->nodes[i]->location.x;
        //     }
        //     if(G->nodes[i]->location.y>maxY){
        //         maxY=G->nodes[i]->location.y;
        //     }
        //     if(G->nodes[i]->location.y<minY){
        //         minY=G->nodes[i]->location.y;
        //     }
        // }

        // double max=Functions::min(maxX-minX,maxY-minY);

        // for(double i=10.0;i>=1.0;i--){
        //     gridSizes.push_back(max/pow(2.0,i));
        // }
        // double subdivision=max/pow(2.0,16.0);
        //         std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(g,subdivision);

        // std::vector<std::vector<double> > fd_points=FractalDimension::calculateBoxCounting_getPoints(std::get<0>(points),std::get<1>(points),gridSizes,max/pow(2.0,15.0));







        // double maxRuns=1.0;
        // double finalFd=0;
        // for(double run=0;run<maxRuns;run++){
        //     std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep(G,10);
        //     std::vector<double> x;
        //     std::vector<double> y;
        //     for(long i=0;i<std::get<0>(points).size();i++){
        //         if(std::get<1>(points)[std::get<0>(points).size()-1-i]!=1||(std::get<1>(points)[std::get<0>(points).size()-1-i]==1&&std::get<1>(points)[std::get<0>(points).size()-2-i]!=1)){
        //             x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-i]));
        //             y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-i]));
        //         }
        //     }
        //     Fxy f=Fxy::createFunction(x,y);
        //     Fxy d=Fxy::getDerivative(&f);
        //     double fd=INFINITY;
        //     // for(long i=0;i<d.x.size();i++){
        //     // if(d.y[d.y.size()/2]){
        //     std::vector<double> orderedValues=Functions::orderValues(d.y,true);
        //     fd=orderedValues[floor(double(orderedValues.size())/2.0)];
        //     // }
        //     // }
        //     finalFd-=fd;
        // }
        // finalFd/=maxRuns;




     double maxRuns=10.0;
     std::vector<double> possibleFds;
        double finalFd=0;
        for(double run=0;run<maxRuns;run++){

//     std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep_mixScales(G,10);
//     std::vector<double> x;
//     std::vector<double> y;
//     for(long j=0;j<std::get<0>(points).size();j++){
//         // if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1||(std::get<1>(points)[std::get<0>(points).size()-2-j]==1&&std::get<1>(points)[std::get<0>(points).size()-1-j]!=1)){
//           // std::cout<<std::get<0>(points).size()<<" "<<std::get<0>(points).size()-1-j<<" "<<std::get<1>(points)[std::get<0>(points).size()-1-j]<<'\n';
// //                if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1){
//               x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
//               y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
//           // }
//     }






 long depthLimit=10;

//         double maxX=-INFINITY;
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
// std::vector<double> sizeGridPerLevel;
//         for(long j=0;j<depthLimit;j++){
//                 sizeGridPerLevel.push_back((2*radius)/pow(2,j));
//             }

// double subdivision=(2*radius)/pow(2.0,16.0);
//                 std::tuple<std::vector<double>,std::vector<double> > points=Grafo::getPointsEvenBreaks(G,subdivision);
// std::vector<double> x;
//     std::vector<double> y;
//         std::vector<std::vector<double> > fd_points=FractalDimension::calculateBoxCounting_getPoints(std::get<0>(points),std::get<1>(points),sizeGridPerLevel,(2*radius)/pow(2.0,15.0));
//         // x=fd_points[0];
//         // y=fd_points[1];
// for(long j=0;j<fd_points[0].size();j++){
//         // if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1||(std::get<1>(points)[std::get<0>(points).size()-2-j]==1&&std::get<1>(points)[std::get<0>(points).size()-1-j]!=1)){
//          // std::cout<<std::get<0>(points).size()<<" "<<std::get<0>(points).size()-1-j<<" "<<std::get<1>(points)[std::get<0>(points).size()-1-j]<<'\n';
// //                if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1){
//               x.push_back(log(fd_points[0][fd_points[0].size()-1-j]));
//               y.push_back(log(fd_points[1][fd_points[1].size()-1-j]));
//  //         }
//     }

 std::tuple<std::vector<double>,std::vector<double> > points=FractalDimension::boxCountingPlaneSweep_mixScales(G,depthLimit);
      std::vector<double> x;
      std::vector<double> y;
      for(long j=0;j<std::get<0>(points).size();j++){
          // if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1||(std::get<1>(points)[std::get<0>(points).size()-2-j]==1&&std::get<1>(points)[std::get<0>(points).size()-1-j]!=1)){
            // std::cout<<std::get<0>(points).size()<<" "<<std::get<0>(points).size()-1-j<<" "<<std::get<1>(points)[std::get<0>(points).size()-1-j]<<'\n';
  //                if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1){
                x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
                y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
            // }
      }





//     std::cout<<x.size()<<'\n';
    Fxy f=Fxy::createFunction(x,y);
    Fxy::derivate(&f);
    double fd=INFINITY;
    // for(long j=0;j<f.x.size();j++){
    //     if(f.derivative[j]<fd){
    //         fd=f.derivative[j];
    //         if(exp(f.x[j])<epsilon){
    //           epsilon=exp(f.x[j]);
    //           N=exp(f.y[j]);

    //         }

    //     }
    // }
  double epsilon=INFINITY;
    fd=Functions::min(f.derivative);
      // std::cout<<"fdTemp "<<fd<<'\n';
      // gamma-=fd;
      possibleFds.push_back(-fd);
      for(long j=f.x.size()-1;j>=0;j--){
        if(f.derivative[j]==fd){
          // std::cout<<exp(f.x[j])<<'\n';
          // if(exp(f.x[j])<epsilon){
            epsilon=exp(f.x[j]);
            // N=exp(f.y[j]);
          // }


        }
      }
    // possibleFds.push_back(-fd);

//    std::cout<<"initial fd "<<fd<<'\n';
    // final
    // for(long j=f.x.size()-1;j>=0;j--){
    //     if(f.derivative[j]==fd){

    //           epsilon=exp(f.x[j]);
    //           // N=exp(f.y[j]);


    //     }
    // }
    // std::cout<<"epsilon "<<epsilon<<'\n';








//     points=FractalDimension::boxCountingPlaneSweep(G,depthLimit);
//     x.clear();
//     y.clear();
//     for(long j=0;j<std::get<0>(points).size();j++){
//         // if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1||(std::get<1>(points)[std::get<0>(points).size()-2-j]==1&&std::get<1>(points)[std::get<0>(points).size()-1-j]!=1)){
//          // std::cout<<std::get<0>(points).size()<<" "<<std::get<0>(points).size()-1-j<<" "<<std::get<1>(points)[std::get<0>(points).size()-1-j]<<'\n';
// //                if(std::get<1>(points)[std::get<0>(points).size()-1-j]!=1){
//               x.push_back(log(std::get<0>(points)[std::get<0>(points).size()-1-j]));
//               y.push_back(log(std::get<1>(points)[std::get<0>(points).size()-1-j]));
//  //         }
//     }
//      std::cout<<x.size()<<'\n';
//     f=Fxy::createFunction(x,y);
//     Fxy::derivate(&f);
//     double fd_final=INFINITY;
//     std::vector<double> minRange,maxRange;
//     for(long j=0;j<x.size();j++){
//       if(x[j]<log(epsilon/4.0)){
//         minRange.push_back(x[j]);
//       }
//       if(x[j]>log(epsilon*4.0)){
//         maxRange.push_back(x[j]);
//       }
//     }
//     double minRangeX=x[0];
//     double maxRangeX=x[x.size()-1];
//     if(minRange.size()>0){
//         minRangeX=minRange[Functions::max(0,minRange.size()-1)];
//     }
//     if(maxRange.size()>0){
//         maxRangeX=maxRange[Functions::min(maxRange.size()-1,0)];
//     }


//     std::vector<double> ys_cor;
//     std::vector<double> xs_cor;


//     for(long j=0;j<f.x.size();j++){
//       if(f.x[j]>=minRangeX&&f.x[j]<=maxRangeX){
//         ys_cor.push_back(f.y[j]);
//         xs_cor.push_back(f.x[j]);
//       }
//     }
//     LinearRegression cor=LinearRegression::compute(xs_cor,ys_cor,false);
//     finalFd=cor.slope;







//     fd_final=Functions::median(values);
    // possibleFds.push_back(-fd_final);
            // std::cout<<"secondary fd "<<fd_final<<'\n';
    // fd=f.derivative[floor(double(f.derivative.size())/2.0)];
//    double gamma=-fd_final;

  // double N;
  //   for(long j=f.x.size()-1;j>=0;j--){
  //       if(f.derivative[j]==fd_final){

  //             epsilon=exp(f.x[j]);
  //             N=exp(f.y[j]);


  //       }
  //   }

// finalFd-=fd;
        }
        // finalFd/=maxRuns;
        finalFd=Functions::median(possibleFds);








        return finalFd;

}

std::pair<double,std::pair<long,long> > FractalDimension::detectStartingGridSize(Grafo* G,double maxDepth){
    std::cout<<'\n';
    std::cout<<"Detecting initial grid size "<<'\n';
    double massNode=1;
    double M=G->nodes.size()*massNode;
    double L=sqrt(M);
    double bestAdjustedR2=0;
    double currentAdjustedR2=0;
//    bool firstTimeValid=false;
//    double bestGridSize=INFINITY;
//    bool upperBoundFound=false;
    bool lowerBoundFound=false;
//    double upperBound=INFINITY;
    double lowerBound=0;
//    bool goingUp=false;
//    bool goingDown=false;


    std::vector<double> gridSizes;
    std::vector<double> adjustedR2s;
    std::vector<bool> followOrders;
    std::vector<bool> validRanges;

//    std::queue<double> gridSizesToCheck;





    std::vector<std::vector<SparseMatrix> > multipleGrids;

    //    SparseMatrix level4;
    int GEOMETRIC=0;
    int ARITHMETIC=1;
    int type=GEOMETRIC;
    bool followOrder=false;

//    long lowerCutoff=0;
//    long upperCutoff=0;
    long finalUpperCutoff=0;
    long finalLowerCutoff=0;
//    double maxDepth=8;
    std::pair<long,long> lowerUpperCutoff;


    double probabilityToDecideIfCompute=1;
    long numberCalculations=1;

    multipleGrids.resize(numberCalculations);
    for(long i=0;i<numberCalculations;i++){
        multipleGrids[i].resize(maxDepth,SparseMatrix());
    }
    std::vector<double> qs;
    for(double i=-10.0;i<=10.0;i++){
        qs.push_back(i);
    }
    std::vector<double> Dqs;
    Dqs.resize(qs.size(),0.0);
//    Dqs[0]=1;
//    Dqs[1]=0;
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

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

    double gridSize=Functions::max(maxX-minX,maxY-minY);
    gridSizes.push_back(0);
    adjustedR2s.push_back(0);

    std::vector<double> x;
    std::vector<double> y;
//    LinearRegression linearRegression;
    double accumWeight=0;
    double longestDistance=0;
    for(long i=0;i<G->links.size();i++){
        accumWeight+=G->links[i]->weight;
        if(G->links[i]->weight>longestDistance){
            longestDistance=G->links[i]->weight;
        }
    }
    double averWeight=accumWeight/(double)G->links.size();

     double tolerance=averWeight/2;

//    double previousGridSize=gridSize*2;
    double finalGridSize=0;
//    double minSizeGrid=0;

    while(true){
//        std::cout<<"Current gridSize "<<previousGridSize<<'\n';
         for(long g=0;g<multipleGrids.size();g++){
             multipleGrids[g].clear();
             multipleGrids[g].resize(maxDepth,SparseMatrix());
         }


        std::vector<double> averageDistances;
        std::vector<double> averageDistancesTemp;
        std::vector<double> numObjects;
        std::vector<std::vector<double> > masses;
        std::vector<double> massesDeformedByQ;
        std::vector<double> massesTemp;
        std::vector<double> numberTimesExist;
        std::vector<double> radii;
        std::vector<double> topologicalRadii;
        averageDistances.resize(maxDepth+1,0);
        averageDistancesTemp.resize(maxDepth+1,0);
        numObjects.resize(maxDepth+1,0);

        massesDeformedByQ.resize(maxDepth+1,0);
        massesTemp.resize(maxDepth+1,0);

        std::vector<double> alphas;
        alphas.resize(G->nodes.size());
        std::vector<double> gammas;
        gammas.resize(G->nodes.size());






        //    double maxDistance=(averWeight)*maxDepth;
//        double coef=M_PI/4.0;
//        coef=1.0;


        for(long g=0;g<multipleGrids.size();g++){
            Point2d startPoint=Point2d(Functions::runiform(0,gridSize),Functions::runiform(0,gridSize));
            if(numberCalculations==1){
//                startPoint=Point2d((maxX-minX)/2.0,(maxY-minY)/2.0);
                 startPoint=Point2d(0,0);
            }
            std::cout<<"    Calculating levels, grid size = "<<gridSize<<'\n';
            for(long i=0;i<G->nodes.size();i++){
                //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
                multipleGrids[g][0].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSize)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSize)),massNode);
                //        }
//                std::cout<<"x,y "<<static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSize))<<","<<static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSize))<<'\n';
            }

//            std::cout<<"level 0 calculated"<<" "<<multipleGrids[g][0].cells.size()<<'\n';
            if(type==GEOMETRIC){
                for(long i=0;i<maxDepth-1;i++){
                    double gridSizeTemp;

                    gridSizeTemp=pow(3,i);

                    for(auto& it:multipleGrids[g][0].cells){
                        Point2d current=it.first;
                        for(long j=0;j<3;j++){
                            for(long h=0;h<3;h++){
//                                if(i==0){
//                                    std::cout<<"level +1: "<<multipleGrids[g][i].getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h))<<'\n';
//                                }
                                multipleGrids[g][i+1].increaseBy((current.x),(current.y),multipleGrids[g][i].getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
                            }
                        }
                    }
    //                std::cout<<"level "<<i+1<<"/"<<maxDepth<<" calculated"<<'\n';
                }
            }
        }
        //    std::cout<<"level 2/"<< maxDepth<<" calculated"<<'\n';
        //    double gridSizeTemp=3.0;
        //    for(auto& it:level1.cells){
        //        Point2d current=it.first;
        //        for(long j=0;j<3;j++){
        //            for(long h=0;h<3;h++){
        //                level2.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level1.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
        //            }
        //        }
        //    }
        //    std::cout<<"level 3/"<< maxDepth<<" calculated"<<'\n';
        //    gridSizeTemp=9.0;
        //    for(auto& it:level2.cells){
        //        Point2d current=it.first;
        //        for(long j=0;j<3;j++){
        //            for(long h=0;h<3;h++){
        //                level3.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level2.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
        //            }
        //        }
        //    }
        //    std::cout<<"level 4/"<< maxDepth<<" calculated"<<'\n';
        //    gridSizeTemp=3.0;
        //    for(long j=0;j<3;j++){
        //        for(long h=0;h<3;h++){
        //            for(auto& it:level3.cells){
        //                Point2d current=it.first;
        //
        //                level4.increaseBy(static_cast<long>(round((current.x)/gridSizeTemp)*gridSizeTemp-1+j),static_cast<long>(round((current.y)/gridSizeTemp)*gridSizeTemp-1+h),it.second.value);
        //            }
        //        }
        //    }

        masses.resize(multipleGrids[0][0].cells.size(),std::vector<double>());















        radii.clear();

        for(double i=0.0;i<maxDepth;i++){
            if(type==GEOMETRIC){
                radii.push_back(gridSize*pow(3.0,i));
            }
            if(type==ARITHMETIC){
                radii.push_back(gridSize*((i*2.0)+1.0));
                topologicalRadii.push_back(i);
            }

//            std::cout<<"radii "<<radii[i]<<'\n';
        }




        x.clear();
        y.clear();




        double sqrt2=sqrt(2);

        double numberObjectsCounted=0;
        long j=0;
//        std::vector<double> xs;
//        std::vector<double> ys;
//        xs.reserve(radii.size());
//        ys.reserve(radii.size());

        for(auto& it:multipleGrids[0][0].cells){

            masses[j].clear();

            if(Functions::runiform(0, 1)<probabilityToDecideIfCompute){
                numberObjectsCounted++;
                Point2d current=it.first;


                masses[j].resize(maxDepth,0);
                if(type==ARITHMETIC){
                    for(long i=-maxDepth;i<=maxDepth;i++){
                        for(long g=-maxDepth;g<=maxDepth;g++){
                            for(long h=topologicalRadii.size()-1;h>=0;h--){
                                double distance=Functions::getDistance(current,Point2d(current.x+i,current.y+g));
                                if(distance<=topologicalRadii[h]*sqrt2){
                                    masses[j][h]+=multipleGrids[0][0].getValue(current.x+i,current.y+g);
                                }else{
                                    break;
                                }
                            }

                        }
                    }
                }else{
                    for(long g=0;g<numberCalculations;g++){
                        for(long i=0;i<maxDepth;i++){
                            masses[j][i]+=multipleGrids[g][i].getValue(current.x,current.y)/(double)(numberCalculations);
                        }
                    }
                }




                auto linearRegression=LinearRegression::computeBestFit(radii, masses[j],true);
                if(linearRegression.first.slope<1||linearRegression.first.slope>2||linearRegression.first.adjusted_R2<.99){
                    masses[j].clear();
                    numberObjectsCounted--;
                }
            }

            j++;

        }









//        double coefArea=1;
//        double coefRadius=1;
        double q=2.0;

        double M_temp=1.0;
        double L_temp=1.0;
        double maxMass=0.0;

        std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
        x.clear();
        y.clear();

        for(long i=0;i<masses.size();i++){



            if(masses[i].size()>0){
                //                                std::cout<<"gamma "<<gammas[i]<<'\n';

                for(long h=0;h<radii.size()-0;h++){
                    //                if(masses[i][h]<1){
                    //                    std::cout<<""<<'\n';
                    //                }
                    massesDeformedByQ[h]+=pow(masses[i][h]/M_temp,q-1)/numberObjectsCounted;
                    //                        std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
                    if(masses[i][h]>maxMass){

                        maxMass=masses[i][h];
                    }
                }
            }

        }



//        for(long i=0;i<radii.size()-0;i++){
//
//
//
//
//
//            x.push_back(log(radii[i]*coefRadius/L_temp));
//            y.push_back(log(massesDeformedByQ[i])/(q-1));
////            std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<log(radii[i]*coefRadius/L_temp)<<",mass="<<log(massesDeformedByQ[i])/(q-1)<<"))"<<'\n';
//
//        }
//        auto lr=LinearRegression::computeBestFit(x,y,false);
//        double D2=lr.first.slope;
//        lowerUpperCutoff=lr.second;
//        if(std::isfinite(D2)){
//            currentAdjustedR2=lr.first.adjusted_R2;
//        }else{
//            currentAdjustedR2=0;
//        }
//        std::cout<<"D2="<<D2<<'\n';
//
//
//
//
        for(long i=0;i<radii.size()-0;i++){




            y.push_back(log(massesDeformedByQ[i]));
            x.push_back(log(radii[i]/L_temp));
            std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';

        }



    //        auto lr=LinearRegression::computeBestFit(x,y,false);
    //        double D2=lr.first.slope;
    //        lowerUpperCutoff=lr.second;
    //        if(std::isfinite(D2)){
    //            currentAdjustedR2=lr.first.adjusted_R2;
    //        }else{
    //            currentAdjustedR2=0;
    //        }






        auto lr=LinearRegression::computeBestFit(x,y,false);
        double D2=lr.first.slope/(q-1);
        lowerUpperCutoff=lr.second;
//        if(std::isfinite(D2)){
            currentAdjustedR2=lr.first.adjusted_R2;
//        }else{
//            currentAdjustedR2=0;
//        }
        std::cout<<"D2="<<D2<<'\n';

        lr=LinearRegression::computeBestFit(y,x,false);


        double slopeA=lr.first.slope;
        double interceptA=lr.first.intercept;
        long size=x.size();
        x.clear();
        y.clear();
        for(long i=0;i<size;i++){
            x.push_back(exp(log(massesDeformedByQ[i])/(q-1)*slopeA+interceptA));
            y.push_back(radii[i]/L_temp);
        }
        lr=LinearRegression::computeBestFit(x,y,false);


        //    L=pow(M,1/1.7149);
        //    M=maxMass;
        L=lr.first.slope*(exp(log(M)*slopeA+interceptA))+lr.first.intercept;






        //    L=pow(M,1/2);
//        std::cout<<"L ="<<L<<", M ="<<M<<'\n';

        //    M=1;
        //    L=1;

        std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
        x.clear();
        y.clear();

        for(long j=0;j<qs.size();j++){
            if(qs[j]!=1){


                for(long i=0;i<masses.size();i++){


                    if(masses[i].size()>0){

                        for(long h=0;h<radii.size()-0;h++){
                            massesDeformedByQ[h]+=pow(masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted;
                            if(h==0){
                                //                            std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
                            }

                        }
                    }
                }
                //            std::cout<<'\n';
                for(long i=0;i<radii.size()-0;i++){


//                    if(radii[i]/L>0.0&&massesDeformedByQ[i]>0.0){
                        x.push_back(log(radii[i]/L));
                        y.push_back(log(massesDeformedByQ[i]));
//                    }
                    //                 std::cout<<qs[j]<<" "<<massesDeformedByQ[i]<<" "<<log(massesDeformedByQ[i])<<" "<<log(massesDeformedByQ[i])/(qs[j]-1.0)<<'\n';
//                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<(x[x.size()-1])<<",mass="<<log(massesDeformedByQ[i])/(qs[j]-1)<<"))"<<'\n';
                    //                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';


                }

////                    lowerUpperCutoff=LinearRegression::detectUpperAndLowerCutoff(x, y, false);
//                    auto lr=LinearRegression::compute(x, y,lowerUpperCutoff.first,x.size()-lowerUpperCutoff.second,false);
//                    std::cout<<"quality "<<lr.adjusted_R2<<'\n';
//                    Dqs[j]=lr.slope;
//                    std::cout<<"? "<<lr.slope<<" "<<x.size()<<" "<< numberObjectsCounted<<'\n';
//                    if(lr.slope==0&&numberObjectsCounted>0){
//                        for(long i=0;i<x.size();i++){
//                            std::cout<<" x "<<x[i]<<" y "<<y[i]<<'\n';
//                        }
//                    }
//
////                    lowerCutoff=linearRegressionObject.second.first;
////                    upperCutoff=linearRegressionObject.second.second;
//                }else{
                if(j==0){
                lowerUpperCutoff=LinearRegression::detectUpperAndLowerCutoff(x, y, false);
//                lowerUpperCutoff.first=Functions::max(lowerUpperCutoff.first,lowerUpperCutoffTemp.first);
//                lowerUpperCutoff.second=Functions::max(lowerUpperCutoff.second,lowerUpperCutoffTemp.second);
//
                }
                    auto lr=LinearRegression::compute(x, y,lowerUpperCutoff.first,x.size()-lowerUpperCutoff.second,false);
                    Dqs[j]=lr.slope/(qs[j]-1.0);

//                currentAdjustedR2+=lr.adjusted_R2;
                    std::cout<<"q "<<qs[j] <<" slope "<<Dqs[j]<<" quality "<<lr.adjusted_R2<<'\n';
//
//                    std::cout<<"?? "<<lr.slope<<'\n';
//                }

            }else{

                for(long i=0;i<masses.size();i++){


                    if(masses[i].size()>0){

                        for(long h=0;h<radii.size()-0;h++){
                            massesDeformedByQ[h]+=log(masses[i][h]/M)/numberObjectsCounted;

                        }
                    }
                }

                for(long i=0;i<radii.size()-0;i++){


                    if(radii[i]/L>0){
                        x.push_back(log(radii[i]/L));
                        y.push_back((massesDeformedByQ[i]));
//                        std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<(x[x.size()-1])<<",mass="<<(massesDeformedByQ[i])<<"))"<<'\n';
                    }

                }
                auto lr=LinearRegression::compute(x, y,lowerUpperCutoff.first,x.size()-lowerUpperCutoff.second,false);
                std::cout<<"q "<<qs[j] <<" slope "<<lr.slope<<" quality "<<lr.adjusted_R2<<'\n';
                Dqs[j]=lr.slope;
            }
            std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
            x.clear();
            y.clear();

        }

        followOrder=true;
        bool validRange=true;

        double toleranceForFollowOrder=-0.005;
        for(long i=0;i<Dqs.size();i++){
//            if(i>0&&Dqs[i]-Dqs[i-1]>toleranceForFollowOrder){
//                followOrder=false;
//            }
            if(Dqs[i]>2||Dqs[i]<1){
                validRange=false;
//                currentAdjustedR2=0;
            }
        }


        if(Dqs[0]-Dqs[10]<toleranceForFollowOrder||Dqs[0]-Dqs[7]<toleranceForFollowOrder||Dqs[10]-Dqs[11]<toleranceForFollowOrder||Dqs[11]-Dqs[12]<toleranceForFollowOrder||Dqs[0]-Dqs[19]<toleranceForFollowOrder){
            followOrder=false;
        }
//        if(!followOrder||!validRange){
        if(!followOrder){
            currentAdjustedR2-=1;
        }


        std::cout<<"follow order "<<followOrder<<" valid "<<validRange<<" currentAdj-R2 "<<currentAdjustedR2<<" best adj-R2 "<<bestAdjustedR2<<'\n';

        if(std::isfinite(currentAdjustedR2)&&currentAdjustedR2>bestAdjustedR2){
            finalGridSize=gridSize;
            bestAdjustedR2=currentAdjustedR2;
            finalLowerCutoff=lowerUpperCutoff.first;
            finalUpperCutoff=lowerUpperCutoff.second;
        }

        if(!lowerBoundFound){

            if(!followOrder){
                lowerBoundFound=true;
                lowerBound=gridSize;
//                gridSizes.push_back(gridSize);
//                adjustedR2s.push_back(currentAdjustedR2);
                //            }
//                std::vector<long> order=Functions::getIndexesOfOrderedValues(gridSizes, true);
//                double currentMax=0;
//                double indexMax=0;
//                for(long i=0;i<order.size();i++){
//                    if(adjustedR2s[order[i]]>currentMax){
//                        currentMax=adjustedR2s[order[i]];
//                        indexMax=i;
//                    }
//                }
//                if(indexMax==order.size()-1){
//                    gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax-1]])/2.0;
//                    if(gridSizes[order[indexMax]]-gridSizes[order[indexMax-1]]<tolerance){
//                        break;
//                    }
//                }else if(indexMax==0){
//                    gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax+1]])/2.0;
//                    if(gridSizes[order[indexMax+1]]-gridSizes[order[indexMax]]<tolerance){
//                        break;
//                    }
//                }else{
//                    double d1=gridSizes[order[indexMax+1]]-gridSizes[order[indexMax]];
//                    double d2=gridSizes[order[indexMax]]-gridSizes[order[indexMax-1]];
//                    if(adjustedR2s[order[indexMax+1]]>adjustedR2s[order[indexMax-1]]){
//                        gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax+1]])/2.0;
//                        if(d1<tolerance){
//                            break;
//                        }
//
//                    }else{
//                        gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax-1]])/2.0;
//                        if(d2<tolerance){
//                            break;
//                        }
//
//
//                    }
//                    //                if(d1<tolerance&&d2<tolerance){
//                    //                    break;
//                    //                }
//
//                }
            }else{
                gridSizes.push_back(gridSize);
                adjustedR2s.push_back(currentAdjustedR2);
                gridSize/=2.0;

            }
//            if(validRange){

//            }

        }else{
//            if(validRange){
                gridSizes.push_back(gridSize);
                adjustedR2s.push_back(currentAdjustedR2);
//            }
            std::vector<long> order=Functions::getIndexesOfOrderedValues(gridSizes, true);
            double currentMax=0;
            double indexMax=0;
            for(long i=0;i<order.size();i++){
                if(adjustedR2s[order[i]]>currentMax){
                    currentMax=adjustedR2s[order[i]];
                    indexMax=i;
                }
            }
            if(indexMax==order.size()-1){
                gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax-1]])/2.0;
                if(gridSizes[order[indexMax]]-gridSizes[order[indexMax-1]]<tolerance){
                    break;
                }
            }else if(indexMax==0){
                gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax+1]])/2.0;
                if(gridSizes[order[indexMax+1]]-gridSizes[order[indexMax]]<tolerance){
                    break;
                }
            }else{
                double d1=gridSizes[order[indexMax+1]]-gridSizes[order[indexMax]];
                double d2=gridSizes[order[indexMax]]-gridSizes[order[indexMax-1]];
                if(adjustedR2s[order[indexMax+1]]>adjustedR2s[order[indexMax-1]]){
                    gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax+1]])/2.0;
                    if(d1<tolerance){
                        break;
                    }

                }else{
                    gridSize=(gridSizes[order[indexMax]]+gridSizes[order[indexMax-1]])/2.0;
                    if(d2<tolerance){
                        break;
                    }


                }
//                if(d1<tolerance&&d2<tolerance){
//                    break;
//                }

            }
        }





//        if(!followOrder&&gridSize>lowerBound){
//            lowerBound=gridSize;
////            lowerBoundFound=true;
////            lowerBound=gridSize;
//        }
//        if(followOrder&&!validRange&&gridSize<upperBound&&gridSize>bestGridSize){
//            upperBound=gridSize;
//        }
//        if(followOrder&&validRange&&currentAdjustedR2>=bestAdjustedR2&&currentAdjustedR2>.975){
//            if(!firstTimeValid){
//                firstValidValue=gridSize;
//            }
//            firstTimeValid=true;
//            finalGridSize=gridSize;
//        }


//        if(currentAdjustedR2>=bestAdjustedR2&&currentAdjustedR2>.975){
//
//            bestAdjustedR2=currentAdjustedR2;
//            std::cout<<"                still valid"<<'\n';
//
//            previousGridSize=gridSize;
//            gridSize=(minSizeGrid+gridSize)/2.0;
//            finalLowerCutoff=lowerUpperCutoff.first;
//            finalUpperCutoff=lowerUpperCutoff.second;
//            std::cout<<"                lowerUpperCutoff "<<finalLowerCutoff<<" "<<finalUpperCutoff<<'\n';
//            if(Functions::abs(minSizeGrid-gridSize)<=tolerance&&minSizeGrid>0){
//                finalGridSize=previousGridSize;
//                break;
//            }
//
//
//        }else if((numberObjectsCounted<=1)&&bestAdjustedR2>0){
//
//            std::cout<<"                too low"<<'\n';
//            if(Functions::abs(previousGridSize-gridSize)>tolerance){
//                std::cout<<"                too little precise"<<'\n';
//                Dqs[0]=Dqs[1];//to keep on going the while loop
//                minSizeGrid=gridSize;
//                gridSize=(previousGridSize+gridSize)/2.0;
//                //                previousGridSize=Functions::max(previousGridSize,gridSize);
//                //                gridSize=gridSizeTemp;
//
//            }else {
//                std::cout<<"                terminating"<<'\n';
//                finalGridSize=Functions::max(gridSize,previousGridSize);
//                break;
//                //                previousGridSize=gridSize;
//                //                gridSize/=2;
//            }
//
//
//
//
//
//
//        }else if(bestAdjustedR2>0){
////            previousGridSize=gridSize;
//            minSizeGrid=gridSize;
//            gridSize=(previousGridSize+gridSize)/2.0;
//
//        }else{
//            previousGridSize=gridSize;
//            gridSize=(minSizeGrid+gridSize)/2.0;
//        }


    }



//    InterfaceMultiFractalAnalysis ima;
//    Dqs.swap(ima.Dqs);
    return std::pair<double,std::pair<long,long> > (finalGridSize,std::pair<long,long> (finalLowerCutoff,finalUpperCutoff));

}
























InterfaceMultiFractalAnalysis FractalDimension::MultifractalAnalysis_sandBox(Grafo* G,std::vector<double> &qs){
    std::cout<<'\n';
    std::cout<<"Calculating fractal dimension "<<'\n';
    double massNode=1;
    double M=G->nodes.size()*massNode;
    // double L=sqrt(M);



    std::vector<std::vector<SparseMatrix> > multipleGrids;

//    SparseMatrix level4;
    int GEOMETRIC=0;
    int ARITHMETIC=1;
    int type=GEOMETRIC;

//    long lowerCutoff=0;
//    long upperCutoff=0;
    double maxDepth=4;
    double probabilityToDecideIfCompute=1.0;
    long numberCalculations=1;
    if(type==ARITHMETIC){
        numberCalculations=1;
    }

    // auto detectGridSize=FractalDimension::detectStartingGridSize(G,maxDepth);

double accumWeight=0;
    double longestDistance=0;
    for(long i=0;i<G->links.size();i++){
        accumWeight+=G->links[i]->weight;
        if(G->links[i]->weight>longestDistance){
            longestDistance=G->links[i]->weight;
        }
    }
   double averWeight=accumWeight/(double)G->links.size();

    auto detectGridSize=FractalDimension::detectStartingGridSize(G,maxDepth);
    // std::pair<double,std::pair<long,long> > detectGridSize=std::pair<double,std::pair<long,long> > (averWeight*2,std::pair<long,long> (0,0));





//    detectGridSize.second.first+=1;
//    detectGridSize.second.second+=1;
    double gridSize=detectGridSize.first;
    std::cout<<"cutoffs "<<detectGridSize.second.first<<" "<<maxDepth-detectGridSize.second.second<<'\n';

//    maxDepth=maxDepth-detectGridSize.second.second;
//    detectGridSize.second.second=0;

    multipleGrids.resize(numberCalculations);
    for(long i=0;i<numberCalculations;i++){
        multipleGrids[i].resize(maxDepth,SparseMatrix());
    }

    std::vector<double> Dqs;
    Dqs.resize(qs.size(),0.0);

    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

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


    std::vector<double> x;
    std::vector<double> y;
//    LinearRegression linearRegression;








    std::vector<double> averageDistances;
    std::vector<double> averageDistancesTemp;
    std::vector<double> numObjects;
    std::vector<std::vector<double> > masses;
    std::vector<double> massesDeformedByQ;
    std::vector<double> massesTemp;
    std::vector<double> numberTimesExist;
    std::vector<double> radii;
    std::vector<double> topologicalRadii;
    averageDistances.resize(maxDepth+1,0);
    averageDistancesTemp.resize(maxDepth+1,0);
    numObjects.resize(maxDepth+1,0);

    massesDeformedByQ.resize(maxDepth+1,0);
    massesTemp.resize(maxDepth+1,0);

    std::vector<double> alphas;
    alphas.resize(G->nodes.size());
    std::vector<double> gammas;
    gammas.resize(G->nodes.size());





    // double accumWeight=0;
    // double longestDistance=0;
    // for(long i=0;i<G->links.size();i++){
    //     accumWeight+=G->links[i]->weight;
    //     if(G->links[i]->weight>longestDistance){
    //         longestDistance=G->links[i]->weight;
    //     }
    // }
//    double averWeight=accumWeight/(double)G->links.size();
//    double maxDistance=(averWeight)*maxDepth;
//    double coef=M_PI/4.0;
//    coef=1.0;

//    lowerCutoff=detectGridSize.second.first;
//    upperCutoff=detectGridSize.second.second;
    for(long g=0;g<multipleGrids.size();g++){
//        for(long g=0;g<multipleGrids.size();g++){
            multipleGrids[g].clear();
            multipleGrids[g].resize(maxDepth,SparseMatrix());
//        }
        Point2d startPoint=Point2d(Functions::runiform(0,gridSize),Functions::runiform(0,gridSize));
        if(g==0){
            startPoint=Point2d(0,0);
        }
        std::cout<<"Calculating levels, grid size = "<<gridSize<<'\n';
        for(long i=0;i<G->nodes.size();i++){
    //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
                multipleGrids[g][0].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSize)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSize)),massNode);
    //        }
        }

        std::cout<<"level 0 calculated"<<'\n';
        if(type==GEOMETRIC){
            for(long i=0;i<maxDepth-1;i++){
                double gridSizeTemp;

                gridSizeTemp=pow(3.0,i);

                for(auto& it:multipleGrids[g][0].cells){
                    Point2d current=it.first;
                    for(long j=0;j<3;j++){
                        for(long h=0;h<3;h++){

                            multipleGrids[g][i+1].increaseBy((current.x),(current.y),multipleGrids[g][i].getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
                        }
                    }
                }
                std::cout<<"level "<<i+1<<"/"<<maxDepth<<" calculated"<<'\n';
            }
        }
    }
//    std::cout<<"level 2/"<< maxDepth<<" calculated"<<'\n';
//    double gridSizeTemp=3.0;
//    for(auto& it:level1.cells){
//        Point2d current=it.first;
//        for(long j=0;j<3;j++){
//            for(long h=0;h<3;h++){
//                level2.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level1.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
//            }
//        }
//    }
//    std::cout<<"level 3/"<< maxDepth<<" calculated"<<'\n';
//    gridSizeTemp=9.0;
//    for(auto& it:level2.cells){
//        Point2d current=it.first;
//        for(long j=0;j<3;j++){
//            for(long h=0;h<3;h++){
//                level3.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level2.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
//            }
//        }
//    }
//    std::cout<<"level 4/"<< maxDepth<<" calculated"<<'\n';
//    gridSizeTemp=3.0;
//    for(long j=0;j<3;j++){
//        for(long h=0;h<3;h++){
//            for(auto& it:level3.cells){
//                Point2d current=it.first;
//
//                level4.increaseBy(static_cast<long>(round((current.x)/gridSizeTemp)*gridSizeTemp-1+j),static_cast<long>(round((current.y)/gridSizeTemp)*gridSizeTemp-1+h),it.second.value);
//            }
//        }
//    }

    masses.resize(multipleGrids[0][0].cells.size(),std::vector<double>());















    radii.clear();

    for(double i=0.0;i<maxDepth;i++){
        if(type==GEOMETRIC){
            radii.push_back(gridSize*pow(3.0,i));
        }
        if(type==ARITHMETIC){
            radii.push_back(gridSize*((i*2.0)+1.0));
            topologicalRadii.push_back(i);
        }

        std::cout<<"radii "<<radii[i]<<'\n';
    }




    x.clear();
    y.clear();




    double sqrt2=sqrt(2);

    double numberObjectsCounted=0;
    long j=0;
    std::vector<double> xs;
    std::vector<double> ys;
    xs.reserve(radii.size());
    ys.reserve(radii.size());

   M=0;
    for(auto& it:multipleGrids[0][0].cells){
        Point2d current=it.first;
        M+=multipleGrids[0][0].getValue(current.x,current.y);
        masses[j].clear();

        if(Functions::runiform(0, 1)<probabilityToDecideIfCompute){
            numberObjectsCounted++;



            masses[j].resize(maxDepth,0);
            if(type==ARITHMETIC){
                for(long i=-maxDepth;i<=maxDepth;i++){
                    for(long g=-maxDepth;g<=maxDepth;g++){
                        for(long h=topologicalRadii.size()-1;h>=0;h--){
                            double distance=Functions::getDistance(current,Point2d(current.x+i,current.y+g));
                            if(distance<=topologicalRadii[h]*sqrt2){
                                masses[j][h]+=multipleGrids[0][0].getValue(current.x+i,current.y+g);
                            }else{
                                break;
                            }
                        }

                    }
                }
            }else{
                for(long g=0;g<numberCalculations;g++){
                    for(long i=0;i<maxDepth;i++){
                        masses[j][i]+=multipleGrids[g][i].getValue(current.x,current.y)/(double)(numberCalculations);
                    }
                }
            }




            auto lr=LinearRegression::computeBestFit(radii, masses[j],true);
            if(lr.first.slope<1||lr.first.slope>2||lr.first.adjusted_R2<0.99){
                masses[j].clear();
                numberObjectsCounted--;
            }
        }

        j++;

    }










//     double q=2.0;

//     double M_temp=1.0;
//     double L_temp=1.0;
//     double maxMass=0.0;
//     for(long i=0;i<masses.size();i++){



//         if(masses[i].size()>0){
//             //                                std::cout<<"gamma "<<gammas[i]<<'\n';

//             for(long h=0;h<radii.size()-0;h++){
//                 //                if(masses[i][h]<1){
//                 //                    std::cout<<""<<'\n';
//                 //                }
//                 massesDeformedByQ[h]+=pow(masses[i][h]/M_temp,q-1)/numberObjectsCounted;
//                 //                        std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
//                 if(masses[i][h]>maxMass){

//                     maxMass=masses[i][h];
//                 }
//             }
//         }

//     }



// //    for(long i=0;i<radii.size()-0;i++){
// //
// //
// //
// //
// //        x.push_back(log(massesDeformedByQ[i])/(q-1));
// //        y.push_back(log(radii[i]*coefRadius/L_temp));
// //        if(i>=detectGridSize.second.first&&i<=maxDepth-detectGridSize.second.second){
// //            std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(log(radii[i]*coefRadius/L_temp))<<",mass="<<exp(log(massesDeformedByQ[i])/(q-1))<<"))"<<'\n';
// //        }
// //
// //    }
// //    auto lr=LinearRegression::compute(y,x,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
// //    double D2=lr.slope;
// //    std::cout<<"D2="<<D2<<'\n';

//     for(long i=0;i<radii.size()-0;i++){




//         x.push_back(log(massesDeformedByQ[i])/(q-1));
//         y.push_back(log(radii[i]/L_temp));
//         std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';

//     }
//     auto lr=LinearRegression::compute(y,x,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
//     double D2=lr.slope;
//     std::cout<<"D2="<<D2<<'\n';

//     lr=LinearRegression::compute(x,y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);


//     double slopeA=lr.slope;
//     double interceptA=lr.intercept;
//     long size=x.size();
//     x.clear();
//     y.clear();
//     for(long i=0;i<size;i++){
//         x.push_back(exp(log(massesDeformedByQ[i])/(q-1)*slopeA+interceptA));
//         y.push_back(radii[i]/L_temp);
//     }
//     lr=LinearRegression::compute(x,y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);


//     //    L=pow(M,1/1.7149);
//     //    M=maxMass;
//     L=lr.slope*(exp(log(M)*slopeA+interceptA))+lr.intercept;


    M=G->nodes.size()*massNode;
        double L=sqrt(M);








//    M=1;
//    L=1;

    std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
    x.clear();
    y.clear();
    for(long j=0;j<qs.size();j++){
        if(qs[j]!=1){


            for(long i=0;i<masses.size();i++){


                if(masses[i].size()>0){

                    for(long h=0;h<radii.size()-0;h++){
                        massesDeformedByQ[h]+=pow(masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted;
                        if(h==0){
//                            std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
                        }

                    }
                }
            }
//            std::cout<<'\n';
            for(long i=0;i<radii.size()-0;i++){


//                if(radii[i]/L>0&&massesDeformedByQ[i]>0){
                    x.push_back(log(radii[i]/L));
                    y.push_back(log(massesDeformedByQ[i])/(qs[j]-1.0));
//                }
//                 std::cout<<qs[j]<<" "<<massesDeformedByQ[i]<<" "<<log(massesDeformedByQ[i])<<" "<<log(massesDeformedByQ[i])/(qs[j]-1.0)<<'\n';
                 if(i>=detectGridSize.second.first&&i<maxDepth-detectGridSize.second.second){
                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<(x[x.size()-1])<<",mass="<<(log(massesDeformedByQ[i])/(qs[j]-1.0))<<"))"<<'\n';
                 }
//                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';


            }
            if(j==0){
//                detectGridSize.second=LinearRegression::detectUpperAndLowerCutoff(x, y, false);
//                detectGridSize.second.first+=1;
//                detectGridSize.second.second+=1;
            }
            auto lr=LinearRegression::compute(x, y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
            Dqs[j]=lr.slope;
            std::cout<<"R2 ="<<lr.R2<<'\n';

        }else{

            for(long i=0;i<masses.size();i++){


                if(masses[i].size()>0){

                    for(long h=0;h<radii.size()-0;h++){
                        massesDeformedByQ[h]+=log(masses[i][h]/M)/numberObjectsCounted;

                    }
                }
            }

            for(long i=0;i<radii.size()-0;i++){


//                if(radii[i]/L>0){
                    x.push_back(log(radii[i]/L));
                    y.push_back((massesDeformedByQ[i]));
                 if(i>=detectGridSize.second.first&&i<maxDepth-detectGridSize.second.second){
                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<(x[x.size()-1])<<",mass="<<(massesDeformedByQ[i])<<"))"<<'\n';
                 }
//                }

            }
            auto lr=LinearRegression::compute(x, y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
            Dqs[j]=lr.slope;
        }
        std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
        x.clear();
        y.clear();

    }

    InterfaceMultiFractalAnalysis ima;
    Dqs.swap(ima.Dqs);
    return ima;

}






double FractalDimension::calculateCapacityDimension(Grafo* G){
//    std::cout<<"Calculating fractal dimension "<<'\n';

    std::vector<double> x;
    std::vector<double> y;
//    LinearRegression linearRegression;

    double distanceCells=10;
    double minDistanceCells=0;
    double minDistanceCells_final=1;

    std::vector<double> fixedDistances;
    std::vector<double> numObjects;
    std::vector<double> numObjectsPerDistance;
    std::vector<double> masses;

    std::vector<long> distanceIndex;
    std::vector<double> cols;
    std::vector<double> rows;



    SparseMatrix matrix;
    matrix.set_NULL_Value(0);

    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

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
    double widthX=maxX-minX;
    double widthY=maxY-minY;


    double gridSizeX=1;
    double gridSizeY=1;

    double initialGridSize=250;
    double maxNumberObjects=1000;
    double minNumberObjects=100;

    auto coordinates=Grafo::getCoordinates(G);
//    double fractalDimBC=FractalDimension::calculateBoxCounting(std::get<1>(coordinates),std::get<2>(coordinates),Functions::max(500,Functions::min(widthX,widthY)/100),Functions::max(100,Functions::min(widthX,widthY)/1000),10);
//    std::cout<<"box-counting = "<<std::to_string(fractalDimBC)<<'\n';

    if(widthX>widthY){

        if(widthX/initialGridSize>maxNumberObjects){
            initialGridSize=widthX/maxNumberObjects;
        }
        if(widthX/initialGridSize<minNumberObjects){
            initialGridSize=widthX/minNumberObjects;
        }
        double definition=widthX/initialGridSize;
        gridSizeX=widthX/definition;
        double numObjectY=widthY/gridSizeX;
        gridSizeY=widthY/numObjectY;
    }else{

        if(widthY/initialGridSize>maxNumberObjects){
            initialGridSize=widthY/maxNumberObjects;
        }
        if(widthY/initialGridSize<minNumberObjects){
            initialGridSize=widthY/minNumberObjects;
        }
        double definition=widthY/initialGridSize;
        gridSizeY=widthY/definition;
        double numObjectX=widthX/gridSizeY;
        gridSizeX=widthX/numObjectX;

    }

//    std::cout<<"grid sizes "<<gridSizeX<<","<<gridSizeY<<'\n';

    double numberBoxesX=widthX/gridSizeX;
    double numberBoxesY=widthY/gridSizeY;
//    std::cout<<"number boxes "<<numberBoxesX<<","<<numberBoxesY<<'\n';

    for(long i=0;i<G->nodes.size();i++){

        matrix.increase(static_cast<long>(round((G->nodes[i]->location.x-minX)/gridSizeX)),static_cast<long>(round((G->nodes[i]->location.y-minY)/gridSizeY)));


    }

    x.clear();
    y.clear();

    fixedDistances.reserve(distanceCells*2+1);
    for(long i=-distanceCells;i<=distanceCells;i++){
        for(long j=-distanceCells;j<=distanceCells;j++){
            if(Functions::getDistance(Point2d(0,0), Point2d(i,j))>=minDistanceCells&&Functions::getDistance(Point2d(0,0), Point2d(i,j))<distanceCells){
                fixedDistances.push_back(Functions::getDistance(Point2d(0,0), Point2d(i,j)));
                cols.push_back(i+distanceCells);
                rows.push_back(j+distanceCells);
            }
        }
    }
    std::vector<long> order=Functions::getIndexesOfOrderedValues(fixedDistances, true);
    fixedDistances=Functions::orderVectorUsingAnotherVectorWithPositions(fixedDistances, order);
    cols=Functions::orderVectorUsingAnotherVectorWithPositions(cols, order);
    rows=Functions::orderVectorUsingAnotherVectorWithPositions(rows, order);
    std::vector<double> uniqueDistances=Functions::unique(fixedDistances);



    numObjects.resize(uniqueDistances.size(),0);
    numObjectsPerDistance.resize(uniqueDistances.size(),0);
    masses.resize(uniqueDistances.size(),0);


    distanceIndex.resize(fixedDistances.size(),0);
    for(long i=0;i<fixedDistances.size();i++){
        for(long j=0;j<uniqueDistances.size();j++){
            if(fixedDistances[i]==uniqueDistances[j]){

                distanceIndex[i]=j;
                numObjectsPerDistance[j]++;
            }
        }
    }

    std::vector<double> numberObjectsTemp;
    std::vector<double> massesTemp;
    numberObjectsTemp.resize(masses.size(),0);
    massesTemp.resize(masses.size(),0);
    double probability=.3;

    long numBoxesMeasured=0;
//    for(auto& it:matrix.cells){
    for(long f=0;f<numberBoxesX;f++){
    for(long h=0;h<numberBoxesY;h++){
        if(Functions::runiform(0, 1)<probability){
//    for(long h=0;h<numberBoxesY*numberBoxesX*percentage;h++){

//        Point2d current=it.first;
        Point2d current=Point2d(f,h);
//        Point2d current=Point2d(round(Functions::runiform(0, numberBoxesX)),round(Functions::runiform(0, numberBoxesY)));
//        std::cout<<current.x<<","<<current.y<<'\n';
        long index=0;
//        for(long i=0;i<=distanceCells*2;i++){
//            for(long j=0;j<=distanceCells*2;j++){
//        for(long g=0;g<Functions::min(distanceCells*2*distanceCells*2,10);g++){

                 for(long g=0;g<distanceIndex.size();g++){
//            long g=0;{

//        long i=Functions::rnorm(0, distanceCells*2);
// long j=Functions::rnorm(0, distanceCells*2);
//            long index=Functions::max(0,Functions::min(static_cast<long>(round(Functions::abs(Functions::rnorm(0, cols.size()/2)))),cols.size()-1));
                long actualIndex=distanceIndex[index];


                masses[actualIndex]+=matrix.getValue(static_cast<long>(round(current.x-distanceCells+cols[index])),static_cast<long>(round(current.y-distanceCells+rows[index])));
//            numObjects[actualIndex]++;
//            numberObjectsTemp[actualIndex]++;
//                if (matrix.getValue(static_cast<long>((current.x-distanceCells+cols[index])),static_cast<long>((current.y-distanceCells+rows[index])))>0){
////                    masses[actualIndex]+=1/numObjects[actualIndex];
//                    masses[actualIndex]++;
//                }
                index++;
            }

        numBoxesMeasured++;
//        for(long i=0;i<massesTemp.size();i++){
//            if(numberObjectsTemp[i]>0){
////                masses[i]+=massesTemp[i]/numberObjectsTemp[i]*pow(numObjectsPerDistance[i],fractalDimBC/2);
//                masses[i]+=massesTemp[i];
//            }
//        }
//        std::fill(numberObjectsTemp.begin(),numberObjectsTemp.end(),0);
//        std::fill(massesTemp.begin(),massesTemp.end(),0);
        }
    }
    }


//    numBoxesMeasured=1;

//    std::cout<<"total mass "<<G->nodes.size()<<'\n';

    double accumMass=0;
//    if(masses[0]>0){
//        accumMass=1;
//    }
    for(long i=0;i<uniqueDistances.size();i++){

        if(uniqueDistances[i]<minDistanceCells_final){
            accumMass+=masses[i]/numBoxesMeasured;
        }else if(uniqueDistances[i]>=minDistanceCells_final&&uniqueDistances[i]<=distanceCells){

            masses[i]/=numBoxesMeasured;
            accumMass+=masses[i];
            x.push_back(log(uniqueDistances[i]*gridSizeX));
            y.push_back(log(accumMass));
//            std::cout<<"df=rbind(df,data.frame(x="<<uniqueDistances[i]*gridSizeX<<",y="<<accumMass<<"))"<<'\n';
        }

    }

    auto lr=LinearRegression::compute(x,y,false);

    return lr.slope;
}






















InterfaceMultiFractalAnalysis FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(Grafo* G,std::vector<double> &qs){
    std::cout<<"Calculating fractal dimension "<<'\n';
    double M=G->nodes.size();
    double L=sqrt(M);
    double R=L/2;
//    M=1;
//    L=1;
    //    QTree quadTree;
    ////    if(!quadTreeCalculated){
    //        graph->insertGraphIntoQTree(&quadTree);
    //        quadTreeCalculated=true;
    //    }



    long lowerCutoff=0;
    long upperCutoff=0;
    double maxDepth=9.0;
    double probabilityToDecideIfCompute=.1;

    std::vector<double> Dqs;
    Dqs.resize(qs.size(),0);

    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

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
//    double widthX=maxX-minX;
//    double widthY=maxY-minY;

    std::vector<double> x;
    std::vector<double> y;
//    LinearRegression linearRegression;







//    double radius=maxDepth;
    std::vector<double> averageDistances;
    std::vector<double> averageDistancesTemp;
    std::vector<double> numObjects;
    std::vector<std::vector<double> > masses;
    std::vector<double> massesDeformedByQ;
    std::vector<double> massesTemp;
    std::vector<double> numberTimesExist;
    std::vector<double> radii;
    averageDistances.resize(maxDepth,0);
    averageDistancesTemp.resize(maxDepth,0);
    numObjects.resize(maxDepth,0);
    masses.resize(G->nodes.size(),std::vector<double>());
    massesDeformedByQ.resize(maxDepth,0);
    massesTemp.resize(maxDepth,0);

    std::vector<double> intercepts;
    intercepts.resize(G->nodes.size());
    std::vector<double> gammas;
    gammas.resize(G->nodes.size());
//    numberTimesExist.resize(maxDepth+1,0);


    InterfaceDijkstra result;
    result.prepareForBetweenness();

    std::vector<double> topologicalWeights;
//    //    if(type==InterfaceDijkstra::TOPOLOGICAL){
    topologicalWeights.resize(G->links.size(),1);
//    double maxDistance=-INFINITY;
//    Nodo* current=G->nodes[(long)Functions::runiform(0, G->nodes.size()-1)];
//    Grafo::calculateDijkstra(G,topologicalWeights,current,result,maxDepth*2);
////                distances.reserve(result.idsInCutoff.size());
//    for(long i=0;i<result.idsInCutoff.size();i++){
//
//        if(type==InterfaceDijkstra::EUCLIDEAN){
//            double distance=Functions::getDistance(current->location, G->nodes[result.idsInCutoff[i]]->location);
//            if(distance>maxDistance){
//                maxDistance=distance;
//            }
////                        distances.push_back(distance);
////                    averageDistancesTemp[result.getMinDistance(result.idsInCutoff[i])]+=distance;
//
//        }
////                numObjects[result.getMinDistance(result.idsInCutoff[i])]++;
//
////                massesTemp[result.getMinDistance(result.idsInCutoff[i])]++;
//
//
//    }
    double accumWeight=0;
    double longestDistance=0;
    for(long i=0;i<G->links.size();i++){
        accumWeight+=G->links[i]->weight;
        if(G->links[i]->weight>longestDistance){
            longestDistance=G->links[i]->weight;
        }
    }
    double averWeight=accumWeight/(double)G->links.size();
    double maxDistance=(averWeight)*maxDepth;
//    double maxDistance=(averWeight+longestDistance)/2*maxDepth;

//    double preferredCutoffRadius=maxDistance;

    for(double i=1;i<=maxDepth;i++){
//        radii.push_back(averWeight+i*averWeight);
        radii.push_back(2*R/(10)+i*averWeight);
    }


    x.clear();
    y.clear();
    //    bool stop=false;
    //    double totalMass=(double)G->nodes.size();
    //    for(long i=0;i<graph->nodes.size();i++){
    //        if(graph->nodes[i].mass>0){
    //            totalMass+=graph->nodes[i].mass;
    //        }
    //    }

    //    }
    //    double previousMass=0.0;
    //    while (!stop){

    //        double mass=0.0;

    InterfaceDijkstra resultWeighted;

    //        double squaredRadius=radius*radius;
    double numberObjectsCounted=0;
    std::vector<double> radiiTemp;
    radiiTemp.resize(maxDepth,0);
    std::vector<bool> inCutoff;
    for(long j=0;j<G->nodes.size();j++){
//        masses[j].clear();
//        if(j==20){
        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
            numberObjectsCounted++;
//            double maxDistance=-INFINITY;
            std::vector<double> distances;
//            std::vector<double> ysTemp;
//            Grafo::calculateDijkstra(G,topologicalWeights,G->nodes[j],result,maxDepth);
//            double maxEuclideanDistance=0;
//            for(long i=0;i<result.idsInCutoff.size();i++){
//                double euclideanDistance=Functions::getSquaredDistance(G->nodes[j]->location, G->nodes[result.idsInCutoff[i]]->location);
//                if(euclideanDistance>maxEuclideanDistance){
//                    maxEuclideanDistance=euclideanDistance;
//                }
//            }
            double maxWeight=0;
            for(long g=0;g<G->nodes[j]->links.size();g++){
                if(maxWeight<G->nodes[j]->links[g]->weight){
                    maxWeight=G->nodes[j]->links[g]->weight;
                }
            }
            double radiusCutoff=Functions::max(maxWeight*2,maxDistance);
//            distances.reserve(result.idsInCutoff.size());
//            for(long i=0;i<result.idsInCutoff.size();i++){
//
//                if(type==InterfaceDijkstra::EUCLIDEAN){
//                    double distance=Functions::getDistance(G->nodes[j]->location, G->nodes[result.idsInCutoff[i]]->location);
//                    if(distance>maxDistance){
//                        maxDistance=distance;
//                    }
//                    distances.push_back(distance);
////                    averageDistancesTemp[result.getMinDistance(result.idsInCutoff[i])]+=distance;
//
//                }
////                numObjects[result.getMinDistance(result.idsInCutoff[i])]++;
//
////                massesTemp[result.getMinDistance(result.idsInCutoff[i])]++;
//
//
//            }

            Grafo::startMeasuringAroundACircle(G, inCutoff);
            Grafo::takeMeasuresWithinACircle(G, G->nodes[j], result, radiusCutoff,inCutoff);


//            long f=0;
//            for(double i=1;i<=maxDepth;i++){
//                radiiTemp[i]=(i*radiusCutoff/maxDepth+.1);
////                f++;
//            }
//            std::cout<<"Size of cutoff "<<result.idsInCutoff.size()<<'\n';
            distances.reserve(result.idsInCutoff.size());
            std::vector<long> idsInCutoff;
            idsInCutoff.reserve(result.idsInCutoff.size());
            for(long i=0;i<result.idsInCutoff.size();i++){
                distances.push_back(result.getMinDistance(result.idsInCutoff[i]));
                idsInCutoff.push_back(result.idsInCutoff[i]);
//                if(result.getMinDistance(result.idsInCutoff[i])>maxDistance){
//                    maxDistance=result.getMinDistance(result.idsInCutoff[i]);
//                }
            }
            double accumMass=0;
            std::vector<long> order=Functions::getIndexesOfOrderedValues(distances, true);
            distances=Functions::orderVectorUsingAnotherVectorWithPositions(distances,order);
            idsInCutoff=Functions::orderVectorUsingAnotherVectorWithPositions(idsInCutoff, order);
            double index=0;
//            std::vector<double> distancesPerIndex;
//            distancesPerIndex.resize(massesTemp.size(),0);

            massesTemp.clear();

            radiiTemp.clear();
            accumMass=0;
            double previousRadius=-1;

            for(long i=0;i<distances.size();i++){
                accumMass++;
                if(distances[i]!=previousRadius){
//                    accumMass+=distances[i]-previousRadius;
                    previousRadius=distances[i];
                    radiiTemp.push_back(distances[i]+.1);
                    massesTemp.push_back(accumMass);
                }else if(distances[i]==previousRadius){
                    massesTemp[massesTemp.size()-1]=accumMass;
                }

////                distancesPerIndex[index]=maxDistance/maxDepth*(index+.1);
////                if(distances[i]<=maxDistance/maxDepth*(index+.1)){
////                    distancesPerIndex[index]=radii[index];
//                if(distances[i]<=radiiTemp[index]+.1){
////                    if(type==InterfaceDijkstra::EUCLIDEAN){
////                        averageDistancesTemp[i]/=numObjects[i];
////                        averageDistances[i]+=averageDistancesTemp[i];
////                    }
//
//
//
//                    accumMass++;
//
//                }else{
////                    accumMass=1;
//
//                    massesTemp[index]+=accumMass;
//                    accumMass++;
////                    massesDeformedByQ[index]+=pow(accumMass/M,q-1);
//                    index++;
//                }
//
//                if(i>0&&result.getMinDistance(idsInCutoff[i])>radiiTemp[index-1]&&result.getMinDistance(result.getParentID(idsInCutoff[i]))<radiiTemp[index-1]){
//                    double radius=radiiTemp[index-1];
//                    double distanceParent=result.getMinDistance(result.getParentID(idsInCutoff[i]));
//                    double distanceSon=result.getMinDistance(idsInCutoff[i]);
//                    double percentage=(radius-distanceParent)/(distanceSon-distanceParent);
//                    massesTemp[index-1]+=percentage;
//                }
//
////                numberTimesExist[i]++;

            }








//            massesTemp[index]=accumMass;
//            massesTemp[index]+=result.percentagesOfOutsideNodes;



//            for(long i=0;i<massesTemp.size();i++){
//                if(massesTemp[i]>0){
//                    masses[j].push_back(massesTemp[i]);
//                }else{
//                    masses[j].push_back(1);
////                    massesTemp[i]=1;
//                }
//            }

            std::vector<double> xsTemp;
            std::vector<double> ysTemp;
            double lowerCutoffTemp=1;
            double upperCutoffTemp=1;
            xsTemp.reserve(radiiTemp.size()-(lowerCutoffTemp+upperCutoffTemp));
            ysTemp.reserve(radiiTemp.size()-(lowerCutoffTemp+upperCutoffTemp));
            for(long i=lowerCutoffTemp;i<radiiTemp.size()-upperCutoffTemp;i++){
                if(radiiTemp[i]>0&&massesTemp[i]>0){
                    xsTemp.push_back(log(radiiTemp[i]));
                    ysTemp.push_back(log(massesTemp[i]));
                }
            }
            long weightFinalPosition=0;
            for(long i=0;i<weightFinalPosition;i++){
                xsTemp.push_back(log(R));
                ysTemp.push_back(log(M));
            }
            auto lr=LinearRegression::compute(xsTemp,ysTemp,false);
            double slopeA=lr.slope;
//            if(slopeA>1.78){
//            if(linearRegression.R2<.95){
//             std::cout<<'\n';
//                for(long i=lowerCutoffTemp;i<radiiTemp.size()-upperCutoffTemp;i++){
//                    std::cout<<"df=rbind(df,data.frame(q="<<2<<",radii="<<exp(xsTemp[i])<<",mass="<<exp(ysTemp[i])<<"))"<<'\n';
//                }
//            std::cout<<'\n';
//            }
//            }
            double interceptA=lr.intercept;










//            double init=1;
//            double end=xsTemp.size()-1;
//            if(slopeA<1){
//
//
//                while(end-init>1&&(linearRegression.slope<1||linearRegression.slope>2)){
//                    LinearRegression::compute(xsTemp, ysTemp, init, end);
////                    if(Functions::runiform(0, 1)<.95){
//                        end--;
////                    }else{
////                        init++;
////                    }
//                }
//                if(linearRegression.slope<1){
//                    slopeA=1;
//                }else if(linearRegression.slope>2){
//                    slopeA=2;
//                }else{
//                    slopeA=linearRegression.slope;
//
//                }
//                radiiTemp.clear();
//                massesTemp.clear();
//                radiiTemp.reserve(end-init);
//                massesTemp.reserve(end-init);
//                for(long i=0;i<xsTemp.size();i++){
//                    radiiTemp.push_back(exp(xsTemp[i]));
//                    massesTemp.push_back(exp(ysTemp[i]));
//                }
//
//
//            }
//            if(slopeA>2){
////                std::cout<<"slope larger than 2 "<<slopeA<<'\n';
//                while(end-init>1&&(linearRegression.slope<1||linearRegression.slope>2)){
//                    LinearRegression::compute(xsTemp, ysTemp, init, end);
////                    if(Functions::runiform(0, 1)<.95){
//                        end--;
////                    }else{
////                        init++;
////                    }
//                }
//                if(linearRegression.slope<1){
//                    slopeA=1;
//                }else if(linearRegression.slope>2){
//                    slopeA=2;
//                }else{
//                    slopeA=linearRegression.slope;
//
//                }
//                radiiTemp.clear();
//                massesTemp.clear();
//                radiiTemp.reserve(end-init);
//                massesTemp.reserve(end-init);
//                for(long i=0;i<xsTemp.size();i++){
//                    radiiTemp.push_back(exp(xsTemp[i]));
//                    massesTemp.push_back(exp(ysTemp[i]));
//                }
//
//            }

            if(slopeA>1&&slopeA<2&&lr.R2>.97){
                double minMass=1.5;
                xsTemp.clear();
                ysTemp.clear();
                xsTemp.reserve(radiiTemp.size()-(lowerCutoffTemp+upperCutoffTemp));
                ysTemp.reserve(radiiTemp.size()-(lowerCutoffTemp+upperCutoffTemp));
                gammas[j]=slopeA;
                for(long i=lowerCutoffTemp;i<radiiTemp.size()-upperCutoffTemp;i++){
                    if(radiiTemp[i]>0&&massesTemp[i]>0){
                        xsTemp.push_back(exp(slopeA*log(radiiTemp[i])+interceptA));
                        ysTemp.push_back((massesTemp[i]));
                    }
                }
                auto lr=LinearRegression::compute(xsTemp,ysTemp,false);
                double slopeB=lr.slope;
                double interceptB=lr.intercept;
    //            masses[j].resize(radii.size(),0);


                masses[j].resize(radii.size(),0);
                index=0;
                while(radii[index]<=radiiTemp[0]){
                    double extrapolatedMass=(slopeB*(exp(slopeA*log(radii[index])+interceptA)+interceptB));
                    masses[j][index]=Functions::min(M,Functions::max(minMass,extrapolatedMass));
                    index++;
                }
                if(index<radii.size()){
                    for(long i=0;i<radiiTemp.size();i++){
                        while(radii[index]<=radiiTemp[i]){
                            if(i>0){
                                double extrapolatedMass=(slopeB*(exp(slopeA*log(radii[index])+interceptA)+interceptB)-(slopeB*(exp(slopeA*log(radiiTemp[i-1])+interceptA)+interceptB))+massesTemp[i-1]);
                                masses[j][index]=Functions::min(M,Functions::max(minMass,extrapolatedMass));
                                index++;

                            }else{
                                double extrapolatedMass=(slopeB*(exp(slopeA*log(radii[index])+interceptA)+interceptB));
                                masses[j][index]=Functions::min(M,Functions::max(minMass,extrapolatedMass));
                                index++;
                            }
                            if(index>radii.size()-1){
                                break;
                            }
                        }
                        if(index>radii.size()-1){
                            break;
                        }
                        if(radii[index]>radiiTemp[radiiTemp.size()-1]){
                            break;
                        }

                    }
                    for(long indexB=0;indexB<radii.size();indexB++){
                        if(radii[indexB]>=radiiTemp[radiiTemp.size()-1]){
                            double extrapolatedMass=(slopeB*(exp(slopeA*log(radii[indexB])+interceptA)+interceptB)-(slopeB*(exp(slopeA*log(radiiTemp[radiiTemp.size()-1])+interceptA)+interceptB))+massesTemp[radiiTemp.size()-1]);
                            masses[j][indexB]=Functions::min(M,Functions::max(minMass,extrapolatedMass));
                        }
                    }
                }




            }else{
                masses[j].clear();
                numberObjectsCounted--;
            }
            std::fill (massesTemp.begin(),massesTemp.end(),0);
            std::fill (radiiTemp.begin(),radiiTemp.end(),0);
//            std::cout<<'\n';
//            for(long i=0;i<radii.size();i++){
//                std::cout<<"df=rbind(df,data.frame(q="<<2<<",radii="<<radii[i]<<",mass="<<masses[j][i]<<"))"<<'\n';
//            }
//            std::cout<<'\n';




//            for(long i=0;i<radii.size();i++){
////                if(radiiTemp[i]>0&&massesTemp[i]>0){
//                double correction=radii[i]/averWeight+1;
////                double idealMass=Functions::max(correction,(slopeB*(exp(slopeA*log(radii[i])+interceptA))+interceptB));
//                double realMass=masses[j][i];
////                double mass=Functions::max(correction,((exp(slopeA*log(radii[i])))));
////                if(mass<1){
////                    mass=1;
////                }
//                masses[j][i]=(realMass);
////                }
//            }




//            if(linearRegression.slope>=1&&linearRegression.slope<=2){
//                gammas[j]=linearRegression.slope;
////                alphas[j]=log(M/massesTemp[3]);
//            }else{
//                if (linearRegression.slope<1){
//                    std::cout<<"dimension smaller than 1 "<<j<<" "<<'\n';
//                    for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){
//                        if(radii[i]>0&&massesTemp[i]>0){
//                            std::cout<<"df=rbind(df,data.frame(q="<<2<<",radii="<<exp(xsTemp[i])<<",mass="<<exp(ysTemp[i])<<"))"<<'\n';
//                        }
//                    }
//                    std::cout<<'\n';
//                    for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){
////                        if(radii[i]>0&&massesTemp[i]>0){
//                            std::cout<<"df=rbind(df,data.frame(q="<<2<<",radii="<<radii[i]<<",mass="<<massesTemp[i]<<"))"<<'\n';
////                        }
//                    }
//                    std::cout<<'\n';
//                    gammas[j]=1;
//                }
//                if(linearRegression.slope>2){
//                    std::cout<<"dimension larger than 2 "<<j<<'\n';
//                    for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){
//                        if(radii[i]>0&&massesTemp[i]>0){
//                            std::cout<<"df=rbind(df,data.frame(q="<<2<<",radii="<<exp(xsTemp[i])<<",mass="<<exp(ysTemp[i])<<"))"<<'\n';
//                        }
//                    }
//                    std::cout<<'\n';
//                    for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){
//                        //                        if(radii[i]>0&&massesTemp[i]>0){
//                        std::cout<<"df=rbind(df,data.frame(q="<<2<<",radii="<<radii[i]<<",mass="<<massesTemp[i]<<"))"<<'\n';
//                        //                        }
//                    }
//                    std::cout<<'\n';
//                    gammas[j]=2;
//                }
//            }
//            xsTemp.clear();
//            ysTemp.clear();
//            for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){
//
//
//                    double idealMass=exp(gammas[j]*log(radii[i])+intercepts[j]);
//                    xsTemp.push_back(idealMass);
//                    ysTemp.push_back(massesTemp[i]);
//
//            }
//            LinearRegression::compute(xsTemp,ysTemp);

//            for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){
//
//
//                    double idealMass=(exp(gammas[j]*log(radii[i])+intercepts[j]));
//                masses[j][i]=(idealMass+masses[j][i])/2;
////                    xsTemp.push_back(idealMass);
////                    ysTemp.push_back(massesTemp[i]);
//
//            }


//            massesDeformedByQ[index]+=pow(accumMass,q-1);
//            std::vector<double> xsTemp;
//            std::vector<double> ysTemp;
//            for(long i=1;i<massesTemp.size();i++){
////                distancesPerIndex[i]=log(distancesPerIndex[i]);
////                massesTemp[i]=log(massesTemp[i]);
//                if(massesTemp[i]>=1&&distancesPerIndex[i]>=1){
//                    xsTemp.push_back(log(distancesPerIndex[i]));
//                    ysTemp.push_back(log(massesTemp[i]));
////                    std::cout<<"df=rbind(df,data.frame(x="<<distancesPerIndex[i]<<",y="<<massesTemp[i]<<"))"<<'\n';
//                }
//            }
//            distances.clear();
//            LinearRegression::compute(xsTemp,ysTemp);
////            std::cout<<"slope = "<<linearRegression.slope<<'\n';
//            for(long i=0;i<radii.size();i++){
//                masses[i]+=pow((pow(radii[i],linearRegression.slope)+1)/M,q-1);
//            }
//            pow(accumMass/M,q-1);
//            std::fill (massesTemp.begin(),massesTemp.end(),0);
//            std::fill (radiiTemp.begin(),radiiTemp.end(),0);
//            std::fill (numObjects.begin(),numObjects.end(),0);
//            std::fill (averageDistancesTemp.begin(),averageDistancesTemp.end(),0);
            //                mass+=(double)result.numberNodesInCutoff/totalMass;
            //            }else{
            ////                Grafo::calculateDijkstra(G,G->nodes[j],result,radius);
            //                Grafo::takeMeasuresWithinACircle(G, G->nodes[j], result, radius);
            //                mass+=(double)result.numberNodesInCutoff/totalMass;
            //            }

            //            std::cout<<"Number nodes in cutoff in correlation dimension "<<result.numberNodesInCutoff<<'\n';
            //                for(long i=0;i<nodesInRange.size();i++){
            //                    if(nodesInRange[i]->mass>0&&nodesInRange[i]!=&graph->nodes[j]){
            //                        mass+=nodesInRange[i]->mass*graph->nodes[j].mass;
            //                    }
            //                }
            //            }
        }

    }

//    M=1;
//    L=1;





    double coefArea=4/M_PI;
    double coefRadius=2;
    double q=2;

    double M_temp=1;
    double L_temp=1;
    double maxMass=0;
    for(long i=0;i<masses.size();i++){



        if(masses[i].size()>0){
//                                std::cout<<"gamma "<<gammas[i]<<'\n';

            for(long h=lowerCutoff;h<radii.size()-upperCutoff;h++){
//                if(masses[i][h]<1){
//                    std::cout<<""<<'\n';
//                }
                massesDeformedByQ[h]+=pow(coefArea*masses[i][h]/M_temp,q-1)/numberObjectsCounted;
                //                        std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
                if(masses[i][h]>maxMass){

                    maxMass=masses[i][h];
                }
            }
        }

    }



    for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){




        x.push_back(log(massesDeformedByQ[i])/(q-1));
        y.push_back(log(radii[i]*coefRadius/L_temp));
         std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';

    }
    auto lr=LinearRegression::compute(y,x,false);
    double D2=lr.slope;
    std::cout<<"D2="<<D2<<'\n';
    coefArea=pow(4/M_PI,D2/2);
    lr=LinearRegression::compute(x,y,false);


    double slopeA=lr.slope;
    double interceptA=lr.intercept;
    long size=x.size();
    x.clear();
    y.clear();
    for(long i=0;i<size;i++){
        x.push_back(exp(log(massesDeformedByQ[i])/(q-1)*slopeA+interceptA));
        y.push_back(radii[i]*coefRadius/L_temp);
    }
    lr=LinearRegression::compute(x,y,false);


//    L=pow(M,1/1.7149);
//    M=maxMass;
    L=lr.slope*(exp(log(M)*slopeA+interceptA))+lr.intercept;
//    coefArea=4/M_PI;
//    L=1;

//    M=1;
//    L=1;
//    L=radii[radii.size()-1]*2;
//    M=maxMass;

    std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
    x.clear();
    y.clear();
    for(long j=0;j<qs.size();j++){
        if(qs[j]!=1){
//            double numObjects=0;

            for(long i=0;i<masses.size();i++){

//                if(gammas[i]!=0){
//
//                    for(long h=lowerCutoff;h<radii.size()-upperCutoff;h++){
//                        double idealMass=exp(gammas[i]*log(radii[h])+intercepts[i]);
//
//                        massesDeformedByQ[h]+=pow(idealMass/M,qs[j]-1.0)/numberObjectsCounted;
//
//                    }
//                }
                if(masses[i].size()>0){
//                    std::cout<<"gamma "<<gammas[i]<<'\n';
                    for(long h=lowerCutoff;h<radii.size()-upperCutoff;h++){
                        if(qs[j]==0){
//                            std::cout<<(4/M_PI)*masses[i][h]<<" "<<(4/M_PI)*masses[i][h]/M<<" "<<pow((4/M_PI)*masses[i][h]/M,qs[j]-1.0)<<" "<<pow((4/M_PI)*masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted<<" "<<log(pow((4/M_PI)*masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted)<<'\n';
                        }
                        massesDeformedByQ[h]+=pow((coefArea)*masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted;
//                        std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';

                    }
                }
            }
//            std::cout<<'\n';
            for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){


                if(radii[i]/L>0&&massesDeformedByQ[i]>0){
                    x.push_back(log(radii[i]*coefRadius/L));
                    y.push_back(log(massesDeformedByQ[i])/(qs[j]-1.0));
                     std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';
                }
//                  std::cout<<"df=rbind(df,data.frame(x="<<exp(x[x.size()-1])<<",y="<<exp(y[y.size()-1])<<"))"<<'\n';
                //            std::cout<<averageDistances[i]<<" "<<accumMass<<'\n';
                //        }
            }
            auto lr=LinearRegression::compute(x, y,false);
            Dqs[j]=lr.slope;

        }else{

            for(long i=0;i<masses.size();i++){

//                if(gammas[i]!=0){
//
//                    for(long h=lowerCutoff;h<radii.size()-upperCutoff;h++){
//                        massesDeformedByQ[h]+=log(exp(gammas[i]*log(radii[h])+intercepts[i])/M)/numberObjectsCounted;
//
//                    }
//                }
                if(masses[i].size()>0){

                    for(long h=lowerCutoff;h<radii.size()-upperCutoff;h++){
                        massesDeformedByQ[h]+=log((coefArea)*masses[i][h]/M)/numberObjectsCounted;

                    }
                }
            }

            for(long i=lowerCutoff;i<radii.size()-upperCutoff;i++){


                if(radii[i]/L>0){
                    x.push_back(log(radii[i]*coefRadius/L));
                    y.push_back((massesDeformedByQ[i]));
                     std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';
                }
//                std::cout<<"df=rbind(df,data.frame(x="<<exp(x[x.size()-1])<<",y="<<exp(y[y.size()-1])<<"))"<<'\n';
                //            std::cout<<averageDistances[i]<<" "<<accumMass<<'\n';
                //        }
            }
            auto lr=LinearRegression::compute(x, y,false);
            Dqs[j]=lr.slope;
        }
        std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
        x.clear();
        y.clear();
//        std::cout<<'\n';
    }
    //        std::cout<<"mass "<<mass<<" prev. "<<previousMass<<'\n';
    //        if(mass>0){
    ////            if(Functions::abs((0.0)-(previousMass))<.1){
    //
    ////                y.push_back(log((mass/pow(totalMass,2))));
    //
    //            std::cout<<"mass in correlation dimension "<<mass<<" "<<totalMass<<'\n';
    ////            }else{
    ////                double delta=.01;
    ////                if((log(mass)/log(previousMass))>1+delta||(log(mass)/log(previousMass))<1-delta){
    ////                    x.push_back(log(radius));
    ////                    y.push_back(log((mass/pow(totalMass,2))));
    ////                }else{
    ////                    if(x.size()==1){
    ////                        x[0]=(log(radius));
    ////                        y[0]=(log((mass/pow(totalMass,2))));
    ////                    }else{
    ////    //                    x[x.size()-1]=(log(radius));
    ////    //                    y[x.size()-1]=(log((mass/pow(totalMass,2))));
    ////                    }
    ////                }
    ////            }
    ////            previousMass=mass;
    //        }
    //        if((radius>=5&&type==InterfaceDijkstra::TOPOLOGICAL)||(radius>=1200&&type==InterfaceDijkstra::METRIC)){
    //            stop=true;
    //        }
    //        if(type==InterfaceDijkstra::TOPOLOGICAL){
    //            radius+=inc_radius;
    //        }else if(type==InterfaceDijkstra::METRIC){
    //            radius*=inc_radius;
    //        }



    //    }
//    Grafo::finishCalculatingShortestPaths(G);
        Grafo::finishMeasuringAroundACircle(G,inCutoff);
    InterfaceMultiFractalAnalysis ima;
    Dqs.swap(ima.Dqs);
    return ima;
//    LinearRegression::compute(x,y);
//    return linearRegression.slope;
}






double FractalDimension::calculateDimensionSpatiallyEmbeddedGraph(Grafo* G,int type){
//    QTree quadTree;
////    if(!quadTreeCalculated){
//        graph->insertGraphIntoQTree(&quadTree);
//        quadTreeCalculated=true;
//    }
    std::vector<double> x;
    std::vector<double> y;
//    LinearRegression linearRegression;
    long maxDepth=5;
    double radius=maxDepth;
    std::vector<double> averageDistances;
    std::vector<double> averageDistancesTemp;
    std::vector<double> numObjects;
    std::vector<double> masses;
    std::vector<double> numberTimesExist;
    averageDistances.resize(maxDepth+1,0);
    averageDistancesTemp.resize(maxDepth+1,0);
    numObjects.resize(maxDepth+1,0);
    masses.resize(maxDepth+1,0);
    numberTimesExist.resize(maxDepth+1,0);




    x.clear();
    y.clear();
//    bool stop=false;
//    double totalMass=(double)G->nodes.size();
//    for(long i=0;i<graph->nodes.size();i++){
//        if(graph->nodes[i].mass>0){
//            totalMass+=graph->nodes[i].mass;
//        }
//    }
    std::vector<double> topologicalWeights;
//    if(type==InterfaceDijkstra::TOPOLOGICAL){
        topologicalWeights.resize(G->links.size(),1);
//    }
//    double previousMass=0.0;
//    while (!stop){
        std::cout<<"Calculating fractal dimension "<<'\n';
//        double mass=0.0;
        InterfaceDijkstra result;
        InterfaceDijkstra resultWeighted;
    std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
//        double squaredRadius=radius*radius;
        for(long j=0;j<G->nodes.size();j++){
//            if(graph->nodes[j].mass>0){
//                std::vector<Node*> nodesInRange=quadTree.getNodesInARange(graph->nodes[j].location, radius);
//            if(type==InterfaceDijkstra::TOPOLOGICAL){
            Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
                Grafo::calculateDijkstra(G,topologicalWeights,G->nodes[j],result,radius,numbersRepresentingNodes,inDijkstra,inCutoff);
            for(long i=0;i<result.idsInCutoff.size();i++){
//                double distance;
                if(type==InterfaceDijkstra::EUCLIDEAN){
                    double distance=Functions::getDistance(G->nodes[j]->location, G->nodes[result.idsInCutoff[i]]->location);
                    averageDistancesTemp[result.getMinDistance(result.idsInCutoff[i])]+=distance;

                }
                numObjects[result.getMinDistance(result.idsInCutoff[i])]++;

                masses[result.getMinDistance(result.idsInCutoff[i])]++;


            }
            for(long i=0;i<averageDistancesTemp.size();i++){
                if(numObjects[i]>0){
                    if(type==InterfaceDijkstra::EUCLIDEAN){
                        averageDistancesTemp[i]/=numObjects[i];
                        averageDistances[i]+=averageDistancesTemp[i];
                    }
                    numberTimesExist[i]++;
                }
            }
            std::fill (numObjects.begin(),numObjects.end(),0);
            std::fill (averageDistancesTemp.begin(),averageDistancesTemp.end(),0);
//                mass+=(double)result.numberNodesInCutoff/totalMass;
//            }else{
////                Grafo::calculateDijkstra(G,G->nodes[j],result,radius);
//                Grafo::takeMeasuresWithinACircle(G, G->nodes[j], result, radius);
//                mass+=(double)result.numberNodesInCutoff/totalMass;
//            }

//            std::cout<<"Number nodes in cutoff in correlation dimension "<<result.numberNodesInCutoff<<'\n';
//                for(long i=0;i<nodesInRange.size();i++){
//                    if(nodesInRange[i]->mass>0&&nodesInRange[i]!=&graph->nodes[j]){
//                        mass+=nodesInRange[i]->mass*graph->nodes[j].mass;
//                    }
//                }
//            }

        }
    double accumMass=masses[0]/numberTimesExist[0];
    for(long i=1;i<averageDistances.size();i++){
//        if(averageDistances[i]>0){
            if(type==InterfaceDijkstra::EUCLIDEAN){
                averageDistances[i]/=numberTimesExist[i];
            }else if(type==InterfaceDijkstra::TOPOLOGICAL){
                averageDistances[i]=i;
            }
            masses[i]/=numberTimesExist[i];
            accumMass+=masses[i];
            x.push_back(log(averageDistances[i]));
            y.push_back(log(accumMass));
//            std::cout<<averageDistances[i]<<" "<<accumMass<<'\n';
//        }
    }
//        std::cout<<"mass "<<mass<<" prev. "<<previousMass<<'\n';
//        if(mass>0){
////            if(Functions::abs((0.0)-(previousMass))<.1){
//
////                y.push_back(log((mass/pow(totalMass,2))));
//
//            std::cout<<"mass in correlation dimension "<<mass<<" "<<totalMass<<'\n';
////            }else{
////                double delta=.01;
////                if((log(mass)/log(previousMass))>1+delta||(log(mass)/log(previousMass))<1-delta){
////                    x.push_back(log(radius));
////                    y.push_back(log((mass/pow(totalMass,2))));
////                }else{
////                    if(x.size()==1){
////                        x[0]=(log(radius));
////                        y[0]=(log((mass/pow(totalMass,2))));
////                    }else{
////    //                    x[x.size()-1]=(log(radius));
////    //                    y[x.size()-1]=(log((mass/pow(totalMass,2))));
////                    }
////                }
////            }
////            previousMass=mass;
//        }
//        if((radius>=5&&type==InterfaceDijkstra::TOPOLOGICAL)||(radius>=1200&&type==InterfaceDijkstra::METRIC)){
//            stop=true;
//        }
//        if(type==InterfaceDijkstra::TOPOLOGICAL){
//            radius+=inc_radius;
//        }else if(type==InterfaceDijkstra::METRIC){
//            radius*=inc_radius;
//        }



//    }
    Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
//    Grafo::finishMeasuringAroundACircle(G);
    ;
    return LinearRegression::compute(x,y,false).slope;
}



//double FractalDimension::calculateBoxCounting(Graph *graph){
//
//    std::vector<Point2d> pointsFD;
//    double maxX=-INFINITY;
//    double maxY=-INFINITY;
//        double minX=INFINITY;
//            double minY=INFINITY;
//
//    for(long i=0;i<graph->nodes.size();i++){
//        if(graph->nodes[i].location.x>maxX){
//            maxX=graph->nodes[i].location.x;
//        }
//        if(graph->nodes[i].location.y>maxY){
//            maxY=graph->nodes[i].location.y;
//        }
//        if(graph->nodes[i].location.x<minX){
//            minX=graph->nodes[i].location.x;
//        }
//        if(graph->nodes[i].location.y<minY){
//            minY=graph->nodes[i].location.y;
//        }
//    }
//
//    double indexTemp=0;
//    //    double numberObjectsXInit=
//    double startingIndex=((maxX-minX)/500);
//    if(maxX-minX<500){
//        startingIndex=1;
//    }
//    double index=indexTemp*2+startingIndex;
//
//    //    std::cout<<"bounding box "<<minX<<" "<<maxX<<" .. "<<minY<<" "<<maxY<<'\n';
//
//
//    double EPSILON=.0000000001;
//    double gridSizeX=((maxX-minX)/index)+EPSILON;
//    double numberObjectsY=((maxY-minY)/gridSizeX);
//    double gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
//
//
//    bool STOP=false;
//    double numClustersPrev=0;
//    while((gridSizeX>100||indexTemp<4)&&!STOP){
//        double numberClustersOccupied=0;
//        gridSizeX=((maxX-minX)/index)+EPSILON;
//        numberObjectsY=((maxY-minY)/gridSizeX);
//        gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
//
//        long numCol=floor((maxX-minX)/gridSizeX)+1;
//        long numRow=floor((maxY-minY)/gridSizeY)+1;
//
//
//        SparseMatrix matrix;
////        long numCol=floor((maxX-minX)/gridSizeX);
////        long numRow=floor((maxY-minY)/gridSizeY);
//        matrix.init(numCol, numRow);
//
//        for(long i=0;i<graph->nodes.size();i++){
//            long currentCol=floor((graph->nodes[i].location.x-minX)/gridSizeX);
//            long currentRow=floor((graph->nodes[i].location.y-minY)/gridSizeY);
//            if(matrix.get(currentCol, currentRow)==-1){
//                numberClustersOccupied++;
//                matrix.set(1, currentCol, currentRow);
//            }else{
//
//            }
//        }
//
//
//        pointsFD.push_back(Point2d(log(1/gridSizeX),log(numberClustersOccupied)));
//
//
//
//        if(numClustersPrev==numberClustersOccupied){
//            STOP=true;
//        }else{
//            numClustersPrev=numberClustersOccupied;
//        }
//
//        indexTemp=indexTemp+1;
//
//        index=indexTemp*2+startingIndex;
//    }
//
//
//
//
//    LinearRegression fd_lr;
//    auto fd_lr=LinearRegression::compute(pointsFD,false);
//
//    return fd_lr.slope;
//}



//double FractalDimension::calculateBoxCounting(std::vector<Point2d> &points){
//
//    std::vector<Point2d> pointsFD;
//    double maxX=-INFINITY;
//    double maxY=-INFINITY;
//    double minX=INFINITY;
//    double minY=INFINITY;
//
//    for(long i=0;i<points.size();i++){
//        if(points[i].x>maxX){
//            maxX=points[i].x;
//        }
//        if(points[i].y>maxY){
//            maxY=points[i].y;
//        }
//        if(points[i].x<minX){
//            minX=points[i].x;
//        }
//        if(points[i].y<minY){
//            minY=points[i].y;
//        }
//    }
//
//    double indexTemp=0;
//    //    double numberObjectsXInit=
//    double startingIndex=((maxX-minX)/500);
//    if(maxX-minX<500){
//        startingIndex=1;
//    }
//    double index=indexTemp*2+startingIndex;
//
//    //    std::cout<<"bounding box "<<minX<<" "<<maxX<<" .. "<<minY<<" "<<maxY<<'\n';
//
//
//    double EPSILON=.0000000001;
//    double gridSizeX=((maxX-minX)/index)+EPSILON;
//    double numberObjectsY=((maxY-minY)/gridSizeX);
//    double gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
//
//
//    bool STOP=false;
//    double numClustersPrev=0;
//    while((gridSizeX>100||indexTemp<4)&&!STOP){
//        double numberClustersOccupied=0;
//        gridSizeX=((maxX-minX)/index)+EPSILON;
//        numberObjectsY=((maxY-minY)/gridSizeX);
//        gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
//
////        long numCol=floor((maxX-minX)/gridSizeX)+1;
////        long numRow=floor((maxY-minY)/gridSizeY)+1;
//
//        //        std::cout<<"matrix init "<<numCol<<" "<<numRow<<'\n';
//
//        SparseMatrix matrix;
//
//
////        matrix.init(numCol, numRow);
//
//        for(long i=0;i<points.size();i++){
//            long currentCol=floor((points[i].x-minX)/gridSizeX);
//            long currentRow=floor((points[i].y-minY)/gridSizeY);
//            //            std::cout<<"values currentcol etc "<<currentCol<<","<<currentRow<<" = "<<matrix.get(currentCol, currentRow)<<'\n';
//            if(matrix.getValue(currentCol, currentRow)!=1.0){
//                numberClustersOccupied++;
//                matrix.setValue(1.0, currentCol, currentRow);
//                //                std::cout<<"changing value "<<numberClustersOccupied;
//            }else{
//
//            }
//        }
//
//        //        double coordinates[2];
//
//        pointsFD.push_back(Point2d(log(1/gridSizeX),log(numberClustersOccupied)));
//        if(numClustersPrev==numberClustersOccupied){
//            STOP=true;
//        }else{
//            numClustersPrev=numberClustersOccupied;
//        }
//        //        pointsFD.push_back(Point2d(log(1/gridSizeX),log(numberClustersOccupied)));
//
//
//
//
//
//        indexTemp=indexTemp+1;
//
//        index=indexTemp*2+startingIndex;
//    }
//
//
//
//
////    LinearRegression fd_lr;
//    auto fd_lr=LinearRegression::compute(pointsFD,false);
//
//    return fd_lr.slope;
//}


std::vector<std::vector<double> >  FractalDimension::calculateBoxCounting_getPoints(std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint){
    //    double widthPoint=20;
    std::vector<std::vector<double> > pointsFD;
    std::vector<double> xs_result;
    std::vector<double> ys_result;
    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

    for(long i=0;i<xs.size();i++){
        if(xs[i]>maxX){
            maxX=xs[i];
        }
        if(ys[i]>maxY){
            maxY=ys[i];
        }
        if(xs[i]<minX){
            minX=xs[i];
        }
        if(ys[i]<minY){
            minY=ys[i];
        }
    }

//    double indexTemp=0;
    //    double numberObjectsXInit=
//    double startingIndex=((maxX-minX)/max);
//    if(maxX-minX<max){
//        startingIndex=1;
//    }
    double index=0;

    //    std::cout<<"bounding box "<<minX<<" "<<maxX<<" .. "<<minY<<" "<<maxY<<'\n';


    double EPSILON=0;
   double gridSizeX;
   double numberObjectsY;
   double gridSizeY;
   std::vector<double> randomRunsX;
   std::vector<double> randomRunsY;
   double minGridSize=INFINITY;
   for(long i=0;i<gridSizes.size();i++){
    if(gridSizes[i]<minGridSize){
        minGridSize=gridSizes[i];
    }
   }

     double maxRuns=5.0;
        for (long run=0;run<maxRuns;run++){
            double numberClustersOccupied=0;
            gridSizeX=minGridSize;
            numberObjectsY=((maxY-minY)/gridSizeX);
            gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
            double randomX=Functions::runiform(-gridSizeX, gridSizeX);
            double randomY=Functions::runiform(-gridSizeY, gridSizeY);
            randomRunsX.push_back(randomX);
            randomRunsY.push_back(randomY);
        }

    bool STOP=false;
    double numClustersPrev=0;
    while(index<gridSizes.size()&&!STOP){
        double numberClustersOccupied=0;
        gridSizeX=gridSizes[index];
        numberObjectsY=((maxY-minY)/gridSizeX);
        gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;

        //        long numCol=floor((maxX-minX)/gridSizeX)+1;
        //        long numRow=floor((maxY-minY)/gridSizeY)+1;

        //        std::cout<<"matrix init "<<numCol<<" "<<numRow<<'\n';

        // double maxRuns=5.0;
        for (long run=0;run<maxRuns;run++){

            double randomX=randomRunsX[run];
            double randomY=randomRunsY[run];

            if(maxRuns==1){
                randomX=0;
                randomY=0;
            }

            SparseMatrix matrix;
            //            numberClustersOccupied=0;

            //            matrix.init(numCol, numRow);

            for(long i=0;i<xs.size();i++){
                               // long currentCol=floor((xs[i]-minX+randomX)/gridSizeX);
                               // long currentRow=floor((ys[i]-minY+randomY)/gridSizeY);

                               // if(matrix.getValue(currentCol, currentRow)!=1){

                               //     matrix.increaseBy(currentCol, currentRow,1);

                               //     numberClustersOccupied++;

                               // }
                    long leftCol=floor((xs[i]-minX-widthPoint+randomX)/gridSizeX);
                    long rightCol=floor((xs[i]-minX+widthPoint+randomX)/gridSizeX);
                    long upRow=floor((ys[i]-minY+widthPoint+randomY)/gridSizeY);
                    long downRow=floor((ys[i]-minY-widthPoint+randomY)/gridSizeY);


                    for(long currentCol=leftCol;currentCol<=rightCol;currentCol++){
                        for(long currentRow=downRow;currentRow<=upRow;currentRow++){

                                double x0=currentCol*gridSizeX+minX;
                                double x1=(currentCol+1)*gridSizeX+minX;
                                double y0=currentRow*gridSizeY+minY;
                                double y1=(currentRow+1)*gridSizeY+minY;

                                double areaIntersection;
                                if(leftCol!=rightCol||upRow!=downRow){
                                    areaIntersection=Functions::area_intersectionCircleWithRectangle(x0,y0,x1,y1,xs[i],ys[i],widthPoint);
                                }else{
                                    areaIntersection=M_PI*(widthPoint)*(widthPoint);
                                }
                                if(matrix.getValue(currentCol, currentRow)<=0.0){

                                    matrix.increaseBy(currentCol, currentRow,areaIntersection);


                                    if(areaIntersection>0.0){
                                        numberClustersOccupied++;
                                    }

                                }else{
                                    matrix.increaseBy(currentCol, currentRow,areaIntersection);
                                }

                        }
                    }

            }
        }
        numberClustersOccupied/=maxRuns;

        //        double coordinates[2];
        xs_result.push_back(gridSizeX);
        //        if(ys_result.size()>0){
        //            ys_result.push_back(numberClustersOccupied+ys_result[ys_result.size()-1]);
        //        }else{
        ys_result.push_back(numberClustersOccupied);
        //        }
        if(numClustersPrev==numberClustersOccupied){
            // STOP=true;
        }else{
            numClustersPrev=numberClustersOccupied;
        }
        //        pointsFD.push_back(Point2d(log(1/gridSizeX),log(numberClustersOccupied)));




        index++;
//        indexTemp=indexTemp+1;
//
//        index=indexTemp*indexTemp+startingIndex;
    }
    pointsFD.push_back(xs_result);
    pointsFD.push_back(ys_result);



    //    LinearRegression fd_lr;
    //    auto fd_lr=LinearRegression::compute(pointsFD,false);

    return pointsFD;
}




double  FractalDimension::calculateBoxCounting(std::vector<double> &xs,std::vector<double> &ys,std::vector<double> gridSizes,double widthPoint){
    std::vector<std::vector<double> > points=calculateBoxCounting_getPoints(xs,ys, gridSizes, widthPoint);
    std::vector<double> xs_result=points[0];
    std::vector<double> ys_result=points[1];
    auto fd_lr=LinearRegression::compute(xs_result,ys_result,true);

    return -fd_lr.slope;
}











std::vector<std::vector<double> >  FractalDimension::generateSetOfPointsInvertedBoxCounting(double gamma,double maxX,double minX,double maxY,double minY,double max,double min,bool regular,bool random){
    //    double widthPoint=20;
    std::vector<std::vector<double> > pointsFD;
    std::vector<double> xs_result;
    std::vector<double> ys_result;

    std::queue<double> maxXs,minXs,maxYs,minYs,indexes,gammas,prev_gammas;

    double o_maxX,o_maxY,o_minX,o_minY;
    o_maxX=maxX;
    o_maxY=maxY;
    o_minX=minX;
    o_minY=minY;

//    double areaOriginal

    maxXs.push(maxX);
    minXs.push(minX);
    maxYs.push(maxY);
    minYs.push(minY);
    gammas.push(gamma);
    prev_gammas.push(gamma);
//    ps.push(1.0);
//    maxs.push((max));

    double indexTemp=0;
    indexes.push(indexTemp);
    double startingIndex=((maxX-minX)/max);
    if(maxX-minX<max){
        startingIndex=1;
    }
    double EPSILON=.0000000001;
            double gridSizeX=((maxX-minX)/startingIndex)+EPSILON;
            double numberObjectsY=((maxY-minY)/gridSizeX);
            double gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
     numberObjectsY=((maxY-minY)/gridSizeY);
    double numberObjectsX=((maxX-minX)/gridSizeX);
    double previousBoxes=numberObjectsY*numberObjectsX;
    double prev_gamma;
    while (maxXs.size()>0){

//        max=maxs.();
        maxX=maxXs.front();
        maxY=maxYs.front();
        minX=minXs.front();
        minY=minYs.front();
        indexTemp=indexes.front();
        gamma=gammas.front();
        prev_gamma=prev_gammas.front();
//        double p=ps.front();

//        maxs.pop();
        maxXs.pop();
        maxYs.pop();
        minXs.pop();
        minYs.pop();
        indexes.pop();
        gammas.pop();
        prev_gammas.pop();
//        ps.pop();
        double initialIndex=indexTemp;


    //    double numberObjectsXInit=

    double index=(indexTemp)+startingIndex;

    //    std::cout<<"bounding box "<<minX<<" "<<maxX<<" .. "<<minY<<" "<<maxY<<'\n';
//        if(previousBoxes>1){
//            index=2;
//        }


    double gridSizeX=((maxX-minX)/index)+EPSILON;

    double numberObjectsY=((maxY-minY)/gridSizeX);
    double gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;


//    bool STOP=false;
//    double numClustersPrev=0;
//    while((gridSizeX>min)){
//        double numberClustersOccupied=0;
//        gridSizeX=((maxX-minX)/index)+EPSILON;
//        numberObjectsY=((maxY-minY)/gridSizeX);
//        gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
        numberObjectsY=((maxY-minY)/gridSizeY);
//        double numberObjectsX=((maxX-minX)/gridSizeX);

        double area=(o_maxX-o_minX)*(o_maxY-o_minY);
        double L=pow(area,.5);
        double numberBoxesOccupied=(pow((L/gridSizeX),gamma));
        double numberBoxesTotal=(pow((L/(gridSizeX*3)),prev_gamma)*9);
        double probability=numberBoxesOccupied/numberBoxesTotal;
        previousBoxes=0;


//        std::cout<<indexTemp<<" "<<index<<" "<<area<<" "<<gridSizeX<<" "<<numberBoxesOccupied<<" "<<numberObjectsX*numberObjectsY<<" "<<numberBoxesTotal<<'\n';

//        double probability=numberBoxesOccupied/numberBoxesTotal;

//        indexTemp=indexTemp+1;
//        index=(indexTemp)+startingIndex;

        if(((maxX-minX)/(index))+EPSILON<min){
//            SparseMatrix matrix;
//            long numCol=floor((maxX-minX)/gridSizeX)+1;
//            long numRow=floor((maxY-minY)/gridSizeY)+1;
//            matrix.init(numCol, numRow);

            for(long i=0;i<9;i++){
                if(Functions::runiform(0, 1)<=(probability)){
//                    std::cout<<p<<'\n';
                    double currentCol=i/3;
                    double currentRow=i%3;
//                    if(matrix.get(currentCol, currentRow)==-1){
//                        matrix.set(1, currentCol, currentRow);
                        double currentMinX=minX+currentCol*gridSizeX;
                        double currentMinY=minY+currentRow*gridSizeY;
                        double randomX=Functions::runiform(-gridSizeX, gridSizeX)/4;
                        double randomY=Functions::runiform(-gridSizeY, gridSizeY)/4;
                        randomX=Functions::rnorm(0, gridSizeX/10);
                        randomY=Functions::rnorm(0, gridSizeY/10);
                    if(!random){
                    randomX=0;
                    randomY=0;
                    }
                        xs_result.push_back(currentMinX+randomX);
                        ys_result.push_back(currentMinY+randomY);
//                    }
                }

            }
        }else{
//            SparseMatrix matrix;
//            long numCol=floor((maxX-minX)/gridSizeX)+1;
//            long numRow=floor((maxY-minY)/gridSizeY)+1;
//            matrix.init(numCol, numRow);

            for(long i=0;i<9;i++){

//                double p2=0.0;
                double currentCol=i%3;
                double currentRow=i/3;
                if(Functions::runiform(0, 1)<=probability||initialIndex<2){
                    previousBoxes++;
//                    p2=1.0;
//                }
//                double p2=(Functions::runiform(0, 1)+probability)/2;
//                ps.push((p+p2)/2.0);

//                    if(matrix.get(currentCol, currentRow)==-1){
//                         matrix.set(1, currentCol, currentRow);
                    double randomX=Functions::runiform(-gridSizeX, gridSizeX)/4;
                    double randomY=Functions::runiform(-gridSizeY, gridSizeY)/4;
                    randomX=Functions::rnorm(0, gridSizeX/10);
                    randomY=Functions::rnorm(0, gridSizeY/10);
                    if(!random){
                        randomX=0;
                        randomY=0;
                    }

    //                    double index_temp=index+1;
                        startingIndex=1;
                        double gridSizeX_temp=((maxX-minX)/3)+EPSILON;
                        double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                        double gridSizeY_temp=((maxY-minY)/numberObjectsY_temp)+EPSILON;
                    double currentMinX=minX+currentCol*gridSizeX_temp+randomX;
                    double currentMinY=minY+currentRow*gridSizeY_temp+randomY;
                    minXs.push(currentMinX);
                    minYs.push(currentMinY);
                        maxXs.push(currentMinX+gridSizeX_temp);
                        maxYs.push(currentMinY+gridSizeY_temp);
    //                    maxs.push((initialIndex+1)+startingIndex);
                        indexes.push(initialIndex+1);
                    prev_gammas.push(gamma);
                    double newGamma=gamma+min/gridSizeX/30;
//                    newGamma=gamma;
                    if(currentCol==1&&currentRow==1){
//                        newGamma+=Functions::abs(Functions::rnorm(0, .1)*gamma/2.0);
                    }else{

                    }
                    if(!regular){
                    gamma=Functions::max(1.0,Functions::min(2,newGamma));
                    }

                    gammas.push(gamma);
//                    }
                }else if(!regular){
                    prev_gammas.push(gamma);
                    double newGamma=gamma-min/gridSizeX*5;
                    if(currentCol==1&&currentRow==1){

                    }else{
//                        newGamma+=Functions::abs(Functions::rnorm(0, .001)*gamma/2.0);
                    }
                    if(newGamma>1){
                        previousBoxes++;
                        //                    p2=1.0;
                        //                }
                        //                double p2=(Functions::runiform(0, 1)+probability)/2;
                        //                ps.push((p+p2)/2.0);
//                        double currentCol=i/3;
//                        double currentRow=i%3;
                        //                    if(matrix.get(currentCol, currentRow)==-1){
                        //                         matrix.set(1, currentCol, currentRow);
                        double randomX=Functions::runiform(-gridSizeX, gridSizeX)/4;
                        double randomY=Functions::runiform(-gridSizeY, gridSizeY)/4;
                        randomX=Functions::rnorm(0, gridSizeX/10);
                        randomY=Functions::rnorm(0, gridSizeY/10);
                        if(!random){
                            randomX=0;
                            randomY=0;
                        }
                        double currentMinX=minX+currentCol*gridSizeX+randomX;
                        double currentMinY=minY+currentRow*gridSizeY+randomY;
                        minXs.push(currentMinX);
                        minYs.push(currentMinY);
                        //                    double index_temp=index+1;
                        startingIndex=1;
                        double gridSizeX_temp=((maxX-minX)/3)+EPSILON;
                        double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                        double gridSizeY_temp=((maxY-minY)/numberObjectsY_temp)+EPSILON;

                        maxXs.push(currentMinX+gridSizeX_temp);
                        maxYs.push(currentMinY+gridSizeY_temp);
                        //                    maxs.push((initialIndex+1)+startingIndex);
                        indexes.push(initialIndex);
                        gammas.push(newGamma);
                    }
                }

            }

        }






    }
//    }
        pointsFD.push_back(xs_result);
        pointsFD.push_back(ys_result);

    //    LinearRegression fd_lr;
    //    auto fd_lr=LinearRegression::compute(pointsFD,false);

    return pointsFD;
}


































InterfaceMultiFractalAnalysis FractalDimension::MultifractalAnalysis_boxCounting(Grafo* G,std::vector<double> &qs,std::vector<double> & radii){
    std::cout<<'\n';
    std::cout<<"Calculating fractal dimension "<<'\n';
    double massNode=1;
    double M=G->nodes.size()*massNode;
    double L=sqrt(M);



    std::vector<std::vector<SparseMatrix> > multipleGrids;

//    SparseMatrix level4;
    int GEOMETRIC=0;
    int ARITHMETIC=1;
    int type=GEOMETRIC;

//    long lowerCutoff=0;
//    long upperCutoff=0;
    double maxDepth=radii.size();
    double probabilityToDecideIfCompute=1.0;
    long numberCalculations=1;
    if(type==ARITHMETIC){
        numberCalculations=1;
    }




double accumWeight=0;
    double longestDistance=0;
    for(long i=0;i<G->links.size();i++){
        accumWeight+=G->links[i]->weight;
        if(G->links[i]->weight>longestDistance){
            longestDistance=G->links[i]->weight;
        }
    }
   double averWeight=accumWeight/(double)G->links.size();

    // auto detectGridSize=FractalDimension::detectStartingGridSize(G,maxDepth);
    std::pair<double,std::pair<long,long> > detectGridSize=std::pair<double,std::pair<long,long> > (averWeight,std::pair<long,long> (0,0));



//    detectGridSize.second.first+=1;
//    detectGridSize.second.second+=1;
    // double gridSize=detectGridSize.first;
    std::cout<<"cutoffs "<<detectGridSize.second.first<<" "<<maxDepth-detectGridSize.second.second<<'\n';

//    maxDepth=maxDepth-detectGridSize.second.second;
//    detectGridSize.second.second=0;

    multipleGrids.resize(numberCalculations);
    for(long i=0;i<numberCalculations;i++){
        multipleGrids[i].resize(maxDepth,SparseMatrix());
    }

    std::vector<double> Dqs;
    Dqs.resize(qs.size(),0.0);

    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

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


    std::vector<double> x;
    std::vector<double> y;
//    LinearRegression linearRegression;








    std::vector<double> averageDistances;
    std::vector<double> averageDistancesTemp;
    std::vector<double> numObjects;
    std::vector<std::vector<double> > masses;
    std::vector<double> massesDeformedByQ;
    std::vector<double> massesTemp;
    std::vector<double> numberTimesExist;
    // std::vector<double> radii;
    std::vector<double> topologicalRadii;
    averageDistances.resize(maxDepth+1,0);
    averageDistancesTemp.resize(maxDepth+1,0);
    numObjects.resize(maxDepth+1,0);

    massesDeformedByQ.resize(maxDepth+1,0);
    massesTemp.resize(maxDepth+1,0);

    std::vector<double> alphas;
    alphas.resize(G->nodes.size());
    std::vector<double> gammas;
    gammas.resize(G->nodes.size());






//    double maxDistance=(averWeight)*maxDepth;
//    double coef=M_PI/4.0;
//    coef=1.0;

//    lowerCutoff=detectGridSize.second.first;
//    upperCutoff=detectGridSize.second.second;
    for(long g=0;g<multipleGrids.size();g++){
//        for(long g=0;g<multipleGrids.size();g++){
            // multipleGrids[g].clear();
            // multipleGrids[g].resize(maxDepth,SparseMatrix());
//        }

    //     for(long i=0;i<G->nodes.size();i++){
    // //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
    //             multipleGrids[g][0].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSize)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSize)),massNode);
    // //        }
    //     }

        //     std::cout<<"level 0 calculated"<<'\n';double widthPoint=1.0;

        double widthPoint=1.0;
        long numberClustersOccupied=0;

            for(long j=0;j<maxDepth;j++){
                double gridSizeTemp=radii[j];
              Point2d startPoint=Point2d(Functions::runiform(0,gridSizeTemp),Functions::runiform(0,gridSizeTemp));
              if(g==0){
                startPoint=Point2d(0,0);
              }
              std::cout<<"Calculating levels, grid size = "<<gridSizeTemp<<'\n';


//                 if(type==GEOMETRIC){
//                     gridSizeTemp=pow(3.0,j)*gridSize;
//                 }else if(type==ARITHMETIC){
// //                    for(long j=0;j<maxDepth;j++){
// //                        double gridSizeTemp;

//                         gridSizeTemp=gridSize*((j*2.0)+1.0);
//                     }

                double gridSizeX=gridSizeTemp;
                double numberObjectsY=((maxY-minY)/gridSizeX);
                double gridSizeY=((maxY-minY)/numberObjectsY);
                for(long i=0;i<G->nodes.size();i++){
                    //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
                    //                    multipleGrids[g][j].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSizeTemp)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSizeTemp)),massNode);




                    // long leftCol=floor((G->nodes[i]->location.x-minX-widthPoint+startPoint.x)/gridSizeX);
                    // long rightCol=floor((G->nodes[i]->location.x-minX+widthPoint+startPoint.x)/gridSizeX);
                    // long upRow=floor((G->nodes[i]->location.y-minY+widthPoint+startPoint.y)/gridSizeY);
                    // long downRow=floor((G->nodes[i]->location.y-minY-widthPoint+startPoint.y)/gridSizeY);
                    // for(long currentCol=leftCol;currentCol<=rightCol;currentCol++){
                    //     for(long currentRow=downRow;currentRow<=upRow;currentRow++){
                    //         if(Functions::getDistance(Point2d((double)(leftCol+rightCol)/2.0,(double)(upRow+downRow)/2.0), Point2d(currentCol,currentRow))<=(double)(leftCol+rightCol)/2.0){
                    //             if(multipleGrids[g][j].getValue(currentCol, currentRow)<1){
                    //                 //                numberClustersOccupied++;
                    //                 multipleGrids[g][j].increase(currentCol, currentRow);

                    //                 //                        numberClustersOccupied+=(1+(rightCol-leftCol))*(1+(upRow-downRow));
                    //                 numberClustersOccupied++;
                    //                 //                std::cout<<"changing value "<<numberClustersOccupied;
                    //             }else{
                    //                 multipleGrids[g][j].increase(currentCol, currentRow);
                    //             }
                    //         }
                    //     }
                    // }



                    long leftCol=floor((G->nodes[i]->location.x-minX-widthPoint+startPoint.x)/gridSizeX);
                long rightCol=floor((G->nodes[i]->location.x-minX+widthPoint+startPoint.x)/gridSizeX);
                long upRow=floor((G->nodes[i]->location.y-minY+widthPoint+startPoint.y)/gridSizeY);
                long downRow=floor((G->nodes[i]->location.y-minY-widthPoint+startPoint.y)/gridSizeY);
                for(long currentCol=leftCol;currentCol<=rightCol;currentCol++){
                    for(long currentRow=downRow;currentRow<=upRow;currentRow++){
                        // if(Functions::getDistance(Point2d((double)(leftCol+rightCol)/2.0,(double)(upRow+downRow)/2.0), Point2d(currentCol,currentRow))<=(double)(leftCol+rightCol)/2.0){
                            double x0=currentCol*gridSizeX+minX;
                            double x1=(currentCol+1)*gridSizeX+minX;
                            double y0=currentRow*gridSizeY+minY;
                            double y1=(currentRow+1)*gridSizeY+minY;

                            double areaIntersection;
                            if(leftCol!=rightCol||upRow!=downRow){
                                areaIntersection=Functions::area_intersectionCircleWithRectangle(x0,y0,x1,y1,G->nodes[i]->location.x,G->nodes[i]->location.y,widthPoint);
                            }else{
                                areaIntersection=M_PI*(widthPoint)*(widthPoint);
                            }
                            if(multipleGrids[g][j].getValue(currentCol, currentRow)<=0.0){
                                //                numberClustersOccupied++;
                                multipleGrids[g][j].increaseBy(currentCol, currentRow,areaIntersection);

                                //                        numberClustersOccupied+=(1+(rightCol-leftCol))*(1+(upRow-downRow));
                                if(areaIntersection>0.0){
                                    numberClustersOccupied++;
                                }
                                //                std::cout<<"changing value "<<numberClustersOccupied;
                            }else{
                                multipleGrids[g][j].increaseBy(currentCol, currentRow,areaIntersection);
                            }
                        // }
                    }
                }



                    //        }
                }
                // for(auto& it:multipleGrids[g][0].cells){
                //     Point2d current=it.first;
                //     for(long j=0;j<3;j++){
                //         for(long h=0;h<3;h++){

                //             multipleGrids[g][i+1].increaseBy((current.x),(current.y),multipleGrids[g][i].getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
                //         }
                //     }
                // }
                std::cout<<"level "<<j<<"/"<<maxDepth<<" calculated"<<'\n';
            }
//        }else if(type==ARITHMETIC){
//            for(long j=0;j<maxDepth;j++){
//                double gridSizeTemp;
//
//                gridSizeTemp=gridSize*((j*2.0)+1.0);
//                for(long i=0;i<G->nodes.size();i++){
//                    //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
//                    multipleGrids[g][j].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSizeTemp)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSizeTemp)),massNode);
//                    //        }
//                }
//                // for(auto& it:multipleGrids[g][0].cells){
//                //     Point2d current=it.first;
//                //     for(long j=0;j<3;j++){
//                //         for(long h=0;h<3;h++){
//
//                //             multipleGrids[g][i+1].increaseBy((current.x),(current.y),multipleGrids[g][i].getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
//                //         }
//                //     }
//                // }
//                std::cout<<"level "<<j<<"/"<<maxDepth<<" calculated"<<'\n';
//            }
//        }
    }
//    std::cout<<"level 2/"<< maxDepth<<" calculated"<<'\n';
//    double gridSizeTemp=3.0;
//    for(auto& it:level1.cells){
//        Point2d current=it.first;
//        for(long j=0;j<3;j++){
//            for(long h=0;h<3;h++){
//                level2.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level1.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
//            }
//        }
//    }
//    std::cout<<"level 3/"<< maxDepth<<" calculated"<<'\n';
//    gridSizeTemp=9.0;
//    for(auto& it:level2.cells){
//        Point2d current=it.first;
//        for(long j=0;j<3;j++){
//            for(long h=0;h<3;h++){
//                level3.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level2.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
//            }
//        }
//    }
//    std::cout<<"level 4/"<< maxDepth<<" calculated"<<'\n';
//    gridSizeTemp=3.0;
//    for(long j=0;j<3;j++){
//        for(long h=0;h<3;h++){
//            for(auto& it:level3.cells){
//                Point2d current=it.first;
//
//                level4.increaseBy(static_cast<long>(round((current.x)/gridSizeTemp)*gridSizeTemp-1+j),static_cast<long>(round((current.y)/gridSizeTemp)*gridSizeTemp-1+h),it.second.value);
//            }
//        }
//    }

    masses.resize(qs.size(),std::vector<double>());















    // radii.clear();

    // for(double i=0.0;i<maxDepth;i++){
    //     if(type==GEOMETRIC){
    //         radii.push_back(gridSize*pow(3.0,i));
    //     }
    //     if(type==ARITHMETIC){
    //         radii.push_back(gridSize*((i*2.0)+1.0));
    //         topologicalRadii.push_back(i);
    //     }

    //     std::cout<<"radii "<<radii[i]<<'\n';
    // }




    x.clear();
    y.clear();




    double sqrt2=sqrt(2);

    double numberObjectsCounted=0;
    // long j=0;
    std::vector<double> xs;
    std::vector<double> ys;
    xs.reserve(radii.size());
    ys.reserve(radii.size());
    std::vector<double> numberNonZeroBoxes;
    numberNonZeroBoxes.resize(radii.size(),0);


   //// j deberia tener el tamano de qs!!!!
    for(long j=0;j<qs.size();j++){
        // double qs_current=qs[j];
        numberObjectsCounted=0;

        // masses[j].clear();

        // if(Functions::runiform(0, 1)<probabilityToDecideIfCompute){
        //     numberObjectsCounted++;
        //     Point2d current=it.first;


             masses[j].resize(maxDepth,0);
        //     if(type==ARITHMETIC){
        //         std::vector<bool> nonEmpty;
        //         nonEmpty.resize(radii.size(),false);
        //         for(long i=-maxDepth;i<=maxDepth;i++){
        //             for(long g=-maxDepth;g<=maxDepth;g++){
        //                 for(long h=topologicalRadii.size()-1;h>=0;h--){
        //                     double distance=Functions::getDistance(current,Point2d(current.x+i,current.y+g));
        //                     if(distance<=topologicalRadii[h]*sqrt2){
        //                         if(multipleGrids[0][0].getValue(current.x+i,current.y+g)>0){
        //                             nonEmpty[h]=true;
        //                             masses[j][h]+=pow(multipleGrids[0][0].getValue(current.x+i,current.y+g),qs[j]);
        //                         }
        //                     }
        //                     else{
        //                         break;
        //                     }
        //                 }

        //             }
        //         }
        //         for(long h=0;h<nonEmpty.size();h++){
        //             numberNonZeroBoxes[h]++;
        //         }
        //     }else{
                for(long g=0;g<numberCalculations;g++){

                    for(long i=0;i<maxDepth;i++){
                        for(auto& it:multipleGrids[g][i].cells){

                            Point2d current=it.first;
                            if(multipleGrids[g][i].getValue(current.x,current.y)>0){
                            numberNonZeroBoxes[i]+=1.0/(double)(qs.size());
                            masses[j][i]+=pow(multipleGrids[g][i].getValue(current.x,current.y),qs[j])/(double)(numberCalculations);
                            }
                        }
                    }
            // }




            // auto lr=LinearRegression::computeBestFit(radii, masses[j],true);
            // if(lr.first.slope<1||lr.first.slope>2||lr.first.adjusted_R2<0.98){
            //     masses[j].clear();
            //     numberObjectsCounted--;
            // }
                }

        // j++;
        }
//    }





    // std::vector<std::vector<double> > Dqs_epsilon;
    // std::vector<double> taus;
    // taus.resize(qs.size());
    // for(long i=0;i<qs.size();i++){

    //     std::vector<double> Dqs_epsilon_Temp;
    //     Dqs_epsilon_Temp.resize(radii.size());
    //     Dqs_epsilon.push_back(Dqs_epsilon_Temp);
    // }
    for(long i=0;i<masses.size();i++){
            for(long h=0;h<radii.size()-0;h++){
                if(type==ARITHMETIC){
//                    masses[i][h]/=numberNonZeroBoxes[h];
                }else if (type==GEOMETRIC){
//                    masses[i][h]/=numberNonZeroBoxes[h];
                }
        //         Dqs_epsilon[j][h]+=pow(masses[i][h]/numberObjectsCounted,qs[j]);

            }
        }
    for(long j=0;j<qs.size();j++){

        auto lr=LinearRegression::compute(radii,masses[j],detectGridSize.second.first,radii.size()-detectGridSize.second.second,true);
        double d_support=2.0;
        Dqs[j]=((lr.slope))/(qs[j]-1.0);

    }



//     double q=2.0;

//     double M_temp=1.0;
//     double L_temp=1.0;
//     double maxMass=0.0;
//     for(long i=0;i<masses.size();i++){



//         if(masses[i].size()>0){
//             //                                std::cout<<"gamma "<<gammas[i]<<'\n';

//             for(long h=0;h<radii.size()-0;h++){
//                 //                if(masses[i][h]<1){
//                 //                    std::cout<<""<<'\n';
//                 //                }
//                 massesDeformedByQ[h]+=pow(masses[i][h]/M_temp,q-1)/numberObjectsCounted;
//                 //                        std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
//                 if(masses[i][h]>maxMass){

//                     maxMass=masses[i][h];
//                 }
//             }
//         }

//     }



// //    for(long i=0;i<radii.size()-0;i++){
// //
// //
// //
// //
// //        x.push_back(log(massesDeformedByQ[i])/(q-1));
// //        y.push_back(log(radii[i]*coefRadius/L_temp));
// //        if(i>=detectGridSize.second.first&&i<=maxDepth-detectGridSize.second.second){
// //            std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(log(radii[i]*coefRadius/L_temp))<<",mass="<<exp(log(massesDeformedByQ[i])/(q-1))<<"))"<<'\n';
// //        }
// //
// //    }
// //    auto lr=LinearRegression::compute(y,x,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
// //    double D2=lr.slope;
// //    std::cout<<"D2="<<D2<<'\n';

//     for(long i=0;i<radii.size()-0;i++){




//         x.push_back(log(massesDeformedByQ[i])/(q-1));
//         y.push_back(log(radii[i]/L_temp));
//         std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';

//     }
//     auto lr=LinearRegression::compute(y,x,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
//     double D2=lr.slope;
//     std::cout<<"D2="<<D2<<'\n';

//     lr=LinearRegression::compute(x,y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);


//     double slopeA=lr.slope;
//     double interceptA=lr.intercept;
//     long size=x.size();
//     x.clear();
//     y.clear();
//     for(long i=0;i<size;i++){
//         x.push_back(exp(log(massesDeformedByQ[i])/(q-1)*slopeA+interceptA));
//         y.push_back(radii[i]/L_temp);
//     }
//     lr=LinearRegression::compute(x,y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);


//     //    L=pow(M,1/1.7149);
//     //    M=maxMass;
//     L=lr.slope*(exp(log(M)*slopeA+interceptA))+lr.intercept;











// //    M=1;
// //    L=1;

//     std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
//     x.clear();
//     y.clear();
//     for(long j=0;j<qs.size();j++){
//         if(qs[j]!=1){


//             for(long i=0;i<masses.size();i++){


//                 if(masses[i].size()>0){

//                     for(long h=0;h<radii.size()-0;h++){
//                         massesDeformedByQ[h]+=pow(masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted;
//                         if(h==0){
// //                            std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
//                         }

//                     }
//                 }
//             }
// //            std::cout<<'\n';
//             for(long i=0;i<radii.size()-0;i++){


// //                if(radii[i]/L>0&&massesDeformedByQ[i]>0){
//                     x.push_back(log(radii[i]/L));
//                     y.push_back(log(massesDeformedByQ[i])/(qs[j]-1.0));
// //                }
// //                 std::cout<<qs[j]<<" "<<massesDeformedByQ[i]<<" "<<log(massesDeformedByQ[i])<<" "<<log(massesDeformedByQ[i])/(qs[j]-1.0)<<'\n';
//                  if(i>=detectGridSize.second.first&&i<maxDepth-detectGridSize.second.second){
//                     std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(log(massesDeformedByQ[i])/(qs[j]-1))<<"))"<<'\n';
//                  }
// //                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';


//             }
//             if(j==0){
// //                detectGridSize.second=LinearRegression::detectUpperAndLowerCutoff(x, y, false);
// //                detectGridSize.second.first+=1;
// //                detectGridSize.second.second+=1;
//             }
//             auto lr=LinearRegression::compute(x, y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
//             Dqs[j]=lr.slope;


//         }else{

//             for(long i=0;i<masses.size();i++){


//                 if(masses[i].size()>0){

//                     for(long h=0;h<radii.size()-0;h++){
//                         massesDeformedByQ[h]+=log(masses[i][h]/M)/numberObjectsCounted;

//                     }
//                 }
//             }

//             for(long i=0;i<radii.size()-0;i++){


// //                if(radii[i]/L>0){
//                     x.push_back(log(radii[i]/L));
//                     y.push_back((massesDeformedByQ[i]));
//                  if(i>=detectGridSize.second.first&&i<maxDepth-detectGridSize.second.second){
//                     std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(massesDeformedByQ[i])<<"))"<<'\n';
//                  }
// //                }

//             }
//             auto lr=LinearRegression::compute(x, y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
//             Dqs[j]=lr.slope;
//         }
//         std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
//         x.clear();
//         y.clear();

//     }

    InterfaceMultiFractalAnalysis ima;
    Dqs.swap(ima.Dqs);
    return ima;

}



InterfaceMultiFractalAnalysis FractalDimension::MultifractalAnalysis_slidingBox(Grafo* G,std::vector<double> &qs){
    std::cout<<'\n';
    std::cout<<"Calculating fractal dimension "<<'\n';
    double massNode=1;
    double M=G->nodes.size()*massNode;
    double L=sqrt(M);



    std::vector<std::vector<SparseMatrix> > multipleGrids;

    //    SparseMatrix level4;
    int GEOMETRIC=0;
    int ARITHMETIC=1;
    int type=ARITHMETIC;

    //    long lowerCutoff=0;
    //    long upperCutoff=0;
    double maxDepth=3;
    double probabilityToDecideIfCompute=1.0;
    long numberCalculations=1;
    if(type==ARITHMETIC){
        numberCalculations=1;
    }




    double accumWeight=0;
    double longestDistance=0;
    for(long i=0;i<G->links.size();i++){
        accumWeight+=G->links[i]->weight;
        if(G->links[i]->weight>longestDistance){
            longestDistance=G->links[i]->weight;
        }
    }
    double averWeight=accumWeight/(double)G->links.size();

    // auto detectGridSize=FractalDimension::detectStartingGridSize(G,maxDepth);
    std::pair<double,std::pair<long,long> > detectGridSize=std::pair<double,std::pair<long,long> > (averWeight*1.0,std::pair<long,long> (0,0));



    //    detectGridSize.second.first+=1;
    //    detectGridSize.second.second+=1;
    double gridSize=detectGridSize.first;
    std::cout<<"cutoffs "<<detectGridSize.second.first<<" "<<maxDepth-detectGridSize.second.second<<'\n';

    //    maxDepth=maxDepth-detectGridSize.second.second;
    //    detectGridSize.second.second=0;

    multipleGrids.resize(numberCalculations);
    for(long i=0;i<numberCalculations;i++){
        multipleGrids[i].resize(maxDepth,SparseMatrix());
    }

    std::vector<double> Dqs;
    Dqs.resize(qs.size(),0.0);

    double maxX=-INFINITY;
    double maxY=-INFINITY;
    double minX=INFINITY;
    double minY=INFINITY;

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


    std::vector<double> x;
    std::vector<double> y;
    //    LinearRegression linearRegression;








    std::vector<double> averageDistances;
    std::vector<double> averageDistancesTemp;
    std::vector<double> numObjects;
    std::vector<std::vector<double> > masses;
    std::vector<double> massesDeformedByQ;
    std::vector<double> massesTemp;
    std::vector<double> numberTimesExist;
    std::vector<double> radii;
    std::vector<double> topologicalRadii;
    averageDistances.resize(maxDepth+1,0);
    averageDistancesTemp.resize(maxDepth+1,0);
    numObjects.resize(maxDepth+1,0);

    massesDeformedByQ.resize(maxDepth+1,0);
    massesTemp.resize(maxDepth+1,0);

    std::vector<double> alphas;
    alphas.resize(G->nodes.size());
    std::vector<double> gammas;
    gammas.resize(G->nodes.size());






    //    double maxDistance=(averWeight)*maxDepth;
    //    double coef=M_PI/4.0;
    //    coef=1.0;

    //    lowerCutoff=detectGridSize.second.first;
    //    upperCutoff=detectGridSize.second.second;
    for(long g=0;g<multipleGrids.size();g++){
        //        for(long g=0;g<multipleGrids.size();g++){
        // multipleGrids[g].clear();
        // multipleGrids[g].resize(maxDepth,SparseMatrix());
        //        }
        Point2d startPoint=Point2d(Functions::runiform(0,gridSize),Functions::runiform(0,gridSize));
        if(g==0){
            startPoint=Point2d(0,0);
        }
        std::cout<<"Calculating levels, grid size = "<<gridSize<<'\n';
        //     for(long i=0;i<G->nodes.size();i++){
        // //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
        //             multipleGrids[g][0].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSize)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSize)),massNode);
        // //        }
        //     }

        //     std::cout<<"level 0 calculated"<<'\n';

        double widthPoint=1.0;


        long numberClustersOccupied=0;
        if(type==GEOMETRIC){
            for(long j=0;j<maxDepth;j++){
                double gridSizeTemp;


                double gridSizeX=gridSizeTemp;
                double numberObjectsY=((maxY-minY)/gridSizeX);
                double gridSizeY=((maxY-minY)/numberObjectsY);

                gridSizeTemp=pow(3.0,j)*gridSize;
                for(long i=0;i<G->nodes.size();i++){
                    //        if(Functions::runiform(0, 1)<=probabilityToDecideIfCompute){
//                    multipleGrids[g][j].increaseBy(static_cast<long>(round((G->nodes[i]->location.x-minX+startPoint.x)/gridSizeTemp)),static_cast<long>(round((G->nodes[i]->location.y-minY+startPoint.y)/gridSizeTemp)),massNode);




                    long leftCol=floor((G->nodes[i]->location.x-minX-widthPoint+startPoint.x)/gridSizeX);
                    long rightCol=floor((G->nodes[i]->location.x-minX+widthPoint+startPoint.x)/gridSizeX);
                    long upRow=floor((G->nodes[i]->location.y-minY+widthPoint+startPoint.y)/gridSizeY);
                    long downRow=floor((G->nodes[i]->location.y-minY-widthPoint+startPoint.y)/gridSizeY);
                    for(long currentCol=leftCol;currentCol<=rightCol;currentCol++){
                        for(long currentRow=downRow;currentRow<=upRow;currentRow++){
                            if(Functions::getDistance(Point2d((double)(leftCol+rightCol)/2.0,(double)(upRow+downRow)/2.0), Point2d(currentCol,currentRow))<=(double)(leftCol+rightCol)/2.0){
                                if(multipleGrids[g][j].getValue(currentCol, currentRow)<1){
                                    //                numberClustersOccupied++;
                                    multipleGrids[g][j].increase(currentCol, currentRow);

                                    //                        numberClustersOccupied+=(1+(rightCol-leftCol))*(1+(upRow-downRow));
                                    numberClustersOccupied++;
                                    //                std::cout<<"changing value "<<numberClustersOccupied;
                                }else{
                                    multipleGrids[g][j].increase(currentCol, currentRow);
                                }
                            }
                        }
                    }



                    //        }
                }
                // for(auto& it:multipleGrids[g][0].cells){
                //     Point2d current=it.first;
                //     for(long j=0;j<3;j++){
                //         for(long h=0;h<3;h++){

                //             multipleGrids[g][i+1].increaseBy((current.x),(current.y),multipleGrids[g][i].getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
                //         }
                //     }
                // }
                std::cout<<"level "<<j<<"/"<<maxDepth<<" calculated"<<'\n';
            }
        }
    }
    //    std::cout<<"level 2/"<< maxDepth<<" calculated"<<'\n';
    //    double gridSizeTemp=3.0;
    //    for(auto& it:level1.cells){
    //        Point2d current=it.first;
    //        for(long j=0;j<3;j++){
    //            for(long h=0;h<3;h++){
    //                level2.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level1.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
    //            }
    //        }
    //    }
    //    std::cout<<"level 3/"<< maxDepth<<" calculated"<<'\n';
    //    gridSizeTemp=9.0;
    //    for(auto& it:level2.cells){
    //        Point2d current=it.first;
    //        for(long j=0;j<3;j++){
    //            for(long h=0;h<3;h++){
    //                level3.increaseBy(static_cast<long>(current.x),static_cast<long>(current.y),level2.getValue(current.x+gridSizeTemp*(-1+j), current.y+gridSizeTemp*(-1+h)));
    //            }
    //        }
    //    }
    //    std::cout<<"level 4/"<< maxDepth<<" calculated"<<'\n';
    //    gridSizeTemp=3.0;
    //    for(long j=0;j<3;j++){
    //        for(long h=0;h<3;h++){
    //            for(auto& it:level3.cells){
    //                Point2d current=it.first;
    //
    //                level4.increaseBy(static_cast<long>(round((current.x)/gridSizeTemp)*gridSizeTemp-1+j),static_cast<long>(round((current.y)/gridSizeTemp)*gridSizeTemp-1+h),it.second.value);
    //            }
    //        }
    //    }

    masses.resize(qs.size(),std::vector<double>());















    radii.clear();

    for(double i=0.0;i<maxDepth;i++){
        if(type==GEOMETRIC){
            radii.push_back(gridSize*pow(3.0,i));
        }
        if(type==ARITHMETIC){
            radii.push_back(gridSize*((i*2.0)+1.0));
            topologicalRadii.push_back(i);
        }

        std::cout<<"radii "<<radii[i]<<'\n';
    }




    x.clear();
    y.clear();




    double sqrt2=sqrt(2);

    double numberObjectsCounted=0;
    // long j=0;
    std::vector<double> xs;
    std::vector<double> ys;
    xs.reserve(radii.size());
    ys.reserve(radii.size());
    std::vector<double> numberNonZeroBoxes;
    numberNonZeroBoxes.resize(radii.size(),0);


    //// j deberia tener el tamano de qs!!!!
    for(long j=0;j<qs.size();j++){
        // double qs_current=qs[j];
        numberObjectsCounted=0;

        // masses[j].clear();

        // if(Functions::runiform(0, 1)<probabilityToDecideIfCompute){
        //     numberObjectsCounted++;
        //     Point2d current=it.first;


        masses[j].resize(maxDepth,0);
        //     if(type==ARITHMETIC){
        //         std::vector<bool> nonEmpty;
        //         nonEmpty.resize(radii.size(),false);
        //         for(long i=-maxDepth;i<=maxDepth;i++){
        //             for(long g=-maxDepth;g<=maxDepth;g++){
        //                 for(long h=topologicalRadii.size()-1;h>=0;h--){
        //                     double distance=Functions::getDistance(current,Point2d(current.x+i,current.y+g));
        //                     if(distance<=topologicalRadii[h]*sqrt2){
        //                         if(multipleGrids[0][0].getValue(current.x+i,current.y+g)>0){
        //                             nonEmpty[h]=true;
        //                             masses[j][h]+=pow(multipleGrids[0][0].getValue(current.x+i,current.y+g),qs[j]);
        //                         }
        //                     }
        //                     else{
        //                         break;
        //                     }
        //                 }

        //             }
        //         }
        //         for(long h=0;h<nonEmpty.size();h++){
        //             numberNonZeroBoxes[h]++;
        //         }
        //     }else{
        for(long g=0;g<numberCalculations;g++){

            for(long i=0;i<maxDepth;i++){
                for(auto& it:multipleGrids[g][i].cells){

                    Point2d current=it.first;
                    if(multipleGrids[g][i].getValue(current.x,current.y)>0){
                        numberNonZeroBoxes[i]+=1.0/(double)(qs.size());
                        masses[j][i]+=pow(multipleGrids[g][i].getValue(current.x,current.y),qs[j])/(double)(numberCalculations);




                    }
                }
            }
            // }




            // auto lr=LinearRegression::computeBestFit(radii, masses[j],true);
            // if(lr.first.slope<1||lr.first.slope>2||lr.first.adjusted_R2<0.98){
            //     masses[j].clear();
            //     numberObjectsCounted--;
            // }
        }

        // j++;
    }
    //    }





    // std::vector<std::vector<double> > Dqs_epsilon;
    // std::vector<double> taus;
    // taus.resize(qs.size());
    // for(long i=0;i<qs.size();i++){

    //     std::vector<double> Dqs_epsilon_Temp;
    //     Dqs_epsilon_Temp.resize(radii.size());
    //     Dqs_epsilon.push_back(Dqs_epsilon_Temp);
    // }
    for(long i=0;i<masses.size();i++){
        for(long h=0;h<radii.size()-0;h++){
            if(type==ARITHMETIC){
                masses[i][h]/=numberNonZeroBoxes[h];
            }else if (type==GEOMETRIC){
                //                    masses[i][h]/=numberNonZeroBoxes[h];
            }
            //         Dqs_epsilon[j][h]+=pow(masses[i][h]/numberObjectsCounted,qs[j]);

        }
    }
    for(long j=0;j<qs.size();j++){

        auto lr=LinearRegression::compute(radii,masses[j],detectGridSize.second.first,radii.size()-detectGridSize.second.second,true);
        double d_support=2.0;
        Dqs[j]=((lr.slope))/(qs[j]-1.0);

    }



    //     double q=2.0;

    //     double M_temp=1.0;
    //     double L_temp=1.0;
    //     double maxMass=0.0;
    //     for(long i=0;i<masses.size();i++){



    //         if(masses[i].size()>0){
    //             //                                std::cout<<"gamma "<<gammas[i]<<'\n';

    //             for(long h=0;h<radii.size()-0;h++){
    //                 //                if(masses[i][h]<1){
    //                 //                    std::cout<<""<<'\n';
    //                 //                }
    //                 massesDeformedByQ[h]+=pow(masses[i][h]/M_temp,q-1)/numberObjectsCounted;
    //                 //                        std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
    //                 if(masses[i][h]>maxMass){

    //                     maxMass=masses[i][h];
    //                 }
    //             }
    //         }

    //     }



    // //    for(long i=0;i<radii.size()-0;i++){
    // //
    // //
    // //
    // //
    // //        x.push_back(log(massesDeformedByQ[i])/(q-1));
    // //        y.push_back(log(radii[i]*coefRadius/L_temp));
    // //        if(i>=detectGridSize.second.first&&i<=maxDepth-detectGridSize.second.second){
    // //            std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(log(radii[i]*coefRadius/L_temp))<<",mass="<<exp(log(massesDeformedByQ[i])/(q-1))<<"))"<<'\n';
    // //        }
    // //
    // //    }
    // //    auto lr=LinearRegression::compute(y,x,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
    // //    double D2=lr.slope;
    // //    std::cout<<"D2="<<D2<<'\n';

    //     for(long i=0;i<radii.size()-0;i++){




    //         x.push_back(log(massesDeformedByQ[i])/(q-1));
    //         y.push_back(log(radii[i]/L_temp));
    //         std::cout<<"df=rbind(df,data.frame(q="<<q<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';

    //     }
    //     auto lr=LinearRegression::compute(y,x,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
    //     double D2=lr.slope;
    //     std::cout<<"D2="<<D2<<'\n';

    //     lr=LinearRegression::compute(x,y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);


    //     double slopeA=lr.slope;
    //     double interceptA=lr.intercept;
    //     long size=x.size();
    //     x.clear();
    //     y.clear();
    //     for(long i=0;i<size;i++){
    //         x.push_back(exp(log(massesDeformedByQ[i])/(q-1)*slopeA+interceptA));
    //         y.push_back(radii[i]/L_temp);
    //     }
    //     lr=LinearRegression::compute(x,y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);


    //     //    L=pow(M,1/1.7149);
    //     //    M=maxMass;
    //     L=lr.slope*(exp(log(M)*slopeA+interceptA))+lr.intercept;











    // //    M=1;
    // //    L=1;

    //     std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
    //     x.clear();
    //     y.clear();
    //     for(long j=0;j<qs.size();j++){
    //         if(qs[j]!=1){


    //             for(long i=0;i<masses.size();i++){


    //                 if(masses[i].size()>0){

    //                     for(long h=0;h<radii.size()-0;h++){
    //                         massesDeformedByQ[h]+=pow(masses[i][h]/M,qs[j]-1.0)/numberObjectsCounted;
    //                         if(h==0){
    // //                            std::cout<<qs[j]<<" "<<masses[i][h]<<" "<<M<<" "<<numberObjectsCounted<<" "<<" "<<massesDeformedByQ[h]<<'\n';
    //                         }

    //                     }
    //                 }
    //             }
    // //            std::cout<<'\n';
    //             for(long i=0;i<radii.size()-0;i++){


    // //                if(radii[i]/L>0&&massesDeformedByQ[i]>0){
    //                     x.push_back(log(radii[i]/L));
    //                     y.push_back(log(massesDeformedByQ[i])/(qs[j]-1.0));
    // //                }
    // //                 std::cout<<qs[j]<<" "<<massesDeformedByQ[i]<<" "<<log(massesDeformedByQ[i])<<" "<<log(massesDeformedByQ[i])/(qs[j]-1.0)<<'\n';
    //                  if(i>=detectGridSize.second.first&&i<maxDepth-detectGridSize.second.second){
    //                     std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(log(massesDeformedByQ[i])/(qs[j]-1))<<"))"<<'\n';
    //                  }
    // //                    std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(y[y.size()-1])<<"))"<<'\n';


    //             }
    //             if(j==0){
    // //                detectGridSize.second=LinearRegression::detectUpperAndLowerCutoff(x, y, false);
    // //                detectGridSize.second.first+=1;
    // //                detectGridSize.second.second+=1;
    //             }
    //             auto lr=LinearRegression::compute(x, y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
    //             Dqs[j]=lr.slope;


    //         }else{

    //             for(long i=0;i<masses.size();i++){


    //                 if(masses[i].size()>0){

    //                     for(long h=0;h<radii.size()-0;h++){
    //                         massesDeformedByQ[h]+=log(masses[i][h]/M)/numberObjectsCounted;

    //                     }
    //                 }
    //             }

    //             for(long i=0;i<radii.size()-0;i++){


    // //                if(radii[i]/L>0){
    //                     x.push_back(log(radii[i]/L));
    //                     y.push_back((massesDeformedByQ[i]));
    //                  if(i>=detectGridSize.second.first&&i<maxDepth-detectGridSize.second.second){
    //                     std::cout<<"df=rbind(df,data.frame(q="<<qs[j]<<",radii="<<exp(x[x.size()-1])<<",mass="<<exp(massesDeformedByQ[i])<<"))"<<'\n';
    //                  }
    // //                }

    //             }
    //             auto lr=LinearRegression::compute(x, y,detectGridSize.second.first,radii.size()-detectGridSize.second.second,false);
    //             Dqs[j]=lr.slope;
    //         }
    //         std::fill(massesDeformedByQ.begin(),massesDeformedByQ.end(),0);
    //         x.clear();
    //         y.clear();

    //     }

    InterfaceMultiFractalAnalysis ima;
    Dqs.swap(ima.Dqs);
    return ima;

}




std::tuple<std::vector<double>,std::vector<double> >  FractalDimension::boxCountingPlaneSweep(Grafo* G,long depthLimit){
    // int MEMORYorSPEED=
    // if(!G->isPlanar){

        // long maxDegree=-std::numeric_limits<long>::max();

        std::vector<double> boxesPerLevel;
        std::vector<double> sizeGridPerLevel;
        boxesPerLevel.resize(depthLimit,0);
        sizeGridPerLevel.resize(depthLimit,0);
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        // maxDegree=2;

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
        double origMaxX=maxX;
        double origMaxY=maxY;
        double origMinX=minX;
        double origMinY=minY;
        centroid.x/=(double)(G->nodes.size());
        centroid.y/=(double)(G->nodes.size());


        double radius=0;
        radius=Functions::max(Functions::max(maxX-centroid.x,centroid.x-minX),Functions::max(maxY-centroid.y,centroid.y-minY));

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;

        for(long i=0;i<depthLimit;i++){
                sizeGridPerLevel[i]=(2*radius)/pow(2,i);
            }

        double maxRuns=1.0;
        for(long run=0;run<maxRuns;run++){
        //        maxX=-INFINITY;
        //  minX=INFINITY;
        //  maxY=-INFINITY;
        //  minY=INFINITY;

        // for(long i=0;i<G->nodes.size();i++){
        //     if(G->nodes[i]->location.x>maxX){
        //         maxX=G->nodes[i]->location.x;
        //     }
        //     if(G->nodes[i]->location.y>maxY){
        //         maxY=G->nodes[i]->location.y;
        //     }
        //     if(G->nodes[i]->location.x<minX){
        //         minX=G->nodes[i]->location.x;
        //     }
        //     if(G->nodes[i]->location.y<minY){
        //         minY=G->nodes[i]->location.y;
        //     }
        // }
            std::vector<std::vector<long> > idsIntersected;
            std::vector<Point2d> intersections;
            std::deque<double> maxXs;
            std::deque<double>  minXs;
            std::deque<double> maxYs;
            std::deque<double> minYs;
        //    std::queue<long> numbers_DifferentLines;
            std::deque<long> depths;
            std::deque<std::vector<long> > idsLines;
            std::deque<std::vector<long> > idsNodes;
            // std::deque<std::deque<int> > quadrantsToExplore;


            // double a_maxX,a_maxY,a_minX,a_minY;
            long depth;

            // double randomRadius=1.0/pow(2.0,floor(Functions::runiform(0.0,5.0)));
            double randomRadius=1.0/pow(2.0,(double)(run));
            randomRadius=1.0;


            double gridSize=(radius*randomRadius)/2;
            // double gridSize=(2*radius*randomRadius)/pow(2,depthLimit-1);
            double randomX=Functions::runiform(-gridSize,gridSize);
            double randomY=Functions::runiform(-gridSize,gridSize);

            // double randomRadius=1.0/pow(2.0,5.0);
            if(run==0){
                randomX=0;
                randomY=0;
            }
            // a_maxX=maxX;
            // a_maxY=maxY;
            // a_minX=minX;
            // a_minY=minY;

            maxXs.push_front(centroid.x+radius*randomRadius+randomX);
            minXs.push_front(centroid.x-radius*randomRadius+randomX);
            maxYs.push_front(centroid.y+radius*randomRadius+randomY);
            minYs.push_front(centroid.y-radius*randomRadius+randomY);
            // maxXs.push_front(maxX);
            // maxYs.push_front(maxY);
            // minXs.push_front(minX);
            // minYs.push_front(minY);



            std::vector<long> idsLinesTemp;
            std::vector<long> idsNodesTemp;
            std::queue<int> quadrantsToExploreTemp;
            for(long i=0;i<G->links.size();i++){
                idsLinesTemp.push_back(G->links[i]->id);
            }
            for(long i=0;i<G->nodes.size();i++){
                idsNodesTemp.push_back(G->nodes[i]->id);
            }
            for(int i=0;i<4;i++){
                quadrantsToExploreTemp.push(i);
            }
            idsLines.push_front(idsLinesTemp);
            idsNodes.push_front(idsNodesTemp);
            // if(MEMORYorSPEED==MEMORY){
            //     quadrantsToExplore.push_front(quadrantsToExploreTemp);
            // }
        //    numbers_DifferentLines.push(idsLinesTemp.size());
            depths.push_front(0);

            double gridSizeX=2*radius*randomRadius;

            double gridSizeY=2*radius*randomRadius;



            while (depths.size()>0){
                maxX=maxXs.front();
                maxY=maxYs.front();
                minX=minXs.front();
                minY=minYs.front();
                // if(MEMORYorSPEED==MEMORY){
                //     quadrantsToExploreTemp=quadrantsToExplore.front();
                // }

                idsLinesTemp=idsLines.front();
                idsNodesTemp=idsNodes.front();
        //        numLines=numbers_DifferentLines.front();
                depth=depths.front();






        //        std::cout<<depth<<'\n';
                // int currentQuadrant = -1;
               // if(MEMORYorSPEED==MEMORY){
               //      quadrantsToExplore.pop_front();
               //      currentQuadrant=quadrantsToExploreTemp.front();
               //      quadrantsToExploreTemp.pop();

               //      quadrantsToExplore.push_front(quadrantsToExploreTemp);
               //      if(quadrantsToExploreTemp.size()==0){
               //          maxXs.pop_front();
               //          maxYs.pop_front();
               //          minXs.pop_front();
               //          minYs.pop_front();

               //          idsLines.pop_front();
               //          idsNodes.pop_front();
               //          //        numbers_DifferentLines.pop();
               //          depths.pop_front();
               //          quadrantsToExplore.pop_front();
               //      }

               //  }else{
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
        //            quadrantsToExplore.pop_front();
                // }


                if(idsLinesTemp.size()>0||idsNodesTemp.size()>0){
                    // if(run==0&&depth>0&&boxesPerLevel[depth]==0&&boxesPerLevel[depth-1]==1){
                    //     depthLimit++;
                    // }
                    if(boxesPerLevel.size()>depth){
                        boxesPerLevel[depth]++;
                    }else{
                        boxesPerLevel.push_back(1);
                        sizeGridPerLevel.push_back(sizeGridPerLevel[depth-1]/2.0);
                    }


                gridSizeX=((maxX-minX));

                gridSizeY=((maxY-minY));
                // bool STOP=false;
                // if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
                //     STOP=true;
                // }
                if((depth>=depthLimit-1)){
        //            // checkIntersection;
        //             for(long i=0;i<idsLinesTemp.size()-1;i++){
        //                 for(long j=i+1;j<idsLinesTemp.size();j++){
        //                     long it=idsLinesTemp[i];
        //                     long it2=idsLinesTemp[j];
        //                     if(it!=it2){
        // //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
        //                         Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
        //                         if(commonNode==NULL){
        //                             Point2d intersection;
        //                             bool valid;

        //                             Functions::intersection(G->links[it]->A()->location, G->links[it]->B()->location, G->links[it2]->A()->location, G->links[it2]->B()->location, intersection, valid);
        //                             if(valid){
        //                                 std::vector<long> idsIntersectedTemp;
        //                                 idsIntersectedTemp.reserve(2);
        //                                 idsIntersectedTemp.push_back(it);
        //                                 idsIntersectedTemp.push_back(it2);
        //                                 idsIntersected.push_back(idsIntersectedTemp);
        //                                 intersections.push_back(intersection);
        // //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
        //                             }
        //                         }
        //                     }

        //                 }
        //             }


                }else{

                    std::vector<std::vector<long> > idsLinesPerQuadrant;
                    std::vector<std::vector<long> > idsNodesPerQuadrant;
        //            std::vector<long > numLinesPerQuadrant;
        //            numLinesPerQuadrant.resize(4,0);
                    idsLinesPerQuadrant.resize(4,std::vector<long>());
                    idsNodesPerQuadrant.resize(4,std::vector<long>());
                    Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                    for(long i=0;i<idsNodesTemp.size();i++){
                        long quadrant=Functions::getQuadrant(center, G->nodes[idsNodesTemp[i]]->location);

                        if(Functions::inBoundaryOfASquare(center, G->nodes[idsNodesTemp[i]]->location, gridSizeX, gridSizeY)){
                            idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                        }
                    }

                    for(long i=0;i<idsLinesTemp.size();i++){
        //                for(long j=0;j<idsLinesTemp.size();j++){
                            long it=idsLinesTemp[i];

        //                if(depth==1&&it+1==336){
        //                    std::cout<<"check issue";
        //                }
                        std::vector<long> quadrants=Functions::getQuadrantsLine(center, G->links[it]->A()->location, G->links[it]->B()->location, gridSizeX, gridSizeY);
        //                if(quadrants.size()==0){
        //                    std::cout<<"wtf!"<<'\n';
        //                }
        //                if(quadrants.size()==0){
        //                    std::cout<<"Depth: "<<depth<<'\n';
        //                    std::cout<<"id: "<<it+1<<'\n';
        //                }

                        for(long j=0;j<quadrants.size();j++){
                            // if(quadrants[j]==currentQuadrant){
                                idsLinesPerQuadrant[quadrants[j]].push_back(it);
                            // }
        //                    numLinesPerQuadrant[itSet]++;
                        }
                    }

                    int startLoop=0;
                    int endLoop=4;

                    // if(MEMORYorSPEED==MEMORY){
                    //     startLoop=currentQuadrant;
                    //     endLoop=currentQuadrant+1;
                    // }else if (MEMORYorSPEED==SPEED){
                        // startLoop=0;
                        // endLoop=4;
                    // }

                    for(long i=startLoop;i<endLoop;i++){
        //            long i=currentQuadrant;{
                        double currentCol=i%2;
                        double currentRow=i/2;


        //                startingIndex=1;
                        double gridSizeX_temp=((maxX-minX)/2.0);
        //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                        double gridSizeY_temp=((maxY-minY)/2.0);
                        double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                        double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                        minXs.push_back(currentMinX);
                        minYs.push_back(currentMinY);
                        maxXs.push_back(currentMinX+gridSizeX_temp);
                        maxYs.push_back(currentMinY+gridSizeY_temp);
                        idsLines.push_back(idsLinesPerQuadrant[i]);
                        idsNodes.push_back(idsNodesPerQuadrant[i]);
        //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                        depths.push_back(depth+1);

                        // if(MEMORYorSPEED==MEMORY){
                        //     std::queue<int> qTemp;
                        //     for(int i=0;i<4;i++){
                        //         qTemp.push(i);
                        //     }
                        //     quadrantsToExplore.push_front(qTemp);
                        // }


        //                indexes.push(initialIndex);
                    }
                }
            }
            }
        }
        for(long i=0;i<boxesPerLevel.size();i++){
            boxesPerLevel[i]/=maxRuns;
        }
        // Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
    // }
    // G->isPlanar=true;
        std::tuple<std::vector<double>,std::vector<double> > result;
        result=std::make_tuple(sizeGridPerLevel,boxesPerLevel);
        return result;

}








std::tuple<std::vector<double>,std::vector<double> >  FractalDimension::boxCountingPlaneSweep_mixScales(Grafo* G,long depthLimit){
    // int MEMORYorSPEED=
    // if(!G->isPlanar){

        // long maxDegree=-std::numeric_limits<long>::max();
        // long depthLimit=10;
        std::vector<double> boxesPerLevel;
        std::vector<double> sizeGridPerLevel;
        boxesPerLevel.resize(depthLimit,0);
        sizeGridPerLevel.resize(depthLimit,0);
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        // maxDegree=2;

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
        double origMaxX=maxX;
        double origMaxY=maxY;
        double origMinX=minX;
        double origMinY=minY;
        centroid.x/=(double)(G->nodes.size());
        centroid.y/=(double)(G->nodes.size());


        double radius=0;
        radius=(Functions::max(Functions::max(Functions::abs(maxX-centroid.x),Functions::abs(centroid.x-minX)),Functions::max(Functions::abs(maxY-centroid.y),Functions::abs(centroid.y-minY))));
            maxX=(centroid.x+radius);
            minX=(centroid.x-radius);
            maxY=(centroid.y+radius);
            minY=(centroid.y-radius);
            double originalRadius=radius;

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;

        for(long i=0;i<depthLimit;i++){
                sizeGridPerLevel[i]=(2*radius)/pow(2,i);
            }

        double maxRuns=50;
        for(long run=0;run<maxRuns;run++){
            // if(run>0){
            //     radius=originalRadius/4.0/pow(2.0,Functions::min(12,run));
            //     maxX=(centroid.x+radius);
            //     minX=(centroid.x-radius);
            //     maxY=(centroid.y+radius);
            //     minY=(centroid.y-radius);
            // }

            // std::cout<<"sizes "<<2*radius<<" "<<maxX-minX<<" "<<maxY-minY<<'\n';
            std::vector<std::vector<long> > idsIntersected;
            std::vector<Point2d> intersections;
            std::deque<double> maxXs;
            std::deque<double>  minXs;
            std::deque<double> maxYs;
            std::deque<double> minYs;
        //    std::queue<long> numbers_DifferentLines;
            std::deque<long> depths;
            std::deque<std::vector<long> > idsLines;
            std::deque<std::vector<long> > idsNodes;
            // std::deque<std::deque<int> > quadrantsToExplore;


            // double a_maxX,a_maxY,a_minX,a_minY;
            long depth;
            // double noiseSize=Functions::max(maxX-minX,maxY-minY)/pow(2,depthLimit-1);
            double noiseSize=(2*originalRadius)/pow(2,depthLimit-1);
            double randomX=Functions::runiform(-noiseSize,noiseSize);
            double randomY=Functions::runiform(-noiseSize,noiseSize);
            // a_maxX=maxX;
            // a_maxY=maxY;
            // a_minX=minX;
            // a_minY=minY;
            maxXs.push_front(maxX+randomX);
            minXs.push_front(minX+randomX);
            maxYs.push_front(maxY+randomY);
            minYs.push_front(minY+randomY);



            std::vector<long> idsLinesTemp;
            std::vector<long> idsNodesTemp;
            std::queue<int> quadrantsToExploreTemp;
            for(long i=0;i<G->links.size();i++){
                idsLinesTemp.push_back(G->links[i]->id);
            }
            for(long i=0;i<G->nodes.size();i++){
                idsNodesTemp.push_back(G->nodes[i]->id);
            }
            for(int i=0;i<4;i++){
                quadrantsToExploreTemp.push(i);
            }
            idsLines.push_front(idsLinesTemp);
            idsNodes.push_front(idsNodesTemp);
            // if(MEMORYorSPEED==MEMORY){
            //     quadrantsToExplore.push_front(quadrantsToExploreTemp);
            // }
        //    numbers_DifferentLines.push(idsLinesTemp.size());
            depths.push_front(0);

            double gridSizeX=((maxX-minX));

            double gridSizeY=((maxY-minY));



            while (depths.size()>0){
                maxX=maxXs.front();
                maxY=maxYs.front();
                minX=minXs.front();
                minY=minYs.front();
                // if(MEMORYorSPEED==MEMORY){
                //     quadrantsToExploreTemp=quadrantsToExplore.front();
                // }

                idsLinesTemp=idsLines.front();
                idsNodesTemp=idsNodes.front();
        //        numLines=numbers_DifferentLines.front();
                depth=depths.front();






        //        std::cout<<depth<<'\n';
                // int currentQuadrant = -1;
               // if(MEMORYorSPEED==MEMORY){
               //      quadrantsToExplore.pop_front();
               //      currentQuadrant=quadrantsToExploreTemp.front();
               //      quadrantsToExploreTemp.pop();

               //      quadrantsToExplore.push_front(quadrantsToExploreTemp);
               //      if(quadrantsToExploreTemp.size()==0){
               //          maxXs.pop_front();
               //          maxYs.pop_front();
               //          minXs.pop_front();
               //          minYs.pop_front();

               //          idsLines.pop_front();
               //          idsNodes.pop_front();
               //          //        numbers_DifferentLines.pop();
               //          depths.pop_front();
               //          quadrantsToExplore.pop_front();
               //      }

               //  }else{
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
        //            quadrantsToExplore.pop_front();
                // }


                if(idsLinesTemp.size()>0||idsNodesTemp.size()>0){
                    // if(run==0&&depth>0&&boxesPerLevel[depth]==0&&boxesPerLevel[depth-1]==1){
                    //     depthLimit++;
                    // }
                    if(boxesPerLevel.size()>depth){
                        boxesPerLevel[depth]++;
                    }else{
                        boxesPerLevel.push_back(1);
                        sizeGridPerLevel.push_back(sizeGridPerLevel[depth-1]/2.0);
                    }

                gridSizeX=((maxX-minX));

                gridSizeY=((maxY-minY));
                // bool STOP=false;
                // if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
                //     STOP=true;
                // }
                if((depth>=depthLimit-1)){
        //            // checkIntersection;
        //             for(long i=0;i<idsLinesTemp.size()-1;i++){
        //                 for(long j=i+1;j<idsLinesTemp.size();j++){
        //                     long it=idsLinesTemp[i];
        //                     long it2=idsLinesTemp[j];
        //                     if(it!=it2){
        // //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
        //                         Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
        //                         if(commonNode==NULL){
        //                             Point2d intersection;
        //                             bool valid;

        //                             Functions::intersection(G->links[it]->A()->location, G->links[it]->B()->location, G->links[it2]->A()->location, G->links[it2]->B()->location, intersection, valid);
        //                             if(valid){
        //                                 std::vector<long> idsIntersectedTemp;
        //                                 idsIntersectedTemp.reserve(2);
        //                                 idsIntersectedTemp.push_back(it);
        //                                 idsIntersectedTemp.push_back(it2);
        //                                 idsIntersected.push_back(idsIntersectedTemp);
        //                                 intersections.push_back(intersection);
        // //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
        //                             }
        //                         }
        //                     }

        //                 }
        //             }


                }else{
                    std::set<long> numberQuadrants;
                    std::vector<std::vector<long> > idsLinesPerQuadrant;
                    std::vector<std::vector<long> > idsNodesPerQuadrant;
        //            std::vector<long > numLinesPerQuadrant;
        //            numLinesPerQuadrant.resize(4,0);
                    idsLinesPerQuadrant.resize(4,std::vector<long>());
                    idsNodesPerQuadrant.resize(4,std::vector<long>());
                    Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                    for(long i=0;i<idsNodesTemp.size();i++){
                        long quadrant=Functions::getQuadrant(center, G->nodes[idsNodesTemp[i]]->location);

                        if(Functions::inBoundaryOfASquare(center, G->nodes[idsNodesTemp[i]]->location, gridSizeX, gridSizeY)){
                            idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                            numberQuadrants.insert(quadrant);
                        }
                    }

                    for(long i=0;i<idsLinesTemp.size();i++){
        //                for(long j=0;j<idsLinesTemp.size();j++){
                            long it=idsLinesTemp[i];

        //                if(depth==1&&it+1==336){
        //                    std::cout<<"check issue";
        //                }
                        std::vector<long> quadrants=Functions::getQuadrantsLine(center, G->links[it]->A()->location, G->links[it]->B()->location, gridSizeX, gridSizeY);
        //                if(quadrants.size()==0){
        //                    std::cout<<"wtf!"<<'\n';
        //                }
        //                if(quadrants.size()==0){
        //                    std::cout<<"Depth: "<<depth<<'\n';
        //                    std::cout<<"id: "<<it+1<<'\n';
        //                }


                        for(long j=0;j<quadrants.size();j++){
                            // if(quadrants[j]==currentQuadrant){
                                idsLinesPerQuadrant[quadrants[j]].push_back(it);
                                numberQuadrants.insert(quadrants[j]);
                            // }
        //                    numLinesPerQuadrant[itSet]++;
                        }
                    }

                    int startLoop=0;
                    int endLoop=4;

                    // if(MEMORYorSPEED==MEMORY){
                    //     startLoop=currentQuadrant;
                    //     endLoop=currentQuadrant+1;
                    // }else if (MEMORYorSPEED==SPEED){
                        // startLoop=0;
                        // endLoop=4;
                    // }
                    if(numberQuadrants.size()>0){
                        // std::cout<<"number of quadrants "<<numberQuadrants.size()<<" "<<depth<<'\n';
                    for(long i=startLoop;i<endLoop;i++){
            //            long i=currentQuadrant;{
                            double currentCol=i%2;
                            double currentRow=i/2;


            //                startingIndex=1;
                            double gridSizeX_temp=((maxX-minX)/2.0);
            //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                            double gridSizeY_temp=((maxY-minY)/2.0);
                            double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                            double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                            minXs.push_front(currentMinX);
                            minYs.push_front(currentMinY);
                            maxXs.push_front(currentMinX+gridSizeX_temp);
                            maxYs.push_front(currentMinY+gridSizeY_temp);
                            idsLines.push_front(idsLinesPerQuadrant[i]);
                            idsNodes.push_front(idsNodesPerQuadrant[i]);
            //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                            depths.push_front(depth+1);

                            // if(MEMORYorSPEED==MEMORY){
                            //     std::queue<int> qTemp;
                            //     for(int i=0;i<4;i++){
                            //         qTemp.push(i);
                            //     }
                            //     quadrantsToExplore.push_front(qTemp);
                            // }


            //                indexes.push(initialIndex);
                        }
                    }
                }
            }
            }
        }
        for(long i=0;i<boxesPerLevel.size();i++){
            boxesPerLevel[i]/=maxRuns;
        }
        // Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
    // }
    // G->isPlanar=true;
        std::tuple<std::vector<double>,std::vector<double> > result;
        result=std::make_tuple(sizeGridPerLevel,boxesPerLevel);
        return result;

}























std::tuple<std::vector<double>,std::vector<double> >  FractalDimension::boxCountingCheckPlaneSweep(Grafo* G,long depthLimit){
    // int MEMORYorSPEED=
    // if(!G->isPlanar){

        // long maxDegree=-std::numeric_limits<long>::max();

        long levelToRead=5;
        std::vector<double> xsRead;
        std::vector<double> ysRead;


        std::vector<double> boxesPerLevel;
        std::vector<double> sizeGridPerLevel;
        boxesPerLevel.resize(depthLimit,0);
        sizeGridPerLevel.resize(depthLimit,0);
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        // maxDegree=2;

        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;

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

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;

        for(long i=0;i<depthLimit;i++){
                sizeGridPerLevel[i]=(Functions::max(maxX,maxY)-Functions::min(minX,minY))/pow(2,i);
            }

        double maxRuns=1.0;
        for(long run=0;run<maxRuns;run++){
              maxX=-INFINITY;
         minX=INFINITY;
         maxY=-INFINITY;
         minY=INFINITY;

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
            std::vector<std::vector<long> > idsIntersected;
            std::vector<Point2d> intersections;
            std::deque<double> maxXs;
            std::deque<double>  minXs;
            std::deque<double> maxYs;
            std::deque<double> minYs;
        //    std::queue<long> numbers_DifferentLines;
            std::deque<long> depths;
            std::deque<std::vector<long> > idsLines;
            std::deque<std::vector<long> > idsNodes;
            // std::deque<std::deque<int> > quadrantsToExplore;


            // double a_maxX,a_maxY,a_minX,a_minY;
            long depth;
            double gridSize=(Functions::max(maxX,maxY)-Functions::min(minX,minY))/pow(2,depthLimit-1);
            double randomX=Functions::runiform(-gridSize,gridSize);
            double randomY=Functions::runiform(-gridSize,gridSize);
            randomX=0;
            randomY=0;
            // a_maxX=maxX;
            // a_maxY=maxY;
            // a_minX=minX;
            // a_minY=minY;

            maxXs.push_front(Functions::max(maxX,maxY)+randomX);
            minXs.push_front(Functions::min(minX,minY)+randomX);
            maxYs.push_front(Functions::max(maxX,maxY)+randomY);
            minYs.push_front(Functions::min(minX,minY)+randomY);
            // maxXs.push_front(maxX);
            // maxYs.push_front(maxY);
            // minXs.push_front(minX);
            // minYs.push_front(minY);


            std::vector<long> idsLinesTemp;
            std::vector<long> idsNodesTemp;
            std::queue<int> quadrantsToExploreTemp;
            for(long i=0;i<G->links.size();i++){
                idsLinesTemp.push_back(G->links[i]->id);
            }
            for(long i=0;i<G->nodes.size();i++){
                idsNodesTemp.push_back(G->nodes[i]->id);
            }
            for(int i=0;i<4;i++){
                quadrantsToExploreTemp.push(i);
            }
            idsLines.push_front(idsLinesTemp);
            idsNodes.push_front(idsNodesTemp);
            // if(MEMORYorSPEED==MEMORY){
            //     quadrantsToExplore.push_front(quadrantsToExploreTemp);
            // }
        //    numbers_DifferentLines.push(idsLinesTemp.size());
            depths.push_front(0);

            double gridSizeX=((maxX-minX));

            double gridSizeY=((maxY-minY));



            while (depths.size()>0){
                maxX=maxXs.front();
                maxY=maxYs.front();
                minX=minXs.front();
                minY=minYs.front();
                // if(MEMORYorSPEED==MEMORY){
                //     quadrantsToExploreTemp=quadrantsToExplore.front();
                // }

                idsLinesTemp=idsLines.front();
                idsNodesTemp=idsNodes.front();
        //        numLines=numbers_DifferentLines.front();
                depth=depths.front();






        //        std::cout<<depth<<'\n';
                // int currentQuadrant = -1;
               // if(MEMORYorSPEED==MEMORY){
               //      quadrantsToExplore.pop_front();
               //      currentQuadrant=quadrantsToExploreTemp.front();
               //      quadrantsToExploreTemp.pop();

               //      quadrantsToExplore.push_front(quadrantsToExploreTemp);
               //      if(quadrantsToExploreTemp.size()==0){
               //          maxXs.pop_front();
               //          maxYs.pop_front();
               //          minXs.pop_front();
               //          minYs.pop_front();

               //          idsLines.pop_front();
               //          idsNodes.pop_front();
               //          //        numbers_DifferentLines.pop();
               //          depths.pop_front();
               //          quadrantsToExplore.pop_front();
               //      }

               //  }else{
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
        //            quadrantsToExplore.pop_front();
                // }


                if(idsLinesTemp.size()>0||idsNodesTemp.size()>0){
                    boxesPerLevel[depth]++;
                    if(depth==depthLimit-1){
                        // std::cout<<"depth "<<depth<<'\n';
                        xsRead.push_back((maxX+minX)/2.0);
                        ysRead.push_back((maxY+minY)/2.0);
                    }
                    if(depth==0){
                        std::cout<<minX<<" "<<minY<<" , "<<maxX<<" "<<maxY<<'\n';
                    }

                gridSizeX=((maxX-minX));

                gridSizeY=((maxY-minY));
                // bool STOP=false;
                // if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
                //     STOP=true;
                // }
                if((depth>=depthLimit-1)){
        //            // checkIntersection;
        //             for(long i=0;i<idsLinesTemp.size()-1;i++){
        //                 for(long j=i+1;j<idsLinesTemp.size();j++){
        //                     long it=idsLinesTemp[i];
        //                     long it2=idsLinesTemp[j];
        //                     if(it!=it2){
        // //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
        //                         Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
        //                         if(commonNode==NULL){
        //                             Point2d intersection;
        //                             bool valid;

        //                             Functions::intersection(G->links[it]->A()->location, G->links[it]->B()->location, G->links[it2]->A()->location, G->links[it2]->B()->location, intersection, valid);
        //                             if(valid){
        //                                 std::vector<long> idsIntersectedTemp;
        //                                 idsIntersectedTemp.reserve(2);
        //                                 idsIntersectedTemp.push_back(it);
        //                                 idsIntersectedTemp.push_back(it2);
        //                                 idsIntersected.push_back(idsIntersectedTemp);
        //                                 intersections.push_back(intersection);
        // //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
        //                             }
        //                         }
        //                     }

        //                 }
        //             }


                }else{

                    std::vector<std::vector<long> > idsLinesPerQuadrant;
                    std::vector<std::vector<long> > idsNodesPerQuadrant;
        //            std::vector<long > numLinesPerQuadrant;
        //            numLinesPerQuadrant.resize(4,0);
                    idsLinesPerQuadrant.resize(4,std::vector<long>());
                    idsNodesPerQuadrant.resize(4,std::vector<long>());
                    Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                    for(long i=0;i<idsNodesTemp.size();i++){
                        long quadrant=Functions::getQuadrant(center, G->nodes[idsNodesTemp[i]]->location);

                        if(Functions::inBoundaryOfASquare(center, G->nodes[idsNodesTemp[i]]->location, gridSizeX, gridSizeY)){
                            idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                        }
                    }

                    for(long i=0;i<idsLinesTemp.size();i++){
        //                for(long j=0;j<idsLinesTemp.size();j++){
                            long it=idsLinesTemp[i];

        //                if(depth==1&&it+1==336){
        //                    std::cout<<"check issue";
        //                }
                        std::vector<long> quadrants=Functions::getQuadrantsLine(center, G->links[it]->A()->location, G->links[it]->B()->location, gridSizeX, gridSizeY);
        //                if(quadrants.size()==0){
        //                    std::cout<<"wtf!"<<'\n';
        //                }
        //                if(quadrants.size()==0){
        //                    std::cout<<"Depth: "<<depth<<'\n';
        //                    std::cout<<"id: "<<it+1<<'\n';
        //                }

                        for(long j=0;j<quadrants.size();j++){
                            // if(quadrants[j]==currentQuadrant){
                                idsLinesPerQuadrant[quadrants[j]].push_back(it);
                            // }
        //                    numLinesPerQuadrant[itSet]++;
                        }
                    }

                    int startLoop=0;
                    int endLoop=4;

                    // if(MEMORYorSPEED==MEMORY){
                    //     startLoop=currentQuadrant;
                    //     endLoop=currentQuadrant+1;
                    // }else if (MEMORYorSPEED==SPEED){
                        // startLoop=0;
                        // endLoop=4;
                    // }

                    for(long i=startLoop;i<endLoop;i++){
        //            long i=currentQuadrant;{
                        double currentCol=i%2;
                        double currentRow=i/2;
                        // std::cout<<"colrow "<<currentCol<<" "<<currentRow<<'\n';


        //                startingIndex=1;
                        double gridSizeX_temp=((maxX-minX)/2.0);
        //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                        double gridSizeY_temp=((maxY-minY)/2.0);
                        double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                        double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                        minXs.push_front(currentMinX);
                        minYs.push_front(currentMinY);
                        maxXs.push_front(currentMinX+gridSizeX_temp);
                        maxYs.push_front(currentMinY+gridSizeY_temp);
                        idsLines.push_front(idsLinesPerQuadrant[i]);
                        idsNodes.push_front(idsNodesPerQuadrant[i]);
        //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                        depths.push_front(depth+1);

                        // if(MEMORYorSPEED==MEMORY){
                        //     std::queue<int> qTemp;
                        //     for(int i=0;i<4;i++){
                        //         qTemp.push(i);
                        //     }
                        //     quadrantsToExplore.push_front(qTemp);
                        // }


        //                indexes.push(initialIndex);
                    }
                }
            }
            }
        }
        for(long i=0;i<boxesPerLevel.size();i++){
            boxesPerLevel[i]/=maxRuns;
        }
        // Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
    // }
    // G->isPlanar=true;
        std::tuple<std::vector<double>,std::vector<double> > result;
        // result=std::make_tuple(sizeGridPerLevel,boxesPerLevel);
        result=std::make_tuple(xsRead,ysRead);
        return result;

}

std::tuple<std::vector<double>,std::vector<double> >  FractalDimension::boxCountingPlaneSweep_bug(Grafo* G,long depthLimit){
    // int MEMORYorSPEED=
    // if(!G->isPlanar){

        // long maxDegree=-std::numeric_limits<long>::max();
        // long depthLimit=20;
        std::vector<double> boxesPerLevel;
        std::vector<double> sizeGridPerLevel;
        boxesPerLevel.resize(depthLimit,0);
        sizeGridPerLevel.resize(depthLimit,0);
        // for(long i=0;i<G->nodes.size();i++){
        //     long degree=getDegree(G->nodes[i]);
        //     if(degree>maxDegree){
        //         maxDegree=degree;
        //     }
        // }
        // maxDegree=2;

        double maxX=-INFINITY;
        double minX=INFINITY;
        double maxY=-INFINITY;
        double minY=INFINITY;

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

    //    std::vector<double> xs_result;
    //    std::vector<double> ys_result;

        for(long i=0;i<depthLimit;i++){
                sizeGridPerLevel[i]=(Functions::max(maxX,maxY)-Functions::min(minX,minY))/pow(2,i);
            }

        double maxRuns=100.0;
        for(long run=0;run<maxRuns;run++){
            std::vector<std::vector<long> > idsIntersected;
            std::vector<Point2d> intersections;
            std::deque<double> maxXs;
            std::deque<double>  minXs;
            std::deque<double> maxYs;
            std::deque<double> minYs;
        //    std::queue<long> numbers_DifferentLines;
            std::deque<long> depths;
            std::deque<std::vector<long> > idsLines;
            std::deque<std::vector<long> > idsNodes;
            // std::deque<std::deque<int> > quadrantsToExplore;


            // double a_maxX,a_maxY,a_minX,a_minY;
            long depth;
            double gridSize=(Functions::max(maxX,maxY)-Functions::min(minX,minY))/pow(2,depthLimit-1);
            double randomX=Functions::runiform(-gridSize,gridSize);
            double randomY=Functions::runiform(-gridSize,gridSize);
            // a_maxX=maxX;
            // a_maxY=maxY;
            // a_minX=minX;
            // a_minY=minY;
            maxXs.push_front(Functions::max(maxX,maxY)+randomX);
            minXs.push_front(Functions::min(minX,minY)+randomX);
            maxYs.push_front(Functions::max(maxX,maxY)+randomY);
            minYs.push_front(Functions::min(minX,minY)+randomY);



            std::vector<long> idsLinesTemp;
            std::vector<long> idsNodesTemp;
            std::queue<int> quadrantsToExploreTemp;
            for(long i=0;i<G->links.size();i++){
                idsLinesTemp.push_back(G->links[i]->id);
            }
            for(long i=0;i<G->nodes.size();i++){
                idsNodesTemp.push_back(G->nodes[i]->id);
            }
            for(int i=0;i<4;i++){
                quadrantsToExploreTemp.push(i);
            }
            idsLines.push_front(idsLinesTemp);
            idsNodes.push_front(idsNodesTemp);
            // if(MEMORYorSPEED==MEMORY){
            //     quadrantsToExplore.push_front(quadrantsToExploreTemp);
            // }
        //    numbers_DifferentLines.push(idsLinesTemp.size());
            depths.push_front(0);

            double gridSizeX=((maxX-minX));

            double gridSizeY=((maxY-minY));



            while (depths.size()>0){
                maxX=maxXs.front();
                maxY=maxYs.front();
                minX=minXs.front();
                minY=minYs.front();
                // if(MEMORYorSPEED==MEMORY){
                //     quadrantsToExploreTemp=quadrantsToExplore.front();
                // }

                idsLinesTemp=idsLines.front();
                idsNodesTemp=idsNodes.front();
        //        numLines=numbers_DifferentLines.front();
                depth=depths.front();






        //        std::cout<<depth<<'\n';
                // int currentQuadrant = -1;
               // if(MEMORYorSPEED==MEMORY){
               //      quadrantsToExplore.pop_front();
               //      currentQuadrant=quadrantsToExploreTemp.front();
               //      quadrantsToExploreTemp.pop();

               //      quadrantsToExplore.push_front(quadrantsToExploreTemp);
               //      if(quadrantsToExploreTemp.size()==0){
               //          maxXs.pop_front();
               //          maxYs.pop_front();
               //          minXs.pop_front();
               //          minYs.pop_front();

               //          idsLines.pop_front();
               //          idsNodes.pop_front();
               //          //        numbers_DifferentLines.pop();
               //          depths.pop_front();
               //          quadrantsToExplore.pop_front();
               //      }

               //  }else{
                    maxXs.pop_front();
                    maxYs.pop_front();
                    minXs.pop_front();
                    minYs.pop_front();

                    idsLines.pop_front();
                    idsNodes.pop_front();
                    //        numbers_DifferentLines.pop();
                    depths.pop_front();
        //            quadrantsToExplore.pop_front();
                // }


                if(idsLinesTemp.size()>0||idsNodesTemp.size()>0){
                    // if(run==0&&depth>1&&boxesPerLevel[depth]==0&&boxesPerLevel[depth-1]==1){
                    //     depthLimit++;
                    // }
                    // if(boxesPerLevel.size()>depth){
                        boxesPerLevel[depth]++;
                    // }else{
                    //     boxesPerLevel.push_back(1);
                    //     sizeGridPerLevel.push_back(sizeGridPerLevel[depth-1]/2.0);
                    // }

                gridSizeX=((maxX-minX));

                gridSizeY=((maxY-minY));
                // bool STOP=false;
                // if(idsNodesTemp.size()==1&&idsLinesTemp.size()<=Grafo::getDegree(G->nodes[idsNodesTemp[0]])){
                //     STOP=true;
                // }
                if((depth>=depthLimit-1)){
        //            // checkIntersection;
        //             for(long i=0;i<idsLinesTemp.size()-1;i++){
        //                 for(long j=i+1;j<idsLinesTemp.size();j++){
        //                     long it=idsLinesTemp[i];
        //                     long it2=idsLinesTemp[j];
        //                     if(it!=it2){
        // //                        std::cout<<"ids lines intersecting "<<it<<" "<<it2<<'\n';
        //                         Nodo* commonNode=Grafo::commonNode(G->links[it],G->links[it2] );
        //                         if(commonNode==NULL){
        //                             Point2d intersection;
        //                             bool valid;

        //                             Functions::intersection(G->links[it]->A()->location, G->links[it]->B()->location, G->links[it2]->A()->location, G->links[it2]->B()->location, intersection, valid);
        //                             if(valid){
        //                                 std::vector<long> idsIntersectedTemp;
        //                                 idsIntersectedTemp.reserve(2);
        //                                 idsIntersectedTemp.push_back(it);
        //                                 idsIntersectedTemp.push_back(it2);
        //                                 idsIntersected.push_back(idsIntersectedTemp);
        //                                 intersections.push_back(intersection);
        // //                                std::cout<<"c("<<intersection.x-a_minX<<","<<intersection.y-a_minY<<","<<a_minX<<","<<a_minY<<"),";
        //                             }
        //                         }
        //                     }

        //                 }
        //             }


                }else{

                    std::vector<std::vector<long> > idsLinesPerQuadrant;
                    std::vector<std::vector<long> > idsNodesPerQuadrant;
        //            std::vector<long > numLinesPerQuadrant;
        //            numLinesPerQuadrant.resize(4,0);
                    idsLinesPerQuadrant.resize(4,std::vector<long>());
                    idsNodesPerQuadrant.resize(4,std::vector<long>());
                    Point2d center=Point2d(minX+gridSizeX/2.0,minY+gridSizeY/2.0);
                    for(long i=0;i<idsNodesTemp.size();i++){
                        long quadrant=Functions::getQuadrant(center, G->nodes[idsNodesTemp[i]]->location);

                        if(Functions::inBoundaryOfASquare(center, G->nodes[idsNodesTemp[i]]->location, gridSizeX, gridSizeY)){
                            idsNodesPerQuadrant[quadrant].push_back(idsNodesTemp[i]);
                        }
                    }

                    for(long i=0;i<idsLinesTemp.size();i++){
        //                for(long j=0;j<idsLinesTemp.size();j++){
                            long it=idsLinesTemp[i];

        //                if(depth==1&&it+1==336){
        //                    std::cout<<"check issue";
        //                }
                        std::vector<long> quadrants=Functions::getQuadrantsLine(center, G->links[it]->A()->location, G->links[it]->B()->location, gridSizeX, gridSizeY);
        //                if(quadrants.size()==0){
        //                    std::cout<<"wtf!"<<'\n';
        //                }
        //                if(quadrants.size()==0){
        //                    std::cout<<"Depth: "<<depth<<'\n';
        //                    std::cout<<"id: "<<it+1<<'\n';
        //                }

                        for(long j=0;j<quadrants.size();j++){
                            // if(quadrants[j]==currentQuadrant){
                                idsLinesPerQuadrant[quadrants[j]].push_back(it);
                            // }
        //                    numLinesPerQuadrant[itSet]++;
                        }
                    }

                    int startLoop=0;
                    int endLoop=4;

                    // if(MEMORYorSPEED==MEMORY){
                    //     startLoop=currentQuadrant;
                    //     endLoop=currentQuadrant+1;
                    // }else if (MEMORYorSPEED==SPEED){
                        // startLoop=0;
                        // endLoop=4;
                    // }

                    for(long i=startLoop;i<endLoop;i++){
        //            long i=currentQuadrant;{
                        double currentCol=i%2;
                        double currentRow=i/2;


        //                startingIndex=1;
                        double gridSizeX_temp=((maxX-minX)/2.0);
        //                double numberObjectsY_temp=((maxY-minY)/gridSizeX_temp);
                        double gridSizeY_temp=((maxY-minY)/2.0);
                        double currentMinX=minX+(double)(currentCol)*gridSizeX_temp;
                        double currentMinY=minY+(double)(currentRow)*gridSizeY_temp;
                        minXs.push_front(currentMinX);
                        minYs.push_front(currentMinY);
                        maxXs.push_front(currentMinX+gridSizeX_temp);
                        maxYs.push_front(currentMinY+gridSizeY_temp);
                        idsLines.push_front(idsLinesPerQuadrant[i]);
                        idsNodes.push_front(idsNodesPerQuadrant[i]);
        //                numbers_DifferentLines.push(numLinesPerQuadrant[i]);
                        depths.push_front(depth+1);

                        // if(MEMORYorSPEED==MEMORY){
                        //     std::queue<int> qTemp;
                        //     for(int i=0;i<4;i++){
                        //         qTemp.push(i);
                        //     }
                        //     quadrantsToExplore.push_front(qTemp);
                        // }


        //                indexes.push(initialIndex);
                    }
                }
            }
            }
        }
        for(long i=0;i<boxesPerLevel.size();i++){
            boxesPerLevel[i]/=maxRuns;
        }
        // Grafo::addLinksFollowingIntersections(G,idsIntersected,intersections,pairsOldIdNewIds,keepTrackChanges);
    // }
    // G->isPlanar=true;
        std::tuple<std::vector<double>,std::vector<double> > result;
        result=std::make_tuple(sizeGridPerLevel,boxesPerLevel);
        return result;

}











std::vector<double> FractalDimension::sandBox_severalNodes(Grafo* G,long idStartNode,long idEndNode){
    double distanceLimit=1000;
  std::vector<double> values;
  values.resize(G->nodes.size(),0);
  std::vector<Number*> numbersRepresentingNodes;
    std::vector<bool> inDijkstra;
    std::vector<bool> inCutoff;
    Grafo::startCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
    InterfaceDijkstra ID;

    double breakEach=10;
    // double distanceLimit=3000;
  // for(long i=0;i<G->nodes.size();i++){

    // for (long i=startNode; i<endNode; i++)
    // {
        // if(G->nodes[i]->mass>0){
    // std::vector<long> idNodes;
    std::vector<double> fds;
    fds.resize(idEndNode-idStartNode,0);

    for(long i=idStartNode;i<idEndNode;i++){
        Nodo* node=G->nodes[i];

        std::vector<double> xs;
        std::vector<double> ys;
        // std::vector<double> gridSizes;
        for(long j=0;j<=ceil(log(distanceLimit));j++){
            xs.push_back(exp(j));
        }
        ys.resize(xs.size(),0);

        double distanceLimit_temp=distanceLimit;
        for(long j=0;j<G->nodes[i]->links.size();j++){
            if(G->nodes[i]->links[j]->weight>distanceLimit_temp){
                distanceLimit_temp=G->nodes[i]->links[j]->weight+1;
            }
        }
        Grafo::calculateDijkstra(G,node,ID,distanceLimit_temp,numbersRepresentingNodes,inDijkstra,inCutoff);
        Grafo sg;

        Grafo::inducedSubgraph(G,&sg,ID.idsInCutoff);
        for(long j=0;j<sg.links.size();j++){
            long idA=G->getNodeByLocation(sg.links[j]->A()->location)->id;
            long idB=G->getNodeByLocation(sg.links[j]->B()->location)->id;
            double distanceA=ID.getMinDistance(idA);
            double distanceB=ID.getMinDistance(idB);
            if(distanceA>distanceB){
                std::swap(distanceA,distanceB);
                std::swap(idA,idB);
            }
            double distanceTemp=Functions::getDistance(G->nodes[idA]->location,G->nodes[idB]->location);
            // double dx=G->nodes[idB]->location.x-G->nodes[idA]->location.x;
            // double dy=G->nodes[idB]->location.y-G->nodes[idA]->location.y;

            // if(ceil(log(distanceA))==ceil(log(distanceB))&&ceil(log(distanceA))<=ceil(log(distanceLimit))){
            //     ys[ceil(log(distanceA))]+=distanceTemp;
            // }else{
            //     if(Functions::max(ceil(log(distanceA)),ceil(log(distanceB)))<5){
            //         ys[4]+=distanceTemp;
            //     }else{

                    double counter=0.0;
                    double distanceTT=breakEach*counter;
                    while(distanceTT<distanceTemp){
                        double distanceFromNode=Functions::min(ID.getMinDistance(idA)+distanceTT,ID.getMinDistance(idB)-distanceTT+distanceTemp);
                        if(distanceFromNode<distanceLimit){
                            ys[ceil(log(distanceFromNode+1))]+=breakEach;
                        }
                        counter+=1.0;
                        distanceTT=breakEach*counter;
                    }
            //     }
            // }

        }
        ID.reset();
        for(long j=0;j<ys.size()-1;j++){
            ys[j+1]+=ys[j];
        }
        // for(long j=0;j<ys.size();j++){
        //     std::cout<<"points=rbind(points,data.frame(x="<<xs[j]<<",y="<<ys[j]<<"))"<<'\n';
        // }
        std::vector<double> xs_;
        std::vector<double> ys_;
        for(long j=0;j<ys.size();j++){
            if(j>4){
                xs_.push_back(xs[j]);
                ys_.push_back(ys[j]);
            }
        }
        LinearRegression lr=LinearRegression::compute(xs_,ys_,true);
        double slope=lr.slope;
          if(!isfinite(slope)){
            slope=1;
          }
        fds[i-idStartNode]=slope;
    }
            // std::swap(idNodes,ID.idsInCutoff);
            // for(long j=0;j<ID.idsInCutoff.size();j++){
            //     double id=ID.idsInCutoff[j];
            //     double distance=ID.getMinDistance(id);
            //     if(distance<INFINITY){
            //         values[i]+=1/(1+pow(distance/1000,4));
            //         // distances[i]+=distance*G->nodes[id]->mass;
            //     }
            // }
        // }


    //    ID.reset();

    // }

    // double col=floor(G->nodes[i]->location.x/width);
    // double row=floor(G->nodes[i]->location.y/width);
    // for(auto it:matrix.cells){
    //   Point2d point=it.first;
    //   double value=it.second.value;
    //   double distance=Functions::getDistance(Point2d(col,row),point);
    //   values[i]+=value*(exp(-distance));

    // }
    // for(long d=0;d<maxDistance;d+=100){

    // }
  // }
  Grafo::finishCalculatingShortestPaths(G,numbersRepresentingNodes,inDijkstra,inCutoff);
  return fds;

}





void FractalDimension::calculateFDSetOfPoints_preparationForParallel(std::vector<std::set<Point2d> >& pointsPerIdCluster,long startIndex,long endIndex,std::vector<double>& fd){
    for(long i=startIndex;i<endIndex;i++){
        Grafo G;
        for(auto it:pointsPerIdCluster[i]){
            G.addNode(it);
        }
        fd[i]=FractalDimension::calculateCapacityDimension(&G);
    }
}

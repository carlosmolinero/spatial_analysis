
#include "GenerativeProcedures.h"


void GenerativeProcedures::generateInitialCities(InterfaceCityGeneration* interface,double d0,double saturationLevel,double maxX,double maxY,long numberCitiesPerRow){

    interface->d0=d0;//1.325;//.33/.3
    double minX=0;
    double minY=0;
    // double maxX=1000;
    // double maxY=1000;
    double definition=.5;
    interface->d0*=definition;
    interface->increment=1;
    interface->cityField.create(minX,minY,maxX,maxY,definition);
    interface->potentialField.create(minX,minY,maxX,maxY,definition*1);
//    interface->saturationLevel=5*interface->increment;
    interface->saturationLevel=saturationLevel;

//    std::vector<City> cities;
//    std::vector<long> indexCitiesByClusterId;

    interface->indexCitiesByClusterId.resize(interface->cityField.clusters.size(),-1);
//    Grafo cityGraph;
//    interface->cityGraph=new Grafo();

    for(long i=0;i<interface->cityField.clusters.size();i++){
        Point2d centroid=interface->cityField.clusters[i].calculateCentroid();
        interface->cityGraph.addNode(centroid);
        interface->cityField.clusters[i].value=0;
//        interface->cityGraph->nodes[interface->cityGraph->nodes.size()-1]->location=interface->cityField.clusters[i].calculateCentroid();

    }

//    GENERATE INITIAL CITIES
    double initialIncrement=10;
    Point2d center=Point2d(maxX/2,maxY/2);
    // long numberCitiesPerRow=5;
    double widthDispersion=maxX*.8;
    for(long i=0;i<numberCitiesPerRow*numberCitiesPerRow;i++){
//        Point2d point=Point2d(Functions::runiform(minX, maxX),Functions::runiform(minY,maxY));
        long column=i%numberCitiesPerRow;
        long row=i/numberCitiesPerRow;
        double separation=(widthDispersion)/(numberCitiesPerRow-1);
        Point2d point=Point2d(center.x-widthDispersion/2+(column*separation),center.y-widthDispersion/2+(row*separation));
//        Point2d point=Point2d(Functions::runiform(minX,maxX),Functions::runiform(minY,maxY));
        interface->cityField.setValue(interface->cityField.getCluster(point), interface->cityField.getCluster(point)->value+initialIncrement);
        City city;

        city.node=interface->cityGraph.nodes[interface->cityField.getCluster(point)->id];
        city.id=city.node->id;
        city.x=interface->cityField.getCluster(point)->value;
        interface->cities.push_back(city);
        interface->indexCitiesByClusterId[interface->cityField.getCluster(point)->id]=interface->cities.size()-1;
        addValuesToPotentialField(interface, interface->cityField.getCluster(point)->id, interface->increment);
        addMetropolisis(interface, interface->cityField.getCluster(point)->id);

    }



//    Singleton<Windows>::instance().add(Point2d(15,15), 850,850);
//    Singleton<Windows>::instance().setTitle(0,"Cities");
//    Singleton<Windows>::instance().get(0)->drawPotentialField(&interface->cityField,true,false,true);
//    Singleton<Windows>::instance().get(0)->zoomExtents();
//    Singleton<Windows>::instance().add(Point2d(900,15), 500,500);
//    Singleton<Windows>::instance().setTitle(1,"Potential field");
//    Singleton<Windows>::instance().get(1)->drawPotentialField(&interface->potentialField,false,false,false);
//    Singleton<Windows>::instance().get(1)->zoomExtents();
//    Singleton<Windows>::instance().add(Point2d(900,560), 500,300);
//    return interface;




}

void GenerativeProcedures::loopGenerateCities(InterfaceCityGeneration* interface,double lambda,double alpha,long numberIterations){
    bool random=false;
    if(random){
        interface->saturationLevel=INFINITY;
    }
//    Plot plotPopulationSquares;
//    plotPopulationSquares.mode=Plot::EUCLIDEAN;
//    long numberIterations=1;

    std::vector<double> values;
    double totalmass=0;
//    if(draw){
//
//        for(long i=0;i<interface->metropolises.size();i++){
//            double value=interface->metropolises[i].calculateSize(interface);
////            std::cout<<"metropolis "<<i<<" "<<generation<<" "<<value<<'\n';
//            if(value>0){
//                values.push_back(value);
//            }
//            totalmass+=value;
//        }
////        for(long j=0;j<interface->cities.size();j++){
////            double value=interface->cities[j].x;
////            if(value>0){
////                values.push_back(value);
////            }
////        }
//
//    }
//    values=Functions::orderValues(values,false);
//    double ranking=1;
//    double entropy=0;
//    double k=1;
//    for(long i=0;i<values.size();i++){
////        plotPopulationSquares.addValue(Point2d(log(ranking),log(values[i])));
//        double probability=values[i]/totalmass;
//        entropy+=-k*probability*log10(probability);
//        ranking++;
//    }

//    if(draw){
////        std::cout<<entropy<<'\n';
////        LinearRegression lr;
////        lr=LinearRegression::compute(plotPopulationSquares.setOfValuesEuclidean,false);
////        plotPopulationSquares.slopeRegression=lr.slope;
////        plotPopulationSquares.interceptRegression=lr.intercept;
////        plotPopulationSquares.regression=true;
////        std::cout<<"regression slope "<<lr.slope<<'\n';
//    }
//    interface->metropolises=getMetropolises(interface);


    for(long k=0;k<numberIterations;k++){
        resetValuesPotentialField(interface);

//        interface->potentialField.reset();
//        for (long i=0;i<interface->cities.size();i++){
//
//            double population=interface->cities[i].x;
//
//            for(long j=0;j<interface->potentialField.clusters.size();j++){
//                double distance=Functions::getDistance(interface->potentialField.clusters[j].calculateCentroid(), interface->cities[i].node->location);
//                double valueToAdd=Functions::decay(distance, interface->d0)*population;
//                interface->potentialField.addValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd);
//
//            }
//
//        }
         double randomId=-1;
        double max=-INFINITY;
        std::vector<double> idsToRandomlyChooseFromDistributionOfPotential;
//        if(!random){
            long numberRepetitions=lambda;
            for(long j=0;j<interface->potentialField.clusters.size();j++){
                double value=pow(interface->potentialField.getNormalizedValue(&interface->potentialField.clusters[j]),alpha);//1 was alpha before
//                std::cout<<value<<'\n';
                for(long i=0;i<numberRepetitions;i++){
                     double random=Functions::runiform(0,1);
//                    double random1=Functions::runiform(0,1);
//                    double random2=Functions::runiform(0,1);
//                double newValue=(value-random1)+lambda*random2;
//                    if(newValue>max){
//                        max=newValue;
//                        randomId=j;
//                    }
                    if (random<value){
                        idsToRandomlyChooseFromDistributionOfPotential.push_back(interface->potentialField.clusters[j].id);
                    }
                }
            }
//        }else{
////            idsToRandomlyChooseFromDistributionOfPotential.push_back((long)std::floor(Functions::runiform(0,interface->potentialField.clusters.size()-1)));
//        }

//        long numberOfCitiesToAddPerIteration=1;
//        if(idsToRandomlyChooseFromDistributionOfPotential.size()>0){
//            for(long j=0;j<numberOfCitiesToAddPerIteration;j++){
                long randomId2=(long)std::floor(Functions::runiform(0, idsToRandomlyChooseFromDistributionOfPotential.size()-1));
//                std::cout<<"random2 "<<randomId2<<'\n';
                randomId=idsToRandomlyChooseFromDistributionOfPotential[randomId2];
//                std::cout<<"randomId "<<randomId<<'\n';




                double initialPopulationValue=interface->cityField.clusters[randomId].value;
                long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                if(initialPopulationValue==0){
//                                        std::cout<<"a"<<'\n';
                    interface->cityField.setValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);

                    City city;
                    Point2d point;
                    point=interface->cityField.clusters[randomId].calculateCentroid();
                    Nodo* node=interface->cityGraph.nodes[randomId];
//                    std::cout<<"location of city node "<<node->location.x<<" , "<<node->location.y<<'\n';
                    city.node=node;
                    city.id=city.node->id;
                    city.x=interface->cityField.clusters[randomId].value;
                    interface->cities.push_back(city);
                    interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id]=interface->cities.size()-1;
                    indexCity=interface->cities.size()-1;
                    if(!random){
                        addValuesToPotentialField(interface, randomId, interface->increment);
                    }
                    addMetropolisis(interface, interface->cityField.clusters[randomId].id);
                }else{
//                    std::cout<<"b"<<'\n';
                    if(interface->cityField.clusters[randomId].value+interface->increment<interface->saturationLevel){
                        interface->cityField.setValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
//                        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
                        if(!random){
                            addValuesToPotentialField(interface, randomId, interface->increment);
                        }
                    }else{
                        double remaining=interface->cityField.clusters[randomId].value+interface->increment-interface->saturationLevel;
                        interface->cityField.setValue(&interface->cityField.clusters[randomId], interface->saturationLevel);
                        if(!random){
                            addValuesToPotentialField(interface, randomId, interface->saturationLevel-interface->cityField.clusters[randomId].value);
                        }
                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;

//                        std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//                        std::vector<City*> cityNeighbors;
//                        if(neighbors.size()>0){
//                            for(long i=0;i<neighbors.size();i++){
//                                if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                                    cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                                    Transition trans;
//                                    trans.a=interface->cities[indexCity].node;
//                                    trans.b=cityNeighbors[cityNeighbors.size()-1]->node;
//                                    trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                                    if(trans.a!=NULL&&trans.b!=NULL){
//                                        if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
//                                            interface->cityGraph.addDirectedTransition(trans);
//                                        }else{
//                                            trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                                        }
//                                    }
//                                }
//
//                            }
                            if(remaining>0){
                                cascade(interface,interface->cityField.clusters[randomId].id,remaining);
                            }
//                        }
                        // addMetropolisis(interface, interface->cityField.clusters[randomId].id);




//                    }
//                }
//                std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//                std::vector<City*> cityNeighbors;
//                if(neighbors.size()>0){
//                    for(long i=0;i<neighbors.size();i++){
//                        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                            cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                            Transition trans;
//                            trans.a=cityNeighbors[cityNeighbors.size()-1]->node;
//                            trans.b=interface->cities[indexCity].node;
//                            trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                            if(trans.a!=NULL&&trans.b!=NULL){
//                                if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1!=-1){
//                                    trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                                }
//                            }
//                        }
//                    }
//                }
            }
        }


    }
//    if(draw){
//        Singleton<Windows>::instance().get(0)->deleteTemporary();
//        Singleton<Windows>::instance().get(1)->deleteTemporary();
//        Singleton<Windows>::instance().get(2)->deleteTemporary();
//        Singleton<Windows>::instance().get(0)->drawPotentialField(&interface->cityField,true,false,true);
//        Singleton<Windows>::instance().get(1)->drawPotentialField(&interface->potentialField,false,false,false);
//        std::vector<Plot> plots;
//        plots.push_back(plotPopulationSquares);
//        Singleton<Windows>::instance().get(2)->drawPlot(plots);
//    }
}



void GenerativeProcedures::cascade(InterfaceCityGeneration* interface,long idClusterInit,long numberPeopleToMove){
//    std::cout<<"cascading"<<'\n';
//    std::cout<<numberPeopleToMove<<'\n';

    long indexCity=interface->indexCitiesByClusterId[idClusterInit];
    long id=interface->cities[indexCity].id;
    long idMetropolis=interface->cities[indexCity].metropolisId;
    Metropolis metropolis=interface->metropolises[idMetropolis];
    std::vector<City*> citiesInMetropolis;
    citiesInMetropolis.reserve(metropolis.citiesIndexes.size());
    std::vector<double>distances;
    distances.reserve(metropolis.citiesIndexes.size());
//    std::vector<ClusterField*> borders;
//        std::vector<double> distanceToBorders;
    double minDistanceToBorders=INFINITY;
    ClusterField* closestBorder=NULL;
    for(long i=0;i<metropolis.citiesIndexes.size();i++){
        if(interface->cities[metropolis.citiesIndexes[i]].x<interface->saturationLevel){
            citiesInMetropolis.push_back(&interface->cities[metropolis.citiesIndexes[i]]);
            distances.push_back(Functions::getDistance(interface->cities[indexCity].node->location, interface->cities[metropolis.citiesIndexes[i]].node->location));

        }
        std::vector<ClusterField*> neighbors=interface->cityField.squareNeighborhood(&interface->cityField.clusters[interface->cities[metropolis.citiesIndexes[i]].node->id]);
//        std::cout<<"_______________"<<'\n';
        for(long j=0;j<neighbors.size();j++){
//            std::cout<<j<<" "<<neighbors[j]->value<<'\n';
            if(neighbors[j]->value==0){
//                borders.push_back(neighbors[j]);
//                distanceToBorders.push_back(Functions::getDistance(interface->cities[indexCity].node->location, interface->cityGraph.nodes[neighbors[j]->id]->location));
                double distance=Functions::getDistance(interface->cities[indexCity].node->location, interface->cityGraph.nodes[neighbors[j]->id]->location);
                if(distance<minDistanceToBorders){
                    closestBorder=neighbors[j];
                    minDistanceToBorders=distance;
                }
            }
        }
    }
    std::vector<long> orderOfIndexes=Functions::getIndexesOfOrderedValues(distances, true);
    for(long i=0;i<citiesInMetropolis.size();i++){
        double spaceAvailable=interface->saturationLevel-citiesInMetropolis[orderOfIndexes[i]]->x;
        if(numberPeopleToMove>=spaceAvailable&&spaceAvailable>0){
//            std::cout<<"cascading A"<<'\n';
            interface->cityField.setValue(&interface->cityField.clusters[citiesInMetropolis[orderOfIndexes[i]]->node->id], interface->saturationLevel);
            numberPeopleToMove-=spaceAvailable;

            addValuesToPotentialField(interface, citiesInMetropolis[orderOfIndexes[i]]->node->id, interface->saturationLevel-citiesInMetropolis[orderOfIndexes[i]]->x);
            citiesInMetropolis[orderOfIndexes[i]]->x=interface->saturationLevel;
        }else{
//            std::cout<<"cascading B"<<'\n';
            interface->cityField.setValue(&interface->cityField.clusters[citiesInMetropolis[orderOfIndexes[i]]->node->id], interface->cityField.clusters[citiesInMetropolis[orderOfIndexes[i]]->node->id].value+numberPeopleToMove);
            citiesInMetropolis[orderOfIndexes[i]]->x+=numberPeopleToMove;
            addValuesToPotentialField(interface, citiesInMetropolis[orderOfIndexes[i]]->node->id, numberPeopleToMove);
            numberPeopleToMove=0;
        }
        if(numberPeopleToMove<=0){
            break;
        }

    }
    if(numberPeopleToMove>0){
//        std::cout<<"moving excess"<<'\n';

        if(closestBorder!=NULL){
//            std::cout<<"closest border not null "<<'\n';
            interface->cityField.setValue(&interface->cityField.clusters[closestBorder->id], interface->cityField.clusters[closestBorder->id].value+interface->increment);

            City city;
            city.id=id;
            Point2d point;
            point=interface->cityField.clusters[closestBorder->id].calculateCentroid();
            Nodo* node=interface->cityGraph.nodes[closestBorder->id];
            //                    std::cout<<"location of city node "<<node->location.x<<" , "<<node->location.y<<'\n';
            city.node=node;
            city.x=interface->cityField.clusters[closestBorder->id].value;
            interface->cities.push_back(city);
            interface->indexCitiesByClusterId[interface->cityField.clusters[closestBorder->id].id]=interface->cities.size()-1;
            indexCity=interface->cities.size()-1;
    //        if(!random){
                addValuesToPotentialField(interface, closestBorder->id, interface->increment);
    //        }
            addMetropolisis(interface, interface->cityField.clusters[closestBorder->id].id);
        }
    }





//    long idReturn=idClusterInit;
////    long previousId=idClusterInit;
//
//    while(numberPeopleToMove>0){
//    std::vector<ClusterField*> neighbors=interface->potentialField.vonNeumannNeighborhood(&interface->potentialField.clusters[idClusterInit]);
//    std::vector<double> values;
//    for(long i=0;i<neighbors.size();i++){
//
//        values.push_back(neighbors[i]->value);
//    }
////    std::vector<long> indexOrderedValues=Functions::getIndexesOfOrderedValues(values, true);
//    double remaining=numberPeopleToMove;
//
//
//
//
//
////    for(long j=0;j<numberOfCitiesToAddPerIteration;j++){
//        std::vector<double> normValues=Functions::normalize(values);
//    std::vector<long> idsToChooseFrom;
//    for(long i=0;i<normValues.size();i++){
////        double min=neighbors[indexOrderedValues[0]]->value;
////        if(neighbors[indexOrderedValues[i]]->id==previousId){
////            min=neighbors[indexOrderedValues[1]]->value;
////        }
////        if(neighbors[indexOrderedValues[i]]->value==min){
//        for(long j=0;j<10;j++){
//
//            double random=Functions::runiform(0,1);
//            if(random<1-normValues[i]){
//                idsToChooseFrom.push_back(i);
//            }
////            idsToChooseFrom.push_back(indexOrderedValues[i]);
//        }
//    }
//        if(idsToChooseFrom.size()==0){
//            for(long i=0;i<neighbors.size();i++){
//                idsToChooseFrom.push_back(i);
//            }
//        }
//
//        double randomId=neighbors[idsToChooseFrom[Functions::runiform(0, idsToChooseFrom.size()-1)]]->id;
////        double randomId=neighbors[random()%neighbors.size()]->id;
//
//        double initialPopulationValue=interface->cityField.clusters[randomId].value;
//        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
//        if(initialPopulationValue==0){
//            interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
//
//            City city;
//            city.node=interface->cityGraph.nodes[interface->cityField.clusters[randomId].id];
//            city.x=interface->cityField.clusters[randomId].value;
//            interface->cities.push_back(city);
//            interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id]=interface->cities.size()-1;
//            indexCity=interface->cities.size()-1;
//            remaining=0;
//            addValuesToPotentialField(interface, randomId, interface->increment);
//            addMetropolisis(interface, interface->cityField.clusters[randomId].id);
//        }else{
//            if(interface->cityField.clusters[randomId].value+interface->increment<=interface->saturationLevel){
//                interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
//                //                        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
//                interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
//                remaining=0;
//                addValuesToPotentialField(interface, randomId, interface->increment);
//            }else{
//                remaining=interface->cityField.clusters[randomId].value+interface->increment-interface->saturationLevel;
//                interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->saturationLevel);
//                addValuesToPotentialField(interface, randomId, interface->saturationLevel-interface->cityField.clusters[randomId].value);
//                interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
//
////                std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
////                std::vector<City*> cityNeighbors;
////                if(neighbors.size()>0){
////                    for(long i=0;i<neighbors.size();i++){
////                        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
////                            cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
////                            Transition trans;
////                            trans.a=interface->cities[indexCity].node;
////                            trans.b=cityNeighbors[cityNeighbors.size()-1]->node;
////                            trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
////                            if(trans.a!=NULL&&trans.b!=NULL){
////                                if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
////                                    interface->cityGraph.addDirectedTransition(trans);
////                                }else{
////                                    trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
////                                }
////                            }
////                        }
////
////                    }
////
////                }
//
//
//
//
//
//            }
//        }
////        neighbors.clear();
////        neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
////        std::vector<City*> cityNeighbors;
////        if(neighbors.size()>0){
////            for(long i=0;i<neighbors.size();i++){
////                if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
////                    cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
////                    Transition trans;
////                    trans.a=cityNeighbors[cityNeighbors.size()-1]->node;
////                    trans.b=interface->cities[indexCity].node;
////                    trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
////                    if(trans.a!=NULL&&trans.b!=NULL){
////                        if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1!=-1){
////                            trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
////                        }
////                    }
////                }
////            }
////        }
//
////    }
//        numberPeopleToMove=remaining;
//        idClusterInit=interface->cityField.clusters[randomId].id;
//        idReturn=idClusterInit;
//    }
//
////    if(remaining>0){
////        idReturn=cascade(interface,interface->cityField.clusters[randomId].id,remaining);
////    }
//
//    return idReturn;



}

void GenerativeProcedures::addValuesToPotentialField(InterfaceCityGeneration* interface,long idCluster,long numberPeopleAdded){
    long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[idCluster].id];
    // double population=numberPeopleAdded;
    // double alpha=2.2;
    for(long j=0;j<interface->potentialField.clusters.size();j++){
        Point2d pointTemp=interface->potentialField.clusters[j].calculateCentroid();
        double distance=Functions::getDistance(pointTemp, interface->cities[indexCity].node->location);
        double currentPopulation=interface->cities[indexCity].x;
        double population=currentPopulation+numberPeopleAdded;
        double a=1.44;
        double b=9.06;
        double c=1.53;
        double alpha=exp(a*b);
        double x=currentPopulation;
        double dx=x;
        // dx=1/(a*c*pow(alpha,-1/a))*(pow(1+alpha*pow(x,-a),c)-1)*(pow(x,a+1)+alpha*x)/(double)(interface->cities.size());
        dx=(pow(x,a+1)+alpha*x)/(double)(interface->cities.size());
        double valueToRemove=Functions::decay(distance, interface->d0)*dx;
        valueToRemove=0;
        x=numberPeopleAdded;
        dx=x;
        // dx=1/(a*c*pow(alpha,-1/a))*(pow(1+alpha*pow(x,-a),c)-1)*(pow(x,a+1)+alpha*x)/(double)(interface->cities.size());
        dx=(pow(x,a+1)+alpha*x)/(double)(interface->cities.size());

        double valueToAdd=Functions::decay(distance, interface->d0)*dx;
        if(valueToAdd<0){
            valueToAdd=0;
        }
        interface->potentialField.setValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd-valueToRemove);

    }
}



void GenerativeProcedures::resetValuesPotentialField(InterfaceCityGeneration* interface){
//
//    interface->potentialField.max=0;
//    interface->potentialField.min=0;
//    for(long j=0;j<interface->potentialField.clusters.size();j++){
//        interface->potentialField.clusters[j].value=0;
//    }
//    for(long i=0;i<interface->metropolises.size();i++){
//        double size=interface->metropolises[i].calculateSize(interface);
////        std::cout<<"size "<<size<<'\n';
//        if(size>0){
//            Point2d point=interface->metropolises[i].calculateCentroid(interface);
//            for(long j=0;j<interface->potentialField.clusters.size();j++){
//                Point2d pointTemp=interface->potentialField.clusters[j].calculateCentroid();
//                double distance=Functions::getDistance(pointTemp, point);
//
//                double valueToAdd=Functions::decay(distance, interface->d0)*(size);
//                if(valueToAdd<0){
//                    valueToAdd=0;
//                }
//                interface->potentialField.setValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd);
//
//            }
//        }
//    }
}



void GenerativeProcedures::addMetropolisis(InterfaceCityGeneration* interface,long clusterId){
//    std::vector<Metropolis> metropolises;
//    std::vector<int> occupiedClusters;
    std::vector<ClusterField*> neighbors=interface->potentialField.vonNeumannNeighborhood(&interface->potentialField.clusters[clusterId]);
    std::vector<City*> neighboringCities;
    std::vector<long> metropolisIds;
    for(long i=0;i<neighbors.size();i++){
        // if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1&&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]].x>=interface->saturationLevel/2&&interface->cities[interface->indexCitiesByClusterId[clusterId]].x>=interface->saturationLevel/2){
        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
            neighboringCities.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
            metropolisIds.push_back(interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]].metropolisId);
        }
    }
    if(neighboringCities.size()==0){
        interface->maxIdMetropolis++;
        Metropolis metropolis;
        metropolis.citiesIndexes.push_back(interface->indexCitiesByClusterId[clusterId]);
        metropolis.id=interface->maxIdMetropolis;
        interface->cities[interface->indexCitiesByClusterId[clusterId]].metropolisId=interface->maxIdMetropolis;
        interface->metropolises.push_back(metropolis);
    }else{
        std::vector<long> uniqueMetropolisIds=Functions::unique(metropolisIds);
        if(uniqueMetropolisIds.size()==1){
//            interface->maxIdMetropolis++;
//            Metropolis metropolis;
            interface->metropolises[uniqueMetropolisIds[0]].citiesIndexes.push_back(interface->indexCitiesByClusterId[clusterId]);
//            metropolis.id=interface->maxIdMetropolis;
            interface->cities[interface->indexCitiesByClusterId[clusterId]].metropolisId=uniqueMetropolisIds[0];
//            interface->metropolises.push_back(metropolis);
        }else{
            std::vector<long> sizesMetropolises;
            for(long i=0;i<uniqueMetropolisIds.size();i++){
                sizesMetropolises.push_back(interface->metropolises[uniqueMetropolisIds[i]].calculateSize(interface));
            }
            std::vector<long> indexesMetropolisesBySize=Functions::getIndexesOfOrderedValues(sizesMetropolises, false);
            Metropolis* mainMetropolis=&interface->metropolises[uniqueMetropolisIds[indexesMetropolisesBySize[0]]];
            for(long i=1;i<indexesMetropolisesBySize.size();i++){
                Metropolis* currentMetropolis=&interface->metropolises[uniqueMetropolisIds[indexesMetropolisesBySize[i]]];


                for(long j=0;j<currentMetropolis->citiesIndexes.size();j++){
                    interface->cities[currentMetropolis->citiesIndexes[j]].metropolisId=mainMetropolis->id;
                    mainMetropolis->citiesIndexes.push_back(currentMetropolis->citiesIndexes[j]);
                }
                currentMetropolis->citiesIndexes.clear();
            }
            interface->metropolises[uniqueMetropolisIds[0]].citiesIndexes.push_back(interface->indexCitiesByClusterId[clusterId]);
            interface->cities[interface->indexCitiesByClusterId[clusterId]].metropolisId=uniqueMetropolisIds[0];
        }
    }

//    occupiedClusters.resize(interface->cityField.clusters.size(),0);
//    for(long i=0;i<interface->cityField.clusters.size();i++){
//        if(interface->cityField.clusters[i].value>=interface->saturationLevel){
//            //            interface->cityField.clusters[i].
//        }
//    }
//    return metropolises;
}





//void GenerativeProcedures::migrate(InterfaceCityGeneration* interface,double proportionMigrations){
//
////    long totalNumberMigrations=(long)((double)interface->cities.size()*proportionMigrations);
//    long totalNumberMigrations=1;
//
//
//    bool random=false;
//    long totalNumberMigrationsFinal=totalNumberMigrations;
//    for(long i=0;i<totalNumberMigrations;i++){
//        long idCity=long(Functions::runiform(0, interface->cities.size()));
//        if(interface->cities[idCity].x>=interface->increment){
//            interface->cities[idCity].x=-interface->increment;
//        }else{
//            totalNumberMigrationsFinal--;
//        }
//
//    }
//
//
//
//
//
//
//
//
//
//
//    for(long k=0;k<totalNumberMigrationsFinal;k++){
//
//        //        interface->potentialField.reset();
//        //        for (long i=0;i<interface->cities.size();i++){
//        //
//        //            double population=interface->cities[i].x;
//        //
//        //            for(long j=0;j<interface->potentialField.clusters.size();j++){
//        //                double distance=Functions::getDistance(interface->potentialField.clusters[j].calculateCentroid(), interface->cities[i].node->location);
//        //                double valueToAdd=Functions::decay(distance, interface->d0)*population;
//        //                interface->potentialField.addValue(&interface->potentialField.clusters[j], interface->potentialField.clusters[j].value+valueToAdd);
//        //
//        //            }
//        //
//        //        }
//        std::vector<double> idsToRandomlyChooseFromDistributionOfPotential;
//        if(!random){
//            long numberRepetitions=10;
//            for(long j=0;j<interface->potentialField.clusters.size();j++){
//                double value=interface->potentialField.getNormalizedValue(&interface->potentialField.clusters[j]);
//                for(long i=0;i<numberRepetitions;i++){
//                    double random=Functions::runiform(0, 1);
//                    if (random<value){
//                        idsToRandomlyChooseFromDistributionOfPotential.push_back(interface->potentialField.clusters[j].id);
//                    }
//                }
//            }
//        }else{
//            idsToRandomlyChooseFromDistributionOfPotential.push_back(Functions::runiform(0,interface->potentialField.clusters.size()-1));
//        }
//        double randomId=-1;
//        long numberOfCitiesToAddPerIteration=1;
//        if(idsToRandomlyChooseFromDistributionOfPotential.size()>0){
//            for(long j=0;j<numberOfCitiesToAddPerIteration;j++){
//                randomId=idsToRandomlyChooseFromDistributionOfPotential[Functions::runiform(0, idsToRandomlyChooseFromDistributionOfPotential.size()-1)];
//                double initialPopulationValue=interface->cityField.clusters[randomId].value;
//                long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
//                if(initialPopulationValue==0){
//                    interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
//
//                    City city;
//                    city.node=interface->cityGraph.nodes[interface->cityField.clusters[randomId].id];
//                    city.x=interface->cityField.clusters[randomId].value;
//                    interface->cities.push_back(city);
//                    interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id]=interface->cities.size()-1;
//                    indexCity=interface->cities.size()-1;
//                    if(!random){
//                        addValuesToPotentialField(interface, randomId, interface->increment);
//                    }
//                    addMetropolisis(interface, interface->cityField.clusters[randomId].id);
//                }else{
//                    if(interface->cityField.clusters[randomId].value+interface->increment<interface->saturationLevel){
//                        interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->cityField.clusters[randomId].value+interface->increment);
//                        //                        long indexCity=interface->indexCitiesByClusterId[interface->cityField.clusters[randomId].id];
//                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
//                        if(!random){
//                            addValuesToPotentialField(interface, randomId, interface->increment);
//                        }
//                    }else{
//                        double remaining=interface->cityField.clusters[randomId].value+interface->increment-interface->saturationLevel;
//                        interface->cityField.addValue(&interface->cityField.clusters[randomId], interface->saturationLevel);
//                        if(!random){
//                            addValuesToPotentialField(interface, randomId, interface->saturationLevel-interface->cityField.clusters[randomId].value);
//                        }
//                        interface->cities[indexCity].x=interface->cityField.clusters[randomId].value;
//
//                        std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//                        std::vector<City*> cityNeighbors;
//                        if(neighbors.size()>0){
//                            //                            for(long i=0;i<neighbors.size();i++){
//                            //                                if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                            //                                    cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                            //                                    Transition trans;
//                            //                                    trans.a=interface->cities[indexCity].node;
//                            //                                    trans.b=cityNeighbors[cityNeighbors.size()-1]->node;
//                            //                                    trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                            //                                    if(trans.a!=NULL&&trans.b!=NULL){
//                            //                                        if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1==-1){
//                            //                                            interface->cityGraph.addDirectedTransition(trans);
//                            //                                        }else{
//                            //                                            trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                            //                                        }
//                            //                                    }
//                            //                                }
//                            //
//                            //                            }
//                            if(remaining>0&&!random){
//                                cascade(interface,interface->cityField.clusters[randomId].id,remaining);
//                            }
//                        }
//
//
//
//
//
//                    }
//                }
//                //                std::vector<ClusterField*> neighbors=interface->cityField.vonNeumannNeighborhood(&interface->cityField.clusters[randomId]);
//                //                std::vector<City*> cityNeighbors;
//                //                if(neighbors.size()>0){
//                //                    for(long i=0;i<neighbors.size();i++){
//                //                        if(interface->indexCitiesByClusterId[neighbors[i]->id]!=-1){
//                //                            cityNeighbors.push_back(&interface->cities[interface->indexCitiesByClusterId[neighbors[i]->id]]);
//                //                            Transition trans;
//                //                            trans.a=cityNeighbors[cityNeighbors.size()-1]->node;
//                //                            trans.b=interface->cities[indexCity].node;
//                //                            trans.weight=interface->saturationLevel*2-(interface->cities[indexCity].x+cityNeighbors[cityNeighbors.size()-1]->x);
//                //                            if(trans.a!=NULL&&trans.b!=NULL){
//                //                                if(trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1!=-1){
//                //                                    trans.a->transitions[trans.a->indexOfTransitionsByIdOfDestination[trans.b->originalID]-1]->weight=trans.weight;
//                //                                }
//                //                            }
//                //                        }
//                //                    }
//                //                }
//            }
//        }
//    }
//}











inline double GenerativeProcedures::findnoise(double x,double y,int noiseKey)
{

 int n=(int)x+(int)y*noiseKey;
 n=(n<<13)^n;
 int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
 return 1.0-((double)nn/1073741824.0);
}


inline double GenerativeProcedures::interpolate(double a,double b,double x)
{
 double ft=x * 3.1415927;
 double f=(1.0-cos(ft))* 0.5;
 return a*(1.0-f)+b*f;
}

double GenerativeProcedures::noise(double x,double y,int noiseKey)
{
//    x=abs(x);
//    y=abs(y);
 double floorx=(double)((int)x);//This is kinda a cheap way to floor a double integer.
 double floory=(double)((int)y);
 double s,t,u,v;//Integer declaration
 s=findnoise(floorx,floory,noiseKey);
 t=findnoise(floorx+1,floory,noiseKey);
 u=findnoise(floorx,floory+1,noiseKey);//Get the surrounding pixels to calculate the transition.
 v=findnoise(floorx+1,floory+1,noiseKey);
 double int1=interpolate(s,t,x-floorx);//Interpolate between the values.
 double int2=interpolate(u,v,x-floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
 return interpolate(int1,int2,y-floory);//Here we use y-floory, to get the 2nd dimension.
}



std::vector<std::vector<double> >  GenerativeProcedures::fractal_noise(long xInit,long yInit,int w,int h,double zoom,double expansionFactor,double p,int octaves,int noiseKey,bool ridged)//w and h speak for themselves, zoom wel zoom in and out on it, I usually
{//                                        use 75. P stands for persistence, this controls the roughness of the picture, i use 1/2
 // int octaves=2;
 std::vector<double> xs;
 std::vector<double> ys;
 std::vector<double> zs;


std::vector<std::vector<double> >   matrix;
 // SDL_Surface *ret=SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,24,0,0,0,0);//Create an empty image.
 for(int y=0;y<h;y++)
 {//Loops to loop trough all the pixels
  for(int x=0;x<w;x++)
  {
   double z =1-Functions::abs(noise(((double)(x+xInit)/zoom)/expansionFactor,((double)(y+yInit)/zoom)/expansionFactor,noiseKey));
   for(int a=1;a<octaves;a++)//This loops trough the octaves.
   {
    double frequency = pow(2,a);//This increases the frequency with every loop of the octave.
    double amplitude = pow(p,a);//This decreases the amplitude with every loop of the octave.
       if(!ridged){
           z += noise(((double)(x+xInit)/zoom)*frequency/expansionFactor,((double)(y+yInit)/zoom)/expansionFactor*frequency,noiseKey)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
       }else{
           z=z+(1-Functions::abs(noise(((double)(x+xInit)/zoom)*frequency/expansionFactor,((double)(y+yInit)/zoom)/expansionFactor*frequency,noiseKey)*amplitude));
       }
   }//                                          It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1
//   int color= (int)((getnoise*128.0)+128.0);//Convert to 0-256 values.
   // if(color>255)
   //  color=255;
   // if(color<0)
   //  color=0;
    xs.push_back((x+xInit)/zoom);
    ys.push_back((y+yInit)/zoom);
    zs.push_back(z);





   // SetPixel(ret,x,y,(int)((r/255.0)*(double)color),(int)((g/255.0)*(double)color),(int)((b/255.0)*(double)color));//This colours the image with the RGB values
  }//                                                          given at the beginning in the function.
 }
 matrix.push_back(xs);
 matrix.push_back(ys);
 matrix.push_back(zs);
 return matrix;
}





std::vector<std::vector<double> > GenerativeProcedures::generateTerrain(long xInit,long yInit,int w,int h,double zoom){


    double a=100;

//    double multiplier=50;

    std::vector<std::vector<double> > continents=fractal_noise(xInit,yInit,w,h,zoom,a*50,.5,10,23,false);
    std::vector<std::vector<double> > largeTraits=fractal_noise(xInit,yInit,w,h,zoom,a*30,.5,10,60,false);
    std::vector<std::vector<double> > mediumTraits=fractal_noise(xInit,yInit,w,h,zoom,a*15,.5,10,57,false);
    std::vector<std::vector<double> > smallTraits=fractal_noise(xInit,yInit,w,h,zoom,a*5,.5,10,100,false);
    std::vector<std::vector<double> > mountains=fractal_noise(xInit,yInit,w,h,zoom,a*1,.5,32,101,false);
    std::vector<std::vector<double> > mountains2=fractal_noise(xInit,yInit,w,h,zoom,a*1,.5,32,40,false);
//            std::vector<std::vector<double> > mountains3=fractal_noise(xInit,yInit,100,100,zoom,a*.1,.5,32,90);
//    std::vector<std::vector<double> > details=fractal_noise(xInit,yInit,100,100,zoom,.1,.5,10,80);


    for(long i=0;i<continents[0].size();i++){
//        if(continents[2][i]>0){
//            continents[2][i]=sqrt(continents[2][i]);
//        }
        continents[2][i]*=20;
//        continents[2][i]+=Functions::max(0.0,largeTraits[2][i])*5;
        continents[2][i]+=(largeTraits[2][i])*5;
        continents[2][i]+=Functions::max(0.0,mediumTraits[2][i])*10;
        continents[2][i]+=Functions::max(0.0,smallTraits[2][i])*5;
        continents[2][i]+=Functions::max(0.0,mountains[2][i]*mountains2[2][i]*smallTraits[2][i]*mediumTraits[2][i])*10;
//        continents[2][i]+=Functions::max(0.0,details[2][i])*.1;
    }



    return continents;





}

std::vector<std::vector<double> > GenerativeProcedures::getSlopeTerrain(std::vector<std::vector<double> > &terrain,long w,long h){

    std::vector<std::vector<double> > slopes;

    // // std::vector<double> heights;
    // long index=0;
    // Grafo G;
    // for(long i=0;i<h;i++){
    //     for(long j=0;j<w;j++){
    //         G.addNode(Point2d(terrain[0][index],terrain[1][index]));

    //         Node* thisNode=G->nodes[index];
    //         if(i>1){
    //             long indexNode=(i-1)*w+h;
    //             Node* otherNode=G->nodes[indexNode];
    //             Link link;
    //             link.a=thisNode;
    //             link.b=otherNode;
    //             link.weight=abs(terrain[2][index]-
    //         }
    //         index++;
    //     }

    // }



    return slopes;





}

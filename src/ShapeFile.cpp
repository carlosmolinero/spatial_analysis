//
//  ShapeFile.cpp
//  spatialTools
//
//  Created by Carlos Molinero on 03/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "ShapeFile.h"

double ShapeFile::calculateDistanceLatLon(double lon1,double lat1,double lon2,double lat2){//haversine formula

    // double R=6378137;
    // double inc_lat=lat2-lat1;
    // double inc_lat_rad=inc_lat/180*M_PI;
    // double inc_lon=lon2-lon1;
    // double inc_lon_rad=inc_lon/180*M_PI;
    // double a=sin(inc_lat_rad/2)*sin(inc_lat_rad/2)+cos(lat1/180*M_PI)*cos(lat2/180*M_PI)*sin(inc_lon_rad/2)*sin(inc_lon_rad/2);
    // double c=2*atan2(sqrt(a), sqrt(1-a));
    // return R*c;
    return ShapeFile::calculateDistanceLatLon(Point2d(lon1,lat1),Point2d(lon2,lat2));
}
double ShapeFile::calculateDistanceLatLon(std::pair<double,double> coordinatesLonLat1,std::pair<double,double> coordinatesLonLat2){//haversine formula
    // double lon1=coordinatesLonLat1.first;
    // double lat1=coordinatesLonLat1.second;
    // double lon2=coordinatesLonLat2.first;
    // double lat2=coordinatesLonLat2.second;
    // double R=6378137;
    // double inc_lat=lat2-lat1;
    // double inc_lat_rad=inc_lat/180*M_PI;
    // double inc_lon=lon2-lon1;
    // double inc_lon_rad=inc_lon/180*M_PI;
    // double a=sin(inc_lat_rad/2)*sin(inc_lat_rad/2)+cos(lat1/180*M_PI)*cos(lat2/180*M_PI)*sin(inc_lon_rad/2)*sin(inc_lon_rad/2);
    // double c=2*atan2(sqrt(a), sqrt(1-a));
    // return R*c;
    return ShapeFile::calculateDistanceLatLon(Point2d(coordinatesLonLat1.first,coordinatesLonLat1.second),Point2d(coordinatesLonLat2.first,coordinatesLonLat2.second));
}
double ShapeFile::calculateDistanceLatLon(Point2d coordinatesLonLat1,Point2d coordinatesLonLat2){//not haversine formula but vincenty


    //THIS ONE WAS HAVERSINE, GENERATES PROBLEMS IN ANTIPODES
    // double lon1=coordinatesLonLat1.y;
    // double lat1=coordinatesLonLat1.x;
    // double lon2=coordinatesLonLat2.y;
    // double lat2=coordinatesLonLat2.x;
    // double R=6378137.0;
    // double inc_lat=lat2-lat1;
    // double inc_lat_rad=inc_lat/180.0*M_PI;
    // double inc_lon=lon2-lon1;
    // double inc_lon_rad=inc_lon/180.0*M_PI;
    // double a=sin(inc_lat_rad/2.0)*sin(inc_lat_rad/2.0)+cos(lat1/180.0*M_PI)*cos(lat2/180.0*M_PI)*sin(inc_lon_rad/2.0)*sin(inc_lon_rad/2.0);
    // double c=2.0*atan2(sqrt(a), sqrt(1.0-a));
    // return R*c;
    //THIS IS VINCENTY, SHOULD BE CORRECT

    if(coordinatesLonLat1.y>90){
      coordinatesLonLat1.y-=180;
    }
    if(coordinatesLonLat1.y<-90){
      coordinatesLonLat1.y+=180;
    }
    if(coordinatesLonLat2.y>90){
      coordinatesLonLat2.y-=180;
    }
    if(coordinatesLonLat2.y<-90){
      coordinatesLonLat2.y+=180;
    }

    if(coordinatesLonLat1.x>180){
      coordinatesLonLat1.x-=360;
    }
    if(coordinatesLonLat1.x<-180){
      coordinatesLonLat1.x+=360;
    }
    if(coordinatesLonLat2.x>180){
      coordinatesLonLat2.x-=360;
    }
    if(coordinatesLonLat2.x<-180){
      coordinatesLonLat2.x+=360;
    }

    double lat1=coordinatesLonLat1.y/180.0*M_PI;
    double lon1=coordinatesLonLat1.x/180.0*M_PI;
    double lat2=coordinatesLonLat2.y/180.0*M_PI;
    double lon2=coordinatesLonLat2.x/180.0*M_PI;
    double R=6378137.0;

    // double inc_lat=lat2-lat1;
    // double inc_lat_rad=inc_lat/180.0*M_PI;
    double inc_lon=abs(lon2-lon1);
    double inc_lat=abs(lat2-lat1);
    // double inc_lon_rad=inc_lon/180.0*M_PI;
    // double a=cos(lat2)*sin(inc_lon);
    // double b=cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(inc_lon);
    // double c=sin(lat1)*sin(lat2);
    // double d=cos(lat1)*cos(lat2)*cos(inc_lon);
    // return (R*atan(sqrt(a*a+b*b)/(c+d)));
//LOOKS LIKE I RETURN TO HAVERSINE, BECAUSE THE OTHER ONE WAS GIVING NEGATIVES
    return R*2*asin(sqrt(sin(inc_lat/2)*sin(inc_lat/2)+cos(lat1)*cos(lat2)*sin(inc_lon/2)*sin(inc_lon/2)));

}

//std::pair<double,double> ShapeFile::transformCoordinates(std::pair<double,double> coordinates,std::string EPSG_in,std::string EPSG_out){
//    OGRSpatialReference oTargetSRS;
//    OGRSpatialReference oSourceSRS;
//    OGRCoordinateTransformation *poCT;
//
//
//
//    const char * EPSG_code_cc;
//    EPSG_code_cc= EPSG_out.c_str();
//    oTargetSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
//    EPSG_code_cc= EPSG_in.c_str();
//    oSourceSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
//
//    poCT = OGRCreateCoordinateTransformation( &oSourceSRS,&oTargetSRS );
//
//
////    double prevX=coordinates[0];
////    double prevY=coordinates[1];
//
//    if( poCT == NULL || !poCT->Transform( 1, &coordinates.first, &coordinates.second) ){
//        printf( "Transformation failed.\n" );
//    }
////    else
////        printf( "(%f,%f) -> (%f,%f)\n",
////               prevX,
////               prevY,
////               coordinates[1], coordinates[2]);
//
//    return coordinates;
//
//}

Point2d ShapeFile::transformCoordinates(Point2d coordinates,OGRCoordinateTransformation* poCT){


    //    double prevX=coordinates[0];
    //    double prevY=coordinates[1];

    if( poCT == NULL || !poCT->Transform( 1, &coordinates.x, &coordinates.y) ){
        printf( "Transformation failed.\n" );
    }
    //    else
    //        printf( "(%f,%f) -> (%f,%f)\n",
    //               prevX,
    //               prevY,
    //               coordinates[1], coordinates[2]);

    return coordinates;

}

OGRCoordinateTransformation* ShapeFile::prepareToTransformCoordinates(std::string EPSG_in,std::string EPSG_out){
    OGRSpatialReference oTargetSRS;
    OGRSpatialReference oSourceSRS;
    OGRCoordinateTransformation *poCT;



    const char * EPSG_code_cc;
    EPSG_code_cc= EPSG_out.c_str();
    oTargetSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
    EPSG_code_cc= EPSG_in.c_str();
    oSourceSRS.importFromEPSG( std::atoi(EPSG_code_cc) );

    poCT = OGRCreateCoordinateTransformation( &oSourceSRS,&oTargetSRS );
    return poCT;
}


//OGRSpatialReference ShapeFile::getProjection(OGRFeature* poSRS){
//    OGRSpatialReference oSRS;
////    const char *pszWkt = OGR(poSRS);
//    //make sure its not NULL
////    OGRSpatialReferenceH hSRS;
////    oSRS = OSRNewSpatialReference(pszWkt);
//
//
//    const char *pszProjection = poSRS->GetAttrValue("PROJECTION");
//    if( pszProjection == NULL )
//    {
//        if( poSRS->IsGeographic() )
//            oSRS.SetGeogCS( szProj4+strlen(szProj4), "+proj=longlat " );
//        else
//            oSRS.SetGeogCS( szProj4+strlen(szProj4), "unknown " );
//    }
//    else if( EQUAL(pszProjection,SRS_PT_CYLINDRICAL_EQUAL_AREA) )
//    {
//        oSRS.SetGeogCS( szProj4+strlen(szProj4),
//                "+proj=cea +lon_0=%.9f +lat_ts=%.9f +x_0=%.3f +y_0=%.3f ",
//                poSRS->GetProjParm(SRS_PP_CENTRAL_MERIDIAN,0.0),
//                poSRS->GetProjParm(SRS_PP_STANDARD_PARALLEL_1,0.0),
//                poSRS->GetProjParm(SRS_PP_FALSE_EASTING,0.0),
//                poSRS->GetProjParm(SRS_PP_FALSE_NORTHING,0.0) );
//    }
//    return (oSRS);
//}




std::tuple<std::vector<std::string>, std::vector<std::vector<std::string> > > ShapeFile::readAttributeShapefile(std::string folder,std::string nameNoExtension){
    std::tuple<std::vector<std::string>, std::vector<std::vector<std::string> > > result;

    std::vector<std::vector<std::string> > fields;

 std::cout<<"folder "<<folder<<""<<nameNoExtension<<".shp"<<'\n';
    std::vector<std::string> originalIds;
    std::vector<std::string> names;
    // std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >,std::vector<std::string>  > result;

    // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
    // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol;

    // std::vector<double> xs,ys,weights;
    // std::vector<long> ids,idAs,idBs;


    // OGRSpatialReference oTargetSRS;
    // OGRSpatialReference oSourceSRS;
    // OGRCoordinateTransformation *poCT;



    // const char * EPSG_code_cc;
    // EPSG_code_cc= EPSG_out.c_str();
    // oTargetSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
    // EPSG_code_cc= EPSG_in.c_str();
    // oSourceSRS.importFromEPSG( std::atoi(EPSG_code_cc) );

    // poCT = OGRCreateCoordinateTransformation( &oSourceSRS,&oTargetSRS );

    // if( poCT == NULL ){
    //     printf( "Transformation CRS failed.\n" );
    // }else{




        ShapeFile::init();

        // OGRSpatialReference currentCRS;

        // std::unordered_map<Point2d, long> idsNodesPerCoordinates;
        // long id=1;
        // std::vector<std::string> lines;
        bool namesRead=false;

        // OGRDataSource   *poDS;
        GDALDataset   *poDS;
        std::stringstream ss;

        ss<<folder<<nameNoExtension<<".shp";

        const char * input;
        input=ss.str().c_str();

        // poDS = OGRSFDriverRegistrar::Open( input, FALSE);
        poDS =(GDALDataset*) GDALOpenEx( input, GDAL_OF_VECTOR, NULL, NULL, NULL );
        if( poDS == NULL )
        {
            std::cout<<( "Open failed.\n" );
    //        exit( 1 );
        }else{
            std::cout<<( "Open successful.\n" );
            OGRLayer  *poLayer;
            input=nameNoExtension.c_str();
            poLayer = poDS->GetLayerByName( input );
            OGRFeature *poFeature;

            poLayer->ResetReading();


            while( (poFeature = poLayer->GetNextFeature()) != NULL )
            {
                OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField;
                std::string currentID="";
                if(!namesRead){

                   for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
                    {
                    OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                        // if(names.gcount()!=0){
                        //     names<<" ";
                        // }
                        names.push_back(poFieldDefn->GetNameRef());

                    }
                    // lines.push_back(names.str());
                    fields.resize(names.size(),std::vector<std::string>());
                }

                namesRead=true;
                // std::stringstream fields;
                for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
                {
                    OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                    // char key1[]="ID";
                    // char key2[]="Id";
                    // char key3[]="id";
                    // if(fields.gcount()!=0){
                    //         fields<<" ";
                    //     }

                        fields[iField].push_back(poFeature->GetFieldAsString(iField));



                   // if(strcmp(poFieldDefn->GetNameRef(),key1)==0||strcmp(poFieldDefn->GetNameRef(),key2)==0||strcmp(poFieldDefn->GetNameRef(),key3)==0){
//                        originalIds.push_back( poFeature->GetFieldAsString(iField) );
                        // currentID=poFeature->GetFieldAsString(iField) ;
                    //}
                    if( poFieldDefn->GetType() == OFTInteger ){
        //                printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
                    }
                    else if( poFieldDefn->GetType() == OFTReal ){
        //                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
                    }
                    else if( poFieldDefn->GetType() == OFTString ){
        //                printf( "%s,", poFeature->GetFieldAsString(iField) );
                    }
                    else{
        //                printf( "%s,", poFeature->GetFieldAsString(iField) );
                    }
                }
                // lines.push_back(fields.str());
//                 OGRGeometry *poGeometry;

//                 poGeometry = poFeature->GetGeometryRef();
//                 if( poGeometry != NULL
//                    && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                 {
//     //                OGRPoint *poPoint = (OGRPoint *) poGeometry;

//         //            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                 }
//                 else if( poGeometry != NULL)
//                 {
//                     if(wkbFlatten(poGeometry->getGeometryType()) == wkbLineString){
//     //                    char** text;
//     //                    poGeometry->exportToWkt(text);
//     //                    std::cout<<text<<'\n';
//     //                    poGeometry->flattenTo2D();
//                         OGRLineString *poLine = (OGRLineString *) poGeometry;
//     //                    OGRRawPoint * points;

//                         if(poLine!=NULL){

//                             int numNode = poLine->getNumPoints();
//                             OGRPoint p;
//                             long previousId=0;
//                             for(long i = 0;  i <numNode; i++)
//                             {
//                                 poLine->getPoint((int)i, &p);
//     //                            qDebug();
// //                                ;
// //                                p.getY();
//     //                        }
//     //                        break; } case wkbMultiLineString: { OGRGeometryCollection *poCol = (OGRGeometryCollection*) geom; int numCol = poCol->getNumGeometries(); for(int i=0; inumCol; i++) { // Access line length for example : qDebug()  poCol->getGeometryRef(i)->get_Length(); } break; } default: // process error, like emit signal } // Clean-up OGRGeometryFactory::destroyGeometry(geom); }



//                                 double x=p.getX();
//                                 double y=p.getY();

//                             if( poCT == NULL || !poCT->Transform( 1, &x, &y) ){
//                                 std::cout<<"coordinates transformation for point failed";
//                             }else{






//     //                        poLine->getPoints(points);
//     //                        long numPoints=poLine->getNumPoints();

//     //                        if(points!=NULL){
//     //                            for(long i=0;i<numPoints;i++){
// //                                    std::stringstream coordsPoint;

//     //                                OGRRawPoint poPoint = points[i];


















// //                                    coordsPoint<<round(x)<<";"<<round(y);

//                                     long idNode=idsNodesPerCoordinates[Point2d(x,y)];
//                                     if(idNode==0){
//                                         idsNodesPerCoordinates[Point2d(x,y)]=id;
// //                                        std::vector<double> coordinates_temp;
// //                                        coordinates_temp.resize(3);
//                                         ids.push_back(id);
//                                         xs.push_back(x);
//                                         ys.push_back(y);
// //                                        coordinates.push_back(coordinates_temp);
//                                         idNode=id;
//                                         id++;
//                                     }
//                                     if(previousId!=0){

//                                         std::vector<double> ncol_temp;
//                                         ncol_temp.resize(3);
//                                         idAs.push_back(ids[previousId-1]-1);
//                                         idBs.push_back(ids[idNode-1]-1);
//                                         if(currentID!=""){
//                                             originalIds.push_back(currentID);
//                                         }
//                                         double weight=sqrt((xs[idNode-1]-xs[previousId-1])*(xs[idNode-1]-xs[previousId-1])+(ys[idNode-1]-ys[previousId-1])*(ys[idNode-1]-ys[previousId-1]));
//                                         if(EPSG_out=="4326"){
//                                             weight=calculateDistanceLatLon(xs[previousId-1], ys[previousId-1], xs[idNode-1], ys[idNode-1]);
//                                         }
//                                         weights.push_back(weight);
// //                                        ncol.push_back(ncol_temp);

//             //                            std::cout<< previousId<<" "<<idNode<<" "<<weight<<'\n';
//                                     }
//             //                        std::cout<< "???"<<" "<<previousId<<" "<< idNode<<'\n';
//                                     previousId=idNode;


//     //                            }
//     //                        }
//                             }
//                         }
//                         }

//                     }
//                 }else{
//         //                printf( "geometry was neither a point nor a lineString \n" );



//                 }

//                 int iGeomField;
//                 int nGeomFieldCount;

//                 nGeomFieldCount = poFeature->GetGeomFieldCount();
//                 for(iGeomField = 0; iGeomField < nGeomFieldCount; iGeomField ++ )
//                 {
//                     poGeometry = poFeature->GetGeomFieldRef(iGeomField);
//                     if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                     {
// //                        OGRPoint *poPoint = (OGRPoint *) poGeometry;

//         //                printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                     }
//                     else if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
//                     {
//                         // if(poFeature->GetGeomFieldRef(iGeomField))

//         //                printf( "no point geometry\n" );
//                     }
//                 }
                OGRFeature::DestroyFeature( poFeature );
            }
            // OGRDataSource::DestroyDataSource( poDS );
            GDALClose( poDS );
    //    ShapeFile::close();
        }
        // TextFile::writeToFile(nameFileToSave,lines,false);

        result=std::make_tuple(names,fields);
        return result;

    // }
}




void ShapeFile::readAttributeShapefileAndSaveToAFile(std::string folder,std::string nameNoExtension,std::string nameFileToSave){

    std::cout<<"folder "<<folder<<""<<nameNoExtension<<".shp"<<'\n';
    std::vector<std::string> originalIds;
    // std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >,std::vector<std::string>  > result;

    // std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
    // std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol;

    // std::vector<double> xs,ys,weights;
    // std::vector<long> ids,idAs,idBs;


    // OGRSpatialReference oTargetSRS;
    // OGRSpatialReference oSourceSRS;
    // OGRCoordinateTransformation *poCT;



    // const char * EPSG_code_cc;
    // EPSG_code_cc= EPSG_out.c_str();
    // oTargetSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
    // EPSG_code_cc= EPSG_in.c_str();
    // oSourceSRS.importFromEPSG( std::atoi(EPSG_code_cc) );

    // poCT = OGRCreateCoordinateTransformation( &oSourceSRS,&oTargetSRS );

    // if( poCT == NULL ){
    //     printf( "Transformation CRS failed.\n" );
    // }else{




        ShapeFile::init();

        // OGRSpatialReference currentCRS;

        // std::unordered_map<Point2d, long> idsNodesPerCoordinates;
        // long id=1;
        std::vector<std::string> lines;
        bool namesRead=false;

        // OGRDataSource   *poDS;
        GDALDataset   *poDS;
        std::stringstream ss;

        ss<<folder<<nameNoExtension<<".shp";

        const char * input;
        input=ss.str().c_str();

        // poDS = OGRSFDriverRegistrar::Open( input, FALSE);
        poDS =(GDALDataset*) GDALOpenEx( input, GDAL_OF_VECTOR, NULL, NULL, NULL );

        if( poDS == NULL )
        {
            std::cout<<( "Open failed.\n" );
    //        exit( 1 );
        }else{
            std::cout<<( "Open successful.\n" );
            OGRLayer  *poLayer;
            input=nameNoExtension.c_str();
            poLayer = poDS->GetLayerByName( input );
            OGRFeature *poFeature;

            poLayer->ResetReading();


            while( (poFeature = poLayer->GetNextFeature()) != NULL )
            {
                OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField;
                std::string currentID="";
                if(!namesRead){
                    std::stringstream names;
                   for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
                    {
                    OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                        if(names.gcount()!=0){
                            names<<" ";
                        }
                        names<<poFieldDefn->GetNameRef();
                    }
                    lines.push_back(names.str());
                }
                namesRead=true;
                std::stringstream fields;
                for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
                {
                    OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                    // char key1[]="ID";
                    // char key2[]="Id";
                    // char key3[]="id";
                    if(fields.gcount()!=0){
                            fields<<" ";
                        }
                        fields<<poFeature->GetFieldAsString(iField);
                   // if(strcmp(poFieldDefn->GetNameRef(),key1)==0||strcmp(poFieldDefn->GetNameRef(),key2)==0||strcmp(poFieldDefn->GetNameRef(),key3)==0){
//                        originalIds.push_back( poFeature->GetFieldAsString(iField) );
                        // currentID=poFeature->GetFieldAsString(iField) ;
                    //}
                    if( poFieldDefn->GetType() == OFTInteger ){
        //                printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
                    }
                    else if( poFieldDefn->GetType() == OFTReal ){
        //                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
                    }
                    else if( poFieldDefn->GetType() == OFTString ){
        //                printf( "%s,", poFeature->GetFieldAsString(iField) );
                    }
                    else{
        //                printf( "%s,", poFeature->GetFieldAsString(iField) );
                    }
                }
                lines.push_back(fields.str());
//                 OGRGeometry *poGeometry;

//                 poGeometry = poFeature->GetGeometryRef();
//                 if( poGeometry != NULL
//                    && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                 {
//     //                OGRPoint *poPoint = (OGRPoint *) poGeometry;

//         //            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                 }
//                 else if( poGeometry != NULL)
//                 {
//                     if(wkbFlatten(poGeometry->getGeometryType()) == wkbLineString){
//     //                    char** text;
//     //                    poGeometry->exportToWkt(text);
//     //                    std::cout<<text<<'\n';
//     //                    poGeometry->flattenTo2D();
//                         OGRLineString *poLine = (OGRLineString *) poGeometry;
//     //                    OGRRawPoint * points;

//                         if(poLine!=NULL){

//                             int numNode = poLine->getNumPoints();
//                             OGRPoint p;
//                             long previousId=0;
//                             for(long i = 0;  i <numNode; i++)
//                             {
//                                 poLine->getPoint((int)i, &p);
//     //                            qDebug();
// //                                ;
// //                                p.getY();
//     //                        }
//     //                        break; } case wkbMultiLineString: { OGRGeometryCollection *poCol = (OGRGeometryCollection*) geom; int numCol = poCol->getNumGeometries(); for(int i=0; inumCol; i++) { // Access line length for example : qDebug()  poCol->getGeometryRef(i)->get_Length(); } break; } default: // process error, like emit signal } // Clean-up OGRGeometryFactory::destroyGeometry(geom); }



//                                 double x=p.getX();
//                                 double y=p.getY();

//                             if( poCT == NULL || !poCT->Transform( 1, &x, &y) ){
//                                 std::cout<<"coordinates transformation for point failed";
//                             }else{






//     //                        poLine->getPoints(points);
//     //                        long numPoints=poLine->getNumPoints();

//     //                        if(points!=NULL){
//     //                            for(long i=0;i<numPoints;i++){
// //                                    std::stringstream coordsPoint;

//     //                                OGRRawPoint poPoint = points[i];


















// //                                    coordsPoint<<round(x)<<";"<<round(y);

//                                     long idNode=idsNodesPerCoordinates[Point2d(x,y)];
//                                     if(idNode==0){
//                                         idsNodesPerCoordinates[Point2d(x,y)]=id;
// //                                        std::vector<double> coordinates_temp;
// //                                        coordinates_temp.resize(3);
//                                         ids.push_back(id);
//                                         xs.push_back(x);
//                                         ys.push_back(y);
// //                                        coordinates.push_back(coordinates_temp);
//                                         idNode=id;
//                                         id++;
//                                     }
//                                     if(previousId!=0){

//                                         std::vector<double> ncol_temp;
//                                         ncol_temp.resize(3);
//                                         idAs.push_back(ids[previousId-1]-1);
//                                         idBs.push_back(ids[idNode-1]-1);
//                                         if(currentID!=""){
//                                             originalIds.push_back(currentID);
//                                         }
//                                         double weight=sqrt((xs[idNode-1]-xs[previousId-1])*(xs[idNode-1]-xs[previousId-1])+(ys[idNode-1]-ys[previousId-1])*(ys[idNode-1]-ys[previousId-1]));
//                                         if(EPSG_out=="4326"){
//                                             weight=calculateDistanceLatLon(xs[previousId-1], ys[previousId-1], xs[idNode-1], ys[idNode-1]);
//                                         }
//                                         weights.push_back(weight);
// //                                        ncol.push_back(ncol_temp);

//             //                            std::cout<< previousId<<" "<<idNode<<" "<<weight<<'\n';
//                                     }
//             //                        std::cout<< "???"<<" "<<previousId<<" "<< idNode<<'\n';
//                                     previousId=idNode;


//     //                            }
//     //                        }
//                             }
//                         }
//                         }

//                     }
//                 }else{
//         //                printf( "geometry was neither a point nor a lineString \n" );



//                 }

//                 int iGeomField;
//                 int nGeomFieldCount;

//                 nGeomFieldCount = poFeature->GetGeomFieldCount();
//                 for(iGeomField = 0; iGeomField < nGeomFieldCount; iGeomField ++ )
//                 {
//                     poGeometry = poFeature->GetGeomFieldRef(iGeomField);
//                     if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                     {
// //                        OGRPoint *poPoint = (OGRPoint *) poGeometry;

//         //                printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                     }
//                     else if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
//                     {
//                         // if(poFeature->GetGeomFieldRef(iGeomField))

//         //                printf( "no point geometry\n" );
//                     }
//                 }
                OGRFeature::DestroyFeature( poFeature );
            }
            // OGRDataSource::DestroyDataSource( poDS );
            GDALClose( poDS );
    //    ShapeFile::close();
        }
        TextFile::writeToFile(nameFileToSave,lines,false);
    // }

}















//
//
// std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string> ,int > ShapeFile::readShapeFile(std::string folder,std::string nameNoExtension,std::string EPSG_in,std::string EPSG_out){
//
//     std::cout<<"folder "<<folder<<""<<nameNoExtension<<".shp"<<'\n';
//
//     std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string> ,int > result;
//
//     std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
//     std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol;
//
//     std::vector<double> xs,ys,weights;
//     std::vector<long> ids,idAs,idBs;
//
//
//     OGRSpatialReference oTargetSRS;
//     OGRSpatialReference oSourceSRS;
//     OGRCoordinateTransformation *poCT;
//
//
//
//     const char * EPSG_code_cc;
//     EPSG_code_cc= EPSG_out.c_str();
//     oTargetSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
//     EPSG_code_cc= EPSG_in.c_str();
//     oSourceSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
//
//     poCT = OGRCreateCoordinateTransformation( &oSourceSRS,&oTargetSRS );
//
//     if( poCT == NULL ){
//         printf( "Transformation CRS failed.\n" );
//     }else{
//
//
//
//
//         ShapeFile::init();
//
//         OGRSpatialReference currentCRS;
//
//         std::unordered_map<Point2d, long> idsNodesPerCoordinates;
//         long id=1;
//
//
//         GDALDataset   *poDS;
//         std::stringstream ss;
//
//         ss<<folder<<nameNoExtension<<".shp";
//
//         const char * input;
//         input=ss.str().c_str();
//
//
//         poDS =(GDALDataset*) GDALOpenEx( input, GDAL_OF_VECTOR, NULL, NULL, NULL );
//
//         // poDS = OGRSFDriverRegistrar::Open( input, FALSE);
//         if( poDS == NULL )
//         {
//             std::cout<<( "Open failed.\n" );
//     //        exit( 1 );
//         }else{
//             std::cout<<( "Open successful.\n" );
//             OGRLayer  *poLayer;
//             input=nameNoExtension.c_str();
//             poLayer = poDS->GetLayerByName( input );
//             OGRFeature *poFeature;
//
//             poLayer->ResetReading();
//             while( (poFeature = poLayer->GetNextFeature()) != NULL )
//             {
//                 OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
//                 int iField;
//
//                 for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
//                 {
//                     OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
//
//                     if( poFieldDefn->GetType() == OFTInteger ){
//         //                printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
//                     }
//                     else if( poFieldDefn->GetType() == OFTReal ){
//         //                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
//                     }
//                     else if( poFieldDefn->GetType() == OFTString ){
//         //                printf( "%s,", poFeature->GetFieldAsString(iField) );
//                     }
//                     else{
//         //                printf( "%s,", poFeature->GetFieldAsString(iField) );
//                     }
//                 }
//                 OGRGeometry *poGeometry;
//
//                 poGeometry = poFeature->GetGeometryRef();
//                 if( poGeometry != NULL
//                    && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                 {
//     //                OGRPoint *poPoint = (OGRPoint *) poGeometry;
//
//         //            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                 }
//                 else if( poGeometry != NULL)
//                 {
//                     if(wkbFlatten(poGeometry->getGeometryType()) == wkbLineString){
//     //                    char** text;
//     //                    poGeometry->exportToWkt(text);
//     //                    std::cout<<text<<'\n';
//     //                    poGeometry->flattenTo2D();
//                         OGRLineString *poLine = (OGRLineString *) poGeometry;
//     //                    OGRRawPoint * points;
//
//                         if(poLine!=NULL){
//
//                             int numNode = poLine->getNumPoints();
//                             OGRPoint p;
//                             long previousId=0;
//                             for(long i = 0;  i <numNode; i++)
//                             {
//                                 poLine->getPoint((int)i, &p);
//     //                            qDebug();
// //                                ;
// //                                p.getY();
//     //                        }
//     //                        break; } case wkbMultiLineString: { OGRGeometryCollection *poCol = (OGRGeometryCollection*) geom; int numCol = poCol->getNumGeometries(); for(int i=0; inumCol; i++) { // Access line length for example : qDebug()  poCol->getGeometryRef(i)->get_Length(); } break; } default: // process error, like emit signal } // Clean-up OGRGeometryFactory::destroyGeometry(geom); }
//
//
//
//                                 double x=p.getX();
//                                 double y=p.getY();
//
//                             if( poCT == NULL || !poCT->Transform( 1, &x, &y) ){
//                                 std::cout<<"coordinates transformation for point failed";
//                             }else{
//
//
//
//
//
//
//     //                        poLine->getPoints(points);
//     //                        long numPoints=poLine->getNumPoints();
//
//     //                        if(points!=NULL){
//     //                            for(long i=0;i<numPoints;i++){
// //                                    std::stringstream coordsPoint;
//
//     //                                OGRRawPoint poPoint = points[i];
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
//
//
//
//
//
//
//
//
// //                                    coordsPoint<<round(x)<<";"<<round(y);
//
//                                     long idNode=idsNodesPerCoordinates[Point2d(x,y)];
//                                     if(idNode==0){
//                                         idsNodesPerCoordinates[Point2d(x,y)]=id;
// //                                        std::vector<double> coordinates_temp;
// //                                        coordinates_temp.resize(3);
//                                         ids.push_back(id);
//                                         xs.push_back(x);
//                                         ys.push_back(y);
// //                                        coordinates.push_back(coordinates_temp);
//                                         idNode=id;
//                                         id++;
//                                     }
//                                     if(previousId!=0){
//
//                                         std::vector<double> ncol_temp;
//                                         ncol_temp.resize(3);
//                                         idAs.push_back(ids[previousId-1]-1);
//                                         idBs.push_back(ids[idNode-1]-1);
//                                         double weight=sqrt((xs[idNode-1]-xs[previousId-1])*(xs[idNode-1]-xs[previousId-1])+(ys[idNode-1]-ys[previousId-1])*(ys[idNode-1]-ys[previousId-1]));
//                                         if(EPSG_out=="4326"){
//                                             weight=calculateDistanceLatLon(xs[previousId-1], ys[previousId-1], xs[idNode-1], ys[idNode-1]);
//                                         }
//                                         weights.push_back(weight);
// //                                        ncol.push_back(ncol_temp);
//
//             //                            std::cout<< previousId<<" "<<idNode<<" "<<weight<<'\n';
//                                     }
//             //                        std::cout<< "???"<<" "<<previousId<<" "<< idNode<<'\n';
//                                     previousId=idNode;
//
//
//     //                            }
//     //                        }
//                             }
//                         }
//                         }
//
//                     }
//                 }else{
//         //                printf( "geometry was neither a point nor a lineString \n" );
//
//
//
//                 }
//
//                 int iGeomField;
//                 int nGeomFieldCount;
//
//                 nGeomFieldCount = poFeature->GetGeomFieldCount();
//                 for(iGeomField = 0; iGeomField < nGeomFieldCount; iGeomField ++ )
//                 {
//                     poGeometry = poFeature->GetGeomFieldRef(iGeomField);
//                     if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                     {
// //                        OGRPoint *poPoint = (OGRPoint *) poGeometry;
//
//         //                printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                     }
//                     else
//                     {
//         //                printf( "no point geometry\n" );
//                     }
//                 }
//                 OGRFeature::DestroyFeature( poFeature );
//             }
//             // OGRDataSource::DestroyDataSource( poDS );
//             GDALClose( poDS );
//     //    ShapeFile::close();
//         }
//     }
//
//
//     for(long i=0;i<ids.size();i++){
//         ids[i]-=1;
//     }
//
//     coordinates=std::make_tuple(ids,xs,ys);
//
//     ncol=std::make_tuple(idAs,idBs,weights);
//
//     result.first=ncol;
//     result.second=coordinates;
//
// //    close();
//
//
//     return result;
// }


std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string>, int > ShapeFile::readShapeFile(std::string folder,std::string nameNoExtension,std::string EPSG_in,std::string EPSG_out){

    std::cout<<"folder "<<folder<<""<<nameNoExtension<<".shp"<<'\n';
    std::vector<std::string> originalIds;
    std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> >,std::vector<std::string>, int > result;

    std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > coordinates;
    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ncol;

    std::vector<double> xs,ys,weights;
    std::vector<long> ids,idAs,idBs;


    OGRSpatialReference oTargetSRS;
    OGRSpatialReference oSourceSRS;
    OGRCoordinateTransformation *poCT;
    int type=ShapeFile::TYPE_LINES;


    const char * EPSG_code_cc;
    EPSG_code_cc= EPSG_out.c_str();
    oTargetSRS.importFromEPSG( std::atoi(EPSG_code_cc) );
    EPSG_code_cc= EPSG_in.c_str();
    oSourceSRS.importFromEPSG( std::atoi(EPSG_code_cc) );

    poCT = OGRCreateCoordinateTransformation( &oSourceSRS,&oTargetSRS );

    if( poCT == NULL ){
        printf( "Transformation CRS failed.\n" );
    }else{




        ShapeFile::init();

        OGRSpatialReference currentCRS;

        std::unordered_map<Point2d, long> idsNodesPerCoordinates;
        long id=1;


        // OGRDataSource   *poDS;
                GDALDataset   *poDS;
        std::stringstream ss;

        ss<<folder<<nameNoExtension<<".shp";
        std::string ss_str=ss.str();

        char * input=new char [ss_str.length()+1];
        std::strcpy (input,ss_str.c_str());

        // poDS = OGRSFDriverRegistrar::Open( input, FALSE);
                poDS =(GDALDataset*) GDALOpenEx( input, GDAL_OF_VECTOR, NULL, NULL, NULL );

        delete[] input;
        if( poDS == NULL )
        {
            std::cout<<( "Open failed.\n" );
    //        exit( 1 );
        }else{
            std::cout<<( "Open successful.\n" );
            OGRLayer  *poLayer;
//            input=nameNoExtension.c_str();
            char * input_=new char [nameNoExtension.length()+1];
            std::strcpy (input_,nameNoExtension.c_str());
            poLayer = poDS->GetLayerByName( input_ );
            delete[] input_;
            OGRFeature *poFeature;

            poLayer->ResetReading();
            while( (poFeature = poLayer->GetNextFeature()) != NULL )
            {
                OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
                int iField;
                std::string currentID="";
                for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
                {
                    OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                    char key1[]="ID";
                    char key2[]="Id";
                    char key3[]="id";
                    char key4[]="identifier";
                    if(strcmp(poFieldDefn->GetNameRef(),key1)==0||strcmp(poFieldDefn->GetNameRef(),key2)==0||strcmp(poFieldDefn->GetNameRef(),key3)==0||strcmp(poFieldDefn->GetNameRef(),key4)==0){
//                        originalIds.push_back( poFeature->GetFieldAsString(iField) );
                        currentID=poFeature->GetFieldAsString(iField) ;
                    }
                    if( poFieldDefn->GetType() == OFTInteger ){
        //                printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
                    }
                    else if( poFieldDefn->GetType() == OFTReal ){
        //                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
                    }
                    else if( poFieldDefn->GetType() == OFTString ){
        //                printf( "%s,", poFeature->GetFieldAsString(iField) );
                    }
                    else{
        //                printf( "%s,", poFeature->GetFieldAsString(iField) );
                    }
                }
                OGRGeometry *poGeometry;

                poGeometry = poFeature->GetGeometryRef();
                if( poGeometry != NULL
                   && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
                {
                    type=ShapeFile::TYPE_POINTS;
                   OGRPoint *p = (OGRPoint *) poGeometry;
                     double x=p->getX();
                                double y=p->getY();

                            if( poCT == NULL || !poCT->Transform( 1, &x, &y) ){
                                std::cout<<"coordinates transformation for point failed";
                            }else{
                                ids.push_back(id);
                                        xs.push_back(x);
                                        ys.push_back(y);
//                                        coordinates.push_back(coordinates_temp);
//                                        idNode=id;
                                        id++;
                                        if(currentID!=""){
                                            originalIds.push_back(currentID);
                                        }
                            }
        //            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
                }
                else if( poGeometry != NULL)
                {
                    if(wkbFlatten(poGeometry->getGeometryType()) == wkbLineString){
    //                    char** text;
    //                    poGeometry->exportToWkt(text);
    //                    std::cout<<text<<'\n';
    //                    poGeometry->flattenTo2D();
                        type=ShapeFile::TYPE_LINES;
                        OGRLineString *poLine = (OGRLineString *) poGeometry;
    //                    OGRRawPoint * points;

                        if(poLine!=NULL){

                            int numNode = poLine->getNumPoints();
                            OGRPoint p;
                            long previousId=0;
                            for(long i = 0;  i <numNode; i++)
                            {
                                poLine->getPoint((int)i, &p);
    //                            qDebug();
//                                ;
//                                p.getY();
    //                        }
    //                        break; } case wkbMultiLineString: { OGRGeometryCollection *poCol = (OGRGeometryCollection*) geom; int numCol = poCol->getNumGeometries(); for(int i=0; inumCol; i++) { // Access line length for example : qDebug()  poCol->getGeometryRef(i)->get_Length(); } break; } default: // process error, like emit signal } // Clean-up OGRGeometryFactory::destroyGeometry(geom); }



                                double x=p.getX();
                                double y=p.getY();

                            if( poCT == NULL || !poCT->Transform( 1, &x, &y) ){
                                std::cout<<"coordinates transformation for point failed";
                            }else{






    //                        poLine->getPoints(points);
    //                        long numPoints=poLine->getNumPoints();

    //                        if(points!=NULL){
    //                            for(long i=0;i<numPoints;i++){
//                                    std::stringstream coordsPoint;

    //                                OGRRawPoint poPoint = points[i];


















//                                    coordsPoint<<round(x)<<";"<<round(y);

                                    long idNode=idsNodesPerCoordinates[Point2d(x,y)];
                                    if(idNode==0){
                                        idsNodesPerCoordinates[Point2d(x,y)]=id;
//                                        std::vector<double> coordinates_temp;
//                                        coordinates_temp.resize(3);
                                        ids.push_back(id);
                                        xs.push_back(x);
                                        ys.push_back(y);
//                                        coordinates.push_back(coordinates_temp);
                                        idNode=id;
                                        id++;
                                    }
                                    if(previousId!=0){

                                        std::vector<double> ncol_temp;
                                        ncol_temp.resize(3);
                                        idAs.push_back(ids[previousId-1]-1);
                                        idBs.push_back(ids[idNode-1]-1);
                                        if(currentID!=""){
                                            originalIds.push_back(currentID);
                                        }
                                        double weight=sqrt((xs[idNode-1]-xs[previousId-1])*(xs[idNode-1]-xs[previousId-1])+(ys[idNode-1]-ys[previousId-1])*(ys[idNode-1]-ys[previousId-1]));
                                        if(EPSG_out=="4326"){
                                            weight=calculateDistanceLatLon(xs[previousId-1], ys[previousId-1], xs[idNode-1], ys[idNode-1]);
                                        }
                                        weights.push_back(weight);
//                                        ncol.push_back(ncol_temp);

            //                            std::cout<< previousId<<" "<<idNode<<" "<<weight<<'\n';
                                    }
            //                        std::cout<< "???"<<" "<<previousId<<" "<< idNode<<'\n';
                                    previousId=idNode;


    //                            }
    //                        }
                            }
                        }
                        }

                    }
                }else{
        //                printf( "geometry was neither a point nor a lineString \n" );



                }

//                 int iGeomField;
//                 int nGeomFieldCount;

//                 nGeomFieldCount = poFeature->GetGeomFieldCount();
//                 for(iGeomField = 0; iGeomField < nGeomFieldCount; iGeomField ++ )
//                 {
//                     poGeometry = poFeature->GetGeomFieldRef(iGeomField);
//                     if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//                     {
// //                        OGRPoint *poPoint = (OGRPoint *) poGeometry;

//         //                printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//                     }
//                     else if( poGeometry != NULL
//                        && wkbFlatten(poGeometry->getGeometryType()) == wkbLineString )
//                     {
//                         // if(poFeature->GetGeomFieldRef(iGeomField))

//         //                printf( "no point geometry\n" );
//                     }
//                 }
                OGRFeature::DestroyFeature( poFeature );
            }
            // OGRDataSource::DestroyDataSource( poDS );
                        GDALClose( poDS );
    //    ShapeFile::close();
        }
    }


    for(long i=0;i<ids.size();i++){
        ids[i]-=1;
    }

    coordinates=std::make_tuple(ids,xs,ys);

    ncol=std::make_tuple(idAs,idBs,weights);

    // result.first=ncol;
    // result.second=coordinates;
    result=std::make_tuple(ncol,coordinates,originalIds,type);

//    close();

    return result;
}


void ShapeFile::init(){
    // OGRRegisterAll();
    GDALAllRegister();
}

//void ShapeFile::close(){
//    int n=OGRGetDriverCount();
//    for(int i=0;i<n;i++){
////        std::cout<<"number driver "<<i<<'\n';
//        OGRSFDriverH driver=OGRGetDriver (i);
//        OGRDeregisterDriver (driver);
//
//    }
//
//
//}

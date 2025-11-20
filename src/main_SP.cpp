//
//  main.cpp
//  spatialTools
//
//  Created by Carlos Molinero on 03/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include <iostream>
#include "ShapeFile.h"

int main()
{
//    ShapeFile::init();
    std::string folder="/Users/carlos/Documents/zzz_/";
    std::string nameNoExtension="example";
    std::vector<std::vector<std::vector<double> > > result=ShapeFile::readShapeFile(folder,nameNoExtension,"4326","32631");
//    ShapeFile::close();
    std::cout<<"coordinates"<<'\n';
    
    for(long i=0;i<result[0].size();i++){
        std::cout<<"coords "<<result[0][i][0]<<" "<<result[0][i][1]<<" "<<result[0][i][2]<<" "<<'\n';
    }
    
    std::cout<<"ncol"<<'\n';
    
    for(long i=0;i<result[1].size();i++){
        std::cout<<"ncolValues "<<result[1][i][0]<<" "<<result[1][i][1]<<" "<<result[1][i][2]<<" "<<'\n';
    }
    
//    std::vector<std::vector<std::vector<double> > > result;
//    
//    std::vector<std::vector<double> > coordinates;
//    std::vector<std::vector<double> > ncol;
//    
//    std::unordered_map<std::string, long> idsNodesPerCoordinates;
//    long id=1;
//    
//    
//    OGRDataSource   *poDS;
//    std::stringstream ss;
//    
//    ss<<folder<<nameNoExtension<<".shp";
//    
//    const char * input;
//    input=ss.str().c_str();
//    
//    poDS = OGRSFDriverRegistrar::Open( input, FALSE);
//    if( poDS == NULL )
//    {
//        printf( "Open failed.\n" );
//        exit( 1 );
//    }
//    OGRLayer  *poLayer;
//    input=nameNoExtension.c_str();
//    poLayer = poDS->GetLayerByName( input );
//    OGRFeature *poFeature;
//    
//    poLayer->ResetReading();
//    while( (poFeature = poLayer->GetNextFeature()) != NULL )
//    {
//        OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
//        int iField;
//        
//        for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
//        {
//            OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
//            
//            if( poFieldDefn->GetType() == OFTInteger )
//                printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
//            else if( poFieldDefn->GetType() == OFTReal )
//                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
//            else if( poFieldDefn->GetType() == OFTString )
//                printf( "%s,", poFeature->GetFieldAsString(iField) );
//            else
//                printf( "%s,", poFeature->GetFieldAsString(iField) );
//        }
//        OGRGeometry *poGeometry;
//        
//        poGeometry = poFeature->GetGeometryRef();
//        if( poGeometry != NULL
//           && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//        {
//            OGRPoint *poPoint = (OGRPoint *) poGeometry;
//            
//            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//        }
//        else
//        {
//            if(wkbFlatten(poGeometry->getGeometryType()) == wkbLineString){
//                OGRLineString *poLine = (OGRLineString *) poGeometry;
//                OGRRawPoint * points;
//                poLine->getPoints(points);
//                long numPoints=poLine->getNumPoints();
//                long previousId=0;
//                if(points!=NULL){
//                    for(long i=0;i<numPoints;i++){
//                        std::stringstream coordsPoint;
//                        
//                        OGRRawPoint poPoint = points[i];
//                        coordsPoint<<poPoint.x<<";"<<poPoint.y;
//                        
//                        long idNode=idsNodesPerCoordinates[coordsPoint.str()];
//                        if(idNode==0){
//                            idsNodesPerCoordinates[coordsPoint.str()]=id;
//                            std::vector<double> coordinates_temp;
//                            coordinates_temp.resize(3);
//                            coordinates_temp[0]=id;
//                            coordinates_temp[1]=poPoint.x;
//                            coordinates_temp[2]=poPoint.y;
//                            coordinates.push_back(coordinates_temp);
//                            idNode=id;
//                            id++;
//                        }
//                        if(previousId!=0){
//                            
//                            std::vector<double> ncol_temp;
//                            ncol_temp.resize(3);
//                            ncol_temp[0]=previousId;
//                            ncol_temp[1]=idNode;
//                            double weight=pow(pow((coordinates[idNode-1][1]-coordinates[previousId-1][1]),2)+pow((coordinates[idNode-1][2]-coordinates[previousId-1][2]),2),.5);
//                            ncol_temp[2]=weight;
//                            ncol.push_back(ncol_temp);
//                            
//                            std::cout<< previousId<<" "<<idNode<<" "<<weight<<'\n';
//                        }
//                        previousId=idNode;
//                        std::cout<< poPoint.x<<" "<< poPoint.y<<'\n';
//                        
//                    }
//                }
//                
//            }else{
//                printf( "geometry was neither a point nor a lineString \n" );
//            }
//            
//            
//        }
//        
//        int iGeomField;
//        int nGeomFieldCount;
//        
//        nGeomFieldCount = poFeature->GetGeomFieldCount();
//        for(iGeomField = 0; iGeomField < nGeomFieldCount; iGeomField ++ )
//        {
//            poGeometry = poFeature->GetGeomFieldRef(iGeomField);
//            if( poGeometry != NULL
//               && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
//            {
//                OGRPoint *poPoint = (OGRPoint *) poGeometry;
//                
//                printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
//            }
//            else
//            {
//                printf( "no point geometry\n" );
//            }
//        }
//        OGRFeature::DestroyFeature( poFeature );
//    }
//    OGRDataSource::DestroyDataSource( poDS );

    
    }


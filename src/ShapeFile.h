//
//  ShapeFile.h
//  spatialTools
//
//  Created by Carlos Molinero on 03/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef hashPoint2d
#define hashPoint2d
#include "Point2d.h"
namespace std{
template <>
struct hash<Point2d > {
public:
    size_t operator()(Point2d point) const throw() {
        //        return hash<double>()(round(point.x*Point2d::PRECISION)/Point2d::PRECISION) ^ hash<double>()(round(point.y*Point2d::PRECISION)/Point2d::PRECISION);
        return hash<double>()(point.x) ^ hash<double>()(point.y);

    }
};
}
#endif

#ifndef __spatialTools__ShapeFile__
#define __spatialTools__ShapeFile__

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <ogrsf_frmts.h>
#include <ogr_api.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Point2d.h"
#include "TextFile.h"



class ShapeFile{
public:
//    static OGRSpatialReference getProjection(OGRLayer* poSRS);
    static const int TYPE_POINTS=0;
    static const int TYPE_LINES=1;

    static double calculateDistanceLatLon(double lon1,double lat1,double lon2,double lat2);
    static double calculateDistanceLatLon(std::pair<double,double> coordinatesLonLat1,std::pair<double,double> coordinatesLonLat2);
    static double calculateDistanceLatLon(Point2d coordinatesLonLat1,Point2d coordinatesLonLat2);
//    static std::pair<double,double> transformCoordinates(std::pair<double,double> coordinates,std::string EPSG_in,std::string EPSG_out);
    static OGRCoordinateTransformation* prepareToTransformCoordinates(std::string EPSG_in,std::string EPSG_out);
    static Point2d transformCoordinates(Point2d coordinates,OGRCoordinateTransformation* poCT);
    static std::tuple<std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > ,std::tuple<std::vector<long>,std::vector<double>,std::vector<double> > ,std::vector<std::string> ,int > readShapeFile(std::string folder,std::string nameNoExtension,std::string EPSG_in,std::string EPSG_out);
    static void readAttributeShapefileAndSaveToAFile(std::string folder,std::string nameNoExtension,std::string nameFileToSave);
    static std::tuple<std::vector<std::string>, std::vector<std::vector<std::string> > > readAttributeShapefile(std::string folder,std::string nameNoExtension);
    // static void readGeoTiffDensityPeopleAndSaveResult(std::string pathFile,std::string pathOutput);
    static void init();
//    static void close();
};

#endif /* defined(__spatialTools__ShapeFile__) */

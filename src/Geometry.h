//
//  Geometry.h
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 09/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#ifndef __SpatialAnalysis__Geometry__
#define __SpatialAnalysis__Geometry__

#include <stdio.h>
#include <vector>
#include <iostream>
// #include <conio.h>
#include <math.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/algorithm.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h>
#include "SparseMatrix.h"
#include "Functions.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Filtered_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Sweep_line_2_algorithms.h>
#include "Functions.h"
#include "Point2d.h"


//#include "CGAL/Point.h"
//#include "CGAL/basic.h"
typedef CGAL::Simple_cartesian<double>    CK;
typedef CGAL::Filtered_kernel<CK>         K;
//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT FT;
typedef K::Point_2  Point;
typedef K::Segment_2  Segment;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Alpha_shape_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned long, K> Vb2;
typedef CGAL::Alpha_shape_face_base_2<K>  Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Triangulation_data_structure_2<Vb2,Fb> Tds2;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef CGAL::Delaunay_triangulation_2<K,Tds2> Delaunay;
typedef CGAL::Alpha_shape_2<Triangulation>  Alpha_shape_2;
typedef Alpha_shape_2::Alpha_shape_edges_iterator Alpha_shape_edges_iterator;


typedef K::Circle_2	Circle_2;
typedef K::Segment_2	Segment_2;
typedef K::Line_2	Line_2;
typedef K::Point_2	Point_2;
//typedef CGAL::Arr_circle_segment_traits_2<K> Traits_2;
//typedef CGAL::Arr_circle_segment_traits_2<K>::CoordNT	CoordNT;
//typedef CGAL::Arr_circle_segment_traits_2<K>::Point_2	Point_2;
//typedef CGAL::Arr_circle_segment_traits_2<K>::Curve_2	Curve_2;

//typedef CGAL::Delaunay_triangulation_2<K> Delaunay;


//enum Classification_type { EXTERIOR, SINGULAR, REGULAR, INTERIOR};

class Geometry{
public:
    static std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > calculateAlphaShape(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys,double alpha);
    static std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > delaunay(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys);
    static void intersectCurves(std::vector<Segment_2>  segments, std::pair<double, double>& interSectPoint);
    static double distancePointToSegment(Point2d start,Point2d end, Point2d point);
private:
    template <class OutputIterator>
    static void alpha_edges( const Alpha_shape_2&  A,OutputIterator out);


};

#endif /* defined(__SpatialAnalysis__Geometry__) */

//
//  Geometry.cpp
//  SpatialAnalysis
//
//  Created by Carlos Molinero on 09/04/2016.
//  Copyright (c) 2016 Carlos Molinero. All rights reserved.
//

#include "Geometry.h"

template <class OutputIterator>
void Geometry::alpha_edges( const Alpha_shape_2&  A,OutputIterator out)
{
    for(Alpha_shape_edges_iterator it =  A.alpha_shape_edges_begin();it != A.alpha_shape_edges_end();++it){
        
        Alpha_shape_2::Classification_type type;
        type=A.classify (*it, A.get_alpha());
        if(type==Alpha_shape_2::Classification_type::SINGULAR||type==Alpha_shape_2::Classification_type::REGULAR){
            *out++ = A.segment(*it);
        }
    }
}


std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > Geometry::calculateAlphaShape(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys,double alpha){
    if(alpha==0){
        alpha=2000000;
    }
    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> >  result;
    std::vector<long> idA,idB;
    std::vector<double> weights;
//    std::vector<double> x1,y1,x2,y2;
    std::vector<Point> points;
    points.resize(xs.size());
    SparseMatrix matrix;
//    double maxX=-INFINITY;
//    double maxY=-INFINITY;
//    double minX=INFINITY;
//    double minY=INFINITY;
//    
//    for(long i=0;i<xs.size();i++){
//        if(xs[i]>maxX){
//            maxX=xs[i];
//        }
//        if(ys[i]>maxY){
//            maxY=ys[i];
//        }
//        if(xs[i]<minX){
//            minX=xs[i];
//        }
//        if(ys[i]<minY){
//            minY=ys[i];
//        }
//    }
//    double width=1;
//    double EPSILON=.0000000001;
//    double numberObjectsX=((maxX-minX)/width);
//    double gridSizeX=((maxX-minX)/numberObjectsX)+EPSILON;
//    double numberObjectsY=((maxY-minY)/gridSizeX);
//    double gridSizeY=((maxY-minY)/numberObjectsY)+EPSILON;
//    
//    long numCol=floor((maxX-minX)/gridSizeX);
//    long numRow=floor((maxY-minY)/gridSizeY);
//    matrix.init(numCol, numRow);
    for(long i=0;i<xs.size();i++){
        points[i]=(Point(xs[i],ys[i]));
        long currentCol=((xs[i]));
        long currentRow=((ys[i]));
        matrix.setId(currentCol, currentRow,ids[i]);

    }
    Alpha_shape_2 A(points.begin(), points.end(),FT(alpha),Alpha_shape_2::GENERAL);
    std::vector<Segment> segments;
    alpha_edges( A, std::back_inserter(segments));
//    std::cout << "Alpha Shape computed" << std::endl;
//    std::cout << segments.size() << " alpha shape edges" << std::endl;
//    std::cout << "Optimal alpha: " << *A.find_optimal_alpha(1)<<std::endl;
    idA.resize(segments.size());
    idB.resize(segments.size());
    weights.resize(segments.size());
//    x1.resize(segments.size());
//    y1.resize(segments.size());
//    x2.resize(segments.size());
//    y2.resize(segments.size());
    for(long i=0;i<segments.size();i++){
        
        
//        x1[i]=segments[i].vertex(0).x();
//        y1[i]=segments[i].vertex(0).y();
//        x2[i]=segments[i].vertex(1).x();
//        y2[i]=segments[i].vertex(1).y();
        long currentCol=((segments[i].vertex(0).x()));
        long currentRow=((segments[i].vertex(0).y()));
        idA[i]=matrix.getId(currentCol, currentRow);
        currentCol=((segments[i].vertex(1).x()));
        currentRow=((segments[i].vertex(1).y()));
        idB[i]=matrix.getId(currentCol, currentRow);
        Point2d p1(segments[i].vertex(0).x(),segments[i].vertex(0).y());
        Point2d p2(segments[i].vertex(1).x(),segments[i].vertex(1).y());
        weights[i]=Functions::getDistance(p1, p2);
        
//        std::cout<<segments[i].vertex(0).x()<<","<<segments[i].vertex(0).y()<<" "<<segments[i].vertex(1).x()<<","<<segments[i].vertex(1).y()<<'\n';
    }
//    result.resize(3);
//    result[0]=idA;
//    result[1]=idB;
//    result[2]=weights;
    
    result=std::make_tuple(idA,idB,weights);
//    result[3]=y1;
//    result[4]=x2;
//    result[5]=y2;
    
    return result;
    
}

std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > Geometry::delaunay(std::vector<long> &ids,std::vector<double> &xs,std::vector<double> &ys){
    std::vector<Point> points;
    std::vector<unsigned long> indices;

    points.resize(xs.size());
    indices.resize(xs.size());
    for(long i=0;i<xs.size();i++){
        indices[i]=ids[i];
        points[i]=Point(xs[i],ys[i]);
    }
    std::vector<long> idAs;
    std::vector<long> idBs;
    std::vector<double> weights;
    Delaunay dt;
//    dt.insert(points.begin(),points.end());
    dt.insert( boost::make_zip_iterator(boost::make_tuple( points.begin(),indices.begin() )),boost::make_zip_iterator(boost::make_tuple( points.end(),indices.end() ) )  );
    
    for(Delaunay::Finite_edges_iterator it = dt.finite_edges_begin(); it != dt.finite_edges_end(); ++it)
    {
        Delaunay::Edge e=*it;
        long i1= e.first->vertex( (e.second+1)%3 )->info();
        long i2= e.first->vertex( (e.second+2)%3 )->info();
        idAs.push_back(i1);
        idBs.push_back(i2);
        Point2d pointA(xs[(long)i1],ys[(long)i1]);
        Point2d pointB(xs[(long)i2],ys[(long)i2]);
        double distance=Functions::getDistance(pointA, pointB);
        weights.push_back(distance);
    }
    std::tuple<std::vector<long>,std::vector<long>,std::vector<double> > result=std::make_tuple(idAs,idBs,weights);
    
    return result;
}



void Geometry::intersectCurves(std::vector<Segment_2>  segments, std::pair<double, double>& interSectPoint){
    //TODO I still need to implement this, I do not know how to create a visitor to get back which segments are intersected.
    std::vector<Point_2> pts;

    // Compute all intersection points.
    CGAL::compute_intersection_points (segments.begin(), segments.end(), std::back_inserter (pts), false);
    
    if (!pts.empty())
    {
        
    }
    
    
}




double Geometry::distancePointToSegment(Point2d start,Point2d end, Point2d point)
{
    double x1=start.x;
    double y1=start.y;
     double x2=end.x;
      double y2=end.y;
     double pointX=point.x;
      double pointY=point.y;
    double diffX = x2 - x1;
    float diffY = y2 - y1;
    if ((diffX == 0) && (diffY == 0))
    {
        diffX = pointX - x1;
        diffY = pointY - y1;
        return sqrt(diffX * diffX + diffY * diffY);
    }

    float t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / (diffX * diffX + diffY * diffY);

    if (t < 0)
    {
        //point is nearest to the first point i.e x1 and y1
        diffX = pointX - x1;
        diffY = pointY - y1;
    }
    else if (t > 1)
    {
        //point is nearest to the end point i.e x2 and y2
        diffX = pointX - x2;
        diffY = pointY - y2;
    }
    else
    {
        //if perpendicular line intersect the line segment.
        diffX = pointX - (x1 + t * diffX);
        diffY = pointY - (y1 + t * diffY);
    }

    //returning shortest distance
    return sqrt(diffX * diffX + diffY * diffY);
}


//std::vector<std::vector<long> > Geometry::voronoi(std::vector<double> xs,std::vector<double> ys){
//    std::vector<Point> points;
//    std::vector<unsigned long> indices;
//    //    indices.push_back(0);
//    //    indices.push_back(1);
//    //    indices.push_back(2);
//    //    indices.push_back(3);
//    //    indices.push_back(4);
//    //    indices.push_back(5);
//    //    load_points(points);
//    points.resize(xs.size());
//    indices.resize(xs.size());
//    for(long i=0;i<xs.size();i++){
//        indices[i]=i;
//        points[i]=Point(xs[i],ys[i]);
//    }
//    std::vector<long> idAs;
//    std::vector<long> idBs;
//    
//    Delaunay dt;
//    //    dt.insert(points.begin(),points.end());
//    dt.insert( boost::make_zip_iterator(boost::make_tuple( points.begin(),indices.begin() )),boost::make_zip_iterator(boost::make_tuple( points.end(),indices.end() ) )  );
//    
//    for(Delaunay::Finite_edges_iterator it = dt.finite_edges_begin(); it != dt.finite_edges_end(); ++it)
//    {
//        Delaunay::Edge e=*it;
//        long i1= e.first->vertex( (e.second+1)%3 )->info();
//        long i2= e.first->vertex( (e.second+2)%3 )->info();
//        idAs.push_back(i1);
//        idBs.push_back(i2);
//    }
//    std::vector<std::vector<long> > result;
//    result.push_back(idAs);
//    result.push_back(idBs);
//    
//    return result;
//}

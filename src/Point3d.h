#ifndef POINT3D_H
#define POINT3D_H

class Functions;
#include "Functions.h"



class Point3d
{
public:
//    constexpr static const double PRECISION=10000.0;
    constexpr static const double TOLERANCE=0.0;
    Point3d();
    Point3d(double x,double y);
    virtual ~Point3d();
    double x;
    double y;
    Point3d& operator = (const Point3d &point);
    bool operator()(const Point3d &comp1, const Point3d &comp2) const;
    bool operator < ( const Point3d& s ) const;
    bool operator == ( const Point3d& s ) const;
    Point3d& operator -= ( const Point3d& s ) ;
    Point3d operator - ( const Point3d &s ) const;
    //  friend Point2d operator - (const Point2d &a, const Point2d &b ){
    //
    //   Point2d c=Point2d(a.x-b.x,a.y-b.y);
    //   return c;
    //
    // }
    // Point2d operator + ( const Point2d& s ) const;
    // Point2d operator * ( const double a ) const;
protected:
private:
};



#endif // POINT3D_H

#ifndef POINT2D_H
#define POINT2D_H

class Functions;
#include "Functions.h"



class Point2d
{
public:
//    constexpr static const double PRECISION=10000.0;
    constexpr static const double TOLERANCE=0.0;
    Point2d();
    Point2d(double x,double y);
    virtual ~Point2d();
    double x;
    double y;
    Point2d& operator = (const Point2d &point);
    bool operator()(const Point2d &comp1, const Point2d &comp2) const;
    bool operator < ( const Point2d& s ) const;
    bool operator == ( const Point2d& s ) const;
    Point2d& operator -= ( const Point2d& s ) ;
    Point2d operator - ( const Point2d &s ) const;
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



#endif // POINT2D_H

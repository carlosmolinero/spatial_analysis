#include "Point2d.h"

Point2d::Point2d()
{
    //ctor
    x=0;
    y=0;

}
Point2d::Point2d(double x,double y){
    this->x=x;
    this->y=y;

}


Point2d::~Point2d()
{
    //dtor
}

Point2d& Point2d::operator = (const Point2d &point){

    this->x=point.x;
    this->y=point.y;
    return *this;
}

bool Point2d::operator()(const Point2d &comp1, const Point2d &comp2) const {
    double maxX=Functions::max(comp1.x,comp2.x);
    double maxY=Functions::max(comp1.y,comp2.y);
    double max=Functions::max(maxX,maxY);
    return (pow(2,comp1.x/max)*pow(3,comp1.y/max))<(pow(2,comp2.x/max)*pow(3,comp2.y/max));
}

bool Point2d::operator < ( const Point2d& s ) const{
    double maxX=Functions::max(x,s.x);
    double maxY=Functions::max(y,s.y);
    double max=Functions::max(maxX,maxY);
    return (pow(2,x/max)*pow(3,y/max))<(pow(2,s.x/max)*pow(3,s.y/max));
}

bool Point2d::operator == ( const Point2d& s ) const{
    return Functions::abs(x-s.x)<=TOLERANCE&&Functions::abs(y-s.y)<=TOLERANCE;
}

Point2d& Point2d::operator -= ( const Point2d& s ) {
    this->x-=s.x;
    this->y-=s.y;
    return *this;
}

Point2d Point2d::operator - ( const Point2d &s ) const{
  Point2d c=Point2d(x-s.x,y-s.y);
  return c;
}

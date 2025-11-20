#include "Point3d.h"

Point3d::Point3d()
{
    //ctor
    x=0;
    y=0;

}
Point3d::Point3d(double x,double y){
    this->x=x;
    this->y=y;

}


Point3d::~Point3d()
{
    //dtor
}

Point3d& Point3d::operator = (const Point3d &point){

    this->x=point.x;
    this->y=point.y;
    return *this;
}

bool Point3d::operator()(const Point3d &comp1, const Point3d &comp2) const {
    double maxX=Functions::max(comp1.x,comp2.x);
    double maxY=Functions::max(comp1.y,comp2.y);
    double max=Functions::max(maxX,maxY);
    return (pow(2,comp1.x/max)*pow(3,comp1.y/max))<(pow(2,comp2.x/max)*pow(3,comp2.y/max));
}

bool Point3d::operator < ( const Point3d& s ) const{
    double maxX=Functions::max(x,s.x);
    double maxY=Functions::max(y,s.y);
    double max=Functions::max(maxX,maxY);
    return (pow(2,x/max)*pow(3,y/max))<(pow(2,s.x/max)*pow(3,s.y/max));
}

bool Point3d::operator == ( const Point3d& s ) const{
    return Functions::abs(x-s.x)<=TOLERANCE&&Functions::abs(y-s.y)<=TOLERANCE;
}

Point3d& Point3d::operator -= ( const Point3d& s ) {
    this->x-=s.x;
    this->y-=s.y;
    return *this;
}

Point3d Point3d::operator - ( const Point3d &s ) const{
  Point3d c=Point3d(x-s.x,y-s.y);
  return c;
}

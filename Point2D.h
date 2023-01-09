#ifndef point_H
#define point_H
#include <iostream>
#include "Vector2D.h"

using namespace std;
class Point2D{
    //intitialize public members
    public: 
    double x;
    double y;
    Point2D();
    Point2D(double in_x,double in_y);
    
    
};
    //initialize the nonmember functions
    double GetDistanceBetween(Point2D p1, Point2D p2);
    //operator overloading
     ostream& operator<<(ostream& os, Point2D& p1);
     Point2D operator+(Point2D &p1,Vector2D &v1);
     Vector2D operator-(Point2D &p1,Point2D &p2);

#endif

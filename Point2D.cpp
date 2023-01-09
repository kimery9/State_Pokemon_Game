#ifndef point
#define point

#include <iostream>
#include <cmath>
#include "Point2D.h"
using namespace std;

     Point2D::Point2D(){//create default constructor
         x=0.0;
         y=0.0;
    }
     Point2D::Point2D(double in_x,double in_y){//create constructor
        x=in_x;
        y=in_y;
    }
    double GetDistanceBetween(Point2D p1, Point2D p2){//find distance between two points
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
    }


 ostream& operator<<(ostream& os, Point2D& p1){//overload stream operator to be able to print points
     os<<"("<<p1.x<<","<<p1.y<<")"<<endl;
   return os;
}

Point2D operator+(Point2D &p1,Vector2D &v1){//creation of addition
    return Point2D((p1.x+v1.x),(p1.y+v1.y));
}

Vector2D operator-(Point2D &p1,Point2D &p2){//creation of subtraction
    return Vector2D((p1.x-p2.x),(p1.y-p2.y));
}

#endif
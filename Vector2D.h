#ifndef vecs
#define vecs

#include <iostream>
using namespace std;
class Vector2D{//create Vector2D class
    public: //initialize public variables
    double x;
    double y;
 Vector2D();//default constructor
 Vector2D(double in_x,double in_y);

};
//operator overloading
 Vector2D operator*(Vector2D &v1, double d);

 Vector2D operator/(Vector2D &v1, double d);

 ostream& operator<<(ostream& os, Vector2D& v1);

 #endif
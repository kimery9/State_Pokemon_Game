//
// Created by kaiim on 11/22/2022.
//

#ifndef PA3_VIEW_H
#define PA3_VIEW_H
#include <iostream>
using namespace std;

const int view_maxsize = 20;

class View// create view class
{
private://initialize private members and vars
    int size;
    double scale;
    Point2D origin;
    char grid[view_maxsize][view_maxsize][2];
    bool GetSubscripts(int& out_x, int& out_y, Point2D location);

public://initialize the public members
    View();
    void Clear();
    void Plot(GameObject* );
    void Draw();

};


#endif //PA3_VIEW_H

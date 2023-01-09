
//
// Created by kaiim on 11/22/2022.
//
#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#include "View.h"


using namespace std;


bool View::GetSubscripts(int& out_x, int& out_y, Point2D location) {//calculate column and row subs
    out_x = (location.x - origin.x) / scale;
    out_y = (location.y - origin.y) / scale;
    if (out_x < size && out_y < size) {
        return true;
    }
    else {
        cout << "An object is outside the display. \n";
        return false;
    }
}

View::View() {//set size
    size = 11;
    scale = 2;
    origin = Point2D(0, 0);
}

void View::Clear() {//clear grid
    for (int i = 0; i < view_maxsize; i++) {
        for (int j = 0; j < view_maxsize; j++) {
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject* ptr) {//plot ojects
    int out_x, out_y;
    char* subs = new char[2];
    if (GetSubscripts(out_x, out_y, ptr->GetLocation())) {
        if (grid[out_x][out_y][0] == '.') {
            ptr->DrawSelf(subs);
            grid[out_x][out_y][0] = subs[0];
            grid[out_x][out_y][1] = subs[1];
        }
    }
    else {
        grid[out_x][out_y][0] = '*';
        grid[out_x][out_y][0] = ' ';
    }
    delete [] subs;
}

void View::Draw() {//draw grid array
    for (int j = size - 1; j >= -1; j--) {
        for (int i = -1; i <= size - 1; i++) {
            if (i == -1 && j % 2 == 0) {
                cout << j * 2;
                if (j / 5 == 0) {
                    cout << " ";
                }
            }
            else if (i == -1 && j % 2 != 0) {
                cout << "  ";
            }
            else if (j == -1 && i % 2 == 0) {
                cout << i * 2;
                if (i / 5 == 0) {
                    cout << " ";
                }
                cout << "  ";
            }
            if (i >= 0 && j >= 0) {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}


#include "GameObject.h"
#include <iostream>
using namespace std;

//constructors
GameObject::GameObject(char in_code) {
    display_code = in_code;
    id_num = 1;
    state = 0;
    cout << "GameObject constructed" << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code) {
    location = in_loc;
    id_num = in_id;
    display_code = in_code;
    state = 0;
    cout << "GameObject constructed" << endl;
}

//returns location of gameobject
Point2D GameObject::GetLocation() {
    return location;
}
//returns id of gameobject
int GameObject::GetId() {
    return id_num;
}
//returns state of game object
char GameObject::GetState() {
    return state;
}
//prints status of gameobjects
void GameObject::ShowStatus() {
    cout << display_code << id_num << " at " << location << endl;
}
//virtual function
bool GameObject::Update() {
    return false;
}
//virtual function
bool GameObject::ShouldBeVisible() {
    return true;
}
//destructor
GameObject::~GameObject() {
    cout << "GameObject destructed." << endl;
}
//virtual function
void GameObject::DrawSelf(char * ptr) {
    *ptr = display_code;
    *(ptr + 1) = char('0' + id_num);
}

char GameObject::GetDisplayCode() {
    return display_code;
}

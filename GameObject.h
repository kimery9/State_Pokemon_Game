#ifndef obs
#define obs
#include "Point2D.h"


class GameObject{

protected:
    Point2D location;
    int id_num;
    char display_code;
    char state;
public:
    //constructors
    GameObject(char in_code);
    GameObject(Point2D in_loc, int in_id, char in_code);
    //destructor
    virtual ~GameObject();
    //member functions
    Point2D GetLocation();
    int GetId();
    char GetState();
    char GetDisplayCode();
    virtual void ShowStatus();
    virtual bool Update();
    virtual bool ShouldBeVisible();
    void DrawSelf(char* ptr);
};
#endif
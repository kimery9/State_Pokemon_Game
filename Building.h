   #ifndef build_h
   #define build_h 

#include <iostream>
#include "GameObject.h"
using namespace std;

class Building: public GameObject//inherit from GameObject
{
    private:
    unsigned int trainer_count;

    public:
    Building();//default building constructor
// create building
   Building(Point2D in_loc, int in_id, char in_code);
    //increment trainer count
    void AddOneTrainer();
    //decrement trainer count
    void RemoveOneTrainer();
    //show status of building
    void ShowStatus();
    bool ShouldBeVisible();
};
#endif
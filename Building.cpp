   #ifndef builds
   #define builds 
#include <iostream>
#include "GameObject.h"
#include "Building.h"
using namespace std;
    
    
Building::Building(): GameObject('B'){//create default Building
        trainer_count=0;
        cout<<"Building default constructed"<<endl;
    }
// create building construtor
    Building::Building(Point2D in_loc, int in_id, char in_code):GameObject(in_loc, in_id, in_code){
        id_num=in_id;
        location=in_loc;
        display_code=in_code;
        state=0;
        trainer_count=0;
        cout<<"Building Contstructed"<<endl;
    }
    void Building::AddOneTrainer(){//increament trainer_count
        trainer_count++;
        return;
    }
    void Building::RemoveOneTrainer(){//Decreament trainer_count
    if (trainer_count>0) {//make sure not becoming negative
        trainer_count--;
    }
    else{
        trainer_count=0;
    }
        return;
    }

    void Building::ShowStatus(){//show the status of the building
        cout<<display_code<<id_num<<" located at "<<location;
        if(trainer_count==1){
            cout<<trainer_count<<" trainer is in the building "<<endl;
        }
        else{
            cout<<trainer_count<<" trainers are in the building "<<endl;
        }
        return;
    }
    bool Building::ShouldBeVisible(){
        return true;
    }
#endif
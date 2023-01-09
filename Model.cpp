//
// Created by kaiim on 11/15/2022.
//

#ifndef PA3_MODEL
#define PA3_MODEL
#include "Model.h"
#include "View.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "Trainer.h"
#include "WildPokemon.h"
using namespace std;

//constructors
Model::Model() {
    time = 0;
    count = 0;
    trainer_ptrs.push_back(new Trainer("Ash", 1, 'T', 1, Point2D(5, 1))); //creating trainers
    trainer_ptrs.push_back(new Trainer("Misty", 2, 'T', 2, Point2D(10, 1)));
    object_ptrs.push_back(trainer_ptrs[0]);
    object_ptrs.push_back(trainer_ptrs[1]);
    num_trainers = 2;

    center_ptrs.push_back(new PokemonCenter(1, 1.0, 100, Point2D(1, 20))); //creating center
    center_ptrs.push_back(new PokemonCenter(2, 2.0, 200, Point2D(10, 20)));
    object_ptrs.push_back(center_ptrs[0]);
    object_ptrs.push_back(center_ptrs[1]);
    num_centers = 2;

    gym_ptrs.push_back(new PokemonGym(10, 1, 2.0, 3, 1, Point2D(0, 0))); //creating gym
    gym_ptrs.push_back(new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5, 5)));
    object_ptrs.push_back(gym_ptrs[0]);
    object_ptrs.push_back(gym_ptrs[1]);
    num_gyms = 2;

    wildpokemon_ptrs.push_back(new WildPokemon("W1", 20.0, 20.0, false, 1, Point2D(10, 12)));
    wildpokemon_ptrs.push_back(new WildPokemon("W2", 20.0, 20.0, false, 2, Point2D(15, 5)));
    object_ptrs.push_back(wildpokemon_ptrs[0]);
    object_ptrs.push_back(wildpokemon_ptrs[1]);
    num_wildpokemon = 2;

    active_ptrs = object_ptrs;


    gameover = false;
    num_objects = 8;
    num_trainers = 2;
    num_centers = 2;
    num_gyms = 2;
    num_wildpokemon = 2;
    cout << "Model Default constructed" << endl;
}
//destructor
Model::~Model() {
    for (int i = 0; i < num_objects; i++)
    {
        delete object_ptrs[i];
    }
    cout << "Model destructed" << endl;
}
//function that returns all trainer pointers
Trainer* Model::GetTrainerPtr(int id) { //index to get respective called trainer
    int index;
    bool latch = false;

    try {
        for (int i = 0; i < num_trainers; i++) {
            if (trainer_ptrs[i]->GetId() == id) {
                index = i;
                latch = true;
                break;
            }
        }
        if (!(latch)) {
            Invalid_Input inva("No matching Trainer ID");
            throw inva;
        }
        else {
            return trainer_ptrs[index];
        }
    }
    catch (Invalid_Input inva) {
        cout << "ERROR: " << inva.msg_ptr << endl;
        return NULL;
    }

}

PokemonCenter* Model::GetPokemonCenterPtr(int id) { //index to get respective called pokemon center
    int index;
    bool latch = false;
    try {
        for (int i = 0; i < num_centers; i++) {
            if (center_ptrs[i]->GetId() == id) {
                index = i;
                latch = true;
                break;
            }
        }
        if (!(latch)) {
            Invalid_Input inva("No matching Pokemon Center ID");
            throw inva;
        }
        else {
            return center_ptrs[index];
        }
    }
    catch (Invalid_Input inva) {
        cout << "ERROR: " << inva.msg_ptr << endl;
        return NULL;
    }
}

PokemonGym* Model::GetPokemonGymPtr(int id) { //index to get respective called pokemon gym
    int index;
    bool latch = false;
    try {
        for (int i = 0; i < num_gyms; i++) {
            if (gym_ptrs[i]->GetId() == id) {
                index = i;
                latch = true;
                break;
            }
        }
        if (!(latch)) {
            Invalid_Input inva("No matching Pokemon Gym ID");
            throw inva;
        }
        else {
            return gym_ptrs[index];
        }
    }
    catch (Invalid_Input inva) {
        cout << "ERROR: " << inva.msg_ptr << endl;
        return NULL;
    }
}

WildPokemon* Model::GetWildPokemonPtr(int id) {
    int index;
    bool latch = false;
    try {
        for (int i = 0; i < num_wildpokemon; i++) {
            if (wildpokemon_ptrs[i]->GetId() == id) {
                index = i;
                latch = true;
                break;
            }
        }
        if (!(latch)) {
            Invalid_Input inva("No matching Wild Pokemon ID");
            throw inva;
        }
        else {
            return wildpokemon_ptrs[index];
        }
    }
    catch (Invalid_Input inva) {
        cout << "ERROR: " << inva.msg_ptr << endl;
        return NULL;
    }
}


//function that updates the model after actions have been done
bool Model::Update() {
    time++;
    bool UpdateSuccess = false;
    //check for successful update
    for (int i = 0; i < num_objects; i++)
    {
        if (object_ptrs[i]->Update())
        {
            UpdateSuccess = true;
        }
    }
    for (int i = 0; i < num_wildpokemon; i++) {
        if (wildpokemon_ptrs[i]->GetState() == 2) {
            wildpokemon_ptrs[i]->updateLocation();
        }
    }
    //Check if won
    unsigned int total_battles = gym_ptrs[0]->GetNumBattlesRemaining();
    for (int i = 1; i < num_gyms; i++)
    {
        total_battles += gym_ptrs[i]->GetNumBattlesRemaining();
    }
    if (total_battles == 0)
    {
        cout << "GAME OVER: You win! All battles done!" << endl;
        gameover = true;
        GameOver();
        return  true;
    }
    for (int i = 0; i < num_trainers; i++) {
        for (int j = 0; j < num_wildpokemon; j++) {
            if (fabs(wildpokemon_ptrs[j]->GetLocation().x) == fabs(trainer_ptrs[i]->GetLocation().x) && fabs(wildpokemon_ptrs[j]->GetLocation().y) == fabs(trainer_ptrs[i]->GetLocation().y)) {
                wildpokemon_ptrs[j]->follow(trainer_ptrs[i]);
            }
        }
    }
    //Check if lost
    bool AllTrainersFainted = true;
    for (int i = 0; i < num_trainers; i++)
    {
        AllTrainersFainted = AllTrainersFainted && trainer_ptrs[i]->HasFainted();
    }
    if (AllTrainersFainted)
    {

        cout << "GAME OVER: You lose! All of your Trainers and pokemon have fainted!" << endl;

        gameover = true;
        GameOver();
        return true;
    }


    return UpdateSuccess;
}
//returns the game over variable - true when games over
bool Model::GameOver() {
    return gameover;
}
//sets up the grid
void Model::Display(View& view) {
    view.Clear();

    for (int i = 0; i < num_trainers; i++)
    {
        if (trainer_ptrs[i]->ShouldBeVisible())
        {
            view.Plot(trainer_ptrs[i]);
        }
    }

    for (int i = 0; i < num_gyms; i++)
    {
        view.Plot(gym_ptrs[i]);
    }

    for (int i = 0; i < num_centers; i++)
    {
        view.Plot(center_ptrs[i]);
    }
    for (int i = 0; i < num_wildpokemon; i++) {
        view.Plot(wildpokemon_ptrs[i]);
    }
    view.Draw();
    cout << "Time: " << time;

}
//shows the status of the model
void Model::ShowStatus() {
    cout << "Time: " << time << endl;

    for (int i = 0; i < num_objects; i++)
    {
        object_ptrs[i]->ShowStatus();
    }
}

void Model::NewCommand(char type, int in_id, Point2D in_loc) {

    switch (type) {
        case 'c': case 'C':
            try {
                for (int i = 0; i < num_centers; i++) { //checks to see if ID is currently use
                    if (center_ptrs[i]->GetId() == in_id) {
                        Invalid_Input inva("ID already in use");
                        throw inva;
                    }
                }
                if (in_id < 0 || in_id > 9) {
                    Invalid_Input inva("ID must be 0 through 9");
                    throw inva;
                }
                for (int i = 0; i < num_objects; i++) {
                    if (object_ptrs[i]->GetLocation().x == in_loc.x && object_ptrs[i]->GetLocation().y == in_loc.y) {
                        Invalid_Input inva("Location is already in use");
                        throw inva;
                    }
                }
                center_ptrs.push_back(new PokemonCenter(in_id, 5, 100, in_loc)); //creating of that new center if it meats the requirements
                PokemonGym* gPtr = NULL;
                for (int i = 0; i < num_objects; i++) { //inserting objects in the right are to follow format
                    gPtr = dynamic_cast<PokemonGym*>(object_ptrs[i]);
                    if (gPtr != NULL) {
                        object_ptrs.insert(object_ptrs.begin() + i, center_ptrs[num_centers]);
                        break;
                    }
                }
                active_ptrs.push_back(center_ptrs[num_centers]);
                num_centers++;
                num_objects++;
            }
            catch (Invalid_Input inva) {
                cout << "Error: " << inva.msg_ptr << endl;
            }
            break;
        case 'g': case 'G':

            try {
                for (int i = 0; i < num_gyms; i++) { //checks to see if ID is currently use
                    if (gym_ptrs[i]->GetId() == in_id) {
                        Invalid_Input inva("ID already in use");
                        throw inva;
                    }
                }
                if (in_id < 0 || in_id > 9) {
                    Invalid_Input inva("ID must be 0 through 9");
                    throw inva;
                }
                for (int i = 0; i < num_objects; i++) {
                    if (object_ptrs[i]->GetLocation().x == in_loc.x && object_ptrs[i]->GetLocation().y == in_loc.y) {
                        Invalid_Input inva("Location is already in use");
                        throw inva;
                    }
                }
                gym_ptrs.push_back(new PokemonGym(10, 1, 1.0, 2, in_id, in_loc));
                WildPokemon* wpPtr = NULL;
                for (int i = 0; i < num_objects; i++) {
                    wpPtr = dynamic_cast<WildPokemon*>(object_ptrs[i]);
                    if (wpPtr != NULL) {
                        object_ptrs.insert(object_ptrs.begin() + i, gym_ptrs[num_gyms]);
                        break;
                    }
                }
                active_ptrs.push_back(gym_ptrs[num_gyms]);
                num_gyms++;
                num_objects++;
            }
            catch (Invalid_Input inva) {
                cout << "Error: " << inva.msg_ptr << endl;
            }
            break;
        case 't': case 'T':
            try {
                for (int i = 0; i < num_trainers; i++) { //checks to see if ID is currently use
                    if (trainer_ptrs[i]->GetId() == in_id) {
                        Invalid_Input inva("ID already in use");
                        throw inva;
                    }
                }
                if (in_id < 0 || in_id > 9) {
                    Invalid_Input inva("ID must be 0 through 9");
                    throw inva;
                }
                for (int i = 0; i < num_objects; i++) {
                    if (object_ptrs[i]->GetLocation().x == in_loc.x && object_ptrs[i]->GetLocation().y == in_loc.y) {
                        Invalid_Input inva("Location is already in use");
                        throw inva;
                    }
                }
                stringstream strs; //since the contructor requires a name we created one that can be used
                strs << "Trainer" << in_id; //Creates a defualy name with id so we can differenciate
                trainer_ptrs.push_back(new Trainer(strs.str(), in_id, 'T', 5, in_loc));
                PokemonCenter* cPtr = NULL;
                for (int i = 0; i < num_objects; i++) {
                    cPtr = dynamic_cast<PokemonCenter*>(object_ptrs[i]);
                    if (cPtr != NULL) {
                        object_ptrs.insert(object_ptrs.begin() + i, trainer_ptrs[num_trainers]);
                        break;
                    }
                }
                active_ptrs.push_back(trainer_ptrs[num_trainers]);
                num_trainers++;
                num_objects++;
            }
            catch (Invalid_Input inva) {
                cout << "Error: " << inva.msg_ptr << endl;
            }
            break;
        case 'w': case 'W':
            try {
                for (int i = 0; i < num_wildpokemon; i++) { //checks to see if ID is currently use
                    if (wildpokemon_ptrs[i]->GetId() == in_id) {
                        Invalid_Input inva("ID already in use");
                        throw inva;
                    }
                }
                if (in_id < 0 || in_id > 9) {
                    Invalid_Input inva("ID must be 0 through 9");
                    throw inva;
                }
                for (int i = 0; i < num_objects; i++) {
                    if (object_ptrs[i]->GetLocation().x == in_loc.x && object_ptrs[i]->GetLocation().y == in_loc.y) {
                        Invalid_Input inva("Location is already in use");
                        throw inva;
                    }
                }
                stringstream strs; //since the contructor requires a name we created one that can be used
                strs << "WildPokemon" << in_id; //Creates a defualy name with id so we can differenciate
                wildpokemon_ptrs.push_back(new WildPokemon(strs.str(), 5.0, 2.0, false, in_id, in_loc));
                object_ptrs.push_back(wildpokemon_ptrs[num_wildpokemon]);
                active_ptrs.push_back(wildpokemon_ptrs[num_wildpokemon]);
                num_wildpokemon++;
                num_objects++;
            }
            catch (Invalid_Input inva) {
                cout << "Error: " << inva.msg_ptr << endl;
            }
            break;
    }
}

#endif
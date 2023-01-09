#ifndef Trainer_cpp
 #define Trainer_cpp
#include "Trainer.h"
#include "GameObject.h"
#include <iostream>
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include <math.h>
using namespace std;

//constructors
Trainer::Trainer() : GameObject('T') {
    is_at_center = false;
    is_IN_GYM = false;
    health = 1000;
    experience = 0;
    PokeDollars = 1000;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_gym = nullptr;
    current_center = nullptr;
    speed = 5;
    cout << "Trainer default constructed";
}
Trainer::Trainer(char in_code) : GameObject(in_code) {
    is_at_center = false;
    is_IN_GYM = false;
    health = 1000;
    experience = 0;
    PokeDollars = 1000;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_gym = nullptr;
    current_center = nullptr;
    speed = 5;
    state = STOPPED;
    display_code = in_code;
    cout << "Trainer constructed" << endl;
}
Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc,in_id,in_code) {
    is_at_center = false;
    is_IN_GYM = false;
    health = 1000;
    experience = 0;
    PokeDollars = 1000;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_gym = nullptr;
    current_center = nullptr;
    speed = in_speed;
    name = in_name;
    cout << "Trainer constructed" << endl;
}
//destructor
Trainer::~Trainer() {
    cout << "Trainer destructed" << endl;
}
//function to modify the location based on delta
void Trainer::StartMoving(Point2D dest) {

    //check to see if youre already there
    if (location.x == dest.x && location.y == dest.y) {
        cout << display_code << id_num << ": I'm already there. See?" << endl;
    }
        //check to see if the pokemon have fainted
    else if (health == 0) {
        cout << display_code << id_num << ": My pokemon have fainted. I may move but you cannot see me. " << endl;
    }
    else {
        cout << display_code << id_num << ": On my way!" << endl;
        state = MOVING;
        SetupDestination(dest);
    }

}
void Trainer::followedByWildPokemon(int attack) {
    health = health - attack;
}
//function to set the destination as the gym
void Trainer::StartMovingToGym(PokemonGym* gym) {

    if (location.x == gym->GetLocation().x && location.y == gym->GetLocation().y) {
        cout << display_code << id_num << ": I'm already at the Pokemon Gym!" << endl;
    }
    else if (health == 0) {
        cout << display_code << id_num << ": My pokemon have fainted. I may move but you cannot see me. " << endl;
    }
    else {
        cout << display_code << id_num << ": on my way to gym " << gym->GetId() << endl;
        current_gym = gym;
        SetupDestination(gym->GetLocation());
        state = MOVING_TO_GYM;
    }
}
//function to set the destination as the pokemon center
void Trainer::StartMovingToCenter(PokemonCenter* center) {

    if (location.x == center->GetLocation().x && location.y == center->GetLocation().y) {
        cout << display_code << id_num << ": I'm already at the Pokemon Center!" << endl;
    }
    else if (health == 0) {
        cout << display_code << id_num << ": My pokemon have fainted. I may move but you cannot see me. " << endl;
    }
    else {
        cout << display_code << id_num << ": on my way to center " << center->GetId() << endl;
        current_center = center;
        SetupDestination(center->GetLocation());
        state = MOVING_TO_CENTER;
    }
}
//function that commences battling and makes sure that all constraints are met
void Trainer::StartBattling(unsigned int num_battles) {
    if (health < current_gym->GetHealthCost(num_battles)) {
        cout << display_code << id_num << ": my Pokemon have fainted so no more battles for me!" << endl;
    }
    else if (location.x != current_gym->GetLocation().x || location.y != current_gym->GetLocation().y) {
        cout << display_code << id_num << ": I can only battle in a Pokemon Gym!" << endl;
    }
    else if (PokeDollars < current_gym->GetPokeDollarCost(num_battles)) {
        cout << display_code << id_num << ": Not enough money for battles." << endl;
    }
    else if (current_gym->GetNumBattlesRemaining() == 0) {
        cout << display_code << id_num << ": Cannot battle! This Pokemon Gym has no more trainers!" << endl;
    }
    else {
        state = BATTLING_IN_GYM;
        cout << display_code << id_num << " started to battle at the Pokemon Gym " << current_gym->GetId() << " with " << num_battles << " battles." << endl;
        battles_to_buy = num_battles;

    }

}
//start recovering health function for when inside of a center
void Trainer::StartRecoveringHealth(unsigned int num_potions) {
    if (!current_center->CanAffordPotion(num_potions,PokeDollars)) {
        cout << display_code << id_num << ": Not enough money to start recovery." << endl;
    }
    else if (current_center->GetNumPotionRemaining() == 0) {
        cout << display_code << id_num << ": Cannot recover! No potion remaining in this Pokemon Center." << endl;
    }
    else if (location.x != current_center->GetLocation().x || location.y != current_center->GetLocation().y) {
        cout << display_code << id_num << ": I can only recover health at a Pokemon Center!" << endl;
    }
    else if (num_potions > current_center->GetNumPotionRemaining()) {
        num_potions = current_center->GetNumPotionRemaining();
    }
    else {
        state = RECOVERING_HEALTH;
        cout << display_code << id_num << "Started recovering " << num_potions << " potions at Pokemon Center " << current_center->GetId() << endl;
        potions_to_buy = num_potions;
        health = health + 5 * num_potions;
        PokeDollars = PokeDollars - current_center->GetPokeDollarCost(num_potions);
        current_center->DistributePotion(num_potions);

    }

}
//returns the name of the trainer
string Trainer::GetName() {
    return name;
}
//stops the trainers movement to their current destination
void Trainer::Stop() {
    state = STOPPED;
    cout << display_code << id_num << ": Stopping..." << endl;
}
//checks to see if the trainer has fainted
bool Trainer::HasFainted() {
    if (health == 0) {
        return true;
    }
    else {
        return false;
    }
}
//checks if the trainer has fainted
bool Trainer::ShouldBeVisible() {
    if (health > 0) {
        return true;
    }
    else {
        return false;
    }
}
//shows the status of the trainer
void Trainer::ShowStatus() {
    cout << endl << name << " status: ";
    GameObject::ShowStatus();
    switch (state) {
        case STOPPED:
            cout << "Stopped" << endl;
            break;
        case MOVING:
            cout << "Moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
            break;
        case MOVING_TO_GYM:
            cout << "Heading to PokemonGym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        case MOVING_TO_CENTER:
            cout << "Heading to PokemonCenter " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        case IN_GYM:
            cout << "Inside PokemonGym " << current_gym->GetId() << endl;
            break;
        case AT_CENTER:
            cout << "Inside PokemonCenter " << current_center->GetId() << endl;
            break;
        case BATTLING_IN_GYM:
            cout << "Battling in PokemonGym " << current_gym->GetId() << endl;
            break;
        case RECOVERING_HEALTH:
            cout << "Recovering health in PokemonCenter " << current_center->GetId() << endl;
            break;
    }
    cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
}
//updates the trainer after an action is performed
bool Trainer::Update() {
    if (health == 0) {
        cout << name << " is out of health and can't move!" << endl;
        state = FAINTED;
        return false;
    }
    else
    {
        switch (state) {
            case STOPPED:
                Trainer::ShowStatus();
                return false;
            case MOVING:
                UpdateLocation();
                Trainer::ShowStatus();
                if (location.x == destination.x && location.y == destination.y) {
                    state = STOPPED;
                    return true;
                }
                else {
                    return false;
                }

                break;
            case MOVING_TO_GYM:
                UpdateLocation();
                Trainer::ShowStatus();
                if (location.x == destination.x && location.y == destination.y) {
                    state = IN_GYM;
                    is_IN_GYM = true;
                    current_gym->AddOneTrainer();

                    return true;
                }
                else {
                    return false;
                }
                break;
            case MOVING_TO_CENTER:
                UpdateLocation();
                Trainer::ShowStatus();
                if (location.x == destination.x && location.y == destination.y) {
                    state = AT_CENTER;
                    is_at_center = true;
                    current_center->AddOneTrainer();
                    return true;
                }
                else {
                    return false;
                }
                break;
            case IN_GYM:
                Trainer::ShowStatus();
                return false;
                break;
            case AT_CENTER:
                Trainer::ShowStatus();
                return false;
                break;
            case BATTLING_IN_GYM:
                Trainer::ShowStatus();
                health = health - current_gym->GetHealthCost(battles_to_buy);
                PokeDollars = PokeDollars - current_gym->GetPokeDollarCost(battles_to_buy);
                experience = current_gym->TrainPokemon(battles_to_buy);
                cout << "** " << name << " completed " << battles_to_buy << " battle(s)!**";
                cout << "** " << name << " gained " << (current_gym->GetExperiencePerBattle() * battles_to_buy) << " experience!**";
                state = IN_GYM;
                return true;
                break;
            case RECOVERING_HEALTH:
                Trainer::ShowStatus();
                StartRecoveringHealth(potions_to_buy);
                health = health + potions_to_buy * 5;
                PokeDollars = PokeDollars - current_center->GetPokeDollarCost(potions_to_buy);
                cout << "** " << name << " recovered " << (potions_to_buy * 5) << " health!**";
                cout << "** " << name << " bought " << potions_to_buy << " potion(s)!**";
                state = AT_CENTER;
                return true;
                break;
        }
    }
}
//updates the location after taking a step of delta
bool Trainer::UpdateLocation() {
    health = health - 1;
    PokeDollars = PokeDollars + GetRandomAmountOfPokeDollars();
    if (is_IN_GYM) {
        current_gym->RemoveOneTrainer();
        is_IN_GYM = false;
    }
    if (is_at_center) {
        current_center->RemoveOneTrainer();
        is_at_center = false;
    }
    if (fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y)) {
        cout << display_code << id_num << ": I'm there!";
        location = destination;
        return true;
    }
    else {
        location = location + delta;
        cout << endl << display_code << id_num << ": step..." << endl;
        return false;
    }
}
//determines delta based on the location and destination
void Trainer::SetupDestination(Point2D dest){//set up destination and calc delta
    destination=dest;
    Point2D Loco=GetLocation();
    Vector2D diff=(dest-Loco);
    delta=(diff)*(speed/ GetDistanceBetween(dest,Loco));
}
//get a random amount between 0 and 2
double GetRandomAmountOfPokeDollars() {
    srand(time(0));
    double num = rand() % 2;
    return num;
}
     #endif
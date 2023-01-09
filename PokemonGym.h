#ifndef pokegym_h
#define pokegym_h

#include <iostream>
#include "Building.h"
#include "GameObject.h"

using namespace std;

enum PokemonGymStates {
NOT_DEFEATED = 0,
DEFEATED = 1
};

class PokemonGym: public Building{//inherit from building
private: //initialize the private variables
unsigned int num_battle_remaining;
unsigned int max_number_of_battles;
unsigned int health_cost_per_battle;
double PokeDollar_cost_per_battle;
unsigned int experience_per_battle;

public://initalize the public member functions
PokemonGym();
PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc);
~PokemonGym();
double GetPokeDollarCost(unsigned int battle_qty);
unsigned int GetHealthCost(unsigned int battle_qty);
unsigned int GetNumBattlesRemaining();
bool IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health);
unsigned int TrainPokemon(unsigned int battle_units);
unsigned int GetExperiencePerBattle();
bool Update();
bool passed();
void ShowStatus();


};

#endif
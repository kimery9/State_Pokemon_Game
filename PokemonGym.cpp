#ifndef pokemongym
#define pokemongym
#include <iostream>
#include "Building.h"
#include "GameObject.h"
#include "PokemonGym.h"
#include "Point2D.h"
using namespace std;



PokemonGym::PokemonGym(): Building(){//create the default Gym
    display_code='G';
    state=NOT_DEFEATED;
    max_number_of_battles=10;
    num_battle_remaining=max_number_of_battles;
    health_cost_per_battle=1;
    PokeDollar_cost_per_battle=1.0;
    experience_per_battle=2;
    cout<<"PokemonGym default constructed"<<endl;
}
PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc): Building(in_loc,in_id,'G')//TODO help
{
    display_code='G';
    id_num=in_id;
    max_number_of_battles=max_battle;
    health_cost_per_battle=health_loss;
    experience_per_battle=exp_per_battle;
    PokeDollar_cost_per_battle=PokeDollar_cost;
    location=in_loc;
    num_battle_remaining=max_number_of_battles;//is this correct??
    health_cost_per_battle=1;

}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty){//get cost of gym
    return((PokeDollar_cost_per_battle*battle_qty));
}
unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty){//get health cost
    return((health_cost_per_battle*battle_qty));
}
unsigned int PokemonGym::GetNumBattlesRemaining(){
    return(num_battle_remaining);
}
bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health){//check if the trainer can battle
    if(budget>=(PokeDollar_cost_per_battle*battle_qty) && (health>=(health_cost_per_battle*battle_qty))){
        return true;
    }
    else{
        return false;
    }
}
unsigned int PokemonGym::TrainPokemon(unsigned int battle_units){//update the amount of battles on gym
    if(num_battle_remaining>=battle_units){
        num_battle_remaining=num_battle_remaining-battle_units;
        return(experience_per_battle*battle_units);
    }
    else{
        return(experience_per_battle*num_battle_remaining);
    }

}
unsigned int PokemonGym::GetExperiencePerBattle(){//get XP per battle
    return(experience_per_battle);
}
bool PokemonGym::Update(){//update the id and state of the GYM
    if(num_battle_remaining==0 && display_code!='g'){
        state=DEFEATED;
        display_code='g';
        cout<<display_code<<" "<<id_num<<" has been beaten"<<endl;
        return true;
    }
    else if(display_code=='g'){
        return false;
    }
    else{
        return false;
    }
}
bool PokemonGym::passed(){//check if the gym has been passed
    if(num_battle_remaining==0){
    return true;
    }
    else{
        return false;
    }
}
void PokemonGym::ShowStatus(){//print the status of the gym
        cout<<endl<<"PokemonGym Status: "<<endl;
        Building::ShowStatus();
        cout<<"Max number of battles "<<max_number_of_battles<<endl;
        cout<<"Health cost per battle: "<<health_cost_per_battle<<endl;
        cout<<"PokeDollar per battle "<<PokeDollar_cost_per_battle<<endl;
        cout<<"Expierence per battle "<<experience_per_battle<<endl;
        cout<<num_battle_remaining<<" battle(s) are remaining for this PokemonGym"<<endl;

}

PokemonGym::~PokemonGym(){//destruct the gym
cout<<"PokemonGym destructed."<<endl;
};


#endif
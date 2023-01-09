#ifndef pokecenter
#define pokecenter
#include <iostream>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"


PokemonCenter::PokemonCenter(): Building(){//create default center
        display_code='C';
        potion_capacity=100;
        num_potions_remaining=potion_capacity;
        pokedollar_cost_per_potion=5;
        state=POTIONS_AVAILABLE;
        cout<<"PokemonCenter default constructed"<<endl;
    }

    PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc): Building(in_loc,in_id,'C')
    {
        display_code='C';
        id_num=in_id;
        location=in_loc;
        pokedollar_cost_per_potion=potion_cost;
        potion_capacity=potion_cap;
        num_potions_remaining=potion_capacity;
        state=POTIONS_AVAILABLE;
        cout<<"PokemonCenter Constructed"<<endl;
    }

    bool PokemonCenter::HasPotions(){//check if there are still potions in the center
        if(state==POTIONS_AVAILABLE){
            return true;
        }
        else{
            return false;
        }
    }

    unsigned int PokemonCenter::GetNumPotionRemaining(){//return number of remaining potions
        return num_potions_remaining;
    }

    bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget){//check if the trainer can afford the amount he wants to buy
        if(budget>=(potion*pokedollar_cost_per_potion)){
            return true;
        }
        else{
            return false;
        }
    }
    double PokemonCenter::GetPokeDollarCost(unsigned int potion){//get cost
        return (pokedollar_cost_per_potion*potion);
    }

    unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed){//update the potions in the center
        if(num_potions_remaining>=potion_needed){
            num_potions_remaining=num_potions_remaining-potion_needed;
            return potion_needed;
        }
        else{
            unsigned int out_potion=num_potions_remaining;
            num_potions_remaining=0;
            return out_potion;
        }
    }

    bool PokemonCenter::Update(){//Update the code and state of the center
        if(num_potions_remaining==0 && display_code!='c'){
            state=NO_POTIONS_AVAILABLE;
            display_code='c';
            cout<<"PokemonCenter "<<id_num<<" has ran out of potions"<<endl;
            return true;
        }
        else if (display_code=='c'){
            return false;
        }
        else{
            return false;
        }
    }

    void PokemonCenter::ShowStatus(){//print the status of the center
        cout<<endl<<"PokemonCenter Status: "<<endl;
        Building::ShowStatus();
        cout<<"PokeDollars per potion: "<<pokedollar_cost_per_potion<<endl;
        cout<<"has "<<num_potions_remaining<<" potion(s) remaining"<<endl;

    }
    PokemonCenter::~PokemonCenter() {//destruct the center
        cout<<"PokemonCenter destructed."<<endl;
    }
#endif
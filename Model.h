//
// Created by kaiim on 11/15/2022.
//
//
#ifndef PA3_MODEL_H
#define PA3_MODEL_H
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <list>
#include "WildPokemon.h"
#include "Input_Handling.h"
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
class Model {
private:
    bool gameover;
    int time;
    int count;
    vector<GameObject*> object_ptrs;
    vector<GameObject*> active_ptrs;
    int num_objects;
    vector<Trainer*> trainer_ptrs;
    int num_trainers;
    vector<PokemonCenter*> center_ptrs;
    int num_centers;
    vector<PokemonGym*> gym_ptrs;
    int num_gyms;
    vector<WildPokemon*> wildpokemon_ptrs;
    int num_wildpokemon;
public:
    //constructor
    Model();
    //destructor
    ~Model();
    //member functions
    Trainer* GetTrainerPtr(int id);
    PokemonCenter* GetPokemonCenterPtr(int id);
    PokemonGym* GetPokemonGymPtr(int id);
    WildPokemon* GetWildPokemonPtr(int id);
    bool GameOver();
    bool Update();
    void Display(View& view);
    void ShowStatus();
    virtual void NewCommand(char type, int in_id, Point2D in_loc);
};

#endif
//
// Created by kaiim on 12/10/2022.
//

#ifndef PA3_WILDPOKEMON_H
#define PA3_WILDPOKEMON_H

#include "GameObject.h"
#include "Trainer.h"
#include "Point2D.h"


class WildPokemon : public GameObject {
    enum WildPokemonStates {
        IN_ENVIRONMENT = 0,
        DEAD = 1,
        IN_TRAINER = 2
    };

protected:
    double attack;
    double health;
    bool variant;
    bool in_combat;
    string name;
    Trainer* current_trainer;

public:
    WildPokemon(string name_in, double attack_in, double health_in, bool variant_in, int id_in, Point2D in_loc);

    void follow(Trainer* t);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool Update();
    void ShowStatus();
    bool IsAlive();
    Trainer* getTrainer();
    void updateLocation();
};
#endif //PA3_WILDPOKEMON_H

//
// Created by kaiim on 12/10/2022.
#include "WildPokemon.h"

//constructor
WildPokemon::WildPokemon(string name_in, double attack_in, double health_in, bool variant_in, int id_in, Point2D in_loc) : GameObject('W') {
    name = name_in;
    attack = attack_in;
    health = health_in;
    variant = variant_in;
    id_num = id_in;
    in_combat = false;
    location = in_loc;
    state = IN_ENVIRONMENT;
}

Trainer* WildPokemon::getTrainer() {
    return current_trainer;
}

void WildPokemon::updateLocation() {
    location.x = current_trainer->GetLocation().x;
    location.y = current_trainer->GetLocation().y;
}


void WildPokemon::follow(Trainer* t) {
    state = IN_TRAINER;
    current_trainer = t;
    current_trainer->followedByWildPokemon(attack);

}

bool WildPokemon::get_variant() {
    return variant;
}

double WildPokemon::get_attack() {
    return attack;
}

double WildPokemon::get_health() {
    return health;
}

bool WildPokemon::get_in_combat() {
    return in_combat;
}

bool WildPokemon::Update() {
    if (state == IN_ENVIRONMENT) {
        ShowStatus();
        return false;
    }

    if (health == 0) {
        state = DEAD;
        ShowStatus();
    }
    if (state == IN_TRAINER) {
        ShowStatus();
        return false;
    }
}

void WildPokemon::ShowStatus() {
    if (state == IN_ENVIRONMENT) {
        cout <<name << " is in environment with " << health << " health" << endl;
    }
    else if (state == DEAD) {
        cout << name << " is out of health and has died!" << endl;
    }
    else {
        cout << name << " is following " << current_trainer->GetName() << endl;
    }
}

bool WildPokemon::IsAlive() {
    if (state == DEAD) {
        return false;
    }
    else {
        return true;
    }
}



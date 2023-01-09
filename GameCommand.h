//
// Created by kaiim on 11/22/2022.
//

#ifndef PA3_GAMECOMMAND_H
#define PA3_GAMECOMMAND_H
#include "Model.h"
#include "View.h"
#include "Input_Handling.h"
#include <sstream>
#include <limits>
//global variable
extern bool hasquit;

//functions for each of the game commands
void DoCommands(Model&, View&);
void DoMoveCommand(Model& model, int trainer_id, Point2D p1);
void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id);
void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id);
void DoStopCommand(Model& model, int trainer_id);
void DoBattleCommand(Model& model, int trainer_id, unsigned int battles);
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed);
void DoAdvanceCommand(Model& model, View& view);
void DoRunCommand(Model& model, View& view);
void DoQuit(Model* model);

#endif //PA3_GAMECOMMAND_H

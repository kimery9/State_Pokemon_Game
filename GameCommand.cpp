//
// Created by kaiim on 11/22/2022.
//
#include "Model.h"
#include "View.h"
#include "Trainer.h"
#include "GameCommand.h"

void DoCommands(Model& model, View& view) {
    char command, type;
    int id1, id2, x, y;
    unsigned int battles, potions_needs;

    model.ShowStatus();
    view.Clear();
    model.Display(view);

    cout << "Enter command: ";

    while (true) { //this is used to error check the inputs instead of doing each one individually
        cin >> command;
        switch (command) {
            case 'm': case 'M':
                try {
                    if (cin >> id1 >> x >> y) { //echos the user order input of m 1 10 15
                        DoMoveCommand(model, id1, Point2D(x, y));
                        view.Clear();
                        model.Display(view);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (id, X, Y)");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "ERROR: " << inva.msg_ptr << endl;
                }
                break;
            case 'c': case 'C':
                try {
                    if (cin >> id1 >> id2) {
                        DoMoveToCenterCommand(model, id1, id2);
                        view.Clear();
                        model.Display(view);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (id1, id2)");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "ERROR: " << inva.msg_ptr << endl;
                }
                break;
            case 'g': case 'G':
                try {
                    if (cin >> id1 >> id2) {
                        DoMoveToGymCommand(model, id1, id2);
                        view.Clear();
                        model.Display(view);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (id1, id2)");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "ERROR: " << inva.msg_ptr << endl;
                }
                break;
            case 's': case 'S':
                try {
                    if (cin >> id1) {
                        DoStopCommand(model, id1);
                        view.Clear();
                        model.Display(view);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (id)");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "Error: " << inva.msg_ptr << endl;
                }
                break;
            case 'p': case 'P':
                try {
                    if ((cin >> id1 >> potions_needs) && potions_needs > 0) {
                        DoRecoverInCenterCommand(model, id1, potions_needs);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (id, potions_needed) & potions_needed > 0");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "Error: " << inva.msg_ptr << endl;
                }
                break;
            case 'b': case 'B':
                try {
                    if ((cin >> id1 >> battles) && battles > 0)
                    {
                        DoBattleCommand(model, id1, battles);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (id, battles) & battles > 0");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "Error: " << inva.msg_ptr << endl;
                }
                break;
            case 'a': case 'A':
                DoAdvanceCommand(model, view);
                break;
            case 'r': case 'R':
                DoRunCommand(model, view);
                break;
            case 'n': case 'N':
                try {
                    if (cin >> type >> id1 >> x >> y)
                    {
                        model.NewCommand(type, id1, Point2D(x, y));
                        view.Clear();
                        model.Display(view);
                    }
                    else
                    {
                        Invalid_Input inva("Invalid parameters (type, id1, X, Y)");
                        throw inva;
                    }
                }
                catch (Invalid_Input inva) {
                    cout << "Error: " << inva.msg_ptr << endl;
                }
            case 'q': case 'Q':
                exit(0);
                break;
            default:
                cout << "Error: Please enter a valid command!" << endl;
        }
        cin.clear(); //clears extra inputs that arent needed
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores everything else of the same line then skips to the next
        cout << "Enter command: ";
    }
}


//this command sets the destination that the trainer wants to move to
void DoMoveCommand(Model& model, int trainer_id, Point2D p1) {
    Trainer* t = model.GetTrainerPtr(trainer_id);
    if (t == 0 || p1.x > 20 || p1.y > 20)
    {
        cout << "Error: Please enter valid command!" << endl;
    }
    else
    {
        t->StartMoving(p1);
        cout << "Moving " << t->GetName() << " to " << p1 << endl;
    }

}
//this command sets the destination as whichever center they specify
void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id) {
    Trainer* t = model.GetTrainerPtr(trainer_id);
    PokemonCenter* c = model.GetPokemonCenterPtr(center_id);
    if (t == nullptr || c == nullptr)
    {
        cout << "Error: Please enter valid command!" << endl;
    }
    else
    {
        t->StartMovingToCenter(c);
        cout << "Moving " << t->GetName() << " to pokemon center " << c->GetId() << endl;
    }
}
//this command sets the destination as whichever gym they specify
void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id) {
    Trainer* t = model.GetTrainerPtr(trainer_id);
    PokemonGym* g = model.GetPokemonGymPtr(gym_id);
    if (t == nullptr || g == nullptr)
    {
        cout << "Error: Please enter valid command!" << endl;
    }
    else
    {
        t->StartMovingToGym(g);
        cout << "Moving " << t->GetName() << " to gym " << g->GetId() << endl;
    }
}
//this command resets the current destination
void DoStopCommand(Model& model, int trainer_id) {
    Trainer* t = model.GetTrainerPtr(trainer_id);
    if (t == 0)
    {
        cout << "Error: Please enter valid command!" << endl;
    }
    else
    {
        t->Stop();
        cout << "Stopping " << t->GetName() << endl;
    }
}
//this command initates a battle by accepting an input of how many battles want to be done
void DoBattleCommand(Model& model, int trainer_id, unsigned int battles) {
    Trainer* t = model.GetTrainerPtr(trainer_id);
    if (t == 0)
    {
        cout << "Error: Please enter valid command!" << endl;
    }
    else
    {

        t->StartBattling(battles);
        cout << t->GetName() << " is battling" << endl;
    }
}
//this command starts the recovery for the trainer based on amount of potions
void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed) {
    Trainer* t = model.GetTrainerPtr(trainer_id);
    if (t == 0)
    {
        cout << "Error: Please enter valid command!" << endl;
    }
    else
    {
        t->StartRecoveringHealth(potions_needed);
        cout << "Recovering " << t->GetName() << "'s Pokemon's health" << endl;
    }
}
//this command moves forward one clock cycle
void DoAdvanceCommand(Model& model, View& view) {
    cout << "Advancing one tick" << endl;
}
//this command moves forward five clock cycles
void DoRunCommand(Model& model, View& view) {
    cout << "Advancing to next event" << endl;
}
//this command ends the program and deconstructs all of the objects
void DoQuit(Model* model) {
    cout << "Quitting program...";
    hasquit = false;
    delete model;
}


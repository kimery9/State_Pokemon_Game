#include <iostream>
#include <string.h>
#include "Point2D.h"
#include "Vector2D.h"
#include <math.h>
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "View.h"
#include "Model.h"
#include "GameCommand.h"
using namespace std;

string *separateCommands(string, int &);

bool hasquit = true;

int main() {


    //Game
    Model *model = new Model;
    View *view = new View;
    model->ShowStatus();
    model->Display(*view);
    Point2D loc_n;

    if(model->GameOver()) {//check if game over
        DoQuit(model);
        return 0;
    }

    do {
        if (model->GameOver()) {
            DoQuit(model);
            return 0;
        }
            string input;
            cout << "Enter command: ";
            getline(cin, input);

            int numCommands = 0;
            string *commands = separateCommands(input, numCommands);
            if (commands == 0) {
                continue;
            }
       // DoCommands(*model,*view);

            switch (commands[0][0]) {//check for valid and case input
                case'n':

                    loc_n.x=stoi(commands[3]);
                    loc_n.y=stoi(commands[4]);
                    model->NewCommand(commands[1][0], stoi(commands[2]),loc_n);
                    break;
                case 'm':
                    if (numCommands != 3) {
                        cout << "Error: Please enter valid command!" << endl;
                        break;
                    }

                   DoMoveCommand(*model, stoi(commands[1]), Point2D(stod(commands[2]), stod(commands[3])));
                    break;

                case 'c':
                    if (numCommands != 2) {
                        cout << "Error: Please enter valid command!" << endl;
                        break;
                    }
                    DoMoveToCenterCommand(*model, stoi(commands[1]), stoi(commands[2]));
                    break;

                case 'g':
                    if (numCommands != 2) {
                        cout << "Error: Please enter valid command!" << endl;
                        break;
                    }
                    DoMoveToGymCommand(*model, stoi(commands[1]), stoi(commands[2]));
                    break;

                case 's':
                    if (numCommands != 1) {
                        cout << "Error: Please enter valid command!" << endl;
                        break;
                    }
                    DoStopCommand(*model, stoi(commands[1]));
                    break;

                case 'p':
                    if (numCommands != 2) {
                        cout << "Error: Please enter valid command!" << endl;
                        break;
                    }
                    DoRecoverInCenterCommand(*model, stoi(commands[1]), stoi(commands[2]));
                    break;

                case 'b':
                    if (numCommands != 2) {
                        cout << "Error: Please enter valid command!" << endl;
                        break;
                    }
                    DoBattleCommand(*model, stoi(commands[1]), stoi(commands[2]));
                    break;

                case 'a':
                    cout << "Advancing one tick" << endl;//TODO
                    DoAdvanceCommand(*model, *view);
                    model->Update();
                    break;

                case 'r':
                    cout << "Advancing to the next event" << endl;//TODO
                    for (int i = 0; i < 5; i++) {
                        if (model->Update()) {
                            break;
                        }
                    }
                    break;
                case 'q':
                    DoQuit(model);
                    return 0;
                    break;

                default:
                    break;
            }

            if (hasquit) {
                model->ShowStatus();
                model->Display(*view);//TODO view
            }

        }
        while (hasquit);

        return 0;
    }


    string *separateCommands(string input, int &count)//separate the input into appropriate strings
    {
        string *output = new string[6];

        string word = "";
        for (auto x : input)
        {
            if (count == 6)
            {
                cout << "Error: Please enter valid command!" << endl;
                return 0;
            }

            if (x == ' ')
            {
                output[count] = word;
                word = "";
                count++;
            }
            else
            {
                word = word + x;
            }
        }
        output[count] = word;

        return output;
    }

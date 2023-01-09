//
// Created by kaiim on 12/12/2022.
//

#ifndef PA3_INPUT_HANDLING_H
#define PA3_INPUT_HANDLING_H

#include <iostream>
#include <string>

using namespace std;

class Invalid_Input {
public:
    Invalid_Input(string in_ptr) : msg_ptr(in_ptr) {}

    const string msg_ptr;

private:
    Invalid_Input();
};


#endif //PA3_INPUT_HANDLING_H

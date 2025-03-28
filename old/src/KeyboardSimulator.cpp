#include <unistd.h>
#include <iostream>
#include <string>

#include "KeyboardSimulator.hpp"


void KeyboardSimulator::simulateKeyPress(std::string key){
    std::string keyCode; 
    if (key == "\n"){
        keyCode = "Return";
    }
    else if (key == " ")
    {
        keyCode = "space";
    }
    else {
        keyCode = key;
    }
    std::string cmd = "ydotool type "+keyCode+"\n"; 

    system(cmd.c_str());

}
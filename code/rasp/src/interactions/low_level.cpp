#include "low_level.hpp"
#include <cstdlib>
#include <iostream>

LowLevel::LowLevel() {
    std::system("gpio -g mode 17 in");
    std::system("gpio -g mode 17 up");

    std::system("gpio -g mode 26 in");
    std::system("gpio -g mode 26 up");

    std::system("gpio -g mode 27 in");
    std::system("gpio -g mode 27 up");

    std::system("gpio -g mode 5 in");
    std::system("gpio -g mode 5 up");

    std::system("gpio -g mode 11 in");
    std::system("gpio -g mode 11 up");

}

LowLevel::~LowLevel() {

}


bool LowLevel::is_depart()
{
    return std::system("gpio -g read 27");
}


bool LowLevel::is_equipe_bleu()
{
    int back=std::system("gpio -g read 17");
    if (back==1) {
        std::system("gpio -g mode 26 1");
    }
    return back;
}


bool LowLevel::phare_active()
{
    return std::system("gpio -g read 5");
}


bool LowLevel::boussole_nord()
{
    return std::system("gpio -g read 11");
}

//-------- PRIVATE ---------

int LowLevel::setup() {
//TODO init input and outputs
    return 0;
}

void LowLevel::set_mode() {

}

void LowLevel::write() {

}

void LowLevel::read() {

}

//TODO send_command()

#include "low_level.hpp"

LowLevel::LowLevel() {
    int input_pins[] = {TEAM_SWITCH_INPUT, GO_INPUT, PHARE_INPUT, NORD_INPUT};
    int output_pins[] = {TEAM_LED_OUTPUT};
}

LowLevel::~LowLevel() {

}


bool LowLevel::is_depart();


bool LowLevel::is_equipe_bleu();


bool LowLevel::phare_active();


bool LowLevel::boussole_nord();

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

#include "low_level.hpp"
#include <cstdlib>
#include <iostream>

LowLevel::LowLevel() {
    std::system("gpio -g mode 17 in");
    std::system("gpio -g mode 17 up");

    std::system("gpio -g mode 26 out");

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
    FILE *f = popen("gpio -g read 27", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    pclose(f);
    return ret[0]=='1';
}


bool LowLevel::is_equipe_bleu()
{
    FILE *f = popen("gpio -g read 17", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    if (ret[0]=='1') {
        std::system("gpio -g write 26 1");
    }
    else {
        std::system("gpio -g write 26 0");
    }
    pclose(f);
    return ret[0]=='1';
}


bool LowLevel::phare_active()
{
    FILE *f = popen("gpio -g read 5", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    pclose(f);
    return ret[0]=='1';

}


bool LowLevel::boussole_nord()
{
    FILE *f = popen("gpio -g read 11", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    pclose(f);
    return ret[0]=='1';
}


//TODO send_command()

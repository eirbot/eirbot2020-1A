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
    FILE *f = popen("gpio -g read 27", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    printf("%c \n",ret[0]);
    if (ret[0]=='1') {
        return true;
    }
    else{
        return false;
    }
    pclose(f);
}


bool LowLevel::is_equipe_bleu()
{
    FILE *f = popen("gpio -g read 17", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    printf("%c \n",ret[0]);
    if (ret[0]=='1') {
        std::system("gpio -g mode 26 1");
    }

    if (ret[0]=='1') {
        return true;
    }
    else{
        return false;
    }
    pclose(f);
}


bool LowLevel::phare_active()
{
    FILE *f = popen("gpio -g read 5", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    printf("%c \n",ret[0]);
    if (ret[0]=='1') {
        return true;
    }
    else{
        return false;
    }
    pclose(f);

}


bool LowLevel::boussole_nord()
{
    FILE *f = popen("gpio -g read 11", "r");
    char ret[512] = {0};
    fgets(ret,512,f);
    printf("%c \n",ret[0]);
    if (ret[0]=='1') {
        return true;
    }
    else{
        return false;
    }
    pclose(f);
}


//TODO send_command()

//
// Created by CopperBot on 16/01/2020.
//
#include "mbed.h"
#include "Protocole_nucleo.hpp"
#include "asserv.hpp"

// Protocole protocole=Protocole();

Serial pc(D1,D0);

volatile char c = '\0'; // Initialized to the NULL character


void conCharReceived(void)
{
  c=pc.getc();
}

int main()
{
  init_asserv();
  pc.attach(&conCharReceived);

  while(1) {
    set_pwm();
  }
}

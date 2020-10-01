//
// Created by CopperBot on 16/01/2020.
//
#include "mbed.h"
#include "Protocole_nucleo.hpp"
#include "asserv.hpp"

// Protocole protocole=Protocole();

Serial pc(D1,D0);
// Serial pc(USBTX, USBRX);

volatile char c = '\0'; // Initialized to the NULL character


void conCharReceived(void)
{
  c=pc.getc();
  set_consigne(c);
  pc.printf("OK!\n\r");
}

int main()
{
  pc.printf("Hello ! \n\r");
  init_asserv();
  pc.attach(&conCharReceived);

  while(1) {
    set_pwm();
    print_debug_asserv(pc,c);
  }
}

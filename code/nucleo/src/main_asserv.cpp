//
// Created by CopperBot on 16/01/2020.
//
#include "mbed.h"

#include "asserv.hpp"

// #include "Protocole_nucleo.hpp"
// Protocole protocole=Protocole();

// Serial pc(USBTX, USBRX);
Serial pc(D1, D0);
volatile char c = '\0'; // Initialized to the NULL character

void conCharReceived(void)
{
  c=pc.getc();
  set_consigne(c);
}

int main()
{
  pc.printf("Hello ! \n\r");
  init_asserv();
  pc.attach(&conCharReceived, Serial::RxIrq);
  while(1) {
    // set_pwm(); //essayer de déplacer ça dans fonction_asserv
    print_debug_asserv(pc,c);
    wait_us(500000);
  }
}

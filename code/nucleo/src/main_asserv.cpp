#include "mbed.h"

#include "asserv.hpp"
#include "actionneur_nucleo.hpp"
#include "detection_nucleo.hpp"

#include "Protocole_nucleo.hpp"

Protocole protocole=Protocole();

// Serial pc(USBTX, USBRX);
// Serial pc(D1, D0);

// volatile char c = '\0'; // Initialized to the NULL character

// void conCharReceived(void)
// {
//   c=pc.getc();
//   set_consigne(c);
// }

int main()
{
  //pc.printf("Hello ! \n\r");
  init_bras_pwm();
  desactivate_pavillon();
  init_asserv();
  //pc.attach(&conCharReceived, Serial::RxIrq);
  while(1) {
    protocole.update_state();
    GP2_update(true);
    //print_debug_asserv(pc,c);
    //wait_us(100000);
  }
}

#include "mbed.h"

Serial pc(USBTX, USBRX); // tx, rx

AnalogIn gp2_gauche(A0);
AnalogIn gp2_centre(A1);
AnalogIn gp2_droite(A2);

// float mean(float *sample, int index) {
//     return sample[];
// }


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    float g_sample[8];
    float c_sample[8];
    float d_sample[8];

    int i = 0;

    while (true) {
        g_sample[i] = gp2_gauche.read();
        c_sample[i] = gp2_centre.read();
        d_sample[i] = gp2_droite.read();

        i++;

        if(i >= 8) {
            i = 0;

        }

        wait(0.05f);
    }
}

#include "mbed.h"

Serial pc(USBTX, USBRX); // tx, rx

AnalogIn gp2_gauche(A0);
AnalogIn gp2_centre(A1);
AnalogIn gp2_droite(A2);

AnalogIn lof_GP2[3] = {gp2_gauche, gp2_centre, gp2_droite};


DigitalIn contactor(A3);
// float mean(float *sample, int index) {
//     return sample[];
// }

#define MAX_DISTANCE 10

/*GP2 delivers an output voltage approximated to be linearly linked with
1/x, x the distance in cm

Thus, g_output = a/x + b  with x fluctuating between 0 and 10 cm

*/

int is_close( float gp2_output, int contactor, float d_close = MAX_DISTANCE/2 , float d_max = MAX_DISTANCE, int  a = 20, int b = 0 )
{
  int max_v = a/d_max + b;
  int medium_v = a/d_close + b;

  if(contactor)
  {
    return 1;
  }
  else if(gp2_output > max_v)
  {
    return 2;
  }
  else if(gp2_output > medium_v)
  {
    return 3;
  }
  else
  {
    return 0;
  }


}


int gp2_read(int contactor, AnalogIn GP2[] = lof_GP2, int n = 3)
{
  float GP2_out[n];
  for(int i=0; i< n; i++)
  {
    GP2_out[i] = lof_GP2[i].read();
  }

  for( int i=0; i < n; i++)
  {
    int is_c = is_close(GP2_out[i], contactor);
    if(is_c >0)
      return is_c;
  }

  return 0;

}




int main()
{
  while(true)
  {
    //int cntc = contactor.read();
    int cntc = 0;
    printf("%d",gp2_read(cntc));


  }
}

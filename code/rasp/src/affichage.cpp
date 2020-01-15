#include "affichage.hpp"
using namespace std;

extern int unoptimized;
extern int total_deplacement;
extern int success_deplacement;
extern int total_obstacles;
extern int total_reach;
extern int success_reach;
extern int timeout;


void print_timeout()
{
    printf("\033[31m TIMEOUT \033[0m \n");
}

void print_fail()
{
    printf("\033[31m FAILED \033[0m \n");
}


void print_success()
{
    printf("\033[32m SUCCESS \033[0m \n");
}

void print_optimisated()
{
  unoptimized+=1;
  printf("\033[33m UNOPTIMISED \033[0m ");
}

void affichage(int timeout)
{
  if(timeout==1){
    timeout+=1;
    print_timeout();
    }
  else{
    success_deplacement+=1;
    print_success();
    }
}

void good_port(short result_x, short result_y, short dest_x, short dest_y)
{
  printf("Test sur la concordance de l'arrivée et de la position ... ");
  if(result_x==dest_x && result_y==dest_y){
    success_reach+=1;
      print_success();
    }
  else{
      print_fail();
    }
}

void print_summarise()
{
  printf("___________________________________________________________________\n");
  printf("___________________________________________________________________\n");
  if (debug == 1) {
    printf("Trajectory");
    print_optimisated();
    printf(" .................................  (%d/%d) \n", unoptimized - 1, success_deplacement);
  }
  printf("Go_to");
  printf("     \033[32m SUCCESS \033[0m ......................................  (%d/%d) \n", success_deplacement, success_deplacement+timeout);
  printf("Go_to");
  printf("     \033[31m TIMEOUT \033[0m ......................................  (%d/%d) \n", timeout, success_deplacement+timeout);
  printf("Reach");
  printf("     \033[32m SUCCESS \033[0m ......................................  (%d/%d) \n", success_reach, total_reach);
  printf("___________________________________________________________________\n");
  printf("___________________________________________________________________\n");

}

#include "affichage.hpp"
using namespace std;

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
  printf("\033[33m UNOPTIMISED \033[0m ");
}

void affichage(int timeout)
{
    if(timeout==1){
        print_timeout();
    }
    else{
        print_success();
    }
}

void good_port(short result_x, short result_y, short dest_x, short dest_y)
{
  printf("Test sur la concordance de l'arrivée et de la position ... ");
  if(result_x==dest_x && result_y==dest_y){
      print_success();
    }
    else{
      print_fail();
    }
}

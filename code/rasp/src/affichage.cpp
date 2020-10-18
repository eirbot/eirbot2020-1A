#include "affichage.hpp"
using namespace std;

extern int unoptimized;
extern int total_deplacement;
extern int success_deplacement;
extern int total_obstacles;
extern int total_reach;
extern int success_reach;
extern int timeout;
extern int robot_adv;
class Navigation;

extern int timeout_after_timeout;
void print_timeout()
{
  timeout_after_timeout+=1;
  if (timeout_after_timeout>=100) {
    print_summarise();
    exit(EXIT_FAILURE);
  }
    printf("\033[31m TIMEOUT \033[0m \n");
}

void print_fail()
{
    printf("\033[31m FAILED \033[0m \n");
}


void print_success()
{
  timeout_after_timeout=0;
  printf("\033[32m SUCCESS \033[0m \n");
}

void print_optimisated()
{
  unoptimized+=1;
  printf("\033[33m UNOPTIMISED \033[0m ");
}

void print_detection()
{
  robot_adv+=1;
  printf(".......................................................... \033[31m OBSTACLE \033[0m \n");
}

void print_panic()
{
  printf("\033[31m PANIC \033[0m \n");
}

void affichage(int asserv_back)
{
  if(asserv_back==1){
    timeout+=1;
    print_timeout();
  }
  if(asserv_back==2){
    print_detection();
    }
  if(asserv_back==0){
    success_deplacement+=1;
    print_success();
  }
  if(asserv_back==3){
    print_panic();
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
  printf("Robots");
  printf("    \033[31m OBSTACLE \033[0m .....................................  (%2d)    \n", robot_adv);
  printf("___________________________________________________________________\n");
  printf("___________________________________________________________________\n");

}

#include "test.hpp"
using namespace std;

#include "test_navigation.hpp"
#include "test_asserv.hpp"
#include "test_detection.hpp"
#include "test_actionneur.hpp"
#include "test_protocole.hpp"
#include "test_ecocup.hpp"
#include "test_robot.hpp"

class Protocole Protocole("/dev/ttyS0");

bool debug=false;
vector<Node> debugPath(2);
int total_optimized;
int unoptimized;
int total_deplacement;
int success_deplacement;
int total_reach;
int success_reach;
int timeout;
int robot_adv;
int timeout_after_timeout;
int which_side=0;


int main(int argc, char *argv[]) {
  test_navigation();
  test_asserv();
  test_detection();
  test_actionneur();
  test_protocole(argc,argv);
  test_ecocup();
  test_robot();
}

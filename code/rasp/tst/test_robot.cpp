#include "test_robot.hpp"
#include <time.h>

void test_robot()
{
    TEST_BEGIN;
    Robot Robot;
    // Node src = {16,80,0,0,0,0,0};
    // Node dest= {80,80,0,0,0,0,0};
    // assert(Robot.dimension.width==32 && Robot.dimension.length==32);

    // Robot.calibration();

    // vector<obstacle> list_obstacles;
    // list_obstacles=fillVector();
    // Robot.move(src, dest, list_obstacles);
    // assert(dest.x==dest.x && dest.y==dest.y);

    // short angle = Robot.angle_robot();
    // Robot.rotation(0);
    // assert(angle == Robot.angle_robot());

    // Robot.detection('a','1');

    // Robot.actionneur(1,1);
    Robot.setup_score();
    Robot.set_score(120);
    TEST_END;
}

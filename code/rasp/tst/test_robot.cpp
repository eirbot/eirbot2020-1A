#include "test_robot.hpp"

void test_robot()
{
    TEST_BEGIN;
    Robot Robot;
    Node src = {23,184,0,0,0,0,0};
    assert(Robot.dimension.width==32 && Robot.dimension.length==32);

    Robot.calibration();

    struct position position=Robot.position();
    position.x=30;
    position.y=16;
    Node dest ={(short) position.x,(short) position.y,0,0,0,0,0};

    vector<obstacle> list_obstacles;
    list_obstacles=fillVector();
    Robot.move(src, dest, list_obstacles);
    assert(dest.x==dest.x && dest.y==dest.y);

    short angle = Robot.angle_robot();
    Robot.rotation(0);
    assert(angle == Robot.angle_robot());

    Robot.detection('a','1');

    Robot.actionneur(1,1);

    //Robot.pavillon(1);

    //Robot.pince(1);
    TEST_END;
}

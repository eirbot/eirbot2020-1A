#include "test_protocole.hpp"
#include <unistd.h>

int main(int argc, char *argv[]) {
    char etats[3];
    if(argc > 1) {
        Protocole proto(argv[1]);

        usleep(100000); //0.1s

        printf("Set GP2 on\n");
        proto.set_detection_GP2(1);
        //usleep(100000); //0.1s
        printf("=================================\n");

        printf("Set Position\n");
        proto.set_position(10, 10, etats, 1);
        //usleep(100000); //0.1s
        printf("ANGLE:\n");
        printf("=================================\n");

        printf("Set angle\n");
        proto.set_angle(90);
        //usleep(100000); //0.1s
        printf("=================================\n");

        struct position pos;
        printf("Get Position\n");
        proto.get_position(&pos);
        //usleep(100000); //0.1s
        printf("=================================\n");

        short int angle;
        printf("Get angle\n");
        proto.get_angle(&angle);
        //usleep(100000); //0.1s
        printf("=================================\n");

        printf("Get etats\n");
        char etats_GP2[3];
        proto.get_etats_GP2(etats_GP2);
        //usleep(100000); //0.1s
        printf("=================================\n");
    }
    else {
        printf("Usage : ./test_protocole [port serie]\n");

    }
}

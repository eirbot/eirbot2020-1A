#include "test_protocole.hpp"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc > 1) {
        Protocole proto(argv[1]);

        usleep(500000); //0.5s

        proto.get_position();
        usleep(500000); //0.5s
        proto.update_buffer();

/*        proto.set_position(10, 10);
        usleep(500000); //0.5s
        proto.update_buffer();

        proto.set_angle(90);
        usleep(500000); //0.5s
        proto.update_buffer();

        proto.get_angle();
        usleep(500000); //0.5s
        proto.update_buffer();

        proto.get_etats_GP2();
        usleep(500000); //0.5s
        proto.update_buffer();

        proto.set_seuils_GP2('0','0',30);
        usleep(500000); //0.5s
        proto.update_buffer();*/
    }
    else {
        printf("Usage : ./test_protocole [port serie]\n");

    }
}

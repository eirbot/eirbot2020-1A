#include "test_protocole.hpp"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc > 1) {
        Protocole proto(argv[1]);
        proto.set_position(10, 10);
        proto.get_position();
        proto.set_angle(90);
        proto.get_angle();
        proto.get_etats_GP2();
        proto.set_seuils_GP2('0','0',30);
        sleep(5);
        proto.update_buffer();
    }
    else {
        printf("Usage : ./test_protocole [port serie]\n");

    }
}

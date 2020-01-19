#include "test_protocole.hpp"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        Protocole proto(argv[1]);
        proto.set_position(10, 10);
    }
    else {
        printf("Usage : ./test_protocole [port serie]\n");

    }
}

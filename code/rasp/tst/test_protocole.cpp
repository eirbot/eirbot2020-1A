#include "test_protocole.hpp"
#include <unistd.h>

// class Protocole proto("/dev/ttyACM0");

void message_retour(Protocole::Etat etat) {
        switch(etat) {
                case Protocole::Etat::OK:
                        printf("\033[32m OK \033[0m\n");
                        break;
                case Protocole::Etat::TIME_OUT:
                        printf("\033[33m TIMEOUT \033[0m\n");
                        break;
                case Protocole::Etat::ERROR:
                        printf("\033[31m ERROR \033[0m\n");
                        break;
                case Protocole::Etat::OBSTACLE:
                        printf("\033[34m OBSTACLE \033[0m\n");
                        break;
        }
}

void test_protocole(int argc, char *argv[]) {
        TEST_BEGIN;
        char etats_GP2[] = {'X','X','X'};
        Protocole::Etat ret;

        // printf("Set GP2 on ..................... ");
        // ret = proto.set_detection_GP2(1);
        // message_retour(ret);

        // for(int i = 0; i < 5; i++) {
        //         printf("Set Position ................... ");
        //         ret = Protocole.set_position(16, 80, etats_GP2, 5);
        //         message_retour(ret);
        //         // usleep(3000000);
        // }

        for(int i = 0; i < 5; i++) {
                printf("Set Position ................... ");
                ret = Protocole.set_position(50, 50, etats_GP2, 5);
                message_retour(ret);

                printf("Set Position ................... ");
                ret = Protocole.set_position(80, 50, etats_GP2, 10);
                message_retour(ret);

                printf("Set Position ................... ");
                ret = Protocole.set_position(80, 80, etats_GP2, 10);
                message_retour(ret);

                printf("Set Position ................... ");
                ret = Protocole.set_position(50, 80, etats_GP2, 10);
                message_retour(ret);
        }

        // printf("Set angle ...................... ");
        // ret = proto.set_angle(90);
        // message_retour(ret);

        // printf("Set actionneur ................. ");
        // ret = proto.set_actionneur('1', '1');
        // message_retour(ret);

        // struct position pos;
        // pos.x = 0;
        // pos.y = 0;
        // printf("Get Position ................... ");
        // ret = proto.get_position(&pos);
        // message_retour(ret);
        // printf("POS = %d, %d\n", pos.x, pos.y);

        // printf("Set Position ................... ");
        // ret = proto.set_position(60, 60, etats_GP2, 10);
        // message_retour(ret);

        // short int angle = 666;
        // printf("Get angle ...................... ");
        // ret = proto.get_angle(&angle);
        // message_retour(ret);
        // printf("ANGLE = %hd\n", angle);

        // printf("Get etats ...................... ");
        // ret = proto.get_etats_GP2(etats_GP2);
        // message_retour(ret);
        // printf("Etats GP2 = %c, %c, %c\n", etats_GP2[0], etats_GP2[1], etats_GP2[2]);
        TEST_END;
}

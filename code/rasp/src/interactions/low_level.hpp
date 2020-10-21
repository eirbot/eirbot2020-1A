#ifndef __LOW_LEVEL_H_
#define __LOW_LEVEL_H_

/**
 * @file low_level.hpp
 * @brief fonction bas niveau rasp (GPIO)
 * @author PtitLu
 */
//BCM numbering
const int TEAM_SWITCH_INPUT = 17; //bleu = 0 , jaune = 1
const int TEAM_LED_OUTPUT = 26;
const int GO_INPUT = 27;
const int PHARE_INPUT = 5; //FIXME lequel est lequel ?
const int NORD_INPUT = 11; //FIXME


class LowLevel {
    public:
        LowLevel();
        ~LowLevel();

        /**
         * @brief est-ce que le jack est retiré ?
         * @return true=go, false=pas bouger
         */
        bool is_depart();


        /**
         * @brief est-ce qu'on est bleu ?
         * @return true=bleu, false=jaune
         */
        bool is_equipe_bleu();


        /**
         * @brief est-ce que le phare est activé ?
         * @return true=activé, false=pas activé fuck
         */
        bool phare_active();


        /**
         * @brief est-ce qu'on se gare au nord ?
         * @return true=nord, false=sud
         */
        bool boussole_nord();

    private:
        int setup();
        void set_mode();
        void write();
        void read();
};



#endif // __LOW_LEVEL_H_

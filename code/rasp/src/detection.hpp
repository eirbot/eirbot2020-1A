#ifndef __DETECTION_H__
#define __DETECTION_H__

//Pris sur les anciens dépots a modifier !!!!
// 1.0  -> 6 cm
// 0.4  -> 20 cm
// 0.72 -> 10 cm
// O.19 -> 50 cm

enum GP2{
gauche_avant,centre_avant,droite_avant
}

class GP2{

    public:
                GP2();
                GP2(int intput,int activated,int distance_seuil);
                void activate(); //Active la detection
                void disactivate(); //Désactive la detection
                bool gp2Obstacle(int distance_seuil, GP2 input);
                void EVITEMENT(GP2 gauche_avant, GP2 centre_avant, GP2 droite_avant, );
                ~GP2();
    private:
        int input; //identifiant du GP2
        int activated;
        int distance_seuil;
};

#endif // __DETECTION_H__

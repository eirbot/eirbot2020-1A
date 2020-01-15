#ifndef __DETECTION_H__
#define __DETECTION_H__

//Pris sur les anciens dépots a modifier !!!!
// 1.0  -> 6 cm
// 0.4  -> 20 cm
// 0.72 -> 10 cm
// O.19 -> 50 cm



class GP2{

    public:
        GP2();
        GP2(int intput,int activated,int distance_seuil);
        void activate(); //Active la detection
        void disactivate(); //Désactive la detection
        bool gp2Obstacle(int distance_seuil, GP2 input);
        ~GP2();
    private:
        int input;
        int activated;
        int distance_seuil;
};

#endif // __DETECTION_H__

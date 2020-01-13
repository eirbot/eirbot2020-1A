#ifndef __ACTIONNEUR_H__
#define __ACTIONNEUR_H__

#include "world.hpp"
#include "asserv.hpp"
#include "navigation.hpp"

class Actionneur{

    public:
        static void Phare_activation(); //Sort l'actionneur et avance un peu pour activer le phare
        static void Phare_desactivation(); //Rentre l'actionneur
        static void Manche_activation(); //Sort l'actioneur
        static void Manche_desactivation(); //Rentre l'actionneur
    private:
};

#endif

#include "actionneur.hpp"

Actionneur::Actionneur(){
   
}

void Actionneur::Gauche_activation()
{
    int back= (int) Protocole.set_actionneur('0','1');
    printf("Sortie de l'actionneur ....................................... ");
    affichage(back);
}

void Actionneur::Gauche_desactivation()
{
    int back = (int) Protocole.set_actionneur('0','0');
    printf("Rentrée de l'actionneur ...................................... ");
    affichage(back);
}

void Actionneur::Droit_activation()
{
    int back= (int) Protocole.set_actionneur('1','1');
    printf("Sortie de l'actionneur ....................................... ");
    affichage(back);
}

void Actionneur::Droit_desactivation()
{
    int back = (int) Protocole.set_actionneur('1','0');
    printf("Rentrée de l'actionneur ...................................... ");
    affichage(back);
}


void Actionneur::Pavillon()
{
    int back = (int) Protocole.set_actionneur('2','1');
    printf("Lancement du pavillon ........................................ ");
    affichage(back);
}

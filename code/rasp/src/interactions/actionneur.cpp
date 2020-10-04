#include "actionneur.hpp"
void Gauche_activation()
{
    int back= (int) Protocole.set_actionneur('0','1');
    printf("Sortie de l'actionneur ....................................... ");
    affichage(back);
}

void Gauche_desactivation()
{
    int back = (int) Protocole.set_actionneur('0','0');
    printf("Rentrée de l'actionneur ...................................... ");
    affichage(back);
}

void Droit_activation()
{
    int back= (int) Protocole.set_actionneur('1','1');
    printf("Sortie de l'actionneur ....................................... ");
    affichage(back);
}

void Droit_desactivation()
{
    int back = (int) Protocole.set_actionneur('1','0');
    printf("Rentrée de l'actionneur ...................................... ");
    affichage(back);
}


void Pavillon()
{
    int back = (int) Protocole.set_actionneur('2','1');
    printf("Lancement du pavillon ........................................ ");
    affichage(back);
}

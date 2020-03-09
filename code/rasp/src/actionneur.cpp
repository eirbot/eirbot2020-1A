#include "actionneur.hpp"
void Actionneur::Phare_activation()
{
    int back= (int) Protocole.set_actionneur('0','1');
    printf("Sortie de l'actionneur ....................................... ");
    affichage(back);
}

void Actionneur::Phare_desactivation()
{
    int back = (int) Protocole.set_actionneur('0','0');
    printf("Rentrée de l'actionneur ...................................... ");
    affichage(back);
}

void Actionneur::Pavillon()
{
    int back = (int) Protocole.set_actionneur('1','1');
    printf("Lancement du pavillon ........................................ ");
    affichage(back);
}

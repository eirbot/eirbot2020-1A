#ifndef __DETECTION_H_
#define __DETECTION_H_

//C'est le fichier le plus complet sur la nucléo (hormis l'asserv), il doit récup l'information sur les 6 GP2, checker leurs états
//et renvoyer obstacle si ils détectent quelque chose.
// L'idée c'est aussi de gérer les contacteurs dans ce fichier
// En résumé ça se passe comme ça :
// La strat demande un déplacement vers un point x y
// La com transmet cet ordre en appelant la boucle d'asservissement
// Dans la boucle il y a une interuption de détection
// C'est cette interuption que l'on crée ici
// Elle est en deux partie
// Une partie GP2, check la détection sur les GP2 actifs et renvoie la distance à laquelle on détecte l'adversaire
// Une partie contacteur, si un contacteur s'active alors qu'on est au milieu de la table, (cela revient à renvoyer une distance nulle)

//L'interuption est toujours un void void, l'idée c'est que chaque demi seconde (ou le temps que l'on veut), la boucle va appeler automatiquement
//cette fonction, c'est dedans que l'on va creer le branchement.
//En gros soit on ne détecte rien et donc on sort de la fonction de manière classique, soit on détecte et donc on réagit en fonction
void interuption();



#endif // __DETECTION_H_

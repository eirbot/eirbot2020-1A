#include "test_ecocup.hpp"

extern int *cycle_hamiltonien;
extern short ecocup_coordonne[100][2];
extern char ecocup_couleur[100][1];

void test_ecocup()
{
    TEST_BEGIN;
    // Robot Robot;
    // int taille=8;
    // printf("Début des tests sur les fonctions principales \n");
    // printf("Test sur la lecture du fichier ");
    // assert(cycle_hamiltonien==NULL);
    // ecocup_read(taille);
    // for (int i=0; i<taille; i++) {
    //     assert(ecocup_coordonne[i][0]>=0);
    //     assert(ecocup_coordonne[i][1]>=0);
    //     assert(ecocup_couleur[i][0]=='P' || ecocup_couleur[i][0]=='V' || ecocup_couleur[i][0]=='R' );
    // }
    // print_success();

    // printf("Test sur la résolution du problème \n");
    // ecocup_road(taille, Robot);

    // assert(cycle_hamiltonien!=NULL);
    // printf("Chemin trouvé : ");
    // for (int i=0; i<taille; i++) {
    //     printf("%d-",cycle_hamiltonien[i]);
    //     assert(cycle_hamiltonien[i]>=0);
    // }
    // printf("%d ........................ ",cycle_hamiltonien[0]);
    // print_success();

    // ecocup_take();

    // printf("Début des tests sur les fonctions auxiliaires \n");
    // printf("Test sur l'obtention des villes non visitées par une fourmi");
    // list_ville test_liste;
    // test_liste=getvilleNonVisite(2);
    // assert(test_liste!=NULL);
    // assert(test_liste->num_ville>=0);
    // print_success();

    // printf("Test sur l'effacage d'une liste .......................... ");
    // effacerliste(test_liste);
    // assert(test_liste->num_ville==NULL);
    // print_success();

    // printf("Test sur le calcul de probabilité ........................ ");
    // float proba=calcul_probabilite(2, 0, 3);
    // assert(proba>=0);
    // print_success();

    // printf("Test sur la longueur du cycle hamiltonien ................ ");
    // float longueur=getLongueur_cycle_hamiltonien(2);
    // assert(longueur>=0);
    // print_success();

    // printf("Test sur la quantité de phéromones déposées .............. ");
    // float quantite=get_quantite_pheromones_deposes(0, 2);
    // assert(quantite>=0);
    // print_success();

    // printf("Test sur le ant system \t");
    // ant_system();
    // assert(cycle_hamiltonien!=NULL);
    // printf("Chemin trouvé : ");
    // for (int i=0; i<taille; i++) {
    //     printf("%d-",cycle_hamiltonien[i]);
    //     assert(cycle_hamiltonien[i]>=0);
    // }
    // printf("%d  ",cycle_hamiltonien[0]);
    // print_success();
   
    TEST_END;
}

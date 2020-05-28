#ifndef __ECOCUP_PDV_H_
#define __ECOCUP_PDV_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define C_IMPORTANCE_VISIBILITE_VILLE 0.5 //Importance donnée à la visibilité des villes.
#define C_IMPORTANCE_QUANTITE_PHEROMONE 0.5 //Importance donnée à la quantité de phéromones déposées
#define C_VITESSE_EVAPORATION_PHEROMONE 0.75 //Définit la vitesse d'évaporation des phéromones.
#define C_PISTE_PHEROMONE 0.5 //Constante utilisée pour l'initialisation des pistes de phéromones
#define C_QUANTITE_PHEROMONE 100 //Constante utilisée dans le calcul de la quantité de phéromones déposés par les fourmis.
#define C_NB_CYCLE 50 //Nombre d'itérations ou plutôt de cycles exécutés par l'algorithme.

typedef struct ville ville;
struct ville
{
	int num_ville;
	struct ville *nxt;
};
typedef ville* list_ville;


void effacerliste(list_ville list);
void initPremiereVilleParcourue(void);
void initQuantitePheromones(void);
void initMatriceVisibilite();
list_ville getvilleNonVisite(int num_fourmi);
float calcul_probabilite(int num_fourmi, int ville_actuel, int ville_non_visite);
float getLongueur_cycle_hamiltonien(int num_fourmi);
void reinitialiser_ville_fourmis(void);
float get_quantite_pheromones_deposes_par_une_fourmi(int num_fourmi,int i,int j);
float get_quantite_pheromones_deposes(int i,int j);
void ant_system(void);
void initMatriceVille(int taille);
void CalculeBest();
void ecocup_pdv(int taille);
void ecocup_print(int taille);

#endif // __ECOCUP_PDV_H_

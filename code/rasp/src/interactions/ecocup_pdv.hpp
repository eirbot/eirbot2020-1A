#ifndef __ECOCUP_PDV_H_
#define __ECOCUP_PDV_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/**
 * @file ecocup_pdv.hpp
 * @brief Implémentation (en C) du problème du voyageur avec le système de colonie de fourmis*/

/**
 * @brief Importance donnée à la visibilité des villes.*/
#define C_IMPORTANCE_VISIBILITE_VILLE 0.5

/**
 * @brief Importe donnée à la quantité de phéromones déposées */
#define C_IMPORTANCE_QUANTITE_PHEROMONE 0.5

/**
 * @brief Définit la vitesse d'évaporation des phéromones */
#define C_VITESSE_EVAPORATION_PHEROMONE 0.75

/**
 * @brief Constante utilisée pour l'initialisation des pistes de phéromones */
#define C_PISTE_PHEROMONE 0.5

/**
 * @brief Constante utilisée dans le calcul de la quantité de phéromones déposés par les fourmis*/
#define C_QUANTITE_PHEROMONE 100

/**
 * @brief Nombre d'itérations de l'algorithme */
#define C_NB_CYCLE 50



/**
 * @struct ville
 * @brief permet de faire une liste chainée de ville
 * @param num_ville: identifiant de la ville
 * @param nxt: ville suivante*/
typedef struct ville ville;
struct ville
{
	int num_ville;
	struct ville *nxt;
};
typedef ville* list_ville;

/**
 * @brief Efface la liste des villes
 * @param list: la liste de ville*/
void effacerliste(list_ville list);
/**
 * @brief Définit la première ville parcourue*/
void initPremiereVilleParcourue();
/**
 * @brief Initialise la quantité de Phéromones*/
void initQuantitePheromones();
/**
 * @brief Initialisation la matrice de visibilité*/
void initMatriceVisibilite();

/**
 * @brief Permet de savoir les villes non explorées par une fourmi
 * @param num_fourmi: identifiant de la fourmi
 * @return une liste chainée de ville*/
list_ville getvilleNonVisite(int num_fourmi);

/**
 * @brief Calcul la probabilité qu'une fourmi passe sur un arc
 * @param num_fourmi: identifiant de la fourmi
 * @param ville_actuelle : départ de l'arc
 * @param ville_non_visite: fin de l'arc
 * @return La probabilité*/
float calcul_probabilite(int num_fourmi, int ville_actuelle, int ville_non_visite);

/**
 * @brief Renvoie la longueur du cycle hamiltonien d'une fourmi*/
float getLongueur_cycle_hamiltonien(int num_fourmi);
/**
 * @brief Vide la liste des villes pour toutes les fourmis */
void reinitialiser_ville_fourmis();

/**
 * @brief Calcule la quantité de phéromone déposée par une formi sur l'arc i j*/
float get_quantite_pheromones_deposes_par_une_fourmi(int num_fourmi,int i,int j);

/**
 * @brief Calcule la quantité de phéromone déposée sur un arc i j */
float get_quantite_pheromones_deposes(int i,int j);

/**
 * @brief Coeur de l'algorithme : algorithme de colonie de fourmi https://fr.wikipedia.org/wiki/Algorithme_de_colonies_de_fourmis*/
void ant_system();

/**
 * @brief Lit le fichier de ville pour remplir la matrice des villes
 * @param taille: le nombre de ville à lire*/
void initMatriceVille(int taille);

/**
 * @brief Trouve le meilleur voyage parmis ceux calculés par ant_system*/
void CalculeBest();

/**
 * @brief Fonction récapitulative permettant de faire tout le système (initialisation, ant_system, trouver le meilleur)
 * @param taille: nombre de ville à considérer*/
void ecocup_pdv(int taille);

/**
 * @brief Permet d'afficher le chemin trouvé*/
void ecocup_print(int taille);

#endif // __ECOCUP_PDV_H_

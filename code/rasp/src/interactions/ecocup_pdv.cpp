#include "ecocup_pdv.hpp"
#include <stdio.h>

float **matrice_ville;
float **matrice_visibilite;
float **quantite_pheromones_existante;
list_ville *list_ville_fourmi;


float Best = 0;
int *cycle_hamiltonien;

int C_NB_VILLE;
int C_NOMBRE_FOURMIS;

FILE * fichier_trace;
int cnt=0;

//--------------------------------------------------------------------------------------------------------------------------
// Fonction pour libérer la mémoire de la liste chainé
//--------------------------------------------------------------------------------------------------------------------------
void effacerliste(list_ville list)
{
    ville* temp = list;
    ville* tempnxt;
    while(temp != NULL)
    {
        tempnxt = temp->nxt;
        free(temp); // libiration de la mémoire
        temp = tempnxt;
    }
    list = NULL;
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction pour initialiser la première ville pour chaque fourmi
//--------------------------------------------------------------------------------------------------------------------------
void initPremiereVilleParcourue()
{
    int i;

    C_NOMBRE_FOURMIS = 2*C_NB_VILLE; // initialiser le nombre des fourmis a utiliser dans l'algorithme ant system

    // initialisation du tableau de liste chainé des villes parcouris par les fourmis
    list_ville_fourmi = (list_ville *)malloc(C_NOMBRE_FOURMIS * sizeof(list_ville));

    srand((unsigned int)time(NULL));

    // positionnement des fourmis sur les villes
    for(i=0;i<C_NOMBRE_FOURMIS;i=i+1)
    {
        ville* nouvelleVille = (ville*)malloc(sizeof(ville));
        nouvelleVille->num_ville =7; // rand()%C_NB_VILLE;
        nouvelleVille->nxt = NULL;
        list_ville_fourmi[i] = nouvelleVille;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction pour initialiser la matrice contenant la quantité de phéromones existante sur chaque arc
//--------------------------------------------------------------------------------------------------------------------------
void initQuantitePheromones()
{
    int i,j;

    quantite_pheromones_existante = (float **)malloc(C_NB_VILLE * sizeof(float *));

    if(quantite_pheromones_existante == NULL)
    {
        printf("espace mémoire insuffisant\n");
        exit(1);
    }

    for(i = 0; i < C_NB_VILLE; i++)
    {
        quantite_pheromones_existante[i] = (float *)malloc(C_NB_VILLE * sizeof(float));

        if(quantite_pheromones_existante[i] == NULL)
        {
            printf("espace mémoire insuffisant\n");
            exit(1);
        }
    }

    for(i=0;i<C_NB_VILLE;i++)
    {
        for(j=0;j<C_NB_VILLE;j++)
        {
            quantite_pheromones_existante[i][j] = (float)C_PISTE_PHEROMONE;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction pour initialiser la matrice de visibilité
//--------------------------------------------------------------------------------------------------------------------------
void initMatriceVisibilite()
{
    int i,j;

    matrice_visibilite = (float **)malloc(C_NB_VILLE * sizeof(float *));

    if(matrice_visibilite == NULL)
    {
        printf("espace mémoire insuffisant\n");
        exit(1);
    }

    for(i = 0; i < C_NB_VILLE; i++)
    {
        matrice_visibilite[i] = (float *)malloc(C_NB_VILLE * sizeof(float));

        if(matrice_visibilite[i] == NULL)
        {
            printf("espace mémoire insuffisant\n");
            exit(1);
        }
    }

    for(i=0;i<C_NB_VILLE;i++)
    {
        for(j=0;j<C_NB_VILLE;j++)
        {
            if(matrice_ville[i][j] != 0)
            {
                matrice_visibilite[i][j] = (float)1/matrice_ville[i][j];
            }
            else
            {
                matrice_visibilite[i][j] = 0;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction retourne la liste chainé des villes non visité par une fourmi
//--------------------------------------------------------------------------------------------------------------------------
list_ville getvilleNonVisite(int num_fourmi)
{
    list_ville ret_list_ville = NULL;
    ville* temp;
    int i;
    int trouve;
    for(i=0;i<C_NB_VILLE;i++)
    {
        temp = list_ville_fourmi[num_fourmi];
        trouve = 0;
        while(temp != NULL)
        {
            if(temp->num_ville == i)
            {
                trouve = 1;
                break;
            }
            temp = temp->nxt;
        }

        if(trouve == 0)
        {
            ville* nouvelleVille = (ville*)malloc(sizeof(ville));
            nouvelleVille->num_ville = i;
            nouvelleVille->nxt = NULL;

            if(ret_list_ville == NULL)
            {
                ret_list_ville = nouvelleVille;
            }
            else
            {
                temp = ret_list_ville;
                while(temp->nxt != NULL)
                {
                    temp = temp->nxt;
                }
                temp->nxt = nouvelleVille;
            }
        }
    }
    return ret_list_ville;
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction retourne la probabilité qui une fourmi passe par l'arc i->j
//--------------------------------------------------------------------------------------------------------------------------
float calcul_probabilite(int num_fourmi, int ville_actuel, int ville_non_visite)
{
    float p,q=0;

    ville* temp;

    p = pow(quantite_pheromones_existante[ville_actuel][ville_non_visite],(float)C_IMPORTANCE_VISIBILITE_VILLE)*pow(matrice_visibilite[ville_actuel][ville_non_visite],(float)C_IMPORTANCE_QUANTITE_PHEROMONE);

    list_ville list_ville_non_visite = getvilleNonVisite(num_fourmi);

    temp = list_ville_non_visite;
    while(temp != NULL)
    {
        q += pow(quantite_pheromones_existante[ville_actuel][temp->num_ville],(float)C_IMPORTANCE_VISIBILITE_VILLE)*pow(matrice_visibilite[ville_actuel][temp->num_ville],(float)C_IMPORTANCE_QUANTITE_PHEROMONE);
        temp = temp->nxt;
    }

    effacerliste(list_ville_non_visite);

    if(q != 0)
    {
        return (p/q);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Permet de calculer le distance parcourus par une fourmi
//--------------------------------------------------------------------------------------------------------------------------
float getLongueur_cycle_hamiltonien(int num_fourmi)
{
    int i,j;
    float longueur_cycle_hamiltonien = 0;
    ville* temp = list_ville_fourmi[num_fourmi];
    while(temp->nxt != NULL)
    {
        i= temp->num_ville;
        j= temp->nxt->num_ville;
        longueur_cycle_hamiltonien += matrice_ville[i][j];
        temp = temp->nxt;
    }

    return longueur_cycle_hamiltonien;
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction permet de reinitialiser le tableau de liste chainé qui stock les villes parcourus par les fourmis
//--------------------------------------------------------------------------------------------------------------------------
void reinitialiser_ville_fourmis()
{
    int j;
    ville* temp;
    for(j=0;j<C_NOMBRE_FOURMIS;j++)
    {
        temp = list_ville_fourmi[j]->nxt;

        effacerliste(temp);

        list_ville_fourmi[j]->nxt = NULL;
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction retourne la quantité des phéromones deposé par une fourmi sur l'arc i->j
//--------------------------------------------------------------------------------------------------------------------------
float get_quantite_pheromones_deposes_par_une_fourmi(int num_fourmi,int i,int j)
{
    float quantite_pheromones_deposes = 0;
    int arc_appartient_au_cycle_hamiltonien = 0;
    ville* temp = list_ville_fourmi[num_fourmi];
    while(temp != NULL)
    {
        if(temp->num_ville == i)
        {
            if(temp->nxt != NULL)
            {
                if(temp->nxt->num_ville == j)
                {
                    arc_appartient_au_cycle_hamiltonien = 1;
                    break;
                }
            }
        }

        if(temp->num_ville == j)
        {
            if(temp->nxt != NULL)
            {
                if(temp->nxt->num_ville == i)
                {
                    arc_appartient_au_cycle_hamiltonien = 1;
                    break;
                }
            }
        }
        temp = temp->nxt;
    }

    if(arc_appartient_au_cycle_hamiltonien == 1)
    {
        quantite_pheromones_deposes = ((float)C_QUANTITE_PHEROMONE)/getLongueur_cycle_hamiltonien(num_fourmi);
    }
    return quantite_pheromones_deposes;
}

//--------------------------------------------------------------------------------------------------------------------------
// Fonction retourne la quantité des phéromones deposé par l'ensemble des fourmis sur l'arc i->j
//--------------------------------------------------------------------------------------------------------------------------
float get_quantite_pheromones_deposes(int i,int j)
{
    float quantite_pheromones_deposes = 0,piste_pheromone;
    int k;

    quantite_pheromones_deposes = (float)C_VITESSE_EVAPORATION_PHEROMONE * quantite_pheromones_existante[i][j];

    for(k=0;k<C_NOMBRE_FOURMIS;k++)
    {
        quantite_pheromones_deposes += get_quantite_pheromones_deposes_par_une_fourmi(k,i,j);
    }

    if(Best != 0)
    {
        piste_pheromone = ((float)C_QUANTITE_PHEROMONE)/Best;
        if(quantite_pheromones_deposes < 0.00001) quantite_pheromones_deposes = piste_pheromone;
    }

    return quantite_pheromones_deposes;
}

void affiche_matrice(int mat)
{
    int i,j;
    if(mat==0) return;
    if(mat == 1)
    {
        for(i=0;i<C_NB_VILLE;i++)
        {
            for(j=0;j<C_NB_VILLE;j++)
            {
                printf("%f , ",quantite_pheromones_existante[i][j]);
            }
            printf("\n");
        }
    }
    else if(mat == 2)
    {
        for(i=0;i<C_NB_VILLE;i++)
        {
            for(j=0;j<C_NB_VILLE;j++)
            {
                printf("%f , ",matrice_ville[i][j]);
            }
            printf("\n");
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------
// implimentation de l'algorithme Ant system
//--------------------------------------------------------------------------------------------------------------------------
void ant_system()
{
    int i,j,k,l,h;
    int p_rand,q_rand;
    ville* temp;
    int num_ville_suivante,num_ville_actuelle;
    float probabilite, max_probabilite,lg;
    list_ville list_ville_non_visite = NULL;
    for(i=0;i<C_NB_CYCLE;i++)
    {
        for(k=0;k<C_NB_VILLE;k++)
        {
            for(j=0;j<C_NOMBRE_FOURMIS;j++)
            {
                temp = list_ville_fourmi[j];

                while(temp != NULL)
                {
                    if(temp->nxt == NULL)
                    {
                        break;
                    }
                    temp = temp->nxt;
                }

                if(temp != NULL)
                {
                    num_ville_actuelle = temp->num_ville;
                    list_ville_non_visite = getvilleNonVisite(j);
                    max_probabilite = -1;
                    num_ville_suivante = -1;
                    temp = list_ville_non_visite;
                    p_rand = rand()%9999;
                    q_rand = rand()%10000 + 1;
                    while(temp != NULL)
                    {
                        probabilite = calcul_probabilite(j,num_ville_actuelle,temp->num_ville);
                        if(max_probabilite <= probabilite)
                        {
                            max_probabilite = probabilite;
                            num_ville_suivante = temp->num_ville;
                            if(max_probabilite > (p_rand/q_rand))
                            {
                                break;
                            }
                        }
                        temp = temp->nxt;
                    }
                    effacerliste(list_ville_non_visite);
                }

                temp = list_ville_fourmi[j];

                if(num_ville_suivante == -1)
                {
                    num_ville_suivante = temp->num_ville;
                }

                while(temp->nxt != NULL)
                {
                    temp = temp->nxt;
                }

                ville* nouvelleVille = (ville*)malloc(sizeof(ville));
                nouvelleVille->num_ville = num_ville_suivante;
                nouvelleVille->nxt = NULL;
                temp->nxt = nouvelleVille;
            }
        }

        for(l=0;l<C_NB_VILLE;l++)
        {
            for(h=0;h<C_NB_VILLE;h++)
            {
                if(l != h)
                {
                    quantite_pheromones_existante[l][h] = get_quantite_pheromones_deposes(l,h);
                }
            }
        }

        CalculeBest();

        reinitialiser_ville_fourmis();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
// Fonction :
// permet de lire les coordonné de chaque ville à partir du fichier fichier_ecocup.txt
// permet de faire le calcule de la distance entre les villes
// permet d'initialiser la matrice des villes
//--------------------------------------------------------------------------------------------------------------------------
void initMatriceVille(int taille)
{
    int i,j;
    float x=0;
    float y=0;
    char color=0;
    FILE * fichier_ecocup;
    float ville_coordonne[100][3];
    C_NB_VILLE=taille;
    matrice_ville = (float **)malloc(C_NB_VILLE * sizeof(float *));

    if(matrice_ville == NULL)
    {
        printf("espace mémoire insuffisant\n");
        exit(1);
    }

    for(i = 0; i < C_NB_VILLE; i++)
    {
        matrice_ville[i] = (float *)malloc(C_NB_VILLE * sizeof(float));
        if(matrice_ville[i] == NULL)
        {
            printf("espace mémoire insuffisant\n");
            exit(1);
        }
    }
    for (i=0;i<C_NB_VILLE;i++)
    {
        matrice_ville[i][i]=0;
    }

    fichier_ecocup=fopen("fichier_ecocup.txt","r");

    if (fichier_ecocup != NULL)
    {
        while (fscanf(fichier_ecocup,"%d",&i) != EOF)
        {
            fscanf(fichier_ecocup,"%f",&x);
            fscanf(fichier_ecocup,"%f",&y);
            fscanf(fichier_ecocup,"%c",&color);
            ville_coordonne[i-1][0] = x;
            ville_coordonne[i-1][1] = y;
            ville_coordonne[i-1][2] = color;
        }
        fclose(fichier_ecocup);

        for(i=0;i<C_NB_VILLE;i++)
        {
            for(j=0;j<C_NB_VILLE;j++)
            {
                matrice_ville[i][j] = sqrt(pow(ville_coordonne[i][0] - ville_coordonne[j][0],2) + pow(ville_coordonne[i][1] - ville_coordonne[j][1],2));
            }
        }
    }
    else
    {
        printf("Fichier fichier_ecocup.txt absent!");
        exit(1);
    }
    fichier_ecocup = NULL;
}

void CalculeBest(void)
{
    int i,j;
    float lg=0;
    char txt_ville[10];
    ville* temp=NULL;
    for(i=0;i<C_NOMBRE_FOURMIS;i++)
    {
        lg = getLongueur_cycle_hamiltonien(i);
        if(Best > lg || Best == 0)
        {
            Best = lg;
            temp = list_ville_fourmi[i];
            if(cycle_hamiltonien == NULL)
            {
                cycle_hamiltonien = (int *)malloc(C_NB_VILLE * sizeof(int));
            }
            j=0;
            while(temp != NULL)
            {
                cycle_hamiltonien[j] = temp->num_ville;
                temp = temp->nxt;
                j++;
            }
        }
    }
}

void ecocup_pdv(int taille)
{
    initMatriceVille(taille);
    initMatriceVisibilite();
    initQuantitePheromones();
    initPremiereVilleParcourue();
    ant_system();
}

void ecocup_print(int taille)
{
    ecocup_pdv(taille);
    printf("Plus court chemin pour parcourir les %d bouées :\n\033[34m",C_NB_VILLE);
    printf("%d",cycle_hamiltonien[0] +1);
    for(int i=1;i<C_NB_VILLE;i++)
    {
        printf("-%d",cycle_hamiltonien[i] +1);
    }
    printf("-%d",cycle_hamiltonien[0] +1);
    printf("\033[0m\nDistance totale :");
    printf("%f \n",Best);
}

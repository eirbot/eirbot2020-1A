#include "ecocup.hpp"

extern int *cycle_hamiltonien;

short ecocup_coordonne[100][2];
char ecocup_couleur[100][1];

void ecocup_road(int taille, Robot Robot)
{
    ecocup_pdv(taille);
    ecocup_read(taille);
    ecocup_print(taille);
    std::vector<Node> result;
    int back;
    struct Node src={0,0,0,0,0,0,0};
    struct position my_position=Robot.position();
    src.x=my_position.x=16;
    src.y=my_position.y=80;
    struct Node dest={0,0,0,0,0,0,0};
    vector <obstacle> list_obstacles_without_ecocup=fillVector_no_ecocup();
    for (int i=1; i<taille ; i++) {
        //On trouve le x et le y auquel on doit aller
        dest.x=ecocup_coordonne[cycle_hamiltonien[i+1]][0];
        dest.y=ecocup_coordonne[cycle_hamiltonien[i+1]][1];

        //On va à l'éco cup
        Robot.move(src,dest,list_obstacles_without_ecocup);
       
        src.x=dest.x;
        src.y=dest.y;
        ecocup_take();

        //On retourne au port
        if (ecocup_couleur[cycle_hamiltonien[i]][0]=='V') {
            dest={16,40,0,0,0,0,0};
        }
        if (ecocup_couleur[cycle_hamiltonien[i]][0]=='R') {
            dest={16,120};
        }
        Robot.move(src,dest,list_obstacles_without_ecocup);
        src.x=dest.x;
        src.y=dest.y;

    }
}

void ecocup_read(int taille)
{
       int i,j;
    short x=0;
    short y=0;
    char color=0;
    FILE * fichier_ecocup;
    int C_NB_ECOCUP=taille;
    fichier_ecocup=fopen("../fichier_ecocup.txt","r");
    if (fichier_ecocup != NULL)
    {
        while (fscanf(fichier_ecocup,"%d",&i) != EOF)
        {
            fscanf(fichier_ecocup,"%hd",&x);
            fscanf(fichier_ecocup,"%hd",&y);
            fscanf(fichier_ecocup,"%c",&color);
            ecocup_coordonne[i-1][0] = x;
            ecocup_coordonne[i-1][1] = y;
            ecocup_couleur[i-1][0] = color;
        }
        fclose(fichier_ecocup);
    }
}

void ecocup_take()
{
    printf("Début de la procédure de ramassage ....................... ");
    print_success();
}

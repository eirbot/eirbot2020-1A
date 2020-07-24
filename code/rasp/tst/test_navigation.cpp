#include "test_navigation.hpp"

extern int which_side;

static short side(short y)
{
    if(which_side==1){
        return Y_MAX-y;
    }
    return y;
}


void test_navigation()
{
    TEST_BEGIN;
    //Définition des points d'interets
    struct Node Phare={30,side(16),0,0,0,0,0};
    struct Node Manche_1={23,side(184),0,0,0,0,0};
    struct Node Manche_2={63,side(184),0,0,0,0,0};
    struct Node Port={16,side(80),0,0,0,0,0};
    struct Node Port_N={16,side(40),0,0,0,0,0};
    struct Node Port_S={16,side(120),0,0,0,0,0};
    printf("Test sur le remplissage du vecteur d'obstacles ...");
    std::vector<obstacle> list_obstacles=fillVector();
    assert(list_obstacles.size()==27);
    print_success();

    printf("Test sur l'exécution de l'Astar ... \n");
    printf("Test classique de déplacement basique ... \n");
    Navigation test_navigation=Navigation(Phare);
    std::vector<Node> test_path=test_navigation.Astar(test_navigation, Navigation(Manche_1),list_obstacles);
    assert(test_path.size()!=0);
    assert(test_path[0].x==Phare.x && test_path[0].y==Phare.y);
    assert(test_path[test_path.size()-1].x==Manche_1.x);
    assert(test_path[test_path.size()-1].y==Manche_1.y);
    good_port(test_path[test_path.size()-1].x, test_path[test_path.size()-1].y, Port.x, Port.y);
    print_success();

    printf("Test si la desination est un obstacle ... \n");
    std::vector<Node> test_path_obstacle=test_navigation.Astar(test_navigation, Navigation({45,51}),list_obstacles);
    assert(test_path_obstacle.size()==0);
    print_success();

    printf("Test si nous sommes à la destination ... \n");
    std::vector<Node> test_path_destination=test_navigation.Astar(test_navigation, test_navigation,list_obstacles);
    assert(test_path_destination.size()==0);
    print_success();

    printf("Test de déplacement plus complexe ... \n");
    test_path=test_navigation.Astar(test_navigation, Navigation(Manche_1),list_obstacles);
    assert(test_path[0].x==Phare.x && test_path[0].y==Phare.y);
    test_path=test_navigation.Astar(Navigation(Manche_1), Navigation(Manche_2),list_obstacles);
    test_path=test_navigation.Astar(Navigation(Manche_2), Navigation(Phare),list_obstacles);
    test_path=test_navigation.Astar(Navigation(Phare), Navigation(Port),list_obstacles);
    assert(test_path[test_path.size()-1].x==Port.x && test_path[test_path.size()-1].y==Port.y);
    good_port(test_path[test_path.size()-1].x, test_path[test_path.size()-1].y, Port.x, Port.y);
    print_success();

    printf("Test sur l'affichage d'un chemin ... \n");
    test_navigation.Print_path(test_path,list_obstacles);
    print_success();


    printf("Test sur la transmission du chemin à l'asservissement ... \n");
    int back=-5;
    back=test_navigation.Navigate_to_asserv(test_path, Navigation(Manche_1), list_obstacles);
    assert(back!=-5);
    print_success();

    printf("Test sur la fonction back_effect \n");
    printf("Si back=0, normal si il ne se passe rien ...");
    test_navigation.back_effect(0, Navigation(Manche_1), list_obstacles);
    print_success();
    printf("Si back=1, demande la position du robot et renvoie l'information ... \n");
    test_navigation.back_effect(1, Navigation(Manche_1), list_obstacles);
    print_success();
    printf("Si back=2, demande la position du robot et aux GP2 l'information sur les obstacles et renvoie l'information ... \n");
    test_navigation.back_effect(2, Navigation(Manche_1), list_obstacles);
    print_success();

    print_summarise();
    TEST_END;
}


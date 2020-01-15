#include "navigation.hpp"

using namespace std;

inline bool operator <(const Navigation& lhs, const Navigation& rhs)
{//We need to overload "<" to put our struct into a set
    return lhs.node.fcost < rhs.node.fcost;
}


bool Navigation::isDestination(int x, int y, Navigation dest) //Permet de savoir si o est arrivé à destination
{
    if (x==dest.node.x && y==dest.node.y){
        return true;
    }
    return false;
}

double Navigation::calculateE(int x, int y, Navigation dest,double E) //Permet de calculer la distance euclidienne
{
    E = (sqrt((x - dest.node.x)*(x - dest.node.x) + (y - dest.node.y)*(y - dest.node.y)));
    return E;
}

bool Navigation::onTable(Navigation pos)
{
    if(pos.node.x>=X_MAX){
        return false;
    }
    if(pos.node.y>=Y_MAX){
        return false;
    }
    return true;
}

Node first={0,0,0,0,0,0,0};

Navigation::Navigation():node(first)
{

}

Navigation::Navigation(Node node): node(node)
{

}

//Gros merci à Openclassroom xD
std::vector<Node> Navigation::Astar(Navigation src, Navigation dest,std::vector<obstacle> list_obstacles)
{
    double E=0;
    vector<Node> empty;
    if (World::isValid(dest.node.x,dest.node.y,list_obstacles)==false){
        printf("La destination est un obstacle ........................... ");
        print_fail();
        return empty;
        //Si l'arrivée est un obstacle on ne fait rien
    }
    if (Navigation::isDestination(src.node.x, src.node.y, dest)==true){
        printf("Vous etes à la destination ............................... ");
        print_fail();
        return empty;
        //Si la source et l'arrivée sont confondues
    }
    if (Navigation::onTable(dest)==false){
        printf("La destination n'est pas sur le plateau de jeu ........... ");
        print_fail();
        return empty;
        //Si on veut aller en dehors de la table
    }
    //Permet d'initialiser la closed list
    bool closedList[X_MAX][Y_MAX];
    array<array<Node,Y_MAX>,X_MAX> allMap;
    for (int x=0; x<X_MAX; x++) {
        for (int y=0; y<Y_MAX; y++) {
            allMap[x][y].fcost=FLT_MAX;
            allMap[x][y].gcost=FLT_MAX;
            allMap[x][y].hcost=FLT_MAX;
            allMap[x][y].parentX=-1;
            allMap[x][y].parentY=-1;
            allMap[x][y].x=x;
            allMap[x][y].y=y;
            closedList[x][y]=false;
        }
    }

    //Initialise le point où l'on est
    short x=src.node.x;
    short y=src.node.y;
    allMap[x][y].fcost=0.0;
    allMap[x][y].gcost=0.0;
    allMap[x][y].hcost=0.0;
    allMap[x][y].parentX=x;
    allMap[x][y].parentY=y;

    //Création de l'openlist
    vector<Node> openList;
    openList.emplace_back(allMap[x][y]);
    bool destinationReach=false;

    //Boucle principale permettant de faire le chemin
    while(!openList.empty()&&openList.size()<(X_MAX*Y_MAX)){
        Node node;
        do{
            float tmp=FLT_MAX;
            vector<Node>::iterator itNode; //Merci Openclassroom
            for (vector<Node>::iterator it=openList.begin(); it!=openList.end() ; it=next(it)) {
                Node n=*it;
                if (n.fcost<tmp) {
                    tmp=n.fcost;
                    itNode=it;
                }
            }
            node =*itNode;
            openList.erase(itNode);

        }while(World::isValid(node.x,node.y,list_obstacles)==false);
        double fNew,gNew,hNew;
        x=node.x;
        y=node.y;
        closedList[x][y]=true;
        //On ajoute les voisins dans la closed list
        for (short i= -1 ; i<=1; i++) {
            for (short j=-1; j<=1; j++) {
                if (World::isValid(x+i,y+j,list_obstacles)==true) {
                    //Si on trouve la destination finale
                    if (isDestination(x+i,y+j,dest)==true) {
                        allMap[x+i][y+j].parentX=x;
                        allMap[x+i][y+j].parentY=y;
                        destinationReach=true;
                        return MakePath(allMap,dest);
                    }
                    else if (closedList[x+i][y+j]==false) {
                        gNew=node.gcost+1.0;
                        hNew=calculateE(x+i,y+j,dest,E);
                        fNew=gNew+hNew;
                        //Verifier si le chemin est meilleur que le précédent chemin
                        if (allMap[x + i][y + j].fcost == FLT_MAX ||
                            allMap[x + i][y + j].fcost > fNew) {
                            allMap[x + i][y + j].fcost = fNew;
                            allMap[x + i][y + j].gcost = gNew;
                            allMap[x + i][y + j].hcost = hNew;
                            allMap[x + i][y + j].parentX = x;
                            allMap[x + i][y + j].parentY = y;
                            openList.push_back(allMap[x + i][y + j]);
                        }
                    }
                }
            }
        }
    }
        if(destinationReach==false){
            printf("You can cry \n");
            return empty;
        }
    return empty;
}

std::vector<Node> Navigation::MakePath(array<array<Node,Y_MAX>,X_MAX> map, Navigation dest)
{
    vector<Node> empty;
  try {     printf("Found a path ............................................. ");
   int x = dest.node.x;
    int y = dest.node.y;
    stack<Node> path;
    vector<Node> usablePath;
    while (!(map[x][y].parentX ==x && map[x][y].parentY==y)){
        path.push(map[x][y]);
        int tmpX=map[x][y].parentX;
        int tmpY=map[x][y].parentY;
        x=tmpX;
        y=tmpY;
    }
    path.push(map[x][y]);
    Node top;
    while(!path.empty())
    {
        top=path.top();
        path.pop();
        usablePath.emplace_back(top);
    }
    affichage(TIMEOUT);
    return usablePath;
  }
  catch(const exception& e){
      printf("\033[31m ERREUR \n \033[0m");
  }
  return  empty;
}

void Navigation::Print_path(vector<Node> usablePath)
{
    Node tmp;
    for (size_t i=0; i<usablePath.size(); i++) {
        tmp=usablePath.operator[](i);
        printf(" x : %d ; y : %d \n",tmp.x,tmp.y);
    }
}


void Navigation::Navigate_to_asserv(vector<Node>usablePath, Navigation dest)
{
    printf("Conversion ............................................... \n");
    int j=0;
    int size=usablePath.size();
    struct Node position=usablePath.operator[](0);
    short dep_x=0;
    short dep_y=0;
    bool mv=0;
    while (j<size-1 && position.x!=dest.node.x && position.y!=dest.node.y) {
        //x croissant
        while(1+usablePath.operator[](j).x==usablePath.operator[](j+1).x && usablePath.operator[](j).y==usablePath.operator[](j+1).y){
            dep_x+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x+dep_x,.y=position.y});
            mv=0;
            position.x+=dep_x;
            dep_x=0;
        }

        //x décroissant
        while (usablePath.operator[](j).x-1==usablePath.operator[](j+1).x &&usablePath.operator[](j).y==usablePath.operator[](j+1).y) {
            dep_x+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x-dep_x,.y=position.y});
            mv=0;
            position.x-=dep_x;
            dep_x=0;
        }

        //y croissant
        while (usablePath.operator[](j).x==usablePath.operator[](j+1).x && 1+usablePath.operator[](j).y==usablePath.operator[](j+1).y) {
            dep_y+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x,.y=position.y+dep_y});
            mv=0;
            position.y+=dep_y;
            dep_y=0;
        }

        //y décroissant
        while (usablePath[j].x==usablePath.operator[](j+1).x && usablePath.operator[](j).y-1==usablePath.operator[](j+1).y) {
            dep_y+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x,.y=position.y-dep_y});
            mv=0;
            position.y-=dep_y;
            dep_y=0;
        }

        //x croissant y croissant
        while (usablePath.operator[](j).x+1==usablePath.operator[](j+1).x && usablePath.operator[](j).y+1==usablePath.operator[](j+1).y) {
            dep_x+=1;
            dep_y+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x+dep_x,.y=position.y+dep_y});
            mv=0;
            position.y+=dep_y;
            position.x+=dep_x;
            dep_x=0;
            dep_y=0;
                j-=1;
        }

        //x croissant y décroissant
        while (usablePath.operator[](j).x+1==usablePath.operator[](j+1).x && usablePath.operator[](j).y-1==usablePath.operator[](j+1).y) {
            dep_x+=1;
            dep_y+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x+dep_x,.y=position.y-dep_y});
            mv=0;
            position.y-=dep_y;
            position.x+=dep_x;
            dep_x=0;
            dep_y=0;
                j-=1;
        }
        //x décroissant y croissant
        while (usablePath.operator[](j).x-1==usablePath.operator[](j+1).x && usablePath.operator[](j).y+1==usablePath.operator[](j+1).y) {
            dep_x+=1;
            dep_y+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x-dep_x,.y=position.y+dep_y});
            mv=0;
            position.y+=dep_y;
            position.x-=dep_x;
            dep_x=0;
            dep_y=0;
                j-=1;
        }

        //x décroissant y décroissant
        while (usablePath.operator[](j).x-1==usablePath.operator[](j+1).x && usablePath.operator[](j).y-1==usablePath.operator[](j+1).y) {
            dep_x+=1;
            dep_y+=1;
            j+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=position.x-dep_x,.y=position.y-dep_y});
            mv=0;
            position.y-=dep_y;
            position.x-=dep_x;
            dep_x=0;
            dep_y=0;
                j-=1;
        }
        j+=1;
    }
    Asservissement::go_to({.x=dest.node.x,.y=dest.node.y});
}

Navigation::~Navigation()
{

}

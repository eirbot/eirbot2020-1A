#include "navigation.h"

using namespace std;

bool Navigation::isValid(int x, int y) //Permet de savoir si un noeud est un obstacle (renvoie vrai si ce n'est pas un obstacle)
{
    if (world.obstacle(x,y)==true){
        return false;
    }

}

bool Navigation::isDestination(int x, int y, Node dest) //Permet de savoir si o est arrivé à destination
{
    if (x==dest.x && y==dest.y){
        return true;
    }
    return false;
}

double Navigation::calculateE(int x, int y, Node dest) //Permet de calculer la distance euclidienne
{
    double E = (sqrt((x - dest.x)*(x - dest.x) + (y - dest.y)*(y - dest.y)));
    return E;
}

bool Navigation::onTable(Node pos)
{
    if(pos.x>3000 || pos.x<0){
        return false;
    }
    if(pos.y>2000 || pos.y<0){
        return false;
    }
    return true;
}

Navigation::Navigation():
{

}

Navigation::Navigation(Node src, Node dst)
{

}

std::vector<Node> Navigation::Astar(Node src, Node dest)
{
    vector<Node> empty;
    if (Navigation::isValid(dest.x, dest.y)==false){
        printf("Destination is an obstacle");
        return empty;
        //Si l'arrivée est un obstacle on ne fait rien
    }
    if (Navigation::isDestination(src.x, src.y, dest)==true){
        printf("You are the destination");
        return empty;
        //Si la source et l'arrivée sont confondues
    }
    if (Navigation::onTable(dest)==false){
        printf("Think outside the box");
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
    int x=src.x;
    int y=src.y;
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
    while(!openList.empty() && openList.size()<X_MAX*Y_MAX){
        Node node;
        do{
            float tmp=FLT_MAX;
            vector<Node>::iterator itNode; //Merci Openclassroom
            for (vector<Node>::iterator it=openList.begin(); it!=openList.end() ; next(it)) {
                Node n=* it;
                if (n.fcost<tmp) {
                    tmp=n.fcost;
                    itNode=it;
                }
                node =*itNode;
                openList.erase(itNode);
            }

        }while(isValid(node.x,node.y)==false);
        x=node.x;
        y=node.y;
        closedList[x][y]=true;
        //On ajoute les voisins dans la closed list
        for (int i= -1 ; i<=1; i++) {
            for (int j=-1; j<=1; j++) {
                double fNew,gNew,hNew;
                if (isValid(x+i,y+j)) {
                    if (isDestination(x+i,y+j,dest)) {
                        allMap[x+i][y+j].parentX=x;
                        allMap[x+i][y+j].parentY=y;
                        destinationReach=true;
                        //TODO makepath
                    }
                }
            }

        }
    }

}

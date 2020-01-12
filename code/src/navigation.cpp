#include "navigation.h"

using namespace std;

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
    return lhs.fcost < rhs.fcost;
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
        printf("Destination is an obstacle \n");
        return empty;
        //Si l'arrivée est un obstacle on ne fait rien
    }
    if (Navigation::isDestination(src.node.x, src.node.y, dest)==true){
        printf("You are the destination \n");
        return empty;
        //Si la source et l'arrivée sont confondues
    }
    if (Navigation::onTable(dest)==false){
        printf("Think outside the box \n");
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
    Node n;
    Node node;
    vector<Node>::iterator itNode; //Merci Openclassroom
    while(!openList.empty()&&openList.size()<(X_MAX*Y_MAX)){
    float tmp=FLT_MAX;
        do{
            for (vector<Node>::iterator it=openList.begin(); it!=openList.end() ; it=next(it)) {
                n=*it;
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
                        printf("je le fais !\n");
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
  try {     printf("Found a path \n");
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
    return usablePath;
  }
  catch(const exception& e){
      printf("Erreur");
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

void Navigation::Navigate_to_asserv(vector<Node>usablePath)
{
    printf("Conversion \n");
    Node tmp;
    int j=0;
    tmp.x=usablePath.operator[](0).x;
    tmp.y=usablePath.operator[](0).y;
    short size=usablePath.size();
    short dep_x=0; //déplacement à faire en x
    short dep_y=0; //déplacement à faire en y
    int i=0; //compteur
    int mv=0; //Flag pour savoir si il faut bouger
    while(j<size-1){
        //x positif
        while(1+usablePath.operator[](i).x == usablePath.operator[](i+1).x && usablePath.operator[](i).y==usablePath.operator[](i+1).y){
            i=i+1;
            dep_x+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x+dep_x, .y=tmp.y});
            mv=0;
            tmp.x+=dep_x;
            dep_x=0;
            j+=i;
        }
        //x négatif
                while(usablePath.operator[](i).x-1 == usablePath.operator[](i+1).x && usablePath.operator[](i).y==usablePath.operator[](i+1).y){
            i=i+1;
            dep_x+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x-dep_x, .y=tmp.y});
            mv=0;
            tmp.x-=dep_x;
            dep_x=0;
            j+=i;
        }

        //y positif
        while(1+usablePath.operator[](i).y == usablePath.operator[](i+1).y && usablePath.operator[](i).x==usablePath.operator[](i+1).x){
            i=i+1;
            dep_y+=1;
            mv=1;

        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x, .y=tmp.y+dep_y});
            mv=0;
            tmp.y+=dep_y;
            dep_y=0;
            j+=i;
        }

        //y négatif
        while(usablePath.operator[](i).y-1 == usablePath.operator[](i+1).y && usablePath.operator[](i).x==usablePath.operator[](i+1).x){
            i=i+1;
            dep_y+=1;
            mv=1;

        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x, .y=tmp.y-dep_y});
            mv=0;
            tmp.y-=dep_y;
            dep_y=0;
            j+=i;
        }

        //diag haut droite
        while(1+usablePath.operator[](i).y == usablePath.operator[](i+1).y && 1+usablePath.operator[](i).x==usablePath.operator[](i+1).x){
            i=i+1;
            dep_y+=1;
            dep_x+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x+dep_x, .y=tmp.y+dep_x});
            mv=0;
            tmp.x+=dep_x;
            tmp.y+=dep_y;
            dep_y=dep_x=0;
            j+=i;
        }

        //diag bas gauche
        while(usablePath.operator[](i).y-1 == usablePath.operator[](i+1).y && usablePath.operator[](i).x-1==usablePath.operator[](i+1).x){
            i=i+1;
            dep_y+=1;
            dep_x+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x-dep_x, .y=tmp.y-dep_y});
            mv=0;
            tmp.x-=dep_x;
            tmp.y-=dep_y;
            dep_y=dep_x=0;
            j+=i;
        }

        //diag bas droite
        while(usablePath.operator[](i).y+1 == usablePath.operator[](i+1).y && usablePath.operator[](i).x-1==usablePath.operator[](i+1).x){
            i=i+1;
            dep_y+=1;
            dep_x+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x-dep_x, .y=tmp.y+dep_y});
            mv=0;
            tmp.x+=dep_x;
            tmp.y-=dep_y;
            dep_y=dep_x=0;
            j+=i;
        }

        //diag haut gauche
        while(usablePath.operator[](i).y-1 == usablePath.operator[](i+1).y && usablePath.operator[](i).x+1==usablePath.operator[](i+1).x){
            i=i+1;
            dep_y+=1;
            dep_x+=1;
            mv=1;
        }
        if (mv==1) {
            Asservissement::go_to({.x=tmp.x+dep_x, .y=tmp.y-dep_y});
            mv=0;
            tmp.x+=dep_x;
            tmp.y-=dep_y;
            dep_y=dep_x=0;
            j+=i;
        }

    }
    j+=1;
}

Navigation::~Navigation()
{

}

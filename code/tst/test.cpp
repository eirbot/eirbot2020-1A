#include "test.hpp"
int main(int argc, char *argv[]) {
    printf("Test en cours veuillez patienter \n");
    Node src;
    src.x=0;
    src.y=0;
    Node dest;
    dest.x=0;
    dest.y=0;
    std::vector<Node> result;
    for (int i=0; i < 299; i++) {
        dest.x=i;
        printf(" .");
        for (int j=0; j < 199; j++) {
            dest.y=j;
            printf("%d %d \n",i, j);
            result=Navigation::Astar(src,dest);
        }
    }
    printf("\n");
    return 0;
}

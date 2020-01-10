#include "test.hpp"
int main(int argc, char *argv[]) {
    printf("Test en cours veuillez patienter");
    Node src;
    src.x=12;
    src.y=0;
    Node dest;
    dest.x=0;
    dest.y=0;
    std::vector<Node> result;
    for (int i=0; i < 300; i++) {
        dest.x+=1;
        printf(" .");
        for (int j=0; j < 200; j++) {
            dest.y+=1;
            result=Navigation::Astar(src,dest);
        }
    }
    printf("\n");
    printf("%d \n",test);
    return 0;
}

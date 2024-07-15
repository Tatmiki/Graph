#include <stdio.h>
#include <stdlib.h>
#include "../../include/Graph.h"

// 1. tamanhos em mb
int main()
{
    M_Graph G = mg_makeGraphFromFile("./graphs/grafo_1.txt");
    printf("Tamanho do grafo 1 em MB: %lf\n", mg_representationSize(mg_getNumOfVertexes(G)) / 1000000.);
    //printf("vertices: %d\narestas: %d\n", mg_getNumOfVertexes(G), mg_getNumOfEdges(G));
    getchar();
    //mg_destroyGraph(&G);
}
    // printf("Diametro: %d", lg_aprroximateDiameter(G));
    // printf("Distancia entre 10 e 20: %d\n", lg_distance(G, 10, 20));
    // printf("Distancia entre 10 e 30: %d\n", lg_distance(G, 10, 30));
    // printf("Distancia entre 20 e 30: %d\n", lg_distance(G, 20, 30));
    // l_ConnectedComponents lcc = lg_connectedComponents(G);
    // cc_listCComponents(lcc);
    // cc_destroyCComponents(&lcc);
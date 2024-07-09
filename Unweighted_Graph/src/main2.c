#include <stdio.h>
#include <stdlib.h>
#include "../include/Graph.h"

// 1. tamanhos em mb
int main()
{
    printf("Tamanho do grafo 1 em MB: %llu\n", lg_representationSize(10000, 109925));
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    printf("vertices: %d\narestas: %d\n", lg_getNumOfVertexes(G), lg_getNumOfEdges(G));
    getchar();
    lg_destroyGraph(&G);
}
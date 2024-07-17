#include <stdio.h>
#include "../../include/Graph.h"

int main()
{
    LW_Graph G = lwg_makeGraphFromFile("./graphs/grafo_W_1.txt");
    printf("Vertices: %d\nArestas: %d\n", lwg_getNumOfVertexes(G), lwg_getNumOfEdges(G));
    //printf("Distância: %.2lf\n", lwg_distance(G, 20, 10, "./graphs/output/sp.txt"));
    lwg_dijkstraHeap(G, 10, "./graphs/output/djH.txt");
    printf("%d\n", lwg_dijkstraVet(G, 20, "./graphs/output/djH2.txt"));
    //lwg_show(G);
    lwg_destroyGraph(&G); 
}
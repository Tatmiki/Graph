#include <stdio.h>
#include "../../include/Graph.h"

int main()
{
    LW_Graph G = lwg_makeGraphFromFile("./graphs/grafo_p.txt");
    printf("Vertices: %d\n Arestas: %d\n", lwg_getNumOfVertexes(G), lwg_getNumOfEdges(G));
    printf("Peso entre 1 e 2: %.2lf\n", lwg_getEdge(G, 1, 2));
    lwg_show(G);
    lwg_destroyGraph(&G);
}
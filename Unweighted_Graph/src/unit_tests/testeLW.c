#include <stdio.h>
#include <stdlib.h>
#include "../../include/Graph.h"

int main()
{
    MW_Graph G = mwg_makeGraphFromFile("./graphs/grafo_W_1.txt");
    printf("%.2f\n", mwg_getEdge(G,1,2));
    printf("%d\n", mwg_getNumOfEdges(G));
    
    //printf("vertices: %d\narestas: %d\n", mg_getNumOfVertexes(G), mg_getNumOfEdges(G));
    getchar();
    mwg_show(G);
    mwg_destroyGraph(&G);
}
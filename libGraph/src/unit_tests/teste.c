#include <stdio.h>
#include <stdlib.h>
#include "../../include/Graph.h"

int main()
{
    MW_Graph G = mwg_makeGraphFromFile("./graphs/grafo_W_1.txt");
    
    double *vet = mwg_dijkstraHeap(G, 1, NULL);

    for(vertex w = 0; w < mwg_getNumOfVertexes(G); w++)
        printf("%.2lf\n", vet[w]);

    free(vet);
    mwg_destroyGraph(&G);
}
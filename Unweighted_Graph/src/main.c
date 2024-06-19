#include <stdio.h>
#include "../include/L_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    lg_bsf(G, 4, "./graphs/bfsL.txt");
    lg_destroyGraph(&G);
}
#include <stdio.h>
#include "../../include/Graph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    lg_recursiveDfs(G, 1, "./graphs/output/dfsL.txt");

    lg_destroyGraph(&G);
}
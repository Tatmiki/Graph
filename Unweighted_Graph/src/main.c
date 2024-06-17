#include <stdio.h>
#include "../include/L_UGraph.h"
#include "../include/M_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    //printf("%d\n", lg_removeEdge(G, 9999, 5283));
    if(G != NULL)
        lg_show(G);
    else printf("ERRO!\n");
}
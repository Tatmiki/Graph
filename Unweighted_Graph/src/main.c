#include <stdio.h>
#include "../include/L_UGraph.h"
#include "../include/M_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    if(G != NULL)
        lg_outputFile(G, "./graphs/saidaL.txt");
    lg_destroyGraph(&G);
}
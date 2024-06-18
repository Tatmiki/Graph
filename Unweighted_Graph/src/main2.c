#include <stdio.h>
#include "../include/L_UGraph.h"
#include "../include/M_UGraph.h"

int main()
{
    M_Graph G = mg_makeGraphFromFile("./graphs/grafo_1.txt");
    if(G != NULL)
        mg_outputFile(G, "./graphs/saida.txt");
}
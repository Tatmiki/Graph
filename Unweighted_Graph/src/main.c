#include <stdio.h>
#include "../include/L_UGraph.h"
#include "../include/M_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraph(10);
    lg_insertEdge(G, 1, 2);
    lg_insertEdge(G, 2, 4);
    lg_insertEdge(G, 2, 3);
    lg_insertEdge(G, 3, 5);
    lg_insertEdge(G, 3, 7);
    lg_insertEdge(G, 4, 5);
    lg_insertEdge(G, 6, 7);
    lg_insertEdge(G, 6, 8);
    lg_insertEdge(G, 7, 8);
    lg_insertEdge(G, 8, 9);
    lg_insertEdge(G, 9, 10);
    lg_show(G);
    lg_bsf(G, 4, "./graphs/bfsL.txt");
    lg_destroyGraph(&G);
}
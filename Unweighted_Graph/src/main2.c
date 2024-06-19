#include <stdio.h>
#include "../include/M_UGraph.h"

int main()
{
    M_Graph G = mg_makeGraph(10);
    mg_insertEdge(G, 1, 2);
    mg_insertEdge(G, 2, 4);
    mg_insertEdge(G, 2, 3);
    mg_insertEdge(G, 3, 5);
    mg_insertEdge(G, 3, 7);
    mg_insertEdge(G, 4, 5);
    mg_insertEdge(G, 6, 7);
    mg_insertEdge(G, 6, 8);
    mg_insertEdge(G, 7, 8);
    mg_insertEdge(G, 8, 9);
    mg_insertEdge(G, 9, 10);
    mg_show(G);
    mg_bsf(G, 4, "./graphs/bfsM.txt");
    mg_destroyGraph(&G);
}
#include <stdio.h>
#include "../include/L_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraph(6);
    lg_insertEdge(G, 1, 2);
    lg_insertEdge(G, 1, 5);
    lg_insertEdge(G, 2, 5);
    lg_insertEdge(G, 2, 3);
    lg_insertEdge(G, 5, 4);
    lg_insertEdge(G, 3, 4);
    lg_insertEdge(G, 4, 6);
    lg_bfs(G,4,"./graphs/bfsL.txt");
    printf("%d",lg_distance(G,1,6));
    lg_destroyGraph(&G);
}
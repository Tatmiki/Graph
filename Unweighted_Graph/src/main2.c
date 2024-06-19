#include <stdio.h>
#include "../include/M_UGraph.h"

int main()
{
    M_Graph G = mg_makeGraphFromFile("./graphs/grafo_1.txt");
    mg_dfs(G, 279, "./graphs/dfsM.txt");
    mg_destroyGraph(&G);
}

// int main()
// {
//     M_Graph G = mg_makeGraph(6);
//     mg_insertEdge(G, 1, 2);
//     mg_insertEdge(G, 1, 5);
//     mg_insertEdge(G, 2, 5);
//     mg_insertEdge(G, 2, 3);
//     mg_insertEdge(G, 5, 4);
//     mg_insertEdge(G, 3, 4);
//     mg_insertEdge(G, 4, 6);
//     mg_show(G);
//     mg_dfs(G, 6, "./graphs/dfsM.txt");
//     mg_destroyGraph(&G);
// }

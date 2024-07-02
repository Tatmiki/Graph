#include <stdio.h>
#include "../include/M_UGraph.h"

int main()
{
    M_Graph G = mg_makeGraphFromFile("./graphs/grafo_1.txt");
    //mg_show(G);
    printf("%d\n", mg_bfs(G, 1, "./graphs/output/bfsM.txt"));
    mg_destroyGraph(&G);
}

// int main()
// {
//     M_Graph G = mg_makeGraph(6);
//     mg_insertEdge(G, 1, 2);
//     mg_insertEdge(G, 1, 6);
//     mg_insertEdge(G, 2, 5);
//     mg_insertEdge(G, 2, 3);
//     mg_insertEdge(G, 3, 4);
//     mg_insertEdge(G, 4, 5);
//     mg_insertEdge(G, 5, 6);
//     mg_show(G);
//     mg_bfs(G, 2, "./graphs/output/bfsM.txt");
//     printf("%d\n", mg_absoluteDiameter(G));
//     mg_destroyGraph(&G);
// }

// int main()
// {
//     M_Graph G = mg_makeGraph(10);
//     mg_insertEdge(G, 1, 2);
//     mg_insertEdge(G, 2, 3);
//     mg_insertEdge(G, 2, 4);
//     mg_insertEdge(G, 3, 5);
//     mg_insertEdge(G, 4, 5);
//     mg_insertEdge(G, 3, 7);
//     mg_insertEdge(G, 7, 6);
//     mg_insertEdge(G, 7, 8);
//     mg_insertEdge(G, 6, 8);
//     mg_insertEdge(G, 8, 9);
//     mg_insertEdge(G, 9, 10);

//     mg_show(G);
//     printf("%d\n", mg_diameter(G));
//     mg_destroyGraph(&G);
// }
#include <stdio.h>
#include "../include/L_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_6.txt");
    printf("a\n");
    printf("Excentricidade o vértice 2: %d\n", lg_vertexEccentricity(G, 2));
    printf("Diametro aproximado do grafo: %d\n", lg_aprroximateDiameter(G));
    //printf("Diametro absoluto do grafo: %d\n", lg_absoluteDiameter(G));
    printf("Distância entre os vértices 2 e 1: %d\n", lg_distance(G, 1, 2));
    l_ConnectedComponents lcc = lg_connectedComponents(G);
    lg_listCComponents(lcc);
    printf("sair: "); getchar();
    lg_destroyCComponents(&lcc);
    lg_destroyGraph(&G);
}

// int main()
// {
//     L_Graph G = lg_makeGraph(6);
//     printf("a\n");
//     lg_insertEdge(G, 1, 2);
//     printf("a\n");
//     lg_insertEdge(G, 1, 6);
//     printf("b\n");
//     lg_insertEdge(G, 2, 5);
//     lg_insertEdge(G, 2, 3);
//     lg_insertEdge(G, 3, 4);
//     lg_insertEdge(G, 4, 5);
//     lg_insertEdge(G, 5, 6);
//     lg_show(G);
//     lg_bfs(G, 2, "./graphs/output/bfsM.txt");
//     printf("%d\n", lg_absoluteDiameter(G));
//     lg_destroyGraph(&G);
// }

// int main()
// {
//     L_Graph G = lg_makeGraph(13);
//     lg_insertEdge(G, 1, 7);
//     lg_insertEdge(G, 1, 3);
//     lg_insertEdge(G, 1, 2);
//     lg_insertEdge(G, 1, 6);
//     lg_insertEdge(G, 6, 5);
//     lg_insertEdge(G, 6, 4);
//     lg_insertEdge(G, 7, 5);

//     lg_insertEdge(G, 8, 9);

//     lg_insertEdge(G, 10, 11);
//     lg_insertEdge(G, 10, 13);
//     lg_insertEdge(G, 10, 12);
//     lg_insertEdge(G, 12, 13);

//     //lg_show(G);

//     printf("Excentricidade o vértice 2: %d\n", lg_vertexEccentricity(G, 2));
//     printf("Diametro aproximado do grafo: %d\n", lg_aprroximateDiameter(G));
//     printf("Diametro absoluto do grafo: %d\n", lg_absoluteDiameter(G));
//     printf("Distância entre os vértices 2 e 1: %d\n", lg_distance(G, 1, 2));
//     l_ConnectedComponents lcc = lg_connectedComponents(G);
//     lg_listCComponents(lcc);
//     lg_destroyCComponents(&lcc);
//     lg_destroyGraph(&G);
// }
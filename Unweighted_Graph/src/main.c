#include <stdio.h>
#include "../include/L_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    
    lg_bfs(G, 1 ,"./graphs/output/bfsL.txt");
    lg_dfs(G, 1 ,"./graphs/output/dfsL.txt");
    //printf("%d", lg_absoluteDiameter(G));
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
#include <stdio.h>
#include "../include/L_UGraph.h"

int main()
{
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_1.txt");
    
    lg_bfs(G, 1 ,"./graphs/output/bfsL.txt");
    lg_dfs(G, 1 ,"./graphs/output/dfsL.txt");
    printf("%d", lg_diameter(G));
    lg_destroyGraph(&G);
}
#include <stdio.h>
#include <string.h>
#include "../../include/Graph.h"

/*
    Considere a rede de colaboração entre pesquisadores da área de Computação disponível no
    website da disciplina, onde o peso da aresta indica a proximidade entre os pesquisadores (peso
    é inversamente proporcional ao número de artigos publicados em co-autoria). Responda às
    perguntas abaixo.

    1. Calcule a distância e o caminho mínimo entre Edsger W. Dijkstra (o pesquisador) e os
    seguintes pesquisadores da rede de colaboração: Alan M. Turing, J. B. Kruskal, Jon M.
    Kleinberg, Éva Tardos, Daniel R. Figueiredo. Utilize exatamente estes nomes (strings)
    para identificar os Índices dos vértices no grafo.
*/

typedef struct
{
    vertex node;
    char name[50];
} Searcher;

vertex findVertex(char *name)
{
    FILE *f = fopen("./graphs/rede_colaboracao_vertices.txt", "r");
    vertex searcherVertex;
    char searcherName[50];
    while(fscanf(f, "%d,%50[^\n]", &searcherVertex, searcherName) != EOF)
    {
        if(strcmp(searcherName, name) == 0)
        {
            fclose(f); 
            return searcherVertex;
        }
    }
    fclose(f);
    return -1;
}

int main()
{
    LW_Graph G = lwg_makeGraphFromFile("./graphs/rede_colaboracao.txt");

    printf("Tamanho da rede (num. de vértices): %d\n", lwg_getNumOfEdges(G));
    printf("Conexões totais (num. de arestas): %d\n", lwg_getNumOfEdges(G));

    // Busca de Alan M. Turing
    printf("Inciando busca dos pontos dos pesquisadores...\n"); 
    Searcher searchers[6];
    searchers[0] = (Searcher) {findVertex("Edsger W. Dijkstra"), "Edsger W. Dijkstra"};
    searchers[1] = (Searcher) {findVertex("Alan M. Turing"), "Alan M. Turing"};
    searchers[2] = (Searcher) {findVertex("J. B. Kruskal"), "J. B. Kruskal"};
    searchers[3] = (Searcher) {findVertex("Jon M. Kleinberg"), "Jon M. Kleinberg"};
    searchers[4] = (Searcher) {findVertex("Éva Tardos"), "Éva Tardos"};
    searchers[5] = (Searcher) {findVertex("Daniel R. Figueiredo"), "Daniel R. Figueiredo"};
    printf("Concluido!\n\n");

    double distance;
     
    for(int i = 1; i < 6; i++)
    {
        printf("aqui1\n");
        distance = lwg_distanceHeapDjk(G, searchers[0].node, searchers[i].node, "./graphs/output/distanceName");
        //distance = lwg_distanceVetDjk(G, searchers[0].node, searchers[i].node, "./graphs/output/distanceName");
        //lwg_dijkstraVet(G, searchers[0].node, "./graphs/output/cade.txt");
        printf("aqui2\n");
        if(distance != -1)
            printf("~ A distância entre %s e %s é de %.2lf\n", searchers[0].name, searchers[i].name, distance);
        else
            printf("~ Não há caminho entre %s e %s!\n", searchers[0].name, searchers[i].name);
    }
    lwg_destroyGraph(&G);
}
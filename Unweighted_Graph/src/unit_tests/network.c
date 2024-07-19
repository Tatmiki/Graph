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

vertex findVertex(char *name);
void readSearchersFromFile(Searcher searchers[], int quantity, char *path);

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

    // Calculando as distãncias mónimas e gerando um arquivon de caminhos mínimos
    double distance;
    vertex w;
    char path[30] = "./graphs/output/caminhoMin_X"; // X na pos 27
    for(w = 1; w < lwg_getNumOfVertexes(G); w++)
    {
        path[27] = '1' + w;
        distance = lwg_distanceHeapDjk(G, searchers[0].node, searchers[w].node, path);
        if(distance != -1)
            printf("~ A distância de %s para %s eh de: %.2lf\n", searchers[0].name, searchers[w].name, distance);
        else
            printf("Nao ha caminho entre %s e %s!\n", searchers[0].name, searchers[w].name);
    }
    
    int searchersQuantity = lwg_getNumOfVertexes(G);
    lwg_destroyGraph(&G);

    // Lendo todos os pesquisadores para iterar sobre os caminhos mínimos
    Searcher *listOfSearchers = (Searcher*) malloc(sizeof(Searcher) * searchersQuantity);
    readSearchersFromFile(searchers, searchersQuantity, "./graphs/rede_colaboracao_vertices.txt");

    // Editando os arquivos de saída de caminhos mínimos para suportar os nomes

    return 0;
}

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

void readSearchersFromFile(Searcher searchers[], int quantity, char *path)
{
    FILE *f = fopen(path, "r");
    int i = 0;
    while(fscanf(f, "%d,%50[^\n]", &searchers[i].node, searchers[i].name) != EOF && i < quantity);
    fclose(f);
}
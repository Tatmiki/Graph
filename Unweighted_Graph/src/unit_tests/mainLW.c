#include <stdio.h>
#include <stdlib.h>
#include "../../include/Graph.h"

int main()
{
    //Montando grafo apartir de um arquivo
    LW_Graph G = lwg_makeGraphFromFile("./graphs/grafo_testeWL.txt");
    if(G == NULL)
    {
        printf("Arquivo do grafo não foi encontrado!\n");
        return 0;
    }
    /*
        Para criar o seu próprio grafo, utilize a função lwg_makeGraph(int V), sendo V a quantidade de vértices que pertencerão
        ao grafo. Assim, ao criar o seu grafo, utilize a função mg_insertEdge(G, v, u, w) para adicionar ao grafo G uma arestas 
        entre o vértice v e o vértice u e o seu peso w.

        Ex:
            LW_Graph G = mg_makeGraph(2);
            mg_insertEdge(G, 1, 2, 10);
            .
            .
            .
    */
   
    //Exibindo grafo ponderado
    lwg_show(G);

    //Exibindo tamanho do grafo em MBs
    printf("\nTamanho do arquivo em MB: %lf\n", (lwg_representationSize((long long)lwg_getNumOfVertexes(G), (long long)lwg_getNumOfEdges(G))/1000000.));

     //Exibe o peso da aresta entre dois vértices
    printf("Peso da aresta: %.2lf\n",lwg_getEdge(G, 1, 2));

    //verificação da existência de uma aresta utilizando inserção e remoção
    if(lwg_getEdge(G, 1, 4) == -1)
        printf("Nao existe\n");
    lwg_insertEdge(G, 1, 4, 15.50);
    if(lwg_getEdge(G, 1, 4))
        printf("Existe - Peso: %.2lf\n", lwg_getEdge(G, 1, 4));
    lwg_removeEdge(G, 1, 4);
    if(lwg_getEdge(G, 1, 4) == -1)
        printf("Nao existe\n");

    //Exibindo némero de arestas e de vértices
    printf("Quant. Arestas: %d\n",lwg_getNumOfEdges(G));
    printf("Quant. vertices: %d\n",lwg_getNumOfVertexes(G));

    //Dijkstras
    free(lwg_dijkstraHeap(G, 1, "./graphs/output/saidaDijksHEAP_LW.txt"));
    free(lwg_dijkstraVet(G, 1, "./graphs/output/saidaDijksVET_LW.txt"));

    //Distancia mínima e caminho mínimo entre dois vértices
    lwg_distanceHeapDjk(G, 1, 3, "./graphs/output/saidaDistance_LW.txt");

    //Desalocamento
    lwg_destroyGraph(&G);
}
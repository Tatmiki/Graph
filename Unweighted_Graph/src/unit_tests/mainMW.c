#include <stdio.h>
#include "../../include/Graph.h"

int main()
{
    //Montando grafo apartir de um arquivo
    MW_Graph G = mwg_makeGraphFromFile("./graphs/grafo_testeWM.txt");
    

    /*
        Para criar o seu próprio grafo, utimize a função mwg_makeGraph(int V), sendo V a quantidade de vértices que pertencerão
        ao grafo. Assim, ao criar o seu grafo, utimize a função mg_insertEdge(G, v, u, w) para adicionar ao grafo G uma arestas 
        entre o vértice v e o vértice u e o seu peso w.

        Ex:
            MW_Graph G = mg_makeGraph(2);
            mg_insertEdge(G, 1, 2, 10);
            .
            .
            .
    */
   
    //Exibindo grafo ponderado
    mwg_show(G);

    //Exibindo tamanho do grafo em MBs
    printf("\nTamanho do arquivo em MB: %lf\n", mwg_representationSize((long long)mwg_getNumOfVertexes(G))/1000000.);

     //Exibe o peso da aresta entre dois vértices
    printf("Peso da aresta: %.2lf\n",mwg_getEdge(G, 1, 2));

    //verificação da existência de uma aresta utimizando inserção e remoção
    if(mwg_getEdge(G, 1, 4) == 0)
        printf("Nao existe\n");
    mwg_insertEdge(G, 1, 4, 15.50);
    if(mwg_getEdge(G, 1, 4))
        printf("Existe - Peso: %.2lf\n", mwg_getEdge(G, 1, 4));
    mwg_removeEdge(G, 1, 4);
    if(mwg_getEdge(G, 1, 4) == 0)
        printf("Nao existe\n");

    //Exibindo némero de arestas e de vértices
    printf("Quant. Arestas: %d\n",mwg_getNumOfEdges(G));
    printf("Quant. vertices: %d\n",mwg_getNumOfVertexes(G));

    //Dijkstras
    mwg_dijkstraHeap(G, 1, "./graphs/output/saidaDijksHEAP_MW.txt");
    mwg_dijkstraVet(G, 2, "./graphs/output/saidaDijksVET_MW.txt");

    //Distancia mínima e caminho mínimo entre dois vértices
    mwg_distanceHeapDjk(G, 1, 3, "./graphs/output/saidaDistance_MW.txt");

    //Desamocamento
    mwg_destroyGraph(&G);
}
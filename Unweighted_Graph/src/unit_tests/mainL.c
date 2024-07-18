#include <stdio.h>
#include "../../include/Graph.h"

int main()
{   
    int id;
    //Montando grafo apartir de um arquivo
    L_Graph G = lg_makeGraphFromFile("./graphs/grafo_testeL.txt"); //Adicione aqui o endereço do arquivo 

    /*
        Para criar o seu próprio grafo, utilize a função lg_makeGraph(int V), sendo V a quantidade de vértices que pertencerão
        ao grafo. Assim, ao criar o seu grafo, utilize a função lg_insertEdge(G, v, w) para adicionar ao grafo G uma arestas 
        entre o vértice v e o vértice w.

        Ex:
            L_Graph G = lg_makeGraph(2);
            lg_insertEdge(G, 1, 2);
            .
            .
            .
    */

    //Exibindo grafo
    lg_show(G);

    //Exibindo tamanho do grafo em MBs
   printf("\nTamanho do arquivo em MB: %lf", (lg_representationSize((long long)lg_getNumOfVertexes(G), (long long)lg_getNumOfEdges(G))/1000000.));

    //Exibindo némero de arestas e de vértices
    printf("Quant. Arestas: %d\n",lg_getNumOfEdges(G));
    printf("Quant. vertices: %d\n",lg_getNumOfVertexes(G));

    //Criar arquivo vom informações sobre o grafo 
     lg_outputFile(G, "./graphs/output/meuGrafo_L.txt"); 

    //verificação da existência de uma aresta utilizando inserção e remoção
    if(!lg_getEdge(G, 1, 4))
        printf("Nao existe\n");
    lg_insertEdge(G, 1, 4);
    if(lg_getEdge(G, 1, 4))
        printf("Existe\n");
    lg_removeEdge(G, 1, 4);
    if(!lg_getEdge(G, 1, 4))
        printf("Nao existe\n");

    //BUSCAS
    lg_bfs(G, 1, "./graphs/output/saidaBFS_L.txt");
    lg_iterativeDfs(G,6,"./graphs/output/saidaIterativeDFS_L.txt");
    lg_recursiveDfs(G,6,"./graphs/output/saidaRecursiveDFS_L.txt");

    //Diametros e distancia
    printf("Eccentricity: %d\n",lg_vertexEccentricity(G, 6));
    printf("Diametro absoluto: %d\n",lg_absoluteDiameter(G)); // Não recomendado para grafos com grande quantidade de vértices e de arestas 
    printf("Diametro aproximado: %d\n",lg_aprroximateDiameter(G));
    printf("Distancia: %d\n",lg_distance(G, 1, 4));

    //Criação dos componentes conectados
    l_ConnectedComponents lcc =  lg_connectedComponents(G);

    //Funções de componentes conectados
    printf("Quantidade de componentes conectados: %d\n",cc_getNumOfCComponents(lcc));
    cc_listCComponents(lcc);
    printf("\nInforme o id do componentes conectado que deseja exibir informações e o seu tamanho: ");
    scanf("%d", &id);
    cc_showCComponent(lcc, id);
    printf("Tamanho do componente: %d\n",cc_getSizeCComponent(lcc,id));

    //Desalocamneto
    cc_destroyCComponents(&lcc);
    lg_destroyGraph(&G);
}
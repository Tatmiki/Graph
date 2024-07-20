#include <stdio.h>
#include "../../include/Graph.h"

int main()
{   
    int id;
    //Montando grafo apartir de um arquivo
    M_Graph G = mg_makeGraphFromFile("./graphs/grafo_testeL.txt"); //Adicione aqui o endereço do arquivo 
    if(G == NULL)
    {
        printf("Arquivo do grafo não foi encontrado!\n");
        return 0;
    }
    /*
        Para criar o seu próprio grafo, utilize a função mg_makeGraph(int V), sendo V a quantidade de vértices que pertencerão
        ao grafo. Assim, ao criar o seu grafo, utilize a função mg_insertEdge(G, v, w) para adicionar ao grafo G uma arestas 
        entre o vértice v e o vértice w.

        Ex:
            M_Graph G = mg_makeGraph(2);
            mg_insertEdge(G, 1, 2);
            .
            .
            .
    */

    //Exibindo grafo
    mg_show(G);

    //Exibindo tamanho do grafo em MBs
    printf("\nTamanho do arquivo em MB: %lf\n", (mg_representationSize((long long)mg_getNumOfVertexes(G))/1000000.));

    //Exibindo némero de arestas e de vértices
    printf("Quant. Arestas: %d\n",mg_getNumOfEdges(G));
    printf("Quant. vertices: %d\n",mg_getNumOfVertexes(G));

    //Criar arquivo vom informações sobre o grafo
     mg_outputFile(G, "./graphs/output/meuGrafo_M.txt"); 

    //verificação da existência de uma aresta utilizando inserção e remoção
    if(!mg_getEdge(G, 1, 4))
        printf("Nao existe\n");
    mg_insertEdge(G, 1, 4);
    if(mg_getEdge(G, 1, 4))
        printf("Existe\n");
    mg_removeEdge(G, 1, 4);
    if(!mg_getEdge(G, 1, 4))
        printf("Nao existe\n");

    //BUSCAS
    mg_bfs(G, 1, "./graphs/output/saidaBFS_L.txt");
    mg_iterativeDfs(G,6,"./graphs/output/saidaIterativeDFS_M.txt");
    mg_recursiveDfs(G,6,"./graphs/output/saidaRecursiveDFS_M.txt");

    //Diametros e distancia
    printf("Eccentricity: %d\n",mg_vertexEccentricity(G, 6));
    printf("Diametro absoluto: %d\n",mg_absoluteDiameter(G)); // Não recomendado para grafos com grande quantidade de vértices e de arestas 
    printf("Diametro aproximado: %d\n",mg_aprroximateDiameter(G));
    printf("Distancia: %d\n",mg_distance(G, 1, 4));

    //Criação dos componentes conectados
    l_ConnectedComponents lcc =  mg_connectedComponents(G);
    
    //Funções de componentes conectados
    printf("Quantidade de componentes conectados: %d\n",cc_getNumOfCComponents(lcc));
    cc_listCComponents(lcc);
    printf("\nInforme o id do componentes conectado que deseja exibir informações e o seu tamanho: ");
    scanf("%d", &id);
    cc_showCComponent(lcc, id);
    printf("Tamanho do componente: %d\n",cc_getSizeCComponent(lcc,id));
    
    //Desalocamneto
    cc_destroyCComponents(&lcc);
    mg_destroyGraph(&G);
}
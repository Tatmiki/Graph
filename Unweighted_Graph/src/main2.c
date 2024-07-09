#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "../include/Graph.h"

/*
    Criar grafo
    Criar grafo de um arquivo de texto
    Inserir aresta
    Remover aresta
    Arquivo de saída de inforamções do grafo
    BFS com arquivo de saída
    DFS com arquivo de saída
    Distância entre dois vértices
    Excentricidade de um vértice
    Diametro absoluto
    Diametro aproximado
    Gerar lista de componentes conexos
    **as funções abaixo dependem da geração da lista de cc, se a lista for vazia elas não podem ser feitas**
    Quantidade de componentes conexos do grafo
    Listagem dos componentes
    Exibição de um componente específico
    Tamanho de um componente específico
    
    *NÃO ESQUECER DE DESTRUIR AS ESTRUTURAS ANTES DO FECHAMENTO DO PROGRAMA
*/
int main()
{
    //case 1
    M_Graph G = NULL;
    int opc = 0;
    int verteces;

    //case 2 e 5
    char arquivo[50];

    //case 3
    int quant, i;
    vertex vertece1, vertece2;

    int distancia, exentricidade, diametroAbs, diametroApox, vertece;

    l_ConnectedComponents lcc = NULL;
    int id;

    while(opc != 13)
    {
        printf("\n1  - Criar um grafo\n");
        printf("2  - Criar um grafo apartir de um arquivo texto\n");
        printf("3  - Inserir aresta\n");
        printf("4  - Remover aresta\n");
        printf("5  - Criar arquivo de saida de inforamacoes do grafo\n");
        printf("6  - BFS com arquivo de saida\n");
        printf("7  - DFS com arquivo de saida\n");
        printf("8  - Distancia entre dois vertices\n");
        printf("9  - Exentricidade de um vertice\n");
        printf("10 - Diametro absoluto\n");
        printf("11 - Diametro aproximado\n");
        printf("12 - Gerar lista de componentes conexos\n");
        printf("13 - Sair");
        printf("\n\tInsira a opcao: ");
        scanf("%d", &opc);
        switch(opc)
        {
            case 1:
                mg_destroyGraph(&G);
                printf("\n~> Informe a quantidade de verteces: ");
                scanf("%d", &verteces);
                G = mg_makeGraph(verteces);
                if(G == NULL)
                    printf("Falha na criação do grafo\n");
                else    
                    printf("Criacao do grafo concluida!\n");
                break;
            case 2:
                mg_destroyGraph(&G);
                printf("\n~> Informe o arquivo: ");
                scanf(" %s", arquivo);
                G = mg_makeGraphFromFile(arquivo);
                if(G == NULL)
                    printf("Falha na criação do grafo\n");
                else    
                    printf("Criacao do grafo concluida!\n");
                break;
            case 3:
                if(G != NULL && mg_getNumOfVertexes(G) > 1) //Adicionar G->V
                {
                    printf("\n~> Informe quantas arestas deseja adicionar: ");
                    scanf("%d", &quant);
                    for(i = 0; i < quant; i++)
                    {
                        printf("\n~> Informe os dois vertices que deseja adicionar a arestas: ");
                        scanf("%u %u",&vertece1, &vertece2);
                        if(mg_insertEdge(G,vertece1, vertece2))
                            printf("Arestas inseridas com sucesso!\n");
                        else
                        {
                            printf("Falha na insercao!\n");
                            i--;
                        }
                    }
                    printf("Insercao completa!\n");
                }
                else if(mg_getNumOfVertexes(G) < 2)
                    printf("A quantidade de vertices deve ser maior que 1 para se efetuar uma adicao de aresta!\n");
                
                else
                    printf("Grafo nao criado...\n");
                break;
            case 4:
                if((G != NULL && mg_getNumOfVertexes(G) > 1) && mg_getNumOfEdges(G) > 0) //Adicionar G->V
                {
                    printf("\n~> Informe quantas arestas deseja remover: ");
                    scanf("%d", &quant);
                    for(i = 0; i < quant; i++)
                    {
                        if(mg_insertEdge(G,vertece1, vertece2))
                                printf("Aresta removida com sucesso!\n");
                        else
                        {
                            printf("Falha na remocao!\n");
                            i--;
                        }
                    }
                    printf("Remocao completa!\n");
                }
                else if(mg_getNumOfVertexes(G) < 2 || mg_getNumOfEdges(G) < 1)
                    printf("Quantidade de vertices = 1\nNecessario mais de 1 vertice para remover arestas\n");
                else
                    printf("Grafo nao criado...\n");               
                break;
            case 5:
                if(G != NULL)
                {
                    printf("\nInforme o arquivo de saida: ");
                    scanf("%s", arquivo);
                    if(mg_outputFile(G,arquivo))
                        printf("Arquivo de saída criado com sucesso!\n");
                    else    
                        printf("Falha na criação do arquivo...\n");
                }
                else
                    printf("Grafo nao criado...\n");  
                break;
            case 6:
                if(G != NULL)
                {
                    printf("\nInforme o arquivo de saida: ");
                    scanf("%s", arquivo);
                    printf("Informe de qual vertice deseja iniciar a BFS: ");
                    scanf("%u",&vertece1);
                    if(mg_bfs(G,vertece1,arquivo))
                        printf("Arquivo de saída criado com sucesso!\n");
                    else    
                        printf("Falha na criação do arquivo...\n");
                }
                else
                    printf("Grafo nao criado...\n");  
                break;
            case 7:
                if(G != NULL)
                {
                    printf("\nInforme o arquivo de saida: ");
                    scanf("%s", arquivo);
                    printf("Informe de qual vertice deseja iniciar a DFS: ");
                    scanf("%u",&vertece1);
                    if(mg_iterativeDfs(G,vertece1,arquivo))
                        printf("Arquivo de saída criado com sucesso!\n");
                    else    
                        printf("Falha na criação do arquivo...\n");
                }
                else
                    printf("Grafo nao criado...\n"); 
                break;
            case 8:
                if(G != NULL)
                {
                    printf("Digite os dois vertices que deseja buscar a distancia: ");
                    scanf("%u %u", &vertece1, &vertece2);
                    distancia = mg_distance(G, vertece1, vertece2);
                    if(distancia == -1)
                        printf("Nao ha um caminho direto entre os vertices...\n");
                    else    
                        printf("Distancia: %d\n", distancia);
                }
               else
                    printf("Grafo nao criado...\n");     

                break;
            case 9:
                if(G != NULL)
                {
                    printf("Digite o vertices que deseja buscar a exentricidade: ");
                    scanf("%d", &vertece);
                    exentricidade = mg_vertexEccentricity(G, vertece);
                    if(exentricidade == -1)
                        printf("O grafo e desconexo, sendo assim sua exentricidade e infinita...\n");
                    else    
                        printf("Exentricidade: %d\n", exentricidade);
                }
               else
                    printf("Grafo nao criado...\n");  
                break;
            case 10:
                if(G != NULL)
                {
                    diametroAbs = mg_absoluteDiameter(G);
                    if(diametroAbs == -1)
                        printf("O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro...\n");
                    else    
                        printf("Diametro absoluto: %d\n", diametroAbs);
                }
                else
                    printf("Grafo nao criado...\n");  
                break;
            case 11:
                if(G != NULL)
                {
                    diametroApox = mg_aprroximateDiameter(G);
                    if(diametroApox == -1)
                        printf("O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.s...\n");
                    else    
                        printf("Diametro aproximado: %d\n", diametroApox);
                }
                else
                    printf("Grafo nao criado...\n");
                break;
            case 12:
                lcc = mg_connectedComponents(G);
                if(lcc != NULL)
                {
                    printf("Quantidade de componentes conexos: %d\n", cc_getNumOfCComponents(lcc));
                    cc_listCComponents(lcc);
                    printf("\nInforme o id do componente para exibi-lo(Ids informados acima): ");
                    scanf("%d", &id);
                    cc_showCComponent(lcc, id-1);
                    printf("\nInforme o id do componente para saber o seu tamanho(Ids informados acima): ");
                    scanf("%d", &id);
                    printf("%d",cc_getSizeCComponent(lcc, id-1));
                }
                else
                    printf("ERRO na criação da lista de componentes conexos...");
                cc_destroyCComponents(&lcc);
                break;
            case 13:
                printf("Fechando programa!");
                break;
            default:
                printf("Insira uma opc correta!");
                break;
        }
        getche();
        system("cls");
    }
    mg_destroyGraph(&G);
    return 0;
}
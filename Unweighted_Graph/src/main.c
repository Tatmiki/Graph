#include <stdio.h>
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
    int opc = 0;
    while(opc != 14)
    {
        printf("1  - Criar um grafo");
        printf("2  - Criar um grafo apartir de um arquivo texto");
        printf("3  - Inserir aresta");
        printf("4  - Remover aresta");
        printf("5  - Criar arquivo de saida de inforamcoes do grafo");
        printf("6  - BFS com arquivo de saida");
        printf("7  - DFS com arquivo de saida");
        printf("8  - Distancia entre dois vertices");
        printf("9  - Exentricidade de um vertice");
        printf("10 - Diametro absoluto");
        printf("11 - Diametro aproximado");
        printf("12 - Gerar lista de componentes conexos");
        printf("\n\tInsira a opcao: ");
        scanf("%d", &opc);
        switch(opc)
        {
            case 1:
                int verteces;
                printf("~> Informe a quantidade de verteces: ");
                scanf("%d", &verteces);
                L_Graph G = lg_makeGraph(verteces);

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
            case 9:

                break;
            case 10:

                break;
            case 11:

                break;
            case 12:

                break;
            default:

                break;
        }
    }
}
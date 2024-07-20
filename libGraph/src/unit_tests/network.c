#include <stdio.h>
#include <stdlib.h>
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

    *Obs da solução: a saída desenvolvida nesse programa é específica ao problema abordado
    e não geneŕica, logo evite fazer grandes alterações.
*/

typedef struct
{
    vertex node;
    char name[50];
} Searcher;

vertex findVertex(char *name);
void readSearchersFromFile(Searcher *searchers, int quantity, char *path);

int main()
{
    // Cria um grafo da rede de colaboração.
    LW_Graph G = lwg_makeGraphFromFile("./graphs/rede_colaboracao.txt");
    if(G == NULL)
    {
        printf("Arquivo do grafo não foi encontrado!\n");
        return 0;
    }

    // Exibe algumas informações básicas do grafo.
    printf("Tamanho da rede (num. de vértices): %d\n", lwg_getNumOfVertexes(G));
    printf("Conexões totais (num. de arestas): %d\n", lwg_getNumOfEdges(G));

    // Busca os respectivos de cada pesquisador do problema no arquivo de vértices.
    // *Obs: optamos por não carregar o grafos e os nomes ao mesmo tempo em memória, por isso essa busca.
    printf("Inciando busca dos pontos dos pesquisadores...\n"); 
    Searcher searchers[6];
    searchers[0] = (Searcher) {findVertex("Edsger W. Dijkstra"), "Edsger W. Dijkstra"};
    searchers[1] = (Searcher) {findVertex("Alan M. Turing"), "Alan M. Turing"};
    searchers[2] = (Searcher) {findVertex("J. B. Kruskal"), "J. B. Kruskal"};
    searchers[3] = (Searcher) {findVertex("Jon M. Kleinberg"), "Jon M. Kleinberg"};
    searchers[4] = (Searcher) {findVertex("Éva Tardos"), "Éva Tardos"};
    searchers[5] = (Searcher) {findVertex("Daniel R. Figueiredo"), "Daniel R. Figueiredo"};
    printf("Concluido!\n\n");

    // Calculando as distãncias mónimas e gerando um arquivon de caminhos mínimos.
    double distance;
    vertex w;
    char path[30] = "./graphs/output/caminhoMin_X"; // X na pos 27
    for(w = 1; w < 6; w++)
    {
        path[27] = '0' + w;
        distance = lwg_distanceHeapDjk(G, searchers[0].node, searchers[w].node, path);
        if(distance != -1)
            printf("~ A distância de %s para %s eh de: %.2lf\n", searchers[0].name, searchers[w].name, distance);
        else
            printf("Nao ha caminho entre %s e %s!\n", searchers[0].name, searchers[w].name);
    }
    
    // Salva a quantidade de vértices e libera o grafo que não será mais utilizado.
    int searchersQuantity = lwg_getNumOfVertexes(G);
    lwg_destroyGraph(&G);

    // Lendo todos os pesquisadores para reescrever o arquivo de arquivos mínimos com os nomes do vértices.
    Searcher *listOfSearchers = (Searcher*) malloc(sizeof(Searcher) * searchersQuantity);
    readSearchersFromFile(listOfSearchers, searchersQuantity, "./graphs/rede_colaboracao_vertices.txt");
    
    // Editando os arquivos de saída de caminhos mínimos para suportar os nomes dos vértices.
    FILE *fin, *fout;
    char output_path[30];
    char line[15];
    for(w = 1; w < 6; w++)
    {
        // nomeia o arquivo copia de saida
        path[27] = 'X';
        strcpy(output_path, path);

        // abre o arquivo de caminhos mínimos gerado anteriormente
        path[27] = '0' + w;
        fin = fopen(path, "r");

        // verifica se o arquivo do respectivo dijkstra foi realmente gerado
        if(fin == NULL)
            continue;
        
        fout = fopen(output_path, "w"); // cria um arquivo cópia para saída com os nomes 

        fscanf(fin, "%[^\n]\n", line); // pula o START
        fprintf(fout, "START\n"); // copia o START
        while(1)
        {
            int i = fscanf(fin, "%[^\n]\n", line); // lê uma linha do arquivo de caminhos mínimos
            if(line[0] == 'E') // se ela for o END, quebra esse loop
                break;
            line[i-2] = '\0'; // retira a vírgula do final
            i = strtol(line, NULL, 10); // converte a string para o respectivo vértice numérico
            fprintf(fout, "%d, %s\n", i, listOfSearchers[i-1].name); // copia o vértice e escreve o respectivo nome para o arquivo de saída
        }
        fprintf(fout, "END\n"); // copia o END

        // fecha o arquivo de entrada e o de cópia
        fclose(fin);
        fclose(fout);

        // exclui o arquivo de entrada e renomeia a cópia com o nome do anterior.
        remove(path);
        rename(output_path, path);
    }
    free(listOfSearchers);
    
    printf("\n~ Arquivo de saída de caminhos mínimos gerados na pasta graphs/output.\n");
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

void readSearchersFromFile(Searcher *searchers, int quantity, char *path)
{
    FILE *f = fopen(path, "r");
    int i = 0;
    while(fscanf(f, "%d,%50[^\n]", &searchers[i].node, searchers[i].name) != EOF && i < quantity) i++;
    fclose(f);
}
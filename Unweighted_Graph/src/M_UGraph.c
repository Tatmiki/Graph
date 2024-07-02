#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/M_UGraph.h"
#include "../include/List.h"
#include "../include/Queue.h"

/**
 * @brief Estrutura do grafo com representação em matriz de ajacência.
 */
struct m_graph
{
    int V;   /**< Número V de vértices(vertexes). */
    int E;   /**< Número E de arestas(edges). */
    int **adj;  /**< Matriz de ajacências. */
};

/**
 * @brief Estrutura de apoio para os algoritmos de BFS e DFS.
 */
typedef struct
{
    char color;             /**< Cor do vértice ('W' - White, 'G' - Gray, 'B' - Black). **/
    int depth;              /**< Profundidade do vértice na árvore bfs ou dfs. **/
    vertex father;         /**< Pai do vértice na árvore bfs ou dfs. **/
} Vertex_info;

/** FUNÇÕES ESTÁTICAS **/

/**
 * @brief Função para alocar e retornar uma matriz de inteiros.
 * 
 * @param m Quantidade de linhas da matriz.
 * @param n Quantidade de colunas da matriz.
 * @param initVal Valor inicial dos elementos da matriz.
 * @return Retorna um vetor de inteiros alocado dinamicamente.
 */
static int** allocMatrix(int m, int n, int initVal)
{
    int **matrix = (int**) malloc(m * sizeof(int*));
    if(matrix == NULL)
        return NULL;
    int i, j;
    for(i = 0; i < m; i++)
    {
        matrix[i] = (int*) malloc(n * sizeof(int));
        if(matrix[i] == NULL)
        {
            if(i != 0)
                for(; i >= 0; i--)
                    free(matrix[i]);
            free(matrix);
            return NULL;
        }
        for(j = 0; j < n; j++)
            matrix[i][j] = initVal;
    }
    return matrix;
}

/**
 * @brief Função para desalocar uma matriz de inteiros.
 * 
 * @param matrix Endereço da matriz em questão.
 * @param n Quantidade de colunas da matriz,
 */
static void freeMatrix(int **matrix, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * @brief Troca o valor de duas variáveis inteiras
 * 
 * @param a Variável a.
 * @param b Variável b.
 */
static void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Realiza a ordenação rápida de um vetor em ordem crescente.
 * 
 * @param vet Vetor em questão.
 * @param start Início relativo ao índice do vetor (geralmente 0).
 * @param end  Final realtivo ao índice do vetor (geralmente tamanho-1).
 */
static void quicksort(int vet[], const int start, const int end)
{
    int left = start, right = end, pivot = vet[(start+end)/2];
    do
    {
        while(vet[left] < pivot) ++left;
        while(vet[right] > pivot) --right;
        if(left <= right)
        {
            swap(&vet[left], &vet[right]);
            left++; right--;
        }
    }while(left <= right);
    if(right > start) quicksort(vet, start, right); // ramo esquerdo
    if(left < end) quicksort(vet, left, end); // ramo direito
}

/**
 * @brief Realiza busca em profundidade no grafo a partir de um pivo u.
 * 
 * @param G Grafo em questão.
 * @param u Vértice inicial da busca.
 * @param vertexes Vetor que armazenará os dados da busca.
 */
static void dfs_visit(M_Graph G, vertex u, Vertex_info vertexes[])
{
    vertexes[u].color = 'G';
    vertex v;
    for(v = 0; v < G->V; v++)
    {
        if(G->adj[u][v] == 1)
        {
            if(vertexes[v].color == 'W')
            {
                vertexes[v].father = u;
                vertexes[v].depth = vertexes[u].depth + 1;
                dfs_visit(G, v, vertexes);
            }
        }
    }
    vertexes[u].color = 'B';
}

/**
 * @brief Realiza a busca em largura em um grafo G a partir de um vertice u e preenche
 * um vetor de Vertex_info com as informações da busca.
 * 
 * @param G Grafo em questão.
 * @param u Vértice incial da busca.
 * @param vertexes Vetor que armazenará os dados da busca.
 * @return Retorna a posição relativa ao vetor de vértices do vértice com maior profundidade da árvore BFS.
 */
static vertex bfs_distances(M_Graph G, vertex v, Vertex_info vertexes[])
{
    vertex w, u = v;
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1;
    }
    vertexes[v].color = 'G';
    Queue Q = q_initQueue();
    q_enqueue(Q, v);
    while(!q_isEmpty(Q))
    {
        u = q_dequeue(Q);
        for(w = 0; w < G->V; w++)
        {
            if(G->adj[u][w] == 1)
            {
                if(vertexes[w].color == 'W')
                {
                    vertexes[w].color = 'G';
                    vertexes[w].father = u;
                    vertexes[w].depth = vertexes[u].depth + 1;
                    q_enqueue(Q, w);
                }
            }
        }
        vertexes[u].color = 'B';
    }
    q_destroyQueue(&Q);
    return u; // Índice relativo ao vetor
}

/** FUNÇÕES DA BIBLIOTECA **/

M_Graph mg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f ==  NULL)
        return NULL;
    size_t V;
    vertex u, v;
    if(!fscanf(f, "%lu", &V))
    {
        fclose(f);
        return NULL;
    }
    M_Graph G = mg_makeGraph(V);
    if(G == NULL)
    {
        fclose(f);
        exit(EXIT_FAILURE);
    }
    while(fscanf(f, "%d %d", &v, &u) != EOF)
        mg_insertEdge(G, v, u);
    fclose(f);
    return G;
}

M_Graph mg_makeGraph(size_t V)
{
    M_Graph G = (struct m_graph*) malloc(sizeof(struct m_graph));
    G->V = V;
    G->E = 0;
    G->adj = allocMatrix(V, V, 0);
    return G;
}

void mg_destroyGraph(M_Graph *G)
{
    freeMatrix((*G)->adj, (*G)->V);
    free(*G);
    G = NULL;
}

int mg_insertEdge(M_Graph G, vertex v, vertex u)
{
    v--; u--;
    if(G->adj[v][u] == 0)
    {
        G->adj[v][u] = G->adj[u][v] = 1;
        G->E++;
        return 1;
    }
    return 0;
}

int mg_removeEdge(M_Graph G, vertex v, vertex u)
{
    v--; u--;
    if(G->adj[v][u] == 1)
    {
        G->adj[v][u] = G->adj[u][v] = 0;
        G->E--;
        return 1;
    }
    return 0;
}

int mg_getEdge(M_Graph G,vertex v, vertex u)
{
    return G->adj[v-1][u-1];
}

void mg_show(M_Graph G)
{
    vertex i, j;
    printf("--- MATRIZ DE ADJACÊNCIAS ---\n");
    for(i = 0; i < G->V; i++)
    {
        printf("%d", G->adj[i][0]);
        for(j = 1; j < G->V; j++)
        {
            printf(" %d", G->adj[i][j]);
        }
        putchar('\n');
    }
}

int mg_outputFile(M_Graph G, char *path)
{
    // Cria/substitui um arquivo texto chamado "saida.txt" no caminho indicado.
    FILE *f = fopen(path, "w");
    if(f == NULL) // Caso o caminho seja inválido.
        return 0;

    int minDegree = INT_MAX, maxDegree = 0;
    double mediumDegree = 0, degreeMedian;
    int vertexesDegrees[G->V];
    vertex i, j;
    for(i = 0; i < G->V; i++)
    {
        vertexesDegrees[i] = 0;
        for(j = 0; j < G->V; j++) // Calcula o grau de um vértice
        {
            vertexesDegrees[i] += G->adj[i][j];
        }
        if(vertexesDegrees[i] < minDegree) // é o menor grau?
            minDegree = vertexesDegrees[i];
        if(vertexesDegrees[i] > maxDegree) // é o maior grau?
            maxDegree = vertexesDegrees[i];
        mediumDegree += vertexesDegrees[i]; // soma para a média
    }
    // Calcula o grau médio.
    mediumDegree /= G->V;
    // Calcula a mediana
    quicksort(vertexesDegrees, 0, G->V-1);
    if(G->V % 2 != 0)
        degreeMedian = vertexesDegrees[(G->V / 2) + 1];
    else
        degreeMedian = (vertexesDegrees[G->V / 2] + vertexesDegrees[(G->V / 2) + 1]) / 2.;
    
    // Saída para o arquivo
    fprintf(f, "numberOfVertexes=%d\n", G->V);
    fprintf(f, "numberOfEdges=%d\n", G->E);
    fprintf(f, "minDegree=%d\n", minDegree);
    fprintf(f, "maxDegree=%d\n", maxDegree);
    fprintf(f, "mediumDegree=%lf\n", mediumDegree);
    fprintf(f, "degreeMedian=%lf\n", degreeMedian);

    fclose(f);
    return 1;
}

int mg_bfs(M_Graph G, vertex v, char *path)
{
    v--;
    Vertex_info vertexes[G->V];
    bfs_distances(G, v, vertexes);
    
    // SAÍDA
    FILE *f = fopen(path, "w");
    if(f ==  NULL)
        return 0;
    vertex w;
    for(w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B') // UM SET SERIA UMA BOA OPÇÃO PARA EVITAR ISSO E DEIXAR A EXIBIÇÃO ORDENADA!!!!!
            fprintf(f, "vertex=%u\tfather=%u\tdepth=%u\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }
    fclose(f);

    return 1;
}

int mg_dfs(M_Graph G, vertex v, char *path)
{
    v--;
    Vertex_info vertexes[G->V];
    vertex w;
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1;
    }
    
    // DFS
    dfs_visit(G, v, vertexes);
    
    // SAÍDA
    FILE *f = fopen(path, "w");
    if(f == NULL)
        return 0;
    for(w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B') // UM SET SERIA UMA BOA OPÇÃO PARA EVITAR ISSO E DEIXAR A EXIBIÇÃO ORDENADA!!!!!
            fprintf(f, "vertex=%u\tfather=%u\tdepth=%u\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }
    fclose(f);
    return 1;
}

int mg_distance(M_Graph G, vertex v, vertex u)
{
    if(v == u)
        return 0;
    v--; u--;
    Vertex_info vertexes[G->V];
    vertex w;
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1; // Apesar de father ser unsigned int, +1 ele saíra como 0.
    }
    vertexes[v].color = 'G';
    Queue Q = q_initQueue();
    
    // BFS
    q_enqueue(Q, v);
    while(!q_isEmpty(Q))
    {
        vertex t = q_dequeue(Q);
        for(w = 0; w < G->V; w++)
        {
            if(G->adj[t][w] == 1)
            {
                if(vertexes[w].color == 'W')
                {
                    vertexes[w].color = 'G';
                    vertexes[w].father = t;
                    vertexes[w].depth = vertexes[t].depth + 1;
                    if(w == u)
                        break;
                    q_enqueue(Q, w);
                }
            }
        }
        vertexes[t].color = 'B';
    }
    q_destroyQueue(&Q);
    if(w == u)
        return vertexes[u].depth;
    else 
        return -1;
}

int mg_vertexEccentricity(M_Graph G, vertex v)
{
    v--;
    Vertex_info vertexes[G->V];
    vertex w = bfs_distances(G, v, vertexes);
    return vertexes[w].depth;
}

int mg_absoluteDiameter(M_Graph G)
{
    vertex w = 1;
    int diameter, eccentricity;
    eccentricity = mg_vertexEccentricity(G, w);
    if(eccentricity == -1)
        return -1;
    diameter = eccentricity;
    for(w = 1; w <= G->V; w++)
    {
        eccentricity = mg_vertexEccentricity(G, w);
        if(diameter < eccentricity)
            diameter = eccentricity;
    }
    return diameter;
}

int mg_aprroximateDiameter(M_Graph G)
{
    Vertex_info vertexes[G->V];
    vertex farthest = bfs_distances(G, 0, vertexes);
    farthest = bfs_distances(G, farthest, vertexes);
    return vertexes[farthest].depth;
}

void mg_listConnectedComponents(M_Graph G)
{
    
}
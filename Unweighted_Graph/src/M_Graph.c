/**
 * @file M_Graph.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/Graph.h"
#include "../include/GraphUtil.h"
#include "../include/CCUtil.h"
#include "../include/Queue.h"
#include "../include/Stack.h"

/**
 * @brief Estrutura do grafo com representação em matriz de ajacência.
 */
struct m_graph
{
    int V;      /**< Número V de vértices(vertexes).*/
    int E;      /**< Número E de arestas(edges).    */
    int **adj;  /**< Matriz de ajacências.          */
};

/**
 * @brief Função para alocar e retornar uma matriz de inteiros.
 * 
 * @param m Quantidade de linhas da matriz;
 * @param n Quantidade de colunas da matriz;
 * @param initVal Valor inicial dos elementos da matriz.
 * 
 * @return Retorna um vetor de inteiros alocado dinamicamente.
 */
static int** allocMatrix(int m, int n, int initVal)
{
    int **matrix = (int**) malloc(m * sizeof(int*));
    if(matrix == NULL)
        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);
        }
        for(j = 0; j < n; j++)
            matrix[i][j] = initVal;
    }
    return matrix;
}

/**
 * @brief Função para desalocar uma matriz de inteiros.
 * 
 * @param matrix Endereço da matriz em questão;
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
 * @brief Realiza busca em profundidade no grafo a partir de um pivo u.
 * 
 * @param G Grafo em questão.
 * @param u Vértice inicial da busca.
 * @param vertexes Vetor que armazenará os dados da busca.
 */
static void mg_dfs_visit(M_Graph G, vertex v, Vertex_info vertexes[])
{
    vertexes[v].color = 'G';
    vertex w;
    for(w = 0; w < G->V; w++)
    {
        if(G->adj[v][w] == 1)
        {
            if(vertexes[w].color == 'W')
            {
                vertexes[w].father = v;
                vertexes[w].depth = vertexes[v].depth + 1;
                mg_dfs_visit(G, w, vertexes);
            }
        }
    }
    vertexes[v].color = 'B';
}

/**
 * @brief Realiza a busca em largura em um grafo G a partir de um vertice u e preenche
 * um vetor de Vertex_info com as informações da busca.
 * 
 * @param G Grafo em questão;
 * @param u Vértice incial da busca;
 * @param vertexes Vetor que armazenará os dados da busca.
 * 
 * @return Retorna a posição relativa ao vetor de vértices do vértice com maior profundidade da árvore BFS.
 */
static vertex mg_bfs_distances(M_Graph G, vertex v, Vertex_info vertexes[])
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

/**
 * @brief Realiza a busca em profundidade no grafo e marca o componente conexo formado dessa busca.
 * 
 * @param G Grafo em questão;
 * @param u Vértice de início da BFS;
 * @param visited Vetor de status de vértices visitados ou não;
 * @param cc Lista de vértices de um componente conectado;
 * @param id Identificador do componente a ser marcado.
 */
static void mg_dfsCComponents(M_Graph G, vertex u, char visited[], ConnectedComponent *cc, int id)
{
    visited[u] = 'G';
    vertex v;
    for(v = 0; v < G->V; v++)
    {
        if(G->adj[u][v] == 1)
            if(visited[v] == 'W')
                mg_dfsCComponents(G, v, visited, cc, id);
    }
    visited[u] = 'B';
    cc->id = id;
    l_insertBeggining(cc->vertexes, u);
}

unsigned long long mg_representationSize(unsigned long long V)
{
    // custo da estrutura + custo da matriz de adjacências
    return sizeof(struct m_graph) + (V * V) * sizeof(int); 
}

M_Graph mg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f ==  NULL)
        return NULL;
    int V;
    vertex u, v;
    if(!fscanf(f, "%d", &V))
    {
        fclose(f);
        return NULL;
    }
    M_Graph G = mg_makeGraph(V);
    if(G == NULL)
    {
        fclose(f);
        return NULL;
    }
    while(fscanf(f, "%d %d", &v, &u) != EOF)
        mg_insertEdge(G, v, u);
    fclose(f);
    return G;
}

M_Graph mg_makeGraph(int V)
{
    M_Graph G = (struct m_graph*) malloc(sizeof(struct m_graph));
    if(G == NULL)
        exit(EXIT_FAILURE);
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

int mg_getNumOfVertexes(M_Graph G)
{
    return G->V;
}

int mg_getNumOfEdges(M_Graph G)
{
    return G->E;
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
    int *vertexesDegrees = (int*) malloc(sizeof(int) * G->V);
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
    free(vertexesDegrees);
    return 1;
}

int mg_bfs(M_Graph G, vertex v, char *path)
{
    v--;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);

    mg_bfs_distances(G, v, vertexes);
    
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

int mg_recursiveDfs(M_Graph G, vertex v, char *path)
{
    v--;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        return 0;
    vertex w;
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1;
    }
    
    // DFS
    mg_dfs_visit(G, v, vertexes);
    
    // SAÍDA
    FILE *f = fopen(path, "w");
    if(f == NULL)
    {
        free(vertexes);
        return 0;
    }
    for(w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B') // UM SET SERIA UMA BOA OPÇÃO PARA EVITAR ISSO E DEIXAR A EXIBIÇÃO ORDENADA!!!!!
            fprintf(f, "vertex=%u\tfather=%u\tdepth=%u\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }
    fclose(f);
    free(vertexes);
    return 1;
}

int mg_iterativeDfs(M_Graph G, vertex v, char *path)
{
    /*
        Problema dessa implementação comparado a recursiva:
            - A volta da recursão garante que as adjacências já verificadas
            antes de chamar a recursão não serão vistas novamente (função
            continua de onde parou), enquanto nessa implementação sempre que 
            desempilhamos um vértice e vamos para o anterior, este mesmo 
            analisa todas as adjacências novamente, mesmo as já analisadas 
            antes de ser empilhado.
    */
    v--;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
    vertex u, w;
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1;
    }

    Stack S = s_initStack();

    vertexes[v].color = 'G';
    s_push(S, v);
    while(!s_isEmpty(S))
    {
        u = s_top(S);
        for(w = 0; w < G->V; w++)
        {
            if(G->adj[u][w] == 1)
            {
                if (vertexes[w].color == 'W')
                {
                    vertexes[w].color = 'G';
                    vertexes[w].father = u;
                    vertexes[w].depth = vertexes[u].depth + 1;
                    s_push(S, w);
                    break;
                }
            }
        }
        if(w == G->V)
        {
            vertexes[u].color = 'B';
            s_pop(S);
        }
    }
    s_destroyStack(&S);

    // Escrevendo a saída no arquivo
    FILE *f = fopen(path, "w");
    if (!f)
    {
        free(vertexes);
        return 0;
    }
    for (w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B')
            fprintf(f, "vertex=%u\tfather=%d\tdepth=%d\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }
    fclose(f);
    free(vertexes);
    return 1;
}

int mg_distance(M_Graph G, vertex v, vertex u)
{
    if(v == u)
        return 0;
    v--; u--;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
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
                    {
                        q_destroyQueue(&Q);
                        int distance = vertexes[u].depth;
                        free(vertexes);
                        return distance;
                    }
                    q_enqueue(Q, w);
                }
            }
        }
        vertexes[t].color = 'B';
    }
    q_destroyQueue(&Q);
    free(vertexes);
    return -1;
}

int mg_vertexEccentricity(M_Graph G, vertex v)
{
    v--;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
    vertex w = mg_bfs_distances(G, v, vertexes), u;
    for(u = 0; u < G->V; u++)
        if(vertexes[u].color == 'W')
        {
            free(vertexes);
            return -1;
        }
    int eccentricity = vertexes[w].depth;
    free(vertexes);
    return eccentricity;
}

int mg_absoluteDiameter(M_Graph G)
{
    vertex w = 1;
    int diameter, eccentricity;
    eccentricity = mg_vertexEccentricity(G, w);
    if(eccentricity == -1)
        return -1;
    diameter = eccentricity;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    for(w = 1; w < G->V; w++)
    {
        eccentricity = vertexes[mg_bfs_distances(G, w, vertexes)].depth;
        if(diameter < eccentricity)
            diameter = eccentricity;
    }
    free(vertexes);
    return diameter;
}

int mg_aprroximateDiameter(M_Graph G)
{
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    vertex farthest = mg_bfs_distances(G, 0, vertexes);
    vertex u;
    for(u = 0; u < G->V; u++)
        if(vertexes[u].color == 'W')
        {
            free(vertexes);
            return -1;
        }
    farthest = mg_bfs_distances(G, farthest, vertexes);
    int diameter = vertexes[farthest].depth;
    free(vertexes);
    return diameter;
}

l_ConnectedComponents mg_connectedComponents(M_Graph G)
{
    l_ConnectedComponents lcc = allocLCC(); // Lista de componentes conexos
    if(lcc == NULL)
        return NULL;
    int id = 0; // Índice de acesso aos componentes conexos da lista e identificador de cada componente
    char *visited = (char*) malloc(G->V); // Salva o estado de visitado ou não de um vértice na dfs
    if(visited == NULL)
    {
        cc_destroyCComponents(&lcc);
        return NULL;
    }
    vertex v;
    for(v = 0; v < G->V; v++)
        visited[v] = 'W'; // inicializa todos como branco (não visitado)
    for(v = 0; v < G->V; v++)
    {
        if(visited[v] == 'W')
        {
            lcc->list[id].vertexes = l_initList(); // inicializa a lista de vértices do novo componente
            mg_dfsCComponents(G, v, visited, &lcc->list[id], id+1); // percorre os vértices do componente a partir de v
            id++;
            if(id == lcc->size) // caso falte posições na lista
                reallocLCC(lcc, lcc->size * 2); // dobra-se o tamanho alocado atualmente
        }
    }
    free(visited);
    if(lcc->size != id)
        if(!reallocLCC(lcc, id)) // reajusta o tamanho alocado da lista para o utilizado
            return NULL; 
    quicksortLCC(lcc->list, 0, lcc->size-1); // ordena os componentes em ordem decrescente
    return lcc;
}
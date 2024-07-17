/**
 * @file MW_Graph.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#define FLOAT_MAX 3.402823466e+38F
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/Graph.h"
#include "../include/Util.h"
#include "../include/CCUtil.h"
#include "../include/PriorityQueue.h"

struct mw_graph
{
    int V;      /**< Número V de vértices(vertexes).*/
    int E;      /**< Número E de arestas(edges).    */
    float **adj;  /**< Matriz de ajacências.          */
};

/**
 * @brief Função para alocar e retornar uma matriz de inteiros.
 * 
 * @param m Quantidade de linhas da matriz;
 * @param n Quantidade de colunas da matriz;
 * @param initVal Valor de peso inicial dos elementos da matriz.
 * 
 * @return Retorna um vetor de ponto fluante alocado dinamicamente.
 */
static float** allocMatrix(int m, int n, float initVal)
{
    float **matrix = (float**) malloc(m * sizeof(float*));
    if(matrix == NULL)
        exit(EXIT_FAILURE);
    int i, j;
    for(i = 0; i < m; i++)
    {
        matrix[i] = (float*) malloc(n * sizeof(float));
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
static void freeMatrix(float **matrix, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

static int negativeEdgeVerification(MW_Graph G)
{
    vertex i,j;
    for(i = 0; i < G->V; i++)
        for(j = 0; j < G->V; j++)
            if(G->adj[i][j] < 0)
                return 0;
    return 1;
}

static void mwg_shortestPath(vertex v, Vertex_djk *vertexes, FILE *f)
{
    if(vertexes[v].distance != 0.)
    {
        mwg_shortestPath(vertexes[v].father, vertexes, f);
        fprintf(f, "%d,\n", v+1);
    }
    else
        fprintf(f, "%d,\n", v+1);
}

unsigned long long mwg_representationSize(unsigned long long V)
{
    return sizeof(struct mw_graph) + (V * V) * sizeof(float); 
}

MW_Graph mwg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f ==  NULL)
        return NULL;
    int V;
    vertex u, v;
    float w;
    if(!fscanf(f, "%d", &V))
    {
        fclose(f);
        return NULL;
    }
    MW_Graph G = mwg_makeGraph(V);
    if(G == NULL)
    {
        fclose(f);
        return NULL;
    }
    while(fscanf(f, "%d %d %f", &v, &u, &w) != EOF)
        mwg_insertEdge(G, v, u, w);
    fclose(f);
    return G;
}

MW_Graph mwg_makeGraph(int V)
{
    MW_Graph G = (struct mw_graph*) malloc(sizeof(struct mw_graph));
    if(G == NULL)
        exit(EXIT_FAILURE);
    G->V = V;
    G->E = 0;
    G->adj = allocMatrix(V, V, 0.0);
    return G;
}

void mwg_destroyGraph(MW_Graph *G)
{
    freeMatrix((*G)->adj, (*G)->V);
    free(*G);
    G = NULL;
}

int mwg_insertEdge(MW_Graph G, vertex v, vertex u, float w)
{
    v--; u--;
    if(G->adj[v][u] == 0)
    {
        G->adj[v][u] = G->adj[u][v] = w;
        G->E++;
        return 1;
    }
    return 0;
}

int mwwg_removeEdge(MW_Graph G, vertex v, vertex u)
{
    v--; u--;
    if(G->adj[v][u] != 0)
    {
        G->adj[v][u] = G->adj[u][v] = 0;
        G->E--;
        return 1;
    }
    return 0;
}

float mwg_getEdge(MW_Graph G, vertex v, vertex u)
{
    return G->adj[v-1][u-1];
}

int mwg_getNumOfVertexes(MW_Graph G)
{
    return G->V;
}

int mwg_getNumOfEdges(MW_Graph G)
{
    return G->E;
}

void mwg_show(MW_Graph G)
{
    vertex i, j;
    printf("--- MATRIZ DE ADJACÊNCIAS ---\n");
    for(i = 0; i < G->V; i++)
    {
        printf("%6.2f", G->adj[i][0]);
        for(j = 1; j < G->V; j++)
        {
            printf(" %6.2f", G->adj[i][j]);
        }
        putchar('\n');
    }
}

double mwg_distance(MW_Graph G, vertex u, vertex v)
{
    u--; v--; 

    if (!negativeEdgeVerification(G))
        return -1;

    int w, x;
    double shortest_distance;
    Vertex_djk *vertexes = (Vertex_djk*) malloc(sizeof(Vertex_djk) * G->V);
    if (vertexes == NULL)
        return -1;

    for (w = 0; w < G->V; w++) 
    {
        vertexes[w].visited = 'W';
        vertexes[w].father = -1;
        vertexes[w].distance = INT_MAX; 
    }

    vertexes[u].distance = 0.0;

    int all_visited = 0;
    while (!all_visited) 
    {
        shortest_distance = INT_MAX;
        int u_index = -1;

        for (x = 0; x < G->V; x++) 
            if (vertexes[x].visited == 'W' && vertexes[x].distance < shortest_distance) 
            {
                shortest_distance = vertexes[x].distance;
                u_index = x;
            }
        
        if (u_index == -1 || shortest_distance == INT_MAX)
            break;

        vertexes[u_index].visited = 'B';

        for (w = 0; w < G->V; w++) 
            if (G->adj[u_index][w] > 0) 
            {
                double weight = G->adj[u_index][w];
                if (vertexes[w].visited == 'W' && vertexes[w].distance > vertexes[u_index].distance + weight) 
                {
                    vertexes[w].distance = vertexes[u_index].distance + weight;
                    vertexes[w].father = u_index;
                }
            }

        all_visited = 1;
        for (x = 0; x < G->V; x++) 
            if (vertexes[x].visited == 'W') 
            {
                all_visited = 0;
                break;
            }
        
    }
    double distance = vertexes[v].distance;
    
    
    FILE *f = fopen("./graphs/output/Caminho.txt", "w");
    if(!f)
    {
        free(vertexes);
        return 0;
    } 
    fprintf(f, "Start\n");
    mwg_shortestPath(v, vertexes, f);
    fprintf(f, "End\n");
    fclose(f);
    free(vertexes);
    return distance;
}

int mwg_dijkstraVet(MW_Graph G, vertex v, char *path)
{
    v--; 
    int w, u, x;
    double shortest_distance;
    Vertex_djk *vertexes = (Vertex_djk*) malloc(sizeof(Vertex_djk) * G->V);
    if (vertexes == NULL)
        return 0;

    if (v < 0 || v >= G->V) {
        free(vertexes);
        return 0;
    }

    if (!negativeEdgeVerification(G)) {
        free(vertexes);
        return 0;
    }

    for (w = 0; w < G->V; w++) {
        vertexes[w].visited = 'W';
        vertexes[w].father = -1;
        vertexes[w].distance = INT_MAX; 
    }

    vertexes[v].distance = 0.0;

    int all_visited = 0;
    while (!all_visited) {
        shortest_distance = INT_MAX;
        u = -1;

        for (x = 0; x < G->V; x++) {
            if (vertexes[x].visited == 'W' && vertexes[x].distance < shortest_distance) {
                shortest_distance = vertexes[x].distance;
                u = x;
            }
        }

        if (u == -1 || shortest_distance == INT_MAX)
            break;

        vertexes[u].visited = 'B';

        for (w = 0; w < G->V; w++) {
            if (G->adj[u][w] > 0) {
                double weight = G->adj[u][w];
                if (vertexes[w].visited == 'W' && vertexes[w].distance > vertexes[u].distance + weight) {
                    vertexes[w].distance = vertexes[u].distance + weight;
                    vertexes[w].father = u;
                }
            }
        }

        all_visited = 1;
        for (x = 0; x < G->V; x++) {
            if (vertexes[x].visited == 'W') {
                all_visited = 0;
                break;
            }
        }
    }

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        free(vertexes);
        return 0;
    }

    fprintf(file, "--- Arvore geradora minima de %u---\n", v + 1);
    for (w = 0; w < G->V; w++) {
        fprintf(file, "%d ~> %d | dist: %.2f\n", v + 1, w + 1, vertexes[w].distance);
        
    }

    fclose(file);
    free(vertexes);

    return 1;
    

}

int mwg_dijkstraHeap(MW_Graph G, vertex v, char *path)
{
    v--;
    Vertex_djk *vertexes = (Vertex_djk*) malloc(sizeof(Vertex_djk) * G->V);
    vertex w;

    for(w = 0; w < G->V; w++)
    {
        vertexes[w].distance = FLOAT_MAX;
        vertexes[w].father = -1;
        vertexes[w].visited = 'W';
    }

    vertexes[v].distance = 0.;
    PriorityQueue pq = pq_initPQueue(G->V);
    WeightedEdge pivot = {v, 0.};
    pq_enqueue(pq, pivot);

    while(!pq_isEmpty(pq))
    {
        pivot = pq_dequeue(pq);

        for (int w = 0; w < G->V; w++)
        {
            if (G->adj[pivot.v][w] > 0)  
            {
                if (vertexes[w].distance > vertexes[pivot.v].distance + G->adj[pivot.v][w])
                {
                    vertexes[w].distance = vertexes[pivot.v].distance + G->adj[pivot.v][w];
                    vertexes[w].father = pivot.v;
                    pq_enqueue(pq, (WeightedEdge){w, vertexes[w].distance});
                }
            }
        }
    }
    
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        free(vertexes);
        return 0;
    }

    fprintf(file, "--- Arvore geradora minima de %u---\n", v + 1);
    for (w = 0; w < G->V; w++) {
        fprintf(file, "%d ~> %d | dist: %.2f\n", v + 1, w + 1, vertexes[w].distance);
        
    }

    fclose(file);
    free(vertexes);

    return 1;
}
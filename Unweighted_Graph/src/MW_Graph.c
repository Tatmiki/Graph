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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/Graph.h"
#include "../include/GraphUtil.h"
#include "../include/CCUtil.h"

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
/**
 * @file LW_Graph.c
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
#include "../include/List_W.h"

struct lw_graph
{
    int V;
    int E;
    List_W *adj;
};

/**
 * @brief Verifica a existência de uma aresta com peso negativo no grafo.
 * 
 * @param G Grafo em questão.
 * 
 * @retval 1 - Há ao menos uma aresta com peso negativo;
 * @retval 0 - Não há arestas com peso negativo.
 */
static int checkNegativeEdge(LW_Graph G)
{
    Node_W head;
    vertex v;
    for(v = 0; v < G->V; v++)
        for(head = G->adj[v]->head; head != NULL; head = head->next)
            if(head->edge.weight < 0)
                return 0;
    return 1;
}

unsigned long long lwg_representationSize(unsigned long long V, unsigned long long E)
{
    // custo da estrutura + custo do vetor de ponteiros de lista 
    // + custo da estrutura de lista + custo dos nós de adjacências (2x pois é u-v e v-u)
    return sizeof(struct lw_graph) 
           + V * sizeof(struct list_w*) 
           + V * sizeof(struct list_w) 
           + (E * 2) * sizeof(struct node_w);
}

LW_Graph lwg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f == NULL)
        return NULL;
    int V;
    vertex v, u;
    double w;
    if(!fscanf(f, "%d", &V))
    {
        fclose(f);
        return NULL;
    }
    LW_Graph G = lwg_makeGraph(V);
    if(G == NULL)
    {
        fclose(f);
        return NULL;
    }
    while(fscanf(f, "%d %d %lf", &v, &u, &w) != EOF)
        lwg_insertEdge(G, v, u, w);
    fclose(f);
    return G;
}

LW_Graph lwg_makeGraph(int V)
{
    LW_Graph G = (LW_Graph) malloc(sizeof(struct lw_graph));
    if(G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->adj = (List_W*) malloc(sizeof(List_W) * V); // aloca um vetor de listas
    if(G->adj == NULL)
    {
        free(G);
        return NULL;
    }
    vertex v;
    for(v = 0; v < G->V; v++)
        G->adj[v] = lw_initList();
    return G;
}

void lwg_destroyGraph(LW_Graph *G)
{
    if(*G == NULL)
        return;
    vertex v;
    for(v = 0; v < (*G)->V; v++)
        lw_destroyList(&(*G)->adj[v]);
    free((*G)->adj);
    free(*G);
    *G = NULL;
}

int lwg_insertEdge(LW_Graph G, vertex v, vertex u, double w)
{
    v--; u--;
    if(lw_find(G->adj[v], u) != NULL)
        return 0;
    lw_insertBeggining(G->adj[v], u, w);
    lw_insertBeggining(G->adj[u], v, w);
    G->E++;
    return 1;
}

int lwg_removeEdge(LW_Graph G, vertex v, vertex u)
{
    v--; u--;
    if(!lw_remove(G->adj[v], u))
        return 0;
    lw_remove(G->adj[u], v);
    G->E--;
    return 0;
}

double lwg_getEdge(LW_Graph G, vertex v, vertex u)
{
    v--; u--;
    WeightedEdge *w = lw_find(G->adj[v], u);
    if(w == NULL)
        return -1;
    return w->weight;
}

int lwg_getNumOfVertexes(LW_Graph G)
{
    return G->V;
}

int lwg_getNumOfEdges(LW_Graph G)
{
    return G->E;
}

void lwg_show(LW_Graph G)
{
    printf("--- Adjacency List ---\n");
    vertex i;
    for(i = 0; i < G->V; i++)
    {
        printf("%d: ", i+1);
        lw_show(G->adj[i]);
    }
}
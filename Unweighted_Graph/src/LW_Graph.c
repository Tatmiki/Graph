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
#include <math.h>
#include "../include/Graph.h"
#include "../include/List_W.h"
#include "../include/PriorityQueue.h"
#include "../include/Util.h"

#define DOUBLE_MAX 1.7976931348623157e+308
#define EPSILON 1e-9

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
                return 1;
    return 0;
}

static void lwg_shortestPath(vertex v, Vertex_djk *vertexes, FILE *f)
{
    if(vertexes[v].father != -1)
    {
        lwg_shortestPath(vertexes[v].father, vertexes, f);
        fprintf(f, "%d,\n", v+1);
    }
    else
        fprintf(f, "%d,\n", v+1);
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

double lwg_distance(LW_Graph G, vertex u, vertex v, char *path)
{
    if(checkNegativeEdge(G))
        return 0;
    u--; v--;
    Vertex_djk *vertexes = (Vertex_djk*) malloc(sizeof(Vertex_djk) * G->V);
    vertex w;

    // Inicializa as distãncias, antecessores e estado de visitado
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].distance = DOUBLE_MAX;
        vertexes[w].father = -1;
        vertexes[w].visited = 'W';
    }

    // Inicializa a heap
    vertexes[u].distance = 0.;
    PriorityQueue pq = pq_initPQueue(G->V);
    WeightedEdge pivot = {u, 0.};
    Node_W head;

    pq_enqueue(pq, pivot);
    while(!pq_isEmpty(pq))
    {
        pivot = pq_dequeue(pq);

        for(head = G->adj[pivot.v]->head; head != NULL; head = head->next)
        {
            if(vertexes[head->edge.v].distance > vertexes[pivot.v].distance + head->edge.weight)
            {
                vertexes[head->edge.v].distance = vertexes[pivot.v].distance + head->edge.weight;
                vertexes[head->edge.v].father = pivot.v;
                pq_enqueue(pq, (WeightedEdge){head->edge.v, vertexes[head->edge.v].distance});
            }
        }
    }
    double distance = vertexes[v].distance;
    FILE *f = fopen(path, "w");
    if(f == NULL)
    {
        free(vertexes);
        return 0;
    }
    fprintf(f, "START\n");
    lwg_shortestPath(v, vertexes, f);
    fprintf(f, "END\n");
    fclose(f);
    pq_destroyPQueue(&pq);
    free(vertexes);
    return distance;
    return -1; 
}

int lwg_dijkstraVet(LW_Graph G, vertex v, char *path)
{
    if(checkNegativeEdge(G))
        return 0;
    v--;
    Vertex_djk *vertexes = (Vertex_djk*) malloc(sizeof(Vertex_djk) * G->V);
    vertex w;
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].distance = DOUBLE_MAX;
        vertexes[w].father = -1;
        vertexes[w].visited = 'W';
    }

    // Inicializa a heap
    vertexes[v].distance = 0.;
    Node_W head;
    double min;
    vertex pivot = v;

    while(1)
    {
        min = DOUBLE_MAX;

        for(w = 0; w < G->V; w++)
        {
            if(vertexes[w].visited == 'B') continue;
            if(vertexes[w].distance < min)
            {
                min = vertexes[w].distance;
                pivot = w;
            }
        }

        if(fabs(min - DOUBLE_MAX) < EPSILON) break;

        printf("o pivo ja foi:  %d\n", pivot);

        for(head = G->adj[pivot]->head; head != NULL; head = head->next)
        {
            if(vertexes[head->edge.v].visited == 'B') continue;
            if(vertexes[head->edge.v].distance > vertexes[pivot].distance + head->edge.weight)
            {
                vertexes[head->edge.v].distance = vertexes[pivot].distance + head->edge.weight;
                vertexes[head->edge.v].father = pivot;
            }
        }
        vertexes[pivot].visited = 'B';
    }
    
    // Escrevendo a saída no arquivo
    FILE *f = fopen(path, "w");
    if (!f)
    {
        free(vertexes);
        return 0;
    }
    for (w = 0; w < G->V; w++)
    {
        fprintf(f, "vertex=%d\tfather=%d\tdistance=%.2lf\n", w + 1, vertexes[w].father + 1, vertexes[w].distance);
    }
    fclose(f);
    free(vertexes);
    return 1;
}

int lwg_dijkstraHeap(LW_Graph G, vertex v, char *path)
{
    if(checkNegativeEdge(G))
        return 0;
    v--;
    Vertex_djk *vertexes = (Vertex_djk*) malloc(sizeof(Vertex_djk) * G->V);
    vertex w;

    // Inicializa as distãncias, antecessores e estado de visitado
    for(w = 0; w < G->V; w++)
    {
        vertexes[w].distance = DOUBLE_MAX;
        vertexes[w].father = -1;
        vertexes[w].visited = 'W';
    }

    // Inicializa a heap
    vertexes[v].distance = 0.;
    PriorityQueue pq = pq_initPQueue(G->V);
    WeightedEdge pivot = {v, 0.};
    Node_W head;

    pq_enqueue(pq, pivot);
    while(!pq_isEmpty(pq))
    {
        pivot = pq_dequeue(pq);

        for(head = G->adj[pivot.v]->head; head != NULL; head = head->next)
        {
            if(vertexes[head->edge.v].distance > vertexes[pivot.v].distance + head->edge.weight)
            {
                vertexes[head->edge.v].distance = vertexes[pivot.v].distance + head->edge.weight;
                vertexes[head->edge.v].father = pivot.v;
                pq_enqueue(pq, (WeightedEdge){head->edge.v, vertexes[head->edge.v].distance});
            }
        }
    }
    
    // Escrevendo a saída no arquivo
    FILE *f = fopen(path, "w");
    if (!f)
    {
        free(vertexes);
        return 0;
    }
    for (w = 0; w < G->V; w++)
    {
        fprintf(f, "vertex=%u\tfather=%d\tdistance=%.2lf\n", w + 1, vertexes[w].father + 1, vertexes[w].distance);
    }
    fclose(f);
    free(vertexes);
    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include "../include/L_UGraph.h"

/**
 * @brief Estrura de nó para ligação de vértices da lista de adjacência.
 */
typedef struct node 
{
    vertex w;     /**< Indíce vértice W.                             */
    struct node* next;  /**< Ponteiro para o próximo vértice da lista.   */
} *Node;

/**
 * @brief Estrutura do grafo com representação em lista de ajacência.
 */
struct l_graph 
{
    size_t V;   /**< Número V de vértices(vertexes).    */
    size_t E;   /**< Número E de arestas(edges).        */
    Node *adj;  /**< Vetor das listas de adjacências.     */
};

/**
 * @brief Aloca um novo nodo de vértice.
 * 
 * @param w Número do vértice
 * @param next Próximo nó da lista.
 * @retval ( Node ) - Novo nó alocado
 * @retval ( NULL ) - Ponteiro nulo indicando erro de alocação.
 */
static Node newNode(vertex w, Node next)
{
    Node newNode = (Node) malloc(sizeof(struct node));
    if(newNode == NULL)
        return NULL;
    newNode->w = w;
    newNode->next = next;
    return newNode;
}

/**
 * @brief Desaloca o vetor de listas de adjacências.
 * 
 * @param list Vetor de listas de adjacências.
 * @param V Número de vértices (tamanho do vetor de vértices).
 */
static void freeList(Node *list, size_t V)
{
    vertex v;
    Node temp;
    for(v = 0; v < V; v++)
    {
        while(list[v] != NULL)
        {
            temp = list[v];
            list[v] = list[v]->next;
            free(temp); 
        }
    }
    free(list);
}

L_Graph lg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f == NULL)
        return 0;
    size_t V;
    vertex v, u;
    if(!fscanf(f, "%lu", &V))
    {
        fclose(f);
        return 0;
    }
    L_Graph G = lg_makeGraph(V);
    if(G == NULL)
    {
        fclose(f);
        return 0;
    }
    while(fscanf(f, "%u %u", &v, &u) != EOF)
        lg_insertEdge(G, v-1, u-1);
    fclose(f);
    return G;
}

L_Graph lg_makeGraph(size_t V)
{
    L_Graph G = (L_Graph) malloc(sizeof(struct l_graph));
    G->V = V;
    G->E = 0;
    G->adj = (Node*) malloc(V * sizeof(Node));
    vertex v;
    for(v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void lg_destroyGraph(L_Graph *G)
{
    freeList((*G)->adj, (*G)->V);
    free(*G);
    *G = NULL;
}

int lg_insertEdge(L_Graph G, vertex v, vertex u)
{
    Node head;
    for(head = G->adj[v]; head != NULL; head = head->next)
        if(head->w == u)
            return 0;
    G->adj[v] = newNode(u, G->adj[v]);
    G->E++;
    return 1;
}

int lg_removeEdge(L_Graph G, vertex v, vertex u)
{
    Node previous = NULL;
    Node current = G->adj[v];

    while(current != NULL)
    {
        if((current)->w == u)
        {
            if(previous != NULL)
                previous->next = current->next;
            else
                G->adj[v] = current->next;
            free(current);
            G->E--;
            return 1;
        } 
        previous = current;
        current = current->next;
    }
    return 0;
}

int lg_getEdge(L_Graph G,vertex v, vertex u)
{
    Node prox = G->adj[v];
    while(prox != NULL)
    {
        if(prox->w == u)
            return 1;
        prox = prox->next;
    }
    return 0;
}

void lg_show(L_Graph G)
{
    printf("--- Adjacency List ---\n");
    vertex i;
    for(i = 0; i < G->V; i++)
    {
        printf("%d: ", i);
        Node adjacent = G->adj[i];
        while(adjacent != NULL)
        {
            printf(" -> %d", adjacent->w);
            adjacent = adjacent->next;
        }
        printf("\n");
    }
}

void lg_bsf()
{
    
}

void lg_dfs()
{
    
}

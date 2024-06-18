#include <stdio.h>
#include <stdlib.h>
#include "../include/L_UGraph.h"
#include <limits.h>

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
    G->adj[u] = newNode(v, G->adj[u]);
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
            break;
        } 
        previous = current;
        current = current->next;
    }

    if(current == NULL)
        return 0;

    previous = NULL;
    current = G->adj[u];

    while(current != NULL)
    {
        if((current)->w == v)
        {
            if(previous != NULL)
                previous->next = current->next;
            else
                G->adj[u] = current->next;
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

int lg_outputFile(L_Graph G, char *path)
{
    // Cria/substitui um arquivo texto chamado "saida.txt" no caminho indicado.
    FILE *f = fopen(path, "w");
    if(!f)
        return 0;
    int vertexesDegrees[G->V], maxDegree = 0, minDegree = INT_MAX;
    double mediumDegree = 0, DegreeMedian;
    Node adjacent;
    vertex v;
    for(v; v < G->V; v++)
    {
        vertexesDegrees[v] = 0;
        adjacent = G->adj[v];
        while(adjacent != NULL) // Calcula o grau de um vértice
        {
            vertexesDegrees[v]++;
            adjacent = adjacent->next;
        }
        if(vertexesDegrees[v] < minDegree)// é o menor grau?
            minDegree = vertexesDegrees[v];
        if(vertexesDegrees[v] > maxDegree)// é o maior grau?
            maxDegree = vertexesDegrees[v];
        mediumDegree += vertexesDegrees[v];// soma para média
    }
    //Calcula o grau médio
    mediumDegree /= G->V;
    //Calcula a mediana
    quicksort(vertexesDegrees, 0, G->V-1);
    if(G->V % 2 != 0)
        DegreeMedian = vertexesDegrees[(G->V / 2) + 1];
    else
        DegreeMedian = (vertexesDegrees[G->V / 2] + vertexesDegrees[(G->V / 2) + 1]) / 2.;

    //Saída para o arquivo
    fprintf(f, "numberOfVertexes=%lu\n", G->V);
    fprintf(f, "numberOfEdges=%lu\n", G->E);
    fprintf(f, "minDegree=%d\n", minDegree);
    fprintf(f, "maxDegree=%d\n", maxDegree);
    fprintf(f, "mediumDegree=%lf\n", mediumDegree);
    fprintf(f, "DegreeMedian=%lf\n", DegreeMedian);

    fclose(f);
    return 1;
}

int lg_bsf(L_Graph G, vertex v, char *path)
{
    
}

int lg_dfs(L_Graph G, vertex v, char *path)
{

}

int lg_distance(L_Graph G, vertex v, vertex u)
{

}

int lg_diameter(L_Graph G)
{

}

void lg_listConnectedComponents(L_Graph G)
{
    
}
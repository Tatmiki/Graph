#include <stdio.h>
#include <stdlib.h>
#include "../include/L_UGraph.h"
#include "../include/List.h"
#include "../include/Queue.h"
#include <limits.h>


/**
 * @brief Estrutura do grafo com representação em lista de ajacência.
 */
struct l_graph 
{
    int V;   /**< Número V de vértices(vertexes).    */
    int E;   /**< Número E de arestas(edges).        */
    List *adj;  /**< Vetor das listas de adjacências.     */
};

/**
 * @brief Estrutura de apoio para os algoritmos de BFS e DFS.
 */
typedef struct
{
    char color;
    vertex father;
    int depth;
} Vertex_info;

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
 * @brief Função responsável por visitar os vértices adjacentes a um determinado outro vértice
 * 
 * @param G Grafo em que os vérices serão visitados
 * @param v Vértice a qual seus adjacentes serão visitados
 * @param vertexes Vetor de vértices pertencentes ao Grafo
 */
static void dfs_visit(L_Graph G, vertex v, Vertex_info vertexes[])
{
    vertexes[v].color = 'G';  // Marcando o vértice como visitado
    vertex w;

    Node head = G->adj[v]->head;
    while (head != NULL)
    {
        w = head->w;
        if (vertexes[w].color == 'W')
        {
            vertexes[w].father = v;
            vertexes[w].depth = vertexes[v].depth + 1;
            dfs_visit(G, w, vertexes);
        }
        head = head->next;
    }
    vertexes[v].color = 'B';  // Finalizando a visita do vértice
}

/**
 * @brief Função resonsável retornar o vértixe mais distante de outro determinado vértixe 
 * 
 * @param G Grafo que deseja buscar o vértice
 * @param v Vértice de origem
 * @param vertexes Vetor contendo todos os vértices
 * 
 * @retval ( u ) - Indice do vetor de vértices do vértice mais profundo da árvore BFS.
 */
static vertex bfs_distancesVertex(L_Graph G, vertex v, Vertex_info vertexes[]) 
{
    vertex w;
    
    for (w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1;
    }

    vertexes[v].color = 'G';
    Queue Q = q_initQueue();
    q_enqueue(Q, v);

    vertex u = 0;
    Node head;
    while(!q_isEmpty(Q))
    {
        u = q_dequeue(Q);

        head = G->adj[u]->head; // Acessa a lista de adjacência do vértice u
        
        while (head != NULL)
        {
            w = head->w;
            if (vertexes[w].color == 'W')
            {
                
                vertexes[w].color = 'G';
                vertexes[w].father = u;
                vertexes[w].depth = vertexes[u].depth + 1;
                q_enqueue(Q, w);
            }
            head = head->next; // Avança para o próximo vizinho na lista de adjacência
        }
        vertexes[u].color = 'B';
    }
    q_destroyQueue(&Q);
    return u;
}

L_Graph lg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f == NULL)
        return 0;
    int V;
    vertex v, u;
    if(!fscanf(f, "%d", &V))
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
    while(fscanf(f, "%d %d", &v, &u) != EOF)
        lg_insertEdge(G, v, u);
    fclose(f);
    return G;
}

L_Graph lg_makeGraph(size_t V)
{
    L_Graph G = (L_Graph) malloc(sizeof(struct l_graph));
    G->V = (int) V;
    G->E = 0;
    G->adj = (List*) malloc(sizeof(struct list) * V); // aloca um vetor de listas
    vertex v;
    for(v = 0; v < G->V; v++)
        G->adj[v] = l_initList();
    return G;
}

void lg_destroyGraph(L_Graph *G)
{
    vertex v;
    for(v = 0; v < (*G)->V; v++)
        l_destroyList(&(*G)->adj[v]);
    free(*G);
    *G = NULL;
}

int lg_insertEdge(L_Graph G, vertex v, vertex u)
{
    v--; u--;
    if(l_find(G->adj[v], u))
        return 0;
    l_insertBeggining(G->adj[v], u);
    l_insertBeggining(G->adj[u], v);
    G->E++;
    return 1;
}

int lg_removeEdge(L_Graph G, vertex v, vertex u)
{
    v--;u--;
    l_remove(G->adj[v], u);
    l_remove(G->adj[u], v);
    return 0;
}

int lg_getEdge(L_Graph G,vertex v, vertex u)
{
    v--; u--;
    return l_find(G->adj[v], u);
}

void lg_show(L_Graph G)
{
    printf("--- Adjacency List ---\n");
    vertex i;
    for(i = 0; i < G->V; i++)
    {
        printf("%d: ", i+1);
        l_show(G->adj[i]);
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
    vertex v;
    for(v = 0; v < G->V; v++)
    {
        vertexesDegrees[v] = l_getSize(G->adj[v]);
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
    fprintf(f, "numberOfVertexes=%d\n", G->V);
    fprintf(f, "numberOfEdges=%d\n", G->E);
    fprintf(f, "minDegree=%d\n", minDegree);
    fprintf(f, "maxDegree=%d\n", maxDegree);
    fprintf(f, "mediumDegree=%lf\n", mediumDegree);
    fprintf(f, "DegreeMedian=%lf\n", DegreeMedian);

    fclose(f);
    return 1;
}

int lg_bfs(L_Graph G, vertex v, char *path)
{
    v--; 
    Vertex_info vertexes[G->V];
    bfs_distancesVertex(G, v, vertexes);
    
    FILE *f = fopen(path, "w");
    if (!f)
        return 0;
    
    vertex w;
    for (w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B')
            fprintf(f, "vertex=%u\tfather=%d\tdepth=%d\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }
    fclose(f);
    return 1;
}

int lg_dfs(L_Graph G, vertex v, char *path)
{
    v--; // Ajustando o vértice para ser base 0
    Vertex_info vertexes[G->V];
    vertex w;

    // Inicializando as estruturas de dados
    for (w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';  // Todos os vértices são inicialmente não visitados
        vertexes[w].depth = 0;
        vertexes[w].father = -1;  // Inicialmente nenhum vértice tem pai definido
    }

    // Chamando a DFS para cada vértice não visitado
    dfs_visit(G, v, vertexes);

    // Escrevendo a saída no arquivo
    FILE *f = fopen(path, "w");
    if (!f)
        return 0;

    for (w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B')
            fprintf(f, "vertex=%u\tfather=%d\tdepth=%d\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }

    fclose(f);
    return 1;
}

int lg_distance(L_Graph G, vertex v, vertex u)
{
    v--; u--;  
    if (v == u) 
        return 0;
    
    Vertex_info vertexes[G->V];
    vertex w;

    for (w = 0; w < G->V; w++) 
    {
        vertexes[w].color = 'W';
        vertexes[w].depth = 0;
        vertexes[w].father = -1;
    }

    vertexes[v].color = 'G';
    Queue Q = q_initQueue();
    q_enqueue(Q, v);

    Node head;
    vertex y;
    while (!q_isEmpty(Q)) 
    {
        y = q_dequeue(Q);
        head = G->adj[y]->head;  

        while (head != NULL) 
        {
            w = head->w;
            if (vertexes[w].color == 'W') 
            {
                vertexes[w].color = 'G';
                vertexes[w].father = y;
                vertexes[w].depth = vertexes[y].depth + 1;
                q_enqueue(Q, w);
            }

            if (w == u) 
                break;

            head = head->next; 
        }
        vertexes[y].color = 'B';
    }
    q_destroyQueue(&Q);

    return vertexes[u].depth;  
}

int lg_vertexEccentricity(L_Graph G, vertex v)
{
    Vertex_info vertexes[G->V];
    vertex w = bfs_distancesVertex(G, v, vertexes);
    return vertexes[w].depth;
}

int lg_absoluteDiameter(L_Graph G)
{
    vertex w = 0;
    int diameter = 0;
    int eccentricity = lg_vertexEccentricity(G,w);
    if(eccentricity == -1)
        return -1;
    diameter = eccentricity;
    for(w = 1; w < G->V; w++)
    {
        eccentricity = lg_vertexEccentricity(G,w);
        if(diameter < eccentricity)
            diameter = eccentricity;
    }
    return diameter;
}

int lg_aprroximateDiameter(L_Graph G)
{
    Vertex_info vertexes[G->V];

    vertex v = bfs_distancesVertex(G, 0, vertexes);
    v = bfs_distancesVertex(G, v, vertexes);

    return vertexes[v].depth;
}

void lg_listConnectedComponents(L_Graph G)
{
    
}
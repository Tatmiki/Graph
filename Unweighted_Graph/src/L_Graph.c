/**
 * @file L_Graph.c
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
#include "../include/Util.h"
#include "../include/CCUtil.h"
#include "../include/List.h"
#include "../include/Queue.h"
#include "../include/Stack.h"

/**
 * @brief Estrutura do grafo com representação em lista de ajacência.
 */
struct l_graph 
{
    int V;      /**< Número V de vértices(vertexes).    */
    int E;      /**< Número E de arestas(edges).        */
    List *adj;  /**< Vetor das listas de adjacências.   */
};

/**
 * @brief Realiza a BFS para identificar um componente conexo de um grafo marcando todos os vértices alcançáveis
 * a partir de u como visitados ('B'lack).
 * 
 * @param G Grafo em questão;
 * @param u Vértice de início da BFS;
 * @param visited Vetor de status de vértices visitados ou não;
 * @param cc Lista de vértices de um componente conectado;
 * @param id Identificador do componente a ser marcado.
 */
static void lg_bfsCComponents(L_Graph G, vertex u, char visited[], ConnectedComponent *cc, int id)
{
    visited[u] = 'G';
    Queue Q = q_initQueue();
    q_enqueue(Q, u);

    vertex v = 0, w;
    Node head;
    while(!q_isEmpty(Q))
    {
        v = q_dequeue(Q);
        head = G->adj[v]->head; // Acessa a lista de adjacência do vértice u
        while (head != NULL)
        {
            w = head->w;
            if (visited[w] == 'W')
            {
                visited[w] = 'G';
                q_enqueue(Q, w);
            }
            head = head->next; // Avança para o próximo vizinho na lista de adjacência
        }
        cc->id = id;
        l_insertBeggining(cc->vertexes, v);
        visited[v]= 'B';
    }
    q_destroyQueue(&Q);
}

/**
 * @brief Função responsável por visitar em profundidade os vértices adjacentes a um determinado outro vértice.
 * 
 * @param G Grafo em que os vérices serão visitados
 * @param v Vértice a qual seus adjacentes serão visitados
 * @param vertexes Vetor de vértices pertencentes ao Grafo
 */
static void lg_dfs_visit(L_Graph G, vertex v, Vertex_info vertexes[])
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
            lg_dfs_visit(G, w, vertexes);
        }
        head = head->next;
    }
    vertexes[v].color = 'B';  // Finalizando a visita do vértice
}

/**
 * @brief Função de BFS responsável retornar o vértice mais distante de outro determinado vértice. 
 * 
 * @param G Grafo em questão;
 * @param v Vértice de origem/destino;
 * @param vertexes Vetor de informações do vértices.
 * 
 * @retval ( u ) - Indice do vetor de vértices do vértice mais profundo da árvore BFS.
 */
static vertex lg_bfs_distances(L_Graph G, vertex v, Vertex_info vertexes[]) 
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

unsigned long long lg_representationSize(unsigned long long V, unsigned long long E)
{
    // custo da estrutura + custo do vetor de ponteiros de lista 
    // + custo da estrutura de lista + custo dos nós de adjacências (2x pois é u-v e v-u)
    return sizeof(struct l_graph) + V * sizeof(struct list*) + V * sizeof(struct list) + (E * 2) * sizeof(struct node);
}

L_Graph lg_makeGraphFromFile(char *path)
{
    FILE *f = fopen(path, "r");
    if(f == NULL)
        return NULL;
    int V;
    vertex v, u;
    if(!fscanf(f, "%d", &V))
    {
        fclose(f);
        return NULL;
    }
    L_Graph G = lg_makeGraph(V);
    if(G == NULL)
    {
        fclose(f);
        return NULL;
    }
    while(fscanf(f, "%d %d", &v, &u) != EOF)
        lg_insertEdge(G, v, u);
    fclose(f);
    return G;
}

L_Graph lg_makeGraph(int V)
{
    L_Graph G = (L_Graph) malloc(sizeof(struct l_graph));
    if(G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->adj = (List*) malloc(sizeof(struct list) * V); // aloca um vetor de listas
    if(G->adj == NULL)
    {
        free(G);
        return NULL;
    }
    vertex v;
    for(v = 0; v < G->V; v++)
        G->adj[v] = l_initList();
    return G;
}

void lg_destroyGraph(L_Graph *G)
{
    if(*G == NULL)
        return;
    vertex v;
    for(v = 0; v < (*G)->V; v++)
        l_destroyList(&(*G)->adj[v]);
    free((*G)->adj);
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
    v--; u--;
    if(!l_remove(G->adj[v], u))
        return 0;
    l_remove(G->adj[u], v);
    G->E--;
    return 0;
}

int lg_getEdge(L_Graph G,vertex v, vertex u)
{
    v--; u--;
    return l_find(G->adj[v], u);
}

int lg_getNumOfVertexes(L_Graph G)
{
    return G->V;
}

int lg_getNumOfEdges(L_Graph G)
{
    return G->E;
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
    // Cria ou substitui um arquivo texto chamado "saida.txt" no caminho indicado.
    FILE *f = fopen(path, "w");
    if(!f)
        return 0;
    int *vertexesDegrees = (int*) malloc(sizeof(int) * G->V), maxDegree = 0, minDegree = INT_MAX;
    if(vertexesDegrees == NULL)
        exit(EXIT_FAILURE);
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
    free(vertexesDegrees);
    return 1;
}

int lg_bfs(L_Graph G, vertex v, char *path)
{
    v--; 
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
    
    lg_bfs_distances(G, v, vertexes);
    
    FILE *f = fopen(path, "w");
    if (!f)
    {
        free(vertexes);
        return 0;
    }
        
    vertex w;
    for (w = 0; w < G->V; w++)
    {
        if(vertexes[w].color == 'B')
            fprintf(f, "vertex=%u\tfather=%d\tdepth=%d\n", w + 1, vertexes[w].father + 1, vertexes[w].depth);
    }
    fclose(f);
    free(vertexes);
    return 1;
}

int lg_recursiveDfs(L_Graph G, vertex v, char *path)
{
    v--; // Ajustando o vértice para ser base 0
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        return 0;

    // Inicializando as estruturas de dados
    vertex w;
    for (w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';  // Todos os vértices são inicialmente não visitados
        vertexes[w].depth = 0;
        vertexes[w].father = -1;  // Inicialmente nenhum vértice tem pai definido
    }

    // Chamando a DFS
    lg_dfs_visit(G, v, vertexes);

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

int lg_iterativeDfs(L_Graph G, vertex v, char *path)
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
    Node head;
    while(!s_isEmpty(S))
    {
        u = s_top(S);
        head = G->adj[u]->head; // Acessa a lista de adjacência do vértice u
        while (1)
        {
            if(head == NULL)
            {
                vertexes[u].color = 'B';
                s_pop(S);
                break;
            }
            w = head->w;
            if (vertexes[w].color == 'W')
            {
                vertexes[w].color = 'G';
                vertexes[w].father = u;
                vertexes[w].depth = vertexes[u].depth + 1;
                s_push(S, w);
                break;
            }
            else
                head = head->next;
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

int lg_distance(L_Graph G, vertex v, vertex u)
{
    v--; u--;  
    if (v == u) 
        return 0;
    
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);

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
            {
                q_destroyQueue(&Q);
                int distance = vertexes[u].depth;
                free(vertexes);
                return distance;  
            }
            head = head->next; 
        }
        vertexes[y].color = 'B';
    }
    q_destroyQueue(&Q);
    free(vertexes);
    return -1;  
}

int lg_vertexEccentricity(L_Graph G, vertex v)
{
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    vertex w = lg_bfs_distances(G, v, vertexes);
    vertex u;
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

int lg_absoluteDiameter(L_Graph G)
{
    vertex w = 0;
    int diameter = 0;
    int eccentricity = lg_vertexEccentricity(G,w);
    if(eccentricity == -1)
        return -1;
    diameter = eccentricity;
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
    for(w = 1; w < G->V; w++)
    {
        eccentricity = vertexes[lg_bfs_distances(G, w, vertexes)].depth;
        if(diameter < eccentricity)
            diameter = eccentricity;
    }
    free(vertexes);
    return diameter;
}

int lg_aprroximateDiameter(L_Graph G)
{
    Vertex_info *vertexes = (Vertex_info*) malloc(sizeof(Vertex_info) * G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
    vertex v = lg_bfs_distances(G, 0, vertexes);
    vertex u;
    for(u = 0; u < G->V; u++)
        if(vertexes[u].color == 'W')
        {
            free(vertexes);
            return -1;
        }
    v = lg_bfs_distances(G, v, vertexes);
    int aprroximateDiameter = vertexes[v].depth;
    free(vertexes);
    return aprroximateDiameter;
}

l_ConnectedComponents lg_connectedComponents(L_Graph G)
{
    l_ConnectedComponents lc = allocLCC();
    if(lc == NULL)
        return NULL;
    vertex v;
    char *vertexes = (char*) malloc(G->V);
    if(vertexes == NULL)
    {
        cc_destroyCComponents(&lc);
        return NULL;
    }
    int id = 0;
    for(v = 0; v < G->V; v++)
        vertexes[v] = 'W';
    for(v = 0; v < G->V; v++)
    {
        if(vertexes[v] == 'W')
        {
            lc->list[id].vertexes = l_initList();
            lg_bfsCComponents(G, v, vertexes, &lc->list[id], id+1);
            id++;
            if(lc->size == id)
                reallocLCC(lc, lc->size * 2);
        }
    }
    free(vertexes);
    if(id != lc->size)
        if(!reallocLCC(lc, id))
            return NULL;
    quicksortLCC(lc->list, 0, lc->size - 1);
    return lc;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "../include/Graph.h"
#include "../include/List.h"
#include "../include/Queue.h"
#include "../include/Stack.h"

clock_t clock_begin = 0;
clock_t clock_end = 0;
double time_lapsed = 0;

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
 * @brief Estrutura do grafo com representação em matriz de ajacência.
 */
struct m_graph
{
    int V;      /**< Número V de vértices(vertexes).*/
    int E;      /**< Número E de arestas(edges).    */
    int **adj;  /**< Matriz de ajacências.          */
};

/**
 * @brief Estrutura de apoio para os algoritmos de BFS e DFS.
 */
typedef struct
{
    char color;     /*> Cor de status do vértice. ('W'hite não visitado, 'G'ray de visto e 'B'lack de visitado) */
    vertex father;  /*> Vértice pai do veŕtice em questão.                                                      */
    int depth;      /*> Porfundidade de um vértice em relação ao início da BFS ou DFS realizada.                */
} Vertex_info;

/**
 * @brief Estrutura de um componente conexo.
 */
typedef struct
{
    List vertexes;  /*> Lista de vértices pertencentes ao componente.   */
    int id;         /*> Identificador do componente.                    */
} ConnectedComponent;

/**
 * @brief Estrutura da lista de componentes conexos.
 */
struct l_connected_components
{
    ConnectedComponent *list;   /*> Lista de componentes conexos.   */
    int size;                   /*> Tamanho da lista.               */
};

//----------------------------------------------------------------------------------

/**
 * @brief Troca o valor de duas variáveis inteiras
 * 
 * @param a Endereço da variável a.
 * @param b Endereço da variável b.
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
 * @param vet Vetor em questão;
 * @param start Início relativo ao índice do vetor (geralmente 0);
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
 * @brief Aloca uma lista de componentes conexos.
 * 
 * @return Uma lista alocada de componentes conectados com tamanho inicial de alocação 10.
 */
static l_ConnectedComponents allocLCC()
{
    l_ConnectedComponents lc = (l_ConnectedComponents) malloc(sizeof(struct l_connected_components));
    if(lc == NULL)
        exit(EXIT_FAILURE);
    lc->list = (ConnectedComponent*) malloc(sizeof(ConnectedComponent) * 10);
    if(lc->list == NULL)
        exit(EXIT_FAILURE);
    lc->size = 10;
    return lc;
}

/**
 * @brief Reajusta a área alocada de uma lista de componentes conexos.
 * 
 * @param lc Lista em questão;
 * @param newSize Novo tamanho da lista.
 */
static void reallocLCC(l_ConnectedComponents lc, int newSize)
{
    lc->list = (ConnectedComponent*) realloc(lc->list, sizeof(ConnectedComponent) * newSize);
    if(lc->list == NULL)
        exit(EXIT_FAILURE);
    lc->size = newSize;
}

/**
 * @brief Troca a lista de dois componentes conexos.
 * 
 * @param a Endereço do componente a;
 * @param b Endereço do componente b.
 */
static void swapCC(ConnectedComponent *a, ConnectedComponent *b)
{
    ConnectedComponent temp = *a;
    (*a).vertexes = (*b).vertexes;
    (*b).vertexes = temp.vertexes;
}

/**
 * @brief Realiza o quicksort descrescente em uma lista de componentes conexos.
 * 
 * @param vet Lista de componentes conexos;
 * @param start Início da lista (geralmente 0);
 * @param end Última posição da lista (geralmente tamanho-1).
 */
static void quicksortLCC(ConnectedComponent vet[], const int start, const int end)
{
    int left = start, right = end, pivot = l_getSize(vet[(start+end)/2].vertexes);
    do
    {
        
        while(l_getSize(vet[left].vertexes) > pivot) ++left;
        while(l_getSize(vet[right].vertexes) < pivot) --right;
        if(left <= right)
        {
            swapCC(&vet[left], &vet[right]);
            left++; right--;
        }
    }while(left <= right);
    
    if(right > start) quicksortLCC(vet, start, right); // ramo esquerdo
    if(left < end) quicksortLCC(vet, left, end); // ramo direito
}


//----------------------------------------------------------------------------------

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
    G->V = (int) V;
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
    vertex w;

    if(vertexes == NULL)
        exit(EXIT_FAILURE);

    // Inicializando as estruturas de dados
    for (w = 0; w < G->V; w++)
    {
        vertexes[w].color = 'W';  // Todos os vértices são inicialmente não visitados
        vertexes[w].depth = 0;
        vertexes[w].father = -1;  // Inicialmente nenhum vértice tem pai definido
    }

    // Chamando a DFS para cada vértice não visitado
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
            {
                if(head->next == NULL)
                {
                    vertexes[u].color = 'B';
                    s_pop(S);
                    break;
                }
                else
                    head = head->next;
            }
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

//TODO: RETORNAR NULO
l_ConnectedComponents lg_connectedComponents(L_Graph G)
{
    l_ConnectedComponents lc = allocLCC();
    vertex v;
    char *vertexes = (char*) malloc(G->V);
    if(vertexes == NULL)
        exit(EXIT_FAILURE);
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
        reallocLCC(lc, id);
    quicksortLCC(lc->list, 0, lc->size - 1);
    return lc;
}

//----------------------------------------------------------------------------------

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
static void mg_dfs_visit(M_Graph G, vertex u, Vertex_info vertexes[])
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
                mg_dfs_visit(G, v, vertexes);
            }
        }
    }
    vertexes[u].color = 'B';
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
        exit(EXIT_FAILURE);
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

//TODO: RETORNAR NULO
l_ConnectedComponents mg_connectedComponents(M_Graph G)
{
    l_ConnectedComponents lcc = allocLCC(); // Lista de componentes conexos
    int id = 0; // Índice de acesso aos componentes conexos da lista e identificador de cada componente
    char *visited = (char*) malloc(G->V); // Salva o estado de visitado ou não de um vértice na dfs
    if(visited == NULL)
        exit(EXIT_FAILURE);
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
        reallocLCC(lcc, id); // reajusta o tamanho alocado da lista para o utilizado
    quicksortLCC(lcc->list, 0, lcc->size-1); // ordena os componentes em ordem decrescente
    return lcc;
}

//----------------------------------------------------------------------------------

int cc_getNumOfCComponents(l_ConnectedComponents lcc)
{
    return lcc->size;
}

int cc_getSizeCComponent(l_ConnectedComponents l, int id)
{
    return l_getSize(l->list[id-1].vertexes);
}

void cc_listCComponents(l_ConnectedComponents lcc)
{
    printf("Há %d componente(s) conexo(s).\nListagem:\n", lcc->size);
    int i;
    for(i = 0; i < lcc->size; i++)
    {
        printf("\n~> Componentes [%d]:\n", lcc->list[i].id);
        printf("      - Quantidade de vertices: %d\n", cc_getSizeCComponent(lcc, i+1));
    }
}

void cc_showCComponent(l_ConnectedComponents lcc, int id)
{
    printf("\n~ Componente [%d]:\n", lcc->list[id-1].id);
    printf("      - Qnt. de vértices: %d\n", cc_getSizeCComponent(lcc, id));
    printf("      - Vértices pertencentes:\n         ");
    l_show(lcc->list[id-1].vertexes);
}

void cc_destroyCComponents(l_ConnectedComponents *lcc)
{
    int i;
    for(i = 0; i < (*lcc)->size; i++)
        l_destroyList(&(*lcc)->list[i].vertexes);
    free((*lcc)->list);
    free(*lcc);
    *lcc = NULL;
}
/**
 * @file Grafo.h
 *
 * @author João Henrique Vieira do Carmo
 * @author Thiago Antonio Costa do Nascimento
 * 
 * @brief Biblioteca de grafos não ponderados.
 * 
 * Essa é um biblioteca livre de grafos não ponderados que implementa
 * as representações em matriz de adjacência e lista de adjacências, além
 * de implementar algoritmos de busca, distância e identificar componentes
 * conexos do grafo.
 * 
 * @version 0.2
 * @date 2024-06-13
 */

#ifndef M_UGRAFOS_H
#define M_UGRAFOS_H

/*******************************/
/*   Estruturas e definições   */
/*******************************/

/**
 * @brief Definição do índice do vérticie como um valor inteiro não-negativo.
 */
#define vertex int

/**
 * @brief Definição da estrutura do grafo com representação em matriz de adjacências.
 * Os índices de um grafo criado são acessados de 1 a N, sendo N o último vértice do 
 * grafo.
 * 
 * @note Campos ocultos na implementação.
 */
typedef struct m_graph *M_Graph;

/**
 * @brief Estrutura para uma lista de componentes conexos que podem ser extraídos de um grafo.
 */
typedef struct l_connected_components *l_ConnectedComponents;


/*****************************/
/*   Funções da Biblioteca   */
/*****************************/

/**
 * @brief matrix_graph: Criar a partir de um arquivo texto de adjacências, contendo 
 *        em sua primeira linha o número de vértices e as seguintes as adjacências.
 * 
 * @param path Caminho para o arquivo texto.
 * @retval ( M_Graph* ) - Ponteiro para o grafo criado;
 * @retval ( NULL ) - Ponteiro nulo indicando erro na criação por falha no arquivo ou na alocação.
 */
M_Graph mg_makeGraphFromFile(char *path);

/**
 * @brief matrix_graph: Cria um grafo de matriz de adjacências.
 * 
 * @details Após a criação do grafo, recomenda-se criar uma função que atualize os dados de todos os vértices,
 * os campos virão vazios.
 * 
 * @see mg_destroyGraph
 * @warning Não deixe de armazenar o retorno da função e use a função mg_destroyGraph() ao término do uso do grafo alocado.
 * 
 * @param V Número de vértices iniciais do grafo.
 * @retval ( M_Graph* ) - Ponteiro para um grafo alocado;
 * @retval ( NULL ) - Ponteiro nulo caso haja erro na alocação.
 */
M_Graph mg_makeGraph(size_t V);

/**
 * @brief matrix_graph: Desaloca a memória alocada de um grafo de matriz de adjacências.
 * 
 * @see mg_makeGraph
 * @warning sempre use essa função após o término do uso do grafo alocado na função mg_makeGraph()!
 * 
 * @param M_Graph Grafo a ser desalocado.
 */
void mg_destroyGraph(M_Graph *G);

/**
 * @brief matrix_graph: Insere uma aresta no grafo G, ligando os vértices v e u. Não admite arestas múltiplas.
 * 
 * @param G Grafo em que será inserido a aresta.
 * @param v Vértice v de origem/destino.
 * @param u Vértice u de origem/destino.
 * @retval ( 1 ) - Inserção bem-sucedida;
 * @retval ( 0 ) - Caso a aresta já exista ou algum parâmetro seja incoerente.
 */
int mg_insertEdge(M_Graph G, vertex v, vertex u);

/** 
 * @brief matrix_graph: Remove uma aresta no grafo G entre os vértices v e u
 * 
 * @param G Grafo em que será removido a arestas
 * @param v Vértice v de origem/destino
 * @param u Vértice u de origem/destino
 * @retval ( 1 ) - Remoção bem-sucedida;
 * @retval ( 0 ) - Caso a aresta não exista ou algum parâmetro seja incoerente.
 */
int mg_removeEdge(M_Graph G, vertex v, vertex u);

/**
 * @brief matrix_graph: Verifica a existência de uma aresta entre os vértices v e u.
 * 
 * @param G Grafo a ser considerado.
 * @param v Indice do vértice de origem/destino.
 * @param u Indice do vértice de origem/destino.
 * @retval ( 1 ) - existe uma aresta entre u e v; 
 * @retval ( 0 ) - NÃO existe uma aresta entre u e v.
 */
int mg_getEdge(M_Graph G, vertex v, vertex u);

/**
 * @brief matrix_graph: Exibe a matriz de adjacências.
 * 
 * @param G Grafo a ser exibido.
 */
void mg_show(M_Graph G);

/**
 * @brief matrix_graph: Gera um arquivo de saída com informações sobre o grafo.
 * 
 * @details As seguinte informações serão geradas: número de vértices, 
 * número de arestas, grau mínimo, grau máximo, grau médio, e mediana de grau.
 * 
 * @param G Grafo em questão.
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 * 
 * @retval ( 1 ) - Arquivo de saída gerado com sucesso;
 * @retval ( 0 ) - Erro na geração do arquivo de saída.
 */
int mg_outputFile(M_Graph G, char *path);

/**
 * @brief matrix_graph: Percorre o grafo usando a busca em largura e gera um arquivo de texto com árvore gerada.
 * 
 * @details O arquivo texto contém os vértices e seus respectivos níveis na árvore a partir da raiz (0).
 * 
 * @param G Grafo a ser percorrido.
 * @param v Vértice inicial.
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 * 
 * @retval ( 1 ) - Arquivo de saída gerado com sucesso;
 * @retval ( 0 ) - Erro na geração do arquivo de saída.
 */
int mg_bfs(M_Graph G, vertex v, char *path);

/**
 * @brief matrix_graph: Percorre o grafo usando a busca em profundidade e gera um arquivo de texto com árvore gerada.
 * 
 * @details O arquivo texto contém os vértices e seus respectivos níveis na árvore a partir da raiz (0).
 * 
 * @param G Grafo a ser percorrido.
 * @param v Vértice inicial.
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 * 
 * @retval ( 1 ) - Arquivo de saída gerado com sucesso;
 * @retval ( 0 ) - Erro na geração do arquivo de saída.
 */
int mg_dfs(M_Graph G, vertex v, char *path);

/**
 * @brief matrix_graph: Calcula a distância entre dois vértices utilizando BFS.
 * 
 * @param G Grafo em questão.
 * @param v Vértice de partida.
 * @param u Vértice de destino.
 * @retval ( int ) - Um número inteiro representando distância entre os dois vértices.
 * @retval ( -1 ) - Caso não exista um caminho entre os dois vértices.
 */
int mg_distance(M_Graph G, vertex v, vertex u);

/**
 * @brief matrix_graph: A excentricidade de é um vértice v, E(v), é o valor da distância
 * máxima da distãncia entre v e w, para todo w pertencente ao conjunto dos vértices V
 * de G(V,E). Essa função calcula a maior distância mínima de v a um vértice w.
 * 
 * @details Base teórica da excentricidade infinita: 
 *      West, D. B. Introduction to Graph Theory, 2nd ed. Englewood Cliffs, NJ: Prentice-Hall, 2000.
 *          - pág. 71.
 * 
 * @param G Grafo em questão.
 * @retval ( int ) - Maior distância mínima possíveis de v a w.
 * @retval ( -1 ) - O grafo é desconexo, logo a excentricidade do vértice é infinita.
 */
int mg_vertexEccentricity(M_Graph G, vertex v);

/**
 * @brief matrix_graph: O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho do grafo. Essa função garante o diâmetro exato de um grafo 
 * conectado, porém sua complexidade é O(V^3).
 * 
 * @param G Grafo em questão.
 * @retval ( int ) - Diâmetro do grafo.
 * @retval ( -1 ) - O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.
 */
int mg_absoluteDiameter(M_Graph G);

/**
 * @brief matrix_graph: O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho do grafo. Essa função retorna o diâmetro aproximado de um grafo 
 * conectado, porém com uma alta taxa de precisão. Sua complexidade é duas vezes O(V^2).
 * 
 * @param G Grafo em questão.
 * @retval ( int ) - Diãmetro do grafo.
 * @retval ( -1 ) - O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.
 */
int mg_aprroximateDiameter(M_Graph G);

/**
 * @brief matrix_graph: Calcula e retorna um lista de componentes conectados do grafo. A partir dela pode-se
 * utlizar funções adicionais da biblioteca que retornam a quantidade de componentes conexos, listam os
 * os componentes em ordem decrescente e exibe os dados de um componente específico.
 * 
 * @warning Essa estrutura deve ser desalocada pela função mg_destroyCComponents
 * 
 * @see mg_getNumOfCComponents, mg_listCComponent, mg_showCComponent, mg_destroyCComponents
 * 
 * @param G Grafo em questão.
 * 
 * @retval ( l_ConnectedComponents ) - Um ponteiro para a estrutura alocada de lista de componentes conexos.
 */
l_ConnectedComponents mg_connectedComponents(M_Graph G);

/**
 * @brief Retorna o número de componentes conexos extraídos de um grafo.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 * @return Quantidade de componentes na lista.
 */
int mg_getNumOfCComponents(l_ConnectedComponents l);

/**
 * @brief Lista os componentes e seus tamanhos de forma crescente de uma lista de componentes conexos.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 */
void mg_listCComponents(l_ConnectedComponents l);

/**
 * @brief Exibe as informações de tamanho e exibe os vértices pertencentes a um componente conexo.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 * @param id Identificador do componente em questão. O identificador pode ser encontrado na função mg_listCComponents.
 */
void mg_showCComponent(l_ConnectedComponents l, int id);

/**
 * @brief Desaloca a memória de uma lista de componentes conexos.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 */
void mg_destroyCComponents(l_ConnectedComponents *l);

#endif
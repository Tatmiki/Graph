/**
 * @file L_UGrafo.h
 *
 * @author João Henrique Vieira do Carmo
 * @author Thiago Antonio Costa do Nascimento
 * 
 * @brief Biblioteca de grafos não ponderados com representação de lista de adjacências.
 * 
 * Essa é um biblioteca livre de grafos não ponderados que implementa a representação de 
 * lista de adjacências, além de implementar algoritmos de busca, distância e identificar 
 * componentes conexos do grafo.
 * 
 * @version 0.1
 * @date 2024-06-16
 * @since 2024-06-08
 */

#ifndef L_UGRAFOS_H
#define L_UGRAFOS_H

/*******************************/
/*   Estruturas e definições   */
/*******************************/

/**
 * @brief Definição do índice do vérticie como um valor inteiro não-negativo.
 */
#define vertex unsigned int

/**
 * @brief Definição da strutura do grafo com representação em lista de adjacências.
 * Os índices de um grafo criado são acessados de 1 a N, sendo N o último vértice 
 * do grafo.
 * 
 * @note Campos ocultos na implementação.
 */
typedef struct l_graph *L_Graph;


/*****************************/
/*   Funções da Biblioteca   */
/*****************************/

/**
 * @brief list_graph: Criar um grafo apartir de um arquivo texto de adjacências, contendo 
 *        em sua primeira linha o número de vértices e as seguintes as adjacências.
 *
 * @param path Caminho para o arquivo texto.
 * @retval ( L_Graph* ) - Ponteiro para o grafo criado;
 * @retval ( NULL ) - Ponteiro nulo indicando erro na criação por falha no arquivo ou na alocação.
 */
L_Graph lg_makeGraphFromFile(char *path);

/**
 * @brief list_graph: Cria um grafo de lista de adjacências.
 * 
 * @details Após a criação do grafo, recomenda-se criar uma função que atualize os dados de todos os vértices,
 * os campos virão vazios.
 * @see lg_destroyGraph
 * 
 * @warning Não deixe de armazenar o retorno da função e use a função lg_destroyGraph() ao término do uso do grafo alocado.
 * 
 * @param V Número de vértices iniciais do grafo.
 * @retval ( L_Graph* ) - Pontereito para um grafo de lista de adjacências alocado;
 * @retval ( NULL ) - Ponteiro nulo caso haja erro na alocação.
 */
L_Graph lg_makeGraph(size_t V);

/**
 * @brief list_graph: Desaloca a memória alocada de um grafo de lista de adjacências.
 * 
 * @see lg_makeGraph
 * @warning sempre use essa função após o término do uso do grafo alocado na função lg_makeGraph()!
 * 
 * @param L_Graph Endereço do grafo a ser desalocado.
 */
void lg_destroyGraph(L_Graph *G);

/**
 * @brief list_graph: Insere uma aresta no grafo G, ligando os vértices v e u. Não admite arestas múltiplas.
 * 
 * @param G Grafo em que a aresta será inserida
 * @param v Vértice v de origem/entrada
 * @param u Vértice u de origem/entrada
 * @retval ( 0 ) - para inserção bem-sucedida;
 * @retval ( 1 ) - caso a aresta já exista ou algum parâmetro seja incoerente.
 */
int lg_insertEdge(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Remove uma aresta do grafo G entre os vértices v e u.
 * 
 * @param G Grafo em que a aresta será removida.
 * @param v Vértice v de origem/destino da aresta.
 * @param u Vértice u de origem/destino da aresta.
 * @retval ( 0 ) - se a remoção bem-sucedida;
 * @retval ( 1 ) - caso a aresta já exista ou algum parâmetro seja incoerente.
 */
int lg_removeEdge(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Verifica a existência de uma aresta entre os vértices v e u.
 * 
 * @param G Grafo a ser considerado.
 * @param v Indice do vértice de origem/destino.
 * @param u Indice do vértice de origem/destino.
 * @retval ( 1 ) - se existe uma aresta entre u e v; 
 * @retval ( 0 ) - se não existe uma aresta entre u e v.
 */
int lg_getEdge(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Exibe o grafo através de uma lista de adjacência
 * 
 * @param G Grafo a ser exibido 
 */
void lg_show(L_Graph G);

/**
 * @brief list_graph: Gera um arquivo de saída com informações sobre o grafo.
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
int lg_outputFile(L_Graph G, char *path);

/**
 * @brief list_graph: Percorre o grafo usando a busca em largura e gera um arquivo de texto com árvore gerada.
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
int lg_bsf(L_Graph G, vertex v, char *path);

/**
 * @brief list_graph: Percorre o grafo usando a busca em profundidade e gera um arquivo de texto com árvore gerada.
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
int lg_dfs(L_Graph G, vertex v, char *path);

/**
 * @brief list_graph: Calcula a distância entre dois vértices utilizando BFS.
 * 
 * @param G Grafo em questão.
 * @param v Vértice de partida.
 * @param u Vértice de destino.
 * @retval ( int ) - A distância entre os dois vértices.
 * @retval ( 0 ) - Caso não exista um caminho entre os dois vértices.
 */
int lg_distance(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Calcula o diâmetro de um grafo.
 * 
 * @details O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho do grafo.
 * 
 * @param G Grafo em questão.
 * @return Retorna o diâmetro do grafo.
 */
int lg_diameter(L_Graph G);

/**
 * @brief list_graph: Imprime informações sobre os componentes conexos de um grafo e lista os vértices pertencentes 
 * a cada um.
 * 
 * @details Serão impressos informações do tamanho (em vértices) dos componentes e a lista de vértices
 * pertencentes a cada um dos componentes. A listagem será feita em ordem decrescente (do maior ao menor).
 * 
 * @param G Grafo em questão.
 */
void lg_listConnectedComponents(L_Graph G);

#endif
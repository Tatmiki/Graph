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

void lg_bsf();
void lg_dfs();

#endif
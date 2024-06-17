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
#define vertex unsigned int


/*****************************/
/*   Funções da Biblioteca   */
/*****************************/

/**
 * @brief Definição da estrutura do grafo com representação em matriz de adjacências.
 * 
 * @note Campos ocultos na implementação.
 */
typedef struct m_graph *M_Graph;

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

void mg_bsf();
void mg_dfs();

#endif
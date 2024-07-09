/**
 * @file Graph.h
 *
 * @author João Henrique Vieira do Carmo
 * @author Thiago Antonio Costa do Nascimento
 * 
 * @brief Biblioteca de grafos não ponderados.
 * 
 * @details Essa é um biblioteca livre de grafos não ponderados que implementa
 * as representações em matriz de adjacência e lista de adjacências, além
 * de implementar algoritmos de busca, distância e identificar componentes
 * conexos do grafo.
 * 
 * @version 1.0
 * @date 2024-07-07
 */

#ifndef GRAPH_H
#define GRAPH_H

/*******************************/
/*   Estruturas e definições   */
/*******************************/

/**
 * @brief Definição do índice do vérticie como um valor inteiro.
 */
#define vertex int

/**
 * @brief Definição da estrutura do grafo com representação em lista de adjacências.
 * Os índices de um grafo criado são acessados de 1 a N, sendo N o último vértice 
 * do grafo.
 */
typedef struct l_graph *L_Graph;

/**
 * @brief Definição da estrutura do grafo com representação em matriz de adjacências.
 * Os índices de um grafo criado são acessados de 1 a N, sendo N o último vértice do 
 * grafo.
 */
typedef struct m_graph *M_Graph;

/**
 * @brief Estrutura de lista de componentes conexos. Utilizada para extrair as informações 
 * dos componentes conexos de um grafo.
 */
typedef struct l_connected_components *l_ConnectedComponents;

//----------------------------------------------------------------------------------

/*****************************/
/*   Funções da Biblioteca   */
/*****************************/

/**
 * @brief list_graph: Cria um grafo a partir de um arquivo texto de adjacências, contendo 
 * em sua primeira linha o número de vértices e as seguintes as adjacências.
 *
 * @param path Caminho para o arquivo texto (completo ou em relação ao ambiente de execução).
 * 
 * @retval L_Graph - Ponteiro para o grafo criado;
 * @retval NULL - Ponteiro nulo indicando erro na criação por falha no arquivo ou na alocação.
 */
L_Graph lg_makeGraphFromFile(char *path);

/**
 * @brief list_graph: Cria um grafo de lista de adjacências.
 * 
 * @warning Não deixe de armazenar o retorno da função e use a função lg_destroyGraph() ao término do uso do grafo alocado.
 * @see lg_destroyGraph
 * 
 * @param V Número de vértices iniciais do grafo.
 * 
 * @retval L_Graph* - Pontereito para um grafo de lista de adjacências alocado;
 * @retval NULL - Ponteiro nulo caso haja erro na alocação.
 */
L_Graph lg_makeGraph(int V);

/**
 * @brief list_graph: Desaloca a memória alocada de um grafo de lista de adjacências e configura seu ponteiro para nulo.
 * 
 * @warning Sempre use essa função após o término do uso do grafo alocado na função lg_makeGraph()!
 * @see lg_makeGraph
 * 
 * @param L_Graph Endereço do grafo a ser desalocado.
 */
void lg_destroyGraph(L_Graph *G);

/**
 * @brief list_graph: Insere uma aresta no grafo G, ligando os vértices v e u. Não admite arestas múltiplas.
 * 
 * @param G Grafo em que a aresta será inserida;
 * @param v Vértice v de origem/entrada;
 * @param u Vértice u de origem/entrada.
 * 
 * @retval 0 - para inserção bem-sucedida;
 * @retval 1 - caso a aresta já exista ou algum parâmetro seja incoerente.
 */
int lg_insertEdge(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Remove uma aresta do grafo G entre os vértices v e u.
 * 
 * @param G Grafo em questão.
 * @param v Vértice v de origem/destino;
 * @param u Vértice u de origem/destino.
 * 
 * @retval 0 - se a remoção foi bem-sucedida;
 * @retval 1 - caso a aresta não exista ou algum parâmetro seja incoerente.
 */
int lg_removeEdge(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Verifica a existência de uma aresta entre os vértices v e u.
 * 
 * @param G Grafo a ser considerado;
 * @param v Vértice v de origem/destino;
 * @param u Vértice u de origem/destino.
 * 
 * @retval 1 - Existe uma aresta entre u e v; 
 * @retval 0 - NÃO existe uma aresta entre u e v.
 */
int lg_getEdge(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: Exibe o grafo de lista de adjacências.
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
 * @retval 1 - Arquivo de saída gerado com sucesso;
 * @retval 0 - Erro na geração do arquivo de saída.
 */
int lg_outputFile(L_Graph G, char *path);

/**
 * @brief list_graph: Percorre o grafo usando a busca em largura e gera um arquivo de texto da árvore geradorada.
 * 
 * @details O arquivo texto contém os vértices e seus respectivos níveis na árvore a partir da raiz (0).
 * 
 * @param G Grafo a ser percorrido;
 * @param v Vértice inicial.
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 *  
 * @retval 1 - Arquivo de saída gerado com sucesso;
 * @retval 0 - Erro na geração do arquivo de saída.
 */
int lg_bfs(L_Graph G, vertex v, char *path);

/**
 * @brief list_graph: Percorre o grafo usando a busca em profundidade e gera um arquivo de texto da árvore geradora.
 * 
 * @details O arquivo texto contém os vértices e seus respectivos níveis na árvore a partir da raiz (0).
 * 
 * @param G Grafo a ser percorrido;
 * @param v Vértice inicial;
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 *  
 * @retval 1 - Arquivo de saída gerado com sucesso;
 * @retval 0 - Erro na geração do arquivo de saída.
 */
int lg_dfs(L_Graph G, vertex v, char *path);

/**
 * @brief list_graph: Calcula a distância entre dois vértices utilizando BFS.
 * 
 * @param G Grafo em questão;
 * @param v Vértice de partida;
 * @param u Vértice de destino.
 * 
 * @retval int - A distância entre os dois vértices;
 * @retval -1 - Caso não exista um caminho direto entre os dois vértices.
 */
int lg_distance(L_Graph G, vertex v, vertex u);

/**
 * @brief list_graph: A excentricidade de é um vértice v, E(v), é o valor da distância
 * máxima da distãncia entre v e w, para todo w pertencente ao conjunto dos vértices V
 * de G(V,E). Essa função calcula a maior distância mínima de v a um vértice w.
 * 
 * @details Base teórica da excentricidade infinita: 
 *      West, D. B. Introduction to Graph Theory, 2nd ed. Englewood Cliffs, Prentice-Hall, 2000.
 *          - pág. 71.
 * 
 * @param G Grafo em questão.
 * @param v Vértice em questão.
 * 
 * @retval int - Maior distância mínima possíveis de v a w;
 * @retval -1 - O grafo é desconexo, logo a excentricidade do vértice é infinita.
 */
int lg_vertexEccentricity(L_Graph G, vertex v);

/**
 * @brief list_graph: O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho do grafo. Essa função garante o diâmetro exato de um grafo 
 * conectado, porém sua complexidade é O(V * (V + E)).
 * 
 * @param G Grafo em questão.
 * 
 * @retval int - Diâmetro do grafo;
 * @retval -1 - O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.
 */
int lg_absoluteDiameter(L_Graph G);

/**
 * @brief list_graph: O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho mínimo do grafo. Essa função retorna o diâmetro aproximado de um grafo 
 * conectado, porém com uma alta taxa de precisão. Sua complexidade é duas vezes O(V + E).
 * 
 * @details O princípio é que selecionamos um vértice qualquer (a função escolhe o 1º) e executamos
 * a BFS nele e descobrimos o vértice v mais distante, então executamos a BFS em v e descobrimos o
 * vértice u mais distante, e nisso temos que a distância entre v e u é o diâmetro do grafo.
 * 
 * @param G Grafo em questão.
 * 
 * @retval int - Diâmetro do grafo;
 * @retval -1 - O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.
 */
int lg_aprroximateDiameter(L_Graph G);

/**
 * @brief list_graph: Calcula e retorna um lista de componentes conectados de um grafo. A partir dela pode-se
 * utlizar funções adicionais da biblioteca que retornam a quantidade de componentes conexos, listam os
 * os componentes em ordem decrescente e exibe os dados de um componente específico.
 * 
 * @details Serão extraídas informações do tamanho (em vértices) dos componentes e a lista de vértices
 * pertencentes a cada um dos componentes. A lista será feita em ordem decrescente (do maior ao menor).
 * 
 * @warning Essa estrutura deve ser desalocada pela função cc_destroyCComponents
 * @see cc_getNumOfCComponents, cc_listCComponent, cc_showCComponent, cc_destroyCComponents
 * 
 * @param G Grafo em questão.
 * 
 * @retval l_ConnectedComponents - Lista de componentes conectados e suas informações.
 */
l_ConnectedComponents lg_connectedComponents(L_Graph G);

//----------------------------------------------------------------------------------

/**
 * @brief matrix_graph: Cria a partir de um arquivo texto de adjacências, contendo 
 * em sua primeira linha o número de vértices e as seguintes as adjacências.
 * 
 * @param path Caminho para o arquivo texto (completo ou em relação ao ambiente de execução).
 * 
 * @retval M_Graph* - Ponteiro para o grafo criado;
 * @retval NULL - Ponteiro nulo indicando erro na criação por falha no arquivo ou na alocação.
 */
M_Graph mg_makeGraphFromFile(char *path);

/**
 * @brief matrix_graph: Cria um grafo de matriz de adjacências.
 * 
 * @warning Não deixe de armazenar o retorno da função e use a função mg_destroyGraph() ao término do uso do grafo alocado.
 * @see mg_destroyGraph
 * 
 * @param V Número de vértices iniciais do grafo.
 * 
 * @retval M_Graph - Ponteiro para um grafo alocado;
 * @retval NULL - Ponteiro nulo caso haja erro na alocação.
 */
M_Graph mg_makeGraph(int V);

/**
 * @brief matrix_graph: Desaloca a memória alocada de um grafo de matriz de adjacências e configura seu ponteiro para nulo.
 * 
 * @warning Sempre use essa função após o término do uso do grafo alocado na função mg_makeGraph()!
 * @see mg_makeGraph
 * 
 * @param M_Graph Endereço do grafo a ser desalocado.
 */
void mg_destroyGraph(M_Graph *G);

/**
 * @brief matrix_graph: Insere uma aresta no grafo G, ligando os vértices v e u. Não admite arestas múltiplas.
 * 
 * @param G Grafo em que será inserido a aresta;
 * @param v Vértice v de origem/destino;
 * @param u Vértice u de origem/destino.
 * 
 * @retval 1 - Inserção bem-sucedida;
 * @retval 0 - Caso a aresta já exista ou algum parâmetro seja incoerente.
 */
int mg_insertEdge(M_Graph G, vertex v, vertex u);

/** 
 * @brief matrix_graph: Remove uma aresta no grafo G entre os vértices v e u.
 * 
 * @param G Grafo em questão;
 * @param v Vértice v de origem/destino;
 * @param u Vértice u de origem/destino.
 * 
 * @retval 1 - Remoção bem-sucedida;
 * @retval 0 - Caso a aresta não exista ou algum parâmetro seja incoerente.
 */
int mg_removeEdge(M_Graph G, vertex v, vertex u);

/**
 * @brief matrix_graph: Verifica a existência de uma aresta entre os vértices v e u.
 * 
 * @param G Grafo em questão;
 * @param v Vértice de origem/destino;
 * @param u Vértice de origem/destino.
 * 
 * @retval 1 - existe uma aresta entre u e v; 
 * @retval 0 - NÃO existe uma aresta entre u e v.
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
 * @retval 1 - Arquivo de saída gerado com sucesso;
 * @retval 0 - Erro na geração do arquivo de saída.
 */
int mg_outputFile(M_Graph G, char *path);

/**
 * @brief matrix_graph: Percorre o grafo usando a busca em largura e gera um arquivo de texto da árvore geradora.
 * 
 * @details O arquivo texto contém os vértices e seus respectivos níveis na árvore a partir da raiz (0).
 * 
 * @param G Grafo a ser percorrido;
 * @param v Vértice inicial;
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 * 
 * @retval 1 - Arquivo de saída gerado com sucesso;
 * @retval 0 - Erro na geração do arquivo de saída.
 */
int mg_bfs(M_Graph G, vertex v, char *path);

/**
 * @brief matrix_graph: Percorre o grafo usando a busca em profundidade e gera um arquivo de texto da árvore geradora.
 * 
 * @details O arquivo texto contém os vértices e seus respectivos níveis na árvore a partir da raiz (0).
 * 
 * @param G Grafo a ser percorrido;
 * @param v Vértice inicial;
 * @param path String indicando o caminho e nome do arquivo de texto de saída(ex: "./graphs/output/saida.txt").
 * 
 * @retval 1 - Arquivo de saída gerado com sucesso;
 * @retval 0 - Erro na geração do arquivo de saída.
 */
int mg_dfs(M_Graph G, vertex v, char *path);

/**
 * @brief matrix_graph: Calcula a distância entre dois vértices utilizando BFS.
 * 
 * @param G Grafo em questão;
 * @param v Vértice de origem/destino;
 * @param u Vértice de origem/destino.
 * 
 * @retval int - Um número inteiro representando distância entre os dois vértices;
 * @retval -1 - Caso não exista um caminho entre os dois vértices.
 */
int mg_distance(M_Graph G, vertex v, vertex u);

/**
 * @brief matrix_graph: A excentricidade de é um vértice v, E(v), é o valor da distância
 * máxima da distãncia entre v e w, para todo w pertencente ao conjunto dos vértices V
 * de G(V,E). Essa função calcula a maior distância mínima de v a um vértice w.
 * 
 * @details Base teórica da excentricidade infinita: 
 *      West, D. B. Introduction to Graph Theory, 2nd ed. Englewood Cliffs, Prentice-Hall, 2000.
 *          - pág. 71.
 * 
 * @param G Grafo em questão.
 * @param v Vértice em questão.
 * 
 * @retval int - Maior distância mínima possíveis de v a w.
 * @retval -1 - O grafo é desconexo, logo a excentricidade do vértice é infinita.
 */
int mg_vertexEccentricity(M_Graph G, vertex v);

/**
 * @brief matrix_graph: O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho mínimo do grafo. Essa função garante o diâmetro exato de um grafo 
 * conectado, porém sua complexidade é O(V^3).
 * 
 * @param G Grafo em questão.
 * 
 * @retval int - Diâmetro do grafo.
 * @retval -1 - O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.
 */
int mg_absoluteDiameter(M_Graph G);

/**
 * @brief matrix_graph: O diâmetro de um grafo é a maior distância entre qualquer par de vértices do grafo,
 * ou seja, o comprimento do maior caminho do grafo. Essa função retorna o diâmetro aproximado de um grafo 
 * conectado, porém com uma alta taxa de precisão. Sua complexidade é duas vezes O(V^2).
 * 
 * @param G Grafo em questão.
 * 
 * @retval int - Diãmetro do grafo.
 * @retval -1 - O grafo é desconexo, logo a excentricidade é infinita para todos os vértices, tanto quanto para do diâmetro.
 */
int mg_aprroximateDiameter(M_Graph G);

/**
 * @brief matrix_graph: Calcula e retorna um lista de componentes conectados de um grafo. A partir dela pode-se
 * utlizar funções adicionais da biblioteca que retornam a quantidade de componentes conexos, listam os
 * os componentes em ordem decrescente e exibe os dados de um componente específico.
 * 
 * @warning Essa estrutura deve ser desalocada pela função cc_destroyCComponents
 * @see cc_getNumOfCComponents, cc_listCComponent, cc_showCComponent, cc_destroyCComponents
 * 
 * @param G Grafo em questão.
 * 
 * @retval l_ConnectedComponents - Lista de componentes conectados e suas informações.
 */
l_ConnectedComponents mg_connectedComponents(M_Graph G);

//----------------------------------------------------------------------------------

/**
 * @brief Retorna o número de componentes conexos extraídos de um grafo.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 * 
 * @return Quantidade de componentes na lista.
 */
int cc_getNumOfCComponents(l_ConnectedComponents l);

/**
 * @brief Lista os componentes e seus tamanhos de forma crescente de uma lista de componentes conexos.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 */
void cc_listCComponents(l_ConnectedComponents l);

/**
 * @brief Exibe as informações de tamanho e exibe os vértices pertencentes a um componente conexo.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 * @param id Identificador do componente em questão. O identificador pode ser encontrado na função mg_listCComponents.
 */
void cc_showCComponent(l_ConnectedComponents l, int id);

/**
 * @brief Exibe o tamanho, em vértices, de um componente conectado pertecente a uma lista de componentes.
 * 
 * @param l Lista de componentes conexos anteriormente extraída.
 * @param id Identificador do componente em questão. O identificador pode ser encontrado na função mg_listCComponents.
 * 
 * @return int - Número de vértices que compõem o componente em questão.
 */
int cc_getSizeCComponent(l_ConnectedComponents l, int id);

/**
 * @brief Desaloca a memória de uma lista de componentes conexos e configura seu ponteiro para nulo.
 * 
 * @warning Sempre use essa função após o término do uso do grafo alocado 
 * na função mg_connectedComponents() ou lg_connectedComponents!
 * @see mg_connectedComponents, lg_connectedComponents
 *
 * @param l Lista de componentes conexos anteriormente extraída.
 */
void cc_destroyCComponents(l_ConnectedComponents *l);

#endif // GRAPH_H
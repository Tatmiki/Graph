/**
 * @file List_W.h
 * @author João Henrique
 * @brief Bibiblioteca de lista escadeada dinâmica.
 * 
 * @version 1.0
 * @date 2024-07-02
 */

#ifndef LIST_W_H
#define LIST_W_H

#include "Util.h"

/**
 * @brief Estrutura de nó para navegação da lista dinâmica.
 */
typedef struct node_w 
{
    WeightedEdge edge;         /*> Par ordenado de vértice e peso.             */
    struct node_w* next;    /*> Ponteiro para o próximo elemento da lista.  */
} *Node_W;

/**
 * @brief Estrutura da lista encadeada dinâmica.
 */
typedef struct list_w
{
    Node_W head;    /*> Nó do primeiro elemento da lista.   */
    int size;       /*> Tamanho da lista.                   */
} *List_W;

/**
 * @brief Aloca e inicializa um lista dinâmica e a retorna para uso.
 * 
 * @warning Lembre-se de desalocá-la com a função lw_destroyList().
 * @see lw_destroyList
 * 
 * @retval List_W - Lista alocada e inicializada.
 */
List_W lw_initList();

/**
 * @brief Dessaloca uma lista passada por parâmetro de referência e configura seu ponteiro para nulo.
 * 
 * @param lw Um ponteiro para a lista a ser desalocada.
 */
void lw_destroyList(List_W *lw);

/**
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param lw Lista em questão;
 * @param v Elemento a ser adicionado.
 * 
 * @return 1 para sucesso, caso contrário o erro de alocação encerrará o programa.
 */
int lw_insertBeggining(List_W lw, int v, double w);

/**
 * @brief Remove um elemento da lista.
 * 
 * @param lw Lista em questão;
 * @param v Elemento a ser eliminado (se houver mais de um, o primeiro encontrado será eliminado).
 * 
 * @retval 1 - Elemento encontrado e eliminado com sucesso;
 * @retval 0 - Elemento não encontrado.
 */
int lw_remove(List_W lw, int v);

/**
 * @brief Busca um elemento na lista.
 * 
 * @param lw Lista em questão;
 * @param v Elemento a ser buscado.
 * 
 * @retval double - Valor de w do elemento encontrado;
 * @retval 0 - Elemento não encontrado.
 */
WeightedEdge* lw_find(List_W lw, int v);

/**
 * @brief Exibe a lista.
 *
 * @param lw Lista a ser exibida.
 */
void lw_show(List_W lw);

/**
 * @brief Retorna a quantidade de elementos ou tamanho da lista.
 * 
 * @param lw Lista em questão.
 * @return int - Número de elementos da lista
 */
int lw_getSize(List_W lw);

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param lw Lista em questão.
 * @retval 1 - A lista está vazia.
 * @retval 0 - A lista NÃO está vazia.
 */
int lw_isEmpty(List_W lw);

#endif
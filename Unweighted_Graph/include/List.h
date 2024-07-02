/**
 * @file List.h
 * @author João Henrique
 * @brief Bibiblioteca de lista escadeada dinâmica.
 * 
 * @version 1.0
 * @date 2024-07-02
 */

#ifndef LIST_H
#define LIST_H

/**
 * @brief Estrutura de nó para navegação da lista dinâmica.
 */
typedef struct node 
{
    int w;
    struct node* next;
} *Node;

/**
 * @brief Estrutura da lista com a cabeça e a quantidade de elementos (size).
 */
typedef struct list
{
    Node head;
    int size;
} *List;

/**
 * @brief Aloca e inicializa um lista dinâmica e a retorna para uso.
 * 
 * @warning Lembre-se de desalocá-la com a função l_destroyList().
 * 
 * @retval ( List ) - Ponteiro para um lista alocada e inicializada.
 */
List l_initList();

/**
 * @brief Dessaloca uma lista passada por parâmetro de referência e configura o ponteiro de sua
 * estrutura para nulo.
 * 
 * @param l Um ponteiro para a lista a ser desalocada.
 */
void l_destroyList(List *l);

/**
 * @brief Insere um novo elemento no início da lista.
 * 
 * @param l Lista em questão.
 * @param v Elemento a ser adicionado.
 * @return 1 para sucesso, caso contrário o erro de alocação encerrará o programa.
 */
int l_insertBeggining(List l, int v);

/**
 * @brief Remove um elemento da lista.
 * 
 * @param l Lista em questão.
 * @param v Elemento a ser eliminado (se houver mais de um, o primeiro encontrado será eliminado)
 * @retval ( 1 ) - Elemento encontrado e eliminado com sucesso.
 * @retval ( 0 ) - Elemento não encontrado.
 */
int l_remove(List l, int v);

/**
 * @brief Busca um elemento na lista.
 * 
 * @param l Lista em questão.
 * @param w Elemento a ser buscado.
 * @retval ( 1 ) - Elemento encontrado.
 * @retval ( 0 ) - Elemento não encontrado.
 */
int l_find(List l, int w);

/**
 * @brief Exibe a lista
 *
 * @param l Lista a ser exibida.
 */
void l_show(List l);

/**
 * @brief Retorna a quantidade de elementos ou tamanho da lista.
 * 
 * @param l Lista em questão.
 * @return ( int ) - Número de elementos da lista
 */
int l_getSize(List l);

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param l Lista em questão.
 * @retval ( 1 ) - A lista está vazia.
 * @retval ( 0 ) - A lista NÃO está vazia.
 */
int l_isEmpty(List l);

#endif
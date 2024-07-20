/**
 * @file Queue.h
 * @author João Henrique
 * @brief Biblioteca de pilha encadeada dinâmica.
 * 
 * @version 1.0
 * @date 2024-07-02
 */

#ifndef STACK_H
#define STACK_H

/**
 * @brief Estrutura da pilha dinâmica encadeada.
 * 
 * @note Campos ocultos na implementação.
 */
typedef struct stack *Stack;

/**
 * @brief Aloca e inicializa uma pilha dinâmica.
 * 
 * @warning Lembre-se de desalocar a pilha após o uso com a função q_destroyQueue().
 * @see q_destroyQueue
 * 
 * @retval Stack - Pilha alocada e inicializada.
 */
Stack s_initStack();

/**
 * @brief Desaloca a pilha e configura seu ponteiro para nulo.
 * 
 * @param p Ponteiro para a pilha em questão.
 */
void s_destroyStack(Stack *p);

/**
 * @brief Empilha um elemento no topo.
 *
 * @param p Pilha em questão;
 * @param w Valor a ser inserido na pilha.
 * 
 * @retval 1 - Valor inserido com sucesso;
 * @retval 0 - Falha na alocação de memória.
 */
void s_push(Stack p, int w);

/**
 * @brief Desempilha um elemento do topo.
 * 
 * @warning Garanta que a pilha não está vazia!
 * 
 * @param p Pilha em questão.
 * 
 * @retval int - Elemento que foi removido da pilha.
 */
int s_pop(Stack p);

/**
 * @brief Retorna o primeiro elemento da pilha (topo).
 * 
 * @warning Certifique-se de que a pilha não está vazia.
 * 
 * @param p Pilha em questão.
 * 
 * @retval int - Topo da pilha. 
 */
int s_top(Stack p);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param p Pilha em questão.
 * 
 * @retval 1 - A pilha está vazia;
 * @retval 0 - A pilha NÃO está vazia.
 */
int s_isEmpty(Stack p);

#endif
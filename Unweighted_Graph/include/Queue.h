/**
 * @file Queue.h
 * @author João Henrique
 * @brief Biblioteca de fila dinâmica.
 * 
 * @version 1.0
 * @date 2024-07-02
 */

#ifndef QUEUE_H
#define QUEUE_H


/**
 * @brief Estrutura da fila.
 * 
 * @note Oculta na implementação..
 */
typedef struct queue *Queue;

/**
 * @brief Aloca e inicializa uma fila dinâmica.
 * 
 * @warning Lembre-se de desalocar a fila apoós o uso com a função q_destroyQueue().
 * 
 * @retval ( Queue ) - Um ponteiro para uma fila alocada e inicializada.
 */
Queue q_initQueue();

/**
 * @brief Desaloca a fila e configura seu ponteiro para nulo.
 * 
 * @param q Ponteiro para a fila m questão.
 */
void q_destroyQueue(Queue *q);

/**
 * @brief Enfilera um elemento no final da fila.
 * 
 * @param q Fila em questão.
 * @param w Valor a ser inserido na fila.
 * @retval ( 1 ) - Valor inserido com sucesso.
 * @retval ( 0 ) - Falha na alocação de memória.
 */
int q_enqueue(Queue q, int w);

/**
 * @brief Desenfilera um elemento do início da fila.
 * 
 * @param q Fila em questão.
 * @retval ( int ) - Elemento que foi removido da fila.
 */
int q_dequeue(Queue q);

/**
 * @brief Retorna o primeiro elemento da fila (frente da fila).
 * 
 * @warning Certifique-se de que a fila não está vazia.
 * 
 * @param q Fila em questão.
 * @retval ( int ) - Primeiro elemento da fila. 
 */
int q_front(Queue q);

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param q 
 * @return int 
 */
int q_isEmpty(Queue q);

#endif
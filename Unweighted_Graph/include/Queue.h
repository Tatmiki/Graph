/**
 * @file Queue.h
 * @author João Henrique
 * @brief Biblioteca de fila encadeada dinâmica.
 * 
 * @version 1.0
 * @date 2024-07-02
 */

#ifndef QUEUE_H
#define QUEUE_H

/**
 * @brief Estrutura da fila dinâmica encadeada.
 * 
 * @note Campos ocultos na implementação.
 */
typedef struct queue *Queue;

/**
 * @brief Aloca e inicializa uma fila dinâmica.
 * 
 * @warning Lembre-se de desalocar a fila apoós o uso com a função q_destroyQueue().
 * @see q_destroyQueue
 * 
 * @retval Queue - Fila alocada e inicializada.
 */
Queue q_initQueue();

/**
 * @brief Desaloca a fila e configura seu ponteiro para nulo.
 * 
 * @param q Ponteiro para a fila em questão.
 */
void q_destroyQueue(Queue *q);

/**
 * @brief Enfilera um elemento no final da fila.
 *
 * @param q Fila em questão;
 * @param w Valor a ser inserido na fila.
 * 
 * @retval 1 - Valor inserido com sucesso;
 * @retval 0 - Falha na alocação de memória.
 */
int q_enqueue(Queue q, int w);

/**
 * @brief Desenfilera um elemento do início da fila.
 * 
 * @warning Garanta que a fila não está vazia!
 * 
 * @param q Fila em questão.
 * 
 * @retval int - Elemento que foi removido da fila.
 */
int q_dequeue(Queue q);

/**
 * @brief Retorna o primeiro elemento da fila (frente da fila).
 * 
 * @warning Certifique-se de que a fila não está vazia.
 * 
 * @param q Fila em questão.
 * 
 * @retval int - Primeiro elemento da fila. 
 */
int q_front(Queue q);

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param q FIla em questão.
 * 
 * @retval 1 - A fila está vazia;
 * @retval 0 - A fila NÃO está vazia.
 */
int q_isEmpty(Queue q);

#endif
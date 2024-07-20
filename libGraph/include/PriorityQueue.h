/**
 * @file PriorityQueue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Util.h"

/**
 * @brief Estrutura da fila de prioridade implementada com árvore mín heap.
 * 
 * @note Campos ocultos na implementação.
 */
typedef struct priority_queue *PriorityQueue;

/**
 * @brief Aloca e inicializa uma fila de prioridade.
 * 
 * @warning Lembre-se de desalocar a fila após o uso com a função pq_destroyPQueue().
 * @see pq_destroyPQueue
 * 
 * @retval PriorityQueue - Fila alocada e inicializada.
 */
PriorityQueue pq_initPQueue(int size);

/**
 * @brief Desaloca a fila e configura seu ponteiro para nulo.
 * 
 * @param pq Ponteiro para a fila em questão.
 */
void pq_destroyPQueue(PriorityQueue *pq);

/**
 * @brief Enfilera um elemento na fila dada sua prioridade.
 *
 * @param pq Fila em questão;
 * @param w Valor a ser inserido na fila.
 * 
 * @retval 1 - Valor inserido com sucesso;
 * @retval 0 - Falha na alocação de memória.
 */
int pq_enqueue(PriorityQueue pq, WeightedEdge w);

/**
 * @brief Desenfilera um elemento do início da fila (menor elemento presente na fila).
 * 
 * @warning Garanta que a fila não está vazia!
 * 
 * @param pq Fila em questão.
 * 
 * @retval int - Elemento que foi removido da fila.
 */
WeightedEdge pq_dequeue(PriorityQueue pq);

/**
 * @brief Retorna o primeiro elemento da fila (menor elemento presente na fila).
 * 
 * @warning Certifique-se de que a fila não está vazia.
 * 
 * @param pq Fila em questão.
 * 
 * @retval int - Primeiro elemento da fila. 
 */
WeightedEdge pq_front(PriorityQueue pq);

/**
 * @brief Retorna o tamanho da fila de prioridade.
 * 
 * @param pq Fila em questão.
 * 
 * @retval int - Tamanho da fila.
 */
int pq_getSize(PriorityQueue pq);

/**
 * @brief Verifica se a fila está vazia.
 * 
 * @param pq Fila em questão.
 * 
 * @retval 1 - A fila está vazia;
 * @retval 0 - A fila NÃO está vazia.
 */
int pq_isEmpty(PriorityQueue pq);

#endif
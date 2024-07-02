/**
 * @file Queue.h
 * @author João Henrique
 * @brief Biblioteca de fila dinâmica.
 * 
 * @version 0.1
 * @date 2024-07-02
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue *Queue;

Queue q_initQueue();
void q_destroyQueue(Queue *q);
int q_enqueue(Queue q, int w);
int q_dequeue(Queue q);
int q_front(Queue q);
int q_isEmpty(Queue q);

#endif
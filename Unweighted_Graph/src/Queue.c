/**
 * @file Queue.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Queue.h"
#include <stdlib.h>

typedef struct node 
{
    int w;
    struct node* next;
} *Node;

struct queue
{
    Node front;
    Node end;
};

static Node newNode(int w, Node next)
{
    Node newNode = (Node) malloc(sizeof(struct node));
    if(newNode == NULL)
        exit(EXIT_FAILURE);
    newNode->w = w;
    newNode->next = next;
    return newNode;
}

Queue q_initQueue()
{
    Queue q = (Queue) malloc(sizeof(struct queue));
    if(q == NULL)
        exit(EXIT_FAILURE);
    q->front = NULL;
    q->end = NULL;
    return q;
}

void q_destroyQueue(Queue *q)
{
    while(!q_isEmpty(*q))
        q_dequeue(*q);
    free(*q);
    *q = NULL;
}

int q_enqueue(Queue q, int w)
{
    Node new = newNode(w, NULL);
    if(new == NULL)
        return 0;
    if(q_isEmpty(q))
        q->front = new;
    else 
        q->end->next = new;
    q->end = new;
    return 1;
}

int q_dequeue(Queue q)
{
    Node temp = q->front;
    int v = temp->w;
    q->front = q->front->next;

    if(q_isEmpty(q))
        q->end = NULL;
    
    free(temp);
    return v;
}

int q_front(Queue q)
{
    return q->front->w;
}

int q_isEmpty(Queue q)
{
    return q->front == NULL;
}


/**
 * @file PriorityQueue.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "../include/PriorityQueue.h"
#include "../include/Util.h"

struct priority_queue
{
    int* heapTree;
    int size;
    int capacity;
};

static int parent(int i)
{
    return (i - 1) / 2;
}

static int left(int i)
{
    return 2 * i + 1;
}

static int right(int i)
{
    return left(i) + 1;
}

static void heapify_up(PriorityQueue pq, int i)
{
    while(i > 0 && pq->heapTree[parent(i)] > pq->heapTree[i])
    {
        swap(&pq->heapTree[parent(i)], &pq->heapTree[i]);
        i = parent(i);
    }
}

static void heapify_down(PriorityQueue pq, int i)
{
    while(left(i) < pq->size)
    {
        if(right(i) < pq->size)
        {
            if(pq->heapTree[left(i)] < pq->heapTree[right(i)])
                i = left(i);
            else
                i = right(i);
        }
        else
            i = left(i);
        if(pq->heapTree[i] < pq->heapTree[parent(i)])
            swap(&pq->heapTree[i], &pq->heapTree[parent(i)]);
    }
}

PriorityQueue pq_initPQueue(int capacity)
{
    PriorityQueue pq = (PriorityQueue) malloc(sizeof(struct priority_queue));
    if(pq == NULL)
        return NULL;
    pq->heapTree = (int*) malloc(sizeof(int) * capacity);
    if(pq->heapTree == NULL)
    {
        free(pq);
        return NULL;
    }
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void pq_destroyPQueue(PriorityQueue *pq)
{
    free((*pq)->heapTree);
    free(*pq);
    *pq = NULL;
}

int pq_enqueue(PriorityQueue pq, int w)
{
    if(pq->size == pq->capacity)
        return 0;
    int i = pq->size;
    pq->heapTree[i] = w;
    heapify_up(pq, i);
    pq->size++;
    return 1;
}

int pq_dequeue(PriorityQueue pq)
{
    int min = pq->heapTree[0];
    pq->heapTree[0] = pq->heapTree[pq->size-1];
    pq->size--;
    heapify_down(pq, 0);
    return min;
}

int pq_front(PriorityQueue pq)
{
    return pq->heapTree[0];
}

int pq_isEmpty(PriorityQueue pq)
{
    return pq->size == 0;
}
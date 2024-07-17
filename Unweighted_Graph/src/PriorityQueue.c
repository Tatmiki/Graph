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

struct priority_queue
{
    WeightedEdge* heapTree;
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
    while(i > 0 && pq->heapTree[parent(i)].weight > pq->heapTree[i].weight)
    {
        swapEdge(&pq->heapTree[parent(i)], &pq->heapTree[i]);
        i = parent(i);
    }
}

static void heapify_down(PriorityQueue pq, int i)
{
    while(left(i) < pq->size)
    {
        if(right(i) < pq->size)
        {
            if(pq->heapTree[left(i)].weight < pq->heapTree[right(i)].weight)
                i = left(i);
            else
                i = right(i);
        }
        else
            i = left(i);
        if(pq->heapTree[i].weight < pq->heapTree[parent(i)].weight)
            swapEdge(&pq->heapTree[i], &pq->heapTree[parent(i)]);
    }
}

PriorityQueue pq_initPQueue(int capacity)
{
    PriorityQueue pq = (PriorityQueue) malloc(sizeof(struct priority_queue));
    if(pq == NULL)
        return NULL;
    pq->heapTree = (WeightedEdge*) malloc(sizeof(WeightedEdge) * capacity);
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

int pq_enqueue(PriorityQueue pq, WeightedEdge w)
{
    if(pq->size == pq->capacity)
        return 0;
    int i = pq->size;
    pq->heapTree[i] = w;
    heapify_up(pq, i);
    pq->size++;
    return 1;
}

WeightedEdge pq_dequeue(PriorityQueue pq)
{
    WeightedEdge min = pq->heapTree[0];
    pq->heapTree[0] = pq->heapTree[pq->size-1];
    pq->size--;
    heapify_down(pq, 0);
    return min;
}

WeightedEdge pq_front(PriorityQueue pq)
{
    return pq->heapTree[0];
}

int pq_getSize(PriorityQueue pq)
{
    return pq->size;
}

int pq_isEmpty(PriorityQueue pq)
{
    return pq->size == 0;
}
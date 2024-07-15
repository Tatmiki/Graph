#include <stdio.h>
#include "../../include/PriorityQueue.h"

int main()
{
    PriorityQueue pq = pq_initPQueue(10);
    if(pq == NULL)
        return 0;
    pq_enqueue(pq, 20);
    pq_enqueue(pq, 30);
    pq_enqueue(pq, 10);
    pq_enqueue(pq, 40);
    pq_enqueue(pq, 2);
    pq_enqueue(pq, 3);
    pq_enqueue(pq, 8);
    pq_enqueue(pq, 11);
    pq_enqueue(pq, 1);
    
    while(!pq_isEmpty(pq))
        printf("%d\n", pq_dequeue(pq));
        
    pq_destroyPQueue(&pq);
}
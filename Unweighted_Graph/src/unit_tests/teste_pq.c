#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/PriorityQueue.h"

int main()
{
    srand(time(0));
    PriorityQueue pq = pq_initPQueue(10);
    if(pq == NULL)
        return 0;
    WeightedEdge w;
    int i;
    for(i = 0; i < 20; i++)
    {
        w.v = rand()%101;
        w.weight = rand()%101;
        pq_enqueue(pq, w);
    }
    
    WeightedEdge *wp = pq_dequeue(pq);
    while(!pq_isEmpty(pq))
    {
        printf("%3d %.2lf\n", wp->v, wp->weight);
        wp = pq_dequeue(pq);
    }   
    pq_destroyPQueue(&pq);
}
/**
 * @file List_W.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/List_W.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Cria um novo nó encadeado.
 * 
 * @param w Novo elemento;
 * @param next Edereço ao encadeamento do próximo desse elemento.
 * @return ( Node_W ) Alocado e inicializado com os parâmetros passados.
 */
static Node_W newNode(int v, double w, Node_W next)
{
    Node_W newNode = (Node_W) malloc(sizeof(struct node_w));
    if(newNode == NULL)
        exit(EXIT_FAILURE);
    newNode->edge.v = v;
    newNode->edge.weight = w;
    newNode->next = next;
    return newNode;
}

List_W lw_initList()
{
    List_W lw = (List_W) malloc(sizeof(struct list_w));
    if(lw == NULL)
        exit(EXIT_FAILURE);
    lw->head = NULL;
    lw->size = 0;
    return lw;
}

void lw_destroyList(List_W *lw)
{
    Node_W temp;
    while((*lw)->head != NULL)
    {
        temp = (*lw)->head;
        (*lw)->head = (*lw)->head->next;
        free(temp); 
    }
    free(*lw);
    *lw = NULL;
}

int lw_insertBeggining(List_W lw, int v, double w)
{
    lw->head = newNode(v, w, lw->head);
    lw->size++;
    return 1;
}

int lw_remove(List_W lw, int v)
{
    Node_W previous = NULL;
    Node_W current = lw->head;

    while(current != NULL)
    {
        if(current->edge.v == v)
        {
            if(previous != NULL)
                previous->next = current->next;
            else
                lw->head = current->next;
            free(current);
            lw->size--;
            return 1;
        } 
        previous = current;
        current = current->next;
    }
    return 0;
}

WeightedEdge* lw_find(List_W lw, int v)
{
    Node_W head = lw->head;
    while(head != NULL)
    {
        if(head->edge.v == v)
            return &head->edge;
        head = head->next;
    }
    return NULL;
}

void lw_show(List_W lw)
{
    Node_W head;
    for(head = lw->head; head != NULL; head = head->next)
        printf(" -> %7d | %6.2lf", head->edge.v+1, head->edge.weight);
    putchar('\n');
}

int lw_getSize(List_W lw)
{
    return lw->size;
}

int lw_isEmpty(List_W lw)
{
    return lw->head == NULL;
}
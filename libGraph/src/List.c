/**
 * @file List.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/List.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Cria um novo nó encadeado.
 * 
 * @param w Novo elemento;
 * @param next Edereço ao encadeamento do próximo desse elemento.
 * @return ( Node ) Alocado e inicializado com os parâmetros passados.
 */
static Node newNode(int w, Node next)
{
    Node newNode = (Node) malloc(sizeof(struct node));
    if(newNode == NULL)
        exit(EXIT_FAILURE);
    newNode->w = w;
    newNode->next = next;
    return newNode;
}

List l_initList()
{
    List l = (List) malloc(sizeof(struct list));
    if(l == NULL)
        exit(EXIT_FAILURE);
    l->head = NULL;
    l->size = 0;
    return l;
}

void l_destroyList(List *l)
{
    Node temp;
    while((*l)->head != NULL)
    {
        temp = (*l)->head;
        (*l)->head = (*l)->head->next;
        free(temp); 
    }
    free(*l);
    *l = NULL;
}

int l_insertBeggining(List l, int v)
{
    l->head = newNode(v, l->head);
    l->size++;
    return 1;
}

int l_remove(List l, int v)
{
    Node previous = NULL;
    Node current = l->head;

    while(current != NULL)
    {
        if(current->w == v)
        {
            if(previous != NULL)
                previous->next = current->next;
            else
                l->head = current->next;
            free(current);
            l->size--;
            return 1;
        } 
        previous = current;
        current = current->next;
    }
    return 0;
}

int l_find(List l, int v)
{
    Node head = l->head;
    while(head != NULL){
        if(head->w == v)
            return 1;
        head = head->next;
    }
    return 0;
}

void l_show(List l)
{
    Node head = l->head;
    while(head != NULL)
    {
        printf(" -> %d", head->w+1);
        head = head->next;
    }
    putchar('\n');
}

int l_getSize(List l)
{
    return l->size;
}

int l_isEmpty(List l)
{
    return l->head == NULL;
}
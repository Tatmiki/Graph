/**
 * @file List.h
 * @author João Henriquei
 * @brief Bibiblioteca de lista escadeada dinâmica.
 * 
 * @version 0.1
 * @date 2024-07-02
 */

#ifndef LIST_H
#define LIST_H

typedef struct node 
{
    int w;
    struct node* next;
} *Node;

typedef struct list
{
    Node head;
    int size;
} *List;

List l_initList();
void l_destroyList(List *l);
int l_insertBeggining(List l, int v);
int l_remove(List l, int v);
int l_find(List l, int w);
void l_show(List l);
int l_getSize(List l);
int l_isEmpty(List l);

#endif
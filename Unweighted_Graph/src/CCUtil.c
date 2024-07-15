/**
 * @file ConnectedComponents.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/Graph.h"
#include "../include/CCUtil.h"
#include "../include/List.h"

l_ConnectedComponents allocLCC()
{
    l_ConnectedComponents lc = (l_ConnectedComponents) malloc(sizeof(struct l_connected_components));
    if(lc == NULL)
        return NULL;
    lc->list = (ConnectedComponent*) malloc(sizeof(ConnectedComponent) * 10);
    if(lc->list == NULL)
    {
        free(lc);
        return NULL;
    }
    lc->size = 10;
    return lc;
}

int reallocLCC(l_ConnectedComponents lc, int newSize)
{
    lc->list = (ConnectedComponent*) realloc(lc->list, sizeof(ConnectedComponent) * newSize);
    if(lc->list == NULL)
        return 0;
    lc->size = newSize;
    return 1;
}

void swapCC(ConnectedComponent *a, ConnectedComponent *b)
{
    ConnectedComponent temp = *a;
    (*a).vertexes = (*b).vertexes;
    (*b).vertexes = temp.vertexes;
}

void quicksortLCC(ConnectedComponent vet[], const int start, const int end)
{
    int left = start, right = end, pivot = l_getSize(vet[(start+end)/2].vertexes);
    do
    {
        
        while(l_getSize(vet[left].vertexes) > pivot) ++left;
        while(l_getSize(vet[right].vertexes) < pivot) --right;
        if(left <= right)
        {
            swapCC(&vet[left], &vet[right]);
            left++; right--;
        }
    }while(left <= right);
    
    if(right > start) quicksortLCC(vet, start, right); // ramo esquerdo
    if(left < end) quicksortLCC(vet, left, end); // ramo direito
}

int cc_getNumOfCComponents(l_ConnectedComponents lcc)
{
    return lcc->size;
}

int cc_getSizeCComponent(l_ConnectedComponents l, int id)
{
    return l_getSize(l->list[id-1].vertexes);
}

void cc_listCComponents(l_ConnectedComponents lcc)
{
    printf("Há %d componente(s) conexo(s).\nListagem:\n", lcc->size);
    int i;
    for(i = 0; i < lcc->size; i++)
    {
        printf("\n~> Componentes [%d]:\n", lcc->list[i].id);
        printf("      - Quantidade de vertices: %d\n", cc_getSizeCComponent(lcc, i+1));
    }
}

void cc_showCComponent(l_ConnectedComponents lcc, int id)
{
    printf("\n~ Componente [%d]:\n", lcc->list[id-1].id);
    printf("      - Qnt. de vértices: %d\n", cc_getSizeCComponent(lcc, id));
    printf("      - Vértices pertencentes:\n         ");
    l_show(lcc->list[id-1].vertexes);
}

void cc_destroyCComponents(l_ConnectedComponents *lcc)
{
    int i;
    for(i = 0; i < (*lcc)->size; i++)
        l_destroyList(&(*lcc)->list[i].vertexes);
    free((*lcc)->list);
    free(*lcc);
    *lcc = NULL;
}
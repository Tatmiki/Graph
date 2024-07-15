/**
 * @file GraphUtil.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/Util.h"

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int vet[], const int start, const int end)
{
    int left = start, right = end, pivot = vet[(start+end)/2];
    do
    {
        while(vet[left] < pivot) ++left;
        while(vet[right] > pivot) --right;
        if(left <= right)
        {
            swap(&vet[left], &vet[right]);
            left++; right--;
        }
    }while(left <= right);
    if(right > start) quicksort(vet, start, right); // ramo esquerdo
    if(left < end) quicksort(vet, left, end); // ramo direito
}
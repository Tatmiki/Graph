/**
 * @file GraphUtil.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GRAPH_UTIL_H
#define GRAPH_UTIL_H

#include "Graph.h"

/**
 * @brief Estrutura de apoio para os algoritmos de BFS e DFS.
 */
typedef struct
{
    char color;     /*> Cor de status do vértice. ('W'hite não visitado, 'G'ray de visto e 'B'lack de visitado) */
    vertex father;  /*> Vértice pai do veŕtice em questão.                                                      */
    int depth;      /*> Porfundidade de um vértice em relação ao início da BFS ou DFS realizada.                */
} Vertex_info;

/**
 * @brief Troca o valor de duas variáveis inteiras
 * 
 * @param a Endereço da variável a.
 * @param b Endereço da variável b.
 */
void swap(int* a, int* b);

/**
 * @brief Realiza a ordenação rápida de um vetor em ordem crescente.
 * 
 * @param vet Vetor em questão;
 * @param start Início relativo ao índice do vetor (geralmente 0);
 * @param end  Final realtivo ao índice do vetor (geralmente tamanho-1).
 */
void quicksort(int vet[], const int start, const int end);

#endif
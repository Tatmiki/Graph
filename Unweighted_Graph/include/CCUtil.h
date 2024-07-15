/**
 * @file ConnectedComponent.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CONNECTED_COMPONENT_UTIL
#define CONNECTED_COMPONENT_UTIL

#include "../include/Graph.h"
#include "../include/List.h"

/**
 * @brief Estrutura de um componente conexo.
 */
typedef struct
{
    List vertexes;  /*> Lista de vértices pertencentes ao componente.   */
    int id;         /*> Identificador do componente.                    */
} ConnectedComponent;

/**
 * @brief Estrutura da lista de componentes conexos.
 */
struct l_connected_components
{
    ConnectedComponent *list;   /*> Lista de componentes conexos.   */
    int size;                   /*> Tamanho da lista.               */
};

/**
 * @brief Aloca uma lista de componentes conexos.
 * 
 * @return Uma lista alocada de componentes conectados com tamanho inicial de alocação 10.
 */
l_ConnectedComponents allocLCC();

/**
 * @brief Reajusta a área alocada de uma lista de componentes conexos.
 * 
 * @param lc Lista em questão;
 * @param newSize Novo tamanho da lista.
 */
int reallocLCC(l_ConnectedComponents lc, int newSize);

/**
 * @brief Troca a lista de dois componentes conexos.
 * 
 * @param a Endereço do componente a;
 * @param b Endereço do componente b.
 */
void swapCC(ConnectedComponent *a, ConnectedComponent *b);

/**
 * @brief Realiza o quicksort descrescente em uma lista de componentes conexos.
 * 
 * @param vet Lista de componentes conexos;
 * @param start Início da lista (geralmente 0);
 * @param end Última posição da lista (geralmente tamanho-1).
 */
void quicksortLCC(ConnectedComponent vet[], const int start, const int end);

#endif
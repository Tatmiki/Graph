/**
 * @file Queue.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 */

#include "../include/Stack.h"
#include <stdlib.h>

/**
 * @brief Estrutura de nó para a pilha encadeada dinâmica.
 */
typedef struct node 
{
    int w;              /*> Elemento do tipo inteiro.   */
    struct node* next;  /*> Nó para o próximo elemento. */
} *Node;

/**
 * @brief Estrutura da pilha dinâmica encadeada.
 */
struct stack
{
    Node top;
};

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

Stack s_initStack()
{
    Stack s = (Stack) malloc(sizeof(struct stack));
    if(s == NULL)
        exit(EXIT_FAILURE);
    s->top = NULL;
    return s;
}

void s_destroyStack(Stack *s)
{
    while(!s_isEmpty(*s))
        s_pop(*s);
    free(*s);
    *s = NULL;
}

void s_push(Stack s, int w)
{
    s->top = newNode(w, s->top);
}

int s_pop(Stack s)
{
    int w = s->top->w;
    Node temp = s->top;
    s->top = s->top->next;
    free(temp);
    return w;
}

int s_top(Stack s)
{
    return s->top->w;
}

int s_isEmpty(Stack s)
{
    return s->top == NULL;
}
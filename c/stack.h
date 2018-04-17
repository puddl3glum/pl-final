
# pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "pair.h"

struct Node;

typedef struct Node {
    Pair range;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} List;

List new_list() {
    List l = {NULL};
    return l;
}

bool empty(List * l) {
    return l->top == NULL;
}

void push (List *stack, Pair range) {
    Node * new_node = (Node * ) malloc(sizeof(Node));

    new_node->range = range;
    // get ref to top of stack
    new_node->next = stack->top;
    stack->top = new_node;
}

Pair pop (List *stack) {
    //Node * new_node = (Node * ) malloc(sizeof(Node));

    // get ref to top of stack
    Node * old_top = stack->top;

    Pair old = old_top->range;
    stack->top = old_top->next;

    free(old_top);

    return old;
}

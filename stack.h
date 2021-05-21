#ifndef _STACK_H_
#define _STACK_H_
#include "list.h"
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

#define STACK_CAPACITY LIST_MAX_NUM_NODES
typedef Node type;

typedef struct Stack_s Stack;
struct Stack_s {
    int top;
    type elems[STACK_CAPACITY];
    type* ptrs[STACK_CAPACITY];
};
// I don't like that I'm doing this. It's spaghetti code. But here I am doing it anyway.
Stack the_node_stack;
Stack* free_nodes = NULL; // This means the_node_stack hasn't been initialized.

bool Stack_init(Stack*);
bool Stack_push(Stack*, type*);
type* Stack_pop(Stack*);

#endif
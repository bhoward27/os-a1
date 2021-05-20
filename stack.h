#ifndef _STACK_H_
#define _STACK_H_
#include "list.h"
#include <stddef.h>

#define STACK_CAPACITY LIST_MAX_NUM_NODES
typedef Node type;

typedef struct Stack_s Stack;
struct Stack_s {
    int top;
    type elems[STACK_CAPACITY];
    type* ptrs[STACK_CAPACITY];
};
Stack stack;

Stack* Stack_init();
bool Stack_push(type*);
type* Stack_pop();

#endif
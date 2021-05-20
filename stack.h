#ifndef _STACK_H_
#define _STACK_H_
#include "list.h"

#define STACK_CAPACITY LIST_MAX_NUM_NODES
typedef Node type;

typedef struct Stack_s Stack;
struct Stack_s {
    int size;
    int top;
    type arr [STACK_CAPACITY];
};

Stack stack;

//  Declare the function prototypes
Stack* Stack_init();

#endif
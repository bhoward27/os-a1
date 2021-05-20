#include "stack.h"

Stack* Stack_init() {
    stack.top = -1;
    while (Stack_push(&stack.elems[stack.top + 1]));
    return &stack;
}

// Stack should NOT be a singleton. BAD IDEA. So must change this. Easy to fix.
bool Stack_push(type* elem_ptr) {
    if (stack.top >= STACK_CAPACITY - 1) return false;
    stack.ptrs[++stack.top] = elem_ptr;
    return true;
}

type* Stack_pop() {
    if (stack.top <= -1) return NULL;
    return stack.ptrs[stack.top--];
}
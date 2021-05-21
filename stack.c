#include "stack.h"

//  Returns true iff. init was successful.
bool Stack_init(Stack* new_stack) {
    assert(new_stack != NULL);
    //  We proceed under the assumption that we were handed an empty stack.
    new_stack->top = -1;
    while (Stack_push(new_stack, &(new_stack->elems[new_stack->top + 1])));
    return (new_stack->top == STACK_CAPACITY - 1);
}

bool Stack_push(Stack* stack, type* elem_ptr) {
    assert(stack != NULL);
    if (stack->top >= STACK_CAPACITY - 1) return false;
    stack->ptrs[++(stack->top)] = elem_ptr;
    return true;
}

type* Stack_pop(Stack* stack) {
    assert(stack != NULL);
    if (stack->top <= -1) return NULL;
    return stack->ptrs[(stack->top)--];
}
#include <stdio.h>
#include "stack.h"

int main() {
    Stack stack;
    if (!Stack_init(&stack)) {
        printf("Error: Stack_init failed.\n");
        return 1;
    }
    printf("Number of free nodes available = %d\n", stack.top + 1);
    type* x = Stack_pop(&stack);
    char ch = 'a';
    x->item = (void*) &ch;
    x->next = (type*) 0x5; // No rhyme or reason, just testing.
    x->prev = (type*) 0x17;
    type* y = Stack_pop(&stack);
    type* z = Stack_pop(&stack);
    type* b;
    if (!Stack_push(&stack, x)) {
        printf("Error: Stack_push failed.\n");
        return 1;
    }
    b = Stack_pop(&stack);
    printf("(b == x)?%d\n", b == x);
    printf("b->next = %p\n", (void*) b->next);
    printf("b->prev = %p\n", (void*) b->prev);
    printf("(b->item)* = %c\n", *((char *) (b->item)));

    return 0;
}

#include <stdio.h>
#include "stack.h"

int main() {
    Stack* free_nodes = Stack_init();
    type* x = Stack_pop();
    char ch = 'a';
    x->item = (void*) &ch;
    x->next = (type*) 0x5; // No rhyme or reason, just testing.
    x->prev = (type*) 0x17;
    type* y = Stack_pop();
    type* z = Stack_pop();
    type* b;
    if (!Stack_push(x)) {
        printf("Error: Stack_push failed.\n");
        return 1;
    }
    b = Stack_pop();
    printf("(b == x)?%d\n", b == x);
    printf("b->next = %p\n", (void*) b->next);
    printf("b->prev = %p\n", (void*) b->prev);
    printf("(b->item)* = %c\n", *((char *) (b->item)));

    return 0;
}

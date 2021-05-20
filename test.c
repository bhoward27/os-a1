#include <stdio.h>
#include "stack.h"

int main() {
    printf("5 + 3 = %d\n\n", 5 + 3);
    Stack* free_nodes = Stack_init();
    printf("7 * 7 = %d\n", 7 * 7);

    return 0;
}

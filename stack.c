#include "stack.h"

Stack* Stack_init() {
    stack.size = 0;
    stack.top = -1;
    return &stack;
}

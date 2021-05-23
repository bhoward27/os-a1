#include <stdio.h>
#include "list.h"
#include "node_manager.h"

int main() {
    List* l = List_create();
    char ch = 'a';
    List_add(l, &ch);
    char q = '3';
    List_add(l, &q);
    List_add(l, &ch);
    List_add(l, &ch);
    printf("List_count(l) = %d\n", List_count(l));
    
    return 0;
}

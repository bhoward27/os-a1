#include <stdio.h>
#include "list.h"
#include "node_manager.h"

void test_count(List*);
void test_add(List*, void*);
void test_remove(List*);
void test_prev(List*);

int main() {
    List* l = List_create();
    char ch = 'a';
    test_add(l, &ch);
    char q = '3';
    char b = 'b';
    test_add(l, &ch);
    test_add(l, &q);
    test_add(l, &b);

    test_remove(l);
    test_prev(l);
    test_remove(l);
    test_prev(l);
    test_remove(l);
    test_prev(l);
    test_remove(l);
    test_prev(l);
    test_remove(l);
    
    return 0;
}

void test_count(List* l) {
    printf("List_count(l) = %d\n", List_count(l));
}

void test_add(List* l, void* item) {
    printf("List_add(l, item) = %d\n", List_add(l, item));
    test_count(l);
}

void test_remove(List* l) {
    char* item = (char*) List_remove(l);
    if (item == NULL) {
        printf("List_remove(l, item) = NULL\n");
    }
    else {
        printf("List_remove(l, item) = %c\n", *item);
    }
    test_count(l);
}

void test_prev(List* l) {
    char* item = (char*) List_prev(l);
    if (item == NULL) {
        printf("List_prev(l) = NULL\n");
    }
    else {
        printf("List_prev(l) = %c\n", *item);
    }
}
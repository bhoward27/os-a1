#include <stdio.h>
#include "list.h"
#include "node_manager.h"

void test_count(List*);
void test_add(List*, void*);
void test_remove(List*);
void test_prev(List*);
void test_tail(List*);

int main() {
    List* l = List_create();
    char one = '1';
    test_add(l, &one);
    char two = '2';
    char three = '3';
    char four = '4';
    test_add(l, &two);
    test_add(l, &three);
    test_add(l, &four);

    test_remove(l);
    test_tail(l);

    test_prev(l);
    test_remove(l);
    test_tail(l);

    test_prev(l);
    test_remove(l);
    test_tail(l);

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

void test_tail(List* l) {
    printf("l->tail = %p\n", (void*) l->tail);
    // printf("LIST_OOB_END = %p\n", (void*) (Node*) LIST_OOB_END);
    printf("l->tail->item = %c\n", *((char*) l->tail->item));
}
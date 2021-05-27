#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node_manager.h"
#include <stdbool.h>
#include <time.h>
#define NUM_ITEMS 126

int test_count(List*, char);
void test_add(List*, void*, char);
void test_remove(List*, char);
void test_prev(List*);
void test_tail(List*);
void test_curr(List*);
void print_list(List*, char);
void print_free_list(Node_manager*);
void print_all_nodes(Node_manager*);
void old_test();
void rand_alloc(const int, List**, char*, const int);
void testerino(const int, List**, char*, const int);

char items[NUM_ITEMS];

int main() {
    // Create the array of items which will be referenced by nodes.
    // chars with ASCII code 33 to 126 are readable.
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i] = (char) i + 33;
    }

    // Declare 12 lists.
    List* a;
    List* b;
    List* c;
    List* d;
    List* e;
    List* f;
    List* g;
    List* h;
    List* i;
    List* j;
    List* k;
    List* l;

    // Create three empty lists.
    a = List_create();
    b = List_create();
    c = List_create();

    const int NUM_LISTS1 = 3;
    List* lists1[] = {a, b, c};
    char list_names1[] = {'a', 'b', 'c'};

    // Add 90 elements total, allocating randomly.
    const int NUM_ELEMS1 = 90;
    
    srand(time(0));
    rand_alloc(NUM_ELEMS1, lists1, list_names1, NUM_LISTS1);
    testerino(NUM_LISTS1, lists1, list_names1, NUM_ELEMS1);

    // Try to add more than 100 nodes collectively to all the lists.
    d = List_create();
    e = List_create();

    const int NUM_LISTS2 = 2;
    List* lists2[] = {d, e};
    char list_names2[] = {'d', 'e'};

    // Add 11 elements total, allocating randomly.
    const int NUM_ELEMS2 = 11;
    rand_alloc(NUM_ELEMS2, lists2, list_names2, NUM_LISTS2);
    testerino(NUM_LISTS2, lists2, list_names2, NUM_ELEMS2);

    return 0;
}

void rand_alloc(const int NUM_ELEMS, List** lists, char* list_names, const int NUM_LISTS) {
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        test_add(lists[choice], (void*) (items + i), list_names[choice]);
    }
}

void testerino(const int NUM_LISTS, List** lists, char* list_names, const int NUM_ELEMS) {
    int total = 0;
    for (int i = 0; i < NUM_LISTS; ++i) {
        print_list(lists[i], list_names[i]);
        total += test_count(lists[i], list_names[i]);
        printf("\n");
    }
    printf("Total number of elements (actual) = %d\n", total);
    printf("Total number of elements (requested) = %d\n", NUM_ELEMS);
    printf("\n");
}

int test_count(List* list, char list_name) {
    int count = List_count(list);
    printf("List_count(%c) = %d\n", list_name, count);
    return count;
}

void test_add(List* l, void* item, char list_name) {
    char* x = (char*) item;
    if (x != NULL) {
        printf("List_add(%c, *item = %c) = %d\n", list_name, *x, List_add(l, item));
    }
    else {
        printf("List_add(%c, item = NULL) = %d\n", list_name, List_add(l, item));
    }
}

void test_remove(List* list, char list_name) {
    char* item = (char*) List_remove(list);
    if (item == NULL) {
        printf("List_remove(%c, item) = NULL\n", list_name);
    }
    else {
        printf("List_remove(%c, item) = %c\n", list_name, *item);
    }
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
    if (l->tail == NULL) {
         printf("Bad tail. Tail = NULL\n");
    }
    else {
        printf("l->tail = %p\n", (void*) l->tail);
        printf("l->tail->item = %c\n", *((char*) l->tail->item));
    }
}

void test_curr(List* l) {
    if (l->current == NULL) {
        printf("l->current = NULL\nl->current_state = %d\n", l->current_state);
    }
    else {
        printf("l->current = %p\nl->current_state = %d\n", (void*) l->current, l->current_state);
        void* item = List_curr(l);
        if (item == NULL) {
            printf("l->current->item = INACCESSIBLE or NULL\n");
        }
        else {
            printf("l->current->item = %c\n", *((char*) List_curr(l)));
        }
    }
}

void print_list(List *l, char name) {
    assert(l != NULL);
    if (l->size == 0) {
        printf("**********  %c  **********\n", name);
        printf("Empty.\n\n");
        return;
    }
    Node *head = l->head;
    if (head == NULL) {
        printf("Bad head. Head = NULL\n");
        return;
    }
    Node *tail = l->tail;
    if (tail == NULL) {
        printf("Bad tail. Tail = NULL\n");
        return;
    }

    printf("**********  %c  **********\n", name);
    Node *cursor = head;
    while (cursor != tail) {
        char* item = (char*) cursor->item;
        if (item != NULL)
            printf("%c   ", *item);
        else
            printf("INACCESSIBLE   ");
        cursor = cursor->next;
    }
    char* item = (char*) cursor->item;
    if (item != NULL)
        printf("%c\n", *item);
    else
        printf("INACCESSIBLE\n");
}

void print_free_list(Node_manager *nm) {
    
}

void print_all_nodes(Node_manager *nm) {

}
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node_manager.h"
#include <stdbool.h>
#include <time.h>
#define NUM_ITEMS 126

int test_count(List*, char);
void test_add(List*, void*, char);
void* test_remove(List*, char);
void test_prev(List*, char);
void test_tail(List*);
void test_curr(List*);
void print_list(List*, char);
void print_free_list(Node_manager*);
void print_all_nodes(Node_manager*);
void old_test();
void rand_alloc(const int, List**, char*, const int);
void rand_dealloc(const int, List**, char*, const int);
void testerino(const int, List**, char*, const int);
void test_create(List**, char);

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

    // Try to create 7 more lists 
    // In that case we'll have 12 lists in total--2 more than the maximum allowed.
    const int NUM_LISTS3 = 7;
    List** lists3[] = {&f, &g, &h, &i, &j, &k, &l};
    char list_names3[] = {'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    for (int i = 0; i < NUM_LISTS3; i++) {
        test_create(lists3[i], list_names3[i]);
    }
    printf("\n");

    // Remove 80 nodes randomly from lists that have size != 0.
    const int NUM_LISTS4 = 5;
    const int NUM_ELEMS4 = 80;
    List* lists4[] = {a, b, c, d, e};
    char list_names4[] = {'a', 'b', 'c', 'd', 'e'};
    rand_dealloc(NUM_ELEMS4, lists4, list_names4, NUM_LISTS4);
    testerino(NUM_LISTS4, lists4, list_names4, 100 - NUM_ELEMS4);

    const int NUM_LISTS5 = 10;
    List* lists5[] = {a, b, c, d, e, f, g, h, i, j};
    // ***NEED TO ADD ONE LAST TEST***
    // Test with removes and adds done randomly on random lists, y'know, intermixed with each other
    // Run it like, a thousand times to see what happens.
    // If you're good there, then the current functionality is definitely working as intended.


    return 0;
}

void test_create(List** list, char list_name) {
    *list = List_create();
    if (*list == NULL) {
        printf("%c = List_create() == NULL\n", list_name);
    }
    else {
        printf("%c = List_create() == %p\n", list_name, (void*) *list);
    }
}

void rand_alloc(const int NUM_ELEMS, List** lists, char* list_names, const int NUM_LISTS) {
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        test_add(lists[choice], (void*) (items + i), list_names[choice]);
    }
}

void rand_dealloc(const int NUM_ELEMS, List** lists, char* list_names, const int NUM_LISTS) {
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        List* list = lists[choice];
        char list_name = list_names[choice];
        int size = List_count(list);

        // If list is empty, of course we can't remove anything, so try again for a different list.
        if (size == 0) { 
            i--;
            continue;
        }

        void* item = test_remove(list, list_name);

        // If it failed, try doing List_prev and then removing.
        if (item == NULL) {
            test_prev(list, list_name);
            item = test_remove(list, list_name);
        }
    }
}

void testerino(const int NUM_LISTS, List** lists, char* list_names, const int NUM_REQUESTED_NODES) {
    int total = 0;
    for (int i = 0; i < NUM_LISTS; ++i) {
        print_list(lists[i], list_names[i]);
        total += test_count(lists[i], list_names[i]);
        printf("\n");
    }
    printf("Total number of elements (actual) = %d\n", total);
    printf("Total number of elements (requested) = %d\n", NUM_REQUESTED_NODES);
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

void* test_remove(List* list, char list_name) {
    char* item = (char*) List_remove(list);
    if (item == NULL) {
        printf("List_remove(%c, item) = NULL\n", list_name);
        return NULL;
    }
    else {
        printf("List_remove(%c, item) = %c\n", list_name, *item);
        return (void*) item;
    }
}

void test_prev(List* l, char list_name) {
    char* item = (char*) List_prev(l);
    if (item == NULL) {
        printf("List_prev(%c) = NULL\n", list_name);
    }
    else {
        printf("List_prev(%c) = %c\n", list_name, *item);
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
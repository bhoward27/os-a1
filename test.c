#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node_manager.h"
#include <stdbool.h>
#include <time.h>

int test_count(List*);
void test_add(List*, void*);
void test_remove(List*);
void test_prev(List*);
void test_tail(List*);
void test_curr(List*);
void print_list(List*, char);
void print_free_list(Node_manager*);
void print_all_nodes(Node_manager*);
void old_test();

const int NUM_ITEMS = 126; 

int main() {
    // Create the array of items which will be referenced by nodes.
    // chars with ASCII code 33 to 126 are readable.
    char items[NUM_ITEMS];
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

    const int NUM_LISTS = 3;
    List* lists[] = {a, b, c};
    char list_names[] = {'a', 'b', 'c'};

    // Add 90 elements total, allocating randomly.
    const int NUM_ELEMS = 90;
    
    srand(time(0));
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        List_add(lists[choice], (void*) (items + i));
    }

    int total = 0;
    for (int i = 0; i < NUM_LISTS; ++i) {
        print_list(lists[i], list_names[i]);
        total += test_count(lists[i]);
        printf("\n");
    }
    printf("Total number of elements (actual) = %d\n", total);
    printf("Total number of elements (expected) = %d\n", NUM_ELEMS);
    printf("\n");


    return 0;
}

// void old_test() {
//     printf("Possible values for current_state:\n"
//         "LIST_OOB_START = %d\n"
//         "LIST_OOB_END = %d\n"
//         "LIST_OOB_OK = %d\n"
//         "LIST_OOB_BAD = %d\n\n", 
//         LIST_OOB_START, LIST_OOB_END, LIST_OOB_OK, LIST_OOB_BAD);

//     List* l = List_create();
//     char one = '1';
//     char two = '2';
//     char three = '3';
//     char four = '4';
//     test_add(l, &one);
//     test_add(l, &two);
//     test_add(l, &three);
//     test_add(l, &four);
//     print_list(l);
//     test_curr(l);

//     test_remove(l);
//     print_list(l);
//     test_tail(l);
//     test_curr(l);

//     test_prev(l);
//     test_curr(l);
//     test_remove(l);
//     print_list(l);
//     test_tail(l);
//     test_curr(l);

//     test_prev(l);
//     test_curr(l);
//     test_remove(l);
//     print_list(l);
//     test_tail(l);
//     test_curr(l);

//     test_prev(l);
//     test_curr(l);
//     test_remove(l);
//     print_list(l);
//     test_tail(l);
//     test_curr(l);
// }

int test_count(List* l) {
    int count = List_count(l);
    printf("List_count(l) = %d\n", count);
    return count;
}

void test_add(List* l, void* item) {
    char* x = (char*) item;
    if (x != NULL) {
        printf("List_add(l, *item = %c) = %d\n", *x, List_add(l, item));
    }
    else {
        printf("List_add(l, item = NULL) = %d\n", List_add(l, item));
    }
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
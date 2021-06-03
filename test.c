#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <stdbool.h>
#include <time.h>
#define NUM_ITEMS 126

int test_count(List*, char);
void test_add(List*, void*, char);
void* test_remove(List*, char);
void* test_prev(List*, char);
void test_tail(List*);
void test_curr(List*, char);
void print_list(List*, char);
void old_test();
void rand_alloc(const int, List**, char*, const int, void (*) (List*, void*, char));
void rand_alloc_p(const int, List***, char*, const int, void (*) (List*, void*, char));
void rand_dealloc(const int, List**, char*, const int);
void rand_dealloc_p(const int, List***, char*, const int);
void testerino(const int, List**, char*, const int);
void testerino_p(const int, List***, char*, const int);
void test_create(List**, char);
void test_createrino(const int, List***, char*);

// New functions.
void test_first(List*, char); // Works.
void test_last(List*, char); // Works.
void test_insert(List* l, void* item, char list_name);
void test_add_thing(List*, void*, char, int (*) (List*, void*), char*);
void* test_trim(List*, char);
void test_prepend(List*, void*, char);
void test_search(List*, void*, char);
bool cmp_ch(void*, void*);
void* test_remove_thing(List*, char, void* (*) (List*), char*);
void rand_add(const int, List**, char*, const int);
void rand_add_p(const int, List***, char*, const int);
void rand_insert(const int, List**, char*, const int);
void rand_insert_p(const int, List***, char*, const int);

char items[NUM_ITEMS];

int main() {
    // Create the array of items which will be referenced by nodes.
    // chars with ASCII code 33 to 126 are readable.
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i] = (char) (i + 33);
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
    const int NUM_LISTS1 = 3;
    List** lists1[] = {&a, &b, &c};
    char list_names1[] = {'a', 'b', 'c'};
    test_createrino(NUM_LISTS1, lists1, list_names1);

    // Add 90 elements total, allocating randomly.
    const int NUM_ELEMS1 = 90;
    
    srand(time(0));
    rand_add_p(NUM_ELEMS1, lists1, list_names1, NUM_LISTS1);
    testerino_p(NUM_LISTS1, lists1, list_names1, NUM_ELEMS1);

    // Try to add more than 100 nodes collectively to all the lists.
    const int NUM_LISTS2 = 2;
    List** lists2[] = {&d, &e};
    char list_names2[] = {'d', 'e'};
    test_createrino(NUM_LISTS2, lists2, list_names2);

    // Add 11 elements total, allocating randomly.
    const int NUM_ELEMS2 = 11;
    rand_add_p(NUM_ELEMS2, lists2, list_names2, NUM_LISTS2);
    testerino_p(NUM_LISTS2, lists2, list_names2, NUM_ELEMS2);

    // Try to create 7 more lists 
    // In that case we'll have 12 lists in total--2 more than the maximum allowed.
    const int NUM_LISTS3 = 7;
    List** lists3[] = {&f, &g, &h, &i, &j, &k, &l};
    char list_names3[] = {'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    test_createrino(NUM_LISTS3, lists3, list_names3);
    printf("\n");

    // Remove 80 nodes randomly from lists that have size != 0.
    const int NUM_LISTS4 = 5;
    const int NUM_ELEMS4 = 80;
    List* lists4[] = {a, b, c, d, e};
    char list_names4[] = {'a', 'b', 'c', 'd', 'e'};
    rand_dealloc(NUM_ELEMS4, lists4, list_names4, NUM_LISTS4);
    testerino(NUM_LISTS4, lists4, list_names4, 100 - NUM_ELEMS4);

    // Do some more allocations and deallocations to make sure that things don't get into a bad 
    // state after removals or additions--CURRENTLY THEY DO.
    const int NUM_LISTS5 = 10;
    const int NUM_ELEMS5 = 50;
    List* lists5[] = {a, b, c, d, e, f, g, h, i, j};
    char list_names5[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    rand_add(NUM_ELEMS5, lists5, list_names5, NUM_LISTS5);
    testerino(NUM_LISTS5, lists5, list_names5, NUM_ELEMS5 + 20);

    const int NUM_ELEMS6 = 27;
    rand_dealloc(NUM_ELEMS6, lists5, list_names5, NUM_LISTS5);
    testerino(NUM_LISTS5, lists5, list_names5, NUM_ELEMS5 + 20 - NUM_ELEMS6);

    List* y = f;
    char y_name = 'f';
    while (test_prev(y, y_name) != NULL);
    char ch = '^';
    test_add(y, (void*) &ch, y_name);
    print_list(y, y_name);
    test_count(y, y_name);
    printf("\n");
    while (test_prev(y, y_name) != NULL);
    test_remove(y, y_name);
    print_list(y, y_name);
    test_count(y, y_name);
    printf("\n");

    // Need to test insertion somewhere.

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

void test_createrino(const int NUM_LISTS, List*** lists, char* list_names) {
    for (int i = 0; i < NUM_LISTS; i++) {
        test_create(lists[i], list_names[i]);
    }
}

void rand_add(const int NUM_ELEMS, List** lists, char* list_names, const int NUM_LISTS) {
    rand_alloc(NUM_ELEMS, lists, list_names, NUM_LISTS, test_add);
}

void rand_add_p(const int NUM_ELEMS, List*** lists, char* list_names, const int NUM_LISTS) {
    rand_alloc_p(NUM_ELEMS, lists, list_names, NUM_LISTS, test_add);
}

void rand_insert(const int NUM_ELEMS, List** lists, char* list_names, const int NUM_LISTS) {
    rand_alloc(NUM_ELEMS, lists, list_names, NUM_LISTS, test_insert);
}

void rand_insert_p(const int NUM_ELEMS, List*** lists, char* list_names, const int NUM_LISTS) {
    rand_alloc_p(NUM_ELEMS, lists, list_names, NUM_LISTS, test_insert);
}

void rand_alloc(const int NUM_ELEMS, List** lists, char* list_names, const int NUM_LISTS,
                    void (*alloc_func) (List*, void*, char)) {
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        alloc_func(lists[choice], (void*) (items + i), list_names[choice]);
    }
}

void rand_alloc_p(const int NUM_ELEMS, List*** lists, char* list_names, const int NUM_LISTS,
                    void (*alloc_func) (List*, void*, char)) {
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        alloc_func(*(lists[choice]), (void*) (items + i), list_names[choice]);
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

void rand_dealloc_p(const int NUM_ELEMS, List*** lists, char* list_names, const int NUM_LISTS) {
    for (int i = 0; i < NUM_ELEMS; ++i) {
        int choice = rand() % NUM_LISTS;
        List* list = *(lists[choice]);
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

void testerino_p(const int NUM_LISTS, List*** lists, char* list_names, const int NUM_REQUESTED_NODES) {
    int total = 0;
    for (int i = 0; i < NUM_LISTS; ++i) {
        print_list(*(lists[i]), list_names[i]);
        total += test_count(*(lists[i]), list_names[i]);
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
    test_add_thing(l, item, list_name, List_add, "List_add");
}

void* test_remove(List* list, char list_name) {
    return test_remove_thing(list, list_name, List_remove, "List_remove");
}

// Helper function.
void* test_remove_thing(List* l, char list_name,
                        void* (*remove_func) (List*), char* remove_func_name) {
    char* item = (char*) remove_func(l);
    if (item == NULL) {
        printf("%s(%c, item) = NULL\n", remove_func_name, list_name);
        return NULL;
    }
    else {
        printf("%s(%c, item) = %c\n", remove_func_name, list_name, *item);
        return (void*) item;
    }
}

void* test_trim(List* list, char list_name) {
    return test_remove_thing(list, list_name, List_trim, "List_trim");
}

void* test_prev(List* l, char list_name) {
    char* item = (char*) List_prev(l);
    if (item == NULL) {
        printf("List_prev(%c) = NULL\n", list_name);
    }
    else {
        printf("List_prev(%c) = %c\n", list_name, *item);
    }
    return item;
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

void test_curr(List* l, char list_name) {
    if (l->current == NULL) {
        printf("%c->current = NULL\n%c->current_state = %d\n", list_name, list_name, 
                l->current_state);
    }
    else {
        printf("%c->current = %p\n%c->current_state = %d\n", list_name, (void*) l->current, 
                list_name, l->current_state);
        void* item = List_curr(l);
        if (item == NULL) {
            printf("%c->current->item = INACCESSIBLE or NULL\n", list_name);
        }
        else {
            printf("%c->current->item = %c\n", list_name, *((char*) List_curr(l)));
        }
    }
}

void print_list(List *l, char name) {
    // printf("\n");
    // test_first(l, name); // Remove later.
    // printf("\n");
    // test_last(l, name); // Remove later.
    // printf("\n");
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

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void test_first(List* list, char list_name) {
    assert(list != NULL);
    printf("%c->head = %p\n", list_name, (void*) list->head);
    printf("%c->current (initial) = %p\n", list_name, (void*) list->current);
    
    void* item = List_first(list);
    if (item == NULL) {
        printf("List_first(%c) = INACCESSIBLE or NULL\n", list_name);
    }
    else {
        printf("List_first(%c) = %c\n", list_name, *((char*) item));
    }
    printf("%c->current (new) = %p\n", list_name, (void*) list->current);
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.

// Could do for a refactor here as test_first is almost identical to this function.
void test_last(List* list, char list_name) {
    assert(list != NULL);
    printf("%c->tail = %p\n", list_name, (void*) list->tail);
    printf("%c->current (initial) = %p\n", list_name, (void*) list->current);
    
    void* item = List_last(list);
    if (item == NULL) {
        printf("List_last(%c) = INACCESSIBLE or NULL\n", list_name);
    }
    else {
        printf("List_last(%c) = %c\n", list_name, *((char*) item));
    }
    printf("%c->current (new) = %p\n", list_name, (void*) list->current);
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* test_next(List* list, char list_name) {
    char* item = (char*) List_next(list);
    if (item == NULL) {
        printf("List_next(%c) = NULL\n", list_name);
    }
    else {
        printf("List_next(%c) = %c\n", list_name, *item);
    }
    return item;
}

void test_insert(List* l, void* item, char list_name) {
    test_add_thing(l, item, list_name, List_insert, "List_insert");
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
void test_append(List* l, void* item, char list_name) {
   test_add_thing(l, item, list_name, List_append, "List_append");
}

// Helper function.
void test_add_thing(List* l, void* item, char list_name,
                        int (*add_func) (List*, void*), char* add_func_name) {
    char* x = (char*) item;
    if (x != NULL) {
        printf("%s(%c, *item = %c) = %d\n", add_func_name, list_name, *x, add_func(l, item));
    }
    else {
        printf("%s(%c, item = NULL) = %d\n", add_func_name, list_name, add_func(l, item));
    }
}

void test_prepend(List* l, void* item, char list_name) {
    test_add_thing(l, item, list_name, List_prepend, "List_prepend");
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
void test_search(List* list, void* cmp_arg, char list_name) {
    char arg = *((char*) cmp_arg);
    test_curr(list, list_name);
    printf("Searching %c for '%c'...\n", list_name, arg);
    char* item = (char*) List_search(list, cmp_ch, cmp_arg);
    if (item == NULL) {
        printf("'%c' not found.\n", arg);
    }
    else {
        printf("Found '%c' at address %p\n", *item, (void*) item);
    }
    test_curr(list, list_name);
}

// My comparator.
bool cmp_ch(void* item, void* cmp_arg) {
    char i = *((char*) item);
    char arg = *((char*) cmp_arg);
    return i == arg;
}
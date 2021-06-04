#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "list.h"

#define NUM_ITEMS 126

static char* LC = "List_create()";
static char* LCN = "List_count()";
static char* LF = "List_first()";

void  print_list(List*, char);
bool  cmp_ch(void*, void*);
bool test_first(List*);
bool test_add(List*, char*, int);
bool test_create(List**);
bool test_count(List*, int);
void print_running(char* test_name);
void print_result(char*, bool);

int main() {
    char* items = (char*) malloc(sizeof(char) * NUM_ITEMS);
    assert(items != NULL);
    // Create the array of items which will be referenced by nodes.
    // chars with ASCII code 33 to 126 are readable.
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i] = (char) (i + 33);
    }

    List* a;

    print_running(LC);
    print_result(LC, test_create(&a));
    printf("\n");
    
    print_running("List_add() 4 times");
    print_result("(1) List_add()", test_add(a, items, LIST_SUCCESS));
    print_result("(2) List_add()", test_add(a, items + 1, LIST_SUCCESS));
    print_result("(3) List_add()", test_add(a, items + 2, LIST_SUCCESS));
    print_result("(4) List_add()", test_add(a, items + 3, LIST_SUCCESS));
    printf("\n");

    // May want to print contents of a.

    print_running(LCN);
    print_result(LCN, test_count(a, 4));
    printf("\n");

    print_running(LF);
    print_result(LF, test_first(a));
    printf("\n");

    return 0;
}

bool test_first(List* l) {
    Node* head = l->head;
    void* result = List_first(l);
    if (result == NULL) return false;
    if (result != head->item) return false;
    if (result != l->current->item) return false;

    return true;
}

bool test_add(List* l, char* item, int expected) {
    int result = List_add(l, (void*) item);
    return result == expected;
}

bool test_create(List** l) {
    *l = List_create();
    return (bool) l;
}

bool test_count(List* l, int expected_count) {
    int count = List_count(l);
    return (count == expected_count);
}

void print_running(char* test_name) {
    printf("Running %s...\n", test_name);
}

void print_result(char* test_name, bool result) {
    char* out = (result) ? "PASSED" : "FAILED";
    printf("%s %s\n", test_name, out);
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

// My comparator.
bool cmp_ch(void* item, void* cmp_arg) {
    char i = *((char*) item);
    char arg = *((char*) cmp_arg);
    return i == arg;
}
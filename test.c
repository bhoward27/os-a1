#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "list.h"

#define NUM_ITEMS 126

static char* LC = "List_create()";
static char* LCN = "List_count()";
static char* LF = "List_first()";
static char* LL = "List_last()";
static char* LN = "List_next()";
static char* LP = "List_prev()";
static char* LCR = "List_curr()";
static char* LCI = "List_insert()";
static char* LA = "List_append()";
static char* LPRP = "List_prepend()";
static char* LR = "List_remove()";
static char* LCON = "List_concat()";
static char* LS = "List_search()";
static char* LFR = "List_free()";

bool  cmp_ch(void*, void*);
bool test_first(List*);
bool test_add(List*, char*, int);
bool test_create(List**);
bool test_count(List*, int);
bool test_curr(List*);
bool test_prev(List*, bool);
bool test_next(List*, bool);
bool test_last(List*);
bool test_remove(List*, bool);
bool test_insert(List*, char*, int);
bool test_append(List*, char*, int);
bool test_prepend(List*, char*, int);
bool test_concat(List*, List*);
bool test_free(List**);
bool test_search(List*, void*, bool);
bool test_concat(List*, List*);
void free_fn(void*);

void print_running(char* test_name);
void print_result(char*, bool);
void print_list(List*, char);

int main() {
    char items[NUM_ITEMS];
    assert(items != NULL);
    // Create the array of items which will be referenced by nodes.
    // chars with ASCII code 33 to 126 are readable.
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i] = (char) (i + 33);
    }

    List* a;

    print_running(LC);
    print_result(LC, test_create(&a));
    print_list(a, 'a');
    printf("\n");
    
    print_running("List_add() 4 times");
    print_result("(1) List_add()", test_add(a, items, LIST_SUCCESS));
    print_result("(2) List_add()", test_add(a, items + 1, LIST_SUCCESS));
    print_result("(3) List_add()", test_add(a, items + 2, LIST_SUCCESS));
    print_result("(4) List_add()", test_add(a, items + 3, LIST_SUCCESS));
    print_list(a, 'a');
    printf("\n");

    print_running(LCN);
    print_result(LCN, test_count(a, 4));
    print_list(a, 'a');
    printf("\n");

    print_running(LF);
    print_result(LF, test_first(a));
    print_list(a, 'a');
    printf("\n");

    print_running(LL);
    print_result(LL, test_last(a));
    print_list(a, 'a');
    printf("\n");

    print_running(LN);
    print_result(LN, test_next(a, true));
    print_list(a, 'a');
    printf("\n");

    print_running(LP);
    print_result(LP, test_prev(a, false));
    print_list(a, 'a');
    printf("\n");

    print_running(LCR);
    print_result(LCR, test_curr(a));
    print_list(a, 'a');
    printf("\n");

    print_running(LCI);
    print_result(LCI, test_insert(a, items + 4, LIST_SUCCESS));
    print_list(a, 'a');
    printf("\n");

    print_running(LA);
    print_result(LA, test_append(a, items + 5, LIST_SUCCESS));
    print_list(a, 'a');
    printf("\n");

    print_running(LPRP);
    print_result(LPRP, test_prepend(a, items + 6, LIST_SUCCESS));
    print_list(a, 'a');
    printf("\n");

    print_running(LR);
    print_result(LR, test_remove(a, false));
    print_list(a, 'a');
    printf("\n");

    List* b;
    print_running(LC);
    print_result(LC, test_create(&b));
    print_list(b, 'b');
    printf("\n");
    
    print_running("List_add() 4 times");
    print_result("(1) List_add()", test_add(b, items + 10, LIST_SUCCESS));
    print_result("(2) List_add()", test_add(b, items + 7, LIST_SUCCESS));
    print_result("(3) List_add()", test_add(b, items + 8, LIST_SUCCESS));
    print_result("(4) List_add()", test_add(b, items + 9, LIST_SUCCESS));
    print_list(b, 'b');
    printf("\n");

    print_running(LCON);
    print_result(LCON, test_concat(a, b));
    print_list(a, 'a');

    print_running(LF);
    print_result(LF, test_first(a));
    print_list(a, 'a');
    printf("\n");

    void* arg = (void*) (items + 5);
    print_running(LS);
    print_result(LS, test_search(a, arg, false));
    printf("\n");

    printf("Creating maximum amount of lists...\n");
    while (List_create());
    printf("Done.\n");
    print_running(LFR);
    print_result(LFR, test_free(&a));
    print_list(a, 'a'); //should be empty.
    printf("\n");

    return 0;
}

void free_fn(void* item) {
    return;
}

bool test_free(List** l) {
    if (List_create() == NULL) {
        List_free(*l, free_fn);
        *l = List_create();
        if (*l == NULL) return false;
    }
    return true;
}

bool test_search(List* l, void* arg, bool expect_null) {
    void* result = List_search(l, cmp_ch, arg);
    if (expect_null) {
        if (result) return false;
        return l->current_state == LIST_OOB_END;
    } 
   
    if (result != arg) return false;
    if (l->current->item != arg) return false;
    return true;
}

bool test_concat(List* u, List* v) {
    int u_size = List_count(u);
    int v_size = List_count(v);
    Node* v_tail = v->tail;
    Node* u_current = u->current;
    List_concat(u, v);
    if (u_current != u->current) return false;
    if (u_size + v_size != List_count(u)) return false;
    if (v_tail != u->tail) return false;
    return true;
}

bool test_curr(List* l) {
    void* result = List_curr(l);
    enum ListOutOfBounds state = l->current_state;
    if (state != LIST_OOB_OK) {
        return result == NULL;
    }
    return result == l->current->item;
}

bool test_prev(List* l, bool expect_null) {
    Node* prev;
    if (l->current_state == LIST_OOB_END && !expect_null) {
        void* result = List_prev(l);
        return result == l->tail->item;
    }
    if (!expect_null) {
        if (l->current == NULL) return false;
        prev = l->current->prev;
    }
    void* result = List_prev(l);
    if (expect_null) {
        if (result) return false;
        return l->current_state == LIST_OOB_START || l->current_state == LIST_OOB_BAD;
    }
    return l->current == prev;
}

bool test_next(List* l, bool expect_null) {
    Node* next;
    if (!expect_null) {
        next = l->current->next;
    }
    void* result = List_next(l);
    if (expect_null) {
        if (result) return false;
        return l->current_state == LIST_OOB_END || l->current_state == LIST_OOB_BAD;
    }
    return l->current == next;
}

bool test_first(List* l) {
    Node* head = l->head;
    void* result = List_first(l);
    if (result == NULL) return false;
    if (result != head->item) return false;
    if (result != l->current->item) return false;

    return true;
}

bool test_last(List* l) {
    Node* tail = l->tail;
    void* result = List_last(l);
    if (result == NULL) return false;
    if (result != tail->item) return false;
    if (result != l->current->item) return false;

    return true;
}

bool test_add(List* l, char* item, int expected) {
    int result = List_add(l, (void*) item);
    return result == expected;
}

bool test_remove(List* l, bool expect_null) {
    int size_a = List_count(l);
    Node* current = l->current;
    void* result = List_remove(l);
    if (expect_null) return !result;
    if (result != current->item) return false;
    if (current == l->current) return false;
    int size_b = List_count(l);
    return size_b == size_a - 1;
}

bool test_insert(List* l, char* item, int expected) {
    int result = List_insert(l, (void*) item);
    return result == expected;
}

bool test_append(List* l, char* item, int expected) {
    int result = List_append(l, (void*) item);
    return result == expected;
}

bool test_prepend(List* l, char* item, int expected) {
    int result = List_prepend(l, (void*) item);
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
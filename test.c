#include <stdio.h>
#include "list.h"
#include "node_manager.h"

void test_count(List*);
void test_add(List*, void*);
void test_remove(List*);
void test_prev(List*);
void test_tail(List*);
void test_curr(List*);
void print_list(List*);
void print_free_list(Node_manager*);
void print_all_nodes(Node_manager*);

int main() {
    printf("Possible values for current_state:\n"
        "LIST_OOB_START = %d\n"
        "LIST_OOB_END = %d\n"
        "LIST_OOB_OK = %d\n"
        "LIST_OOB_BAD = %d\n\n", 
        LIST_OOB_START, LIST_OOB_END, LIST_OOB_OK, LIST_OOB_BAD);

    List* l = List_create();
    char one = '1';
    char two = '2';
    char three = '3';
    char four = '4';
    test_add(l, &one);
    test_add(l, &two);
    test_add(l, &three);
    test_add(l, &four);
    print_list(l);
    test_curr(l);

    test_remove(l);
    print_list(l);
    test_tail(l);
    test_curr(l);

    test_prev(l);
    test_curr(l);
    test_remove(l);
    print_list(l);
    test_tail(l);
    test_curr(l);

    test_prev(l);
    test_curr(l);
    test_remove(l);
    print_list(l);
    test_tail(l);
    test_curr(l);

    test_prev(l);
    test_curr(l);
    test_remove(l);
    print_list(l);
    test_tail(l);
    test_curr(l);
    
    return 0;
}

void test_count(List* l) {
    printf("List_count(l) = %d\n", List_count(l));
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

void print_list(List *l) {
    assert(l != NULL);
    Node *head = l->head;
    Node *tail = l->tail;

    if (l->size == 0) {
        printf("-------l--------\n");
        printf("Empty.\n\n");
        return;
    }
    if (head == NULL) {
        printf("Bad head. Head = NULL\n\n");
        return;
    }
    if (tail == NULL) {
        printf("Bad tail. Tail = NULL\n\n");
        return;
    }

    printf("-------l--------\n");
    Node *cursor = head;
    char *item = NULL;
    while (cursor != tail) {
        item = (char*) cursor->item;
        if (item != NULL)
            printf("%c -> ", *item);
        else
            printf("INACCESSIBLE -> ");
        cursor = cursor->next;
    }
    item = (char*) cursor->item;
    if (item != NULL)
        printf("%c\n\n", *item);
    else
        printf("INACCESSIBLE\n\n");
}

void print_free_list(Node_manager *nm) {
    
}

void print_all_nodes(Node_manager *nm) {

}
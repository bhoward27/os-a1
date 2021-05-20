#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*
    At the moment, the below functions will be implemented in the tradional linked list way 
    (i.e, with malloc)--although this is incorrect for the project, this is done as a temporary step
    to brush up on linked lists and provide as skeleton for the future code.
*/

static int num_heads = 0;

List* List_create() {
    if (num_heads >= LIST_MAX_NUM_HEADS) return NULL;

    List* new_list = malloc(sizeof(List));
    if (new_list == NULL) return NULL;

    new_list->head = new_list->tail = new_list->current = NULL; // The list is empty, so no nodes exist yet--so point "nowhere".
    new_list->size = 0;
    return new_list;
}

int List_count(List* pList) {
    assert(pList != NULL);
    return pList->size;
}

int List_add(List* pList, void* pItem) {
    assert(pList != NULL);
}
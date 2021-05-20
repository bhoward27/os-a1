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

    // The list is empty, so no nodes exist yet--so point "nowhere".
    new_list->head = new_list->tail = new_list->current = NULL;
    new_list->size = 0;
    num_heads++;
    return new_list;
}

int List_count(List* pList) {
    assert(pList != NULL);
    return pList->size;
}

int List_add(List* pList, void* pItem) {
    assert(pList != NULL);
    // If in C++, I would make these actually const. Might want to move to other part of file.
    int FAILED = -1;
    int SUCCEEDED = 0;
    //  In real code, need to check if there are free nodes available before going further.

    if (pList->size == 0) {
        //  Somewhere, deal with current node.
        
        Node* new_node = malloc(sizeof(Node));
        if (new_node == NULL) return FAILED;
        new_node->item = pItem;

        pList->head = new_node;
        pList->tail = new_node;
        new_node->next = new_node->prev = NULL;

        pList->size = 1;

        return SUCCEEDED;
    }
}
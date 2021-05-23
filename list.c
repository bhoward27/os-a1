#include "list.h"
#include "node_manager.h"

List* List_create() {
    if (nm_ptr == NULL) {
        init_free_list(&node_manager);
        nm_ptr = &node_manager;
    }
    if (num_heads >= LIST_MAX_NUM_HEADS) return NULL;
    List* new_list = lists + num_heads;

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
    if (pList->size > 0) {
        // Somewhere, deal with current node.
        Node* x = new_node(nm_ptr);
        if (x == NULL) return LIST_FAIL;
        x->item = pItem;

        x->prev = pList->current;
        x->next = pList->current->next;
        pList->current = x;

        (pList->size)++;
    }
    else if (pList->size == 0) {
        //  Somewhere, deal with current node.
        
        Node* x = new_node(nm_ptr);
        if (x == NULL) return LIST_FAIL;
        x->item = pItem;

        pList->head = x;
        pList->tail = x;
        x->next = x->prev = NULL;
        pList->current = x;

        pList->size = 1;

        return LIST_SUCCESS;
    }
    else return LIST_FAIL;
}
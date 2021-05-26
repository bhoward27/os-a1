#include "list.h"
#include "node_manager.h"

int num_heads = 0;
List lists[LIST_MAX_NUM_HEADS];

List* List_create() {
    if (nm_ptr == NULL) {
        init_free_list(&node_manager);
        nm_ptr = &node_manager;
    }
    if (num_heads >= LIST_MAX_NUM_HEADS) return NULL;
    List* new_list = lists + num_heads;

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->current = NULL;
    new_list->current_state = LIST_OOB_BAD;
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
        //  Should probably be checking current_state
        Node* x = new_node(nm_ptr);
        if (x == NULL) return LIST_FAIL;
        x->item = pItem;

        x->prev = pList->current;
        x->next = pList->current->next;
        pList->current->next = x;

        pList->current = x;
        if (x->prev == pList->tail) pList->tail = x;

        (pList->size)++;
        return LIST_SUCCESS;
    }
    else if (pList->size == 0) {
        Node* x = new_node(nm_ptr);
        if (x == NULL) return LIST_FAIL;
        x->item = pItem;

        pList->head = x;
        pList->tail = x;
        x->next = NULL;
        x->prev = NULL;
        pList->current = x;
        pList->current_state = LIST_OOB_OK;

        pList->size = 1;

        return LIST_SUCCESS;
    }
    else return LIST_FAIL;
}

void* List_remove(List* pList) {
    assert(pList != NULL);
    if (pList->size == 0) return NULL;
    Node* temp = pList->current;
    if (temp == NULL) {
        return NULL;
    }

    if (pList->size == 1) {
        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
        pList->current_state = LIST_OOB_BAD;
        delete_node(nm_ptr, temp);
        pList->size = 0;
        return temp->item;
    }

    if (temp == pList->tail) {
        pList->tail = temp->prev;
        pList->tail->next = NULL;
        pList->current_state = LIST_OOB_END;
    }   
    pList->current = temp->next;

    delete_node(nm_ptr, temp);
    (pList->size)--;
    return temp->item;
}

void* List_prev(List* pList) {
    // May need to have some additional conditions regarding current_status.
    // This would be to account for the fact if this operation changes current_status.
    assert(pList != NULL);

    if (pList->current_state == LIST_OOB_START) return NULL;

    // If we get this "bad" input, assume that the previous element should be the tail.
    if (pList->current_state == LIST_OOB_END) {
        pList->current = pList->tail;
        pList->current_state = LIST_OOB_OK;
        return pList->tail->item;
    }

    if (pList->current->prev == NULL) {
        pList->current = NULL;
        pList->current_state = LIST_OOB_START;
        return NULL;
    }

    pList->current = pList->current->prev;
    
    return pList->current->item;
}

void* List_curr(List* pList) {
    assert(pList != NULL);
    Node* ptr = pList->current;
    if (ptr == NULL) return NULL;
    return ptr->item;
}
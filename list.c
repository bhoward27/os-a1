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
    int size = List_count(pList);

    // If size < 0, the value has been corrupted, perhaps due to overflow, so abort.
    assert(size >= 0);

    Node* x = new_node(nm_ptr);
    if (x == NULL) return LIST_FAIL;
    x->item = pItem;

    if (size > 0) {
        enum ListOutOfBounds state = pList->current_state;
        switch(state) {
            case LIST_OOB_OK:
                x->prev = pList->current;
                x->next = pList->current->next;
                pList->current->next = x;
                pList->current = x;
                if (x->prev == pList->tail) pList->tail = x;
                break;
            case LIST_OOB_START:
                List_add_to_start(pList, x);
                break; 
            case LIST_OOB_END:
                List_add_to_end(pList, x);
                break;

            // These last two cases should be impossible (esp. when size > 0) so abort.
            case LIST_OOB_BAD:
            default:
                return LIST_FAIL;
                break;
        }
    }
    else List_add_to_empty(pList, x);
    (pList->size)++;
    return LIST_SUCCESS;
}

void* List_remove(List* pList) {
    assert(pList != NULL);
    int size = List_count(pList);
    assert(size >= 0);

    if (size == 0) return NULL;
    Node* temp = pList->current;
    if (temp == NULL) {
        return NULL;
    }

    if (size == 1) {
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
    assert(pList != NULL);
    enum ListOutOfBounds state = pList->current_state;
    switch(state) {
        case LIST_OOB_START:
        case LIST_OOB_BAD:
            return NULL;
            break;
        case LIST_OOB_END:
            pList->current = pList->tail;
            pList->current_state = LIST_OOB_OK;
            return pList->tail->item;
            break;
        case LIST_OOB_OK:
            if (pList->current->prev == NULL) {
                pList->current = NULL;
                pList->current_state = LIST_OOB_START;
                return NULL;
            }

            pList->current = pList->current->prev;
            
            return pList->current->item;
            break;
        default:
            return NULL;
            break;
    }
}

void* List_curr(List* pList) {
    assert(pList != NULL);
    Node* ptr = pList->current;
    if (ptr == NULL) return NULL;
    return ptr->item;
}

// Untested
void* List_first(List* pList) {
    assert(pList != NULL);
    return List_fl(pList, pList->head);
}

// Untested
void* List_last(List* pList) {
    assert(pList != NULL);
    return List_fl(pList, pList->tail);
}

// This helper function should only be called by List_first or List_last.
void* List_fl(List* pList, Node* fl) {
    int size = List_count(pList);
    assert(size >= 0);
    if (size == 0) {
        // No need to set current to NULL, as, if the list is empty, this SHOULD already be the case.
        return NULL;
    }
    // We assume here that fl can't be NULL if size > 0.
    pList->current = fl;
    pList->current_state = LIST_OOB_OK;
    return fl->item;
}


void* List_next(List* pList) {
    assert(pList != NULL);
    enum ListOutOfBounds state = pList->current_state;
    switch(state) {
        case LIST_OOB_END:
        case LIST_OOB_BAD:
            return NULL;
            break;
        case LIST_OOB_START:
            pList->current = pList->head;
            // Assume the head is not null.
            pList->current_state = LIST_OOB_OK;
            return pList->current->item;
            break;
        case LIST_OOB_OK:
            if (pList->current == pList->tail) {
                pList->current = NULL;
                pList->current_state = LIST_OOB_END;
                return NULL;
            }
            pList->current = pList->current->next;
            return pList->current->item;
            break;
        default:
            return NULL;
            break;
    }
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem) {
    assert(pList != NULL);
    int size = List_count(pList);

    // If size < 0, the value has been corrupted, perhaps due to overflow, so abort.
    assert(size >= 0);

    Node* x = new_node(nm_ptr);
    if (x == NULL) return LIST_FAIL;
    x->item = pItem;

    if (size > 0) {
        enum ListOutOfBounds state = pList->current_state;
        switch(state) {
            case LIST_OOB_OK:
                x->next = pList->current;
                x->prev = pList->current->prev;
                pList->current->prev = x;
                pList->current = x;
                if (pList->current == pList->head) pList->head = x;
                break;
            case LIST_OOB_START:
                List_add_to_start(pList, x);
                break;  
            case LIST_OOB_END:
                List_add_to_end(pList, x);
                break;

            // These last two cases should be impossible (esp. when size > 0) so abort.
            case LIST_OOB_BAD:
            default:
                return LIST_FAIL;
                break;
        }
    }
    else List_add_to_empty(pList, x);
    (pList->size)++;
    return LIST_SUCCESS;
}

// Helper function. Only to be called by List_add or List_insert.
void List_add_to_end(List* pList, Node* x) {
    x->prev = pList->tail;
    x->next = NULL;
    pList->tail->next = x;
    pList->tail = x;
    pList->current = x;
    pList->current_state = LIST_OOB_OK;
}

// Helper function. Only to be called by List_add or List_insert.
void List_add_to_start(List* pList, Node* x) {
    x->prev = NULL;
    x->next = pList->head;
    pList->head->prev = x;
    pList->head = x;
    pList->current = x;
    pList->current_state = LIST_OOB_OK;
}

// Helper function. Only to be called by List_add or List_insert.
void List_add_to_empty(List* pList, Node* x) {
    pList->head = x;
    pList->tail = x;
    x->next = NULL;
    x->prev = NULL;
    pList->current = x;
    pList->current_state = LIST_OOB_OK;
}
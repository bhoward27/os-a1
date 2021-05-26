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
        //  Should probably be checking current_state
        x->prev = pList->current;
        x->next = pList->current->next;
        pList->current->next = x;

        pList->current = x;
        if (x->prev == pList->tail) pList->tail = x;
    }
    else {
        pList->head = x;
        pList->tail = x;
        x->next = NULL;
        x->prev = NULL;
        pList->current = x;
        pList->current_state = LIST_OOB_OK;
    }
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

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList) {
    assert(pList != NULL);
    if (List_count(pList) == 0) {
        // No need to set current to NULL, as, if the list is empty, this SHOULD already be the case.
        return NULL;
    }
    Node* first = pList->tail;
    // Not done here.


    return first->item;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
// void* List_last(List* pList) {

// }

// // Advances pList's current item by one, and returns a pointer to the new current item.
// // If this operation advances the current item beyond the end of the pList, a NULL pointer 
// // is returned and the current item is set to be beyond end of pList.
// void* List_next(List* pList) {

// }
#include "list.h"
#include "node_manager.h"

int num_heads = 0;

List* List_create() {
    if (nm_ptr == NULL) {
        init_free_list(&node_manager);
        nm_ptr = &node_manager;
    }
    if (num_heads >= LIST_MAX_NUM_HEADS) return NULL;
    List* new_list = lists + num_heads;

    new_list->head = (Node*) LIST_OOB_START;
    new_list->tail = (Node*) LIST_OOB_END;
    new_list->current = NULL;
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
        return LIST_SUCCESS;
    }
    else if (pList->size == 0) {
        //  Somewhere, deal with current node.
        
        Node* x = new_node(nm_ptr);
        if (x == NULL) return LIST_FAIL;
        x->item = pItem;

        pList->head = x;
        pList->tail = x;
        x->next = (Node*) LIST_OOB_END;
        x->prev = (Node*) LIST_OOB_START;
        pList->current = x;

        pList->size = 1;

        return LIST_SUCCESS;
    }
    else return LIST_FAIL;
}

void* List_remove(List* pList) {
    /*
        Remember, if current = LIST_OOB_START (or END), it is NOT pointing to a node.
        So if you say current = LIST_OOB, then you are saying current is bunk and can't be used.
        Right? you're giving current an invalid value, so any other operation you do will fail
        because current is invalid.
        So I don't think you actually want to set current to LIST_OOB, but maybe it's next or prev.
    */
    assert(pList != NULL);
    if (pList->size == 0) return NULL;
    Node* temp = pList->current;
    if (temp == (Node*) LIST_OOB_END || temp == (Node*) LIST_OOB_START) {
        return NULL;
    }
    pList->current = temp->next;
    delete_node(nm_ptr, temp);
    (pList->size)--;
    return temp->item;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList) {
    assert(pList != NULL);

    if (pList->current == (Node*) LIST_OOB_START || pList->current == (Node*) LIST_OOB_END) {
        return NULL;
    }

    pList->current = pList->current->prev;
    if (pList->current == (Node*) LIST_OOB_START) return NULL;
    
    return pList->current->item;
}
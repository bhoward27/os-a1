#include "list.h"
#include "node_manager.h"

List* List_create() {
    // if (free_nodes == NULL) {
    //     if (!Stack_init(&the_node_stack)) return NULL;
    //     free_nodes = &the_node_stack;
    // }

    if (num_heads >= LIST_MAX_NUM_HEADS) return NULL;

    List* new_list = lists + num_heads;

    // The list is empty, so no nodes exist yet--so point "nowhere".
    new_list->head = new_list->tail = new_list->current = NULL;
    new_list->size = 0;
    num_heads++;
    return new_list;
}

int List_count(List* pList) {
//     assert(pList != NULL);
//     return pList->size;
// }

// int List_add(List* pList, void* pItem) {
//     assert(pList != NULL);
//     if (pList->size > 0) {
//         // Somewhere, deal with current node.
//         Node* new_node = Stack_pop(free_nodes);
//         if (new_node == NULL) return LIST_FAIL;
//         new_node->item = pItem;

//         new_node->prev = pList->current;
//         new_node->next = pList->current->next;
//         pList->current = new_node;

//         (pList->size)++;
//     }
//     else if (pList->size == 0) {
//         //  Somewhere, deal with current node.
        
//         Node* new_node = Stack_pop(free_nodes);
//         if (new_node == NULL) return LIST_FAIL;
//         new_node->item = pItem;

//         pList->head = new_node;
//         pList->tail = new_node;
//         new_node->next = new_node->prev = NULL;

//         pList->size = 1;

//         return LIST_SUCCESS;
//     }
//     else return LIST_FAIL;
}
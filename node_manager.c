#include "node_manager.h"

void init_free_list(Node_manager* node_manager) {
    assert(node_manager != NULL);
    int i;
    Node* head = node_manager->free_head = node_manager->nodes;
    Node* current = head;
    Node* x;
    for (i = 1; i < LIST_MAX_NUM_NODES; ++i) {
        x = current->next = head + i;
        current = x;
    }
    current->next = NULL;
}

bool delete_node(Node_manager* node_manager, Node* x) {
    assert(node_manager != NULL);
    assert(x != NULL);
     // Operation doesn't make sense in this case, so abort.
    if (node_manager->free_head == NULL) return false;

    x->next = node_manager->free_head;
    node_manager->free_head = x;
    return true;
}

Node* new_node(Node_manager* node_manager) {
    assert(node_manager != NULL);
    // if (node_manager
}
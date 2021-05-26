#include "node_manager.h"

Node_manager node_manager;
Node_manager* nm_ptr = NULL;

void init_free_list(Node_manager* node_manager) {
    assert(node_manager != NULL);
    assert(node_manager->nodes != NULL);

    Node* head = node_manager->free_head = node_manager->nodes;
    Node* current = head;
    for (int i = 1; i < LIST_MAX_NUM_NODES; ++i) {
        Node* x = current->next = head + i;
        current = x;
    }
    current->next = NULL;
}

void delete_node(Node_manager* node_manager, Node* x) {
    assert(node_manager != NULL);
    assert(x != NULL);

    x->next = node_manager->free_head;
    node_manager->free_head = x;
}

Node* new_node(Node_manager* node_manager) {
    assert(node_manager != NULL);

    // In this case, all nodes are being used, so operation fails.
    if (node_manager->free_head == NULL) return NULL;

    Node* new_node = node_manager->free_head;
    node_manager->free_head = new_node->next;
    return new_node;
}
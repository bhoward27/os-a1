#ifndef _NODE_MANAGER_H_
#define _NODE_MANAGER_H_
#include "list.h"

typedef struct Node_manager_s Node_manager;
struct Node_manager_s {
    Node nodes[LIST_MAX_NUM_NODES];
    Node* free_head;
};

// I guess this is a no-no since it says to make globals static,
// but since list.c requires these variables, I can't make it static.
extern Node_manager node_manager;
extern Node_manager* nm_ptr;

void init_nodes(Node_manager*);
void delete_node(Node_manager*, Node*);
Node* new_node(Node_manager*);

#endif
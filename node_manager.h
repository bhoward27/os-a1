#ifndef _NODE_MANAGER_H_
#define _NODE_MANAGER_H_
#include "list.h"

typedef struct Node_manager_s Node_manager;
struct Node_manager_s {
    Node nodes[LIST_MAX_NUM_NODES];
    Node* free_head;
};

extern Node_manager node_manager;
extern Node_manager* nm_ptr;

void init_free_list(Node_manager*);
bool delete_node(Node_manager*, Node*);
Node* new_node(Node_manager*);

#endif
#ifndef _NODE_MANAGER_H_
#define _NODE_MANAGER_H_
#include "list.h"

typedef struct Node_manager_s Node_manager;
struct Node_manager_s {
    Node nodes[LIST_MAX_NUM_NODES];
    Node* free_head;
};

Node_manager node_manager;

#endif
#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>

template <typename T>
struct Node {
    T value;
    Node *next;
};

#endif

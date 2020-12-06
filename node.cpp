// node.cpp
// Author: Tailon Russell
// Date: 12/5/2020.
// The source file for class Node

#include "node.h"
bool operator< (Node lhs, Node rhs) {
    return lhs.priority < rhs.priority;
}

bool operator== (Node lhs, Node rhs) {
    return lhs.value == rhs.value && lhs.priority == rhs.priority;
}

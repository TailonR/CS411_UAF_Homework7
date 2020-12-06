// node.cpp
// Author: Tailon Russell
// Date: 12/5/2020.
// The source file for class Node

#include "node.h"
//operator<
// Returns whether or not the left node has less priority than the right node
//Pre: None
//Post: The returned value will be true if the priority of the left node is less
// than the priority of the right node
//Error: None
bool operator< (Node lhs, Node rhs) {
    return lhs.priority < rhs.priority;
}

//operator==()
// returns true if the two nodes are equal
//Pre: None
//Post: The value returned will be true if the each node's value are equal to each other
// and if each node's priority are equal to each other
//Error: None
bool operator== (Node lhs, Node rhs) {
    return lhs.value == rhs.value && lhs.priority == rhs.priority;
}

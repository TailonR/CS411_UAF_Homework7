// node.h
// Author: Tailon Russell
// Date: 12/5/2020.
// The header file for class Node

#ifndef HOMEWORK7_NODE_H
#define HOMEWORK7_NODE_H

//class Node
// Invariants: None
class Node{
public:
    int value;
    int priority;
};

bool operator< (Node lhs, Node rhs);
bool operator== (Node lhs, Node rhs);
#endif //HOMEWORK7_NODE_H

// binHeap.cpp
// Author: Tailon Russell
// Date: 11/28/2020.
// The source file for class BinHeap

#include "binHeap.h"
#include <stdexcept>

//Default ctor
BinHeap::BinHeap() = default;

//1-param ctor
//Given a vector of ints inserts the items in accordance with the max-heap property
BinHeap::BinHeap(const std::vector<Node> & nodeItems){
    for(auto node: nodeItems)
        insert(node);
}


//insert()
//Given a value, inserts the new value into the binary heap
void BinHeap::insert(const Node & newNode){
    _nodes.push_back(newNode);
    siftUp(std::distance(_nodes.begin(), _nodes.end())-1);
}


//siftUp2()
//Given the index of a child, checks if the child and parent conform to the max-heap property
//  swaps the parent a child if they don't
void BinHeap::siftUp(int childIndex) {
    if (childIndex-1 < 0) {
        return;
    }

    int parentIndex = (childIndex-1)/2;

    // If ">" then we are creating a min-heap
    // If "<" then we are creating a max-heap
    if(_nodes[parentIndex].priority < _nodes[childIndex].priority) {
        std::swap(_nodes[childIndex], _nodes[parentIndex]);
        // The reason for the "+1" will be explained in updatePriority
        _lookup[_nodes[childIndex].value] = childIndex+1;
        _lookup[_nodes[parentIndex].value] = parentIndex+1;
        siftUp(parentIndex);

    }
    _lookup[_nodes[childIndex].value] = childIndex+1;
    _lookup[_nodes[parentIndex].value] = parentIndex+1;

}

//updatePriority()
//Given two ints, replace the value of the node indicated by the first param with the value of the second param
void BinHeap::updatePriority(int nodeValue, int newNodePriority){
    // The reason for the "+1" is due to the fact that at() returns 0 if the key is not in the map
    //      However, the root of the tree is at index 0, therefore there was no way to distinguish the difference
    //          without traversing _lookup each time
    auto nodeIndex = _lookup.at(nodeValue)? _lookup[nodeValue]-1: -1;
    if (nodeIndex != -1) {
        _nodes[nodeIndex].priority = newNodePriority;
    }
    if((nodeIndex-1)/2 > 0 && _nodes[(nodeIndex-1)/2].priority < _nodes[nodeIndex].priority)
        siftUp(nodeIndex);
    else
        siftDown(nodeIndex);
}

//root()
//return the root of the binary heap
std::optional<int> BinHeap::root() {
    if (!_nodes.empty())
        return _nodes[0].value;
    return std::nullopt;
}

//deleteRoot()
//deletes the root
void BinHeap::deleteRoot() {
    auto elementToBeDeleted = _nodes.begin()->value;
    _nodes.erase(_nodes.begin());
    _lookup.erase(elementToBeDeleted);
    heapify();
}

//heapify()
//Traverses the class vector and swaps elements until they conform to the max-heap property
void BinHeap::heapify() {
    for(auto index = _nodes.end(); index != _nodes.begin()-1; index--)
        siftDown(std::distance(index,_nodes.end()));
}

//siftDown()
//Given the index of the parent, checks if the parent and children conform to the max-heap property
//  swaps the parent a child if they don't
void BinHeap::siftDown(int parentIndex) {
    int leftChildIndex = 2*parentIndex+1;
    int rightChildIndex = 2*parentIndex+2;

    // If ">" then we are creating a min-heap
    // If "<" then we are creating a max-heap
    if(leftChildIndex < _nodes.size() && _nodes[parentIndex].priority < _nodes[leftChildIndex].priority) {
        std::swap(_nodes[leftChildIndex], _nodes[parentIndex]);
        // The reason for the "+1" will be explained in updatePriority
        _lookup[_nodes[leftChildIndex].value] = leftChildIndex+1;
        _lookup[_nodes[parentIndex].value] = parentIndex+1;
        siftDown(leftChildIndex);

    }

    if(rightChildIndex < _nodes.size() && _nodes[parentIndex].priority < _nodes[rightChildIndex].priority) {
        std::swap(_nodes[rightChildIndex], _nodes[parentIndex]);
        _lookup[_nodes[rightChildIndex].value] = rightChildIndex+1;
        _lookup[_nodes[parentIndex].value] = parentIndex+1;
        siftDown(rightChildIndex);
    }

    if(rightChildIndex < _nodes.size() && leftChildIndex < _nodes.size()) {
        _lookup[_nodes[leftChildIndex].value] = leftChildIndex+1;
        _lookup[_nodes[rightChildIndex].value] = rightChildIndex+1;
        _lookup[_nodes[parentIndex].value] = parentIndex+1;
    }
}

//getNumOfNodes()
//Returns the size
int BinHeap::getNumOfNodes() {
    return _nodes.size();
}

//height()
//Returns the height of tree
int BinHeap::height() {
    return heightOfTree(0);
}

// heightOfTree()
//finds height of the tree
int BinHeap::heightOfTree(int parentIndex) {
    int leftChildIndex = 2*parentIndex+1;
    int rightChildIndex = 2*parentIndex+2;
    if(leftChildIndex >= _nodes.size() && rightChildIndex >= _nodes.size()) {
        return 0;
    }
    else {
        int leftHeight = heightOfTree(leftChildIndex);
        int rightHeight = heightOfTree(rightChildIndex);
        int heightOfTree = std::max(leftHeight, rightHeight) + 1;
        return heightOfTree;
    }

}

//operator==()
// returns true if the two heaps are equal
bool operator==(const BinHeap & lhs, const BinHeap & rhs) {
    return lhs._nodes == rhs._nodes;
}

//operator<<
// So that the test program can print the heaps when they are not equal
std::ostream& operator<<(std::ostream & output, const BinHeap & rhs){
    for(auto element: rhs._nodes)
        output << element.value << ": " << element.priority << "   ";
    output << "\n";
    return output;
}

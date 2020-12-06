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
//Pre: nodeItems must have size >= 1
//Error: None
BinHeap::BinHeap(const std::vector<Node> & nodeItems){
    for(auto node: nodeItems)
        insert(node);
}


//insert()
//Given a value, inserts the new value into the binary heap
//Pre: None
//Post: _nodes will contain the new node and in the position to maintain the max-heap property
//Error: None
void BinHeap::insert(const Node & newNode){
    _nodes.push_back(newNode);
    siftUp(std::distance(_nodes.begin(), _nodes.end())-1);
}


//siftUp2()
//Given the index of a child, checks if the child and parent conform to the max-heap property
//  swaps the parent a child if they don't
//Pre: None
//Post: _nodes will be sorted based on each element's priority to maintain the max-heap property
// _lookup will be indexed by the value of the node and the index of the node in _nodes
//Error: None
void BinHeap::siftUp(int childIndex) {
    if (childIndex-1 < 0) {
        return;
    }

    int parentIndex = (childIndex-1)/2;

    // If ">" then we are creating a min-heap
    // If "<" then we are creating a max-heap
    if(_nodes[parentIndex].priority < _nodes[childIndex].priority) {
        std::swap(_nodes[childIndex], _nodes[parentIndex]);
        _lookup[_nodes[childIndex].value] = childIndex;
        _lookup[_nodes[parentIndex].value] = parentIndex;
        siftUp(parentIndex);

    }
    _lookup[_nodes[childIndex].value] = childIndex;
    _lookup[_nodes[parentIndex].value] = parentIndex;

}

//updatePriority()
//Given two ints, replace the value of the node indicated by the first param with the value of the second param
//Pre: None
//Post: the node with the given value in _nodes will be assigned the given and in the position that maintains
// the max-heap property
//Error: Strong Guarantee
void BinHeap::updatePriority(int nodeValue, int newNodePriority){
    int nodeIndex;
    try {
       nodeIndex = _lookup.at(nodeValue);
    } catch (...) {
        throw std::out_of_range("The node was not found");
    }
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
//Pre: None
//Post: Returns the value of the root or a nullopt if the tree is empty
//Error: None
std::optional<int> BinHeap::root() {
    if (!_nodes.empty())
        return _nodes[0].value;
    return std::nullopt;
}

//deleteRoot()
//deletes the root
//Pre: None
//Post: _nodes will have one less element and sorted as to maintain the max-heap property
// the element indexed by the value of the first element in _nodes will be deleted from _lookup
//  and the rest of node values will be updated with the correct index
//Error: None
void BinHeap::deleteRoot() {
    auto elementToBeDeleted = _nodes.begin()->value;
    _nodes.erase(_nodes.begin());
    _lookup.erase(elementToBeDeleted);
    heapify();
}

//heapify()
//Traverses the class vector and swaps elements until they conform to the max-heap property
//Pre: None
//Post: _nodes will be sorted as to maintain the max-heap property
//Error: None
void BinHeap::heapify() {
    for(auto index = _nodes.end(); index != _nodes.begin()-1; index--)
        siftDown(std::distance(index,_nodes.end()));
}

//siftDown()
//Given the index of the parent, checks if the parent and children conform to the max-heap property
//  swaps the parent a child if they don't
//Pre: None
//Post: _nodes will be sorted based on each element's priority to maintain the max-heap property
// _lookup will be indexed by the value of the node and the index of the node in _nodes
//Error: None
void BinHeap::siftDown(int parentIndex) {
    int leftChildIndex = 2*parentIndex+1;
    int rightChildIndex = 2*parentIndex+2;

    // If ">" then we are creating a min-heap
    // If "<" then we are creating a max-heap
    if(leftChildIndex < _nodes.size() && _nodes[parentIndex].priority < _nodes[leftChildIndex].priority) {
        std::swap(_nodes[leftChildIndex], _nodes[parentIndex]);
        _lookup[_nodes[leftChildIndex].value] = leftChildIndex;
        _lookup[_nodes[parentIndex].value] = parentIndex;
        siftDown(leftChildIndex);

    }

    if(rightChildIndex < _nodes.size() && _nodes[parentIndex].priority < _nodes[rightChildIndex].priority) {
        std::swap(_nodes[rightChildIndex], _nodes[parentIndex]);
        _lookup[_nodes[rightChildIndex].value] = rightChildIndex;
        _lookup[_nodes[parentIndex].value] = parentIndex;
        siftDown(rightChildIndex);
    }

    if(rightChildIndex < _nodes.size() && leftChildIndex < _nodes.size()) {
        _lookup[_nodes[leftChildIndex].value] = leftChildIndex;
        _lookup[_nodes[rightChildIndex].value] = rightChildIndex;
        _lookup[_nodes[parentIndex].value] = parentIndex;
    }
}

//getNumOfNodes()
//Returns the size
//Pre: None
//Post: The value returned is the size of the _node vector
//Error: None
int BinHeap::getNumOfNodes() {
    return _nodes.size();
}

//height()
//Returns the height of tree
//Pre: None
//Post: The value returned is the height of the tree
//Error: None
int BinHeap::height() {
    return heightOfTree(0);
}

// heightOfTree()
//Finds height of the tree
//Pre: None
//Post: The value returned is the height of each sub-tree
//Error: None
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
//Pre: None
//Post: The value returned will be true if the _nodes vector of each BinHeap is equal
//Error: None
bool operator==(const BinHeap & lhs, const BinHeap & rhs) {
    return lhs._nodes == rhs._nodes;
}

//operator<<
// So that the test program can print the heaps when they are not equal
//Pre: None
//Post: The elements of the binary will be written to the given ostream
//Error: None
std::ostream& operator<<(std::ostream & output, const BinHeap & rhs){
    for(auto element: rhs._nodes)
        output << element.value << ": " << element.priority << "   ";
    output << "\n";
    return output;
}

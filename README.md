# Solution to Homework7 CS411 UAF
The goal is to implement a binary heap data structure with updatePriority functionality.

This project was developed in Clion.
The project consists of four files binHeap.h and node.h, binHeap.cpp, and node.cpp.
The test file is binHeap_test.cpp.

# The Problem
Implement a binary heap with an updatePriority function.

# Usage
Class BinHeap provides 2 constructors and 6 functions.
You can create an empty BinHeap (1) or create a BinHeap based on a given vector (2).
```c++
//1
BinHeap newHeap();
//2
std::vector<Node> data = {Node{1,2}, Node{5,3}};
BinHeap newHeap3(data);
// as of c++11
BinHeap newHeap2({Node{1,2}, Node{5,3}});
```
Note: The order of parameters of Node is the value and then the priority
<br>

You can insert new nodes using the insert function.
```c++
newHeap.insert(Node{7,8});
```
<br/>

You can change the priority of a node by using the updatePriority function
```c++
newHeap.updatePriority(7,4);
```
<br/>

The root function returns the root of the binary heap if the heap is not empty 
and returns a nullopt if the heap is empty
```c++
newHeap.root();
```
<br/>

The deleteRoot function deletes the root of the heap. After this 
function executes there will be a new root.
```c++
newHeap.deleteRoot();
```
<br/>

You can get the number of nodes by using the getNumOfNodes function.
```c++
newHeap.getNumOfNodes();
```
<br/>

You can get the height of the heap by using the height function.
```c++
newHeap.height();
```
# Key Highlights
The update priority function is the key highlight. 
```c++
void BinHeap::updatePriority(int nodeValue, int newNodePriority){
    auto nodeIndex = _lookup.at(nodeValue)? _lookup[nodeValue]-1: -1;
    if (nodeIndex != -1) {
        _nodes[nodeIndex].priority = newNodePriority;
    }
    if((nodeIndex-1)/2 > 0 && _nodes[(nodeIndex-1)/2].priority < _nodes[nodeIndex].priority)
        siftUp(nodeIndex);
    else
        siftDown(nodeIndex);
}
```
The binary heap contains nodes which are represented by the class Node, which has two variables: value and priority.
updatePriority looks for the node with value specified by nodeValue and then changes the priority of that node. It then
checks if the new priority is larger or smaller than it's parent, if it is, the node will be sifted up, if it's not, 
then it will be sifted down. Note: _lookup is an auxiliary map that keeps track of the indices of the various nodes so 
that updatePriority is O(logn) rather than O(n). Each entry in _lookup is indexed by the value of the node.

# License
[MIT](https://choosealicense.com/licenses/mit/)

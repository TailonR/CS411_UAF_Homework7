// binHeap.h
// Author: Tailon Russell
// Date: 11/28/2020.
// The header file for class BinHeap
#ifndef HOMEWORK7_BINHEAP_H
#define HOMEWORK7_BINHEAP_H
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <optional>
#include "node.h"

class BinHeap{
    friend bool operator==(const BinHeap & lhs, const BinHeap & rhs);
    friend std::ostream& operator<<(std::ostream & output, const BinHeap & rhs);
public:
    BinHeap();

    explicit BinHeap(const std::vector<Node> & items);

    void insert(const Node & newNode);

    void updatePriority(int nodeValue, int newNodePriority);

    std::optional<int> root();

    void deleteRoot();

    int getNumOfNodes();

    int height();
private:
    int heightOfTree(int parentIndex);

    void heapify();

    void siftDown(int parentIndex);

    void siftUp(int childIndex);

    std::vector<Node> _nodes;
    std::map<int, int> _lookup;
};
#endif //HOMEWORK7_BINHEAP_H

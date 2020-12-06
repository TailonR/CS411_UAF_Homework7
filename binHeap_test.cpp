// binHeap_test.cpp
// Author: Tailon Russell
// Date: 11/28/20
// The test program for class BinHeap

#include "binHeap.h"   // For class BinHeap
#include "binHeap.h"   // Double inclusion test
#include <vector>
#include "node.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Testing binHeap constructors") {
    BinHeap newHeap;
    std::vector<Node> data = {Node{2, 1},
                              Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    BinHeap newHeap2(data);
    std::cout << newHeap2 << std::endl;
    CHECK(newHeap.getNumOfNodes() == 0);
    CHECK(newHeap2.getNumOfNodes() == data.size());
}

TEST_CASE("Testing height of tree") {
    BinHeap newHeap;
    std::vector<Node> data = {Node{2, 1},
                              Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    BinHeap newHeap2(data);
    CHECK(newHeap.height() == 0);
    CHECK(newHeap2.height() == 3);
}

TEST_CASE("Testing acquiring the root") {
    std::vector<Node> data = {Node{2, 1},
                              Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    std::vector<Node> data2 = {Node{21, 1},
                               Node{70, 3},
                               Node{32, 4},
                               Node{8, 11},
                               Node{9, 30},
                               Node{7, 14},
                               Node{3, 25},
                               Node{27, 27}};
    BinHeap newHeap(data);
    BinHeap newHeap2(data2);
    BinHeap newHeap3;
    CHECK(newHeap.root() == 19);
    CHECK(newHeap2.root() == 9);
    CHECK(newHeap3.root() == std::nullopt);
}

TEST_CASE("Testing operator==") {
    std::vector<Node> data = {Node{2, 1},
                              Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    BinHeap heap(data);
    BinHeap newHeap({Node{2, 1},
                           Node{17, 3},
                           Node{23, 4},
                           Node{1, 11},
                           Node{19, 30},
                           Node{7, 14},
                           Node{8, 25},
                           Node{77, 27}});
    CHECK(heap == heap);
    CHECK(newHeap == newHeap);
}

TEST_CASE("Testing deleting the root") {
    std::vector<Node> data = {Node{2, 1},
                              Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    BinHeap heap(data);
    heap.deleteRoot();
    // This is under the assumption that we are implementing a max-heap
    BinHeap newHeap({Node{77, 27},
                     Node{8, 25},
                     Node{7, 14},
                     Node{23, 4},
                     Node{17, 3},
                     Node{1, 11},
                     Node{2, 1}});
    CHECK(heap == newHeap);
}

TEST_CASE("Testing insert element") {
    std::vector<Node> data = {Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    BinHeap heap(data);
    heap.insert(Node{45, 1});
    BinHeap newHeap({Node{19, 30},
                          Node{7, 14},
                          Node{77, 27},
                          Node{17, 3},
                          Node{1, 11},
                          Node{23, 4},
                          Node{8, 25},
                          Node{45, 1}});
    CHECK(heap == newHeap);
}

TEST_CASE("Testing update priority") {
    std::vector<Node> data = {Node{2, 1},
                              Node{17, 3},
                              Node{23, 4},
                              Node{1, 11},
                              Node{19, 30},
                              Node{7, 14},
                              Node{8, 25},
                              Node{77, 27}};
    BinHeap heap(data);
    BinHeap heap2(data);

    heap.updatePriority(77, 2);
    BinHeap newHeap({Node{19, 30},
                     Node{1, 11},
                     Node{8, 25},
                     Node{77, 2},
                     Node{23, 4},
                     Node{17, 3},
                     Node{7, 14},
                     Node{2, 1}});
    CHECK(heap == newHeap);
    heap2.updatePriority(19, 10);
    BinHeap newHeap2({Node{77, 27},
                      Node{1, 11},
                      Node{8, 25},
                      Node{19, 10},
                      Node{23, 4},
                      Node{17, 3},
                      Node{7, 14},
                      Node{2, 1}});

    CHECK(heap2 == newHeap2);

}

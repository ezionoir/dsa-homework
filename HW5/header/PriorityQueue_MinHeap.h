#ifndef PRIORITY_QUEUE_MIN_HEAP_H
#define PRIORITY_QUEUE_MIN_HEAP_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct HeapNode {
    string ID;
    int priority;   // The lower priority value, the higher priority of node
    int order;      // Node's order = k <=> it is the k-th node in queue (by time added)
};

typedef vector<HeapNode> Heap;  // Use a vector as container for heap, since it's easy to update the order when removing a node

bool isEmpty(Heap q);
HeapNode getHeapNode(string ID, int priority);
void shiftUp(Heap &q, int i);
void shiftDown(Heap& q, int i);
void Insert(Heap &q, string ID, int priority);
HeapNode Extract(Heap &q);
bool Remove(Heap &q, string ID);
bool changePriority(Heap &q, string ID, int newPriority);
void Print(Heap q);


#endif
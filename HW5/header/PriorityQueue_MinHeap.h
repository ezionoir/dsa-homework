#ifndef PRIORITY_QUEUE_MIN_HEAP_H
#define PRIORITY_QUEUE_MIN_HEAP_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct HeapNode {
    string ID;
    int priority;
    int order;
};

typedef vector<HeapNode> Heap;

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
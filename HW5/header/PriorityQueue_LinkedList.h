#ifndef PRIORITY_QUEUE_LINKED_LIST_H
#define PRIORITY_QUEUE_LINKED_LIST_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    string ID;
    int order;
    int priority;
    Node* next;
};

struct Queue {
    Node* head; // dummy head
    int nNode;
};

bool isEmpty(Queue q);
Node* getNode(const string ID, int priority);
Node* Insert(Queue &q, const string ID, int priority);
Node* Extract(Queue &q);
bool Remove(Queue &q, const string ID);
Node* changePriority(Queue &q, const string ID, int newPriority);
void Print(Queue q);
void Delete(Queue &q);

#endif
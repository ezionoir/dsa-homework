#ifndef PRIORITY_QUEUE_LINKED_LIST_H
#define PRIORITY_QUEUE_LINKED_LIST_H

#include <iostream>
#include <string>

using namespace std;

struct ListNode {
    string ID;
    int order;
    int priority;
    ListNode* next;
};

struct Queue {
    ListNode* head; // dummy head
    int nNode;
};

bool isEmpty(Queue q);
ListNode* getListNode(const string ID, int priority);
ListNode* Insert(Queue &q, const string ID, int priority);
ListNode* Extract(Queue &q);
bool Remove(Queue &q, const string ID);
ListNode* changePriority(Queue &q, const string ID, int newPriority);
void Print(Queue q);
void Delete(Queue &q);

#endif
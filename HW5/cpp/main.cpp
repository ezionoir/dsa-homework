#include "../header/PriorityQueue_LinkedList.h"
#include "../header/PriorityQueue_MinHeap.h"

int main() {
    // Queue q;
    // q.head = getListNode("", 0);
    // q.nNode = 0;

    // Insert(q, "a", 7);
    // Insert(q, "b", 1);
    // Insert(q, "c", 3);
    // Insert(q, "d", 2);
    // Insert(q, "e", 10);
    // Insert(q, "f", 1);
    // Insert(q, "g", 1);
    // Print(q);

    // ListNode* p;
    // p = Extract(q);
    // cout << p->ID << endl;
    // delete p;

    // p = Extract(q);
    // cout << p->ID << endl;
    // delete p;

    // p = Extract(q);
    // cout << p->ID << endl;
    // delete p;

    // Remove(q, "a");

    // p = Extract(q);
    // cout << p->ID << endl;
    // delete p;

    // Remove(q, "b");
    // Remove(q, "c");

    // p = Extract(q);
    // cout << p->ID << endl;
    // delete p;

    // Print(q);

    // Delete(q);
    // cout << "Deleted " << q.head << endl;    Queue q;

    Heap q;
    q.clear();

    Insert(q, "a", 7);
    Insert(q, "b", 1);
    Insert(q, "c", 3);
    Insert(q, "d", 2);
    Insert(q, "e", 10);
    Insert(q, "f", 1);
    Insert(q, "g", 1);
    Print(q);

    HeapNode p;
    p = Extract(q);
    cout << p.ID << endl;
    Print(q);

    p = Extract(q);
    cout << p.ID << endl;
    Print(q);

    p = Extract(q);
    cout << p.ID << endl;
    Print(q);

    Remove(q, "a");
    Print(q);

    p = Extract(q);
    cout << p.ID << endl;
    Print(q);

    Remove(q, "b");
    Remove(q, "c");
    Print(q);

    p = Extract(q);
    cout << p.ID << endl;
    Print(q);


    return 0;
}
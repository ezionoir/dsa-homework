#include "../header/PriorityQueue_LinkedList.h"

int main() {
    Queue q;
    q.head = getNode("", 0);
    q.nNode = 0;

    Insert(q, "a", 7);
    Insert(q, "b", 1);
    Insert(q, "c", 3);
    Insert(q, "d", 2);
    Insert(q, "e", 10);
    Insert(q, "f", 1);
    Insert(q, "g", 1);
    Print(q);

    Node* p;
    p = Extract(q);
    cout << p->ID << endl;
    delete p;

    p = Extract(q);
    cout << p->ID << endl;
    delete p;

    p = Extract(q);
    cout << p->ID << endl;
    delete p;

    Remove(q, "a");

    p = Extract(q);
    cout << p->ID << endl;
    delete p;

    Remove(q, "b");
    Remove(q, "c");

    p = Extract(q);
    cout << p->ID << endl;
    delete p;

    Print(q);

    Delete(q);
    cout << "Deleted " << q.head << endl;

    return 0;
}
#include "../header/PriorityQueue_LinkedList.h"

bool isEmpty(Queue q) {
    return (q.nNode == 0);
}

ListNode* getListNode(const string ID, int priority) {
    ListNode* p = new ListNode;

    p->ID = ID;
    p->order = 0;
    p->priority = priority;
    p->next = nullptr;

    return p;
}

ListNode* Insert(Queue &q, const string ID, int priority) {
    ListNode* p = getListNode(ID, priority);
    p->order = ++(q.nNode);
    
    ListNode* p1 = q.head;
    ListNode* p2 = p1->next;
    while ((p2 != nullptr) && (p->priority > p2->priority)) {
        p1 = p2;
        p2 = p2->next;
    }

    p1->next = p;
    p->next = p2;

    return p;
}

ListNode* Extract(Queue &q) {
    if (isEmpty(q)) return nullptr;

    ListNode* p = q.head->next;
    q.head->next = p->next;
    p->next = nullptr;

    int order = p->order;
    for (ListNode* r = q.head->next; r != nullptr; r = r->next)
        if (r->order > order) --(r->order);
    --(q.nNode);

    return p;
}

bool Remove(Queue &q, const string ID) {
    ListNode* p1 = q.head;
    ListNode* p2 = p1->next;

    while ((p2 != nullptr) && (p2->ID.compare(ID) != 0)) {
        p1 = p2;
        p2 = p2->next;
    }

    if (p2 != nullptr) {
        int order = p2->order;
        p1->next = p2->next;
        delete p2;

        // Update the order
        for (ListNode* p = q.head->next; p != nullptr; p = p->next)
            if (p->order > order) --(p->order);
        --(q.nNode);

        return true;
    }

    return false;
}

ListNode* changePriority(Queue &q, const string ID, int newPriority) {
    ListNode* p1 = q.head;
    ListNode* p2 = p1->next;

    while ((p2 != nullptr) && (p2->ID.compare(ID) != 0)) {
        p1 = p2;
        p2 = p2->next;
    }

    if (p2 == nullptr) return nullptr;
    
    ListNode* updateNode = p2;
    ListNode *r1, *r2;
    if (newPriority > updateNode->priority) {
        //  ...     p1  --> updateNode  --> updateNode->next    ...
        //  ...     r1  --> updateNode  --> r2                  ...
        r1 = p1;
        r2 = updateNode->next;
    }
    else {
        r1 = q.head;
        r2 = r1->next;
    }

    p1->next = updateNode->next;
    updateNode->priority = newPriority;
    while ((r2 != nullptr) && (updateNode->priority > r2->priority)) {
        r1 = r2;
        r2 = r2->next;
    }

    r1->next = updateNode;
    updateNode->next = r2;

    return updateNode;
}

void Print(Queue q) {
    if (isEmpty(q)) {
        cout << "Queue is empty!" << endl;
        return;
    }

    for (ListNode* p = q.head->next; p != nullptr; p = p->next)
        cout << "(\"" << p->ID << "\", " << p->priority << ", " << p->order << ") --> ";
    cout << "(x)" << endl;
}

void Delete(Queue &q) {
    ListNode* temp;
    while (q.head != nullptr) {
        temp = q.head;
        q.head = q.head->next;
        delete temp;
    }

    q.head = nullptr;
    q.nNode = 0;
}
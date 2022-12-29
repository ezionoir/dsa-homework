#include "../header/PriorityQueue_MinHeap.h"

bool isEmpty(Heap q) {
    return (q.empty());
}

// Create a node with given ID and priority
HeapNode getHeapNode(string ID, int priority) {
    HeapNode hn;
    hn.ID = ID;
    hn.priority = priority;
    hn.order = 0;

    return hn;
}

// Check in upward direction. If a node has smaller priority than its parent, shift it up
void shiftUp(Heap &q, int i) {
    if ((i < 0) || (i >= q.size())) return;

    int parent = (i - 1) / 2;
    if ((parent >= 0) && (q[parent].priority > q[i].priority)) {
        swap(q[parent], q[i]);
        shiftUp(q, parent);
    }
}

// Check in downward direction. If a node is not smaller than both its children, shift it down
void shiftDown(Heap& q, int i) {
    if ((i < 0) || (i >= q.size())) return;
    
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int max = i;
    if ((left < q.size()) && (q[left].priority < q[max].priority))
        max = left;
    if ((right < q.size()) && (q[right].priority < q[max].priority))
        max = right;

    if (max != i) {
        swap(q[i], q[max]);
        shiftDown(q, max);
    }
}

void Insert(Heap &q, string ID, int priority) {
    // Append the new node to the vector
    q.push_back(getHeapNode(ID, priority));
    q[q.size() - 1].order = q.size();
    // Shift up the new node
    shiftUp(q, q.size() - 1);
}

HeapNode Extract(Heap &q) {
    if (isEmpty(q)) return getHeapNode("", 0);

    // Swap the top of heap with the last, then pop it out
    HeapNode rtn = q[0];
    swap(q[0], q[q.size() - 1]);
    q.pop_back();
    // Shift down the new top
    shiftDown(q, 0);

    // Update the order (if a node's order is greater than removed node's order, decrease it by 1)
    int order = rtn.order;
    for (int i = 0; i < q.size(); ++i)
        if (q[i].order > order) --(q[i].order);

    return rtn;
}

bool Remove(Heap &q, string ID) {
    int i = 0;
    for (; i < q.size(); ++i)
        if (q[i].ID.compare(ID) == 0) break;
    
    if (i == q.size()) return false;
    
    // Swap the current node with the last, then pop it out
    swap(q[i], q[q.size() - 1]);
    int order = q[q.size() - 1].order;
    q.pop_back();

    // Update the order (if a node's order is greater than removed node's order, decrease it by 1)
    for (int j = 0; j < q.size(); ++j)
        if (q[j].order > order) --(q[j].order);

    // Update the node
    int parent = (i - 1) / 2;
    if (parent > 0 && q[i].priority < q[parent].priority)
        shiftUp(q, i);
    else
        shiftDown(q, i);

    return true;
}

bool changePriority(Heap &q, string ID, int newPriority) {
    int i = 0;
    for (; i < q.size(); ++i)
        if (q[i].ID.compare(ID) == 0) break;

    if (i == q.size()) return false;
    if (q[i].priority == newPriority) return false;

    if (newPriority < q[i].priority) {
        q[i].priority = newPriority;
        shiftUp(q, i);
    }
    else {
        q[i].priority = newPriority;
        shiftDown(q, i);
    }

    return true;
}

// Format: (ID, priority, order)
void Print(Heap q) {
    if (isEmpty(q)) {
        cout << "Queue is empty!" << endl;
        return;
    }
    for (int i = 0; i < q.size(); ++i)
        cout << "(\"" << q[i].ID << "\", " << q[i].priority << ", " << q[i].order << ") ";
    cout << endl;
}
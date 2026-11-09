#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};

Node* mergeLists(vector<Node*>& lists) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != NULL) {
            minHeap.push(lists[i]);
        }
    }

    Node* head = NULL;
    Node* tail = NULL;

    while (!minHeap.empty()) {
        Node* smallest = minHeap.top();
        minHeap.pop();

        Node* nextNode = smallest->next;

        if (head == NULL) {
            head = smallest;
            tail = smallest;
        }
        else {
            tail->next = smallest;
            tail = smallest;
        }

        if (nextNode != NULL) {
            minHeap.push(nextNode);
        }
    }

    if (tail != NULL) {
        tail->next = NULL;
    }

    return head;
}

void display(Node* head) {
    while (head != NULL) {
        cout << head->data;

        if (head->next != NULL)
            cout << " -> ";

        head = head->next;
    }
    cout << endl;
}

int main() {
    int k;

    cout << "Enter number of linked lists: ";
    cin >> k;

    vector<Node*> lists(k);

    for (int i = 0; i < k; i++) {
        int n, value;
        Node* head = NULL;
        Node* tail = NULL;

        cout << "Enter size of list " << i + 1 << ": ";
        cin >> n;

        cout << "Enter sorted elements: ";

        for (int j = 0; j < n; j++) {
            cin >> value;

            Node* newNode = new Node(value);

            if (head == NULL) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        lists[i] = head;
    }

    Node* result = mergeLists(lists);

    cout << "\nMerged Linked List:\n";
    display(result);

    return 0;
}


#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string code) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        cout << root->ch << " : ";
        cout << (code == "" ? "0" : code) << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void preorder(Node* root) {
    if (root == NULL)
        return;

    cout << root->freq << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;

        cout << "Enter character and frequency: ";
        cin >> ch >> freq;

        minHeap.push(new Node(ch, freq));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* parent = new Node('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    Node* root = minHeap.top();

    cout << "\nHuffman Codes:\n";
    printCodes(root, "");

    cout << "\nPreorder Traversal:\n";
    preorder(root);

    return 0;
}

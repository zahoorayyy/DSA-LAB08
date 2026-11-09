#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int height(Node* root) {
    if (root == NULL)
        return 0;

    return root->height;
}

int getBalance(Node* root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + maxValue(height(y->left), height(y->right));
    x->height = 1 + maxValue(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + maxValue(height(x->left), height(x->right));
    y->height = 1 + maxValue(height(y->left), height(y->right));

    return y;
}

Node* insert(Node* root, int key) {
    if (root == NULL)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = 1 + maxValue(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* minimumNode(Node* root) {
    Node* current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            if (temp == NULL) {
                delete root;
                return NULL;
            }
            else {
                Node* oldRoot = root;
                root = temp;
                delete oldRoot;
            }
        }
        else {
            Node* temp = minimumNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + maxValue(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node* root) {
    if (root == NULL)
        return;

    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void topMaximum(Node* root, vector<int>& result, int k) {
    if (root == NULL || result.size() == k)
        return;

    topMaximum(root->right, result, k);

    if (result.size() < k)
        result.push_back(root->key);

    topMaximum(root->left, result, k);
}

void topMinimum(Node* root, vector<int>& result, int k) {
    if (root == NULL || result.size() == k)
        return;

    topMinimum(root->left, result, k);

    if (result.size() < k)
        result.push_back(root->key);

    topMinimum(root->right, result, k);
}

int main() {
    Node* root = NULL;
    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter value: ";
        cin >> value;

        root = insert(root, value);

        cout << "AVL Tree after insertion: ";
        preorder(root);
        cout << endl;
    }

    int choice, k;

    cout << "\nChoose criteria:\n";
    cout << "1. Maximum elements\n";
    cout << "2. Minimum elements\n";
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter K: ";
    cin >> k;

    vector<int> result;

    if (choice == 1)
        topMaximum(root, result, k);
    else if (choice == 2)
        topMinimum(root, result, k);
    else {
        cout << "Invalid choice!";
        return 0;
    }

    cout << "\nTop K elements: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    cout << "\n\nDeleting Top K elements:\n";

    for (int i = 0; i < result.size(); i++) {
        root = deleteNode(root, result[i]);

        cout << "Tree after deleting " << result[i] << ": ";
        preorder(root);
        cout << endl;
    }

    return 0;
}

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
        height = 1;   // new node starts at height 1
    }
};

// --------------------
// Get Height
// --------------------
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// --------------------
// Get Balance Factor
// BF = height(left) - height(right)
// --------------------
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// ==================================================
// RIGHT ROTATION (LL CASE)
// ==================================================
/*
    BEFORE (LL Case):

            z
           /
          y
         /
        x

    AFTER Right Rotation:

            y
           / \
          x   z
*/
Node* rightRotate(Node* z) {
    Node* y = z->left;
    Node* T2 = y->right;

    // Rotation
    y->right = z;
    z->left = T2;

    // Update heights
    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;   // new root
}

// ==================================================
// LEFT ROTATION (RR CASE)
// ==================================================
/*
    BEFORE (RR Case):

        z
         \
          y
           \
            x

    AFTER Left Rotation:

            y
           / \
          z   x
*/
Node* leftRotate(Node* z) {
    Node* y = z->right;
    Node* T2 = y->left;

    // Rotation
    y->left = z;
    z->right = T2;

    // Update heights
    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;   // new root
}

// ==================================================
// AVL INSERTION (handles all 4 cases)
// ==================================================
Node* insert(Node* node, int key) {

    // Normal BST insertion
    if (node == NULL)
        return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;   // no duplicates

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // ==================================================
    // LL CASE
    // Insertion in LEFT subtree of LEFT child
    //
    //        z
    //       /
    //      y
    //     /
    //    x
    // ==================================================
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // ==================================================
    // RR CASE
    // Insertion in RIGHT subtree of RIGHT child
    //
    //    z
    //     \
    //      y
    //       \
    //        x
    // ==================================================
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // ==================================================
    // LR CASE
    // Insertion in RIGHT subtree of LEFT child
    //
    //        z
    //       /
    //      y
    //       \
    //        x
    //
    // Step 1: Left Rotate y
    // Step 2: Right Rotate z
    // ==================================================
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // ==================================================
    // RL CASE
    // Insertion in LEFT subtree of RIGHT child
    //
    //    z
    //     \
    //      y
    //     /
    //    x
    //
    // Step 1: Right Rotate y
    // Step 2: Left Rotate z
    // ==================================================
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// --------------------
// Inorder Traversal
// --------------------
void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// --------------------
// Main Function
// --------------------
int main() {
    Node* root = NULL;

    // Try these insertions to trigger rotations:
    // LL Case: 30, 20, 10
    // RR Case: 10, 20, 30
    // LR Case: 30, 10, 20
    // RL Case: 10, 30, 20

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder Traversal of AVL Tree: ";
    inorder(root);

    return 0;
}




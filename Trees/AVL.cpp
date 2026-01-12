#include <iostream>
using namespace std;

// ==================================================
// AVL TREE NODE DEFINITION
// ==================================================
struct Node {
    int data;          // Value stored in the node
    Node* left;        // Pointer to left child
    Node* right;       // Pointer to right child
    int height;        // Height of the node

    // Constructor
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
        height = 1;    // New node is always added as a leaf
    }
};

// ==================================================
// FUNCTION: Get height of a node
// ==================================================
// If node is NULL → height = 0
// Otherwise → return stored height
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// ==================================================
// FUNCTION: Get Balance Factor
// ==================================================
// Balance Factor = height(left subtree) - height(right subtree)
// Valid AVL range: -1, 0, +1
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// ==================================================
// RIGHT ROTATION
// Applied to FIX an LL CASE
//
// LL CASE (Insertion-path diagram):
// Insertion occurs in the LEFT subtree of the LEFT child
//
//        z
//       /
//      y
//     /
//    x
//
// Rotation-pointer view (what the code handles):
//   z → unbalanced node
//   y → left child of z        (y = z->left)
//   x → right subtree of y    (x = y->right)
//
// BEFORE rotation (pointer structure):
//
//            z
//           /
//          y
//           \
//            x
//
// AFTER rotation:
//
//            y
//           / \
//     y->left   z
//              /
//             x
//
// Pointer updates:
//   y->right = z
//   z->left  = x
// ==================================================
Node* rightRotate(Node* z) {
    Node* y = z->left;      // Left child of z
    Node* x = y->right;    // Right subtree of y

    //Rotating:

    y->right = z;
    z->left = x;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// ==================================================
// LEFT ROTATION
// Applied to FIX an RR CASE
//
// RR CASE (Insertion-path diagram):
// Insertion occurs in the RIGHT subtree of the RIGHT child
//
//    z
//     \
//      y
//       \
//        x
//
// Rotation-pointer view (what the code handles):
//   z → unbalanced node
//   y → right child of z       (y = z->right)
//   x → left subtree of y     (x = y->left)
//
// BEFORE rotation (pointer structure):
//
//        z
//         \
//          y
//         /
//        x
//
// AFTER rotation:
//
//            y
//           / \
//          z   y->right
//           \
//            x
//
// Pointer updates:
//   y->left  = z
//   z->right = x
// ==================================================
Node* leftRotate(Node* z) {
    Node* y = z->right;     // Right child of z
    Node* x = y->left;     // Left subtree of y

    y->left = z;
    z->right = x;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


// ==================================================
// AVL INSERT FUNCTION
// ==================================================
// 1. Perform normal BST insertion
// 2. Update height of current node
// 3. Check balance factor
// 4. Apply rotations if needed
Node* insert(Node* node, int key) {

    // ---------- BST INSERT ----------
    if (node == NULL)
        return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;   // Duplicate keys not allowed

    // ---------- UPDATE HEIGHT ----------
    node->height = 1 + max(height(node->left), height(node->right));

    // ---------- CHECK BALANCE ----------
    int balance = getBalance(node);

    // ==================================================
    // LL CASE
    // Left-heavy and insertion in left subtree of left child
    // ==================================================
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // ==================================================
    // RR CASE
    // Right-heavy and insertion in right subtree of right child
    // ==================================================
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // ==================================================
    // LR CASE
    // Left-heavy and insertion in right subtree of left child
    //
    // Step 1: Left rotate left child
    // Step 2: Right rotate node
    // ==================================================
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // ==================================================
    // RL CASE
    // Right-heavy and insertion in left subtree of right child
    //
    // Step 1: Right rotate right child
    // Step 2: Left rotate node
    // ==================================================
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Node is balanced
    return node;
}

// ==================================================
// INORDER TRAVERSAL
// ==================================================
// Left → Root → Right
// Always prints sorted order in AVL tree
void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// ==================================================
// MAIN FUNCTION
// ==================================================
int main() {
    Node* root = NULL;

    // Insertions chosen to trigger multiple rotations
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

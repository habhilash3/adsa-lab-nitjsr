#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Utility: Get max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Utility: Get height of a node
int height(Node* n) {
    return (n == NULL) ? 0 : n->height;
}

// Create new node
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Function 1: Create Tree (returns NULL initially)
Node* createTree() {
    return NULL;
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

// Get balance factor of node
int getBalance(Node* n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

// Function 2: Insert Item into AVL tree
Node* insertItem(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else
        return node; // Duplicates not allowed

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // Balancing cases
    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Unchanged
}

// Utility: Get minimum value node
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function 3: Delete Item from AVL tree
Node* deleteItem(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            // Node with two children
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Balance
    int balance = getBalance(root);

    // Balancing cases
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function 4: Search Item
Node* searchItem(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchItem(root->left, key);
    else
        return searchItem(root->right, key);
}

// Function 5: Delete Tree (Free memory)
void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Utility: Inorder Traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Driver code
int main() {
    Node* root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("Inorder traversal of AVL tree: ");
    inorder(root);
    printf("\n");

    root = deleteItem(root, 40);
    printf("After deleting 40: ");
    inorder(root);
    printf("\n");

    Node* found = searchItem(root, 25);
    if (found != NULL)
        printf("Found key: %d\n", found->key);
    else
        printf("Key not found\n");

    deleteTree(root); // Free memory
    return 0;
}

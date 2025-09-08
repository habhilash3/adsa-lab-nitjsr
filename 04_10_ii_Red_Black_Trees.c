#include <stdio.h>
#include <stdlib.h>

// Node colors
#define RED 0
#define BLACK 1

// Red-Black Tree Node
typedef struct Node {
    int key;
    int color;
    struct Node* left, *right, *parent;
} Node;

// Root of the Red-Black Tree
Node* root = NULL;

// Utility: Create a new node
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;   // New nodes are always red initially
    node->left = node->right = node->parent = NULL;
    return node;
}

// Function 1: Create Tree
Node* createTree() {
    return NULL;
}

// Utility: Left Rotate
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Utility: Right Rotate
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL) x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix violations after insertion
void fixInsert(Node** root, Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2 & 3: Uncle is black
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2 & 3: Uncle is black
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; // Root is always black
}

// Function 2: Insert Item
void insertItem(Node** root, int key) {
    Node* z = createNode(key);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == NULL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    fixInsert(root, z);
}

// Utility: Transplant
void transplant(Node** root, Node* u, Node* v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// Utility: Minimum Node
Node* minValueNode(Node* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

// Fix violations after deletion
void fixDelete(Node** root, Node* x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL) w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL) w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL) x->color = BLACK;
}

// Function 3: Delete Item
void deleteItem(Node** root, int key) {
    Node* z = *root;
    Node* x, *y;

    while (z != NULL && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }

    if (z == NULL) return; // Key not found

    y = z;
    int yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);
    if (yOriginalColor == BLACK && x != NULL)
        fixDelete(root, x);
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
        printf("%d(%s) ", root->key, (root->color == RED) ? "R" : "B");
        inorder(root->right);
    }
}

// Driver code
int main() {
    root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 30);
    insertItem(&root, 15);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    deleteItem(&root, 20);
    printf("After deleting 20: ");
    inorder(root);
    printf("\n");

    Node* found = searchItem(root, 15);
    if (found != NULL)
        printf("Found key: %d\n", found->key);
    else
        printf("Key not found\n");

    deleteTree(root);
    return 0;
}

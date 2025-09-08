#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define minimum degree of B-Tree
#define T 3   // Can change (T=3 means max 5 keys per node)

// Node structure
typedef struct BTreeNode {
    int keys[2*T-1];           // Array of keys
    struct BTreeNode* children[2*T]; // Child pointers
    int n;                     // Current number of keys
    bool leaf;                 // Is true if leaf
} BTreeNode;

// Function to create a new node
BTreeNode* createNode(bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

// Function 1: Create Tree
BTreeNode* createTree() {
    return createNode(true); // Initially root is a leaf
}

// Search key in B-Tree
BTreeNode* searchItem(BTreeNode* root, int key, int* index) {
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;

    if (i < root->n && key == root->keys[i]) {
        *index = i;
        return root;
    }

    if (root->leaf)
        return NULL;

    return searchItem(root->children[i], key, index);
}

// Utility: Split child
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T-1; j++)
        z->keys[j] = y->keys[j+T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j+T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= i+1; j--)
        parent->children[j+1] = parent->children[j];

    parent->children[i+1] = z;

    for (int j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    parent->keys[i] = y->keys[T-1];
    parent->n += 1;
}

// Insert non-full
void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n += 1;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;

        if (node->children[i]->n == 2*T-1) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// Function 2: Insert Item
void insertItem(BTreeNode** root, int key) {
    BTreeNode* r = *root;
    if (r->n == 2*T-1) {
        BTreeNode* s = createNode(false);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, key);
    } else {
        insertNonFull(r, key);
    }
}

// Utility: Get predecessor
int getPred(BTreeNode* node, int idx) {
    BTreeNode* cur = node->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n-1];
}

// Utility: Get successor
int getSucc(BTreeNode* node, int idx) {
    BTreeNode* cur = node->children[idx+1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

// Merge children
void merge(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx+1];

    child->keys[T-1] = node->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i+T] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->children[i+T] = sibling->children[i];
    }

    for (int i = idx+1; i < node->n; i++)
        node->keys[i-1] = node->keys[i];
    for (int i = idx+2; i <= node->n; i++)
        node->children[i-1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}

// Borrow from previous sibling
void borrowFromPrev(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx-1];

    for (int i = child->n-1; i >= 0; i--)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->children[i+1] = child->children[i];
    }

    child->keys[0] = node->keys[idx-1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    node->keys[idx-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;
}

// Borrow from next sibling
void borrowFromNext(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx+1];

    child->keys[child->n] = node->keys[idx];
    if (!child->leaf)
        child->children[child->n+1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i-1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->children[i-1] = sibling->children[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// Delete from node
void deleteFromNode(BTreeNode* node, int key);

// Ensure child has at least T keys
void fill(BTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx-1]->n >= T)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->children[idx+1]->n >= T)
        borrowFromNext(node, idx);
    else {
        if (idx != node->n)
            merge(node, idx);
        else
            merge(node, idx-1);
    }
}

// Delete key
void deleteFromNode(BTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < key)
        idx++;

    if (idx < node->n && node->keys[idx] == key) {
        if (node->leaf) {
            for (int i = idx+1; i < node->n; i++)
                node->keys[i-1] = node->keys[i];
            node->n--;
        } else {
            if (node->children[idx]->n >= T) {
                int pred = getPred(node, idx);
                node->keys[idx] = pred;
                deleteFromNode(node->children[idx], pred);
            } else if (node->children[idx+1]->n >= T) {
                int succ = getSucc(node, idx);
                node->keys[idx] = succ;
                deleteFromNode(node->children[idx+1], succ);
            } else {
                merge(node, idx);
                deleteFromNode(node->children[idx], key);
            }
        }
    } else {
        if (node->leaf) return;

        bool flag = (idx == node->n);

        if (node->children[idx]->n < T)
            fill(node, idx);

        if (flag && idx > node->n)
            deleteFromNode(node->children[idx-1], key);
        else
            deleteFromNode(node->children[idx], key);
    }
}

// Function 3: Delete Item
void deleteItem(BTreeNode** root, int key) {
    if (*root == NULL) return;

    deleteFromNode(*root, key);

    if ((*root)->n == 0) {
        BTreeNode* tmp = *root;
        if ((*root)->leaf)
            *root = NULL;
        else
            *root = (*root)->children[0];
        free(tmp);
    }
}

// Function 4: Delete Tree
void deleteTree(BTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

// Utility: Traverse inorder
void traverse(BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf) traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) traverse(root->children[i]);
    }
}

// Driver code
int main() {
    BTreeNode* root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 5);
    insertItem(&root, 6);
    insertItem(&root, 12);
    insertItem(&root, 30);
    insertItem(&root, 7);
    insertItem(&root, 17);

    printf("Traversal of tree: ");
    traverse(root);
    printf("\n");

    deleteItem(&root, 6);
    printf("After deleting 6: ");
    traverse(root);
    printf("\n");

    int index;
    BTreeNode* found = searchItem(root, 12, &index);
    if (found != NULL)
        printf("Found key: %d\n", found->keys[index]);
    else
        printf("Key not found\n");

    deleteTree(root);
    return 0;
}

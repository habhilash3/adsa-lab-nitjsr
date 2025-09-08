#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3   // Minimum degree (B+ Tree order)

// Node structure
typedef struct BPTreeNode {
    int keys[2*T];                   // Keys
    struct BPTreeNode* children[2*T+1]; // Pointers
    int n;                           // Number of keys
    bool leaf;                       // Is leaf
    struct BPTreeNode* next;         // Next leaf (for range queries)
} BPTreeNode;

// Function to create a new node
BPTreeNode* createNode(bool leaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->leaf = leaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i <= 2*T; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Function 1: Create Tree
BPTreeNode* createTree() {
    return createNode(true);  // Start with empty leaf root
}

// Search a key
BPTreeNode* searchItem(BPTreeNode* root, int key, int* index) {
    if (root == NULL) return NULL;
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;
    if (root->leaf) {
        if (i < root->n && key == root->keys[i]) {
            *index = i;
            return root;
        }
        return NULL;
    }
    return searchItem(root->children[i], key, index);
}

// Split child during insertion
void splitChild(BPTreeNode* parent, int i, BPTreeNode* y) {
    BPTreeNode* z = createNode(y->leaf);
    int mid = y->n / 2;

    // For leaf node
    if (y->leaf) {
        z->n = y->n - mid;
        for (int j = 0; j < z->n; j++)
            z->keys[j] = y->keys[mid + j];
        y->n = mid;

        z->next = y->next;
        y->next = z;

        for (int j = parent->n; j >= i+1; j--)
            parent->children[j+1] = parent->children[j];
        parent->children[i+1] = z;

        for (int j = parent->n; j >= i; j--)
            parent->keys[j+1] = parent->keys[j];
        parent->keys[i] = z->keys[0];
        parent->n++;
    }
    else { // For internal node
        z->n = y->n - mid - 1;
        for (int j = 0; j < z->n; j++)
            z->keys[j] = y->keys[mid + 1 + j];
        for (int j = 0; j <= z->n; j++)
            z->children[j] = y->children[mid + 1 + j];
        y->n = mid;

        for (int j = parent->n; j >= i+1; j--)
            parent->children[j+1] = parent->children[j];
        parent->children[i+1] = z;

        for (int j = parent->n-1; j >= i; j--)
            parent->keys[j+1] = parent->keys[j];
        parent->keys[i] = y->keys[mid];
        parent->n++;
    }
}

// Insert non-full
void insertNonFull(BPTreeNode* node, int key) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->n == 2*T) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// Function 2: Insert Item
void insertItem(BPTreeNode** root, int key) {
    BPTreeNode* r = *root;
    if (r->n == 2*T) {
        BPTreeNode* s = createNode(false);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, key);
    } else {
        insertNonFull(r, key);
    }
}

// Function 3: Delete Item (simplified: only leaf deletion, no rebalance)
void deleteItem(BPTreeNode* root, int key) {
    if (root == NULL) return;
    if (root->leaf) {
        int i;
        for (i = 0; i < root->n && root->keys[i] != key; i++);
        if (i == root->n) return;
        for (; i < root->n - 1; i++)
            root->keys[i] = root->keys[i+1];
        root->n--;
    } else {
        int i = 0;
        while (i < root->n && key > root->keys[i])
            i++;
        deleteItem(root->children[i], key);
    }
}

// Function 4: Delete Tree
void deleteTree(BPTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

// Utility: Traverse leaf level (in order)
void traverseLeaves(BPTreeNode* root) {
    if (root == NULL) return;
    while (!root->leaf)
        root = root->children[0];
    BPTreeNode* curr = root;
    while (curr != NULL) {
        for (int i = 0; i < curr->n; i++)
            printf("%d ", curr->keys[i]);
        curr = curr->next;
    }
    printf("\n");
}

// Driver code
int main() {
    BPTreeNode* root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 5);
    insertItem(&root, 6);
    insertItem(&root, 12);
    insertItem(&root, 30);
    insertItem(&root, 7);
    insertItem(&root, 17);

    printf("Traversal of leaf nodes: ");
    traverseLeaves(root);

    int index;
    BPTreeNode* found = searchItem(root, 12, &index);
    if (found != NULL)
        printf("Found key: %d\n", found->keys[index]);
    else
        printf("Key not found\n");

    deleteItem(root, 6);
    printf("After deleting 6: ");
    traverseLeaves(root);

    deleteTree(root);
    return 0;
}

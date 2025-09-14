#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3  

struct BPTreeNode {
    int keys[ORDER];
    struct BPTreeNode* children[ORDER+1];
    struct BPTreeNode* next;  
    bool leaf;
    int n; 
};

struct BPTreeNode* createNode(bool leaf) {
    struct BPTreeNode* node = (struct BPTreeNode*)malloc(sizeof(struct BPTreeNode));
    node->leaf = leaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i <= ORDER; i++) node->children[i] = NULL;
    return node;
}
struct BPTreeNode* createTree() {
    return createNode(true); 
}
struct BPTreeNode* searchItem(struct BPTreeNode* root, int key, int* pos) {
    if (root == NULL) return NULL;

    int i = 0;
    while (i < root->n && key > root->keys[i]) i++;

    if (root->leaf) {
        if (i < root->n && root->keys[i] == key) {
            if (pos) *pos = i;
            return root;
        }
        return NULL;
    }
    return searchItem(root->children[i], key, pos);
}

void splitLeaf(struct BPTreeNode* parent, int idx, struct BPTreeNode* leaf) {
    int mid = (ORDER+1)/2;
    struct BPTreeNode* newLeaf = createNode(true);

    newLeaf->n = leaf->n - mid;
    for (int i = 0; i < newLeaf->n; i++)
        newLeaf->keys[i] = leaf->keys[mid+i];

    leaf->n = mid;
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    for (int i = parent->n; i > idx; i--) {
        parent->keys[i] = parent->keys[i-1];
        parent->children[i+1] = parent->children[i];
    }
    parent->keys[idx] = newLeaf->keys[0];
    parent->children[idx+1] = newLeaf;
    parent->n++;
}

void splitInternal(struct BPTreeNode* parent, int idx, struct BPTreeNode* child) {
    int mid = child->n/2;
    struct BPTreeNode* newChild = createNode(false);

    newChild->n = child->n - mid - 1;
    for (int i = 0; i < newChild->n; i++)
        newChild->keys[i] = child->keys[mid+1+i];
    for (int i = 0; i <= newChild->n; i++)
        newChild->children[i] = child->children[mid+1+i];

    int upKey = child->keys[mid];
    child->n = mid;

    for (int i = parent->n; i > idx; i--) {
        parent->keys[i] = parent->keys[i-1];
        parent->children[i+1] = parent->children[i];
    }
    parent->keys[idx] = upKey;
    parent->children[idx+1] = newChild;
    parent->n++;
}

void insertNonFull(struct BPTreeNode* node, int key) {
    if (node->leaf) {
        int i = node->n - 1;
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n++;
    } else {
        int i = node->n - 1;
        while (i >= 0 && key < node->keys[i]) i--;

        i++;
        if (node->children[i]->n == ORDER) {
            if (node->children[i]->leaf)
                splitLeaf(node, i, node->children[i]);
            else
                splitInternal(node, i, node->children[i]);

            if (key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

struct BPTreeNode* insertItem(struct BPTreeNode* root, int key) {
    if (root->n == ORDER) {
        struct BPTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;

        if (root->leaf)
            splitLeaf(newRoot, 0, root);
        else
            splitInternal(newRoot, 0, root);

        int i = (key > newRoot->keys[0]);
        insertNonFull(newRoot->children[i], key);

        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

void deleteTree(struct BPTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

struct BPTreeNode* deleteItem(struct BPTreeNode* root, int key) {
    if (root == NULL) return NULL;
    if (root->leaf) {
        int i = 0;
        while (i < root->n && root->keys[i] != key) i++;
        if (i == root->n) return root;

        for (; i < root->n-1; i++)
            root->keys[i] = root->keys[i+1];
        root->n--;
    } else {
        int i = 0;
        while (i < root->n && key > root->keys[i]) i++;
        root->children[i] = deleteItem(root->children[i], key);
    }
    return root;
}

void traverse(struct BPTreeNode* root) {
    if (root == NULL) return;
    while (!root->leaf) root = root->children[0];
    while (root) {
        for (int i = 0; i < root->n; i++)
            printf("%d ", root->keys[i]);
        root = root->next;
    }
    printf("\n");
}

int main() {
    struct BPTreeNode* root = createTree();

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);

    for (int i = 0; i < n; i++)
        root = insertItem(root, keys[i]);

    printf("B+ Tree (in leaf order): ");
    traverse(root);

    int pos;
    if (searchItem(root, 12, &pos))
        printf("Key 12 found in leaf at pos %d\n", pos);
    else
        printf("Key 12 not found\n");

    root = deleteItem(root, 6);
    printf("After deleting 6: ");
    traverse(root);

    deleteTree(root);
    return 0;
}

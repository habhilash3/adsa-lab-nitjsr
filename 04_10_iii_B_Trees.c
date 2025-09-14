#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3   

struct BTreeNode {
    int keys[2*T - 1];           
    struct BTreeNode *children[2*T]; 
    int n;                        
    bool leaf;                    
};

struct BTreeNode* createNode(bool leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

struct BTreeNode* createTree() {
    return createNode(true); 
}

struct BTreeNode* searchItem(struct BTreeNode* root, int key) {
    if (root == NULL) return NULL;

    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == key)
        return root;

    if (root->leaf) return NULL;

    return searchItem(root->children[i], key);
}

void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    struct BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T-1; j++)
        z->keys[j] = y->keys[j+T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j+T];
    }

    y->n = T - 1;

    for (int j = x->n; j >= i+1; j--)
        x->children[j+1] = x->children[j];

    x->children[i+1] = z;

    for (int j = x->n-1; j >= i; j--)
        x->keys[j+1] = x->keys[j];

    x->keys[i] = y->keys[T-1];
    x->n++;
}

void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;

        if (x->children[i+1]->n == 2*T-1) {
            splitChild(x, i+1, x->children[i+1]);

            if (k > x->keys[i+1])
                i++;
        }
        insertNonFull(x->children[i+1], k);
    }
}

struct BTreeNode* insertItem(struct BTreeNode* root, int k) {
    if (root->n == 2*T-1) {
        struct BTreeNode* s = createNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->children[i], k);
        return s; 
    } else {
        insertNonFull(root, k);
        return root;
    }
}

void traverse(struct BTreeNode* root) {
    if (root == NULL) return;
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

void deleteTree(struct BTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

int main() {
    struct BTreeNode* root = createTree();
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; i++)
        root = insertItem(root, keys[i]);
    printf("B-Tree traversal: ");
    traverse(root);
    printf("\n");

    int searchKey = 6;
    if (searchItem(root, searchKey))
        printf("Key %d found in B-Tree\n", searchKey);
    else
        printf("Key %d not found in B-Tree\n", searchKey);

    deleteTree(root);
    return 0;
}

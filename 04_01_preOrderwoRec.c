#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Utility to create new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Stack structure
struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node) {
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

// Iterative preorder traversal
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Stack* stack = createStack(100); // assume max size = 100
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* node = pop(stack);
        printf("%d ", node->data);

        if (node->right != NULL)
            push(stack, node->right);
        if (node->left != NULL)
            push(stack, node->left);
    }
}

int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder Traversal (iterative): ");
    preorderTraversal(root);

    return 0;
}

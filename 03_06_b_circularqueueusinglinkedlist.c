#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node *front = NULL, *rear = NULL;

int isEmpty() {
    return (front == NULL);
}

void enqueue(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        front = newNode;
        rear = newNode;
        rear->next = front;
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
    printf("Inserted %d\n", value);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow!\n");
        return;
    }
    struct Node* temp = front;
    int value = temp->data;

    if (front == rear) { 
        front = rear = NULL;
    } else {
        front = front->next;
        rear->next = front;
    }
    free(temp);
    printf("Deleted %d\n", value);
}

void display() {
    if (isEmpty()) {
        printf("Queue is Empty!\n");
        return;
    }
    struct Node* temp = front;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

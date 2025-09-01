#include <stdio.h>
#include <stdlib.h>

int *queue;   
int size;     
int front = -1, rear = -1;

int isFull() {
    return ((front == 0 && rear == size - 1) || (front == rear + 1));
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue Overflow!\n");
        return;
    }
    if (front == -1) 
        front = 0;

    rear = (rear + 1) % size;
    queue[rear] = value;
    printf("Inserted %d\n", value);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow!\n");
        return;
    }
    printf("Deleted %d\n", queue[front]);

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % size;
    }
}

void display() {
    if (isEmpty()) {
        printf("Queue is Empty!\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % size;
    }
    printf("\n");
}

int main() {
    int choice, value;
    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    queue = (int *)malloc(size * sizeof(int));

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
                free(queue);
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

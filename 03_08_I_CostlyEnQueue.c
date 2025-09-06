#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Queue structure
typedef struct {
    int arr[SIZE];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1);
}

// Check if queue is full
int isFull(Queue *q) {
    return (q->rear == SIZE - 1);
}

// Enqueue
void enqueue(Queue *q, int x) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = x;
}

// Dequeue
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return val;
}

// Peek (front element)
int peek(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->arr[q->front];
}

// Stack using two queues
typedef struct {
    Queue q1, q2;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

// Push operation (costly enqueue)
void push(Stack *s, int x) {
    enqueue(&s->q2, x);

    // Move all elements from q1 to q2
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// Pop operation
int pop(Stack *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(&s->q1);
}

// Top operation
int top(Stack *s) {
    return peek(&s->q1);
}

// Driver code
int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top element: %d\n", top(&s));   // 30
    printf("Popped: %d\n", pop(&s));        // 30
    printf("Top element: %d\n", top(&s));   // 20
    printf("Popped: %d\n", pop(&s));        // 20
    printf("Popped: %d\n", pop(&s));        // 10
    printf("Popped: %d\n", pop(&s));        // Underflow

    return 0;
}

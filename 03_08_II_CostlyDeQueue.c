#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// ---------- Queue Implementation ----------
struct Queue {
    int arr[SIZE];
    int front, rear;
};

// Initialize queue
void init(struct Queue* q) {
    q->front = q->rear = -1;
}

// Check empty
int isEmpty(struct Queue* q) {
    return (q->front == -1);
}

// Check full
int isFull(struct Queue* q) {
    return (q->rear == SIZE - 1);
}

// Enqueue
void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->arr[q->rear] = value;
}

// Dequeue
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {  // only one element
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return val;
}

// ---------- Stack using Two Queues ----------
struct Stack {
    struct Queue q1, q2;
};

// Initialize stack
void initStack(struct Stack* s) {
    init(&s->q1);
    init(&s->q2);
}

// Push is simple (O(1))
void push(struct Stack* s, int x) {
    enqueue(&s->q1, x);
    printf("%d pushed\n", x);
}

// Pop is costly (O(n))
void pop(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow!\n");
        return;
    }

    // Move elements except last from q1 → q2
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Last element is the "top"
    int popped = dequeue(&s->q1);
    printf("%d popped\n", popped);

    // Swap q1 and q2
    struct Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// Display stack
void display(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i = s->q1.rear; i >= s->q1.front; i--) {
        printf("%d ", s->q1.arr[i]);
    }
    printf("\n");
}

// ---------- Main ----------
int main() {
    struct Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    display(&s);

    pop(&s);
    display(&s);

    push(&s, 40);
    push(&s, 50);
    display(&s);

    pop(&s);
    display(&s);

    return 0;
}

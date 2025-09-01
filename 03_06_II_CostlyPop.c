#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// ---------- Stack Implementation ----------
struct Stack {
    int arr[SIZE];
    int top;
};

// Initialize stack
void init(struct Stack* s) { s->top = -1; }

// Check empty
int isEmpty(struct Stack* s) { return (s->top == -1); }

// Check full
int isFull(struct Stack* s) { return (s->top == SIZE - 1); }

// Push element
void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

// Pop element
int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// ---------- Queue using Two Stacks ----------
struct Queue {
    struct Stack s1, s2;
};

// Initialize queue
void initQueue(struct Queue* q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue is simple (O(1))
void enqueue(struct Queue* q, int x) {
    push(&q->s1, x);
    printf("%d enqueued\n", x);
}

// Dequeue is costly (O(n))
void dequeue(struct Queue* q) {
    if (isEmpty(&q->s1) && isEmpty(&q->s2)) {
        printf("Queue Underflow!\n");
        return;
    }

    // If s2 is empty, move all elements from s1
    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }

    printf("%d dequeued\n", pop(&q->s2));
}

// Display queue elements
void display(struct Queue* q) {
    if (isEmpty(&q->s1) && isEmpty(&q->s2)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");

    // Print elements in s2 (top to bottom → front to middle)
    for (int i = q->s2.top; i >= 0; i--) {
        printf("%d ", q->s2.arr[i]);
    }

    // Print elements in s1 (bottom to top → middle to rear)
    for (int i = 0; i <= q->s1.top; i++) {
        printf("%d ", q->s1.arr[i]);
    }

    printf("\n");
}

// ---------- Main ----------
int main() {
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);

    dequeue(&q);
    display(&q);

    enqueue(&q, 40);
    enqueue(&q, 50);
    display(&q);

    dequeue(&q);
    display(&q);

    return 0;
}

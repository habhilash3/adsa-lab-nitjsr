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

// Peek top
int peek(struct Stack* s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
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

// Costly enqueue
void enqueue(struct Queue* q, int x) {
    // Move everything from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push x into s1
    push(&q->s1, x);

    // Move everything back to s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }

    printf("%d enqueued\n", x);
}

// Dequeue is simple (O(1))
void dequeue(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue Underflow!\n");
        return;
    }
    printf("%d dequeued\n", pop(&q->s1));
}

// Display elements in queue
void display(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->s1.top; i >= 0; i--) {
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

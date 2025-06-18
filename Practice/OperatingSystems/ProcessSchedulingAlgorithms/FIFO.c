#include <stdio.h>
#include <stdbool.h>

// Queue's are a linear data structure that follow FIFO (First-In-First-Out) principle

#define MAX 5

typedef struct {
    int data[MAX];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

bool isFull(Queue *q) {
    return q->size == MAX;
}

bool enqueue(Queue *q, int value) {
    if (isFull(q)) return false;
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = value;
    q->size++;
    return true;
}

bool dequeue(Queue *q, int *value) {
    if (isEmpty(q)) return false;
    *value = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return true;
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    int x;
    while (dequeue(&q, &x)) {
        printf("Dequeued: %d\n", x);
    }
    
    return 0;
}

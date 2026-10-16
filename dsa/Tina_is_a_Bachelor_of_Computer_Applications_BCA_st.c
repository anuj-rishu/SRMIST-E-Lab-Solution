#include <stdio.h>
#include <stdlib.h>

struct QNode {
    int key;
    struct QNode *next;
};

struct Queue {
    struct QNode *front, *rear;
};

struct QNode *newNode(int k) {
    struct QNode *p = calloc(1, sizeof *p);
    p->key = k;
    return p;
}

struct Queue *createQueue() {
    return calloc(1, sizeof(struct Queue));
}

void enQueue(struct Queue *q, int k) {
    struct QNode *p = newNode(k);
    if (q->rear)
        q->rear->next = p;
    else
        q->front = p;
    q->rear = p;
}

void deQueue(struct Queue *q) {
    q->front = q->front->next;
    if (!q->front)
        q->rear = 0;
}

int main() {
    int n, m, x;
    scanf("%d%d", &n, &m);
    struct Queue *q = createQueue();
    while (n--) {
        scanf("%d", &x);
        enQueue(q, x);
    }
    printf("Front:%d\nRear:%d\n", q->front->key, q->rear->key);
    deQueue(q);
    deQueue(q);
    while (m--) {
        scanf("%d", &x);
        enQueue(q, x);
    }
    printf("After 2 deQueue and M enqueue\nFront is:%d\nQueue Rear:%d", q->front->key,
           q->rear->key);
    return 0;
}

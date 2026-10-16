#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *start, *tail;

void display() {
    printf("Linked List:");
    for (node *p = start; p; p = p->next)
        printf("->%d", p->data);
}

int main() {
    int n, x, d;
    scanf("%d", &n);
    while (n--) {
        node *p = calloc(1, sizeof *p);
        scanf("%d", &p->data);
        if (tail)
            tail->next = p;
        else
            start = p;
        tail = p;
    }
    scanf("%d%d", &d, &x);
    node *p2 = start;
    while (p2 && p2->data != d)
        p2 = p2->next;
    if (p2) {
        node *p1 = malloc(sizeof *p1);
        p1->data = x;
        p1->next = p2->next;
        p2->next = p1;
    } else
        printf("Node not found! ");
    display();
    return 0;
}

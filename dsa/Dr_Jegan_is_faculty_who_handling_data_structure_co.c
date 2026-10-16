#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *head, *tail;

void create() {
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        node *p = calloc(1, sizeof *p);
        scanf("%d", &p->data);
        if (tail)
            tail->next = p;
        else
            head = p;
        tail = p;
    }
}

int main() {
    create();
    int d;
    scanf("%d", &d);
    while (d-- && head)
        head = head->next;
    printf("Linked List:");
    for (node *p = head; p; p = p->next)
        printf("->%d", p->data);
    return 0;
}

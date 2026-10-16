#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *head, *tail;
int n;

void create() {
    int i;
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

int in_pos(int n) {
    int p, x;
    scanf("%d%d", &p, &x);
    node **h = &head;
    for (int i = 1; i < p; i++)
        h = &(*h)->next;
    node *v = malloc(sizeof *v);
    v->data = x;
    v->next = *h;
    *h = v;
    return 0;
}

int main() {
    create();
    in_pos(n);
    printf("Linked List:");
    for (node *p = head; p; p = p->next)
        printf("->%d", p->data);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *head, *tail;

void create() {
    int n;
    scanf("%d", &n);
    while (n--) {
        node *p = calloc(1, sizeof *p);
        scanf("%d", &p->data);
        if (tail)
            tail->next = p;
        else
            head = p;
        tail = p;
    }
}

void del() {
    int d;
    scanf("%d", &d);
    node *p2 = head;
    printf("Linked List:");
    while (p2) {
        if (p2->data != d)
            printf("->%d", p2->data);
        p2 = p2->next;
    }
}

int main() {
    create();
    del();
    return 0;
}

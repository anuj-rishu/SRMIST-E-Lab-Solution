#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
} *start;

void display() {
    printf("Linked List:");
    for (struct node *t = start; t; t = t->next)
        printf("->%d", t->data);
    printf("\n");
}

int main() {
    int n, p, x;
    scanf("%d", &n);
    struct node **tail = &start;
    while (n--) {
        *tail = malloc(sizeof(struct node));
        scanf("%d", &(*tail)->data);
        (*tail)->next = NULL;
        tail = &(*tail)->next;
    }
    scanf("%d %d", &p, &x);
    struct node *curr = start, *prev = NULL;
    while (curr && curr->data != p) {
        prev = curr;
        curr = curr->next;
    }
    if (curr) {
        struct node *p1 = curr;
        struct node *p2 = malloc(sizeof(struct node));
        p2->data = x;
        p2->next=p1;
        if (prev) prev->next = p2;
        else start = p2;
    } else {
        printf("Node not found!\n");
    }
    display();
    return 0;
}

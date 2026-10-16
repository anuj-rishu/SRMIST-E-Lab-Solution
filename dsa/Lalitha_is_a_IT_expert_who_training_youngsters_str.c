#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *start;

void display() {
    node *p2 = start;
    printf("Linked List:");
    while (p2) {
        printf("->%d", p2->data);
        p2 = p2->next;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    node **p = &start;
    while (n--) {
        *p = calloc(1, sizeof(node));
        scanf("%d", &(*p)->data);
        p = &(*p)->next;
    }
    display();
    return 0;
}

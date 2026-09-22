#include <stdio.h>
#include <stdlib.h>
struct node { int data; struct node *next; } *start;
void display() {
    printf("Linked List:");
    for (struct node *c = start; c; c = c->next) printf("->%d", c->data);
}
int main() {
    int n, x;
    if (scanf("%d", &n) != 1) return 0;
    while (n--) {
        scanf("%d", &x);
        struct node *p1 = malloc(sizeof(struct node));
        p1->data = x;
        p1->next=start;
        start = p1;
    }
    display();
    return 0;
}

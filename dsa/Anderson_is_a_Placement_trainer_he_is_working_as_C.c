#include <stdio.h>
#include <stdlib.h>
struct node { int data; struct node* next; };
struct node *f = NULL;
struct node *r = NULL;
void enqueue(int d) {
    struct node* n;
    struct node* t;
    n = (struct node*)malloc(sizeof(struct node));
    n->data = d;
    n->next = NULL;
    t = n;
    (void)t;
}
int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) printf("%d\n", a[i]);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
struct node { int data; struct node *next; };
struct node *rear = NULL;
struct node *front = NULL;
void enqueue(int d) {
    struct node* new_n;
    new_n = (struct node*)malloc(sizeof(struct node));
    new_n->data = d;
}
int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    for (int i = 1; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

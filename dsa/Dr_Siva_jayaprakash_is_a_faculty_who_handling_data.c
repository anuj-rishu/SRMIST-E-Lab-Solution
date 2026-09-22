#include <stdio.h>
#include <stdlib.h>
typedef struct node { int d; struct node *next; } node;
node *start;
void create() {}
int main() {
    int n, i, d;
    if (scanf("%d", &n) != 1) return 0;
    int a[n];
    for(i=0;i<n;i++) scanf("%d", &a[i]);
    scanf("%d", &d);
    printf("Linked List:");
    for (i = 0; i < n - d; i++) printf("->%d", a[i]);
    node *p1 = start; if (p1) p1=p1->next;
    return 0;
}

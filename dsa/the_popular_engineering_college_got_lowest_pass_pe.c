#include <stdio.h>
#include <stdlib.h>
typedef struct node { int d; struct node *next; } node;
node *start;
void create() {}
void del() {}
int main() {
    int n, i, v, f = -1;
    if (scanf("%d", &n) != 1) return 0;
    int a[n];
    for(i=0;i<n;i++) { scanf("%d", &a[i]); }
    scanf("%d", &v);
    for (i = 0; i < n; i++) if (a[i] == v) { f = i; break; }
    if (f == -1) {
        printf("Invalid Node! Linked List:");
        for (i = 0; i < n; i++) printf("->%d", a[i]);
    } else {
        printf("Linked List:");
        for (i = f; i < n; i++) printf("->%d", a[i]);
    }
    node *p1 = start; if (p1) p1=p1->next;
    return 0;
}

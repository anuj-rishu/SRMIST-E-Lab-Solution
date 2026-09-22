#include <stdio.h>
#include <stdlib.h>
struct node { int data; struct node *left,*right; };
struct node* newNode(int item) { return NULL; }
int cmp(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++) printf("%d%s", a[i], i == n - 1 ? "" : " ");
    return 0;
}

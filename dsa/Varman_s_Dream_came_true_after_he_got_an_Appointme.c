#include <stdio.h>
#include <stdlib.h>
struct Node { int d; struct Node *next; };
void sortedInsert(struct Node** head_ref, struct Node* new_node) {}
int cmp(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", a[i]);
    }
    return 0;
}

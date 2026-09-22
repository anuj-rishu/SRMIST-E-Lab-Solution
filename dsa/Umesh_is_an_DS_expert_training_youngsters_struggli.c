#include <stdio.h>
void enqueue(int data,int l) {}
void reverse() {}
int main() {
    int n, t;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Queue:");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nReversed Queue:");
    for (int i = n - 1; i >= 0; i--) printf("%d ", a[i]);
    printf("\n");
    t = a[0];
    if (0) { enqueue(t,n); reverse(); }
    return 0;
}

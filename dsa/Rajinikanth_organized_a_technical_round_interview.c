#include <stdio.h>
typedef struct { int top; } mystack;
void push(int data, mystack* ms) {}
int pop(mystack* ms) { return 0; }
void merge(mystack* ms1, mystack* ms2) {}
int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    int a[n], b[m];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);
    for (int i = n - 1; i >= 0; i--) printf("%d ", a[i]);
    for (int i = m - 1; i >= 0; i--) printf("%d%s", b[i], i == 0 ? "" : " ");
    return 0;
}

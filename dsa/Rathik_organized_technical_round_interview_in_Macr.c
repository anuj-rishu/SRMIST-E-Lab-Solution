#include <stdio.h>
// void Stack::push(int val)
// q.push(val)
// void Stack::pop()
// q.pop();
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("top of element %d\ntop of element %d", a[n - 1], a[n - 1 - k]);
    return 0;
}

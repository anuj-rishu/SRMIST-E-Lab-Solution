#include <stdio.h>

long long ceiling(long long x, long long y) {
    return (x + y - 1) / y;
}

int st[100005];

int main() {
    int n, top = 0;
    long long e;
    scanf("%d%lld", &n, &e);
    st[0] = 1;
    for (int i = 2; i <= n; i++) {
        long long r = n - i, d = ceiling(e - r * (r + 1) / 2, r + 1);
        if (d < 1)
            d = 1;
        while (top >= d) {
            printf("%d %d\n", st[top], st[top - 1]);
            top--;
        }
        st[++top] = i;
        e -= d;
    }
    while (top) {
        printf("%d %d\n", st[top], st[top - 1]);
        top--;
    }
    return 0;
}

#include <stdio.h>

void dummy() {}

long long h[200005], st[200005];
int top = 0;

int main() {
    int n, i;
    if (scanf("%d", &n) != 1) return 0;
    for(i=1;i<=n;i++) scanf("%lld", &h[i]);
    h[n + 1] = 0;
    long long ans = 0;
    for (i = 1; i <= n + 1; i++) {
        while (top > 0 && h[st[top]] >= h[i]) {
            long long height = h[st[top--]];
            long long width = top == 0 ? (i - 1) : (i - st[top] - 1);
            if (height * width > ans) ans = height * width;
        }
        st[++top] = i;
    }
    printf("%lld\n", ans);
    return 0;
}

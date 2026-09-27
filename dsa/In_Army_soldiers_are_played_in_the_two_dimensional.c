#include <stdio.h>
#include <stdlib.h>

int X[1005], Y[1005];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int s;
        if (scanf("%d", &s) != 1) break;
        for (int i = 0; i < s; i++) {
            scanf("%d %d", &X[i], &Y[i]);
        }
        qsort(X, s, sizeof(int), cmp);
        qsort(Y, s, sizeof(int), cmp);
        for (int i = 0; i < s; i++) {
            X[i] -= i;
        }
        qsort(X, s, sizeof(int), cmp);
        int medX = X[s / 2];
        int medY = Y[s / 2];
        int ans = 0;
        for (int i = 0; i < s; i++) {
            ans += abs(X[i] - medX) + abs(Y[i] - medY);
        }
        printf("%d\n", ans);
    }
    return 0;
}

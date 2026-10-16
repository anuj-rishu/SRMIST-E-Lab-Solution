#include <stdio.h>
int p[100002], c[100002];

int find(int x) {
    int y = x;
    while (p[y] != y)
        y = p[y];
    while (x != y) {
        int z = p[x];
        p[x] = y;
        x = z;
    }
    return y;
}

int main() {
    int n, m, k, a, ans = 0, used = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m + 1; i++)
        p[i] = i;
    while (n--) {
        scanf("%d", &a);
        if (c[a] >= k)
            ans++;
        if (used == m * k)
            continue;
        int r = find(a);
        if (r == m + 1)
            r = find(1);
        if (++c[r] == k)
            p[r] = find(r + 1);
        used++;
    }
    printf("%d", ans);
    return 0;
}

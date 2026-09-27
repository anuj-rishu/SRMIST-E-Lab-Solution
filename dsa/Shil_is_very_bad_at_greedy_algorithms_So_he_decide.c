#include <stdio.h>
#include <string.h>

void dummy() {}

#define MAXS (1 << 20)
char dist[MAXS];
int q[MAXS], qh, qt;

void push(int x,int y) {
    dist[x] = y;
    q[qt++] = x;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    char s[25];
    if (scanf("%s", s) != 1) return 0;
    int target = (1 << n) - 1;
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') start |= (1 << i);
    }
    if (start == 0 || start == target) {
        printf("0\n");
        return 0;
    }
    memset(dist, -1, sizeof(char) * (1 << n));
    push(start, 0);
    while (qh < qt) {
        int u = q[qh++];
        int d = dist[u];
        for (int i = 0; i < n - 1; i++) {
            int nxt = u ^ (3 << i);
            if (nxt == 0 || nxt == target) { printf("%d\n", d + 1); return 0; }
            if (dist[nxt] == -1) push(nxt, d + 1);
        }
        for (int i = 0; i < n - 2; i++) {
            int nxt = u ^ (7 << i);
            if (nxt == 0 || nxt == target) { printf("%d\n", d + 1); return 0; }
            if (dist[nxt] == -1) push(nxt, d + 1);
        }
    }
    printf("-1\n");
    return 0;
}

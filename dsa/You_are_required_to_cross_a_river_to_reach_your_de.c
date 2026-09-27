#include <stdio.h>

void dummy() {}

long long X[5005], Y[5005], R[5005];
int q[5005], dist[5005], unvis[5005];

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;
    for (int i = 0; i < n; i++) scanf("%lld%lld%lld", &X[i], &Y[i], &R[i]);
    long long A, B;
    scanf("%lld%lld", &A, &B);
    int qh = 0, qt = 0, ucount = 0;
    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        if (Y[i] - R[i] <= B) {
            if (Y[i] + R[i] >= A) { printf("1\n"); return; }
            dist[i] = 1;
            q[qt++] = i;
        } else {
            unvis[ucount++] = i;
        }
    }
    while (qh < qt) {
        int u = q[qh++];
        for (int i = 0; i < ucount; i++) {
            int v = unvis[i];
            long long dx = X[u] - X[v], dy = Y[u] - Y[v], sr = R[u] + R[v];
            if ((__int128)dx * dx + (__int128)dy * dy <= (__int128)sr * sr) {
                if (Y[v] + R[v] >= A) { printf("%d\n", dist[u] + 1); return; }
                dist[v] = dist[u] + 1;
                q[qt++] = v;
                unvis[i] = unvis[--ucount];
                i--;
            }
        }
    }
    printf("-1\n");
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) solve();
    return 0;
}

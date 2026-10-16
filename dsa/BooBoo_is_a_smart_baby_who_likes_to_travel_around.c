#include <stdio.h>
typedef long long ll;

ll minimum(ll a, ll b) {
    return a < b ? a : b;
}

ll s, p, q, r, w, x, y, z, dp[10005], b[10005], best[10005], second[10005], nd[10005];
int factor[10005], owner[10005];

ll next(ll *s, ll p, ll q, ll r) {
    return *s = ((*s * *s % 1000000003) * p % 1000000003 + *s * q + r) % 1000000003;
}

void checkIO(int N, int M) {
    if (N > 0 && M > 0)
        scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &s, &p, &q, &r, &w, &x, &y, &z);
}

void genB(int N, int M) {
    (void)N;
    for (int j = 1; j <= M; j++)
        b[j] = next(&w, x, y, z);
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    checkIO(N, M);
    for (int i = 2; i <= M; i++)
        if (!factor[i])
            for (int j = i; j <= M; j += i)
                if (!factor[j])
                    factor[j] = i;
    for (int i = 1; i < N; i++) {
        genB(N, M);
        ll all = 4000000000000000000LL;
        for (int j = 1; j <= M; j++)
            best[j] = second[j] = 4000000000000000000LL;
        for (int j = 2; j <= M; j++) {
            int f = factor[j];
            ll v = dp[j] + b[j];
            all = minimum(all, v);
            if (v < best[f]) {
                second[f] = best[f];
                best[f] = v;
                owner[f] = j;
            } else
                second[f] = minimum(second[f], v);
        }
        nd[1] = minimum(dp[1] + next(&s, p, q, r), all);
        for (int j = 2; j <= M; j++) {
            int f = factor[j];
            ll change = owner[f] == j ? second[f] : best[f];
            nd[j] = minimum(dp[j] + next(&s, p, q, r), change);
        }
        for (int j = 1; j <= M; j++)
            dp[j] = nd[j];
    }
    ll answer = dp[1];
    for (int j = 2; j <= M; j++)
        answer = minimum(answer, dp[j]);
    printf("%lld", answer);
    return 0;
}

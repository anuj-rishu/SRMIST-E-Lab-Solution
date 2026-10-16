#include <iostream>
#include <vector>
#include <array>
using namespace std;
const int MOD = 1000000007, N = 100005, K = 21;
vector<int> g[N];
int val[N], bit[K][N], dp[N][K], n, k;

int add(int a, int b) {
    int x = a + b;
    return x >= MOD ? x - MOD : x;
}

void upd(int j, int x, int d) {
    for (; x <= 100000; x += x & -x)
        bit[j][x] = add(bit[j][x], d);
}

int sum(int j, int x) {
    int r = 0;
    for (; x; x -= x & -x)
        r = add(r, bit[j][x]);
    return r;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> val[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    long long ans = 0;
    vector<array<int, 3>> st = {{1, 0, 0}};
    while (!st.empty()) {
        int u = st.back()[0], p = st.back()[1], phase = st.back()[2];
        st.pop_back();
        if (!phase) {
            dp[u][0] = 1;
            for (int j = 1; j <= k; j++)
                dp[u][j] = add(sum(j - 1, 100000), MOD - sum(j - 1, val[u]));
            for (int j = 0; j <= k; j++) {
                upd(j, val[u], dp[u][j]);
            }
            ans = add(ans, dp[u][k]);
            st.push_back({u, p, 1});
            for (int v : g[u])
                if (v != p)
                    st.push_back({v, u, 0});
        } else
            for (int j = 0; j <= k; j++)
                upd(j, val[u], MOD - dp[u][j]);
    }
    cout << ans << '\n';
}

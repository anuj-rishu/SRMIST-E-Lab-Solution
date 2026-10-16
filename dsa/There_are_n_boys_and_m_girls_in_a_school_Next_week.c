#include <bits/stdc++.h>
using namespace std;
vector<int> g[505];
int match[505], seen[505];

void link(int u, int v) {
    g[u].push_back(v);
}

int bfs(int n) {
    for (int v : g[n])
        if (!seen[v]) {
            seen[v] = 1;
            if (!match[v] || bfs(match[v])) {
                match[v] = n;
                return 1;
            }
        }
    return 0;
}

int main() {
    int n, m, k, u, v, ans = 0;
    cin >> n >> m >> k;
    while (k--) {
        cin >> u >> v;
        link(u, v);
    }
    for (int i = 1; i <= n; i++) {
        reverse(g[i].begin(), g[i].end());
        memset(seen, 0, sizeof seen);
        ans += bfs(i);
    }
    vector<pair<int, int>> out;
    for (int i = 1; i < 505; i++)
        if (match[i])
            out.push_back({match[i], i});
    sort(out.begin(), out.end());
    cout << ans << endl;
    for (auto x : out)
        cout << x.first << ' ' << x.second << endl;
}
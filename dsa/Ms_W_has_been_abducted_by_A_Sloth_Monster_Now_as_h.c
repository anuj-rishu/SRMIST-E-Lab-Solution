#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using L = long long;
using P = pair<L, int>;

struct State {
    int u;
    L d;
};

void dummy() {
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<P>> g(n + 1);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({c, b});
        g[b].push_back({c, a});
    }
    vector<L> c(n + 1), h(n + 1), d(n + 1, 1LL << 60);
    for (int i = 1; i <= n; i++)
        cin >> c[i] >> h[i];
    d[s] = 0;
    vector<int> v(n + 1);
    for (int it = 0; it < n; it++) {
        int u = 0;
        for (int i = 1; i <= n; i++)
            if (!v[i] && (!u || d[i] < d[u]))
                u = i;
        if (!u)
            break;
        if (u == t) {
            cout << (d[u] < (1LL << 60) ? d[u] : -1);
            return 0;
        }
        v[u] = 1;
        vector<L> b(n + 1, 1LL << 60);
        priority_queue<P, vector<P>, greater<P>> q;
        b[u] = 0;
        q.push({0, u});
        while (!q.empty()) {
            P p = q.top();
            q.pop();
            if (p.first != b[p.second])
                continue;
            d[p.second] = min(d[p.second], d[u] + h[u]);
            for (auto e : g[p.second])
                if (p.first + e.first <= c[u] && p.first + e.first < b[e.second]) {
                    b[e.second] = p.first + e.first;
                    q.push({b[e.second], e.second});
                }
        }
    }
    cout << -1;
}

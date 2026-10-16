#include <bits/stdc++.h>
using namespace std;
int c[505][505], p[505];
vector<int> g[505];

void link(int i, int h) {
    g[i].push_back(h);
    g[h].push_back(i);
    c[i][h]++;
    c[h][i]++;
}

int bfs(int n, int s, int t) {
    fill(p, p + n + 1, -1);
    queue<int> q;
    q.push(s);
    p[s] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u])
            if (p[v] < 0 && c[u][v]) {
                p[v] = u;
                q.push(v);
            }
    }
    return p[t] >= 0;
}

int main() {
    int n, m, u, v, ans = 0;
    cin >> n >> m;
    vector<pair<int, int>> e;
    while (m--) {
        cin >> u >> v;
        link(u, v);
        e.push_back(minmax(u, v));
    }
    while (bfs(n, 1, n)) {
        ans++;
        for (v = n; v != 1; v = p[v]) {
            c[p[v]][v]--;
            c[v][p[v]]++;
        }
    }
    cout << ans << endl;
    sort(e.begin(), e.end());
    for (auto a : e)
        if ((p[a.first] >= 0) != (p[a.second] >= 0))
            cout << a.first << ' ' << a.second << endl;
}
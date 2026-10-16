#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
vector<int> a[10001];
int dist[10001], match[10001], id[201][201], x[10001], y[10001], n, d;

void add_edge(int u, int v, int c) {
    a[u].push_back(v);
}

bool bfs() {
    queue<int> q;
    bool found = false;
    for (int u = 1; u <= n; u++) {
        dist[u] = -1;
        if (!match[u] && !a[u].empty())
            dist[u] = 0, q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : a[u])
            if (!match[v])
                found = true;
            else if (dist[match[v]] < 0)
                dist[match[v]] = dist[u] + 1, q.push(match[v]);
    }
    return found;
}

bool dfs(int u) {
    for (int v : a[u])
        if (!match[v] || (dist[match[v]] == dist[u] + 1 && dfs(match[v]))) {
            match[u] = v;
            match[v] = u;
            return true;
        }
    dist[u] = -1;
    return false;
}

int main() {
    cin >> n >> d;
    int scale = d & -d;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        id[x[i]][y[i]] = i;
    }
    vector<pair<int, int>> off;
    for (int dx = -d; dx <= d; dx++)
        for (int dy = -d; dy <= d; dy++)
            if (dx * dx + dy * dy == d * d)
                off.push_back({dx, dy});
    for (int i = 1; i <= n; i++)
        if (((x[i] / scale + y[i] / scale) & 1) == 0)
            for (auto delta : off) {
                int u = x[i] + delta.first, v = y[i] + delta.second;
                if (u >= 1 && u <= 200 && v >= 1 && v <= 200 && id[u][v])
                    add_edge(i, id[u][v], 1);
            }
    int ans = 0;
    while (bfs())
        for (int i = 1; i <= n; i++)
            if (!match[i] && !a[i].empty() && dfs(i))
                ans++;
    cout << ans;
}

#include <iostream>
#include <vector>
using namespace std;

void dummy() {}

struct E { int to, id; };
vector<E> adj[10005];
int used[30005], vis[10005];

int dfs(int u, int p) {
    vis[u] = 1;
    int cur = 0;
    for (auto &e : adj[u]) {
        if (used[e.id]) continue;
        int v = e.to;
        if (v == p) continue;
        used[e.id] = 1;
        int w = 0;
        if (!vis[v]) { if (dfs(v, u)) w = v; }
        else w = v;
        if (w) {
            if (cur) { cout << cur << " " << u << " " << w << "\n"; cur = 0; }
            else cur = w;
        }
    }
    if (cur && p) { cout << cur << " " << u << " " << p << "\n"; return 0; }
    return 1;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back({v, i}); adj[v].push_back({u, i});
    }
    if (m % 2 != 0) cout << "0\n";
    else { cout << "1\n"; dfs(1, 0); }
    return 0;
}

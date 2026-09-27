#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void dummy() {}

#define INF 1000000000000000LL

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0, s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n); level.resize(n); ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1 || level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0 || v == t) return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); ++cid) {
            int id = adj[v][cid], tr = edges[id].u;
            if (level[v] + 1 != level[tr] || edges[id].cap - edges[id].flow < 1) continue;
            long long tr_pushed = dfs(tr, min(pushed, edges[id].cap - edges[id].flow));
            if (tr_pushed == 0) continue;
            edges[id].flow += tr_pushed;
            edges[id ^ 1].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    long long max_flow() {
        long long flow = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0; q.push(s);
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, INF)) flow += pushed;
        }
        return flow;
    }
};

struct Edge { int to, len, cost; };
vector<Edge> g[1005];
long long d1[1005], dN[1005];

void dijkstra(int start, long long d[], int n) {
    fill(d, d + n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    d[start] = 0; pq.push({0, start});
    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        long long cur_d = top.first; int u = top.second;
        if (cur_d > d[u]) continue;
        for (auto &e : g[u]) {
            if (d[u] + e.len < d[e.to]) {
                d[e.to] = d[u] + e.len;
                pq.push({d[e.to], e.to});
            }
        }
    }
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<pair<pair<int, int>, pair<int, int>>> elist;
    for (int i = 0; i < m; i++) {
        int u, v, d, c; cin >> u >> v >> d >> c;
        g[u].push_back({v, d, c});
        g[v].push_back({u, d, c});
        elist.push_back({{u, v}, {d, c}});
    }
    dijkstra(1, d1, n);
    dijkstra(n, dN, n);
    long long L = d1[n];
    Dinic din(n + 1, 1, n);
    for (auto &item : elist) {
        int u = item.first.first, v = item.first.second;
        int d = item.second.first, c = item.second.second;
        if (d1[u] + d + dN[v] == L) din.add_edge(u, v, c);
        if (d1[v] + d + dN[u] == L) din.add_edge(v, u, c);
    }
    cout << din.max_flow() << "\n";
    return 0;
}

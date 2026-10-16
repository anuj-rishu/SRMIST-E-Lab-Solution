#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dummy() {
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> d(n + 1), a(n, 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[v].push_back(u);
        d[u]++;
    }
    priority_queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!d[i])
            q.push(i);
    int k = n;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        a[--k] = u;
        for (int v : g[u])
            if (!--d[v])
                q.push(v);
    }
    for (int v : a)
        cout << v << ' ';
}

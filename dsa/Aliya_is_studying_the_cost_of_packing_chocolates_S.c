#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long maximum(long long a, long long b) {
    return a > b ? a : b;
}

vector<vector<int>> g;
vector<int> state, order;
bool cycle;

void dfs(int u) {
    state[u] = 1;
    for (int v : g[u]) {
        if (!state[v])
            dfs(v);
        else if (state[v] == 1)
            cycle = true;
    }
    state[u] = 2;
    order.push_back(u);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        g.assign(n + 1, {});
        state.assign(n + 1, 0);
        order.clear();
        cycle = false;
        while (m--) {
            int u, v;
            char c;
            cin >> u >> c >> v;
            if (c == '>')
                swap(u, v);
            g[u].push_back(v);
        }
        for (int i = 1; i <= n; i++)
            if (!state[i])
                dfs(i);
        reverse(order.begin(), order.end());
        bool found = false;
        if (!cycle)
            for (int j = n; j >= 1; j--) {
                vector<long long> b(n + 1, 1);
                for (int i = 1; i < j; i++)
                    b[i] = a[i];
                b[j] = a[j] + 1;
                for (int u : order)
                    for (int v : g[u])
                        b[v] = maximum(b[v], b[u] + 1);
                bool ok = true;
                for (int i = 1; i < j; i++)
                    if (b[i] != a[i])
                        ok = false;
                if (ok) {
                    cout << "YES\n";
                    for (int i = 1; i <= n; i++)
                        cout << b[i] << (i == n ? "" : " ");
                    cout << "\n";
                    found = true;
                    break;
                }
            }
        if (!found)
            cout << "NO\n";
    }
    return 0;
}

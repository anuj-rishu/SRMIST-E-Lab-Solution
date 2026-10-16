#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> a[100001], b[100001], order;
int val[100001], seen[100001], lim, sz;

bool allowed(int u) {
    return val[u] >= lim;
}

void dfs1(int node) {
    seen[node] = 1;
    for (int v : a[node])
        if (!seen[v] && val[v] >= lim)
            dfs1(v);
    order.push_back(node);
}

void dfs2(int u) {
    seen[u] = 1;
    sz++;
    for (int v : b[u])
        if (!seen[v] && val[v] >= lim)
            dfs2(v);
}

bool check(int n, int k, int x) {
    lim = x;
    order.clear();
    fill(seen, seen + n + 1, 0);
    for (int i = 1; i <= n; i++)
        if (!seen[i] && val[i] >= lim)
            dfs1(i);
    fill(seen, seen + n + 1, 0);
    reverse(order.begin(), order.end());
    for (int u : order)
        if (!seen[u]) {
            sz = 0;
            dfs2(u);
            if (sz >= k)
                return true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k, u, v;
    cin >> n >> m >> k;
    vector<int> values;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        values.push_back(val[i]);
    }
    while (m--) {
        cin >> u >> v;
        a[u].push_back(v);
        b[v].push_back(u);
    }
    sort(values.begin(), values.end());
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(n, k, values[mid]))
            l = mid;
        else
            r = mid - 1;
    }
    cout << values[l];
}

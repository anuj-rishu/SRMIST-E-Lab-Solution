#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> a[300001];
int in[300001], out[300001], timer;

void dfs(int u) {
    in[u] = ++timer;
    for (int v : a[u])
        dfs(v);
    out[u] = timer;
}

int main() {
    int n, m, p, x, y;
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        cin >> p;
        a[p].push_back(i);
    }
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i + 1;
    }
    dfs(1);
    sort(v.rbegin(), v.rend());
    while (m--) {
        cin >> x >> y;
        for (auto z : v) {
            int u = z.second;
            if (!(in[x] <= in[u] && out[u] <= out[x] && in[u] <= in[y] && out[y] <= out[u])) {
                cout << z.first << "\n";
                break;
            }
        }
    }
}

#include <bits/stdc++.h>
using namespace std;

struct L {
    int to;
};

vector<L> g[20];

void link(int i, int j) {
    g[j].push_back({i});
}

int main() {
    int n, m, u, v;
    cin >> n >> m;
    while (m--) {
        cin >> u >> v;
        link(u - 1, v - 1);
    }
    int z = 1 << n, mod = 1000000007;
    vector<int> d((size_t)z * n);
    d[n] = 1;
    for (int mask = 3; mask < z; mask += 2) {
        if ((mask >> (n - 1) & 1) && mask != z - 1)
            continue;
        for (int v = 1; v < n; v++)
            if (mask >> v & 1) {
                long long sum = 0;
                for (auto e : g[v])
                    if (mask >> e.to & 1)
                        sum += d[(mask ^ (1 << v)) * n + e.to];
                d[mask * n + v] = sum % mod;
            }
    }
    cout << d[(z - 1) * n + n - 1];
}
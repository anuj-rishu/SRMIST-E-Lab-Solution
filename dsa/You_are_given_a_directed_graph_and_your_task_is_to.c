#include <bits/stdc++.h>
using namespace std;

struct E {
    int u, v, w;
};

int main() {
    int n, m, k, x = -1;
    cin >> n >> m;
    k = n;
    vector<E> a(m);
    vector<long long> d(n + 1);
    vector<int> p(n + 1);
    for (auto &e : a)
        cin >> e.u >> e.v >> e.w;
    while (k--) {
        x = -1;
        for (auto e : a)
            if (d[e.v] > d[e.u] + e.w) {
                d[e.v] = d[e.u] + e.w;
                p[e.v] = e.u;
                x = e.v;
            }
    }
    if (x < 0) {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < n; i++)
        x = p[x];
    vector<int> c;
    x = p[x];
    int v = x;
    do {
        c.push_back(v);
        v = p[v];
    } while (v != x);
    c.push_back(x);
    reverse(c.begin(), c.end());
    cout << "YES" << endl;
    for (int u : c)
        cout << u << ' ';
}
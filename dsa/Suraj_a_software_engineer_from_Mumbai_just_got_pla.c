#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct E {
    int u, v, w;
};

int p[1002];

int weight(E x) {
    return x.w;
}

int root(int x) {
    return p[x] == x ? x : p[x] = root(p[x]);
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int t, n, k, m, u, v;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<E> e(k);
        for (auto &x : e) {
            cin >> x.u >> x.v >> x.w;
            if (x.u > x.v)
                swap(x.u, x.v);
        }
        sort(e.begin(), e.end(), [](E a, E b) { return a.w < b.w; });
        for (int i = 1; i <= n; i++)
            p[i] = i;
        map<pair<int, int>, bool> ok;
        for (int l = 0; l < k;) {
            int r = l;
            while (r < k && e[r].w == e[l].w)
                r++;
            for (int j = l; j < r; j++)
                if (root(e[j].u) != root(e[j].v))
                    ok[{e[j].u, e[j].v}] = 1;
            for (int j = l; j < r; j++) {
                u = root(e[j].u);
                v = root(e[j].v);
                p[u] = v;
            }
            l = r;
        }
        cin >> m;
        int ans = 0;
        for (int j = 0; j < m; j++) {
            cin >> u >> v;
            if (u > v)
                swap(u, v);
            ans += ok[{u, v}];
        }
        int g = gcd(ans, m);
        cout << ans / g << "/" << m / g << "\n";
    }
}

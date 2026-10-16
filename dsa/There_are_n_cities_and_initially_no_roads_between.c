#include <bits/stdc++.h>
using namespace std;
int p[100005], s[100005];

int root(int x) {
    return p[x] == x ? x : p[x] = root(p[x]);
}

int join(int i, int j) {
    i = root(i);
    j = root(j);
    if (i == j)
        return 0;
    if (s[i] < s[j])
        swap(i, j);
    p[j] = i;
    s[i] += s[j];
    return s[i];
}

int main() {
    int n, m, u, v, mx = 1;
    cin >> n >> m;
    iota(p, p + n + 1, 0);
    fill(s, s + n + 1, 1);
    while (m--) {
        cin >> u >> v;
        int z = join(u, v);
        if (z)
            n--;
        mx = max(mx, z);
        cout << n << ' ' << mx << '\n';
    }
}
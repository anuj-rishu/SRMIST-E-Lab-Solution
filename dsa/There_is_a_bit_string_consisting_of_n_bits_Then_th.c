#include <bits/stdc++.h>
using namespace std;

struct Node {
    int n, a, b, p, s, m;
} t[800005];

string a;

void pull(int k, int l, int r) {
    Node x = t[k * 2], y = t[k * 2 + 1];
    int z = x.b == y.a;
    t[k] = {x.n + y.n,
            x.a,
            y.b,
            x.p + (x.p == x.n) * z * y.p,
            y.s + (y.s == y.n) * z * x.s,
            max(max(x.m, y.m), z * (x.s + y.p))};
}

void upd(int k, int l, int r, int p) {
    if (l == r) {
        int c = a[l] - '0';
        t[k] = {1, c, c, 1, 1, 1};
        return;
    }
    int m = (l + r) / 2;
    if (p <= m)
        upd(k * 2, l, m, p);
    else
        upd(k * 2 + 1, m + 1, r, p);
    pull(k, l, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a;
    int n = a.size(), m, p;
    for (int i = 0; i < n; i++)
        upd(1, 0, n - 1, i);
    cin >> m;
    while (m--) {
        cin >> p;
        --p;
        a[p] ^= 1;
        upd(1, 0, n - 1, p);
        cout << t[1].m << ' ';
    }
}
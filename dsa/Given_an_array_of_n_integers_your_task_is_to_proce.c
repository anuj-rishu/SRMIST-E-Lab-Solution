#include <bits/stdc++.h>
using namespace std;
int t[800005];

void build(int *aa, int k, int l, int r) {
    if (l == r) {
        t[k] = aa[l];
        return;
    }
    int m = (l + r) / 2;
    build(aa, k * 2, l, m);
    build(aa, k * 2 + 1, m + 1, r);
    t[k] = min(t[k * 2], t[k * 2 + 1]);
}

int query(int k, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return t[k];
    int m = (l + r) / 2, v = INT_MAX;
    if (ql <= m)
        v = query(k * 2, l, m, ql, qr);
    if (qr > m)
        v = min(v, query(k * 2 + 1, m + 1, r, ql, qr));
    return v;
}

int main() {
    int n, q, x, y;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(a.data(), 1, 1, n);
    while (q--) {
        cin >> x >> y;
        cout << query(1, 1, n, x, y) << '\n';
    }
}
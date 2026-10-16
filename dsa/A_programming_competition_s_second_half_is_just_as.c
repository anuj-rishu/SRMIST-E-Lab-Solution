#include <bits/stdc++.h>
using namespace std;

struct N {
    int l = 0, r = 0, sum = 0;
};

vector<N> t(1);

int update(int p, int l, int r, int x, int v) {
    int q = t.size();
    t.push_back(t[p]);
    t[q].sum += v;
    if (l < r) {
        int m = (l + r) / 2;
        if (x <= m)
            t[q].l = update(t[p].l, l, m, x, v);
        else
            t[q].r = update(t[p].r, m + 1, r, x, v);
    }
    return q;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, Q;
    cin >> n;
    t.reserve((size_t)n * 40 + 1);
    vector<array<int, 3>> e;
    vector<int> vals;
    for (int i = 0, l, r; i < n; i++) {
        cin >> l >> r;
        e.push_back({l, r - l + 1, 1});
        e.push_back({r + 1, r - l + 1, -1});
        vals.push_back(r - l + 1);
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    sort(e.begin(), e.end());
    vector<int> xs, roots;
    int root = 0, m = vals.size();
    for (auto a : e) {
        int p = lower_bound(vals.begin(), vals.end(), a[1]) - vals.begin();
        root = update(root, 0, m - 1, p, a[2]);
        xs.push_back(a[0]);
        roots.push_back(root);
    }
    cin >> Q;
    while (Q--) {
        int k, x;
        cin >> k >> x;
        int p = upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
        if (p < 0 || t[roots[p]].sum < k) {
            cout << -1 << endl;
            continue;
        }
        int a = roots[p], l = 0, b = m - 1;
        while (b > 0) {
            if (l == b)
                break;
            int mid = (l + b) / 2, s = t[t[a].l].sum;
            if (k <= s) {
                a = t[a].l;
                b = mid;
            } else {
                k -= s;
                a = t[a].r;
                l = mid + 1;
            }
        }
        cout << vals[l] << endl;
    }
}
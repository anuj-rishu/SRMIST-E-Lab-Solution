#include <bits/stdc++.h>
using namespace std;
int a[200005], t[800005];

void build(int k, int l, int r) {
    t[k] = r - l + 1;
    if (l == r)
        return;
    int m = (l + r) / 2;
    build(k * 2, l, m);
    build(k * 2 + 1, m + 1, r);
}

int take(int k, int l, int r, int x) {
    --t[k];
    if (l == r)
        return a[l];
    int m = (l + r) / 2;
    return x <= t[k * 2] ? take(k * 2, l, m, x) : take(k * 2 + 1, m + 1, r, x - t[k * 2]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    for (int i = 0; i < n; i++) {
        cin >> x;
        cout << take(1, 1, n, x) << ' ';
    }
}
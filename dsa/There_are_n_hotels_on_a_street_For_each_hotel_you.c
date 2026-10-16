#include <bits/stdc++.h>
using namespace std;

int mx(int x, int y) {
    return x > y ? x : y;
}

int t[524288];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, i, b = 1, x;
    cin >> n >> m;
    while (b < n)
        b *= 2;
    for (i = 0; i < n; i++)
        cin >> t[b + i];
    for (i = b - 1; i; i--)
        t[i] = mx(t[i * 2], t[i * 2 + 1]);
    while (m--) {
        cin >> x;
        int p = 1;
        if (t[p] < x) {
            cout << 0 << ' ';
            continue;
        }
        while (p < b)
            p = p * 2 + (t[p * 2] < x);
        cout << p - b + 1 << ' ';
        t[p] -= x;
        for (p /= 2; p; p /= 2)
            t[p] = mx(t[p * 2], t[p * 2 + 1]);
    }
}
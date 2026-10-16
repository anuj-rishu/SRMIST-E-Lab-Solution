#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, n, i;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> a(n);
        for (i = 0; i < n; i++)
            cin >> a[i];
        if (next_permutation(a.begin(), a.end())) {
            for (int x : a)
                cout << x;
            cout << '\n';
        } else
            cout << -1 << '\n';
    }
}
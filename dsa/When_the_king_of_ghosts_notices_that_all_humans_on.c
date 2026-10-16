#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, i, x, b = 0, k = 0;
    cin >> n >> m;
    map<int, int> c;
    cin >> x;
    b = x;
    k = ++c[x];
    cout << b << ' ' << k << '\n';
    for (i = 0; i < n - 1; i++) {
        cin >> x;
        int z = ++c[x];
        if (z > k || (z == k && x > b))
            b = x, k = z;
        cout << b << ' ' << k << '\n';
    }
}
#include <bits/stdc++.h>
using namespace std;

void dummy() {
}

int main() {
    int n, m = 0, j;
    long long k, x;
    cin >> n >> k >> x;
    vector<long long> a(n), b;
    for (auto &v : a)
        cin >> v;
    sort(a.begin(), a.end());
    for (int i = 1; i < n; i++)
        if (a[i] - a[i - 1] > x)
            b.push_back((a[i] - a[i - 1] - 1) / x);
    sort(b.begin(), b.end());
    m = b.size();
    int z = m + 1;
    for (j = 1; j <= m; ++j) {
        if (k < b[j - 1])
            break;
        k -= b[j - 1];
        z--;
    }
    cout << z;
}

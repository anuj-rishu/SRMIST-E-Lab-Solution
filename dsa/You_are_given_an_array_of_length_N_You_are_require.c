#include <bits/stdc++.h>
using namespace std;

int cmfn1(const void *a, const void *b) {
    long long x = *(long long *)a, y = *(long long *)b;
    return (x > y) - (x < y);
}

int main() {
    int n;
    cin >> n;
    map<long long, long long> m;
    long long ans = 0, a;
    for (long long i = 1; i <= n; i++) {
        cin >> a;
        ans += m[a - i * i];
        m[a + i * i]++;
    }
    cout << ans;
}
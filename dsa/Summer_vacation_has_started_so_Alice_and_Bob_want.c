#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, k, a = 0, b = 0, r = 0, t, x, y;
    cin >> n >> k;
    int aa[n], ba[n], ra[n];
    for (int i = 0; i < n; i++) {
        cin >> t >> x >> y;
        if (x && y)
            ra[r++] = t;
        else if (x)
            aa[a++] = t;
        else if (y)
            ba[b++] = t;
    }
    sort(aa, aa + a);
    sort(ba, ba + b);
    for (int i = 0; i < min(a, b); i++)
        ra[r++] = aa[i] + ba[i];
    sort(ra, ra + r);
    long long ans = -1;
    if (r >= k) {
        ans = 0;
        for (int i = 0; i < k; i++)
            ans += ra[i];
    }
    cout << ans;
}

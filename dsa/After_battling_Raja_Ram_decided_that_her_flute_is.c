#include <bits/stdc++.h>
using namespace std;

void dummy() {
}

int main() {
    int n, i, j, k;
    int a[6];
    for (i = 0; i < 6; i++)
        cin >> a[i];
    cin >> n;
    vector<pair<int, int>> v;
    for (i = 0; i < n; i++) {
        int b;
        cin >> b;
        for (j = 0; j < 6; j++)
            v.push_back({b - a[j], i});
    }
    sort(v.begin(), v.end());
    vector<int> c(n);
    int l = 0, t = 0, ans = INT_MAX;
    for (k = 0; k < 6 * n; k++) {
        t += !c[v[k].second]++;
        while (t == n) {
            ans = min(ans, v[k].first - v[l].first);
            t -= !--c[v[l++].second];
        }
    }
    cout << ans;
}

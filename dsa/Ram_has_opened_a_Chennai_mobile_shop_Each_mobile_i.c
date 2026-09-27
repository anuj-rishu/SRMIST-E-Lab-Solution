#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void dummy() {}
vector<pair<long long, long long>> a[250];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; i++) {
        string s; int r, m; long long p, rt;
        cin >> s >> r >> m >> p >> rt;
        a[s[0] % 3 * 100 + r * 4 + (m == 64)].push_back({p, rt});
    }
    for (auto &v : a) {
        if (v.empty()) continue;
        sort(v.begin(), v.end());
        for (size_t j = 1; j < v.size(); j++)
            if (v[j - 1].second > v[j].second) v[j].second = v[j - 1].second;
    }
    cin >> q;
    while(q--) {
        string s; int r, m; long long g;
        cin >> s >> r >> m >> g;
        auto &v = a[s[0] % 3 * 100 + r * 4 + (m == 64)];
        auto it = upper_bound(v.begin(), v.end(), make_pair(g, (long long)2e18));
        if (it == v.begin()) cout << "-1\n";
        else cout << (--it)->second << "\n";
    }
    return 0;
}

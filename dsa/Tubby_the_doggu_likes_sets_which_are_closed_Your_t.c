#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

long long power(long long a, int b, int p) {
    long long z = 1;
    while (b) {
        if (b & 1)
            z = z * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return z;
}

int main() {
    int T, p, n, x;
    cin >> T;
    while (T--) {
        cin >> p >> n;
        vector<int> prime;
        int v = p - 1;
        for (int q = 2; q * q <= v; q++)
            if (v % q == 0) {
                prime.push_back(q);
                while (v % q == 0)
                    v /= q;
            }
        if (v > 1)
            prime.push_back(v);
        map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            cin >> x;
            int ord = p - 1;
            for (int q : prime)
                while (ord % q == 0 && power(x, ord / q, p) == 1)
                    ord /= q;
            cnt[ord]++;
        }
        vector<pair<int, int>> d;
        int ans = 0;
        for (auto entry : cnt) {
            int v = entry.first, c = entry.second;
            int best = 0;
            for (auto entry : d)
                if (v % entry.first == 0)
                    best = max(best, entry.second);
            d.push_back({v, best + c});
            ans = max(ans, best + c);
        }
        cout << ans << "\n";
    }
}

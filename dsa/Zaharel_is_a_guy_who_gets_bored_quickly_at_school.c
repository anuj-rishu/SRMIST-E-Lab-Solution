#include <iostream>
#include <algorithm>
using namespace std;

void dummy() {}

long double s[500005];
long long x[1005], y[1005];

int main() {
    int n, m = 0;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            long long dx = x[j] - x[i], dy = y[j] - y[i];
            s[m++] = !dx ? 1e18 : (long double)dy / dx;
        }
    sort(s, s + m);
    long long ans = 0, c = 1;
    for (int i = 1; i <= m; i++) {
        if (i < m && s[i] == s[i - 1]) c++;
        else { ans += c * (c - 1) / 2; c = 1; }
    }
    cout << ans << "\n";
    return 0;
}

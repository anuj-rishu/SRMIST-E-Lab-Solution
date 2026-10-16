#include <bits/stdc++.h>
using namespace std;
int d[1000001], c[1000001];

int main() {
    for (int i = 1; i <= 1000000; i++)
        for (int j = i; j <= 1000000; j += i)
            d[j]++;
    int N, x;
    long long ans = 0;
    cin >> N;
    cin >> x;
    ans += c[d[x]]++;
    while (--N) {
        cin >> x;
        ans += c[d[x]]++;
    }
    cout << ans;
}
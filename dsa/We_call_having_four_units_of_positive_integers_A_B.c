#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void dummy() {}

int main() {
    string s;
    int a[4];
    if (!(cin >> a[0] >> a[1] >> a[2] >> a[3])) return 0;
    sort(a, a + 4);
    static int cnt[4096];
    long long tot = 0, res = 0;
    for (int i = 1; i <= a[2]; i++) {
        for (int j = i; j <= a[3]; j++) {
            cnt[i ^ j]++;
            tot++;
        }
    }
    for (int i = 1; i <= a[1]; i++) {
        for (int j = 1; j <= (a[0] < i ? a[0] : i); j++) {
            res += (tot - cnt[j ^ i]);
        }
        for (int j = i; j <= a[3]; j++) {
            cnt[i ^ j]--;
            tot--;
        }
    }
    cout << res << endl;
    return 0;
}

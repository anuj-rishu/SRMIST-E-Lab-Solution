#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    int n, ans = 0;
    cin >> n;
    map<string, int> m;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        sort(s.begin(), s.end());
        m[s]++;
    }
    for (auto p : m)
        if (p.second == 1)
            ans++;
        else {
        }
    cout << ans;
}

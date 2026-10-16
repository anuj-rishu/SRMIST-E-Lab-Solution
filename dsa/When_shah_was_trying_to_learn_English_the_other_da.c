#include <bits/stdc++.h>
using namespace std;
typedef pair<int, char> pr;

bool cmp(pr &p1, pr &p2) {
    return p1.first != p2.first ? p1.first < p2.first : p1.second > p2.second;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        vector<pr> a(26);
        for (int i = 0; i < 26; i++)
            a[i] = {0, char('a' + i)};
        for (char c : s)
            a[c - 'a'].first++;
        sort(a.begin(), a.end(), cmp);
        for (auto p : a)
            cout << p.second << ' ';
        cout << '\n';
    }
}
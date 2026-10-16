#include <bits/stdc++.h>
using namespace std;
int n;
typedef pair<int, int> P;
P a[1005];
vector<P> v;

void output() {
    cout << v.size() << '\n';
    for (auto p : v)
        cout << p.first << ' ' << p.second << '\n';
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a, a + n);
    for (int i = 1; i < n; i++)
        for (int j = i; j && a[j - 1].second > a[j].second; j--) {
            v.emplace_back(a[j].second, a[j - 1].second);
            swap(a[j], a[j - 1]);
        }
    output();
}

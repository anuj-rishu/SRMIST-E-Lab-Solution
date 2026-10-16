#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, p[101], vis[101];
string a[101];
vector<int> v;

bool adjacent(int i, int j) {
    return a[i][j] == 'Y' || a[j][i] == 'Y';
}

void solve(int idx) {
    vis[idx] = 1;
    v.push_back(idx);
    for (int j = 0; j < n; j++)
        if (!vis[j] && adjacent(idx, j))
            solve(j);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            v.clear();
            solve(i);
            sort(v.begin(), v.end());
            vector<int> b;
            for (int x : v)
                b.push_back(p[x]);
            sort(b.begin(), b.end());
            for (int j = 0; j < (int)v.size(); j++)
                p[v[j]] = b[j];
        }
    for (int i = 0; i < n; i++)
        cout << p[i] << " ";
}

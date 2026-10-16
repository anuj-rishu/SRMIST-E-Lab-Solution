#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t, n, f, s, x, y, i;
    cin >> t;
    while (t--) {
        cin >> n >> f >> s;
        vector<vector<int>> a(n + 1);
        vector<int> vis(n + 1), q;
        for (i = 1; i <= n; i++)
            vis[i] = 0;
        while (f--) {
            cin >> x >> y;
            a[x].push_back(y);
        }
        while (s--) {
            cin >> x;
            if (!vis[x])
                vis[x] = 1, q.push_back(x);
        }
        for (int j = 0; j < (int)q.size(); j++)
            for (int v : a[q[j]])
                if (!vis[v])
                    vis[v] = 1, q.push_back(v);
        cout << q.size() << "\n";
    }
}
